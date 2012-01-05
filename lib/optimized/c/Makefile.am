CINC = -I$(top_builddir)/include -I$(top_srcdir)/include -I$(srcdir)/include

OPTLIBS =
if NC3
  OPTLIBS += libf3 libd3
endif

all: $(OPTLIBS)

.PHONY: libf3 libd3

libf3:
	if test -n "`find $(srcdir)/src -maxdepth 1 -name QLA_F3_\*.c -print -quit`"; then \
	  for f in $(srcdir)/src/QLA_F3_*.c; do \
	    if [ -f $f ]; then \
	      echo compiling $$f; \
	      echo $(CC) $(CFLAGS) $(CINC) -c $$f; \
	      $(CC) $(CFLAGS) $(CINC) -c $$f; \
	    fi; \
	  done; \
	  mv -f QLA_F3_*.o ../../qla_f3; \
	fi

libd3:
	if test -n "`find $(srcdir)/src -maxdepth 1 -name QLA_D3_\*.c -print -quit`"; then \
	  for f in $(srcdir)/src/QLA_D3_*.c; do \
	    if [ -f $f ]; then \
	      echo compiling $$f; \
	      echo $(CC) $(CFLAGS) $(CINC) -c $$f; \
	      $(CC) $(CFLAGS) $(CINC) -c $$f; \
	    fi; \
	  done; \
	  mv -f QLA_D3_*.o ../../qla_d3; \
	fi

EXTRA_DIST = include src
