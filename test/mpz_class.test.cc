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
TEST_CASE("MpzClass & long long", "[long long]") {
  const long long a = GENERATE(take(100, random(-100, 100)));
  const int shift = GENERATE(range(0, 128));

  const long long x = a << shift;

  REQUIRE(mpz_class(x) == x);
  REQUIRE(x == mpz_class(x));
  REQUIRE(mpz_class(x) == mpz_class(x));
  REQUIRE(mpz_class(x).get_sll() == x);
  REQUIRE(mpz_class(x).fits_slonglong_p());
}

TEST_CASE("MpzClass & unsigned long long", "[unsigned long long]") {
  const unsigned long long a = GENERATE(take(100, random(0, 100)));
  const int shift = GENERATE(range(0, 128));

  const unsigned long long x = a << shift;

  REQUIRE(mpz_class(x) == x);
  REQUIRE(x == mpz_class(x));
  REQUIRE(mpz_class(x) == mpz_class(x));
  REQUIRE(mpz_class(x).get_ull() == x);
  REQUIRE(mpz_class(x).fits_ulonglong_p());
}
}  // namespace gmpxxll::test
