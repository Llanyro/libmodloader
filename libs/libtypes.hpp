/*
 * libtypes.hpp
 *
 *  Created on: Feb 28, 2022
 *      Author: llanyro
 */

#ifndef LIBMOD_LIBS_TYPES_HPP_
#define LIBMOD_LIBS_TYPES_HPP_


#if !defined(FALSE_LL_LIB)
#include "../../llpc/core/header/llanytypeslib.h"
#else
 /*
	 This header contains reqired types of Llanylib, to been used without it
 */

typedef int ll_int_t;
typedef long long ll_longlong_t;
typedef unsigned long long ll_ulonglong_t;

typedef ll_int_t ll_int32_t;
typedef ll_longlong_t ll_int64_t;
typedef ll_ulonglong_t ll_uint64_t;

typedef ll_uint64_t len_t;

typedef const char* ll_str_t;
typedef bool ll_bool_t;


#define LL_NULLPTR nullptr
#define elif else if
#define as =

#pragma warning(disable:4996)
#endif

 // For pointer to libs (Handle)
typedef void* ll_lib_t;

#endif /* LIBMOD_LIBS_TYPES_HPP_ */
