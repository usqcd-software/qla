rem(`
     Variable definitions
     (Include file for test_tensor_idx.[1-4].m4)
')
  int nc = QLA_Nc;
  int ns = 4;
  int ic,jc,is,js;
  int mu,sign;

  QLA_Real                  sR1[MAX],sR2[MAX],sR3[MAX];
  QLA_Complex               sC1[MAX],sC2[MAX],sC3[MAX];
  QLA_ColorMatrix           sM1[MAX],sM2[MAX],sM3[MAX];
  QLA_HalfFermion           sH1[MAX],sH2[MAX],sH3[MAX];
  QLA_DiracFermion          sD1[MAX],sD2[MAX],sD3[MAX];
  QLA_ColorVector           sV1[MAX],sV2[MAX],sV3[MAX];
  QLA_DiracPropagator       sP1[MAX],sP2[MAX],sP3[MAX];

  QLA_RandomState           sS1[MAX];

  QLA_Real                  destR[MAX],chkR[MAX];
  QLA_Complex               destC[MAX],chkC[MAX];
  QLA_ColorMatrix           destM[MAX],chkM[MAX];
  QLA_HalfFermion           destH[MAX],chkH[MAX];
  QLA_DiracFermion          destD[MAX],chkD[MAX];
  QLA_ColorVector           destV[MAX],chkV[MAX];
  QLA_DiracPropagator       destP[MAX],chkP[MAX];
			    
  QLA_Q_Real                chkRQ[MAX];
  QLA_Q_Complex             chkCQ[MAX];
  QLA_Q_ColorMatrix         chkMQ[MAX];
  QLA_Q_HalfFermion         chkHQ[MAX];
  QLA_Q_DiracFermion        chkDQ[MAX];
  QLA_Q_ColorVector         chkVQ[MAX];
  QLA_Q_DiracPropagator     chkPQ[MAX];
			    
  QLA_D_Real                chkRD[MAX];
  QLA_D_Complex             chkCD[MAX];
  QLA_D_ColorMatrix         chkMD[MAX];
  QLA_D_HalfFermion         chkHD[MAX];
  QLA_D_DiracFermion        chkDD[MAX];
  QLA_D_ColorVector         chkVD[MAX];
  QLA_D_DiracPropagator     chkPD[MAX];
			    
  QLA_Q_Real                chkrQ;
  QLA_Q_Complex             chkcQ;
  QLA_Q_ColorMatrix         chkmQ;
  QLA_Q_HalfFermion         chkhQ;
  QLA_Q_DiracFermion        chkdQ;
  QLA_Q_ColorVector         chkvQ;
  QLA_Q_DiracPropagator     chkpQ;

  QLA_D_Real                chkrD;
  QLA_D_Complex             chkcD;
  QLA_D_ColorMatrix         chkmD;
  QLA_D_HalfFermion         chkhD;
  QLA_D_DiracFermion        chkdD;
  QLA_D_ColorVector         chkvD;
  QLA_D_DiracPropagator     chkpD;

  QLA_Real sR4       = -6.35;

  QLA_Real sC4re      = 831.2;
  QLA_Real sC4im      = -701.;

  QLA_Complex sC4;

  QLA_ColorMatrix sM4;
  QLA_HalfFermion sH4;
  QLA_DiracFermion sD4;
  QLA_ColorVector sV4;
  QLA_DiracPropagator sP4;

  int nI1[MAX] = { 3, 12, 7, 1, 5, 8, 3, 2, 1, 5};
  int zI1[MAX] = { 3, 0, 7, 1, 0, 0, 3, 2, 1, 0};

  QLA_Int sI1[MAX] = { 61, -10,  73, -96,  50,
		   92,  34, -21, -67, 104};

  QLA_Int sI3[MAX] = { 92,  34, -21, -67, 104,
		   61, -10,  73, -96,  50};

  QLA_Int sI4      = 5001;

  int dRx[MAX]  = {8,5,6,7,1,2,9,0,3,4};
  int sR1x[MAX] = {3,0,1,8,2,4,5,9,7,6};
  int sR2x[MAX] = {4,9,0,2,1,3,7,8,5,6};
  int sR3x[MAX] = {8,3,2,5,6,9,7,4,0,1};

  int dCx[MAX]  = {8,3,2,5,6,9,7,4,0,1};
  int sC1x[MAX] = {8,5,6,7,1,2,9,0,3,4};
  int sC2x[MAX] = {4,9,0,2,1,3,7,8,5,6};

  int sI1x[MAX] = {4,9,0,2,1,3,7,8,5,6};
  int sI3x[MAX] = {3,0,1,8,2,4,5,9,7,6};

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

  int dMx[MAX]  = {1,2,9,7,3,0,4,6,5,8};
  int sM1x[MAX] = {6,0,3,7,9,5,8,1,2,4};
  int sM2x[MAX] = {6,1,4,5,0,7,9,2,8,3};

  int zI1x[MAX] = {8,5,6,7,1,2,9,0,3,4};

  int sS1x[MAX] = {1,3,8,5,9,4,7,6,0,2};

  QLA_Int *nI1p[MAX], *zI1p[MAX];
  QLA_Int                 *sI1p[MAX];
  QLA_Real                *sR1p[MAX], *sR2p[MAX], *sR3p[MAX];
  QLA_Complex             *sC1p[MAX], *sC2p[MAX], *sC3p[MAX], *chkCp[MAX];
  QLA_ColorMatrix         *sM1p[MAX], *sM2p[MAX], *sM3p[MAX];
  QLA_HalfFermion         *sH1p[MAX], *sH2p[MAX], *sH3p[MAX];
  QLA_DiracFermion        *sD1p[MAX], *sD2p[MAX], *sD3p[MAX], *chkDp[MAX];
  QLA_ColorVector    *sV1p[MAX], *sV2p[MAX], *sV3p[MAX], *chkVp[MAX];
  QLA_DiracPropagator     *sP1p[MAX], *sP2p[MAX], *sP3p[MAX];
  QLA_RandomState         *sS1p[MAX];
  
  int i;
  QLA_Real                 destr,chkr;
  QLA_Complex              destc,chkc;
  QLA_ColorMatrix          destm,chkm;
  QLA_HalfFermion          desth,chkh;
  QLA_DiracFermion         destd,chkd;
  QLA_ColorVector     destv,chkv;
  QLA_DiracPropagator      destp,chkp;
 
  QLA_Q_Real               destrQ;
  QLA_Q_Complex            destcQ;

  char name[64];

  for(i = 0; i < MAX; i++){
    sR1p[i] = &sR1[sR2x[i]];
    sR2p[i] = &sR2[sR3x[i]];
    sR3p[i] = &sR3[sR1x[i]];

    sC1p[i] = &sC1[sC1x[i]];
    sC2p[i] = &sC2[sC2x[i]];
    sC3p[i] = &sC3[sC2x[i]];
    chkCp[i] = &chkC[sC1x[i]];

    sH1p[i] = &sH1[sH1x[i]];
    sH2p[i] = &sH2[sH2x[i]];
    sH3p[i] = &sH3[sH2x[i]];

    sD1p[i] = &sD1[sD1x[i]];
    sD2p[i] = &sD2[sD2x[i]];
    sD3p[i] = &sD3[sD2x[i]];
    chkDp[i] = &chkD[sD1x[i]];

    sV1p[i] = &sV1[sV1x[i]];
    sV2p[i] = &sV2[sV2x[i]];
    sV3p[i] = &sV3[sV2x[i]];
    chkVp[i] = &chkV[sV1x[i]];

    sP1p[i] = &sP1[sP1x[i]];
    sP2p[i] = &sP2[sP2x[i]];
    sP3p[i] = &sP3[sP2x[i]];

    sM1p[i] = &sM1[sM1x[i]];
    sM2p[i] = &sM2[sM2x[i]];
    sM3p[i] = &sM3[sM2x[i]];

    sI1p[i] = &sI1[sI1x[i]];

    nI1p[i] = &nI1[sR3x[i]];
    zI1p[i] = &zI1[sR2x[i]];

    sS1p[i] = &sS1[sS1x[i]];
  }

  QLA_c_eq_r_plus_ir(sC4,sC4re,sC4im);
  /* Preliminary check of vector copy */

alltensors(`chkVectorCopy')
alltensors2(`unary',eq);
alltensors2(`unary',peq);
alltensors2(`unary',eqm);
alltensors2(`unary',meq);

  /* Preliminary check of random number generator */

unaryrand(H,eq_gaussian)
unaryrand(D,eq_gaussian)
unaryrand(V,eq_gaussian)
unaryrand(P,eq_gaussian)
unaryrand(M,eq_gaussian)

`
  /* Create random test values */
  QLA_S_veq_seed_i_I(sS1,sI4,sI3,MAX);

  QLA_H_eq_gaussian_S(&sH4,sS1);
  QLA_D_eq_gaussian_S(&sD4,sS1);
  QLA_V_eq_gaussian_S(&sV4,sS1);
  QLA_P_eq_gaussian_S(&sP4,sS1);
  QLA_M_eq_gaussian_S(&sM4,sS1);

  for(i = 0; i < MAX; i++){

    QLA_H_veq_gaussian_S(sH1,sS1,MAX);
    QLA_H_veq_gaussian_S(sH2,sS1,MAX);
    QLA_H_veq_gaussian_S(sH3,sS1,MAX);
			  	 
    QLA_D_veq_gaussian_S(sD1,sS1,MAX);
    QLA_D_veq_gaussian_S(sD2,sS1,MAX);
    QLA_D_veq_gaussian_S(sD3,sS1,MAX);
			  	 
    QLA_V_veq_gaussian_S(sV1,sS1,MAX);
    QLA_V_veq_gaussian_S(sV2,sS1,MAX);
    QLA_V_veq_gaussian_S(sV3,sS1,MAX);
			  	 
    QLA_P_veq_gaussian_S(sP1,sS1,MAX);
    QLA_P_veq_gaussian_S(sP2,sS1,MAX);
    QLA_P_veq_gaussian_S(sP3,sS1,MAX);
			  	 
    QLA_M_veq_gaussian_S(sM1,sS1,MAX);
    QLA_M_veq_gaussian_S(sM2,sS1,MAX);
    QLA_M_veq_gaussian_S(sM3,sS1,MAX);
  }
'


