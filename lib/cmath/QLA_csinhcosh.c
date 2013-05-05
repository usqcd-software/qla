#include <qla_config.h>
#include <qla_types.h>
#include <qla_cmath.h>
#define _GNU_SOURCE
#include <math.h>

#ifndef __USE_GNU
#define sincosf(x,s,c) *(s) = sinf(x); *(c) = cosf(x)
#define sincos(x,s,c) *(s) = sin(x); *(c) = cos(x)
#endif

// sinh(z) = cos(y)*sinh(x) + i*sin(y)*cosh(x)
// cosh(z) = cos(y)*cosh(x) + i*sin(y)*sinh(x)
void
QLA_F_csinhcosh(QLA_F_Complex *a, QLA_F_Complex *sh, QLA_F_Complex *ch)
{
  QLA_F_Real sx = sinhf(QLA_real(*a));
  //QLA_F_Real cx = coshf(QLA_real(*a));
  QLA_F_Real cx = sqrtf(1+sx*sx);
  QLA_F_Real sy, cy;
  sincosf(QLA_imag(*a), &sy, &cy);
  QLA_c_eq_r_plus_ir(*sh, cy*sx, sy*cx);
  QLA_c_eq_r_plus_ir(*ch, cy*cx, sy*sx);
}

void
QLA_D_csinhcosh(QLA_D_Complex *a, QLA_D_Complex *sh, QLA_D_Complex *ch)
{
  QLA_D_Real sx = sinh(QLA_real(*a));
  //QLA_D_Real cx = cosh(QLA_real(*a));
  QLA_D_Real cx = sqrt(1+sx*sx);
  QLA_D_Real sy, cy;
  sincos(QLA_imag(*a), &sy, &cy);
  QLA_c_eq_r_plus_ir(*sh, cy*sx, sy*cx);
  QLA_c_eq_r_plus_ir(*ch, cy*cx, sy*sx);
}
