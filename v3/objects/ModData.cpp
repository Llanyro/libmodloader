/*
 * ModData.cpp
 *
 *  Created on: Feb 25, 2023
 *      Author: llanyro
 */

#include "ModData.hpp"

//#include <type_traits>

#if defined(_WIN32) or defined(_WIN64)
#include "../windows/pch.h"
#endif // _WIN32 || _WIN64


namespace llcpp {
namespace modlibcore {

ModData::ModData(std::string&& modName, std::string&& modVersion)
	: ModBasicData(std::move(modName), std::move(modVersion))
	, dependencesRequired()
	, dependencesOptional()
	, dependencesRequiredReturned()
	, dependencesOptionalReturned()
{}
ModData::~ModData() {
	for (auto& i : this->dependencesRequired)
		delete i;
	for (auto& i : this->dependencesOptional)
		delete i;
}

void ModData::addDependencesRequired(ModBasicData* dependence) {
	this->dependencesRequired.push_back(dependence);
}
void ModData::addDependencesOptional(ModBasicData* dependence) {
	this->dependencesOptional.push_back(dependence);
}

const std::vector<ModBasicData*>& ModData::getDependencesRequired() const {
	return this->dependencesRequired;
}
const std::vector<ModBasicData*>& ModData::getDependencesOptional() const {
	return this->dependencesOptional;
}

std::vector<const ModInfo*>& ModData::getDependenceRequiredReturned() {
	return this->dependencesRequiredReturned;
}
std::vector<const ModInfo*>& ModData::getDependenceOptionalReturned() {
	return this->dependencesOptionalReturned;
}


} /* namespace modlibcore */
} /* namespace llcpp */
