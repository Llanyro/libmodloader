/*
 * ModCore.cpp
 *
 *  Created on: Feb 25, 2023
 *      Author: llanyro
 */

#include "ModCore.hpp"
#include "ModData.hpp"

#include <stdexcept>

namespace llcpp {
namespace modlibcore {

ModCore::ModCore(const ModData* modData) {
	if (!modData)
		throw std::invalid_argument("modData can not be nullptr");
	else
		this->modData = modData;
}
ModCore::~ModCore() {}
const ModData* ModCore::getModData() const { return this->modData; }
const ModBasicData* ModCore::getModBasicData() const { return this->modData; }

} /* namespace modlibcore */
} /* namespace llcpp */
