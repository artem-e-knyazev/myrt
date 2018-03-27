# Myrt

*Myrt* stands for "My RayTracer". It's a simple path tracing app, written to experiment with C++ in the "real app" context. It uses `myrt-math` package that abstracts some 3D math types and operations.

## Table of Contents

* [Installation](https://github.com/artemeknyazev/myrt#installation)
* [Options](https://github.com/artemeknyazev/myrt#options)
* [Inspirations](https://github.com/artemeknyazev/myrt#inspirations)
* [Architecture](https://github.com/artemeknyazev/myrt#architecture)
* [Example output](https://github.com/artemeknyazev/myrt#example-output)

## Installation

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
> make
> ./build/myrt <options>
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

It is inspired mostly by Peter Shirley's book series on raytracing ([one](https://www.amazon.com/Ray-Tracing-Weekend-Minibooks-Book-ebook/dp/B01B5AODD8/ref=asap_bc?ie=UTF8), [two](https://www.amazon.com/Ray-Tracing-Next-Week-Minibooks-ebook/dp/B01CO7PQ8C/ref=asap_bc?ie=UTF8) and [three](https://www.amazon.com/Ray-Tracing-Rest-Your-Minibooks-ebook/dp/B01DN58P8C/ref=asap_bc?ie=UTF8)). Some of the code is just copy-pasted, but I plan to rewrite it sometime (extract collision code into `myrt-math`, add other types of objects, add thread pool for multithreaded tracer).

## Architecture

We abstract Scene as a container of objects. Scene has a `hit` function that is called for each ray produced by the tracer. `hit` returns boolean and passes some data into a `HitRecord` object, like material and etc.

Scene contains objects. Object is something hitable in 3D space, that has a material. Scene calls `hit` on all objects and finds the nearest object to the ray origin. Object's material is then passed in a `HitRecord` to tracer.

Material is an abstraction that defines how rays are reflected/refracted and attenuated. Lambertian (perfectly diffuse) and Metal (fully reflective to somewhat diffuse) have texture that defines attenuation. Currently only Dielectric (designed to represent transparent objects like glass that both reflects and refracts) has no texture.

Texture is just a function that returns a color for a specific point of object in UV-coords.

Note `for each pixel we produce a ray` part. To define how rays a produced from pixels we abstract a Camera object that accepts normalized image coordinates and returns a ray. We can experiment with emitted rays creating a Depth of Field effect. To simplify things, we add Camera to Scene.

We use ImageBuffer to abstract a container of pixels. It will be populated by the Tracer and then saved into an image of some format using ImageSaver API. Currently only PPM format is supported.

So, we defined a Scene, populated it with objects, defined Camera as a view point and created an output image buffer. Now we pass all of these objects into a Tracer that does the magic.

For each pixel of the output image we produce a ray that hits a scene object (or not). If it hits, the ray color is attenuated by the texture color and the ray is reflected/refracted by the object material. We create new reflected/refracted ray from the hit point and iterate until depth exceedes the limit. After we just save the image.

## Example output

### Example 1

Fuzzy metal sphere to the left, checkered lambertian sphere in the center, metal (fully reflective) sphere to the right, big diffuse sphere at the bottom as a ground. Sky color is hardcoded using simple vector math.

![Example 1](https://github.com/artemeknyazev/myrt/blob/master/examples/example-1-800x400-gamma-2.png)
