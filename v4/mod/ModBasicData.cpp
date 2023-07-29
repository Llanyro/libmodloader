/*
 * ModBasicData.cpp
 *
 *  Created on: Feb 25, 2023
 *      Author: llanyro
 */

#include "ModBasicData.hpp"

#include <city.hpp>

#include <cstdlib>
#include <cstring>

namespace llcpp {
namespace modlibcore {
namespace v4 {

ModBasicData::ModBasicData(ll_string_t modName, ll_string_t modVersion)
	: modName(modName), modVersion(modVersion)
{}
ModBasicData::~ModBasicData() {}

ll_string_t ModBasicData::getModName() const { return this->modName; }
ll_string_t ModBasicData::getModVersion() const { return this->modVersion; }

ll_hash_t ModBasicData::hash() const {
	len_t len1 = strlen(this->modName);
	len_t len2 = strlen(this->modVersion);
	len_t len = len1 + len2;
	char* fullId = new char[len + 1];
	std::memcpy(fullId, this->modName, sizeof(char) * len1);
	std::memcpy(fullId + len1, this->modVersion, sizeof(char) * len2);
	fullId[len] = '\0';
	ll_hash_t h = city::CityHash64(fullId, len);
	delete[] fullId;
	return h;
}

} /* namespace v4 */
} /* namespace modlibcore */
} /* namespace llcpp */
