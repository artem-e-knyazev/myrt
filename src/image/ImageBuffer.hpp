#ifndef MYRT_IMAGE_BUFFER_HPP
#define MYRT_IMAGE_BUFFER_HPP

#include <vector>

#include "myrt_math/color.hpp"
#include "options/Options.hpp"

namespace Myrt::Image {

using Myrt::Options::ImageBufferOptionsPtr;

class ImageBuffer;
using ImageBufferPtr = std::shared_ptr<ImageBuffer>;

class ImageBuffer {
private:
    std::vector<color> mBuffer;
    unsigned int mWidth;
    unsigned int mHeight;

    ImageBuffer(ImageBufferOptionsPtr pImageBufferOptions)
        : mWidth(pImageBufferOptions->getImageWidth()),
          mHeight(pImageBufferOptions->getImageHeight())
    {
        mBuffer.resize(mWidth*mHeight);
    }

public:
    void setPixelColor(unsigned int x, unsigned int y, color& c) {
        mBuffer[x + y * mWidth] = c;
    }

    const color& getPixelColor(unsigned int x, unsigned int y) const {
        return mBuffer[x + y * mWidth];
    }

    unsigned int getWidth() const
    { return mWidth; }

    unsigned int getHeight() const
    { return mHeight; }

    friend ImageBufferPtr make_image_buffer(ImageBufferOptionsPtr);
};

ImageBufferPtr make_image_buffer(ImageBufferOptionsPtr pImageBufferOptions) {
    ImageBufferPtr ptr;
    ptr.reset(new ImageBuffer(pImageBufferOptions));
    return ptr;
}

} // namespace Myrt::Image

#endif

