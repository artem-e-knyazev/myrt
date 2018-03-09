#ifndef MYRT_TRACER_ABSTRACT_TRACER
#define MYRT_TRACER_ABSTRACT_TRACER

#include "scene/Scene.hpp"
#include "image/OutputImage.hpp"
#include "options/Options.hpp"

namespace Myrt::Tracer {

using Myrt::Scene::ScenePtr;
using Myrt::Image::OutputImagePtr;
using Myrt::Options::TracerOptionsPtr;

class AbstractTracer {
private:
    ScenePtr mpScene;
    OutputImagePtr mpImage;
    unsigned int mSamples;

protected:
    const ScenePtr& getScene() const
    { return mpScene; }

    const OutputImagePtr& getOutputImage() const
    { return mpImage; }

    unsigned int getSamples() const
    { return mSamples; }

public:
    void setScene(ScenePtr pScene)
    { mpScene = pScene; }

    void setOutputImage(OutputImagePtr pImage)
    { mpImage = pImage; }

    virtual void setOptions(TracerOptionsPtr pOptions) {
        mSamples = pOptions->getSamples();
    }

    virtual void trace() const = 0;

    virtual ~AbstractTracer() = default;
};

} // namespace Myrt::Tracer

#endif

