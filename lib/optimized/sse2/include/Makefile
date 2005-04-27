PERL = perl
N2C = $(PERL) bin/nasm2c.pl
HDR = $(PERL) bin/headers.pl

all:
	for f in nas/*.s; do \
	  t=`basename $$f .s`.h; \
	  $(N2C) < $$f > $$t; \
	done
	$(HDR) > inline_headers.h

clean:
	rm -f QLA_*.h inline_headers.h
