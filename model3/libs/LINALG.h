#ifndef LINALG_H
#define LINALG_H

#include <iostream>
#include <vector>

class Matrix {
    private:
        int y;
        int x;
    public:
        std::vector<std::vector<double> > vals;

        Matrix(int h, int w);
        void print();
        Matrix multiply(Matrix n);
        void fill(float num);
        Matrix cross_product3(Matrix vector1);
        Matrix transpose();
        Matrix Vector3_toHG();
        Matrix HG_toVector3();
        void normalize();
        Matrix scale(float n);
};

Matrix Vector3(float x, float y, float z);
Matrix RotX(float d_theta);
Matrix RotY(float d_theta);
Matrix RotZ(float d_theta);
Matrix Trans(float dx, float dy, float dz);

#endif