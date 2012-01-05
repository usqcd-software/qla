/********************** csqrt.c **********************/
/* MILC version 6 */
/* Subroutines for operations on complex numbers */
/* complex square root */

#include <qla_config.h>
#include <qla_types.h>
#include <qla_cmath.h>
#include <math.h>

#if (__STDC_VERSION__ >= 199901L) && !defined(__STDC_NO_COMPLEX__)
#include <complex.h>

QLA_F_Complex
QLA_F_csqrt(QLA_F_Complex *a)
{
  float _Complex ca, cr;
  QLA_F_c99_eq_c(ca, *a);
  cr = csqrtf(ca);
  QLA_F_Complex r;
  QLA_F_c_eq_c99(r, cr);
  return r;
}

QLA_D_Complex
QLA_D_csqrt(QLA_D_Complex *a)
{
  double _Complex ca, cr;
  QLA_D_c99_eq_c(ca, *a);
  cr = csqrt(ca);
  QLA_D_Complex r;
  QLA_D_c_eq_c99(r, cr);
  return r;
}

#else

QLA_F_Complex QLA_F_csqrt( QLA_F_Complex *z ){
  QLA_F_Complex c;
  float theta,r;

  r = sqrtf((float)QLA_norm_c(*z));
  theta = 0.5*QLA_arg_c(*z);
  c = QLA_F_cexpi(theta);
  QLA_c_eq_c_times_r(c,c,r);
  return(c);
}

QLA_D_Complex QLA_D_csqrt( QLA_D_Complex *z ){
  QLA_D_Complex c;
  double theta,r;

  r = sqrt((double)QLA_norm_c(*z));
  theta = 0.5*QLA_arg_c(*z);
  c = QLA_D_cexpi(theta);
  QLA_c_eq_c_times_r(c,c,r);
  return(c);
}

#endif
