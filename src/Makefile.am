
lib_LTLIBRARIES = libpmalloc.la
libpmalloc_la_SOURCES = \
	pmaddress.c pmreport.c \
	pmfunction.c pmalloc.c pmalloc.h pmprivate.h \
	pmcalloc.c pmfree.c pmcheck.c pmalign.c \
	pmrealloc.c pmvalloc.c pmmap.c pmattach.c \
	pmdetach.c pmkeys.c

include_HEADERS = pmalloc.h

libpmalloc_la_CFLAGS = 

libpmalloc_la_LDFLAGS = -shared -version-info 1:8:0

EXTRA_DIST = README TODO

