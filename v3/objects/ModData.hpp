/*
 * ModData.hpp
 *
 *  Created on: Feb 25, 2023
 *      Author: llanyro
 */

#ifndef LIBMOD_OBJECT_MODDATA_HPP_
#define LIBMOD_OBJECT_MODDATA_HPP_

#include "ModBasicData.hpp"

#include "../libs/libshare.hpp"

#include <vector>

namespace llcpp {
namespace modlibcore {
class ModInfo;

class LL_SHARED_LIB ModData : public ModBasicData {
	protected:
		std::vector<ModBasicData*> dependencesRequired;
		std::vector<ModBasicData*> dependencesOptional;
		// Pointers to modcores required
		std::vector<const ModInfo*> dependencesRequiredReturned;
		std::vector<const ModInfo*> dependencesOptionalReturned;
	public:
		ModData(std::string&& modName, std::string&& modVersion);
		~ModData();

		void addDependencesRequired(ModBasicData* dependence);
		void addDependencesOptional(ModBasicData* dependence);

		const std::vector<ModBasicData*>& getDependencesRequired() const;
		const std::vector<ModBasicData*>& getDependencesOptional() const;

		std::vector<const ModInfo*>& getDependenceRequiredReturned();
		std::vector<const ModInfo*>& getDependenceOptionalReturned();
};

} /* namespace modlibcore */
} /* namespace llcpp */

#endif /* LIBMOD_OBJECT_MODDATA_HPP_ */
