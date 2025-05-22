noinst_PROGRAMS = benchmark

benchmark_SOURCES = main.cc mpz_class.benchmark.cc

AM_CPPFLAGS = -I $(srcdir)/.. -I $(builddir)/..
LDADD = -lgmpxx -lgmp
# Google Benchmark and its dependencies
if OS_LINUX
AM_LDFLAGS += -lbenchmark -lrt -lpthread
else
AM_LDFLAGS += -lbenchmark -lpthread
endif
