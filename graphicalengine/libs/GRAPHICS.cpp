#include "GRAPHICS.h"

Screen::Screen(int width, int height, float fov_vertical, float z_near, float z_far): ToScreenSpace(4, 4) {
    w = width;
    h = height;
    AR = (float) w/h;
    fov_y = fov_vertical;
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
    ProjM.vals[0][0] = 1 / AR / tan(fov_y/2);
    ProjM.vals[1][1] = 1 / tan(fov_y/2);
    ProjM.vals[2][2] = z_f / (z_f - z_n);
    ProjM.vals[2][3] = -(z_f*z_n)/(z_f-z_n);
    ProjM.vals[3][2] = 1;
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

// x, y, z MUST BE ALRADY IN VIEW VOLUME, ONLY SOME VALIDATION IS DONE HERE
#ifdef USE_SFML
void Screen::set_point_SFML(double x, double y, double z, sf::RenderWindow& window) {

    if (x > -1 && x <= 1 && y > -1 && y <= 1 && z > 0 && z <= 1) {
        int grid_x_int = static_cast<int>(std::round((x + 1) * w / 2));
        int grid_y_int = static_cast<int>(std::round((1 - y) * h / 2));

        if (grid_x_int < w && grid_x_int >= 0 && grid_y_int < h && grid_y_int >= 0) {

            sf::CircleShape point(1);
            point.setFillColor(sf::Color::Red);
            point.setPosition(grid_x_int, grid_y_int);
            window.draw(point);

        }
    }
}
#endif

void Screen::set_point_Terminal(double x, double y, double z) {

    if (x > -1 && x <= 1 && y > -1 && y <= 1 && z > 0 && z <= 1) {
        int grid_x_int = static_cast<int>(std::round((x + 1) * w / 2));
        int grid_y_int = static_cast<int>(std::round((1 - y) * h / 2));

        if (grid_x_int < w && grid_x_int >= 0 && grid_y_int < h && grid_y_int >= 0) {

            grid[grid_y_int][grid_x_int] = 'X';
        }
    }
}


// JUST 3D INTERPOLATION, NO SCALING
#ifdef USE_SFML
void Screen::set_line_SFML(float x1, float y1, float z1, float x2, float y2, float z2, sf::RenderWindow& window) {
    double grid_x1 = x1;
    double grid_y1 = y1;
    double grid_x2 = x2;
    double grid_y2 = y2;

    if (std::abs(grid_x1 - grid_x2) < std::numeric_limits<double>::epsilon()) {
        double y = std::min(grid_y1, grid_y2);
        while (y <= std::max(grid_y1, grid_y2)) {
            set_point_SFML(grid_x1, y, lerp(z1, z2, (y - grid_y1) / (grid_y2 - grid_y1)), window);
            y += 0.005;
        }
        return;
    }

    double slope_y = (grid_y2 - grid_y1) / (grid_x2 - grid_x1);
    double slope_z = (z2 - z1) / (grid_x2 - grid_x1);
    double bias_y = grid_y1 - slope_y * grid_x1;
    double bias_z = z1 - slope_z * grid_x1;

    if (grid_x2 > grid_x1) {
        double x = grid_x1;
        while (x <= grid_x2) {
            double y = slope_y * x + bias_y;
            double z = slope_z * x + bias_z;
            set_point_SFML(x, y, z, window);
            x += 0.005;
        }
    } else {
        double x = grid_x2;
        while (x <= grid_x1) {
            double y = slope_y * x + bias_y;
            double z = slope_z * x + bias_z;
            set_point_SFML(x, y, z, window);
            x += 0.005;
        }
    }
}
#endif

void Screen::set_line_Terminal(float x1, float y1, float z1, float x2, float y2, float z2) {
    double grid_x1 = x1;
    double grid_y1 = y1;
    double grid_x2 = x2;
    double grid_y2 = y2;

    if (std::abs(grid_x1 - grid_x2) < std::numeric_limits<double>::epsilon()) {
        double y = std::min(grid_y1, grid_y2);
        while (y <= std::max(grid_y1, grid_y2)) {
            set_point_Terminal(grid_x1, y, lerp(z1, z2, (y - grid_y1) / (grid_y2 - grid_y1)));
            y += 0.001;
        }
        return;
    }

    double slope_y = (grid_y2 - grid_y1) / (grid_x2 - grid_x1);
    double slope_z = (z2 - z1) / (grid_x2 - grid_x1);
    double bias_y = grid_y1 - slope_y * grid_x1;
    double bias_z = z1 - slope_z * grid_x1;

    if (grid_x2 > grid_x1) {
        double x = grid_x1;
        while (x <= grid_x2) {
            double y = slope_y * x + bias_y;
            double z = slope_z * x + bias_z;
            set_point_Terminal(x, y, z);
            x += 0.001;
        }
    } else {
        double x = grid_x2;
        while (x <= grid_x1) {
            double y = slope_y * x + bias_y;
            double z = slope_z * x + bias_z;
            set_point_Terminal(x, y, z);
            x += 0.001;
        }
    }
}

double Screen::lerp(double a, double b, double t) {
    return a + t * (b - a);
}


struct Mesh Screen::mesh_to_view_volume(struct Mesh mesh) {
    float w;
    for (int i = 0; i < mesh.tris.size(); i++) {
        for (int j = 0; j < 3; j++) {

            Matrix old_v(4, 1);
            old_v = mesh.tris[i].nodes[j].Vector3_toHG();

            Matrix new_v = ToScreenSpace.multiply(old_v);

            w = new_v.vals[3][0];
            if (w != 0) {
                new_v.scale(1/w);
            }


            mesh.tris[i].nodes[j] = new_v.HG_toVector3();
        }
    }
    return mesh;
}

#ifdef USE_SFML
void Screen::draw_mesh_SFML(struct Mesh mesh, sf::RenderWindow& window) {

    for (int i = 0; i < mesh.tris.size(); i++) {
        for (int j = 0; j < 3; j++) {
            float x1 = mesh.tris[i].nodes[j].vals[0][0];
            float y1 = mesh.tris[i].nodes[j].vals[1][0];
            float z1 = mesh.tris[i].nodes[j].vals[2][0];
            float x2 = mesh.tris[i].nodes[(j+1)%3].vals[0][0];
            float y2 = mesh.tris[i].nodes[(j+1)%3].vals[1][0];
            float z2 = mesh.tris[i].nodes[(j+1)%3].vals[2][0];

            set_line_SFML(x1, y1, z1, x2, y2, z2, window);
        }
    }
}
#endif

void Screen::draw_mesh_Terminal(struct Mesh mesh) {

    for (int i = 0; i < mesh.tris.size(); i++) {
        for (int j = 0; j < 3; j++) {
            float x1 = mesh.tris[i].nodes[j].vals[0][0];
            float y1 = mesh.tris[i].nodes[j].vals[1][0];
            float z1 = mesh.tris[i].nodes[j].vals[2][0];
            float x2 = mesh.tris[i].nodes[(j+1)%3].vals[0][0];
            float y2 = mesh.tris[i].nodes[(j+1)%3].vals[1][0];
            float z2 = mesh.tris[i].nodes[(j+1)%3].vals[2][0];

            set_line_Terminal(x1, y1, z1, x2, y2, z2);
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