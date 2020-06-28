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

#include <benchmark/benchmark.h>

#include "../gmpxxll/mpz_class.hpp"

using benchmark::DoNotOptimize;
using benchmark::State;

namespace {
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
}  // namespace
