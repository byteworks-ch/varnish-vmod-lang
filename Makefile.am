ACLOCAL_AMFLAGS = -I m4

SUBDIRS = src

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

