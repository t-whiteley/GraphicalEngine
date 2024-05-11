#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <unistd.h>
#include "libs/GRAPHICS.h"
#include "libs/LINALG.h"
#include "libs/SHAPES.h"


// g++ -std=c++11 -o app app_sfml.cpp libs/LINALG.cpp libs/GRAPHICS.cpp libs/SHAPES.cpp -I/opt/homebrew/Cellar/sfml/2.6.1/include -L/opt/homebrew/Cellar/sfml/2.6.1/lib -lsfml-graphics -lsfml-window -lsfml-system -DUSE_SFML


int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Graphics Engine");
    window.setFramerateLimit(60);

    Screen S(window.getSize().x, window.getSize().y, 2, 0.1, 1000);
    Camera C;

    // Initial shape vars
    struct Mesh shape1_objet_space;
    struct Mesh shape1_world_space;
    struct Mesh shape1_cam_space;
    struct Mesh shape1_view_volume;
    float d_theta = 0.05;
    float theta = 0;
    float pos_scale = 5;

    // Initial cam settings
    float cam_dx = 0;
    float cam_dy = 0;
    float cam_dz = 0;
    float cam_d_pitch = 0;
    float cam_d_yaw = 0;
    float rotation_rate = 0.05;
    float displacement_rate = 5;


    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed)
            {
                switch (event.key.code)
                {
                    case sf::Keyboard::W: cam_dz = displacement_rate; break;
                    case sf::Keyboard::S: cam_dz = -displacement_rate; break;
                    case sf::Keyboard::D: cam_dx = displacement_rate; break;
                    case sf::Keyboard::A: cam_dx = -displacement_rate; break;
                    case sf::Keyboard::Space: cam_dy = displacement_rate; break;
                    case sf::Keyboard::LShift: cam_dy = -displacement_rate; break;
                    case sf::Keyboard::M: cam_d_pitch = rotation_rate; break;
                    case sf::Keyboard::N: cam_d_pitch = -rotation_rate; break;
                    case sf::Keyboard::J: cam_d_yaw = rotation_rate; break;
                    case sf::Keyboard::K: cam_d_yaw = -rotation_rate; break;
                    case sf::Keyboard::Q: window.close(); break;
                    default: break;
                }
            }
        }

        // make my object do some rotations
        theta += d_theta;

        C.control_cam(cam_dx, cam_dy, -cam_dz, cam_d_pitch, cam_d_yaw);
        shape1_objet_space = build_cube_mesh(pos_scale*sin(theta)/2, pos_scale*cos(theta), -5, theta/5, theta/2, theta/3, 1);
        shape1_world_space = mesh_to_world_space(shape1_objet_space);
        shape1_cam_space = C.mesh_to_cam_space(shape1_world_space);
        shape1_view_volume = S.mesh_to_view_volume(shape1_cam_space);

        S.draw_mesh_SFML(shape1_view_volume, window);
        window.display();
        window.clear();
        cam_dx = cam_dy = cam_dz = cam_d_pitch = cam_d_yaw = 0;
    }
}