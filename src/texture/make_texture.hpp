#ifndef MYRT_TEXTURE_MAKE_TEXTURE_HPP
#define MYRT_TEXTURE_MAKE_TEXTURE_HPP

#include "texture/forward.hpp"
#include "texture/AbstractTexture.hpp"
#include "texture/Constant.hpp"
#include "texture/Checker.hpp"

namespace Myrt::Texture {

template<typename T, typename... Args>
TexturePtr make_texture(Args&&... args) {
    return std::make_shared<T>(std::forward<Args>(args)...);
};

};

#endif

