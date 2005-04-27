/**************** QLA_F3_V_vpeq_M_times_V.c ********************/

#include <qla_types.h>
#include <qla_cmath.h>
#include <math.h>
#include <stdlib.h>
#include "QLA_F3_V_peq_M_times_V.h"

void
QLA_F3_V_vpeq_M_times_pV( QLA_F3_ColorVector *__restrict__ r,
			  QLA_F3_ColorMatrix *a,
			  QLA_F3_ColorVector **b,
			  int n )
{
  int i;

  for(i=0; i<n; i++) {
    QLA_F3_V_peq_M_times_V( &r[i], &a[i], b[i] );
  }
}
