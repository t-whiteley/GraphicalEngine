#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <unistd.h>
#include "libs/GRAPHICS.h"
#include "libs/LINALG.h"
#include "libs/SHAPES.h"
#include <SFML/Graphics.hpp>


// g++ -std=c++11 -o app app1.cpp libs/LINALG.cpp libs/GRAPHICS.cpp libs/SHAPES.cpp -I/opt/homebrew/Cellar/sfml/2.6.1/include -L/opt/homebrew/Cellar/sfml/2.6.1/lib   -lsfml-graphics -lsfml-window -lsfml-system
// SET POINT DOES SOME VALIDATION TO MAKE SURE COORDS ARE WITHIN THE CANONICAL, AND THEN SCALES TO THE VIEWPORT
// BUT THE PERSP. PROJ. TRANSFORM CONVERTS TO CANONICAL COORDS
// CURRENTLY THE CAMERA CONTROLS MOVE IN THE ABSOLUTE SPACE; I WANT THEM TO MOVE RELATIVE TO THE DIRECTION IT POINTS
// IMPROVE LIBRARY MANAGEMENT -> MAKE FILE
// PERFORMANCE / CLEAN UP CODE
// WEIRD BEHAVIOUR WHEN LINES GO OVER YOUR HEAD

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Graphics Engine");
    window.setFramerateLimit(60);

    Screen S(window.getSize().x, window.getSize().y, 2.5, 0.1, 100);
    Camera C;

    // Initial shape vars
    struct Mesh shape1_objet_space;
    struct Mesh shape1_world_space;
    struct Mesh shape1_cam_space;
    struct Mesh shape1_view_volume;
    float d_theta = 0.05;
    float theta = 0;

    // Initial cam settings
    float cam_dx = 0;
    float cam_dy = 0;
    float cam_dz = 0;
    float cam_d_pitch = 0;
    float cam_d_yaw = 0;
    float rotation_rate = 0.1;
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


        theta += d_theta;
        C.control_cam(cam_dx, cam_dy, -cam_dz, cam_d_pitch, cam_d_yaw);
        shape1_objet_space = build_cube_mesh(0, 0, -5, theta, theta/2, 0, 10);
        shape1_world_space = mesh_to_world_space(shape1_objet_space);
        shape1_cam_space = C.mesh_to_cam_space(shape1_world_space);
        shape1_view_volume = S.mesh_to_view_volume(shape1_cam_space);

        S.draw_mesh(shape1_view_volume, window);
        window.display();
        window.clear();
        cam_dx = cam_dy = cam_dz = cam_d_pitch = cam_d_yaw = 0;
    }
}