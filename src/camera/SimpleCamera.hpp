#ifndef MYRT_CAMERA_SIMPLE_CAMERA_HPP
#define MYRT_CAMERA_SIMPLE_CAMERA_HPP

#include <camera/AbstractCamera.hpp>

namespace Myrt::Camera {

class SimpleCamera final: public AbstractCamera {
public:
    SimpleCamera(const vec4& from,
                 const vec4& at,
                 const vec4& up,
                 float vfov,
                 float aspect)
    {
        float th = vfov * M_PI / 180.f;
        float hh = tan(th / 2.f);
        float hw = aspect * hh;
        vec4 vz = Normalize(from - at);
        vec4 vx = Normalize(Cross(up, vz));
        vec4 vy = Cross(vz, vx);

        mOrigin     = from;
        mLowerLeft  = -hw * vx - hh * vy - vz;
        mHorizontal = 2.f * hw * vx;
        mVertical   = 2.f * hh * vy;
    }

    virtual ray4 getRay(float u, float v) const override {
        return Ray4(mOrigin,
                    Normalize(mLowerLeft + u * mHorizontal + v * mVertical));
    }

private:
    vec4 mOrigin;
    vec4 mLowerLeft;
    vec4 mHorizontal;
    vec4 mVertical;
};

} // namespace Myrt::Camera

#endif

