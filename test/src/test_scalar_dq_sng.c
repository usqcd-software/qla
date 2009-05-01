/* QLA test code */
/* for single scalar routines.  Precision conversion */
/* Standalone C Code source */

#include <qla.h>
#include <qla_d.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "compare.h"

#define CHECKeqsngQRR(a,b,c,d) {QLA_Q_Real tmp1, tmp2; tmp1 = (a); tmp2 = (b); \
      checkeqsngQRR(&tmp1,&tmp2,c,d);}

#define CHECKeqsngDRR(a,b,c,d) {QLA_D_Real tmp1, tmp2; tmp1 = (a); tmp2 = (b); \
      checkeqsngDRR(&tmp1,&tmp2,c,d);}

#define CHECKeqsngQCC(a,b,c,d) {QLA_Q_Complex tmp1, tmp2; tmp1 = (a); tmp2 = (b); \
      checkeqsngQCC(&tmp1,&tmp2,c,d);}

#define CHECKeqsngDCC(a,b,c,d) {QLA_D_Complex tmp1, tmp2; tmp1 = (a); tmp2 = (b); \
      checkeqsngDCC(&tmp1,&tmp2,c,d);}


int main(int argc, char *argv[]){

  QLA_Int sI2 = 0;
  QLA_Int sI3 = 7032;

  QLA_D_Real sRD1,sRD2;
  QLA_Q_Real sRQ1;

  QLA_D_Complex sCD1,sCD2;
  QLA_Q_Complex sCQ1;

  QLA_D_Complex destCD,chkCD;
  QLA_Q_Complex destCQ,chkCQ;

  QLA_D_Real destRD,chkRD;
  QLA_Q_Real destRQ,chkRQ;

  QLA_RandomState sS1;

  char name[64];
  FILE *fp;

  char *test_program_name= basename(argv[0]); 
  test_program_name = strcat(test_program_name, ".result");
  if (NULL == (fp = fopen(test_program_name,"w"))) {
    fprintf(stderr, "Error in report function - cannot create \"%s\"\n", test_program_name);
    exit(-1);
  }

  /* Initialize random values */

  QLA_S_eq_seed_i_I(&sS1,sI2,&sI3);
  QLA_D_R_eq_gaussian_S(&sRD1,&sS1);
  QLA_D_R_eq_gaussian_S(&sRD2,&sS1);
  sRQ1 = sRD1*sRD2;
  QLA_D_C_eq_gaussian_S(&sCD1,&sS1);
  QLA_D_C_eq_gaussian_S(&sCD2,&sS1);
  QLA_c_eq_c_times_c(sCQ1,sCD1,sCD2);

  /* QLA_QD_R_eq_R */

  strcpy(name,"QLA_DQ_R_eq_R");
  QLA_DQ_R_eq_R(&destRD,&sRQ1);
  chkRD = sRQ1;
  CHECKeqsngDRR(destRD,chkRD,name,fp);

  /* QLA_QD_C_eq_C */

  strcpy(name,"QLA_DQ_C_eq_C");
  QLA_DQ_C_eq_C(&destCD,&sCQ1);
  QLA_c_eq_c(chkCD,sCQ1);
  CHECKeqsngDCC(destCD,chkCD,name,fp);

  /* QLA_QD_r_eq_sum_R */

  strcpy(name,"QLA_QD_r_eq_sum_R");
  QLA_QD_r_eq_sum_R(&destRQ,&sRD2);
  chkRQ = sRD2;
  CHECKeqsngQRR(destRQ,chkRQ,name,fp);

  /* QLA_QD_r_eq_norm2_R */

  strcpy(name,"QLA_QD_r_eq_norm2_R");
  QLA_QD_r_eq_norm2_R(&destRQ,&sRD2);
  chkRQ = sRD2*sRD2;
  CHECKeqsngQRR(destRQ,chkRQ,name,fp);

  strcpy(name,"QLA_QD_r_eq_norm2_C");
  QLA_QD_r_eq_norm2_C(&destRQ,&sCD1);
  chkRQ = QLA_norm2_c(sCD1);
  CHECKeqsngQRR(destRQ,chkRQ,name,fp);

  /* QLA_QD_R_eq_R_dot_R */

  strcpy(name,"QLA_QD_r_eq_R_dot_R");
  QLA_QD_r_eq_R_dot_R(&destRQ,&sRD1,&sRD2);
  chkRQ = sRD1*sRD2;
  CHECKeqsngQRR(destRQ,chkRQ,name,fp);

  strcpy(name,"QLA_QD_c_eq_C_dot_C");
  QLA_QD_c_eq_C_dot_C(&destCQ,&sCD1,&sCD2);
  QLA_c_eq_ca_times_c(chkCQ,sCD1,sCD2);
  CHECKeqsngQCC(destCQ,chkCQ,name,fp);

  strcpy(name,"QLA_QD_r_eq_re_C_dot_C");
  QLA_QD_r_eq_re_C_dot_C(&destRQ,&sCD1,&sCD2);
  QLA_r_eq_Re_ca_times_c(chkRQ,sCD1,sCD2);
  CHECKeqsngQRR(destRQ,chkRQ,name,fp);

  /* QLA_QD_r_eq_sum_R */

  strcpy(name,"QLA_QD_r_eq_sum_R");
  QLA_QD_r_eq_sum_R(&destRQ,&sRD2);
  chkRQ = sRD2;
  CHECKeqsngQRR(destRQ,chkRQ,name,fp);

  strcpy(name,"QLA_QD_c_eq_sum_C");
  QLA_QD_c_eq_sum_C(&destCQ,&sCD2);
  QLA_c_eq_c(chkCQ,sCD2);
  CHECKeqsngQCC(destCQ,chkCQ,name,fp);

  return 0;
}
