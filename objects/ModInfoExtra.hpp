/*
 * ModInfoExtra.hpp
 *
 *  Created on: Mar 5, 2023
 *      Author: llanyro
 */

#ifndef LIBMOD_MODINFOEXTRA_HPP_
#define LIBMOD_MODINFOEXTRA_HPP_

#include "ModInfo.hpp"
#include "../libs/libmodincludes.hpp"

// For lists
template<class T, class Node = llcpp::util::node::Node<T>>
using List as llcpp::util::list::linked::LinkedList<T, Node>;

namespace llcpp {
namespace modlibcore {
namespace enums { enum class StatusID; } /* namespace enums */

class ModBasicData;

class ModInfoExtra : public ModInfo {
	protected:
		ll_str_t filename;								// Path provided by folder
		enums::StatusID statusID;						// Error Type
		List<const ModBasicData*>* dependencesNotFound;	// Dependences not found
		//List<const ModInfoExtra*>* dependencesFound;	// Dependences found
	public:
		ModInfoExtra();
		virtual ~ModInfoExtra();
		ll_bool_t operator==(const ModBasicData& dep) const;

		ll_str_t getFilename() const;
		void setFilename(ll_str_t name);
		//
		enums::StatusID getStatusID() const;
		void setStatusID(const enums::StatusID& status);
		//
		List<const ModBasicData*>* getDependencesNotFound();
		// Once data extracted, this object will be invalid, so delete it
		ModInfo* extractBasicInfo();
};

} /* namespace modlibcore */
} /* namespace llcpp */

#endif // !LIBMOD_MODINFOEXTRA_HPP_
