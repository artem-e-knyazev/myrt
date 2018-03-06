#ifndef MYRT_OPTIONS_EXCEPTION_HPP
#define MYRT_OPTIONS_EXCEPTION_HPP

namespace Myrt::Options {

namespace {
    std::string getOptionsHelpString() {
        std::stringstream sstr;
        sstr << "Following options are available:\n";
        sstr << "    -o <path>  output image path; default is \"output.ppm\"\n";
        sstr << "    -w <int>   image width; default is 800;\n";
        sstr << "    -h <int>   image height; default is 400;\n";
        sstr << "    -g <float> output image gamma; default is 2.0;\n";
        sstr << "    -s <int>   samples per pixel; default is 100;\n";
        sstr << "    --help     this message\n";
        return sstr.str();
    }
}

class MyrtOptionsException: public std::exception
{};

class MyrtOptionsHelpException: public MyrtOptionsException {
private:
    static std::string mWhat;
public:
    virtual const char* what() const noexcept {
        if (mWhat.empty())
            mWhat = getOptionsHelpString();
        return mWhat.c_str();
    }
};

std::string MyrtOptionsHelpException::mWhat = "";

class MyrtOptionsOptionNotValidException: public MyrtOptionsException {
private:
    std::string mWhat;
public:
    MyrtOptionsOptionNotValidException(std::string option) {
        mWhat = option + " option is not valid or not defined";
    }

    virtual const char* what() const noexcept {
        return mWhat.c_str();
    }
};

} // namespace Myrt::Options

#endif

