#ifndef MYRT_CAMERA_LENS_CAMERA_HPP
#define MYRT_CAMERA_LENS_CAMERA_HPP

#include <camera/AbstractCamera.hpp>

namespace Myrt::Camera {

class LensCamera final: public AbstractCamera {
public:
    LensCamera(const vec4& from,
               const vec4& at,
               const vec4& up,
               float vfov,
               float aspect,
               float aperture,
               float focus_dist)
    {
        init(from, at, up, vfov, aspect, aperture, focus_dist);
    }

    LensCamera(const vec4& from,
               const vec4& at,
               const vec4& up,
               float vfov,
               float aspect,
               float aperture)
    {
        init(from, at, up, vfov, aspect, aperture, Length(from-at));
    }

    virtual ray4 getRay(float u, float v) const override {
        vec4 lensPoint = mLensRadius * Random::random_in_unit_disk();
        vec4 offset = mX * lensPoint.x + mY * lensPoint.y;
        return Ray4(mOrigin + offset,
                    mLowerLeft + u * mHorizontal + v * mVertical - offset);
    }

private:
    void init(const vec4& from,
              const vec4& at,
              const vec4& up,
              float vfov,
              float aspect,
              float aperture,
              float focus_dist)
    {
        float th = vfov * M_PI / 180.f;
        float hh = tan(th / 2.f);
        float hw = aspect * hh;

        mZ = Normalize(from - at);
        mX = Normalize(Cross(up, mZ));
        mY = Cross(mZ, mX);

        mOrigin     = from;
        mLowerLeft  = focus_dist * (-hw * mX - hh * mY - mZ);
        mHorizontal = focus_dist * 2.f * hw * mX;
        mVertical   = focus_dist * 2.f * hh * mY;
        mLensRadius = aperture * .5f;
    }

    vec4  mOrigin;
    vec4  mLowerLeft;
    vec4  mHorizontal;
    vec4  mVertical;
    vec4  mX, mY, mZ;
    float mLensRadius;
};

} // namespace Myrt::Camera

#endif

