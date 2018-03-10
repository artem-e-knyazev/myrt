#ifndef MYRT_RANDOM_RANDOM_HPP
#define MYRT_RANDOM_RANDOM_HPP

namespace Myrt::Random {

vec4 random_in_unit_sphere() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_real_distribution<> dis(-1.f, 1.f);

    vec4 p;
    do    { p = Vec4(dis(gen), dis(gen), dis(gen)); }
    while (Dot3(p, p) >= 1.f);
    return p;
}

} // namespace Myrt::Random

#endif

