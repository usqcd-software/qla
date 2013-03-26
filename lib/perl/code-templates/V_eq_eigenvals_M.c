/**************** QLA_M_eq_inverse_M.c ********************/

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

void
QLAPC(V_eq_eigenvals_M)(NCARG QLAN(ColorVector,(*restrict r)), QLAN(ColorMatrix,(*restrict a)))
{
#ifdef HAVE_XLC
#pragma disjoint(*r, *a)
  __alignx(16,r);
  __alignx(16,a);
#endif

  if(NC==1) {
    QLA_c_eq_c(QLA_elem_V(*r,0), QLA_elem_M(*a,0,0));
    return;
  }
  if(NC==2) {
    QLA_Complex tr, det, d;
    QLA_c_eq_c_plus_c(tr, QLA_elem_M(*a,0,0), QLA_elem_M(*a,1,1));
    QLA_c_eq_c_times_c (det, QLA_elem_M(*a,0,0), QLA_elem_M(*a,1,1));
    QLA_c_meq_c_times_c(det, QLA_elem_M(*a,0,1), QLA_elem_M(*a,1,0));
    // lambda = 0.5*(tr \pm sqrt(tr^2 - 4*det) )
    QLA_c_eq_c_times_c(d, tr, tr);
    QLA_c_meq_r_times_c(d, 4, det);
    QLA_Complex sd = QLAP(csqrt)(&d);
    if(QLA_real(tr)>=0) {
      QLA_c_peq_c(tr, sd);
    } else {
      QLA_c_meq_c(tr, sd);
    }
    QLA_c_eq_r_times_c(QLA_elem_V(*r,1), 0.5, tr);
    QLA_c_eq_c_div_c(QLA_elem_V(*r,0), det, QLA_elem_V(*r,1));
    return;
  }
  if(NC==3) {
    QLA_Complex tr, s2, det, det0, det1, det2, d;
    QLA_c_eq_c_plus_c(tr, QLA_elem_M(*a,0,0), QLA_elem_M(*a,1,1));
    QLA_c_peq_c(tr, QLA_elem_M(*a,2,2));
    QLA_c_eq_c_times_c (det2, QLA_elem_M(*a,0,0), QLA_elem_M(*a,1,1));
    QLA_c_meq_c_times_c(det2, QLA_elem_M(*a,0,1), QLA_elem_M(*a,1,0));
    QLA_c_eq_c_times_c (det1, QLA_elem_M(*a,0,2), QLA_elem_M(*a,1,0));
    QLA_c_meq_c_times_c(det1, QLA_elem_M(*a,0,0), QLA_elem_M(*a,1,2));
    QLA_c_eq_c_times_c (det0, QLA_elem_M(*a,0,1), QLA_elem_M(*a,1,2));
    QLA_c_meq_c_times_c(det0, QLA_elem_M(*a,0,2), QLA_elem_M(*a,1,1));
    QLA_c_eq_c_times_c (det, det2, QLA_elem_M(*a,2,2));
    QLA_c_peq_c_times_c(det, det1, QLA_elem_M(*a,2,1));
    QLA_c_peq_c_times_c(det, det0, QLA_elem_M(*a,2,0));
    QLA_c_eq_c(s2, det2);
    QLA_c_peq_c_times_c(s2, QLA_elem_M(*a,0,0), QLA_elem_M(*a,2,2));
    QLA_c_meq_c_times_c(s2, QLA_elem_M(*a,0,2), QLA_elem_M(*a,2,0));
    QLA_c_peq_c_times_c(s2, QLA_elem_M(*a,1,1), QLA_elem_M(*a,2,2));
    QLA_c_meq_c_times_c(s2, QLA_elem_M(*a,1,2), QLA_elem_M(*a,2,1));
    // solve: x^3 - tr x^2 + s2 x - det = 0

    return;
  }
}
