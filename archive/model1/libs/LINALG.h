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
};

Matrix Vector3(int x, int y, int z);
// Matrix VectorHG(int x, int y, int z);

#endif