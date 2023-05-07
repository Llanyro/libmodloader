/*
 * modapi.hpp
 *
 *  Created on: Feb 25, 2023
 *      Author: llanyro
 */

#ifndef LIBMOD_MODAPI_HPP_
#define LIBMOD_MODAPI_HPP_

#define FALSE_LL_LIB

#if !defined(FALSE_LL_LIB)
#define LOAD_EVENTS
#include "../../../llpc/core/header/llanytypeslib.h"
#include "../../../llcpp/core/singleton/Singleton.hpp"
#else
#include "falsellheader.hpp"
#endif

namespace llcpp {
namespace modlibcore {
namespace v2 {

/*
	Pros:
		Robusto
			Estable y coherente. Obliga a pensar antes de hacer nada ya que tiene un coste grande cambiar cosas.

	Contras:
		Resistente a los cambios
			Un cambio de una funcion puede impactar en los modulos que depende de ello
*/


/*
	Data for mod info and mod dependeces
*/
class ModBasicData {
	protected:
		ll_str_t modName;
		ll_str_t modVersion;
	public:
		ModBasicData();
		ModBasicData(ll_str_t modName, ll_str_t modVersion);
		ll_str_t getModName() const;
		ll_str_t getModVersion() const;
		void setModName(ll_str_t str);
		void setModVersion(ll_str_t str);
		ll_bool_t operator==(const ModBasicData& other);
};

class ModData : public ModBasicData {
	protected:
		// Dependences required
		ModBasicData* dependences; len_t numDependences;
		// Dependences non required
		ModBasicData* dependencesExtra; len_t numDependencesExtra;
	public:
		ModData(ll_str_t modName, ll_str_t modVersion, const len_t& numDependences, const len_t& numDependencesExtra);
		virtual ~ModData();

		// Dependences required
		const ModBasicData* getDependences() const;
		len_t getNumDependences() const;

		// Dependences non required
		const ModBasicData* getDependencesExtra() const;
		len_t getNumDependencesExtra() const;
};

// To request libs data from mod
typedef ModData* (*GetModData)();

} /* namespace v2 */
} /* namespace modlibcore */
} /* namespace llcpp */

#endif /* LIBMOD_MODAPI_HPP_ */
