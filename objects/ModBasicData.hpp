/*
 * ModBasicData.hpp
 *
 *  Created on: Feb 25, 2023
 *      Author: llanyro
 */

#ifndef LIBMOD_MODBASICDATA_HPP_
#define LIBMOD_MODBASICDATA_HPP_

//#define FALSE_LL_LIB

#if !defined(FALSE_LL_LIB)
#define LOAD_EVENTS
#include "../../llpc/core/header/llanytypeslib.h"
#else
#include "../libs/falsellheader.hpp"
#endif

namespace llcpp {
namespace modlibcore {

/*
	Data for mod info and mod dependeces
*/
class ModBasicData {
	protected:
		ll_str_t modName;
		ll_str_t modVersion;
	public:
		///ModBasicData();
		ModBasicData(ll_str_t modName, ll_str_t modVersion);
		ll_str_t getModName() const;
		ll_str_t getModVersion() const;
		ll_bool_t operator==(const ModBasicData& other) const;
};

} /* namespace modlibcore */
} /* namespace llcpp */

#endif /* LIBMOD_MODBASICDATA_HPP_ */
