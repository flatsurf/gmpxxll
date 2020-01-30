/**********************************************************************
 *  This file is part of gmpxxll.
 *
 *        Copyright (C) 2019-2020 Julian Rüth
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 *********************************************************************/

#include "external/catch2/single_include/catch2/catch.hpp"

#include "../gmpxxll/mpz_class.hpp"

namespace gmpxxll::test {

TEMPLATE_TEST_CASE("MpzClass & (unsigned) long long", "[mpz_class]", (long long), (unsigned long long)) {
  TestType a;
  if constexpr (std::is_same_v<TestType, long long>) {
    a = GENERATE(take(100, random(-100, 100)));
  } else {
    a = GENERATE(take(100, random(0, 100)));
  }
  const int shift = GENERATE(range(0, 128));

  const TestType x = a << shift;

  if constexpr (std::is_same_v<TestType, long long>) {
    REQUIRE(mpz_class(x).get_sll() == x);
    REQUIRE(mpz_class(x).fits_slonglong_p());
  } else {
    REQUIRE(mpz_class(x).get_ull() == x);
    REQUIRE(mpz_class(x).fits_ulonglong_p());
  }
  REQUIRE(mpz_class(x) == mpz_class(x));

  SECTION("Comparison Operators") {
    const TestType less = x - 1;
    const TestType more = x + 1;
    const auto X = mpz_class(x);

    SECTION("operator==") {
      REQUIRE(X == x);
      REQUIRE(x == X);
      REQUIRE(!(X == less));
      REQUIRE(!(less == X));
    }

    SECTION("operator!=") {
      REQUIRE(!(X != x));
      REQUIRE(!(x != X));
      REQUIRE(X != less);
      REQUIRE(less != X);
    }

    SECTION("operator<") {
      if (more > x) {
        REQUIRE(X < more);
      }
      if (less < x) {
        REQUIRE(less < X);
      }
      REQUIRE(!(X < x));
      REQUIRE(!(x < X));
    }

    SECTION("operator>") {
      if (less < x) {
        REQUIRE(X > less);
      }
      if (more > x) {
        REQUIRE(more > X);
      }
      REQUIRE(!(X > x));
      REQUIRE(!(x > X));
    }

    SECTION("operator<=") {
      REQUIRE(X <= x);
      REQUIRE(x <= X);
      if (less < x) {
        REQUIRE(!(X <= less));
      }
      if (more > x) {
        REQUIRE(!(more <= X));
      }
    }

    SECTION("operator>=") {
      REQUIRE(X >= x);
      REQUIRE(x >= X);
      if (more > x) {
        REQUIRE(!(X >= more));
      }
      if (less < x) {
        REQUIRE(!(less >= X));
      }
    }
  }
}

}  // namespace gmpxxll::test
