/*
 * libmodenums.hpp
 *
 *  Created on: Mar 5, 2023
 *      Author: llanyro
 */

#ifndef LIBMOD_LIBMODENUM_HPP_
#define LIBMOD_LIBMODENUM_HPP_

namespace llcpp {
namespace modlibcore {
namespace enums {

enum class OSSystem {
	WINDOWS,
	LINUX,
	NULL_OS
};
enum class StatusID {
	NOT_INITIALITED,								// 
	OK,												// 
	ERROR_OPENING_MOD,								// Cannot open mod
	ERROR_GET_MOD_CORE,								// Tried to get "getModCore" function defined with GetModData
	ERROR_MOD_CORE_NULL,							// "getModCore" returned null pointer
	ERROR_MOD_DATA_NULL,							// Mod core returned data null pointer
	ERROR_MOD_NAME_NULL,							// 
	ERROR_MOD_VERSION_NULL,							// 
	ERROR_DEPENDENCES_NO_VALID_CORRELATION_1,		// dependences.size() != dependencesReturned.size()
	ERROR_DEPENDENCES_NO_VALID_CORRELATION_2,		// dependencesExtra.size() != dependencesExtraReturned.size()
};

} /* namespace enums */
} /* namespace modlibcore */
} /* namespace llcpp */

#endif // !LIBMOD_LIBMODENUM_HPP_
