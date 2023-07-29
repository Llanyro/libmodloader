/*
 * ModCore.hpp
 *
 *  Created on: Feb 25, 2023
 *      Author: llanyro
 */

#include "ModCore.hpp"

namespace llcpp {
namespace modlibcore {
namespace v4 {

ModCore::ModCore(const ModBasicData& modData)
    : modData(modData.getModName(), modData.getModVersion())
{}
ModCore::ModCore(ll_string_t modName, ll_string_t modVersion)
    : modData(modName, modVersion)
{}
ModCore::~ModCore() {}

ModData* ModCore::getModData() { return &this->modData; }
const ModData* ModCore::getModData() const { return &this->modData; }
const ModBasicData* ModCore::getModBasicData() const { return &this->modData; }

} /* namespace v4 */
} /* namespace modlibcore */
} /* namespace llcpp */
