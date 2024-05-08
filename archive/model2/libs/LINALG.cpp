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


Matrix Matrix::cross_product3(Matrix vector1) {
    assert(y == 3 && x == 1 && vector1.y == 3 && vector1.x == 1);

    Matrix result(3, 1);
    result.vals[0][0] = vals[1][0] * vector1.vals[2][0] - vals[2][0] * vector1.vals[1][0];
    result.vals[1][0] = vals[2][0] * vector1.vals[0][0] - vals[0][0] * vector1.vals[2][0];
    result.vals[2][0] = vals[0][0] * vector1.vals[1][0] - vals[1][0] * vector1.vals[0][0];
    return result;
}

Matrix Matrix::transpose() {
    Matrix result(x, y);
    for (int i = 0; i < y; i++) {
        for (int j = 0; j < x; j++) {
            result.vals[j][i] = vals[i][j];
        }
    }
    return result;
}


Matrix Matrix::Vector3_toHG() {
    assert(y==3 && x==1);
    Matrix homog(4, 1);
    homog.vals[0][0] = vals[0][0];
    homog.vals[1][0] = vals[1][0];
    homog.vals[2][0] = vals[2][0];
    homog.vals[3][0] = 1;
    return homog;
}

void Matrix::normalize() {
    double magnitude = 0.0;
    for (int i = 0; i < y; ++i) {
        for (int j = 0; j < x; ++j) {
            magnitude += vals[i][j] * vals[i][j];
        }
    }
    magnitude = std::sqrt(magnitude);
    if (magnitude != 0) {
        for (int i = 0; i < y; ++i) {
            for (int j = 0; j < x; ++j) {
                vals[i][j] /= magnitude;
            }
        }
    }

}


Matrix Matrix::scale(float n) {
    Matrix m(y, x);
    for (int i = 0; i < y; ++i) {
        for (int j = 0; j < x; ++j) {
            m.vals[i][j] = vals[i][j] *= n;
        }
    }
    return m;
}



Matrix Vector3(float x, float y, float z) {
    Matrix m(3, 1);
    m.vals[0][0] = x;
    m.vals[1][0] = y;
    m.vals[2][0] = z;
    return m;
}