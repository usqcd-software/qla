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
QLAPC(M_eq_invsqrt_M)(NCARG QLAN(ColorMatrix,(*restrict a)), QLAN(ColorMatrix,(*restrict b)))
{
#ifdef HAVE_XLC
#pragma disjoint(*a, *b)
  __alignx(16,a);
  __alignx(16,b);
#endif

  double ds = maxev(NCVAR b);
  //printf("ds = %g\n", ds);
  if (ds == 0) {
    QLAN(M_eq_zero, a);
    return;
  }

  QLAN(ColorMatrix,x);
  QLAN(ColorMatrix,e);
  QLAN(ColorMatrix,xi);
  QLAN(ColorMatrix,t1);
  QLAN(ColorMatrix,t2);

  // x = 1
  M_eq_d(&x, 1);
  // e = 0.5*ds/b - 0.5
  QLAN(M_eq_inverse_M, &xi, b);
  M_eq_d(&e, -0.5);
  M_peq_d_times_M(&e, 0.5*ds, &xi);
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

  M_eq_d_times_M(a, 1/sqrt(ds), &x);

#if 0
  QLAN(M_eq_M_times_M, &x, a, a);
  QLAN(M_meq_M, &x, b);
  enorm = maxev(NCVAR &x);
  printf("%i %g %g %g\n", nit, enorm, enorm/ds, EPS);
#endif
}
