#ifndef MYRT_OUTPUT_IMAGE_HPP
#define MYRT_OUTPUT_IMAGE_HPP

#include <memory>

#include "image/ImageBuffer.hpp"
#include "image/saver/make_image_saver.hpp"

namespace Myrt::Image {

using Myrt::Image::Saver::ImageType;
using Myrt::Image::Saver::ImageSaverUPtr;
using Myrt::Image::Saver::make_image_saver;

class OutputImage;
using OutputImagePtr = std::shared_ptr<OutputImage>;

class OutputImage {
private:
    ImageBufferPtr mpImageBuffer;
    ImageSaverUPtr mpImageSaver;

    OutputImage(unsigned int width,
                unsigned int height,
                std::string path,
                ImageType type,
                float gamma)
        : mpImageBuffer(new ImageBuffer(width, height))
    {
        mpImageSaver = make_image_saver(type);
        mpImageSaver->setImageBuffer(mpImageBuffer);
        mpImageSaver->setPath(path);
        mpImageSaver->setGamma(gamma);
    }

public:
    void setPixelColor(unsigned int x, unsigned int y, color c) {
        mpImageBuffer->setPixelColor(x, y, c);
    }

    void save() {
        mpImageSaver->save();
    }

    friend OutputImagePtr
    make_output_image(unsigned int, unsigned int,
            std::string, ImageType, float);
};

OutputImagePtr make_output_image(unsigned int width,
                                 unsigned int height,
                                 std::string path,
                                 ImageType type,
                                 float gamma = 2.f)
{
    OutputImagePtr ptr;
    ptr.reset(new OutputImage(width, height, path, type, gamma));
    return ptr;
}

} // namespace Myrt::Image

#endif

