AM_CPPFLAGS = -I$(top_srcdir)/include

TESTS = tag
check_PROGRAMS = tag
tag_SOURCES = tag.c list.c 
tag_CFLAGS = @CHECK_CFLAGS@
tag_LDADD = $(top_builddir)/src/libtag.la @CHECK_LIBS@
