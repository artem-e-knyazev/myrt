#ifndef MYRT_TEXTURE_CHECKER_TEXTURE_HPP
#define MYRT_TEXTURE_CHECKER_TEXTURE_HPP

#include "texture/AbstractTexture.hpp"

namespace Myrt::Texture {

class Checker final: public AbstractTexture {
public:
    Checker(TexturePtr pRed, TexturePtr pBlack, int n)
        : mpRed(pRed), mpBlack(pBlack), mNX(n), mNY(n/2) {}

    Checker(TexturePtr pRed, TexturePtr pBlack, int nx, int ny)
        : mpRed(pRed), mpBlack(pBlack), mNX(nx), mNY(ny) {}

    virtual color getColor(float u, float v, const vec4& p) const override {
        int x = std::floor(u * mNX);
        int y = std::floor(v * mNY);
        // todo: smooth later
        if ((x % 2) == (y % 2))
            return mpRed->getColor(u, v, p);
        else
            return mpBlack->getColor(u, v, p);
    }

private:
    TexturePtr mpRed;
    TexturePtr mpBlack;
    int mNX;
    int mNY;
};

} //  namespace Myrt::Texture

#endif

