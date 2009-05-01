#ifndef _QLA_CMATH_H
#define _QLA_CMATH_H

QLA_D_Complex QLA_cexp( QLA_D_Complex *a );
QLA_D_Complex QLA_cexpi( QLA_D_Real theta );
QLA_D_Complex QLA_clog( QLA_D_Complex *a );
QLA_D_Complex QLA_csqrt( QLA_D_Complex *z );

/*********************************************************************/
/* If the compiler doesn't know about "round" (C99 standard) 
   we have to define it   */
/*********************************************************************/
double round(double x);

#endif /* _QLA_CMATH_H */
