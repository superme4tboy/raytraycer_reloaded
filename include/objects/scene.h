#pragma once

#include <vector>
#include <memory>

#include "sceneObject.h"
#include "sphere.h"

class Scene {

private: 
    std::vector<std::shared_ptr<SceneObject>> objects;
    //std::vector<Light*> lights;
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
