# Makefile.am for building the qla_q library

AUTOMAKE_OPTIONS = no-dependencies

QLASRC1 = \
QLA_Q_C_eq_C.c \
QLA_Q_C_eq_gaussian_S.c \
QLA_Q_C_eqm_C.c \
QLA_Q_C_eq_zero.c \
QLA_Q_C_meq_C.c \
QLA_Q_C_peq_C.c \
QLA_Q_C_veq_C.c \
QLA_Q_C_veq_gaussian_pS.c \
QLA_Q_C_veq_gaussian_S.c \
QLA_Q_C_veqm_C.c \
QLA_Q_C_veqm_pC.c \
QLA_Q_C_veq_pC.c \
QLA_Q_C_veq_zero.c \
QLA_Q_C_vmeq_C.c \
QLA_Q_C_vmeq_pC.c \
QLA_Q_C_vpeq_C.c \
QLA_Q_C_vpeq_pC.c \
QLA_Q_C_xeq_C.c \
QLA_Q_C_xeq_gaussian_pS.c \
QLA_Q_C_xeq_gaussian_S.c \
QLA_Q_C_xeqm_C.c \
QLA_Q_C_xeqm_pC.c \
QLA_Q_C_xeq_pC.c \
QLA_Q_C_xeq_zero.c \
QLA_Q_C_xmeq_C.c \
QLA_Q_C_xmeq_pC.c \
QLA_Q_C_xpeq_C.c \
QLA_Q_C_xpeq_pC.c \
QLA_Q_R_eq_gaussian_S.c \
QLA_Q_R_eqm_R.c \
QLA_Q_R_eq_R.c \
QLA_Q_R_eq_zero.c \
QLA_Q_R_meq_R.c \
QLA_Q_R_peq_R.c \
QLA_Q_R_veq_gaussian_pS.c \
QLA_Q_R_veq_gaussian_S.c \
QLA_Q_R_veqm_pR.c \
QLA_Q_R_veqm_R.c \
QLA_Q_R_veq_pR.c \
QLA_Q_R_veq_R.c \
QLA_Q_R_veq_zero.c \
QLA_Q_R_vmeq_pR.c \
QLA_Q_R_vmeq_R.c \
QLA_Q_R_vpeq_pR.c \
QLA_Q_R_vpeq_R.c \
QLA_Q_R_xeq_gaussian_pS.c \
QLA_Q_R_xeq_gaussian_S.c \
QLA_Q_R_xeqm_pR.c \
QLA_Q_R_xeqm_R.c \
QLA_Q_R_xeq_pR.c \
QLA_Q_R_xeq_R.c \
QLA_Q_R_xeq_zero.c \
QLA_Q_R_xmeq_pR.c \
QLA_Q_R_xmeq_R.c \
QLA_Q_R_xpeq_pR.c \
QLA_Q_R_xpeq_R.c

QLAOBJ1 = \
QLA_Q_C_eq_C.o \
QLA_Q_C_eq_gaussian_S.o \
QLA_Q_C_eqm_C.o \
QLA_Q_C_eq_zero.o \
QLA_Q_C_meq_C.o \
QLA_Q_C_peq_C.o \
QLA_Q_C_veq_C.o \
QLA_Q_C_veq_gaussian_pS.o \
QLA_Q_C_veq_gaussian_S.o \
QLA_Q_C_veqm_C.o \
QLA_Q_C_veqm_pC.o \
QLA_Q_C_veq_pC.o \
QLA_Q_C_veq_zero.o \
QLA_Q_C_vmeq_C.o \
QLA_Q_C_vmeq_pC.o \
QLA_Q_C_vpeq_C.o \
QLA_Q_C_vpeq_pC.o \
QLA_Q_C_xeq_C.o \
QLA_Q_C_xeq_gaussian_pS.o \
QLA_Q_C_xeq_gaussian_S.o \
QLA_Q_C_xeqm_C.o \
QLA_Q_C_xeqm_pC.o \
QLA_Q_C_xeq_pC.o \
QLA_Q_C_xeq_zero.o \
QLA_Q_C_xmeq_C.o \
QLA_Q_C_xmeq_pC.o \
QLA_Q_C_xpeq_C.o \
QLA_Q_C_xpeq_pC.o \
QLA_Q_R_eq_gaussian_S.o \
QLA_Q_R_eqm_R.o \
QLA_Q_R_eq_R.o \
QLA_Q_R_eq_zero.o \
QLA_Q_R_meq_R.o \
QLA_Q_R_peq_R.o \
QLA_Q_R_veq_gaussian_pS.o \
QLA_Q_R_veq_gaussian_S.o \
QLA_Q_R_veqm_pR.o \
QLA_Q_R_veqm_R.o \
QLA_Q_R_veq_pR.o \
QLA_Q_R_veq_R.o \
QLA_Q_R_veq_zero.o \
QLA_Q_R_vmeq_pR.o \
QLA_Q_R_vmeq_R.o \
QLA_Q_R_vpeq_pR.o \
QLA_Q_R_vpeq_R.o \
QLA_Q_R_xeq_gaussian_pS.o \
QLA_Q_R_xeq_gaussian_S.o \
QLA_Q_R_xeqm_pR.o \
QLA_Q_R_xeqm_R.o \
QLA_Q_R_xeq_pR.o \
QLA_Q_R_xeq_R.o \
QLA_Q_R_xeq_zero.o \
QLA_Q_R_xmeq_pR.o \
QLA_Q_R_xmeq_R.o \
QLA_Q_R_xpeq_pR.o \
QLA_Q_R_xpeq_R.o

QLASRC = $(QLASRC1)
QLAOBJ = $(QLAOBJ1)

BUILD_SCRIPT_DIR = $(top_srcdir)/lib/perl

BUILD_SCRIPT = $(BUILD_SCRIPT_DIR)/build_qla.pl

BUILD_DEPS = \
	$(BUILD_SCRIPT_DIR)/build_qla.pl \
	$(BUILD_SCRIPT_DIR)/datatypes.pl \
	$(BUILD_SCRIPT_DIR)/expressions_gamma.pl \
	$(BUILD_SCRIPT_DIR)/expressions_scalar.pl \
	$(BUILD_SCRIPT_DIR)/expressions_tensor.pl \
	$(BUILD_SCRIPT_DIR)/formatting.pl \
	$(BUILD_SCRIPT_DIR)/headers.pl \
	$(BUILD_SCRIPT_DIR)/indirection.pl \
	$(BUILD_SCRIPT_DIR)/make_code_binary.pl \
	$(BUILD_SCRIPT_DIR)/make_code_real_complex.pl \
	$(BUILD_SCRIPT_DIR)/make_code_ternary.pl \
	$(BUILD_SCRIPT_DIR)/make_code_unary.pl \
	$(BUILD_SCRIPT_DIR)/operatortypes.pl \
	$(BUILD_SCRIPT_DIR)/prototype.pl \
	$(BUILD_SCRIPT_DIR)/variable_names.pl

lib_LIBRARIES = ../libqla_q.a

AM_CFLAGS = -I$(top_srcdir)/include

# this is just to force automake to include the .c.o rule
nodist____libqla_q_a_SOURCES = QLA_Q_C_eq_C.c

nodist_include_HEADERS = $(top_builddir)/include/qla_q.h $(top_builddir)/include/qla_q_generic.h

source-stamp: $(BUILD_DEPS) 
	@rm -f source-temp
	@touch source-temp
	$(PERL) $(BUILD_SCRIPT) QLA_Q $(top_builddir)/include/qla_q.h .
	@mv -f source-temp $@

$(QLASRC) $(nodist_include_HEADERS): source-stamp
	## Recover from the removal of $@
	@if test -f $@; then :; else \
	  trap 'rm -rf source-lock source-stamp' 1 2 13 15; \
	  if mkdir source-lock 2>/dev/null; then \
	    rm -f source-stamp; \
	    $(MAKE) $(AM_MAKEFLAGS) source-stamp; \
	    rmdir source-lock; \
	  else \
	    while test -d source-lock; do sleep 1; done; \
	    test -f source-stamp; exit $$?; \
	  fi; \
	fi

../libqla_q.a: $(QLAOBJ) ../optimized/Makefile
	-rm -f ../libqla_q.a
	$(AR) $(ARFLAGS) ../libqla_q.a $(QLAOBJ1)
	$(RANLIB) ../libqla_q.a

clean-local:
	-rm -f $(nodist_include_HEADERS) source-stamp
	-rm -f $(QLASRC1)
	-rm -f $(QLAOBJ1)
