#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <unistd.h>
#include "libs/LINALG.h"
#include "libs/GRAPHICS.h"
#include "libs/SHAPES.h"

// g++ -std=c++11 -o app app.cpp libs/LINALG.cpp libs/GRAPHICS.cpp libs/SHAPES.cpp


int main() {

    Screen S(175, 60, 4, 0.1, 1000);
    Camera C;   

    struct Mesh shape1 = build_cube_mesh(0, 0, 20, 0.2, 0.1, 0.2, 30);
    // struct Mesh shape1 = build_dodecahedron_mesh(6, 2, 5, 0.2, 0.2, 0.2, 15);
    // struct Mesh shape1 = build_octahedron_mesh(6, 2, 5, 0.2, 0.2, 0.2, 15);


    // Initial cam settings
    float cam_dx = 0;
    float cam_dy = 0;
    float cam_dz = 0;
    float cam_d_pitch = 0;
    float cam_d_yaw = 0;
    char ch;
    float rotation_rate = 0.1;
    float displacement_rate = 5;


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


        // Change the position of an object in space
        shape1.world_yaw += 0.07;
        shape1.world_pitch += 0.08;
        shape1.world_roll += 0.08;



        // Perform all the transformations
        C.control_cam(cam_dx, cam_dy, cam_dz, cam_d_pitch, cam_d_yaw);

        struct Mesh shape1_world_space = mesh_to_world_space(shape1);

        struct Mesh shape1_cam_space = C.mesh_to_cam_space(shape1_world_space);

        struct Mesh shape1_view_volume_space = S.mesh_to_view_volume(shape1_cam_space);

        S.draw_mesh(shape1_view_volume_space);

        S.display();
        S.refresh();
        usleep(40000);

        cam_dx = cam_dy = cam_dz = cam_d_pitch = cam_d_yaw = 0;
    }
}