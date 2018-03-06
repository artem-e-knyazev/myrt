### Camera

Produces a ray for given (u, v) image point.

Required only aspect ratio and position in simple case.

### Image (or ImageBuffer, PixelBuffer)?

Contains rendered pixels. Stores color. Can either save itself, or use factory to save in the specified format (e.g. PPMImageSaver accepts PixelBuffer, applies gamma and outputs to file).

### Abstract object

Pure virtual class. Is hitable, i.e. returns true when ray hits it, outputs ray hit position and hit record with color and other properties, e.g. material.

### ObjectCollection or Scene

Is also hitable, but contains all other objects as a list of pointers to AbstractObjects. When calling hit returns if any object inside is hit and outputs hit record for the object that is nearest to the ray origin.

### SceneObjects or MaterialObjects

Pure virtual. MaterialObject inherits from the AbstractObject and contains a reference to a Material. Use `get/setMaterial`. From this objects should inherit all actual objects. Can also add transform member and helpers for bboxes?

### Actual objects

Can be instantiated. Implements desired hit function, i.e. defines form of the objects.

### Material

Defines scattering, attenuation and so on. Contains a pointer to a texture.

### Texture

Defines color at the specified point of the object.

### Tracer

Accepts Scene, Camera and PixelBuffer and renders scene into the latter.
