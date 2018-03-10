#ifndef MYRT_MATERIAL_DIELECTRIC_HPP
#define MYRT_MATERIAL_DIELECTRIC_HPP

namespace Myrt::Material {

class Dielectric: public AbstractMaterial {
public:
    Dielectric(float refIndFrac): mRefIndFrac(refIndFrac) {}

    // note: always refracts when possible; try modify to use reflection too when refracted?
    virtual bool scatter(const ray4& ray, const HitRecord& hr, color& attenuation, ray4& scattered) const override {
        attenuation = Color(1.f, 1.f, 1.f);

        float nn;
        vec4 normal;
        // make normal codirectional to the ray direction
        // and use appropriate ref. ind. fraction
        if (Dot3(ray.m_dir, hr.mNormal) > 0) {
            normal = -hr.mNormal;
            nn = mRefIndFrac;
        } else {
            normal = hr.mNormal;
            nn = 1.f / mRefIndFrac;
        }

        vec4 refracted;
        if (refract(ray.m_dir, normal, nn, refracted)) {
            scattered.m_orig = hr.mHitPoint;
            scattered.m_dir = refracted;
            return false;
        } else {
            vec4 reflected = ray.m_dir - 2.f * Dot3(ray.m_dir, hr.mNormal) * hr.mNormal;
            scattered.m_orig = hr.mHitPoint;
            scattered.m_dir = reflected;
            return true;
        }
    }

protected:
    // derivation in https://physics.stackexchange.com/a/159975
    // assumes incoming and normal vectors are codirectional
    bool refract(const vec4& incoming, const vec4& normal, float nn, vec4& transmitted) const {
        float costh1 = Dot3(incoming, normal);
        float sqcosth2 = 1.f - nn * nn * (1.f - costh1 * costh1);
        if (sqcosth2 < 0)
            return false;
        transmitted = nn * incoming + (costh1 * nn - std::sqrt(sqcosth2)) * normal;
        return true;
    }

private:
    float mRefIndFrac;
};

} // namespace Myrt::Material

#endif

