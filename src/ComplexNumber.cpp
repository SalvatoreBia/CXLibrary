#include <cmath>
#include "ComplexNumber.h"

	
cx::cx(const cx& obj): real(obj.real), imag(obj.imag) { }

explicit cx::operator std::pair<float, float>() const noexcept
{
    return {real, imag};
}

cx::operator +(const cx& obj) const noexcept
{
	return cx(real + obj.real, imag + obj.imag);
}

cx::operator -(const cx& obj) const noexcept
{
	return cx(real - obj.real, imag - obj.imag);
}

cx::operator *(const cx& obj) const noexcept
{
	return cx(
		(real * obj.real) - (imag * obj.imag),
		(real * obj.imag) + (imag * obj.real) 
	);
}

cx::operator /(const cx& obj) const
{
	if (obj.real == 0 && obj.imag == 0)
		throw std::runtime_error("Division by zero.");
	
	float denominator = std::pow(obj.real, 2) + std::pow(obj.imag, 2);
	return cx(
		(float)((real * obj.real) + (imag * obj.imag)) / denominator,
		(float)((imag * obj.real) - (real * obj.imag)) / denominator
	);
}

std::ostream& operator <<(std::ostream& os, const cx& obj) 
{
    os << obj.real;

    if (obj.imag != 0) 
	{
        if (obj.imag > 0) os << "+";
        if (obj.imag == 1 || obj.imag == -1)
            os << ((obj.imag == -1) ? "-" : "") << "i";
        else
            os << obj.imag << "i";
    }
    return os;
}

float cx::mod() const noexcept
{
	return std::sqrt(std::pow(real, 2) * std::pow(imag, 2));
}

float cx::mod2() const noexcept
{
	return std::pow(real, 2) * std::pow(imag, 2);
}

float cx::phase() const noexcept
{
	return std::atan2(imag, real);
}

cx cx::conjugate() const noexcept
{
	return cx(real, -imag);
}

bool cx::operator ==(const cx& obj) const noexcept
{
	return real == obj.real && imag == obj.imag;
}

bool cx::operator !=(const cx& obj) const noexcept
{
	return real != obj.real || imag != obj.imag;
}

cx cx::operator -() const noexcept
{
	return cx(-real, -imag);
}

cx cx::pow(int n) const noexcept
{
	float mag = std::pow(mod(), n);
	float ph  = n * phase();
	return cx(
		mag * std::cos(ph),
		mag * std::sin(ph)	
	);
}

cx cx::sqrt() const noexcept
{
	float mag = std::sqrt(mod());
	float ph  = (float)phase() / 2;
	return cx(
		mag * std::cos(ph),
		mag * std::sin(ph)
	);
}

cx cx::from_pair(const std::pair<float, float>& p) noexcept
{
	return cx(p.first, p.second);
}

std::pair<float, float> cx::to_polar() const noexcept
{
	return {mod(), phase()};
}

