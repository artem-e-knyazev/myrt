#ifndef MYRT_CAMERA_SIMPLE_CAMERA_HPP
#define MYRT_CAMERA_SIMPLE_CAMERA_HPP

#include <camera/AbstractCamera.hpp>

namespace Myrt::Camera {

class SimpleCamera final: public AbstractCamera {
protected:
    SimpleCamera(const vec4& from,
                 const vec4& at,
                 const vec4& up,
                 float vfov,
                 float aspect)
    {
        float th = vfov * M_PI / 180.f;
        float hh = tan(th / 2.f);
        float hw = aspect * hh;
        mOrigin = from;
        vec4 vx, vy, vz;
        vz = Normalize(from - at);
        // todo: handle case when vz is parallel to up
        vx = Normalize(Cross(up, vz));
        vy = Cross(vz, vx);
        mLowerLeft = -hw * vx - hh * vy - vz;
        mHorizontal = 2.f * hw * vx;
        mVertical = 2.f * hh * vy;
    }

public:
    virtual ray4 getRay(float u, float v) const override {
        return Ray4(mOrigin,
                    Normalize(mLowerLeft + u * mHorizontal + v * mVertical));
    }

private:
    vec4 mOrigin;
    vec4 mLowerLeft;
    vec4 mHorizontal;
    vec4 mVertical;

    template<typename T, typename... Args>
    friend CameraPtr make_camera(Args&&...);
};

} // namespace Myrt::Camera

#endif

