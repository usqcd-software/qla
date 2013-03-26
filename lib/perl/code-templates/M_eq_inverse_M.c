/**************** QLA_M_eq_inverse_M.c ********************/

#include <stdio.h>
#include <qla_config.h>
#include <qla_types.h>
#include <qla_random.h>
#include <qla_cmath.h>
#include <math.h>

#if QLA_Precision == 'F'
#  define QLAPX(x,y) QLA_F ## x ## _ ## y
#else
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

void
QLAPC(M_eq_inverse_M)(NCARG QLAN(ColorMatrix,(*restrict x)), QLAN(ColorMatrix,(*restrict a)))
{
#ifdef HAVE_XLC
#pragma disjoint(*x, *a)
  __alignx(16,x);
  __alignx(16,a);
#endif

  if(NC==1) {
    QLA_c_eq_r_div_c(QLA_elem_M(*x,0,0), 1, QLA_elem_M(*a,0,0));
    return;
  }
  if(NC==2) {
    QLA_Complex det;
    QLA_c_eq_c_times_c (det, QLA_elem_M(*a,0,0), QLA_elem_M(*a,1,1));
    QLA_c_meq_c_times_c(det, QLA_elem_M(*a,0,1), QLA_elem_M(*a,1,0));
    QLA_Complex idet;
    QLA_c_eq_r_div_c(idet, 1, det);
    QLA_c_eq_c_times_c (QLA_elem_M(*x,0,0), QLA_elem_M(*a,1,1), idet);
    QLA_c_eqm_c_times_c(QLA_elem_M(*x,0,1), QLA_elem_M(*a,0,1), idet);
    QLA_c_eqm_c_times_c(QLA_elem_M(*x,1,0), QLA_elem_M(*a,1,0), idet);
    QLA_c_eq_c_times_c (QLA_elem_M(*x,1,1), QLA_elem_M(*a,0,0), idet);
    return;
  }
  if(NC==3) {
    QLA_Complex det, det0, det1, det2;
    QLA_c_eq_c_times_c (det2, QLA_elem_M(*a,0,0), QLA_elem_M(*a,1,1));
    QLA_c_meq_c_times_c(det2, QLA_elem_M(*a,0,1), QLA_elem_M(*a,1,0));
    QLA_c_eq_c_times_c (det1, QLA_elem_M(*a,0,2), QLA_elem_M(*a,1,0));
    QLA_c_meq_c_times_c(det1, QLA_elem_M(*a,0,0), QLA_elem_M(*a,1,2));
    QLA_c_eq_c_times_c (det0, QLA_elem_M(*a,0,1), QLA_elem_M(*a,1,2));
    QLA_c_meq_c_times_c(det0, QLA_elem_M(*a,0,2), QLA_elem_M(*a,1,1));
    QLA_c_eq_c_times_c (det, det2, QLA_elem_M(*a,2,2));
    QLA_c_peq_c_times_c(det, det1, QLA_elem_M(*a,2,1));
    QLA_c_peq_c_times_c(det, det0, QLA_elem_M(*a,2,0));
    QLA_Complex idet;
    QLA_c_eq_r_div_c(idet, 1, det);
#define set(i0,j0,i1,j1,i2,j2) \
    QLA_c_eq_c_times_c (det, QLA_elem_M(*a,i1,j1), QLA_elem_M(*a,i2,j2)); \
    QLA_c_meq_c_times_c(det, QLA_elem_M(*a,i1,j2), QLA_elem_M(*a,i2,j1)); \
    QLA_c_eq_c_times_c(QLA_elem_M(*x,i0,j0), det, idet);
    set(0,0,1,1,2,2);
    set(0,1,2,1,0,2);
    QLA_c_eq_c_times_c(QLA_elem_M(*x,0,2), det0, idet);
    set(1,0,1,2,2,0);
    set(1,1,2,2,0,0);
    QLA_c_eq_c_times_c(QLA_elem_M(*x,1,2), det1, idet);
    set(2,0,1,0,2,1);
    set(2,1,2,0,0,1);
    QLA_c_eq_c_times_c(QLA_elem_M(*x,2,2), det2, idet);
#undef set
    return;
  }

  QLAN(ColorMatrix, c);
  QLAN(ColorMatrix, d);
  int row[NC];

  // copy input, set identity output and row pivot
  for(int i=0; i<NC; i++) {
    for(int j=0; j<NC; j++) {
      QLA_c_eq_c(QLA_elem_M(c,i,j), QLA_elem_M(*a,i,j));
      QLA_c_eq_r(QLA_elem_M(d,i,j), 0);
    }
    QLA_c_eq_r(QLA_elem_M(d,i,i), 1);
    row[i] = i;
  }
#define C(i,j) QLA_elem_M(c,row[i],j)
#define D(i,j) QLA_elem_M(d,row[i],j)
  for(int k=0; k<NC; k++) {
    QLA_Complex s;
    QLA_Real rmax = QLA_norm2_c(C(k,k));
    int imax = k;
    for(int i=k+1; i<NC; i++) {
      QLA_Real r = QLA_norm2_c(C(i,k));
      if(r>rmax) { rmax = r; imax = i; }
    }
    { int rk = row[k]; row[k] = row[imax]; row[imax] = rk; }
    rmax = 1/rmax;
    QLA_c_eq_r_times_ca(s, rmax, C(k,k));
    QLA_c_eq_c(C(k,k), s);
    for(int i=0; i<NC; i++) {
      if(i==k) continue;
      QLA_Complex t;
      QLA_c_eq_c_times_c(t, s, C(i,k));
      for(int j=k+1; j<NC; j++) {
        QLA_c_meq_c_times_c(C(i,j), t, C(k,j));
      }
      for(int j=0; j<NC; j++) {
        QLA_c_meq_c_times_c(D(i,j), t, D(k,j));
      }
    }
  }
  for(int i=0; i<NC; i++) {
    for(int j=0; j<NC; j++) {
      QLA_c_eq_c_times_c(QLA_elem_M(*x,i,j), C(i,i), D(i,j));
    }
  }
}
