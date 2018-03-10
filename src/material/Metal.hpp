#ifndef MYRT_MATERIAL_METAL_MATERIAL_HPP
#define MYRT_MATERIAL_METAL_MATERIAL_HPP

namespace Myrt::Material {

class Metal: public AbstractMaterial {
public:
    Metal(const color& albedo, float fuzziness = 0.f)
        : mAlbedo(albedo), mFuzziness(std::clamp(fuzziness, 0.f, 1.f)) {}

    virtual bool scatter(const ray4& ray, const HitRecord& hr, color& attenuation, ray4& scattered) const override {
        scattered.m_orig = hr.mHitPoint;
        // reflect ray using normal from hit point
        vec4 reflected = ray.m_dir - 2.f * Dot3(ray.m_dir, hr.mNormal) * hr.mNormal;
        scattered.m_dir = Normalize(reflected + mFuzziness * Random::random_in_unit_sphere());
        attenuation = mAlbedo;
        return true;
    }

private:
    color mAlbedo;
    float mFuzziness;
};

} // namespace Myrt::Material

#endif

