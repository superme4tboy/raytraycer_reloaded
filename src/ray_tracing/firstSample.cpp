#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

#include "utils/vec3.h"
#include "utils/display.h"


class firstExample {
    
    public:
    firstExample() {}

    void drawFirstExample(sf::Uint8 *framebuffer, Display &display) {
        int width = display.getDisplayWidth();

        for(int y = 0; y<display.getDisplayHeight(); y++) {
            for(int x = 0; x < display.getDisplayWidth(); x++) {
            vec3 pixel_color = vec3();
            pixel_color.x =  double(x) / double(width-1);
            pixel_color.y =  double(y) / double(display.getDisplayHeight()-1);
            pixel_color.z =  0.0;
            int currentPos = display.getFramebufferPos(x, y);
            framebuffer[currentPos    ] = pixel_color.x * 255;     // Red
            framebuffer[currentPos + 1] = pixel_color.y * 255; // Green
            framebuffer[currentPos + 2] = pixel_color.z * 255; // Blue
            framebuffer[currentPos + 3] = 255;                   // Alpha Value
            }
        }
    }

};