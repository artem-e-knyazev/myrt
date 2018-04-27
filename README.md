# Myrt

**Myrt** stands for **My** **R**ay **T**racer. It's a simple path tracing app inspired by Peter Shirley's books on raytracing (some code is just blatantly copied), written to experiment with C++ in a "real app" context. It uses `myrt-math` package that abstracts some 3D math types and operations.

## Contents

* [Installation](https://github.com/artemeknyazev/myrt#installation)
* [Options](https://github.com/artemeknyazev/myrt#options)
* [Inspirations](https://github.com/artemeknyazev/myrt#inspirations)
* [Architecture](https://github.com/artemeknyazev/myrt#architecture)
* [Example output](https://github.com/artemeknyazev/myrt#example-output)

## Installation

Requires CMake >= 3.0.0.

```
> git clone --recursive https://github.com/artemeknyazev/myrt.git
```
or
```
> git clone https://github.com/artemeknyazev/myrt.git
> cd ./myrt
> git submodule update --init recursive
```
Then
```
> cd myrt && mkdir -p build && cd build
> cmake ../
> ./myrt <options>
```

## Options
```
> ./build/myrt --help
Following options are available:
    -o <path>  output image path; default is "output.ppm";
    -w <int>   image width; default is 800;
    -h <int>   image height; default is 400;
    -g <float> output image gamma; default is 2.0;
    -s <int>   samples per pixel; default is 100;
    -v         verbose mode; off by default; // currently does nothing
    --help     this message
```

## Inspirations

It is inspired mostly by Peter Shirley's book series on raytracing ([one](https://www.amazon.com/Ray-Tracing-Weekend-Minibooks-Book-ebook/dp/B01B5AODD8/ref=asap_bc?ie=UTF8), [two](https://www.amazon.com/Ray-Tracing-Next-Week-Minibooks-ebook/dp/B01CO7PQ8C/ref=asap_bc?ie=UTF8) and [three](https://www.amazon.com/Ray-Tracing-Rest-Your-Minibooks-ebook/dp/B01DN58P8C/ref=asap_bc?ie=UTF8)). Some of the code is just copy-pasted, but rewriting is on the way.

## Architecture

We abstract a Scene as a container of objects. Scene has a `hit` function that is called for each ray produced by a Tracer. `hit` returns a boolean and passes some data into a `HitRecord` object, like material and etc.

The Scene contains objects. An Object is something hitable in 3D space, that has a material. The Scene calls `hit` on all objects and finds the nearest one to the ray origin. Object's material is then passed in a `HitRecord` to the Tracer.

A Material is an abstraction that defines how rays are reflected/refracted and attenuated. A Lambertian (perfectly diffuse) and Metal (fully reflective to somewhat diffuse) ones have a texture that defines an attenuation. Currently only a Dielectric (designed to represent transparent objects like glass that both reflects and refracts) has no texture.

A Texture is just a function that returns a color for a specific point of an object in UV-coords.

We use an ImageBuffer to abstract a container of pixels. It will be populated by the Tracer and then saved into an image of some format using ImageSaver API. Currently only PPM format is supported.

To define how rays a produced from pixels of an output image (that essentially acts like a screen we project onto) we abstract a Camera object that accepts normalized image coordinates and returns a ray. We can experiment with emitted rays creating a Depth of Field effect. To simplify things, we add the Camera to the Scene object.

So, we defined a scene, populated it with objects, defined a camera as a view point and created an output image buffer. Now we pass all of these objects into a Tracer that does the magic.

For each pixel of the output image we produce a ray that hits a scene object (or not). If it hits, the ray color is attenuated by the texture color and the ray is reflected/refracted by object's material. We create new reflected/refracted ray from the hit point and iterate until depth exceedes the limit. If depth exceedes the limit or a ray hit nothing, we return sky's color for a given direction. After iterating through all points we just save the image buffer contents into an output file.

### Example 1

A fuzzy metal sphere to the left, a checkered lambertian one in the center, a metal (fully reflective) one to the right and a big diffuse one  at the bottom as a ground. Sky color is hardcoded using simple vector math.

![Example 1](https://github.com/artemeknyazev/myrt/blob/master/examples/example-1-800x400-gamma-2.png)
