/**************** QLA_M_eq_exp_M.c ********************/

#include <stdio.h>
#include <qla_config.h>
#include <qla_types.h>
#include <qla_random.h>
#include <qla_cmath.h>
#include <math.h>

#if QLA_Precision == 'F'
#  define QLAP(y) QLA_F ## _ ## y
#  define QLAPX(x,y) QLA_F ## x ## _ ## y
#else
#  define QLAP(y) QLA_D ## _ ## y
#  define QLAPX(x,y) QLA_D ## x ## _ ## y
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
  double cs[NC], rmax=0;
  for(int j=0; j<NC; j++) cs[j] = 0;
  for(int i=0; i<NC; i++) {
    double rs = 0;
    for(int j=0; j<NC; j++) {
      double x = QLA_norm2_c(QLA_elem_M(*a,i,j));
      rs += x;
      cs[j] += x;
    }
    if(rs>rmax) {
      //QLA_Complex z = QLA_elem_M(*a,i,j);
      //printf("%i %i  %g %g\n", i, j, QLA_real(*z), QLA_imag(*z));
      rmax = rs;
    }
  }
  for(int j=1; j<NC; j++) if(cs[j]>cs[0]) cs[0] = cs[j];
  if(cs[0]<rmax) rmax = cs[0];
  return sqrt(NC*rmax);
}

void
QLAPC(M_eq_exp_M)(NCARG QLAN(ColorMatrix,(*restrict r)), QLAN(ColorMatrix,(*restrict a)))
{
#ifdef HAVE_XLC
#pragma disjoint(*r, *a)
  __alignx(16,r);
  __alignx(16,a);
#endif

  if(NC==1) {
    QLA_elem_M(*r,0,0) = QLAP(cexp)(&QLA_elem_M(*a,0,0));
    return;
  }
  if(NC==2) {
    QLA_Complex tr, det;
    QLA_c_eq_c_plus_c(tr, QLA_elem_M(*a,0,0), QLA_elem_M(*a,1,1));
    QLA_c_eq_c_times_c (det, QLA_elem_M(*a,0,0), QLA_elem_M(*a,1,1));
    QLA_c_meq_c_times_c(det, QLA_elem_M(*a,0,1), QLA_elem_M(*a,1,0));
    // s = 0.5*tr;  t = sqrt(s^2 - det)
    QLA_Complex s, s2;
    QLA_c_eq_r_times_c(s, 0.5, tr);
    QLA_c_eq_c_times_c(s2, s, s);
    QLA_c_meq_c(s2, det);
    QLA_Complex t = QLAP(csqrt)(&s2);
    // c0 = exp(s)[cosh(t) - s*sinh(t)/t];  c1 = exp(s) sinh(t)/t
    QLA_Complex sh, st, ch;
    if(QLA_real(t)==0 && QLA_imag(t)==0) {
      QLA_c_eq_r(sh, 0);
      QLA_c_eq_r(st, 1);
      QLA_c_eq_r(ch, 1);
    } else {
      sh = QLAP(csinh)(&t);
      QLA_c_eq_c_div_c(st, sh, t);
      ch = QLAP(ccosh)(&t);
    }
    QLA_Complex c0, c1, es;
    es = QLAP(cexp)(&s);
    QLA_c_eq_c_times_c(c1, es, st);
    QLA_c_meq_c_times_c(ch, s, st);
    QLA_c_eq_c_times_c(c0, es, ch);
    // c0 + c1*a
    QLA_c_eq_c_times_c_plus_c(QLA_elem_M(*r,0,0), c1, QLA_elem_M(*a,0,0), c0);
    QLA_c_eq_c_times_c(QLA_elem_M(*r,0,1), c1, QLA_elem_M(*a,0,1));
    QLA_c_eq_c_times_c(QLA_elem_M(*r,1,0), c1, QLA_elem_M(*a,1,0));
    QLA_c_eq_c_times_c_plus_c(QLA_elem_M(*r,1,1), c1, QLA_elem_M(*a,1,1), c0);
    return;
  }

  /* get the integer scale */
  double ds = 2 * maxev(NCVAR a);
  unsigned int s = (unsigned int)(ceil(ds));
  //printf("s = %i\n", s);
  if (s == 0) {
    M_eq_d(r, 1);
    return;
  }
  if (s > 1024) s = 1024;
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
  QLAN(M_meq_M, &qb, &bs6);
  QLAN(M_eq_inverse_M, &pb, &qb);
  QLAN(M_eq_M_times_M, &qb, &bs6, &pb);
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
