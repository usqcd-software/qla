CC = @TEST_CC@
CFLAGS = @TEST_CFLAGS@
AM_CFLAGS = -I$(top_srcdir)/test/src -I$(top_srcdir)/include
LDADD = ../../lib/libqla_int.a ../../lib/libqla_random.a -lm

check_PROGRAMS = test_int_sng test_int_idx

TESTS_ENVIRONMENT = @BACKEND_TEST_CMD@
TESTS = $(check_PROGRAMS)

distclean-local:
	-rm -f *.result

CMPSRC = ../src/compare.c

nodist_test_int_sng_SOURCES = ../src/test_int_sng.c $(CMPSRC)
nodist_test_int_idx_SOURCES = ../src/test_int_idx.c $(CMPSRC)

