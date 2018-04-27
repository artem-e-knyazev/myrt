cmake_minimum_required(VERSION 3.11.0)
project(myrt)

# project-specific includes
include_directories(src)
# myrt-math as a submodule
include_directories(submodules/myrt-math/include)

# SOURCE
set(DEPS_MYRT_MATH_SRC
    submodules/myrt-math/include/myrt-math/storage.hpp
    submodules/myrt-math/include/myrt-math/color.hpp
    submodules/myrt-math/include/myrt-math/vec4.hpp
    submodules/myrt-math/include/myrt-math/ray4.hpp
    submodules/myrt-math/include/myrt-math/mat4.hpp)
set(CAMERA_SRC
    src/camera/AbstractCamera.hpp
    src/camera/SimpleCamera.hpp
    src/camera/LensCamera.hpp
    src/camera/make_camera.hpp)
set(EXCEPTION_SRC
    src/exception/MyrtException.hpp
    src/exception/OptionsException.hpp)
set(HIT_RECORD_SRC
    src/hit_record/HitRecord.hpp)
set(IMAGE_BUFFER_SRC
    src/image/buffer/ImageBuffer.hpp
    src/image/buffer/make_image_buffer.hpp)
set(IMAGE_SAVER_SRC
    src/image/saver/AbstractImageSaver.hpp
    src/image/saver/PPMImageSaver.hpp
    src/image/saver/ImageType.hpp
    src/image/saver/make_image_saver.hpp)
set(IMAGE_SRC
    src/image/OutputImage.hpp
    src/image/make_output_image.hpp)
set(MATERIAL_SRC
    src/material/AbstractMaterial.hpp
    src/material/Lambertian.hpp
    src/material/Metal.hpp
    src/material/Dielectric.hpp
    src/material/forward.hpp
    src/material/make_material.hpp)
set(OBJECT_SRC
    src/object/AbstractObject.hpp
    src/object/Sphere.hpp
    src/object/make_object.hpp)
set(OPTIONS_SRC
    src/options/Options.hpp
    src/options/parse_options.hpp
    src/options/get_help_string.hpp)
set(SCENE_SRC
    src/scene/Scene.hpp
    src/scene/make_scene.hpp)
set(TEXTURE_SRC
    src/texture/AbstractTexture.hpp
    src/texture/Checker.hpp
    src/texture/Constant.hpp
    src/texture/forward.hpp
    src/texture/make_texture.hpp)
set(TRACER_SRC
    src/tracer/AbstractTracer.hpp
    src/tracer/SimpleTracer.hpp
    src/tracer/trace_scene.hpp)
set(MAIN_SRC
    src/main.hpp
    src/main.cpp)
set(MYRT_SRC
    ${MAIN_SRC}
    ${DEPS_MYRT_MATH_SRC}
    ${CAMERA_SRC} ${EXCEPTION_SRC} ${IMAGE_SRC} ${IMAGE_SAVER_SRC}
    ${IMAGE_BUFFER_SRC} ${MATERIAL_SRC} ${OBJECT_SRC} ${OPTIONS_SRC}
    ${SCENE_SRC} ${TEXTURE_SRC} ${TRACER_SRC})

# SOURCE GROUPS
source_group("[dependencies]\\myrt-math" FILES ${DEPS_MYRT_MATH_SRC})
source_group(main FILES ${MAIN_SRC})
source_group(camera FILES ${CAMERA_SRC})
source_group(exception FILES ${EXCEPTION_SRC})
source_group(image FILES ${IMAGE_SRC})
source_group(image\\buffer FILES ${IMAGE_BUFFER_SRC})
source_group(image\\saver FILES ${IMAGE_SAVER_SRC})
source_group(material FILES ${MATERIAL_SRC})
source_group(object FILES ${OBJECT_SRC})
source_group(options FILES ${OPTIONS_SRC})
source_group(scene FILES ${SCENE_SRC})
source_group(texture FILES ${TEXTURE_SRC})
source_group(tracer FILES ${TRACER_SRC})

# COMPILER OPTIONS
set(CXXFLAGS -std=c++1z -O3 -Weffc++)

# MAIN EXECUTABLE
add_executable(myrt)
target_compile_options(myrt PUBLIC ${CXXFLAGS})
target_sources(myrt PRIVATE ${MYRT_SRC})
