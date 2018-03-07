#ifndef MYRT_MAKE_IMAGE_SAVER_HPP
#define MYRT_MAKE_IMAGE_SAVER_HPP

#include <exception>
#include <memory>

#include "image/saver/ImageType.hpp"
#include "image/saver/AbstractImageSaver.hpp"
#include "image/saver/PPMImageSaver.hpp"

namespace Myrt::Image::Saver {

ImageSaverPtr make_image_saver(ImageSaverOptionsPtr pOptions, ImageBufferPtr pImageBuffer) {
    ImageSaverPtr p;
    switch (pOptions->getImageType()) {
        case ImageType::PPM:
            p = std::make_shared<PPMImageSaver>();
            break;
        default:
            // todo: implement own exception
            // todo: (better) make static type check instead of runtime check
            throw std::logic_error("make_image_saver received unkown image type");
    }
    p->init(pOptions, pImageBuffer);
    return p;
}

} // namespace Myrt::Image::Saver

#endif

