AUTOMAKE_OPTIONS = 1.5 subdir-objects
ACLOCAL_AMFLAGS = -I m4

AM_CPPFLAGS = -I$(top_srcdir)/common

SUBDIRS = .

noinst_HEADERS =
BUILT_SOURCES =
noinst_LTLIBRARIES =
CLEANFILES =
DISTCLEANFILES =
MAINTAINERCLEANFILES =
bin_PROGRAMS =
EXTRA_PROGRAMS =

libcreed_la = libcreed-1.0.la
lib_LTLIBRARIES = libcreed-1.0.la
libcreed_1_0_la_SOURCES = $(lib_src)
libcreed_1_0_la_LIBADD = $(CREED_LIBS)
libcreed_1_0_la_LDFLAGS = \
    $(CREED_LDFLAGS) $(NO_UNDEFINED) -version-info $(LIBRARY_VERSION_INFO)

EXTRA_DIST =
lib_src =


include query/Makefile.mk
include common/Makefile.mk
include index/Makefile.mk