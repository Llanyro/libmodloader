/*
 * ModLoader.hpp
 *
 *  Created on: Feb 25, 2023
 *      Author: llanyro
 */

#ifndef LIBMOD_MODLOADER_HPP_
#define LIBMOD_MODLOADER_HPP_

#include "../../llcppheaders/llanytypeslib.hpp"

#include <string>
#include <map>
#include <vector>

namespace llcpp {
namespace modlibcore {
namespace v4 {

class ModInfo;
class ModInfoExtra;

class LL_SHARED_LIB ModLoader {
	protected:
		using ModMap = std::map<ui128, ModInfoExtra*>;
		using ModVector = std::vector<ModInfoExtra*>;
	protected:
		ll_string_t path;			// Mod path folder
		ModMap modsInfo;			// All mods loaded
		ModVector modsInfoErr;		// All mods "loaded" that contains any error
		ui8 vervoseLevel;
	protected:
		//void loadMod();
		//void unloadMod();
		ModInfoExtra* getModInfoEx(std::string& modName) const;
	public:
		ModLoader(ll_string_t modFolderPath = "./mods");
		~ModLoader();

		void setVervoseLevel(const ui8 v = 1);

		// Loads all phases and returns number of error ocurred
		len_t load();
		//void reloadMod();
		//void loadMod();
		//void unloadMod();
        // Closes all libs
        // All memory should be delete on close
		void clearMods();

		const std::map<ui128, ModInfoExtra*>& getLoadedMods() const;
		const std::vector<ModInfoExtra*>& getErrorMods() const;

		// Returns a fixed vector of mod info with minimal data
        //
		std::vector<const ModInfo*> getModsToUse() const;
};

} /* namespace v4 */
} /* namespace modlibcore */
} /* namespace llcpp */

#endif /* LIBMOD_MODLOADER_HPP_ */
