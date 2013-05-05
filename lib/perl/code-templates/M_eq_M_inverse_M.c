/**************** QLA_M_eq_M_inverse_M.c ********************/

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
QLAPC(M_eq_M_inverse_M)(NCARG QLAN(ColorMatrix,(*restrict x)), QLAN(ColorMatrix,(*restrict a)), QLAN(ColorMatrix,(*restrict b)))
{
#ifdef HAVE_XLC
#pragma disjoint(*x, *a, *b)
  __alignx(16,x);
  __alignx(16,a);
  __alignx(16,b);
#endif

  if(NC==1) {
    QLA_c_eq_c_div_c(QLA_elem_M(*x,0,0), QLA_elem_M(*b,0,0), QLA_elem_M(*a,0,0));
    return;
  }
  if(NC==2) {
    QLA_Complex a00, a01, a10, a11, b00, b01, b10, b11, r00, r01, r10, r11, det, idet;
    QLA_c_eq_c(a00, QLA_elem_M(*a,0,0));
    QLA_c_eq_c(a01, QLA_elem_M(*a,0,1));
    QLA_c_eq_c(a10, QLA_elem_M(*a,1,0));
    QLA_c_eq_c(a11, QLA_elem_M(*a,1,1));
    QLA_c_eq_c(b00, QLA_elem_M(*b,0,0));
    QLA_c_eq_c(b01, QLA_elem_M(*b,0,1));
    QLA_c_eq_c(b10, QLA_elem_M(*b,1,0));
    QLA_c_eq_c(b11, QLA_elem_M(*b,1,1));
    QLA_c_eq_c_times_c (det, a00, a11);
    QLA_c_meq_c_times_c(det, a01, a10);
    QLA_c_eq_r_div_c(idet, 1, det);
    QLA_c_eq_c_times_c (r00, a11, b00);
    QLA_c_meq_c_times_c(r00, a01, b10);
    QLA_c_eq_c_times_c (r01, a11, b01);
    QLA_c_meq_c_times_c(r01, a01, b11);
    QLA_c_eq_c_times_c (r10, a00, b10);
    QLA_c_meq_c_times_c(r10, a10, b00);
    QLA_c_eq_c_times_c (r11, a00, b11);
    QLA_c_meq_c_times_c(r11, a10, b01);
    QLA_c_eq_c_times_c(QLA_elem_M(*x,0,0), r00, idet);
    QLA_c_eq_c_times_c(QLA_elem_M(*x,0,1), r01, idet);
    QLA_c_eq_c_times_c(QLA_elem_M(*x,1,0), r10, idet);
    QLA_c_eq_c_times_c(QLA_elem_M(*x,1,1), r11, idet);
    return;
  }

  QLAN(ColorMatrix, c);
  QLAN(ColorMatrix, d);
  int row[NC];

  // copy input, set identity output and row pivot
  for(int i=0; i<NC; i++) {
    for(int j=0; j<NC; j++) {
      QLA_c_eq_c(QLA_elem_M(c,i,j), QLA_elem_M(*a,i,j));
      QLA_c_eq_c(QLA_elem_M(d,i,j), QLA_elem_M(*b,i,j));
    }
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
