#=============================================================================
#
# libvmod-lang: src/Makefile.am
#
#=============================================================================

AM_CPPFLAGS = \
    @VARNISH_CFLAGS@ \
    -I@top_builddir@/include

vmoddir = @VARNISH_VMODDIR@
vmod_LTLIBRARIES = libvmod_lang.la

libvmod_lang_la_LDFLAGS = \
    @VARNISH_LIBS@ \
    -module \
    -export-dynamic \
    -avoid-version \
    -shared

libvmod_lang_la_SOURCES = \
	vcc_if.c \
	vcc_if.h \
	vmod_lang.c

if VARNISHSRC_3_X
vcc_if.c vcc_if.h: @top_srcdir@/src/vmod_lang3.vcc
	@PYTHON@ @VMODTOOL@ @top_srcdir@/src/vmod_lang3.vcc
else
vcc_if.c vcc_if.h: @top_srcdir@/src/vmod_lang.vcc
	@PYTHON@ @VMODTOOL@ @top_srcdir@/src/vmod_lang.vcc
endif

VMOD_TESTS = @abs_srcdir@/tests/*.vtc
.PHONY: $(VMOD_TESTS)

@abs_srcdir@/tests/*.vtc:
	PATH="@VARNISHD_PATH@:@VARNISHTEST_PATH@:${PATH}" \
	@VARNISHTEST@ \
        -Dvarnish_source=@VARNISHSRC@ \
        -Dvarnishd=@VARNISHD@  \
        -Dvmod_topbuild=@abs_top_builddir@ $@

check: $(VMOD_TESTS)

EXTRA_DIST = \
	vmod_lang.vcc \
	$(VMOD_TESTS)

CLEANFILES = @builddir@/vcc_if.c @builddir@/vcc_if.h

## EOF

