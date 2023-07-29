/*
 * ModInfo.cpp
 *
 *  Created on: Feb 25, 2023
 *	  Author: llanyro
 */

#include "ModInfo.hpp"

#include "libfunctions.hpp"

namespace llcpp {
namespace modlibcore {
namespace v4 {

ModInfo::ModInfo()
    : modHandle(LL_NULLPTR)
    , modCore()
{}
ModInfo::~ModInfo() {
	if (this->modHandle) close_lib(this->modHandle);
    /// Mod core should be deleted on close lib
    this->modHandle = LL_NULLPTR;
    this->modCore = LL_NULLPTR;
}

void* ModInfo::getFunction(ll_string_t functionName) const {
	return get_lib_address(this->modHandle, functionName);
}
void ModInfo::setModHandle(ll_lib_t handle) { this->modHandle = handle; }

void ModInfo::setModCore(ModCore* modCore) { this->modCore = modCore; }
const ModCore* ModInfo::getModCore() const { return this->modCore; }
ModCore* ModInfo::getModCore() { return this->modCore; }

} /* namespace v4 */
} /* namespace modlibcore */
} /* namespace llcpp */

