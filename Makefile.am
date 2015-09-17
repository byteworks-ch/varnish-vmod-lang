ACLOCAL_AMFLAGS = -I m4 -I ${LIBVARNISHAPI_DATAROOTDIR}/aclocal

SUBDIRS = src

DISTCHECK_CONFIGURE_FLAGS = \
	VMOD_DIR='$${libdir}/varnish/vmods'

EXTRA_DIST = README.rst LICENSE vmod-lang.spec debian

doc_DATA = README.rst LICENSE

dist_man_MANS = vmod_lang.3
MAINTAINERCLEANFILES = $(dist_man_MANS)

vmod_lang.3: README.rst

%.1 %.2 %.3 %.4 %.5 %.6 %.7 %.8 %.9:
if HAVE_RST2MAN
	${RST2MAN} $< $@
else
	@echo "========================================"
	@echo "You need rst2man installed to make dist"
	@echo "========================================"
	@false
endif

realclean: distclean
	@rm -rf aclocal.m4 autom4te.cache config.* configure depcomp install-sh libtool ltmain.sh missing Makefile Makefile.in stamp-h1 vmod_lang.3
	@rm -rf m4/* src/.deps src/Makefile src/Makefile.in

