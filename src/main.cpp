#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <iostream>
#include <memory>
#include <vector>
#include <cmath>
#include <limits>
#include <tuple>
#include <algorithm>
#include <iostream>
#include <atomic>
#include <assert.h>
#include <chrono>
#include <future>
#include <assert.h>
#include <cstring>

#include "utils/thread_pool.hpp"
#include "display.h"
#include "ray_tracing/firstSample.cpp"
#include "raytracer.h"

std::atomic<int> finished_threads = 0;
int threads = 0;

class main_window
{
private:
    std::vector<std::future<bool>> futures;
    bool thread_enabled = true;

public:
    void main_window_loop(sf::RenderWindow &window, sf::Uint8 *framebuffer, Display &display, sf::Texture &texture, sf::Sprite &sprite)
    {
        std::atomic<bool> should_abort = false;
        thread_pool pool;
        //const auto objects = create_scene_objects();

        auto range = display.getDisplayHeight() / pool.get_thread_count();

        bool draw_new_image = true;

        // std::promise<void> exitSignal;
        sf::Clock clock;
        while (window.isOpen())
        {
            // check all the window's events that were triggered since the last iteration of the loop
            sf::Event event;
            while (window.pollEvent(event))
            {
                // "close requested" event: we close the window
                if (event.type == sf::Event::Closed)
                    window.close();
                if (event.type == sf::Event::Resized)
                {
                    window.setView(sf::View(sf::FloatRect(sf::Vector2f(0, 0), sf::Vector2f(event.size.width, event.size.height))));
                    should_abort = true;

                    display = Display((int)event.size.width, (int)event.size.height);
                    //exception aborted why?

                    for(auto &future : futures)
                    {
                        future.wait();
                    }

                    delete[] framebuffer;
                    uint32_t size = display.getDisplayWidth() * display.getDisplayHeight() * 4;
                    framebuffer = new sf::Uint8[size];
                    std::memset(framebuffer,0,size);
                    range = (display.getDisplayHeight() / pool.get_thread_count());
                    should_abort = false;
                    draw_new_image = true;
                }
            }
            // draw
            if (draw_new_image)
            {
                raytracer Raytracer = raytracer();
                int y_max = display.getDisplayHeight();
                int y_min = y_max - range;
                threads = 0;
                finished_threads = 0;
                futures.clear();
                if(thread_enabled) 
                {
                while (y_min > 0)
                {
                    futures.push_back(pool.submit([&display, &framebuffer, &Raytracer, y_min, y_max,&should_abort]
                                                    { Raytracer.render(framebuffer, display, y_min, y_max,should_abort); finished_threads++; }));
                    threads++;
                    y_max -= range;
                    y_min -= range;
                }
                if (y_max >= 0)
                {
                    futures.push_back(pool.submit([&display, &framebuffer,&Raytracer, y_min, y_max, &should_abort]
                                                       { Raytracer.render(framebuffer, display, 0, y_max,should_abort); finished_threads++; }));
                    
                    threads++;
                }
            } else {
                Raytracer.render(framebuffer, display, 0, display.getDisplayHeight(),should_abort);
            }
                draw_new_image = false;
            }
            window.clear(sf::Color::Black);
            window.draw(sprite);
            if (threads == finished_threads || clock.getElapsedTime().asMilliseconds() >= 100)
            {
                clock.restart();
                if (threads == finished_threads)
                {
                    threads = 0;
                }
                texture.create(display.getDisplayWidth(), display.getDisplayHeight());
                texture.update(framebuffer);
                sprite.setTexture(texture, true);
            }
            window.display();
        }
        // If window is closed the image does not render.
        should_abort = true;
    }

    /**
     * @brief create a standard sized window and start the RayTracer function.
     * It renders the finished picture. With resizing the Window the picture should be renewed
     */
    void entry_point_main_window()
    {

        //const auto lights = create_scene_lights();

        //Display display = Display(3440, 1440);
        Display display = Display(800, 600);
        sf::Uint8 *framebuffer = new sf::Uint8[display.getDisplayWidth() * display.getDisplayHeight() * 4];
        sf::Texture texture;
        texture.create(display.getDisplayWidth(), display.getDisplayHeight());
        sf::Sprite sprite(texture);
        sf::RenderWindow window(sf::VideoMode(display.getDisplayWidth(), display.getDisplayHeight()), "RayTracer");
        window.setVerticalSyncEnabled(true);
        window.setActive(false);

        main_window_loop(window, framebuffer, display, texture, sprite);
    }
};

int main()
{
    main_window ray_tracer = main_window();
    ray_tracer.entry_point_main_window();
    return 0;
}