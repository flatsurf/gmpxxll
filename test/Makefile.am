check_PROGRAMS = mpz_class

TESTS = $(check_PROGRAMS)

mpz_class_SOURCES = mpz_class.test.cc main.cc

# We vendor the single-header catch2 to run our tests
EXTRA_DIST = external/catch2/single_include/catch2/catch.hpp

AM_LDFLAGS = -lgmpxx -lgmp
