#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "ComplexNumber.h"

TEST_CASE("ComplexNumber constructors...", "[cx]")
{
    SECTION("Default constructor")
    {
        cx a;
        REQUIRE(a.real == 0.0f);
        REQUIRE(a.imag == 0.0f);
    }

    SECTION("Constructor with only real part")
    {
        cx a(1.0f);
        REQUIRE(a.real == 1.0f);
        REQUIRE(a.imag == 0.0f);
    }

    SECTION("Constructor with real and imag parts")
    {
        cx a(1.0f, 2.0f);
        REQUIRE(a.real == 1.0f);
        REQUIRE(a.imag == 2.0f);
    }

    SECTION("Copy constructor")
    {
        cx a(1.0f, 2.0f);
        cx b(a);
        REQUIRE(b.real == 1.0f);
        REQUIRE(b.imag == 2.0f);
    }

    SECTION("Constructor with pair")
    {
        std::pair<float, float> p = std::make_pair(1.0f, 2.0f);
        cx a(p);
        REQUIRE(a.real == 1.0f);
        REQUIRE(a.imag == 2.0f);
    }
}

TEST_CASE("ComplexNumber operators...", "[cx]")
{
    cx a(3.0f, 4.0f);
    cx b(1.0f, -2.0f);

    SECTION("Assign operator")
    {
        cx c = a;
        REQUIRE(c.real == a.real);
        REQUIRE(c.imag == a.imag);
    }

    SECTION("Add operator")
    {
        cx c = a + b;
        REQUIRE(c.real == (a.real + b.real));
        REQUIRE(c.imag == (a.imag + b.imag));
    }

    SECTION("Subtract operator")
    {
        cx c = a - b;
        REQUIRE(c.real == (a.real - b.real));
        REQUIRE(c.imag == (a.imag - b.imag));
    }

    SECTION("Multiply operator")
    {
        cx c = a * b;
        REQUIRE(c.real == Approx((a.real * b.real) - (a.imag * b.imag)));
        REQUIRE(c.imag == Approx((a.real * b.imag) + (a.imag * b.real)));
    }

    SECTION("Divide operator")
    {
        cx c = a / b;
        float denominator = std::pow(b.real, 2) + std::pow(b.imag, 2);
        REQUIRE(c.real == Approx(((a.real * b.real) + (a.imag * b.imag)) / denominator));
        REQUIRE(c.imag == Approx(((a.imag * b.real) - (a.real * b.imag)) / denominator));
    }

    SECTION("Divide by zero")
    {
        cx zero(0.0f, 0.0f);
        REQUIRE_THROWS_AS(a / zero, std::runtime_error);
    }

    SECTION("Unary minus operator")
    {
        cx c = -a;
        REQUIRE(c.real == -a.real);
        REQUIRE(c.imag == -a.imag);
    }
}

TEST_CASE("ComplexNumber mathematical functions...", "[cx]")
{
    cx a(3.0f, 4.0f);
    cx b(-3.0f, -4.0f);

    SECTION("Modulus")
    {
        REQUIRE(a.mod() == Approx(5.0f));
        REQUIRE(b.mod() == Approx(5.0f));
    }

    SECTION("Square of modulus")
    {
        REQUIRE(a.mod2() == Approx(25.0f));
        REQUIRE(b.mod2() == Approx(25.0f));
    }

    SECTION("Phase")
    {
        REQUIRE(a.phase() == Approx(std::atan2(4.0f, 3.0f)));
        REQUIRE(b.phase() == Approx(std::atan2(-4.0f, -3.0f)));
    }

    SECTION("Conjugate")
    {
        cx c = a.conjugate();
        REQUIRE(c.real == a.real);
        REQUIRE(c.imag == -a.imag);
    }

    SECTION("Power")
    {
        cx c = a.pow(2);
        REQUIRE(c.real == Approx(-7.0f));  
        REQUIRE(c.imag == Approx(24.0f));
    }

    SECTION("Square root")
    {
        cx c = a.sqrt();
        REQUIRE(c.real == Approx(2.0f)); 
        REQUIRE(c.imag == Approx(1.0f)); 
    }
}

TEST_CASE("ComplexNumber conversions...", "[cx]")
{
    cx a(3.0f, 4.0f);

    SECTION("To polar coordinates")
    {
        auto polar = a.to_polar();
        REQUIRE(polar.first == Approx(5.0f)); 
        REQUIRE(polar.second == Approx(std::atan2(4.0f, 3.0f))); 
    }

    SECTION("From pair")
    {
        std::pair<float, float> p = std::make_pair(1.0f, -1.0f);
        cx c = cx::from_pair(p);
        REQUIRE(c.real == 1.0f);
        REQUIRE(c.imag == -1.0f);
    }

    SECTION("Explicit conversion to pair")
    {
        std::pair<float, float> p = static_cast<std::pair<float, float>>(a);
        REQUIRE(p.first == a.real);
        REQUIRE(p.second == a.imag);
    }
}

TEST_CASE("ComplexNumber comparison operators...", "[cx]")
{
    cx a(3.0f, 4.0f);
    cx b(3.0f, 4.0f);
    cx c(1.0f, -2.0f);

    SECTION("Equality operator")
    {
        REQUIRE(a == b);
        REQUIRE(!(a == c));
    }

    SECTION("Inequality operator")
    {
        REQUIRE(a != c);
        REQUIRE(!(a != b));
    }
}

TEST_CASE("ComplexNumber stream operator...", "[cx]")
{
    cx a(3.0f, 4.0f);
    cx b(3.0f, -4.0f);
    cx c(3.0f, 0.0f);

    SECTION("Positive imaginary part")
    {
        std::ostringstream os;
        os << a;
        REQUIRE(os.str() == "3+4i");
    }

    SECTION("Negative imaginary part")
    {
        std::ostringstream os;
        os << b;
        REQUIRE(os.str() == "3-4i");
    }

    SECTION("No imaginary part")
    {
        std::ostringstream os;
        os << c;
        REQUIRE(os.str() == "3");
    }
}

TEST_CASE("ComplexNumber initialization from string...", "[cx]")
{
    SECTION("Constructor from string - valid strings") {
        cx a = cx::from_string("3+4i");
        REQUIRE(a.real == Approx(3.0f));
        REQUIRE(a.imag == Approx(4.0f));

        cx b = cx::from_string("-2-3i");
        REQUIRE(b.real == Approx(-2.0f));
        REQUIRE(b.imag == Approx(-3.0f));

        cx c = cx::from_string("5");
        REQUIRE(c.real == Approx(5.0f));
        REQUIRE(c.imag == Approx(0.0f));

        cx d = cx::from_string("i");
        REQUIRE(d.real == Approx(0.0f));
        REQUIRE(d.imag == Approx(1.0f));

        cx e = cx::from_string("-4i");
        REQUIRE(e.real == Approx(0.0f));
        REQUIRE(e.imag == Approx(-4.0f));

        cx f = cx::from_string("-3.5+2.5i");
        REQUIRE(f.real == Approx(-3.5f));
        REQUIRE(f.imag == Approx(2.5f));
    }

    SECTION("Constructor from string - invalid strings") {
        REQUIRE_THROWS(cx::from_string(""));
        REQUIRE_THROWS(cx::from_string("abc"));     
        REQUIRE_THROWS(cx::from_string("1 + i"));   
        REQUIRE_THROWS(cx::from_string("1+i2"));    
        REQUIRE_THROWS(cx::from_string("++3-2i"));  
    }
}