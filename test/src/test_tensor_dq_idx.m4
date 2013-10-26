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
#elif QLA_Nc == 1
#include <qla_d1.h>
#include <qla_f1.h>
#else
#include <qla_dn.h>
#include <qla_fn.h>
#endif
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "compare.h"

int main(int argc, char * argv[]){
'
#define QLA_PRF(x) QLA_DF_ ## x
#define QLA_PRD(x) QLA_QD_ ## x
`
  QLA_Q_Real                destrQ,chkrQ;
  QLA_Q_Complex             destcQ,chkcQ;
  QLA_Q_ColorMatrix         destmQ,chkmQ;
  QLA_Q_HalfFermion         desthQ,chkhQ;
  QLA_Q_DiracFermion        destdQ,chkdQ;
  QLA_Q_ColorVector         destvQ,chkvQ;
  QLA_Q_DiracPropagator     destpQ,chkpQ;

  QLA_Q_ColorMatrix         sMQ1[MAX]/*,sMQ2[MAX],sMQ3[MAX]*/;
  QLA_Q_HalfFermion         sHQ1[MAX]/*,sHQ2[MAX],sHQ3[MAX]*/;
  QLA_Q_DiracFermion        sDQ1[MAX]/*,sDQ2[MAX],sDQ3[MAX]*/;
  QLA_Q_ColorVector         sVQ1[MAX]/*,sVQ2[MAX],sVQ3[MAX]*/;
  QLA_Q_DiracPropagator     sPQ1[MAX]/*,sPQ2[MAX],sPQ3[MAX]*/;

  QLA_Q_ColorMatrix         /*destMQ[MAX],*/chkMQ[MAX];
  QLA_Q_HalfFermion         /*destHQ[MAX],*/chkHQ[MAX];
  QLA_Q_DiracFermion        /*destDQ[MAX],*/chkDQ[MAX];
  QLA_Q_ColorVector         /*destVQ[MAX],*/chkVQ[MAX];
  QLA_Q_DiracPropagator     /*destPQ[MAX],*/chkPQ[MAX];

  QLA_D_ColorMatrix         sMD1[MAX],sMD2[MAX],sMD3[MAX];
  QLA_D_HalfFermion         sHD1[MAX],sHD2[MAX],sHD3[MAX];
  QLA_D_DiracFermion        sDD1[MAX],sDD2[MAX],sDD3[MAX];
  QLA_D_ColorVector         sVD1[MAX],sVD2[MAX],sVD3[MAX];
  QLA_D_DiracPropagator     sPD1[MAX],sPD2[MAX],sPD3[MAX];

  QLA_D_ColorMatrix         destMD[MAX],chkMD[MAX];
  QLA_D_HalfFermion         destHD[MAX],chkHD[MAX];
  QLA_D_DiracFermion        destDD[MAX],chkDD[MAX];
  QLA_D_ColorVector         destVD[MAX],chkVD[MAX];
  QLA_D_DiracPropagator     destPD[MAX],chkPD[MAX];

  QLA_RandomState sS1[MAX];

  QLA_Int sI3[MAX] = { 92,  34, -21, -67, 104, 61, -10,  73, -96,  50};

  QLA_Int sI4      = 5001;

  QLA_Q_Real sRQ1 =  0.17320508075688772;
  QLA_Q_Real sRQ2 =  0.28723479823477934;

  /*int dMx[MAX]  = {9,1,8,5,6,0,3,7,2,4};*/
  int sM1x[MAX] = {0,2,9,7,6,1,4,5,8,3};
  int sM2x[MAX] = {3,6,4,0,1,2,9,7,5,8};

  /*int dHx[MAX]  = {9,2,6,1,4,5,7,0,8,3};*/
  int sH1x[MAX] = {4,6,1,2,9,7,0,3,5,8};
  int sH2x[MAX] = {8,1,6,0,3,7,5,9,2,4};

  /*int dDx[MAX]  = {4,1,2,9,7,5,3,6,0,8};*/
  int sD1x[MAX] = {8,6,0,3,7,2,9,1,5,4};
  int sD2x[MAX] = {9,6,1,4,5,8,0,2,7,3};

  /*int dVx[MAX]  = {4,2,5,1,6,0,3,8,9,7};*/
  int sV1x[MAX] = {6,4,0,2,1,9,7,3,5,8};
  int sV2x[MAX] = {1,9,3,6,2,4,0,8,7,5};

  /*int dPx[MAX]  = {9,7,3,2,5,8,6,4,0,1};*/
  int sP1x[MAX] = {3,7,9,0,2,4,1,8,5,6};
  int sP2x[MAX] = {2,9,5,6,7,8,1,0,3,4};

  QLA_Q_ColorMatrix         *sMQ1p[MAX]/*, *sMQ2p[MAX], *sMQ3p[MAX]*/;
  QLA_Q_HalfFermion         *sHQ1p[MAX]/*, *sHQ2p[MAX], *sHQ3p[MAX]*/;
  QLA_Q_DiracFermion        *sDQ1p[MAX]/*, *sDQ2p[MAX], *sDQ3p[MAX]*/;
  QLA_Q_ColorVector         *sVQ1p[MAX]/*, *sVQ2p[MAX], *sVQ3p[MAX]*/;
  QLA_Q_DiracPropagator     *sPQ1p[MAX]/*, *sPQ2p[MAX], *sPQ3p[MAX]*/;

  QLA_D_ColorMatrix         *sMD1p[MAX], *sMD2p[MAX]/*, *sMD3p[MAX]*/;
  QLA_D_HalfFermion         *sHD1p[MAX], *sHD2p[MAX]/*, *sHD3p[MAX]*/;
  QLA_D_DiracFermion        *sDD1p[MAX], *sDD2p[MAX]/*, *sDD3p[MAX]*/;
  QLA_D_ColorVector         *sVD1p[MAX], *sVD2p[MAX]/*, *sVD3p[MAX]*/;
  QLA_D_DiracPropagator     *sPD1p[MAX], *sPD2p[MAX]/*, *sPD3p[MAX]*/;

  int i;
  int ic,jc,is,js;

  int nc = QLA_Nc;
  int ns = QLA_Ns;

  char name[64];
  FILE *fp;

  char *test_program_name= basename(argv[0]); 
  test_program_name = strcat(test_program_name, ".result");
  if (NULL == (fp = fopen(test_program_name,"w"))) {
    fprintf(stderr, "Error in report function - cannot create \"%s\"\n", test_program_name);
    exit(-1);
  }

  for(i = 0; i < MAX; i++){

    sHQ1p[i] = &sHQ1[sH1x[i]];
    //sHQ2p[i] = &sHQ2[sH2x[i]];
    //sHQ3p[i] = &sHQ3[sH2x[i]];

    sDQ1p[i] = &sDQ1[sD1x[i]];
    //sDQ2p[i] = &sDQ2[sD2x[i]];
    //sDQ3p[i] = &sDQ3[sD2x[i]];

    sVQ1p[i] = &sVQ1[sV1x[i]];
    //sVQ2p[i] = &sVQ2[sV2x[i]];
    //sVQ3p[i] = &sVQ3[sV2x[i]];

    sPQ1p[i] = &sPQ1[sP1x[i]];
    //sPQ2p[i] = &sPQ2[sP2x[i]];
    //sPQ3p[i] = &sPQ3[sP2x[i]];

    sMQ1p[i] = &sMQ1[sM1x[i]];
    //sMQ2p[i] = &sMQ2[sM2x[i]];
    //sMQ3p[i] = &sMQ3[sM2x[i]];

    sHD1p[i] = &sHD1[sH1x[i]];
    sHD2p[i] = &sHD2[sH2x[i]];
    //sHD3p[i] = &sHD3[sH2x[i]];

    sDD1p[i] = &sDD1[sD1x[i]];
    sDD2p[i] = &sDD2[sD2x[i]];
    //sDD3p[i] = &sDD3[sD2x[i]];

    sVD1p[i] = &sVD1[sV1x[i]];
    sVD2p[i] = &sVD2[sV2x[i]];
    //sVD3p[i] = &sVD3[sV2x[i]];

    sPD1p[i] = &sPD1[sP1x[i]];
    sPD2p[i] = &sPD2[sP2x[i]];
    //sPD3p[i] = &sPD3[sP2x[i]];

    sMD1p[i] = &sMD1[sM1x[i]];
    sMD2p[i] = &sMD2[sM2x[i]];
    //sMD3p[i] = &sMD3[sM2x[i]];

  }

  /* Create random test values */
  QLA_S_veq_seed_i_I(sS1,sI4,sI3,MAX);

  for(i = 0; i < MAX; i++){

    /* Long double precision */
'
    makeGaussianQarray(H,sHQ1);
    /*makeGaussianQarray(H,sHQ2);*/
    /*makeGaussianQarray(H,sHQ3);*/

    makeGaussianQarray(D,sDQ1);
    /*makeGaussianQarray(D,sDQ2);*/
    /*makeGaussianQarray(D,sDQ3);*/

    makeGaussianQarray(V,sVQ1);
    /*makeGaussianQarray(V,sVQ2);*/
    /*makeGaussianQarray(V,sVQ3);*/

    makeGaussianQarray(P,sPQ1);
    /*makeGaussianQarray(P,sPQ2);*/
    /*makeGaussianQarray(P,sPQ3);*/

    makeGaussianQarray(M,sMQ1);
    /*makeGaussianQarray(M,sMQ2);*/
    /*makeGaussianQarray(M,sMQ3);*/
`
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

  }
'

/* Precision conversion */

unary_spec(H,eq,H,_DQ,D,Q)
unary_spec(D,eq,D,_DQ,D,Q)
unary_spec(V,eq,V,_DQ,D,Q)
unary_spec(P,eq,P,_DQ,D,Q)
unary_spec(M,eq,M,_DQ,D,Q)

/* Reductions */

unaryglobalnorm2(r,eq_norm2,H,_QD,Q,D)
unaryglobalnorm2(r,eq_norm2,D,_QD,Q,D)
unaryglobalnorm2(r,eq_norm2,V,_QD,Q,D)
unaryglobalnorm2(r,eq_norm2,P,_QD,Q,D)
unaryglobalnorm2(r,eq_norm2,M,_QD,Q,D)

binaryglobaldot(c,eq,H,dot,H,_QD,Q,D,D)
binaryglobaldot(c,eq,D,dot,D,_QD,Q,D,D)
binaryglobaldot(c,eq,V,dot,V,_QD,Q,D,D)
binaryglobaldot(c,eq,P,dot,P,_QD,Q,D,D)
binaryglobaldot(c,eq,M,dot,M,_QD,Q,D,D)

binaryglobaldotreal(r,eq_re,H,dot,H,_QD,Q,D,D)
binaryglobaldotreal(r,eq_re,D,dot,D,_QD,Q,D,D)
binaryglobaldotreal(r,eq_re,V,dot,V,_QD,Q,D,D)
binaryglobaldotreal(r,eq_re,P,dot,P,_QD,Q,D,D)
binaryglobaldotreal(r,eq_re,M,dot,M,_QD,Q,D,D)

unarysum(h,eq_sum,H,_QD,Q,D)
unarysum(d,eq_sum,D,_QD,Q,D)
unarysum(v,eq_sum,V,_QD,Q,D)
unarysum(p,eq_sum,P,_QD,Q,D)
unarysum(m,eq_sum,M,_QD,Q,D)

`
  return 0;
}
'
