/*
 * ModBasicData.cpp
 *
 *  Created on: Feb 25, 2023
 *      Author: llanyro
 */

#include "ModBasicData.hpp"

//#include <type_traits>

#if defined(_WIN32) or defined(_WIN64)
#include "../windows/pch.h"
#endif // _WIN32 || _WIN64

namespace llcpp {
namespace modlibcore {

ModBasicData::ModBasicData(std::string&& modName, std::string&& modVersion)
: modName(std::move(modName)), modVersion(std::move(modVersion)) {}
ModBasicData::~ModBasicData() {}
const std::string& ModBasicData::getModName() const { return this->modName; }
const std::string& ModBasicData::getModVersion() const { return this->modVersion; }
bool ModBasicData::operator==(const ModBasicData& other) const {
	return this->modName == other.modName && this->modVersion == other.modVersion;
}

} /* namespace modlibcore */
} /* namespace llcpp */
