AC_INIT([creed-core], [1.0], [founders@goshoplane.com])

LIBRARY_VERSION_INFO=6:0:0
AC_SUBST([LIBRARY_VERSION_INFO])

LIBRARY_VERSION_SUFFIX=-1.0
AC_SUBST([LIBRARY_VERSION_SUFFIX])

AM_INIT_AUTOMAKE([1.11 -Wportability tar-ustar no-dist-gzip dist-xz std-options])
AC_CONFIG_HEADERS([config.h])

AC_CONFIG_MACRO_DIR([m4])

dnl Use libtool to manage our libraries.
LT_PREREQ([2.2.8])
dnl Default to only building shared libraries.
dnl
dnl Building both shared and static means having to compile the files which
dnl make up the library twice on most platforms.  Shared libraries are the
dnl better option for most users, and if anyone really wants static libraries,
dnl they can configure with --enable-static (or --enable-static=xapian-core if
dnl configuring a combined tree with the bindings).
LT_INIT([disable-static])

NO_UNDEFINED=
AC_SUBST([NO_UNDEFINED])

AC_LANG([C++])
AC_PROG_CXX
dnl AC_PROG_LIBTOOL

dnl m4_include([m4/ax_cxx_compile_stdcxx_11.m4])
dnl AX_CHECK_COMPILE_FLAG([-std=c++11], [compile_flag_cxx11=yes])
dnl if test "x${compile_flag_cxx11}" = "xyes"; then
dnl    CXXFLAGS="-std=c++11 $CXXFLAGS"
dnl    CXX_STANDARD=201103L
dnl else
dnl    CXX_STANDARD=199711L
dnl fi

dnl CXXFLAGS = "-std=c++11 $CXXFLAGS"

dnl AC_SUBST([CXX_STANDARD])

AC_CANONICAL_HOST

CREED_LDFLAGS=
CREED_LIBS=
AC_SUBST([CREED_LDFLAGS])
AC_SUBST([CREED_LIBS])

AC_CONFIG_FILES([
    Makefile
])

AC_OUTPUT