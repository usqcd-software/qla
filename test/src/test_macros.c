/* Test macros for complex arithmetic in qla_complex.h */

#include <qla.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#if (__STDC_VERSION__ >= 199901L) && !defined(__STDC_NO_COMPLEX__)
#include <complex.h>
#endif
#include "compare.h"

#define CHECKeqsngII(a,b,c,d) {QLA_Int tmp1,tmp2; tmp1 = (a); tmp2 = (b); \
    checkeqsngII(&tmp1,&tmp2,c,d); (a) = -999; }

#define CHECKeqsngRR(a,b,c,d) {QLA_Real tmp1,tmp2; tmp1 = (a); tmp2 = (b); \
    checkeqsngRR(&tmp1,&tmp2,c,d); (a) = -999.999; }

#define CHECKeqsngCC(a,b,c,d) {checkeqsngCC(&a,&b,c,d); QLA_c_eq_r_plus_ir(a,-999.999,99.99); }

#define CHECKeqsngCRR(a,b,c,d,e) {QLA_Real tmp1,tmp2; tmp1 = (b); tmp2 = (c); \
    checkeqsngCRR(&a,&tmp1,&tmp2,d,e); QLA_c_eq_r_plus_ir(a,-999.999,99.99); }

#define STR(x) #x
#define STRM(x) STR(x)
#define MACROP "MACRO " STRM(QLA_Precision) " "
#define IDENT(x) x
#define QLAP3(x,y) QLA_ ## x ## _ ## y
#define QLAP2(x,y) QLAP3(x,y)
#define QLAP(x) QLAP2(QLA_PrecisionLetter,x)

int main(int argc, char *argv[]){

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
  FILE *fp;

  char *test_program_name= basename(argv[0]); 
  test_program_name = strcat(test_program_name, ".result");
  if (NULL == (fp = fopen(test_program_name,"w"))) {
    fprintf(stderr, "Error in report function - cannot create \"%s\"\n", test_program_name);
    exit(-1);
  }

  /* Assign values for complex constants */

  QLA_c_eq_r_plus_ir(sC1,sC1re,sC1im);
  QLA_c_eq_r_plus_ir(sC2,sC2re,sC2im);
  QLA_c_eq_r_plus_ir(sC3,sC3re,sC3im);

  /* Test checks */

  strcpy(name,MACROP"CHECKeqsngRR");
  destR = sC1re;
  CHECKeqsngRR(destR,destR,name,fp);

  strcpy(name,MACROP"CHECKeqsngCRR");
  destC = sC1;
  CHECKeqsngCRR(destC,sC1re,sC1im,name,fp);

  strcpy(name,MACROP"CHECKeqsngCC");
  destC = sC1;
  CHECKeqsngCC(destC,sC1,name,fp);

  /* Test accessors */

  strcpy(name,MACROP"QLA_real");
  destR = QLA_real(sC1);
  chkR = sC1re;
  CHECKeqsngRR(destR,chkR,name,fp);

  strcpy(name,MACROP"QLA_imag");
  destR = QLA_imag(sC1);
  chkR = sC1im;
  CHECKeqsngRR(destR,chkR,name,fp);

  strcpy(name,MACROP"QLA_norm2_c");
  destR = QLA_norm2_c(sC1);
  chkR = sC1re*sC1re + sC1im*sC1im;
  CHECKeqsngRR(destR,chkR,name,fp);

  strcpy(name,MACROP"QLA_norm_c");
  destR = QLA_norm_c(sC1);
  chkR = sqrt(sC1re*sC1re + sC1im*sC1im);
  CHECKeqsngRR(destR,chkR,name,fp);

  strcpy(name,MACROP"QLA_arg_c");
  destR = QLA_arg_c(sC1);
  chkR = atan2(sC1im,sC1re);
  CHECKeqsngRR(destR,chkR,name,fp);

#if (__STDC_VERSION__ >= 199901L) && !defined(__STDC_NO_COMPLEX__)
  {
#if QLA_Precision == 'F'
    float _Complex z99 = 0;
#elif QLA_Precision == 'D'
    double _Complex z99 = 0;
#else
    long double _Complex z99 = 0;
#endif

    strcpy(name,MACROP"QLA_c99_eq_c");
    QLA_c99_eq_c(z99, sC1);
    destR = creall(z99);
    CHECKeqsngRR(destR,sC1re,name,fp);
    destR = cimagl(z99);
    CHECKeqsngRR(destR,sC1im,name,fp);

    strcpy(name,MACROP"QLA_c_eq_c99");
    QLA_c_eq_c99(destC, z99);
    CHECKeqsngCC(destC,sC1,name,fp);
  }
#endif

  strcpy(name,MACROP"QLA_" STRM(QLA_PrecisionLetter) "_norm_c");
  destR = QLAP(norm_c)(sC1);
  chkR = sqrt(sC1re*sC1re + sC1im*sC1im);
  CHECKeqsngRR(destR,chkR,name,fp);

  strcpy(name,MACROP"QLA_" STRM(QLA_PrecisionLetter) "_arg_c");
  destR = QLAP(arg_c)(sC1);
  chkR = atan2(sC1im,sC1re);
  CHECKeqsngRR(destR,chkR,name,fp);

  /* Test precision conversion */

#if QLA_Precision == 'F'

  strcpy(name,MACROP"QLA_FD_r");
  { QLA_D_Real s = (QLA_D_Real) sR1;
    QLA_F_Real d = QLA_FD_r(s);
    destR = (QLA_Real) d;
    CHECKeqsngRR(destR,sR1,name,fp);
  }

  strcpy(name,MACROP"QLA_DF_r");
  { QLA_F_Real s = (QLA_F_Real) sR1;
    QLA_D_Real d = QLA_DF_r(s);
    destR = (QLA_Real) d;
    CHECKeqsngRR(destR,sR1,name,fp);
  }

  strcpy(name,MACROP"QLA_FD_c");
  { QLA_D_Complex s; QLA_c_eq_r_plus_ir(s,sC1re,sC1im);
    QLA_F_Complex d = QLA_FD_c(s);
    QLA_c_eq_r_plus_ir(destC, QLA_real(d), QLA_imag(d));
    CHECKeqsngCRR(destC,sC1re,sC1im,name,fp);
  }

  strcpy(name,MACROP"QLA_DF_c");
  { QLA_F_Complex s; QLA_c_eq_r_plus_ir(s,sC1re,sC1im);
    QLA_D_Complex d = QLA_DF_c(s);
    QLA_c_eq_r_plus_ir(destC, QLA_real(d), QLA_imag(d));
    CHECKeqsngCRR(destC,sC1re,sC1im,name,fp);
  }

  strcpy(name,MACROP"QLA_FD_c_eq_c");
  { QLA_D_Complex s; QLA_c_eq_r_plus_ir(s,sC1re,sC1im);
    QLA_F_Complex d; QLA_FD_c_eq_c(d, s);
    QLA_c_eq_r_plus_ir(destC, QLA_real(d), QLA_imag(d));
    CHECKeqsngCRR(destC,sC1re,sC1im,name,fp);
  }

  strcpy(name,MACROP"QLA_DF_c_eq_c");
  { QLA_F_Complex s; QLA_c_eq_r_plus_ir(s,sC1re,sC1im);
    QLA_D_Complex d; QLA_DF_c_eq_c(d, s);
    QLA_c_eq_r_plus_ir(destC, QLA_real(d), QLA_imag(d));
    CHECKeqsngCRR(destC,sC1re,sC1im,name,fp);
  }

#elif QLA_Precision == 'D'

  strcpy(name,MACROP"QLA_DQ_r");
  { QLA_Q_Real s = (QLA_Q_Real) sR1;
    QLA_D_Real d = QLA_DQ_r(s);
    destR = (QLA_Real) d;
    CHECKeqsngRR(destR,sR1,name,fp);
  }

  strcpy(name,MACROP"QLA_QD_r");
  { QLA_D_Real s = (QLA_D_Real) sR1;
    QLA_Q_Real d = QLA_QD_r(s);
    destR = (QLA_Real) d;
    CHECKeqsngRR(destR,sR1,name,fp);
  }

  strcpy(name,MACROP"QLA_DQ_c");
  { QLA_Q_Complex s; QLA_c_eq_r_plus_ir(s,sC1re,sC1im);
    QLA_D_Complex d = QLA_DQ_c(s);
    QLA_c_eq_r_plus_ir(destC, QLA_real(d), QLA_imag(d));
    CHECKeqsngCRR(destC,sC1re,sC1im,name,fp);
  }

  strcpy(name,MACROP"QLA_QD_c");
  { QLA_D_Complex s; QLA_c_eq_r_plus_ir(s,sC1re,sC1im);
    QLA_Q_Complex d = QLA_QD_c(s);
    QLA_c_eq_r_plus_ir(destC, QLA_real(d), QLA_imag(d));
    CHECKeqsngCRR(destC,sC1re,sC1im,name,fp);
  }

  strcpy(name,MACROP"QLA_DQ_c_eq_c");
  { QLA_Q_Complex s; QLA_c_eq_r_plus_ir(s,sC1re,sC1im);
    QLA_D_Complex d; QLA_DQ_c_eq_c(d, s);
    QLA_c_eq_r_plus_ir(destC, QLA_real(d), QLA_imag(d));
    CHECKeqsngCRR(destC,sC1re,sC1im,name,fp);
  }

  strcpy(name,MACROP"QLA_QD_c_eq_c");
  { QLA_D_Complex s; QLA_c_eq_r_plus_ir(s,sC1re,sC1im);
    QLA_Q_Complex d; QLA_QD_c_eq_c(d, s);
    QLA_c_eq_r_plus_ir(destC, QLA_real(d), QLA_imag(d));
    CHECKeqsngCRR(destC,sC1re,sC1im,name,fp);
  }

#endif

  /* Unary operations */

  strcpy(name,MACROP"QLA_c_eq_r");
  QLA_c_eq_r(destC,sC1re);
  CHECKeqsngCRR(destC,sC1re,0.,name,fp);
  
  strcpy(name,MACROP"QLA_c_eq_c");
  QLA_c_eq_c(destC,sC1);
  CHECKeqsngCRR(destC,sC1re,sC1im,name,fp);

  strcpy(name,MACROP"QLA_c_eqm_r");
  QLA_c_eqm_r(destC,sC1re);
  CHECKeqsngCRR(destC,-sC1re,0.,name,fp);
  
  strcpy(name,MACROP"QLA_c_eqm_c");
  QLA_c_eqm_c(destC,sC1);
  CHECKeqsngCRR(destC,-sC1re,-sC1im,name,fp);

  strcpy(name,MACROP"QLA_c_peq_r");
  QLA_c_eq_c(destC,sC2);
  QLA_c_peq_r(destC,sC1re);
  CHECKeqsngCRR(destC,sC1re+sC2re,sC2im,name,fp);
  
  strcpy(name,MACROP"QLA_c_peq_c");
  QLA_c_eq_c(destC,sC2);
  QLA_c_peq_c(destC,sC1);
  CHECKeqsngCRR(destC,sC1re+sC2re,sC1im+sC2im,name,fp);

  strcpy(name,MACROP"QLA_c_meq_r");
  QLA_c_eq_c(destC,sC2);
  QLA_c_meq_r(destC,sC1re);
  CHECKeqsngCRR(destC,-sC1re+sC2re,sC2im,name,fp);
  
  strcpy(name,MACROP"QLA_c_meq_c");
  QLA_c_eq_c(destC,sC2);
  QLA_c_meq_c(destC,sC1);
  CHECKeqsngCRR(destC,-sC1re+sC2re,-sC1im+sC2im,name,fp);

  strcpy(name,MACROP"QLA_c_eq_ca");
  QLA_c_eq_ca(destC,sC1);
  CHECKeqsngCRR(destC,sC1re,-sC1im,name,fp);

  strcpy(name,MACROP"QLA_c_eqm_ca");
  QLA_c_eqm_ca(destC,sC1);
  CHECKeqsngCRR(destC,-sC1re,sC1im,name,fp);

  strcpy(name,MACROP"QLA_c_peq_ca");
  QLA_c_eq_c(destC,sC2);
  QLA_c_peq_ca(destC,sC1);
  CHECKeqsngCRR(destC,sC1re+sC2re,-sC1im+sC2im,name,fp);

  strcpy(name,MACROP"QLA_c_meq_ca");
  QLA_c_eq_c(destC,sC2);
  QLA_c_meq_ca(destC,sC1);
  CHECKeqsngCRR(destC,-sC1re+sC2re,sC1im+sC2im,name,fp);

  strcpy(name,MACROP"QLA_r_eq_Re_c");
  QLA_r_eq_Re_c(destR,sC1);
  CHECKeqsngRR(destR,sC1re,name,fp);

  strcpy(name,MACROP"QLA_r_eq_Im_c");
  QLA_r_eq_Im_c(destR,sC1);
  CHECKeqsngRR(destR,sC1im,name,fp);

  strcpy(name,MACROP"QLA_r_eqm_Re_c");
  QLA_r_eqm_Re_c(destR,sC1);
  CHECKeqsngRR(destR,-sC1re,name,fp);

  strcpy(name,MACROP"QLA_r_eqm_Im_c");
  QLA_r_eqm_Im_c(destR,sC1);
  CHECKeqsngRR(destR,-sC1im,name,fp);

  strcpy(name,MACROP"QLA_r_peq_Re_c");
  destR = sR2;
  QLA_r_peq_Re_c(destR,sC1);
  CHECKeqsngRR(destR,sC1re+sR2,name,fp);

  strcpy(name,MACROP"QLA_r_peq_Im_c");
  destR = sR2;
  QLA_r_peq_Im_c(destR,sC1);
  CHECKeqsngRR(destR,sC1im+sR2,name,fp);

  strcpy(name,MACROP"QLA_r_meq_Re_c");
  destR = sR2;
  QLA_r_meq_Re_c(destR,sC1);
  CHECKeqsngRR(destR,-sC1re+sR2,name,fp);

  strcpy(name,MACROP"QLA_r_meq_Im_c");
  destR = sR2;
  QLA_r_meq_Im_c(destR,sC1);
  CHECKeqsngRR(destR,-sC1im+sR2,name,fp);

  strcpy(name,MACROP"QLA_c_eq_ic");
  QLA_c_eq_ic(destC,sC1);
  CHECKeqsngCRR(destC,-sC1im,sC1re,name,fp);

  strcpy(name,MACROP"QLA_c_eqm_ic");
  QLA_c_eqm_ic(destC,sC1);
  CHECKeqsngCRR(destC,sC1im,-sC1re,name,fp);

  strcpy(name,MACROP"QLA_c_peq_ic");
  QLA_c_eq_c(destC,sC2);
  QLA_c_peq_ic(destC,sC1);
  CHECKeqsngCRR(destC,-sC1im+sC2re,sC1re+sC2im,name,fp);

  strcpy(name,MACROP"QLA_c_meq_ic");
  QLA_c_eq_c(destC,sC2);
  QLA_c_meq_ic(destC,sC1);
  CHECKeqsngCRR(destC,sC1im+sC2re,-sC1re+sC2im,name,fp);

  /* Binary operations */

  strcpy(name,MACROP"QLA_c_eq_r_plus_ir");
  QLA_c_eq_r_plus_ir(destC,sC1re,sC1im);
  CHECKeqsngCRR(destC,sC1re,sC1im,name,fp);
  
  strcpy(name,MACROP"QLA_c_peq_r_plus_ir");
  QLA_c_eq_c(destC,sC2);
  QLA_c_peq_r_plus_ir(destC,sC1re,sC1im);
  CHECKeqsngCRR(destC,sC1re+sC2re,sC1im+sC2im,name,fp);

  strcpy(name,MACROP"QLA_c_eqm_r_plus_ir");
  QLA_c_eqm_r_plus_ir(destC,sC1re,sC1im);
  CHECKeqsngCRR(destC,-sC1re,-sC1im,name,fp);
  
  strcpy(name,MACROP"QLA_c_meq_r_plus_ir");
  QLA_c_eq_c(destC,sC2);
  QLA_c_meq_r_plus_ir(destC,sC1re,sC1im);
  CHECKeqsngCRR(destC,-sC1re+sC2re,-sC1im+sC2im,name,fp);

  strcpy(name,MACROP"QLA_c_eq_c_plus_c");
  QLA_c_eq_c_plus_c(destC,sC1,sC2);
  CHECKeqsngCRR(destC,sC1re+sC2re,sC1im+sC2im,name,fp);

  strcpy(name,MACROP"QLA_c_eqm_c_plus_c");
  QLA_c_eqm_c_plus_c(destC,sC1,sC2);
  CHECKeqsngCRR(destC,-sC1re-sC2re,-sC1im-sC2im,name,fp);

  strcpy(name,MACROP"QLA_c_peq_c_plus_c");
  QLA_c_eq_c(destC,sC3);
  QLA_c_peq_c_plus_c(destC,sC1,sC2);
  CHECKeqsngCRR(destC,sC3re+sC1re+sC2re,sC3im+sC1im+sC2im,name,fp);

  strcpy(name,MACROP"QLA_c_meq_c_plus_c");
  QLA_c_eq_c(destC,sC3);
  QLA_c_meq_c_plus_c(destC,sC1,sC2);
  CHECKeqsngCRR(destC,sC3re-sC1re-sC2re,sC3im-sC1im-sC2im,name,fp);

  strcpy(name,MACROP"QLA_c_eq_c_plus_ic");
  QLA_c_eq_c_plus_ic(destC,sC1,sC2);
  CHECKeqsngCRR(destC,sC1re-sC2im,sC1im+sC2re,name,fp);

  strcpy(name,MACROP"QLA_c_eqm_c_plus_ic");
  QLA_c_eqm_c_plus_ic(destC,sC1,sC2);
  CHECKeqsngCRR(destC,-sC1re+sC2im,-sC1im-sC2re,name,fp);

  strcpy(name,MACROP"QLA_c_peq_c_plus_ic");
  QLA_c_eq_c(destC,sC3);
  QLA_c_peq_c_plus_ic(destC,sC1,sC2);
  CHECKeqsngCRR(destC,sC3re+sC1re-sC2im,sC3im+sC1im+sC2re,name,fp);

  strcpy(name,MACROP"QLA_c_meq_c_plus_ic");
  QLA_c_eq_c(destC,sC3);
  QLA_c_meq_c_plus_ic(destC,sC1,sC2);
  CHECKeqsngCRR(destC,sC3re-sC1re+sC2im,sC3im-sC1im-sC2re,name,fp);

  strcpy(name,MACROP"QLA_c_eq_c_minus_c");
  QLA_c_eq_c_minus_c(destC,sC1,sC2);
  CHECKeqsngCRR(destC,sC1re-sC2re,sC1im-sC2im,name,fp);

  strcpy(name,MACROP"QLA_c_eqm_c_minus_c");
  QLA_c_eqm_c_minus_c(destC,sC1,sC2);
  CHECKeqsngCRR(destC,-sC1re+sC2re,-sC1im+sC2im,name,fp);

  strcpy(name,MACROP"QLA_c_peq_c_minus_c");
  QLA_c_eq_c(destC,sC3);
  QLA_c_peq_c_minus_c(destC,sC1,sC2);
  CHECKeqsngCRR(destC,sC3re+sC1re-sC2re,sC3im+sC1im-sC2im,name,fp);

  strcpy(name,MACROP"QLA_c_meq_c_minus_c");
  QLA_c_eq_c(destC,sC3);
  QLA_c_meq_c_minus_c(destC,sC1,sC2);
  CHECKeqsngCRR(destC,sC3re-sC1re+sC2re,sC3im-sC1im+sC2im,name,fp);

  strcpy(name,MACROP"QLA_c_eq_c_minus_ic");
  QLA_c_eq_c_minus_ic(destC,sC1,sC2);
  CHECKeqsngCRR(destC,sC1re+sC2im,sC1im-sC2re,name,fp);

  strcpy(name,MACROP"QLA_c_eqm_c_minus_ic");
  QLA_c_eqm_c_minus_ic(destC,sC1,sC2);
  CHECKeqsngCRR(destC,-sC1re-sC2im,-sC1im+sC2re,name,fp);

  strcpy(name,MACROP"QLA_c_peq_c_minus_ic");
  QLA_c_eq_c(destC,sC3);
  QLA_c_peq_c_minus_ic(destC,sC1,sC2);
  CHECKeqsngCRR(destC,sC3re+sC1re+sC2im,sC3im+sC1im-sC2re,name,fp);

  strcpy(name,MACROP"QLA_c_meq_c_minus_ic");
  QLA_c_eq_c(destC,sC3);
  QLA_c_meq_c_minus_ic(destC,sC1,sC2);
  CHECKeqsngCRR(destC,sC3re-sC1re-sC2im,sC3im-sC1im+sC2re,name,fp);

  strcpy(name,MACROP"QLA_c_eq_c_minus_ca");
  QLA_c_eq_c_minus_ca(destC,sC1,sC2);
  CHECKeqsngCRR(destC,sC1re-sC2re,sC1im+sC2im,name,fp);

  strcpy(name,MACROP"QLA_c_eq_c_times_c");
  QLA_c_eq_c_times_c(destC,sC1,sC2);
  CHECKeqsngCRR(destC,sC1re*sC2re-sC1im*sC2im,sC1re*sC2im+sC1im*sC2re,name,fp);

  strcpy(name,MACROP"QLA_c_peq_c_times_c");
  QLA_c_eq_c(destC,sC3);
  QLA_c_peq_c_times_c(destC,sC1,sC2);
  CHECKeqsngCRR(destC,sC3re+sC1re*sC2re-sC1im*sC2im,sC3im+sC1re*sC2im+sC1im*sC2re,name,fp);

  strcpy(name,MACROP"QLA_c_eqm_c_times_c");
  QLA_c_eqm_c_times_c(destC,sC1,sC2);
  CHECKeqsngCRR(destC,-sC1re*sC2re+sC1im*sC2im,-sC1re*sC2im-sC1im*sC2re,name,fp);

  strcpy(name,MACROP"QLA_c_meq_c_times_c");
  QLA_c_eq_c(destC,sC3);
  QLA_c_meq_c_times_c(destC,sC1,sC2);
  CHECKeqsngCRR(destC,sC3re-sC1re*sC2re+sC1im*sC2im,sC3im-sC1re*sC2im-sC1im*sC2re,name,fp);

  strcpy(name,MACROP"QLA_Re_c_times_c");
  destR = QLA_Re_c_times_c(sC1,sC2);
  CHECKeqsngRR(destR,sC1re*sC2re-sC1im*sC2im,name,fp);

  strcpy(name,MACROP"QLA_r_eq_Re_c_times_c");
  QLA_r_eq_Re_c_times_c(destR,sC1,sC2);
  CHECKeqsngRR(destR,sC1re*sC2re-sC1im*sC2im,name,fp);

  strcpy(name,MACROP"QLA_r_peq_Re_c_times_c");
  destR = sR3;
  QLA_r_peq_Re_c_times_c(destR,sC1,sC2);
  CHECKeqsngRR(destR,sR3+sC1re*sC2re-sC1im*sC2im,name,fp);

  strcpy(name,MACROP"QLA_r_eqm_Re_c_times_c");
  QLA_r_eqm_Re_c_times_c(destR,sC1,sC2);
  CHECKeqsngRR(destR,-sC1re*sC2re+sC1im*sC2im,name,fp);

  strcpy(name,MACROP"QLA_r_meq_Re_c_times_c");
  destR = sR3;
  QLA_r_meq_Re_c_times_c(destR,sC1,sC2);
  CHECKeqsngRR(destR,sR3-sC1re*sC2re+sC1im*sC2im,name,fp);

  strcpy(name,MACROP"QLA_r_eq_Im_c_times_c");
  QLA_r_eq_Im_c_times_c(destR,sC1,sC2);
  CHECKeqsngRR(destR,sC1re*sC2im+sC1im*sC2re,name,fp);

  strcpy(name,MACROP"QLA_r_peq_Im_c_times_c");
  destR = sR3;
  QLA_r_peq_Im_c_times_c(destR,sC1,sC2);
  CHECKeqsngRR(destR,sR3+sC1re*sC2im+sC1im*sC2re,name,fp);

  strcpy(name,MACROP"QLA_r_eqm_Im_c_times_c");
  QLA_r_eqm_Im_c_times_c(destR,sC1,sC2);
  CHECKeqsngRR(destR,-sC1re*sC2im-sC1im*sC2re,name,fp);

  strcpy(name,MACROP"QLA_r_meq_Im_c_times_c");
  destR = sR3;
  QLA_r_meq_Im_c_times_c(destR,sC1,sC2);
  CHECKeqsngRR(destR,sR3-sC1re*sC2im-sC1im*sC2re,name,fp);

  strcpy(name,MACROP"QLA_r_eq_Re_c_times_ca");
  QLA_r_eq_Re_c_times_ca(destR,sC1,sC2);
  CHECKeqsngRR(destR,sC1re*sC2re+sC1im*sC2im,name,fp);

  strcpy(name,MACROP"QLA_r_peq_Re_c_times_ca");
  destR = sR3;
  QLA_r_peq_Re_c_times_ca(destR,sC1,sC2);
  CHECKeqsngRR(destR,sR3+sC1re*sC2re+sC1im*sC2im,name,fp);

  strcpy(name,MACROP"QLA_r_eqm_Re_c_times_ca");
  QLA_r_eqm_Re_c_times_ca(destR,sC1,sC2);
  CHECKeqsngRR(destR,-sC1re*sC2re-sC1im*sC2im,name,fp);

  strcpy(name,MACROP"QLA_r_meq_Re_c_times_ca");
  destR = sR3;
  QLA_r_meq_Re_c_times_ca(destR,sC1,sC2);
  CHECKeqsngRR(destR,sR3-sC1re*sC2re-sC1im*sC2im,name,fp);

  strcpy(name,MACROP"QLA_r_eq_Im_c_times_ca");
  QLA_r_eq_Im_c_times_ca(destR,sC1,sC2);
  CHECKeqsngRR(destR,-sC1re*sC2im+sC1im*sC2re,name,fp);

  strcpy(name,MACROP"QLA_r_peq_Im_c_times_ca");
  destR = sR3;
  QLA_r_peq_Im_c_times_ca(destR,sC1,sC2);
  CHECKeqsngRR(destR,sR3-sC1re*sC2im+sC1im*sC2re,name,fp);

  strcpy(name,MACROP"QLA_r_eqm_Im_c_times_ca");
  QLA_r_eqm_Im_c_times_ca(destR,sC1,sC2);
  CHECKeqsngRR(destR,sC1re*sC2im-sC1im*sC2re,name,fp);

  strcpy(name,MACROP"QLA_r_meq_Im_c_times_ca");
  destR = sR3;
  QLA_r_meq_Im_c_times_ca(destR,sC1,sC2);
  CHECKeqsngRR(destR,sR3+sC1re*sC2im-sC1im*sC2re,name,fp);

  strcpy(name,MACROP"QLA_r_eq_Re_ca_times_c");
  QLA_r_eq_Re_ca_times_c(destR,sC1,sC2);
  CHECKeqsngRR(destR,sC1re*sC2re+sC1im*sC2im,name,fp);

  strcpy(name,MACROP"QLA_r_peq_Re_ca_times_c");
  destR = sR3;
  QLA_r_peq_Re_ca_times_c(destR,sC1,sC2);
  CHECKeqsngRR(destR,sR3+sC1re*sC2re+sC1im*sC2im,name,fp);

  strcpy(name,MACROP"QLA_r_eqm_Re_ca_times_c");
  QLA_r_eqm_Re_ca_times_c(destR,sC1,sC2);
  CHECKeqsngRR(destR,-sC1re*sC2re-sC1im*sC2im,name,fp);

  strcpy(name,MACROP"QLA_r_meq_Re_ca_times_c");
  destR = sR3;
  QLA_r_meq_Re_ca_times_c(destR,sC1,sC2);
  CHECKeqsngRR(destR,sR3-sC1re*sC2re-sC1im*sC2im,name,fp);

  strcpy(name,MACROP"QLA_r_eq_Im_ca_times_c");
  QLA_r_eq_Im_ca_times_c(destR,sC1,sC2);
  CHECKeqsngRR(destR,sC1re*sC2im-sC1im*sC2re,name,fp);

  strcpy(name,MACROP"QLA_r_peq_Im_ca_times_c");
  destR = sR3;
  QLA_r_peq_Im_ca_times_c(destR,sC1,sC2);
  CHECKeqsngRR(destR,sR3+sC1re*sC2im-sC1im*sC2re,name,fp);

  strcpy(name,MACROP"QLA_r_eqm_Im_ca_times_c");
  QLA_r_eqm_Im_ca_times_c(destR,sC1,sC2);
  CHECKeqsngRR(destR,-sC1re*sC2im+sC1im*sC2re,name,fp);

  strcpy(name,MACROP"QLA_r_meq_Im_ca_times_c");
  destR = sR3;
  QLA_r_meq_Im_ca_times_c(destR,sC1,sC2);
  CHECKeqsngRR(destR,sR3-sC1re*sC2im+sC1im*sC2re,name,fp);

  strcpy(name,MACROP"QLA_r_eq_Re_ca_times_ca");
  QLA_r_eq_Re_ca_times_ca(destR,sC1,sC2);
  CHECKeqsngRR(destR,sC1re*sC2re-sC1im*sC2im,name,fp);

  strcpy(name,MACROP"QLA_r_peq_Re_ca_times_ca");
  destR = sR3;
  QLA_r_peq_Re_ca_times_ca(destR,sC1,sC2);
  CHECKeqsngRR(destR,sR3+sC1re*sC2re-sC1im*sC2im,name,fp);

  strcpy(name,MACROP"QLA_r_eqm_Re_ca_times_ca");
  QLA_r_eqm_Re_ca_times_ca(destR,sC1,sC2);
  CHECKeqsngRR(destR,-sC1re*sC2re+sC1im*sC2im,name,fp);

  strcpy(name,MACROP"QLA_r_meq_Re_ca_times_ca");
  destR = sR3;
  QLA_r_meq_Re_ca_times_ca(destR,sC1,sC2);
  CHECKeqsngRR(destR,sR3-sC1re*sC2re+sC1im*sC2im,name,fp);

  strcpy(name,MACROP"QLA_r_eq_Im_ca_times_ca");
  QLA_r_eq_Im_ca_times_ca(destR,sC1,sC2);
  CHECKeqsngRR(destR,-sC1re*sC2im-sC1im*sC2re,name,fp);

  strcpy(name,MACROP"QLA_r_peq_Im_ca_times_ca");
  destR = sR3;
  QLA_r_peq_Im_ca_times_ca(destR,sC1,sC2);
  CHECKeqsngRR(destR,sR3-sC1re*sC2im-sC1im*sC2re,name,fp);

  strcpy(name,MACROP"QLA_r_eqm_Im_ca_times_ca");
  QLA_r_eqm_Im_ca_times_ca(destR,sC1,sC2);
  CHECKeqsngRR(destR,sC1re*sC2im+sC1im*sC2re,name,fp);

  strcpy(name,MACROP"QLA_r_meq_Im_ca_times_ca");
  destR = sR3;
  QLA_r_meq_Im_ca_times_ca(destR,sC1,sC2);
  CHECKeqsngRR(destR,sR3+sC1re*sC2im+sC1im*sC2re,name,fp);

  strcpy(name,MACROP"QLA_c_eq_c_times_ca");
  QLA_c_eq_c_times_ca(destC,sC1,sC2);
  CHECKeqsngCRR(destC,sC1re*sC2re+sC1im*sC2im,-sC1re*sC2im+sC1im*sC2re,name,fp);

  strcpy(name,MACROP"QLA_c_peq_c_times_ca");
  QLA_c_eq_c(destC,sC3);
  QLA_c_peq_c_times_ca(destC,sC1,sC2);
  CHECKeqsngCRR(destC,sC3re+sC1re*sC2re+sC1im*sC2im,sC3im-sC1re*sC2im+sC1im*sC2re,name,fp);

  strcpy(name,MACROP"QLA_c_eqm_c_times_ca");
  QLA_c_eqm_c_times_ca(destC,sC1,sC2);
  CHECKeqsngCRR(destC,-sC1re*sC2re-sC1im*sC2im,sC1re*sC2im-sC1im*sC2re,name,fp);

  strcpy(name,MACROP"QLA_c_meq_c_times_ca");
  QLA_c_eq_c(destC,sC3);
  QLA_c_meq_c_times_ca(destC,sC1,sC2);
  CHECKeqsngCRR(destC,sC3re-sC1re*sC2re-sC1im*sC2im,sC3im+sC1re*sC2im-sC1im*sC2re,name,fp);

  strcpy(name,MACROP"QLA_c_eq_ca_times_c");
  QLA_c_eq_ca_times_c(destC,sC1,sC2);
  CHECKeqsngCRR(destC,sC1re*sC2re+sC1im*sC2im,sC1re*sC2im-sC1im*sC2re,name,fp);

  strcpy(name,MACROP"QLA_c_peq_ca_times_c");
  QLA_c_eq_c(destC,sC3);
  QLA_c_peq_ca_times_c(destC,sC1,sC2);
  CHECKeqsngCRR(destC,sC3re+sC1re*sC2re+sC1im*sC2im,sC3im+sC1re*sC2im-sC1im*sC2re,name,fp);

  strcpy(name,MACROP"QLA_c_eqm_ca_times_c");
  QLA_c_eqm_ca_times_c(destC,sC1,sC2);
  CHECKeqsngCRR(destC,-sC1re*sC2re-sC1im*sC2im,-sC1re*sC2im+sC1im*sC2re,name,fp);

  strcpy(name,MACROP"QLA_c_meq_ca_times_c");
  QLA_c_eq_c(destC,sC3);
  QLA_c_meq_ca_times_c(destC,sC1,sC2);
  CHECKeqsngCRR(destC,sC3re-sC1re*sC2re-sC1im*sC2im,sC3im-sC1re*sC2im+sC1im*sC2re,name,fp);

  strcpy(name,MACROP"QLA_c_eq_ca_times_ca");
  QLA_c_eq_ca_times_ca(destC,sC1,sC2);
  CHECKeqsngCRR(destC,sC1re*sC2re-sC1im*sC2im,-sC1re*sC2im-sC1im*sC2re,name,fp);

  strcpy(name,MACROP"QLA_c_eqm_ca_times_ca");
  QLA_c_eqm_ca_times_ca(destC,sC1,sC2);
  CHECKeqsngCRR(destC,-sC1re*sC2re+sC1im*sC2im,sC1re*sC2im+sC1im*sC2re,name,fp);

  strcpy(name,MACROP"QLA_c_peq_ca_times_ca");
  QLA_c_eq_c(destC,sC3);
  QLA_c_peq_ca_times_ca(destC,sC1,sC2);
  CHECKeqsngCRR(destC,sC3re+sC1re*sC2re-sC1im*sC2im,sC3im-sC1re*sC2im-sC1im*sC2re,name,fp);

  strcpy(name,MACROP"QLA_c_meq_ca_times_ca");
  QLA_c_eq_c(destC,sC3);
  QLA_c_meq_ca_times_ca(destC,sC1,sC2);
  CHECKeqsngCRR(destC,sC3re-sC1re*sC2re+sC1im*sC2im,sC3im+sC1re*sC2im+sC1im*sC2re,name,fp);

  strcpy(name,MACROP"QLA_c_eq_c_times_r");
  QLA_c_eq_c_times_r(destC,sC1,sR2);
  CHECKeqsngCRR(destC,sC1re*sR2,sC1im*sR2,name,fp);

  strcpy(name,MACROP"QLA_c_peq_c_times_r");
  QLA_c_eq_c(destC,sC3);
  QLA_c_peq_c_times_r(destC,sC1,sR2);
  CHECKeqsngCRR(destC,sC3re+sC1re*sR2,sC3im+sC1im*sR2,name,fp);

  strcpy(name,MACROP"QLA_c_eqm_c_times_r");
  QLA_c_eqm_c_times_r(destC,sC1,sR2);
  CHECKeqsngCRR(destC,-sC1re*sR2,-sC1im*sR2,name,fp);

  strcpy(name,MACROP"QLA_c_meq_c_times_r");
  QLA_c_eq_c(destC,sC3);
  QLA_c_meq_c_times_r(destC,sC1,sR2);
  CHECKeqsngCRR(destC,sC3re-sC1re*sR2,sC3im-sC1im*sR2,name,fp);

  strcpy(name,MACROP"QLA_c_eq_r_times_c");
  QLA_c_eq_r_times_c(destC,sR1,sC2);
  CHECKeqsngCRR(destC,sR1*sC2re,sR1*sC2im,name,fp);

  strcpy(name,MACROP"QLA_c_peq_r_times_c");
  QLA_c_eq_c(destC,sC3);
  QLA_c_peq_r_times_c(destC,sR1,sC2);
  CHECKeqsngCRR(destC,sC3re+sR1*sC2re,sC3im+sR1*sC2im,name,fp);

  strcpy(name,MACROP"QLA_c_eqm_r_times_c");
  QLA_c_eqm_r_times_c(destC,sR1,sC2);
  CHECKeqsngCRR(destC,-sR1*sC2re,-sR1*sC2im,name,fp);

  strcpy(name,MACROP"QLA_c_meq_r_times_c");
  QLA_c_eq_c(destC,sC3);
  QLA_c_meq_r_times_c(destC,sR1,sC2);
  CHECKeqsngCRR(destC,sC3re-sR1*sC2re,sC3im-sR1*sC2im,name,fp);

  strcpy(name,MACROP"QLA_c_eq_ca_times_r");
  QLA_c_eq_ca_times_r(destC,sC1,sR2);
  CHECKeqsngCRR(destC,sC1re*sR2,-sC1im*sR2,name,fp);

  strcpy(name,MACROP"QLA_c_peq_ca_times_r");
  QLA_c_eq_c(destC,sC3);
  QLA_c_peq_ca_times_r(destC,sC1,sR2);
  CHECKeqsngCRR(destC,sC3re+sC1re*sR2,sC3im-sC1im*sR2,name,fp);

  strcpy(name,MACROP"QLA_c_eqm_ca_times_r");
  QLA_c_eqm_ca_times_r(destC,sC1,sR2);
  CHECKeqsngCRR(destC,-sC1re*sR2,sC1im*sR2,name,fp);

  strcpy(name,MACROP"QLA_c_meq_ca_times_r");
  QLA_c_eq_c(destC,sC3);
  QLA_c_meq_ca_times_r(destC,sC1,sR2);
  CHECKeqsngCRR(destC,sC3re-sC1re*sR2,sC3im+sC1im*sR2,name,fp);

  strcpy(name,MACROP"QLA_c_eq_r_times_ca");
  QLA_c_eq_r_times_ca(destC,sR1,sC2);
  CHECKeqsngCRR(destC,sR1*sC2re,-sR1*sC2im,name,fp);

  strcpy(name,MACROP"QLA_c_peq_r_times_ca");
  QLA_c_eq_c(destC,sC3);
  QLA_c_peq_r_times_ca(destC,sR1,sC2);
  CHECKeqsngCRR(destC,sC3re+sR1*sC2re,sC3im-sR1*sC2im,name,fp);

  strcpy(name,MACROP"QLA_c_eqm_r_times_ca");
  QLA_c_eqm_r_times_ca(destC,sR1,sC2);
  CHECKeqsngCRR(destC,-sR1*sC2re,sR1*sC2im,name,fp);

  strcpy(name,MACROP"QLA_c_meq_r_times_ca");
  QLA_c_eq_c(destC,sC3);
  QLA_c_meq_r_times_ca(destC,sR1,sC2);
  CHECKeqsngCRR(destC,sC3re-sR1*sC2re,sC3im+sR1*sC2im,name,fp);

  strcpy(name,MACROP"QLA_c_eq_c_div_r");
  QLA_c_eq_c_div_r(destC,sC1,sR2);
  CHECKeqsngCRR(destC,sC1re/sR2,sC1im/sR2,name,fp);

  strcpy(name,MACROP"QLA_c_eq_r_div_c");
  QLA_c_eq_r_div_c(destC,sR1,sC2);
  destR = sR1/QLA_norm2_c(sC2);
  CHECKeqsngCRR(destC,sC2re*destR,-sC2im*destR,name,fp);

  strcpy(name,MACROP"QLA_c_eq_c_div_c");
  QLA_c_eq_c_div_c(destC,sC1,sC2);
  destR = QLA_norm2_c(sC2);
  CHECKeqsngCRR(destC,(sC1re*sC2re+sC1im*sC2im)/destR,
		(-sC1re*sC2im+sC1im*sC2re)/destR,name,fp);

  strcpy(name,MACROP"QLA_" STRM(QLA_PrecisionLetter) "_c_eq_r_div_c");
  QLAP(c_eq_r_div_c)(destC,sR1,sC2);
  destR = sR1/QLA_norm2_c(sC2);
  CHECKeqsngCRR(destC,sC2re*destR,-sC2im*destR,name,fp);

  strcpy(name,MACROP"QLA_" STRM(QLA_PrecisionLetter) "_c_eq_c_div_c");
  QLAP(c_eq_c_div_c)(destC,sC1,sC2);
  destR = QLA_norm2_c(sC2);
  CHECKeqsngCRR(destC,(sC1re*sC2re+sC1im*sC2im)/destR,
		(-sC1re*sC2im+sC1im*sC2re)/destR,name,fp);

  /* Ternary operations */

  strcpy(name,MACROP"QLA_c_eq_c_times_c_plus_c");
  QLA_c_eq_c_times_c_plus_c(destC,sC1,sC2,sC3);
  CHECKeqsngCRR(destC,sC1re*sC2re-sC1im*sC2im+sC3re,
		sC1re*sC2im+sC1im*sC2re+sC3im,name,fp);

  strcpy(name,MACROP"QLA_c_eq_c_times_c_minus_c");
  QLA_c_eq_c_times_c_minus_c(destC,sC1,sC2,sC3);
  CHECKeqsngCRR(destC,sC1re*sC2re-sC1im*sC2im-sC3re,
		sC1re*sC2im+sC1im*sC2re-sC3im,name,fp);

  strcpy(name,MACROP"QLA_c_eqm_c_times_c_plus_c");
  QLA_c_eqm_c_times_c_plus_c(destC,sC1,sC2,sC3);
  CHECKeqsngCRR(destC,-sC1re*sC2re+sC1im*sC2im-sC3re,
		-sC1re*sC2im-sC1im*sC2re-sC3im,name,fp);

  strcpy(name,MACROP"QLA_c_eqm_c_times_c_minus_c");
  QLA_c_eqm_c_times_c_minus_c(destC,sC1,sC2,sC3);
  CHECKeqsngCRR(destC,-sC1re*sC2re+sC1im*sC2im+sC3re,
		-sC1re*sC2im-sC1im*sC2re+sC3im,name,fp);

  strcpy(name,MACROP"QLA_c_eq_c_times_r_plus_r");
  QLA_c_eq_c_times_r_plus_r(destC,sC1,sR2,sR3);
  CHECKeqsngCRR(destC,sC1re*sR2+sR3,sC1im*sR2,name,fp);

  strcpy(name,MACROP"QLA_c_eq_c_times_r_minus_r");
  QLA_c_eq_c_times_r_minus_r(destC,sC1,sR2,sR3);
  CHECKeqsngCRR(destC,sC1re*sR2-sR3,sC1im*sR2,name,fp);

  strcpy(name,MACROP"QLA_c_eq_r_times_c_plus_c");
  QLA_c_eq_r_times_c_plus_c(destC,sR1,sC2,sC3);
  CHECKeqsngCRR(destC,sR1*sC2re+sC3re,sR1*sC2im+sC3im,name,fp);

  strcpy(name,MACROP"QLA_c_eq_r_times_c_minus_c");
  QLA_c_eq_r_times_c_minus_c(destC,sR1,sC2,sC3);
  CHECKeqsngCRR(destC,sR1*sC2re-sC3re,sR1*sC2im-sC3im,name,fp);

  return 0;
}
