noinst_PROGRAMS = benchmark

benchmark_SOURCES = main.cc mpz_class.benchmark.cc

AM_CPPFLAGS = -I $(srcdir)/.. -I $(builddir)/..
LDADD = -lgmpxx -lgmp
# Google Benchmark and its dependencies
LDADD += -lbenchmark -lpthread -lrt
