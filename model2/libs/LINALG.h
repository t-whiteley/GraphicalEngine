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
        void normalize();
        Matrix scale(float n);
};

Matrix Vector3(float x, float y, float z);
// Matrix VectorHG(int x, int y, int z);

#endif