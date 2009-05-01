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

  /* Define test data */
'
#if ( QLA_Precision != 'Q' )  /* Q precision is limited to assignments */
static  int mu,sign;

static  QLA_Real sR4       = -6.35;
#endif

include(tensor_idx_defs.m4);

#if ( QLA_Precision != 'Q' )  /* Q precision is limited to assignments */

  /* Trace */
void do_tr(FILE *fp) {
unary(R,eq_re_trace,M)
unary(R,eq_im_trace,M)
unary(C,eq_trace,M)
unary(M,eq_antiherm,M)
unary(M,eq_spintrace,P)
}

  /* Spin projection/ reconstruction */
void do_spr(FILE *fp) {
alleqops(`unary_spproj(H,',`_spproj,D)')
alleqops(`unary_spproj(D,',`_spproj,D)')
alleqops(`unary_sprecon(D,',`_sprecon,H)')
}

  /* Spin projection/ reconstruction with matrix multiply */
void do_sprmult(FILE *fp) {
alleqops(`binary_spproj(H,',`_spproj,M,,times,D)')
alleqops(`binary_spproj(H,',`_spproj,M,a,times,D)')
alleqops(`binary_spproj(D,',`_spproj,M,,times,D)')
alleqops(`binary_spproj(D,',`_spproj,M,a,times,D)')
alleqops(`binary_spproj(D,',`_sprecon,M,,times,H)')
alleqops(`binary_spproj(D,',`_sprecon,M,a,times,H)')
}

  /* Multiplication by real/complex constant */
void do_mrc(FILE *fp) {
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
}

  /* Multiplication by gamma (left/right) */
void do_mg(FILE *fp) {
unary_gammal(D,eq,D)
unary_gammal(P,eq,P)
unary_gammar(P,eq,P)
}

  /* Multiplcation - uniform types */
void do_mut(FILE *fp) {
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
}

  /* Outer product */
void do_op(FILE *fp) {
binary(M,eq,V,times,Va,sV1,sV2)
binary(M,peq,V,times,Va,sV1,sV2)
binary(M,eqm,V,times,Va,sV1,sV2)
binary(M,meq,V,times,Va,sV1,sV2)
}

  /* Local dot product */
void do_ldp(FILE *fp) {
alleqops(`binary(C,',`,H,dot,H,sH1,sH2)')
alleqops(`binary(C,',`,D,dot,D,sD1,sD2)')
alleqops(`binary(C,',`,V,dot,V,sV1,sV2)')
alleqops(`binary(C,',`,P,dot,P,sP1,sP2)')
alleqops(`binary(C,',`,M,dot,M,sM1,sM2)')

alleqops(`binary(R,',`_re,H,dot,H,sH1,sH2)')
alleqops(`binary(R,',`_re,D,dot,D,sD1,sD2)')
alleqops(`binary(R,',`_re,V,dot,V,sV1,sV2)')
alleqops(`binary(R,',`_re,P,dot,P,sP1,sP2)')
alleqops(`binary(R,',`_re,M,dot,M,sM1,sM2)')
}

#endif
`
int test_tensor_idx2(FILE *fp){
  initialize_variables(fp);
'
#if ( QLA_Precision != 'Q' )  /* Q precision is limited to assignments */

  /* Trace */
  do_tr(fp);

  /* Spin projection/ reconstruction */
  do_spr(fp);

  /* Spin projection/ reconstruction with matrix multiply */
  do_sprmult(fp);

  /* Multiplication by real/complex constant */
  do_mrc(fp);

  /* Multiplication by gamma (left/right) */
  do_mg(fp);

  /* Multiplcation - uniform types */
  do_mut(fp);

  /* Outer product */
  do_op(fp);

  /* Local dot product */
  do_ldp(fp);

#endif /* QLA_Precision != Q */

`
  return 0;
}
'
