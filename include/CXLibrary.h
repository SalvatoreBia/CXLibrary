#ifndef CXLIBRARY_H
#define CXLIBRARY_H

#include "ComplexNumber.h"
#include "ComplexVector.h"
#include "ComplexMatrix.h"


namespace cx_lib
{
    struct cx;
    class cx_vector;
    class cx_matrix;
    class cx_tensor;

    cx_matrix matmul(const cx_matrix& a, const cx_matrix& b);
    cx_vector matmul(const cx_vector& a, const cx_matrix& b);
    cx_vector matmul(const cx_matrix& a, const cx_vector& b);
    cx_vector hadamard_vprod(const cx_vector& a, const cx_vector& b);
    cx_matrix hadamard_prod(const cx_matrix& a, const cx_matrix& b);
    cx_vector tensor_prod(const cx_vector& a, const cx_vector& b) noexcept;
}

#endif
