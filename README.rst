=========
vmod_lang
=========

-------------------
Varnish Lang Module
-------------------

:Author: Michael Bischof
:Date: 2014-05-09
:Version: 1.0
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
using the varnishtest tool.

Usage::

 ./configure VARNISHSRC=DIR [VMODDIR=DIR]

`VARNISHSRC` is the directory of the Varnish source tree for which to
compile your vmod. Both the `VARNISHSRC` and `VARNISHSRC/include`
will be added to the include search paths for your module.

Optionally you can also set the vmod install directory by adding
`VMODDIR=DIR` (defaults to the pkg-config discovered directory from your
Varnish installation).

Make targets:

* make - builds the vmod
* make install - installs your vmod in `VMODDIR`
* make check - runs the unit tests in ``src/tests/*.vtc``

In your VCL you could then use this vmod along the following lines::
	
	import lang;

	sub vcl_deliver {
		# This sets resp.http.x-lang to the detected language
		set resp.http.x-lang = lang.detect(req.http.Accept-Lanugage, "de,en,fr,it", "de");
	}

HISTORY
=======

This manual page was released as part of the libvmod-lang package.
For further modules and inspiration check the vmod directory:
https://www.varnish-cache.org/vmods

COPYRIGHT
=========

This document is licensed under the same license as the
libvmod-lang project. See LICENSE for details.

* Copyright (c) 2014 by Byteworks GmbH

