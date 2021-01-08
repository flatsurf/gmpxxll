---
title: README
---
# C++ Documentation

We build our documentation with
[standardese](https://github.com/standardese/standardese).

All the generated bits are in `generated/`. To recreate these run in the root
directory
```
standardese gmpxxll/mpz_class.hpp --verbose -I $CONDA_PREFIX/include --compilation.standard=c++17 --verbose --output.prefix doc/standardese/generated/
```

To preview the documentation, run in this directory
```
bundle config set path vendor/bundle
bundle install
bundle exec jekyll serve
```

If you want to understand what these do, here is a [very brief summary](https://jekyllrb.com/docs/ruby-101/).
