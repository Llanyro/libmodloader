/*
 * ModObject.hpp
 *
 *  Created on: Feb 25, 2023
 *      Author: llanyro
 */

#ifndef LIBMOD_TEST_MODOBJECT_HPP_
#define LIBMOD_TEST_MODOBJECT_HPP_

#include <llanytypeslib.hpp>

namespace llcpp {
namespace modlibcore {
namespace v4 {
class ModBasicData;
namespace test {

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
		// All objects should be clonable
		// By default this function returns nullptr
		virtual ModObject* clone() const;
};

} /* namespace test */
} /* namespace v4 */
} /* namespace modlibcore */
} /* namespace llcpp */

#endif /* LIBMOD_TEST_MODOBJECT_HPP_ */
