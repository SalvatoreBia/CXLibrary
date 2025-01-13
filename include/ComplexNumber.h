#ifndef COMPLEX_NUMBER_H
#define COMPLEX_NUMBER_H

#include <ostream>
#include <utility>
#include <stdexcept>


struct cx
{
	float real;
	float imag;
	
	cx()  = default;
	~cx() = default;
	explicit cx(float r): real(r), imag(0) { }
	explicit cx(float r, float i): real(r), imag(i) { }
	cx(const cx&) noexcept;
	explicit cx(const std::pair<float, float>& p): real(p.first), imag(p.second) { }

	explicit operator std::pair<float, float>() const noexcept;	
	cx& operator =(const cx&) noexcept = default;
	cx operator +(const cx&)  const noexcept;
	cx operator -(const cx&)  const noexcept;
	cx operator *(const cx&)  const noexcept;
	cx operator /(const cx&)  const;
	friend std::ostream& operator <<(std::ostream&, const cx&);
	bool operator ==(const cx&) const noexcept;
	bool operator !=(const cx&) const noexcept;
	cx operator -() const noexcept;
	
	float mod()    const noexcept;
	float mod2()   const noexcept;
	float phase()  const noexcept;
	cx conjugate() const noexcept;
	cx pow(int)    const noexcept;
	cx sqrt()	   const noexcept;
	
	static cx from_pair(const std::pair<float, float>&) noexcept;
	std::pair<float, float> to_polar() const noexcept;
};


#endif
