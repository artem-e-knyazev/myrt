#ifndef MYRT_ABSTRACT_IMAGE_SAVER_HPP
#define MYRT_ABSTRACT_IMAGE_SAVER_HPP

#include "myrt_math/color.hpp"
#include "ImageBuffer.hpp"

namespace Myrt::Image {

enum class ImageType { PPM };

class AbstractImageSaver;
using ImageSaverUPtr = std::unique_ptr<AbstractImageSaver>;

class AbstractImageSaver {
public:
    void save() const {
        doSave();
    }

    void setImageBuffer(ImageBufferPtr pImageBuffer)
    { mpImageBuffer = pImageBuffer; }

    void setGamma(float g)
    { mGamma = g; }

    void setPath(std::string path)
    { mPath = std::move(path); }

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

} // namespace Myrt::Image

#endif

