#include <cmath>
#include "GRAPHICS.h"

Screen::Screen(int width, int height) {
    w = width;
    h = height;
    AR = (float) w/h;

    for (int i = 0; i < h; i++) {
        std::vector<char> temp;
        for (int j = 0; j < w; j++) {
            temp.push_back('.');
        }
        grid.push_back(temp);
    }
}

void Screen::refresh() {
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            grid[i][j] = '.';
        }
    }
}

void Screen::display() {
    printf("__\n");
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            std::cout << grid[i][j];
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

void Screen::set_point(int x, int y) {
    if (x >= w || x < 0 || y < 1 || y >= h) {
        return;
    }
    grid[h-y][x] = 'X';
}

void Screen::set_line(int x1, int y1, int x2, int y2) {
    if (x1 == x2) {
        for (int y = std::min(y1, y2); y <= std::max(y1, y2); y++) {
            set_point(x1, y);
        }
        return;
    }

    double slope = static_cast<double>(y2 - y1) / (x2 - x1);
    double bias = y1 - slope * x1;
    if (x2 > x1) {
        for (int x = x1; x <= x2; x++) {
            int y = static_cast<int>(slope * x + bias);
            set_point(x, y);
        }
    }
    else {
        for (int x = x2; x <= x1; x++) {
            int y = static_cast<int>(slope * x + bias);
            set_point(x, y);
        }
    }
}



void Screen::draw_mesh(struct Mesh mesh) {
    for (int i = 0; i < mesh.tris.size(); i++) {
        for (int j = 0; j < 3; j++) {
            int x1 = mesh.tris[i].nodes[j].vals[0][0];
            int y1 = mesh.tris[i].nodes[j].vals[1][0];
            int x2 = mesh.tris[i].nodes[(j+1)%3].vals[0][0];
            int y2 = mesh.tris[i].nodes[(j+1)%3].vals[1][0];
            // mesh.tris[i].nodes[j].print();
            // set_point(x1, y1);
            // printf("x1: %d, y1: %d -> x2: %d, y2: %d\n", x1, y1, x2, y2);
            set_line(x1, y1, x2, y2);
        }
    }
}

void Screen::draw_mesh_project(struct Mesh mesh) {
    float fov_x = 2; // rad
    float fov_y = fov_x * w/h;
    float z_near = 0.1;
    float z_far = 100;

    Matrix proj_m(4, 4);
    proj_m.fill(0);
    proj_m.vals[0][0] = atan(fov_x/2);
    proj_m.vals[1][1] = atan(fov_y/2);
    proj_m.vals[2][2] = -(z_far+z_near)/(z_far-z_near);
    proj_m.vals[2][3] = -2*(z_far*z_near)/(z_far-z_near);
    proj_m.vals[3][2] = -1;


    for (int i = 0; i < mesh.tris.size(); i++) {
        for (int j = 0; j < 3; j++) {
            Matrix old_v(4, 1);
            old_v.vals[0][0] = mesh.tris[i].nodes[j].vals[0][0];
            old_v.vals[1][0] = mesh.tris[i].nodes[j].vals[1][0];
            old_v.vals[2][0] = mesh.tris[i].nodes[j].vals[2][0];
            old_v.vals[3][0] = 1;

            Matrix new_v = proj_m.multiply(old_v);
            new_v.vals[0][0] /= new_v.vals[3][0];
            new_v.vals[1][0] /= new_v.vals[3][0];
        }
    }

    for (int i = 0; i < mesh.tris.size(); i++) {
        for (int j = 0; j < 3; j++) {
            int x1 = mesh.tris[i].nodes[j].vals[0][0];
            int y1 = mesh.tris[i].nodes[j].vals[1][0];
            int x2 = mesh.tris[i].nodes[(j+1)%3].vals[0][0];
            int y2 = mesh.tris[i].nodes[(j+1)%3].vals[1][0];
            // mesh.tris[i].nodes[j].print();
            // set_point(x1, y1);
            // printf("x1: %d, y1: %d -> x2: %d, y2: %d\n", x1, y1, x2, y2);
            set_line(x1, y1, x2, y2);
        }
    }
}
