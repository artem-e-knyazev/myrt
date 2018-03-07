#ifndef MYRT_SCENE_SCENE_HPP
#define MYRT_SCENE_SCENE_HPP

#include "object/AbstractObject.hpp"
#include "camera/AbstractCamera.hpp"

namespace Myrt::Scene {

class Scene;
using ScenePtr = std::shared_ptr<Scene>;

class Scene {
private:
    std::vector<ObjectPtr> mObjects;
    CameraPtr mpCamera;

    Scene() = default;

public:
    void addObject(ObjectPtr pObject)
    { mObjects.push_back(std::move(pObject)); }

    void setCamera(CameraPtr pCamera)
    { mpCamera = pCamera; }

    CameraPtr getCamera()
    { return mpCamera;  }

    bool hit(const ray4& ray, float& tmin, HitRecord& hr) {
        bool isHit = false;
        HitRecord thr;
        float ttmin;
        for (const auto& pObject: mObjects) {
            if (pObject->hit(ray, ttmin, thr) && (ttmin < tmin)) {
                tmin = ttmin;
                hr = thr;
                isHit = true;
            }
        }
        return isHit;
    }
};

}; // namespace Myrt::Scene

#endif

