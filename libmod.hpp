/*
 * libmod.hpp
 *
 *  Created on: Feb 22, 2023
 *      Author: llanyro
 */

#ifndef LIBMOD_LIBMOD_HPP_
#define LIBMOD_LIBMOD_HPP_

#include "modapi.hpp"
#include "libmodincludes.hpp"

#if !defined(FALSE_LL_LIB)
#define LOAD_EVENTS
#include "../../../llpc/core/header/eventlib.h"
#else
#include "falsellheader.hpp"
#endif

namespace llcpp {
namespace modlibcore {
namespace v2 {
namespace enums { enum class OSSystem; } /* namespace enums */

class ModInfo;
class ModInfoEx;

// For event lists
extern BasicEvent __modListsEvent__;
template<class T, BasicEvent* evn = &__modListsEvent__, class Node = llcpp::util::node::EventNode<T, evn>>
using EvList as llcpp::util::list::linked::LinkedList<T, Node>;
using ModEventList as EvList<ModInfoEx*>;
using ModVector as llcpp::util::list::vector::dynamic::Vector<ModInfo*>;

class ModLoader {
	private:
		ll_str_t path;				// Mod path folder
		enums::OSSystem os;			// Os host
		ModEventList* modsInfo;		// All mods loaded
		ModEventList* modsInfoErr;	// All mods "loaded" that contains any error
	public:
		ModLoader(const enums::OSSystem& os, ll_str_t modFolderPath);
		ModLoader(const enums::OSSystem& os);
		~ModLoader();

		// Loads all phases and returns number of error ocurred
		ll_int64_t load();
		ModEventList* getLoadedMods();
		ModEventList* getErrorMods();

		// Returns a fixed vector of mod info with minimal data used
		ModVector* getModsToUse();
};

} /* namespace v2 */
} /* namespace modlibcore */
} /* namespace llcpp */

#endif /* LIBMOD_LIBMOD_HPP_ */
