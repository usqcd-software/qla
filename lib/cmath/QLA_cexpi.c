/********************** cexpi.c **********************/
/* MILC version 6 */
/* Subroutines for operations on complex numbers */
/* exp( i*theta ) */

#include <qla_config.h>
#include <qla_types.h>
#include <qla_cmath.h>
#include <math.h>

QLA_D_Complex QLA_cexpi( QLA_D_Real theta ){
    QLA_D_Complex c;

    QLA_c_eq_r_plus_ir(c, cos( (double)theta ), sin( (double)theta ));
    /* there must be a more efficient way */
    return( c );
}
