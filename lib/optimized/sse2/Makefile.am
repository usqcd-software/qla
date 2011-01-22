SSE_CC = @SSE_CC@
SSE_CFLAGS = @SSE_CFLAGS@

OPTLIBS =
if NC3
  OPTLIBS += libd3
endif

all: $(OPTLIBS)

.PHONY: libd3
libd3:
	for f in $(srcdir)/src/*.c; do \
	  echo compiling $$f; \
	  $(SSE_CC) $(SSE_CFLAGS) -I$(top_srcdir)/include -I$(top_builddir)/include -I$(srcdir)/include -c $$f; \
	done
	mv -f *.o ../../qla_d3

EXTRA_DIST = include src
