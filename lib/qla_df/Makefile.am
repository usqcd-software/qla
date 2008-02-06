# Makefile.am for building the qla_df library

AUTOMAKE_OPTIONS = no-dependencies

QLASRC1 = \
QLA_DF_c1_eq_C_dot_C.c \
QLA_DF_c1_eq_sum_C.c \
QLA_DF_c1_veq_C_dot_C.c \
QLA_DF_c1_veq_C_dot_pC.c \
QLA_DF_c1_veq_pC_dot_C.c \
QLA_DF_c1_veq_pC_dot_pC.c \
QLA_DF_c1_veq_sum_C.c \
QLA_DF_c1_veq_sum_pC.c \
QLA_DF_c1_xeq_C_dot_C.c \
QLA_DF_c1_xeq_C_dot_pC.c \
QLA_DF_c1_xeq_pC_dot_C.c \
QLA_DF_c1_xeq_pC_dot_pC.c \
QLA_DF_c1_xeq_sum_C.c \
QLA_DF_c1_xeq_sum_pC.c \
QLA_DF_C_eq_C.c \
QLA_DF_C_veq_C.c \
QLA_DF_C_veq_pC.c \
QLA_DF_C_xeq_C.c \
QLA_DF_C_xeq_pC.c \
QLA_DF_r1_eq_norm2_C.c \
QLA_DF_r1_eq_norm2_R.c \
QLA_DF_r1_eq_R_dot_R.c \
QLA_DF_r1_eq_re_C_dot_C.c \
QLA_DF_r1_eq_sum_R.c \
QLA_DF_r1_veq_norm2_C.c \
QLA_DF_r1_veq_norm2_pC.c \
QLA_DF_r1_veq_norm2_pR.c \
QLA_DF_r1_veq_norm2_R.c \
QLA_DF_r1_veq_pR_dot_pR.c \
QLA_DF_r1_veq_pR_dot_R.c \
QLA_DF_r1_veq_R_dot_pR.c \
QLA_DF_r1_veq_R_dot_R.c \
QLA_DF_r1_veq_re_C_dot_C.c \
QLA_DF_r1_veq_re_C_dot_pC.c \
QLA_DF_r1_veq_re_pC_dot_C.c \
QLA_DF_r1_veq_re_pC_dot_pC.c \
QLA_DF_r1_veq_sum_pR.c \
QLA_DF_r1_veq_sum_R.c \
QLA_DF_r1_xeq_norm2_C.c \
QLA_DF_r1_xeq_norm2_pC.c \
QLA_DF_r1_xeq_norm2_pR.c \
QLA_DF_r1_xeq_norm2_R.c \
QLA_DF_r1_xeq_pR_dot_pR.c \
QLA_DF_r1_xeq_pR_dot_R.c \
QLA_DF_r1_xeq_R_dot_pR.c \
QLA_DF_r1_xeq_R_dot_R.c \
QLA_DF_r1_xeq_re_C_dot_C.c \
QLA_DF_r1_xeq_re_C_dot_pC.c \
QLA_DF_r1_xeq_re_pC_dot_C.c \
QLA_DF_r1_xeq_re_pC_dot_pC.c \
QLA_DF_r1_xeq_sum_pR.c \
QLA_DF_r1_xeq_sum_R.c \
QLA_DF_R_eq_R.c \
QLA_DF_R_veq_pR.c \
QLA_DF_R_veq_R.c \
QLA_DF_R_xeq_pR.c \
QLA_DF_R_xeq_R.c \
QLA_FD_C_eq_C.c \
QLA_FD_C_veq_C.c \
QLA_FD_C_veq_pC.c \
QLA_FD_C_xeq_C.c \
QLA_FD_C_xeq_pC.c \
QLA_FD_R_eq_R.c \
QLA_FD_R_veq_pR.c \
QLA_FD_R_veq_R.c \
QLA_FD_R_xeq_pR.c \
QLA_FD_R_xeq_R.c

QLAOBJ1 = \
QLA_DF_c1_eq_C_dot_C.o \
QLA_DF_c1_eq_sum_C.o \
QLA_DF_c1_veq_C_dot_C.o \
QLA_DF_c1_veq_C_dot_pC.o \
QLA_DF_c1_veq_pC_dot_C.o \
QLA_DF_c1_veq_pC_dot_pC.o \
QLA_DF_c1_veq_sum_C.o \
QLA_DF_c1_veq_sum_pC.o \
QLA_DF_c1_xeq_C_dot_C.o \
QLA_DF_c1_xeq_C_dot_pC.o \
QLA_DF_c1_xeq_pC_dot_C.o \
QLA_DF_c1_xeq_pC_dot_pC.o \
QLA_DF_c1_xeq_sum_C.o \
QLA_DF_c1_xeq_sum_pC.o \
QLA_DF_C_eq_C.o \
QLA_DF_C_veq_C.o \
QLA_DF_C_veq_pC.o \
QLA_DF_C_xeq_C.o \
QLA_DF_C_xeq_pC.o \
QLA_DF_r1_eq_norm2_C.o \
QLA_DF_r1_eq_norm2_R.o \
QLA_DF_r1_eq_R_dot_R.o \
QLA_DF_r1_eq_re_C_dot_C.o \
QLA_DF_r1_eq_sum_R.o \
QLA_DF_r1_veq_norm2_C.o \
QLA_DF_r1_veq_norm2_pC.o \
QLA_DF_r1_veq_norm2_pR.o \
QLA_DF_r1_veq_norm2_R.o \
QLA_DF_r1_veq_pR_dot_pR.o \
QLA_DF_r1_veq_pR_dot_R.o \
QLA_DF_r1_veq_R_dot_pR.o \
QLA_DF_r1_veq_R_dot_R.o \
QLA_DF_r1_veq_re_C_dot_C.o \
QLA_DF_r1_veq_re_C_dot_pC.o \
QLA_DF_r1_veq_re_pC_dot_C.o \
QLA_DF_r1_veq_re_pC_dot_pC.o \
QLA_DF_r1_veq_sum_pR.o \
QLA_DF_r1_veq_sum_R.o \
QLA_DF_r1_xeq_norm2_C.o \
QLA_DF_r1_xeq_norm2_pC.o \
QLA_DF_r1_xeq_norm2_pR.o \
QLA_DF_r1_xeq_norm2_R.o \
QLA_DF_r1_xeq_pR_dot_pR.o \
QLA_DF_r1_xeq_pR_dot_R.o \
QLA_DF_r1_xeq_R_dot_pR.o \
QLA_DF_r1_xeq_R_dot_R.o \
QLA_DF_r1_xeq_re_C_dot_C.o \
QLA_DF_r1_xeq_re_C_dot_pC.o \
QLA_DF_r1_xeq_re_pC_dot_C.o \
QLA_DF_r1_xeq_re_pC_dot_pC.o \
QLA_DF_r1_xeq_sum_pR.o \
QLA_DF_r1_xeq_sum_R.o \
QLA_DF_R_eq_R.o \
QLA_DF_R_veq_pR.o \
QLA_DF_R_veq_R.o \
QLA_DF_R_xeq_pR.o \
QLA_DF_R_xeq_R.o \
QLA_FD_C_eq_C.o \
QLA_FD_C_veq_C.o \
QLA_FD_C_veq_pC.o \
QLA_FD_C_xeq_C.o \
QLA_FD_C_xeq_pC.o \
QLA_FD_R_eq_R.o \
QLA_FD_R_veq_pR.o \
QLA_FD_R_veq_R.o \
QLA_FD_R_xeq_pR.o \
QLA_FD_R_xeq_R.o

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

lib_LIBRARIES = ../libqla_df.a

AM_CFLAGS = -I$(top_srcdir)/include

# this is just to force automake to include the .c.o rule
nodist____libqla_df_a_SOURCES = QLA_DF_c1_eq_C_dot_C.c

nodist_include_HEADERS = $(top_builddir)/include/qla_df.h

source-stamp: $(BUILD_DEPS) 
	@rm -f source-temp
	@touch source-temp
	$(PERL) $(BUILD_SCRIPT) QLA_DF $(top_builddir)/include/qla_df.h .
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

../libqla_df.a: $(QLAOBJ) ../optimized/Makefile
	-rm -f ../libqla_df.a
	$(AR) $(ARFLAGS) ../libqla_df.a $(QLAOBJ1)
	$(RANLIB) ../libqla_df.a

clean-local:
	-rm -f $(nodist_include_HEADERS)
	-rm -f $(QLASRC1)
	-rm -f $(QLAOBJ1)
