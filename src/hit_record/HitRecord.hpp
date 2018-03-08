#ifndef MYRT_HIT_RECORD_HIT_RECORD_HPP
#define MYRT_HIT_RECORD_HIT_RECORD_HPP

namespace Myrt::HitRecord {

struct HitRecord {
    vec4  mNormal;
    vec4  mHitPoint;
    color mColor;
};

} // namespace Myrt::HitRecord

#endif

