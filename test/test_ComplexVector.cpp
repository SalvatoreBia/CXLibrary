#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "CXLibrary.h"

using namespace cx_lib;

TEST_CASE("ComplexVector constructors...", "[cx_vector]") {
    SECTION("Default constructor") {
        cx_vector v(2, cx(0, 0));
        REQUIRE(v.dim() == 2);
        REQUIRE(v.sum() == cx(0, 0));
    }

    SECTION("Constructor with std::vector<cx>") {
        std::vector<cx> data = {cx(1, 2), cx(3, 4)};
        cx_vector v(data);
        REQUIRE(v.dim() == 2);
        REQUIRE(v[0] == cx(1, 2));
        REQUIRE(v[1] == cx(3, 4));
    }

    SECTION("Constructor with size and initial value") {
        cx_vector v(3, cx(1, -1));
        REQUIRE(v.dim() == 3);
        REQUIRE(v[0] == cx(1, -1));
        REQUIRE(v[1] == cx(1, -1));
        REQUIRE(v[2] == cx(1, -1));
    }

    SECTION("Copy constructor") {
        cx_vector original(3, cx(2, 3));
        cx_vector copy(original);
        REQUIRE(copy.dim() == original.dim());
        REQUIRE(copy == original);
    }
}

TEST_CASE("ComplexVector operators...", "[cx_vector]") {
    cx_vector v1(3, cx(1, 1));
    cx_vector v2(3, cx(2, -1));

    SECTION("Addition operator") {
        cx_vector result = v1 + v2;
        REQUIRE(result[0] == cx(3, 0));
        REQUIRE(result[1] == cx(3, 0));
        REQUIRE(result[2] == cx(3, 0));
    }

    SECTION("Subtraction operator") {
        cx_vector result = v1 - v2;
        REQUIRE(result[0] == cx(-1, 2));
        REQUIRE(result[1] == cx(-1, 2));
        REQUIRE(result[2] == cx(-1, 2));
    }

    SECTION("Scalar multiplication") {
        cx_vector result = v1 * cx(2, 0);
        REQUIRE(result[0] == cx(2, 2));
        REQUIRE(result[1] == cx(2, 2));
        REQUIRE(result[2] == cx(2, 2));
    }

    SECTION("Equality operator") {
        cx_vector v3(3, cx(1, 1));
        REQUIRE(v1 == v3);
        REQUIRE(v1 != v2);
    }
}

TEST_CASE("ComplexVector methods...", "[cx_vector]") {
    cx_vector v(3, cx(1, 1));

    SECTION("Dimension") {
        REQUIRE(v.dim() == 3);
    }

    SECTION("Modulus") {
        REQUIRE(v.mod() == Approx(std::sqrt(6.0f)));
    }

    SECTION("Normalize") {
        v.normalize();
        REQUIRE(v.mod() == Approx(1.0f));
    }

    SECTION("Cumulative sum") {
        std::vector<cx> data = {cx(1, 1), cx(2, 2), cx(3, 3)};
        cx_vector v(data);
        cx_vector result = v.cumulative_sum();

        REQUIRE(result[0] == cx(1, 1));
        REQUIRE(result[1] == cx(3, 3));
        REQUIRE(result[2] == cx(6, 6));
    }

    SECTION("Dot product") {
        std::vector<cx> data1 = {cx(1, 1), cx(2, 2)};
        std::vector<cx> data2 = {cx(3, -1), cx(1, -2)};

        cx_vector v1(data1);
        cx_vector v2(data2);

        cx dot_result = v1.dot(v2);
        REQUIRE(dot_result == cx(0, 10));
    }

    SECTION("Projection") {
        std::vector<cx> data1 = {cx(1, 2), cx(2, 3)};
        std::vector<cx> data2 = {cx(1, 0), cx(0, 1)};

        cx_vector v1(data1);
        cx_vector v2(data2);

        cx_vector projection = v1.projection(v2);
        REQUIRE(projection.dim() == 2);
    }

    SECTION("Conjugate") {
        cx_vector conjugated = v.conjugate();
        REQUIRE(conjugated[0] == cx(1, -1));
        REQUIRE(conjugated[1] == cx(1, -1));
        REQUIRE(conjugated[2] == cx(1, -1));
    }

    SECTION("Null vector") {
        cx_vector null_vec = cx_vector::null_vector(3);
        REQUIRE(null_vec.dim() == 3);
        REQUIRE(null_vec[0] == cx(0, 0));
    }
}
