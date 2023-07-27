/*
 * ModLoader.cpp
 *
 *  Created on: Feb 22, 2023
 *	  Author: llanyro
 */

#include "ModLoader.hpp"

#include "libs/libmodbase.hpp"
#include "libs/libmodenums.hpp"

#include "objects/ModData.hpp"
#include "objects/ModCore.hpp"
#include "objects/ModInfoExtra.hpp"

#include <filesystem>
#include <algorithm>
#include <string>

#if defined(_WIN32) or defined(_WIN64)
#include "windows/pch.h"
#endif // _WIN32 || _WIN64

namespace modlib = llcpp::modlibcore;

// For reading all files by estension in a folder
void loadModFolder(const std::string& modFolderPath, const char* ext, std::vector<std::string>& l) {
	if (std::filesystem::exists(modFolderPath))
		for (const auto& entry : std::filesystem::directory_iterator(modFolderPath))
			if (entry.path().extension() == ext) {
				auto a = entry.path().native();
				l.push_back(std::string(a.begin(), a.end()));
			}
}

modlib::ModInfoExtra* getModInfoEx(const std::string& mod) {
	modlib::ModInfoExtra* info = new modlib::ModInfoExtra();
	info->setStatusID(modlib::enums::StatusID::OK);
	info->setFilename(mod);

	ll_lib_t hModule = load_lib(info->getFilename().c_str());
	if (!hModule) {
		info->setStatusID(modlib::enums::StatusID::ERROR_OPENING_MOD);
		fprintf(stderr, "%s\n", dlerror());
		return info;
	}
	info->setModHandle(hModule);

	modlib::GetModCore getModCore = (modlib::GetModCore)get_lib_address(hModule, GET_MOD_CORE);
	if (!getModCore) {
		info->setStatusID(modlib::enums::StatusID::ERROR_GET_MOD_CORE);
		close_lib(hModule);
		return info;
	}

	modlib::ModCore* core = getModCore();
	if (core) {
		info->setModCore(core);
		modlib::ModData* data = core->getModData();
		if (data) {
			if (data->getModName().empty())
				info->setStatusID(modlib::enums::StatusID::ERROR_MOD_NAME_NULL);
			else if(data->getModVersion().empty())
				info->setStatusID(modlib::enums::StatusID::ERROR_MOD_VERSION_NULL);
			else {
				const std::vector<modlib::ModBasicData*>& data_arr = data->getDependencesRequired();
				const std::vector<modlib::ModBasicData*>& data_arr_ex = data->getDependencesOptional();

				std::vector<const modlib::ModInfo*>& data_arr_ret = data->getDependenceRequiredReturned();
				std::vector<const modlib::ModInfo*>& data_arr_ex_ret = data->getDependenceOptionalReturned();

				// Prepare return vector to return data
				if (data_arr.size() > 0) data_arr_ret.reserve(data_arr.size());
				if (data_arr_ex.size() > 0) data_arr_ex_ret.reserve(data_arr_ex.size());
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
	for (auto& i : this->modsInfo) delete i;
	for (auto& i : this->modsInfoErr) delete i;
}

ModLoader::ModLoader(std::string modFolderPath)
	: path(std::move(modFolderPath))
	, modsInfo()
	, modsInfoErr()
{}
ModLoader::~ModLoader() { this->clearMods(); }

std::size_t ModLoader::load() {
	std::size_t numErrors = 0;

	const char* extension = nullptr;
	std::vector<std::string> mods;
	// Get all mods of folder
	#if defined(_WIN32) or defined(_WIN64)
	extension = ".dll";
	#else
	extension = ".so";
	#endif // _WIN32 || _WIN64
    loadModFolder(this->path, extension, mods);


	// Get info of all mods loaded
	auto getModsInfoLambda = [this, &numErrors](const std::string& modPathName) {
		fprintf(stderr, "%s\n", modPathName.c_str());
		ModInfoExtra* info = getModInfoEx(modPathName);
		if (info->getStatusID() == enums::StatusID::OK)
			this->modsInfo.push_back(info);
		else {
			this->modsInfoErr.push_back(info);
			numErrors++;
		}
	};
	for (auto& i : mods)
		getModsInfoLambda(i);

	// Mods path is needed no more
	mods.clear();

	// Check duplicates
	/// No, user needs to check if he wants
	/// Duplicate?, Whats a duplicate mod?
	/// Same modName? Same version? Same dependences?

	// Check dependences
	std::vector<std::size_t> listPosErrors;
	std::size_t pos = 0;
	auto dependenceCheckerLambda =
		[this, &numErrors, &pos, &listPosErrors]
		(ModInfoExtra* info) {
		// Get mod data to get dependences
		ModData* data = info->getModCore()->getModData();

		const std::vector<modlib::ModBasicData*>& data_arr = data->getDependencesRequired();
		std::vector<const modlib::ModInfo*>& data_arr_ret = data->getDependenceRequiredReturned();

		const std::vector<modlib::ModBasicData*>& data_arr_ex = data->getDependencesOptional();
		std::vector<const modlib::ModInfo*>& data_arr_ex_ret = data->getDependenceOptionalReturned();

		// Check dependences and store it
		// If found -> store in mod return
		// If not found -> store in error list
		auto f2f = 
			[&info, this] 
			(const std::vector<modlib::ModBasicData*>& vec,
			std::vector<const modlib::ModInfo*>& ret) {
			const ModBasicData* tmp = nullptr;
			const ModInfo* tmp_core = nullptr;
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
			for (auto& i : vec) {
				auto it = std::find_if(this->modsInfo.begin(), this->modsInfo.end(), f2f2);
				if (it != this->modsInfo.end())
					ret.push_back(tmp_core);
				else {
					ret.push_back(nullptr);
					info->addDependencesNotFound(i);
				}
			}
		};

		if(!data_arr.empty())
			f2f(data_arr, data_arr_ret);
		if (!data_arr_ex.empty())
			f2f(data_arr_ex, data_arr_ex_ret);


		// If an error happened
		if (!info->getDependencesNotFound().empty()) {
			listPosErrors.push_back(pos);
			numErrors++;
		}
		pos++;
	};
	for(auto& i : this->modsInfo)
		dependenceCheckerLambda(i);

	// Extract errors from list
	pos = 0;
	for (auto& i : listPosErrors) {
		// Get iterator of mod
		auto it = this->modsInfo.begin() + i - pos;
		this->modsInfoErr.insert(this->modsInfoErr.end(), std::move(*it));
		this->modsInfo.erase(it);
	}
	return numErrors;
}

const std::vector<const ModInfoExtra*>& ModLoader::getLoadedMods() const {
	return reinterpret_cast<const std::vector<const ModInfoExtra*>&>((this->modsInfo));
}
const std::vector<const ModInfoExtra*>& ModLoader::getErrorMods() const {
	return reinterpret_cast<const std::vector<const ModInfoExtra*>&>((this->modsInfoErr));
}

void ModLoader::getModsToUse(std::vector<const ModInfo*>& v) {
	for (auto& i : this->modsInfo)
		v.push_back(i);
}

} /* namespace modlibcore */
} /* namespace llcpp */
