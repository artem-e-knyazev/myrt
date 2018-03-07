#ifndef MYRT_IMAGE_MAKE_OUTPUT_IMAGE_HPP
#define MYRT_IMAGE_MAKE_OUTPUT_IMAGE_HPP

#include "image/OutputImage.hpp"

namespace Myrt::Image {

using Myrt::Options::OptionsPtr;

OutputImagePtr make_output_image(OptionsPtr pOptions) {
    OutputImagePtr ptr;
    ptr.reset(new OutputImage(pOptions->getOutputImageOptions()));
    return ptr;
}

} // namespace Myrt::Image

#endif
