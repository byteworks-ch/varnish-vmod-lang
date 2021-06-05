=========
vmod_lang
=========

-------------------
Varnish Lang Module
-------------------

:Author: Michael Bischof
:Date: 2015-09-15
:Version: 2.0
:Manual section: 3

SYNOPSIS
========

import lang;

DESCRIPTION
===========

Functions to handle language detection based on the Accept-Language
header sent by the client.

This module can also be used to normalize the Accept-Language
and therefore reduce the page variants cached.

FUNCTIONS
=========

detect
------

Prototype
        ::

		detect(STRING HEADER, STRING LANGUAGES, STRING LANGUAGE)
Return value
	STRING
Description
	Returns the detected language out of the list "languages" or the default language "language"
	if there is no match.
Example
        ::

		set resp.http.x-lang = lang.detect(req.http.Accept-Language, "de,en,fr,it", "de");

INSTALLATION
============

The source tree is based on autotools to configure the building, and
does also have the necessary bits in place to do functional unit tests
using the ``varnishtest`` tool.

Building requires the Varnish header files and uses pkg-config to find
the necessary paths.

Usage::

 ./autogen.sh
 ./configure

If you have installed Varnish to a non-standard directory, call
``autogen.sh`` and ``configure`` with ``PKG_CONFIG_PATH`` pointing to
the appropriate path. For example, when varnishd configure was called
with ``--prefix=$PREFIX``, use

PKG_CONFIG_PATH=${PREFIX}/lib/pkgconfig
export PKG_CONFIG_PATH

Make targets:

* make - builds the vmod.
* make install - installs your vmod.
* make check - runs the unit tests in ``src/tests/*.vtc``
* make distcheck - run check and prepare a tarball of the vmod.

In your VCL you could then use this vmod along the following lines::

	import lang;

	sub vcl_deliver {
		# This sets resp.http.x-lang to the detected language
		set resp.http.x-lang = lang.detect(req.http.Accept-Lanugage, "de,en,fr,it", "de");
	}


COMMON PROBLEMS
===============

* configure: error: Need varnish.m4 -- see README.rst

  Check if ``PKG_CONFIG_PATH`` has been set correctly before calling
  ``autogen.sh`` and ``configure``


COPYRIGHT
=========

This document is licensed under the same license as the
libvmod-lang project. See LICENSE for details.

* Copyright (c) 2014 by Byteworks GmbH

