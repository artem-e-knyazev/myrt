#ifndef MYRT_CAMERA_MAKE_CAMERA_HPP
#define MYRT_CAMERA_MAKE_CAMERA_HPP

#include "camera/AbstractCamera.hpp"
#include "camera/SimpleCamera.hpp"
#include "camera/LensCamera.hpp"

namespace Myrt::Camera {

template<typename T, typename... Args>
CameraPtr make_camera(Args&&... args) {
    CameraPtr ptr;
    ptr.reset(new T(std::forward<Args>(args)...));
    return ptr;
};

};

#endif

