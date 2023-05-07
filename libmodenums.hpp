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
namespace v2 {
namespace enums {

enum class OSSystem {
	WINDOWS,
	LINUX
};
enum class StatusID {
	NOT_INITIALITED,								// 
	OK,												// 
	ERROR_OPENING_MOD,								// Cannot open mod
	ERROR_GET_MOD_DATA,								// Tried to get "getModData" function defined with GetModData
	ERROR_MOD_DATA_NULL,							// "getModData" returned null pointer
	ERROR_MOD_NAME_NULL,							// 
	ERROR_MOD_VERSION_NULL,							// 
	ERROR_DEPENDENCES_NO_VALID_CORRELATION_1,		// List is null && len > 0
	ERROR_DEPENDENCES_NO_VALID_CORRELATION_2,		// List is not null && len == 0
	ERROR_DEPENDENCES_EXTRA_NO_VALID_CORRELATION_1,	// List Ex is null && len > 0
	ERROR_DEPENDENCES_EXTRA_NO_VALID_CORRELATION_2,	// List Ex is not null && len == 0
};

} /* namespace enums */
} /* namespace v2 */
} /* namespace modlibcore */
} /* namespace llcpp */

#endif // !LIBMOD_LIBMODENUM_HPP_
