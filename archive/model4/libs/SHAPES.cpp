#include "SHAPES.h"

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

struct Mesh build_octahedron_mesh(float x, float y, float z, float pitch, float yaw, float roll, float scale) {
    struct Mesh shape1 = {.world_x = x, .world_y = y, .world_z = z, .world_pitch = pitch, .world_yaw = yaw, .world_roll = roll, .world_scale = scale};

    // Vertices of an octahedron
    Matrix vertices[] = {
        Vector3(0, 0, 1),
        Vector3(1, 0, 0),
        Vector3(0, 1, 0),
        Vector3(-1, 0, 0),
        Vector3(0, -1, 0),
        Vector3(0, 0, -1)
    };
    
    // Faces of an octahedron
    struct Triangle t1_1 = {.nodes = {vertices[0], vertices[1], vertices[2]}};
    struct Triangle t1_2 = {.nodes = {vertices[0], vertices[2], vertices[3]}};
    struct Triangle t1_3 = {.nodes = {vertices[0], vertices[3], vertices[4]}};
    struct Triangle t1_4 = {.nodes = {vertices[0], vertices[4], vertices[1]}};
    struct Triangle t1_5 = {.nodes = {vertices[5], vertices[1], vertices[2]}};
    struct Triangle t1_6 = {.nodes = {vertices[5], vertices[2], vertices[3]}};
    struct Triangle t1_7 = {.nodes = {vertices[5], vertices[3], vertices[4]}};
    struct Triangle t1_8 = {.nodes = {vertices[5], vertices[4], vertices[1]}};

    shape1.tris.push_back(t1_1);
    shape1.tris.push_back(t1_2);
    shape1.tris.push_back(t1_3);
    shape1.tris.push_back(t1_4);
    shape1.tris.push_back(t1_5);
    shape1.tris.push_back(t1_6);
    shape1.tris.push_back(t1_7);
    shape1.tris.push_back(t1_8);

    return shape1;
}



struct Mesh build_dodecahedron_mesh(float x, float y, float z, float pitch, float yaw, float roll, float scale) {
    struct Mesh shape1 = {.world_x = x, .world_y = y, .world_z = z, .world_pitch = pitch, .world_yaw = yaw, .world_roll = roll, .world_scale = scale};

    // Vertices of a dodecahedron
    Matrix vertices[] = {
        Vector3(0, 1, 1.618),
        Vector3(0, -1, 1.618),
        Vector3(1, 1.618, 0),
        Vector3(1, -1.618, 0),
        Vector3(-1, 1.618, 0),
        Vector3(-1, -1.618, 0),
        Vector3(1.618, 0, 1),
        Vector3(-1.618, 0, 1),
        Vector3(1.618, 0, -1),
        Vector3(-1.618, 0, -1),
        Vector3(1, 1, -1.618),
        Vector3(1, -1, -1.618),
        Vector3(-1, 1, -1.618),
        Vector3(-1, -1, -1.618),
        Vector3(0, 1, -1.618),
        Vector3(0, -1, -1.618),
        Vector3(1.618, 1, 0),
        Vector3(1.618, -1, 0),
        Vector3(-1.618, 1, 0),
        Vector3(-1.618, -1, 0) };
    
    // Faces of a dodecahedron
    struct Triangle t1_11 = {.nodes = {vertices[0], vertices[2], vertices[6]}};
    struct Triangle t1_12 = {.nodes = {vertices[0], vertices[6], vertices[8]}};
    struct Triangle t1_13 = {.nodes = {vertices[0], vertices[8], vertices[4]}};
    struct Triangle t1_14 = {.nodes = {vertices[0], vertices[4], vertices[12]}};
    struct Triangle t1_15 = {.nodes = {vertices[0], vertices[12], vertices[2]}};
    struct Triangle t1_21 = {.nodes = {vertices[1], vertices[3], vertices[7]}};
    struct Triangle t1_22 = {.nodes = {vertices[1], vertices[7], vertices[9]}};
    struct Triangle t1_23 = {.nodes = {vertices[1], vertices[9], vertices[5]}};
    struct Triangle t1_24 = {.nodes = {vertices[1], vertices[5], vertices[13]}};
    struct Triangle t1_25 = {.nodes = {vertices[1], vertices[13], vertices[3]}};
    struct Triangle t1_31 = {.nodes = {vertices[2], vertices[6], vertices[10]}};
    struct Triangle t1_32 = {.nodes = {vertices[2], vertices[10], vertices[11]}};
    struct Triangle t1_33 = {.nodes = {vertices[2], vertices[11], vertices[16]}};
    struct Triangle t1_34 = {.nodes = {vertices[2], vertices[16], vertices[6]}};
    struct Triangle t1_41 = {.nodes = {vertices[3], vertices[7], vertices[17]}};
    struct Triangle t1_42 = {.nodes = {vertices[3], vertices[17], vertices[18]}};
    struct Triangle t1_43 = {.nodes = {vertices[3], vertices[18], vertices[8]}};
    struct Triangle t1_44 = {.nodes = {vertices[3], vertices[8], vertices[11]}};
    struct Triangle t1_45 = {.nodes = {vertices[3], vertices[11], vertices[7]}};
    struct Triangle t1_51 = {.nodes = {vertices[4], vertices[8], vertices[18]}};
    struct Triangle t1_52 = {.nodes = {vertices[4], vertices[18], vertices[19]}};
    struct Triangle t1_53 = {.nodes = {vertices[4], vertices[19], vertices[14]}};
    struct Triangle t1_54 = {.nodes = {vertices[4], vertices[14], vertices[12]}};
    struct Triangle t1_55 = {.nodes = {vertices[4], vertices[12], vertices[8]}};
    struct Triangle t1_61 = {.nodes = {vertices[5], vertices[9], vertices[15]}};
    struct Triangle t1_62 = {.nodes = {vertices[5], vertices[15], vertices[16]}};
    struct Triangle t1_63 = {.nodes = {vertices[5], vertices[16], vertices[10]}};
    struct Triangle t1_64 = {.nodes = {vertices[5], vertices[10], vertices[13]}};
    struct Triangle t1_65 = {.nodes = {vertices[5], vertices[13], vertices[9]}};
    struct Triangle t1_71 = {.nodes = {vertices[6], vertices[16], vertices[15]}};
    struct Triangle t1_72 = {.nodes = {vertices[6], vertices[15], vertices[17]}};
    struct Triangle t1_73 = {.nodes = {vertices[6], vertices[17], vertices[7]}};
    struct Triangle t1_74 = {.nodes = {vertices[6], vertices[7], vertices[10]}};
    struct Triangle t1_81 = {.nodes = {vertices[9], vertices[13], vertices[10]}};
    struct Triangle t1_82 = {.nodes = {vertices[9], vertices[10], vertices[17]}};
    struct Triangle t1_83 = {.nodes = {vertices[9], vertices[17], vertices[15]}};
    struct Triangle t1_84 = {.nodes = {vertices[9], vertices[15], vertices[5]}};
    struct Triangle t1_91 = {.nodes = {vertices[12], vertices[14], vertices[19]}};
    struct Triangle t1_92 = {.nodes = {vertices[12], vertices[19], vertices[18]}};
    struct Triangle t1_93 = {.nodes = {vertices[12], vertices[18], vertices[17]}};
    struct Triangle t1_94 = {.nodes = {vertices[12], vertices[17], vertices[15]}};
    struct Triangle t1_95 = {.nodes = {vertices[12], vertices[15], vertices[14]}};
    struct Triangle t1_101 = {.nodes = {vertices[11], vertices[10], vertices[13]}};
    struct Triangle t1_102 = {.nodes = {vertices[11], vertices[13], vertices[5]}};
    struct Triangle t1_103 = {.nodes = {vertices[11], vertices[5], vertices[16]}};
    struct Triangle t1_104 = {.nodes = {vertices[11], vertices[16], vertices[8]}};
    struct Triangle t1_105 = {.nodes = {vertices[11], vertices[8], vertices[18]}};
    struct Triangle t1_106 = {.nodes = {vertices[14], vertices[15], vertices[16]}};
    struct Triangle t1_107 = {.nodes = {vertices[14], vertices[16], vertices[5]}};
    struct Triangle t1_108 = {.nodes = {vertices[14], vertices[5], vertices[9]}};
    struct Triangle t1_109 = {.nodes = {vertices[14], vertices[9], vertices[13]}};
    struct Triangle t1_110 = {.nodes = {vertices[14], vertices[13], vertices[10]}};
    struct Triangle t1_111 = {.nodes = {vertices[14], vertices[10], vertices[15]}};
    struct Triangle t1_112 = {.nodes = {vertices[17], vertices[18], vertices[19]}};
    struct Triangle t1_113 = {.nodes = {vertices[17], vertices[19], vertices[4]}};
    struct Triangle t1_114 = {.nodes = {vertices[17], vertices[4], vertices[8]}};
    struct Triangle t1_115 = {.nodes = {vertices[17], vertices[8], vertices[18]}};

    shape1.tris.push_back(t1_11);
    shape1.tris.push_back(t1_12);
    shape1.tris.push_back(t1_13);
    shape1.tris.push_back(t1_14);
    shape1.tris.push_back(t1_15);
    shape1.tris.push_back(t1_21);
    shape1.tris.push_back(t1_22);
    shape1.tris.push_back(t1_23);
    shape1.tris.push_back(t1_24);
    shape1.tris.push_back(t1_25);
    shape1.tris.push_back(t1_31);
    shape1.tris.push_back(t1_32);
    shape1.tris.push_back(t1_33);
    shape1.tris.push_back(t1_34);
    shape1.tris.push_back(t1_41);
    shape1.tris.push_back(t1_42);
    shape1.tris.push_back(t1_43);
    shape1.tris.push_back(t1_44);
    shape1.tris.push_back(t1_45);
    shape1.tris.push_back(t1_51);
    shape1.tris.push_back(t1_52);
    shape1.tris.push_back(t1_53);
    shape1.tris.push_back(t1_54);
    shape1.tris.push_back(t1_55);
    shape1.tris.push_back(t1_61);
    shape1.tris.push_back(t1_62);
    shape1.tris.push_back(t1_63);
    shape1.tris.push_back(t1_64);
    shape1.tris.push_back(t1_65);
    shape1.tris.push_back(t1_71);
    shape1.tris.push_back(t1_72);
    shape1.tris.push_back(t1_73);
    shape1.tris.push_back(t1_74);
    shape1.tris.push_back(t1_81);
    shape1.tris.push_back(t1_82);
    shape1.tris.push_back(t1_83);
    shape1.tris.push_back(t1_84);
    shape1.tris.push_back(t1_91);
    shape1.tris.push_back(t1_92);
    shape1.tris.push_back(t1_93);
    shape1.tris.push_back(t1_94);
    shape1.tris.push_back(t1_95);
    shape1.tris.push_back(t1_101);
    shape1.tris.push_back(t1_102);
    shape1.tris.push_back(t1_103);
    shape1.tris.push_back(t1_104);
    shape1.tris.push_back(t1_105);
    shape1.tris.push_back(t1_106);
    shape1.tris.push_back(t1_107);
    shape1.tris.push_back(t1_108);
    shape1.tris.push_back(t1_109);
    shape1.tris.push_back(t1_110);
    shape1.tris.push_back(t1_111);
    shape1.tris.push_back(t1_112);
    shape1.tris.push_back(t1_113);
    shape1.tris.push_back(t1_114);
    shape1.tris.push_back(t1_115);

    return shape1;
}
