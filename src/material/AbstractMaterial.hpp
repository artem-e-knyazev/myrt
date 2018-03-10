#ifndef MYRT_MATERIAL_ABSTRACT_MATERIAL_HPP
#define MYRT_MATERIAL_ABSTRACT_MATERIAL_HPP

#include "material/forward.hpp"
#include "hit_record/HitRecord.hpp"

namespace Myrt::Material {

using Myrt::HitRecord::HitRecord;

class AbstractMaterial {
public:
    virtual bool scatter(const ray4& ray, const HitRecord& hr, color& attenuation, ray4& scattered) const = 0;

    virtual ~AbstractMaterial() = default;
};

} // namespace Myrt::Material

#endif

