# Scene 1
* Plane:
    * texture: cloudy
    * bump mapping: (turbulence, 10) * 2 && (turbulence, 20) * 3
    * reflection, refraction
    * specular
* Ellipsoid:
    * texture: lambertian
* Sphere:
    * texture: metal
    * specular
* Capsule:
    * texture: metal
    * specular
    * bump mapping: turbulence
* Cube:
    * texture: wood
* Union - 2 spheres:
    * texture: turbulence
    * specular
* Boat:
    * Obj loader
* Sphere:
    * texture: marble
    * bump mapping: wood

# Scene 2
* Spheres:
    * texture: metal
    * specular

# Scene 3
* Plane:
    * 1 - texture: checkerboard black and white
    * 2 - texture: lambertian
    * 2 - bump mapping: turbulence
    * 2 - displacement mapping ? sheep pattern / stars / bird

* Union - 2 spheres:
    * texture: lambertian
    * specular
* Intersection - 2 spheres:
    * texture: lambertian with transparency
* Intersection - 2 spheres:
    * texture: lambertian
* Difference - 2 spheres:
    * texture: metal
    * specular
* Minus - 2 spheres:
    * texture: horizontal strip
    * specular
* Minus - 2 spheres:
    * texture: vertical strip
    * specular
* First line of spheres:
    * texture: metal
    * reflection decreasing
* Second line of spheres:
    * texture: metal
    * object specular decreasing

# Scene 4
* Plane:
    * texture: noise
* Blob with 3 / 4 / 6 spheres:
    *  3 / 4 / 6 spheres
    * smooth / normal triangles

# Scene 5
* Holed Plane:
    * texture: rainbow
    * specular
* Plane:
    * texture: checkerboard gray and white
* Sphere:
    * texture: noise black and red
    * specular
* Sphere:
    * texture: rainbow
* Sphere:
    * texture: turbulence
* Sphere:
    * texture: vertical strip
* Sphere:
    * texture: marble
* Sphere:
    * texture: wood
* Sphere:
    * texture: checkerboard
    * specular
* Sphere:
    * texture: horizontal strip
    * bump mapping: noise
    * specular
* Sphere:
    * texture: lambertian
    * bump mapping: wood and turbulence
* Sphere:
    * texture: noise blue and pink
    * bump mapping: wood
* Sphere:
    * texture: rainbow
    * bump mapping: noise
* Sphere:
    * texture: image mapping
    * specular
* Sphere:
    * bump mapping: noise
* Sphere:
    * texture: marble
    * bump mapping: marble
* Sphere:
    * texture: spherical strip
    * specular
* Sphere:
    * bump mapping: wood
* Sphere:
    * bump mapping: marble
* Sphere:
    * texture: horizontal strip (white && colored wood)
    * specular
* Sphere:
    * bump mapping: noise

# Scene 6
* Plane:
    * texture: checkerboard rainbow and white
* Cone
    * texture: strip
* Ellipsoid
    * texture: metal
    * specular
* Torus
    * texture: lambertian
* Cylinder:
    * texture: strip
* Cube
    * texture: chekerboard
* Capped cone
    * texture: lambertian
* Capsule
    * texture: lambertian
* Spheres
    * texture: lambertian
    * ior : 1 or 1.33
    * specular
* Fog:
    * linear / exp / square exp
