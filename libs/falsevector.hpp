/*
 * falsevector.hpp
 *
 *  Created on: May 7, 2023
 *      Author: llanyro
 */

#ifndef LIBMOD_LIBS_FALSEVECTOR_HPP_
#define LIBMOD_LIBS_FALSEVECTOR_HPP_

/*
	This lib replicates internal classes used in this lib from Llanylib
		using std objects as vector or list
	Some objects or classes are not use cause lib difference (std vs Llanylib)
*/

#include <vector>

namespace llcpp {
namespace util {
namespace list {
namespace vector {
namespace dynamic {

template<class T>
class Vector : public std::vector<T> {
	public:
		Vector(const len_t& len) : std::vector<T>(len) {}
		void set(const T& item, const len_t& pos) {
			this->operator[](pos) = item;
		}
		const T* cget(const len_t& pos) const {
			return &this->operator[](pos);
		}
};

} /* namespace dynamic */
} /* namespace vector */
} /* namespace list */
} /* namespace util */
} /* namespace llcpp */

#endif // !LIBMOD_LIBS_FALSEVECTOR_HPP_
