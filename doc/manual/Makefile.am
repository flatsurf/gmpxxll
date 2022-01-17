PORT ?= 8080
EXTRA_STANDARDESE_FLAGS ?=

STANDARDESE_FLAGS = --warn-as-error --free-file-comments -X
# Configure search paths for #include statements
STANDARDESE_FLAGS += -I $(srcdir)/../../gmpxxll -I $(builddir)/../../gmpxxll -I $(includedir)
# Allow === Output Section === Syntax
STANDARDESE_FLAGS += -p output_section='=== (.*) ==='
# Allow ==* Group *== Syntax
STANDARDESE_FLAGS += -p group='==\* ((?:.(?!\*==))+)() \*=='
# Allow [Excluded from documentation] Syntax
STANDARDESE_FLAGS += -p exclude='\[Excluded from documentation\]'
# Allow :param:`name` syntax like in Sphinx.
STANDARDESE_FLAGS += -p param=':param:`([^`]*)`'
# We will serve the documentation from the gmpxxll subdirectory
STANDARDESE_FLAGS += --vpath 'gmpxxll/doc_{{ sanitize_basename(name) }}'
# We use C++17 features in gmpxxll headers
STANDARDESE_FLAGS += --std=c++17
# Shorten type names in the documentation that reference common namespaces or use complicated aliases.
STANDARDESE_FLAGS += --format type='{% set formatted = format(option("default:type_format")) %}{% set formatted = replace(formatted, "std::|gmpxxll::", "") %}{% set formatted = replace(formatted, "mp_limb_signed_t", "slong") %}{% set formatted = replace(formatted, "mp_bitcnt_t", "ulong") %}{{ formatted }}'

STANDARDESE_FLAGS += ${EXTRA_STANDARDESE_FLAGS}

# Process all header files with standardese.
STANDARDESE_INPUTS = `find $(srcdir)/../../gmpxxll/ -name '*.hpp' -not -path '*external*'`
# Process all MarkDown files with standardese.
STANDARDESE_INPUTS += `find $(srcdir)/ -name '*.md'`

$(builddir)/generated/inventory:
	@# Create an inventory of gmpxxll so Sphinx can link against it. (This also creates the entire documentation since there is no flag in standardese yet to only generate the inventory.)
	mkdir -p $(builddir)/generated/inventory
	$(STANDARDESE) --outdir $(builddir)/generated/inventory/ $(STANDARDESE_FLAGS) $(STANDARDESE_INPUTS)

$(builddir)/generated/markdown:
	@# Build markdown files from C++ headers
	mkdir -p $(builddir)/generated/
	cp -RT $(srcdir)/gmpxxll/* $(builddir)/generated/markdown
	$(STANDARDESE) --outdir $(builddir)/generated/markdown/ $(STANDARDESE_FLAGS) $(STANDARDESE_INPUTS)

html: $(builddir)/generated/markdown $(builddir)/generated/markdown/mkdocs.yml
	@# Create html documentation from markdown files
	cd $(builddir)/generated/markdown &&\
	$(MKDOCS) build --config-file mkdocs.yml --site-dir $(abs_builddir)/generated/html/

$(builddir)/generated/markdown/mkdocs.yml: $(srcdir)/gmpxxll/mkdocs.yml.in Makefile
	mkdir -p $(builddir)/generated/markdown
	sed -e 's,[@]srcdir[@],$(srcdir),g' -e 's,[@]builddir[@],$(builddir),g' < $< > $@

serve: html
	python -m http.server ${PORT} --bind 127.0.0.1 --directory $(builddir)/generated/html

all: html

.PHONY: serve $(builddir)/generated/html $(builddir)/generated/markdown $(builddir)/generated/inventory

EXTRA_DIST = README.md libeantic

mostlyclean-local:
	[[ ! -d generated ]] || (chmod -R u+w generated && rm -rf generated)
	[[ ! -d build ]] || (chmod -R u+w build && rm -rf build)

