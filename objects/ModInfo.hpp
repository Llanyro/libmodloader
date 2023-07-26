/*
 * ModInfo.hpp
 *
 *  Created on: Mar 5, 2023
 *      Author: llanyro
 */

#ifndef LIBMOD_OBJECT_MODINFO_HPP_
#define LIBMOD_OBJECT_MODINFO_HPP_

#include "../libs/libshare.hpp"

 // For pointer to libs (Handle)
typedef void* ll_lib_t;

namespace llcpp {
namespace modlibcore {

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

		void* getFunction(const char* const functionName) const;

		void setModHandle(ll_lib_t handle);
		void setModCore(ModCore* modCore);
		const ModCore* getModCore() const;
		ModCore* getModCore();
};

} /* namespace modlibcore */
} /* namespace llcpp */

#endif // !LIBMOD_OBJECT_MODINFO_HPP_
