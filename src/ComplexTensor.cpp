#include "ComplexTensor.h"

namespace cx_lib
{
    cx_tensor::cx_tensor(const std::vector<size_t>& __shape, const cx& val)
        : data(__shape.size() ? std::vector<cx>(std::accumulate(__shape.begin(), __shape.end(), 1, std::multiplies<size_t>()), val) : std::vector<cx>()),
          __shape__(__shape),
          __size__(std::accumulate(__shape.begin(), __shape.end(), 1, std::multiplies<size_t>()))
    {
        if (__shape.empty())
            throw std::invalid_argument("Shape cannot be empty.");
    }

    cx_tensor::cx_tensor(const std::vector<size_t>& __shape, const std::vector<cx> &data)
        : data(data),
          __shape__(__shape),
          __size__(std::accumulate(__shape.begin(), __shape.end(), 1, std::multiplies<size_t>()))
    {
        if (__shape.empty())
            throw std::invalid_argument("Shape cannot be empty.");
        if (data.size() != __size__)
            throw std::invalid_argument("Data size does not match shape dimensions.");
    }

    size_t cx_tensor::size() const noexcept
    {
        return this->__size__;
    }

    const std::vector<size_t> &cx_tensor::shape() const noexcept
    {
        return this->__shape__;
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

    cx &cx_tensor::operator[](size_t __indices) noexcept
    {
        return this->data[__indices];
    }

    const cx &cx_tensor::operator[](size_t __indices) const noexcept
    {
        return this->data[__indices];
    }

    cx &cx_tensor::at(const std::vector<size_t>& __indices)
    {
        return this->data[lindex(__indices)];
    }

    const cx &cx_tensor::at(const std::vector<size_t> &__indices) const
    {
        return this->data[lindex(__indices)];
    }

    cx_tensor cx_tensor::operator+(const cx_tensor& obj) const
    {
        if (this->shape() != obj.shape())
            throw std::invalid_argument("Dimensions mismatch between tensors.");

        cx_tensor new_(this->shape(), cx(0, 0));

        if (cx_lib::__cx_multithread_enabled__)
        {
            if (this->size() == 0)
                return new_;

            const size_t min_chunk_size = 1000;
            size_t max_threads = std::thread::hardware_concurrency();
            size_t needed_threads = (this->size() + min_chunk_size - 1) / min_chunk_size;
            size_t num_threads = std::min(max_threads, needed_threads);

            if (num_threads <= 1)
            {
                for (size_t i = 0; i < this->size(); i++)
                    new_[i] = (*this)[i] + obj[i];
                return new_;
            }

            size_t chunk_size = this->size() / num_threads;
            std::vector<std::thread> threads;
            threads.reserve(num_threads);

            for (size_t t = 0; t < num_threads; ++t)
            {
                threads.emplace_back([&, t]()
                                     {
                                        size_t start = t * chunk_size;
                                        size_t end = (t == num_threads - 1) ? this->size() : (t + 1) * chunk_size;
                                        for (size_t i = start; i < end; ++i)
                                            new_[i] = (*this)[i] + obj[i]; 
                                     });
            }

            for (auto &thr : threads)
                thr.join();
        }
        else
        {
            for (size_t i = 0; i < this->size(); i++)
                new_[i] = (*this)[i] + obj[i];
        }

        return new_;
    }

    cx_tensor cx_tensor::operator-(const cx_tensor& obj) const
    {
        if (this->shape() != obj.shape())
            throw std::invalid_argument("Dimensions mismatch between tensors.");

        cx_tensor new_(this->shape(), cx(0, 0));

        if (cx_lib::__cx_multithread_enabled__)
        {
            if (this->size() == 0)
                return new_;

            const size_t min_chunk_size = 1000;
            size_t max_threads = std::thread::hardware_concurrency();
            size_t needed_threads = (this->size() + min_chunk_size - 1) / min_chunk_size;
            size_t num_threads = std::min(max_threads, needed_threads);

            if (num_threads <= 1)
            {
                for (size_t i = 0; i < this->size(); i++)
                    new_[i] = (*this)[i] + obj[i];
                return new_;
            }

            size_t chunk_size = this->size() / num_threads;
            std::vector<std::thread> threads;
            threads.reserve(num_threads);

            for (size_t t = 0; t < num_threads; ++t)
            {
                threads.emplace_back([&, t]()
                                     {
                                        size_t start = t * chunk_size;
                                        size_t end = (t == num_threads - 1) ? this->size() : (t + 1) * chunk_size;
                                        for (size_t i = start; i < end; ++i)
                                            new_[i] = (*this)[i] - obj[i]; 
                                     });
            }

            for (auto &thr : threads)
                thr.join();
        }
        else
        {
            for (size_t i = 0; i < this->size(); i++)
                new_[i] = (*this)[i] - obj[i];
        }

        return new_;
    }

    cx_tensor &cx_tensor::reshape(const std::vector<size_t>& __shape)
    {
        size_t new_size = 1;
        for (size_t dim : __shape)
        {
            if (dim == 0)
                throw std::invalid_argument("Invalid shape: dimensions must be greater than zero.");
            new_size *= dim;
        }

        if (new_size != this->size())
            throw std::invalid_argument("Invalid shape: total number of elements does not match.");

        this->__shape__ = __shape;
        return *this;
    }

    cx_tensor cx_tensor::broadcast_add(const cx_tensor& obj) const
    {
        if (this->__shape__.size() < obj.__shape__.size())
            throw std::invalid_argument("Cannot broadcast: dimensions mismatch.");

        cx_tensor new_ = *this;

        if (cx_lib::__cx_multithread_enabled__)
        {
            size_t num_threads = std::thread::hardware_concurrency();
            std::vector<std::mutex> mutexes(this->__size__);
            std::vector<std::thread> threads;
            threads.reserve(num_threads);

            size_t chunk_size = obj.size() / num_threads;

            for (size_t t = 0; t < num_threads; ++t)
            {
                threads.emplace_back([&, t]()
                                     {
                size_t start = t * chunk_size;
                size_t end = (t == num_threads - 1) ? obj.size() : (t + 1) * chunk_size;

                for (size_t i = start; i < end; ++i)
                {
                    size_t target_idx = i % this->__size__;
                    std::lock_guard<std::mutex> lock(mutexes[target_idx]);
                    new_[target_idx] = new_[target_idx] + obj[i];
                } });
            }

            for (auto &thr : threads)
                thr.join();
        }
        else
        {
            for (size_t i = 0; i < obj.size(); i++)
                new_[i % this->__size__] = new_[i % this->__size__] + obj[i];
        }

        return new_;
    }

    cx_tensor cx_tensor::slice(const std::vector<size_t>& start, const std::vector<size_t>& end) const
    {
        if (start.size() != end.size() || start.size() != this->__shape__.size())
            throw std::invalid_argument("Start and end dimensions must match tensor shape.");

        for (size_t i = 0; i < start.size(); i++)
            if (start[i] >= end[i] || end[i] > this->__shape__[i])
                throw std::invalid_argument("Invalid slicing range.");

        std::vector<size_t> new_shape;
        for (size_t i = 0; i < start.size(); i++)
            new_shape.push_back(end[i] - start[i]);

        std::vector<cx> sliced_data;
        for (size_t i = start[0]; i < end[0]; i++)
            sliced_data.push_back(this->data[i]);

        return cx_tensor(new_shape, sliced_data);
    }

    cx_tensor cx_tensor::transpose(const std::vector<size_t>& axes) const
    {
        if (axes.size() != this->__shape__.size())
            throw std::invalid_argument("Axes size must match tensor dimensions.");

        std::vector<size_t> new_shape(this->__shape__.size());
        for (size_t i = 0; i < axes.size(); ++i)
        {
            if (axes[i] >= this->__shape__.size())
                throw std::invalid_argument("Invalid axis for transpose.");
            new_shape[i] = this->__shape__[axes[i]];
        }

        cx_tensor result(new_shape, cx(0, 0));

        std::vector<size_t> old_strides(this->__shape__.size(), 1);
        for (int i = this->__shape__.size() - 2; i >= 0; --i)
            old_strides[i] = old_strides[i + 1] * this->__shape__[i + 1];

        std::vector<size_t> new_strides(new_shape.size(), 1);
        for (int i = new_shape.size() - 2; i >= 0; --i)
            new_strides[i] = new_strides[i + 1] * new_shape[i + 1];

        if (cx_lib::__cx_multithread_enabled__)
        {
            size_t num_threads = std::thread::hardware_concurrency();
            size_t chunk_size = this->__size__ / num_threads;
            std::vector<std::thread> threads;
            threads.reserve(num_threads);

            for (size_t t = 0; t < num_threads; ++t)
            {
                threads.emplace_back([&, t]()
                                     {
                size_t start = t * chunk_size;
                size_t end = (t == num_threads - 1)? this->__size__ : (t + 1) * chunk_size;

                for (size_t i = start; i < end; ++i)
                {
                    std::vector<size_t> old_indices(this->__shape__.size(), 0);
                    size_t temp = i;
                    for (size_t j = 0; j < this->__shape__.size(); ++j)
                    {
                        old_indices[j] = temp / old_strides[j];
                        temp %= old_strides[j];
                    }

                    size_t new_index = 0;
                    for (size_t j = 0; j < axes.size(); ++j)
                        new_index += old_indices[axes[j]] * new_strides[j];

                    result[new_index] = this->data[i];
                } });
            }

            for (auto &thr : threads)
                thr.join();
        }
        else
        {
            for (size_t i = 0; i < this->__size__; ++i)
            {
                std::vector<size_t> old_indices(this->__shape__.size(), 0);
                size_t temp = i;
                for (size_t j = 0; j < this->__shape__.size(); ++j)
                {
                    old_indices[j] = temp / old_strides[j];
                    temp %= old_strides[j];
                }

                size_t new_index = 0;
                for (size_t j = 0; j < axes.size(); ++j)
                    new_index += old_indices[axes[j]] * new_strides[j];

                result[new_index] = this->data[i];
            }
        }

        return result;
    }

}