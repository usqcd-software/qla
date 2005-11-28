# Makefile.am for building the qla_dq library

AUTOMAKE_OPTIONS = no-dependencies

QLASRC1 = \
QLA_DQ_C_eq_C.c \
QLA_DQ_C_veq_C.c \
QLA_DQ_C_veq_pC.c \
QLA_DQ_C_xeq_C.c \
QLA_DQ_C_xeq_pC.c \
QLA_DQ_R_eq_R.c \
QLA_DQ_R_veq_pR.c \
QLA_DQ_R_veq_R.c \
QLA_DQ_R_xeq_pR.c \
QLA_DQ_R_xeq_R.c \
QLA_QD_c_eq_C_dot_C.c \
QLA_QD_c_eq_sum_C.c \
QLA_QD_c_veq_C_dot_C.c \
QLA_QD_c_veq_C_dot_pC.c \
QLA_QD_c_veq_pC_dot_C.c \
QLA_QD_c_veq_pC_dot_pC.c \
QLA_QD_c_veq_sum_C.c \
QLA_QD_c_veq_sum_pC.c \
QLA_QD_c_xeq_C_dot_C.c \
QLA_QD_c_xeq_C_dot_pC.c \
QLA_QD_c_xeq_pC_dot_C.c \
QLA_QD_c_xeq_pC_dot_pC.c \
QLA_QD_c_xeq_sum_C.c \
QLA_QD_c_xeq_sum_pC.c \
QLA_QD_r_eq_norm2_C.c \
QLA_QD_r_eq_norm2_R.c \
QLA_QD_r_eq_R_dot_R.c \
QLA_QD_r_eq_re_C_dot_C.c \
QLA_QD_r_eq_sum_R.c \
QLA_QD_r_veq_norm2_C.c \
QLA_QD_r_veq_norm2_pC.c \
QLA_QD_r_veq_norm2_pR.c \
QLA_QD_r_veq_norm2_R.c \
QLA_QD_r_veq_pR_dot_pR.c \
QLA_QD_r_veq_pR_dot_R.c \
QLA_QD_r_veq_R_dot_pR.c \
QLA_QD_r_veq_R_dot_R.c \
QLA_QD_r_veq_re_C_dot_C.c \
QLA_QD_r_veq_re_C_dot_pC.c \
QLA_QD_r_veq_re_pC_dot_C.c \
QLA_QD_r_veq_re_pC_dot_pC.c \
QLA_QD_r_veq_sum_pR.c \
QLA_QD_r_veq_sum_R.c \
QLA_QD_r_xeq_norm2_C.c \
QLA_QD_r_xeq_norm2_pC.c \
QLA_QD_r_xeq_norm2_pR.c \
QLA_QD_r_xeq_norm2_R.c \
QLA_QD_r_xeq_pR_dot_pR.c \
QLA_QD_r_xeq_pR_dot_R.c \
QLA_QD_r_xeq_R_dot_pR.c \
QLA_QD_r_xeq_R_dot_R.c \
QLA_QD_r_xeq_re_C_dot_C.c \
QLA_QD_r_xeq_re_C_dot_pC.c \
QLA_QD_r_xeq_re_pC_dot_C.c \
QLA_QD_r_xeq_re_pC_dot_pC.c \
QLA_QD_r_xeq_sum_pR.c \
QLA_QD_r_xeq_sum_R.c

QLAOBJ1 = \
QLA_DQ_C_eq_C.o \
QLA_DQ_C_veq_C.o \
QLA_DQ_C_veq_pC.o \
QLA_DQ_C_xeq_C.o \
QLA_DQ_C_xeq_pC.o \
QLA_DQ_R_eq_R.o \
QLA_DQ_R_veq_pR.o \
QLA_DQ_R_veq_R.o \
QLA_DQ_R_xeq_pR.o \
QLA_DQ_R_xeq_R.o \
QLA_QD_c_eq_C_dot_C.o \
QLA_QD_c_eq_sum_C.o \
QLA_QD_c_veq_C_dot_C.o \
QLA_QD_c_veq_C_dot_pC.o \
QLA_QD_c_veq_pC_dot_C.o \
QLA_QD_c_veq_pC_dot_pC.o \
QLA_QD_c_veq_sum_C.o \
QLA_QD_c_veq_sum_pC.o \
QLA_QD_c_xeq_C_dot_C.o \
QLA_QD_c_xeq_C_dot_pC.o \
QLA_QD_c_xeq_pC_dot_C.o \
QLA_QD_c_xeq_pC_dot_pC.o \
QLA_QD_c_xeq_sum_C.o \
QLA_QD_c_xeq_sum_pC.o \
QLA_QD_r_eq_norm2_C.o \
QLA_QD_r_eq_norm2_R.o \
QLA_QD_r_eq_R_dot_R.o \
QLA_QD_r_eq_re_C_dot_C.o \
QLA_QD_r_eq_sum_R.o \
QLA_QD_r_veq_norm2_C.o \
QLA_QD_r_veq_norm2_pC.o \
QLA_QD_r_veq_norm2_pR.o \
QLA_QD_r_veq_norm2_R.o \
QLA_QD_r_veq_pR_dot_pR.o \
QLA_QD_r_veq_pR_dot_R.o \
QLA_QD_r_veq_R_dot_pR.o \
QLA_QD_r_veq_R_dot_R.o \
QLA_QD_r_veq_re_C_dot_C.o \
QLA_QD_r_veq_re_C_dot_pC.o \
QLA_QD_r_veq_re_pC_dot_C.o \
QLA_QD_r_veq_re_pC_dot_pC.o \
QLA_QD_r_veq_sum_pR.o \
QLA_QD_r_veq_sum_R.o \
QLA_QD_r_xeq_norm2_C.o \
QLA_QD_r_xeq_norm2_pC.o \
QLA_QD_r_xeq_norm2_pR.o \
QLA_QD_r_xeq_norm2_R.o \
QLA_QD_r_xeq_pR_dot_pR.o \
QLA_QD_r_xeq_pR_dot_R.o \
QLA_QD_r_xeq_R_dot_pR.o \
QLA_QD_r_xeq_R_dot_R.o \
QLA_QD_r_xeq_re_C_dot_C.o \
QLA_QD_r_xeq_re_C_dot_pC.o \
QLA_QD_r_xeq_re_pC_dot_C.o \
QLA_QD_r_xeq_re_pC_dot_pC.o \
QLA_QD_r_xeq_sum_pR.o \
QLA_QD_r_xeq_sum_R.o

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

lib_LIBRARIES = ../libqla_dq.a

AM_CFLAGS = -I$(top_srcdir)/include

# this is just to force automake to include the .c.o rule
nodist____libqla_dq_a_SOURCES = QLA_DQ_C_eq_C.c

nodist_include_HEADERS = $(top_builddir)/include/qla_dq.h

$(QLASRC): $(BUILD_DEPS)
	$(PERL) $(BUILD_SCRIPT) QLA_DQ $(top_builddir)/include/qla_dq.h .

../libqla_dq.a: $(QLAOBJ) ../optimized/Makefile
	-rm -f ../libqla_dq.a
	$(AR) $(ARFLAGS) ../libqla_dq.a $(QLAOBJ1)
	$(RANLIB) ../libqla_dq.a

clean-local:
	-rm -f $(top_builddir)/include/qla_dq.h
	-rm -f $(QLASRC1)
	-rm -f $(QLAOBJ1)
