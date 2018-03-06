#ifndef MYRT_IMAGE_BUFFER_HPP
#define MYRT_IMAGE_BUFFER_HPP

#include <vector>

#include "myrt_math/color.hpp"

namespace Myrt::Image {

class ImageBuffer;
using ImageBufferPtr = std::shared_ptr<ImageBuffer>;

class ImageBuffer {
private:
    std::vector<color> mBuffer;
    unsigned int mWidth;
    unsigned int mHeight;

    ImageBuffer(unsigned int width, unsigned int height)
        : mWidth(width), mHeight(height)
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

    friend class OutputImage;
};

} // namespace Myrt::Image

#endif

