/**********************************************************************
 *  This file is part of gmpxxll.
 *
 *        Copyright (C) 2019 Vincent Delecroix
 *        Copyright (C) 2019 Julian Rüth
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

#include <benchmark/benchmark.h>

#include "../gmpxxll/mpz_class.hpp"

using benchmark::DoNotOptimize;
using benchmark::State;

namespace gmpxxll::benchmark {

// For comparison, the official mpz_class initializing from an int.
static void FromInt(State& state) {
  const int x = 1;
  for (auto _ : state)
    DoNotOptimize(::mpz_class(x));
}
BENCHMARK(FromInt);

// For comparison, converting the official mpz_class to an int.
static void ToInt(State& state) {
  const ::mpz_class x = 1;
  for (auto _ : state)
    DoNotOptimize(x.get_si());
}
BENCHMARK(ToInt);

static void FromLongLong(State& state) {
  const long long x = 1ll << state.range(0);
  for (auto _ : state) {
    DoNotOptimize(mpz_class(x));
  }
}
BENCHMARK(FromLongLong)->Arg(0)->Arg(10)->Arg(30)->Arg(40)->Arg(60);

static void ToLongLong(State& state) {
  const auto x = mpz_class(1ll << state.range(0));
  for (auto _ : state) {
    DoNotOptimize(x.get_sll());
  }
}
BENCHMARK(ToLongLong)->Arg(0)->Arg(10)->Arg(30)->Arg(40)->Arg(60);

}  // namespace gmpxxll::benchmark
