#pragma once

#include <memory>

#include "display.h"
// #include "sceneObject.h"
#include "thread_pool.hpp"
#include "camera.h"
#include "scene.h"

class raytracer
{
private:
    const int MAX_DEPTH = 5;
    const int samples_per_pixel = 1;

public:
    raytracer() = default;
    vec3 ray_color(const Ray &r, int currentDepth, Scene currentScene);

    void render(sf::Uint8 *framebuffer, Display &display, int y_min, int y_max, std::atomic<bool> &should_abort);

private:
    
    
};