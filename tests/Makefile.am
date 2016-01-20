
TESTS = check_pmsimulate check_pmclear check_pmrecycle check_pmalloc

noinst_PROGRAMS = $(TESTS)

check_pmalloc_SOURCES = check_pmalloc.c check_common.c

check_pmalloc_CFLAGS = -I../src @CHECK_CFLAGS@

check_pmalloc_LDADD = ../src/libpmalloc.la @CHECK_LIBS@ -lrt

check_pmrecycle_SOURCES = check_pmrecycle.c check_common.c

check_pmrecycle_CFLAGS = -I../src @CHECK_CFLAGS@

check_pmrecycle_LDADD = ../src/libpmalloc.la @CHECK_LIBS@ -lrt

check_pmclear_SOURCES = check_pmclear.c check_common.c

check_pmclear_CFLAGS = -I../src @CHECK_CFLAGS@

check_pmclear_LDADD = ../src/libpmalloc.la @CHECK_LIBS@ -lrt 

check_pmsimulate_SOURCES = check_pmsimulate.c check_common.c

check_pmsimulate_CFLAGS = -I../src @CHECK_CFLAGS@

check_pmsimulate_LDADD = ../src/libpmalloc.la @CHECK_LIBS@ -lrt 

clean-local:
	rm -f *.data *.dat

