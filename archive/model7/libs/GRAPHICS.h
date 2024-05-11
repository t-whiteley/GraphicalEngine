#ifndef GRAPHICS_H
#define GRAPHICS_H


#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <unistd.h>
#include "LINALG.h"


#ifdef USE_SFML
#include <SFML/Graphics.hpp>
#endif

// namespace sf {
//     class RenderWindow;
// }

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

        void set_point_Terminal(double x, double y, double z);
        void set_line_Terminal(float x1, float y1, float z1, float x2, float y2, float z2);
        void draw_mesh_Terminal(struct Mesh mesh);

        #ifdef USE_SFML
        void set_point_SFML(double x, double y, double z, sf::RenderWindow& window);
        void set_line_SFML(float x1, float y1, float z1, float x2, float y2, float z2, sf::RenderWindow& window);
        void draw_mesh_SFML(struct Mesh mesh, sf::RenderWindow& window);
        #endif

        
        double lerp(double a, double b, double t);

        struct Mesh mesh_to_view_volume(struct Mesh mesh);



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