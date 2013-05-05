/**************** QLA_M_eq_sqrt_M.c ********************/

#include <stdio.h>
#include <qla_config.h>
#include <qla_types.h>
#include <qla_random.h>
#include <qla_cmath.h>
#include <math.h>
#include <float.h>

#if QLA_Precision == 'F'
#  define QLAP(y) QLA_F ## _ ## y
#  define QLAPX(x,y) QLA_F ## x ## _ ## y
#  define EPS FLT_EPSILON
#else
#  define QLAP(y) QLA_D ## _ ## y
#  define QLAPX(x,y) QLA_D ## x ## _ ## y
#  define EPS DBL_EPSILON
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

#define M_eq_d(x,d) {QLA_Complex zz; QLA_c_eq_r(zz,d); QLAN(M_eq_c, x, &zz);}
#define M_eq_d_times_M(x,d,a) {QLA_Real rr=(d); QLAN(M_eq_r_times_M, x, &rr, a);}
#define M_peq_d_times_M(x,d,a) {QLA_Real rr=(d); QLAN(M_peq_r_times_M, x, &rr, a);}

static double
maxev2(NCARG QLAN(ColorMatrix,(*a)))
{
  // flops: 4*n*n
  double fnorm = 0;
  for(int i=0; i<NC; i++) {
    for(int j=0; j<NC; j++) {
      fnorm += QLA_norm2_c(QLA_elem_M(*a,i,j));
    }
  }
  return fnorm;
}

void
QLAPC(M_eq_sqrt_M)(NCARG QLAN(ColorMatrix,(*restrict r)), QLAN(ColorMatrix,(*restrict a)))
{
#ifdef HAVE_XLC
#pragma disjoint(*r, *a)
  __alignx(16,r);
  __alignx(16,a);
#endif

  if(NC==1) {
    // flops: 0  csqrt: 1
    QLA_elem_M(*r,0,0) = QLAP(csqrt)(&QLA_elem_M(*a,0,0));
    return;
  }
  if(NC==2) {
    // flops: 73  rdivc: 1  cdivc: 1  csqrt: 3
    QLA_Complex a00, a01, a10, a11, tr, s, det, d;
    QLA_c_eq_c(a00, QLA_elem_M(*a,0,0));
    QLA_c_eq_c(a01, QLA_elem_M(*a,0,1));
    QLA_c_eq_c(a10, QLA_elem_M(*a,1,0));
    QLA_c_eq_c(a11, QLA_elem_M(*a,1,1));
    QLA_c_eq_c_plus_c(tr, a00, a11);
    QLA_c_eq_r_times_c(s, 0.5, tr);
    QLA_c_eq_c_times_c (det, a00, a11);
    QLA_c_meq_c_times_c(det, a01, a10);
    // lambda = 0.5*(tr \pm sqrt(tr^2 - 4*det) ) = s \pm sqrt(s^2 - det)
    QLA_c_eq_c_times_c(d, s, s);
    QLA_c_meq_c(d, det);
    QLA_Complex l0, l1, sd = QLAP(csqrt)(&d);
    QLA_Real ts;
    QLA_r_eq_Re_ca_times_c(ts, s, sd);
    if(ts>=0) {
      QLA_c_eq_c_plus_c(l1, s, sd);
    } else {
      QLA_c_eq_c_minus_c(l1, s, sd);
    }
    QLA_c_eq_c_div_c(l0, det, l1);
    QLA_Complex sl0 = QLAP(csqrt)(&l0);
    QLA_Complex sl1 = QLAP(csqrt)(&l1);
    QLA_Complex ss, ps, c0, c1;
    QLA_c_eq_c_plus_c(ss, sl0, sl1);
    QLA_c_eq_c_times_c(ps, sl0, sl1);
    QLA_c_eq_r_div_c(c1, 1, ss);
    QLA_c_eq_c_times_c(c0, ps, c1);
    // c0 + c1*a
    QLA_c_eq_c_times_c_plus_c(QLA_elem_M(*r,0,0), c1, a00, c0);
    QLA_c_eq_c_times_c(QLA_elem_M(*r,0,1), c1, a01);
    QLA_c_eq_c_times_c(QLA_elem_M(*r,1,0), c1, a10);
    QLA_c_eq_c_times_c_plus_c(QLA_elem_M(*r,1,1), c1, a11, c0);
    return;
  }

  // flops: 4n2(1+c)  sqrt: 2  div: 1
  // MpeqM: 1+c  MeqdtM: 2+c  MpeqdtM: 1  MtM: c  Minv: 0  MinvM: c
  // flops: 12n2+3 + c(20n3+5.5n2+2.5n)
  double ds = maxev2(NCVAR a);
  //printf("ds = %g\n", ds);
  if(ds == 0) {
    QLAN(M_eq_zero, r);
    return;
  }
  ds = sqrt(ds);

  QLAN(ColorMatrix,x);
  QLAN(ColorMatrix,e);
  //QLAN(ColorMatrix,xi);
  QLAN(ColorMatrix,t1);
  QLAN(ColorMatrix,t2);

  M_eq_d_times_M(&x, 1/ds, a);   // x = b/ds = A
  M_eq_d(&e, 0.5);
  M_peq_d_times_M(&e, -0.5, &x); // e = 0.5 - 0.5 * x
  QLAN(M_peq_M, &x, &e);

  double enorm, estop = EPS;
  int maxit = 20;
  int nit = 0;
  do {  // e = -0.5 e x^-1 e; x += e
    nit++;
    //QLAN(M_eq_inverse_M, &xi, &x);
    //QLAN(M_eq_M_times_M, &t1, &xi, &e);
    QLAN(M_eq_M_inverse_M, &t1, &x, &e);
    QLAN(M_eq_M_times_M, &t2, &e, &t1);
    M_eq_d_times_M(&e, -0.5, &t2);
    QLAN(M_peq_M, &x, &e);
    enorm = maxev2(NCVAR &e);
    //printf("%i enorm = %g\n", nit, enorm);
  } while(nit<maxit && enorm>estop);

  M_eq_d_times_M(r, sqrt(ds), &x);

#if 0
  QLAN(M_eq_M_times_M, &x, r, r);
  QLAN(M_meq_M, &x, a);
  enorm = maxev(NCVAR &x);
  printf("%i %g %g %g\n", nit, enorm, enorm/ds, EPS);
#endif
}
