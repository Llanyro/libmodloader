/*
 * ModLoader.hpp
 *
 *  Created on: Feb 22, 2023
 *      Author: llanyro
 */

#ifndef LIBMOD_MODLOADER_HPP_
#define LIBMOD_MODLOADER_HPP_

#include "libs/libtypes.hpp"
#include "libs/libmodincludes.hpp"

namespace llcpp {
namespace modlibcore {
namespace enums { enum class OSSystem; } /* namespace enums */

class ModInfo;
class ModInfoExtra;

// For event lists
extern BasicEvent __modListsEvent__;	// Is used as extern cause i dont want to include here its header
template<class T, BasicEvent* evn = &__modListsEvent__, class Node = llcpp::util::node::EventNode<T, evn>>
using EvList as llcpp::util::list::linked::LinkedList<T, Node>;
using ModEventList as EvList<ModInfoExtra*>;
using ModVector as llcpp::util::list::vector::dynamic::Vector<ModInfo*>;

class ModLoader {
	protected:
		ll_str_t path;				// Mod path folder
		enums::OSSystem os;			// Os host
		ModEventList* modsInfo;		// All mods loaded
		ModEventList* modsInfoErr;	// All mods "loaded" that contains any error
	protected:
		void loadMod();
		void unloadMod();
	public:
		ModLoader(const enums::OSSystem& os, ll_str_t modFolderPath);
		ModLoader(const enums::OSSystem& os);
		~ModLoader();

		// Loads all phases and returns number of error ocurred
		ll_int64_t load();
		//void reloadMod();
		//void loadMod();
		//void unloadMod();
		void clearMods();

		ModEventList* getLoadedMods();
		ModEventList* getErrorMods();

		// Returns a fixed vector of mod info with minimal data used
		ModVector* getModsToUse();
};

} /* namespace modlibcore */
} /* namespace llcpp */

#endif /* LIBMOD_MODLOADER_HPP_ */
