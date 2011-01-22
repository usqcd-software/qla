/**************** QLA_F3_D_vmeq_spproj_D.c ********************/

#include <stdio.h>
#include <qla_config.h>
#include <qla_types.h>
#include <qla_random.h>
#include <qla_cmath.h>
#include <qla_sse.h>
#include <math.h>

void
QLA_F3_D_vmeq_spproj_D( QLA_F3_DiracFermion *restrict r,
			QLA_F3_DiracFermion *restrict a,
			int mu, int sign, int n )
{
  if( (is_aligned(r,16)) && (is_aligned(a,16)) ) {
    if(sign==1) {
      switch(mu) {
      case 0: {
#pragma omp parallel for
	for(int i=0; i<n; i++) {
	  QLA_F3_DiracFermion *ri = &r[i];
	  QLA_F3_DiracFermion *ai = &a[i];
	  int i_c;
	  for(i_c=0; i_c<3; i_c++) {
	    v4sf t1, t2;
	    spproj0p(t1, foff(ai,8*i_c));
	    storeaps(foff(ri,8*i_c), subps(loadaps(foff(ri,8*i_c)), t1));
	    sprecon0p(t2, t1);
	    storeaps(foff(ri,8*i_c+4), subps(loadaps(foff(ri,8*i_c+4)), t2));
	  }
	}
      } break;
      case 1: {
#pragma omp parallel for
	for(int i=0; i<n; i++) {
	  QLA_F3_DiracFermion *ri = &r[i];
	  QLA_F3_DiracFermion *ai = &a[i];
	  int i_c;
	  for(i_c=0; i_c<3; i_c++) {
	    v4sf t1, t2;
	    spproj1p(t1, foff(ai,8*i_c));
	    storeaps(foff(ri,8*i_c), subps(loadaps(foff(ri,8*i_c)), t1));
	    sprecon1p(t2, t1);
	    storeaps(foff(ri,8*i_c+4), subps(loadaps(foff(ri,8*i_c+4)), t2));
	  }
	}
      } break;
      case 2: {
#pragma omp parallel for
	for(int i=0; i<n; i++) {
	  QLA_F3_DiracFermion *ri = &r[i];
	  QLA_F3_DiracFermion *ai = &a[i];
	  int i_c;
	  for(i_c=0; i_c<3; i_c++) {
	    v4sf t1, t2;
	    spproj2p(t1, foff(ai,8*i_c));
	    storeaps(foff(ri,8*i_c), subps(loadaps(foff(ri,8*i_c)), t1));
	    sprecon2p(t2, t1);
	    storeaps(foff(ri,8*i_c+4), subps(loadaps(foff(ri,8*i_c+4)), t2));
	  }
	}
      } break;
      case 3: {
#pragma omp parallel for
	for(int i=0; i<n; i++) {
	  QLA_F3_DiracFermion *ri = &r[i];
	  QLA_F3_DiracFermion *ai = &a[i];
	  int i_c;
	  for(i_c=0; i_c<3; i_c++) {
	    v4sf t1, t2;
	    spproj3p(t1, foff(ai,8*i_c));
	    storeaps(foff(ri,8*i_c), subps(loadaps(foff(ri,8*i_c)), t1));
	    sprecon3p(t2, t1);
	    storeaps(foff(ri,8*i_c+4), subps(loadaps(foff(ri,8*i_c+4)), t2));
	  }
	}
      } break;
      case 4: {
#pragma omp parallel for
	for(int i=0; i<n; i++) {
	  QLA_F3_DiracFermion *ri = &r[i];
	  QLA_F3_DiracFermion *ai = &a[i];
	  int i_c;
	  for(i_c=0; i_c<3; i_c++) {
	    v4sf t1, t2;
	    spproj4p(t1, foff(ai,8*i_c));
	    spproj4m(t2, foff(ai,8*i_c));
	    storeaps(foff(ri,8*i_c), subps(loadaps(foff(ri,8*i_c)), t1));
	  }
	}
      } break;
      }
    } else {
      switch(mu) {
      case 0: {
#pragma omp parallel for
	for(int i=0; i<n; i++) {
	  QLA_F3_DiracFermion *ri = &r[i];
	  QLA_F3_DiracFermion *ai = &a[i];
	  int i_c;
	  for(i_c=0; i_c<3; i_c++) {
	    v4sf t1, t2;
	    spproj0m(t1, foff(ai,8*i_c));
	    storeaps(foff(ri,8*i_c), subps(loadaps(foff(ri,8*i_c)), t1));
	    sprecon0m(t2, t1);
	    storeaps(foff(ri,8*i_c+4), subps(loadaps(foff(ri,8*i_c+4)), t2));
	  }
	}
      } break;
      case 1: {
#pragma omp parallel for
	for(int i=0; i<n; i++) {
	  QLA_F3_DiracFermion *ri = &r[i];
	  QLA_F3_DiracFermion *ai = &a[i];
	  int i_c;
	  for(i_c=0; i_c<3; i_c++) {
	    v4sf t1, t2;
	    spproj1m(t1, foff(ai,8*i_c));
	    storeaps(foff(ri,8*i_c), subps(loadaps(foff(ri,8*i_c)), t1));
	    sprecon1m(t2, t1);
	    storeaps(foff(ri,8*i_c+4), subps(loadaps(foff(ri,8*i_c+4)), t2));
	  }
	}
      } break;
      case 2: {
#pragma omp parallel for
	for(int i=0; i<n; i++) {
	  QLA_F3_DiracFermion *ri = &r[i];
	  QLA_F3_DiracFermion *ai = &a[i];
	  int i_c;
	  for(i_c=0; i_c<3; i_c++) {
	    v4sf t1, t2;
	    spproj2m(t1, foff(ai,8*i_c));
	    storeaps(foff(ri,8*i_c), subps(loadaps(foff(ri,8*i_c)), t1));
	    sprecon2m(t2, t1);
	    storeaps(foff(ri,8*i_c+4), subps(loadaps(foff(ri,8*i_c+4)), t2));
	  }
	}
      } break;
      case 3: {
#pragma omp parallel for
	for(int i=0; i<n; i++) {
	  QLA_F3_DiracFermion *ri = &r[i];
	  QLA_F3_DiracFermion *ai = &a[i];
	  int i_c;
	  for(i_c=0; i_c<3; i_c++) {
	    v4sf t1, t2;
	    spproj3m(t1, foff(ai,8*i_c));
	    storeaps(foff(ri,8*i_c), subps(loadaps(foff(ri,8*i_c)), t1));
	    sprecon3m(t2, t1);
	    storeaps(foff(ri,8*i_c+4), subps(loadaps(foff(ri,8*i_c+4)), t2));
	  }
	}
      } break;
      case 4: {
#pragma omp parallel for
	for(int i=0; i<n; i++) {
	  QLA_F3_DiracFermion *ri = &r[i];
	  QLA_F3_DiracFermion *ai = &a[i];
	  int i_c;
	  for(i_c=0; i_c<3; i_c++) {
	    v4sf t1;
	    spproj4m(t1, foff(ai,8*i_c));
	    storeaps(foff(ri,8*i_c+4), subps(loadaps(foff(ri,8*i_c+4)), t1));
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
	for(int i=0;i<n;i++)
	  {
	    QLA_F3_DiracFermion *ri = &r[i];
	    QLA_F3_DiracFermion *ai = &a[i];
	    int i_c;
	    for(i_c=0;i_c<3;i_c++)
	      {
		QLA_F3_HalfFermion t;
		QLA_c_eq_c_plus_ic(QLA_F3_elem_H(t,i_c,0),
				   QLA_F3_elem_D(*ai,i_c,0),QLA_F3_elem_D(*ai,i_c,3));
		QLA_c_eq_c_plus_ic(QLA_F3_elem_H(t,i_c,1),
				   QLA_F3_elem_D(*ai,i_c,1),QLA_F3_elem_D(*ai,i_c,2));
		QLA_c_meq_c(QLA_F3_elem_D(*ri,i_c,0),QLA_F3_elem_H(t,i_c,0));
		QLA_c_meq_c(QLA_F3_elem_D(*ri,i_c,1),QLA_F3_elem_H(t,i_c,1));
		QLA_c_peq_ic(QLA_F3_elem_D(*ri,i_c,2),QLA_F3_elem_H(t,i_c,1));
		QLA_c_peq_ic(QLA_F3_elem_D(*ri,i_c,3),QLA_F3_elem_H(t,i_c,0));
	      }
	  }
      } break;
      case 1: {
#pragma omp parallel for
	for(int i=0;i<n;i++)
	  {
	    QLA_F3_DiracFermion *ri = &r[i];
	    QLA_F3_DiracFermion *ai = &a[i];
	    int i_c;
	    for(i_c=0;i_c<3;i_c++)
	      {
		QLA_F3_HalfFermion t;
		QLA_c_eq_c_plus_c(QLA_F3_elem_H(t,i_c,0),
				  QLA_F3_elem_D(*ai,i_c,0),QLA_F3_elem_D(*ai,i_c,3));
		QLA_c_eq_c_minus_c(QLA_F3_elem_H(t,i_c,1),
				   QLA_F3_elem_D(*ai,i_c,1),QLA_F3_elem_D(*ai,i_c,2));
		QLA_c_meq_c(QLA_F3_elem_D(*ri,i_c,0),QLA_F3_elem_H(t,i_c,0));
		QLA_c_meq_c(QLA_F3_elem_D(*ri,i_c,1),QLA_F3_elem_H(t,i_c,1));
		QLA_c_peq_c(QLA_F3_elem_D(*ri,i_c,2),QLA_F3_elem_H(t,i_c,1));
		QLA_c_meq_c(QLA_F3_elem_D(*ri,i_c,3),QLA_F3_elem_H(t,i_c,0));
	      }
	  }
      } break;
      case 2: {
#pragma omp parallel for
	for(int i=0;i<n;i++)
	  {
	    QLA_F3_DiracFermion *ri = &r[i];
	    QLA_F3_DiracFermion *ai = &a[i];
	    int i_c;
	    for(i_c=0;i_c<3;i_c++)
	      {
		QLA_F3_HalfFermion t;
		QLA_c_eq_c_plus_ic(QLA_F3_elem_H(t,i_c,0),
				   QLA_F3_elem_D(*ai,i_c,0),QLA_F3_elem_D(*ai,i_c,2));
		QLA_c_eq_c_minus_ic(QLA_F3_elem_H(t,i_c,1),
				    QLA_F3_elem_D(*ai,i_c,1),QLA_F3_elem_D(*ai,i_c,3));
		QLA_c_meq_c(QLA_F3_elem_D(*ri,i_c,0),QLA_F3_elem_H(t,i_c,0));
		QLA_c_meq_c(QLA_F3_elem_D(*ri,i_c,1),QLA_F3_elem_H(t,i_c,1));
		QLA_c_peq_ic(QLA_F3_elem_D(*ri,i_c,2),QLA_F3_elem_H(t,i_c,0));
		QLA_c_meq_ic(QLA_F3_elem_D(*ri,i_c,3),QLA_F3_elem_H(t,i_c,1));
	      }
	  }
      } break;
      case 3: {
#pragma omp parallel for
	for(int i=0;i<n;i++)
	  {
	    QLA_F3_DiracFermion *ri = &r[i];
	    QLA_F3_DiracFermion *ai = &a[i];
	    int i_c;
	    for(i_c=0;i_c<3;i_c++)
	      {
		QLA_F3_HalfFermion t;
		QLA_c_eq_c_plus_c(QLA_F3_elem_H(t,i_c,0),
				  QLA_F3_elem_D(*ai,i_c,0),QLA_F3_elem_D(*ai,i_c,2));
		QLA_c_eq_c_plus_c(QLA_F3_elem_H(t,i_c,1),
				  QLA_F3_elem_D(*ai,i_c,1),QLA_F3_elem_D(*ai,i_c,3));
		QLA_c_meq_c(QLA_F3_elem_D(*ri,i_c,0),QLA_F3_elem_H(t,i_c,0));
		QLA_c_meq_c(QLA_F3_elem_D(*ri,i_c,1),QLA_F3_elem_H(t,i_c,1));
		QLA_c_meq_c(QLA_F3_elem_D(*ri,i_c,2),QLA_F3_elem_H(t,i_c,0));
		QLA_c_meq_c(QLA_F3_elem_D(*ri,i_c,3),QLA_F3_elem_H(t,i_c,1));
	      }
	  }
      } break;
      case 4: {
#pragma omp parallel for
	for(int i=0;i<n;i++)
	  {
	    QLA_F3_DiracFermion *ri = &r[i];
	    QLA_F3_DiracFermion *ai = &a[i];
	    int i_c;
	    for(i_c=0;i_c<3;i_c++)
	      {
		QLA_c_meq_c(QLA_F3_elem_D(*ri,i_c,0),QLA_F3_elem_D(*ai,i_c,0));
		QLA_c_meq_c(QLA_F3_elem_D(*ri,i_c,1),QLA_F3_elem_D(*ai,i_c,1));
	      }
	  }
      } break;
      }
    }
    else {
      switch(mu) {
      case 0: {
#pragma omp parallel for
	for(int i=0;i<n;i++)
	  {
	    QLA_F3_DiracFermion *ri = &r[i];
	    QLA_F3_DiracFermion *ai = &a[i];
	    int i_c;
	    for(i_c=0;i_c<3;i_c++)
	      {
		QLA_F3_HalfFermion t;
		QLA_c_eq_c_minus_ic(QLA_F3_elem_H(t,i_c,0),
				    QLA_F3_elem_D(*ai,i_c,0),QLA_F3_elem_D(*ai,i_c,3));
		QLA_c_eq_c_minus_ic(QLA_F3_elem_H(t,i_c,1),
				    QLA_F3_elem_D(*ai,i_c,1),QLA_F3_elem_D(*ai,i_c,2));
		QLA_c_meq_c(QLA_F3_elem_D(*ri,i_c,0),QLA_F3_elem_H(t,i_c,0));
		QLA_c_meq_c(QLA_F3_elem_D(*ri,i_c,1),QLA_F3_elem_H(t,i_c,1));
		QLA_c_meq_ic(QLA_F3_elem_D(*ri,i_c,2),QLA_F3_elem_H(t,i_c,1));
		QLA_c_meq_ic(QLA_F3_elem_D(*ri,i_c,3),QLA_F3_elem_H(t,i_c,0));
	      }
	  }
      } break;
      case 1: {
#pragma omp parallel for
	for(int i=0;i<n;i++)
	  {
	    QLA_F3_DiracFermion *ri = &r[i];
	    QLA_F3_DiracFermion *ai = &a[i];
	    int i_c;
	    for(i_c=0;i_c<3;i_c++)
	      {
		QLA_F3_HalfFermion t;
		QLA_c_eq_c_minus_c(QLA_F3_elem_H(t,i_c,0),
				   QLA_F3_elem_D(*ai,i_c,0),QLA_F3_elem_D(*ai,i_c,3));
		QLA_c_eq_c_plus_c(QLA_F3_elem_H(t,i_c,1),
				  QLA_F3_elem_D(*ai,i_c,1),QLA_F3_elem_D(*ai,i_c,2));
		QLA_c_meq_c(QLA_F3_elem_D(*ri,i_c,0),QLA_F3_elem_H(t,i_c,0));
		QLA_c_meq_c(QLA_F3_elem_D(*ri,i_c,1),QLA_F3_elem_H(t,i_c,1));
		QLA_c_meq_c(QLA_F3_elem_D(*ri,i_c,2),QLA_F3_elem_H(t,i_c,1));
		QLA_c_peq_c(QLA_F3_elem_D(*ri,i_c,3),QLA_F3_elem_H(t,i_c,0));
	      }
	  }
      } break;
      case 2: {
#pragma omp parallel for
	for(int i=0;i<n;i++)
	  {
	    QLA_F3_DiracFermion *ri = &r[i];
	    QLA_F3_DiracFermion *ai = &a[i];
	    int i_c;
	    for(i_c=0;i_c<3;i_c++)
	      {
		QLA_F3_HalfFermion t;
		QLA_c_eq_c_minus_ic(QLA_F3_elem_H(t,i_c,0),
				    QLA_F3_elem_D(*ai,i_c,0),QLA_F3_elem_D(*ai,i_c,2));
		QLA_c_eq_c_plus_ic(QLA_F3_elem_H(t,i_c,1),
				   QLA_F3_elem_D(*ai,i_c,1),QLA_F3_elem_D(*ai,i_c,3));
		QLA_c_meq_c(QLA_F3_elem_D(*ri,i_c,0),QLA_F3_elem_H(t,i_c,0));
		QLA_c_meq_c(QLA_F3_elem_D(*ri,i_c,1),QLA_F3_elem_H(t,i_c,1));
		QLA_c_meq_ic(QLA_F3_elem_D(*ri,i_c,2),QLA_F3_elem_H(t,i_c,0));
		QLA_c_peq_ic(QLA_F3_elem_D(*ri,i_c,3),QLA_F3_elem_H(t,i_c,1));
	      }
	  }
      } break;
      case 3: {
#pragma omp parallel for
	for(int i=0;i<n;i++)
	  {
	    QLA_F3_DiracFermion *ri = &r[i];
	    QLA_F3_DiracFermion *ai = &a[i];
	    int i_c;
	    for(i_c=0;i_c<3;i_c++)
	      {
		QLA_F3_HalfFermion t;
		QLA_c_eq_c_minus_c(QLA_F3_elem_H(t,i_c,0),
				   QLA_F3_elem_D(*ai,i_c,0),QLA_F3_elem_D(*ai,i_c,2));
		QLA_c_eq_c_minus_c(QLA_F3_elem_H(t,i_c,1),
				   QLA_F3_elem_D(*ai,i_c,1),QLA_F3_elem_D(*ai,i_c,3));
		QLA_c_meq_c(QLA_F3_elem_D(*ri,i_c,0),QLA_F3_elem_H(t,i_c,0));
		QLA_c_meq_c(QLA_F3_elem_D(*ri,i_c,1),QLA_F3_elem_H(t,i_c,1));
		QLA_c_peq_c(QLA_F3_elem_D(*ri,i_c,2),QLA_F3_elem_H(t,i_c,0));
		QLA_c_peq_c(QLA_F3_elem_D(*ri,i_c,3),QLA_F3_elem_H(t,i_c,1));
	      }
	  }
      } break;
      case 4: {
#pragma omp parallel for
	for(int i=0;i<n;i++)
	  {
	    QLA_F3_DiracFermion *ri = &r[i];
	    QLA_F3_DiracFermion *ai = &a[i];
	    int i_c;
	    for(i_c=0;i_c<3;i_c++)
	      {
		QLA_c_meq_c(QLA_F3_elem_D(*ri,i_c,2),QLA_F3_elem_D(*ai,i_c,2));
		QLA_c_meq_c(QLA_F3_elem_D(*ri,i_c,3),QLA_F3_elem_D(*ai,i_c,3));
	      }
	  }
      } break;
      }
    }
  }
}
