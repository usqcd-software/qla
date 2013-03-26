#include <qla_config.h>
#include <qla_types.h>
#include <qla_cmath.h>
#include <math.h>

#if (__STDC_VERSION__ >= 199901L) && !defined(__STDC_NO_COMPLEX__)
#include <complex.h>

QLA_F_Complex
QLA_F_ccosh(QLA_F_Complex *a)
{
  float _Complex ca, cr;
  QLA_F_c99_eq_c(ca, *a);
  cr = ccoshf(ca);
  QLA_F_Complex r;
  QLA_F_c_eq_c99(r, cr);
  return r;
}

QLA_D_Complex
QLA_D_ccosh(QLA_D_Complex *a)
{
  double _Complex ca, cr;
  QLA_D_c99_eq_c(ca, *a);
  cr = ccosh(ca);
  QLA_D_Complex r;
  QLA_D_c_eq_c99(r, cr);
  return r;
}

#else

// 0.5*[exp(x)*(cos(y)+i*sin(y))+exp(-x)*(cos(y)-i*sin(y))]
// cos(y)*cosh(x) + i*sin(y)*sinh(x)
QLA_F_Complex
QLA_F_ccosh( QLA_F_Complex *a )
{
  QLA_F_Complex c;
  float sx,cx,sy,cy;
  sx = sinhf(QLA_real(*a));
  cx = coshf(QLA_real(*a));
  sy = sinf(QLA_imag(*a));
  cy = cosf(QLA_imag(*a));
  QLA_c_eq_r_plus_ir(c, cy*cx, sy*sx);
  return c;
}

QLA_D_Complex
QLA_D_ccosh( QLA_D_Complex *a )
{
  QLA_D_Complex c;
  double sx,cx,sy,cy;
  sx = sinh(QLA_real(*a));
  cx = cosh(QLA_real(*a));
  sy = sin(QLA_imag(*a));
  cy = cos(QLA_imag(*a));
  QLA_c_eq_r_plus_ir(c, cy*cx, sy*sx);
  return c;
}

#endif
