libvmod-lang
============

Overview
--------

This is a simple VMOD for [Varnish Cache](https://www.varnish-cache.org/) which
provides functions to handle language detection based on the Accept-Language
header sent by the client.

This module can also be used to normalize the Accept-Language
and therefore reduce the page variants cached.

LICENSE
-------

Copyright (c) 2014-2021 by Byteworks GmbH.
See [LICENSE](./LICENSE) for more information.

Usage
-----

##### Detecting language

It accepts the accept language header, a list of languages (separated by comma) and
the default language. The given languages are evaluated and the best fit is choosen.
If there is no match, the default language given is returned.

```
import lang;

sub vcl_deliver {
	# This sets resp.http.x-lang to the detected language
	set resp.http.x-lang = lang.detect(req.http.Accept-Language, "de,en,fr,it", "de");
}
```

Building
--------

This vmod can be built against a compiled varnish source, or against an installed
`varnish-dev/-devel` package which includes the appropriate `.pc` files.

### Setup

Before anything else is done, your source directory has to be initialized:

```sh
./autogen.sh
```

### Configuration

To build against a standard varnish development package, you should be able to
simply invoke:
```sh
./configure && make && make check
```
(See `./configure --help` for configure-time options)

This vmod can also be compiled against a pre-built Varnish Cache 3.x/4.x/5.x/6.x
source by indicating the path to the (pre-compiled!) varnish source using the
`VARNISHSRC` configuration variable, like so:

```sh
./configure VARNISHSRC=path/to/varnish-M.m.p && make && make check
```

Additional configuration variables and options can be found by invoking
`configure --help`.


### Check Targets

Libvmod-lang provides a set of simple unit tests driven by
**varnishtest**. They can be executed as part of the build process by
invoking `make check`.

