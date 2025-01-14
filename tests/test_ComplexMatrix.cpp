#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "ComplexMatrix.h"

TEST_CASE("cx_matrix Constructors...", "[cx_matrix]") {

    SECTION("Constructor (rows, cols, cx)") {
        cx_matrix m(2, 3, cx(1, -1));
        REQUIRE(m.rows() == 2);
        REQUIRE(m.cols() == 3);
        for (size_t r = 0; r < 2; r++) {
            for (size_t c = 0; c < 3; c++) {
                REQUIRE(m(r, c) == cx(1, -1));
            }
        }
    }

    SECTION("Constructor from std::vector<std::vector<cx>>") {
        std::vector<std::vector<cx>> data = {
            {cx(1,1), cx(2,2), cx(3,3)},
            {cx(4,4), cx(5,5), cx(6,6)}
        };
        cx_matrix m(data);
        REQUIRE(m.rows() == 2);
        REQUIRE(m.cols() == 3);
        REQUIRE(m(0,0) == cx(1,1));
        REQUIRE(m(1,2) == cx(6,6));
    }

    SECTION("Constructor from std::vector<cx_vector>") {
        std::vector<cx_vector> data;
        data.push_back(cx_vector({cx(1,0), cx(2,0)}));
        data.push_back(cx_vector({cx(3,1), cx(4,2)}));

        cx_matrix m(data);
        REQUIRE(m.rows() == 2);
        REQUIRE(m.cols() == 2);
        REQUIRE(m(0,0) == cx(1,0));
        REQUIRE(m(1,1) == cx(4,2));
    }

    SECTION("Copy constructor") {
        cx_matrix original(2, 2, cx(1, 1));
        cx_matrix copy(original);
        REQUIRE(copy.rows() == 2);
        REQUIRE(copy.cols() == 2);
        REQUIRE(copy(0,0) == cx(1,1));
        REQUIRE(original == copy);
    }

    SECTION("Invalid size throws") {
        REQUIRE_THROWS(cx_matrix(1, 3, cx(0,0)));
        REQUIRE_THROWS(cx_matrix(2, 1, cx(0,0)));

        std::vector<std::vector<cx>> badData = {{cx(1,1)}};
        REQUIRE_THROWS(cx_matrix(badData));

        std::vector<std::vector<cx>> badRect = {
            {cx(1), cx(2)}, 
            {cx(3), cx(4), cx(5)}
        };
        REQUIRE_THROWS(cx_matrix(badRect));
    }
}

TEST_CASE("cx_matrix Accessors...", "[cx_matrix]") {
    std::vector<std::vector<cx>> data = {
        {cx(1,1), cx(2,2)},
        {cx(3,3), cx(4,4)}
    };
    cx_matrix m(data);

    SECTION("operator()(row, col)") {
        REQUIRE(m(0,0) == cx(1,1));
        REQUIRE(m(1,1) == cx(4,4));

        m(0,0) = cx(10, 10);
        REQUIRE(m(0,0) == cx(10,10));
    }

    SECTION("at(row, col)") {
        REQUIRE(m.at(0,0) == cx(1,1));
        REQUIRE(m.at(1,1) == cx(4,4));

        REQUIRE_THROWS(m.at(10,10));
    }

    SECTION("operator[](index)") {
        cx_vector row0 = m[0];
        REQUIRE(row0.dim() == 2);
        REQUIRE(row0[0] == cx(1,1));
        REQUIRE(row0[1] == cx(2,2));

        m[0][1] = cx(7,7);
        REQUIRE(m(0,1) == cx(7,7));
    }

    SECTION("rows() / cols() / dim()") {
        REQUIRE(m.rows() == 2);
        REQUIRE(m.cols() == 2);
        auto dims = m.dim();
        REQUIRE(dims.first  == 2);
        REQUIRE(dims.second == 2);
    }

    SECTION("get_col()") {
        cx_vector col0 = m.get_col(0);
        REQUIRE(col0.dim() == 2);
        REQUIRE(col0[0] == cx(1,1));
        REQUIRE(col0[1] == cx(3,3));

        REQUIRE_THROWS(m.get_col(2));
    }
}

TEST_CASE("cx_matrix Operators...", "[cx_matrix]") {
    // 2x2
    cx_matrix A(2, 2, cx(1,1));
    cx_matrix B(2, 2, cx(2,-1));

    SECTION("Operator +") {
        cx_matrix C = A + B;
        REQUIRE(C(0,0) == cx(3, 0));
        REQUIRE(C(1,1) == cx(3, 0));
    }

    SECTION("Operator -") {
        cx_matrix C = A - B;
        REQUIRE(C(0,0) == cx(-1, 2));
        REQUIRE(C(1,1) == cx(-1, 2));
    }

    SECTION("Dimension mismatch throws") {
        cx_matrix C(2, 3, cx(0,0));
        REQUIRE_THROWS(A + C);
        REQUIRE_THROWS(A - C);
    }

    SECTION("Assignment operator =") {
        cx_matrix C(2, 2, cx(0,0));
        C = A;
        REQUIRE(A == C);
        C(0,0) = cx(10,10);
        REQUIRE_FALSE(A == C);
    }
}

TEST_CASE("cx_matrix Utility Methods...", "[cx_matrix]") {

    SECTION("get_identity()") {
        cx_matrix I = cx_matrix::get_identity(3);
        REQUIRE(I.rows() == 3);
        REQUIRE(I.cols() == 3);

        for (size_t r = 0; r < 3; r++)
            for (size_t c = 0; c < 3; c++) {
                if (r == c) {
                    REQUIRE(I(r,c) == cx(1,0));
                } else {
                    REQUIRE(I(r,c) == cx(0,0));
                }
            }
    }

    SECTION("get()") {
        cx_matrix M(2, 2, cx(3, -2));
        auto matData = M.get();
        REQUIRE(matData.size() == 2);
        REQUIRE(matData[0].dim() == 2);
        REQUIRE(matData[1].dim() == 2);
        REQUIRE(matData[0][0] == cx(3, -2));
    }
}
