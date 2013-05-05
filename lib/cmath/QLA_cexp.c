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
QLA_F_cexp(QLA_F_Complex *a)
{
  float _Complex ca, cr;
  QLA_F_c99_eq_c(ca, *a);
  cr = cexpf(ca);
  QLA_F_Complex r;
  QLA_F_c_eq_c99(r, cr);
  return r;
}

QLA_D_Complex
QLA_D_cexp(QLA_D_Complex *a)
{
  double _Complex ca, cr;
  QLA_D_c99_eq_c(ca, *a);
  cr = cexp(ca);
  QLA_D_Complex r;
  QLA_D_c_eq_c99(r, cr);
  return r;
}

#else

QLA_F_Complex
QLA_F_cexp(QLA_F_Complex *a)
{
  QLA_F_Real mag = expf(QLA_real(*a));
  QLA_F_Real s, c;
  sincosf(QLA_imag(*a), &s, &c);
  QLA_F_Complex z;
  QLA_c_eq_r_plus_ir(z, mag*c, mag*s);
  return z;
}

QLA_D_Complex
QLA_D_cexp(QLA_D_Complex *a)
{
  QLA_D_Real mag = exp(QLA_real(*a));
  QLA_D_Real s, c;
  sincos(QLA_imag(*a), &s, &c);
  QLA_D_Complex z;
  QLA_c_eq_r_plus_ir(z, mag*c, mag*s);
  return z;
}

#endif
