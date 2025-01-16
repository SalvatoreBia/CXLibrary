#ifndef COMPLEX_NUMBER_H
#define COMPLEX_NUMBER_H

#include <ostream>
#include <utility>
#include <stdexcept>
#include <string>

namespace cx_lib
{
    /**
     * @brief Complex number struct representing numbers in the form a + bi
     * 
     * Provides basic complex number operations including:
     * - Arithmetic operations (+, -, *, /)
     * - Conversion to/from polar form
     * - Common complex functions (e.g. pow, modulus, conjugate)
     * - String parsing and formatting
     */
    struct cx
    {
        float real;  ///< Real part of the complex number
        float imag;  ///< Imaginary part of the complex number
        
        /** @brief Default constructor initializing to 0 + 0i */
        cx()  = default;
        /** @brief Default destructor */
        ~cx() = default;
        /** @brief Construct from real part, imaginary part set to 0 
         * @param r Real part value
         */
        explicit cx(float r): real(r), imag(0) { }
        /** @brief Construct from real and imaginary parts
         * @param r Real part value
         * @param i Imaginary part value
         */
        explicit cx(float r, float i): real(r), imag(i) { }
        /** @brief Copy constructor 
         * @param obj Complex number to copy
         */
        cx(const cx&) noexcept;
        /** @brief Construct from pair (real, imaginary)
         * @param p Pair containing (real, imaginary) parts
         */
        explicit cx(const std::pair<float, float>& p): real(p.first), imag(p.second) { }

        /** @brief Convert to std::pair(real, imaginary) */
        explicit operator std::pair<float, float>() const noexcept;    
        /** @brief Assignment operator */
        cx& operator =(const cx&) noexcept = default;
        /** @brief Addition operator */
        cx operator +(const cx&) const noexcept;
        /** @brief Addition assignment operator */
        cx& operator +=(const cx&) noexcept;
        /** @brief Subtraction operator */
        cx operator -(const cx&) const noexcept;
        /** @brief Subtraction assignment operator */
        cx& operator -=(const cx&) noexcept;
        /** @brief Multiplication operator */
        cx operator *(const cx&) const noexcept;
        /** @brief Multiplication assignment operator */
        cx& operator *=(const cx&) noexcept;
        /** @brief Division operator
         * @throws std::runtime_error if dividing by zero
         */
        cx operator /(const cx&) const;
        /** @brief Division assignment operator
         * @throws std::runtime_error if dividing by zero
         */
        cx& operator /=(const cx&);
        /** @brief Stream output operator */
        friend std::ostream& operator <<(std::ostream&, const cx&);
        /** @brief Equality comparison operator */
        bool operator ==(const cx&) const noexcept;
        /** @brief Inequality comparison operator */
        bool operator !=(const cx&) const noexcept;
        /** @brief Unary minus operator */
        cx operator -() const noexcept;
        
        /** @brief Calculate modulus (magnitude) */
        float mod() const noexcept;
        /** @brief Calculate squared modulus */
        float mod2() const noexcept;
        /** @brief Calculate phase angle in radians */
        float phase() const noexcept;
        /** @brief Get complex conjugate */
        cx conjugate() const noexcept;
        /** @brief Raise to integer power
         * @param n Power to raise to
         */
        cx pow(int) const noexcept;
        /** @brief Calculate square root */
        cx sqrt() const noexcept;
        
        /** @brief Create from pair (real, imaginary)
         * @param p Pair containing (real, imaginary) parts
         */
        static cx from_pair(const std::pair<float, float>&) noexcept;
        /** @brief Parse from string in format "a+bi"
         * @param str String to parse
         * @throws std::invalid_argument if string format is invalid
         */
        static cx from_string(const std::string&);
        /** @brief Convert to polar form (r, θ)
         * @return Pair containing (modulus, phase in radians)
         */
        std::pair<float, float> to_polar() const noexcept;
    };
}

#endif