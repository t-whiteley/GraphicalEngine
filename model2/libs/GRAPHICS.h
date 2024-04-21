#ifndef GRAPHICS_H
#define GRAPHICS_H


#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <unistd.h>
#include "LINALG.h"

struct Triangle {
    Matrix nodes[3];
};

struct Mesh {
    std::vector<Triangle> tris;
};

class Screen {
    private:
        Matrix Build_ToScreenSpace();

    public:
        std::vector<std::vector<char> > grid;
        int w;
        int h;
        float AR;
        float fov_x;
        float fov_y;
        float z_n;
        float z_f;

        Matrix ToScreenSpace;
        
        Screen(int width, int height, float fov_x, float z_near, float z_far);

        void refresh();

        void display();

        void set_point(int x, int y);

        void set_line(int x1, int y1, int x2, int y2);

        void draw_mesh(struct Mesh mesh);

        void draw_mesh_project(struct Mesh mesh);

};


class Camera {
    private:
        Matrix Build_ToCamSpace();
    
    public:
        Matrix cam_position;
        float cam_yaw; // measured from -z
        float cam_pitch; // measured from pitch vector up
        Matrix ToCamSpace;

        Camera();

        void control_cam(float dx, float dy, float dz, float d_pitch, float d_yaw);

        struct Mesh mesh_to_cam_space(struct Mesh mesh);

};


#endif