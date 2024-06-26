#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <iostream>
#include <vector>
#include "LINALG.h"


#ifdef USE_SFML
#include <SFML/Graphics.hpp>
#endif

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


struct Mesh build_cube_mesh(float x, float y, float z, float pitch, float yaw, float roll, float scale);
struct Mesh build_dummy_mesh(struct Mesh original_mesh);
void transform_mesh(float dx, float dy, float dz, float dpitch, float dyaw, float droll, float dscale, struct Mesh& mesh);
void mesh_to_world_space(struct Mesh& mesh0, struct Mesh& mesh1);



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
        float lerp(float a, float b, float t);

        void set_point_Terminal(float x, float y, float z);
        void set_line_Terminal(float x1, float y1, float z1, float x2, float y2, float z2);
        void draw_mesh_Terminal(struct Mesh& mesh);

        #ifdef USE_SFML
        void set_point_SFML(double x, double y, double z, sf::RenderWindow& window);
        void set_line_SFML(float x1, float y1, float z1, float x2, float y2, float z2, sf::RenderWindow& window);
        void draw_mesh_SFML(struct Mesh& mesh, sf::RenderWindow& window);
        #endif

        void mesh_to_view_volume(struct Mesh& mesh0, struct Mesh& mesh1);
};



class Camera {
    private:
        void Build_ToCamSpace(Matrix& m);
    
    public:
        Matrix cam_position;
        float cam_yaw; // measured from -z
        float cam_pitch; // measured from pitch vector up
        Matrix ToCamSpace;

        Camera();
        void control_cam(float dx, float dy, float dz, float d_pitch, float d_yaw);
        void mesh_to_cam_space(struct Mesh& mesh0, struct Mesh& mesh1);
};


#endif