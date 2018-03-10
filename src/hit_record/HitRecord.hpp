#ifndef MYRT_HIT_RECORD_HIT_RECORD_HPP
#define MYRT_HIT_RECORD_HIT_RECORD_HPP

#include "material/forward.hpp"

namespace Myrt::HitRecord {

using Myrt::Material::MaterialPtr;

struct HitRecord {
    vec4        mNormal;
    vec4        mHitPoint;
    MaterialPtr mpMaterial;
};

} // namespace Myrt::HitRecord

#endif

