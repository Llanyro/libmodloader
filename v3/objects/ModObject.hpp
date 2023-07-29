/*
 * ModObject.hpp
 *
 *  Created on: Feb 25, 2023
 *      Author: llanyro
 */

#ifndef LIBMOD_OBJECT_MODOBJECT_HPP_
#define LIBMOD_OBJECT_MODOBJECT_HPP_

#include "../libs/libshare.hpp"

namespace llcpp {
namespace modlibcore {

class ModBasicData;

/*
*	This time this class is an "interface" or "abstract class"
*	But the thing is, you can have a list of mod objects
*	And delete them, cause this class has virtual destructor
* 
*	Also, you can inherit this class to give object indentifiers to know
*		what object you are using if there are many objects and you manages them randomly
*/
class LL_SHARED_LIB ModObject {
	protected:
		const ModBasicData* modData;
	public:
		ModObject(const ModBasicData* modData);
		virtual ~ModObject();

		const ModBasicData* getBaseModData() const;
		// All objects should be clonable ¿?
		// By default this function returns nullptr
		virtual ModObject* clone() const;
};

} /* namespace modlibcore */
} /* namespace llcpp */

#endif /* LIBMOD_OBJECT_MODOBJECT_HPP_ */
