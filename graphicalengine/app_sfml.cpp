#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <unistd.h>
#include "libs/GRAPHICS.h"
#include "libs/LINALG.h"

// g++ -std=c++11 -o app app_sfml.cpp libs/LINALG.cpp libs/GRAPHICS.cpp -I/opt/homebrew/Cellar/sfml/2.6.1/include -L/opt/homebrew/Cellar/sfml/2.6.1/lib -lsfml-graphics -lsfml-window -lsfml-system -DUSE_SFML

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Graphics Engine");
    window.setFramerateLimit(60);

    Screen S(window.getSize().x, window.getSize().y, 2, 0.1, 1000);
    Camera C;

    // Initial mesh vars
    struct Mesh m1_obj_space = build_cube_mesh(0, 0, -3, 0, 0, 0, 1);
    struct Mesh m1_world_space = build_dummy_mesh(m1_obj_space);
    struct Mesh m1_cam_space = build_dummy_mesh(m1_obj_space);
    struct Mesh m1_viewvol_space = build_dummy_mesh(m1_obj_space);

    // Initial cam settings
    float d_theta = 0.05;
    float cam_dx = 0, cam_dy = 0, cam_dz = 0, cam_d_pitch = 0, cam_d_yaw = 0;
    float rotation_rate = 0.1, displacement_rate = 0.5;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed) {
                switch (event.key.code) {
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

        C.control_cam(cam_dx, cam_dy, -cam_dz, cam_d_pitch, cam_d_yaw);
        transform_mesh(0, 0, 0, d_theta, d_theta/2, 0, 0, m1_obj_space);
        mesh_to_world_space(m1_obj_space, m1_world_space);
        C.mesh_to_cam_space(m1_world_space, m1_cam_space);
        S.mesh_to_view_volume(m1_cam_space, m1_viewvol_space);

        S.draw_mesh_SFML(m1_viewvol_space, window);
        window.display();
        window.clear();

        cam_dx = cam_dy = cam_dz = cam_d_pitch = cam_d_yaw = 0;
    }
}

