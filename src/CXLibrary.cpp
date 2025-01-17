#include "CXLibrary.h"
#include "ComplexMatrix.h"
#include "ComplexVector.h"

namespace cx_lib
{
    std::atomic<bool> __cx_multithread_enabled__ = false;

    void enable_multithreading(bool enable) noexcept
    {
        __cx_multithread_enabled__ = enable;
    }

    cx_matrix matmul(const cx_matrix& a, const cx_matrix& b)
    {
        if (a.cols() != b.rows())
            throw std::runtime_error("Can't perform cx_lib::matmul -> dimensions mismatch.");

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
            throw std::runtime_error("Can't perform cx_lib::matmul -> dimensions mismatch.");
        
        cx_vector new_(a.rows(), cx(0, 0));
        for (size_t i = 0; i < a.rows(); i++)
            new_[i] = a[i].dot(b);

        return new_;
    }

    cx_vector matmul(const cx_vector& a, const cx_matrix& b)
    {
        if (a.dim() != b.rows())
            throw std::runtime_error("Can't perform cx_lib::matmul -> dimensions mismatch.");
            
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
            throw std::runtime_error("Can't perform cx_lib::hadamard_vprod -> dimensions mismatch.");

        cx_vector prod_(a.dim(), cx(0, 0));
        for (size_t i = 0; i < a.dim(); i++)
            prod_[i] = a[i] * b[i];

        return prod_;
    }

    cx_matrix hadamard_prod(const cx_matrix& a, const cx_matrix& b)
    {
        if (a.dim() != b.dim())
            throw std::runtime_error("Can't perform cx_lib::hadamard_prod -> dimensions mismatch.");

        cx_matrix prod_(a.rows(), a.cols(), cx(0, 0));
        for (size_t i = 0; i < a.rows(); i++)
            prod_[i] = hadamard_vprod(a[i], b[i]);

        return prod_;
    }

    cx_tensor hadamard_prod(const cx_tensor& a, const cx_tensor& b)
    {
        if (a.shape() != b.shape())
            throw std::invalid_argument("Shapes do not match for Hadamard product.");

        cx_tensor result(a.shape(), cx(0, 0));

        if (cx_lib::__cx_multithread_enabled__)
        {
            size_t num_threads = std::thread::hardware_concurrency();
            size_t chunk_size = a.size() / num_threads;
            std::vector<std::thread> threads;

            for (size_t t = 0; t < num_threads; t++)
            {
                threads.emplace_back([&, t]() {
                    size_t start = t * chunk_size;
                    size_t end = (t == num_threads - 1)? a.size() : (t + 1) * chunk_size;
                    for (size_t i = start; i < end; i++)
                        result[i] = a[i] * b[i];
                });
            }

            for (auto& thread : threads)
                thread.join();
        }
        else
            for (size_t i = 0; i < a.size(); i++)
                result[i] = a[i] * b[i];

        return result;
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

    cx_tensor tensor_prod(const cx_tensor& a, const cx_tensor& b) noexcept
    {
        std::vector<size_t> shape_a(a.shape());
        std::vector<size_t> shape_b(b.shape());
        shape_a.insert(shape_a.end(), shape_b.begin(), shape_b.end());
        cx_tensor new_(shape_a, cx(0, 0));

        for (size_t i = 0; i < a.size(); i++)
        {
            std::vector<size_t> idx_a = a.unravel_index(i);
            for (size_t j = 0; j < b.size(); j++)
            {
                std::vector<size_t> idx_b = b.unravel_index(j);
                std::vector<size_t> idx_new = idx_a;
                idx_new.insert(idx_new.end(), idx_b.begin(), idx_b.end());
                new_.at(idx_new) = a[i] * b[j];
            }
        }

        return new_;
    }
}