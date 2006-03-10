SSE_CC = @SSE_CC@
SSE_CFLAGS = @SSE_CFLAGS@

OPTLIBS =
if NC3
  OPTLIBS += libf3
endif

all: $(OPTLIBS)

.PHONY: libf3
libf3:
	for f in $(srcdir)/src/*.c; do \
	  echo compiling $$f; \
	  $(SSE_CC) $(SSE_CFLAGS) -I$(top_srcdir)/include -I$(top_builddir)/include -I$(srcdir)/include -c $$f; \
	done
	mv -f *.o ../../qla_f3

EXTRA_DIST = include src
