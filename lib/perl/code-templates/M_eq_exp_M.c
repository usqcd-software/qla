/**************** QLA_M_eq_exp_M.c ********************/

#include <stdio.h>
#include <qla_config.h>
#include <qla_types.h>
#include <qla_random.h>
#include <qla_cmath.h>
#include <math.h>
#include <complex.h>

#if (QLA_Colors == 3) || (QLA_Colors == 'N')
//#define OPT_NC3
#endif

#if QLA_Precision == 'F'
#  define QLAP(y) QLA_F ## _ ## y
#  define QLAPX(x,y) QLA_F ## x ## _ ## y
typedef float _Complex cmplx;
#else
#  define QLAP(y) QLA_D ## _ ## y
#  define QLAPX(x,y) QLA_D ## x ## _ ## y
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

#ifdef OPT_NC3
static void
safedivC(QLA_Complex *r, QLA_Complex *a, QLA_Complex *b, QLA_Real z)
{
  QLA_Real d = QLA_norm2_c(*b);
  if(d==0) {
    QLA_c_eq_r(*r, z);
  } else {
    QLA_Real di = 1/d;
    QLA_c_eq_c_times_ca(*r, *a, *b);
    QLA_c_eq_r_times_c(*r, di, *r);
  }
}

static QLA_Complex
getfxy(QLA_Complex s, QLA_Complex d)
{
  QLA_Complex s2, d2, es, sh, shc, r;
  QLA_c_eq_r_times_c(d2, 0.5, d);
  QLA_c_eq_r_times_c(s2, 0.5, s);
  sh = QLAP(csinh)(&d2);
  es = QLAP(cexp)(&s2);
  safedivC(&shc, &sh, &d2, 1);
  QLA_c_eq_c_times_c(r, es, shc);
  return r;
}

static void
getfs(QLA_Complex *f0, QLA_Complex *f1, QLA_Complex *f2,
      QLA_Complex *pp2, QLA_Complex *det)
{
  // flops: 202  rdivc: 1  cdivc: 2  csqrt: 1  cexp: 2  cpow: 1  csincos: 1
  // c0 = det(Q) = -2q; c1 = 0.5*TrQ^2 = -3*p; u = q0/2; w = (q1-q2)/2
  // s2 = 0.5*(s1^2-p2) = -0.5*p2
  // solve: x^3 + s2 x - det = 0
  QLA_Complex p, q, p2, q2, t, d, w0, w, pw0, e0, e1, e2;
  QLA_c_eq_r_times_c(p, -1./6., *pp2);
  QLA_c_eq_r_times_c(q, -0.5, *det);
  QLA_c_eq_c_times_c(p2, p, p);
  QLA_c_eq_c_times_c(q2, q, q);
  QLA_c_eq_c_times_c_plus_c(d, p, p2, q2);
  t = QLAP(csqrt)(&d);
  QLA_Real ts;
  QLA_r_eq_Re_ca_times_c(ts, q, t);
  if(ts>=0) {
    QLA_c_peq_c(q, t);
  } else {
    QLA_c_meq_c(q, t);
  }
  w0 = QLAP(cpow)(&q, 1./3.);
  QLA_c_eq_r_plus_ir(w, -0.5, 0.86602540378443864676);  // -0.5+i*sqrt(3)/2
  safedivC(&pw0, &p, &w0, 0);
  QLA_c_eq_c_minus_c(e0, pw0, w0);
  QLA_c_eq_ca_times_c(e1, w, pw0);
  QLA_c_meq_c_times_c(e1, w, w0);
  QLA_c_eq_c_times_c(e2, w, pw0);
  QLA_c_meq_ca_times_c(e2, w, w0);
  QLA_Complex s01, s02, d10, d20, d21, f10, f20, f2010, ff0;
  QLA_c_eq_c_plus_c(s01, e0, e1);
  QLA_c_eq_c_plus_c(s02, e0, e2);
  QLA_c_eq_c_minus_c(d10, e1, e0);
  QLA_c_eq_c_minus_c(d20, e2, e0);
  QLA_c_eq_c_minus_c(d21, e2, e1);
  f10 = getfxy(s01, d10);
  f20 = getfxy(s02, d20);
  QLA_c_eq_c_minus_c(f2010, f20, f10);
  safedivC(f2, &f2010, &d21, 0);
  QLA_c_eqm_c_times_c_minus_c(*f1, s01, *f2, f10);
  ff0 = QLAP(cexp)(&e0);
  QLA_c_eqm_c_times_c_minus_c(t, e1, *f2, f10);
  QLA_c_eqm_c_times_c_minus_c(*f0, e0, t, ff0);
}

static void
matexp(QLA3(ColorMatrix,(*e)), QLA3(ColorMatrix,(*iq)))
{
  // flops: 430  cexp: 1
  QLA_Complex f0, f1, f2;
  QLA_Complex tr, s, f, p2, a0, a1, a2;
  QLA_Complex iq00, iq01, iq02, iq10, iq11, iq12, iq20, iq21, iq22;
  QLA_Complex mqq00, mqq01, mqq02, mqq10, mqq11, mqq12, mqq20, mqq21, mqq22;

  QLA_c_eq_c(iq00, QLA_elem_M(*iq,0,0));
  QLA_c_eq_c(iq01, QLA_elem_M(*iq,0,1));
  QLA_c_eq_c(iq02, QLA_elem_M(*iq,0,2));
  QLA_c_eq_c(iq10, QLA_elem_M(*iq,1,0));
  QLA_c_eq_c(iq11, QLA_elem_M(*iq,1,1));
  QLA_c_eq_c(iq12, QLA_elem_M(*iq,1,2));
  QLA_c_eq_c(iq20, QLA_elem_M(*iq,2,0));
  QLA_c_eq_c(iq21, QLA_elem_M(*iq,2,1));
  QLA_c_eq_c(iq22, QLA_elem_M(*iq,2,2));

  QLA_c_eq_c_plus_c(tr, iq00, iq11);
  QLA_c_peq_c(tr, iq22);
  QLA_c_eq_r_times_c(s, (1./3.), tr);
  QLA_c_meq_c(iq00, s);
  QLA_c_meq_c(iq11, s);
  QLA_c_meq_c(iq22, s);
  f = QLAP(cexp)(&s);

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

  QLA_c_eq_c_plus_c(p2, mqq00, mqq11);
  QLA_c_peq_c(p2, mqq22);

  QLA_Complex det0, det1, det2, det;
  QLA_c_eq_c_times_c (det2, iq00, iq11);
  QLA_c_meq_c_times_c(det2, iq01, iq10);
  QLA_c_eq_c_times_c (det1, iq02, iq10);
  QLA_c_meq_c_times_c(det1, iq00, iq12);
  QLA_c_eq_c_times_c (det0, iq01, iq12);
  QLA_c_meq_c_times_c(det0, iq02, iq11);
  QLA_c_eq_c_times_c (det, det2, iq22);
  QLA_c_peq_c_times_c(det, det1, iq21);
  QLA_c_peq_c_times_c(det, det0, iq20);

  getfs(&f0, &f1, &f2, &p2, &det);
  QLA_c_eq_c_times_c(a0, f, f0);
  QLA_c_eq_c_times_c(a1, f, f1);
  QLA_c_eq_c_times_c(a2, f, f2);

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
#endif

void
QLAPC(M_eq_exp_M)(NCARG QLAN(ColorMatrix,(*restrict r)), QLAN(ColorMatrix,(*restrict a)))
{
#ifdef HAVE_XLC
#pragma disjoint(*r, *a)
  __alignx(16,r);
  __alignx(16,a);
#endif

  if(NC==1) {
    // flops: 0  cexp: 1
    QLA_elem_M(*r,0,0) = QLAP(cexp)(&QLA_elem_M(*a,0,0));
    return;
  }
  if(NC==2) {
    // flops: 62  cdivc: 1  csqrt: 1  cexp: 1  csinhcosh: 1
    QLA_Complex a00, a01, a10, a11, tr, s, mdet;
    QLA_c_eq_c(a00, QLA_elem_M(*a,0,0));
    QLA_c_eq_c(a01, QLA_elem_M(*a,0,1));
    QLA_c_eq_c(a10, QLA_elem_M(*a,1,0));
    QLA_c_eq_c(a11, QLA_elem_M(*a,1,1));
    // s = 0.5*tr;  remove trace from a;  t = sqrt(-det)
    QLA_c_eq_c_plus_c(tr, a00, a11);
    QLA_c_eq_r_times_c(s, 0.5, tr);
    QLA_c_meq_c(a00, s);
    QLA_c_meq_c(a11, s);
    QLA_c_eq_c_times_c (mdet, a01, a10);
    QLA_c_meq_c_times_c(mdet, a00, a11);
    QLA_Complex t = QLAP(csqrt)(&mdet);
    // c0 = exp(s) cosh(t);  c1 = exp(s) sinh(t)/t
    QLA_Complex st, ch;
    if(QLA_real(t)==0 && QLA_imag(t)==0) {
      QLA_c_eq_r(st, 1);
      QLA_c_eq_r(ch, 1);
    } else {
      QLA_Complex sh; QLAP(csinhcosh)(&t, &sh, &ch);
      QLA_c_eq_c_div_c(st, sh, t);
    }
    QLA_Complex c0, c1, es;
    es = QLAP(cexp)(&s);
    QLA_c_eq_c_times_c(c0, es, ch);
    QLA_c_eq_c_times_c(c1, es, st);
    // c0 + c1*a
    QLA_c_eq_c_times_c_plus_c(QLA_elem_M(*r,0,0), c1, a00, c0);
    QLA_c_eq_c_times_c(QLA_elem_M(*r,0,1), c1, a01);
    QLA_c_eq_c_times_c(QLA_elem_M(*r,1,0), c1, a10);
    QLA_c_eq_c_times_c_plus_c(QLA_elem_M(*r,1,1), c1, a11, c0);
    return;
  }
#ifdef OPT_NC3
  if(NC==3) {
    // flops: 632  rdivc: 1  cdivc: 2  csqrt: 1  cexp: 3  cpow: 1  csincos: 1
    matexp((QLA3(ColorMatrix,(*))) r, (QLA3(ColorMatrix,(*))) a);
    return;
  }
#endif

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
