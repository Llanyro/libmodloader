/*
 * ModIndo.hpp
 *
 *  Created on: Mar 5, 2023
 *      Author: llanyro
 */

#ifndef LIBMOD_MODINFO_HPP_
#define LIBMOD_MODINFO_HPP_

#include "modapi.hpp"
#include "libmodincludes.hpp"

 // For pointer to libs
typedef void* ll_lib_t;

// For lists
template<class T, class Node = llcpp::util::node::Node<T>>
using List as llcpp::util::list::linked::LinkedList<T, Node>;


namespace llcpp {
namespace modlibcore {
namespace v2 {
namespace enums { enum class StatusID; } /* namespace enums */

class ModInfo {
	protected:
		ll_lib_t modHandle;								// Pointer to lib
		ModData* modData;								// Data from mod
	public:
		ModInfo();
		virtual ~ModInfo();
		void* getFunction(ll_str_t functionName) const;

		void setModHandle(ll_lib_t handle);
		void setModData(ModData* modData);
		const ModData* getModData() const;
};
class ModInfoEx : public ModInfo {
	protected:
		ll_str_t filename;								// Path provided by folder
		enums::StatusID statusID;						// Error Type
		List<const ModBasicData*>* dependencesNotFound;	// Dependences not found
		List<const ModInfoEx*>* dependencesFound;		// Dependences found
	public:
		ModInfoEx();
		virtual ~ModInfoEx();
		ll_bool_t operator==(const ModBasicData& dep) const;

		ll_str_t getFilename() const;
		void setFilename(ll_str_t name);

		enums::StatusID getStatusID() const;
		void setStatusID(const enums::StatusID& status);

		List<const ModBasicData*>* getDependencesNotFound();

		ModInfo* extractBasicInfo();
};

} /* namespace v2 */
} /* namespace modlibcore */
} /* namespace llcpp */

#endif // !LIBMOD_MODINFO_HPP_
