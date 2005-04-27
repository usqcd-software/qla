/********************** cexpi.c **********************/
/* MILC version 6 */
/* Subroutines for operations on complex numbers */
/* exp( i*theta ) */

#include <math.h>
#include <qla_complex.h>

QLA_D_Complex QLA_cexpi( QLA_D_Real theta ){
    QLA_D_Complex c;

    QLA_c_eq_r_plus_ir(c, cos( (double)theta ), sin( (double)theta ));
    /* there must be a more efficient way */
    return( c );
}
