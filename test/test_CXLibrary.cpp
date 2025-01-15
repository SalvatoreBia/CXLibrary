#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "CXLibrary.h"

using namespace cx_lib;

TEST_CASE("matmul(cx_matrix, cx_matrix)...") {
    cx_matrix A = cx_matrix::get_identity(2);
    std::vector<std::vector<cx>> dataB = {
        {cx(1,0), cx(2,0)},
        {cx(3,0), cx(4,0)}
    };
    cx_matrix B(dataB);
    cx_matrix C = cx_lib::matmul(A, B);
    REQUIRE(C.rows() == 2);
    REQUIRE(C.cols() == 2);
    REQUIRE(C(0,0) == cx(1,0));
    REQUIRE(C(0,1) == cx(2,0));
    REQUIRE(C(1,0) == cx(3,0));
    REQUIRE(C(1,1) == cx(4,0));
    cx_matrix D(3,2,cx(0,0));
    REQUIRE_THROWS(cx_lib::matmul(B,D));
}

TEST_CASE("matmul(cx_matrix, cx_vector)...") {
    std::vector<std::vector<cx>> dataA = {
        {cx(1,0), cx(2,0)},
        {cx(3,0), cx(4,0)}
    };
    cx_matrix A(dataA);
    cx_vector v(std::vector<cx>{cx(5,0), cx(6,0)});
    cx_vector r = cx_lib::matmul(A, v);
    REQUIRE(r.dim() == 2);
    REQUIRE(r[0] == cx(17,0));
    REQUIRE(r[1] == cx(39,0));
    cx_vector wrongDim(3, cx(1,0));
    REQUIRE_THROWS(cx_lib::matmul(A,wrongDim));
}

TEST_CASE("matmul(cx_vector, cx_matrix)...") {
    std::vector<std::vector<cx>> dataB = {
        {cx(1,0), cx(2,0)},
        {cx(3,0), cx(4,0)}
    };
    cx_matrix B(dataB);
    cx_vector v(std::vector<cx>{cx(5,0), cx(6,0)});
    cx_vector r = cx_lib::matmul(v, B);
    REQUIRE(r.dim() == 2);
    REQUIRE(r[0] == cx(23,0));
    REQUIRE(r[1] == cx(34,0));
    cx_vector wrongDim(3, cx(1,0));
    REQUIRE_THROWS(cx_lib::matmul(wrongDim,B));
}

TEST_CASE("hadamard_vprod...") {
    cx_vector a(std::vector<cx>{cx(1,1), cx(2,2)});
    cx_vector b(std::vector<cx>{cx(3,0), cx(1,2)});
    cx_vector r = cx_lib::hadamard_vprod(a,b);
    REQUIRE(r.dim() == 2);
    REQUIRE(r[0] == cx(3,0) * cx(1,1)); 
    REQUIRE(r[1] == cx(2,2) * cx(1,2));
    cx_vector c(std::vector<cx>{cx(1,0), cx(2,0), cx(3,0)});
    REQUIRE_THROWS(cx_lib::hadamard_vprod(a,c));
}

TEST_CASE("hadamard_prod...") {
    std::vector<std::vector<cx>> dataA = {
        {cx(1,1), cx(2,2)},
        {cx(3,3), cx(4,4)}
    };
    std::vector<std::vector<cx>> dataB = {
        {cx(1,0), cx(0,1)},
        {cx(2,2), cx(1,1)}
    };
    cx_matrix A(dataA);
    cx_matrix B(dataB);
    cx_matrix R = cx_lib::hadamard_prod(A,B);
    REQUIRE(R.rows() == 2);
    REQUIRE(R.cols() == 2);
    REQUIRE(R(0,0) == cx(1,1)*cx(1,0));
    REQUIRE(R(0,1) == cx(2,2)*cx(0,1));
    REQUIRE(R(1,0) == cx(3,3)*cx(2,2));
    REQUIRE(R(1,1) == cx(4,4)*cx(1,1));
    cx_matrix C(2,3,cx(1,0));
    REQUIRE_THROWS(cx_lib::hadamard_prod(A,C));
}

TEST_CASE("tensor_prod...") {
    cx_vector a(std::vector<cx>{cx(1,0), cx(0,1)});
    cx_vector b(std::vector<cx>{cx(2,2), cx(3,3)});
    cx_vector r = cx_lib::tensor_prod(a,b);
    REQUIRE(r.dim() == 4);
    REQUIRE(r[0] == cx(1,0)*cx(2,2));
    REQUIRE(r[1] == cx(1,0)*cx(3,3));
    REQUIRE(r[2] == cx(0,1)*cx(2,2));
    REQUIRE(r[3] == cx(0,1)*cx(3,3));
}
