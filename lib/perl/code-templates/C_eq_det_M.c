/**************** QLA_C_eq_det_M.c ********************/

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
QLAPC(C_eq_det_M)(NCARG QLA_Complex *a, QLAN(ColorMatrix,(*b)))
{
#ifdef HAVE_XLC
  __alignx(16,a);
  __alignx(16,b);
#endif

  QLAN(ColorMatrix, c);
  int row[NC], nswaps=0;
  QLA_c_eq_r(*a, 1);

  for(int i=0; i<NC; i++) {
    for(int j=0; j<NC; j++) {
      QLA_c_eq_c(QLA_elem_M(c,i,j), QLA_elem_M(*b,i,j));
    }
    row[i] = i;
  }
#define C(i,j) QLA_elem_M(c,row[i],j)
  for(int j=0; j<NC; j++) {

    if(j>0) {
      for(int i=j; i<NC; i++) {
	QLA_Complex t2;
	QLA_c_eq_c(t2, C(i,j));
	for(int k=0; k<j; k++)
	  QLA_c_meq_c_times_c(t2, C(i,k), C(k,j));
	QLA_c_eq_c(C(i,j), t2);
      }
    }

    QLA_Real rmax = QLA_norm2_c(C(j,j));
    int jmax = j;
    for(int k=j+1; k<NC; k++) {
      QLA_Real r = QLA_norm2_c(C(k,j));
      if(r>rmax) { rmax = r; jmax = j; }
    }
    if(rmax==0) { // matrix is singular
      QLA_c_eq_r(*a, 0);
      return;
    }
    if(jmax!=j) {
      int rj = row[j]; row[j] = row[jmax]; row[jmax] = rj;
      nswaps++;
    }

    {
      QLA_Complex z;
      QLA_c_eq_c(z, *a);
      QLA_c_eq_c_times_c(*a, z, C(j,j));
    }

    for(int i=j+1; i<NC; i++) {
      QLA_Complex t2;
      QLA_c_eq_c(t2, C(j,i));
      for(int k=0; k<j; k++)
        QLA_c_meq_c_times_c(t2, C(j,k), C(k,i));
      QLA_c_eq_c_div_c(C(j,i), t2, C(j,j));
    }

  }

  if(nswaps&1) QLA_c_eqm_c(*a, *a);
}