/* QLA test code */
/* for indexed tensor routines.  Precision conversion */
/* C Code automatically generated from test_df_tensor_idx.m4 */

include(protocol_idx.m4)

`
#include <qla.h>
#if QLA_Nc == 3
#include <qla_d3.h>
#include <qla_f3.h>
#elif QLA_Nc == 2
#include <qla_d2.h>
#include <qla_f2.h>
#else
#include <qla_dn.h>
#include <qla_fn.h>
#endif
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "compare.h"

int main(){
 
  QLA_D_Real                destrD,chkrD;
  QLA_D_Complex             destcD,chkcD;
  QLA_D_ColorMatrix         destmD,chkmD;
  QLA_D_HalfFermion         desthD,chkhD;
  QLA_D_DiracFermion        destdD,chkdD;
  QLA_D_ColorVector         destvD,chkvD;
  QLA_D_DiracPropagator     destpD,chkpD;

  QLA_Q_Real                destrQ,chkrQ;
  QLA_Q_Complex             destcQ,chkcQ;
  QLA_Q_ColorMatrix         destmQ,chkmQ;
  QLA_Q_HalfFermion         desthQ,chkhQ;
  QLA_Q_DiracFermion        destdQ,chkdQ;
  QLA_Q_ColorVector         destvQ,chkvQ;
  QLA_Q_DiracPropagator     destpQ,chkpQ;

  QLA_D_ColorMatrix         sMD1[MAX],sMD2[MAX],sMD3[MAX];
  QLA_D_HalfFermion         sHD1[MAX],sHD2[MAX],sHD3[MAX];
  QLA_D_DiracFermion        sDD1[MAX],sDD2[MAX],sDD3[MAX];
  QLA_D_ColorVector         sVD1[MAX],sVD2[MAX],sVD3[MAX];
  QLA_D_DiracPropagator     sPD1[MAX],sPD2[MAX],sPD3[MAX];

  QLA_Q_ColorMatrix         destMQ[MAX],chkMQ[MAX];
  QLA_Q_HalfFermion         destHQ[MAX],chkHQ[MAX];
  QLA_Q_DiracFermion        destDQ[MAX],chkDQ[MAX];
  QLA_Q_ColorVector         destVQ[MAX],chkVQ[MAX];
  QLA_Q_DiracPropagator     destPQ[MAX],chkPQ[MAX];

  QLA_D_ColorMatrix         destMD[MAX],chkMD[MAX];
  QLA_D_HalfFermion         destHD[MAX],chkHD[MAX];
  QLA_D_DiracFermion        destDD[MAX],chkDD[MAX];
  QLA_D_ColorVector         destVD[MAX],chkVD[MAX];
  QLA_D_DiracPropagator     destPD[MAX],chkPD[MAX];

  QLA_F_ColorMatrix         sMF1[MAX],sMF2[MAX],sMF3[MAX];
  QLA_F_HalfFermion         sHF1[MAX],sHF2[MAX],sHF3[MAX];
  QLA_F_DiracFermion        sDF1[MAX],sDF2[MAX],sDF3[MAX];
  QLA_F_ColorVector         sVF1[MAX],sVF2[MAX],sVF3[MAX];
  QLA_F_DiracPropagator     sPF1[MAX],sPF2[MAX],sPF3[MAX];

  QLA_F_ColorMatrix         destMF[MAX],chkMF[MAX];
  QLA_F_HalfFermion         destHF[MAX],chkHF[MAX];
  QLA_F_DiracFermion        destDF[MAX],chkDF[MAX];
  QLA_F_ColorVector         destVF[MAX],chkVF[MAX];
  QLA_F_DiracPropagator     destPF[MAX],chkPF[MAX];

  QLA_RandomState sS1[MAX];

  QLA_Int sI3[MAX] = { 92,  34, -21, -67, 104,
		   61, -10,  73, -96,  50};

  QLA_Int sI4      = 5001;

  int dMx[MAX]  = {9,1,8,5,6,0,3,7,2,4};
  int sM1x[MAX] = {0,2,9,7,6,1,4,5,8,3};
  int sM2x[MAX] = {3,6,4,0,1,2,9,7,5,8};

  int dHx[MAX]  = {9,2,6,1,4,5,7,0,8,3};
  int sH1x[MAX] = {4,6,1,2,9,7,0,3,5,8};
  int sH2x[MAX] = {8,1,6,0,3,7,5,9,2,4};

  int dDx[MAX]  = {4,1,2,9,7,5,3,6,0,8};
  int sD1x[MAX] = {8,6,0,3,7,2,9,1,5,4};
  int sD2x[MAX] = {9,6,1,4,5,8,0,2,7,3};

  int dVx[MAX]  = {4,2,5,1,6,0,3,8,9,7};
  int sV1x[MAX] = {6,4,0,2,1,9,7,3,5,8};
  int sV2x[MAX] = {1,9,3,6,2,4,0,8,7,5};

  int dPx[MAX]  = {9,7,3,2,5,8,6,4,0,1};
  int sP1x[MAX] = {3,7,9,0,2,4,1,8,5,6};
  int sP2x[MAX] = {2,9,5,6,7,8,1,0,3,4};

  QLA_D_ColorMatrix         *sMD1p[MAX], *sMD2p[MAX], *sMD3p[MAX];
  QLA_D_HalfFermion         *sHD1p[MAX], *sHD2p[MAX], *sHD3p[MAX];
  QLA_D_DiracFermion        *sDD1p[MAX], *sDD2p[MAX], *sDD3p[MAX];
  QLA_D_ColorVector         *sVD1p[MAX], *sVD2p[MAX], *sVD3p[MAX];
  QLA_D_DiracPropagator     *sPD1p[MAX], *sPD2p[MAX], *sPD3p[MAX];
			       		     	       	 	 
  QLA_F_ColorMatrix         *sMF1p[MAX], *sMF2p[MAX], *sMF3p[MAX];
  QLA_F_HalfFermion         *sHF1p[MAX], *sHF2p[MAX], *sHF3p[MAX];
  QLA_F_DiracFermion        *sDF1p[MAX], *sDF2p[MAX], *sDF3p[MAX];
  QLA_F_ColorVector         *sVF1p[MAX], *sVF2p[MAX], *sVF3p[MAX];
  QLA_F_DiracPropagator     *sPF1p[MAX], *sPF2p[MAX], *sPF3p[MAX];

  int i;
  int ic,jc,is,js;
  char name[64];

  int nc = QLA_Nc;
  int ns = 4;

  for(i = 0; i < MAX; i++){

    sMD1p[i] = &sMD1[sM1x[i]];
    sMD2p[i] = &sMD2[sM2x[i]];
    sMD3p[i] = &sMD3[sM2x[i]];

    sHD1p[i] = &sHD1[sH1x[i]];
    sHD2p[i] = &sHD2[sH2x[i]];
    sHD3p[i] = &sHD3[sH2x[i]];

    sDD1p[i] = &sDD1[sD1x[i]];
    sDD2p[i] = &sDD2[sD2x[i]];
    sDD3p[i] = &sDD3[sD2x[i]];

    sVD1p[i] = &sVD1[sV1x[i]];
    sVD2p[i] = &sVD2[sV2x[i]];
    sVD3p[i] = &sVD3[sV2x[i]];

    sPD1p[i] = &sPD1[sP1x[i]];
    sPD2p[i] = &sPD2[sP2x[i]];
    sPD3p[i] = &sPD3[sP2x[i]];

    sMD1p[i] = &sMD1[sM1x[i]];
    sMD2p[i] = &sMD2[sM2x[i]];
    sMD3p[i] = &sMD3[sM2x[i]];

    sMF1p[i] = &sMF1[sM1x[i]];
    sMF2p[i] = &sMF2[sM2x[i]];
    sMF3p[i] = &sMF3[sM2x[i]];

    sHF1p[i] = &sHF1[sH1x[i]];
    sHF2p[i] = &sHF2[sH2x[i]];
    sHF3p[i] = &sHF3[sH2x[i]];

    sDF1p[i] = &sDF1[sD1x[i]];
    sDF2p[i] = &sDF2[sD2x[i]];
    sDF3p[i] = &sDF3[sD2x[i]];

    sVF1p[i] = &sVF1[sV1x[i]];
    sVF2p[i] = &sVF2[sV2x[i]];
    sVF3p[i] = &sVF3[sV2x[i]];

    sPF1p[i] = &sPF1[sP1x[i]];
    sPF2p[i] = &sPF2[sP2x[i]];
    sPF3p[i] = &sPF3[sP2x[i]];

    sMF1p[i] = &sMF1[sM1x[i]];
    sMF2p[i] = &sMF2[sM2x[i]];
    sMF3p[i] = &sMF3[sM2x[i]];

  }

  /* Create random test values */
  QLA_S_veq_seed_i_I(sS1,sI4,sI3,MAX);

  for(i = 0; i < MAX; i++){

    /* Double precision */

    QLA_D_H_veq_gaussian_S(sHD1,sS1,MAX);
    QLA_D_H_veq_gaussian_S(sHD2,sS1,MAX);
    QLA_D_H_veq_gaussian_S(sHD3,sS1,MAX);
			  	 
    QLA_D_D_veq_gaussian_S(sDD1,sS1,MAX);
    QLA_D_D_veq_gaussian_S(sDD2,sS1,MAX);
    QLA_D_D_veq_gaussian_S(sDD3,sS1,MAX);
			  	 
    QLA_D_V_veq_gaussian_S(sVD1,sS1,MAX);
    QLA_D_V_veq_gaussian_S(sVD2,sS1,MAX);
    QLA_D_V_veq_gaussian_S(sVD3,sS1,MAX);
			  	 
    QLA_D_P_veq_gaussian_S(sPD1,sS1,MAX);
    QLA_D_P_veq_gaussian_S(sPD2,sS1,MAX);
    QLA_D_P_veq_gaussian_S(sPD3,sS1,MAX);
			  	 
    QLA_D_M_veq_gaussian_S(sMD1,sS1,MAX);
    QLA_D_M_veq_gaussian_S(sMD2,sS1,MAX);
    QLA_D_M_veq_gaussian_S(sMD3,sS1,MAX);

    /* Single precision */

    QLA_F_H_veq_gaussian_S(sHF1,sS1,MAX);
    QLA_F_H_veq_gaussian_S(sHF2,sS1,MAX);
    QLA_F_H_veq_gaussian_S(sHF3,sS1,MAX);
			  	 
    QLA_F_D_veq_gaussian_S(sDF1,sS1,MAX);
    QLA_F_D_veq_gaussian_S(sDF2,sS1,MAX);
    QLA_F_D_veq_gaussian_S(sDF3,sS1,MAX);
			  	 
    QLA_F_V_veq_gaussian_S(sVF1,sS1,MAX);
    QLA_F_V_veq_gaussian_S(sVF2,sS1,MAX);
    QLA_F_V_veq_gaussian_S(sVF3,sS1,MAX);
			  	 
    QLA_F_P_veq_gaussian_S(sPF1,sS1,MAX);
    QLA_F_P_veq_gaussian_S(sPF2,sS1,MAX);
    QLA_F_P_veq_gaussian_S(sPF3,sS1,MAX);
			  	 
    QLA_F_M_veq_gaussian_S(sMF1,sS1,MAX);
    QLA_F_M_veq_gaussian_S(sMF2,sS1,MAX);
    QLA_F_M_veq_gaussian_S(sMF3,sS1,MAX);

  }
'

/* Precision conversion */

unary_spec(H,eq,H,_DF,D,F)
unary_spec(D,eq,D,_DF,D,F)
unary_spec(V,eq,V,_DF,D,F)
unary_spec(P,eq,P,_DF,D,F)
unary_spec(M,eq,M,_DF,D,F)
unary_spec(H,eq,H,_FD,F,D)
unary_spec(D,eq,D,_FD,F,D)
unary_spec(V,eq,V,_FD,F,D)
unary_spec(P,eq,P,_FD,F,D)
unary_spec(M,eq,M,_FD,F,D)

/* Reductions */
unaryglobalnorm2(r,eq_norm2,H,_DF,D,F)
unaryglobalnorm2(r,eq_norm2,D,_DF,D,F)
unaryglobalnorm2(r,eq_norm2,V,_DF,D,F)
unaryglobalnorm2(r,eq_norm2,P,_DF,D,F)
unaryglobalnorm2(r,eq_norm2,M,_DF,D,F)

binaryglobaldot(c,eq,H,dot,H,_DF,D,F,F)
binaryglobaldot(c,eq,D,dot,D,_DF,D,F,F)
binaryglobaldot(c,eq,V,dot,V,_DF,D,F,F)
binaryglobaldot(c,eq,P,dot,P,_DF,D,F,F)
binaryglobaldot(c,eq,M,dot,M,_DF,D,F,F)

binaryglobaldotreal(r,eq_re,H,dot,H,_DF,D,F,F)
binaryglobaldotreal(r,eq_re,D,dot,D,_DF,D,F,F)
binaryglobaldotreal(r,eq_re,V,dot,V,_DF,D,F,F)
binaryglobaldotreal(r,eq_re,P,dot,P,_DF,D,F,F)
binaryglobaldotreal(r,eq_re,M,dot,M,_DF,D,F,F)

unarysum(h,eq_sum,H,_DF,D,F)
unarysum(d,eq_sum,D,_DF,D,F)
unarysum(v,eq_sum,V,_DF,D,F)
unarysum(p,eq_sum,P,_DF,D,F)
unarysum(m,eq_sum,M,_DF,D,F)

`
  return 0;
}
'

