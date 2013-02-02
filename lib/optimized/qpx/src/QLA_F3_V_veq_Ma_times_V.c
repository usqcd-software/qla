/**************** QLA_F3_V_veq_Ma_times_V.c ********************/

#include <qla_config.h>
#include <qla_types.h>
#include <qla_random.h>
#include <qla_cmath.h>
#include <math.h>

#include <bgqintrin.h>
#include <QLA_F3_V_veq_Ma_times_V_a2i.h>

void
QLA_F3_V_veq_Ma_times_V( QLA_F3_ColorVector *restrict r, QLA_F3_ColorMatrix *restrict a, QLA_F3_ColorVector *restrict b, int n )
{
#ifdef HAVE_XLC
#pragma disjoint(*r, *a, *b)
#endif
  if(is_aligned(r,16) && is_aligned(a,16) && is_aligned(b,16) && (n&1)==0) {
    QLA_F3_V_veq_Ma_times_V_a2(r,a,b,n);
  } else {
#pragma omp parallel for
    for(int i=0; i<n; i++) {
      for(int i_c=0; i_c<3; i_c++) {
	QLA_D_Complex x;
	QLA_c_eq_r(x,0.);
	for(int k_c=0; k_c<3; k_c++) {
	  QLA_c_peq_ca_times_c(x,QLA_F3_elem_M(a[i],k_c,i_c),QLA_F3_elem_V(b[i],k_c));
	}
	QLA_FD_c_eq_c(QLA_F3_elem_V(r[i],i_c),x);
      }
    }
  }
}
