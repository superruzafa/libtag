AM_CPPFLAGS = -I$(top_srcdir)/include

TESTS = libtag
check_PROGRAMS = libtag
libtag_SOURCES = tag.c node.c 
libtag_CFLAGS = @CHECK_CFLAGS@
libtag_LDADD = $(top_builddir)/src/libtag.la @CHECK_LIBS@
