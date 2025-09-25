#include <../include/matrix.h>
#include <cstdlib>
#include <ctime>
#include <tuple>
#include <iostream>

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

Matrix& Matrix::operator=(const Matrix& m){
  std::cout << "Assignment operator called " << std::endl;
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

void Matrix::mult (float l)
{
  for (int i=0; i<rows*cols;i++){
    data[i] *= (float)l;
  }
}

void Matrix::add (float a)
{
  for (int i=0; i<rows*cols;i++){
    data[i] += (float)a;
  }
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

void Matrix::rand(){
  for (int i=0; i<rows*cols;i++){
    data[i] = (float)(std::rand()%100001)/100000.f;
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