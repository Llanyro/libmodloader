/*
 * ModCore.cpp
 *
 *  Created on: Feb 25, 2023
 *      Author: llanyro
 */

#include "ModCore.hpp"
#include "ModData.hpp"

#include <stdexcept>

#if defined(_WIN32) or defined(_WIN64)
#include "../windows/pch.h"
#endif // _WIN32 || _WIN64

namespace llcpp {
namespace modlibcore {

ModCore::ModCore(ModData* modData)
	: modData(modData)
{
	if (!modData)
		throw std::invalid_argument("modData can not be nullptr");
}
ModCore::~ModCore() {
	delete this->modData;
	this->modData = nullptr;
}
ModData* ModCore::getModData() { return this->modData; }
const ModData* ModCore::getModData() const { return this->modData; }
const ModBasicData* ModCore::getModBasicData() const { return this->modData; }

} /* namespace modlibcore */
} /* namespace llcpp */
