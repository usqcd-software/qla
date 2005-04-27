/* QLA test code */
/* for indexed tensor routines.  Part 2 */
/* C Code automatically generated from test_tensor_idx.2.m4 */

include(protocol_idx.m4)

`
#include <qla.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "compare.h"

int test_tensor_idx2(){
'

  /* Define test data */

include(tensor_idx_defs.m4);

#if ( QLA_Precision != 'Q' )  /* Q precision is limited to assignments */

  /* Trace */

unary(R,eq_re_trace,M)
unary(R,eq_im_trace,M)
unary(C,eq_trace,M)
unary(M,eq_antiherm,M)
unary(M,eq_spintrace,P)

  /* Spin projection/ reconstruction */

unary_spproj(H,eq_spproj,D)
unary_sprecon(D,eq_sprecon,H)
unary_sprecon(D,peq_sprecon,H)

  /* Multiplication by real/complex constant */

alltensors3(`binaryconst',eq_r_times,R)
alltensors3(`binaryconst',peq_r_times,R)
alltensors3(`binaryconst',eqm_r_times,R)
alltensors3(`binaryconst',meq_r_times,R)
alltensors3(`binaryconst',eq_c_times,C)
alltensors3(`binaryconst',peq_c_times,C)
alltensors3(`binaryconst',eqm_c_times,C)
alltensors3(`binaryconst',meq_c_times,C)
alltensors2(`unarytimesi',eq_i)
alltensors2(`unarytimesi',peq_i)
alltensors2(`unarytimesi',eqm_i)
alltensors2(`unarytimesi',meq_i)

  /* Multiplication by gamma (left/right) */

unary_gammal(D,eq,D)
unary_gammal(P,eq,P)
unary_gammar(P,eq,P)

   /* Multiplcation - uniform types */

binary(H,eq,H,plus,H,sH1,sH2)
binary(D,eq,D,plus,D,sD1,sD2)
binary(V,eq,V,plus,V,sV1,sV2)
binary(P,eq,P,plus,P,sP1,sP2)
binary(M,eq,M,plus,M,sM1,sM2)
binary(H,eq,H,minus,H,sH1,sH2)
binary(D,eq,D,minus,D,sD1,sD2)
binary(V,eq,V,minus,V,sV1,sV2)
binary(P,eq,P,minus,P,sP1,sP2)
binary(M,eq,M,minus,M,sM1,sM2)
binary(P,eq,P,times,P,sP1,sP2)
binary(P,peq,P,times,P,sP1,sP2)
binary(M,peq,M,times,M,sM1,sM2)
binary(P,eqm,P,times,P,sP1,sP2)
binary(M,eqm,M,times,M,sM1,sM2)
binary(P,meq,P,times,P,sP1,sP2)
binary(M,meq,M,times,M,sM1,sM2)

  /* Outer product */

binary(M,eq,V,times,Va,sV1,sV2)
binary(M,peq,V,times,Va,sV1,sV2)
binary(M,eqm,V,times,Va,sV1,sV2)
binary(M,meq,V,times,Va,sV1,sV2)

  /* Local dot product */

binary(C,eq,H,dot,H,sH1,sH2)
binary(C,eq,D,dot,D,sD1,sD2)
binary(C,eq,V,dot,V,sV1,sV2)
binary(C,eq,P,dot,P,sP1,sP2)
binary(C,eq,M,dot,M,sM1,sM2)

binary(R,eq_re,H,dot,H,sH1,sH2)
binary(R,eq_re,D,dot,D,sD1,sD2)
binary(R,eq_re,V,dot,V,sV1,sV2)
binary(R,eq_re,P,dot,P,sP1,sP2)
binary(R,eq_re,M,dot,M,sM1,sM2)

#endif /* QLA_Precision != Q */

`
  return 0;
}
'
