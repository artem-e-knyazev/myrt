#ifndef MYRT_TRACER_TRACE_SCENE_HPP
#define MYRT_TRACER_TRACE_SCENE_HPP

#include "tracer/AbstractTracer.hpp"
#include "tracer/SimpleTracer.hpp"

namespace Myrt::Tracer {

template <typename TracerType>
void trace_scene(TracerOptionsPtr pOptions, ScenePtr pScene, OutputImagePtr pImage) {
    auto pTracer = std::unique_ptr<TracerType>();
    pTracer->setOptions(pOptions);
    pTracer->setScene(pScene);
    pTracer->setOutputImage(pImage);
    pTracer->trace();
}

} // namespace Myrt::Tracer

#endif

