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

int test_tensor_idx4(){
'
  /* Define test data */

include(tensor_idx_defs.m4);

#if ( QLA_Precision != 'Q' )  /* Q precision is limited to assignments */

  /* Ternary operations */

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

unaryconst(H,eq_h)
unaryconst(D,eq_d)
unaryconst(V,eq_v)
unaryconst(P,eq_p)
unaryconst(M,eq_m)

unarydiagconst(M,eq_c)

#endif /* QLA_Precision != Q */

`
  return 0;
}
'
