/*
 * ModBasicData.hpp
 *
 *  Created on: Feb 25, 2023
 *      Author: llanyro
 */

#ifndef LIBMOD_MODBASICDATA_HPP_
#define LIBMOD_MODBASICDATA_HPP_

#include "../../llcppheaders/llanytypeslib.hpp"

namespace llcpp {
namespace modlibcore {
namespace v4 {

/*
*	Indentifier of mod
*	All objects should have a pointer of this object to indentify
*		what mod belongs
*/
class LL_SHARED_LIB ModBasicData {
	protected:
		ll_string_t modName;
		ll_string_t modVersion;
	public:
		ModBasicData(ll_string_t modName, ll_string_t modVersion);
		~ModBasicData();
		ll_string_t getModName() const;
		ll_string_t getModVersion() const;

		ui128 hash() const;
};

} /* namespace v4 */
} /* namespace modlibcore */
} /* namespace llcpp */

#endif /* LIBMOD_MODBASICDATA_HPP_ */
