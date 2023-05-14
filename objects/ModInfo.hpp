/*
 * ModInfo.hpp
 *
 *  Created on: Mar 5, 2023
 *      Author: llanyro
 */

#ifndef LIBMOD_OBJECT_MODINFO_HPP_
#define LIBMOD_OBJECT_MODINFO_HPP_

#include "../libs/libtypes.hpp"

namespace llcpp {
namespace modlibcore {
namespace enums { enum class StatusID; } /* namespace enums */

class ModCore;

class ModInfo {
	protected:
		ll_lib_t modHandle;								// Pointer to lib
		const ModCore* modCore;							// Core from mod
	public:
		ModInfo();
		virtual ~ModInfo();
		void* getFunction(ll_str_t functionName) const;

		void setModHandle(ll_lib_t handle);
		void setModCore(const ModCore* modCore);
		const ModCore* getModCore() const;
};

} /* namespace modlibcore */
} /* namespace llcpp */

#endif // !LIBMOD_OBJECT_MODINFO_HPP_
