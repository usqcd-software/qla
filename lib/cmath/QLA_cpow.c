#include <qla_config.h>
#include <qla_types.h>
#include <qla_cmath.h>
#include <math.h>

//#if (__STDC_VERSION__ >= 199901L) && !defined(__STDC_NO_COMPLEX__)
#if 0
#include <complex.h>

QLA_F_Complex
QLA_F_cpow(QLA_F_Complex *a, QLA_F_Real b)
{
  float _Complex ca, cr;
  QLA_F_c99_eq_c(ca, *a);
  cr = cpowf(ca, b);
  QLA_F_Complex r;
  QLA_F_c_eq_c99(r, cr);
  return r;
}

QLA_D_Complex
QLA_D_cpow(QLA_D_Complex *a, QLA_D_Real b)
{
  double _Complex ca, cr;
  QLA_D_c99_eq_c(ca, *a);
  cr = cpow(ca, b);
  QLA_D_Complex r;
  QLA_D_c_eq_c99(r, cr);
  return r;
}

#else

QLA_F_Complex
QLA_F_cpow(QLA_F_Complex *a, QLA_F_Real b)
{
  QLA_F_Real r = pow(QLA_norm2_c(*a), 0.5*b);
  QLA_F_Real theta = b*QLA_F_arg_c(*a);
  QLA_F_Complex c = QLA_F_cexpi(theta);
  QLA_c_eq_c_times_r(c,c,r);
  return c;
}

QLA_D_Complex
QLA_D_cpow(QLA_D_Complex *a, QLA_D_Real b)
{
  QLA_D_Real r = pow(QLA_norm2_c(*a), 0.5*b);
  QLA_D_Real theta = b*QLA_D_arg_c(*a);
  QLA_D_Complex c = QLA_D_cexpi(theta);
  QLA_c_eq_c_times_r(c,c,r);
  return c;
}

#endif
