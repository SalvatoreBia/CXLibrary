#include "CXLibrary.h"


namespace cx_lib
{
    cx_matrix matmul(const cx_matrix& a, const cx_matrix& b)
    {
        if (a.cols() != b.rows())
            throw std::runtime_error("Can\'t perform cx_lib::matmul -> dimensions mismatch.");

        cx_matrix new_(a.rows(), b.cols(), cx(0, 0));
        for (size_t j = 0; j < b.cols(); j++)
        {
            cx_vector elem = b.get_col(j);
            for (size_t i = 0; i < a.rows(); i++)
                new_(i, j) = a[i].dot(elem);
        }

        return new_;
    }

    cx_vector matmul(const cx_matrix& a, const cx_vector& b)
    {
        if (a.cols() != b.dim())
            throw std::runtime_error("Can\'t perform cx_lib::matmul -> dimensions mismatch.");
        
        cx_vector new_(a.rows(), cx(0, 0));
        for (size_t i = 0; i < a.rows(); i++)
            new_[i] = a[i].dot(b);

        return new_;
    }

    cx_vector matmul(const cx_vector& a, const cx_matrix& b)
    {
        if (a.dim() != b.rows())
            throw std::runtime_error("Can\'t perform cx_lib::matmul -> dimensions mismatch.");
            
        cx_vector new_(b.cols(), cx(0, 0));
        for (size_t j = 0; j < b.cols(); j++)
        {
            cx_vector elem = b.get_col(j);
            new_[j] = a.dot(elem);
        }

        return new_;
    }

    cx_vector hadamard_vprod(const cx_vector& a, const cx_vector& b)
    {
        if (a.dim() != b.dim())
            throw std::runtime_error("Can\'t perform cx_lib::hadamard_vprod -> dimensions mismatch.");

        cx_vector prod_(a.dim(), cx(0, 0));
        for (size_t i = 0; i < a.dim(); i++)
            prod_[i] = a[i] * b[i];

        return prod_;
    }

    cx_matrix hadamard_prod(const cx_matrix& a, const cx_matrix& b)
    {
        if (a.dim() != b.dim())
            throw std::runtime_error("Can\'t perform cx_lib::hadamard_prod -> dimensions mismatch.");

        cx_matrix prod_(a.rows(), a.cols(), cx(0, 0));
        for (size_t i = 0; i < a.rows(); i++)
            prod_[i] = hadamard_vprod(a[i], b[i]);

        return prod_;
    }

    cx_vector tensor_prod(const cx_vector& a, const cx_vector& b) noexcept
    {
        cx_vector prod_(a.dim() * b.dim(), cx(0, 0));
        for (size_t i = 0; i < a.dim(); i++) 
        {
            for (size_t j = 0; j < b.dim(); j++) 
            {
                size_t index = i * b.dim() + j;
                prod_[index] = a[i] * b[j];
            }
        }

        return prod_;
    }

}