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
#define loadb(_i) QLA_D_Complex b##_i; QLA_c_eq_c(b##_i,QLA_D3_elem_V(*b[i],_i))
#define loadr(_i) QLA_D_Complex r##_i; QLA_c_eq_c(r##_i,QLA_D3_elem_V(r[i],_i))
#define storer(_i) QLA_c_eq_c(QLA_D3_elem_V(r[i],_i),r##_i);
#define peq(_i,_j) QLA_c_peq_c_times_c(r##_i, a##_i##_j, b##_j)
void QLA_D3_V_vpeq_M_times_pV ( QLA_D3_ColorVector *restrict r, QLA_D3_ColorMatrix *restrict a, QLA_D3_ColorVector *restrict *b, int n )
{
#ifdef HAVE_XLC
#pragma disjoint(*r, *a, **b)
  __alignx(16,r);
  __alignx(16,a);
#endif
  for(int i=0; i<n; i++) {
#ifdef HAVE_XLC
    __alignx(16,b[i]);
#endif
    loadb(0);
    loadb(1);
    loadb(2);

    loadr(0);
    loadr(1);
    loadr(2);

    loada(0,0);
    loada(0,1);
    loada(0,2);
    peq(0,0);
    peq(0,1);
    peq(0,2);
    loada(1,0);
    loada(1,1);
    loada(1,2);
    peq(1,0);
    peq(1,1);
    peq(1,2);
    loada(2,0);
    loada(2,1);
    loada(2,2);
    peq(2,0);
    peq(2,1);
    peq(2,2);

    storer(0);
    storer(1);
    storer(2);
  }
}
