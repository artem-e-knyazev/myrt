#ifndef MYRT_SCENE_MAKE_SCENE
#define MYRT_SCENE_MAKE_SCENE

#include "scene/Scene.hpp"

namespace Myrt::Scene {

ScenePtr make_scene() {
    ScenePtr ptr;
    ptr.reset(new Scene);
    return ptr;
}

} // namespace Myrt::Scene

#endif

