#ifndef MYRT_IMAGE_BUFFER_MAKE_IMAGE_BUFFER_HPP
#define MYRT_IMAGE_BUFFER_MAKE_IMAGE_BUFFER_HPP

#include "options/Options.hpp"
#include "image/buffer/ImageBuffer.hpp"

namespace Myrt::Image::Buffer {

using Myrt::Options::ImageBufferOptionsPtr;

ImageBufferPtr make_image_buffer(ImageBufferOptionsPtr pImageBufferOptions) {
    ImageBufferPtr ptr;
    ptr.reset(new ImageBuffer(pImageBufferOptions));
    return ptr;
}

} // namespace Myrt::Image::Buffer

#endif

