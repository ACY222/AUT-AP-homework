// #include "hw1.h"
#include "../include/hw1.h"
#include <cstdlib>
#include <random>
#include <stdexcept>
#include <vector>

using std::logic_error;

static inline void check_empty(const Matrix& matrix) {
  if (matrix.empty() or matrix[0].empty()) {
    throw logic_error("The matrix must be non-empty");
  }
}

static inline void check_square(const Matrix& matrix) {
  if (matrix.size() != matrix[0].size()) {
    throw logic_error("The matrix must be square");
  }
}

static inline void check_positive_parameter(size_t x) {
  if (x <= 0) {
    throw logic_error("The parameters must be positive");
  }
}

static inline void check_same_size(const Matrix& matrix1, const Matrix& matrix2) {
  if (matrix1.size() != matrix2.size() or matrix1[0].size() != matrix2[0].size()) {
    throw logic_error("The size of two matrices must be the same");
  }
}

namespace algebra {
Matrix zeros(size_t n, size_t m) {
  check_positive_parameter(n);
  check_positive_parameter(m);
  return vector(n, vector<double>(m, 0));
}

Matrix ones(size_t n, size_t m) {
  check_positive_parameter(n);
  check_positive_parameter(m);
  return vector(n, vector<double>(m, 1));
}

Matrix random(size_t n, size_t m, double min, double max) {
  check_positive_parameter(n);
  check_positive_parameter(m);
  if (min >= max) {
    throw std::logic_error("The lower bound should be strictly smaller than upper bound");
  }
  std::default_random_engine e;
  std::uniform_real_distribution<double> distribution(min, max);
  Matrix result(n, std::vector<double>(m));
  for (int i = 0; i < n; ++i) {
    for (int j = 0 ; j < m; ++j) {
      result[i][j] = distribution(e);
    }
  }
  return result;
}

void show(const Matrix& matrix) {
  check_empty(matrix);
  const int output_width = 8;
  // force decimal display with 3 decimal places
  std::cout << std::fixed << std::setprecision(3);

  for (const auto& row : matrix) {
    std::cout << "| ";
    for (const auto& val : row) {
      // set the output width and right align
      std::cout << std::setw(output_width) << val << ' ';
    }
    std::cout << "|\n";
  }
}

Matrix multiply(const Matrix& matrix, double c) {
  check_empty(matrix);
  int n = matrix.size(), m = matrix[0].size();
  Matrix result(n, std::vector<double>(m));
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      result[i][j] = matrix[i][j] * c;
    }
  }
  return result;
}

Matrix multiply(const Matrix& matrix1, const Matrix& matrix2) {
  if (matrix1.empty()) return matrix2;
  if (matrix2.empty()) return matrix1;
  if (matrix1[0].size() != matrix2.size()) {
    throw logic_error("Matrices with wrong dimensions cannot be multiplied");
  }
  int row = matrix1.size(), mid = matrix1[0].size(), col = matrix2[0].size();
  Matrix result(row, std::vector<double>(col, 0));
  for (int i = 0; i < row; ++i) {
    for (int j = 0; j < col; ++j) {
      for (int k = 0; k < mid; ++k) {
        result[i][j] += matrix1[i][k] * matrix2[k][j];
      }
    }
  }
  return result;
}

Matrix sum(const Matrix& matrix, double c) {
  if (matrix.empty())   return matrix;
  int n = matrix.size(), m = matrix[0].size();
  Matrix result(matrix);
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      result[i][j] = result[i][j] + c;
    }
  }
  return result;
}

Matrix sum(const Matrix& matrix1, const Matrix& matrix2) {
  if (matrix1.empty() and matrix2.empty()) return {};
  check_same_size(matrix1, matrix2);
  int n = matrix1.size(), m = matrix1[0].size();
  Matrix result(n, std::vector<double>(m));
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      result[i][j] = matrix1[i][j] + matrix2[i][j];
    }
  }
  return result;
}

Matrix transpose(const Matrix& matrix) {
  if (matrix.empty()) return matrix;
  int n = matrix.size(), m = matrix[0].size();
  Matrix result(m, std::vector<double>(n));
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      result[j][i] = matrix[i][j];
    }
  }
  return result;
}

Matrix minor(const Matrix& matrix, size_t n, size_t m) {
  check_empty(matrix);
  int row = matrix.size(), col = matrix[0].size();
  if (n >= row or m >= col) {
    throw logic_error("The parameters is out of range");
  }
  Matrix result(row - 1, std::vector<double>(col - 1));
  for (int i = 0; i < row; ++i) {
    for (int j = 0; j < col; ++j) {
      if (i == n or j == m) {
        continue;
      }
      int i1 = i, j1 = j;
      if (i > n) {
        i1 = i - 1;
      }
      if (j > m) {
        j1 = j - 1;
      }
      result[i1][j1] = matrix[i][j];
    }
  }
  return result;
}

double determinant(const Matrix &matrix) {
  if (matrix.empty()) {
    return 1;
  }
  check_square(matrix);
  if (matrix.size() == 1) { // if there is only one element in the matrix
    return matrix[0][0];
  }

  // if the size of the matrix is greater than 1
  auto isOdd = [](int x) -> bool { return x % 2 == 1; };
  double result = 0;
  for (int j = 0; j < matrix[0].size(); ++j) {
    result = result + (j & 1 ? -1 : 1) * determinant(minor(matrix, 0, j)) * matrix[0][j];
  }
  return result;
}

Matrix adjoint(const Matrix& matrix, int n) {
  Matrix result = zeros(n, n);
  auto isOdd = [](int x) { return x % 2 == 1;};
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      result[i][j] = ((i + j) & 1 ? -1 : 1) * determinant(minor(matrix, i, j));
    }
  }
  return transpose(result);
}

// A^{-1} = adj(A) / |A|
Matrix inverse(const Matrix& matrix) {
  if (matrix.empty()) return matrix;
  check_square(matrix);
  double det = determinant(matrix);
  if (std::abs(det) < 1e-9) { // |A| cannot be 0
    throw logic_error("Singular matrices have no inverse");
  }
  Matrix adj = adjoint(matrix, matrix.size());
  return multiply(adj, 1.0 / det);
}

Matrix concatenate(const Matrix& m1, const Matrix &m2, int axis) {
  check_empty(m1);
  check_empty(m2);
  Matrix result;
  if (axis == 0) {
    if (m1[0].size() != m2[0].size()) {
      throw logic_error("The numbers of columns of two matrices must be the same");
    }
    int row = m1.size() + m2.size(), col = m1[0].size();
    result.resize(row, std::vector<double>(col));
    for (int i = 0; i < row; ++i) {
      for (int j = 0; j < col; ++j) {
        if (i < m1.size()) {
          result[i][j] = m1[i][j];
        }
        else {
          result[i][j] = m2[i - m1.size()][j];
        }
      }
    }
  }
  else {
    if (m1.size() != m2.size()) {
      throw logic_error("The numbers of rows of two matrices must be the same");
    }
    int row = m1.size(), col = m1[0].size() + m2[0].size();
    result.resize(row, std::vector<double>(col));
    for (int i = 0; i < row; ++i) {
      for (int j = 0; j < col; ++j) {
        if (j < m1[0].size()) {
          result[i][j] = m1[i][j];
        }
        else {
          result[i][j] = m2[i][j - m1[0].size()];
        }
      }
    }
  }
  return result;
}

Matrix ero_swap(const Matrix& matrix, size_t r1, size_t r2) {
  if (r1 < 0 or r1 >= matrix.size() or r2 < 0 or r2 >= matrix.size()) {
    throw logic_error("The two rows must be in the matrix");
  }
  Matrix result(matrix);
  std::swap(result[r1], result[r2]);
  return result;
}


Matrix ero_multiply(const Matrix& matrix, size_t r, double c) {
  if (r < 0 or r >= matrix.size()) {
    throw std::logic_error("The row must be in the matrix");
  }
  Matrix result(matrix);
  for (int j = 0; j < result[0].size(); ++j) {
    result[r][j] *= c;
  }
  return result;
}

// add r1 * c to r2
Matrix ero_sum(const Matrix& matrix, size_t r1, double c, size_t r2) {
  if (r1 < 0 or r1 >= matrix.size() or r2 < 0 or r2 >= matrix.size()) {
    throw logic_error("The two rows must be in the matrix");
  }
  Matrix result(matrix);
  for (int j = 0; j < result[0].size(); ++j) {
    result[r2][j] += result[r1][j] * c;
  }
  return result;
}

Matrix upper_triangular(const Matrix& matrix) {
  if (matrix.size() <= 1) return matrix;
  check_square(matrix);
  using namespace algebra;
  Matrix result(matrix);
  for (int i = 0; i < matrix.size(); ++i) {
    bool pivot_not_zero = true;
    // if the pivot == 0, find a non-empty pivot in the following rows
    if (std::abs(result[i][i]) < 1e-9) {
      pivot_not_zero = false;
      for (int k = i + 1; k < matrix.size(); ++k) {
        if (std::abs(result[k][i]) > 1e-9) {
          pivot_not_zero = true;
          result = ero_swap(result, i, k);  // swap row-i and row-k if possible
          break;
        }
      }
    }
    if (!pivot_not_zero) {  // if we could not find a non-zero pivot
      continue;
    }
    for (int k = i + 1; k < matrix.size(); ++k) {
      result = ero_sum(result, i, -result[k][i] / result[i][i], k);
    }
  }
  return result;
}

}
