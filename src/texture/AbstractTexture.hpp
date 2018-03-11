#ifndef MYRT_TEXTURE_ABSTRACT_TEXTURE
#define MYRT_TEXTURE_ABSTRACT_TEXTURE

#include "texture/forward.hpp"

namespace Myrt::Texture {

class AbstractTexture {
public:
    virtual color getColor(float u, float v, const vec4& p) const = 0;

    virtual ~AbstractTexture() = default;
};

} // namespace Myrt::Texture

#endif

