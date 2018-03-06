#ifndef MYRT_MAKE_IMAGE_SAVER_HPP
#define MYRT_MAKE_IMAGE_SAVER_HPP

#include <exception>
#include <memory>

#include "image/saver/AbstractImageSaver.hpp"
#include "image/saver/PPMImageSaver.hpp"

namespace Myrt::Image::Saver {

ImageSaverUPtr make_image_saver(ImageType type) {
    switch (type) {
        case ImageType::PPM:
            return std::make_unique<PPMImageSaver>();
        default:
            // todo: implement own exception
            // todo: (better) make static type check instead of runtime check
            throw std::logic_error("make_image_saver received unkown image type");
    }
}

} // namespace Myrt::Image::Saver

#endif

