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

#include <gmp.h>
#include <gmpxx.h>

#include <limits>
#include <sstream>
#include <string>
#include <type_traits>

namespace {
namespace gmpxxll {

// Adds some long long functionality to mpz_class.
// Everything has been done quite naively and is likely slow in some cases. If
// the performance is a problem for you, patches are always very welcome.
class mpz_class : public ::mpz_class {
  /// Helper method that turns a (unsigned) long long value into a GMP `mpz_class`.
  template <typename T>
  static ::mpz_class make(const T value) {
    using Long = std::conditional_t<std::is_signed_v<T>, long, unsigned long>;

    if constexpr (std::numeric_limits<T>::max() <= std::numeric_limits<Long>::max() && std::numeric_limits<T>::min() >= std::numeric_limits<Long>::min()) {
      return ::mpz_class(static_cast<Long>(value));
    } else {
      if (value >= std::numeric_limits<Long>::min() && value <= std::numeric_limits<Long>::max()) {
        return ::mpz_class(static_cast<Long>(value));
      } else {
        return ::mpz_class(std::to_string(value));
      }
    }
  }

 public:
  using ::mpz_class::mpz_class;

  //- Support all the constructors provided by the base class.
  template <typename T>
  mpz_class(T&& value) : ::mpz_class(std::forward<T>(value)) {}

  /// === Constructors ===
  /// Construct an `mpz_class` from an (unsigned) long long value.
  /// All the constructors provided by GMP's `mpz_class` are also available
  /// through a forwarding constructor.
  mpz_class(long long value) : ::mpz_class(make(value)) {}

  mpz_class(unsigned long long value) : ::mpz_class(make(value)) {}

  //- Bring the original assignment operators back to life that have been
  //- hidden by the implicitly generated assignment operators.
  template <typename T, typename = std::enable_if_t<std::is_convertible_v<T, ::mpz_class>>>
  mpz_class& operator=(T&& rhs) {
    ::mpz_class::operator=(std::forward<T>(rhs));
    return *this;
  }

  /// == Type Conversion ==
  /// Return this integer as an (unsigned) long long value.
  /// The behaviour is undefined when the integer does not fit into an (unsigned) long long.
  long long get_sll() const {
    if (fits_slong_p())
      return get_si();

    std::stringstream str;
    str << *this;
    long long ret;
    str >> ret;
    return ret;
  }

  unsigned long long get_ull() const {
    if (fits_ulong_p())
      return get_ui();

    std::stringstream str;
    str << *this;
    unsigned long long ret;
    str >> ret;
    return ret;
  }

  bool fits_slonglong_p() const noexcept {
    return *this >= mpz_class(std::numeric_limits<long long>::min()) && *this <= mpz_class(std::numeric_limits<long long>::max());
  }

  bool fits_ulonglong_p() const noexcept {
    return *this >= 0 && *this <= mpz_class(std::numeric_limits<unsigned long long>::max());
  }
};

inline bool operator==(const mpz_class& lhs, const long long rhs) { return lhs == mpz_class(rhs); }
inline bool operator<(const mpz_class& lhs, const long long rhs) { return lhs < mpz_class(rhs); }
inline bool operator>(const mpz_class& lhs, const long long rhs) { return lhs > mpz_class(rhs); }

inline bool operator==(const mpz_class& lhs, const unsigned long long rhs) { return lhs == mpz_class(rhs); }
inline bool operator<(const mpz_class& lhs, const unsigned long long rhs) { return lhs < mpz_class(rhs); }
inline bool operator>(const mpz_class& lhs, const unsigned long long rhs) { return lhs > mpz_class(rhs); }

// Operators derived from the above (we cannot use boost operators here, as
// they lead to hiding issues with the base class operators.)
inline bool operator==(const long long lhs, const mpz_class& rhs) { return rhs == lhs; }
inline bool operator!=(const mpz_class& lhs, const long long rhs) { return !(lhs == rhs); }
inline bool operator!=(const long long lhs, const mpz_class& rhs) { return !(lhs == rhs); }
inline bool operator<(const long long lhs, const mpz_class& rhs) { return rhs > lhs; }
inline bool operator>(const long long lhs, const mpz_class& rhs) { return rhs < lhs; }
inline bool operator<=(const long long lhs, const mpz_class& rhs) { return !(lhs > rhs); }
inline bool operator>=(const long long lhs, const mpz_class& rhs) { return !(lhs < rhs); }
inline bool operator<=(const mpz_class& lhs, const long long rhs) { return !(lhs > rhs); }
inline bool operator>=(const mpz_class& lhs, const long long rhs) { return !(lhs < rhs); }

inline bool operator==(const unsigned long long lhs, const mpz_class& rhs) { return rhs == lhs; }
inline bool operator!=(const mpz_class& lhs, const unsigned long long rhs) { return !(lhs == rhs); }
inline bool operator!=(const unsigned long long lhs, const mpz_class& rhs) { return !(lhs == rhs); }
inline bool operator<(const unsigned long long lhs, const mpz_class& rhs) { return rhs > lhs; }
inline bool operator>(const unsigned long long lhs, const mpz_class& rhs) { return rhs < lhs; }
inline bool operator<=(const unsigned long long lhs, const mpz_class& rhs) { return !(lhs > rhs); }
inline bool operator>=(const unsigned long long lhs, const mpz_class& rhs) { return !(lhs < rhs); }
inline bool operator<=(const mpz_class& lhs, const unsigned long long rhs) { return !(lhs > rhs); }
inline bool operator>=(const mpz_class& lhs, const unsigned long long rhs) { return !(lhs < rhs); }

}  // namespace gmpxxll
}  // namespace

#endif
