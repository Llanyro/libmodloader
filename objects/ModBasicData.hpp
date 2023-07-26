/*
 * ModBasicData.hpp
 *
 *  Created on: Feb 25, 2023
 *      Author: llanyro
 */

#ifndef LIBMOD_OBJECT_MODBASICDATA_HPP_
#define LIBMOD_OBJECT_MODBASICDATA_HPP_

#include "../libs/libshare.hpp"

#include <string>

namespace llcpp {
namespace modlibcore {

/*
*	Indentifier of mod
*	All objects should have a pointer of this object to indentify
*		what mod belongs
*/
class LL_SHARED_LIB ModBasicData {
	protected:
		std::string modName;
		std::string modVersion;
	public:
		ModBasicData(std::string&& modName, std::string&& modVersion);
		~ModBasicData();
		const std::string& getModName() const;
		const std::string& getModVersion() const;
		bool operator==(const ModBasicData& other) const;
};

} /* namespace modlibcore */
} /* namespace llcpp */

#endif /* LIBMOD_OBJECT_MODBASICDATA_HPP_ */
