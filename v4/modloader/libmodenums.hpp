/*
 * libmodenums.hpp
 *
 *  Created on: Feb 25, 2023
 *      Author: llanyro
 */

#ifndef LIBMOD_LIBMODENUM_HPP_
#define LIBMOD_LIBMODENUM_HPP_

namespace llcpp {
namespace modlibcore {
namespace v4 {
namespace enums {

enum class StatusID {
	NOT_INITIALITED,		// 
	OK,						// 
	FILENAME_EMPTY,			// Filename is empty
	ERROR_OPENING_MOD,		// Cannot open mod
	ERROR_GET_MOD_CORE,		// Tried to get "getModCore" function defined with GetModData
	ERROR_MOD_CORE_NULL,	// "getModCore" returned null pointer
	ERROR_MOD_DATA_NULL,	// Mod core returned data null pointer
	ERROR_MOD_NAME_NULL,	// 
	ERROR_MOD_VERSION_NULL,	// 
};

} /* namespace enums */
} /* namespace modlibcore */
} /* namespace v4 */
} /* namespace llcpp */

#endif // !LIBMOD_LIBMODENUM_HPP_
