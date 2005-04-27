AM_CFLAGS = -I$(top_srcdir)/test/src -I$(top_srcdir)/include
LDADD = ../../lib/libqla_int.a ../../lib/libqla_random.a -lm

check_PROGRAMS = test_int_sng test_int_idx

TESTS = check_int

EXTRA_DIST = $(TESTS)

distclean-local:
	-rm -f results.*

CMPSRC = ../src/compare.c

nodist_test_int_sng_SOURCES = ../src/test_int_sng.c $(CMPSRC)
nodist_test_int_idx_SOURCES = ../src/test_int_idx.c $(CMPSRC)

