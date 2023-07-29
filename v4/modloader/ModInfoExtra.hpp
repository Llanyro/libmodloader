/*
 * ModInfoExtra.hpp
 *
 *  Created on: Feb 25, 2023
 *      Author: llanyro
 */

#ifndef LIBMOD_MODINFOEXTRA_HPP_
#define LIBMOD_MODINFOEXTRA_HPP_

#include "ModInfo.hpp"

#include <string>

namespace llcpp {
namespace modlibcore {
namespace v4 {
namespace enums { enum class StatusID; } /* namespace enums */

class LL_SHARED_LIB ModInfoExtra : public ModInfo {
	protected:
		std::string filename;			// Path provided by folder
		enums::StatusID statusID;		// Status Type
	public:
		ModInfoExtra();
		~ModInfoExtra();

		const std::string& getFilename() const;
		void setFilename(std::string&& filename);

		enums::StatusID getStatusID() const;
		void setStatusID(const enums::StatusID& status);
};

} /* namespace v4 */
} /* namespace modlibcore */
} /* namespace llcpp */

#endif /* LIBMOD_MODINFOEXTRA_HPP_ */
