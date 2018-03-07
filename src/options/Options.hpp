#ifndef MYRT_OPTIONS_HPP
#define MYRT_OPTIONS_HPP

#include <memory>
#include <iosfwd>
#include <sstream>
#include <exception>

#include "options/OptionsException.hpp"
#include "image/saver/ImageType.hpp"

namespace Myrt::Options {

using Myrt::Image::Saver::ImageType;

class Options;
using OptionsPtr = std::shared_ptr<Options>;

class OutputImageOptions;
using OutputImageOptionsPtr = std::shared_ptr<OutputImageOptions>;

class ImageBufferOptions;
using ImageBufferOptionsPtr = std::shared_ptr<ImageBufferOptions>;

class ImageSaverOptions;
using ImageSaverOptionsPtr = std::shared_ptr<ImageSaverOptions>;

class TracerOptions;
using TracerOptionsPtr = std::shared_ptr<TracerOptions>;

class Options: public std::enable_shared_from_this<Options> {
private:
    std::string mOutputPath;
    unsigned int mImageWidth;
    unsigned int mImageHeight;
    unsigned int mSamples;
    float mGamma;
    ImageType mImageType;
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

    Options()
        : mOutputPath("out.ppm"),
          mImageWidth(800), 
          mImageHeight(400),
          mSamples(100),
          mGamma(2.f),
          mImageType(ImageType::PPM),
          mVerbose(false)
    {}

    // todo: add check that T inherits DerivedOptions and T is trivially constructible
    template<typename T>
    std::shared_ptr<T> make_derived() {
        auto ptr = std::make_shared<T>();
        ptr->mpOptions = shared_from_this();
        return ptr;
    }
public:
    // todo: works for now; replace with cli options parsing from boost later
    static std::unique_ptr<Options> parse(int argc, char **argv) {
        std::unique_ptr<Options> uptr(new Options);
        int i = 1;
        std::string curr;
        while (i < argc) {
            curr = argv[i];
            if (curr == mOptionHelp) {
                throw OptionsHelpException();
            } else if (curr == mOptionOutputPath) {
                char *value = argv[++i];
                if (value[0] == '-')
                    throw OptionsOptionNotValidException(mOptionOutputPathName);
                uptr->mOutputPath = value;
                ++i;
            } else if (curr == mOptionImageHeight) {
                char *value = argv[++i];
                if (value[0] == '-')
                    throw OptionsOptionNotValidException(mOptionImageHeightName);
                uptr->mImageHeight = std::atoi(value);
                if (uptr->mImageHeight <= 0)
                    throw OptionsOptionNotValidException(mOptionImageHeightName);
                ++i;
            } else if (curr == mOptionImageWidth) {
                char *value = argv[++i];
                if (value[0] == '-')
                    throw OptionsOptionNotValidException(mOptionImageWidthName);
                uptr->mImageWidth = std::atoi(value);
                if (uptr->mImageWidth <= 0)
                    throw OptionsOptionNotValidException(mOptionImageWidthName);
                ++i;
            } else if (curr == mOptionSamples) {
                char *value = argv[++i];
                if (value[0] == '-')
                    throw OptionsOptionNotValidException(mOptionSamplesName);
                uptr->mSamples = std::atoi(value);
                if (uptr->mSamples <= 0)
                    throw OptionsOptionNotValidException(mOptionSamplesName);
                ++i;
            } else if (curr == mOptionGamma) {
                char *value = argv[++i];
                if (value[0] == '-')
                    throw OptionsOptionNotValidException(mOptionGammaName);
                uptr->mGamma = std::atof(value);
                if (uptr->mSamples <= 0)
                    throw OptionsOptionNotValidException(mOptionGammaName);
                ++i;
            } else if (curr == mOptionVerbose) {
                uptr->mVerbose = true;
                ++i;
            }
        }
        return uptr;
    }

    std::string getOutputPath() const 
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

    ImageType getImageType() const
    { return mImageType; }

    OutputImageOptionsPtr getOutputImageOptions() {
        return make_derived<OutputImageOptions>();
    }

    TracerOptionsPtr getTracerOptions() {
        return make_derived<TracerOptions>();
    }

    std::ostream& print(std::ostream& out) const {
        return out << "Output path:    " << mOutputPath << '\n'
                   << "Dimensions:     " << mImageWidth << 'x' << mImageHeight << '\n'
                   << "Samples per px: " << mSamples << '\n';
    }
}; // class Options

const std::string Options::mOptionOutputPath      = "-o";
const std::string Options::mOptionOutputPathName  = "output path";
const std::string Options::mOptionImageHeight     = "-h";
const std::string Options::mOptionImageHeightName = "image height";
const std::string Options::mOptionImageWidth      = "-w";
const std::string Options::mOptionImageWidthName  = "image width";
const std::string Options::mOptionSamples         = "-s";
const std::string Options::mOptionSamplesName     = "samples";
const std::string Options::mOptionGamma           = "-s";
const std::string Options::mOptionGammaName       = "gamma";
const std::string Options::mOptionVerbose         = "-s";
const std::string Options::mOptionVerboseName     = "verbose";
const std::string Options::mOptionHelp            = "--help";
const std::string Options::mOptionHelpName        = "help";

std::ostream& operator<<(std::ostream& out, const Options& options) {
    return options.print(out);
}

class DerivedOptions {
private:
    OptionsPtr mpOptions;
protected:
    const OptionsPtr& getOptions() const { return mpOptions; }

    // todo: add check that T inherits DerivedOptions and T is trivially constructible
    template<typename T>
    std::shared_ptr<T> make_derived() const {
        auto pDerived = std::make_shared<T>();
        pDerived->mpOptions = getOptions();
        return pDerived;
    }
public:
    virtual ~DerivedOptions() = default;

    friend class Options;
    friend class DerivedOptions;
};

class ImageBufferOptions: public DerivedOptions {
public:
    unsigned int getImageHeight() const
    { return getOptions()->getImageHeight(); }

    unsigned int getImageWidth() const
    { return getOptions()->getImageWidth(); }
};

class ImageSaverOptions: public DerivedOptions {
public:
    std::string getOutputPath() const 
    { return getOptions()->getOutputPath(); }

    float getGamma() const
    { return getOptions()->getGamma(); }

    ImageType getImageType() const
    { return getOptions()->getImageType(); }
};

class OutputImageOptions: public DerivedOptions {
public:
    ImageBufferOptionsPtr getImageBufferOptions() const
    { return make_derived<ImageBufferOptions>(); }

    ImageSaverOptionsPtr getImageSaverOptions() const
    { return make_derived<ImageSaverOptions>(); }
};

class TracerOptions: public DerivedOptions {
public:
    unsigned int getSamples()
    { return getOptions()->getSamples(); }
};

} // namespace Myrt::Options

#endif

