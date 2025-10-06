#ifndef AP_HW1_H
#define AP_HW1_H

#include <vector>
using Matrix = std::vector<std::vector<double>>;

namespace algebra {
  Matrix zeros(size_t n, size_t m);
  Matrix ones(size_t n, size_t m);
  // create a n*m matrix with all elements in [min, max]
  // use <random> library first introduced in C++11
  Matrix random(size_t n, size_t m, double min, double max);
  // display the matrix in a beautiful way
  // use <iomanip> library, each element have 3 decimal places
  void show(const Matrix& matrix);

  Matrix multiply(const Matrix& matrix, double c);
  Matrix multiply(const Matrix& matrix1, const Matrix& matrix2);
  Matrix sum(const Matrix& matrix, double c);
  Matrix sum(const Matrix& matrix1, const Matrix& matrix2);

  Matrix transpose(const Matrix& matrix);
  // return the matrix without n-th row and m-th column
  Matrix minor(const Matrix& matrix, size_t n, size_t m);
  double determinant(const Matrix& matrix);

  Matrix inverse(const Matrix& matrix);

  // concatenate m1 and m2 along the specified axis
  // 0: on top of each other, 1: alongside each other
  Matrix concatenate(const Matrix& m1, const Matrix& m2, int axis = 0);
  Matrix ero_swap(const Matrix& matrix, size_t r1, size_t r2);
  Matrix ero_multiply(const Matrix& matrix, size_t r, double c);
  Matrix ero_sum(const Matrix& matrix, size_t r1, double c, size_t r2);
  Matrix upper_triangular(const Matrix& matrix);
}


#endif //AP_HW1_H
