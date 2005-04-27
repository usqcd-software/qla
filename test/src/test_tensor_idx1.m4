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

int test_tensor_idx1(){
'
  /* Define test data */

include(tensor_idx_defs.m4);

#if ( QLA_Precision != 'Q' )  /* Q precision is limited to assignments */

  /* Matrix adjoint */

unarya(P,eq,P)
unarya(M,eq,M)
unarya(P,peq,P)
unarya(M,peq,M)
unarya(P,eqm,P)
unarya(M,eqm,M)
unarya(P,meq,P)
unarya(M,meq,M)

  /* Transpose */

unary(P,eq_transpose,P)
unary(M,eq_transpose,M)
unary(P,peq_transpose,P)
unary(M,peq_transpose,M)
unary(P,meq_transpose,P)
unary(M,meq_transpose,M)
unary(P,eqm_transpose,P)
unary(M,eqm_transpose,M)

#endif /* QLA_Precision != Q */

  /* Local squared norm */

unary(R,eq_norm2,H);
unary(R,eq_norm2,D);
unary(R,eq_norm2,V);
unary(R,eq_norm2,P);
unary(R,eq_norm2,M);

#if ( QLA_Precision != 'Q' )  /* Q precision is limited to assignments */

  /* Complex conjugate */

alltensors2(`unary',eq_conj);
alltensors2(`unary',peq_conj);
alltensors2(`unary',eqm_conj);
alltensors2(`unary',meq_conj);


  /* Extracting elements */

unary_get_elem(C,eq_elem,H)
unary_get_elem(C,eq_elem,D)
unary_get_elem(C,eq_elem,V)
unary_get_elem(C,eq_elem,P)
unary_get_elem(C,eq_elem,M)

  /* Inserting elements */

unary_set_elem(H,eq_elem,C)
unary_set_elem(D,eq_elem,C)
unary_set_elem(V,eq_elem,C)
unary_set_elem(P,eq_elem,C)
unary_set_elem(M,eq_elem,C)

  /* Extracting color vectors */

unary_get_colorvec(V,eq_colorvec,H)
unary_get_colorvec(V,eq_colorvec,D)
unary_get_colorvec(V,eq_colorvec,P)
unary_get_colorvec(V,eq_colorvec,M)

  /* Inserting color vectors */

unary_set_colorvec(H,eq_colorvec,V)
unary_set_colorvec(D,eq_colorvec,V)
unary_set_colorvec(P,eq_colorvec,V)
unary_set_colorvec(M,eq_colorvec,V)

  /* Extracting and inserting Dirac vectors */

unary_get_diracvec(D,eq_diracvec,P)
unary_set_diracvec(P,eq_diracvec,D)

#endif /* QLA_Precision != Q */
`
  return 0;
}
'
