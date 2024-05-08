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
    float world_x;
    float world_y;
    float world_z;
    float world_pitch;
    float world_yaw;
    float world_roll;
    float world_scale;
};

class Screen {
    private:
        Matrix Build_ToScreenSpace();

    public:
        std::vector<std::vector<char> > grid;
        int w;
        int h;
        float AR;
        float fov_y;
        float z_n;
        float z_f;

        Matrix ToScreenSpace;
        
        Screen(int width, int height, float fov_vertical, float z_near, float z_far);

        void refresh();

        void display();

        void set_point(double x, double y, double z);

        void set_line(float x1, float y1, float z1, float x2, float y2, float z2);
        
        double lerp(double a, double b, double t);

        struct Mesh mesh_to_view_volume(struct Mesh mesh);

        void draw_mesh(struct Mesh mesh);


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


struct Mesh build_cube_mesh(float x, float y, float z, float pitch, float yaw, float roll, float scale);

struct Mesh mesh_to_world_space(struct Mesh mesh);

#endif