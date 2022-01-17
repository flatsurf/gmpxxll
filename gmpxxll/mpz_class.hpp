/* ********************************************************************
 *  This file is part of gmpxxll.
 *
 *        Copyright (C) 2019-2022 Julian Rüth
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
 * *******************************************************************/

/// long long support for `mpz_class`.
/// This file provides `gmpxll::mpz_class` which inherits from the official
/// `mpz_class` and is binary compatible with it.
///
/// This makes it possible to mix the two types quite freely. So, you might
/// want to use `gmpxxll::mpz_class` where you perform (generic) conversion 
/// from/to standard integer types and use the regular `mpz_class` everywhere
/// else:
/// ```c++
/// #include "gmpxxll/mpz_class.hpp"
///
/// mpz_class n;
/// gmpxxll::mpz_class m = std::limits<long long>::max;
///
/// // Since gmpxxll::mpz_class is derived from mpz_class, it casts implicitly into it:
/// n = m;
///
/// // Conversely, there are explicit conversions:
/// m = n;
/// m = gmpxxll::mpz_class(n);
/// ```

#ifndef GMPXXLL_MPZ_CLASS_HPP
#define GMPXXLL_MPZ_CLASS_HPP

#include <gmp.h>
#include <gmpxx.h>

#include <limits>
#include <sstream>
#include <string>
#include <type_traits>

namespace gmpxxll {

/// Adds long long functionality to `mpz_class`.
/// This class derives from GMP's `mpz_class`. It is binary compatible with
/// that class but adds some methods related to `long long` and `unsigned long
/// long`.
/// Note that on LP64 implementations of C++ both `long` and `long long` are 64
/// bits wide so this does not add anything and performance overhead should be
/// negligible when optimizations are enabled. On LLP64 implementations, most
/// notably Microsoft Windows, conversions actually need to take place. These
/// conversions are probably not implemented very efficiently yet.
class mpz_class : public ::mpz_class {
  /// [Excluded from documentation]
  /// Helper method that turns an (unsigned) long long value into a GMP `mpz_class`.
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

  /// [Excluded from documentation]
  /// Support all the constructors provided by the base class.
  template <typename T>
  mpz_class(T&& value) : ::mpz_class(std::forward<T>(value)) {}

  /// ==* Constructors *==
  /// Construct an `mpz_class` from an (unsigned) long long value.
  /// All the constructors provided by GMP's `mpz_class` are also available
  /// through a forwarding constructor.
  mpz_class(long long value) : ::mpz_class(make(value)) {}

  mpz_class(unsigned long long value) : ::mpz_class(make(value)) {}

  /// [Excluded from documentation]
  /// Bring the original assignment operators back to life that have been
  /// hidden by the implicitly generated assignment operators.
  template <typename T, typename = std::enable_if_t<std::is_convertible_v<T, ::mpz_class>>>
  mpz_class& operator=(T&& rhs) {
    ::mpz_class::operator=(std::forward<T>(rhs));
    return *this;
  }

  /// ==* Type Conversion *==
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

  /// ==* Range Checks *==
  /// Return whether this integers is within the range of an (unsigned) long long.
  bool fits_slonglong_p() const {
    return *this >= mpz_class(std::numeric_limits<long long>::min()) && *this <= mpz_class(std::numeric_limits<long long>::max());
  }

  bool fits_ulonglong_p() const {
    return *this >= 0 && *this <= mpz_class(std::numeric_limits<unsigned long long>::max());
  }
};

/// ==* Relational Operators *==
/// All the binary operators `<`, `<=`, `==`, `!=`, `>=`, `>` support `long
/// long` operands. Note that binary arithmetic operators are implicitly
/// supported because there is an implicit constructor that can cast a `long
/// long` to an `gmpxxll::mpz_class`.
inline bool operator==(const mpz_class& lhs, const long long rhs) { return lhs == mpz_class(rhs); }
inline bool operator<(const mpz_class& lhs, const long long rhs) { return lhs < mpz_class(rhs); }
inline bool operator>(const mpz_class& lhs, const long long rhs) { return lhs > mpz_class(rhs); }

inline bool operator==(const mpz_class& lhs, const unsigned long long rhs) { return lhs == mpz_class(rhs); }
inline bool operator<(const mpz_class& lhs, const unsigned long long rhs) { return lhs < mpz_class(rhs); }
inline bool operator>(const mpz_class& lhs, const unsigned long long rhs) { return lhs > mpz_class(rhs); }

/// [Excluded from documentation]
/// Operators derived from the above (we cannot use boost operators here, as
/// they lead to hiding issues with the base class operators.)
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

#endif
