/*
 * ModObject.hpp
 *
 *  Created on: Feb 25, 2023
 *      Author: llanyro
 */

#ifndef LIBMOD_OBJECT_MODOBJECT_HPP_
#define LIBMOD_OBJECT_MODOBJECT_HPP_

namespace llcpp {
namespace modlibcore {

class ModBasicData;

class ModObject {
	protected:
		const ModBasicData* modData;
	public:
		ModObject(const ModBasicData* modData);
		~ModObject();
		const ModBasicData* getBaseModData() const;
		// All objects should be clonable
		virtual ModObject* clone() const = 0;
};

} /* namespace modlibcore */
} /* namespace llcpp */

#endif /* LIBMOD_OBJECT_MODOBJECT_HPP_ */
