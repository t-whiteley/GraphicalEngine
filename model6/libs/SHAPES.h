#ifndef SHAPES_H
#define SHAPES_H

#include <iostream>
#include <vector>
#include <cmath>
#include "LINALG.h"
#include "GRAPHICS.h"

struct Mesh build_cube_mesh(float x, float y, float z, float pitch, float yaw, float roll, float scale);
struct Mesh build_octahedron_mesh(float x, float y, float z, float pitch, float yaw, float roll, float scale);
struct Mesh build_dodecahedron_mesh(float x, float y, float z, float pitch, float yaw, float roll, float scale);


#endif