#ifndef MYRT_ABSTRACT_IMAGE_SAVER_HPP
#define MYRT_ABSTRACT_IMAGE_SAVER_HPP

#include "myrt_math/color.hpp"
#include "image/ImageBuffer.hpp"
#include "image/saver/ImageType.hpp"
#include "options/Options.hpp"

namespace Myrt::Image::Saver {

using Myrt::Options::ImageSaverOptionsPtr;

class AbstractImageSaver;
using ImageSaverPtr = std::shared_ptr<AbstractImageSaver>;

class AbstractImageSaver {
public:
    void save() const {
        doSave();
    }

    virtual void init(ImageSaverOptionsPtr pOptions, ImageBufferPtr pImageBuffer) {
        mpImageBuffer = pImageBuffer;
        mGamma = pOptions->getGamma();
        mPath = pOptions->getOutputPath();
    }

    virtual ~AbstractImageSaver() = default;

protected:
    virtual void doSave() const = 0;

    rgb_color getPixelColor(unsigned int x, unsigned int y) const {
        return RGBColor(Gamma(mpImageBuffer->getPixelColor(x, y), mGamma));
    }

    const std::string& getPath() const
    { return mPath; }

    unsigned int getImageWidth() const
    { return mpImageBuffer->getWidth(); }

    unsigned int getImageHeight() const
    { return mpImageBuffer->getHeight(); }

private:
    ImageBufferPtr mpImageBuffer;
    float mGamma = 2.f;
    std::string mPath;
};

} // namespace Myrt::Image::Saver

#endif

