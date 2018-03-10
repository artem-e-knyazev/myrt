#ifndef MYRT_MATERIAL_MAKE_MATERIAL_HPP
#define MYRT_MATERIAL_MAKE_MATERIAL_HPP

#include "material/forward.hpp"
#include "material/AbstractMaterial.hpp"
#include "material/Lambertian.hpp"
#include "material/Metal.hpp"
#include "material/Dielectric.hpp"

namespace Myrt::Material {

template<typename T, typename... Args>
MaterialPtr make_material(Args&&... args) {
    return std::make_shared<T>(std::forward<Args>(args)...);
};                    

} // namespace Myrt::Material

#endif

