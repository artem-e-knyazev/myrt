#ifndef MYRT_OPTIONS_HPP
#define MYRT_OPTIONS_HPP

#include "image/saver/ImageType.hpp"

namespace Myrt::Options {

using Myrt::Image::Saver::ImageType;

class Options;
using OptionsPtr = std::shared_ptr<Options>;

class OutputImageOptions;
using OutputImageOptionsPtr = std::shared_ptr<OutputImageOptions>;

class ImageBufferOptions;
using ImageBufferOptionsPtr = std::shared_ptr<ImageBufferOptions>;

class ImageSaverOptions;
using ImageSaverOptionsPtr = std::shared_ptr<ImageSaverOptions>;

class TracerOptions;
using TracerOptionsPtr = std::shared_ptr<TracerOptions>;

class Options: public std::enable_shared_from_this<Options> {
private:
    std::string mOutputPath;
    unsigned int mImageWidth;
    unsigned int mImageHeight;
    unsigned int mSamples;
    float mGamma;
    ImageType mImageType;
    bool mVerbose;

    Options()
        : mOutputPath("out.ppm"),
          mImageWidth(800), 
          mImageHeight(400),
          mSamples(100),
          mGamma(1.f),
          mImageType(ImageType::PPM),
          mVerbose(false)
    {}

    // todo: add check that T inherits DerivedOptions and T is trivially constructible
    template<typename T>
    std::shared_ptr<T> make_derived() {
        auto ptr = std::make_shared<T>();
        ptr->mpOptions = shared_from_this();
        return ptr;
    }

    void setOutputPath(std::string path) { mOutputPath = std::move(path); }
    void setImageWidth(unsigned int width) { mImageWidth = width; }
    void setImageHeight(unsigned int height) { mImageHeight = height; }
    void setSamples(unsigned int samples) { mSamples = samples; }
    void setGamma(float gamma) { mGamma = gamma; }
    void setImageType(ImageType type) { mImageType = type; }
    void setVerbose(bool verbose) { mVerbose = verbose; }

public:
    std::string getOutputPath() const { return mOutputPath; }
    unsigned int getImageWidth() const { return mImageWidth; }
    unsigned int getImageHeight() const { return mImageHeight; }
    unsigned int getSamples() const { return mSamples; }
    unsigned int getGamma() const { return mGamma; }
    bool getVerbose() const { return mVerbose; }
    ImageType getImageType() const { return mImageType; }

    OutputImageOptionsPtr getOutputImageOptions()
    { return make_derived<OutputImageOptions>(); }

    TracerOptionsPtr getTracerOptions()
    { return make_derived<TracerOptions>(); }

    friend OptionsPtr try_parse_options(int argc, char **argv);
}; // class Options

class DerivedOptions {
private:
    OptionsPtr mpOptions;
protected:
    const OptionsPtr& getOptions() const { return mpOptions; }

    // todo: add check that T inherits DerivedOptions and T is trivially constructible
    template<typename T>
    std::shared_ptr<T> make_derived() const {
        auto pDerived = std::make_shared<T>();
        pDerived->mpOptions = getOptions();
        return pDerived;
    }
public:
    virtual ~DerivedOptions() = default;

    friend class Options;
    friend class DerivedOptions;
};

class ImageBufferOptions: public DerivedOptions {
public:
    unsigned int getImageHeight() const
    { return getOptions()->getImageHeight(); }

    unsigned int getImageWidth() const
    { return getOptions()->getImageWidth(); }
};

class ImageSaverOptions: public DerivedOptions {
public:
    std::string getOutputPath() const 
    { return getOptions()->getOutputPath(); }

    float getGamma() const
    { return getOptions()->getGamma(); }

    ImageType getImageType() const
    { return getOptions()->getImageType(); }
};

class OutputImageOptions: public DerivedOptions {
public:
    ImageBufferOptionsPtr getImageBufferOptions() const
    { return make_derived<ImageBufferOptions>(); }

    ImageSaverOptionsPtr getImageSaverOptions() const
    { return make_derived<ImageSaverOptions>(); }
};

class TracerOptions: public DerivedOptions {
public:
    unsigned int getSamples()
    { return getOptions()->getSamples(); }
};

} // namespace Myrt::Options

#endif

