#include <qla_config.h>
#include <qla_types.h>
#include <qla_cmath.h>
#define _GNU_SOURCE
#include <math.h>

#ifndef __USE_GNU
#define sincosf(x,s,c) *(s) = sinf(x); *(c) = cosf(x)
#define sincos(x,s,c) *(s) = sin(x); *(c) = cos(x)
#endif

QLA_F_Complex
QLA_F_cexpi(QLA_F_Real theta)
{
  QLA_F_Real s, c;
  sincosf(theta, &s, &c);
  QLA_F_Complex z;
  QLA_c_eq_r_plus_ir(z, c, s);
  return z;
}

QLA_D_Complex
QLA_D_cexpi(QLA_D_Real theta)
{
  QLA_D_Real s, c;
  sincos(theta, &s, &c);
  QLA_D_Complex z;
  QLA_c_eq_r_plus_ir(z, c, s);
  return z;
}
