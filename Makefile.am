
ACLOCAL_AMFLAGS=-I m4

SUBDIRS = \
	src \
	tests \
	perf 

EXTRA_DIST = LICENSING README VERSION

dist-hook:
	echo @VERSION@ > VERSION

.PHONY: dist-hook

clean-local:
	rm -f *.data *.dat


