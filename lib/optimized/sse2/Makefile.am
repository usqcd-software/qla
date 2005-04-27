GCC = @GCC@

OPTLIBS =
if NC3
  OPTLIBS += libd3
endif

all: $(OPTLIBS)

.PHONY: libd3
libd3:
	for f in $(srcdir)/src/*.c; do \
	  $(GCC) -O3 -DSSE_INLINE -I$(top_srcdir)/include -I$(srcdir)/include -c $$f; \
	done
	mv -f *.o ../../qla_d3

EXTRA_DIST = include src
