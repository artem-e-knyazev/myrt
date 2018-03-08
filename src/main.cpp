#include "main.hpp"

#include "exception/OptionsException.hpp"
#include "options/parse_options.hpp"
#include "options/get_help_string.hpp"
#include "scene/make_scene.hpp"
#include "object/make_object.hpp"
#include "camera/make_camera.hpp"
#include "image/make_output_image.hpp"
#include "tracer/trace_scene.hpp"

auto parse_options(int argc, char **argv) {
    try {
        return Myrt::Options::try_parse_options(argc, argv);
    } catch (Myrt::Exception::OptionsHelpException& ex) {
        std::cerr << Myrt::Options::get_help_string() << std::endl;
        std::exit(0);
    } catch (Myrt::Exception::OptionsException& ex) {
        std::cerr << "Error: " << ex.what() << std::endl;
        std::cerr << Myrt::Options::get_help_string() << std::endl;
        std::exit(1);
    }
}

auto prepare_test_scene(float aspect) {
    using Myrt::Scene::make_scene;
    using Myrt::Object::make_object;
    using Myrt::Object::Sphere;

    auto scene = make_scene();
    scene->addObject(make_object<Sphere>(Vec4(0.f, 0.f, 0.f), 1.f));
    scene->addObject(make_object<Sphere>(Vec4(0.f, 0.f, 0.f), 1.f));

    using Myrt::Camera::make_camera;

    auto pCamera = make_camera<Myrt::Camera::SimpleCamera>(
            Vec4(0.f, 0.f, 0.f), Vec4(0.f, 0.f, -1.f), Vec4(0.f, 1.f, 0.f),
            60.f, aspect);
    scene->setCamera(pCamera);

    return scene;
}

int main(int argc, char **argv) {
    using Myrt::Image::make_output_image;
    using Myrt::Tracer::trace_scene;

    auto options = parse_options(argc, argv);
    auto image = make_output_image(options);
    auto scene = prepare_test_scene(image->getAspectRatio());
    trace_scene<Myrt::Tracer::SimpleTracer>(options->getTracerOptions(), scene, image);
    image->save();
}

