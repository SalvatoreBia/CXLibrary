#ifndef CXLIBRARY_H
#define CXLIBRARY_H

#include "ComplexNumber.h"
#include "ComplexVector.h"
#include "ComplexMatrix.h"
#include "ComplexTensor.h"
#include <atomic>
#include <mutex>
#include <thread>

namespace cx_lib
{
    struct cx;
    class cx_vector;
    class cx_matrix;
    class cx_tensor;

    /** @brief Global flag for enabling/disabling multithreading (can use only on tensors)*/
    extern std::atomic<bool> __cx_multithread_enabled__;
    
    /** @brief Enable or disable multithreading for operations
     * @param enable True to enable, false to disable
     */
    void enable_multithreading(bool enable) noexcept;

    /** @brief Matrix multiplication of two matrices
     * @param a Left matrix
     * @param b Right matrix
     * @return Result of a × b
     * @throws std::invalid_argument if dimensions mismatch
     */
    cx_matrix matmul(const cx_matrix& a, const cx_matrix& b);

    /** @brief Matrix multiplication of vector and matrix
     * @param a Vector (treated as row vector)
     * @param b Matrix
     * @return Result vector
     */
    cx_vector matmul(const cx_vector& a, const cx_matrix& b);

    /** @brief Matrix multiplication of matrix and vector
     * @param a Matrix
     * @param b Vector (treated as column vector)
     * @return Result vector
     */
    cx_vector matmul(const cx_matrix& a, const cx_vector& b);

    /** @brief Element-wise product of two vectors
     * @param a First vector
     * @param b Second vector
     * @return Result of element-wise multiplication
     */
    cx_vector hadamard_vprod(const cx_vector& a, const cx_vector& b);

    /** @brief Element-wise product of two matrices
     * @param a First matrix
     * @param b Second matrix
     * @return Result of element-wise multiplication
     */
    cx_matrix hadamard_prod(const cx_matrix& a, const cx_matrix& b);

    /** @brief Element-wise product of two tensors
     * @param a First tensor
     * @param b Second tensor
     * @return Result of element-wise multiplication
     */
    cx_tensor hadamard_prod(const cx_tensor& a, const cx_tensor& b);

    /** @brief Tensor (outer) product of two vectors
     * @param a First vector
     * @param b Second vector
     * @return Result of tensor product
     */
    cx_vector tensor_prod(const cx_vector& a, const cx_vector& b) noexcept;

    /** @brief Tensor (outer) product of two tensors
     * @param a First tensor
     * @param b Second tensor
     * @return Result of tensor product
     */
    cx_tensor tensor_prod(const cx_tensor& a, const cx_tensor& b) noexcept;
}

#endif