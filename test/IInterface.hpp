/*
 * ModData.hpp
 *
 *  Created on: Feb 25, 2023
 *      Author: llanyro
 */

#ifndef LIBMOD_TEST_IINTERFACE_HPP_
#define LIBMOD_TEST_IINTERFACE_HPP_

#include "../objects/ModObject.hpp"

namespace llcpp {
namespace modlibcore {
namespace test {

class IInterface : public ModObject {
    public:
        IInterface(const ModBasicData* modData)
            : ModObject(modData) {}
        virtual ~IInterface() {}

        virtual void printText() const = 0;
        virtual void add(int val) = 0;
        virtual void sub(int val) = 0;
        virtual int get() const = 0;
};

} /* namespace test */
} /* namespace modlibcore */
} /* namespace llcpp */

#endif /* LIBMOD_TEST_IINTERFACE_HPP_ */
