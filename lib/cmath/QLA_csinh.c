#include <qla_config.h>
#include <qla_types.h>
#include <qla_cmath.h>
#define _GNU_SOURCE
#include <math.h>

#ifndef __USE_GNU
#define sincosf(x,s,c) *(s) = sinf(x); *(c) = cosf(x)
#define sincos(x,s,c) *(s) = sin(x); *(c) = cos(x)
#endif

//#if (__STDC_VERSION__ >= 199901L) && !defined(__STDC_NO_COMPLEX__)
#if 0
#include <complex.h>

QLA_F_Complex
QLA_F_csinh(QLA_F_Complex *a)
{
  float _Complex ca, cr;
  QLA_F_c99_eq_c(ca, *a);
  cr = csinhf(ca);
  QLA_F_Complex r;
  QLA_F_c_eq_c99(r, cr);
  return r;
}

QLA_D_Complex
QLA_D_csinh(QLA_D_Complex *a)
{
  double _Complex ca, cr;
  QLA_D_c99_eq_c(ca, *a);
  cr = csinh(ca);
  QLA_D_Complex r;
  QLA_D_c_eq_c99(r, cr);
  return r;
}

#else

// 0.5*[exp(x)*(cos(y)+i*sin(y))-exp(-x)*(cos(y)-i*sin(y))]
// cos(y)*sinh(x) + i*sin(y)*cosh(x)
QLA_F_Complex
QLA_F_csinh(QLA_F_Complex *a)
{
  QLA_F_Real sx = sinhf(QLA_real(*a));
  //QLA_F_Real cx = coshf(QLA_real(*a));
  QLA_F_Real cx = sqrtf(1+sx*sx);
  QLA_F_Real sy, cy;
  sincosf(QLA_imag(*a), &sy, &cy);
  QLA_F_Complex z;
  QLA_c_eq_r_plus_ir(z, cy*sx, sy*cx);
  return z;
}

QLA_D_Complex
QLA_D_csinh(QLA_D_Complex *a)
{
  QLA_D_Real sx = sinh(QLA_real(*a));
  //QLA_D_Real cx = cosh(QLA_real(*a));
  QLA_D_Real cx = sqrt(1+sx*sx);
  QLA_D_Real sy, cy;
  sincos(QLA_imag(*a), &sy, &cy);
  QLA_D_Complex z;
  QLA_c_eq_r_plus_ir(z, cy*sx, sy*cx);
  return z;
}

#endif
