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
    public:
        std::vector<std::vector<char> > grid;
        int w;
        int h;
        float AR;
        
        Screen(int width, int height);

        void refresh();

        void display();

        void set_point(int x, int y);

        void set_line(int x1, int y1, int x2, int y2);

        void draw_mesh(struct Mesh mesh);

        void draw_mesh_project(struct Mesh mesh);

};


#endif