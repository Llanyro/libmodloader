/*
 * ModLoader.hpp
 *
 *  Created on: Feb 22, 2023
 *      Author: llanyro
 */

#ifndef LIBMOD_MODLOADER_HPP_
#define LIBMOD_MODLOADER_HPP_

#include "libs/libshare.hpp"

#include <string>
#include <vector>

namespace llcpp {
namespace modlibcore {

class ModInfo;
class ModInfoExtra;

class LL_SHARED_LIB ModLoader {
	protected:
		std::string path;						// Mod path folder
		std::vector<ModInfoExtra*> modsInfo;	// All mods loaded
		std::vector<ModInfoExtra*> modsInfoErr;	// All mods "loaded" that contains any error
	protected:
		void loadMod();
		void unloadMod();
	public:
		ModLoader(std::string modFolderPath = "./mods");
		~ModLoader();

		// Loads all phases and returns number of error ocurred
		std::size_t load();
		//void reloadMod();
		//void loadMod();
		//void unloadMod();
		void clearMods();

		const std::vector<const ModInfoExtra*>& getLoadedMods() const;
		const std::vector<const ModInfoExtra*>& getErrorMods() const;

		// Returns a fixed vector of mod info with minimal data used
		std::vector<const ModInfo*>&& getModsToUse();
};

} /* namespace modlibcore */
} /* namespace llcpp */

#endif /* LIBMOD_MODLOADER_HPP_ */
