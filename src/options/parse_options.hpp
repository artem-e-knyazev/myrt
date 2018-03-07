#ifndef MYRT_OPTIONS_PARSE_OPTIONS_HPP
#define MYRT_OPTIONS_PARSE_OPTIONS_HPP

#include "options/Options.hpp"
#include "options/OptionsException.hpp"

namespace Myrt::Options {

OptionsPtr parse_options(int argc, char **argv) {
    OptionsPtr options;
    try {
        options = Options::parse(argc, argv);
    } catch (OptionsHelpException& ex) {
        std::cerr << ex.what() << std::endl;
        std::exit(0);
    } catch (OptionsException& ex) {
        std::cerr << "Error: " << ex.what() << std::endl;
        std::exit(1);
    }
    return options;
}

} // namespace Myrt::Options

#endif

