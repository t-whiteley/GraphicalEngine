#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <unistd.h>
#include "libs/LINALG.h"
#include "libs/GRAPHICS.h"


// HOW TO RUN g++ -std=c++11 -o  app app2.cpp libs/LINALG.cpp libs/GRAPHICS.cpp


int main() {
    Screen S(100, 60);

    struct Mesh shape1;
    // Front face
    struct Triangle t11 = {.nodes = {Vector3(-10, -10, 10), Vector3(-10, 10, 10), Vector3(10, -10, 10)}};
    struct Triangle t12 = {.nodes = {Vector3(10, 10, 10), Vector3(-10, 10, 10), Vector3(10, -10, 10)}};

    // Back face
    struct Triangle t21 = {.nodes = {Vector3(-10, -10, -10), Vector3(10, -10, -10), Vector3(-10, 10, -10)}};
    struct Triangle t22 = {.nodes = {Vector3(10, -10, -10), Vector3(10, 10, -10), Vector3(-10, 10, -10)}};

    // Top face
    struct Triangle t31 = {.nodes = {Vector3(-10, 10, -10), Vector3(-10, 10, 10), Vector3(10, 10, -10)}};
    struct Triangle t32 = {.nodes = {Vector3(10, 10, 10), Vector3(10, 10, -10), Vector3(-10, 10, 10)}};

    // Bottom face
    struct Triangle t41 = {.nodes = {Vector3(-10, -10, -10), Vector3(10, -10, -10), Vector3(-10, -10, 10)}};
    struct Triangle t42 = {.nodes = {Vector3(10, -10, 10), Vector3(10, -10, -10), Vector3(-10, -10, 10)}};

    // Left face
    struct Triangle t51 = {.nodes = {Vector3(-10, -10, -10), Vector3(-10, -10, 10), Vector3(-10, 10, -10)}};
    struct Triangle t52 = {.nodes = {Vector3(-10, 10, 10), Vector3(-10, 10, -10), Vector3(-10, -10, 10)}};

    // Right face
    struct Triangle t61 = {.nodes = {Vector3(10, -10, -10), Vector3(10, 10, -10), Vector3(10, -10, 10)}};
    struct Triangle t62 = {.nodes = {Vector3(10, 10, 10), Vector3(10, 10, -10), Vector3(10, -10, 10)}};

    shape1.tris.push_back(t11);
    shape1.tris.push_back(t12);
    shape1.tris.push_back(t21);
    shape1.tris.push_back(t22);
    shape1.tris.push_back(t31);
    shape1.tris.push_back(t32);
    shape1.tris.push_back(t41);
    shape1.tris.push_back(t42);
    shape1.tris.push_back(t51);
    shape1.tris.push_back(t52);
    shape1.tris.push_back(t61);
    shape1.tris.push_back(t62);
    
    int x_bar, y_bar, diff_x, diff_y, count;
    float dt = 0.07;
    
    // Rotation around the x-axis
    Matrix rotation_x(3, 3);
    rotation_x.vals[0][0] = 1;
    rotation_x.vals[0][1] = 0;
    rotation_x.vals[0][2] = 0;
    rotation_x.vals[1][0] = 0;
    rotation_x.vals[1][1] = cos(dt);
    rotation_x.vals[1][2] = -sin(dt);
    rotation_x.vals[2][0] = 0;
    rotation_x.vals[2][1] = sin(dt);
    rotation_x.vals[2][2] = cos(dt);

    // Rotation around the y-axis
    Matrix rotation_y(3, 3);
    rotation_y.vals[0][0] = cos(dt);
    rotation_y.vals[0][1] = 0;
    rotation_y.vals[0][2] = sin(dt);
    rotation_y.vals[1][0] = 0;
    rotation_y.vals[1][1] = 1;
    rotation_y.vals[1][2] = 0;
    rotation_y.vals[2][0] = -sin(dt);
    rotation_y.vals[2][1] = 0;
    rotation_y.vals[2][2] = cos(dt);

    // Rotation around the z-axis
    Matrix rotation_z(3, 3);
    rotation_z.vals[0][0] = cos(dt);
    rotation_z.vals[0][1] = -sin(dt);
    rotation_z.vals[0][2] = 0;
    rotation_z.vals[1][0] = sin(dt);
    rotation_z.vals[1][1] = cos(dt);
    rotation_z.vals[1][2] = 0;
    rotation_z.vals[2][0] = 0;
    rotation_z.vals[2][1] = 0;
    rotation_z.vals[2][2] = 1;



    while (true) {
        x_bar = 0;
        y_bar = 0;
        count = 0;

        for (int tri = 0; tri < shape1.tris.size(); tri++) {


            for (int v = 0; v < 3; v++) {
                // Original point
                Matrix original_3d(3, 1);
                original_3d.vals[0][0] = shape1.tris[tri].nodes[v].vals[0][0];
                original_3d.vals[1][0] = shape1.tris[tri].nodes[v].vals[1][0];
                original_3d.vals[2][0] = shape1.tris[tri].nodes[v].vals[3][0];

                // Apply rotation
                Matrix final_3d = rotation_y.multiply(rotation_x.multiply(original_3d));

                // Update the point with the rotated coordinates
                shape1.tris[tri].nodes[v].vals[0][0] = final_3d.vals[0][0];
                shape1.tris[tri].nodes[v].vals[1][0] = final_3d.vals[1][0];
                shape1.tris[tri].nodes[v].vals[2][0] = final_3d.vals[2][0];
                
                // Center on screen
                x_bar += shape1.tris[tri].nodes[v].vals[0][0];
                y_bar += shape1.tris[tri].nodes[v].vals[1][0];
                count += 3;
            }

        }

        x_bar /= count;
        y_bar /= count;
        diff_x = S.w / 2 - x_bar;
        diff_y = S.h / 2 - y_bar;

        for (int tri = 0; tri < shape1.tris.size(); tri++) {
            for (int v = 0; v < 3; v++) {

                for (int v = 0; v < 3; v++) {
                    shape1.tris[tri].nodes[v].vals[0][0] += diff_x;
                    shape1.tris[tri].nodes[v].vals[1][0] += diff_y;
                }
            }
        }


        S.draw_mesh_project(shape1);
        S.display();
        S.refresh();
        usleep(20000);

    }

}