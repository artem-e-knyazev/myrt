#ifndef MYRT_OBJECT_ABSTRACT_OBJECT
#define MYRT_OBJECT_ABSTRACT_OBJECT

#include "hit_record/HitRecord.hpp"
#include "material/AbstractMaterial.hpp"

namespace Myrt::Object {

using Myrt::HitRecord::HitRecord;
using Myrt::Material::MaterialPtr;

class AbstractObject;
using ObjectPtr = std::shared_ptr<AbstractObject>;

class AbstractObject {
public:
    bool hit(const ray4& ray, float& tmin, HitRecord& hr) {
        return doHit(ray, tmin, hr);
    }

    virtual ~AbstractObject() = default;

    void setMaterial(MaterialPtr pMaterial)
    { mpMaterial = pMaterial; }

    const MaterialPtr& getMaterial() const
    { return mpMaterial; }

protected:
    virtual bool doHit(const ray4& ray, float& tmin, HitRecord& hr) const = 0;

private:
    MaterialPtr mpMaterial;
};

} // namespace Myrt::Object

#endif

