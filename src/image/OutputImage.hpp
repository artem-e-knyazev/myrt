#ifndef MYRT_OUTPUT_IMAGE_HPP
#define MYRT_OUTPUT_IMAGE_HPP

#include "options/Options.hpp"
#include "image/buffer/make_image_buffer.hpp"
#include "image/saver/make_image_saver.hpp"

namespace Myrt::Image {

using Myrt::Options::OptionsPtr;
using Myrt::Options::OutputImageOptionsPtr;
using Myrt::Image::Saver::ImageSaverPtr;
using Myrt::Image::Saver::make_image_saver;
using Myrt::Image::Buffer::ImageBufferPtr;
using Myrt::Image::Buffer::make_image_buffer;

class OutputImage;
using OutputImagePtr = std::shared_ptr<OutputImage>;

class OutputImage {
private:
    ImageBufferPtr mpImageBuffer;
    ImageSaverPtr mpImageSaver;

    OutputImage(OutputImageOptionsPtr pOutputImageOptions)
        : mpImageBuffer(make_image_buffer(pOutputImageOptions->getImageBufferOptions())),
          mpImageSaver(make_image_saver(pOutputImageOptions->getImageSaverOptions(), mpImageBuffer))
    {}

public:
    void setPixelColor(unsigned int x, unsigned int y, color c) {
        mpImageBuffer->setPixelColor(x, y, c);
    }

    void save() {
        mpImageSaver->save();
    }

    friend OutputImagePtr make_output_image(OptionsPtr);
};

} // namespace Myrt::Image

#endif

