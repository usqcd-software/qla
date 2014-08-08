/* QLA test code */
/* for indexed scalar routines.  Precision conversion */
/* C Code automatically generated from test_df_scalar_idx.m4 */

include(protocol_idx.m4)

`
#include <qla.h>
#include <qla_d.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "compare.h"

int main(int argc, char *argv[]){

#define QLA_PRF(x) QLA_DF_ ## x
#define QLA_PRD(x) QLA_QD_ ## x

  QLA_Q_Real chkrQ;

  QLA_D_Real sRD1[MAX] = { 61.88, -10.38,  73.59, -96.07,  50.32,
		92.37,   34.58, -21.10, -67.05, 104.01};

  QLA_D_Real sRD3[MAX] = {-23.59, -56.32, -55.88, -11.55, 145.46, 
		 219.29, 71.47, -268.80, 42.82, 54.72};

  QLA_D_Real sCD1re[MAX] = { 92.37,   34.58, -21.10, -67.05, 104.01,
		      61.88, -10.38,  73.59, -96.07,  50.32};

  QLA_D_Real sCD3re[MAX] = {219.29, 71.47, -268.80, 42.82, 54.72,
		     -23.59, -56.32, -55.88, -11.55, 145.46}; 

  QLA_D_Real sCD1im[MAX] = {-23.59, -61.06, -55.88 -68.99, -50.00,
		      92.37,   34.58, -21.10, -67.05, 104.01};

  QLA_D_Real sCD3im[MAX] = {-23.59, -56.32, -55.88, -11.55, 145.46, 
		      97.89, -44.57, 86.02, 42.82, 79.20};

  QLA_Q_Complex chkCQ[MAX];

  QLA_Q_Complex chkcQ;

  QLA_D_Complex sCD1[MAX],sCD3[MAX];

  /*int dRx[MAX]   = {8,5,6,7,1,2,9,0,3,4};*/
  int sR1x[MAX]  = {3,0,1,8,2,4,5,9,7,6};
  int sR2x[MAX] = {4,9,0,2,1,3,7,8,5,6};
  int sR3x[MAX] = {8,3,2,5,6,9,7,4,0,1};

  /*int dCx[MAX]  = {8,3,2,5,6,9,7,4,0,1};*/
  int sC1x[MAX] = {8,5,6,7,1,2,9,0,3,4};
  int sC2x[MAX] = {4,9,0,2,1,3,7,8,5,6};

  QLA_D_Real destRD[MAX],chkRD[MAX];

  QLA_D_Real destrD,chkrD;

  QLA_D_Complex destCD[MAX],chkCD[MAX];

  QLA_D_Complex destcD,chkcD;

  QLA_D_Real *sRD1p[MAX];

  QLA_D_Complex *sCD1p[MAX];

  QLA_F_Real sRF1[MAX] = { 61.88, -10.38,  73.59, -96.07,  50.32,
		92.37,   34.58, -21.10, -67.05, 104.01};

  QLA_F_Real sRF2[MAX] = {.2359, .6106, .5588, .6899, .5000,
		.9789, .4457, .8602, .4282, .7920};
  
  QLA_F_Real sRF3[MAX] = {-23.59, -56.32, -55.88, -11.55, 145.46, 
		 219.29, 71.47, -268.80, 42.82, 54.72};

  QLA_F_Real sCF1re[MAX] = { 92.37,   34.58, -21.10, -67.05, 104.01,
		      61.88, -10.38,  73.59, -96.07,  50.32};

  QLA_F_Real sCF2re[MAX] = { .9789, -.4457, .8602, .4282, .7920,
		     -.2359, -.6106, -.5588 -.6899, -.5000};
  
  QLA_F_Real sCF3re[MAX] = {219.29, 71.47, -268.80, 42.82, 54.72,
		     -23.59, -56.32, -55.88, -11.55, 145.46}; 

  QLA_F_Real sCF1im[MAX] = {-23.59, -61.06, -55.88 -68.99, -50.00,
		      92.37,   34.58, -21.10, -67.05, 104.01};

  QLA_F_Real sCF2im[MAX] = { .6188, -.1038,  .7359, -.9607,  .5032,
		     2.1929, .7147, -2.6880, .4282, .5472};
  
  QLA_F_Real sCF3im[MAX] = {-23.59, -56.32, -55.88, -11.55, 145.46, 
		      97.89, -44.57, 86.02, 42.82, 79.20};

  QLA_F_Complex sCF1[MAX],sCF2[MAX],sCF3[MAX];

  QLA_F_Real destRF[MAX],chkRF[MAX];

  QLA_F_Complex destCF[MAX],chkCF[MAX];

  QLA_F_Real *sRF1p[MAX],*sRF2p[MAX];

  QLA_F_Complex *sCF1p[MAX],*sCF2p[MAX];

  char name[64];
  FILE *fp;

  char *test_program_name= basename(argv[0]); 
  test_program_name = strcat(test_program_name, ".result");
  if (NULL == (fp = fopen(test_program_name,"w"))) {
    fprintf(stderr, "Error in report function - cannot create \"%s\"\n", test_program_name);
    exit(-1);
  }

  int i;

  for(i = 0; i < MAX; i++){
    sRD1p[i] = &sRD1[sR2x[i]];
    sRF1p[i] = &sRF1[sR2x[i]];
    sRF2p[i] = &sRF2[sR3x[i]];

    sCD1p[i] = &sCD1[sC1x[i]];
    sCF1p[i] = &sCF1[sC1x[i]];
    sCF2p[i] = &sCF2[sC2x[i]];
  }

  for(i = 0; i < MAX; i++){
    QLA_c_eq_r_plus_ir(sCD1[i],sCD1re[i],sCD1im[i]);
    QLA_c_eq_r_plus_ir(sCD3[i],sCD3re[i],sCD3im[i]);
    QLA_c_eq_r_plus_ir(sCF1[i],sCF1re[i],sCF1im[i]);
    QLA_c_eq_r_plus_ir(sCF2[i],sCF2re[i],sCF2im[i]);
    QLA_c_eq_r_plus_ir(sCF3[i],sCF3re[i],sCF3im[i]);
  }
'

/* Precision conversion */
unary_spec(R,eq,R,_DF,D,F)
unary_spec(C,eq,C,_DF,D,F)
unary_spec(R,eq,R,_FD,F,D)
unary_spec(C,eq,C,_FD,F,D)

/* Reductions */
unaryglobalnorm2real(r,eq_norm2,R,_DF,D,F)
unaryglobalnorm2(r,eq_norm2,C,_DF,D,F)
binaryglobaldotreal(r,eq,R,dot,R,_DF,D,F,F)
binaryglobaldot(c,eq,C,dot,C,_DF,D,F,F)
binaryglobaldot(c,eq,Ca,dot,C,_DF,D,F,F)
binaryglobaldotreal(r,eq_re,C,dot,C,_DF,D,F,F)
unarysumreal(r,eq_sum,R,_DF,D,F)
unarysum(c,eq_sum,C,_DF,D,F)

`
  return 0;
}
'
