#pragma once
#include <cstdlib>
#include <ctime>
#include <tuple>
#include <iostream>
#include <cmath>

class Matrix {
    public:
        Matrix(unsigned n, unsigned m);
        ~Matrix();                                          // Destruct
        Matrix(const Matrix& m);                            // Copy
        Matrix operator+(const Matrix& other) const;        // Add
        Matrix operator-(const Matrix& other) const;        // Subtract
        Matrix& operator-=(const Matrix& other);             // Another Subtract
        Matrix operator*(const Matrix& other) const;        // Mult
        Matrix operator*(float scalar) const;               // Scalar Mult
        Matrix& operator=(const Matrix& m);                 // Assign
        float operator()(unsigned n, unsigned m) const;     // Subscript
        float& operator()(unsigned n, unsigned m);          // Subscript

        void set(int row, int col, float value);
        float sum_squared() const;
        int argmax() const;

        void T();
        Matrix transpose() const;

        void randomize(float min, float max);
        unsigned* shape();

        void printshape();
        void printdata();

        void sigmoid();
        void relu();

        Matrix sigmoid_derivative() const;
        Matrix relu_derivative() const;

        Matrix hadamard(const Matrix& other) const;
    private:
        unsigned rows, cols;
        float* data;
};