#ifndef MYRT_OPTIONS_GET_HELP_STRING
#define MYRT_OPTIONS_GET_HELP_STRING

namespace Myrt::Options {

std::string get_help_string() {
    std::stringstream sstr;
    sstr << "Following options are available:\n";
    sstr << "    -o <path>  output image path; default is \"output.ppm\";\n";
    sstr << "    -w <int>   image width; default is 800;\n";
    sstr << "    -h <int>   image height; default is 400;\n";
    sstr << "    -g <float> output image gamma; default is 2.0;\n";
    sstr << "    -s <int>   samples per pixel; default is 100;\n";
    sstr << "    -v         verbose mode; off by default;\n";
    sstr << "    --help     this message\n";
    return sstr.str();
}

} // namespace Myrt::Options

#endif

