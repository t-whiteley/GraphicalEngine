#include "LINALG.h"
#include <assert.h>


Matrix::Matrix(int h, int w) {
    y = h;
    x = w;
    for (int i = 0; i < y; i++) {
        std::vector<double> temp;
        for (int j = 0; j < x; j++) {
            temp.push_back(0);
        }
        vals.push_back(temp);
    }
}


void Matrix::print() {
    std::cout << "[\n";
    for (int i = 0; i < y; i++) {
        for (int j = 0; j < x; j++) {
            std::cout << vals[i][j] << "\t";
        }
        std::cout << "\n";
    }
    std::cout << "]\n\n";
}


Matrix Matrix::multiply(Matrix n) {
    assert(x == n.y);

    Matrix f(y, n.x);
    for (int i = 0; i < f.y; i++) {
        for (int j = 0; j < f.x; j++) {

            int num = 0;
            for (int k = 0; k < x; k++) {
                num += vals[i][k] * n.vals[k][j];
            }
            f.vals[i][j] = num;
        }
    }
    return f;
}

void Matrix::fill(float num) {
    for (int i = 0; i < y; i++) {
        for (int j = 0; j < x; j++) {
            vals[i][j] = num;
        }
    }
}


Matrix Vector3(int x, int y, int z) {
    Matrix m(3, 1);
    m.vals[0][0] = x;
    m.vals[1][0] = y;
    m.vals[2][0] = z;
    return m;
}

// Matrix VectorHG(int x, int y, int z) {
//     Matrix m(4, 1);
//     m.vals[0][0] = x;
//     m.vals[1][0] = y;
//     m.vals[2][0] = z;
//     m.vals[3][0] = 1;
//     return m;
// }



// int main() {
//     Matrix m1(4, 2);
//     for (int i = 0; i < 4; i++) {
//         for (int j = 0; j < 2; j++) {
//             m1.m[i][j] = i + j;
//         }
//     }

//     Matrix m2(2, 4);
//         for (int i = 0; i < 2; i++) {
//         for (int j = 0; j < 4; j++) {
//             m2.m[i][j] = i + j;
//         }
//     }

//     m1.print();
//     m2.print();
//     Matrix m3 = m1.multiply(m2);
//     m3.print();
// }