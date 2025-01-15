#include "ComplexTensor.h"

namespace cx_lib
{
    cx_tensor::cx_tensor(const std::vector<size_t>& __shape, const cx& val)
        : __shape__(__shape)
    {
        this->__size__ = 1;
        for (size_t dim : __shape)
            this->__size__ *= dim;

        this->data = std::vector<cx>(this->__size__, val);
    }

    size_t cx_tensor::lindex(const std::vector<size_t>& __indices) const
    {
        if (__indices.size() != this->__shape__.size())
            throw std::invalid_argument("Index dimensionality mismatch.");

        size_t idx = 0;
        size_t stride = 1;
        for (size_t i = 0; i < this->__shape__.size(); i++)
        {
            idx += __indices[this->__shape__.size() - i - 1] * stride;
            stride *= this->__shape__[this->__shape__.size() - i - 1];
        }

        return idx;
    }

    cx& cx_tensor::at(const std::vector<size_t>& __indices)
    {
        return this->data[lindex(__indices)];
    }

    const cx& cx_tensor::at(const std::vector<size_t>& __indices) const
    {
        return this->data[lindex(__indices)];
    }
}