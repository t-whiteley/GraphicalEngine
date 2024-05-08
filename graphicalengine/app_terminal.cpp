#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <unistd.h>
#include "libs/LINALG.h"
#include "libs/GRAPHICS.h"
#include "libs/SHAPES.h"


// g++ -std=c++11 -o app app_terminal.cpp libs/LINALG.cpp libs/GRAPHICS.cpp libs/SHAPES.cpp

int main() {
    Screen S(175, 60, 1, 0.1, 1000);
    Camera C;

    float d_theta = 0.05;
    float theta = 0;

    // Initial cam settings
    float cam_dx = 0;
    float cam_dy = 0;
    float cam_dz = 0;
    float cam_d_pitch = 0;
    float cam_d_yaw = 0;
    char ch;
    float rotation_rate = 0.1;
    float displacement_rate = 0.1;


    while (true) {

        // Pan the camera from user input
        std::cout << "Change: \n";
        std::cin >> ch;
        switch (ch) {
            case 'w': cam_dz = displacement_rate; break;
            case 's': cam_dz = -displacement_rate; break;
            case 'd': cam_dx = displacement_rate; break;
            case 'a': cam_dx = -displacement_rate; break;
            case 'u': cam_dy = displacement_rate; break;
            case 'i': cam_dy = -displacement_rate; break;
            case 'm': cam_d_pitch = rotation_rate; break;
            case 'n': cam_d_pitch = -rotation_rate; break;
            case 'k': cam_d_yaw = rotation_rate; break;
            case 'j': cam_d_yaw = -rotation_rate; break;
            default:  break;
        }
        if (ch == 'q')
            break;


        // theta += d_theta;
        C.control_cam(cam_dx, cam_dy, -cam_dz, cam_d_pitch, cam_d_yaw);
        struct Mesh shape1_objet_space = build_cube_mesh(0, 0, -5, theta, theta/2, 0, 0.5);
        struct Mesh shape1_world_space = mesh_to_world_space(shape1_objet_space);
        struct Mesh shape1_cam_space = C.mesh_to_cam_space(shape1_world_space);
        struct Mesh shape1_view_volume = S.mesh_to_view_volume(shape1_cam_space);

        S.draw_mesh_Terminal(shape1_view_volume);
        S.display();
        S.refresh();

        float dt = (1.0f / 60) * 1000000; // 60 fps
        usleep(dt*2);

        cam_dx = cam_dy = cam_dz = cam_d_pitch = cam_d_yaw = 0;
    }

}