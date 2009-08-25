/********************** csqrt.c **********************/
/* MILC version 6 */
/* Subroutines for operations on complex numbers */
/* complex square root */

#include <qla_config.h>
#include <qla_types.h>
#include <qla_cmath.h>
#include <math.h>

QLA_D_Complex QLA_csqrt( QLA_D_Complex *z ){
  QLA_D_Complex c;
  double theta,r;

  r = sqrt((double)QLA_norm_c(*z));
  theta = 0.5*QLA_arg_c(*z);
  c = QLA_cexpi(theta);
  QLA_c_eq_c_times_r(c,c,r);
  return(c);
}
