/*
 * ModInfo.cpp
 *
 *  Created on: Mar 5, 2023
 *      Author: llanyro
 */

#include "ModInfo.hpp"
#include "../libs/libmodbase.hpp"

namespace llcpp {
namespace modlibcore {

    ModInfo::ModInfo()
    : modCore(LL_NULLPTR)
    , modHandle(LL_NULLPTR)
{}
ModInfo::~ModInfo() {
    if (this->modHandle) close_lib(this->modHandle);
    /// Mod core should be deleted on close lib
    this->modHandle = LL_NULLPTR;
}
void* ModInfo::getFunction(ll_str_t functionName) const { return get_lib_address(this->modHandle, functionName); }
void ModInfo::setModHandle(ll_lib_t handle) { this->modHandle = handle; }
void ModInfo::setModCore(const ModCore* modCore) { this->modCore = modCore; }
const ModCore* ModInfo::getModCore() const { return this->modCore; }
//const ModCore* ModInfo::getModCoreConst() const { return this->modCore; }

} /* namespace modlibcore */
} /* namespace llcpp */
