/**************** QLA_F3_D_vpeq_sprecon_M_times_pH.c ********************/

#include <stdio.h>
#include <qla_types.h>
#include <qla_random.h>
#include <qla_cmath.h>
#include <math.h>
#include "inline_sse.h"

void QLA_F3_D_vpeq_sprecon_M_times_pH ( QLA_F3_DiracFermion *__restrict__ r , QLA_F3_ColorMatrix  *a , QLA_F3_HalfFermion  **b , int mu, int sign , int n )
{
  if(sign==1) {
    switch(mu) {
    case 0: {
      int i;
      for(i=0;i<n;i++)
        {
          QLA_F3_HalfFermion t;
          QLA_F3_DiracFermion *ri = &r[i];
          QLA_F3_ColorMatrix *ai = &a[i];
          QLA_F3_HalfFermion *bi = b[i];
          {
            QLA_F3_H_eq_M_times_H(&t, ai, bi);
          }
          {
            int i_c;
            for(i_c=0;i_c<3;i_c++)
              {
                QLA_c_peq_c(QLA_F3_elem_D(*ri,i_c,0),QLA_F3_elem_H(t,i_c,0))
                QLA_c_peq_c(QLA_F3_elem_D(*ri,i_c,1),QLA_F3_elem_H(t,i_c,1))
                QLA_c_meq_ic(QLA_F3_elem_D(*ri,i_c,2),QLA_F3_elem_H(t,i_c,1))
                QLA_c_meq_ic(QLA_F3_elem_D(*ri,i_c,3),QLA_F3_elem_H(t,i_c,0))
              }
          }
        }
      } break;
    case 1: {
      int i;
      for(i=0;i<n;i++)
        {
          QLA_F3_HalfFermion t;
          QLA_F3_DiracFermion *ri = &r[i];
          QLA_F3_ColorMatrix *ai = &a[i];
          QLA_F3_HalfFermion *bi = b[i];
          {
            QLA_F3_H_eq_M_times_H(&t, ai, bi);
          }
          {
            int i_c;
            for(i_c=0;i_c<3;i_c++)
              {
                QLA_c_peq_c(QLA_F3_elem_D(*ri,i_c,0),QLA_F3_elem_H(t,i_c,0))
                QLA_c_peq_c(QLA_F3_elem_D(*ri,i_c,1),QLA_F3_elem_H(t,i_c,1))
                QLA_c_meq_c(QLA_F3_elem_D(*ri,i_c,2),QLA_F3_elem_H(t,i_c,1))
                QLA_c_peq_c(QLA_F3_elem_D(*ri,i_c,3),QLA_F3_elem_H(t,i_c,0))
              }
          }
        }
      } break;
    case 2: {
      int i;
      for(i=0;i<n;i++)
        {
          QLA_F3_HalfFermion t;
          QLA_F3_DiracFermion *ri = &r[i];
          QLA_F3_ColorMatrix *ai = &a[i];
          QLA_F3_HalfFermion *bi = b[i];
          {
            QLA_F3_H_eq_M_times_H(&t, ai, bi);
          }
          {
            int i_c;
            for(i_c=0;i_c<3;i_c++)
              {
                QLA_c_peq_c(QLA_F3_elem_D(*ri,i_c,0),QLA_F3_elem_H(t,i_c,0))
                QLA_c_peq_c(QLA_F3_elem_D(*ri,i_c,1),QLA_F3_elem_H(t,i_c,1))
                QLA_c_meq_ic(QLA_F3_elem_D(*ri,i_c,2),QLA_F3_elem_H(t,i_c,0))
                QLA_c_peq_ic(QLA_F3_elem_D(*ri,i_c,3),QLA_F3_elem_H(t,i_c,1))
              }
          }
        }
      } break;
    case 3: {
      int i;
      for(i=0;i<n;i++)
        {
          QLA_F3_HalfFermion t;
          QLA_F3_DiracFermion *ri = &r[i];
          QLA_F3_ColorMatrix *ai = &a[i];
          QLA_F3_HalfFermion *bi = b[i];
          {
            QLA_F3_H_eq_M_times_H(&t, ai, bi);
          }
          {
            int i_c;
            for(i_c=0;i_c<3;i_c++)
              {
                QLA_c_peq_c(QLA_F3_elem_D(*ri,i_c,0),QLA_F3_elem_H(t,i_c,0))
                QLA_c_peq_c(QLA_F3_elem_D(*ri,i_c,1),QLA_F3_elem_H(t,i_c,1))
                QLA_c_peq_c(QLA_F3_elem_D(*ri,i_c,2),QLA_F3_elem_H(t,i_c,0))
                QLA_c_peq_c(QLA_F3_elem_D(*ri,i_c,3),QLA_F3_elem_H(t,i_c,1))
              }
          }
        }
      } break;
    case 4: {
      int i;
      for(i=0;i<n;i++)
        {
          QLA_F3_HalfFermion t;
          QLA_F3_DiracFermion *ri = &r[i];
          QLA_F3_ColorMatrix *ai = &a[i];
          QLA_F3_HalfFermion *bi = b[i];
          {
            QLA_F3_H_eq_M_times_H(&t, ai, bi);
          }
          {
            int i_c;
            for(i_c=0;i_c<3;i_c++)
              {
                QLA_c_peq_c(QLA_F3_elem_D(*ri,i_c,0),QLA_F3_elem_H(t,i_c,0))
                QLA_c_peq_c(QLA_F3_elem_D(*ri,i_c,1),QLA_F3_elem_H(t,i_c,1))
              }
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
          QLA_F3_HalfFermion t;
          QLA_F3_DiracFermion *ri = &r[i];
          QLA_F3_ColorMatrix *ai = &a[i];
          QLA_F3_HalfFermion *bi = b[i];
          {
            QLA_F3_H_eq_M_times_H(&t, ai, bi);
          }
          {
            int i_c;
            for(i_c=0;i_c<3;i_c++)
              {
                QLA_c_peq_c(QLA_F3_elem_D(*ri,i_c,0),QLA_F3_elem_H(t,i_c,0))
                QLA_c_peq_c(QLA_F3_elem_D(*ri,i_c,1),QLA_F3_elem_H(t,i_c,1))
                QLA_c_peq_ic(QLA_F3_elem_D(*ri,i_c,2),QLA_F3_elem_H(t,i_c,1))
                QLA_c_peq_ic(QLA_F3_elem_D(*ri,i_c,3),QLA_F3_elem_H(t,i_c,0))
              }
          }
        }
      } break;
    case 1: {
      int i;
      for(i=0;i<n;i++)
        {
          QLA_F3_HalfFermion t;
          QLA_F3_DiracFermion *ri = &r[i];
          QLA_F3_ColorMatrix *ai = &a[i];
          QLA_F3_HalfFermion *bi = b[i];
          {
            QLA_F3_H_eq_M_times_H(&t, ai, bi);
          }
          {
            int i_c;
            for(i_c=0;i_c<3;i_c++)
              {
                QLA_c_peq_c(QLA_F3_elem_D(*ri,i_c,0),QLA_F3_elem_H(t,i_c,0))
                QLA_c_peq_c(QLA_F3_elem_D(*ri,i_c,1),QLA_F3_elem_H(t,i_c,1))
                QLA_c_peq_c(QLA_F3_elem_D(*ri,i_c,2),QLA_F3_elem_H(t,i_c,1))
                QLA_c_meq_c(QLA_F3_elem_D(*ri,i_c,3),QLA_F3_elem_H(t,i_c,0))
              }
          }
        }
      } break;
    case 2: {
      int i;
      for(i=0;i<n;i++)
        {
          QLA_F3_HalfFermion t;
          QLA_F3_DiracFermion *ri = &r[i];
          QLA_F3_ColorMatrix *ai = &a[i];
          QLA_F3_HalfFermion *bi = b[i];
          {
            QLA_F3_H_eq_M_times_H(&t, ai, bi);
          }
          {
            int i_c;
            for(i_c=0;i_c<3;i_c++)
              {
                QLA_c_peq_c(QLA_F3_elem_D(*ri,i_c,0),QLA_F3_elem_H(t,i_c,0))
                QLA_c_peq_c(QLA_F3_elem_D(*ri,i_c,1),QLA_F3_elem_H(t,i_c,1))
                QLA_c_peq_ic(QLA_F3_elem_D(*ri,i_c,2),QLA_F3_elem_H(t,i_c,0))
                QLA_c_meq_ic(QLA_F3_elem_D(*ri,i_c,3),QLA_F3_elem_H(t,i_c,1))
              }
          }
        }
      } break;
    case 3: {
      int i;
      for(i=0;i<n;i++)
        {
          QLA_F3_HalfFermion t;
          QLA_F3_DiracFermion *ri = &r[i];
          QLA_F3_ColorMatrix *ai = &a[i];
          QLA_F3_HalfFermion *bi = b[i];
          {
            QLA_F3_H_eq_M_times_H(&t, ai, bi);
          }
          {
            int i_c;
            for(i_c=0;i_c<3;i_c++)
              {
                QLA_c_peq_c(QLA_F3_elem_D(*ri,i_c,0),QLA_F3_elem_H(t,i_c,0))
                QLA_c_peq_c(QLA_F3_elem_D(*ri,i_c,1),QLA_F3_elem_H(t,i_c,1))
                QLA_c_meq_c(QLA_F3_elem_D(*ri,i_c,2),QLA_F3_elem_H(t,i_c,0))
                QLA_c_meq_c(QLA_F3_elem_D(*ri,i_c,3),QLA_F3_elem_H(t,i_c,1))
              }
          }
        }
      } break;
    case 4: {
      int i;
      for(i=0;i<n;i++)
        {
          QLA_F3_HalfFermion t;
          QLA_F3_DiracFermion *ri = &r[i];
          QLA_F3_ColorMatrix *ai = &a[i];
          QLA_F3_HalfFermion *bi = b[i];
          {
            QLA_F3_H_eq_M_times_H(&t, ai, bi);
          }
          {
            int i_c;
            for(i_c=0;i_c<3;i_c++)
              {
                QLA_c_peq_c(QLA_F3_elem_D(*ri,i_c,2),QLA_F3_elem_H(t,i_c,0))
                QLA_c_peq_c(QLA_F3_elem_D(*ri,i_c,3),QLA_F3_elem_H(t,i_c,1))
              }
          }
        }
      } break;
    }
  }
}
