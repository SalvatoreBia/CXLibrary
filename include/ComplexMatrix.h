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
    cx_vector& operator[](size_t) noexcept;
    const cx_vector& operator[](size_t) const noexcept;
    cx& at(size_t, size_t);
    const cx& at(size_t, size_t) const;

    cx_matrix& operator =(const cx_matrix&) noexcept;
    cx_matrix operator +(const cx_matrix&) const;
    cx_matrix operator -(const cx_matrix&) const;
    bool operator ==(const cx_matrix&) const noexcept;
    bool operator !=(const cx_matrix&) const noexcept;

    size_t rows() const noexcept;
    size_t cols() const noexcept;
    std::pair<size_t, size_t> dim() const noexcept;
    cx_vector get_col(size_t) const;

    static cx_matrix get_identity(size_t);

    std::vector<cx_vector> get() noexcept;
};


#endif