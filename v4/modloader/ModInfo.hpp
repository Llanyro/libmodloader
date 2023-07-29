/*
 * ModInfo.hpp
 *
 *  Created on: Feb 25, 2023
 *	  Author: llanyro
 */

#ifndef LIBMOD_MODINFO_HPP_
#define LIBMOD_MODINFO_HPP_

#include "../../llcppheaders/llanytypeslib.hpp"

namespace llcpp {
namespace modlibcore {
namespace v4 {

class ModCore;

/*
*	This if a object to proxy access to the mod(library)
*		that you created
*	You can ask for a function and it will return a pointer of the memory function
*	I will not explain here how it works because a comment in not enough
* 
*	Also this class is not virtual!
*	Do not use it as an interface!
*/
class LL_SHARED_LIB ModInfo {
	protected:
		ll_lib_t modHandle;		// Pointer to lib
		ModCore* modCore;		// Reference mod core
	public:
		ModInfo();
		~ModInfo();

		void* getFunction(ll_string_t functionName) const;

		void setModHandle(ll_lib_t handle);

		void setModCore(ModCore* modCore);
		const ModCore* getModCore() const;
		ModCore* getModCore();
};

} /* namespace v4 */
} /* namespace modlibcore */
} /* namespace llcpp */

#endif /* LIBMOD_MODLOADER_HPP_ */
