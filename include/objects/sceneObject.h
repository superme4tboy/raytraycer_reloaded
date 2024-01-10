#pragma once

#include "ray.h"

struct HitRecord {
    #include "vec3.h"

    double t; // the parameter t from the ray equation that gives the hit point
    vec3 p; // the point of intersection
    vec3 normal; // the normal at the point of intersection
    //std::shared_ptr<Material> material; // the material of the object hit
    vec3 hit_color; // the color hit_color by the object hit
    bool front_face; // true if the ray hits the front face of the object

    void set_face_normal(const Ray& r, const vec3& outward_normal) {
        // Sets the hit record normal vector.
        // NOTE: the parameter `outward_normal` is assumed to have unit length.

        front_face = vec3::dot(r.direction(), outward_normal) < 0;
        normal = front_face ? outward_normal : -outward_normal;
    }
};

class SceneObject {
public:
    SceneObject();
    SceneObject(vec3& object_color): object_color(object_color) {};
    
    virtual bool hit(const Ray& ray, double t_min, double t_closest_so_far, HitRecord &hitRecord) const = 0;

protected:
    vec3 object_color;
};