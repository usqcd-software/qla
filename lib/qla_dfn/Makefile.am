# Makefile.am for building the qla_dfn library

AUTOMAKE_OPTIONS = no-dependencies

QLASRC1 = \
QLA_DFN_D_eq_D.c \
QLA_DFN_D_veq_D.c \
QLA_DFN_D_veq_pD.c \
QLA_DFN_D_xeq_D.c \
QLA_DFN_D_xeq_pD.c \
QLA_DFN_H_eq_H.c \
QLA_DFN_H_veq_H.c \
QLA_DFN_H_veq_pH.c \
QLA_DFN_H_xeq_H.c \
QLA_DFN_H_xeq_pH.c \
QLA_DFN_M_eq_M.c \
QLA_DFN_M_veq_M.c \
QLA_DFN_M_veq_pM.c \
QLA_DFN_M_xeq_M.c \
QLA_DFN_M_xeq_pM.c \
QLA_DFN_P_eq_P.c \
QLA_DFN_P_veq_P.c \
QLA_DFN_P_veq_pP.c \
QLA_DFN_P_xeq_P.c \
QLA_DFN_P_xeq_pP.c \
QLA_DFN_V_eq_V.c \
QLA_DFN_V_veq_V.c \
QLA_DFN_V_veq_pV.c \
QLA_DFN_V_xeq_V.c \
QLA_DFN_V_xeq_pV.c \
QLA_DFN_c1_eq_D_dot_D.c \
QLA_DFN_c1_eq_H_dot_H.c \
QLA_DFN_c1_eq_M_dot_M.c \
QLA_DFN_c1_eq_P_dot_P.c \
QLA_DFN_c1_eq_V_dot_V.c \
QLA_DFN_c1_veq_D_dot_D.c \
QLA_DFN_c1_veq_D_dot_pD.c \
QLA_DFN_c1_veq_H_dot_H.c \
QLA_DFN_c1_veq_H_dot_pH.c \
QLA_DFN_c1_veq_M_dot_M.c \
QLA_DFN_c1_veq_M_dot_pM.c \
QLA_DFN_c1_veq_P_dot_P.c \
QLA_DFN_c1_veq_P_dot_pP.c \
QLA_DFN_c1_veq_V_dot_V.c \
QLA_DFN_c1_veq_V_dot_pV.c \
QLA_DFN_c1_veq_pD_dot_D.c \
QLA_DFN_c1_veq_pD_dot_pD.c \
QLA_DFN_c1_veq_pH_dot_H.c \
QLA_DFN_c1_veq_pH_dot_pH.c \
QLA_DFN_c1_veq_pM_dot_M.c \
QLA_DFN_c1_veq_pM_dot_pM.c \
QLA_DFN_c1_veq_pP_dot_P.c \
QLA_DFN_c1_veq_pP_dot_pP.c \
QLA_DFN_c1_veq_pV_dot_V.c \
QLA_DFN_c1_veq_pV_dot_pV.c \
QLA_DFN_c1_xeq_D_dot_D.c \
QLA_DFN_c1_xeq_D_dot_pD.c \
QLA_DFN_c1_xeq_H_dot_H.c \
QLA_DFN_c1_xeq_H_dot_pH.c \
QLA_DFN_c1_xeq_M_dot_M.c \
QLA_DFN_c1_xeq_M_dot_pM.c \
QLA_DFN_c1_xeq_P_dot_P.c \
QLA_DFN_c1_xeq_P_dot_pP.c \
QLA_DFN_c1_xeq_V_dot_V.c \
QLA_DFN_c1_xeq_V_dot_pV.c \
QLA_DFN_c1_xeq_pD_dot_D.c \
QLA_DFN_c1_xeq_pD_dot_pD.c \
QLA_DFN_c1_xeq_pH_dot_H.c \
QLA_DFN_c1_xeq_pH_dot_pH.c \
QLA_DFN_c1_xeq_pM_dot_M.c \
QLA_DFN_c1_xeq_pM_dot_pM.c \
QLA_DFN_c1_xeq_pP_dot_P.c \
QLA_DFN_c1_xeq_pP_dot_pP.c \
QLA_DFN_c1_xeq_pV_dot_V.c \
QLA_DFN_c1_xeq_pV_dot_pV.c \
QLA_DFN_d1_eq_sum_D.c \
QLA_DFN_d1_veq_sum_D.c \
QLA_DFN_d1_veq_sum_pD.c \
QLA_DFN_d1_xeq_sum_D.c \
QLA_DFN_d1_xeq_sum_pD.c \
QLA_DFN_h1_eq_sum_H.c \
QLA_DFN_h1_veq_sum_H.c \
QLA_DFN_h1_veq_sum_pH.c \
QLA_DFN_h1_xeq_sum_H.c \
QLA_DFN_h1_xeq_sum_pH.c \
QLA_DFN_m1_eq_sum_M.c \
QLA_DFN_m1_veq_sum_M.c \
QLA_DFN_m1_veq_sum_pM.c \
QLA_DFN_m1_xeq_sum_M.c \
QLA_DFN_m1_xeq_sum_pM.c \
QLA_DFN_p1_eq_sum_P.c \
QLA_DFN_p1_veq_sum_P.c \
QLA_DFN_p1_veq_sum_pP.c \
QLA_DFN_p1_xeq_sum_P.c \
QLA_DFN_p1_xeq_sum_pP.c \
QLA_DFN_r1_eq_norm2_D.c \
QLA_DFN_r1_eq_norm2_H.c \
QLA_DFN_r1_eq_norm2_M.c \
QLA_DFN_r1_eq_norm2_P.c \
QLA_DFN_r1_eq_norm2_V.c \
QLA_DFN_r1_eq_re_D_dot_D.c \
QLA_DFN_r1_eq_re_H_dot_H.c \
QLA_DFN_r1_eq_re_M_dot_M.c \
QLA_DFN_r1_eq_re_P_dot_P.c \
QLA_DFN_r1_eq_re_V_dot_V.c \
QLA_DFN_r1_veq_norm2_D.c \
QLA_DFN_r1_veq_norm2_H.c \
QLA_DFN_r1_veq_norm2_M.c \
QLA_DFN_r1_veq_norm2_P.c \
QLA_DFN_r1_veq_norm2_V.c \
QLA_DFN_r1_veq_norm2_pD.c \
QLA_DFN_r1_veq_norm2_pH.c \
QLA_DFN_r1_veq_norm2_pM.c \
QLA_DFN_r1_veq_norm2_pP.c \
QLA_DFN_r1_veq_norm2_pV.c \
QLA_DFN_r1_veq_re_D_dot_D.c \
QLA_DFN_r1_veq_re_D_dot_pD.c \
QLA_DFN_r1_veq_re_H_dot_H.c \
QLA_DFN_r1_veq_re_H_dot_pH.c \
QLA_DFN_r1_veq_re_M_dot_M.c \
QLA_DFN_r1_veq_re_M_dot_pM.c \
QLA_DFN_r1_veq_re_P_dot_P.c \
QLA_DFN_r1_veq_re_P_dot_pP.c \
QLA_DFN_r1_veq_re_V_dot_V.c \
QLA_DFN_r1_veq_re_V_dot_pV.c \
QLA_DFN_r1_veq_re_pD_dot_D.c \
QLA_DFN_r1_veq_re_pD_dot_pD.c \
QLA_DFN_r1_veq_re_pH_dot_H.c \
QLA_DFN_r1_veq_re_pH_dot_pH.c \
QLA_DFN_r1_veq_re_pM_dot_M.c \
QLA_DFN_r1_veq_re_pM_dot_pM.c \
QLA_DFN_r1_veq_re_pP_dot_P.c \
QLA_DFN_r1_veq_re_pP_dot_pP.c \
QLA_DFN_r1_veq_re_pV_dot_V.c \
QLA_DFN_r1_veq_re_pV_dot_pV.c \
QLA_DFN_r1_xeq_norm2_D.c \
QLA_DFN_r1_xeq_norm2_H.c \
QLA_DFN_r1_xeq_norm2_M.c \
QLA_DFN_r1_xeq_norm2_P.c \
QLA_DFN_r1_xeq_norm2_V.c \
QLA_DFN_r1_xeq_norm2_pD.c \
QLA_DFN_r1_xeq_norm2_pH.c \
QLA_DFN_r1_xeq_norm2_pM.c \
QLA_DFN_r1_xeq_norm2_pP.c \
QLA_DFN_r1_xeq_norm2_pV.c \
QLA_DFN_r1_xeq_re_D_dot_D.c \
QLA_DFN_r1_xeq_re_D_dot_pD.c \
QLA_DFN_r1_xeq_re_H_dot_H.c \
QLA_DFN_r1_xeq_re_H_dot_pH.c \
QLA_DFN_r1_xeq_re_M_dot_M.c \
QLA_DFN_r1_xeq_re_M_dot_pM.c \
QLA_DFN_r1_xeq_re_P_dot_P.c \
QLA_DFN_r1_xeq_re_P_dot_pP.c \
QLA_DFN_r1_xeq_re_V_dot_V.c \
QLA_DFN_r1_xeq_re_V_dot_pV.c \
QLA_DFN_r1_xeq_re_pD_dot_D.c \
QLA_DFN_r1_xeq_re_pD_dot_pD.c \
QLA_DFN_r1_xeq_re_pH_dot_H.c \
QLA_DFN_r1_xeq_re_pH_dot_pH.c \
QLA_DFN_r1_xeq_re_pM_dot_M.c \
QLA_DFN_r1_xeq_re_pM_dot_pM.c \
QLA_DFN_r1_xeq_re_pP_dot_P.c \
QLA_DFN_r1_xeq_re_pP_dot_pP.c \
QLA_DFN_r1_xeq_re_pV_dot_V.c \
QLA_DFN_r1_xeq_re_pV_dot_pV.c \
QLA_DFN_v1_eq_sum_V.c \
QLA_DFN_v1_veq_sum_V.c \
QLA_DFN_v1_veq_sum_pV.c \
QLA_DFN_v1_xeq_sum_V.c \
QLA_DFN_v1_xeq_sum_pV.c \
QLA_FDN_D_eq_D.c \
QLA_FDN_D_veq_D.c \
QLA_FDN_D_veq_pD.c \
QLA_FDN_D_xeq_D.c \
QLA_FDN_D_xeq_pD.c \
QLA_FDN_H_eq_H.c \
QLA_FDN_H_veq_H.c \
QLA_FDN_H_veq_pH.c \
QLA_FDN_H_xeq_H.c \
QLA_FDN_H_xeq_pH.c \
QLA_FDN_M_eq_M.c \
QLA_FDN_M_veq_M.c \
QLA_FDN_M_veq_pM.c \
QLA_FDN_M_xeq_M.c \
QLA_FDN_M_xeq_pM.c \
QLA_FDN_P_eq_P.c \
QLA_FDN_P_veq_P.c \
QLA_FDN_P_veq_pP.c \
QLA_FDN_P_xeq_P.c \
QLA_FDN_P_xeq_pP.c \
QLA_FDN_V_eq_V.c \
QLA_FDN_V_veq_V.c \
QLA_FDN_V_veq_pV.c \
QLA_FDN_V_xeq_V.c \
QLA_FDN_V_xeq_pV.c

QLAOBJ1 = \
QLA_DFN_D_eq_D.o \
QLA_DFN_D_veq_D.o \
QLA_DFN_D_veq_pD.o \
QLA_DFN_D_xeq_D.o \
QLA_DFN_D_xeq_pD.o \
QLA_DFN_H_eq_H.o \
QLA_DFN_H_veq_H.o \
QLA_DFN_H_veq_pH.o \
QLA_DFN_H_xeq_H.o \
QLA_DFN_H_xeq_pH.o \
QLA_DFN_M_eq_M.o \
QLA_DFN_M_veq_M.o \
QLA_DFN_M_veq_pM.o \
QLA_DFN_M_xeq_M.o \
QLA_DFN_M_xeq_pM.o \
QLA_DFN_P_eq_P.o \
QLA_DFN_P_veq_P.o \
QLA_DFN_P_veq_pP.o \
QLA_DFN_P_xeq_P.o \
QLA_DFN_P_xeq_pP.o \
QLA_DFN_V_eq_V.o \
QLA_DFN_V_veq_V.o \
QLA_DFN_V_veq_pV.o \
QLA_DFN_V_xeq_V.o \
QLA_DFN_V_xeq_pV.o \
QLA_DFN_c1_eq_D_dot_D.o \
QLA_DFN_c1_eq_H_dot_H.o \
QLA_DFN_c1_eq_M_dot_M.o \
QLA_DFN_c1_eq_P_dot_P.o \
QLA_DFN_c1_eq_V_dot_V.o \
QLA_DFN_c1_veq_D_dot_D.o \
QLA_DFN_c1_veq_D_dot_pD.o \
QLA_DFN_c1_veq_H_dot_H.o \
QLA_DFN_c1_veq_H_dot_pH.o \
QLA_DFN_c1_veq_M_dot_M.o \
QLA_DFN_c1_veq_M_dot_pM.o \
QLA_DFN_c1_veq_P_dot_P.o \
QLA_DFN_c1_veq_P_dot_pP.o \
QLA_DFN_c1_veq_V_dot_V.o \
QLA_DFN_c1_veq_V_dot_pV.o \
QLA_DFN_c1_veq_pD_dot_D.o \
QLA_DFN_c1_veq_pD_dot_pD.o \
QLA_DFN_c1_veq_pH_dot_H.o \
QLA_DFN_c1_veq_pH_dot_pH.o \
QLA_DFN_c1_veq_pM_dot_M.o \
QLA_DFN_c1_veq_pM_dot_pM.o \
QLA_DFN_c1_veq_pP_dot_P.o \
QLA_DFN_c1_veq_pP_dot_pP.o \
QLA_DFN_c1_veq_pV_dot_V.o \
QLA_DFN_c1_veq_pV_dot_pV.o \
QLA_DFN_c1_xeq_D_dot_D.o \
QLA_DFN_c1_xeq_D_dot_pD.o \
QLA_DFN_c1_xeq_H_dot_H.o \
QLA_DFN_c1_xeq_H_dot_pH.o \
QLA_DFN_c1_xeq_M_dot_M.o \
QLA_DFN_c1_xeq_M_dot_pM.o \
QLA_DFN_c1_xeq_P_dot_P.o \
QLA_DFN_c1_xeq_P_dot_pP.o \
QLA_DFN_c1_xeq_V_dot_V.o \
QLA_DFN_c1_xeq_V_dot_pV.o \
QLA_DFN_c1_xeq_pD_dot_D.o \
QLA_DFN_c1_xeq_pD_dot_pD.o \
QLA_DFN_c1_xeq_pH_dot_H.o \
QLA_DFN_c1_xeq_pH_dot_pH.o \
QLA_DFN_c1_xeq_pM_dot_M.o \
QLA_DFN_c1_xeq_pM_dot_pM.o \
QLA_DFN_c1_xeq_pP_dot_P.o \
QLA_DFN_c1_xeq_pP_dot_pP.o \
QLA_DFN_c1_xeq_pV_dot_V.o \
QLA_DFN_c1_xeq_pV_dot_pV.o \
QLA_DFN_d1_eq_sum_D.o \
QLA_DFN_d1_veq_sum_D.o \
QLA_DFN_d1_veq_sum_pD.o \
QLA_DFN_d1_xeq_sum_D.o \
QLA_DFN_d1_xeq_sum_pD.o \
QLA_DFN_h1_eq_sum_H.o \
QLA_DFN_h1_veq_sum_H.o \
QLA_DFN_h1_veq_sum_pH.o \
QLA_DFN_h1_xeq_sum_H.o \
QLA_DFN_h1_xeq_sum_pH.o \
QLA_DFN_m1_eq_sum_M.o \
QLA_DFN_m1_veq_sum_M.o \
QLA_DFN_m1_veq_sum_pM.o \
QLA_DFN_m1_xeq_sum_M.o \
QLA_DFN_m1_xeq_sum_pM.o \
QLA_DFN_p1_eq_sum_P.o \
QLA_DFN_p1_veq_sum_P.o \
QLA_DFN_p1_veq_sum_pP.o \
QLA_DFN_p1_xeq_sum_P.o \
QLA_DFN_p1_xeq_sum_pP.o \
QLA_DFN_r1_eq_norm2_D.o \
QLA_DFN_r1_eq_norm2_H.o \
QLA_DFN_r1_eq_norm2_M.o \
QLA_DFN_r1_eq_norm2_P.o \
QLA_DFN_r1_eq_norm2_V.o \
QLA_DFN_r1_eq_re_D_dot_D.o \
QLA_DFN_r1_eq_re_H_dot_H.o \
QLA_DFN_r1_eq_re_M_dot_M.o \
QLA_DFN_r1_eq_re_P_dot_P.o \
QLA_DFN_r1_eq_re_V_dot_V.o \
QLA_DFN_r1_veq_norm2_D.o \
QLA_DFN_r1_veq_norm2_H.o \
QLA_DFN_r1_veq_norm2_M.o \
QLA_DFN_r1_veq_norm2_P.o \
QLA_DFN_r1_veq_norm2_V.o \
QLA_DFN_r1_veq_norm2_pD.o \
QLA_DFN_r1_veq_norm2_pH.o \
QLA_DFN_r1_veq_norm2_pM.o \
QLA_DFN_r1_veq_norm2_pP.o \
QLA_DFN_r1_veq_norm2_pV.o \
QLA_DFN_r1_veq_re_D_dot_D.o \
QLA_DFN_r1_veq_re_D_dot_pD.o \
QLA_DFN_r1_veq_re_H_dot_H.o \
QLA_DFN_r1_veq_re_H_dot_pH.o \
QLA_DFN_r1_veq_re_M_dot_M.o \
QLA_DFN_r1_veq_re_M_dot_pM.o \
QLA_DFN_r1_veq_re_P_dot_P.o \
QLA_DFN_r1_veq_re_P_dot_pP.o \
QLA_DFN_r1_veq_re_V_dot_V.o \
QLA_DFN_r1_veq_re_V_dot_pV.o \
QLA_DFN_r1_veq_re_pD_dot_D.o \
QLA_DFN_r1_veq_re_pD_dot_pD.o \
QLA_DFN_r1_veq_re_pH_dot_H.o \
QLA_DFN_r1_veq_re_pH_dot_pH.o \
QLA_DFN_r1_veq_re_pM_dot_M.o \
QLA_DFN_r1_veq_re_pM_dot_pM.o \
QLA_DFN_r1_veq_re_pP_dot_P.o \
QLA_DFN_r1_veq_re_pP_dot_pP.o \
QLA_DFN_r1_veq_re_pV_dot_V.o \
QLA_DFN_r1_veq_re_pV_dot_pV.o \
QLA_DFN_r1_xeq_norm2_D.o \
QLA_DFN_r1_xeq_norm2_H.o \
QLA_DFN_r1_xeq_norm2_M.o \
QLA_DFN_r1_xeq_norm2_P.o \
QLA_DFN_r1_xeq_norm2_V.o \
QLA_DFN_r1_xeq_norm2_pD.o \
QLA_DFN_r1_xeq_norm2_pH.o \
QLA_DFN_r1_xeq_norm2_pM.o \
QLA_DFN_r1_xeq_norm2_pP.o \
QLA_DFN_r1_xeq_norm2_pV.o \
QLA_DFN_r1_xeq_re_D_dot_D.o \
QLA_DFN_r1_xeq_re_D_dot_pD.o \
QLA_DFN_r1_xeq_re_H_dot_H.o \
QLA_DFN_r1_xeq_re_H_dot_pH.o \
QLA_DFN_r1_xeq_re_M_dot_M.o \
QLA_DFN_r1_xeq_re_M_dot_pM.o \
QLA_DFN_r1_xeq_re_P_dot_P.o \
QLA_DFN_r1_xeq_re_P_dot_pP.o \
QLA_DFN_r1_xeq_re_V_dot_V.o \
QLA_DFN_r1_xeq_re_V_dot_pV.o \
QLA_DFN_r1_xeq_re_pD_dot_D.o \
QLA_DFN_r1_xeq_re_pD_dot_pD.o \
QLA_DFN_r1_xeq_re_pH_dot_H.o \
QLA_DFN_r1_xeq_re_pH_dot_pH.o \
QLA_DFN_r1_xeq_re_pM_dot_M.o \
QLA_DFN_r1_xeq_re_pM_dot_pM.o \
QLA_DFN_r1_xeq_re_pP_dot_P.o \
QLA_DFN_r1_xeq_re_pP_dot_pP.o \
QLA_DFN_r1_xeq_re_pV_dot_V.o \
QLA_DFN_r1_xeq_re_pV_dot_pV.o \
QLA_DFN_v1_eq_sum_V.o \
QLA_DFN_v1_veq_sum_V.o \
QLA_DFN_v1_veq_sum_pV.o \
QLA_DFN_v1_xeq_sum_V.o \
QLA_DFN_v1_xeq_sum_pV.o \
QLA_FDN_D_eq_D.o \
QLA_FDN_D_veq_D.o \
QLA_FDN_D_veq_pD.o \
QLA_FDN_D_xeq_D.o \
QLA_FDN_D_xeq_pD.o \
QLA_FDN_H_eq_H.o \
QLA_FDN_H_veq_H.o \
QLA_FDN_H_veq_pH.o \
QLA_FDN_H_xeq_H.o \
QLA_FDN_H_xeq_pH.o \
QLA_FDN_M_eq_M.o \
QLA_FDN_M_veq_M.o \
QLA_FDN_M_veq_pM.o \
QLA_FDN_M_xeq_M.o \
QLA_FDN_M_xeq_pM.o \
QLA_FDN_P_eq_P.o \
QLA_FDN_P_veq_P.o \
QLA_FDN_P_veq_pP.o \
QLA_FDN_P_xeq_P.o \
QLA_FDN_P_xeq_pP.o \
QLA_FDN_V_eq_V.o \
QLA_FDN_V_veq_V.o \
QLA_FDN_V_veq_pV.o \
QLA_FDN_V_xeq_V.o \
QLA_FDN_V_xeq_pV.o

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

lib_LIBRARIES = ../libqla_dfn.a

AM_CFLAGS = -I$(top_srcdir)/include  -DQLA_Colors=\'N\'

# this is just to force automake to include the .c.o rule
nodist____libqla_dfn_a_SOURCES = QLA_DFN_D_eq_D.c

nodist_include_HEADERS = $(top_builddir)/include/qla_dfn.h $(top_builddir)/include/qla_dfn_color_generic.h

source-stamp: $(BUILD_DEPS) 
	@rm -f source-temp
	@touch source-temp
	$(PERL) $(BUILD_SCRIPT) QLA_DFN $(top_builddir)/include/qla_dfn.h .
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

../libqla_dfn.a: $(QLAOBJ) ../optimized/Makefile
	-rm -f ../libqla_dfn.a
	$(AR) $(ARFLAGS) ../libqla_dfn.a $(QLAOBJ1)
	$(RANLIB) ../libqla_dfn.a

clean-local:
	-rm -f $(nodist_include_HEADERS) source-stamp
	-rm -f $(QLASRC1)
	-rm -f $(QLAOBJ1)
