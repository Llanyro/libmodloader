/*
 * ModBasicData.cpp
 *
 *  Created on: Feb 25, 2023
 *      Author: llanyro
 */

#include "ModBasicData.hpp"

#include <string.h>
#include <stdexcept>

///#define UNDEFINED_MOD "undefined"
///#define UNDEFINED_VERSION "0"

namespace llcpp {
namespace modlibcore {

///ModBasicData::ModBasicData() : ModBasicData(UNDEFINED_MOD, UNDEFINED_VERSION) {}
ModBasicData::ModBasicData(ll_str_t modName, ll_str_t modVersion)
: modName(modName), modVersion(modVersion) {}
ll_str_t ModBasicData::getModName() const { return this->modName; }
ll_str_t ModBasicData::getModVersion() const { return this->modVersion; }
ll_bool_t ModBasicData::operator==(const ModBasicData& other) const {
	return
		(strcmp(this->getModName(), other.getModName()) == 0) &&
		(strcmp(this->getModVersion(), other.getModVersion()) == 0);
}

} /* namespace modlibcore */
} /* namespace llcpp */
