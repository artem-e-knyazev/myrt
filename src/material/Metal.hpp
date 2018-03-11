#ifndef MYRT_MATERIAL_METAL_MATERIAL_HPP
#define MYRT_MATERIAL_METAL_MATERIAL_HPP

#include "material/AbstractMaterial.hpp"

namespace Myrt::Material {

class Metal: public AbstractMaterial {
public:
    Metal(TexturePtr pTexture, float fuzziness = 0.f)
        : mpTexture(pTexture), mFuzziness(std::clamp(fuzziness, 0.f, 1.f)) {}

    virtual bool scatter(const ray4& ray, const HitRecord& hr, color& attenuation, ray4& scattered) const override {
        scattered.m_orig = hr.mHitPoint;
        // reflect ray using normal from hit point
        vec4 reflected = ray.m_dir - 2.f * Dot3(ray.m_dir, hr.mNormal) * hr.mNormal;
        scattered.m_dir = Normalize(reflected + mFuzziness * Random::random_in_unit_sphere());
        attenuation = mpTexture->getColor(hr.mU, hr.mV, hr.mHitPoint);
        return true;
    }

private:
    TexturePtr mpTexture;
    float mFuzziness;
};

} // namespace Myrt::Material

#endif

