#include "GRAPHICS.h"

struct Mesh build_cube_mesh(float x, float y, float z, float pitch, float yaw, float roll, float scale) {
    struct Mesh shape1 = {.world_x = x, .world_y = y, .world_z = z, .world_pitch = pitch, .world_yaw = yaw, .world_roll = roll, .world_scale = scale};

    struct Triangle t1_11 = {.nodes = {Vector3(-1, -1, 1), Vector3(-1, 1, 1), Vector3(1, -1, 1)}};
    struct Triangle t1_12 = {.nodes = {Vector3(1, 1, 1), Vector3(-1, 1, 1), Vector3(1, -1, 1)}};
    struct Triangle t1_21 = {.nodes = {Vector3(-1, -1, -1), Vector3(1, -1, -1), Vector3(-1, 1, -1)}};
    struct Triangle t1_22 = {.nodes = {Vector3(1, -1, -1), Vector3(1, 1, -1), Vector3(-1, 1, -1)}};
    struct Triangle t1_31 = {.nodes = {Vector3(-1, 1, -1), Vector3(-1, 1, 1), Vector3(1, 1, -1)}};
    struct Triangle t1_32 = {.nodes = {Vector3(1, 1, 1), Vector3(1, 1, -1), Vector3(-1, 1, 1)}};
    struct Triangle t1_41 = {.nodes = {Vector3(-1, -1, -1), Vector3(1, -1, -1), Vector3(-1, -1, 1)}};
    struct Triangle t1_42 = {.nodes = {Vector3(1, -1, 1), Vector3(1, -1, -1), Vector3(-1, -1, 1)}};
    struct Triangle t1_51 = {.nodes = {Vector3(-1, -1, -1), Vector3(-1, -1, 1), Vector3(-1, 1, -1)}};
    struct Triangle t1_52 = {.nodes = {Vector3(-1, 1, 1), Vector3(-1, 1, -1), Vector3(-1, -1, 1)}};
    struct Triangle t1_61 = {.nodes = {Vector3(1, -1, -1), Vector3(1, 1, -1), Vector3(1, -1, 1)}};
    struct Triangle t1_62 = {.nodes = {Vector3(1, 1, 1), Vector3(1, 1, -1), Vector3(1, -1, 1)}};

    shape1.tris.push_back(t1_11);
    shape1.tris.push_back(t1_12);
    shape1.tris.push_back(t1_21);
    shape1.tris.push_back(t1_22);
    shape1.tris.push_back(t1_31);
    shape1.tris.push_back(t1_32);
    shape1.tris.push_back(t1_41);
    shape1.tris.push_back(t1_42);
    shape1.tris.push_back(t1_51);
    shape1.tris.push_back(t1_52);
    shape1.tris.push_back(t1_61);
    shape1.tris.push_back(t1_62);

    return shape1;
}

struct Mesh build_dummy_mesh(struct Mesh original_mesh) {
    return original_mesh;
}

void transform_mesh(float dx, float dy, float dz, float dpitch, float dyaw, float droll, float dscale, struct Mesh& mesh) {
    mesh.world_x += dx;
    mesh.world_y += dy;
    mesh.world_z += dz;
    mesh.world_pitch += dpitch;
    mesh.world_yaw += dyaw;
    mesh.world_roll += droll;
    mesh.world_scale += dscale;
}

void mesh_to_world_space(struct Mesh& mesh0, struct Mesh& mesh1) {
    Matrix rotX = RotX(mesh0.world_pitch);
    Matrix rotY = RotY(mesh0.world_yaw);
    Matrix rotZ = RotZ(mesh0.world_roll);
    Matrix trans = Trans(mesh0.world_x, mesh0.world_y, mesh0.world_z);

    Matrix temp0(4, 4);
    Matrix temp1(4, 4);
    Matrix temp2(4, 4);
    Matrix v_temp0(4, 1);
    Matrix v_temp1(4, 1);

    trans.multiply(rotZ, temp0);
    temp0.multiply(rotY, temp1);
    temp1.multiply(rotX, temp2);

    for (int i = 0; i < mesh0.tris.size(); i++) {
        for (int j = 0; j < 3; j++) {
            mesh0.tris[i].nodes[j].Vector3_toHG(v_temp0);
            v_temp0.scale(mesh0.world_scale);
            temp2.multiply(v_temp0, v_temp1);
            v_temp1.vals[3][0] = 1;
            v_temp1.HG_toVector3(mesh1.tris[i].nodes[j]);

            // printf("start\n");
            // temp2.print();
            // v_temp0.print();
            // v_temp1.print();
            // mesh1.tris[i].nodes[j].print();
            
            v_temp0.fill(0);
            v_temp1.fill(0);

        }

    }
}


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


float Screen::lerp(float a, float b, float t) {
    return a + t * (b - a);
}


void Screen::set_point_Terminal(float x, float y, float z) {

    if (x > -1 && x <= 1 && y > -1 && y <= 1 && z > 0 && z <= 1) {
        int grid_x_int = static_cast<int>(std::round((x + 1) * w / 2));
        int grid_y_int = static_cast<int>(std::round((1 - y) * h / 2));

        if (grid_x_int < w && grid_x_int >= 0 && grid_y_int < h && grid_y_int >= 0) {

            grid[grid_y_int][grid_x_int] = 'X';
        }
    }
}


void Screen::set_line_Terminal(float x1, float y1, float z1, float x2, float y2, float z2) {
    float grid_x1 = x1;
    float grid_y1 = y1;
    float grid_x2 = x2;
    float grid_y2 = y2;

    if (std::abs(grid_x1 - grid_x2) < std::numeric_limits<float>::epsilon()) {
        float y = std::min(grid_y1, grid_y2);
        while (y <= std::max(grid_y1, grid_y2)) {
            set_point_Terminal(grid_x1, y, lerp(z1, z2, (y - grid_y1) / (grid_y2 - grid_y1)));
            y += 0.001;
        }
        return;
    }

    float slope_y = (grid_y2 - grid_y1) / (grid_x2 - grid_x1);
    float slope_z = (z2 - z1) / (grid_x2 - grid_x1);
    float bias_y = grid_y1 - slope_y * grid_x1;
    float bias_z = z1 - slope_z * grid_x1;

    if (grid_x2 > grid_x1) {
        float x = grid_x1;
        while (x <= grid_x2) {
            float y = slope_y * x + bias_y;
            float z = slope_z * x + bias_z;
            set_point_Terminal(x, y, z);
            x += 0.001;
        }
    } else {
        float x = grid_x2;
        while (x <= grid_x1) {
            float y = slope_y * x + bias_y;
            float z = slope_z * x + bias_z;
            set_point_Terminal(x, y, z);
            x += 0.001;
        }
    }
}


void Screen::draw_mesh_Terminal(struct Mesh& mesh) {
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

void Screen::set_line_SFML(float x1, float y1, float z1, float x2, float y2, float z2, sf::RenderWindow& window) {
    double grid_x1 = x1;
    double grid_y1 = y1;
    double grid_x2 = x2;
    double grid_y2 = y2;

    if (std::abs(grid_x1 - grid_x2) < std::numeric_limits<double>::epsilon()) {
        double y = std::min(grid_y1, grid_y2);
        while (y <= std::max(grid_y1, grid_y2)) {
            set_point_SFML(grid_x1, y, lerp(z1, z2, (y - grid_y1) / (grid_y2 - grid_y1)), window);
            y += 0.01;
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
            x += 0.01;
        }
    } else {
        double x = grid_x2;
        while (x <= grid_x1) {
            double y = slope_y * x + bias_y;
            double z = slope_z * x + bias_z;
            set_point_SFML(x, y, z, window);
            x += 0.01;
        }
    }
}

void Screen::draw_mesh_SFML(struct Mesh& mesh, sf::RenderWindow& window) {

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


void Screen::mesh_to_view_volume(struct Mesh& mesh0, struct Mesh& mesh1) {
    Matrix v_temp1(4, 1);
    Matrix v_temp2(4, 1);

    for (int i = 0; i < mesh0.tris.size(); i++) {
        for (int j = 0; j < 3; j++) {
            mesh0.tris[i].nodes[j].Vector3_toHG(v_temp1);
            ToScreenSpace.multiply(v_temp1, v_temp2);
            v_temp2.HG_toVector3(mesh1.tris[i].nodes[j]);
            
            v_temp1.fill(0);
            v_temp2.fill(0);
        }
    }
}


Camera::Camera() : cam_position(3, 1), ToCamSpace(4, 4) {   
        cam_position = Vector3(0, 0, 0);
        cam_pitch = 0;
        cam_yaw = 0;
        Build_ToCamSpace(ToCamSpace);

}

void Camera::Build_ToCamSpace(Matrix& m) {
    
    Matrix global_up = Vector3(0, 1, 0);
    Matrix cam_f = Vector3( cos(cam_pitch) * sin(cam_yaw),
                            sin(cam_pitch),
                            cos(cam_pitch) * cos(cam_yaw) );

    Matrix cam_r(3, 1);
    global_up.cross_product3(cam_f, cam_r);
    cam_r.normalize();

    Matrix cam_u(3, 1);
    cam_f.cross_product3(cam_r, cam_u);
    cam_u.normalize();


    float tx = cam_position.vals[0][0];
    float ty = cam_position.vals[1][0];
    float tz = cam_position.vals[2][0];

    m.vals[0][0] = cam_r.vals[0][0];
    m.vals[0][1] = cam_r.vals[1][0];
    m.vals[0][2] = cam_r.vals[2][0];
    m.vals[0][3] = -(cam_r.vals[0][0]*tx + cam_r.vals[1][0]*ty + cam_r.vals[2][0]*tz);
    m.vals[1][0] = cam_u.vals[0][0];
    m.vals[1][1] = cam_u.vals[1][0];
    m.vals[1][2] = cam_u.vals[2][0];
    m.vals[1][3] = -(cam_u.vals[0][0]*tx + cam_u.vals[1][0]*ty + cam_u.vals[2][0]*tz);
    m.vals[2][0] = -cam_f.vals[0][0];
    m.vals[2][1] = -cam_f.vals[1][0];
    m.vals[2][2] = -cam_f.vals[2][0];
    m.vals[2][3] = (cam_f.vals[0][0]*tx + cam_f.vals[1][0]*ty + cam_f.vals[2][0]*tz); // two negatives cancelled
    m.vals[3][0] = 0;
    m.vals[3][1] = 0;
    m.vals[3][2] = 0;
    m.vals[3][3] = 1;
}


void Camera::control_cam(float dx, float dy, float dz, float d_pitch, float d_yaw) {
    cam_position.vals[0][0] += dx;
    cam_position.vals[1][0] += dy;
    cam_position.vals[2][0] += dz;
    cam_pitch += d_pitch;
    cam_yaw += d_yaw;
    Build_ToCamSpace(ToCamSpace);
}

void Camera::mesh_to_cam_space(struct Mesh& mesh0, struct Mesh& mesh1) {
    Matrix hg_temp0(4, 1);
    Matrix hg_temp1(4, 1);
    for (int i = 0; i < mesh0.tris.size(); i++) {
        for (int j = 0; j < 3; j++) {

            // hg_temp0.print();
            mesh0.tris[i].nodes[j].Vector3_toHG(hg_temp0);
            // hg_temp0.print();

            ToCamSpace.multiply(hg_temp0, hg_temp1);
            // ToCamSpace.print();
            // hg_temp1.print();

            hg_temp1.vals[3][0] = 1;
            hg_temp1.HG_toVector3(mesh1.tris[i].nodes[j]);

            hg_temp0.fill(0);
            hg_temp1.fill(0);
        }
    }
}