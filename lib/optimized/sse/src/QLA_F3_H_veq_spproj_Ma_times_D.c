/**************** QLA_F3_H_veq_spproj_Ma_times_D.c ********************/

#include <stdio.h>
#include <qla_types.h>
#include <qla_random.h>
#include <qla_cmath.h>
#include <math.h>
#include "inline_sse.h"

void QLA_F3_H_veq_spproj_Ma_times_D ( QLA_F3_HalfFermion *__restrict__ r , QLA_F3_ColorMatrix  *a , QLA_F3_DiracFermion  *b , int mu, int sign , int n )
{
  if(sign==1) {
    switch(mu) {
    case 0: {
      int i;
      for(i=0;i<n;i++)
        {
          QLA_F3_HalfFermion t;
          QLA_F3_HalfFermion *ri = &r[i];
          QLA_F3_ColorMatrix *ai = &a[i];
          QLA_F3_DiracFermion *bi = &b[i];
          {
            int i_c;
            for(i_c=0;i_c<3;i_c++)
              {
                QLA_c_eq_c_plus_ic(QLA_F3_elem_H(t,i_c,0),                QLA_F3_elem_D(*bi,i_c,0),QLA_F3_elem_D(*bi,i_c,3))
                QLA_c_eq_c_plus_ic(QLA_F3_elem_H(t,i_c,1),                QLA_F3_elem_D(*bi,i_c,1),QLA_F3_elem_D(*bi,i_c,2))
              }
          }
          {
            QLA_F3_H_eq_Ma_times_H(ri, ai, &t);
          }
        }
      } break;
    case 1: {
      int i;
      for(i=0;i<n;i++)
        {
          QLA_F3_HalfFermion t;
          QLA_F3_HalfFermion *ri = &r[i];
          QLA_F3_ColorMatrix *ai = &a[i];
          QLA_F3_DiracFermion *bi = &b[i];
          {
            int i_c;
            for(i_c=0;i_c<3;i_c++)
              {
                QLA_c_eq_c_plus_c(QLA_F3_elem_H(t,i_c,0),                QLA_F3_elem_D(*bi,i_c,0),QLA_F3_elem_D(*bi,i_c,3))
                QLA_c_eq_c_minus_c(QLA_F3_elem_H(t,i_c,1),                QLA_F3_elem_D(*bi,i_c,1),QLA_F3_elem_D(*bi,i_c,2))
              }
          }
          {
            QLA_F3_H_eq_Ma_times_H(ri, ai, &t);
          }
        }
      } break;
    case 2: {
      int i;
      for(i=0;i<n;i++)
        {
          QLA_F3_HalfFermion t;
          QLA_F3_HalfFermion *ri = &r[i];
          QLA_F3_ColorMatrix *ai = &a[i];
          QLA_F3_DiracFermion *bi = &b[i];
          {
            int i_c;
            for(i_c=0;i_c<3;i_c++)
              {
                QLA_c_eq_c_plus_ic(QLA_F3_elem_H(t,i_c,0),                QLA_F3_elem_D(*bi,i_c,0),QLA_F3_elem_D(*bi,i_c,2))
                QLA_c_eq_c_minus_ic(QLA_F3_elem_H(t,i_c,1),                QLA_F3_elem_D(*bi,i_c,1),QLA_F3_elem_D(*bi,i_c,3))
              }
          }
          {
            QLA_F3_H_eq_Ma_times_H(ri, ai, &t);
          }
        }
      } break;
    case 3: {
      int i;
      for(i=0;i<n;i++)
        {
          QLA_F3_HalfFermion t;
          QLA_F3_HalfFermion *ri = &r[i];
          QLA_F3_ColorMatrix *ai = &a[i];
          QLA_F3_DiracFermion *bi = &b[i];
          {
            int i_c;
            for(i_c=0;i_c<3;i_c++)
              {
                QLA_c_eq_c_plus_c(QLA_F3_elem_H(t,i_c,0),                QLA_F3_elem_D(*bi,i_c,0),QLA_F3_elem_D(*bi,i_c,2))
                QLA_c_eq_c_plus_c(QLA_F3_elem_H(t,i_c,1),                QLA_F3_elem_D(*bi,i_c,1),QLA_F3_elem_D(*bi,i_c,3))
              }
          }
          {
            QLA_F3_H_eq_Ma_times_H(ri, ai, &t);
          }
        }
      } break;
    case 4: {
      int i;
      for(i=0;i<n;i++)
        {
          QLA_F3_HalfFermion t;
          QLA_F3_HalfFermion *ri = &r[i];
          QLA_F3_ColorMatrix *ai = &a[i];
          QLA_F3_DiracFermion *bi = &b[i];
          {
            int i_c;
            for(i_c=0;i_c<3;i_c++)
              {
                QLA_c_eq_c(QLA_F3_elem_H(t,i_c,0),                QLA_F3_elem_D(*bi,i_c,0))
                QLA_c_eq_c(QLA_F3_elem_H(t,i_c,1),                QLA_F3_elem_D(*bi,i_c,1))
              }
          }
          {
            QLA_F3_H_eq_Ma_times_H(ri, ai, &t);
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
          QLA_F3_HalfFermion *ri = &r[i];
          QLA_F3_ColorMatrix *ai = &a[i];
          QLA_F3_DiracFermion *bi = &b[i];
          {
            int i_c;
            for(i_c=0;i_c<3;i_c++)
              {
                QLA_c_eq_c_minus_ic(QLA_F3_elem_H(t,i_c,0),                QLA_F3_elem_D(*bi,i_c,0),QLA_F3_elem_D(*bi,i_c,3))
                QLA_c_eq_c_minus_ic(QLA_F3_elem_H(t,i_c,1),                QLA_F3_elem_D(*bi,i_c,1),QLA_F3_elem_D(*bi,i_c,2))
              }
          }
          {
            QLA_F3_H_eq_Ma_times_H(ri, ai, &t);
          }
        }
      } break;
    case 1: {
      int i;
      for(i=0;i<n;i++)
        {
          QLA_F3_HalfFermion t;
          QLA_F3_HalfFermion *ri = &r[i];
          QLA_F3_ColorMatrix *ai = &a[i];
          QLA_F3_DiracFermion *bi = &b[i];
          {
            int i_c;
            for(i_c=0;i_c<3;i_c++)
              {
                QLA_c_eq_c_minus_c(QLA_F3_elem_H(t,i_c,0),                QLA_F3_elem_D(*bi,i_c,0),QLA_F3_elem_D(*bi,i_c,3))
                QLA_c_eq_c_plus_c(QLA_F3_elem_H(t,i_c,1),                QLA_F3_elem_D(*bi,i_c,1),QLA_F3_elem_D(*bi,i_c,2))
              }
          }
          {
            QLA_F3_H_eq_Ma_times_H(ri, ai, &t);
          }
        }
      } break;
    case 2: {
      int i;
      for(i=0;i<n;i++)
        {
          QLA_F3_HalfFermion t;
          QLA_F3_HalfFermion *ri = &r[i];
          QLA_F3_ColorMatrix *ai = &a[i];
          QLA_F3_DiracFermion *bi = &b[i];
          {
            int i_c;
            for(i_c=0;i_c<3;i_c++)
              {
                QLA_c_eq_c_minus_ic(QLA_F3_elem_H(t,i_c,0),                QLA_F3_elem_D(*bi,i_c,0),QLA_F3_elem_D(*bi,i_c,2))
                QLA_c_eq_c_plus_ic(QLA_F3_elem_H(t,i_c,1),                QLA_F3_elem_D(*bi,i_c,1),QLA_F3_elem_D(*bi,i_c,3))
              }
          }
          {
            QLA_F3_H_eq_Ma_times_H(ri, ai, &t);
          }
        }
      } break;
    case 3: {
      int i;
      for(i=0;i<n;i++)
        {
          QLA_F3_HalfFermion t;
          QLA_F3_HalfFermion *ri = &r[i];
          QLA_F3_ColorMatrix *ai = &a[i];
          QLA_F3_DiracFermion *bi = &b[i];
          {
            int i_c;
            for(i_c=0;i_c<3;i_c++)
              {
                QLA_c_eq_c_minus_c(QLA_F3_elem_H(t,i_c,0),                QLA_F3_elem_D(*bi,i_c,0),QLA_F3_elem_D(*bi,i_c,2))
                QLA_c_eq_c_minus_c(QLA_F3_elem_H(t,i_c,1),                QLA_F3_elem_D(*bi,i_c,1),QLA_F3_elem_D(*bi,i_c,3))
              }
          }
          {
            QLA_F3_H_eq_Ma_times_H(ri, ai, &t);
          }
        }
      } break;
    case 4: {
      int i;
      for(i=0;i<n;i++)
        {
          QLA_F3_HalfFermion t;
          QLA_F3_HalfFermion *ri = &r[i];
          QLA_F3_ColorMatrix *ai = &a[i];
          QLA_F3_DiracFermion *bi = &b[i];
          {
            int i_c;
            for(i_c=0;i_c<3;i_c++)
              {
                QLA_c_eq_c(QLA_F3_elem_H(t,i_c,0),                QLA_F3_elem_D(*bi,i_c,2))
                QLA_c_eq_c(QLA_F3_elem_H(t,i_c,1),                QLA_F3_elem_D(*bi,i_c,3))
              }
          }
          {
            QLA_F3_H_eq_Ma_times_H(ri, ai, &t);
          }
        }
      } break;
    }
  }
}
