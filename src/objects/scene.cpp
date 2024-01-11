#include "scene.h"

Scene::Scene() {
    // Constructor
}

Scene::~Scene() {
    // Destructor
    // No need to delete objects because we are using smart pointers
}

void Scene::add_object(SceneObject *object) {
    objects.push_back(std::shared_ptr<SceneObject>(object));
}

std::vector<std::shared_ptr<SceneObject>> Scene::create_scene_objects() {
    {
        const vec3 pos(0,-100.5,-1);
        const double radius = 100;
        objects.push_back(std::shared_ptr<SceneObject>(std::make_shared<Sphere>(pos, radius, material_ground)));
    }

    {
        //muesste pos(0,0,-1) sein siehe kapitel ueber antialiasing
        const vec3 pos(0,0,-1);
        const double radius = 0.5;
        objects.push_back(std::shared_ptr<SceneObject>(std::make_shared<Sphere>(pos, radius, material_center)));
    }

    {
        const vec3 pos(-1,0,-1);
        const double radius = 0.4;
        objects.push_back(std::shared_ptr<SceneObject>(std::make_shared<Sphere>(pos, radius, material_left)));
    }

    {
        const vec3 pos(1,0,-1);
        const double radius = 0.5;
        objects.push_back(std::shared_ptr<SceneObject>(std::make_shared<Sphere>(pos, radius, material_right)));
    }

    // {
    //     const vec3 pos(0,1.4,-1);
    //     const double radius = 0.5;
    //     const vec3 color(0.0,0.0,1.0);
    //     objects.push_back(std::shared_ptr<SceneObject>(std::make_shared<Sphere>(pos, radius, color)));
    // }

    
    
    return objects;
}

std::vector<std::shared_ptr<SceneObject>> Scene::get_objects() const {
    return objects;
}

void Scene::clear_objects() {
    objects.clear();
}

bool Scene::hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const {
    HitRecord temp_rec;
    bool hit_anything = false;
    auto closest_so_far = t_max;

    for (const auto& object : objects) {
        if (object->hit(r, t_min, closest_so_far, temp_rec)) {
            hit_anything = true;
            closest_so_far = temp_rec.t;
            rec = temp_rec;
        }
    }

    return hit_anything;
}