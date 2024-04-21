#include "GRAPHICS.h"

Screen::Screen(int width, int height, float fov_horizontal, float z_near, float z_far): ToScreenSpace(4, 4) {
    w = width;
    h = height;
    AR = (float) w/h;
    fov_x = fov_horizontal;
    fov_y = fov_x / AR; // not sure
    z_n = z_near;
    z_f = z_far;
    ToScreenSpace = Build_ToScreenSpace();

    for (int i = 0; i < h; i++) {
        std::vector<char> temp;
        for (int j = 0; j < w; j++) {
            temp.push_back('.');
        }
        grid.push_back(temp);
    }
}

Matrix Screen::Build_ToScreenSpace() {
    Matrix ProjM(4, 4);
    ProjM.fill(0);
    ProjM.vals[0][0] = atan(fov_x/2);
    ProjM.vals[1][1] = atan(fov_y/2);
    ProjM.vals[2][2] = -(z_f+z_n)/(z_f-z_n);
    ProjM.vals[2][3] = -2*(z_f*z_n)/(z_f-z_n);
    ProjM.vals[3][2] = -1;
    return ProjM;
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


// void Screen::draw_mesh_project(struct Mesh mesh) {
    
//     float w;
//     for (int i = 0; i < mesh.tris.size(); i++) {
//         for (int j = 0; j < 3; j++) {
//             Matrix old_v(4, 1);
//             old_v = mesh.tris[i].nodes[j].Vector3_toHG();

//             Matrix new_v = ToScreenSpace.multiply(old_v);
//             w = new_v.vals[3][0];
//             if (w != 0) {
//                 new_v.vals[0][0] /= w;
//                 new_v.vals[1][0] /= w;
//                 new_v.vals[2][0] /= w;
//             }

//         }
//     }

//     for (int i = 0; i < mesh.tris.size(); i++) {
//         for (int j = 0; j < 3; j++) {
//             int x1 = mesh.tris[i].nodes[j].vals[0][0];
//             int y1 = mesh.tris[i].nodes[j].vals[1][0];
//             int x2 = mesh.tris[i].nodes[(j+1)%3].vals[0][0];
//             int y2 = mesh.tris[i].nodes[(j+1)%3].vals[1][0];
//             set_line(x1, y1, x2, y2);
//         }
//     }
// }


void Screen::draw_mesh_project(struct Mesh mesh) {
    
    float w;
    for (int i = 0; i < mesh.tris.size(); i++) {
        for (int j = 0; j < 3; j++) {
            Matrix old_v(4, 1);
            old_v.vals[0][0] = mesh.tris[i].nodes[j].vals[0][0];
            old_v.vals[1][0] = mesh.tris[i].nodes[j].vals[1][0];
            old_v.vals[2][0] = mesh.tris[i].nodes[j].vals[2][0];
            old_v.vals[3][0] = 1;

            Matrix new_v = ToScreenSpace.multiply(old_v);
            w = new_v.vals[3][0];
            if (w != 0) {
                new_v.vals[0][0] /= w;
                new_v.vals[1][0] /= w;
                new_v.vals[2][0] /= w;
            }
        }
    }

    for (int i = 0; i < mesh.tris.size(); i++) {
        for (int j = 0; j < 3; j++) {
            int x1 = mesh.tris[i].nodes[j].vals[0][0];
            int y1 = mesh.tris[i].nodes[j].vals[1][0];
            int x2 = mesh.tris[i].nodes[(j+1)%3].vals[0][0];
            int y2 = mesh.tris[i].nodes[(j+1)%3].vals[1][0];
            set_line(x1, y1, x2, y2);
        }
    }
}



Camera::Camera() : cam_position(3, 1), ToCamSpace(4, 4) {   
        cam_position = Vector3(0, 0, 0);
        cam_pitch = 0;
        cam_yaw = 0;
        ToCamSpace = Build_ToCamSpace();

}

Matrix Camera::Build_ToCamSpace() {
    
    Matrix global_up = Vector3(0, 1, 0);
    Matrix cam_f = Vector3( cos(cam_pitch) * sin(cam_yaw),
                            sin(cam_pitch),
                            cos(cam_pitch) * cos(cam_yaw) );

    Matrix cam_r = global_up.cross_product3(cam_f);
    Matrix cam_u = cam_f.cross_product3(cam_r);

    cam_r.normalize();
    cam_u.normalize();

    float tx = cam_position.vals[0][0];
    float ty = cam_position.vals[1][0];
    float tz = cam_position.vals[2][0];

    Matrix v_inv(4, 4);
    v_inv.vals[0][0] = cam_r.vals[0][0];
    v_inv.vals[0][1] = cam_r.vals[1][0];
    v_inv.vals[0][2] = cam_r.vals[2][0];
    v_inv.vals[0][3] = -(cam_r.vals[0][0]*tx + cam_r.vals[1][0]*ty + cam_r.vals[2][0]*tz);
    v_inv.vals[1][0] = cam_u.vals[0][0];
    v_inv.vals[1][1] = cam_u.vals[1][0];
    v_inv.vals[1][2] = cam_u.vals[2][0];
    v_inv.vals[1][3] = -(cam_u.vals[0][0]*tx + cam_u.vals[1][0]*ty + cam_u.vals[2][0]*tz);
    v_inv.vals[2][0] = -cam_f.vals[0][0];
    v_inv.vals[2][1] = -cam_f.vals[1][0];
    v_inv.vals[2][2] = -cam_f.vals[2][0];
    v_inv.vals[2][3] = (cam_f.vals[0][0]*tx + cam_f.vals[1][0]*ty + cam_f.vals[2][0]*tz); // two negatives cancelled
    v_inv.vals[3][0] = 0;
    v_inv.vals[3][1] = 0;
    v_inv.vals[3][2] = 0;
    v_inv.vals[3][3] = 1;

    return v_inv;
}


void Camera::control_cam(float dx, float dy, float dz, float d_pitch, float d_yaw) {
    cam_position.vals[0][0] += dx;
    cam_position.vals[1][0] += dy;
    cam_position.vals[2][0] += dz;
    cam_pitch += d_pitch;
    cam_yaw += d_yaw;
    ToCamSpace = Build_ToCamSpace();
}

struct Mesh Camera::mesh_to_cam_space(struct Mesh mesh) {
    Matrix HG_node(4, 1);
    for (int i = 0; i < mesh.tris.size(); i++) {
        for (int j = 0; j < 3; j++) {
            HG_node = mesh.tris[i].nodes[j].Vector3_toHG();
            HG_node = ToCamSpace.multiply(HG_node);
            mesh.tris[i].nodes[j] = HG_node.HG_toVector3();
        }
    }
    return mesh;
}


struct Mesh mesh_to_world_space(struct Mesh mesh) {

    Matrix rotX = RotX(mesh.world_pitch);
    Matrix rotY = RotY(mesh.world_yaw);
    Matrix rotZ = RotZ(mesh.world_roll);
    Matrix trans = Trans(mesh.world_x, mesh.world_y, mesh.world_z);

    for (int i = 0; i < mesh.tris.size(); i++) {
        for (int j = 0; j < 3; j++) {
            Matrix dest(4, 1);
            dest = mesh.tris[i].nodes[j].Vector3_toHG();
            dest.scale(mesh.world_scale);
            dest = trans.multiply(rotZ.multiply(rotY.multiply(rotX.multiply(dest))));
            mesh.tris[i].nodes[j] = dest.HG_toVector3();
        }

    }

    return mesh;
}