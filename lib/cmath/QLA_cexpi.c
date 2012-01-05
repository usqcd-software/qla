/********************** cexpi.c **********************/
/* MILC version 6 */
/* Subroutines for operations on complex numbers */
/* exp( i*theta ) */

#include <qla_config.h>
#include <qla_types.h>
#include <qla_cmath.h>
#define _GNU_SOURCE
#include <math.h>

QLA_F_Complex
QLA_F_cexpi(QLA_F_Real theta)
{
  QLA_F_Complex z;
  QLA_F_Real s, c;
#ifdef __USE_GNU
  sincosf(theta, &s, &c);
#else
  s = sinf(theta);
  c = cosf(theta);
#endif
  QLA_c_eq_r_plus_ir(z, c, s);
  return z;
}

QLA_D_Complex
QLA_D_cexpi(QLA_D_Real theta)
{
  QLA_D_Complex z;
  QLA_D_Real s, c;
#ifdef __USE_GNU
  sincos(theta, &s, &c);
#else
  s = sin(theta);
  c = cos(theta);
#endif
  QLA_c_eq_r_plus_ir(z, c, s);
  return z;
}
