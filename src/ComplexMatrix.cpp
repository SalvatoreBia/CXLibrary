#include "ComplexMatrix.h"

cx_matrix::cx_matrix(size_t __rows, size_t __cols, const cx &val)
{
    if (__rows < 2 || __cols < 2)
        throw std::invalid_argument("cx_matrix must have at least 2 rows and columns");

    this->mat = std::vector<cx_vector>(__rows);
    for (size_t i = 0; i < __rows; i++)
        this->mat[i] = cx_vector(__cols, val);
}

cx_matrix::cx_matrix(const std::vector<std::vector<cx>> &vec)
{
    size_t __rows = vec.size();
    if (__rows < 2)
        throw std::invalid_argument("cx_matrix must have at least 2 rows and columns.");

    size_t __cols = vec[0].size();
    for (size_t i = 0; i < __rows; i++)
    {
        if (__cols != vec[i].size())
            throw std::invalid_argument("cx_matrix accepts accepts only rectangular matrices.");

        __cols = vec[i].size();
    }

    if (__cols < 2)
        throw std::invalid_argument("cx_matrix must have at least 2 rows and columns.");

    this->mat = std::vector<cx_vector>(__rows);
    for (size_t i = 0; i < __rows; i++)
        this->mat[i] = cx_vector(vec[i]);
}

cx_matrix::cx_matrix(const std::vector<cx_vector> &vec)
{
    size_t __rows = vec.size();
    if (__rows < 2)
        throw std::invalid_argument("cx_matrix must have at least 2 rows and columns.");

    size_t __cols = vec[0].dim();
    for (size_t i = 1; i < __rows; i++)
    {
        if (__cols != vec[i].dim())
            throw std::invalid_argument("cx_matrix accepts accepts only rectangular matrices.");

        __cols = vec[i].dim();
    }

    if (__cols < 2)
        throw std::invalid_argument("cx_matrix must have at least 2 rows and columns.");

    this->mat = std::vector<cx_vector>(__rows);
    for (size_t i = 0; i < __rows; i++)
        this->mat[i] = vec[i];
}

cx_matrix::cx_matrix(const cx_matrix &obj) noexcept
{
    this->mat = obj.mat;
}

cx &cx_matrix::operator()(size_t __row, size_t __col) noexcept
{
    return this->mat[__row][__col];
}

const cx &cx_matrix::operator()(size_t __row, size_t __col) const noexcept
{
    return this->mat[__row][__col];
}

cx &cx_matrix::at(size_t __row, size_t __col)
{
    if (
        (__row < 0 || __row >= this->rows()) ||
        (__col < 0 || __col >= this->cols()))
        throw std::runtime_error("Index out of range.");

    return this->mat[__row][__col];
}

const cx &cx_matrix::at(size_t __row, size_t __col) const
{
    if (
        (__row < 0 || __row >= this->rows()) ||
        (__col < 0 || __col >= this->cols()))
        throw std::runtime_error("Index out of range.");

    return this->mat[__row][__col];
}

size_t cx_matrix::rows() const noexcept
{
    return this->mat.size();
}

size_t cx_matrix::cols() const noexcept
{
    return this->mat[0].dim();
}

std::pair<size_t, size_t> cx_matrix::dim() const noexcept
{
    return std::make_pair(this->rows(), this->cols());
}