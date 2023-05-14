/*
 * libmodincludes.hpp
 *
 *  Created on: Mar 5, 2023
 *      Author: llanyro
 */

#ifndef LIBMOD_LIBMODINCLUDES_HPP_
#define LIBMOD_LIBMODINCLUDES_HPP_

struct BasicEvent;

namespace llcpp {
namespace util {

namespace node {
template<class T>
class Node;
template<class T, BasicEvent* evn>
class EventNode;
} /* namespace node */

namespace list {
namespace linked {
template<class T, class Node>
class LinkedList;
} /* namespace linked */
namespace vector {
namespace dynamic {
template<class T>
class Vector;
} /* namespace dynamic */
} /* namespace vector */
} /* namespace list */

} /* namespace util */

} /* namespace llcpp */

#endif // !LIBMOD_LIBMODINCLUDES_HPP_
