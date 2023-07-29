/*
 * ModCore.cpp
 *
 *  Created on: Feb 25, 2023
 *      Author: llanyro
 */
#include "ModObject.hpp"

#include <stdexcept>

#if defined(_WIN32) or defined(_WIN64)
#include "../windows/pch.h"
#endif // _WIN32 || _WIN64

namespace llcpp {
namespace modlibcore {

ModObject::ModObject(const ModBasicData* modData)
    : modData(modData)
{
    if(!modData)
        throw std::invalid_argument("modData can not be nullptr");
}
ModObject::~ModObject() {}

const ModBasicData* ModObject::getBaseModData() const { return this->modData; }

ModObject* ModObject::clone() const { return nullptr; }

} /* namespace modlibcore */
} /* namespace llcpp */
