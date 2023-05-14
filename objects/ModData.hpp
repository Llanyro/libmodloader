/*
 * ModData.hpp
 *
 *  Created on: Feb 25, 2023
 *      Author: llanyro
 */

#ifndef LIBMOD_MODDATA_HPP_
#define LIBMOD_MODDATA_HPP_

#include "ModBasicData.hpp"
// Includes all required classes as incompleted
#include "../libs/libmodincludes.hpp"

namespace llcpp {
namespace modlibcore {

class ModCore;
namespace vector as llcpp::util::list::vector::dynamic;

class ModData : public ModBasicData {
	protected:
		vector::Vector<ModBasicData*>* dependences;
		vector::Vector<ModBasicData*>* dependencesExtra;
		// Pointers to modcores required
		vector::Vector<const ModCore*>* dependencesReturned;
		vector::Vector<const ModCore*>* dependencesExtraReturned;
	public:
		ModData(ll_str_t modName, ll_str_t modVersion, const len_t& numDependences, const len_t& numDependencesExtra);
		virtual ~ModData();

		// Dependence list
		const vector::Vector<ModBasicData*>* getDependences() const;
		// Dependence list exrta no required
		const vector::Vector<ModBasicData*>* getDependencesExtra() const;
		// 
		vector::Vector<const ModCore*>* getDependencesReturned() const;
		// 
		vector::Vector<const ModCore*>* getDependencesExtraReturned() const;
};

} /* namespace modlibcore */
} /* namespace llcpp */

#endif /* LIBMOD_MODDATA_HPP_ */
