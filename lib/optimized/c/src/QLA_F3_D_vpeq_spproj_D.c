/**************** QLA_F3_D_vpeq_spproj_D.c ********************/

#include <stdio.h>
#include <qla_config.h>
#include <qla_types.h>
#include <qla_random.h>
#include <qla_cmath.h>
#include <math.h>

void QLA_F3_D_vpeq_spproj_D ( QLA_F3_DiracFermion *restrict r, QLA_F3_DiracFermion *restrict a, int mu, int sign , int n )
{
  if(sign==1) {
    switch(mu) {
    case 0: {
      int i;
      for(i=0;i<n;i++)
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
              QLA_c_peq_c(QLA_F3_elem_D(*ri,i_c,0),QLA_F3_elem_H(t,i_c,0));
              QLA_c_peq_c(QLA_F3_elem_D(*ri,i_c,1),QLA_F3_elem_H(t,i_c,1));
              QLA_c_meq_ic(QLA_F3_elem_D(*ri,i_c,2),QLA_F3_elem_H(t,i_c,1));
              QLA_c_meq_ic(QLA_F3_elem_D(*ri,i_c,3),QLA_F3_elem_H(t,i_c,0));
            }
        }
      } break;
    case 1: {
      int i;
      for(i=0;i<n;i++)
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
              QLA_c_peq_c(QLA_F3_elem_D(*ri,i_c,0),QLA_F3_elem_H(t,i_c,0));
              QLA_c_peq_c(QLA_F3_elem_D(*ri,i_c,1),QLA_F3_elem_H(t,i_c,1));
              QLA_c_peq_c(QLA_F3_elem_D(*ri,i_c,2),QLA_F3_elem_H(t,i_c,1));
              QLA_c_meq_c(QLA_F3_elem_D(*ri,i_c,3),QLA_F3_elem_H(t,i_c,0));
            }
        }
      } break;
    case 2: {
      int i;
      for(i=0;i<n;i++)
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
              QLA_c_peq_c(QLA_F3_elem_D(*ri,i_c,0),QLA_F3_elem_H(t,i_c,0));
              QLA_c_peq_c(QLA_F3_elem_D(*ri,i_c,1),QLA_F3_elem_H(t,i_c,1));
              QLA_c_meq_ic(QLA_F3_elem_D(*ri,i_c,2),QLA_F3_elem_H(t,i_c,0));
              QLA_c_peq_ic(QLA_F3_elem_D(*ri,i_c,3),QLA_F3_elem_H(t,i_c,1));
            }
        }
      } break;
    case 3: {
      int i;
      for(i=0;i<n;i++)
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
              QLA_c_peq_c(QLA_F3_elem_D(*ri,i_c,0),QLA_F3_elem_H(t,i_c,0));
              QLA_c_peq_c(QLA_F3_elem_D(*ri,i_c,1),QLA_F3_elem_H(t,i_c,1));
              QLA_c_peq_c(QLA_F3_elem_D(*ri,i_c,2),QLA_F3_elem_H(t,i_c,0));
              QLA_c_peq_c(QLA_F3_elem_D(*ri,i_c,3),QLA_F3_elem_H(t,i_c,1));
            }
        }
      } break;
    case 4: {
      int i;
      for(i=0;i<n;i++)
        {
          QLA_F3_DiracFermion *ri = &r[i];
          QLA_F3_DiracFermion *ai = &a[i];
          int i_c;
          for(i_c=0;i_c<3;i_c++)
            {
              QLA_c_peq_c(QLA_F3_elem_D(*ri,i_c,0),QLA_F3_elem_D(*ai,i_c,0));
              QLA_c_peq_c(QLA_F3_elem_D(*ri,i_c,1),QLA_F3_elem_D(*ai,i_c,1));
            }
        }
      } break;
    }
  }
  else {
    switch(mu) {
    case 0: {
      int i;
      for(i=0;i<n;i++)
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
              QLA_c_peq_c(QLA_F3_elem_D(*ri,i_c,0),QLA_F3_elem_H(t,i_c,0));
              QLA_c_peq_c(QLA_F3_elem_D(*ri,i_c,1),QLA_F3_elem_H(t,i_c,1));
              QLA_c_peq_ic(QLA_F3_elem_D(*ri,i_c,2),QLA_F3_elem_H(t,i_c,1));
              QLA_c_peq_ic(QLA_F3_elem_D(*ri,i_c,3),QLA_F3_elem_H(t,i_c,0));
            }
        }
      } break;
    case 1: {
      int i;
      for(i=0;i<n;i++)
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
              QLA_c_peq_c(QLA_F3_elem_D(*ri,i_c,0),QLA_F3_elem_H(t,i_c,0));
              QLA_c_peq_c(QLA_F3_elem_D(*ri,i_c,1),QLA_F3_elem_H(t,i_c,1));
              QLA_c_meq_c(QLA_F3_elem_D(*ri,i_c,2),QLA_F3_elem_H(t,i_c,1));
              QLA_c_peq_c(QLA_F3_elem_D(*ri,i_c,3),QLA_F3_elem_H(t,i_c,0));
            }
        }
      } break;
    case 2: {
      int i;
      for(i=0;i<n;i++)
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
              QLA_c_peq_c(QLA_F3_elem_D(*ri,i_c,0),QLA_F3_elem_H(t,i_c,0));
              QLA_c_peq_c(QLA_F3_elem_D(*ri,i_c,1),QLA_F3_elem_H(t,i_c,1));
              QLA_c_peq_ic(QLA_F3_elem_D(*ri,i_c,2),QLA_F3_elem_H(t,i_c,0));
              QLA_c_meq_ic(QLA_F3_elem_D(*ri,i_c,3),QLA_F3_elem_H(t,i_c,1));
            }
        }
      } break;
    case 3: {
      int i;
      for(i=0;i<n;i++)
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
              QLA_c_peq_c(QLA_F3_elem_D(*ri,i_c,0),QLA_F3_elem_H(t,i_c,0));
              QLA_c_peq_c(QLA_F3_elem_D(*ri,i_c,1),QLA_F3_elem_H(t,i_c,1));
              QLA_c_meq_c(QLA_F3_elem_D(*ri,i_c,2),QLA_F3_elem_H(t,i_c,0));
              QLA_c_meq_c(QLA_F3_elem_D(*ri,i_c,3),QLA_F3_elem_H(t,i_c,1));
            }
        }
      } break;
    case 4: {
      int i;
      for(i=0;i<n;i++)
        {
          QLA_F3_DiracFermion *ri = &r[i];
          QLA_F3_DiracFermion *ai = &a[i];
          int i_c;
          for(i_c=0;i_c<3;i_c++)
            {
              QLA_c_peq_c(QLA_F3_elem_D(*ri,i_c,2),QLA_F3_elem_D(*ai,i_c,2));
              QLA_c_peq_c(QLA_F3_elem_D(*ri,i_c,3),QLA_F3_elem_D(*ai,i_c,3));
            }
        }
      } break;
    }
  }
}
