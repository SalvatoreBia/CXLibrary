#ifndef COMPLEX_VEC_H
#define COMPLEX_VEC_H

#include <vector>
#include <cmath>
#include <stdexcept>
#include <ostream>
#include "ComplexNumber.h"

namespace cx_lib
{
    /**
     * @brief Complex vector class for mathematical operations
     * 
     * Provides functionality for:
     * - Basic vector operations (+, -, *, etc.)
     * - Vector products (dot, cross)
     * - Statistical operations (mean, sum, max, min)
     * - Vector transformations (normalize, projection)
     */
    class cx_vector
    {
    private:
        std::vector<cx> arr;      ///< Storage for complex numbers
        cx __sum__;               ///< Cached sum of elements
        cx __mean__;             ///< Cached mean of elements
        cx __max__;              ///< Cached maximum element
        cx __min__;              ///< Cached minimum element
        bool cache_valid = false; ///< Flag indicating if cache is valid

    public:
        /** @brief Default constructor creating empty vector */
        cx_vector() = default;
        /** @brief Construct from vector of complex numbers
         * @param vec Vector of complex numbers to copy
         */
        cx_vector(const std::vector<cx>&);
        /** @brief Copy constructor
         * @param other Vector to copy
         */
        cx_vector(const cx_vector&) noexcept;
        /** @brief Move constructor */
        cx_vector(cx_vector&&) noexcept = default;
        /** @brief Construct vector with size elements of value
         * @param size Number of elements
         * @param value Value to fill with
         */
        cx_vector(size_t size, const cx& value);

        /** @brief Copy assignment operator */
        cx_vector& operator =(const cx_vector&) noexcept;
        /** @brief Vector addition operator */
        cx_vector operator  +(const cx_vector&) const;
        /** @brief Vector subtraction operator */
        cx_vector operator  -(const cx_vector&) const;
        /** @brief Scalar multiplication with complex number */
        cx_vector operator  *(const cx&) const noexcept;
        /** @brief Scalar multiplication with float */
        cx_vector operator  *(float) const noexcept;
        /** @brief Array subscript operator */
        cx& operator [](size_t index) noexcept;
        /** @brief Const array subscript operator */
        const cx& operator [](size_t index) const noexcept;
        /** @brief Equality comparison operator */
        bool operator ==(const cx_vector&) const noexcept;
        /** @brief Inequality comparison operator */
        bool operator !=(const cx_vector&) const noexcept;

        /** @brief Safe element access with bounds checking
         * @throws std::out_of_range if index is invalid
         */
        const cx& at(size_t index) const;
        /** @brief Get vector dimension */
        size_t dim() const noexcept;
        /** @brief Normalize vector in-place */
        void normalize();
        /** @brief Calculate vector magnitude */
        float mod() const noexcept;
        /** @brief Calculate cumulative sum vector */
        cx_vector cumulative_sum() const noexcept;
        /** @brief Calculate vector projection onto another vector */
        cx_vector projection(const cx_vector&) const;
        /** @brief Calculate complex conjugate of vector */
        cx_vector conjugate() const noexcept;
        /** @brief Calculate dot product with another vector */
        cx dot(const cx_vector&) const;
        /** @brief Calculate cross product with another vector */
        cx_vector cross(const cx_vector&) const;

        /** @brief Get sum of all elements */
        cx sum() const noexcept;
        /** @brief Get mean of all elements */
        cx mean() const noexcept;
        /** @brief Get maximum element */
        cx max() const noexcept;
        /** @brief Get minimum element */
        cx min() const noexcept;

        /** @brief Create zero vector of given size */
        static cx_vector null_vector(size_t);
        /** @brief Get underlying vector */
        std::vector<cx> get() noexcept;
        /** @brief Stream output operator */
        friend std::ostream& operator <<(std::ostream&, const cx_vector&);
        
    private:
        /** @brief Reset cached values */
        void reset_values();
    };
}

#endif