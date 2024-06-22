#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <memory>
#include "Cell.h"

template<typename T>
class Matrix {
private:
    std::vector<T> data;
    int rows;
    int cols;

public:
    Matrix(int rows, int cols);
    Matrix();

    T& operator()(int row, int col);
    const T& operator()(int row, int col) const;

    int rowSize() const;
    int colSize() const;
};

// Explicit instantiation of commonly used types
extern template class Matrix<std::unique_ptr<Cell>>;

#endif // MATRIX_H