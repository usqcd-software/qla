OPTLIBS = 
if NC3
  OPTLIBS += libf3
endif

all: $(OPTLIBS)

.PHONY: libf3
libf3:
	for f in $(srcdir)/src/*.s; do \
	  echo compiling $$f; \
	  $(CC) $(CFLAGS) -I$(top_srcdir)/include -c $$f; \
	done
	mv -f *.o ../../qla_f3

EXTRA_DIST = src
