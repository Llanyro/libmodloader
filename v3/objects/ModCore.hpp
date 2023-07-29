/*
 * ModCore.hpp
 *
 *  Created on: Feb 25, 2023
 *      Author: llanyro
 */

#ifndef LIBMOD_OBJECT_MODCORE_HPP_
#define LIBMOD_OBJECT_MODCORE_HPP_

#include "../libs/libshare.hpp"

namespace llcpp {
namespace modlibcore {

class ModData;
class ModBasicData;

/*
*	Class that is used to store mod data by standard
*	Any mod need a ModCore and this class (inheritanced)
* 
*	Remember that this object 
* 
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
		ModData* modData;
	public:
		ModCore(ModData* modData);
		~ModCore();
		ModData* getModData();
		const ModData* getModData() const;
		const ModBasicData* getModBasicData() const;
};

// To request libs data from mod
typedef ModCore* (*GetModCore)();
#define GET_MOD_CORE "getModCore"

} /* namespace modlibcore */
} /* namespace llcpp */

#endif /* LIBMOD_OBJECT_MODCORE_HPP_ */
