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
    // Screen S(450, 120, 2, 9.9, 10);
    Screen S(150, 50, 3, 0.1, 100);
    Camera C;
    

    std::vector<struct Mesh> shapes_in_world;
    struct Mesh shape1 = build_cube_mesh(5, 2, -3, 0.2, 0.2, 0.2, 15);
    // struct Mesh shape1 = build_dodecahedron_mesh(6, 2, 5, 0.2, 0.2, 0.2, 15);
    // struct Mesh shape1 = build_octahedron_mesh(6, 2, 5, 0.2, 0.2, 0.2, 15);
    shapes_in_world.push_back(shape1);


    float cam_dx = 0;
    float cam_dy = 0;
    float cam_dz = 0;
    float cam_d_pitch = 0;
    float cam_d_yaw = 0;
    char invar;
    float rotation_rate = 0.1;
    float displacement_rate = 5;

    while (true) {

        // std::cout << "Change: \n"; // Type a number and press enter
        // std::cin >> invar;
        // switch (invar) {
        //     case 'w': cam_dz = displacement_rate; break;
        //     case 's': cam_dz = -displacement_rate; break;
        //     case 'd': cam_dx = displacement_rate; break;
        //     case 'a': cam_dx = -displacement_rate; break;
        //     case 'u': cam_dy = displacement_rate; break;
        //     case 'i': cam_dy = -displacement_rate; break;
        //     case 'm': cam_d_pitch = rotation_rate; break;
        //     case 'n': cam_d_pitch = -rotation_rate; break;
        //     case 'k': cam_d_yaw = rotation_rate; break;
        //     case 'j': cam_d_yaw = -rotation_rate; break;
        //     default:  break;
        // }

        shape1.world_yaw += 0.07;
        shape1.world_pitch += 0.08;
        // shape1.world_roll += 0.08;


        C.control_cam(cam_dx, cam_dy, cam_dz, cam_d_pitch, cam_d_yaw);

        struct Mesh shape1_world_space = mesh_to_world_space(shape1); // object space -> world space
        // shape1_world_space.tris[0].nodes[0].print();

        struct Mesh shape1_cam_space = C.mesh_to_cam_space(shape1_world_space); // world space -> cam space
        // shape1_cam_space.tris[0].nodes[0].print();

        S.draw_mesh_project(shape1_cam_space); // cam space to canonical view vol.
        S.display();
        S.refresh();
        usleep(50000);
    }


}