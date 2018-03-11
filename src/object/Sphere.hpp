#ifndef MYRT_OBJECT_SPHERE_HPP
#define MYRT_OBJECT_SPHERE_HPP

#include "object/AbstractObject.hpp"
#include "hit_record/HitRecord.hpp"

namespace Myrt::Object {

using Myrt::HitRecord::HitRecord;

class Sphere: public AbstractObject {
public:
    Sphere(const vec4& center, float r)
        : mCenter(center), mRadius(r)
    {}

    virtual bool doHit(const ray4& ray, float& tmin, HitRecord& hr) const override {
        // todo: move to myrt_math into collision_ray_sphere function!
        float t;
        vec4 tmp = ray.m_orig - mCenter;
        float a = Dot3(ray.m_dir, ray.m_dir);
        float b = Dot3(tmp, ray.m_dir);
        float c = Dot3(tmp, tmp) - mRadius * mRadius;
        float d = b * b - a * c;

        if (d < .0f)
            return false;
        float e = std::sqrt(d);
        float inva = 1.f / a;
        t = (-b - e) * inva;
        if (t > 10e-6f && t < tmin) {
            tmin = t;
            hr.mpMaterial = getMaterial();
            hr.mNormal = Normalize(tmp + t * ray.m_dir);
            hr.mHitPoint = ray.m_orig + t * ray.m_dir;
            getUV(hr.mNormal, hr.mU, hr.mV);
            return true;
        }

        t = (-b + e) * inva;
        if (t > 10e-6f && t < tmin) {
            tmin = t;
            hr.mpMaterial = getMaterial();
            hr.mNormal = Normalize(tmp + t * ray.m_dir);
            hr.mHitPoint = ray.m_orig + t * ray.m_dir;
            getUV(hr.mNormal, hr.mU, hr.mV);
            return true;
        }

        return false;
    }

private:
    vec4 mCenter;
    float mRadius;

    void getUV(const vec4& n, float& u, float& v) const {
        u = .5f * (1.f - std::atan2(n.z, n.x) / M_PI);
        v = std::asin(n.y) / M_PI + .5f;
    }
};

} // namespace Myrt::Object

#endif

