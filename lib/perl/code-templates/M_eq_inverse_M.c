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
QLAPC(M_eq_inverse_M)(NCARG QLAN(ColorMatrix,(*restrict a)), QLAN(ColorMatrix,(*restrict b)))
{
#ifdef HAVE_XLC
#pragma disjoint(*a, *b)
  __alignx(16,a);
  __alignx(16,b);
#endif

  QLAN(ColorMatrix, c);
  QLAN(ColorMatrix, d);
  int row[NC];

  // copy input, set identity output and row pivot
  for(int i=0; i<NC; i++) {
    for(int j=0; j<NC; j++) {
      QLA_c_eq_c(QLA_elem_M(c,i,j), QLA_elem_M(*b,i,j));
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
    QLA_Complex s;
    QLA_Real r = 1/QLA_norm2_c(C(i,i));
    QLA_c_eq_r_times_ca(s, r, C(i,i));
    for(int j=0; j<NC; j++) {
      QLA_c_eq_c_times_c(QLA_elem_M(*a,i,j), s, D(i,j));
    }
  }
}
