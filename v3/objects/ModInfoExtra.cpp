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

 //#include <cstdlib>
//#include <cstring>

//#include <type_traits>

#if defined(_WIN32) or defined(_WIN64)
#include "../windows/pch.h"
#endif // _WIN32 || _WIN64

namespace llcpp {
namespace modlibcore {

ModInfoExtra::ModInfoExtra()
    : ModInfo()
    , filename()
    , statusID(enums::StatusID::NOT_INITIALITED)
    , dependencesNotFound()
{}
ModInfoExtra::~ModInfoExtra() { this->clearSimple(); }

bool ModInfoExtra::operator==(const ModBasicData& dep) const {
    return this->modCore->getModBasicData()->operator==(dep);
}


const std::string& ModInfoExtra::getFilename() const { return this->filename; }
void ModInfoExtra::setFilename(const std::string& filename) {
    this->filename = filename;
}

enums::StatusID ModInfoExtra::getStatusID() const { return this->statusID; }
void ModInfoExtra::setStatusID(const enums::StatusID& status) { this->statusID = status; }

void ModInfoExtra::addDependencesNotFound(ModBasicData* data) {
    this->dependencesNotFound.push_back(data);
}

const std::vector<const ModBasicData*>& ModInfoExtra::getDependencesNotFound() const {
    return this->dependencesNotFound;
}

ModInfo* ModInfoExtra::extractBasicInfo() {
    this->clearSimple();
    return this;
}
void ModInfoExtra::clearSimple() {
    this->filename.clear();
    this->dependencesNotFound.clear();
}

} /* namespace modlibcore */
} /* namespace llcpp */
