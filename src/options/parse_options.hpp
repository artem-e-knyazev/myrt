#ifndef MYRT_OPTIONS_PARSE_OPTIONS_HPP
#define MYRT_OPTIONS_PARSE_OPTIONS_HPP

#include "options/Options.hpp"
#include "exception/OptionsException.hpp"

namespace Myrt::Options {

using Myrt::Exception::OptionsHelpException;
using Myrt::Exception::OptionsOptionNotValidException;
using Myrt::Exception::OptionsOptionsUnknownException;

static const std::string OPTION_OUTPUT_PATH       = "-o";
static const std::string OPTION_OUTPUT_PATH_NAME  = "output path";
static const std::string OPTION_IMAGE_HEIGHT      = "-h";
static const std::string OPTION_IMAGE_HEIGHT_NAME = "image height";
static const std::string OPTION_IMAGE_WIDTH       = "-w";
static const std::string OPTION_IMAGE_WIDTH_NAME  = "image width";
static const std::string OPTION_SAMPLES           = "-s";
static const std::string OPTION_SAMPLES_NAME      = "samples";
static const std::string OPTION_GAMMA             = "-g";
static const std::string OPTION_GAMMA_NAME        = "gamma";
static const std::string OPTION_VERBOSE           = "-v";
static const std::string OPTION_VERBOSE_NAME      = "verbose";
static const std::string OPTION_HELP              = "--help";
static const std::string OPTION_HELP_NAME         = "help";

// todo: works for now; replace with cli options parsing from boost later
OptionsPtr try_parse_options(int argc, char **argv) {
    OptionsPtr ptr(new Options);
    int i = 1;
    std::string curr;
    while (i < argc) {
        curr = argv[i];
        if (curr == OPTION_HELP) {
            throw OptionsHelpException();
        } else if (curr == OPTION_OUTPUT_PATH) {
            if (i == argc-1)
                throw OptionsOptionNotValidException(OPTION_OUTPUT_PATH_NAME);
            char *value = argv[++i];
            if (value[0] == '-')
                throw OptionsOptionNotValidException(OPTION_OUTPUT_PATH_NAME);
            ptr->mOutputPath = value;
            ++i;
        } else if (curr == OPTION_IMAGE_HEIGHT) {
            if (i == argc-1)
                throw OptionsOptionNotValidException(OPTION_IMAGE_HEIGHT_NAME);
            char *value = argv[++i];
            if (value[0] == '-')
                throw OptionsOptionNotValidException(OPTION_IMAGE_HEIGHT_NAME);
            ptr->mImageHeight = std::atoi(value);
            if (ptr->mImageHeight <= 0)
                throw OptionsOptionNotValidException(OPTION_IMAGE_HEIGHT_NAME);
            ++i;
        } else if (curr == OPTION_IMAGE_WIDTH) {
            if (i == argc-1)
                throw OptionsOptionNotValidException(OPTION_IMAGE_WIDTH_NAME);
            char *value = argv[++i];
            if (value[0] == '-')
                throw OptionsOptionNotValidException(OPTION_IMAGE_WIDTH_NAME);
            ptr->mImageWidth = std::atoi(value);
            if (ptr->mImageWidth <= 0)
                throw OptionsOptionNotValidException(OPTION_IMAGE_WIDTH_NAME);
            ++i;
        } else if (curr == OPTION_SAMPLES) {
            if (i == argc-1)
                throw OptionsOptionNotValidException(OPTION_SAMPLES_NAME);
            char *value = argv[++i];
            if (value[0] == '-')
                throw OptionsOptionNotValidException(OPTION_SAMPLES_NAME);
            ptr->mSamples = std::atoi(value);
            if (ptr->mSamples <= 0)
                throw OptionsOptionNotValidException(OPTION_SAMPLES_NAME);
            ++i;
        } else if (curr == OPTION_GAMMA) {
            if (i == argc-1)
                throw OptionsOptionNotValidException(OPTION_GAMMA_NAME);
            char *value = argv[++i];
            if (value[0] == '-')
                throw OptionsOptionNotValidException(OPTION_GAMMA_NAME);
            ptr->mGamma = std::atof(value);
            if (ptr->mGamma <= 0)
                throw OptionsOptionNotValidException(OPTION_GAMMA_NAME);
            ++i;
        } else if (curr == OPTION_VERBOSE) {
            ptr->mVerbose = true;
            ++i;
        } else {
            throw OptionsOptionsUnknownException(curr);
        }
    }
    return ptr;
}

} // namespace Myrt::Options

#endif

