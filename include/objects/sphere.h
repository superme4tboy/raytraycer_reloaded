#pragma once

#include "sceneObject.h"
#include <cmath>
#include <memory>

class Sphere : public SceneObject
{
public:
    Sphere() {}
    Sphere(vec3 _center, double _radius,std::shared_ptr<Material> _material) : center(_center), radius(_radius), material(_material){};

    bool hit(const Ray &ray, double t_min, double t_closest_so_far, HitRecord &hitRecord) const override
    {
        vec3 oc = ray.origin() - center;
        double a = vec3::dot(ray.direction(), ray.direction());
        double half_b = vec3::dot(oc, vec3::normalize(ray.direction()));

        double c = oc.length_squared() - radius * radius;

        double discriminant = half_b * half_b - a * c;
        if (discriminant < 0)
            return false;
        auto sqrtd = std::sqrt(discriminant);

        // Find the nearest root that lies in the acceptable range.
        auto root = (-half_b - sqrtd) / a;
        if (root < t_min || t_closest_so_far < root)
        {
            root = (-half_b + sqrtd) / a;
            if (root < t_min || t_closest_so_far < root)
                return false;
        }
        double t = root; //- std::pow(10, -7);
        hitRecord.t = t;
        hitRecord.p = ray.at(root);
        hitRecord.material = material;
        vec3 outward_normal = (hitRecord.p - center) / radius;
        hitRecord.set_face_normal(ray, outward_normal);
        return true;
    }

private:
    vec3 center;
    double radius;
    std::shared_ptr<Material> material;
};