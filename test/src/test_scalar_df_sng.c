/* QLA test code */
/* for single scalar routines.  Precision conversion */
/* Standalone C Code source */

#include <qla.h>
#include <qla_d.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "compare.h"

#define CHECKeqsngDRR(a,b,c,d) {QLA_D_Real tmp1, tmp2; tmp1 = (a); tmp2 = (b); \
      checkeqsngDRR(&tmp1,&tmp2,c,d);}

#define CHECKeqsngFRR(a,b,c,d) {QLA_F_Real tmp1, tmp2; tmp1 = (a); tmp2 = (b); \
      checkeqsngFRR(&tmp1,&tmp2,c,d);}

#define CHECKeqsngDCC(a,b,c,d) {QLA_D_Complex tmp1, tmp2; tmp1 = (a); tmp2 = (b); \
      checkeqsngDCC(&tmp1,&tmp2,c,d);}

#define CHECKeqsngFCC(a,b,c,d) {QLA_F_Complex tmp1, tmp2; tmp1 = (a); tmp2 = (b); \
      checkeqsngFCC(&tmp1,&tmp2,c,d);}


int main(int argc, char *argv[]){

  QLA_Int sI2 = 0;
  QLA_Int sI3 = 7032;

  QLA_F_Real sRF1,sRF2;
  QLA_D_Real sRD1;

  QLA_F_Complex sCF1,sCF2;
  QLA_D_Complex sCD1;

  QLA_F_Complex destCF,chkCF;
  QLA_D_Complex destCD,chkCD;

  QLA_F_Real destRF,chkRF;
  QLA_D_Real destRD,chkRD;

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
  QLA_F_R_eq_gaussian_S(&sRF1,&sS1);
  QLA_F_R_eq_gaussian_S(&sRF2,&sS1);
  QLA_D_R_eq_gaussian_S(&sRD1,&sS1);
  QLA_F_C_eq_gaussian_S(&sCF1,&sS1);
  QLA_F_C_eq_gaussian_S(&sCF2,&sS1);
  QLA_D_C_eq_gaussian_S(&sCD1,&sS1);

  /* QLA_DF_R_eq_R */

  strcpy(name,"QLA_DF_R_eq_R");
  QLA_DF_R_eq_R(&destRD,&sRF1);
  chkRD = sRF1;
  CHECKeqsngDRR(destRD,chkRD,name,fp);

  strcpy(name,"QLA_FD_R_eq_R");
  QLA_FD_R_eq_R(&destRF,&sRD1);
  chkRF = sRD1;
  CHECKeqsngFRR(destRF,chkRF,name,fp);

  /* QLA_DF_C_eq_C */

  strcpy(name,"QLA_DF_C_eq_C");
  QLA_DF_C_eq_C(&destCD,&sCF1);
  QLA_c_eq_c(chkCD,sCF1);
  CHECKeqsngDCC(destCD,chkCD,name,fp);

  strcpy(name,"QLA_FD_C_eq_C");
  QLA_FD_C_eq_C(&destCF,&sCD1);
  QLA_c_eq_c(chkCF,sCD1);
  CHECKeqsngFCC(destCF,chkCF,name,fp);

  /* QLA_DF_r_eq_norm2_R */

  strcpy(name,"QLA_DF_r_eq_norm2_R");
  QLA_DF_r_eq_norm2_R(&destRD,&sRF2);
  chkRD = sRF2*sRF2;
  CHECKeqsngDRR(destRD,chkRD,name,fp);

  strcpy(name,"QLA_DF_r_eq_norm2_C");
  QLA_DF_r_eq_norm2_C(&destRD,&sCF1);
  chkRD = QLA_norm2_c(sCF1);
  CHECKeqsngDRR(destRD,chkRD,name,fp);

  /* QLA_DF_r_eq_R_dot_R */

  strcpy(name,"QLA_DF_r_eq_R_dot_R");
  QLA_DF_r_eq_R_dot_R(&destRD,&sRF1,&sRF2);
  chkRD = sRF1*sRF2;
  CHECKeqsngDRR(destRD,chkRD,name,fp);

  strcpy(name,"QLA_DF_c_eq_C_dot_C");
  QLA_DF_c_eq_C_dot_C(&destCD,&sCF1,&sCF2);
  QLA_c_eq_ca_times_c(chkCD,sCF1,sCF2);
  CHECKeqsngDCC(destCD,chkCD,name,fp);

  strcpy(name,"QLA_DF_r_eq_re_C_dot_C");
  QLA_DF_r_eq_re_C_dot_C(&destRD,&sCF1,&sCF2);
  QLA_r_eq_Re_ca_times_c(chkRD,sCF1,sCF2);
  CHECKeqsngDRR(destRD,chkRD,name,fp);

  /* QLA_DF_r_eq_sum_R */

  strcpy(name,"QLA_DF_r_eq_sum_R");
  QLA_DF_r_eq_sum_R(&destRD,&sRF2);
  chkRD = sRF2;
  CHECKeqsngDRR(destRD,chkRD,name,fp);

  strcpy(name,"QLA_DF_c_eq_sum_C");
  QLA_DF_c_eq_sum_C(&destCD,&sCF2);
  QLA_c_eq_c(chkCD,sCF2);
  CHECKeqsngDCC(destCD,chkCD,name,fp);

  return 0;
}
