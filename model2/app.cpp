#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <unistd.h>
#include "libs/LINALG.h"
#include "libs/GRAPHICS.h"

// g++ -std=c++11 -o app app.cpp libs/LINALG.cpp libs/GRAPHICS.cpp

int main() {
    // Screen S(194, 60, 2, 9.9, 10);
    Screen S(450, 120, 2, 9.9, 10);
    Camera C;

    // struct Mesh shape1;
    // struct Triangle t1_11 = {.nodes = {Vector3(-10, -10, 10), Vector3(-10, 10, 10), Vector3(10, -10, 10)}};
    // struct Triangle t1_12 = {.nodes = {Vector3(10, 10, 10), Vector3(-10, 10, 10), Vector3(10, -10, 10)}};
    // struct Triangle t1_21 = {.nodes = {Vector3(-10, -10, -10), Vector3(10, -10, -10), Vector3(-10, 10, -10)}};
    // struct Triangle t1_22 = {.nodes = {Vector3(10, -10, -10), Vector3(10, 10, -10), Vector3(-10, 10, -10)}};
    // struct Triangle t1_31 = {.nodes = {Vector3(-10, 10, -10), Vector3(-10, 10, 10), Vector3(10, 10, -10)}};
    // struct Triangle t1_32 = {.nodes = {Vector3(10, 10, 10), Vector3(10, 10, -10), Vector3(-10, 10, 10)}};
    // struct Triangle t1_41 = {.nodes = {Vector3(-10, -10, -10), Vector3(10, -10, -10), Vector3(-10, -10, 10)}};
    // struct Triangle t1_42 = {.nodes = {Vector3(10, -10, 10), Vector3(10, -10, -10), Vector3(-10, -10, 10)}};
    // struct Triangle t1_51 = {.nodes = {Vector3(-10, -10, -10), Vector3(-10, -10, 10), Vector3(-10, 10, -10)}};
    // struct Triangle t1_52 = {.nodes = {Vector3(-10, 10, 10), Vector3(-10, 10, -10), Vector3(-10, -10, 10)}};
    // struct Triangle t1_61 = {.nodes = {Vector3(10, -10, -10), Vector3(10, 10, -10), Vector3(10, -10, 10)}};
    // struct Triangle t1_62 = {.nodes = {Vector3(10, 10, 10), Vector3(10, 10, -10), Vector3(10, -10, 10)}};

    // shape1.tris.push_back(t1_11);
    // shape1.tris.push_back(t1_12);
    // shape1.tris.push_back(t1_21);
    // shape1.tris.push_back(t1_22);
    // shape1.tris.push_back(t1_31);
    // shape1.tris.push_back(t1_32);
    // shape1.tris.push_back(t1_41);
    // shape1.tris.push_back(t1_42);
    // shape1.tris.push_back(t1_51);
    // shape1.tris.push_back(t1_52);
    // shape1.tris.push_back(t1_61);
    // shape1.tris.push_back(t1_62);

    struct Mesh shape1;
    // Vertices of a dodecahedron
    Matrix vertices[] = {
        Vector3(0, 1, 1.618).scale(30),
        Vector3(0, -1, 1.618).scale(30),
        Vector3(1, 1.618, 0).scale(30),
        Vector3(1, -1.618, 0).scale(30),
        Vector3(-1, 1.618, 0).scale(30),
        Vector3(-1, -1.618, 0).scale(30),
        Vector3(1.618, 0, 1).scale(30),
        Vector3(-1.618, 0, 1).scale(30),
        Vector3(1.618, 0, -1).scale(30),
        Vector3(-1.618, 0, -1).scale(30),
        Vector3(1, 1, -1.618).scale(30),
        Vector3(1, -1, -1.618).scale(30),
        Vector3(-1, 1, -1.618).scale(30),
        Vector3(-1, -1, -1.618).scale(30),
        Vector3(0, 1, -1.618).scale(30),
        Vector3(0, -1, -1.618).scale(30),
        Vector3(1.618, 1, 0).scale(30),
        Vector3(1.618, -1, 0).scale(30),
        Vector3(-1.618, 1, 0).scale(30),
        Vector3(-1.618, -1, 0).scale(30)
    };
    
    // Faces of a dodecahedron
    struct Triangle t1_11 = {.nodes = {vertices[0], vertices[2], vertices[6]}};
    struct Triangle t1_12 = {.nodes = {vertices[0], vertices[6], vertices[8]}};
    struct Triangle t1_13 = {.nodes = {vertices[0], vertices[8], vertices[4]}};
    struct Triangle t1_14 = {.nodes = {vertices[0], vertices[4], vertices[12]}};
    struct Triangle t1_15 = {.nodes = {vertices[0], vertices[12], vertices[2]}};
    struct Triangle t1_21 = {.nodes = {vertices[1], vertices[3], vertices[7]}};
    struct Triangle t1_22 = {.nodes = {vertices[1], vertices[7], vertices[9]}};
    struct Triangle t1_23 = {.nodes = {vertices[1], vertices[9], vertices[5]}};
    struct Triangle t1_24 = {.nodes = {vertices[1], vertices[5], vertices[13]}};
    struct Triangle t1_25 = {.nodes = {vertices[1], vertices[13], vertices[3]}};
    struct Triangle t1_31 = {.nodes = {vertices[2], vertices[6], vertices[10]}};
    struct Triangle t1_32 = {.nodes = {vertices[2], vertices[10], vertices[11]}};
    struct Triangle t1_33 = {.nodes = {vertices[2], vertices[11], vertices[16]}};
    struct Triangle t1_34 = {.nodes = {vertices[2], vertices[16], vertices[6]}};
    struct Triangle t1_41 = {.nodes = {vertices[3], vertices[7], vertices[17]}};
    struct Triangle t1_42 = {.nodes = {vertices[3], vertices[17], vertices[18]}};
    struct Triangle t1_43 = {.nodes = {vertices[3], vertices[18], vertices[8]}};
    struct Triangle t1_44 = {.nodes = {vertices[3], vertices[8], vertices[11]}};
    struct Triangle t1_45 = {.nodes = {vertices[3], vertices[11], vertices[7]}};
    struct Triangle t1_51 = {.nodes = {vertices[4], vertices[8], vertices[18]}};
    struct Triangle t1_52 = {.nodes = {vertices[4], vertices[18], vertices[19]}};
    struct Triangle t1_53 = {.nodes = {vertices[4], vertices[19], vertices[14]}};
    struct Triangle t1_54 = {.nodes = {vertices[4], vertices[14], vertices[12]}};
    struct Triangle t1_55 = {.nodes = {vertices[4], vertices[12], vertices[8]}};
    struct Triangle t1_61 = {.nodes = {vertices[5], vertices[9], vertices[15]}};
    struct Triangle t1_62 = {.nodes = {vertices[5], vertices[15], vertices[16]}};
    struct Triangle t1_63 = {.nodes = {vertices[5], vertices[16], vertices[10]}};
    struct Triangle t1_64 = {.nodes = {vertices[5], vertices[10], vertices[13]}};
    struct Triangle t1_65 = {.nodes = {vertices[5], vertices[13], vertices[9]}};
    struct Triangle t1_71 = {.nodes = {vertices[6], vertices[16], vertices[15]}};
    struct Triangle t1_72 = {.nodes = {vertices[6], vertices[15], vertices[17]}};
    struct Triangle t1_73 = {.nodes = {vertices[6], vertices[17], vertices[7]}};
    struct Triangle t1_74 = {.nodes = {vertices[6], vertices[7], vertices[10]}};
    struct Triangle t1_81 = {.nodes = {vertices[9], vertices[13], vertices[10]}};
    struct Triangle t1_82 = {.nodes = {vertices[9], vertices[10], vertices[17]}};
    struct Triangle t1_83 = {.nodes = {vertices[9], vertices[17], vertices[15]}};
    struct Triangle t1_84 = {.nodes = {vertices[9], vertices[15], vertices[5]}};
    struct Triangle t1_91 = {.nodes = {vertices[12], vertices[14], vertices[19]}};
    struct Triangle t1_92 = {.nodes = {vertices[12], vertices[19], vertices[18]}};
    struct Triangle t1_93 = {.nodes = {vertices[12], vertices[18], vertices[17]}};
    struct Triangle t1_94 = {.nodes = {vertices[12], vertices[17], vertices[15]}};
    struct Triangle t1_95 = {.nodes = {vertices[12], vertices[15], vertices[14]}};
    struct Triangle t1_101 = {.nodes = {vertices[11], vertices[10], vertices[13]}};
    struct Triangle t1_102 = {.nodes = {vertices[11], vertices[13], vertices[5]}};
    struct Triangle t1_103 = {.nodes = {vertices[11], vertices[5], vertices[16]}};
    struct Triangle t1_104 = {.nodes = {vertices[11], vertices[16], vertices[8]}};
    struct Triangle t1_105 = {.nodes = {vertices[11], vertices[8], vertices[18]}};

    shape1.tris.push_back(t1_11);
    shape1.tris.push_back(t1_12);
    shape1.tris.push_back(t1_13);
    shape1.tris.push_back(t1_14);
    shape1.tris.push_back(t1_15);
    shape1.tris.push_back(t1_21);
    shape1.tris.push_back(t1_22);
    shape1.tris.push_back(t1_23);
    shape1.tris.push_back(t1_24);
    shape1.tris.push_back(t1_25);
    shape1.tris.push_back(t1_31);
    shape1.tris.push_back(t1_32);
    shape1.tris.push_back(t1_33);
    shape1.tris.push_back(t1_34);
    shape1.tris.push_back(t1_41);
    shape1.tris.push_back(t1_42);
    shape1.tris.push_back(t1_43);
    shape1.tris.push_back(t1_44);
    shape1.tris.push_back(t1_45);
    shape1.tris.push_back(t1_51);
    shape1.tris.push_back(t1_52);
    shape1.tris.push_back(t1_53);
    shape1.tris.push_back(t1_54);
    shape1.tris.push_back(t1_55);
    shape1.tris.push_back(t1_61);
    shape1.tris.push_back(t1_62);
    shape1.tris.push_back(t1_63);
    shape1.tris.push_back(t1_64);
    shape1.tris.push_back(t1_65);
    shape1.tris.push_back(t1_71);
    shape1.tris.push_back(t1_72);
    shape1.tris.push_back(t1_73);
    shape1.tris.push_back(t1_74);
    shape1.tris.push_back(t1_81);
    shape1.tris.push_back(t1_82);
    shape1.tris.push_back(t1_83);
    shape1.tris.push_back(t1_84);
    shape1.tris.push_back(t1_91);
    shape1.tris.push_back(t1_92);
    shape1.tris.push_back(t1_93);
    shape1.tris.push_back(t1_94);
    shape1.tris.push_back(t1_95);
    shape1.tris.push_back(t1_101);
    shape1.tris.push_back(t1_102);
    shape1.tris.push_back(t1_103);
    shape1.tris.push_back(t1_104);
    shape1.tris.push_back(t1_105);

    float dx;
    float dy;
    float dz;
    float d_pitch;
    float d_yaw;
    char invar;
    float rotation_rate = 0.1;
    float displacement_rate = 5;

    while (true) {

        dx = 0;
        dy = 0;
        dz = 0;
        d_pitch = 0;
        d_yaw = 0;

        std::cout << "Type rel. coord changes: \n"; // Type a number and press enter
        std::cin >> invar;
        switch (invar) {
            case 'w': dz = displacement_rate; break;
            case 's': dz = -displacement_rate; break;
            case 'd': dx = displacement_rate; break;
            case 'a': dx = -displacement_rate; break;
            case 'u': dy = displacement_rate; break;
            case 'i': dy = -displacement_rate; break;
            case 'm': d_pitch = rotation_rate; break;
            case 'n': d_pitch = -rotation_rate; break;
            case 'k': d_yaw = rotation_rate; break;
            case 'j': d_yaw = -rotation_rate; break;
            default:  break;
        }


        // std::cout << dx << ", " << dy << ", " << dz << ", " << d_pitch << ", " << d_yaw << std::endl;

        C.control_cam(dx, dy, dz, d_pitch, d_yaw);
        struct Mesh shape1_cam_space = C.mesh_to_cam_space(shape1);
        S.draw_mesh_project(shape1_cam_space);
        S.display();
        S.refresh();
        usleep(50000);
    }


}