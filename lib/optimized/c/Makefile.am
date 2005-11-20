CINC = -I$(top_builddir)/include -I$(top_srcdir)/include -I$(srcdir)/include

OPTLIBS = 
if NC3
  OPTLIBS += libf3
endif

all: $(OPTLIBS)

.PHONY: libf3
libf3:
	-for f in $(srcdir)/src/*.c; do \
	  if [ -f $f ]; then \
	    echo compiling $$f; \
	    $(CC) $(CFLAGS) $(CINC) -c $$f; \
	  fi; \
	done
	-mv -f *.o ../../qla_f3

EXTRA_DIST = include src
