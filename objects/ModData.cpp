/*
 * ModData.cpp
 *
 *  Created on: Feb 25, 2023
 *      Author: llanyro
 */

#include "ModData.hpp"

#include "../libs/vector.hpp"

#include <string.h>

namespace llcpp {
namespace modlibcore {

ModData::ModData(ll_str_t modName, ll_str_t modVersion, const len_t& numDependences, const len_t& numDependencesExtra) 
	: ModBasicData(modName, modVersion)
	, dependences(LL_NULLPTR)
	, dependencesExtra(LL_NULLPTR)
	, dependencesReturned(LL_NULLPTR)
	, dependencesExtraReturned(LL_NULLPTR)
{
	if (numDependences > 0) {
		this->dependences = new vector::Vector<ModBasicData*>(numDependences);
		this->dependencesReturned = new vector::Vector<const ModInfo*>(numDependences);
	}

	if (numDependencesExtra > 0) {
		this->dependencesExtra = new vector::Vector<ModBasicData*>(numDependences);
		this->dependencesExtraReturned = new vector::Vector<const ModInfo*>(numDependences);
	}
}
ModData::~ModData() {
	if (this->dependences) {
		for (auto i : *this->dependences)
			delete i;
		delete this->dependences;
	}
	if (this->dependencesExtra) {
		for (auto i : *this->dependencesExtra)
			delete i;
		delete this->dependencesExtra;
	}
	if (this->dependencesReturned) delete this->dependencesReturned;
	if (this->dependencesExtraReturned) delete this->dependencesExtraReturned;

	this->dependences = LL_NULLPTR;
	this->dependencesExtra = LL_NULLPTR;
	this->dependencesReturned = LL_NULLPTR;
	this->dependencesExtraReturned = LL_NULLPTR;
}
const vector::Vector<ModBasicData*>* llcpp::modlibcore::ModData::getDependences() const {
	return this->dependences;
}
const vector::Vector<ModBasicData*>* llcpp::modlibcore::ModData::getDependencesExtra() const {
	return this->dependencesExtra;
}
vector::Vector<const ModInfo*>* llcpp::modlibcore::ModData::getDependencesReturned() const {
	return this->dependencesReturned;
}
vector::Vector<const ModInfo*>* llcpp::modlibcore::ModData::getDependencesExtraReturned() const {
	return this->dependencesExtraReturned;
}

} /* namespace modlibcore */
} /* namespace llcpp */
