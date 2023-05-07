/*
 * falselllib.hpp
 *
 *  Created on: May 7, 2023
 *      Author: llanyro
 */

#ifndef LIBMOD_FALSELLLIB_HPP_
#define LIBMOD_FALSELLLIB_HPP_

#include <list>
#include <vector>

typedef void (*event_function)(void*);

struct BasicEvent {
	event_function onCreate = nullptr;
	event_function onGet = nullptr;
	event_function onSet = nullptr;
	event_function onDelete = nullptr;
};

namespace llcpp {
namespace util {
namespace node {

template<class T, BasicEvent* ev = nullptr>
class EventNode {

};

} /* namespace node */

namespace list {
namespace linked {

template<class T, class UnusedNode>
class LinkedList : std::list<T> {
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
namespace vector {
namespace dynamic {

template<class T>
class Vector : std::vector<T> {
	public:
		Vector(const len_t& len) : std::vector<T>(len) {}
		void set(const T& item, const len_t& pos) {
			this->operator[](pos) = item;
		}
};

} /* namespace dynamic */
} /* namespace vector */


} /* namespace list */
} /* namespace util */
} /* namespace llcpp */

#endif // !LIBMOD_FALSELLLIB_HPP_
