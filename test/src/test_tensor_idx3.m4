/* QLA test code */
/* for indexed tensor routines.  Part 3 */
/* C Code automatically generated from test_tensor_idx.3.m4 */

include(protocol_idx.m4)

`
#include <qla.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "compare.h"

int test_tensor_idx3(){
'
  /* Define test data */

include(tensor_idx_defs.m4);

#if ( QLA_Precision != 'Q' )  /* Q precision is limited to assignments */

  /* Right multiply by color matrix */

binary(H,eq,M,times,H,sM1,sH2)
binary(D,eq,M,times,D,sM1,sD2)
binary(V,eq,M,times,V,sM1,sV2)
binary(P,eq,M,times,P,sM1,sP2)
binary(H,peq,M,times,H,sM1,sH2)
binary(D,peq,M,times,D,sM1,sD2)
binary(V,peq,M,times,V,sM1,sV2)
binary(P,peq,M,times,P,sM1,sP2)
binary(H,eqm,M,times,H,sM1,sH2)
binary(D,eqm,M,times,D,sM1,sD2)
binary(V,eqm,M,times,V,sM1,sV2)
binary(P,eqm,M,times,P,sM1,sP2)
binary(H,meq,M,times,H,sM1,sH2)
binary(D,meq,M,times,D,sM1,sD2)
binary(V,meq,M,times,V,sM1,sV2)
binary(P,meq,M,times,P,sM1,sP2)

  /* Adjoint of color matrix times adjoint of color matrix */

binary(M,eq,Ma,times,Ma,sM1,sM2)
binary(M,peq,Ma,times,Ma,sM1,sM2)
binary(M,eqm,Ma,times,Ma,sM1,sM2)
binary(M,meq,Ma,times,Ma,sM1,sM2)

  /* Left multiply by adjoint of color matrix */

binary(H,eq,Ma,times,H,sM1,sH2)
binary(D,eq,Ma,times,D,sM1,sD2)
binary(V,eq,Ma,times,V,sM1,sV2)
binary(P,eq,Ma,times,P,sM1,sP2)
binary(M,eq,Ma,times,M,sM1,sM2)

binary(H,peq,Ma,times,H,sM1,sH2)
binary(D,peq,Ma,times,D,sM1,sD2)
binary(V,peq,Ma,times,V,sM1,sV2)
binary(P,peq,Ma,times,P,sM1,sP2)
binary(M,peq,Ma,times,M,sM1,sM2)

binary(H,eqm,Ma,times,H,sM1,sH2)
binary(D,eqm,Ma,times,D,sM1,sD2)
binary(V,eqm,Ma,times,V,sM1,sV2)
binary(P,eqm,Ma,times,P,sM1,sP2)
binary(M,eqm,Ma,times,M,sM1,sM2)

binary(H,meq,Ma,times,H,sM1,sH2)
binary(D,meq,Ma,times,D,sM1,sD2)
binary(V,meq,Ma,times,V,sM1,sV2)
binary(P,meq,Ma,times,P,sM1,sP2)
binary(M,meq,Ma,times,M,sM1,sM2)

  /* Right multiply by color matrix */

binary(P,eq,P,times,M,sP1,sM2)
binary(M,eq,M,times,M,sM1,sM2)

binary(P,peq,P,times,M,sP1,sM2)
binary(M,peq,M,times,M,sM1,sM2)

binary(P,eqm,P,times,M,sP1,sM2)
binary(M,eqm,M,times,M,sM1,sM2)

binary(P,meq,P,times,M,sP1,sM2)
binary(M,meq,M,times,M,sM1,sM2)

  /* Right multiply by adjoint of color matrix */

binary(P,eq,P,times,Ma,sP1,sM2)
binary(M,eq,M,times,Ma,sM1,sM2)

binary(P,peq,P,times,Ma,sP1,sM2)
binary(M,peq,M,times,Ma,sM1,sM2)

binary(P,eqm,P,times,Ma,sP1,sM2)
binary(M,eqm,M,times,Ma,sM1,sM2)

binary(P,meq,P,times,Ma,sP1,sM2)
binary(M,meq,M,times,Ma,sM1,sM2)

#endif /* QLA_Precision != Q */

`
  return 0;
}
'
