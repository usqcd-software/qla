# Makefile.am for building the qla_q2 library

AUTOMAKE_OPTIONS = no-dependencies

QLASRC1 = \
QLA_Q2_D_eq_D.c \
QLA_Q2_D_eq_gaussian_S.c \
QLA_Q2_D_eq_zero.c \
QLA_Q2_D_eqm_D.c \
QLA_Q2_D_meq_D.c \
QLA_Q2_D_peq_D.c \
QLA_Q2_D_veq_D.c \
QLA_Q2_D_veq_gaussian_S.c \
QLA_Q2_D_veq_gaussian_pS.c \
QLA_Q2_D_veq_pD.c \
QLA_Q2_D_veq_zero.c \
QLA_Q2_D_veqm_D.c \
QLA_Q2_D_veqm_pD.c \
QLA_Q2_D_vmeq_D.c \
QLA_Q2_D_vmeq_pD.c \
QLA_Q2_D_vpeq_D.c \
QLA_Q2_D_vpeq_pD.c \
QLA_Q2_D_xeq_D.c \
QLA_Q2_D_xeq_gaussian_S.c \
QLA_Q2_D_xeq_gaussian_pS.c \
QLA_Q2_D_xeq_pD.c \
QLA_Q2_D_xeq_zero.c \
QLA_Q2_D_xeqm_D.c \
QLA_Q2_D_xeqm_pD.c \
QLA_Q2_D_xmeq_D.c \
QLA_Q2_D_xmeq_pD.c \
QLA_Q2_D_xpeq_D.c \
QLA_Q2_D_xpeq_pD.c \
QLA_Q2_H_eq_H.c \
QLA_Q2_H_eq_gaussian_S.c \
QLA_Q2_H_eq_zero.c \
QLA_Q2_H_eqm_H.c \
QLA_Q2_H_meq_H.c \
QLA_Q2_H_peq_H.c \
QLA_Q2_H_veq_H.c \
QLA_Q2_H_veq_gaussian_S.c \
QLA_Q2_H_veq_gaussian_pS.c \
QLA_Q2_H_veq_pH.c \
QLA_Q2_H_veq_zero.c \
QLA_Q2_H_veqm_H.c \
QLA_Q2_H_veqm_pH.c \
QLA_Q2_H_vmeq_H.c \
QLA_Q2_H_vmeq_pH.c \
QLA_Q2_H_vpeq_H.c \
QLA_Q2_H_vpeq_pH.c \
QLA_Q2_H_xeq_H.c \
QLA_Q2_H_xeq_gaussian_S.c \
QLA_Q2_H_xeq_gaussian_pS.c \
QLA_Q2_H_xeq_pH.c \
QLA_Q2_H_xeq_zero.c \
QLA_Q2_H_xeqm_H.c \
QLA_Q2_H_xeqm_pH.c \
QLA_Q2_H_xmeq_H.c \
QLA_Q2_H_xmeq_pH.c \
QLA_Q2_H_xpeq_H.c \
QLA_Q2_H_xpeq_pH.c \
QLA_Q2_M_eq_M.c \
QLA_Q2_M_eq_gaussian_S.c \
QLA_Q2_M_eq_zero.c \
QLA_Q2_M_eqm_M.c \
QLA_Q2_M_meq_M.c \
QLA_Q2_M_peq_M.c \
QLA_Q2_M_veq_M.c \
QLA_Q2_M_veq_gaussian_S.c \
QLA_Q2_M_veq_gaussian_pS.c \
QLA_Q2_M_veq_pM.c \
QLA_Q2_M_veq_zero.c \
QLA_Q2_M_veqm_M.c \
QLA_Q2_M_veqm_pM.c \
QLA_Q2_M_vmeq_M.c \
QLA_Q2_M_vmeq_pM.c \
QLA_Q2_M_vpeq_M.c \
QLA_Q2_M_vpeq_pM.c \
QLA_Q2_M_xeq_M.c \
QLA_Q2_M_xeq_gaussian_S.c \
QLA_Q2_M_xeq_gaussian_pS.c \
QLA_Q2_M_xeq_pM.c \
QLA_Q2_M_xeq_zero.c \
QLA_Q2_M_xeqm_M.c \
QLA_Q2_M_xeqm_pM.c \
QLA_Q2_M_xmeq_M.c \
QLA_Q2_M_xmeq_pM.c \
QLA_Q2_M_xpeq_M.c \
QLA_Q2_M_xpeq_pM.c \
QLA_Q2_P_eq_P.c \
QLA_Q2_P_eq_gaussian_S.c \
QLA_Q2_P_eq_zero.c \
QLA_Q2_P_eqm_P.c \
QLA_Q2_P_meq_P.c \
QLA_Q2_P_peq_P.c \
QLA_Q2_P_veq_P.c \
QLA_Q2_P_veq_gaussian_S.c \
QLA_Q2_P_veq_gaussian_pS.c \
QLA_Q2_P_veq_pP.c \
QLA_Q2_P_veq_zero.c \
QLA_Q2_P_veqm_P.c \
QLA_Q2_P_veqm_pP.c \
QLA_Q2_P_vmeq_P.c \
QLA_Q2_P_vmeq_pP.c \
QLA_Q2_P_vpeq_P.c \
QLA_Q2_P_vpeq_pP.c \
QLA_Q2_P_xeq_P.c \
QLA_Q2_P_xeq_gaussian_S.c \
QLA_Q2_P_xeq_gaussian_pS.c \
QLA_Q2_P_xeq_pP.c \
QLA_Q2_P_xeq_zero.c \
QLA_Q2_P_xeqm_P.c \
QLA_Q2_P_xeqm_pP.c \
QLA_Q2_P_xmeq_P.c \
QLA_Q2_P_xmeq_pP.c \
QLA_Q2_P_xpeq_P.c \
QLA_Q2_P_xpeq_pP.c \
QLA_Q2_V_eq_V.c \
QLA_Q2_V_eq_gaussian_S.c \
QLA_Q2_V_eq_zero.c \
QLA_Q2_V_eqm_V.c \
QLA_Q2_V_meq_V.c \
QLA_Q2_V_peq_V.c \
QLA_Q2_V_veq_V.c \
QLA_Q2_V_veq_gaussian_S.c \
QLA_Q2_V_veq_gaussian_pS.c \
QLA_Q2_V_veq_pV.c \
QLA_Q2_V_veq_zero.c \
QLA_Q2_V_veqm_V.c \
QLA_Q2_V_veqm_pV.c \
QLA_Q2_V_vmeq_V.c \
QLA_Q2_V_vmeq_pV.c \
QLA_Q2_V_vpeq_V.c \
QLA_Q2_V_vpeq_pV.c \
QLA_Q2_V_xeq_V.c \
QLA_Q2_V_xeq_gaussian_S.c \
QLA_Q2_V_xeq_gaussian_pS.c \
QLA_Q2_V_xeq_pV.c \
QLA_Q2_V_xeq_zero.c \
QLA_Q2_V_xeqm_V.c \
QLA_Q2_V_xeqm_pV.c \
QLA_Q2_V_xmeq_V.c \
QLA_Q2_V_xmeq_pV.c \
QLA_Q2_V_xpeq_V.c \
QLA_Q2_V_xpeq_pV.c

QLAOBJ1 = \
QLA_Q2_D_eq_D.o \
QLA_Q2_D_eq_gaussian_S.o \
QLA_Q2_D_eq_zero.o \
QLA_Q2_D_eqm_D.o \
QLA_Q2_D_meq_D.o \
QLA_Q2_D_peq_D.o \
QLA_Q2_D_veq_D.o \
QLA_Q2_D_veq_gaussian_S.o \
QLA_Q2_D_veq_gaussian_pS.o \
QLA_Q2_D_veq_pD.o \
QLA_Q2_D_veq_zero.o \
QLA_Q2_D_veqm_D.o \
QLA_Q2_D_veqm_pD.o \
QLA_Q2_D_vmeq_D.o \
QLA_Q2_D_vmeq_pD.o \
QLA_Q2_D_vpeq_D.o \
QLA_Q2_D_vpeq_pD.o \
QLA_Q2_D_xeq_D.o \
QLA_Q2_D_xeq_gaussian_S.o \
QLA_Q2_D_xeq_gaussian_pS.o \
QLA_Q2_D_xeq_pD.o \
QLA_Q2_D_xeq_zero.o \
QLA_Q2_D_xeqm_D.o \
QLA_Q2_D_xeqm_pD.o \
QLA_Q2_D_xmeq_D.o \
QLA_Q2_D_xmeq_pD.o \
QLA_Q2_D_xpeq_D.o \
QLA_Q2_D_xpeq_pD.o \
QLA_Q2_H_eq_H.o \
QLA_Q2_H_eq_gaussian_S.o \
QLA_Q2_H_eq_zero.o \
QLA_Q2_H_eqm_H.o \
QLA_Q2_H_meq_H.o \
QLA_Q2_H_peq_H.o \
QLA_Q2_H_veq_H.o \
QLA_Q2_H_veq_gaussian_S.o \
QLA_Q2_H_veq_gaussian_pS.o \
QLA_Q2_H_veq_pH.o \
QLA_Q2_H_veq_zero.o \
QLA_Q2_H_veqm_H.o \
QLA_Q2_H_veqm_pH.o \
QLA_Q2_H_vmeq_H.o \
QLA_Q2_H_vmeq_pH.o \
QLA_Q2_H_vpeq_H.o \
QLA_Q2_H_vpeq_pH.o \
QLA_Q2_H_xeq_H.o \
QLA_Q2_H_xeq_gaussian_S.o \
QLA_Q2_H_xeq_gaussian_pS.o \
QLA_Q2_H_xeq_pH.o \
QLA_Q2_H_xeq_zero.o \
QLA_Q2_H_xeqm_H.o \
QLA_Q2_H_xeqm_pH.o \
QLA_Q2_H_xmeq_H.o \
QLA_Q2_H_xmeq_pH.o \
QLA_Q2_H_xpeq_H.o \
QLA_Q2_H_xpeq_pH.o \
QLA_Q2_M_eq_M.o \
QLA_Q2_M_eq_gaussian_S.o \
QLA_Q2_M_eq_zero.o \
QLA_Q2_M_eqm_M.o \
QLA_Q2_M_meq_M.o \
QLA_Q2_M_peq_M.o \
QLA_Q2_M_veq_M.o \
QLA_Q2_M_veq_gaussian_S.o \
QLA_Q2_M_veq_gaussian_pS.o \
QLA_Q2_M_veq_pM.o \
QLA_Q2_M_veq_zero.o \
QLA_Q2_M_veqm_M.o \
QLA_Q2_M_veqm_pM.o \
QLA_Q2_M_vmeq_M.o \
QLA_Q2_M_vmeq_pM.o \
QLA_Q2_M_vpeq_M.o \
QLA_Q2_M_vpeq_pM.o \
QLA_Q2_M_xeq_M.o \
QLA_Q2_M_xeq_gaussian_S.o \
QLA_Q2_M_xeq_gaussian_pS.o \
QLA_Q2_M_xeq_pM.o \
QLA_Q2_M_xeq_zero.o \
QLA_Q2_M_xeqm_M.o \
QLA_Q2_M_xeqm_pM.o \
QLA_Q2_M_xmeq_M.o \
QLA_Q2_M_xmeq_pM.o \
QLA_Q2_M_xpeq_M.o \
QLA_Q2_M_xpeq_pM.o \
QLA_Q2_P_eq_P.o \
QLA_Q2_P_eq_gaussian_S.o \
QLA_Q2_P_eq_zero.o \
QLA_Q2_P_eqm_P.o \
QLA_Q2_P_meq_P.o \
QLA_Q2_P_peq_P.o \
QLA_Q2_P_veq_P.o \
QLA_Q2_P_veq_gaussian_S.o \
QLA_Q2_P_veq_gaussian_pS.o \
QLA_Q2_P_veq_pP.o \
QLA_Q2_P_veq_zero.o \
QLA_Q2_P_veqm_P.o \
QLA_Q2_P_veqm_pP.o \
QLA_Q2_P_vmeq_P.o \
QLA_Q2_P_vmeq_pP.o \
QLA_Q2_P_vpeq_P.o \
QLA_Q2_P_vpeq_pP.o \
QLA_Q2_P_xeq_P.o \
QLA_Q2_P_xeq_gaussian_S.o \
QLA_Q2_P_xeq_gaussian_pS.o \
QLA_Q2_P_xeq_pP.o \
QLA_Q2_P_xeq_zero.o \
QLA_Q2_P_xeqm_P.o \
QLA_Q2_P_xeqm_pP.o \
QLA_Q2_P_xmeq_P.o \
QLA_Q2_P_xmeq_pP.o \
QLA_Q2_P_xpeq_P.o \
QLA_Q2_P_xpeq_pP.o \
QLA_Q2_V_eq_V.o \
QLA_Q2_V_eq_gaussian_S.o \
QLA_Q2_V_eq_zero.o \
QLA_Q2_V_eqm_V.o \
QLA_Q2_V_meq_V.o \
QLA_Q2_V_peq_V.o \
QLA_Q2_V_veq_V.o \
QLA_Q2_V_veq_gaussian_S.o \
QLA_Q2_V_veq_gaussian_pS.o \
QLA_Q2_V_veq_pV.o \
QLA_Q2_V_veq_zero.o \
QLA_Q2_V_veqm_V.o \
QLA_Q2_V_veqm_pV.o \
QLA_Q2_V_vmeq_V.o \
QLA_Q2_V_vmeq_pV.o \
QLA_Q2_V_vpeq_V.o \
QLA_Q2_V_vpeq_pV.o \
QLA_Q2_V_xeq_V.o \
QLA_Q2_V_xeq_gaussian_S.o \
QLA_Q2_V_xeq_gaussian_pS.o \
QLA_Q2_V_xeq_pV.o \
QLA_Q2_V_xeq_zero.o \
QLA_Q2_V_xeqm_V.o \
QLA_Q2_V_xeqm_pV.o \
QLA_Q2_V_xmeq_V.o \
QLA_Q2_V_xmeq_pV.o \
QLA_Q2_V_xpeq_V.o \
QLA_Q2_V_xpeq_pV.o

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

lib_LIBRARIES = ../libqla_q2.a

AM_CFLAGS = -I$(top_srcdir)/include  -DQLA_Colors=2

# this is just to force automake to include the .c.o rule
nodist____libqla_q2_a_SOURCES = QLA_Q2_D_eq_D.c

nodist_include_HEADERS = $(top_builddir)/include/qla_q2.h $(top_builddir)/include/qla_q2_generic.h $(top_builddir)/include/qla_q2_color_generic.h

source-stamp: $(BUILD_DEPS) 
	@rm -f source-temp
	@touch source-temp
	$(PERL) $(BUILD_SCRIPT) QLA_Q2 $(top_builddir)/include/qla_q2.h .
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

../libqla_q2.a: $(QLAOBJ) ../optimized/Makefile
	-rm -f ../libqla_q2.a
	$(AR) $(ARFLAGS) ../libqla_q2.a $(QLAOBJ1)
	$(RANLIB) ../libqla_q2.a

clean-local:
	-rm -f $(nodist_include_HEADERS) source-stamp
	-rm -f $(QLASRC1)
	-rm -f $(QLAOBJ1)
