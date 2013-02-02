/**************** QLA_F3_V_vpeq_M_times_pV.c ********************/

#include <qla_config.h>
#include <qla_types.h>
#include <qla_random.h>
#include <qla_cmath.h>
#include <math.h>

#include <bgqintrin.h>
#include <QLA_D3_V_vpeq_M_times_pV_a2i.h>

void QLA_D3_V_vpeq_M_times_pV ( QLA_D3_ColorVector *restrict r, QLA_D3_ColorMatrix *restrict a, QLA_D3_ColorVector *restrict *b, int n )
{
#ifdef HAVE_XLC
#pragma disjoint(*r, *a, **b)
#endif
  if(is_aligned(r,32) && is_aligned(a,32) && (n&1)==0) {
    QLA_D3_V_vpeq_M_times_pV_a2(r,a,b,n);
  } else {
#pragma omp parallel for
    for(int i=0; i<n; i++) {
      for(int i_c=0; i_c<3; i_c++) {
	QLA_D_Complex x;
	QLA_c_eq_c(x,QLA_D3_elem_V(r[i],i_c));
	for(int k_c=0; k_c<3; k_c++) {
	  QLA_c_peq_c_times_c(x, QLA_D3_elem_M(a[i],i_c,k_c), QLA_D3_elem_V(*b[i],k_c));
	}
	QLA_c_eq_c(QLA_D3_elem_V(r[i],i_c),x);
      }
    }
  }
}
