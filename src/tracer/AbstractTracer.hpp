#ifndef MYRT_TRACER_ABSTRACT_TRACER
#define MYRT_TRACER_ABSTRACT_TRACER

namespace Myrt::Tracer {

class AbstractTracer {
private:
    ScenePtr mpScene;
    OutputImagePtr mpImage;
    unsigned int mSamples;

protected:
    ScenePtr getScene()
    { return mpScene; }

    OutputImagePtr getOutputImage()
    { return mpImage; }

    unsigned int getSamples()
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

