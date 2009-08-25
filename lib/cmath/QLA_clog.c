/********************** clog.c **********************/
/* MILC version 6 */
/* Subroutines for operations on complex numbers */
/* complex logarithm */

#include <qla_config.h>
#include <qla_types.h>
#include <qla_cmath.h>
#include <math.h>

QLA_D_Complex QLA_clog( QLA_D_Complex *a ){
    QLA_D_Complex c;

    QLA_c_eq_r_plus_ir(c, 0.5*log((double)QLA_norm2_c(*a)), QLA_arg_c(*a));
    return(c);
}
