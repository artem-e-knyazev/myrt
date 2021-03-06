#ifndef MYRT_PPM_IMAGE_SAVER_HPP
#define MYRT_PPM_IMAGE_SAVER_HPP

#include <fstream>
#include "image/saver/AbstractImageSaver.hpp"

namespace Myrt::Image::Saver {

class PPMImageSaver: public AbstractImageSaver {
protected:
    virtual void doSave() const {
        unsigned int width = getImageWidth();
        unsigned int height = getImageHeight();
        std::ofstream ofs(getPath());
        ofs << "P3\n" << width << " " << height << "\n255\n";
        for (unsigned int y = 0; y < height; ++y) {
            for (unsigned int x = 0; x < width; ++x) {
                rgb_color c = getPixelColor(x, y);
                ofs << int(c.r) << " " << int(c.g) << " " << int(c.b) << "\n";
            }
        }
    }
};

} // namespace Myrt::Image::Saver

#endif

