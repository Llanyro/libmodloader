/*
 * modapi.hpp
 *
 *  Created on: Feb 25, 2023
 *      Author: llanyro
 */

#include "modapi.hpp"

#include <string.h>

#define UNDEFINED_MOD "undefined"
#define UNDEFINED_VERSION "0"

namespace llcpp {
namespace modlibcore {
namespace v2 {

ModBasicData::ModBasicData() : ModBasicData(UNDEFINED_MOD, UNDEFINED_VERSION) {}
ModBasicData::ModBasicData(ll_str_t modName, ll_str_t modVersion)
: modName(modName), modVersion(modVersion) {}
ll_str_t ModBasicData::getModName() const { return this->modName; }
ll_str_t ModBasicData::getModVersion() const { return this->modVersion; }
void ModBasicData::setModName(ll_str_t str) { this->modName = str ? str : UNDEFINED_MOD; }
void ModBasicData::setModVersion(ll_str_t str) { this->modName = str ? str : UNDEFINED_VERSION; }
ll_bool_t ModBasicData::operator==(const ModBasicData& other) {
	return
		(strcmp(this->getModName(), other.getModName()) == 0) &&
		(strcmp(this->getModVersion(), other.getModVersion()) == 0);
}

ModData::ModData(ll_str_t modName, ll_str_t modVersion, const len_t& numDependences, const len_t& numDependencesExtra) 
	: ModBasicData(modName, modVersion) {
	
	this->dependences = (numDependences > 0)
		? new ModBasicData[numDependences]()
		: LL_NULLPTR;
	this->numDependences = numDependences;

	this->dependencesExtra = (numDependencesExtra > 0)
		? new ModBasicData[numDependencesExtra]()
		: LL_NULLPTR;
	this->numDependencesExtra = numDependencesExtra;
}
ModData::~ModData() {
	if (this->dependences) delete[] this->dependences;
	if (this->dependencesExtra) delete[] this->dependencesExtra;

	this->dependences = LL_NULLPTR;
	this->dependencesExtra = LL_NULLPTR;
}
const ModBasicData* ModData::getDependences() const { return this->dependences; }
len_t ModData::getNumDependences() const { return this->numDependences; }
const ModBasicData* ModData::getDependencesExtra() const { return this->dependencesExtra; }
len_t ModData::getNumDependencesExtra() const { return this->numDependencesExtra; }

} /* namespace v2 */
} /* namespace modlibcore */
} /* namespace llcpp */
