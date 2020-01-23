/**********************************************************************
 *  This file is part of gmpxxll.
 *
 *        Copyright (C) 2020 Julian Rüth
 *
 *  Gmpxxll is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  Gmpxxll is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with gmpxxll. If not, see <https://www.gnu.org/licenses/>.
 *********************************************************************/

#include "external/catch2/single_include/catch2/catch.hpp"

#include "../gmpxxll/mpz_class.hpp"

namespace gmpxxll::test {
TEST_CASE("MpzClass & long long", "[long long]") {
  const long long a = GENERATE(take(100, random(-100, 100)));
  const int shift = GENERATE(range(0, 128));

  const long long x = a << shift;

  REQUIRE(mpz_class(x) == x);
  REQUIRE(mpz_class(x) == x);
  REQUIRE(mpz_class(x) == mpz_class(x));
  REQUIRE(static_cast<long long>(mpz_class(x)) == x);
}

TEST_CASE("MpzClass & unsigned long long", "[unsigned long long]") {
  const unsigned long long a = GENERATE(take(100, random(0, 100)));
  const int shift = GENERATE(range(0, 128));

  const unsigned long long x = a << shift;

  REQUIRE(mpz_class(x) == x);
  REQUIRE(mpz_class(x) == x);
  REQUIRE(mpz_class(x) == mpz_class(x));
  REQUIRE(static_cast<unsigned long long>(mpz_class(x)) == x);
}
}  // namespace gmpxxll::test

