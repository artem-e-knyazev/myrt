#ifndef MYRT_CAMERA_ABSTRACT_CAMERA
#define MYRT_CAMERA_ABSTRACT_CAMERA

namespace Myrt::Camera {

class AbstractCamera;
using CameraPtr = std::shared_ptr<AbstractCamera>;

class AbstractCamera {
public:
    virtual ray4 getRay(float u, float v) const = 0;

    virtual ~AbstractCamera() = default;
};

} // namespace Myrt::Camera

#endif

