#ifndef _COMPARE_H
#define _COMPARE_H
#define MAX 10

#include <float.h>

/* Allowed discrepancy */
#define NABS 10
#define NREL 10
#if QLA_Precision == 'F'
#define TOLABS NABS*FLT_EPSILON
#define TOLREL NREL*FLT_EPSILON
#define PREC "F"
#elif QLA_Precision == 'D'
#define TOLABS NABS*DBL_EPSILON
#define TOLREL NREL*DBL_EPSILON
#define PREC "D"
#else
#define TOLABS NABS*LDBL_EPSILON
#define TOLREL NREL*LDBL_EPSILON
#define PREC "Q"
#endif

int checkeqsngII(QLA_Int *ia, QLA_Int *ib, char name[]);
int checkeqsngRR(QLA_Real *sa, QLA_Real *sb, char name[]);
int checkeqsngFRR(QLA_F_Real *sa, QLA_F_Real *sb, char name[]);
int checkeqsngDRR(QLA_D_Real *sa, QLA_D_Real *sb, char name[]);
int checkeqsngQRR(QLA_Q_Real *sa, QLA_Q_Real *sb, char name[]);
int checkeqsngCC(QLA_Complex *sa, QLA_Complex *sb, char name[]);
int checkeqsngDCC(QLA_D_Complex *sa, QLA_D_Complex *sb, char name[]);
int checkeqsngQCC(QLA_Q_Complex *sa, QLA_Q_Complex *sb, char name[]);
int checkeqsngFCC(QLA_F_Complex *sa, QLA_F_Complex *sb, char name[]);
int checkeqsngCRR(QLA_Complex *sa, QLA_Real *sbre, QLA_Real *sbim, char name[]);
int checkeqsngHH(QLA_HalfFermion *sa, QLA_HalfFermion *sb, char name[]);
int checkeqsngFHH(QLA_F_HalfFermion *sa, QLA_F_HalfFermion *sb, char name[]);
int checkeqsngDHH(QLA_D_HalfFermion *sa, QLA_D_HalfFermion *sb, char name[]);
int checkeqsngQHH(QLA_Q_HalfFermion *sa, QLA_Q_HalfFermion *sb, char name[]);
int checkeqsngDD(QLA_DiracFermion *sa, QLA_DiracFermion *sb, char name[]);
int checkeqsngFDD(QLA_F_DiracFermion *sa, QLA_F_DiracFermion *sb, char name[]);
int checkeqsngDDD(QLA_D_DiracFermion *sa, QLA_D_DiracFermion *sb, char name[]);
int checkeqsngQDD(QLA_Q_DiracFermion *sa, QLA_Q_DiracFermion *sb, char name[]);
int checkeqsngVV(QLA_ColorVector *sa, QLA_ColorVector *sb, char name[]);
int checkeqsngFVV(QLA_F_ColorVector *sa, QLA_F_ColorVector *sb, char name[]);
int checkeqsngDVV(QLA_D_ColorVector *sa, QLA_D_ColorVector *sb, char name[]);
int checkeqsngQVV(QLA_Q_ColorVector *sa, QLA_Q_ColorVector *sb, char name[]);
int checkeqsngMM(QLA_ColorMatrix *sa, QLA_ColorMatrix *sb, char name[]);
int checkeqsngFMM(QLA_F_ColorMatrix *sa, QLA_F_ColorMatrix *sb, char name[]);
int checkeqsngDMM(QLA_D_ColorMatrix *sa, QLA_D_ColorMatrix *sb, char name[]);
int checkeqsngQMM(QLA_Q_ColorMatrix *sa, QLA_Q_ColorMatrix *sb, char name[]);
int checkeqsngPP(QLA_DiracPropagator *sa, QLA_DiracPropagator *sb, char name[]);
int checkeqsngFPP(QLA_F_DiracPropagator *sa, QLA_F_DiracPropagator *sb, char name[]);
int checkeqsngDPP(QLA_D_DiracPropagator *sa, QLA_D_DiracPropagator *sb, char name[]);
int checkeqsngQPP(QLA_Q_DiracPropagator *sa, QLA_Q_DiracPropagator *sb, char name[]);
int checkeqsngSS(QLA_RandomState *sa, QLA_RandomState *sb, char name[]);

int checkeqidxII(QLA_Int sa[], QLA_Int sb[], char name[]);
int checkeqidxRR(QLA_Real a[], QLA_Real b[], char name[]);
int checkeqidxFRR(QLA_F_Real a[], QLA_F_Real b[], char name[]);
int checkeqidxDRR(QLA_D_Real a[], QLA_D_Real b[], char name[]);
int checkeqidxQRR(QLA_Q_Real a[], QLA_Q_Real b[], char name[]);
int checkeqidxCC(QLA_Complex a[], QLA_Complex b[], char name[]);
int checkeqidxFCC(QLA_F_Complex a[], QLA_F_Complex b[], char name[]);
int checkeqidxDCC(QLA_D_Complex a[], QLA_D_Complex b[], char name[]);
int checkeqidxQCC(QLA_Q_Complex a[], QLA_Q_Complex b[], char name[]);
int checkeqidxHH(QLA_HalfFermion a[], QLA_HalfFermion b[], char name[]);
int checkeqidxFHH(QLA_F_HalfFermion a[], QLA_F_HalfFermion b[], char name[]);
int checkeqidxDHH(QLA_D_HalfFermion a[], QLA_D_HalfFermion b[], char name[]);
int checkeqidxQHH(QLA_Q_HalfFermion a[], QLA_Q_HalfFermion b[], char name[]);
int checkeqidxDD(QLA_DiracFermion a[], QLA_DiracFermion b[], char name[]);
int checkeqidxFDD(QLA_F_DiracFermion a[], QLA_F_DiracFermion b[], char name[]);
int checkeqidxDDD(QLA_D_DiracFermion a[], QLA_D_DiracFermion b[], char name[]);
int checkeqidxQDD(QLA_Q_DiracFermion a[], QLA_Q_DiracFermion b[], char name[]);
int checkeqidxVV(QLA_ColorVector a[], QLA_ColorVector b[], char name[]);
int checkeqidxFVV(QLA_F_ColorVector a[], QLA_F_ColorVector b[], char name[]);
int checkeqidxDVV(QLA_D_ColorVector a[], QLA_D_ColorVector b[], char name[]);
int checkeqidxQVV(QLA_Q_ColorVector a[], QLA_Q_ColorVector b[], char name[]);
int checkeqidxMM(QLA_ColorMatrix a[], QLA_ColorMatrix b[], char name[]);
int checkeqidxFMM(QLA_F_ColorMatrix a[], QLA_F_ColorMatrix b[], char name[]);
int checkeqidxDMM(QLA_D_ColorMatrix a[], QLA_D_ColorMatrix b[], char name[]);
int checkeqidxPP(QLA_DiracPropagator a[], QLA_DiracPropagator b[], char name[]);
int checkeqidxFPP(QLA_F_DiracPropagator a[], QLA_F_DiracPropagator b[], char name[]);
int checkeqidxDPP(QLA_D_DiracPropagator a[], QLA_D_DiracPropagator b[], char name[]);
int checkeqidxQPP(QLA_Q_DiracPropagator a[], QLA_Q_DiracPropagator b[], char name[]);
int checkeqidxSS(QLA_RandomState a[], QLA_RandomState b[], char name[]);

#endif /* _COMPARE_H */
