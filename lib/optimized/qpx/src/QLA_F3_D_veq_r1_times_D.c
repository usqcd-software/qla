/**************** QLA_F3_D_veq_r1_times_D.c ********************/

#include <qla_config.h>
#include <qla_types.h>
#include <qla_random.h>
#include <qla_cmath.h>
#include <math.h>

#include <bgqintrin.h>

void
QLA_F3_D_veq_r_times_D(QLA_F3_DiracFermion *restrict r, QLA_F_Real *restrict a,
		       QLA_F3_DiracFermion *restrict b, int n)
{
#ifdef HAVE_XLC
#pragma disjoint(*r, *a, *b)
  //__alignx(16,r);
  //__alignx(16,a);
  //__alignx(16,b);
#endif
  if(is_aligned(r,16) && is_aligned(b,16)) {
    V4D a4 = SPLAT1DF(*a);
#pragma omp parallel for
    for(int i=0; i<n; i++) {
      //QLA_F3_DiracFermion *ri = &r[i];
      //QLA_F3_DiracFermion *bi = &b[i];
      //QLA_F_Complex *ri = &r[i][0][0];
      //QLA_F_Complex *bi = &b[i][0][0];
      QLA_F_Real *ri = (QLA_F_Real *) &r[i][0][0];
      QLA_F_Real *bi = (QLA_F_Real *) &b[i][0][0];
      //#define mul(o) STORE4FDA(foff(ri,o), MUL4D(a4, LOAD4DFA(foff(bi,o)) ) )
      //#define mul(o) do { V4D t=LOAD4DFA(foff(bi,o)); STORE4FDA(foff(ri,o), MUL4D(a4,t) ); } while(0)
#define mul(o) do { V4D t=LOADFX(bi,4*o); STOREFX(ri,4*o,MUL4D(a4,t)); } while(0)
      //#define mul(o) STOREFX(ri,4*o,MUL4D(a4,LOADFX(bi,4*o)))
      mul(0);
      mul(4);
      mul(8);
      mul(12);
      mul(16);
      mul(20);
    }
  } else {
    QLA_D_Real at = QLA_DF_r(*a);
#pragma omp parallel for
    for(int i=0; i<n; i++) {
      for(int i_c=0; i_c<3; i_c++) {
	for(int i_s=0; i_s<4; i_s++) {
	  QLA_D_Complex x;
	  QLA_c_eq_r_times_c(x,at,QLA_F3_elem_D(b[i],i_c,i_s));
	  QLA_FD_c_eq_c(QLA_F3_elem_D(r[i],i_c,i_s),x);
	}
      }
    }
  }
}

/*
void QLA_F3_D_veq_r_times_D ( QLA_F3_DiracFermion *restrict r, QLA_F_Real *restrict a, QLA_F3_DiracFermion *restrict b, int n )
{
#ifdef HAVE_XLC
#pragma disjoint(*r, *a, *b)
  __alignx(16,r);
  __alignx(16,a);
  __alignx(16,b);
#endif
  QLA_D_Real at;
  at = QLA_DF_r(*a);
  int i;
  for(i=0; i<n; i++) {
    int i_c;
    for(i_c=0; i_c<3; i_c++) {
      int i_s;
      for(i_s=0; i_s<4; i_s++) {
        QLA_D_Complex x;
        QLA_c_eq_r_times_c(x,at,QLA_F3_elem_D(b[i],i_c,i_s));
        QLA_FD_c_eq_c(QLA_F3_elem_D(r[i],i_c,i_s),x);
      }
    }
  }
}
*/
