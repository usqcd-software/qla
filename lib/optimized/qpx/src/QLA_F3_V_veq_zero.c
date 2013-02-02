/**************** QLA_F3_V_veq_zero.c ********************/

#include <qla_config.h>
#include <qla_types.h>
#include <qla_random.h>
#include <qla_cmath.h>
#include <math.h>

#include <bgqintrin.h>

void QLA_F3_V_veq_zero ( QLA_F3_ColorVector *restrict r, int n )
{
  if(is_aligned(r,16) && ((n&1)==0)) {
    V4D z = v4splat(0);
    QLA_F_Real *r0 = (QLA_F_Real *) r;
    int nn = 6*n;
#pragma omp parallel for
    for(int i=0; i<nn; i+=4) {
      v4storefnr(r0,4*i,z);
    }
  } else {
#pragma omp parallel for
    for(int i=0; i<n; i++) {
      for(int i_c=0; i_c<3; i_c++) {
	QLA_c_eq_r(QLA_F3_elem_V(r[i],i_c),0.);
      }
    }
  }
}
