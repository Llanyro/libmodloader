/*
 * ModData.hpp
 *
 *  Created on: Feb 25, 2023
 *	  Author: llanyro
 */

#include "ModData.hpp"

namespace llcpp {
namespace modlibcore {
namespace v4 {

void ModData::addDependenceOut(const ModInfo* data) { this->dependencesOut.push_back(data); }
void ModData::addOptionalDependenceOut(const ModInfo* data) { this->optionalDependencesOut.push_back(data); }
void ModData::addDependant(const ModInfo* data) { this->dependants.push_back(data); }

ModData::ModData(ll_string_t modName, ll_string_t modVersion)
	: ModBasicData(modName, modVersion)
	, dependences()
	, optionalDependences()
	, dependants()
	, dependencesOut()
	, optionalDependencesOut()
{}
ModData::~ModData() {}

void ModData::addDependence(const ModBasicData& data) { this->dependences.push_back(data); }
///void ModData::addDependence(const ModBasicData& data) { this->addDependence(data.hash()); }
//void ModData::addDependence(const ui128& data) { this->dependences.push_back(data); }
void ModData::addOptionalDependence(const ModBasicData& data) { this->optionalDependences.push_back(data); }
///void ModData::addOptionalDependence(const ModBasicData& data) { this->addDependence(data.hash()); }
//void ModData::addOptionalDependence(const ui128& data) { this->optionalDependences.push_back(data); }
void ModData::resizeOut() {
	this->dependencesOut.clear();
	this->optionalDependencesOut.clear();
}


const std::vector<ModBasicData>& ModData::getDependences() const { return this->dependences; }
///const std::vector<ui128>& ModData::getDependences() const { return this->dependences; }
const std::vector<ModBasicData>& ModData::getOptionalDependences() const { return this->optionalDependences; }
///const std::vector<ui128>& ModData::getOptionalDependences() const { return this->optionalDependences; }
const std::vector<const ModInfo*>& ModData::getDependats() const { return this->dependants; }

} /* namespace v4 */
} /* namespace modlibcore */
} /* namespace llcpp */
