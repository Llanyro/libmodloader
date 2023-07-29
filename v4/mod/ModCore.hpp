/*
 * ModCore.hpp
 *
 *  Created on: Feb 25, 2023
 *      Author: llanyro
 */

#ifndef LIBMOD_MODCORE_HPP_
#define LIBMOD_MODCORE_HPP_

#include "ModData.hpp"

namespace llcpp {
namespace modlibcore {
namespace v4 {

/*
*	Class that is used to store mod data by standard
*	Any mod need a ModCore and this class (inheritanced)
* 
*	Remember that this object 
* 
*	All objects fron same mod references the same modData
*	So, this way makes easy to access to its indentifier
* 
*	The best way i think to use this class is in a singleton class
*	So when module is unloaded, the class destructs itself and closes anything realted about the mod
* 
*	But class destructor is not virtual
*	This is because its not an interface!
*/
class LL_SHARED_LIB ModCore {
	protected:
		ModData modData;
	public:
		ModCore(const ModBasicData& modData);
		ModCore(ll_string_t modName, ll_string_t modVersion);
		~ModCore();
		ModData* getModData();
		const ModData* getModData() const;
		const ModBasicData* getModBasicData() const;
};

typedef ModCore* (*GetModCore)();
constexpr ll_string_t GET_MOD_CORE = "getModCore";
extern "C" LL_SHARED_LIB ModCore& getModCore();

} /* namespace v4 */
} /* namespace modlibcore */
} /* namespace llcpp */

#endif /* LIBMOD_MODCORE_HPP_ */
