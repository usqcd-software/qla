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
QLAPC(M_eq_sqrt_M)(NCARG QLAN(ColorMatrix,(*restrict r)), QLAN(ColorMatrix,(*restrict a)))
{
#ifdef HAVE_XLC
#pragma disjoint(*r, *a)
  __alignx(16,r);
  __alignx(16,a);
#endif

  if(NC==1) {
    QLA_elem_M(*r,0,0) = QLAP(csqrt)(&QLA_elem_M(*a,0,0));
    return;
  }
  if(NC==2) {
    QLA_Complex tr, det;
    QLA_c_eq_c_plus_c(tr, QLA_elem_M(*a,0,0), QLA_elem_M(*a,1,1));
    QLA_c_eq_c_times_c (det, QLA_elem_M(*a,0,0), QLA_elem_M(*a,1,1));
    QLA_c_meq_c_times_c(det, QLA_elem_M(*a,0,1), QLA_elem_M(*a,1,0));
    // c0 = c1*sqrt(det);  c1 = 1/sqrt(tr+2sqrt(det))
    QLA_Complex sd = QLAP(csqrt)(&det);
    QLA_c_peq_r_times_c(tr, 2, sd);
    QLA_Complex c0, c1;
    //if(QLA_real(tr)==0 && QLA_imag(tr)==0) {
    
    QLA_Complex st = QLAP(csqrt)(&tr);
    QLA_c_eq_r_div_c(c1, 1, st);
    QLA_c_eq_c_times_c(c0, c1, sd);
    // c0 + c1*a
    QLA_c_eq_c_times_c_plus_c(QLA_elem_M(*r,0,0), c1, QLA_elem_M(*a,0,0), c0);
    QLA_c_eq_c_times_c(QLA_elem_M(*r,0,1), c1, QLA_elem_M(*a,0,1));
    QLA_c_eq_c_times_c(QLA_elem_M(*r,1,0), c1, QLA_elem_M(*a,1,0));
    QLA_c_eq_c_times_c_plus_c(QLA_elem_M(*r,1,1), c1, QLA_elem_M(*a,1,1), c0);
    return;
  }

  double ds = maxev(NCVAR a);
  //printf("ds = %g\n", ds);
  if (ds == 0) {
    QLAN(M_eq_zero, r);
    return;
  }

  QLAN(ColorMatrix,x);
  QLAN(ColorMatrix,e);
  QLAN(ColorMatrix,xi);
  QLAN(ColorMatrix,t1);
  QLAN(ColorMatrix,t2);

  M_eq_d_times_M(&x, 1/ds, a);   // x = b/ds = A
  M_eq_d(&e, 0.5);
  M_peq_d_times_M(&e, -0.5, &x); // e = 0.5 - 0.5 * x
  QLAN(M_peq_M, &x, &e);

  double enorm, estop = sqrt(EPS);
  int maxit = 20;
  int nit = 0;
  do {  // e = -0.5 e x^-1 e; x += e
    nit++;
    QLAN(M_eq_inverse_M, &xi, &x);
    QLAN(M_eq_M_times_M, &t1, &xi, &e);
    QLAN(M_eq_M_times_M, &t2, &e, &t1);
    M_eq_d_times_M(&e, -0.5, &t2);
    QLAN(M_peq_M, &x, &e);
    enorm = maxev(NCVAR &e);
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
