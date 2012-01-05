/********************** clog.c **********************/
/* MILC version 6 */
/* Subroutines for operations on complex numbers */
/* complex logarithm */

#include <qla_config.h>
#include <qla_types.h>
#include <qla_cmath.h>
#include <math.h>

#if (__STDC_VERSION__ >= 199901L) && !defined(__STDC_NO_COMPLEX__)
#include <complex.h>

QLA_F_Complex
QLA_F_clog(QLA_F_Complex *a)
{
  float _Complex ca, cr;
  QLA_F_c99_eq_c(ca, *a);
  cr = clogf(ca);
  QLA_F_Complex r;
  QLA_F_c_eq_c99(r, cr);
  return r;
}

QLA_D_Complex
QLA_D_clog(QLA_D_Complex *a)
{
  double _Complex ca, cr;
  QLA_D_c99_eq_c(ca, *a);
  cr = clog(ca);
  QLA_D_Complex r;
  QLA_D_c_eq_c99(r, cr);
  return r;
}

#else

QLA_F_Complex QLA_F_clog( QLA_F_Complex *a ){
    QLA_F_Complex c;

    QLA_c_eq_r_plus_ir(c, 0.5*log((float)QLA_norm2_c(*a)), QLA_arg_c(*a));
    return(c);
}

QLA_D_Complex QLA_D_clog( QLA_D_Complex *a ){
    QLA_D_Complex c;

    QLA_c_eq_r_plus_ir(c, 0.5*log((double)QLA_norm2_c(*a)), QLA_arg_c(*a));
    return(c);
}

#endif
