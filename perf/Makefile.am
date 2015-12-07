
LDADD = ../src/.libs/libpmalloc.la -lrt

CFLAGS += -I../src

noinst_PROGRAMS = struct_objs_write struct_objs_read

struct_objs_write_SOURCES = struct_objs_write.c common.c

struct_objs_read_SOURCES = struct_objs_read.c common.c

clean-local:
	rm -f *.data *.dat

