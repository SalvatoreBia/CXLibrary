#ifndef COMPLEX_TENSOR_H
#define COMPLEX_TENSOR_H

#include <vector>
#include <stdexcept>
#include "ComplexNumber.h"

namespace cx_lib
{
    class cx_tensor
    {
    private:
        std::vector<cx> data;
        std::vector<size_t> __shape__;
        size_t __size__ = 0;

        size_t lindex(const std::vector<size_t>&) const;
    
    public:
        cx_tensor() = default;
        cx_tensor(const std::vector<size_t>&, const cx&);
        cx_tensor(const std::vector<size_t>&, const std::vector<cx>&);

        cx& at(const std::vector<size_t>&);
        const cx& at(const std::vector<size_t>&) const;
    
        cx_tensor operator +(const cx_tensor&) const;
        cx_tensor operator -(const cx_tensor&) const;
    
        cx_tensor reshape(const std::vector<size_t>&) const;

        size_t size() const noexcept;
        const std::vector<size_t>& shape() const noexcept;
    };
}

#endif