export CXXFLAGS="$CXXFLAGS -g3 -UNDEBUG"

autoreconf -ivf

./configure --prefix="$PREFIX" --without-benchmark --without-doc
make install
