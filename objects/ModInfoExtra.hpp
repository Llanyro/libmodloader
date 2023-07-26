/*
 * ModInfoExtra.hpp
 *
 *  Created on: Mar 5, 2023
 *      Author: llanyro
 */

#ifndef LIBMOD_OBJECT_MODINFOEXTRA_HPP_
#define LIBMOD_OBJECT_MODINFOEXTRA_HPP_

#include "../libs/libshare.hpp"

#include "ModInfo.hpp"

#include <string>
#include <vector>

namespace llcpp {
namespace modlibcore {
namespace enums { enum class StatusID; } /* namespace enums */

class ModBasicData;

class LL_SHARED_LIB ModInfoExtra : public ModInfo {
	protected:
		std::string filename;									// Path provided by folder
		enums::StatusID statusID;								// Status Type
		std::vector<const ModBasicData*> dependencesNotFound;	// Dependences not found
	public:
		ModInfoExtra();
		~ModInfoExtra();
		bool operator==(const ModBasicData& dep) const;

		const std::string& getFilename() const;
		void setFilename(const std::string& filename);

		enums::StatusID getStatusID() const;
		void setStatusID(const enums::StatusID& status);

		void addDependencesNotFound(ModBasicData* data) ;
		const std::vector<const ModBasicData*>& getDependencesNotFound() const;
		// Once data extracted, this object will be invalid, so delete it
		ModInfo* extractBasicInfo();
		void clearSimple();
};

} /* namespace modlibcore */
} /* namespace llcpp */

#endif // !LIBMOD_OBJECT_MODINFOEXTRA_HPP_
