/*
 * ModObject.hpp
 *
 *  Created on: Feb 25, 2023
 *      Author: llanyro
 */

#include "ModObject.hpp"

namespace llcpp {
namespace modlibcore {
namespace v4 {
namespace test {

ModObject::ModObject(const ModBasicData* modData)
    : modData(modData) {}
ModObject::~ModObject() {}

const ModBasicData* ModObject::getBaseModData() const { return this->modData; }
ModObject* ModObject::clone() const { return nullptr; }

} /* namespace test */
} /* namespace v4 */
} /* namespace modlibcore */
} /* namespace llcpp */
