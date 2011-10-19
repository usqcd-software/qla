/**************** QLA_D3_V_vpeq_M_times_V.c ********************/

#define QLA_RESTRICT restrict
#define QLA_Precision 'D'
#define QLA_Colors 3

#include <stdio.h>
#include <qla_config.h>
#include <qla_types.h>
#include <qla_random.h>
#include <qla_cmath.h>
#include <qla_d3.h>
#include <math.h>

#define loada(_i,_j) QLA_D_Complex a##_i##_j; QLA_c_eq_c(a##_i##_j,QLA_D3_elem_M(a[i],_i,_j))
#define loadb(_i) QLA_D_Complex b##_i; QLA_c_eq_c(b##_i,QLA_D3_elem_V(b[i],_i))
#define peq(_i,_j) QLA_c_peq_c_times_c(x, a##_i##_j, b##_j)
void QLA_D3_V_vpeq_M_times_V ( QLA_D3_ColorVector *restrict r, QLA_D3_ColorMatrix *restrict a, QLA_D3_ColorVector *restrict b, int n )
{
#ifdef HAVE_XLC
#pragma disjoint(*r, *a, *b)
  __alignx(16,r);
  __alignx(16,a);
  __alignx(16,b);
#endif
  for(int i=0; i<n; i++) {
    loadb(0);
    loadb(1);
    loadb(2);
    for(int i_c=0; i_c<3; i_c++) {
      QLA_D_Complex x;
      QLA_c_eq_c(x,QLA_D3_elem_V(r[i],i_c));

      loada(i_c,0);
      loada(i_c,1);
      loada(i_c,2);

      peq(i_c,0);
      peq(i_c,1);
      peq(i_c,2);

      QLA_c_eq_c(QLA_D3_elem_V(r[i],i_c),x);
    }
  }
}
