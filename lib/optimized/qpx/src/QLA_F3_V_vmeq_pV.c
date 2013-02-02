/**************** QLA_F3_V_vmeq_pV.c ********************/

#include <qla_config.h>
#include <qla_types.h>
#include <qla_random.h>
#include <qla_cmath.h>
#include <math.h>

#include <bgqintrin.h>
//#include <QLA_F3_V_vmeq_pV_a2.h>
#define pairx(a,b) vec_sldw(a,b,2)

void
QLA_F3_V_vmeq_pV( QLA_F3_ColorVector *restrict r, QLA_F3_ColorVector *restrict *a, int n )
{
#ifdef HAVE_XLC
#pragma disjoint(*r, **a)
#endif
  if(is_aligned(r,16) && (n&1)==0) {
    //QLA_F3_V_vmeq_pV_a2(r,a,n);
#pragma unroll(2)
#pragma omp parallel for
    for(int i=0; i<n; i+=2) {
      QLA_F_Real *ri = (QLA_F_Real *) &r[i];
      QLA_F_Real *ai0 = (QLA_F_Real *) a[i];
      QLA_F_Real *ai1 = (QLA_F_Real *) a[i+1];
#ifdef HAVE_XLC
#pragma disjoint(*ri, *ai0, *ai1)
#endif
      V4D a00 = v4load2f(ai0,0);
      V4D a01 = v4load2f(ai0,8);
      V4D a02 = v4load2f(ai0,16);
      V4D a10 = v4load2f(ai1,0);
      V4D a11 = v4load2f(ai1,8);
      V4D a12 = v4load2f(ai1,16);
      V4D r0 = v4loadf(ri,0);
      V4D r1 = v4loadf(ri,16);
      V4D r2 = v4loadf(ri,32);
      V4D a0 = pairx(a00,a01);
      V4D a1 = pairx(a02,a10);
      V4D a2 = pairx(a11,a12);
      v4storef(ri, 0,v4sub(r0,a0));
      v4storef(ri,16,v4sub(r1,a1));
      v4storef(ri,32,v4sub(r2,a2));
    }
  } else {
#pragma omp parallel for
    for(int i=0; i<n; i++) {
      for(int i_c=0; i_c<3; i_c++) {
        QLA_D_Complex _t;
        QLA_DF_c_eq_c(_t,QLA_F3_elem_V(r[i],i_c));
        QLA_c_meq_c(_t, QLA_DF_c(QLA_F3_elem_V(*a[i],i_c)));
        QLA_FD_c_eq_c(QLA_F3_elem_V(r[i],i_c),_t);
      }
    }
  }
}
