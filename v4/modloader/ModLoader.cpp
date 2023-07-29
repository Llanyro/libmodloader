/*
 * ModLoader.cpp
 *
 *  Created on: Feb 25, 2023
 *      Author: llanyro
 */

#include "ModLoader.hpp"

#include <llexpresions.hpp>


#include "libfunctions.hpp"
#include "libmodenums.hpp"

#include "ModInfoExtra.hpp"

#include "../mod/ModCore.hpp"

#include <filesystem>

namespace llcpp {
namespace modlibcore {
namespace v4 {

// For reading all files by estension in a folder
std::vector<std::string> loadModFolder(ll_string_t modFolderPath, ll_string_t ext) {
    std::vector<std::string> l;
	if (std::filesystem::exists(modFolderPath))
		for (const auto& entry : std::filesystem::directory_iterator(modFolderPath))
			if (entry.path().extension() == ext) {
				auto a = entry.path().native();
				l.push_back(std::string(a.begin(), a.end()));
			}
    return l;
}
ModInfoExtra* ModLoader::getModInfoEx(std::string& modName) const {
	ModInfoExtra* infoExtra = new ModInfoExtra();

	if(modName.empty()) {
		infoExtra->setStatusID(enums::StatusID::FILENAME_EMPTY);
		return infoExtra;
	}

	// Ok init set
	infoExtra->setStatusID(enums::StatusID::OK);
	infoExtra->setFilename(std::move(modName));

	// Get the mod
	ll_lib_t handle = load_lib(infoExtra->getFilename().c_str());
	if (!handle) {
		infoExtra->setStatusID(enums::StatusID::ERROR_OPENING_MOD);
		if(this->vervoseLevel == 1)
			fprintf(stderr, "%s\n", dlerror());
		return infoExtra;
	}
	// Get pointer to module
	infoExtra->setModHandle(handle);

	// Now we get mod data by standard
	GetModCore getModCore = 
		reinterpret_cast<GetModCore>(get_lib_address(handle, GET_MOD_CORE));

	if (!getModCore) {
		infoExtra->setStatusID(enums::StatusID::ERROR_GET_MOD_CORE);
		infoExtra->setModHandle(LL_NULLPTR);
		close_lib(handle);
		return infoExtra;
	}

	ModCore* modCore = getModCore();

	if(!modCore) {
		infoExtra->setStatusID(enums::StatusID::ERROR_MOD_CORE_NULL);
		return infoExtra;
	}

	infoExtra->setModCore(modCore);
	ModData* modData = modCore->getModData();

	if(!modData) {
		infoExtra->setStatusID(enums::StatusID::ERROR_MOD_DATA_NULL);
		return infoExtra;
	}

	if(!modData->getModName()) {
		infoExtra->setStatusID(enums::StatusID::ERROR_MOD_NAME_NULL);
		return infoExtra;
	}

	if(!modData->getModName()) {
		infoExtra->setStatusID(enums::StatusID::ERROR_MOD_VERSION_NULL);
		return infoExtra;
	}

	modData->resizeOut();

	return infoExtra;
}

void ModLoader::clearMods() {
	for (auto& i : this->modsInfo) delete i.second;
	for (ModInfoExtra*& i : this->modsInfoErr) delete i;
}

ModLoader::ModLoader(ll_string_t modFolderPath)
	: path(modFolderPath)
	, modsInfo()
	, modsInfoErr()
	, vervoseLevel(0)
{}
ModLoader::~ModLoader() { this->clearMods(); }

void ModLoader::setVervoseLevel(const ui8 v) { this->vervoseLevel = v; }


len_t ModLoader::load() {

	// Get all mods filenames!
	std::vector<std::string> mods =
        loadModFolder(
            this->path,
            llcpp::header::expresions::extensions::DLL_EXTENSION_STR);
    

	// Now we open mod to mod and store its data in class data
	for(auto& modName : mods) {
		if(this->vervoseLevel == 3)
			fprintf(stdout, "Mod folder to analize: %s\n", modName.c_str());

		ModInfoExtra* infoExtra = this->getModInfoEx(modName);
		if(infoExtra->getStatusID() != enums::StatusID::OK)
			this->modsInfoErr.push_back(infoExtra);
		else
			this->modsInfo.insert({
				infoExtra->getModCore()->getModBasicData()->hash(),
				infoExtra
			});
	}
	
	// Now, we dont need mods vector anymore
	mods.clear();

	// Check dependences
	std::vector<ModMap::iterator> errorsIterators;

	for (auto it = this->modsInfo.begin(); it != this->modsInfo.end(); it++) {
		ModData* data = it->second->getModCore()->getModData();
		for(auto& dep : data->getDependences()) {
			auto res = this->modsInfo.find(dep.hash());
			if(res != this->modsInfo.end())
				data->addDependenceOut(res->second);
			else {
				errorsIterators.push_back(it);
				data->addDependenceOut(LL_NULLPTR);
			}
		}
		// Optional dependences do not count as an error
		// So the iterator will not be saved
		for(auto& dep : data->getOptionalDependences()) {
			auto res = this->modsInfo.find(dep.hash());
			if(res != this->modsInfo.end())
				data->addDependenceOut(res->second);
			else
				data->addDependenceOut(LL_NULLPTR);
		}
	}
	
	// We remove each iterator and insert in error list
	for(auto& i : errorsIterators) {
		ModInfoExtra* infoExtra = i->second;
		this->modsInfo.erase(i);
		this->modsInfoErr.push_back(infoExtra);
	}


    return this->modsInfoErr.size();
}


const ModLoader::ModMap& ModLoader::getLoadedMods() const { return this->modsInfo; }
const ModLoader::ModVector& ModLoader::getErrorMods() const { return this->modsInfoErr; }

std::vector<const ModInfo*> ModLoader::getModsToUse() const {
	std::vector<const ModInfo*> mods;
	for (auto& i : this->modsInfo)
		mods.push_back(i.second);
	return mods;
}

} /* namespace v4 */
} /* namespace modlibcore */
} /* namespace llcpp */
