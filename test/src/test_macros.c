/* Test macros for complex arithmetic in qla_complex.h */

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
      checkeqsngCRR(&a,&tmp1,&tmp2,d);}

int main(){

  QLA_Real sR1 =  0.17320508075688772;
  QLA_Real sR2 = -9.3527446341505872;
  QLA_Real sR3 = -3.6694280525381038;

  QLA_Real sC1re = -.88000370811461867;
  QLA_Real sC1im =  .57248575675626134;
  QLA_Real sC2re =  .26141415406703029;
  QLA_Real sC2im = -.96994509499895247;
  QLA_Real sC3re =  .51209437364852809;
  QLA_Real sC3im =  .32319023055820679;

  QLA_Complex sC1,sC2,sC3;

  QLA_Real destR,chkR;
  QLA_Complex destC/*,chkC*/;

  char name[64];

  /* Assign values for complex constants */

  QLA_c_eq_r_plus_ir(sC1,sC1re,sC1im);
  QLA_c_eq_r_plus_ir(sC2,sC2re,sC2im);
  QLA_c_eq_r_plus_ir(sC3,sC3re,sC3im);

  /* Test accessors */

  strcpy(name,"MACRO QLA_norm2_c");
  destR = QLA_norm2_c(sC1);
  chkR = sC1re*sC1re + sC1im*sC1im;
  CHECKeqsngRR(destR,chkR,name);

  strcpy(name,"MACRO QLA_norm_c");
  destR = QLA_norm_c(sC1);
  chkR = sqrt(sC1re*sC1re + sC1im*sC1im);
  CHECKeqsngRR(destR,chkR,name);

  strcpy(name,"MACRO QLA_arg_c");
  destR = QLA_arg_c(sC1);
  chkR = atan2(sC1im,sC1re);
  CHECKeqsngRR(destR,chkR,name);

  /* Unary operations */

  strcpy(name,"MACRO QLA_c_eq_r");
  QLA_c_eq_r(destC,sC1re);
  CHECKeqsngCRR(destC,sC1re,0.,name);
  
  strcpy(name,"MACRO QLA_c_eq_c");
  QLA_c_eq_c(destC,sC1);
  CHECKeqsngCRR(destC,sC1re,sC1im,name);

  strcpy(name,"MACRO QLA_c_eqm_r");
  QLA_c_eqm_r(destC,sC1re);
  CHECKeqsngCRR(destC,-sC1re,0.,name);
  
  strcpy(name,"MACRO QLA_c_eqm_c");
  QLA_c_eqm_c(destC,sC1);
  CHECKeqsngCRR(destC,-sC1re,-sC1im,name);

  strcpy(name,"MACRO QLA_c_peq_r");
  QLA_c_eq_c(destC,sC2);
  QLA_c_peq_r(destC,sC1re);
  CHECKeqsngCRR(destC,sC1re+sC2re,sC2im,name);
  
  strcpy(name,"MACRO QLA_c_peq_c");
  QLA_c_eq_c(destC,sC2);
  QLA_c_peq_c(destC,sC1);
  CHECKeqsngCRR(destC,sC1re+sC2re,sC1im+sC2im,name);

  strcpy(name,"MACRO QLA_c_meq_r");
  QLA_c_eq_c(destC,sC2);
  QLA_c_meq_r(destC,sC1re);
  CHECKeqsngCRR(destC,-sC1re+sC2re,sC2im,name);
  
  strcpy(name,"MACRO QLA_c_meq_c");
  QLA_c_eq_c(destC,sC2);
  QLA_c_meq_c(destC,sC1);
  CHECKeqsngCRR(destC,-sC1re+sC2re,-sC1im+sC2im,name);

  strcpy(name,"MACRO QLA_c_eq_ca");
  QLA_c_eq_ca(destC,sC1);
  CHECKeqsngCRR(destC,sC1re,-sC1im,name);

  strcpy(name,"MACRO QLA_c_eqm_ca");
  QLA_c_eqm_ca(destC,sC1);
  CHECKeqsngCRR(destC,-sC1re,sC1im,name);

  strcpy(name,"MACRO QLA_c_peq_ca");
  QLA_c_eq_c(destC,sC2);
  QLA_c_peq_ca(destC,sC1);
  CHECKeqsngCRR(destC,sC1re+sC2re,-sC1im+sC2im,name);

  strcpy(name,"MACRO QLA_c_meq_ca");
  QLA_c_eq_c(destC,sC2);
  QLA_c_meq_ca(destC,sC1);
  CHECKeqsngCRR(destC,-sC1re+sC2re,sC1im+sC2im,name);

  strcpy(name,"MACRO QLA_r_eq_Re_c");
  QLA_r_eq_Re_c(destR,sC1);
  CHECKeqsngRR(destR,sC1re,name);

  strcpy(name,"MACRO QLA_r_eq_Im_c");
  QLA_r_eq_Im_c(destR,sC1);
  CHECKeqsngRR(destR,sC1im,name);

  strcpy(name,"MACRO QLA_r_eqm_Re_c");
  QLA_r_eqm_Re_c(destR,sC1);
  CHECKeqsngRR(destR,-sC1re,name);

  strcpy(name,"MACRO QLA_r_eqm_Im_c");
  QLA_r_eqm_Im_c(destR,sC1);
  CHECKeqsngRR(destR,-sC1im,name);

  strcpy(name,"MACRO QLA_r_peq_Re_c");
  destR = sR2;
  QLA_r_peq_Re_c(destR,sC1);
  CHECKeqsngRR(destR,sC1re+sR2,name);

  strcpy(name,"MACRO QLA_r_peq_Im_c");
  destR = sR2;
  QLA_r_peq_Im_c(destR,sC1);
  CHECKeqsngRR(destR,sC1im+sR2,name);

  strcpy(name,"MACRO QLA_r_meq_Re_c");
  destR = sR2;
  QLA_r_meq_Re_c(destR,sC1);
  CHECKeqsngRR(destR,-sC1re+sR2,name);

  strcpy(name,"MACRO QLA_r_meq_Im_c");
  destR = sR2;
  QLA_r_meq_Im_c(destR,sC1);
  CHECKeqsngRR(destR,-sC1im+sR2,name);

  strcpy(name,"MACRO QLA_c_eq_ic");
  QLA_c_eq_ic(destC,sC1);
  CHECKeqsngCRR(destC,-sC1im,sC1re,name);

  strcpy(name,"MACRO QLA_c_eqm_ic");
  QLA_c_eqm_ic(destC,sC1);
  CHECKeqsngCRR(destC,sC1im,-sC1re,name);

  strcpy(name,"MACRO QLA_c_peq_ic");
  QLA_c_eq_c(destC,sC2);
  QLA_c_peq_ic(destC,sC1);
  CHECKeqsngCRR(destC,-sC1im+sC2re,sC1re+sC2im,name);

  strcpy(name,"MACRO QLA_c_meq_ic");
  QLA_c_eq_c(destC,sC2);
  QLA_c_meq_ic(destC,sC1);
  CHECKeqsngCRR(destC,sC1im+sC2re,-sC1re+sC2im,name);

  /* Binary operations */

  strcpy(name,"MACRO QLA_c_eq_c_plus_c");
  QLA_c_eq_c_plus_c(destC,sC1,sC2);
  CHECKeqsngCRR(destC,sC1re+sC2re,sC1im+sC2im,name);

  strcpy(name,"MACRO QLA_c_eq_c_plus_ic");
  QLA_c_eq_c_plus_ic(destC,sC1,sC2);
  CHECKeqsngCRR(destC,sC1re-sC2im,sC1im+sC2re,name);

  strcpy(name,"MACRO QLA_c_eq_r_plus_ir");
  QLA_c_eq_r_plus_ir(destC,sC1re,sC1im);
  CHECKeqsngCRR(destC,sC1re,sC1im,name);
  
  strcpy(name,"MACRO QLA_c_peq_r_plus_ir");
  QLA_c_eq_c(destC,sC2);
  QLA_c_peq_r_plus_ir(destC,sC1re,sC1im);
  CHECKeqsngCRR(destC,sC1re+sC2re,sC1im+sC2im,name);

  strcpy(name,"MACRO QLA_c_eqm_r_plus_ir");
  QLA_c_eqm_r_plus_ir(destC,sC1re,sC1im);
  CHECKeqsngCRR(destC,-sC1re,-sC1im,name);
  
  strcpy(name,"MACRO QLA_c_meq_r_plus_ir");
  QLA_c_eq_c(destC,sC2);
  QLA_c_meq_r_plus_ir(destC,sC1re,sC1im);
  CHECKeqsngCRR(destC,-sC1re+sC2re,-sC1im+sC2im,name);

  strcpy(name,"MACRO QLA_c_eq_c_minus_c");
  QLA_c_eq_c_minus_c(destC,sC1,sC2);
  CHECKeqsngCRR(destC,sC1re-sC2re,sC1im-sC2im,name);

  strcpy(name,"MACRO QLA_c_eq_c_minus_ca");
  QLA_c_eq_c_minus_ca(destC,sC1,sC2);
  CHECKeqsngCRR(destC,sC1re-sC2re,sC1im+sC2im,name);

  strcpy(name,"MACRO QLA_c_eq_c_minus_ic");
  QLA_c_eq_c_minus_ic(destC,sC1,sC2);
  CHECKeqsngCRR(destC,sC1re+sC2im,sC1im-sC2re,name);

  strcpy(name,"MACRO QLA_c_eq_c_times_c");
  QLA_c_eq_c_times_c(destC,sC1,sC2);
  CHECKeqsngCRR(destC,sC1re*sC2re-sC1im*sC2im,sC1re*sC2im+sC1im*sC2re,name);

  strcpy(name,"MACRO QLA_c_peq_c_times_c");
  QLA_c_eq_c(destC,sC3);
  QLA_c_peq_c_times_c(destC,sC1,sC2);
  CHECKeqsngCRR(destC,sC3re+sC1re*sC2re-sC1im*sC2im,sC3im+sC1re*sC2im+sC1im*sC2re,name);

  strcpy(name,"MACRO QLA_c_eqm_c_times_c");
  QLA_c_eqm_c_times_c(destC,sC1,sC2);
  CHECKeqsngCRR(destC,-sC1re*sC2re+sC1im*sC2im,-sC1re*sC2im-sC1im*sC2re,name);

  strcpy(name,"MACRO QLA_c_meq_c_times_c");
  QLA_c_eq_c(destC,sC3);
  QLA_c_meq_c_times_c(destC,sC1,sC2);
  CHECKeqsngCRR(destC,sC3re-sC1re*sC2re+sC1im*sC2im,sC3im-sC1re*sC2im-sC1im*sC2re,name);

  strcpy(name,"MACRO QLA_r_eq_Re_c_times_c");
  QLA_r_eq_Re_c_times_c(destR,sC1,sC2);
  CHECKeqsngRR(destR,sC1re*sC2re-sC1im*sC2im,name);

  strcpy(name,"MACRO QLA_r_peq_Re_c_times_c");
  destR = sR3;
  QLA_r_peq_Re_c_times_c(destR,sC1,sC2);
  CHECKeqsngRR(destR,sR3+sC1re*sC2re-sC1im*sC2im,name);

  strcpy(name,"MACRO QLA_r_eqm_Re_c_times_c");
  QLA_r_eqm_Re_c_times_c(destR,sC1,sC2);
  CHECKeqsngRR(destR,-sC1re*sC2re+sC1im*sC2im,name);

  strcpy(name,"MACRO QLA_r_meq_Re_c_times_c");
  destR = sR3;
  QLA_r_meq_Re_c_times_c(destR,sC1,sC2);
  CHECKeqsngRR(destR,sR3-sC1re*sC2re+sC1im*sC2im,name);

  strcpy(name,"MACRO QLA_r_eq_Im_c_times_c");
  QLA_r_eq_Im_c_times_c(destR,sC1,sC2);
  CHECKeqsngRR(destR,sC1re*sC2im+sC1im*sC2re,name);

  strcpy(name,"MACRO QLA_r_peq_Im_c_times_c");
  destR = sR3;
  QLA_r_peq_Im_c_times_c(destR,sC1,sC2);
  CHECKeqsngRR(destR,sR3+sC1re*sC2im+sC1im*sC2re,name);

  strcpy(name,"MACRO QLA_r_eqm_Im_c_times_c");
  QLA_r_eqm_Im_c_times_c(destR,sC1,sC2);
  CHECKeqsngRR(destR,-sC1re*sC2im-sC1im*sC2re,name);

  strcpy(name,"MACRO QLA_r_meq_Im_c_times_c");
  destR = sR3;
  QLA_r_meq_Im_c_times_c(destR,sC1,sC2);
  CHECKeqsngRR(destR,sR3-sC1re*sC2im-sC1im*sC2re,name);

  strcpy(name,"MACRO QLA_c_eq_c_div_c");
  QLA_c_eq_c_div_c(destC,sC1,sC2);
  destR = QLA_norm2_c(sC2);
  CHECKeqsngCRR(destC,(sC1re*sC2re+sC1im*sC2im)/destR,
		(-sC1re*sC2im+sC1im*sC2re)/destR,name);

  strcpy(name,"MACRO QLA_c_eq_c_times_ca");
  QLA_c_eq_c_times_ca(destC,sC1,sC2);
  CHECKeqsngCRR(destC,sC1re*sC2re+sC1im*sC2im,-sC1re*sC2im+sC1im*sC2re,name);

  strcpy(name,"MACRO QLA_c_peq_c_times_ca");
  QLA_c_eq_c(destC,sC3);
  QLA_c_peq_c_times_ca(destC,sC1,sC2);
  CHECKeqsngCRR(destC,sC3re+sC1re*sC2re+sC1im*sC2im,sC3im-sC1re*sC2im+sC1im*sC2re,name);

  strcpy(name,"MACRO QLA_c_eqm_c_times_ca");
  QLA_c_eqm_c_times_ca(destC,sC1,sC2);
  CHECKeqsngCRR(destC,-sC1re*sC2re-sC1im*sC2im,sC1re*sC2im-sC1im*sC2re,name);

  strcpy(name,"MACRO QLA_c_meq_c_times_ca");
  QLA_c_eq_c(destC,sC3);
  QLA_c_meq_c_times_ca(destC,sC1,sC2);
  CHECKeqsngCRR(destC,sC3re-sC1re*sC2re-sC1im*sC2im,sC3im+sC1re*sC2im-sC1im*sC2re,name);

  strcpy(name,"MACRO QLA_c_eq_ca_times_c");
  QLA_c_eq_ca_times_c(destC,sC1,sC2);
  CHECKeqsngCRR(destC,sC1re*sC2re+sC1im*sC2im,sC1re*sC2im-sC1im*sC2re,name);

  strcpy(name,"MACRO QLA_c_peq_ca_times_c");
  QLA_c_eq_c(destC,sC3);
  QLA_c_peq_ca_times_c(destC,sC1,sC2);
  CHECKeqsngCRR(destC,sC3re+sC1re*sC2re+sC1im*sC2im,sC3im+sC1re*sC2im-sC1im*sC2re,name);

  strcpy(name,"MACRO QLA_c_eqm_ca_times_c");
  QLA_c_eqm_ca_times_c(destC,sC1,sC2);
  CHECKeqsngCRR(destC,-sC1re*sC2re-sC1im*sC2im,-sC1re*sC2im+sC1im*sC2re,name);

  strcpy(name,"MACRO QLA_c_meq_ca_times_c");
  QLA_c_eq_c(destC,sC3);
  QLA_c_meq_ca_times_c(destC,sC1,sC2);
  CHECKeqsngCRR(destC,sC3re-sC1re*sC2re-sC1im*sC2im,sC3im-sC1re*sC2im+sC1im*sC2re,name);

  strcpy(name,"MACRO QLA_c_eq_ca_times_ca");
  QLA_c_eq_ca_times_ca(destC,sC1,sC2);
  CHECKeqsngCRR(destC,sC1re*sC2re-sC1im*sC2im,-sC1re*sC2im-sC1im*sC2re,name);

  strcpy(name,"MACRO QLA_c_peq_ca_times_ca");
  QLA_c_eq_c(destC,sC3);
  QLA_c_peq_ca_times_ca(destC,sC1,sC2);
  CHECKeqsngCRR(destC,sC3re+sC1re*sC2re-sC1im*sC2im,sC3im-sC1re*sC2im-sC1im*sC2re,name);

  strcpy(name,"MACRO QLA_c_eqm_ca_times_ca");
  QLA_c_eqm_ca_times_ca(destC,sC1,sC2);
  CHECKeqsngCRR(destC,-sC1re*sC2re+sC1im*sC2im,sC1re*sC2im+sC1im*sC2re,name);

  strcpy(name,"MACRO QLA_c_meq_ca_times_ca");
  QLA_c_eq_c(destC,sC3);
  QLA_c_meq_ca_times_ca(destC,sC1,sC2);
  CHECKeqsngCRR(destC,sC3re-sC1re*sC2re+sC1im*sC2im,sC3im+sC1re*sC2im+sC1im*sC2re,name);

  strcpy(name,"MACRO QLA_c_eq_c_times_r");
  QLA_c_eq_c_times_r(destC,sC1,sR2);
  CHECKeqsngCRR(destC,sC1re*sR2,sC1im*sR2,name);

  strcpy(name,"MACRO QLA_c_peq_c_times_r");
  QLA_c_eq_c(destC,sC3);
  QLA_c_peq_c_times_r(destC,sC1,sR2);
  CHECKeqsngCRR(destC,sC3re+sC1re*sR2,sC3im+sC1im*sR2,name);

  strcpy(name,"MACRO QLA_c_eqm_c_times_r");
  QLA_c_eqm_c_times_r(destC,sC1,sR2);
  CHECKeqsngCRR(destC,-sC1re*sR2,-sC1im*sR2,name);

  strcpy(name,"MACRO QLA_c_meq_c_times_r");
  QLA_c_eq_c(destC,sC3);
  QLA_c_meq_c_times_r(destC,sC1,sR2);
  CHECKeqsngCRR(destC,sC3re-sC1re*sR2,sC3im-sC1im*sR2,name);

  strcpy(name,"MACRO QLA_c_eq_r_times_c");
  QLA_c_eq_r_times_c(destC,sR1,sC2);
  CHECKeqsngCRR(destC,sR1*sC2re,sR1*sC2im,name);

  strcpy(name,"MACRO QLA_c_peq_r_times_c");
  QLA_c_eq_c(destC,sC3);
  QLA_c_peq_r_times_c(destC,sR1,sC2);
  CHECKeqsngCRR(destC,sC3re+sR1*sC2re,sC3im+sR1*sC2im,name);

  strcpy(name,"MACRO QLA_c_eqm_r_times_c");
  QLA_c_eqm_r_times_c(destC,sR1,sC2);
  CHECKeqsngCRR(destC,-sR1*sC2re,-sR1*sC2im,name);

  strcpy(name,"MACRO QLA_c_meq_r_times_c");
  QLA_c_eq_c(destC,sC3);
  QLA_c_meq_r_times_c(destC,sR1,sC2);
  CHECKeqsngCRR(destC,sC3re-sR1*sC2re,sC3im-sR1*sC2im,name);

  strcpy(name,"MACRO QLA_c_eq_c_div_r");
  QLA_c_eq_c_div_r(destC,sC1,sR2);
  CHECKeqsngCRR(destC,sC1re/sR2,sC1im/sR2,name);

  /* Ternary operations */

  strcpy(name,"MACRO QLA_c_eq_c_times_c_plus_c");
  QLA_c_eq_c_times_c_plus_c(destC,sC1,sC2,sC3);
  CHECKeqsngCRR(destC,sC1re*sC2re-sC1im*sC2im+sC3re,
		sC1re*sC2im+sC1im*sC2re+sC3im,name);

  strcpy(name,"MACRO QLA_c_eq_c_times_c_minus_c");
  QLA_c_eq_c_times_c_minus_c(destC,sC1,sC2,sC3);
  CHECKeqsngCRR(destC,sC1re*sC2re-sC1im*sC2im-sC3re,
		sC1re*sC2im+sC1im*sC2re-sC3im,name);

  strcpy(name,"MACRO QLA_c_eq_c_times_r_plus_r");
  QLA_c_eq_c_times_r_plus_r(destC,sC1,sR2,sR3);
  CHECKeqsngCRR(destC,sC1re*sR2+sR3,sC1im*sR2,name);

  strcpy(name,"MACRO QLA_c_eq_c_times_r_minus_r");
  QLA_c_eq_c_times_r_minus_r(destC,sC1,sR2,sR3);
  CHECKeqsngCRR(destC,sC1re*sR2-sR3,sC1im*sR2,name);

  strcpy(name,"MACRO QLA_c_eq_r_times_c_plus_c");
  QLA_c_eq_r_times_c_plus_c(destC,sR1,sC2,sC3);
  CHECKeqsngCRR(destC,sR1*sC2re+sC3re,sR1*sC2im+sC3im,name);

  strcpy(name,"MACRO QLA_c_eq_r_times_c_minus_c");
  QLA_c_eq_r_times_c_minus_c(destC,sR1,sC2,sC3);
  CHECKeqsngCRR(destC,sR1*sC2re-sC3re,sR1*sC2im-sC3im,name);

  return 0;
}
