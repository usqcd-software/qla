/**************** QLA_F3_H_veq_spproj_D.c ********************/

#include <stdio.h>
#include <qla_config.h>
#include <qla_types.h>
#include <qla_random.h>
#include <qla_cmath.h>
#include <qla_sse.h>
#include <math.h>

#define NP 6
#define storepsr storentps

void
QLA_F3_H_veq_spproj_D( QLA_F3_HalfFermion *restrict r,
		       QLA_F3_DiracFermion *restrict a,
		       int mu, int sign , int n )
{
  if(is_aligned(r,16) && is_aligned(a,16)) {
    if(sign==1) {
      switch(mu) {
      case 0: {
#pragma omp parallel for
	for(int i=0; i<n; i++) {
	  QLA_F3_HalfFermion *ri = &r[i];
	  QLA_F3_DiracFermion *ai = &a[i];
	  int i_c;
	  //prefetch(&a[i+NP]);
	  //prefetchnt(&r[i+NP]);
	  for(i_c=0; i_c<3; i_c++) {
	    v4sf t;
	    spproj0p(t, foff(ai,8*i_c));
	    storepsr(foff(ri,4*i_c), t);
	  }
	}
      } break;
      case 1: {
#pragma omp parallel for
	for(int i=0; i<n; i++) {
	  QLA_F3_HalfFermion *ri = &r[i];
	  QLA_F3_DiracFermion *ai = &a[i];
	  int i_c;
	  for(i_c=0;i_c<3;i_c++) {
	    v4sf t;
	    spproj1p(t, foff(ai,8*i_c));
	    storepsr(foff(ri,4*i_c), t);
	  }
        }
      } break;
      case 2: {
#pragma omp parallel for
	for(int i=0; i<n; i++) {
          QLA_F3_HalfFermion *ri = &r[i];
          QLA_F3_DiracFermion *ai = &a[i];
          int i_c;
          for(i_c=0; i_c<3; i_c++) {
	    v4sf t;
	    spproj2p(t, foff(ai,8*i_c));
	    storepsr(foff(ri,4*i_c), t);
	  }
        }
      } break;
      case 3: {
#pragma omp parallel for
	for(int i=0; i<n; i++) {
          QLA_F3_HalfFermion *ri = &r[i];
          QLA_F3_DiracFermion *ai = &a[i];
          int i_c;
          for(i_c=0; i_c<3; i_c++) {
	    v4sf t;
	    spproj3p(t, foff(ai,8*i_c));
	    storepsr(foff(ri,4*i_c), t);
	  }
        }
      } break;
      case 4: {
#pragma omp parallel for
	for(int i=0; i<n; i++) {
          QLA_F3_HalfFermion *ri = &r[i];
          QLA_F3_DiracFermion *ai = &a[i];
          int i_c;
          for(i_c=0; i_c<3; i_c++) {
	    v4sf t;
	    spproj4p(t, foff(ai,8*i_c));
	    storepsr(foff(ri,4*i_c), t);
	  }
        }
      } break;
      }
    } else {
      switch(mu) {
      case 0: {
#pragma omp parallel for
	for(int i=0; i<n; i++) {
          QLA_F3_HalfFermion *ri = &r[i];
          QLA_F3_DiracFermion *ai = &a[i];
          int i_c;
          for(i_c=0; i_c<3; i_c++) {
	    v4sf t;
	    spproj0m(t, foff(ai,8*i_c));
	    storepsr(foff(ri,4*i_c), t);
	  }
        }
      } break;
      case 1: {
#pragma omp parallel for
	for(int i=0; i<n; i++) {
          QLA_F3_HalfFermion *ri = &r[i];
          QLA_F3_DiracFermion *ai = &a[i];
          int i_c;
          for(i_c=0; i_c<3; i_c++) {
	    v4sf t;
	    spproj1m(t, foff(ai,8*i_c));
	    storepsr(foff(ri,4*i_c), t);
	  }
        }
      } break;
      case 2: {
#pragma omp parallel for
	for(int i=0; i<n; i++) {
          QLA_F3_HalfFermion *ri = &r[i];
          QLA_F3_DiracFermion *ai = &a[i];
          int i_c;
          for(i_c=0; i_c<3; i_c++) {
	    v4sf t;
	    spproj2m(t, foff(ai,8*i_c));
	    storepsr(foff(ri,4*i_c), t);
	  }
        }
      } break;
      case 3: {
#pragma omp parallel for
	for(int i=0; i<n; i++) {
          QLA_F3_HalfFermion *ri = &r[i];
          QLA_F3_DiracFermion *ai = &a[i];
          int i_c;
          for(i_c=0; i_c<3; i_c++) {
	    v4sf t;
	    spproj3m(t, foff(ai,8*i_c));
	    storepsr(foff(ri,4*i_c), t);
	  }
        }
      } break;
      case 4: {
#pragma omp parallel for
	for(int i=0; i<n; i++) {
	  QLA_F3_HalfFermion *ri = &r[i];
	  QLA_F3_DiracFermion *ai = &a[i];
          int i_c;
          for(i_c=0; i_c<3; i_c++) {
	    v4sf t;
	    spproj4m(t, foff(ai,8*i_c));
	    storepsr(foff(ri,4*i_c), t);
	  }
        }
      } break;
      }
    }
  } else {  /* not aligned */
    if(sign==1) {
      switch(mu) {
      case 0: {
#pragma omp parallel for
	for(int i=0; i<n; i++) {
	  QLA_F3_HalfFermion *ri = &r[i];
	  QLA_F3_DiracFermion *ai = &a[i];
	  int i_c;
	  for(i_c=0; i_c<3; i_c++) {
	    QLA_c_eq_c_plus_ic(QLA_F3_elem_H(*ri,i_c,0),
			       QLA_F3_elem_D(*ai,i_c,0),
			       QLA_F3_elem_D(*ai,i_c,3));
	    QLA_c_eq_c_plus_ic(QLA_F3_elem_H(*ri,i_c,1),
			       QLA_F3_elem_D(*ai,i_c,1),
			       QLA_F3_elem_D(*ai,i_c,2));
	  }
	}
      } break;
      case 1: {
#pragma omp parallel for
	for(int i=0; i<n; i++) {
	  QLA_F3_HalfFermion *ri = &r[i];
	  QLA_F3_DiracFermion *ai = &a[i];
	  int i_c;
	  for(i_c=0;i_c<3;i_c++) {
	    QLA_c_eq_c_minus_c(QLA_F3_elem_H(*ri,i_c,0),
			       QLA_F3_elem_D(*ai,i_c,0),
			       QLA_F3_elem_D(*ai,i_c,3));
	    QLA_c_eq_c_plus_c(QLA_F3_elem_H(*ri,i_c,1),
			      QLA_F3_elem_D(*ai,i_c,1),
			      QLA_F3_elem_D(*ai,i_c,2));
	  }
        }
      } break;
      case 2: {
#pragma omp parallel for
	for(int i=0; i<n; i++) {
          QLA_F3_HalfFermion *ri = &r[i];
          QLA_F3_DiracFermion *ai = &a[i];
          int i_c;
          for(i_c=0; i_c<3; i_c++) {
	    QLA_c_eq_c_plus_ic(QLA_F3_elem_H(*ri,i_c,0),
			       QLA_F3_elem_D(*ai,i_c,0),
			       QLA_F3_elem_D(*ai,i_c,2));
	    QLA_c_eq_c_minus_ic(QLA_F3_elem_H(*ri,i_c,1),
				QLA_F3_elem_D(*ai,i_c,1),
				QLA_F3_elem_D(*ai,i_c,3));
	  }
        }
      } break;
      case 3: {
#pragma omp parallel for
	for(int i=0; i<n; i++) {
          QLA_F3_HalfFermion *ri = &r[i];
          QLA_F3_DiracFermion *ai = &a[i];
          int i_c;
          for(i_c=0; i_c<3; i_c++) {
	    QLA_c_eq_c_plus_c(QLA_F3_elem_H(*ri,i_c,0),
			      QLA_F3_elem_D(*ai,i_c,0),
			      QLA_F3_elem_D(*ai,i_c,2));
	    QLA_c_eq_c_plus_c(QLA_F3_elem_H(*ri,i_c,1),
			      QLA_F3_elem_D(*ai,i_c,1),
			      QLA_F3_elem_D(*ai,i_c,3));
	  }
        }
      } break;
      case 4: {
#pragma omp parallel for
	for(int i=0; i<n; i++) {
          QLA_F3_HalfFermion *ri = &r[i];
          QLA_F3_DiracFermion *ai = &a[i];
          int i_c;
          for(i_c=0; i_c<3; i_c++) {
	    QLA_c_eq_c(QLA_F3_elem_H(*ri,i_c,0),QLA_F3_elem_D(*ai,i_c,0));
	    QLA_c_eq_c(QLA_F3_elem_H(*ri,i_c,1),QLA_F3_elem_D(*ai,i_c,1));
	  }
        }
      } break;
      }
    } else {
      switch(mu) {
      case 0: {
#pragma omp parallel for
	for(int i=0; i<n; i++) {
          QLA_F3_HalfFermion *ri = &r[i];
          QLA_F3_DiracFermion *ai = &a[i];
          int i_c;
          for(i_c=0; i_c<3; i_c++) {
	    QLA_c_eq_c_minus_ic(QLA_F3_elem_H(*ri,i_c,0),
				QLA_F3_elem_D(*ai,i_c,0),
				QLA_F3_elem_D(*ai,i_c,3));
	    QLA_c_eq_c_minus_ic(QLA_F3_elem_H(*ri,i_c,1),
				QLA_F3_elem_D(*ai,i_c,1),
				QLA_F3_elem_D(*ai,i_c,2));
	  }
        }
      } break;
      case 1: {
#pragma omp parallel for
	for(int i=0; i<n; i++) {
          QLA_F3_HalfFermion *ri = &r[i];
          QLA_F3_DiracFermion *ai = &a[i];
          int i_c;
          for(i_c=0; i_c<3; i_c++) {
	    QLA_c_eq_c_plus_c(QLA_F3_elem_H(*ri,i_c,0),
			      QLA_F3_elem_D(*ai,i_c,0),
			      QLA_F3_elem_D(*ai,i_c,3));
	    QLA_c_eq_c_minus_c(QLA_F3_elem_H(*ri,i_c,1),
			       QLA_F3_elem_D(*ai,i_c,1),
			       QLA_F3_elem_D(*ai,i_c,2));
	  }
        }
      } break;
      case 2: {
#pragma omp parallel for
	for(int i=0; i<n; i++) {
          QLA_F3_HalfFermion *ri = &r[i];
          QLA_F3_DiracFermion *ai = &a[i];
          int i_c;
          for(i_c=0; i_c<3; i_c++) {
	    QLA_c_eq_c_minus_ic(QLA_F3_elem_H(*ri,i_c,0),
				QLA_F3_elem_D(*ai,i_c,0),
				QLA_F3_elem_D(*ai,i_c,2));
	    QLA_c_eq_c_plus_ic(QLA_F3_elem_H(*ri,i_c,1),
			       QLA_F3_elem_D(*ai,i_c,1),
			       QLA_F3_elem_D(*ai,i_c,3));
	  }
        }
      } break;
      case 3: {
#pragma omp parallel for
	for(int i=0; i<n; i++) {
          QLA_F3_HalfFermion *ri = &r[i];
          QLA_F3_DiracFermion *ai = &a[i];
          int i_c;
          for(i_c=0; i_c<3; i_c++) {
	    QLA_c_eq_c_minus_c(QLA_F3_elem_H(*ri,i_c,0),
			       QLA_F3_elem_D(*ai,i_c,0),
			       QLA_F3_elem_D(*ai,i_c,2));
	    QLA_c_eq_c_minus_c(QLA_F3_elem_H(*ri,i_c,1),
			       QLA_F3_elem_D(*ai,i_c,1),
			       QLA_F3_elem_D(*ai,i_c,3));
	  }
        }
      } break;
      case 4: {
#pragma omp parallel for
	for(int i=0; i<n; i++) {
	  QLA_F3_HalfFermion *ri = &r[i];
	  QLA_F3_DiracFermion *ai = &a[i];
          int i_c;
          for(i_c=0; i_c<3; i_c++) {
	    QLA_c_eq_c(QLA_F3_elem_H(*ri,i_c,0),QLA_F3_elem_D(*ai,i_c,2));
	    QLA_c_eq_c(QLA_F3_elem_H(*ri,i_c,1),QLA_F3_elem_D(*ai,i_c,3));
	  }
        }
      } break;
      }
    }
  }
}
