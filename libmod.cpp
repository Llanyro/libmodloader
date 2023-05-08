/*
 * libmod.cpp
 *
 *  Created on: Feb 22, 2023
 *      Author: llanyro
 */

#include "libmod.hpp"

#include "libmodbase.hpp"
#include "libmodenums.hpp"

#include "ModInfo.hpp"

#include <string>
#include <filesystem>

#if !defined(FALSE_LL_LIB)
#define LOAD_EVENTS
#include "../../../llcpp/util/list/vector/Vector.hpp"
#include "../../../llcpp/util/list/linked/LinkedList.hpp"
#else
#include "falselllib.hpp"
#endif

namespace llcpp {
namespace modlibcore {
namespace v2 {

void doNothing(void*) {}

#if !defined(FALSE_LL_LIB)
void deleteModInfoEx(void* a) {
    if (a != LL_NULLPTR)
        delete* reinterpret_cast<llcpp::modlibcore::v2::ModInfoEx**>(a);
}
#else
void deleteModInfoEx(void* a) {
    if (a != LL_NULLPTR)
        delete reinterpret_cast<llcpp::modlibcore::v2::ModInfoEx*>(a);
}
#endif

// For event list
BasicEvent __modListsEvent__{
    doNothing,
    doNothing,
    doNothing,
    deleteModInfoEx
};


List<std::string>* loadModFolder(ll_str_t modFolderPath, ll_str_t ext) {
    List<std::string>* l = new List<std::string>();
    if (std::filesystem::exists(modFolderPath))
        for (const auto& entry : std::filesystem::directory_iterator(modFolderPath))
            if (entry.path().extension() == ext) {
                auto a = entry.path().native();
                l->add(std::string(a.begin(), a.end()));
            }
    return l;
}
ModInfoEx* getModInfoEx(const std::string& mod) {
    ModInfoEx* info = new ModInfoEx();
    info->setStatusID(enums::StatusID::OK);
    info->setFilename(strdup(mod.c_str()));

    ll_lib_t hModule = load_lib(info->getFilename());
    if (hModule == LL_NULLPTR) {
        info->setStatusID(enums::StatusID::ERROR_OPENING_MOD);
        return info;
    }
    info->setModHandle(hModule);

    GetModData getModData = (GetModData)get_lib_address(hModule, "getModData");
    if (getModData == LL_NULLPTR) {
        info->setStatusID(enums::StatusID::ERROR_GET_MOD_DATA);
        close_lib(hModule);
        return info;
    }

    ModData* data = getModData();
    if (data) {
        info->setModData(data);
        if(!data->getModName()) info->setStatusID(enums::StatusID::ERROR_MOD_NAME_NULL);
        elif(!data->getModVersion()) info->setStatusID(enums::StatusID::ERROR_MOD_VERSION_NULL);
        else {
            const ModBasicData* data_arr = data->getDependences();
            len_t len = data->getNumDependences();
            const ModBasicData* data_arr_ex = data->getDependencesExtra();
            len_t len_ex = data->getNumDependencesExtra();

            if(!data_arr && len > 0) info->setStatusID(enums::StatusID::ERROR_DEPENDENCES_NO_VALID_CORRELATION_1);
            elif(data_arr && len == 0) info->setStatusID(enums::StatusID::ERROR_DEPENDENCES_NO_VALID_CORRELATION_2);

            //elif(!data_arr_ex && len_ex > 0) info->setStatusID(enums::StatusID::ERROR_DEPENDENCES_EXTRA_NO_VALID_CORRELATION_1);
            //elif(data_arr_ex && len_ex == 0) info->setStatusID(enums::StatusID::ERROR_DEPENDENCES_EXTRA_NO_VALID_CORRELATION_2);
        }
    }
    else info->setStatusID(enums::StatusID::ERROR_MOD_DATA_NULL);

    return info;
}
ll_bool_t compareDependence(const void* data, const void* dep) {
    const ModInfoEx* info = *(const ModInfoEx**)data;
    const ModBasicData* depend = *(const ModBasicData**)dep;
    return info->operator==(*depend);
}

ModLoader::ModLoader(const enums::OSSystem& os, ll_str_t modFolderPath)
: os(os), path(modFolderPath) {
    this->modsInfo = new ModEventList();
    this->modsInfoErr = new ModEventList();
}
ModLoader::ModLoader(const enums::OSSystem& os) : ModLoader(os, "./mods") {}
ModLoader::~ModLoader() {
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
}
ll_int64_t ModLoader::load() {
    ll_int64_t numErrors = 0;

    // Get all mods of folder
    List<std::string>* mods = loadModFolder(this->path, 
        (this->os == enums::OSSystem::WINDOWS ? ".dll" : ".so")
    );

    // Get info of all mods loaded
    auto f1 = [this, &numErrors](const std::string& modPathName) {
        ModInfoEx* info = getModInfoEx(modPathName);
        if (info->getStatusID() == enums::StatusID::OK) this->modsInfo->add(info);
        else {
            this->modsInfoErr->add(info);
            numErrors++;
        }
    };
    mods->foreach(f1);


    // Mods path is needed no more
    delete mods;

    // Check duplicates
    /// No, user needs to check if he wants
    /// Duplicate?, Whats a duplicate mod?
    /// Same modName? Same version? Same dependences?

    // Check dependences
    List<ll_int32_t> listPosErrors;
    ll_int32_t pos = 0;
    auto f2 = [this, &numErrors, &pos, &listPosErrors](ModInfoEx* info) {
        // Init dependence Error List
        //info->dependencesNotFound = new List<const ModBasicData*>();

        const ModData* data = info->getModData();
        const ModBasicData* dep = data->getDependences();

        //ModInfoEx* tmp = LL_NULLPTR;
        const ModBasicData* tmp = LL_NULLPTR;
        auto f2f = [&tmp](ModInfoEx* info) { return info->operator==(*tmp); };

        // Foreach dependence
        for (len_t i = 0; i < data->getNumDependences(); i++) {
            // If it doesnt exists
            //tmp = (ModInfoEx*)&dep[i];
            tmp = &dep[i];
            if (!this->modsInfo->find(f2f))
                info->getDependencesNotFound()->add(&dep[i]);
            // If dependence is found we need to add to mod dependence list
            else {

            }
        }

        // If an error happened
        if (info->getDependencesNotFound()->len() > 0) {
            listPosErrors.add(pos);
            numErrors++;
        }
        pos++;
    };
    this->modsInfo->foreach(f2);

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

    this->modsInfo->foreach([&v, &pos](ModInfoEx* info) {
        v->set(info->extractBasicInfo(), pos);
        pos++;
    });

    return v;
}

} /* namespace v2 */
} /* namespace modlibcore */
} /* namespace llcpp */
