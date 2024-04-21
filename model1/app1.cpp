#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <unistd.h>
#include "libs/LINALG.h"
#include "libs/GRAPHICS.h"


// HOW TO RUN g++ -std=c++11 -o  app app1.cpp libs/LINALG.cpp libs/GRAPHICS.cpp


int main() {
    Screen S(100, 60);

    struct Mesh shape1;
    struct Triangle t1 = {.nodes = {Vector3(-10, -10, 1), Vector3(10, -10, 1), Vector3(0, 10, 1)}};
    struct Triangle t2 = {.nodes = {Vector3(-20, 10, 1), Vector3(20, 10, 1), Vector3(0, -10, 1)}};
    shape1.tris.push_back(t1);
    shape1.tris.push_back(t2);
    
    int x_bar, y_bar, diff_x, diff_y;
    float dt = 0.07;
    
    // Calculate rotation matrix
    Matrix temp_rot(2, 2);
    temp_rot.vals[0][0] = cos(dt);
    temp_rot.vals[0][1] = -sin(dt);
    temp_rot.vals[1][0] = sin(dt);
    temp_rot.vals[1][1] = cos(dt);

    while (true) {
        for (int tri = 0; tri < shape1.tris.size(); tri++) {

            x_bar = 0;
            y_bar = 0;

            for (int v = 0; v < 3; v++) {
                // Original point
                Matrix original_2d(2, 1);
                original_2d.vals[0][0] = shape1.tris[tri].nodes[v].vals[0][0];
                original_2d.vals[1][0] = shape1.tris[tri].nodes[v].vals[1][0];

                // Apply rotation
                Matrix final_2d = temp_rot.multiply(original_2d);

                // Update the point with the rotated coordinates
                shape1.tris[tri].nodes[v].vals[0][0] = final_2d.vals[0][0];
                shape1.tris[tri].nodes[v].vals[1][0] = final_2d.vals[1][0];
                
                // Center on screen
                x_bar += shape1.tris[tri].nodes[v].vals[0][0] / 3;
                y_bar += shape1.tris[tri].nodes[v].vals[1][0] / 3;
            }

            diff_x = S.w / 2 - x_bar;
            diff_y = S.h / 2 - y_bar;

            for (int v = 0; v < 3; v++) {
                shape1.tris[tri].nodes[v].vals[0][0] += diff_x;
                shape1.tris[tri].nodes[v].vals[1][0] += diff_y;
            }
        }

  

        S.draw_mesh(shape1);
        S.display();
        S.refresh();
        usleep(20000);

    }

}