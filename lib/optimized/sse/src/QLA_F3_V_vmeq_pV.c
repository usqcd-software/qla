/**************** QLA_F3_V_vmeq_pV.c ********************/

#include <qla_types.h>
#include <qla_cmath.h>
#include <math.h>
#include <stdlib.h>
#include "inline_sse.h"

void
QLA_F3_V_vmeq_pV( QLA_F3_ColorVector *__restrict__ r,
		  QLA_F3_ColorVector **a,
		  int n )
{
  int i;

  for(i=0; i<n; i++) {
    QLA_F3_V_meq_V( r, *a );
    ++r; ++a;
  }
}
