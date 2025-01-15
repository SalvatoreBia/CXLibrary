#ifndef COMPLEX_VEC_H
#define COMPLEX_VEC_H

#include <vector>
#include <cmath>
#include <stdexcept>
#include "ComplexNumber.h"

namespace cx_lib
{
    class cx_vector
    {
    private:
        std::vector<cx> arr;
        cx __sum__;
        cx __mean__;
        cx __max__;
        cx __min__;
        bool cache_valid = false;

    public:
        cx_vector() = default;
        cx_vector(const std::vector<cx>&);
        cx_vector(const cx_vector&) noexcept;
        cx_vector(cx_vector&&) noexcept = default;
        cx_vector(size_t, const cx&);

        cx_vector& operator =(const cx_vector&) noexcept;
        cx_vector operator  +(const cx_vector&) const;
        cx_vector operator  -(const cx_vector&) const;
        cx_vector operator  *(const cx&) const noexcept;
        cx_vector operator  *(float) const noexcept;
        cx& operator [](size_t index) noexcept;
        const cx& operator [](size_t index) const noexcept;
        bool operator ==(const cx_vector&) const noexcept;
        bool operator !=(const cx_vector&) const noexcept;

        const cx& at(size_t index) const;
        size_t dim() const noexcept;
        void normalize();
        float mod() const noexcept;
        cx_vector cumulative_sum() const noexcept;
        cx_vector projection(const cx_vector&) const;
        cx_vector conjugate() const noexcept;
        cx dot(const cx_vector&) const;
        cx_vector cross(const cx_vector&) const;

        cx sum() const noexcept;
        cx mean() const noexcept;
        cx max() const noexcept;
        cx min() const noexcept;

        static cx_vector null_vector(size_t);

        std::vector<cx> get() noexcept;
        
    private:
        void reset_values();
    };
}

#endif
