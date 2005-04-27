/********************** cexp.c **********************/
/* From MILC version 6 */
/* Subroutines for operations on complex numbers */
/* complex exponential */

#include <qla_complex.h>
#include <math.h>

QLA_D_Complex QLA_cexp( QLA_D_Complex *a ){
  QLA_D_Complex c;
  double mag;
  mag = exp( (double)QLA_real(*a) );
  QLA_c_eq_r_plus_ir(c,  mag*cos( (double)QLA_imag(*a) ),
		         mag*sin( (double)QLA_imag(*a) ));
  return(c);
}
