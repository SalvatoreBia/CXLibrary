#include <cmath>
#include "ComplexNumber.h"

namespace cx_lib
{
    cx::cx(const cx &obj) noexcept : real(obj.real), imag(obj.imag) {}

    cx::operator std::pair<float, float>() const noexcept
    {
        return {real, imag};
    }

    cx cx::operator+(const cx &obj) const noexcept
    {
        return cx(real + obj.real, imag + obj.imag);
    }

    cx cx::operator-(const cx &obj) const noexcept
    {
        return cx(real - obj.real, imag - obj.imag);
    }

    cx cx::operator*(const cx &obj) const noexcept
    {
        return cx(
            (real * obj.real) - (imag * obj.imag),
            (real * obj.imag) + (imag * obj.real));
    }

    cx cx::operator/(const cx &obj) const
    {
        if (obj.real == 0 && obj.imag == 0)
            throw std::runtime_error("Division by zero.");

        float denominator = std::pow(obj.real, 2) + std::pow(obj.imag, 2);
        return cx(
            (float)((real * obj.real) + (imag * obj.imag)) / denominator,
            (float)((imag * obj.real) - (real * obj.imag)) / denominator);
    }

    std::ostream &operator<<(std::ostream &os, const cx &obj)
    {
        os << obj.real;

        if (obj.imag != 0)
        {
            if (obj.imag > 0)
                os << "+";
            if (obj.imag == 1 || obj.imag == -1)
                os << ((obj.imag == -1) ? "-" : "") << "i";
            else
                os << obj.imag << "i";
        }
        return os;
    }

    float cx::mod() const noexcept
    {
        return std::sqrt(std::pow(real, 2) + std::pow(imag, 2));
    }

    float cx::mod2() const noexcept
    {
        return std::pow(real, 2) + std::pow(imag, 2);
    }

    float cx::phase() const noexcept
    {
        return std::atan2(imag, real);
    }

    cx cx::conjugate() const noexcept
    {
        return cx(real, -imag);
    }

    bool cx::operator==(const cx &obj) const noexcept
    {
        return real == obj.real && imag == obj.imag;
    }

    bool cx::operator!=(const cx &obj) const noexcept
    {
        return real != obj.real || imag != obj.imag;
    }

    cx cx::operator-() const noexcept
    {
        return cx(-real, -imag);
    }

    cx cx::pow(int n) const noexcept
    {
        float mag = std::pow(mod(), n);
        float ph = n * phase();
        return cx(
            mag * std::cos(ph),
            mag * std::sin(ph));
    }

    cx cx::sqrt() const noexcept
    {
        float mag = std::sqrt(mod());
        float ph = (float)phase() / 2;
        return cx(
            mag * std::cos(ph),
            mag * std::sin(ph));
    }

    cx cx::from_pair(const std::pair<float, float> &p) noexcept
    {
        return cx(p.first, p.second);
    }

    static std::string trim(const std::string &s)
    {
        auto start = s.find_first_not_of(" \t\n\r\f\v");
        if (start == std::string::npos)
            return "";

        auto end = s.find_last_not_of(" \t\n\r\f\v");
        return s.substr(start, (end - start + 1));
    }

    cx cx::from_string(const std::string& input)
    {
        std::string str = trim(input);
        if (str.empty())
            throw std::invalid_argument("Can't parse an empty or all-whitespace string.");
        
        std::size_t splitPos = std::string::npos;
        for (std::size_t i = 1; i < str.size(); ++i) {
            if (str[i] == '+' || str[i] == '-') {
                splitPos = i;
                break; 
            }
        }

        float r  = 0.0;
        float im = 0.0;

        if (splitPos == std::string::npos)
        {
            if (!str.empty() && str.back() == 'i')
            {
                std::string body = str.substr(0, str.size() - 1);

                if (body.empty() || body == "+")
                    im = 1.0;
                else if (body == "-")
                    im = -1.0;
                else
                    im = std::stod(body);
                
                r = 0.0;
            }
            else
            {
                r = std::stod(str);
                im = 0.0;
            }
        }
        else
        {
            std::string real_str = str.substr(0, splitPos);
            std::string imag_str = str.substr(splitPos);

            if (imag_str.empty() || imag_str.back() != 'i')
                throw std::invalid_argument("Invalid complex number format (imag part must end with 'i').");

            imag_str.pop_back();

            if (imag_str == "+" || imag_str == "-")
                im = (imag_str == "+") ? 1.0 : -1.0;
            else
                im = std::stod(imag_str);

            r = std::stod(real_str);
        }

        return cx(r, im);
    }

    std::pair<float, float> cx::to_polar() const noexcept
    {
        return {mod(), phase()};
    }
}
