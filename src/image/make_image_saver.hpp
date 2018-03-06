#ifndef MYRT_MAKE_IMAGE_SAVER_HPP
#define MYRT_MAKE_IMAGE_SAVER_HPP

#include <exception>
#include <memory>

#include "AbstractImageSaver.hpp"
#include "PPMImageSaver.hpp"

namespace Myrt::Image {

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

} // namespace Myrt::Image

#endif

