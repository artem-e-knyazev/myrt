#ifndef MYRT_TRACER_TRACE_SCENE_HPP
#define MYRT_TRACER_TRACE_SCENE_HPP

namespace Myrt::Tracer {

template <typename TracerType>
void trace_scene(OptionsPtr pOptions, ScenePtr pScene, OutputImagePtr pImage) {
    auto pTracer = std::unique_ptr<TracerType>();
    pTracer->setOptions(pOptions);
    pTracer->setScene(pScene);
    pTracer->setOutputImage(pImage);
    pTracer->trace();
}

} // namespace Myrt::Tracer

#endif

