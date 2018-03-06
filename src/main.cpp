#include <iostream>
#include <cstdlib>

#include "options/MyrtOptions.hpp"
#include "image/OutputImage.hpp"

using Myrt::Options::parse_options;
using Myrt::Image::make_output_image;
using Myrt::Image::ImageType;

int main(int argc, char **argv) {
    auto options = parse_options(argc, argv);
    std::cout << "Rendering scene with options:\n\n" 
              << *options << '\n' << std::endl;

    auto image = make_output_image(options->getImageWidth(), options->getImageHeight(),
            options->getOutputPath(), ImageType::PPM, options->getGamma());
    image->save();
}

