#include <cassert>
#include "Matrix.h"
#include "../world-generator/Cell.h"

template<typename T>
Matrix<T>::Matrix(int rows, int cols) : rows(rows), cols(cols), data(rows* cols) {}

template<typename T>
Matrix<T>::Matrix() : Matrix(3, 2) {}

template<typename T>
T& Matrix<T>::operator()(int row, int col) {
    assert(row >= 0 && row < rows && col >= 0 && col < cols);
    return data[row * cols + col];
}

template<typename T>
const T& Matrix<T>::operator()(int row, int col) const {
    assert(row >= 0 && row < rows && col >= 0 && col < cols);
    return data[row * cols + col];
}

template<typename T>
int Matrix<T>::rowSize() const {
    return rows;
}

template<typename T>
int Matrix<T>::colSize() const {
    return cols;
}

// Explicitly instantiate the template for std::unique_ptr<Cell>
template class Matrix<std::unique_ptr<Cell>>;