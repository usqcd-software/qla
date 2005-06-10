GCC = @GCC@

OPTLIBS =
if NC3
  OPTLIBS += libf3
endif

all: $(OPTLIBS)

.PHONY: libf3
libf3:
	for f in $(srcdir)/src/*.c; do \
	  $(GCC) -O3 -msse -DSSE_INLINE -I$(top_srcdir)/include -I$(srcdir)/include -c $$f; \
	done
	mv -f *.o ../../qla_f3

EXTRA_DIST = include src
