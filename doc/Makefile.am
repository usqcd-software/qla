# For making Postscript and html documentation

LATEX = @LATEX@

VER     = 1p1
HTMLDIR = html
PS      = qla_${VER}.ps
SRC     = qla_${VER}.tex
DSRC    = $(srcdir)/qla_${VER}.tex
DVI     = qla_${VER}.dvi

.PHONY: ps
ps: ${PS}

${PS}: ${DSRC}
	${LATEX} ${DSRC}
	${LATEX} ${DSRC}
	dvips ${DVI} -o

${HTMLDIR}: ${PS} ${DSRC}
	-rm -rf $@
	mkdir $@
	latex2html -math -dir ${HTMLDIR} `echo "${DSRC}" |sed 's/^\.\///'`

# Removes LaTeX debris
doc-clean:
	-/bin/rm -f *.aux *.log *.err *.dvi

# Removes all but the .tex file and Makefile
doc-distclean: doc-clean
	-/bin/rm -f *.ps
	-/bin/rm -rf ${HTMLDIR}

# also clean on regular make clean and distclean
clean-local: doc-clean
distclean-local: doc-distclean

EXTRA_DIST = qla_1p1.tex README
