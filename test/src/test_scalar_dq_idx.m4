/* QLA test code */
/* for indexed scalar routines.  Precision conversion */
/* C Code automatically generated from test_dq_scalar_idx.m4 */

include(protocol_idx.m4)

`
#include <qla.h>
#include <qla_d.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "compare.h"

int main(){

  QLA_Q_Real sRQ1[MAX] = { 61.88, -10.38,  73.59, -96.07,  50.32,
		92.37,   34.58, -21.10, -67.05, 104.01};

  QLA_Q_Real sRQ3[MAX] = {-23.59, -56.32, -55.88, -11.55, 145.46, 
		 219.29, 71.47, -268.80, 42.82, 54.72};

  QLA_Q_Real sCQ1re[MAX] = { 92.37,   34.58, -21.10, -67.05, 104.01,
		      61.88, -10.38,  73.59, -96.07,  50.32};

  QLA_Q_Real sCQ3re[MAX] = {219.29, 71.47, -268.80, 42.82, 54.72,
		     -23.59, -56.32, -55.88, -11.55, 145.46}; 

  QLA_Q_Real sCQ1im[MAX] = {-23.59, -61.06, -55.88 -68.99, -50.00,
		      92.37,   34.58, -21.10, -67.05, 104.01};

  QLA_Q_Real sCQ3im[MAX] = {-23.59, -56.32, -55.88, -11.55, 145.46, 
		      97.89, -44.57, 86.02, 42.82, 79.20};

  QLA_Q_Complex destCQ[MAX],chkCQ[MAX];

  QLA_Q_Complex destcQ,chkcQ;

  QLA_Q_Complex sCQ1[MAX],sCQ3[MAX];

  int dRx[MAX]   = {8,5,6,7,1,2,9,0,3,4};
  int sR1x[MAX]  = {3,0,1,8,2,4,5,9,7,6};
  int sR2x[MAX] = {4,9,0,2,1,3,7,8,5,6};
  int sR3x[MAX] = {8,3,2,5,6,9,7,4,0,1};

  int dCx[MAX]  = {8,3,2,5,6,9,7,4,0,1};
  int sC1x[MAX] = {8,5,6,7,1,2,9,0,3,4};
  int sC2x[MAX] = {4,9,0,2,1,3,7,8,5,6};

  QLA_Q_Real destRQ[MAX],chkRQ[MAX];

  QLA_Q_Real destrQ,chkrQ;

  QLA_Q_Real *sRQ1p[MAX],*sRQ2p[MAX];

  QLA_Q_Complex *sCQ1p[MAX];

  QLA_D_Real sRD1[MAX] = { 61.88, -10.38,  73.59, -96.07,  50.32,
		92.37,   34.58, -21.10, -67.05, 104.01};

  QLA_D_Real sRD2[MAX] = {.2359, .6106, .5588, .6899, .5000,
		.9789, .4457, .8602, .4282, .7920};
  
  QLA_D_Real sRD3[MAX] = {-23.59, -56.32, -55.88, -11.55, 145.46, 
		 219.29, 71.47, -268.80, 42.82, 54.72};

  QLA_D_Real sCD1re[MAX] = { 92.37,   34.58, -21.10, -67.05, 104.01,
		      61.88, -10.38,  73.59, -96.07,  50.32};

  QLA_D_Real sCD2re[MAX] = { .9789, -.4457, .8602, .4282, .7920,
		     -.2359, -.6106, -.5588 -.6899, -.5000};
  
  QLA_D_Real sCD3re[MAX] = {219.29, 71.47, -268.80, 42.82, 54.72,
		     -23.59, -56.32, -55.88, -11.55, 145.46}; 

  QLA_D_Real sCD1im[MAX] = {-23.59, -61.06, -55.88 -68.99, -50.00,
		      92.37,   34.58, -21.10, -67.05, 104.01};

  QLA_D_Real sCD2im[MAX] = { .6188, -.1038,  .7359, -.9607,  .5032,
		     2.1929, .7147, -2.6880, .4282, .5472};
  
  QLA_D_Real sCD3im[MAX] = {-23.59, -56.32, -55.88, -11.55, 145.46, 
		      97.89, -44.57, 86.02, 42.82, 79.20};

  QLA_D_Complex sCD1[MAX],sCD2[MAX],sCD3[MAX];

  QLA_D_Real destRD[MAX],chkRD[MAX];

  QLA_D_Complex destCD[MAX],chkCD[MAX];

  QLA_D_Real *sRD1p[MAX],*sRD2p[MAX];

  QLA_D_Complex *sCD1p[MAX],*sCD2p[MAX];

  char name[64];

  int i;

  for(i = 0; i < MAX; i++){
    sRQ1p[i] = &sRQ1[sR2x[i]];
    sRD1p[i] = &sRD1[sR2x[i]];
    sRD2p[i] = &sRD2[sR3x[i]];

    sCQ1p[i] = &sCQ1[sC1x[i]];
    sCD1p[i] = &sCD1[sC1x[i]];
    sCD2p[i] = &sCD2[sC2x[i]];
  }

  for(i = 0; i < MAX; i++){
    QLA_c_eq_r_plus_ir(sCQ1[i],sCQ1re[i],sCQ1im[i]);
    QLA_c_eq_r_plus_ir(sCQ3[i],sCQ3re[i],sCQ3im[i]);
    QLA_c_eq_r_plus_ir(sCD1[i],sCD1re[i],sCD1im[i]);
    QLA_c_eq_r_plus_ir(sCD2[i],sCD2re[i],sCD2im[i]);
    QLA_c_eq_r_plus_ir(sCD3[i],sCD3re[i],sCD3im[i]);
  }
'

/* Precision conversion */
unary_spec(R,eq,R,_DQ,D,Q)
unary_spec(C,eq,C,_DQ,D,Q)

/* Reduction */
unaryglobalnorm2real(r,eq_norm2,R,_QD,Q,D)
unaryglobalnorm2(r,eq_norm2,C,_QD,Q,D)
binaryglobaldotreal(r,eq,R,dot,R,_QD,Q,D,D)
binaryglobaldot(c,eq,C,dot,C,_QD,Q,D,D)
binaryglobaldotreal(r,eq_re,C,dot,C,_QD,Q,D,D)
unarysumreal(r,eq_sum,R,_QD,Q,D)
unarysum(c,eq_sum,C,_QD,Q,D)

`
  return 0;
}
'

