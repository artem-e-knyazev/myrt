#ifndef MYRT_OPTIONS_EXCEPTION_HPP
#define MYRT_OPTIONS_EXCEPTION_HPP

#include "exception/MyrtException.hpp"

namespace Myrt::Exception {

class OptionsException: public MyrtException
{};

class OptionsHelpException: public OptionsException
{};

class OptionsOptionNotValidException: public OptionsException {
private:
    std::string mWhat;
public:
    OptionsOptionNotValidException(std::string option) {
        mWhat = option + " option is not valid or not defined";
    }

    virtual const char* what() const noexcept {
        return mWhat.c_str();
    }
};

class OptionsOptionsUnknownException: public OptionsException {
private:
    std::string mWhat;
public:
    OptionsOptionsUnknownException(std::string option) {
        mWhat = "unknown option " + option;
    }

    virtual const char* what() const noexcept {
        return mWhat.c_str();
    }
};

} // namespace Myrt::Options

#endif

