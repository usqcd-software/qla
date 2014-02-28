/* QLA test code */
/* for indexed tensor routines.  Part 4 */
/* C Code automatically generated from test_tensor_idx.4.m4 */

include(protocol_idx.m4)

`
#include <qla.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "compare.h"

  /* Define test data */

#define QLA_DF_r_eq_I_dot_I QLA_D_r_eq_I_dot_I
#define QLA_QD_r_eq_I_dot_I QLA_D_r_eq_I_dot_I

#define QLA(x) QLA_ ## x
#define QLA_DF(x) QLA_DF_ ## x
#define QLA_QD(x) QLA_QD_ ## x

'
#if ( QLA_Precision != 'Q' )  /* Q precision is limited to assignments */
#if (QLA_Precision == 1) || (QLA_Precision == 'F')
`
#define QLA_PR(x) QLA_DF_ ## x
  QLA_D_Real destrP, chkrP;
  QLA_D_Complex destcP, chkcP;
#else
#define QLA_PR(x) QLA_QD_ ## x
  QLA_Q_Real destrP, chkrP;
  QLA_Q_Complex destcP, chkcP;
#endif
static  int nc = QLA_Nc;
static  int ns = QLA_Ns;
static  int ic,jc,is,js;

static  QLA_Real sR4       = -6.35;

  /*QLA_Q_Real                chkRQ[MAX];*/
  /*QLA_Q_Complex             chkCQ[MAX];*/
  QLA_Q_ColorMatrix         chkMQ[MAX];
  QLA_Q_HalfFermion         chkHQ[MAX];
  QLA_Q_DiracFermion        chkDQ[MAX];
  QLA_Q_ColorVector         chkVQ[MAX];
  QLA_Q_DiracPropagator     chkPQ[MAX];

  QLA_Q_Real                chkrQ;
  /*QLA_Q_Complex             chkcQ;*/
  QLA_Q_ColorMatrix         chkmQ;
  QLA_Q_HalfFermion         chkhQ;
  QLA_Q_DiracFermion        chkdQ;
  QLA_Q_ColorVector         chkvQ;
  QLA_Q_DiracPropagator     chkpQ;

  QLA_Real                 destr,chkr;
  QLA_Complex              destc,chkc;
  QLA_ColorMatrix          destm,chkm;
  QLA_HalfFermion          desth,chkh;
  QLA_DiracFermion         destd,chkd;
  QLA_ColorVector          destv,chkv;
  QLA_DiracPropagator      destp,chkp;

#if 0
  QLA_Q_Real               destrQ;
  QLA_Q_Complex            destcQ;
#endif

#endif

  int dHx[MAX]  = {9,2,6,1,4,5,7,0,8,3};
  int dDx[MAX]  = {4,1,2,9,7,5,3,6,0,8};
  int dVx[MAX]  = {4,2,5,1,6,0,3,8,9,7};
  int dPx[MAX]  = {9,7,3,2,5,8,6,4,0,1};
  int dMx[MAX]  = {1,2,9,7,3,0,4,6,5,8};
'
include(tensor_idx_defs.m4)
#if ( QLA_Precision != 'Q' )  /* Q precision is limited to assignments */

  /* Ternary operations */
void do_to(FILE *fp) {
ternaryconst(H,eq_r_times,R,H,plus,H)
ternaryconst(H,eq_r_times,R,H,minus,H)
ternaryconst(D,eq_r_times,R,D,plus,D)
ternaryconst(D,eq_r_times,R,D,minus,D)
ternaryconst(V,eq_r_times,R,V,plus,V)
ternaryconst(V,eq_r_times,R,V,minus,V)
ternaryconst(P,eq_r_times,R,P,plus,P)
ternaryconst(P,eq_r_times,R,P,minus,P)
ternaryconst(M,eq_r_times,R,M,plus,M)
ternaryconst(M,eq_r_times,R,M,minus,M)

ternaryconst(H,eq_c_times,C,H,plus,H)
ternaryconst(H,eq_c_times,C,H,minus,H)
ternaryconst(D,eq_c_times,C,D,plus,D)
ternaryconst(D,eq_c_times,C,D,minus,D)
ternaryconst(V,eq_c_times,C,V,plus,V)
ternaryconst(V,eq_c_times,C,V,minus,V)
ternaryconst(P,eq_c_times,C,P,plus,P)
ternaryconst(P,eq_c_times,C,P,minus,P)
ternaryconst(M,eq_c_times,C,M,plus,M)
ternaryconst(M,eq_c_times,C,M,minus,M)
}

#endif
`
int test_tensor_idx4(FILE *fp, int ealign){
  initialize_variables(fp, ealign);
'
#if ( QLA_Precision != 'Q' )  /* Q precision is limited to assignments */

  /* Ternary operations */
  do_to(fp);

  /* Copymask */

binary(H,eq,H,mask,I,sH1,zI1)
binary(D,eq,D,mask,I,sD1,zI1)
binary(V,eq,V,mask,I,sV1,zI1)
binary(P,eq,P,mask,I,sP1,zI1)
binary(M,eq,M,mask,I,sM1,zI1)

  /* Reductions */

unaryglobalnorm2(r,eq_norm2,H,,,)
unaryglobalnorm2(r,eq_norm2,D,,,)
unaryglobalnorm2(r,eq_norm2,V,,,)
unaryglobalnorm2(r,eq_norm2,P,,,)
unaryglobalnorm2(r,eq_norm2,M,,,)

binaryglobaldot(c,eq,H,dot,H,,,)
binaryglobaldot(c,eq,D,dot,D,,,)
binaryglobaldot(c,eq,V,dot,V,,,)
binaryglobaldot(c,eq,P,dot,P,,,)
binaryglobaldot(c,eq,M,dot,M,,,)

binaryglobaldotreal(r,eq_re,H,dot,H,,,)
binaryglobaldotreal(r,eq_re,D,dot,D,,,)
binaryglobaldotreal(r,eq_re,V,dot,V,,,)
binaryglobaldotreal(r,eq_re,P,dot,P,,,)
binaryglobaldotreal(r,eq_re,M,dot,M,,,)

unarysum(h,eq_sum,H,,,)
unarysum(d,eq_sum,D,,,)
unarysum(v,eq_sum,V,,,)
unarysum(p,eq_sum,P,,,)
unarysum(m,eq_sum,M,,,)

#endif /* QLA_Precision != Q */

  /* Fills */

unaryconstzero(H,eq_zero)
unaryconstzero(D,eq_zero)
unaryconstzero(V,eq_zero)
unaryconstzero(P,eq_zero)
unaryconstzero(M,eq_zero)

#if ( QLA_Precision != 'Q' )  /* Q precision is limited to assignments */

unaryconst(H,h)
unaryconst(D,d)
unaryconst(V,v)
unaryconst(P,p)
unaryconst(M,m)

unarydiagconst(M)

#endif /* QLA_Precision != Q */
`
  return 0;
}
'
