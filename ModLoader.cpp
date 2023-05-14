/*
 * ModLoader.cpp
 *
 *  Created on: Feb 22, 2023
 *      Author: llanyro
 */

#include "ModLoader.hpp"

#include "libs/libmodbase.hpp"
#include "libs/libmodenums.hpp"

#include "objects/ModData.hpp"
#include "objects/ModCore.hpp"
#include "objects/ModInfoExtra.hpp"

#include "libs/vector.hpp"
#include "libs/list.hpp"

#pragma region Includes

/// System includes

// If cant include or use std::filesystem
#if !(__cplusplus < 201703L)
#include <dirent.h>
#define LL_FILESYSTEM_NOT_SUPPORTED_
#else
#include <filesystem>
#endif

#include <string>

#pragma endregion

namespace modlib as llcpp::modlibcore;
namespace fs as std::filesystem;

#pragma region NotClassFunctions
void doNothing(void*) {}

#if !defined(FALSE_LL_LIB)
void deleteModInfoEx(void* a) {
    if (a != LL_NULLPTR)
        delete* reinterpret_cast<modlib::ModInfoExtra**>(a);
}
#else
void deleteModInfoEx(void* a) {
    if (a != LL_NULLPTR)
        delete reinterpret_cast<modlib::ModInfoExtra*>(a);
}
#endif

// Stored inside namespaces to not be called wrongly
namespace llcpp {
namespace modlibcore {

// For event list
BasicEvent __modListsEvent__ = {
    doNothing,
    doNothing,
    doNothing,
    deleteModInfoEx
};

} /* namespace modlibcore */
} /* namespace llcpp */

// For reading all files by estension in a folder
#if defined(FILESYSTEM_NOT_SUPPORTED)
List<std::string>* loadModFolder(ll_str_t modFolderPath, ll_str_t ext) {
    List<std::string>* l = new List<std::string>();
    DIR* dir;
    struct dirent* entry;
    if ((dir = opendir(modFolderPath)) != NULL) {
        while ((entry = readdir(dir)) != NULL) {
            std::string filename = entry->d_name;
            size_t pos = filename.find_last_of(".");
            if (pos != std::string::npos && filename.substr(pos) == ext) {
                std::string str = std::string(modFolderPath) + "/" + filename;
                l->push_back(str);
            }
        }
        closedir(dir);
    }
    else {
        fprintf(stderr, "Error: could not open directory %s\n", modFolderPath);
    }
    return l;
}
#else
List<std::string>* loadModFolder(ll_str_t modFolderPath, ll_str_t ext) {
    List<std::string>* l = new List<std::string>();
    if (fs::exists(modFolderPath))
        for (const auto& entry : fs::directory_iterator(modFolderPath))
            if (entry.path().extension() == ext) {
                auto a = entry.path().native();
                l->add(std::string(a.begin(), a.end()));
            }
    return l;
}
#endif

modlib::ModInfoExtra* getModInfoEx(const std::string& mod) {
    modlib::ModInfoExtra* info = new modlib::ModInfoExtra();
    info->setStatusID(modlib::enums::StatusID::OK);
    info->setFilename(strdup(mod.c_str()));

    ll_lib_t hModule = load_lib(info->getFilename());
    if (hModule == LL_NULLPTR) {
        info->setStatusID(modlib::enums::StatusID::ERROR_OPENING_MOD);
        fprintf(stderr, "%s\n", dlerror());
        return info;
    }
    info->setModHandle(hModule);

    modlib::GetModCore getModCore = (modlib::GetModCore)get_lib_address(hModule, "getModCore");
    if (getModCore == LL_NULLPTR) {
        info->setStatusID(modlib::enums::StatusID::ERROR_GET_MOD_CORE);
        close_lib(hModule);
        return info;
    }

    const modlib::ModCore* core = getModCore();
    if (core) {
        info->setModCore(core);
        const modlib::ModData* data = core->getModData();
        if (data) {
            if (!data->getModName()) info->setStatusID(
                modlib::enums::StatusID::ERROR_MOD_NAME_NULL);
            elif(!data->getModVersion()) info->setStatusID(
                modlib::enums::StatusID::ERROR_MOD_VERSION_NULL);
            else {
                const modlib::vector::Vector<modlib::ModBasicData*>* 
                    data_arr = data->getDependences();
                const modlib::vector::Vector<modlib::ModBasicData*>* 
                    data_arr_ex = data->getDependencesExtra();

                modlib::vector::Vector<const modlib::ModInfo*>*
                    data_arr_ret = data->getDependencesReturned();
                modlib::vector::Vector<const modlib::ModInfo*>*
                    data_arr_ex_ret = data->getDependencesExtraReturned();

                // If mod has dependedces, but vector to store it is different size
                if(data_arr && data_arr_ret)
                    if(data_arr->size() != data_arr_ret->size())
                        info->setStatusID(
                            modlib::enums::StatusID::ERROR_DEPENDENCES_NO_VALID_CORRELATION_1);

                if(data_arr_ex && data_arr_ex_ret)
                    if(data_arr_ex->size() != data_arr_ex_ret->size())
                        info->setStatusID(
                            modlib::enums::StatusID::ERROR_DEPENDENCES_NO_VALID_CORRELATION_2);
            }
        }
        else info->setStatusID(modlib::enums::StatusID::ERROR_MOD_DATA_NULL);
    }
    else info->setStatusID(modlib::enums::StatusID::ERROR_MOD_CORE_NULL);

    return info;
}

#pragma endregion

namespace llcpp {
namespace modlibcore {

void ModLoader::clearMods() {
    #if !defined(FALSE_LL_LIB)
    if (this->modsInfo) delete this->modsInfo;
    if (this->modsInfoErr) delete this->modsInfoErr;
    #else
    if (this->modsInfo) {
        this->modsInfo->foreach(deleteModInfoEx);
        delete this->modsInfo;
    }
    if (this->modsInfoErr) {
        this->modsInfoErr->foreach(deleteModInfoEx);
        delete this->modsInfoErr;
    }
    #endif

    this->modsInfo = LL_NULLPTR;
    this->modsInfoErr = LL_NULLPTR;
    this->path = LL_NULLPTR;
    this->os = enums::OSSystem::NULL_OS;
}

ModLoader::ModLoader(const enums::OSSystem& os, ll_str_t modFolderPath)
    : os(os), path(modFolderPath)
    , modsInfo(new ModEventList())
    , modsInfoErr(new ModEventList())
{}
ModLoader::ModLoader(const enums::OSSystem& os) : ModLoader(os, "./mods") {}
ModLoader::~ModLoader() { this->clearMods(); }

ll_int64_t ModLoader::load() {
    ll_int64_t numErrors = 0;

    // Get all mods of folder
    List<std::string>* mods = loadModFolder(this->path, 
        (this->os == enums::OSSystem::WINDOWS ? ".dll" : ".so")
    );

    // Get info of all mods loaded
    auto getModsInfoLambda = [this, &numErrors](const std::string& modPathName) {
        fprintf(stderr, "%s\n", modPathName.c_str());
        ModInfoExtra* info = getModInfoEx(modPathName);
        if (info->getStatusID() == enums::StatusID::OK) this->modsInfo->add(info);
        else {
            this->modsInfoErr->add(info);
            numErrors++;
        }
    };
    mods->foreach(getModsInfoLambda);


    // Mods path is needed no more
    delete mods;

    // Check duplicates
    /// No, user needs to check if he wants
    /// Duplicate?, Whats a duplicate mod?
    /// Same modName? Same version? Same dependences?

    // Check dependences
    List<ll_int32_t> listPosErrors;
    ll_int32_t pos = 0;
    auto dependenceCheckerLambda =
        [this, &numErrors, &pos, &listPosErrors]
        (ModInfoExtra* info) {
        // Get mod data to get dependences
        const ModData* data = info->getModCore()->getModData();

        // Get dependence list
        const modlib::vector::Vector<modlib::ModBasicData*>* data_arr =
            data->getDependences();
        // Get dependence return
        modlib::vector::Vector<const modlib::ModInfo*>* data_arr_ret =
            data->getDependencesReturned();

        // Get dependence list
        const modlib::vector::Vector<modlib::ModBasicData*>* data_arr_ex =
            data->getDependencesExtra();
        // Get dependence return
        modlib::vector::Vector<const modlib::ModInfo*>* data_arr_ex_ret =
            data->getDependencesExtraReturned();


        // Check dependences and store it
        // If found -> store in mod return
        // If not found -> store in error list
        auto f2f = 
            [&info, this] 
            (const modlib::vector::Vector<modlib::ModBasicData*>* vec,
            modlib::vector::Vector<const modlib::ModInfo*>* ret) {
            const ModBasicData* tmp = LL_NULLPTR;
            const ModInfo* tmp_core = LL_NULLPTR;
            // Returns true if found
            // Also, tmp_core should point to core
            auto f2f2 = [&tmp, &tmp_core](ModInfoExtra* info) {
                if (info->operator==(*tmp)) {
                    tmp_core = info;
                    return true;
                }
                else
                    return false;
            };

            for (len_t i = 0; i < vec->size(); i++) {
                tmp = *vec->cget(i);
                if (!this->modsInfo->find(f2f2))
                    info->getDependencesNotFound()->add(tmp);
                // If dependence is found we need to add to mod dependence list
                else
                    ret->set(tmp_core, i);
            }
        };

        if(data_arr && data_arr_ret)
            f2f(data_arr, data_arr_ret);
        if (data_arr_ex && data_arr_ex_ret)
            f2f(data_arr_ex, data_arr_ex_ret);


        // If an error happened
        if (info->getDependencesNotFound()->len() > 0) {
            listPosErrors.add(pos);
            numErrors++;
        }
        pos++;
    };
    this->modsInfo->foreach(dependenceCheckerLambda);

    // Extract errors from list
    pos = 0;
    listPosErrors.foreach([this, &pos](ll_int32_t& val) {
        this->modsInfo->moveNode(val - pos, this->modsInfoErr);
        pos++;
    });
    return numErrors;
}

ModEventList* ModLoader::getLoadedMods() { return this->modsInfo; }
ModEventList* ModLoader::getErrorMods() { return this->modsInfoErr; }

ModVector* ModLoader::getModsToUse() {
    ModVector* v = new ModVector(this->modsInfo->len());
    len_t pos = 0;

    this->modsInfo->foreach([&v, &pos](ModInfoExtra* info) {
        v->set(info->extractBasicInfo(), pos);
        pos++;
    });

    return v;
}

} /* namespace modlibcore */
} /* namespace llcpp */
