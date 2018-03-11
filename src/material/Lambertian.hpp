#ifndef MYRT_MATERIAL_LAMBERTIAN_MATERIAL_HPP
#define MYRT_MATERIAL_LAMBERTIAN_MATERIAL_HPP

#include "material/AbstractMaterial.hpp"

namespace Myrt::Material {

class Lambertian: public AbstractMaterial {
public:
    Lambertian(TexturePtr pTexture): mpTexture(pTexture) {}

    virtual bool scatter(const ray4& ray, const HitRecord& hr, color& attenuation, ray4& scattered) const override {
        scattered.m_orig = hr.mHitPoint;
        // scatter ray into a unit sphere above the hit point
        scattered.m_dir = Normalize(hr.mNormal + Random::random_in_unit_sphere());
        attenuation = mpTexture->getColor(hr.mU, hr.mV, hr.mHitPoint);
        return true;
    }

private:
    TexturePtr mpTexture;
};

} // namespace Myrt::Material

#endif

