/*
 * ModIndo.cpp
 *
 *  Created on: Mar 5, 2023
 *      Author: llanyro
 */

#include "ModInfoExtra.hpp"

#include "ModCore.hpp"
#include "ModBasicData.hpp"

#include "../libs/libmodenums.hpp"

#include "../libs/list.hpp"

#include <stdlib.h>
#include <string.h>

namespace llcpp {
namespace modlibcore {

ModInfoExtra::ModInfoExtra()
    : ModInfo()
    , filename(LL_NULLPTR)
    , statusID(enums::StatusID::NOT_INITIALITED)
    , dependencesNotFound(new List<const ModBasicData*>())
{}
ModInfoExtra::~ModInfoExtra() { this->clearSimple(); }
ll_bool_t ModInfoExtra::operator==(const ModBasicData& dep) const {
    return this->modCore->getModBasicData()->operator==(dep);
}
ll_str_t ModInfoExtra::getFilename() const { return this->filename; }
void ModInfoExtra::setFilename(ll_str_t name) { this->filename = name; }
enums::StatusID ModInfoExtra::getStatusID() const { return this->statusID; }
void ModInfoExtra::setStatusID(const enums::StatusID& status) { this->statusID = status; }
List<const ModBasicData*>* ModInfoExtra::getDependencesNotFound() { return this->dependencesNotFound; }

ModInfo* ModInfoExtra::extractBasicInfo() {
    this->clearSimple();
    return this;
}
void ModInfoExtra::clearSimple() {
    if (this->filename) free(const_cast<char*>(this->filename));
    if (this->dependencesNotFound) delete this->dependencesNotFound;
    this->filename = LL_NULLPTR;
    this->dependencesNotFound = LL_NULLPTR;
}

} /* namespace modlibcore */
} /* namespace llcpp */
