#include "main.hpp"

#include "exception/OptionsException.hpp"
#include "options/parse_options.hpp"
#include "options/get_help_string.hpp"
#include "image/make_output_image.hpp"

using Myrt::Options::try_parse_options;
using Myrt::Options::get_help_string;
using Myrt::Image::make_output_image;

auto parse_options(int argc, char **argv) {
    try {
        return try_parse_options(argc, argv);
    } catch (Myrt::Exception::OptionsHelpException& ex) {
        std::cerr << get_help_string() << std::endl;
        std::exit(0);
    } catch (Myrt::Exception::OptionsException& ex) {
        std::cerr << "Error: " << ex.what() << std::endl;
        std::cerr << get_help_string() << std::endl;
        std::exit(1);
    }
}

int main(int argc, char **argv) {
    auto options = parse_options(argc, argv);
    auto image = make_output_image(options);
    image->save();
}

