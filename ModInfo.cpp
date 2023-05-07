/*
 * ModIndo.cpp
 *
 *  Created on: Mar 5, 2023
 *      Author: llanyro
 */

#include "ModInfo.hpp"

#include "libmodbase.hpp"
#include "libmodenums.hpp"

#if !defined(FALSE_LL_LIB)
#include "../../../llcpp/util/list/linked/LinkedList.hpp"
#else
#include "falselllib.hpp"
#endif

namespace llcpp {
namespace modlibcore {
namespace v2 {

ModInfo::ModInfo() {
    this->modHandle = LL_NULLPTR;
    this->modData = LL_NULLPTR;
}
ModInfo::~ModInfo() {
    if (this->modHandle) close_lib(this->modHandle);
    //if (this->modData) delete this->modData;
}
void* ModInfo::getFunction(ll_str_t functionName) const { return get_lib_address(this->modHandle, functionName); }
void ModInfo::setModHandle(ll_lib_t handle) { this->modHandle = handle; }
void ModInfo::setModData(ModData* modData) { this->modData = modData; }
const ModData* ModInfo::getModData() const { return this->modData; }




ModInfoEx::ModInfoEx() : ModInfo() {
    this->filename = LL_NULLPTR;
    this->statusID = enums::StatusID::NOT_INITIALITED;
    this->dependencesNotFound = new List<const ModBasicData*>();
    this->dependencesFound = new List<const ModInfoEx*>();
}
ModInfoEx::~ModInfoEx() {
    if (this->filename) free(const_cast<char*>(this->filename));
    if (this->dependencesNotFound) delete this->dependencesNotFound;
}
ll_bool_t ModInfoEx::operator==(const ModBasicData& dep) const { return this->modData->operator==(dep); }
ll_str_t ModInfoEx::getFilename() const { return this->filename; }
void ModInfoEx::setFilename(ll_str_t name) { this->filename = name; }
enums::StatusID ModInfoEx::getStatusID() const { return this->statusID; }
void ModInfoEx::setStatusID(const enums::StatusID& status) { this->statusID = status; }
List<const ModBasicData*>* ModInfoEx::getDependencesNotFound() { return this->dependencesNotFound; }

ModInfo* ModInfoEx::extractBasicInfo() {
    ModInfo* basic = new ModInfo();
    basic->setModData(this->modData);
    basic->setModHandle(this->modHandle);

    this->modData = LL_NULLPTR;
    this->modHandle = LL_NULLPTR;

    return basic;
}


} /* namespace v2 */
} /* namespace modlibcore */
} /* namespace llcpp */
