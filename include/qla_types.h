#ifndef _QLA_TYPES_H
#define _QLA_TYPES_H

/* real and complex */
#include <qla_complex.h>

/* Maximum color Nc */
#define QLA_MAX_Nc 5

/* Number of spins */
#define QLA_Ns 4

/****************************************************************************/
/* Implementation-specific data layout */
/****************************************************************************/
#define NC QLA_MAX_Nc
#define NS QLA_Ns
#define NH (QLA_Ns/2)

/* SU(3) single precision */
typedef struct { QLA_F_Complex e[3][3]; } QLA_F3_ColorMatrix;
typedef struct { QLA_F_Complex c[3]; } QLA_F3_ColorVector;
typedef struct { QLA_F3_ColorVector h[NH]; } QLA_F3_HalfFermion;
typedef struct { QLA_F3_ColorVector d[NS]; } QLA_F3_DiracFermion;
typedef struct { QLA_F3_DiracFermion d[NS]; } QLA_F3_SpinDiracFermion;
typedef struct { QLA_F3_SpinDiracFermion c[3]; } QLA_F3_DiracPropagator;

#define QLA_F3_elem_R(a) (a)
#define QLA_F3_elem_C(a) (a)
#define QLA_F3_elem_I(a) (a)
#define QLA_F3_elem_H(a,ic,is) (a).h[is].c[ic]
#define QLA_F3_elem_D(a,ic,is) (a).d[is].c[ic]
#define QLA_F3_elem_J(a,ic,is,js) (a).d[is].c[ic].d[js]
#define QLA_F3_elem_V(a,ic) (a).c[ic]
#define QLA_F3_elem_P(a,ic,is,jc,js) (a).c[jc].d[js].d[ic].c[is]
#define QLA_F3_elem_M(a,ic,jc) (a).e[ic][jc]

/* SU(3) double precision */
typedef struct { QLA_D_Complex e[3][3]; } QLA_D3_ColorMatrix;
typedef struct { QLA_D_Complex c[3]; } QLA_D3_ColorVector;
typedef struct { QLA_D3_ColorVector h[NH]; } QLA_D3_HalfFermion;
typedef struct { QLA_D3_ColorVector d[NS]; } QLA_D3_DiracFermion;
typedef struct { QLA_D3_DiracFermion d[NS]; } QLA_D3_SpinDiracFermion;
typedef struct { QLA_D3_SpinDiracFermion c[3]; } QLA_D3_DiracPropagator;

#define QLA_D3_elem_R(a) (a)
#define QLA_D3_elem_C(a) (a)
#define QLA_D3_elem_I(a) (a)
#define QLA_D3_elem_H(a,ic,is) (a).h[is].c[ic]
#define QLA_D3_elem_D(a,ic,is) (a).d[is].c[ic]
#define QLA_D3_elem_J(a,ic,is,js) (a).d[is].c[ic].d[js]
#define QLA_D3_elem_V(a,ic) (a).c[ic]
#define QLA_D3_elem_P(a,ic,is,jc,js) (a).c[jc].d[js].d[ic].c[is]
#define QLA_D3_elem_M(a,ic,jc) (a).e[ic][jc]

/* SU(3) long double precision */
typedef struct { QLA_Q_Complex e[3][3]; } QLA_Q3_ColorMatrix;
typedef struct { QLA_Q_Complex c[3]; } QLA_Q3_ColorVector;
typedef struct { QLA_Q3_ColorVector h[NH]; } QLA_Q3_HalfFermion;
typedef struct { QLA_Q3_ColorVector d[NS]; } QLA_Q3_DiracFermion;
typedef struct { QLA_Q3_DiracFermion d[NS]; } QLA_Q3_SpinDiracFermion;
typedef struct { QLA_Q3_SpinDiracFermion c[3]; } QLA_Q3_DiracPropagator;

#define QLA_Q3_elem_R(a) (a)
#define QLA_Q3_elem_C(a) (a)
#define QLA_Q3_elem_I(a) (a)
#define QLA_Q3_elem_H(a,ic,is) (a).h[is].c[ic]
#define QLA_Q3_elem_D(a,ic,is) (a).d[is].c[ic]
#define QLA_Q3_elem_J(a,ic,is,js) (a).d[is].c[ic].d[js]
#define QLA_Q3_elem_V(a,ic) (a).c[ic]
#define QLA_Q3_elem_P(a,ic,is,jc,js) (a).c[jc].d[js].d[ic].c[is]
#define QLA_Q3_elem_M(a,ic,jc) (a).e[ic][jc]

/* SU(N) single precision */

typedef struct { QLA_F_Complex e[NC][NC]; } QLA_FN_ColorMatrix;
typedef struct { QLA_F_Complex c[NC]; } QLA_FN_ColorVector;
typedef struct { QLA_FN_ColorVector h[NH]; } QLA_FN_HalfFermion;
typedef struct { QLA_FN_ColorVector d[NS]; } QLA_FN_DiracFermion;
typedef struct { QLA_FN_DiracFermion d[NS]; } QLA_FN_SpinDiracFermion;
typedef struct { QLA_FN_SpinDiracFermion c[NC]; } QLA_FN_DiracPropagator;

#define QLA_FN_elem_R(a) (a)
#define QLA_FN_elem_C(a) (a)
#define QLA_FN_elem_I(a) (a)
#define QLA_FN_elem_H(a,ic,is) (a).h[is].c[ic]
#define QLA_FN_elem_D(a,ic,is) (a).d[is].c[ic]
#define QLA_FN_elem_J(a,ic,is,js) (a).d[is].c[ic].d[js]
#define QLA_FN_elem_V(a,ic) (a).c[ic]
#define QLA_FN_elem_P(a,ic,is,jc,js) (a).c[jc].d[js].d[ic].c[is]
#define QLA_FN_elem_M(a,ic,jc) (a).e[ic][jc]

/* SU(N) double precision */
typedef struct { QLA_D_Complex e[NC][NC]; } QLA_DN_ColorMatrix;
typedef struct { QLA_D_Complex c[NC]; } QLA_DN_ColorVector;
typedef struct { QLA_DN_ColorVector h[NH]; } QLA_DN_HalfFermion;
typedef struct { QLA_DN_ColorVector d[NS]; } QLA_DN_DiracFermion;
typedef struct { QLA_DN_DiracFermion d[NS]; } QLA_DN_SpinDiracFermion;
typedef struct { QLA_DN_SpinDiracFermion c[NC]; } QLA_DN_DiracPropagator;

#define QLA_DN_elem_R(a) (a)
#define QLA_DN_elem_C(a) (a)
#define QLA_DN_elem_I(a) (a)
#define QLA_DN_elem_H(a,ic,is) (a).h[is].c[ic]
#define QLA_DN_elem_D(a,ic,is) (a).d[is].c[ic]
#define QLA_DN_elem_J(a,ic,is,js) (a).d[is].c[ic].d[js]
#define QLA_DN_elem_V(a,ic) (a).c[ic]
#define QLA_DN_elem_P(a,ic,is,jc,js) (a).c[jc].d[js].d[ic].c[is]
#define QLA_DN_elem_M(a,ic,jc) (a).e[ic][jc]

/* SU(N) long double precision */
typedef struct { QLA_Q_Complex e[NC][NC]; } QLA_QN_ColorMatrix;
typedef struct { QLA_Q_Complex c[NC]; } QLA_QN_ColorVector;
typedef struct { QLA_QN_ColorVector h[NH]; } QLA_QN_HalfFermion;
typedef struct { QLA_QN_ColorVector d[NS]; } QLA_QN_DiracFermion;
typedef struct { QLA_QN_DiracFermion d[NS]; } QLA_QN_SpinDiracFermion;
typedef struct { QLA_QN_SpinDiracFermion c[NC]; } QLA_QN_DiracPropagator;

#define QLA_QN_elem_R(a) (a)
#define QLA_QN_elem_C(a) (a)
#define QLA_QN_elem_I(a) (a)
#define QLA_QN_elem_H(a,ic,is) (a).h[is].c[ic]
#define QLA_QN_elem_D(a,ic,is) (a).d[is].c[ic]
#define QLA_QN_elem_J(a,ic,is,js) (a).d[is].c[ic].d[js]
#define QLA_QN_elem_V(a,ic) (a).c[ic]
#define QLA_QN_elem_P(a,ic,is,jc,js) (a).c[jc].d[js].d[ic].c[is]
#define QLA_QN_elem_M(a,ic,jc) (a).e[ic][jc]

/* SU(2) single precision */
typedef struct { QLA_F_Complex e[2][2]; } QLA_F2_ColorMatrix;
typedef struct { QLA_F_Complex c[2]; } QLA_F2_ColorVector;
typedef struct { QLA_F2_ColorVector h[NH]; } QLA_F2_HalfFermion;
typedef struct { QLA_F2_ColorVector d[NS]; } QLA_F2_DiracFermion;
typedef struct { QLA_F2_DiracFermion d[NS]; } QLA_F2_SpinDiracFermion;
typedef struct { QLA_F2_SpinDiracFermion c[2]; } QLA_F2_DiracPropagator;

#define QLA_F2_elem_R(a) (a)
#define QLA_F2_elem_C(a) (a)
#define QLA_F2_elem_I(a) (a)
#define QLA_F2_elem_H(a,ic,is) (a).h[is].c[ic]
#define QLA_F2_elem_D(a,ic,is) (a).d[is].c[ic]
#define QLA_F2_elem_J(a,ic,is,js) (a).d[is].c[ic].d[js]
#define QLA_F2_elem_V(a,ic) (a).c[ic]
#define QLA_F2_elem_P(a,ic,is,jc,js) (a).c[jc].d[js].d[ic].c[is]
#define QLA_F2_elem_M(a,ic,jc) (a).e[ic][jc]

/* SU(2) double precision */
typedef struct { QLA_D_Complex e[2][2]; } QLA_D2_ColorMatrix;
typedef struct { QLA_D_Complex c[2]; } QLA_D2_ColorVector;
typedef struct { QLA_D2_ColorVector h[NH]; } QLA_D2_HalfFermion;
typedef struct { QLA_D2_ColorVector d[NS]; } QLA_D2_DiracFermion;
typedef struct { QLA_D2_DiracFermion d[NS]; } QLA_D2_SpinDiracFermion;
typedef struct { QLA_D2_SpinDiracFermion c[2]; } QLA_D2_DiracPropagator;

#define QLA_D2_elem_R(a) (a)
#define QLA_D2_elem_C(a) (a)
#define QLA_D2_elem_I(a) (a)
#define QLA_D2_elem_H(a,ic,is) (a).h[is].c[ic]
#define QLA_D2_elem_D(a,ic,is) (a).d[is].c[ic]
#define QLA_D2_elem_J(a,ic,is,js) (a).d[is].c[ic].d[js]
#define QLA_D2_elem_V(a,ic) (a).c[ic]
#define QLA_D2_elem_P(a,ic,is,jc,js) (a).c[jc].d[js].d[ic].c[is]
#define QLA_D2_elem_M(a,ic,jc) (a).e[ic][jc]

/* SU(2) double precision */
typedef struct { QLA_Q_Complex e[2][2]; } QLA_Q2_ColorMatrix;
typedef struct { QLA_Q_Complex c[2]; } QLA_Q2_ColorVector;
typedef struct { QLA_Q2_ColorVector h[NH]; } QLA_Q2_HalfFermion;
typedef struct { QLA_Q2_ColorVector d[NS]; } QLA_Q2_DiracFermion;
typedef struct { QLA_Q2_DiracFermion d[NS]; } QLA_Q2_SpinDiracFermion;
typedef struct { QLA_Q2_SpinDiracFermion c[2]; } QLA_Q2_DiracPropagator;

#define QLA_Q2_elem_R(a) (a)
#define QLA_Q2_elem_C(a) (a)
#define QLA_Q2_elem_I(a) (a)
#define QLA_Q2_elem_H(a,ic,is) (a).h[is].c[ic]
#define QLA_Q2_elem_D(a,ic,is) (a).d[is].c[ic]
#define QLA_Q2_elem_J(a,ic,is,js) (a).d[is].c[ic].d[js]
#define QLA_Q2_elem_V(a,ic) (a).c[ic]
#define QLA_Q2_elem_P(a,ic,is,jc,js) (a).c[jc].d[js].d[ic].c[is]
#define QLA_Q2_elem_M(a,ic,jc) (a).e[ic][jc]

#undef NC
#undef NH
#undef NS

/************************************************************************/
/* If the compiler doesn't know about "restrict" we have to suppress it */
/************************************************************************/
#ifndef __restrict__
#define __restrict__
#endif

/*********************************************************************/
/* If the compiler doesn't know about "round" (C99 standard) 
   we have to define it   */
/*********************************************************************/
double round(double x);

/*********************************************************************/
/* Translation of generic to specific datatypes and accessors */
/*********************************************************************/
/* Works only if QLA_Precision and QLA_Colors are defined */

#if ( QLA_Colors == 3 )

/* These types specify precision but are generic with respect to color */
/* (Long double precision is of very limited use and is not accessible
   through a generic choice.) */

typedef QLA_F3_ColorMatrix         QLA_F_ColorMatrix;
typedef QLA_F3_ColorVector         QLA_F_ColorVector;
typedef QLA_F3_HalfFermion         QLA_F_HalfFermion;
typedef QLA_F3_SpinDiracFermion    QLA_F_SpinDiracFermion;
typedef QLA_F3_DiracFermion        QLA_F_DiracFermion;
typedef QLA_F3_DiracPropagator     QLA_F_DiracPropagator;

#define QLA_F_elem_R QLA_F3_elem_R 
#define QLA_F_elem_C QLA_F3_elem_C 
#define QLA_F_elem_I QLA_F3_elem_I 
#define QLA_F_elem_H QLA_F3_elem_H 
#define QLA_F_elem_D QLA_F3_elem_D 
#define QLA_F_elem_J QLA_F3_elem_J 
#define QLA_F_elem_V QLA_F3_elem_V 
#define QLA_F_elem_P QLA_F3_elem_P 
#define QLA_F_elem_M QLA_F3_elem_M 

typedef QLA_D3_ColorMatrix         QLA_D_ColorMatrix;
typedef QLA_D3_ColorVector         QLA_D_ColorVector;
typedef QLA_D3_HalfFermion         QLA_D_HalfFermion;
typedef QLA_D3_SpinDiracFermion    QLA_D_SpinDiracFermion;
typedef QLA_D3_DiracFermion        QLA_D_DiracFermion;
typedef QLA_D3_DiracPropagator     QLA_D_DiracPropagator;

#define QLA_D_elem_R QLA_D3_elem_R 
#define QLA_D_elem_C QLA_D3_elem_C 
#define QLA_D_elem_I QLA_D3_elem_I 
#define QLA_D_elem_H QLA_D3_elem_H 
#define QLA_D_elem_D QLA_D3_elem_D 
#define QLA_D_elem_J QLA_D3_elem_J 
#define QLA_D_elem_V QLA_D3_elem_V 
#define QLA_D_elem_P QLA_D3_elem_P 
#define QLA_D_elem_M QLA_D3_elem_M 

typedef QLA_Q3_ColorMatrix         QLA_Q_ColorMatrix;
typedef QLA_Q3_ColorVector         QLA_Q_ColorVector;
typedef QLA_Q3_HalfFermion         QLA_Q_HalfFermion;
typedef QLA_Q3_SpinDiracFermion    QLA_Q_SpinDiracFermion;
typedef QLA_Q3_DiracFermion        QLA_Q_DiracFermion;
typedef QLA_Q3_DiracPropagator     QLA_Q_DiracPropagator;

#define QLA_Q_elem_R QLA_Q3_elem_R 
#define QLA_Q_elem_C QLA_Q3_elem_C 
#define QLA_Q_elem_I QLA_Q3_elem_I 
#define QLA_Q_elem_H QLA_Q3_elem_H 
#define QLA_Q_elem_D QLA_Q3_elem_D 
#define QLA_Q_elem_J QLA_Q3_elem_J 
#define QLA_Q_elem_V QLA_Q3_elem_V 
#define QLA_Q_elem_P QLA_Q3_elem_P 
#define QLA_Q_elem_M QLA_Q3_elem_M 

#if ( QLA_Precision == 'F' )

typedef QLA_F3_ColorMatrix         QLA_ColorMatrix;
typedef QLA_F3_ColorVector         QLA_ColorVector;
typedef QLA_F3_HalfFermion         QLA_HalfFermion;
typedef QLA_F3_SpinDiracFermion    QLA_SpinDiracFermion;
typedef QLA_F3_DiracFermion        QLA_DiracFermion;
typedef QLA_F3_DiracPropagator     QLA_DiracPropagator;

#define QLA_elem_R QLA_F3_elem_R 
#define QLA_elem_C QLA_F3_elem_C 
#define QLA_elem_I QLA_F3_elem_I 
#define QLA_elem_H QLA_F3_elem_H 
#define QLA_elem_D QLA_F3_elem_D 
#define QLA_elem_J QLA_F3_elem_J 
#define QLA_elem_V QLA_F3_elem_V 
#define QLA_elem_P QLA_F3_elem_P 
#define QLA_elem_M QLA_F3_elem_M 

#elif ( QLA_Precision == 'D' )

typedef QLA_D3_ColorMatrix         QLA_ColorMatrix;
typedef QLA_D3_ColorVector         QLA_ColorVector;
typedef QLA_D3_HalfFermion         QLA_HalfFermion;
typedef QLA_D3_SpinDiracFermion    QLA_SpinDiracFermion;
typedef QLA_D3_DiracFermion        QLA_DiracFermion;
typedef QLA_D3_DiracPropagator     QLA_DiracPropagator;

#define QLA_elem_R QLA_D3_elem_R 
#define QLA_elem_C QLA_D3_elem_C 
#define QLA_elem_I QLA_D3_elem_I 
#define QLA_elem_H QLA_D3_elem_H 
#define QLA_elem_D QLA_D3_elem_D 
#define QLA_elem_J QLA_D3_elem_J 
#define QLA_elem_V QLA_D3_elem_V 
#define QLA_elem_P QLA_D3_elem_P 
#define QLA_elem_M QLA_D3_elem_M 

#elif ( QLA_Precision == 'Q' )

typedef QLA_Q3_ColorMatrix         QLA_ColorMatrix;
typedef QLA_Q3_ColorVector         QLA_ColorVector;
typedef QLA_Q3_HalfFermion         QLA_HalfFermion;
typedef QLA_Q3_SpinDiracFermion    QLA_SpinDiracFermion;
typedef QLA_Q3_DiracFermion        QLA_DiracFermion;
typedef QLA_Q3_DiracPropagator     QLA_DiracPropagator;

#define QLA_elem_R QLA_Q3_elem_R 
#define QLA_elem_C QLA_Q3_elem_C 
#define QLA_elem_I QLA_Q3_elem_I 
#define QLA_elem_H QLA_Q3_elem_H 
#define QLA_elem_D QLA_Q3_elem_D 
#define QLA_elem_J QLA_Q3_elem_J 
#define QLA_elem_V QLA_Q3_elem_V 
#define QLA_elem_P QLA_Q3_elem_P 
#define QLA_elem_M QLA_Q3_elem_M 

#endif

#elif ( QLA_Colors == 2 )

/* These types specify precision but are generic with respect to color */

typedef QLA_F2_ColorMatrix         QLA_F_ColorMatrix;
typedef QLA_F2_ColorVector         QLA_F_ColorVector;
typedef QLA_F2_HalfFermion         QLA_F_HalfFermion;
typedef QLA_F2_SpinDiracFermion    QLA_F_SpinDiracFermion;
typedef QLA_F2_DiracFermion        QLA_F_DiracFermion;
typedef QLA_F2_DiracPropagator     QLA_F_DiracPropagator;

#define QLA_F_elem_R QLA_F2_elem_R 
#define QLA_F_elem_C QLA_F2_elem_C 
#define QLA_F_elem_I QLA_F2_elem_I 
#define QLA_F_elem_H QLA_F2_elem_H 
#define QLA_F_elem_D QLA_F2_elem_D 
#define QLA_F_elem_J QLA_F2_elem_J 
#define QLA_F_elem_V QLA_F2_elem_V 
#define QLA_F_elem_P QLA_F2_elem_P 
#define QLA_F_elem_M QLA_F2_elem_M 

typedef QLA_D2_ColorMatrix         QLA_D_ColorMatrix;
typedef QLA_D2_ColorVector         QLA_D_ColorVector;
typedef QLA_D2_HalfFermion         QLA_D_HalfFermion;
typedef QLA_D2_SpinDiracFermion    QLA_D_SpinDiracFermion;
typedef QLA_D2_DiracFermion        QLA_D_DiracFermion;
typedef QLA_D2_DiracPropagator     QLA_D_DiracPropagator;

#define QLA_D_elem_R QLA_D2_elem_R 
#define QLA_D_elem_C QLA_D2_elem_C 
#define QLA_D_elem_I QLA_D2_elem_I 
#define QLA_D_elem_H QLA_D2_elem_H 
#define QLA_D_elem_D QLA_D2_elem_D 
#define QLA_D_elem_J QLA_D2_elem_J 
#define QLA_D_elem_V QLA_D2_elem_V 
#define QLA_D_elem_P QLA_D2_elem_P 
#define QLA_D_elem_M QLA_D2_elem_M 

typedef QLA_Q2_ColorMatrix         QLA_Q_ColorMatrix;
typedef QLA_Q2_ColorVector         QLA_Q_ColorVector;
typedef QLA_Q2_HalfFermion         QLA_Q_HalfFermion;
typedef QLA_Q2_SpinDiracFermion    QLA_Q_SpinDiracFermion;
typedef QLA_Q2_DiracFermion        QLA_Q_DiracFermion;
typedef QLA_Q2_DiracPropagator     QLA_Q_DiracPropagator;

#define QLA_Q_elem_R QLA_Q2_elem_R 
#define QLA_Q_elem_C QLA_Q2_elem_C 
#define QLA_Q_elem_I QLA_Q2_elem_I 
#define QLA_Q_elem_H QLA_Q2_elem_H 
#define QLA_Q_elem_D QLA_Q2_elem_D 
#define QLA_Q_elem_J QLA_Q2_elem_J 
#define QLA_Q_elem_V QLA_Q2_elem_V 
#define QLA_Q_elem_P QLA_Q2_elem_P 
#define QLA_Q_elem_M QLA_Q2_elem_M 

#if ( QLA_Precision == 'F' )

typedef QLA_F2_ColorMatrix         QLA_ColorMatrix;
typedef QLA_F2_ColorVector         QLA_ColorVector;
typedef QLA_F2_HalfFermion         QLA_HalfFermion;
typedef QLA_F2_SpinDiracFermion    QLA_SpinDiracFermion;
typedef QLA_F2_DiracFermion        QLA_DiracFermion;
typedef QLA_F2_DiracPropagator     QLA_DiracPropagator;

#define QLA_elem_R QLA_F2_elem_R 
#define QLA_elem_C QLA_F2_elem_C 
#define QLA_elem_I QLA_F2_elem_I 
#define QLA_elem_H QLA_F2_elem_H 
#define QLA_elem_D QLA_F2_elem_D 
#define QLA_elem_J QLA_F2_elem_J 
#define QLA_elem_V QLA_F2_elem_V 
#define QLA_elem_P QLA_F2_elem_P 
#define QLA_elem_M QLA_F2_elem_M 

#elif ( QLA_Precision == 'D' )

typedef QLA_D2_ColorMatrix         QLA_ColorMatrix;
typedef QLA_D2_ColorVector         QLA_ColorVector;
typedef QLA_D2_HalfFermion         QLA_HalfFermion;
typedef QLA_D2_SpinDiracFermion    QLA_SpinDiracFermion;
typedef QLA_D2_DiracFermion        QLA_DiracFermion;
typedef QLA_D2_DiracPropagator     QLA_DiracPropagator;

#define QLA_elem_R QLA_D2_elem_R 
#define QLA_elem_C QLA_D2_elem_C 
#define QLA_elem_I QLA_D2_elem_I 
#define QLA_elem_H QLA_D2_elem_H 
#define QLA_elem_D QLA_D2_elem_D 
#define QLA_elem_J QLA_D2_elem_J 
#define QLA_elem_V QLA_D2_elem_V 
#define QLA_elem_P QLA_D2_elem_P 
#define QLA_elem_M QLA_D2_elem_M 

#elif ( QLA_Precision == 'Q' )

typedef QLA_Q2_ColorMatrix         QLA_ColorMatrix;
typedef QLA_Q2_ColorVector         QLA_ColorVector;
typedef QLA_Q2_HalfFermion         QLA_HalfFermion;
typedef QLA_Q2_SpinDiracFermion    QLA_SpinDiracFermion;
typedef QLA_Q2_DiracFermion        QLA_DiracFermion;
typedef QLA_Q2_DiracPropagator     QLA_DiracPropagator;

#define QLA_elem_R QLA_Q2_elem_R 
#define QLA_elem_C QLA_Q2_elem_C 
#define QLA_elem_I QLA_Q2_elem_I 
#define QLA_elem_H QLA_Q2_elem_H 
#define QLA_elem_D QLA_Q2_elem_D 
#define QLA_elem_J QLA_Q2_elem_J 
#define QLA_elem_V QLA_Q2_elem_V 
#define QLA_elem_P QLA_Q2_elem_P 
#define QLA_elem_M QLA_Q2_elem_M 

#endif

#elif ( QLA_Colors == 'N' )

/* These types specify precision but are generic with respect to color */

typedef QLA_FN_ColorMatrix         QLA_F_ColorMatrix;
typedef QLA_FN_ColorVector         QLA_F_ColorVector;
typedef QLA_FN_HalfFermion         QLA_F_HalfFermion;
typedef QLA_FN_SpinDiracFermion    QLA_F_SpinDiracFermion;
typedef QLA_FN_DiracFermion        QLA_F_DiracFermion;
typedef QLA_FN_DiracPropagator     QLA_F_DiracPropagator;

#define QLA_F_elem_R QLA_FN_elem_R 
#define QLA_F_elem_C QLA_FN_elem_C 
#define QLA_F_elem_I QLA_FN_elem_I 
#define QLA_F_elem_H QLA_FN_elem_H 
#define QLA_F_elem_D QLA_FN_elem_D 
#define QLA_F_elem_J QLA_FN_elem_J 
#define QLA_F_elem_V QLA_FN_elem_V 
#define QLA_F_elem_P QLA_FN_elem_P 
#define QLA_F_elem_M QLA_FN_elem_M 

typedef QLA_DN_ColorMatrix         QLA_D_ColorMatrix;
typedef QLA_DN_ColorVector         QLA_D_ColorVector;
typedef QLA_DN_HalfFermion         QLA_D_HalfFermion;
typedef QLA_DN_SpinDiracFermion    QLA_D_SpinDiracFermion;
typedef QLA_DN_DiracFermion        QLA_D_DiracFermion;
typedef QLA_DN_DiracPropagator     QLA_D_DiracPropagator;

#define QLA_D_elem_R QLA_DN_elem_R 
#define QLA_D_elem_C QLA_DN_elem_C 
#define QLA_D_elem_I QLA_DN_elem_I 
#define QLA_D_elem_H QLA_DN_elem_H 
#define QLA_D_elem_D QLA_DN_elem_D 
#define QLA_D_elem_J QLA_DN_elem_J 
#define QLA_D_elem_V QLA_DN_elem_V 
#define QLA_D_elem_P QLA_DN_elem_P 
#define QLA_D_elem_M QLA_DN_elem_M 

typedef QLA_QN_ColorMatrix         QLA_Q_ColorMatrix;
typedef QLA_QN_ColorVector         QLA_Q_ColorVector;
typedef QLA_QN_HalfFermion         QLA_Q_HalfFermion;
typedef QLA_QN_SpinDiracFermion    QLA_Q_SpinDiracFermion;
typedef QLA_QN_DiracFermion        QLA_Q_DiracFermion;
typedef QLA_QN_DiracPropagator     QLA_Q_DiracPropagator;

#define QLA_Q_elem_R QLA_QN_elem_R 
#define QLA_Q_elem_C QLA_QN_elem_C 
#define QLA_Q_elem_I QLA_QN_elem_I 
#define QLA_Q_elem_H QLA_QN_elem_H 
#define QLA_Q_elem_D QLA_QN_elem_D 
#define QLA_Q_elem_J QLA_QN_elem_J 
#define QLA_Q_elem_V QLA_QN_elem_V 
#define QLA_Q_elem_P QLA_QN_elem_P 
#define QLA_Q_elem_M QLA_QN_elem_M 

#if ( QLA_Precision == 'F' )

typedef QLA_FN_ColorMatrix         QLA_ColorMatrix;
typedef QLA_FN_ColorVector         QLA_ColorVector;
typedef QLA_FN_HalfFermion         QLA_HalfFermion;
typedef QLA_FN_SpinDiracFermion    QLA_SpinDiracFermion;
typedef QLA_FN_DiracFermion        QLA_DiracFermion;
typedef QLA_FN_DiracPropagator     QLA_DiracPropagator;

#define QLA_elem_R QLA_FN_elem_R 
#define QLA_elem_C QLA_FN_elem_C 
#define QLA_elem_I QLA_FN_elem_I 
#define QLA_elem_H QLA_FN_elem_H 
#define QLA_elem_D QLA_FN_elem_D 
#define QLA_elem_J QLA_FN_elem_J 
#define QLA_elem_V QLA_FN_elem_V 
#define QLA_elem_P QLA_FN_elem_P 
#define QLA_elem_M QLA_FN_elem_M 

#elif ( QLA_Precision == 'D' )

typedef QLA_DN_ColorMatrix         QLA_ColorMatrix;
typedef QLA_DN_ColorVector         QLA_ColorVector;
typedef QLA_DN_HalfFermion         QLA_HalfFermion;
typedef QLA_DN_SpinDiracFermion    QLA_SpinDiracFermion;
typedef QLA_DN_DiracFermion        QLA_DiracFermion;
typedef QLA_DN_DiracPropagator     QLA_DiracPropagator;

#define QLA_elem_R QLA_DN_elem_R 
#define QLA_elem_C QLA_DN_elem_C 
#define QLA_elem_I QLA_DN_elem_I 
#define QLA_elem_H QLA_DN_elem_H 
#define QLA_elem_D QLA_DN_elem_D 
#define QLA_elem_J QLA_DN_elem_J 
#define QLA_elem_V QLA_DN_elem_V 
#define QLA_elem_P QLA_DN_elem_P 
#define QLA_elem_M QLA_DN_elem_M 

#elif ( QLA_Precision == 'Q' )

typedef QLA_QN_ColorMatrix         QLA_ColorMatrix;
typedef QLA_QN_ColorVector         QLA_ColorVector;
typedef QLA_QN_HalfFermion         QLA_HalfFermion;
typedef QLA_QN_SpinDiracFermion    QLA_SpinDiracFermion;
typedef QLA_QN_DiracFermion        QLA_DiracFermion;
typedef QLA_QN_DiracPropagator     QLA_DiracPropagator;

#define QLA_elem_R QLA_QN_elem_R 
#define QLA_elem_C QLA_QN_elem_C 
#define QLA_elem_I QLA_QN_elem_I 
#define QLA_elem_H QLA_QN_elem_H 
#define QLA_elem_D QLA_QN_elem_D 
#define QLA_elem_J QLA_QN_elem_J 
#define QLA_elem_V QLA_QN_elem_V 
#define QLA_elem_P QLA_QN_elem_P 
#define QLA_elem_M QLA_QN_elem_M 

#endif

#endif /* if QLA_Colors == ?? */

#endif /* _QLA_TYPES_H */
