#ifndef MYRT_OPTIONS_HPP
#define MYRT_OPTIONS_HPP

#include <memory>
#include <iosfwd>
#include <sstream>
#include <exception>

#include "MyrtOptionsException.hpp"

namespace Myrt::Options {

class MyrtOptions;
using MyrtOptionsPtr = std::unique_ptr<MyrtOptions>;

class MyrtOptions {
private:
    std::string mOutputPath;
    unsigned int mImageWidth;
    unsigned int mImageHeight;
    unsigned int mSamples;
    float mGamma;
    bool mVerbose;

    static const std::string mOptionOutputPath;
    static const std::string mOptionOutputPathName;
    static const std::string mOptionImageHeight;
    static const std::string mOptionImageHeightName;
    static const std::string mOptionImageWidth;
    static const std::string mOptionImageWidthName;
    static const std::string mOptionSamples;
    static const std::string mOptionSamplesName;
    static const std::string mOptionGamma;
    static const std::string mOptionGammaName;
    static const std::string mOptionVerbose;
    static const std::string mOptionVerboseName;
    static const std::string mOptionHelp;
    static const std::string mOptionHelpName;

    MyrtOptions()
        : mOutputPath("out.ppm"), mImageWidth(800), mImageHeight(400), mSamples(100)
    {}
public:
    // todo: works for now; replace with cli options parsing from boost later
    static std::unique_ptr<MyrtOptions> parse(int argc, char **argv) {
        std::unique_ptr<MyrtOptions> uptr(new MyrtOptions);
        int i = 1;
        std::string curr;
        while (i < argc) {
            curr = argv[i];
            if (curr == mOptionHelp) {
                throw MyrtOptionsHelpException();
            } else if (curr == mOptionOutputPath) {
                char *value = argv[++i];
                if (value[0] == '-')
                    throw MyrtOptionsOptionNotValidException(mOptionOutputPathName);
                uptr->mOutputPath = value;
                ++i;
            } else if (curr == mOptionImageHeight) {
                char *value = argv[++i];
                if (value[0] == '-')
                    throw MyrtOptionsOptionNotValidException(mOptionImageHeightName);
                uptr->mImageHeight = std::atoi(value);
                if (uptr->mImageHeight <= 0)
                    throw MyrtOptionsOptionNotValidException(mOptionImageHeightName);
                ++i;
            } else if (curr == mOptionImageWidth) {
                char *value = argv[++i];
                if (value[0] == '-')
                    throw MyrtOptionsOptionNotValidException(mOptionImageWidthName);
                uptr->mImageWidth = std::atoi(value);
                if (uptr->mImageWidth <= 0)
                    throw MyrtOptionsOptionNotValidException(mOptionImageWidthName);
                ++i;
            } else if (curr == mOptionSamples) {
                char *value = argv[++i];
                if (value[0] == '-')
                    throw MyrtOptionsOptionNotValidException(mOptionSamplesName);
                uptr->mSamples = std::atoi(value);
                if (uptr->mSamples <= 0)
                    throw MyrtOptionsOptionNotValidException(mOptionSamplesName);
                ++i;
            } else if (curr == mOptionGamma) {
                char *value = argv[++i];
                if (value[0] == '-')
                    throw MyrtOptionsOptionNotValidException(mOptionGammaName);
                uptr->mGamma = std::atof(value);
                if (uptr->mSamples <= 0)
                    throw MyrtOptionsOptionNotValidException(mOptionGammaName);
                ++i;
            } else if (curr == mOptionVerbose) {
                uptr->mVerbose = true;
                ++i;
            }
        }
        return uptr;
    }

    const std::string& getOutputPath() const 
    { return mOutputPath; }

    unsigned int getImageWidth() const
    { return mImageWidth; }

    unsigned int getImageHeight() const
    { return mImageHeight; }

    unsigned int getSamples() const
    { return mSamples; }

    unsigned int getGamma() const
    { return mGamma; }

    bool getVerbose() const
    { return mVerbose; }

    std::ostream& print(std::ostream& out) const {
        return out << "Output path:    " << mOutputPath << '\n'
                   << "Dimensions:     " << mImageWidth << 'x' << mImageHeight << '\n'
                   << "Samples per px: " << mSamples << '\n';
    }
}; // class MyrtOptions

const std::string MyrtOptions::mOptionOutputPath      = "-o";
const std::string MyrtOptions::mOptionOutputPathName  = "output path";
const std::string MyrtOptions::mOptionImageHeight     = "-h";
const std::string MyrtOptions::mOptionImageHeightName = "image height";
const std::string MyrtOptions::mOptionImageWidth      = "-w";
const std::string MyrtOptions::mOptionImageWidthName  = "image width";
const std::string MyrtOptions::mOptionSamples         = "-s";
const std::string MyrtOptions::mOptionSamplesName     = "samples";
const std::string MyrtOptions::mOptionGamma           = "-s";
const std::string MyrtOptions::mOptionGammaName       = "gamma";
const std::string MyrtOptions::mOptionVerbose         = "-s";
const std::string MyrtOptions::mOptionVerboseName     = "verbose";
const std::string MyrtOptions::mOptionHelp            = "--help";
const std::string MyrtOptions::mOptionHelpName        = "help";

std::ostream& operator<<(std::ostream& out, const MyrtOptions& options) {
    return options.print(out);
}

MyrtOptionsPtr parse_options(int argc, char **argv) {
    MyrtOptionsPtr options;
    try {
        options = MyrtOptions::parse(argc, argv);
    } catch (MyrtOptionsHelpException& ex) {
        std::cerr << ex.what() << std::endl;
        std::exit(0);
    } catch (MyrtOptionsException& ex) {
        std::cerr << "Error: " << ex.what() << std::endl;
        std::exit(1);
    }
    return options;
}

} // namespace Myrt

#endif

