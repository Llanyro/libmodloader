/*
 * libshare.hpp
 *
 *  Created on: Feb 28, 2022
 *      Author: llanyro
 */

#ifndef LIBMOD_LIBS_SHARE_HPP_
#define LIBMOD_LIBS_SHARE_HPP_

/// Win dll
#if defined(_WIN32) or defined(_WIN64)
#define LL_DLL_BUILD
#if defined(LL_DLL_BUILD)
#define LL_SHARED_LIB __declspec(dllexport)
#else
	#define LL_SHARED_LIB __declspec(dllimport)
#define LL_SHARED_LIB
#endif
#else
#define LL_SHARED_LIB
#endif // WINDOWS_SYSTEM

#endif /* LIBMOD_LIBS_SHARE_HPP_ */
