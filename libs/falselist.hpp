/*
 * falselist.hpp
 *
 *  Created on: May 7, 2023
 *      Author: llanyro
 */

#ifndef LIBMOD_LIBS_FALSELIST_HPP_
#define LIBMOD_LIBS_FALSELIST_HPP_

/*
	This lib replicates internal classes used in this lib from Llanylib
		using std objects as vector or list
	Some objects or classes are not use cause lib difference (std vs Llanylib)
*/

#include <list>

typedef void (*event_function)(void*);

struct BasicEvent {
	event_function onCreate = nullptr;
	event_function onGet = nullptr;
	event_function onSet = nullptr;
	event_function onDelete = nullptr;

	BasicEvent(
		event_function create,
		event_function get,
		event_function set,
		event_function del)
		: onCreate(create)
		, onGet(get)
		, onSet(set)
		, onDelete(del) {}
};

namespace llcpp {
namespace util {
namespace node {

template<class T, BasicEvent* ev = nullptr>
class EventNode {};

} /* namespace node */
namespace list {
namespace linked {

template<class T, class UnusedNode>
class LinkedList : public std::list<T> {
	public:
		template<class LambdaFunc>
		void foreach(LambdaFunc func) {
			for (auto i : *this)
				func(i);
		}
		len_t len() { return std::list<T>::size(); }
		len_t size() { return std::list<T>::size(); }
		void add(const T& item) { this->push_back(item); }
		void moveNode(const len_t& pos, LinkedList<T, UnusedNode>* other) {
			auto it = this->begin();
			std::advance(it, pos);
			other->splice(other->begin(), *this, it);
			//this->splice(it, other);
		}
		template<class LambdaFunc>
		ll_bool_t find(LambdaFunc compare) const {
			for (auto i : *this)
				if (compare(i))
					return true;
			return false;
		}
};

} /* namespace linked */
} /* namespace list */
} /* namespace util */
} /* namespace llcpp */

#endif // !LIBMOD_LIBS_FALSELIST_HPP_
