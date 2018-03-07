#ifndef MYRT_TRACER_SIMPLE_TRACER_HPP
#define MYRT_TRACER_SIMPLE_TRACER_HPP

#include "tracer/AbstractTracer.hpp"

namespace Myrt::Tracer {

class SimpleTracer: public AbstractTracer {
public:
    virtual void trace() const override {
        auto pImage = getOutputImage();
        auto pCamera = getScene()->getCamera();
        unsigned int width = pImage->getWidth();
        float invW = 1.f / width;
        unsigned int height = pImage->getHeight();
        float invH = 1.f / height;
        unsigned int samples = getSamples();

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> dis(0.f, 1.f);

        for (unsigned int y = 0; y < height; ++y) {
            for (unsigned int x = 0; x < width; ++x) {
                color c = black;
                for (unsigned int i = 0; i < samples; ++i) {
                    float u = float(x + dis(gen)) * invW;
                    float v = 1.f - float(y + dis(gen)) * invH;
                    c += traceRay(pCamera->getRay(u, v));
                }
                c /= samples;
                pImage->setPixelColor(x, y, c);
            }
        }
    }

private:
    color traceRay(const ray4& ray) const {
        float t = std::numeric_limits<float>::max();
        HitRecord hr;
        if (getScene()->hit(ray, t, hr)) {
            return hr.mColor;
        }
        vec4 unit = Normalize(ray.m_dir);
        t = .5f * (unit.y + 1.f);
        return (1.f - t) * white + t * Color(.5f, .7f, 1.f);
    }
};

} // namespace Myrt::Tracer

#endif

