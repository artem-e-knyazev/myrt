#ifndef MYRT_OBJECT_MAKE_OBJECT_HPP
#define MYRT_OBJECT_MAKE_OBJECT_HPP

#include "object/AbstractObject.hpp"
#include "object/Sphere.hpp"

namespace Myrt::Object {

template<typename T, typename... Args>
ObjectPtr make_object(Args&&... args) {
    ObjectPtr ptr;
    ptr.reset(new T(std::forward<Args>(args)...));
    return ptr;
};

};

#endif
 
