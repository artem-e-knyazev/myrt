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
        float costh;
        // ray can come either from the outside medium, or from inside when refracted
        if (Dot3(ray.m_dir, hr.mNormal) > 0) {
            normal = -hr.mNormal;
            nn = mRefIndFrac;
            costh = mRefIndFrac * Dot3(ray.m_dir, hr.mNormal);
        } else {
            normal = hr.mNormal;
            nn = 1.f / mRefIndFrac;
            costh = -Dot3(ray.m_dir, hr.mNormal);
        }

        vec4 refracted;
        float refl_prob;
        if (refract(ray.m_dir, normal, nn, refracted)) {
            refl_prob = schlick(costh, mRefIndFrac);
        } else {
            refl_prob = 1.f;
        }

        static std::random_device rd;
        static std::mt19937 gen(rd());
        static std::uniform_real_distribution<> dis(0.f, 1.f);
        if (dis(gen) < refl_prob) {
            vec4 reflected = ray.m_dir - 2.f * Dot3(ray.m_dir, hr.mNormal) * hr.mNormal;
            scattered.m_dir = reflected;
        } else {
            scattered.m_dir = refracted;
        }
        scattered.m_orig = hr.mHitPoint;
        return true;
    }

protected:
    // derivation in https://physics.stackexchange.com/a/159975
    bool refract(const vec4& incoming, const vec4& normal, float nn, vec4& transmitted) const {
        float costh1 = Dot3(incoming, normal);
        float sqcosth2 = 1.f - nn * nn * (1.f - costh1 * costh1);
        if (sqcosth2 < 0)
            return false;
        transmitted = nn * incoming + (costh1 * nn - std::sqrt(sqcosth2)) * normal;
        return true;
    }

    float schlick(float costh, float nn) const {
        float a = (1.f-nn)/(1.f+nn);
        a = a * a;
        return a + (1 - a) * std::pow(1-costh, 5);
    }

private:
    float mRefIndFrac;
};

} // namespace Myrt::Material

#endif

