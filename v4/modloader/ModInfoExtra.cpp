/*
 * ModInfoExtra.cpp
 *
 *  Created on: Feb 25, 2023
 *      Author: llanyro
 */

#include "ModInfoExtra.hpp"

#include "libmodenums.hpp"

namespace llcpp {
namespace modlibcore {
namespace v4 {
namespace enums { enum class StatusID; } /* namespace enums */

ModInfoExtra::ModInfoExtra()
	: ModInfo()
	, filename()
	, statusID(enums::StatusID::NOT_INITIALITED)
{}
ModInfoExtra::~ModInfoExtra() {}

const std::string& ModInfoExtra::getFilename() const { return this->filename; }
void ModInfoExtra::setFilename(std::string&& filename) { this->filename = filename; }

enums::StatusID ModInfoExtra::getStatusID() const { return this->statusID; }
void ModInfoExtra::setStatusID(const enums::StatusID& status) { this->statusID = statusID; }

} /* namespace v4 */
} /* namespace modlibcore */
} /* namespace llcpp */
