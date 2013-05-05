/**************** QLA_M_eq_expA_M.c ********************/

#include <stdio.h>
#include <qla_config.h>
#include <qla_types.h>
#include <qla_random.h>
#include <qla_cmath.h>
#include <math.h>
#include <complex.h>

#if QLA_Precision == 'F'
#  define QLAP(y) QLA_F ## _ ## y
#  define QLAPX(x,y) QLA_F ## x ## _ ## y
#  define EPS FLT_EPSILON
#  define fabsP fabsf
#  define sqrtP sqrtf
#  define acosP acosf
typedef float _Complex cmplx;
#else
#  define QLAP(y) QLA_D ## _ ## y
#  define QLAPX(x,y) QLA_D ## x ## _ ## y
#  define EPS DBL_EPSILON
#  define fabsP fabs
#  define sqrtP sqrt
#  define acosP acos
typedef double _Complex cmplx;
#endif

#if QLA_Colors == 2
# if QLA_Precision == 'F'
#  include <qla_f2.h>
# else
#  include <qla_d2.h>
# endif
# define QLAPC(x) QLAPX(2,x)
#elif QLA_Colors == 3
# if QLA_Precision == 'F'
#  include <qla_f3.h>
# else
#  include <qla_d3.h>
# endif
# define QLAPC(x) QLAPX(3,x)
#else
# if QLA_Precision == 'F'
#  include <qla_fn.h>
# else
#  include <qla_dn.h>
# endif
# define QLAPC(x) QLAPX(N,x)
#endif

#if QLA_Colors == 'N'
#  define QLAN(x,...) QLAPC(x)(nc, __VA_ARGS__)
#  define NCVAR nc,
#  define NCARG int nc,
#  define NC nc
#else
#  define QLAN(x,...) QLAPC(x)(__VA_ARGS__)
#  define NCVAR
#  define NCARG
#  define NC QLA_Colors
#endif
#define QLA3(x,...) QLAPX(3,x)(__VA_ARGS__)

static const double P[] = {
  9.99999999999999999910E-1,
  3.02994407707441961300E-2,
  1.26177193074810590878E-4,
};

static const double Q[] = {
  2.00000000000000000009E0,
  2.27265548208155028766E-1,
  2.52448340349684104192E-3,
  3.00198505138664455042E-6,
};

#define M_eq_d(x,d) {QLA_Complex zz; QLA_c_eq_r(zz,d); QLAN(M_eq_c, x, &zz);}
#define M_peq_d_times_M(x,d,a) {QLA_Real rr=(d); QLAN(M_peq_r_times_M, x, &rr, a);}

static double
maxev(NCARG QLAN(ColorMatrix,(*a)))
{
  // flops: 4*n*n  sqrt: 1
  double fnorm = 0;
  for(int i=0; i<NC; i++) {
    for(int j=0; j<NC; j++) {
      fnorm += QLA_norm2_c(QLA_elem_M(*a,i,j));
    }
  }
  return sqrt(fnorm);
}

static void
getfs(cmplx *f0, cmplx *f1, cmplx *f2,
      QLA_Real c0, QLA_Real c1)
{
  // flops: 133  div: 2  rdivc: 1  sqrt: 1  acos: 1  cexpi: 3
  cmplx h0, h1, h2, e2iu, emiu;
  QLA_Real c0m, t, u, w, u2, w2, cw, xi0, di;
  int sign=0;
  if(c0<0) { sign=1; c0=-c0; }
  QLA_Real sc1 = sqrtP(c1);
  QLA_Real sc13 = 0.57735026918962576450*sc1;  // sqrt(1/3)
  c0m = 2*sc13*sc13*sc13;
  t = acosP(c0/c0m);
  QLA_Complex sc = QLAP(cexpi)((1./3.)*t);
  u = sc13 * QLA_real(sc);
  w = sc1  * QLA_imag(sc);
  u2 = u*u;
  w2 = w*w;
  QLA_Complex sc2 = QLAP(cexpi)(w);
  cw = QLA_real(sc2);
  if(w==0) xi0 = 1;
  else xi0 = QLA_imag(sc2)/w;
  QLA_Complex qemiu = QLAP(cexpi)(-u);
  QLA_c99_eq_c(emiu, qemiu);
  //e2iu = 1/(emiu*emiu);
  e2iu = conj(emiu*emiu);
  h0 = (u2-w2)*e2iu + emiu*(8*u2*cw+2*I*u*(3*u2+w2)*xi0);
  h1 = 2*u*e2iu - emiu*(2*u*cw-I*(3*u2-w2)*xi0);
  h2 = e2iu - emiu*(cw+3*I*u*xi0);
  di = 1/(9*u2-w2);
  *f0 = di*h0;
  *f1 = di*h1;
  *f2 = di*h2;
  if(sign) {
    *f0 = conj(*f0);
    *f1 = -conj(*f1);
    *f2 = conj(*f2);
  }
}

static void
QLA_expA_3x3(QLA3(ColorMatrix,(*e)), QLA3(ColorMatrix,(*iq)))
{
  // flops: 410  cexpi: 1
  cmplx f0, f1, f2;
  QLA_Complex f, a0, a1, a2, b0, b1, b2;
  QLA_Complex iq00, iq01, iq02, iq10, iq11, iq12, iq20, iq21, iq22;
  QLA_Complex mqq00, mqq01, mqq02, mqq10, mqq11, mqq12, mqq20, mqq21, mqq22;
  QLA_Real c0, c1;

  QLA_c_eq_c(iq00, QLA_elem_M(*iq,0,0));
  QLA_c_eq_c(iq01, QLA_elem_M(*iq,0,1));
  QLA_c_eq_c(iq02, QLA_elem_M(*iq,0,2));
  QLA_c_eq_c(iq10, QLA_elem_M(*iq,1,0));
  QLA_c_eq_c(iq11, QLA_elem_M(*iq,1,1));
  QLA_c_eq_c(iq12, QLA_elem_M(*iq,1,2));
  QLA_c_eq_c(iq20, QLA_elem_M(*iq,2,0));
  QLA_c_eq_c(iq21, QLA_elem_M(*iq,2,1));
  QLA_c_eq_c(iq22, QLA_elem_M(*iq,2,2));

  QLA_Real tr = QLA_imag(iq00) + QLA_imag(iq11) + QLA_imag(iq22);
  QLA_Real s = (1./3.)*tr;
  QLA_c_eq_r_plus_ir(iq00, QLA_real(iq00), QLA_imag(iq00)-s);
  QLA_c_eq_r_plus_ir(iq11, QLA_real(iq11), QLA_imag(iq11)-s);
  QLA_c_eq_r_plus_ir(iq22, QLA_real(iq22), QLA_imag(iq22)-s);
  f = QLAP(cexpi)(s);

#define mul(i,j) \
  QLA_c_eq_c_times_c(mqq##i##j, iq##i##0, iq##0##j); \
  QLA_c_peq_c_times_c(mqq##i##j, iq##i##1, iq##1##j); \
  QLA_c_peq_c_times_c(mqq##i##j, iq##i##2, iq##2##j);
  mul(0,0);
  mul(0,1);
  mul(0,2);
  mul(1,0);
  mul(1,1);
  mul(1,2);
  mul(2,0);
  mul(2,1);
  mul(2,2);
#undef mul

  QLA_Real r = QLA_real(mqq00) + QLA_real(mqq11) + QLA_real(mqq22);
  c1 = -0.5 * r;

  QLA_Complex det0, det1, det2;
  QLA_Real det;
  QLA_c_eq_c_times_c (det2, iq00, iq11);
  QLA_c_meq_c_times_c(det2, iq01, iq10);
  QLA_c_eq_c_times_c (det1, iq02, iq10);
  QLA_c_meq_c_times_c(det1, iq00, iq12);
  QLA_c_eq_c_times_c (det0, iq01, iq12);
  QLA_c_meq_c_times_c(det0, iq02, iq11);
  QLA_r_eq_Im_c_times_c (det, det2, iq22);
  QLA_r_peq_Im_c_times_c(det, det1, iq21);
  QLA_r_peq_Im_c_times_c(det, det0, iq20);
  c0 = -det;

  getfs(&f0, &f1, &f2, c0, c1);
  QLA_c_eq_r_plus_ir(b0, creal(f0), cimag(f0));
  QLA_c_eq_r_plus_ir(b1, cimag(f1), -creal(f1));
  QLA_c_eq_r_plus_ir(b2, -creal(f2), -cimag(f2));
  QLA_c_eq_c_times_c(a0, f, b0);
  QLA_c_eq_c_times_c(a1, f, b1);
  QLA_c_eq_c_times_c(a2, f, b2);

#define mul(i,j) \
  QLA_c_eq_c_times_c(QLA_elem_M(*e,i,j), a2, mqq##i##j); \
  QLA_c_peq_c_times_c(QLA_elem_M(*e,i,j), a1, iq##i##j);
  mul(0,0);
  mul(0,1);
  mul(0,2);
  mul(1,0);
  mul(1,1);
  mul(1,2);
  mul(2,0);
  mul(2,1);
  mul(2,2);
#undef mul
  QLA_c_peq_c(QLA_elem_M(*e,0,0), a0);
  QLA_c_peq_c(QLA_elem_M(*e,1,1), a0);
  QLA_c_peq_c(QLA_elem_M(*e,2,2), a0);
}

void
QLAPC(M_eq_expA_M)(NCARG QLAN(ColorMatrix,(*restrict r)), QLAN(ColorMatrix,(*restrict a)))
{
#ifdef HAVE_XLC
#pragma disjoint(*r, *a)
  __alignx(16,r);
  __alignx(16,a);
#endif

  if(NC==1) {
    // flops: 0  cexpi: 1
    QLA_elem_M(*r,0,0) = QLAP(cexpi)(QLA_imag(QLA_elem_M(*a,0,0)));
    return;
  }
  if(NC==2) {
    // flops: 47  div: 1  sqrt: 1  cexpi: 2
    QLA_Complex a00, a01, a10, a11, tr, s;
    QLA_Real det;
    QLA_c_eq_c(a00, QLA_elem_M(*a,0,0));
    QLA_c_eq_c(a01, QLA_elem_M(*a,0,1));
    QLA_c_eq_c(a10, QLA_elem_M(*a,1,0));
    QLA_c_eq_c(a11, QLA_elem_M(*a,1,1));
    // s = 0.5*tr;  remove trace from a;  t = sqrt(det)
    QLA_c_eq_c_plus_c(tr, a00, a11);
    QLA_c_eq_r_times_c(s, 0.5, tr);
    QLA_c_meq_c(a00, s);
    QLA_c_meq_c(a11, s);
    QLA_r_eq_Re_c_times_c (det, a00, a11);
    QLA_r_meq_Re_c_times_c(det, a01, a10);
    //QLA_Complex t = QLAP(csqrt)(&mdet);
    QLA_Real t = sqrtP(fabsP(det));
    // c0 = exp(s) cos(t);  c1 = exp(s) sin(t)/t
    QLA_Real st, cs;
    if(t==0) {
      st = 1;
      cs = 1;
    } else {
      QLA_Complex sc = QLAP(cexpi)(t);
      st = QLA_imag(sc)/t;
      cs = QLA_real(sc);
    }
    QLA_Complex c0, c1, es;
    //es = QLAP(cexp)(&s);
    es = QLAP(cexpi)(QLA_imag(s));
    QLA_c_eq_c_times_r(c0, es, cs);
    QLA_c_eq_c_times_r(c1, es, st);
    // c0 + c1*a
    QLA_c_eq_c_times_c_plus_c(QLA_elem_M(*r,0,0), c1, a00, c0);
    QLA_c_eq_c_times_c(QLA_elem_M(*r,0,1), c1, a01);
    QLA_c_eq_c_times_c(QLA_elem_M(*r,1,0), c1, a10);
    QLA_c_eq_c_times_c_plus_c(QLA_elem_M(*r,1,1), c1, a11, c0);
    return;
  }
  if(NC==3) {
    // flops: 543  div: 2  rdivc: 1  sqrt: 1  acos: 1  cexpi: 4
    QLA_expA_3x3((QLA3(ColorMatrix,(*))) r, (QLA3(ColorMatrix,(*))) a);
    return;
  }

  // flops: 4*n*n+1 div: 1 sqrt: 1 MmM: 1 rtM: 1 prtM: 6 MtM: 4+s+b MinvM: 1
  // flops: (44+8(s+b))n3 + 29.5n2 + 2.5n + 3
  /* get the integer scale */
  double ds = maxev(NCVAR a);
  //printf("ds = %i\n", ds);
  if(ds == 0) {
    M_eq_d(r, 1);
    return;
  }
  unsigned int s = (unsigned int) ceil(2*ds);
  if(s > 1024) s = 1024;
  ds = (double) s;

  QLAN(ColorMatrix,bs);
  QLAN(ColorMatrix,bs2);
  QLAN(ColorMatrix,bs4);
  QLAN(ColorMatrix,bs6);
  QLAN(ColorMatrix,pb);
  QLAN(ColorMatrix,qb);
  QLAN(ColorMatrix,(*va0));
  QLAN(ColorMatrix,(*va1));
  QLAN(ColorMatrix,(*vb0));
  QLAN(ColorMatrix,(*vb1));

  QLA_Real dsi = 1.0/ds;
  QLAN(M_eq_r_times_M, &bs, &dsi, a);
  M_eq_d(&pb, P[0]);
  M_eq_d(&qb, Q[0]);
  QLAN(M_eq_M_times_M, &bs2, &bs, &bs);
  M_peq_d_times_M(&pb, P[1], &bs2);
  M_peq_d_times_M(&qb, Q[1], &bs2);
  QLAN(M_eq_M_times_M, &bs4, &bs2, &bs2);
  M_peq_d_times_M(&pb, P[2], &bs4);
  M_peq_d_times_M(&qb, Q[2], &bs4);
  QLAN(M_eq_M_times_M, &bs6, &bs4, &bs2);
  M_peq_d_times_M(&qb, Q[3], &bs6);
  QLAN(M_eq_M_times_M, &bs6, &bs, &pb);
  //QLAN(M_meq_M, &qb, &bs6);
  //QLAN(M_eq_inverse_M, &pb, &qb);
  //QLAN(M_eq_M_times_M, &qb, &bs6, &pb);
  QLAN(M_eq_M_minus_M, &pb, &qb, &bs6);
  QLAN(M_eq_M_inverse_M, &qb, &pb, &bs6);
  M_eq_d(&pb, 1);
  M_peq_d_times_M(&pb, 2, &qb);

  /* construct the full result a = exp(b) */
  if (s == 1) {
    QLAN(M_eq_M, r, &pb);
    return;
  }

  va0 = &bs;
  va1 = &bs2;
  vb0 = &pb;
  vb1 = &bs6;
  //QLAN(M_eq_M, vb0, &bs2);
  M_eq_d(va0, 1);
  for (; s > 0; s >>= 1) {
    if (s & 1) {
      QLAN(M_eq_M_times_M, va1, va0, vb0);
      void *tmp = va1; va1 = va0; va0 = tmp;
    }
    if (s > 0) {
      QLAN(M_eq_M_times_M, vb1, vb0, vb0);
      void *tmp = vb1; vb1 = vb0; vb0 = tmp;
    }
  }
  QLAN(M_eq_M, r, va0);
}
