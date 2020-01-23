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

#ifndef GMPXXLL_MPZ_CLASS_HPP
#define GMPXXLL_MPZ_CLASS_HPP

#include <string>
#include <sstream>
#include <limits>
#include <type_traits>

#include <gmp.h>
#include <gmpxx.h>

namespace gmpxxll {

// Adds some long long functionality to mpz_class.
// Everything has been done quite naively and is likely quite slow. If the
// performance is a problem for you, patches are always very welcome.
class mpz_class : public ::mpz_class {
 public:
  using ::mpz_class::mpz_class;

  template <typename T>
  mpz_class(T&& value) : ::mpz_class(std::forward<T>(value)) {}

  mpz_class(long long value) {
    if constexpr (std::numeric_limits<long long>::max() <= std::numeric_limits<long int>::max() && std::numeric_limits<long long>::min() >= std::numeric_limits<long int>::min()) {
      *this = ::mpz_class(static_cast<long int>(value));
    } else {
      if (value >= std::numeric_limits<long int>::min() && value <= std::numeric_limits<long int>::max()) {
        *this = ::mpz_class(static_cast<long int>(value));
      } else {
        *this = ::mpz_class(std::to_string(value));
      }
    }
  }

  mpz_class(unsigned long long value) {
    if constexpr (std::numeric_limits<unsigned long long>::max() <= std::numeric_limits<unsigned long int>::max()) {
      *this = ::mpz_class(static_cast<unsigned long int>(value));
    } else {
      if (value <= std::numeric_limits<unsigned long int>::max()) {
        *this = ::mpz_class(static_cast<unsigned long int>(value));
      } else {
        *this = ::mpz_class(std::to_string(value));
      }
    }
  }

  // Bring original assignment operators back to life that have been hidden by
  // the implicitly generated assignment operators.
  template <typename T, typename = std::enable_if_t<std::is_convertible_v<T, ::mpz_class>>>
  inline mpz_class& operator=(T&& rhs) {
    ::mpz_class::operator=(std::forward<T>(rhs));
    return *this;
  }

  explicit operator long long() const {
    if (mpz_fits_sint_p(get_mpz_t()))
      return mpz_get_si(get_mpz_t());
    if (*this >= mpz_class(std::numeric_limits<long long>::min()) && *this <= mpz_class(std::numeric_limits<long long>::max())) {
      std::stringstream str;
      str << *this;
      long long ret;
      str >> ret;
      return ret;
    }
    throw std::out_of_range("value does not fit into a long long");
  }

  explicit operator unsigned long long() const {
    if (mpz_fits_uint_p(get_mpz_t()))
      return mpz_get_ui(get_mpz_t());
    if (*this >= 0 && *this <= mpz_class(std::numeric_limits<unsigned long long>::max())) {
      std::stringstream str;
      str << *this;
      unsigned long long ret;
      str >> ret;
      return ret;
    }
    throw std::out_of_range("value does not fit into an unsigned long long");
  }
};

bool operator==(const mpz_class& lhs, const long long rhs) { return lhs == mpz_class(rhs); }
bool operator==(const long long lhs, const mpz_class& rhs) { return rhs == lhs; }

bool operator==(const mpz_class& lhs, const unsigned long long rhs) { return lhs == mpz_class(rhs); }
bool operator==(const unsigned long long lhs, const mpz_class& rhs) { return rhs == lhs; }

}

#endif
