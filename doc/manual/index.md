# Adding long long Support to GMP's C++ Interface

This header only library adds long long support to GMP's C++ interface. To use
it, add [`mpz_class.hpp`](doc_mpz_class_hpp.md) to your project, e.g., by adding this repository as a
submodule, and `#include "gmpxxll/mpz_class.hpp"`. That header provides a binary-compatible implementation of `mpz_class`.

Note that what's implemented here is probably not too performant and not
feature complete. [Pull Requests](https://github.com/flatsurf/gmpxxll/pulls) to
improve the situation are always welcome.

The [Reference Manual](doc_mpz_class_hpp.md) describes the interface in detail.
