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

  /* Define test data */
'
include(tensor_idx_defs.m4)
`
int test_tensor_idx3(FILE *fp)
{
  initialize_variables(fp);
'
#if ( QLA_Precision != 'Q' )  /* Q precision is limited to assignments */

  /* Left multiply by color matrix */

alleqops(`binary(V,',`,M,times,V,sM1,sV1)')
alleqops(`binary(H,',`,M,times,H,sM1,sH1)')
alleqops(`binary(D,',`,M,times,D,sM1,sD1)')
alleqops(`binary(P,',`,M,times,P,sM1,sP1)')
alleqops(`binary(P,',`,M,times,Pa,sM1,sP1)')

alleqops(`binary(V,',`,Ma,times,V,sM1,sV1)')
alleqops(`binary(H,',`,Ma,times,H,sM1,sH1)')
alleqops(`binary(D,',`,Ma,times,D,sM1,sD1)')
alleqops(`binary(P,',`,Ma,times,P,sM1,sP1)')
alleqops(`binary(P,',`,Ma,times,Pa,sM1,sP1)')

  /* Right multiply by color matrix */

alleqops(`binary(P,',`,P,times,M,sP1,sM1)')
alleqops(`binary(P,',`,P,times,Ma,sP1,sM1)')
alleqops(`binary(P,',`,Pa,times,M,sP1,sM1)')
alleqops(`binary(P,',`,Pa,times,Ma,sP1,sM1)')

#endif /* QLA_Precision != Q */
`
  return 0;
}
'
