#=============================================================================
#
# libvmod-lang: Makefile.am
#
#=============================================================================

ACLOCAL_AMFLAGS = -I m4

SUBDIRS = src

doc_DATA = README.md LICENSE

if HAVE_MD2MAN
dist_man_MANS = vmod_lang.3

vmod_lang.3: README.md
MAINTAINERCLEANFILES = $(dist_man_MANS)
	${MD2MAN} @top_srcdir@/README.md > vmod_lang.3
endif

# EOF

