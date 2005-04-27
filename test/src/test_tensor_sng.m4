/* QLA test code */
/* for single tensor routines. */
/* C Code automatically generated from test_tensor_sng.m4 */

include(protocol_tensor_sng.m4)
`
#include <qla.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "compare.h"
#include "milc_gamma.h"

int main(){

  int nc = QLA_Nc;
  int ns = 4;
  int mu,sign;

  QLA_Int sI1 = -4123;
  QLA_Int sI2 = 0;
  QLA_Int sI3 = 7032;

  QLA_Real sR1 =  0.17320508075688772;

  QLA_Real sC1re = -8.8000370811461867;
  QLA_Real sC1im =  5.7248575675626134;
  QLA_Real sC2re =  2.6141415406703029;
  QLA_Real sC2im = -9.6994509499895247;
  QLA_Real sC3re =  5.1209437364852809;
  QLA_Real sC3im =  3.2319023055820679;

  QLA_Complex sC1,sC2,sC3;

  QLA_ColorMatrix         sM1,sM2,sM3;
  QLA_HalfFermion         sH1,sH2,sH3;
  QLA_DiracFermion        sD1,sD2,sD3;
  QLA_ColorVector         sV1,sV2,sV3;
  QLA_DiracPropagator     sP1,sP2,sP3;

  QLA_RandomState sS1;

  QLA_Real                destR,chkR;
  QLA_Complex             destC,chkC;
  QLA_ColorMatrix         destM,chkM;
  QLA_HalfFermion         destH,chkH;
  QLA_DiracFermion        destD,chkD;
  QLA_ColorVector         destV,chkV;
  QLA_DiracPropagator     destP,chkP;

  QLA_D_Real              chkRD;

  char name[64];
  int ic,jc,is,js,kc,ks;
  
  /* Test gaussian random fills against 
     direct call to the same underlying routine */
'
alltensors(`chkGaussian');

`
  /* Then use random number fills to create the test fields */

  QLA_S_eq_seed_i_I(&sS1,sI2,&sI3);

  QLA_H_eq_gaussian_S(&sH1,&sS1);
  QLA_H_eq_gaussian_S(&sH2,&sS1);
  QLA_H_eq_gaussian_S(&sH3,&sS1);
  
  QLA_D_eq_gaussian_S(&sD1,&sS1);
  QLA_D_eq_gaussian_S(&sD2,&sS1);
  QLA_D_eq_gaussian_S(&sD3,&sS1);
  
  QLA_V_eq_gaussian_S(&sV1,&sS1);
  QLA_V_eq_gaussian_S(&sV2,&sS1);
  QLA_V_eq_gaussian_S(&sV3,&sS1);
  
  QLA_P_eq_gaussian_S(&sP1,&sS1);
  QLA_P_eq_gaussian_S(&sP2,&sS1);
  QLA_P_eq_gaussian_S(&sP3,&sS1);
  
  QLA_M_eq_gaussian_S(&sM1,&sS1);
  QLA_M_eq_gaussian_S(&sM2,&sS1);
  QLA_M_eq_gaussian_S(&sM3,&sS1);
'
`
  /* Assign values for complex constants */

  QLA_c_eq_r_plus_ir(sC1,sC1re,sC1im);
  QLA_c_eq_r_plus_ir(sC2,sC2re,sC2im);
  QLA_c_eq_r_plus_ir(sC3,sC3re,sC3im);

  /* QLA_T_eqop_T */
'

alltensors(`chkEqop');

#if ( QLA_Precision != 'Q' )  /* Q precision is limited to assignments */
`
  /* QLA_T_eq_hconj_T */

'
chkHconj(P);
chkHconj(M);

` 
  /* QLA_T_eq_tranpose_T */

'
chkTranspose(P);
chkTranspose(M);

  /* QLA_T_eq_conj_T */

alltensors(`chkConj');

#endif /* QLA_Precision != Q */

  /* QLA_R_eq_norm2_T */
chkLocalNorm2(H);
chkLocalNorm2(D);
chkLocalNorm2(V);
chkLocalNorm2(P);
chkLocalNorm2(M);

#if ( QLA_Precision != 'Q' )  /* Q precision is limited to assignments */

  /* QLA_C_eq_elem_T */

alltensors(`chkExtractElem');

  /* QLA_T_eq_elem_C */

alltensors(`chkInsertElem');

  /* QLA_V_eq_colorvec_T */

chkExtractColorvec(H);
chkExtractColorvec(D);
chkExtractColorvec(P);
chkExtractColorvec(M);

  /* QLA_T_eq_colorvec_V */

chkInsertColorvec(H);
chkInsertColorvec(D);
chkInsertColorvec(P);
chkInsertColorvec(M);

  /* QLA_V_eq_diracvec_T */

chkExtractDiracvec(P);

  /* QLA_T_eq_diracvec_V */

chkInsertDiracvec(P);

  /* QLA_R_eq_*trace_M */

chkRealtrace;
chkImagtrace;
chkTrace;

  /* QLA_M_eq_spintrace_P */

chkSpintrace;

  /* QLA_M_eq_antiherm_M */

chkAntiherm;

  /* Gamma matrix tests */

chkSpproj(eq);
chkSprecon(eq);
chkSprecon(peq);
chkGammamult;

  /* QLA_T_eq_t_times_T */

alltensors(`chkrMult');
alltensors(`chkcMult');
alltensors(`chkiMult');

  /* Check addition/subtraction of elements */

alltensors(`chkPlus');
alltensors(`chkMinus');

  /* Multiplication - uniform types */
chkUniformMult(P);
chkUniformMult(M);

  /* ColorMatrix from outer product */
chkOuterprod;

  /* QLA_C_eq_T_dot_T */
chkLocalDot(H);
chkLocalDot(D);
chkLocalDot(V);
chkLocalDot(P);
chkLocalDot(M);
chkLocalRealDot(H);
chkLocalRealDot(D);
chkLocalRealDot(V);
chkLocalRealDot(P);
chkLocalRealDot(M);

  /* QLA_T_eq_M_times_T */
chkLeftMultM(H);
chkLeftMultM(D);
chkLeftMultM(V);
chkLeftMultM(P);
chkLeftMultM(M);

  /* QLA_M_eq_Ma_times_Ma */
chkMultMaMa;

  /* QLA_T_eq_Ma_times_T */
chkLeftMultMa(H);
chkLeftMultMa(D);
chkLeftMultMa(V);
chkLeftMultMa(P);
chkLeftMultMa(M);

  /* QLA_T_eq_T_times_M */
chkRightMultM(P);
chkRightMultM(M);

  /* QLA_T_eq_T_times_Ma */
chkRightMultMa(P);
chkRightMultMa(M);

  /* QLA_T_eq_rc_times_T_pm_T */
alltensors(`chkrMultAdd');
alltensors(`chkcMultAdd');

  /* QLA_T_eq_T_mask_I */
alltensors(`chkMask');

  /* QLA_r_eq_norm2_T */
alltensors(`chkNorm2');

  /* QLA_c_eq_T_dot_T */
alltensors(`chkDot');
chkRealDot(C);
chkRealDot(H);
chkRealDot(D);
chkRealDot(V);
chkRealDot(P);
chkRealDot(M);

  /* QLA_t_eq_sum_T */
alltensors(`chkSum');

#endif /* QLA_Precision != Q */

  /* QLA_T_eq_zero */
alltensors(`chkZero');

#if ( QLA_Precision != 'Q' )  /* Q precision is limited to assignments */

  /* QLA_T_eq_t */
alltensors(`chkConst')

  /* QLA_M_eq_c */
chkMConst;

#endif /* QLA_Precision != Q */

`
  return 0;
}

'
