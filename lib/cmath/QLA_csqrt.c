#include <qla_config.h>
#include <qla_types.h>
#include <qla_cmath.h>
#include <math.h>

//#if (__STDC_VERSION__ >= 199901L) && !defined(__STDC_NO_COMPLEX__)
#if 0
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

QLA_F_Complex
QLA_F_csqrt(QLA_F_Complex *z)
{
  QLA_F_Real n = QLA_F_norm_c(*z);
  QLA_F_Real r = QLA_real(*z);
  QLA_F_Real i = QLA_imag(*z);
  QLA_F_Real sr = sqrtf(fabsf(0.5*(n+r)));
  QLA_F_Real si = copysignf(sqrtf(fabsf(0.5*(n-r))), i);
  QLA_F_Complex c;
  QLA_c_eq_r_plus_ir(c, sr, si);
  return c;
}

QLA_D_Complex
QLA_D_csqrt(QLA_D_Complex *z)
{
  QLA_D_Real n = QLA_D_norm_c(*z);
  QLA_D_Real r = QLA_real(*z);
  QLA_D_Real i = QLA_imag(*z);
  QLA_D_Real sr = sqrt(fabs(0.5*(n+r)));
  QLA_D_Real si = copysign(sqrt(fabs(0.5*(n-r))), i);
  QLA_D_Complex c;
  QLA_c_eq_r_plus_ir(c, sr, si);
  return c;
}

#endif
