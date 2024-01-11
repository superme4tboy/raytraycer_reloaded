#include "raytracer.h"
#include "sceneObject.h"

void raytracer::render(sf::Uint8 *framebuffer, Display &display, int y_min, int y_max, std::atomic<bool> &should_abort)
{
    int width = display.getDisplayWidth();
    Camera camera = Camera(display);
    Scene currentScene = Scene();
    currentScene.create_scene_objects();

    for (int y = y_min; y < y_max; y++)
    {
        for (int x = 0; x < width; x++)
        {
            
            vec3 pixel_color = vec3();

            for(int i = 0; i < samples_per_pixel;i++) {
                Ray ray = camera.getRayWithOffset(x, y);
                pixel_color += ray_color(ray, 0, currentScene);
            }
            double scale = 1.0 / samples_per_pixel;
            pixel_color = scale * pixel_color;
            //pixel_color = vec3::sqrt(pixel_color);
            pixel_color = vec3::clamp(pixel_color, 0.0, 1.0);
            int currentPos = ((y * width) + x) * 4;
            framebuffer[currentPos] = pixel_color.x * 255;     // Red
            framebuffer[currentPos + 1] = pixel_color.y * 255; // Green
            framebuffer[currentPos + 2] = pixel_color.z * 255; // Blue
            framebuffer[currentPos + 3] = 255;                 // Alpha Value
            if (should_abort)
            {
                return;
            }
        }
    }
}

vec3 raytracer::ray_color(const Ray &r, int currentDepth, Scene currentScene)
{
    if (currentDepth > MAX_DEPTH)
    {
        return vec3(0);
    }

    // pointer to the object that was hit by the ray
    HitRecord rec;

    // intersection distance from the ray origin to the point hit
    auto t = std::numeric_limits<double>::max();

    if (currentScene.hit(r,0.001 ,t, rec))
    {
        Ray scattered;
        vec3 attenuation;
        if (rec.material->scatter(r, rec, attenuation, scattered))
            return attenuation * ray_color(scattered, currentDepth + 1, currentScene);
        return vec3(0,0,0);
    }
    t = 0.5 * (r.direction().y + 1.0);
    vec3 hitColor = (1.0 - t) * vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);
    return hitColor;
}
