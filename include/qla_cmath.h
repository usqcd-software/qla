#ifndef _QLA_CMATH_H
#define _QLA_CMATH_H

QLA_F_Complex QLA_F_csqrt(QLA_F_Complex *a);
QLA_D_Complex QLA_D_csqrt(QLA_D_Complex *a);
#define QLA_csqrt(x) QLA_D_csqrt(x)

QLA_F_Complex QLA_F_cpow(QLA_F_Complex *a, QLA_F_Real b);
QLA_D_Complex QLA_D_cpow(QLA_D_Complex *a, QLA_D_Real b);
#define QLA_cpow(a,b) QLA_D_cpow(a,b)

QLA_F_Complex QLA_F_cexp(QLA_F_Complex *a);
QLA_D_Complex QLA_D_cexp(QLA_D_Complex *a);
#define QLA_cexp(x) QLA_D_cexp(x)

QLA_F_Complex QLA_F_cexpi(QLA_F_Real theta);
QLA_D_Complex QLA_D_cexpi(QLA_D_Real theta);
#define QLA_cexpi(x) QLA_D_cexpi(x)

QLA_F_Complex QLA_F_clog(QLA_F_Complex *a);
QLA_D_Complex QLA_D_clog(QLA_D_Complex *a);
#define QLA_clog(x) QLA_D_clog(x)

QLA_F_Complex QLA_F_csinh(QLA_F_Complex *a);
QLA_D_Complex QLA_D_csinh(QLA_D_Complex *a);
#define QLA_csinh(x) QLA_D_csinh(x)

QLA_F_Complex QLA_F_ccosh(QLA_F_Complex *a);
QLA_D_Complex QLA_D_ccosh(QLA_D_Complex *a);
#define QLA_ccosh(x) QLA_D_ccosh(x)

void QLA_F_csinhcosh(QLA_F_Complex *a, QLA_F_Complex *sh, QLA_F_Complex *ch);
void QLA_D_csinhcosh(QLA_D_Complex *a, QLA_D_Complex *sh, QLA_D_Complex *ch);

/*********************************************************************/
/* If the compiler doesn't know about "round" (C99 standard) 
   we have to define it   */
/*********************************************************************/
#if (__STDC_VERSION__ < 199901L)
double round(double x);
#endif

#endif /* _QLA_CMATH_H */
