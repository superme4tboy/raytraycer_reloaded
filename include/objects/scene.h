#pragma once

#include <vector>
#include <memory>

#include "sceneObject.h"
#include "sphere.h"
#include "material.h"


class Scene {

private: 
        std::vector<std::shared_ptr<SceneObject>> objects;
        //std::vector<Light*> lights;
        std::shared_ptr<lambertian>  material_ground = std::make_shared<lambertian>(vec3(0.8, 0.8, 0.0));
        std::shared_ptr<lambertian>  material_center = std::make_shared<lambertian>(vec3(0.7, 0.3, 0.3));
        std::shared_ptr<dielectric>  material_left   = std::make_shared<dielectric>(1.5);
        std::shared_ptr<metal>       material_right  = std::make_shared<metal>(vec3(0.8, 0.6, 0.2),0.0);
    public:
        Scene();
        ~Scene();

        void add_object(SceneObject *object);

        //void add_light(Light *light);

        std::vector<std::shared_ptr<SceneObject>> create_scene_objects();
    //std::vector<Light*> create_scene_lights();

    std::vector<std::shared_ptr<SceneObject>> get_objects() const;
    //std::vector<Light*> get_lights() const;
    bool hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const;
    //void clear_lights();
    void clear_objects();
};
