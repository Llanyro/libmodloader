/*
 * ModInfo.cpp
 *
 *  Created on: Mar 5, 2023
 *      Author: llanyro
 */

#include "ModInfo.hpp"
#include "../libs/libmodbase.hpp"

#if defined(_WIN32) or defined(_WIN64)
#include "../windows/pch.h"
#endif // _WIN32 || _WIN64

namespace llcpp {
namespace modlibcore {

ModInfo::ModInfo()
    : modHandle(nullptr)
    , modCore(nullptr)
{}
ModInfo::~ModInfo() {
    if (this->modHandle) close_lib(this->modHandle);
    /// Mod core should be deleted on close lib
    this->modHandle = nullptr;
}
void* ModInfo::getFunction(const char* const functionName) const { return get_lib_address(this->modHandle, functionName); }

void ModInfo::setModHandle(ll_lib_t handle) { this->modHandle = handle; }
void ModInfo::setModCore(ModCore* modCore) { this->modCore = modCore; }
const ModCore* ModInfo::getModCore() const { return this->modCore; }
ModCore* ModInfo::getModCore() { return this->modCore; }

} /* namespace modlibcore */
} /* namespace llcpp */
