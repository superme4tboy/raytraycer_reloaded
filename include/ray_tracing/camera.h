#pragma once
#include "vec3.h"
#include "random.h"
#include "display.h"
#include "ray.h"

class Camera
{
private:
    double aspect_ratio;
    double l; //left
    double r; //right
    double b; //botton
    double t; //top
    double d; //distance to camera

    const int display_height;
    const int display_width;
    vec3 cameraPos;
    Random random;
public:
    Camera(Display display)
    : aspect_ratio(display.getDisplayRatio()),l(-1. * aspect_ratio),r(+1. * aspect_ratio),b(-1.),t(+1.),d(+1.),cameraPos(0,0,0),
    display_height(display.getDisplayHeight()),display_width(display.getDisplayWidth()), random(Random())
    {}

    Ray getRayWithOffset(int x, int y)
    {
        double randomNumberX = random.getRandom();
        double randomNumberY = random.getRandom();
        double u = l + (r- l) * (x + randomNumberX) / display_width;
        double v = t + (b - t) * (y + randomNumberY) / display_height;
        vec3 rayDirection = vec3::normalize(vec3(u,v, -d) - cameraPos);
        Ray ray = Ray(cameraPos,rayDirection);
        return ray;
    }

    Ray getRay(int x, int y)
    {
        double u = l + (r- l) * (x) / display_width;
        double v = t + (b - t) * (y) / display_height;
        vec3 rayDirection = vec3::normalize(vec3(u,v, -d) - cameraPos);
        Ray ray = Ray(cameraPos,rayDirection);
        return ray;
    }
};