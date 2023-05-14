/*
 * ModCore.hpp
 *
 *  Created on: Feb 25, 2023
 *      Author: llanyro
 */

#ifndef LIBMOD_MODCORE_HPP_
#define LIBMOD_MODCORE_HPP_

namespace llcpp {
namespace modlibcore {

class ModData;
class ModBasicData;

// Class that is used to store mod data by standard
// Any mod need a ModCore and this class (inheritanced)
class ModCore {
	protected:
		const ModData* modData;
	public:
		ModCore(const ModData* modData);
		~ModCore();
		const ModData* getModData() const;
		const ModBasicData* getModBasicData() const;
};

// To request libs data from mod
//typedef ModData* (*GetModData)();
typedef ModCore* (*GetModCore)();

} /* namespace modlibcore */
} /* namespace llcpp */

#endif /* LIBMOD_MODCORE_HPP_ */
