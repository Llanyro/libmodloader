/*
 * ModData.hpp
 *
 *  Created on: Feb 25, 2023
 *      Author: llanyro
 */

#ifndef LIBMOD_OBJECT_MODDATA_HPP_
#define LIBMOD_OBJECT_MODDATA_HPP_

#include "ModBasicData.hpp"
// Includes all required classes as incompleted
#include "../libs/libmodincludes.hpp"

namespace llcpp {
namespace modlibcore {

class ModInfo;
namespace vector as llcpp::util::list::vector::dynamic;

class ModData : public ModBasicData {
	protected:
		vector::Vector<ModBasicData*>* dependences;
		vector::Vector<ModBasicData*>* dependencesExtra;
		// Pointers to modcores required
		vector::Vector<const ModInfo*>* dependencesReturned;
		vector::Vector<const ModInfo*>* dependencesExtraReturned;
	public:
		ModData(ll_str_t modName, ll_str_t modVersion, const len_t& numDependences, const len_t& numDependencesExtra);
		virtual ~ModData();

		// Dependence list
		const vector::Vector<ModBasicData*>* getDependences() const;
		// Dependence list exrta no required
		const vector::Vector<ModBasicData*>* getDependencesExtra() const;
		// 
		vector::Vector<const ModInfo*>* getDependencesReturned() const;
		// 
		vector::Vector<const ModInfo*>* getDependencesExtraReturned() const;
};

} /* namespace modlibcore */
} /* namespace llcpp */

#endif /* LIBMOD_OBJECT_MODDATA_HPP_ */
