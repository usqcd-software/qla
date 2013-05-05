/**************** QLA_M_eq_log_M.c ********************/

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

#define NROOTS 4

static const double P[] = {
  7.70838733755885391666E0,       
  1.79368678507819816313E1,                                                
  1.44989225341610930846E1,                                                
  4.70579119878881725854E0,                                                
  4.97494994976747001425E-1,                                               
  1.01875663804580931796E-4,                                               
};

static const double Q[] = {
  2.31251620126765340583E1,      
  7.11544750618563894466E1,                                                
  8.29875266912776603211E1,                                                
  4.52279145837532221105E1,                                                
  1.12873587189167450590E1,                                                
  //1.00000000000000000000E0,                                               
};

#define M_eq_d(x,d) {QLA_Complex zz; QLA_c_eq_r(zz,d); QLAN(M_eq_c, x, &zz);}
#define M_eq_d_times_M(x,d,a) {QLA_Real rr=(d); QLAN(M_eq_r_times_M, x, &rr, a);}
#define M_peq_d_times_M(x,d,a) {QLA_Real rr=(d); QLAN(M_peq_r_times_M, x, &rr, a);}

static double
maxev(NCARG QLAN(ColorMatrix,(*a)))
{
  double fnorm = 0;
  for(int i=0; i<NC; i++) {
    for(int j=0; j<NC; j++) {
      fnorm += QLA_norm2_c(QLA_elem_M(*a,i,j));
    }
  }
  return sqrt(fnorm);
}

void
QLAPC(M_eq_log_M)(NCARG QLAN(ColorMatrix,(*restrict r)), QLAN(ColorMatrix,(*restrict a)))
{
#ifdef HAVE_XLC
#pragma disjoint(*r, *a)
  __alignx(16,r);
  __alignx(16,a);
#endif

  if(NC==1) {
    // flops: 0  clog: 1
    QLA_elem_M(*r,0,0) = QLAP(clog)(&QLA_elem_M(*a,0,0));
    return;
  }
  if(NC==2) {
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
    QLA_Complex c0, c1;
    if(QLA_real(d)==0 && QLA_imag(d)==0) {
      // c0 = 0; c1 = log(s)/s
      QLA_Complex ls = QLAP(clog)(&s);
      QLA_c_eq_r(c0, 0);
      QLA_c_eq_c_div_c(c1, ls, s);
    } else {
      QLA_Complex e0, e1, de, sd = QLAP(csqrt)(&d);
      QLA_Real ts;
      QLA_r_eq_Re_ca_times_c(ts, s, sd);
      if(ts>=0) {
	QLA_c_eq_c_plus_c(e1, s, sd);
	QLA_c_eq_r_times_c(de, 2, sd);
      } else {
	QLA_c_eq_c_minus_c(e1, s, sd);
	QLA_c_eq_r_times_c(de, -2, sd);
      }
      QLA_c_eq_c_div_c(e0, det, e1);
      // c0 = (e1*log(e0)-e0*log(e1))/(e1-e0); c1 = (log(e1)-log(e0))/(e1-e0)
      // c0 = 0.5*(log(e0)+log(e1)) - s*c1; c1 = (log(e1)-log(e0))/(2*sd)
      QLA_Complex le0 = QLAP(clog)(&e0);
      QLA_Complex le1 = QLAP(clog)(&e1);
      QLA_Complex dei, dl, dl0;
      QLA_c_eq_r_div_c(dei, 1, de);
      QLA_c_eq_c_minus_c(dl, le1, le0);
      QLA_c_eq_c_times_c(dl0, e1, le0);
      QLA_c_meq_c_times_c(dl0, e0, le1);
      QLA_c_eq_c_times_c(c1, dl, dei);
      QLA_c_eq_c_times_c(c0, dl0, dei);
    }
    // c0 + c1*a
    QLA_c_eq_c_times_c_plus_c(QLA_elem_M(*r,0,0), c1, a00, c0);
    QLA_c_eq_c_times_c(QLA_elem_M(*r,0,1), c1, a01);
    QLA_c_eq_c_times_c(QLA_elem_M(*r,1,0), c1, a10);
    QLA_c_eq_c_times_c_plus_c(QLA_elem_M(*r,1,1), c1, a11, c0);
    return;
  }

  double ds = maxev(NCVAR a);
  //printf("log ds = %g\n", ds);
  if(ds == 0) {
    M_eq_d(r, log(0));
    return;
  }

  QLAN(ColorMatrix,as);
  QLAN(ColorMatrix,as2);
  QLAN(ColorMatrix,as3);
  QLAN(ColorMatrix,as4);
  QLAN(ColorMatrix,as5);
  QLAN(ColorMatrix,pa);
  QLAN(ColorMatrix,qa);

  M_eq_d_times_M(&as, 1/ds, a);
  for(int i=0; i<NROOTS; i++) {
    QLAN(M_eq_M, &as2, &as);
    QLAN(M_eq_sqrt_M, &as, &as2);
  }
  for(int i=0; i<NC; i++) QLA_c_meq_r(QLA_elem_M(as,i,i), 1);

  M_eq_d(&pa, P[0]);
  M_eq_d(&qa, Q[0]);
  M_peq_d_times_M(&pa, P[1], &as);
  M_peq_d_times_M(&qa, Q[1], &as);
  QLAN(M_eq_M_times_M, &as2, &as, &as);
  M_peq_d_times_M(&pa, P[2], &as2);
  M_peq_d_times_M(&qa, Q[2], &as2);
  QLAN(M_eq_M_times_M, &as3, &as, &as2);
  M_peq_d_times_M(&pa, P[3], &as3);
  M_peq_d_times_M(&qa, Q[3], &as3);
  QLAN(M_eq_M_times_M, &as4, &as2, &as2);
  M_peq_d_times_M(&pa, P[4], &as4);
  M_peq_d_times_M(&qa, Q[4], &as4);
  QLAN(M_eq_M_times_M, &as5, &as, &as4);
  M_peq_d_times_M(&pa, P[5], &as5);
  QLAN(M_peq_M, &qa, &as5);

  QLAN(M_eq_inverse_M, &as5, &qa);
  QLAN(M_eq_M_times_M, &qa, &pa, &as5);
  QLAN(M_eq_M_times_M, &pa, &as3, &qa);
  M_peq_d_times_M(&pa, -0.5, &as2);
  QLAN(M_peq_M, &pa, &as);
  M_eq_d_times_M(r, (1<<NROOTS), &pa);
  ds = log(ds);
  for(int i=0; i<NC; i++) QLA_c_peq_r(QLA_elem_M(*r,i,i), ds);

#if 0
  QLAN(M_eq_exp_M, &as, r);
  QLAN(M_meq_M, &as, a);
  double enorm = maxev(NCVAR &as);
  printf("%g %g\n", enorm, enorm*exp(-ds));
#endif
}
