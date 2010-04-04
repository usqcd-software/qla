/**************** QLA_M_eq_log_M.c ********************/

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
QLAPC(M_eq_log_M)(NCARG QLAN(ColorMatrix,(*restrict a)), QLAN(ColorMatrix,(*restrict b)))
{
#ifdef HAVE_XLC
#pragma disjoint(*a, *b)
  __alignx(16,a);
  __alignx(16,b);
#endif

  double ds = maxev(NCVAR b);
  //printf("log ds = %g\n", ds);
  if (ds == 0) {
    M_eq_d(a, log(0));
    return;
  }

  QLAN(ColorMatrix,bs);
  QLAN(ColorMatrix,bs2);
  QLAN(ColorMatrix,bs3);
  QLAN(ColorMatrix,bs4);
  QLAN(ColorMatrix,bs5);
  QLAN(ColorMatrix,pb);
  QLAN(ColorMatrix,qb);

  M_eq_d_times_M(&bs, 1/ds, b);
  for(int i=0; i<NROOTS; i++) {
    QLAN(M_eq_M, &bs2, &bs);
    QLAN(M_eq_sqrt_M, &bs, &bs2);
  }
  for(int i=0; i<NC; i++) QLA_c_meq_r(QLA_elem_M(bs,i,i), 1);

  M_eq_d(&pb, P[0]);
  M_eq_d(&qb, Q[0]);
  M_peq_d_times_M(&pb, P[1], &bs);
  M_peq_d_times_M(&qb, Q[1], &bs);
  QLAN(M_eq_M_times_M, &bs2, &bs, &bs);
  M_peq_d_times_M(&pb, P[2], &bs2);
  M_peq_d_times_M(&qb, Q[2], &bs2);
  QLAN(M_eq_M_times_M, &bs3, &bs, &bs2);
  M_peq_d_times_M(&pb, P[3], &bs3);
  M_peq_d_times_M(&qb, Q[3], &bs3);
  QLAN(M_eq_M_times_M, &bs4, &bs2, &bs2);
  M_peq_d_times_M(&pb, P[4], &bs4);
  M_peq_d_times_M(&qb, Q[4], &bs4);
  QLAN(M_eq_M_times_M, &bs5, &bs, &bs4);
  M_peq_d_times_M(&pb, P[5], &bs5);
  QLAN(M_peq_M, &qb, &bs5);

  QLAN(M_eq_inverse_M, &bs5, &qb);
  QLAN(M_eq_M_times_M, &qb, &pb, &bs5);
  QLAN(M_eq_M_times_M, &pb, &bs3, &qb);
  M_peq_d_times_M(&pb, -0.5, &bs2);
  QLAN(M_peq_M, &pb, &bs);
  M_eq_d_times_M(a, (1<<NROOTS), &pb);
  ds = log(ds);
  for(int i=0; i<NC; i++) QLA_c_peq_r(QLA_elem_M(*a,i,i), ds);

#if 0
  QLAN(M_eq_exp_M, &bs, a);
  QLAN(M_meq_M, &bs, b);
  double enorm = maxev(NCVAR &bs);
  printf("%g %g\n", enorm, enorm*exp(-ds));
#endif
}
