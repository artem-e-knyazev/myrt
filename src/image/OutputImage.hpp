#ifndef MYRT_OUTPUT_IMAGE_HPP
#define MYRT_OUTPUT_IMAGE_HPP

#include <memory>

#include "image/ImageBuffer.hpp"
#include "image/saver/make_image_saver.hpp"

namespace Myrt::Image {

using Myrt::Image::Saver::ImageSaverPtr;
using Myrt::Image::Saver::make_image_saver;
using Myrt::Options::OptionsPtr;
using Myrt::Options::OutputImageOptionsPtr;

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

OutputImagePtr make_output_image(OptionsPtr pOptions) {
    OutputImagePtr ptr;
    ptr.reset(new OutputImage(pOptions->getOutputImageOptions()));
    return ptr;
}

} // namespace Myrt::Image

#endif

