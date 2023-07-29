/*
 * ModData.hpp
 *
 *  Created on: Feb 25, 2023
 *      Author: llanyro
 */

#ifndef LIBMOD_MODDATA_HPP_
#define LIBMOD_MODDATA_HPP_

#include "ModBasicData.hpp"

#include <vector>

namespace llcpp {
namespace modlibcore {
namespace v4 {
class ModInfo;
class ModLoader;

class LL_SHARED_LIB ModData : public ModBasicData {
	private:
		friend class ModLoader;
		// Mod dependences list (hash)
		///std::vector<ui128> dependences;
		std::vector<ModBasicData> dependences;
		// Mod optional dependences list (hash)
		///std::vector<ui128> optionalDependences;
		std::vector<ModBasicData> optionalDependences;

		// Mods that has any dependence on this mod
		std::vector<const ModInfo*> dependants;

		// Pointers to dependences requested
		std::vector<const ModInfo*> dependencesOut;
		// Pointers to optional dependences requested
		std::vector<const ModInfo*> optionalDependencesOut;
	private:
		void addDependenceOut(const ModInfo* data);
		void addOptionalDependenceOut(const ModInfo* data);
		void addDependant(const ModInfo* data);
	public:
		ModData(ll_string_t modName, ll_string_t modVersion);
		~ModData();

		void addDependence(const ModBasicData& data);
		///void addDependence(const ui128& data);
		void addOptionalDependence(const ModBasicData& data);
		///void addOptionalDependence(const ui128& data);
		void resizeOut();

		const std::vector<ModBasicData>& getDependences() const;
		///const std::vector<ui128>& getDependences() const;
		const std::vector<ModBasicData>& getOptionalDependences() const;
		///const std::vector<ui128>& getOptionalDependences() const;
		const std::vector<const ModInfo*>& getDependats() const;


		///*
		//*	Notifies to dependant and optional dependences to unlink with this mod
		//*		is going to be unloaded
		//*	All dependences should be unloaded too
		//*/
		//virtual ll_bool_t notifyUnload() const = 0;
};

} /* namespace v4 */
} /* namespace modlibcore */
} /* namespace llcpp */

#endif /* LIBMOD_MODDATA_HPP_ */
