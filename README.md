# Raytracer project

Project realized by Sabine Hu and Sebastien Menozzi

ING2 - IMAGE

# Features
* Primitives: capped cone, capsule, cone, cube, cylinder, ellipsoid, plane, sphere, holed plane
* Reflection & Refraction
* CSG: union, intersection, minus
* Blobs: with smooth triangle or not
* Textures:
    * Strip (planar/spherical)
    * Checkerboard texture
    * Metal
    * Lambertian
    * Image mapping
    * Perlin noise (noise, turbulence, wood, marble, rainbow, cloud)
* Bump mapping (noise, turbulence, wood, marble)
* Bump / Displacement mapping on plane using any image
* Lights: point, ambient
* Supersampling
* Obj loader
* Add fog (linear, exp, square exp)
* Blur from camera
* Soft shadow

# External library

Use json library to parse scenes from json files.
https://github.com/nlohmann/json
