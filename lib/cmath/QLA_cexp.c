/********************** cexp.c **********************/
/* From MILC version 6 */
/* Subroutines for operations on complex numbers */
/* complex exponential */

#include <qla_config.h>
#include <qla_types.h>
#include <qla_cmath.h>
#include <math.h>

#if (__STDC_VERSION__ >= 199901L) && !defined(__STDC_NO_COMPLEX__)
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

QLA_F_Complex QLA_F_cexp( QLA_F_Complex *a ){
  QLA_F_Complex c;
  float mag;
  mag = expf( (float)QLA_real(*a) );
  QLA_c_eq_r_plus_ir(c,  mag*cosf( (float)QLA_imag(*a) ),
		         mag*sinf( (float)QLA_imag(*a) ));
  return(c);
}

QLA_D_Complex QLA_D_cexp( QLA_D_Complex *a ){
  QLA_D_Complex c;
  double mag;
  mag = exp( (double)QLA_real(*a) );
  QLA_c_eq_r_plus_ir(c,  mag*cos( (double)QLA_imag(*a) ),
		         mag*sin( (double)QLA_imag(*a) ));
  return(c);
}

#endif
