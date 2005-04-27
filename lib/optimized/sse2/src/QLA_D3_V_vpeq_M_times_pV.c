/**************** QLA_D3_V_vpeq_M_times_V.c ********************/

#include <qla_types.h>
#include <qla_cmath.h>
#include <math.h>
#include <stdlib.h>
#include "inline_sse.h"

void
QLA_D3_V_vpeq_M_times_pV( QLA_D3_ColorVector *__restrict__ r,
		 	 QLA_D3_ColorMatrix *a,
			 QLA_D3_ColorVector **b,
			 int n )
{
  int i;

  for(i=0; i<n; i++) {
    QLA_D3_V_peq_M_times_V( r, a, *b );
    ++r; ++a; ++b;
  }
}
