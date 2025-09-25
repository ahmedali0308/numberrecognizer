#pragma once

class Matrix {
    public:
        Matrix(unsigned n, unsigned m);
        ~Matrix();                                          // Destruct
        Matrix(const Matrix& m);                            // Copy
        Matrix& operator=(const Matrix& m);                 // Assign
        float operator()(unsigned n, unsigned m) const;     // Subscript
        float& operator()(unsigned n, unsigned m);          // Subscript

        void mult(float l);
        void add(float a);

        void T();

        void rand();
        unsigned* shape();

        void printshape();
        void printdata();
    private:
        unsigned rows, cols;
        float* data;
};