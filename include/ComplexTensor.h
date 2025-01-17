#ifndef COMPLEX_TENSOR_H
#define COMPLEX_TENSOR_H

#include <vector>
#include <stdexcept>
#include <numeric>
#include <algorithm>
#include "CXLibrary.h"
#include "ComplexNumber.h"

namespace cx_lib
{
    enum __cx_comparison_criteria__
    {
        BY_REAL,
        BY_IMAG,
        BY_MOD,
        BY_PHASE
    };

    /**
     * @brief N-dimensional tensor of complex numbers
     * 
     * Provides functionality for:
     * - Basic tensor operations (+, -)
     * - Tensor transformations (reshape, transpose)
     * - Broadcasting operations
     * - Element access and slicing
     * - Reduction operations
     */
    class cx_tensor
    {
    private:
        std::vector<cx> data;              ///< Flattened storage for tensor elements
        std::vector<size_t> __shape__;     ///< Dimensions of the tensor
        size_t __size__ = 0;               ///< Total number of elements

        /** @brief Convert multi-dimensional index to linear index
         * @param indices Vector of indices for each dimension
         * @return Linear index into data array
         */
        size_t lindex(const std::vector<size_t>&) const;
    
    public:
        /** @brief Default constructor creating empty tensor */
        cx_tensor() = default;
        /** @brief Copy constructor */
        cx_tensor(const cx_tensor&) = default;
        /** @brief Construct tensor with given shape and fill value
         * @param shape Vector of dimensions
         * @param value Value to fill tensor with
         */
        cx_tensor(const std::vector<size_t>&, const cx&);
        /** @brief Construct tensor with given shape and data
         * @param shape Vector of dimensions
         * @param data Vector of values to initialize with
         */
        cx_tensor(const std::vector<size_t>&, const std::vector<cx>&);

        /** @brief Linear index access operator */
        cx& operator [](size_t) noexcept;
        /** @brief Const linear index access operator */
        const cx& operator [](size_t) const noexcept;
        /** @brief Multi-dimensional index access 
         * @throws std::invalid_argument if indices don't match tensor shape
         */
        cx& at(const std::vector<size_t>&);
        /** @brief Const multi-dimensional index access */
        const cx& at(const std::vector<size_t>&) const;
    
        /** @brief Element-wise addition */
        cx_tensor operator +(const cx_tensor&) const;
        /** @brief Element-wise subtraction */
        cx_tensor operator -(const cx_tensor&) const;
    
        /** @brief Reshape tensor to new dimensions
         * @throws std::invalid_argument if new shape is invalid
         */
        cx_tensor& reshape(const std::vector<size_t>&);
        /** @brief Extract slice of tensor
         * @param start Starting indices
         * @param end Ending indices
         */
        cx_tensor slice(const std::vector<size_t>&, const std::vector<size_t>&) const;
        /** @brief Add with broadcasting
         * @throws std::invalid_argument if shapes incompatible
         */
        cx_tensor broadcast_add(const cx_tensor&) const;
        /** @brief Transpose tensor along given axes
         * @param axes Permutation of dimensions
         */
        cx_tensor transpose(const std::vector<size_t>&) const;
        /** @brief Sum reduction along specified axis
         * @param axis Dimension to reduce
         */
        cx_tensor reduce_sum(size_t) const;

        /** @brief Get total number of elements */
        size_t size() const noexcept;
        /** @brief Get tensor dimensions */
        const std::vector<size_t>& shape() const noexcept;
        /** @brief Check if tensor is empty */
        std::vector<size_t> unravel_index(size_t) const;
        
        /** @brief Normalize tensor elements, according to min and max values in it */
        void normalize(__cx_comparison_criteria__);
        /** @brief Flatten tensor to 1D vector */
        void flatten() noexcept;
    };
}

#endif