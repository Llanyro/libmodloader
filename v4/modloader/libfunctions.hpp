/*
 * libfunctions.hpp
 *
 *  Created on: Mar 5, 2023
 *      Author: llanyro
 */

#ifndef LIBMOD_LIBFUNCTIONS_HPP_
#define LIBMOD_LIBFUNCTIONS_HPP_

#include "../../llcppheaders/llanytypeslib.hpp"

#if defined(WINDOWS_SYSTEM)
#include <Windows.h>

#define load_lib(file) LoadLibraryA(file)
#define get_lib_address(handle, funcName) GetProcAddress((HMODULE)handle, funcName)
#define close_lib(handle) FreeLibrary((HMODULE)handle)

inline const char* dlerror() { return ""; }

#elif defined(__unix__)
#include <dlfcn.h>

#define load_lib(file) dlopen(file, RTLD_LAZY)
#define get_lib_address(handle, funcName) dlsym(handle, funcName)
#define close_lib(handle) dlclose(handle)

#else

#define load_lib(file)
#define get_lib_address(handle, funcName)
#define close_lib(handle)

#endif

#endif // !LIBMOD_LIBFUNCTIONS_HPP_
