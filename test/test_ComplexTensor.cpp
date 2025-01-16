#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "CXLibrary.h"

using namespace cx_lib;

TEST_CASE("cx_tensor constructor", "[cx_tensor]")
{
    cx_tensor t({2, 3}, cx(1, 1));
    REQUIRE(t.size() == 6);
    REQUIRE(t.shape()[0] == 2);
    REQUIRE(t.shape()[1] == 3);
    for (size_t i = 0; i < t.size(); ++i)
    {
        REQUIRE(t[i].real == 1);
        REQUIRE(t[i].imag == 1);
    }
}

TEST_CASE("cx_tensor operator + and -", "[cx_tensor]")
{
    cx_tensor t1({2, 2}, cx(1, 1));
    cx_tensor t2({2, 2}, cx(2, 2));
    auto t_add = t1 + t2;
    auto t_sub = t2 - t1;
    for (size_t i = 0; i < t1.size(); ++i)
    {
        REQUIRE(t_add[i].real == 3);
        REQUIRE(t_add[i].imag == 3);
        REQUIRE(t_sub[i].real == 1);
        REQUIRE(t_sub[i].imag == 1);
    }
}

TEST_CASE("cx_tensor reshape", "[cx_tensor]")
{
    cx_tensor t({2, 2}, cx(1, 1));
    REQUIRE_NOTHROW(t.reshape({4, 1}));
    REQUIRE(t.shape()[0] == 4);
    REQUIRE(t.shape()[1] == 1);
    REQUIRE_THROWS(t.reshape({3, 2}));
}

TEST_CASE("cx_tensor broadcast_add", "[cx_tensor]")
{
    cx_tensor t1({4}, cx(1, 1));
    cx_tensor t2({4}, cx(2, 2));
    auto t3 = t1.broadcast_add(t2);
    for (size_t i = 0; i < t1.size(); ++i)
    {
        REQUIRE(t3[i].real == 3);
        REQUIRE(t3[i].imag == 3);
    }
}

TEST_CASE("cx_tensor slice", "[cx_tensor]")
{
    cx_tensor t({4}, cx(1, 1));
    t[2] = cx(3, 3);
    t[3] = cx(4, 4);
    auto sliced = t.slice({1}, {3});
    REQUIRE(sliced.shape()[0] == 2);
    REQUIRE(sliced[0].real == 1);
    REQUIRE(sliced[0].imag == 1);
    REQUIRE(sliced[1].real == 3);
    REQUIRE(sliced[1].imag == 3);
}

TEST_CASE("cx_tensor transpose", "[cx_tensor]")
{
    cx_tensor t({2, 3}, cx(1, 0));

    for (size_t i = 0; i < t.size(); ++i)
        t[i] = cx(static_cast<float>(i), 0);

    auto axes = std::vector<size_t>{1, 0};
    auto transposed = t.transpose(axes);
    REQUIRE(transposed.shape()[0] == 3);
    REQUIRE(transposed.shape()[1] == 2);

    REQUIRE(transposed[0].real == t[0].real);
    REQUIRE(transposed[1].real == t[3].real);
    REQUIRE(transposed[2].real == t[1].real);
    REQUIRE(transposed[3].real == t[4].real);
    REQUIRE(transposed[4].real == t[2].real);
    REQUIRE(transposed[5].real == t[5].real);
}