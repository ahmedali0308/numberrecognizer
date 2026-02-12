#include <../include/matrix.h>

Matrix::Matrix(unsigned n, unsigned m) : rows(n), cols(m) {
    srand(time(NULL));
    if (m == 0 || m == 0)
        throw ("Matrix constructor has 0 size");
    data = new float[n*m];
    for (int i=0; i<rows*cols;i++)
      data[i] = 0.f;
}

Matrix::Matrix(const Matrix& m){
  rows = m.rows;
  cols = m.cols;
  data = new float[rows*cols];
    for (int i=0; i<rows*cols;i++)
      data[i] = m.data[i];
}

Matrix::~Matrix()
{
  delete[] data;
}

Matrix Matrix::operator+(const Matrix& other) const {
    if (rows != other.rows || cols != other.cols) {
        throw "Matrix dimensions must match for addition";
    }
    
    Matrix result(rows, cols);
    for (int i = 0; i < rows * cols; i++) {
        result.data[i] = data[i] + other.data[i];
    }
    
    return result;
}

Matrix Matrix::operator-(const Matrix& other) const {
    if (rows != other.rows || cols != other.cols) {
        throw "Matrix dimensions must match for subtraction";
    }
    
    Matrix result(rows, cols);
    for (int i = 0; i < rows * cols; i++) {
        result.data[i] = data[i] - other.data[i];
    }
    
    return result;
}

Matrix Matrix::operator*(const Matrix& other) const {
    if (cols != other.rows) {
        throw "Matrix dimensions incompatible for multiplication";
    }
    
    Matrix result(rows, other.cols);
    
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < other.cols; j++) {
            float sum = 0.0f;
            for (int k = 0; k < cols; k++) {
                sum += (*this)(i, k) * other(k, j);
            }
            result(i, j) = sum;
        }
    }
    
    return result;
}

Matrix& Matrix::operator-=(const Matrix& other) {
    if (rows != other.rows || cols != other.cols) {
        throw "Matrix dimensions must match for -=";
    }
    
    for (int i = 0; i < rows * cols; i++) {
        data[i] -= other.data[i];
    }
    return *this;
}

Matrix Matrix::operator*(float scalar) const {
    Matrix result(rows, cols);
    for (int i = 0; i < rows * cols; i++) {
        result.data[i] = data[i] * scalar;
    }
    return result;
}

Matrix& Matrix::operator=(const Matrix& m) {
    if (this != &m) { 
        delete[] data;
        rows = m.rows;
        cols = m.cols;
        data = new float[rows * cols];
        for (int i = 0; i < rows * cols; i++) {
            data[i] = m.data[i];
        }
    }
    return *this;
}

float& Matrix::operator() (unsigned n, unsigned m)
{
  if (n >= rows || m >= cols)
    throw ("Matrix subscript out of bounds");
  return data[cols*n + m];
}

float Matrix::operator() (unsigned n, unsigned m) const
{
  if (n >= rows || m >= cols)
    throw ("const Matrix subscript out of bounds");
  return data[cols*n + m];
}

void Matrix::T ()
{
  unsigned new_rows = cols;
  unsigned new_cols = rows;
  float* new_data = new float[rows*cols];
  for (int i=0; i<rows;i++){
    for (int j=0; j<cols;j++){
        new_data[i+rows*j] = data[cols*i+j];
    }
  }
  cols = new_cols;
  rows = new_rows;
  data = new_data;
}

Matrix Matrix::transpose() const {
    Matrix result(cols, rows);
    
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result(j, i) = (*this)(i, j);
        }
    }
    
    return result;
}

void Matrix::set(int row, int col, float value) {
    if (row >= rows || col >= cols) {
        throw "Matrix index out of bounds in set()";
    }
    data[cols * row + col] = value;
}

void Matrix::randomize(float min, float max) {
    for (int i = 0; i < rows * cols; i++) {
        data[i] = min + (float)(std::rand()) / ((float)(RAND_MAX / (max - min)));
    }
}

unsigned* Matrix::shape(){
  static unsigned shape[2] = {rows,cols};
  return shape;
}

void Matrix::printshape(){
  std::cout << "[" << rows << "x" << cols << "]" << std::endl;
}

void Matrix::printdata(){
  for (int i=0; i<rows;i++){
    std::cout << "[";
    for (int j=0; j<cols;j++){
      if (j==cols-1)
        std::cout << data[cols*i+j];
      else
        std::cout << data[cols*i+j] << ", ";
    }
  if (i==rows-1)
    std::cout << "]" << std::endl;
  else
    std::cout << "]," << std::endl;
  }
}

float Matrix::sum_squared() const {
    float sum = 0.0f;
    for (int i = 0; i < rows * cols; i++) {
        sum += data[i] * data[i];
    }
    return sum;
}

int Matrix::argmax() const {
    int maxIndex = 0;
    float maxValue = data[0];
    
    for (int i = 1; i < rows * cols; i++) {
        if (data[i] > maxValue) {
            maxValue = data[i];
            maxIndex = i;
        }
    }
    
    return maxIndex;
}

// Activation functions

void Matrix::sigmoid() {
    for (int i = 0; i < rows * cols; i++) {
        data[i] = 1.0f / (1.0f + std::exp(-data[i]));
    }
}

void Matrix::relu() {
    for (int i = 0; i < rows * cols; i++) {
        data[i] = std::max(0.0f, data[i]);
    }
}


Matrix Matrix::sigmoid_derivative() const {
    Matrix result(rows, cols);
    for (int i = 0; i < rows * cols; i++) {
        result.data[i] = data[i] * (1.0f - data[i]);
    }
    return result;
}

Matrix Matrix::relu_derivative() const {
    Matrix result(rows, cols);
    for (int i = 0; i < rows * cols; i++) {
        result.data[i] = data[i] > 0.0f ? 1.0f : 0.0f;
    }
    return result;
}

Matrix Matrix::hadamard(const Matrix& other) const {
    if (rows != other.rows || cols != other.cols) {
        throw "Matrix dimensions must match for Hadamard product";
    }
    
    Matrix result(rows, cols);
    for (int i = 0; i < rows * cols; i++) {
        result.data[i] = data[i] * other.data[i];
    }
    return result;
}