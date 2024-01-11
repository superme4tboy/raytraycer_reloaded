#ifndef MATERIAL_H
#define MATERIAL_H
#include "ray.h"
#include "vec3.h"
#include "random.h"

class HitRecord;

class Material {
public:
    virtual bool scatter(const Ray& rayIn, const HitRecord& hitRecord, vec3& attenuation, Ray& scattered) const = 0;
};

class lambertian : public Material {
     private:
    vec3 albedo;
  public:
    lambertian(const vec3& a) : albedo(a) {}

    bool scatter(const Ray& r_in, const HitRecord& rec, vec3& attenuation, Ray& scattered)
    const override {
        auto scatter_direction = rec.normal + vec3::random_unit_vector();
        if (scatter_direction.near_zero())
            scatter_direction = rec.normal;
        scattered = Ray(rec.p, scatter_direction);
        attenuation = albedo;
        return true;
    }
};

class metal : public Material {
  public:
    metal(const vec3& a, double f) : albedo(a), fuzz(f < 1 ? f : 1) {}

    bool scatter(const Ray& r_in, const HitRecord& rec, vec3& attenuation, Ray& scattered)
    const override {
        vec3 reflected = vec3::normalize(r_in.direction()).reflect(rec.normal);
        scattered = Ray(rec.p, reflected + fuzz*vec3::random_unit_vector());
        attenuation = albedo;
        return (vec3::dot(scattered.direction(), rec.normal) > 0);
    }

  private:
    vec3 albedo;
    double fuzz;
};

class dielectric: public Material {
  private:
    double ir; // Index of Refraction
    

    static double reflectance(double cosine, double ref_idx) {
        // Use Schlick's approximation for reflectance.
        auto r0 = (1-ref_idx) / (1+ref_idx);
        r0 = r0*r0;
        return r0 + (1-r0)*pow((1 - cosine),5);
    }

  public:
    dielectric(double index_of_refraction) : ir(index_of_refraction) {
    }
    bool scatter(const Ray& r_in, const HitRecord& rec, vec3& attenuation, Ray& scattered) const override {
        Random random = Random(0, 1);
        attenuation = vec3(1.0, 1.0, 1.0);
        double refraction_ratio = rec.front_face ? (1.0/ir) : ir;

        vec3 unit_direction = vec3::normalize(r_in.direction());
        double cos_theta = fmin(vec3::dot(-unit_direction, rec.normal), 1.0);
        double sin_theta = sqrt(1.0 - cos_theta*cos_theta);

        bool cannot_refract = refraction_ratio * sin_theta > 1.0;
        vec3 direction;

        if (cannot_refract || reflectance(cos_theta, refraction_ratio) > random.getRandom())
            direction = vec3::normalize(unit_direction.reflect(rec.normal));
        else
            direction = vec3::normalize(unit_direction.refract(rec.normal, refraction_ratio));

        scattered = Ray(rec.p, direction);
        return true;
    }
  
};
#endif