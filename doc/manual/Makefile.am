export ABS_SRCDIR=$(abs_srcdir)
export ABS_BUILDDIR=$(abs_builddir)

generated/html/index.html: generated/doxygen/xml/index.xml $(srcdir)/*.rst $(srcdir)/conf.py $(srcdir)/_static/extra.css
	python $(SPHINXBUILD) -b html $(srcdir) $(builddir)/generated/html
	cp $(srcdir)/robots.txt generated/html/

generated/doxygen/xml/index.xml: $(srcdir)/Doxyfile $(srcdir)/../../gmpxxll/*.hpp
	mkdir -p generated/doxygen
	$(DOXYGEN) $(srcdir)/Doxyfile

all: generated/html/index.html

EXTRA_DIST = README.md
EXTRA_DIST += robots.txt _static/extra.css
EXTRA_DIST += Doxyfile
EXTRA_DIST += conf.py index.rst gmpxxll.rst

mostlyclean-local:
	[[ ! -d generated ]] || (chmod -R u+w generated && rm -rf generated)

