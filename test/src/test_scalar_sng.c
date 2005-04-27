#include <qla.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "compare.h"

#define CHECKeqsngII(a,b,c) {QLA_Int tmp1,tmp2; tmp1 = (a); tmp2 = (b); \
      checkeqsngII(&tmp1,&tmp2,c);}

#define CHECKeqsngRR(a,b,c) {QLA_Real tmp1,tmp2; tmp1 = (a); tmp2 = (b); \
      checkeqsngRR(&tmp1,&tmp2,c);}

#define CHECKeqsngCC(a,b,c) {checkeqsngCC(a,b,c);}

#define CHECKeqsngCRR(a,b,c,d) {QLA_Real tmp1,tmp2; tmp1 = (b); tmp2 = (c); \
      checkeqsngCRR(a,&tmp1,&tmp2,d);}

#define sign(a) a > 0 ? 1. : -1.

QLA_Real max(QLA_Real sR1, QLA_Real z2){
  return sR1 > z2 ? sR1 : z2;
}

QLA_Real min(QLA_Real sR1, QLA_Real z2){
  return sR1 < z2 ? sR1 : z2;
}

int main(){

  QLA_Int sI1 = -4123;
  QLA_Int sI2 = 0;
  QLA_Int sI3 = 7032;
  QLA_Int sI4 = -17;

  QLA_Real sR1 =  0.17320508075688772;
  QLA_Real sR2 = -9.3527446341505872;
  QLA_Real sR3 = -3.6694280525381038;

  QLA_Real sC1re = -8.8000370811461867;
  QLA_Real sC1im =  5.7248575675626134;
  QLA_Real sC2re =  2.6141415406703029;
  QLA_Real sC2im = -9.6994509499895247;
  QLA_Real sC3re =  5.1209437364852809;
  QLA_Real sC3im =  3.2319023055820679;

  QLA_Complex sC1,sC2,sC3;

  QLA_RandomState sS1;

  QLA_Int destI;
  QLA_Real destR;
  QLA_Complex destC;

  QLA_Int                 chkI;
  QLA_Real                chkR1,chkR2;
  QLA_Complex             chkC;

  char name[64];

  /* Assign values for complex constants */

  QLA_c_eq_r_plus_ir(sC1,sC1re,sC1im);
  QLA_c_eq_r_plus_ir(sC2,sC2re,sC2im);
  QLA_c_eq_r_plus_ir(sC3,sC3re,sC3im);

#if ( QLA_Precision != 'Q' )  /* Q precision is limited to assignments */

  /* QLA_R_eq_func_R */
 
  strcpy(name,"QLA_R_eq_cos_R");
  QLA_R_eq_cos_R(&destR,&sR1);
  CHECKeqsngRR(destR,cos(sR1),name);

  strcpy(name,"QLA_R_eq_sin_R");
  QLA_R_eq_sin_R(&destR,&sR1);
  CHECKeqsngRR(destR,sin(sR1),name);

  strcpy(name,"QLA_R_eq_tan_R");
  QLA_R_eq_tan_R(&destR,&sR1);
  CHECKeqsngRR(destR,tan(sR1),name);

  strcpy(name,"QLA_R_eq_acos_R");
  QLA_R_eq_acos_R(&destR,&sR1);
  CHECKeqsngRR(destR,acos(sR1),name);

  strcpy(name,"QLA_R_eq_asin_R");
  QLA_R_eq_asin_R(&destR,&sR1);
  CHECKeqsngRR(destR,asin(sR1),name);

  strcpy(name,"QLA_R_eq_atan_R");
  QLA_R_eq_atan_R(&destR,&sR1);
  CHECKeqsngRR(destR,atan(sR1),name);

  strcpy(name,"QLA_R_eq_sqrt_R");
  QLA_R_eq_sqrt_R(&destR,&sR1);
  CHECKeqsngRR(destR,sqrt(sR1),name);

  strcpy(name,"QLA_R_eq_fabs_R");
  QLA_R_eq_fabs_R(&destR,&sR2);
  CHECKeqsngRR(destR,fabs(sR2),name);

  strcpy(name,"QLA_R_eq_exp_R");
  QLA_R_eq_exp_R(&destR,&sR1);
  CHECKeqsngRR(destR,exp(sR1),name);

  strcpy(name,"QLA_R_eq_log_R");
  QLA_R_eq_log_R(&destR,&sR1);
  CHECKeqsngRR(destR,log(sR1),name);

  strcpy(name,"QLA_R_eq_sign_R");
  QLA_R_eq_sign_R(&destR,&sR1);
  CHECKeqsngRR(destR,sign(sR1),name);

  strcpy(name,"QLA_R_eq_cosh_R");
  QLA_R_eq_cosh_R(&destR,&sR1);
  CHECKeqsngRR(destR,cosh(sR1),name);

  strcpy(name,"QLA_R_eq_sinh_R");
  QLA_R_eq_sinh_R(&destR,&sR1);
  CHECKeqsngRR(destR,sinh(sR1),name);

  strcpy(name,"QLA_R_eq_tanh_R");
  QLA_R_eq_tanh_R(&destR,&sR1);
  CHECKeqsngRR(destR,tanh(sR1),name);

  strcpy(name,"QLA_R_eq_log10_R");
  QLA_R_eq_log10_R(&destR,&sR1);
  CHECKeqsngRR(destR,log10(sR1),name);

  strcpy(name,"QLA_R_eq_floor_R");
  QLA_R_eq_floor_R(&destR,&sR1);
  CHECKeqsngRR(destR,floor(sR1),name);

  strcpy(name,"QLA_R_eq_ceil_R");
  QLA_R_eq_ceil_R(&destR,&sR1);
  CHECKeqsngRR(destR,ceil(sR1),name);

  /* QLA_R_eq_R_func_R */

  strcpy(name,"QLA_R_eq_R_mod_R");
  QLA_R_eq_R_mod_R(&destR,&sR2,&sR1);
  chkR1 = fmod(sR2,sR1);
  CHECKeqsngRR(destR,chkR1,name);

  strcpy(name,"QLA_R_eq_R_max_R");
  QLA_R_eq_R_max_R(&destR,&sR2,&sR1);
  chkR1 = sR2 > sR1 ? sR2 : sR1;
  CHECKeqsngRR(destR,chkR1,name);

  strcpy(name,"QLA_R_eq_R_min_R");
  QLA_R_eq_R_min_R(&destR,&sR2,&sR1);
  chkR1 = sR2 < sR1 ? sR2 : sR1;
  CHECKeqsngRR(destR,chkR1,name);

  strcpy(name,"QLA_R_eq_R_pow_R");
  QLA_R_eq_R_pow_R(&destR,&sR2,&sR1);
  chkR1 = pow(sR2,sR1);
  CHECKeqsngRR(destR,chkR1,name);

  strcpy(name,"QLA_R_eq_R_atan2_R");
  QLA_R_eq_R_atan2_R(&destR,&sR2,&sR1);
  chkR1 = atan2(sR2,sR1);
  CHECKeqsngRR(destR,chkR1,name);

  strcpy(name,"QLA_R_eq_R_ldexp_I");
  QLA_R_eq_R_ldexp_I(&destR,&sR2,&sI4);
  chkR1 = ldexp(sR2,sI4);
  CHECKeqsngRR(destR,chkR1,name);

  /* QLA_C_eq_cexpi_R */
 
  strcpy(name,"QLA_C_eq_cexpi_R");
  QLA_C_eq_cexpi_R(&destC,&sR1);
  CHECKeqsngCRR(&destC,cos(sR1),sin(sR1),name);

  /* QLA_R_eq_func_C */

  strcpy(name,"QLA_R_eq_norm_C");
  QLA_R_eq_norm_C(&destR,&sC1);
  CHECKeqsngRR(destR,QLA_norm_c(sC1),name);

  strcpy(name,"QLA_R_eq_arg_C");
  QLA_R_eq_arg_C(&destR,&sC1);
  CHECKeqsngRR(destR,atan2(sC1im,sC1re),name);

  /* QLA_C_eq_func_C */
 
  strcpy(name,"QLA_C_eq_cexp_C");
  QLA_C_eq_cexp_C(&destC,&sC1);
  CHECKeqsngCRR(&destC,exp(sC1re)*cos(sC1im),exp(sC1re)*sin(sC1im),name);

  strcpy(name,"QLA_C_eq_csqrt_C");
  QLA_C_eq_csqrt_C(&destC,&sC1);
  chkR1 = sqrt(sC1re*sC1re+sC1im*sC1im);
  chkR2 = atan2(sC1im,sC1re);
  CHECKeqsngCRR(&destC,sqrt(chkR1)*cos(chkR2/2),sqrt(chkR1)*sin(chkR2/2),name);

  strcpy(name,"QLA_C_eq_clog_C");
  QLA_C_eq_clog_C(&destC,&sC1);
  chkR1 = log(sqrt(sC1re*sC1re+sC1im*sC1im));
  chkR2 = atan2(sC1im,sC1re);
  CHECKeqsngCRR(&destC,chkR1,chkR2,name);

#endif /* QLA_Precision != 'Q' */

  /* QLA_T_eq_T */

  strcpy(name,"QLA_R_eq_R");
  QLA_R_eq_R(&destR,&sR1);
  CHECKeqsngRR(destR,sR1,name);

  strcpy(name,"QLA_C_eq_C");
  QLA_C_eq_C(&destC,&sC1);
  CHECKeqsngCC(&destC,&sC1,name);

  destR = sR1;
  strcpy(name,"QLA_R_peq_R");
  QLA_R_peq_R(&destR,&sR2);
  CHECKeqsngRR(destR,sR1+sR2,name);

  QLA_c_eq_c(destC,sC1);
  strcpy(name,"QLA_C_peq_C");
  QLA_C_peq_C(&destC,&sC2);
  QLA_c_eq_c_plus_c(chkC,sC1,sC2);
  CHECKeqsngCC(&destC,&chkC,name);

  strcpy(name,"QLA_R_eqm_R");
  QLA_R_eqm_R(&destR,&sR1);
  CHECKeqsngRR(destR,-sR1,name);

  strcpy(name,"QLA_C_eqm_C");
  QLA_C_eqm_C(&destC,&sC1);
  CHECKeqsngCRR(&destC,-sC1re,-sC1im,name);

  destR = sR1;
  strcpy(name,"QLA_R_meq_R");
  QLA_R_meq_R(&destR,&sR2);
  CHECKeqsngRR(destR,sR1-sR2,name);

  QLA_c_eq_c(destC,sC1);
  strcpy(name,"QLA_C_meq_C");
  QLA_C_meq_C(&destC,&sC2);
  QLA_c_eq_c_minus_c(chkC,sC1,sC2);
  CHECKeqsngCC(&destC,&chkC,name);

#if ( QLA_Precision != 'Q' )  /* Q precision is limited to assignments */

  /* QLA_C_eq_Ca */

  strcpy(name,"QLA_C_eq_Ca");
  QLA_C_eq_Ca(&destC,&sC1);
  CHECKeqsngCRR(&destC,sC1re,-sC1im,name);

  QLA_c_eq_c(destC,sC1);
  strcpy(name,"QLA_C_peq_Ca");
  QLA_C_peq_Ca(&destC,&sC2);
  CHECKeqsngCRR(&destC,sC1re+sC2re,sC1im-sC2im,name);

  strcpy(name,"QLA_C_eqm_Ca");
  QLA_C_eqm_Ca(&destC,&sC1);
  CHECKeqsngCRR(&destC,-sC1re,sC1im,name);

  QLA_c_eq_c(destC,sC1);
  strcpy(name,"QLA_C_meq_Ca");
  QLA_C_meq_Ca(&destC,&sC2);
  CHECKeqsngCRR(&destC,sC1re-sC2re,sC1im+sC2im,name);

  /* QLA_C_eq_conj_C */

  strcpy(name,"QLA_C_eq_conj_C");
  QLA_C_eq_conj_C(&destC,&sC1);
  CHECKeqsngCRR(&destC,sC1re,-sC1im,name);

  QLA_c_eq_c(destC,sC1);
  strcpy(name,"QLA_C_peq_conj_C");
  QLA_C_peq_conj_C(&destC,&sC2);
  CHECKeqsngCRR(&destC,sC1re+sC2re,sC1im-sC2im,name);

  strcpy(name,"QLA_C_eqm_conj_C");
  QLA_C_eqm_conj_C(&destC,&sC1);
  CHECKeqsngCRR(&destC,-sC1re,sC1im,name);

  QLA_c_eq_c(destC,sC1);
  strcpy(name,"QLA_C_meq_conj_C");
  QLA_C_meq_conj_C(&destC,&sC2);
  CHECKeqsngCRR(&destC,sC1re-sC2re,sC1im+sC2im,name);

  /* Local squared norm - complex */

  strcpy(name,"QLA_R_eq_norm2_C");
  QLA_R_eq_norm2_C(&destR,&sC1);
  CHECKeqsngRR(destR,sC1re*sC1re+sC1im*sC1im,name);

  /* Type conversions */

  strcpy(name,"QLA_C_eq_R");
  QLA_C_eq_R(&destC,&sR1);
  CHECKeqsngCRR(&destC,sR1,0.,name);

  strcpy(name,"QLA_R_eq_re_C");
  QLA_R_eq_re_C(&destR,&sC1);
  CHECKeqsngRR(destR,sC1re,name);

  strcpy(name,"QLA_R_eq_im_C");
  QLA_R_eq_im_C(&destR,&sC1);
  CHECKeqsngRR(destR,sC1im,name);

  strcpy(name,"QLA_R_eq_I");
  QLA_R_eq_I(&destR,&sI1);
  CHECKeqsngRR(destR,(QLA_Real)sI1,name);

  strcpy(name,"QLA_I_eq_trunc_R");
  QLA_I_eq_trunc_R(&destI,&sR1);
  chkI = sR1;
  CHECKeqsngII(destI,chkI,name);

  strcpy(name,"QLA_I_eq_round_R");
  QLA_I_eq_round_R(&destI,&sR1);
  chkI = round(sR1);
  CHECKeqsngII(destI,chkI,name);

  strcpy(name,"QLA_C_eq_R_plus_i_R");
  QLA_C_eq_R_plus_i_R(&destC,&sR1,&sR2);
  CHECKeqsngCRR(&destC,sR1,sR2,name);

  /* Mult by real scalar */
  
  strcpy(name,"QLA_R_eq_r_times_R");
  QLA_R_eq_r_times_R(&destR,&sR2,&sR1);
  chkR1 = sR1*sR2;
  CHECKeqsngRR(destR,chkR1,name);

  strcpy(name,"QLA_C_eq_r_times_C");
  QLA_C_eq_r_times_C(&destC,&sR2,&sC1);
  chkR1 = sC1re*sR2;
  chkR2 = sC1im*sR2;
  CHECKeqsngCRR(&destC,chkR1,chkR2,name);

  destR = sR1;
  strcpy(name,"QLA_R_peq_r_times_R");
  QLA_R_peq_r_times_R(&destR,&sR2,&sR3);
  chkR1 = sR1 + sR3*sR2;
  CHECKeqsngRR(destR,chkR1,name);

  destC = sC1;
  strcpy(name,"QLA_C_peq_r_times_C");
  QLA_C_peq_r_times_C(&destC,&sR2,&sC2);
  chkR1 = sC1re + sC2re*sR2;
  chkR2 = sC1im + sC2im*sR2;
  CHECKeqsngCRR(&destC,chkR1,chkR2,name);

  strcpy(name,"QLA_R_eqm_r_times_R");
  QLA_R_eqm_r_times_R(&destR,&sR2,&sR1);
  chkR1 = -sR1*sR2;
  CHECKeqsngRR(destR,chkR1,name);

  strcpy(name,"QLA_C_eqm_r_times_C");
  QLA_C_eqm_r_times_C(&destC,&sR2,&sC1);
  chkR1 = -sC1re*sR2;
  chkR2 = -sC1im*sR2;
  CHECKeqsngCRR(&destC,chkR1,chkR2,name);

  destR = sR1;
  strcpy(name,"QLA_R_meq_r_times_R");
  QLA_R_meq_r_times_R(&destR,&sR2,&sR3);
  chkR1 = sR1 - sR3*sR2;
  CHECKeqsngRR(destR,chkR1,name);

  destC = sC1;
  strcpy(name,"QLA_C_meq_r_times_C");
  QLA_C_meq_r_times_C(&destC,&sR2,&sC2);
  chkR1 = sC1re - sC2re*sR2;
  chkR2 = sC1im - sC2im*sR2;
  CHECKeqsngCRR(&destC,chkR1,chkR2,name);

  /* Mult by complex scalar */

  strcpy(name,"QLA_C_eq_c_times_C");
  QLA_C_eq_c_times_C(&destC,&sC2,&sC3);
  chkR1 = sC2re*sC3re - sC2im*sC3im;
  chkR2 = sC2im*sC3re + sC2re*sC3im;
  CHECKeqsngCRR(&destC,chkR1,chkR2,name);

  destC = sC1;
  strcpy(name,"QLA_C_peq_c_times_C");
  QLA_C_peq_c_times_C(&destC,&sC2,&sC3);
  chkR1 = sC1re + sC2re*sC3re - sC2im*sC3im;
  chkR2 = sC1im + sC2im*sC3re + sC2re*sC3im;
  CHECKeqsngCRR(&destC,chkR1,chkR2,name);

  strcpy(name,"QLA_C_eqm_c_times_C");
  QLA_C_eqm_c_times_C(&destC,&sC2,&sC3);
  chkR1 = -sC2re*sC3re + sC2im*sC3im;
  chkR2 = -sC2im*sC3re - sC2re*sC3im;
  CHECKeqsngCRR(&destC,chkR1,chkR2,name);

  destC = sC1;
  strcpy(name,"QLA_C_meq_c_times_C");
  QLA_C_meq_c_times_C(&destC,&sC2,&sC3);
  chkR1 = sC1re - sC2re*sC3re + sC2im*sC3im;
  chkR2 = sC1im - sC2im*sC3re - sC2re*sC3im;
  CHECKeqsngCRR(&destC,chkR1,chkR2,name);

  /* Mult by i */

  strcpy(name,"QLA_C_eq_i_C");
  QLA_C_eq_i_C(&destC,&sC2);
  chkR1 = -sC2im;
  chkR2 =  sC2re;
  CHECKeqsngCRR(&destC,chkR1,chkR2,name);

  destC = sC1;
  strcpy(name,"QLA_C_peq_i_C");
  QLA_C_peq_i_C(&destC,&sC2);
  chkR1 = sC1re - sC2im;
  chkR2 = sC1im + sC2re;
  CHECKeqsngCRR(&destC,chkR1,chkR2,name);

  strcpy(name,"QLA_C_eqm_i_C");
  QLA_C_eqm_i_C(&destC,&sC2);
  chkR1 =  sC2im;
  chkR2 = -sC2re;
  CHECKeqsngCRR(&destC,chkR1,chkR2,name);

  destC = sC1;
  strcpy(name,"QLA_C_meq_i_C");
  QLA_C_meq_i_C(&destC,&sC2);
  chkR1 = sC1re + sC2im;
  chkR2 = sC1im - sC2re;
  CHECKeqsngCRR(&destC,chkR1,chkR2,name);

  /* Scalar division */

  strcpy(name,"QLA_R_eq_R_divide_R");
  QLA_R_eq_R_divide_R(&destR,&sR2,&sR1);
  chkR1 = sR2/sR1;
  CHECKeqsngRR(destR,chkR1,name);

  strcpy(name,"QLA_C_eq_C_divide_C");
  QLA_C_eq_C_divide_C(&destC,&sC2,&sC1);
  QLA_c_eq_c_div_c(chkC,sC2,sC1);
  CHECKeqsngCC(&destC,&chkC,name);

  /* Uniform types - plus */

  strcpy(name,"QLA_R_eq_R_plus_R");
  QLA_R_eq_R_plus_R(&destR,&sR2,&sR1);
  chkR1 = sR1 + sR2;
  CHECKeqsngRR(destR,chkR1,name);

  strcpy(name,"QLA_C_eq_C_plus_C");
  QLA_C_eq_C_plus_C(&destC,&sC2,&sC1);
  chkR1 = sC1re + sC2re;
  chkR2 = sC1im + sC2im;
  CHECKeqsngCRR(&destC,chkR1,chkR2,name);

  /* Uniform types - minus */

  strcpy(name,"QLA_R_eq_R_minus_R");
  QLA_R_eq_R_minus_R(&destR,&sR2,&sR1);
  chkR1 = sR2 - sR1;
  CHECKeqsngRR(destR,chkR1,name);

  strcpy(name,"QLA_C_eq_C_minus_C");
  QLA_C_eq_C_minus_C(&destC,&sC2,&sC1);
  chkR1 = sC2re - sC1re;
  chkR2 = sC2im - sC1im;
  CHECKeqsngCRR(&destC,chkR1,chkR2,name);

  /* Local "inner product" - complex */

  strcpy(name,"QLA_C_eq_C_dot_C");
  QLA_C_eq_C_dot_C(&destC,&sC2,&sC1);
  QLA_c_eq_ca_times_c(chkC,sC2,sC1);
  CHECKeqsngCC(&chkC,&destC,name);

  strcpy(name,"QLA_R_eq_re_C_dot_C");
  QLA_R_eq_re_C_dot_C(&destR,&sC2,&sC1);
  QLA_r_eq_Re_ca_times_c(chkR1,sC2,sC1);
  CHECKeqsngRR(chkR1,destR,name);

  /* Uniform types - times */

  strcpy(name,"QLA_R_eq_R_times_R");
  QLA_R_eq_R_times_R(&destR,&sR2,&sR1);
  chkR1 = sR1*sR2;
  CHECKeqsngRR(destR,chkR1,name);

  destR = sR1;
  strcpy(name,"QLA_R_peq_R_times_R");
  QLA_R_peq_R_times_R(&destR,&sR2,&sR3);
  chkR1 = sR1 + sR3*sR2;
  CHECKeqsngRR(destR,chkR1,name);

  strcpy(name,"QLA_R_eqm_R_times_R");
  QLA_R_eqm_R_times_R(&destR,&sR2,&sR1);
  chkR1 = -sR1*sR2;
  CHECKeqsngRR(destR,chkR1,name);

  destR = sR1;
  strcpy(name,"QLA_R_meq_R_times_R");
  QLA_R_meq_R_times_R(&destR,&sR2,&sR3);
  chkR1 = sR1 - sR3*sR2;
  CHECKeqsngRR(destR,chkR1,name);

  strcpy(name,"QLA_C_eq_C_times_C");
  QLA_C_eq_C_times_C(&destC,&sC2,&sC3);
  chkR1 = sC2re*sC3re - sC2im*sC3im;
  chkR2 = sC2im*sC3re + sC2re*sC3im;
  CHECKeqsngCRR(&destC,chkR1,chkR2,name);

  destC = sC1;
  strcpy(name,"QLA_C_peq_C_times_C");
  QLA_C_peq_C_times_C(&destC,&sC2,&sC3);
  chkR1 = sC1re + sC2re*sC3re - sC2im*sC3im;
  chkR2 = sC1im + sC2im*sC3re + sC2re*sC3im;
  CHECKeqsngCRR(&destC,chkR1,chkR2,name);

  strcpy(name,"QLA_C_eqm_C_times_C");
  QLA_C_eqm_C_times_C(&destC,&sC2,&sC3);
  chkR1 = -sC2re*sC3re + sC2im*sC3im;
  chkR2 = -sC2im*sC3re - sC2re*sC3im;
  CHECKeqsngCRR(&destC,chkR1,chkR2,name);

  destC = sC1;
  strcpy(name,"QLA_C_meq_C_times_C");
  QLA_C_meq_C_times_C(&destC,&sC2,&sC3);
  chkR1 = sC1re - sC2re*sC3re + sC2im*sC3im;
  chkR2 = sC1im - sC2im*sC3re - sC2re*sC3im;
  CHECKeqsngCRR(&destC,chkR1,chkR2,name);

  /* Ternary a = b*x + c */

  strcpy(name,"QLA_R_eq_r_times_R_plus_R");
  QLA_R_eq_r_times_R_plus_R(&destR,&sR1,&sR2,&sR3);
  chkR1 = sR1*sR2 + sR3;
  CHECKeqsngRR(destR,chkR1,name);

  strcpy(name,"QLA_C_eq_r_times_C_plus_C");
  QLA_C_eq_r_times_C_plus_C(&destC,&sR1,&sC2,&sC3);
  chkR1 = sR1*sC2re + sC3re;
  chkR2 = sR1*sC2im + sC3im;
  CHECKeqsngCRR(&destC,chkR1,chkR2,name);

  strcpy(name,"QLA_C_eq_c_times_C_plus_C");
  QLA_C_eq_c_times_C_plus_C(&destC,&sC1,&sC2,&sC3);
  chkR1 = sC1re*sC2re - sC1im*sC2im + sC3re;
  chkR2 = sC1im*sC2re + sC1re*sC2im + sC3im;
  CHECKeqsngCRR(&destC,chkR1,chkR2,name);

  /* Ternary a = b*x - c */

  strcpy(name,"QLA_R_eq_r_times_R_minus_R");
  QLA_R_eq_r_times_R_minus_R(&destR,&sR1,&sR2,&sR3);
  chkR1 = sR1*sR2 - sR3;
  CHECKeqsngRR(destR,chkR1,name);

  strcpy(name,"QLA_C_eq_r_times_C_minus_C");
  QLA_C_eq_r_times_C_minus_C(&destC,&sR1,&sC2,&sC3);
  chkR1 = sR1*sC2re - sC3re;
  chkR2 = sR1*sC2im - sC3im;
  CHECKeqsngCRR(&destC,chkR1,chkR2,name);

  strcpy(name,"QLA_C_eq_c_times_C_minus_C");
  QLA_C_eq_c_times_C_minus_C(&destC,&sC1,&sC2,&sC3);
  chkR1 = sC1re*sC2re - sC1im*sC2im - sC3re;
  chkR2 = sC1im*sC2re + sC1re*sC2im - sC3im;
  CHECKeqsngCRR(&destC,chkR1,chkR2,name);

  /* Comparisons of reals */

  strcpy(name,"QLA_I_eq_R_eq_R");
  QLA_I_eq_R_eq_R(&destI,&sR1,&sR1);
  chkI = sR1 == sR1 ? 1 : 0;
  CHECKeqsngII(destI,chkI,name);

  strcpy(name,"QLA_I_eq_R_ne_R");
  QLA_I_eq_R_ne_R(&destI,&sR1,&sR2);
  chkI = sR1 != sR2 ? 1 : 0;
  CHECKeqsngII(destI,chkI,name);

  strcpy(name,"QLA_I_eq_R_gt_R");
  QLA_I_eq_R_gt_R(&destI,&sR1,&sR2);
  chkI = sR1 > sR2 ? 1 : 0;
  CHECKeqsngII(destI,chkI,name);

  strcpy(name,"QLA_I_eq_R_lt_R");
  QLA_I_eq_R_lt_R(&destI,&sR1,&sR2);
  chkI = sR1 < sR2 ? 1 : 0;
  CHECKeqsngII(destI,chkI,name);

  strcpy(name,"QLA_I_eq_R_ge_R");
  QLA_I_eq_R_ge_R(&destI,&sR1,&sR2);
  chkI = sR1 >= sR2 ? 1 : 0;
  CHECKeqsngII(destI,chkI,name);

  strcpy(name,"QLA_I_eq_R_le_R");
  QLA_I_eq_R_le_R(&destI,&sR1,&sR2);
  chkI = sR1 <= sR2 ? 1 : 0;
  CHECKeqsngII(destI,chkI,name);

  /* Copymask */

  destR = sR2;
  strcpy(name,"QLA_R_eq_R_mask_I");
  QLA_R_eq_R_mask_I(&destR,&sR1,&sI1);
  chkR1 = sI1 ? sR1 : sR2;
  CHECKeqsngRR(destR,chkR1,name);

  destR = sR2;
  strcpy(name,"QLA_R_eq_R_mask_I");
  QLA_R_eq_R_mask_I(&destR,&sR1,&sI2);
  chkR1 = sI2 ? sR1 : sR2;
  CHECKeqsngRR(destR,chkR1,name);

  destC = sC2;
  strcpy(name,"QLA_C_eq_C_mask_I");
  QLA_C_eq_C_mask_I(&destC,&sC1,&sI1);
  chkC = sI1 ? sC1 : sC2;
  CHECKeqsngCC(&destC,&chkC,name);

  destC = sC2;
  strcpy(name,"QLA_C_eq_C_mask_I");
  QLA_C_eq_C_mask_I(&destC,&sC1,&sI2);
  chkC = sI2 ? sC1 : sC2;
  CHECKeqsngCC(&destC,&chkC,name);

  /* Reductions */

  strcpy(name,"QLA_r_eq_norm2_I");
  QLA_r_eq_norm2_I(&destR,&sI2);
  chkR1 = sI2*sI2;
  CHECKeqsngRR(destR,chkR1,name);

  strcpy(name,"QLA_r_eq_norm2_R");
  QLA_r_eq_norm2_R(&destR,&sR2);
  chkR1 = sR2*sR2;
  CHECKeqsngRR(destR,chkR1,name);

  strcpy(name,"QLA_r_eq_norm2_C");
  QLA_r_eq_norm2_C(&destR,&sC1);
  chkR1 = sC1re*sC1re+sC1im*sC1im;
  CHECKeqsngRR(destR,chkR1,name);

  strcpy(name,"QLA_r_eq_sum_I");
  QLA_r_eq_sum_I(&destR,&sI2);
  chkR1 = sI2;
  CHECKeqsngRR(destR,chkR1,name);

  strcpy(name,"QLA_r_eq_sum_R");
  QLA_r_eq_sum_R(&destR,&sR2);
  CHECKeqsngRR(destR,sR2,name);

  strcpy(name,"QLA_c_eq_sum_C");
  QLA_c_eq_sum_C(&destC,&sC1);
  CHECKeqsngCC(&destC,&sC1,name);

  strcpy(name,"QLA_r_eq_I_dot_I");
  QLA_r_eq_I_dot_I(&destR,&sI1,&sI2);
  chkR1 = sI1*sI2;
  CHECKeqsngRR(destR,chkR1,name);

  strcpy(name,"QLA_r_eq_R_dot_R");
  QLA_r_eq_R_dot_R(&destR,&sR1,&sR2);
  chkR1 = sR1*sR2;
  CHECKeqsngRR(destR,chkR1,name);

  strcpy(name,"QLA_c_eq_C_dot_C");
  QLA_c_eq_C_dot_C(&destC,&sC1,&sC2);
  QLA_c_eq_ca_times_c(chkC,sC1,sC2);
  CHECKeqsngCC(&destC,&chkC,name);

  strcpy(name,"QLA_r_eq_re_C_dot_C");
  QLA_r_eq_re_C_dot_C(&destR,&sC1,&sC2);
  QLA_r_eq_Re_ca_times_c(chkR1,sC1,sC2);
  CHECKeqsngRR(destR,chkR1,name);

#endif /* QLA_Precision != 'Q' */

  /* Fills */

  destR = sR1;
  strcpy(name,"QLA_R_eq_zero");
  QLA_R_eq_zero(&destR);
  CHECKeqsngRR(destR,0.,name);

  strcpy(name,"QLA_C_eq_zero");
  QLA_C_eq_zero(&destC);
  chkR1 = 0.; chkR2 = 0.;
  CHECKeqsngCRR(&destC,chkR1,chkR2,name);

#if ( QLA_Precision != 'Q' )  /* Q precision is limited to assignments */

  destR = sR1;
  strcpy(name,"QLA_R_eq_r");
  QLA_R_eq_r(&destR,&sR2);
  CHECKeqsngRR(destR,sR2,name);

  destC = sC1;
  strcpy(name,"QLA_C_eq_c");
  QLA_C_eq_c(&destC,&sC2);
  chkR1 = 0.; chkR2 = 0.;
  CHECKeqsngCC(&destC,&sC2,name);

  /* Random fills */
  /* Here we just verify that the underlying routines are called as
     expected */

  strcpy(name,"QLA_R_eq_random_S");
  QLA_S_eq_seed_i_I(&sS1,sI2,&sI3);
  QLA_R_eq_random_S(&destR,&sS1);
  QLA_seed_random(&sS1,sI2,sI3);
  chkR1 = QLA_random(&sS1);
  CHECKeqsngRR(destR,chkR1,name);

#endif /* QLA_Precision != 'Q' */

  strcpy(name,"QLA_R_eq_gaussian_S");
  QLA_S_eq_seed_i_I(&sS1,sI2,&sI3);
  QLA_R_eq_gaussian_S(&destR,&sS1);
  QLA_seed_random(&sS1,sI2,sI3);
  chkR1 = QLA_gaussian(&sS1);
  CHECKeqsngRR(destR,chkR1,name);

  strcpy(name,"QLA_C_eq_gaussian_S");
  QLA_S_eq_seed_i_I(&sS1,sI2,&sI3);
  QLA_C_eq_gaussian_S(&destC,&sS1);
  QLA_seed_random(&sS1,sI2,sI3);
  chkR1 = QLA_gaussian(&sS1);
  chkR2 = QLA_gaussian(&sS1);
  CHECKeqsngCRR(&destC,chkR1,chkR2,name);

  return 0;
}

