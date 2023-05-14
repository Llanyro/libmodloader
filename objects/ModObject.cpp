/*
 * ModCore.cpp
 *
 *  Created on: Feb 25, 2023
 *      Author: llanyro
 */

#include "ModObject.hpp"

#include <stdexcept>

namespace llcpp {
namespace modlibcore {

ModObject::ModObject(const ModBasicData* modData) {
    if(!modData)
        throw std::invalid_argument("modData can not be nullptr");
    else
        this->modData = modData;
}
ModObject::~ModObject() {}
const ModBasicData* ModObject::getBaseModData() const { return this->modData; }

} /* namespace modlibcore */
} /* namespace llcpp */
