#ifndef MYRT_TEXTURE_CONSTANT_TEXTURE_HPP
#define MYRT_TEXTURE_CONSTANT_TEXTURE_HPP

#include "texture/AbstractTexture.hpp"

namespace Myrt::Texture {

class Constant final: public AbstractTexture {
public:
    Constant(const color& c) : mColor(c) {}

    virtual color getColor(float u, float v, const vec4& p) const override {
        return mColor;
    }

private:
    color mColor;
};

} //  namespace Myrt::Texture

#endif

