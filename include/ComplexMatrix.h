#ifndef COMPLEX_MATRIX_H
#define COMPLEX_MATRIX_H

#include <cmath>
#include <stdexcept>
#include <vector>
#include <ostream>
#include "ComplexNumber.h"
#include "ComplexVector.h"

namespace cx_lib
{
    /**
     * @brief Complex matrix class for mathematical operations
     * 
     * Provides functionality for:
     * - Basic matrix operations (+, -, *)  
     * - Matrix-vector operations
     * - Element access and modification
     * - Matrix transformations
     */
    class cx_matrix
    {
    private:
        std::vector<cx_vector> mat; ///< Storage for matrix rows as complex vectors

    public:
        /** @brief Default constructor creating empty matrix */
        cx_matrix()  = default;
        /** @brief Default destructor */
        ~cx_matrix() = default;
        /** @brief Construct matrix with dimensions and fill value
         * @param rows Number of rows
         * @param cols Number of columns
         * @param value Value to fill matrix with
         */
        cx_matrix(size_t, size_t, const cx&);
        /** @brief Construct from 2D vector of complex numbers
         * @param mat 2D vector to initialize from
         */
        cx_matrix(const std::vector<std::vector<cx>>&);
        /** @brief Construct from vector of complex vectors
         * @param vecs Vector of complex vectors representing rows
         */
        cx_matrix(const std::vector<cx_vector>&);
        /** @brief Copy constructor
         * @param other Matrix to copy
         */
        cx_matrix(const cx_matrix&) noexcept;

        /** @brief Access element with parentheses operator
         * @param i Row index
         * @param j Column index
         */
        cx& operator ()(size_t, size_t) noexcept;
        /** @brief Const access element with parentheses operator */
        const cx& operator()(size_t, size_t) const noexcept;
        /** @brief Access row with subscript operator */
        cx_vector& operator[](size_t) noexcept;
        /** @brief Const access row with subscript operator */
        const cx_vector& operator[](size_t) const noexcept;
        /** @brief Safe element access with bounds checking
         * @throws std::out_of_range if indices invalid
         */
        cx& at(size_t, size_t);
        /** @brief Const safe element access with bounds checking */
        const cx& at(size_t, size_t) const;

        /** @brief Copy assignment operator */
        cx_matrix& operator =(const cx_matrix&) noexcept;
        /** @brief Matrix addition operator */
        cx_matrix operator +(const cx_matrix&) const;
        /** @brief Matrix subtraction operator */
        cx_matrix operator -(const cx_matrix&) const;
        /** @brief Equality comparison operator */
        bool operator ==(const cx_matrix&) const noexcept;
        /** @brief Inequality comparison operator */
        bool operator !=(const cx_matrix&) const noexcept;

        /** @brief Get number of rows */
        size_t rows() const noexcept;
        /** @brief Get number of columns */
        size_t cols() const noexcept;
        /** @brief Get matrix dimensions as (rows, cols) */
        std::pair<size_t, size_t> dim() const noexcept;
        /** @brief Get specified column as vector */
        cx_vector get_col(size_t) const;

        /** @brief Create identity matrix of given size */
        static cx_matrix get_identity(size_t);
        /** @brief Get underlying vector representation */
        std::vector<cx_vector> get() noexcept;

        /** @brief Stream output operator */
        friend std::ostream& operator <<(std::ostream&, const cx_matrix&);
    };
}

#endif