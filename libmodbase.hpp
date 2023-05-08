/*
 * libmodbase.hpp
 *
 *  Created on: Mar 5, 2023
 *      Author: llanyro
 */

#ifndef LIBMOD_LIBMODBASE_HPP_
#define LIBMOD_LIBMODBASE_HPP_

#if defined(_WIN32)
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

#endif

#endif // !LIBMOD_LIBMODBASE_HPP_
