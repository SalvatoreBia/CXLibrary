#ifndef COMPLEX_MATRIX_H
#define COMPLEX_MATRIX_H

#include <cmath>
#include <stdexcept>
#include <vector>
#include "ComplexNumber.h"
#include "ComplexVector.h"

class cx_matrix
{
private:
    std::vector<cx_vector> mat;

public:
    cx_matrix()  = default;
    ~cx_matrix() = default;
    cx_matrix(size_t, size_t, const cx&);
    cx_matrix(const std::vector<std::vector<cx>>&);
    cx_matrix(const std::vector<cx_vector>&);
    cx_matrix(const cx_matrix&) noexcept;

    cx& operator ()(size_t, size_t) noexcept;
    const cx& operator()(size_t, size_t) const noexcept;
    cx& at(size_t, size_t);
    const cx& at(size_t, size_t) const;

    size_t rows() const noexcept;
    size_t cols() const noexcept;
    std::pair<size_t, size_t> dim() const noexcept;
};


#endif