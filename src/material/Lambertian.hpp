#ifndef MYRT_MATERIAL_LAMBERTIAN_MATERIAL_HPP
#define MYRT_MATERIAL_LAMBERTIAN_MATERIAL_HPP

#include "material/AbstractMaterial.hpp"

namespace Myrt::Material {

class Lambertian: public AbstractMaterial {
public:
    Lambertian(const color& albedo)
        : mAlbedo(albedo) {}

    virtual bool scatter(const ray4& ray, const HitRecord& hr, color& attenuation, ray4& scattered) const override {
        scattered.m_orig = hr.mHitPoint;
        // scatter ray into a unit sphere above the hit point
        scattered.m_dir = Normalize(hr.mNormal + Random::random_in_unit_sphere());
        attenuation = mAlbedo;
        return true;
    }

private:
    color mAlbedo;
};

} // namespace Myrt::Material

#endif

