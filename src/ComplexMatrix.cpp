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

cx_vector& cx_matrix::operator[](size_t __index) noexcept
{
    return this->mat[__index];
}

const cx_vector& cx_matrix::operator[](size_t __index) const noexcept
{
    return this->mat[__index];
}

cx &cx_matrix::at(size_t __row, size_t __col)
{
    if (( __row >= this->rows()) || (__col >= this->cols()))
        throw std::runtime_error("Index out of range.");

    return this->mat[__row][__col];
}

const cx &cx_matrix::at(size_t __row, size_t __col) const
{
    if (( __row >= this->rows()) || (__col >= this->cols()))
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

cx_vector cx_matrix::get_col(size_t __index) const
{
    if (__index >= this->cols())
        throw std::runtime_error("Index out of range.");

    cx_vector col_(this->rows(), cx(0, 0));
    for (size_t i = 0; i < this->rows(); i++)
        col_[i] = this->at(i, __index);

    return col_;
}

cx_matrix& cx_matrix::operator =(const cx_matrix& obj) noexcept
{
    if (this != &obj)
        this->mat = obj.mat;
        
    return *this;
}

cx_matrix cx_matrix::operator +(const cx_matrix& obj) const
{
    if (this->dim() != obj.dim())
        throw std::invalid_argument("Dimensions don\'t match.");

    cx_matrix new_(this->rows(), this->cols(), cx(0, 0));
    for (size_t i = 0; i < this->rows(); i++)
        new_.mat[i] = this->mat[i] + obj.mat[i];

    return new_;
}

cx_matrix cx_matrix::operator -(const cx_matrix& obj) const
{
    if (this->dim() != obj.dim())
        throw std::invalid_argument("Dimensions don\'t match.");

    cx_matrix new_(this->rows(), this->cols(), cx(0, 0));
    for (size_t i = 0; i < this->rows(); i++)
        new_.mat[i] = this->mat[i] - obj.mat[i];

    return new_;
}

bool cx_matrix::operator ==(const cx_matrix& obj) const noexcept
{
    if (this->rows() != obj.rows() || this->cols() != obj.cols()) return false;
    for (size_t i = 0; i < this->rows(); i++)
        for (size_t j = 0; j < this->cols(); j++)
            if ((*this)(i, j) != obj(i, j))
                return false;
    return true;
}

bool cx_matrix::operator !=(const cx_matrix& obj) const noexcept
{
    return !((*this) == obj.mat);
}

cx_matrix cx_matrix::get_identity(size_t __size)
{
    if (__size < 2)
        throw std::invalid_argument("Identity matrix accepts size greater or equal than 2.");

    cx_matrix identity_(__size, __size, cx(0, 0));
    for (size_t i = 0; i < __size; i++)
        identity_(i, i) = cx(1, 0);

    return identity_;
}

std::vector<cx_vector> cx_matrix::get() noexcept
{
    return this->mat;
}