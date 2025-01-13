#include "ComplexVector.h"

cx_vector::cx_vector(const std::vector<cx>& vec)
    : arr(vec)
{
    if (vec.size() < 2)
        throw std::invalid_argument("cx_vector constructor accepts vector with size greater or equal than 2.");
	
	this->reset_values();
}

cx_vector::cx_vector(const cx_vector& obj) noexcept
    : arr(obj.arr)
{
	this->__sum__ = obj.__sum__;
    this->__mean__ = obj.__mean__;
    this->__max__ = obj.__max__;
    this->__min__ = obj.__min__;
}

cx_vector::cx_vector(size_t __size, const cx& val)
    : arr(__size, val)
{
    if (__size < 2)
        throw std::invalid_argument("cx_vector constructor accepts vector with size greater or equal than 2.");

	this->reset_values();
}

cx_vector& cx_vector::operator =(const cx_vector& obj) noexcept
{
    if (this != &obj)
    {
        this->arr = obj.arr;
        this->__sum__ = obj.__sum__;
        this->__mean__ = obj.__mean__;
        this->__max__ = obj.__max__;
        this->__min__ = obj.__min__;
    }
    return *this;
}

const cx& cx_vector::operator [](size_t index) const noexcept
{
    return this->arr[index];
}

const cx& cx_vector::at(size_t index) const
{
    if (index >= this->arr.size())
        throw std::runtime_error("Index out of range.");

    return (*this)[index];
}

cx_vector cx_vector::operator +(const cx_vector& obj) const
{
    if (this->arr.size() != obj.arr.size())
        throw std::runtime_error("Dimensions don\'t match.");

    cx_vector sum_(this->arr.size(), cx(0, 0));
    for (size_t i = 0; i < this->arr.size(); i++)
        sum_[i] = (*this)[i] + obj[i];

	sum_.reset_values();
    return sum_;
}

cx_vector cx_vector::operator -(const cx_vector& obj) const
{
    if (this->arr.size() != obj.arr.size())
        throw std::runtime_error("Dimensions don\'t match.");

    cx_vector sub_(this->arr.size(), cx(0, 0));
    for (size_t i = 0; i < this->arr.size(); i++)
        sub_[i] = (*this)[i] - obj[i];

	sub_.reset_values();
    return sub_;
}

cx_vector cx_vector::operator *(const cx& val) const noexcept
{
    cx_vector prod_ = *this;
    for (size_t i = 0; i < prod_.dim(); i++)
        prod_[i] = prod_[i] * val;

	prod_.reset_values();
    return prod_;
}

cx_vector cx_vector::operator *(float val) const noexcept
{
    return (*this) * cx(val, 0);
}

size_t cx_vector::dim() const noexcept
{
    return this->arr.size();
}

bool cx_vector::operator ==(const cx_vector& obj) const noexcept
{
    if (this->dim() != obj.dim())
        return false;

    for (size_t i = 0; i < this->dim(); i++)
        if ((*this)[i] != obj[i])
            return false;

    return true;
}

bool cx_vector::operator !=(const cx_vector& obj) const noexcept
{
    return !((*this) == obj);
}

float cx_vector::mod() const noexcept
{
    float sum_ = 0.0f;
    for (const auto& val : this->arr)
        sum_ += val.mod() * val.mod();

    return std::sqrt(sum_);
}

void cx_vector::normalize() noexcept
{
    float mag = this->mod();
    if (mag == 0.0f)
        throw std::runtime_error("Cannot normalize a zero vector.");

    for (size_t i = 0; i < this->dim(); i++)
        (*this)[i] = (*this)[i] / cx(mag, 0);

	this->reset_values();
}

cx_vector cx_vector::cumulative_sum() const noexcept
{
    cx_vector cum_(this->dim(), cx(0, 0));
    cx sum_(0, 0);
    for (size_t i = 0; i < this->dim(); i++)
    {
        sum_ = sum_ + (*this)[i];
        cum_[i] = sum_;
    }
    
    cum_.reset_values();
    return cum_;
}

cx_vector cx_vector::conjugate() const noexcept
{
    cx_vector conj_(this->arr);
    for (size_t i = 0; i < conj_.dim(); i++)
        conj_[i] = conj_[i].conjugate();

	this->reset_values();
    return conj_;
}

cx cx_vector::dot(const cx_vector& obj) const
{
    if (this->dim() != obj.dim())
        throw std::runtime_error("Dimensions don\'t match.");

    cx prod_(0, 0);
    for (size_t i = 0; i < this->dim(); i++)
        prod_ = prod_ + ((*this)[i] * obj[i].conjugate());

    return prod_;
}

cx_vector cx_vector::cross(const cx_vector& obj) const
{
    if (this->dim() != 3 || obj.dim() != 3)
        throw std::runtime_error("Cross product is only defined in 3-Dimensional space.");

	cx_vector cross_ = {
        (*this)[1] * obj[2] - (*this)[2] * obj[1],
        (*this)[2] * obj[0] - (*this)[0] * obj[2],
        (*this)[0] * obj[1] - (*this)[1] * obj[0]
    };
    
	cross_.reset_values();
	return cross_;
}

cx_vector cx_vector::projection(const cx_vector& obj) const
{
    if (this->dim() != obj.dim())
        throw std::runtime_error("Dimensions don\'t match.");

    cx dot_product = this->dot(obj);
    cx mod_squared = obj.dot(obj);

    if (mod_squared.real == 0 && mod_squared.imag == 0)
        throw std::runtime_error("Can\'t project onto a zero vector.");

    cx scalar = dot_product / mod_squared;

    cx_vector proj_(obj.dim(), cx(0, 0));
    for (size_t i = 0; i < obj.dim(); i++)
        proj_[i] = obj[i] * scalar;

	proj_.reset_values();
    return proj_;
}


cx cx_vector::sum() const noexcept
{
    return this->__sum__;
}

cx cx_vector::mean() const noexcept
{
    return this->__mean__;
}

cx cx_vector::max() const noexcept
{
    return this->__max__;
}

cx cx_vector::min() const noexcept
{
    return this->__min__;
}