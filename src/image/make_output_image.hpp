#ifndef MYRT_IMAGE_MAKE_OUTPUT_IMAGE_HPP
#define MYRT_IMAGE_MAKE_OUTPUT_IMAGE_HPP

#include "image/OutputImage.hpp"

namespace Myrt::Image {

using Myrt::Options::OutputImageOptionsPtr;

OutputImagePtr make_output_image(OutputImageOptionsPtr pOptions) {
    OutputImagePtr ptr;
    ptr.reset(new OutputImage(pOptions));
    return ptr;
}

} // namespace Myrt::Image

#endif
