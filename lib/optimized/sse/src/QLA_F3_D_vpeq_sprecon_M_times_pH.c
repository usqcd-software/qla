/**************** QLA_F3_D_vpeq_sprecon_M_times_pH.c ********************/

#include <stdio.h>
#include <qla_config.h>
#include <qla_types.h>
#include <qla_random.h>
#include <qla_cmath.h>
#include <qla_sse.h>
#include <math.h>

#define SPR 0p
static inline void
QLA_F3_D_vpeq_sprecon_M_times_pH_0p_sse( QLA_F3_DiracFermion *restrict r,
					 QLA_F3_ColorMatrix *restrict a,
					 QLA_F3_HalfFermion *restrict *b,
					 int n )
#include <QLA_F3_D_vpeq_sprecon_M_times_pH_sse.c>
#undef SPR

#define SPR 1p
static inline void
QLA_F3_D_vpeq_sprecon_M_times_pH_1p_sse( QLA_F3_DiracFermion *restrict r,
					 QLA_F3_ColorMatrix *restrict a,
					 QLA_F3_HalfFermion *restrict *b,
					 int n )
#include <QLA_F3_D_vpeq_sprecon_M_times_pH_sse.c>
#undef SPR

#define SPR 2p
static inline void
QLA_F3_D_vpeq_sprecon_M_times_pH_2p_sse( QLA_F3_DiracFermion *restrict r,
					 QLA_F3_ColorMatrix *restrict a,
					 QLA_F3_HalfFermion *restrict *b,
					 int n )
#include <QLA_F3_D_vpeq_sprecon_M_times_pH_sse.c>
#undef SPR

#define SPR 3p
static inline void
QLA_F3_D_vpeq_sprecon_M_times_pH_3p_sse( QLA_F3_DiracFermion *restrict r,
					 QLA_F3_ColorMatrix *restrict a,
					 QLA_F3_HalfFermion *restrict *b,
					 int n )
#include <QLA_F3_D_vpeq_sprecon_M_times_pH_sse.c>
#undef SPR

#define GAMMA_5_PLUS
static inline void
QLA_F3_D_vpeq_sprecon_M_times_pH_4p_sse( QLA_F3_DiracFermion *restrict r,
					 QLA_F3_ColorMatrix *restrict a,
					 QLA_F3_HalfFermion *restrict *b,
					 int n )
#include <QLA_F3_D_vpeq_sprecon_M_times_pH_sse.c>
#undef GAMMA_5_PLUS

#define SPR 0m
static inline void
QLA_F3_D_vpeq_sprecon_M_times_pH_0m_sse( QLA_F3_DiracFermion *restrict r,
					 QLA_F3_ColorMatrix *restrict a,
					 QLA_F3_HalfFermion *restrict *b,
					 int n )
#include <QLA_F3_D_vpeq_sprecon_M_times_pH_sse.c>
#undef SPR

#define SPR 1m
static inline void
QLA_F3_D_vpeq_sprecon_M_times_pH_1m_sse( QLA_F3_DiracFermion *restrict r,
					 QLA_F3_ColorMatrix *restrict a,
					 QLA_F3_HalfFermion *restrict *b,
					 int n )
#include <QLA_F3_D_vpeq_sprecon_M_times_pH_sse.c>
#undef SPR

#define SPR 2m
static inline void
QLA_F3_D_vpeq_sprecon_M_times_pH_2m_sse( QLA_F3_DiracFermion *restrict r,
					 QLA_F3_ColorMatrix *restrict a,
					 QLA_F3_HalfFermion *restrict *b,
					 int n )
#include <QLA_F3_D_vpeq_sprecon_M_times_pH_sse.c>
#undef SPR

#define SPR 3m
static inline void
QLA_F3_D_vpeq_sprecon_M_times_pH_3m_sse( QLA_F3_DiracFermion *restrict r,
					 QLA_F3_ColorMatrix *restrict a,
					 QLA_F3_HalfFermion *restrict *b,
					 int n )
#include <QLA_F3_D_vpeq_sprecon_M_times_pH_sse.c>
#undef SPR

#define GAMMA_5_MINUS
static inline void
QLA_F3_D_vpeq_sprecon_M_times_pH_4m_sse( QLA_F3_DiracFermion *restrict r,
					 QLA_F3_ColorMatrix *restrict a,
					 QLA_F3_HalfFermion *restrict *b,
					 int n )
#include <QLA_F3_D_vpeq_sprecon_M_times_pH_sse.c>
#undef GAMMA_5_MINUS


void
QLA_F3_D_vpeq_sprecon_M_times_pH( QLA_F3_DiracFermion *restrict r,
				  QLA_F3_ColorMatrix *restrict a,
				  QLA_F3_HalfFermion *restrict *b,
				  int mu, int sign, int n )
{
  if( is_aligned(r,16) && is_aligned(a,8) && is_aligned(b[0],16) ) {
    if(sign==1) {
      switch(mu) {
      case 0: {
	QLA_F3_D_vpeq_sprecon_M_times_pH_0p_sse(r, a, b, n);
      } break;
      case 1: {
	QLA_F3_D_vpeq_sprecon_M_times_pH_1p_sse(r, a, b, n);
      } break;
      case 2: {
	QLA_F3_D_vpeq_sprecon_M_times_pH_2p_sse(r, a, b, n);
      } break;
      case 3: {
	QLA_F3_D_vpeq_sprecon_M_times_pH_3p_sse(r, a, b, n);
      } break;
      case 4: {
	QLA_F3_D_vpeq_sprecon_M_times_pH_4p_sse(r, a, b, n);
      } break;
      }
    } else {
      switch(mu) {
      case 0: {
	QLA_F3_D_vpeq_sprecon_M_times_pH_0m_sse(r, a, b, n);
      } break;
      case 1: {
	QLA_F3_D_vpeq_sprecon_M_times_pH_1m_sse(r, a, b, n);
      } break;
      case 2: {
	QLA_F3_D_vpeq_sprecon_M_times_pH_2m_sse(r, a, b, n);
      } break;
      case 3: {
	QLA_F3_D_vpeq_sprecon_M_times_pH_3m_sse(r, a, b, n);
      } break;
      case 4: {
	QLA_F3_D_vpeq_sprecon_M_times_pH_4m_sse(r, a, b, n);
      } break;
      }
    }
  } else {  /* not aligned */
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
	      QLA_F_Real tr00, tr01, tr10, tr11, tr20, tr21;
	      QLA_F_Real ti00, ti01, ti10, ti11, ti20, ti21;
	      int k_c;
	      tr00 = 0.;
	      ti00 = 0.;
	      tr01 = 0.;
	      ti01 = 0.;
	      tr10 = 0.;
	      ti10 = 0.;
	      tr11 = 0.;
	      ti11 = 0.;
	      tr20 = 0.;
	      ti20 = 0.;
	      tr21 = 0.;
	      ti21 = 0.;
	      for(k_c=0;k_c<3;k_c++)
		{
		  QLA_F_Real xr0, xr1;
		  QLA_F_Real xi0, xi1;
		  xr0 = QLA_real(QLA_F3_elem_H(*bi,k_c,0));
		  xi0 = QLA_imag(QLA_F3_elem_H(*bi,k_c,0));
		  xr1 = QLA_real(QLA_F3_elem_H(*bi,k_c,1));
		  xi1 = QLA_imag(QLA_F3_elem_H(*bi,k_c,1));
		  tr00 += QLA_real(QLA_F3_elem_M(*ai,0,k_c)) * xr0;
		  ti00 += QLA_imag(QLA_F3_elem_M(*ai,0,k_c)) * xr0;
		  tr01 += QLA_real(QLA_F3_elem_M(*ai,0,k_c)) * xr1;
		  ti01 += QLA_imag(QLA_F3_elem_M(*ai,0,k_c)) * xr1;
		  tr10 += QLA_real(QLA_F3_elem_M(*ai,1,k_c)) * xr0;
		  ti10 += QLA_imag(QLA_F3_elem_M(*ai,1,k_c)) * xr0;
		  tr11 += QLA_real(QLA_F3_elem_M(*ai,1,k_c)) * xr1;
		  ti11 += QLA_imag(QLA_F3_elem_M(*ai,1,k_c)) * xr1;
		  tr20 += QLA_real(QLA_F3_elem_M(*ai,2,k_c)) * xr0;
		  ti20 += QLA_imag(QLA_F3_elem_M(*ai,2,k_c)) * xr0;
		  tr21 += QLA_real(QLA_F3_elem_M(*ai,2,k_c)) * xr1;
		  ti21 += QLA_imag(QLA_F3_elem_M(*ai,2,k_c)) * xr1;
		  tr00 -= QLA_imag(QLA_F3_elem_M(*ai,0,k_c)) * xi0;
		  ti00 += QLA_real(QLA_F3_elem_M(*ai,0,k_c)) * xi0;
		  tr01 -= QLA_imag(QLA_F3_elem_M(*ai,0,k_c)) * xi1;
		  ti01 += QLA_real(QLA_F3_elem_M(*ai,0,k_c)) * xi1;
		  tr10 -= QLA_imag(QLA_F3_elem_M(*ai,1,k_c)) * xi0;
		  ti10 += QLA_real(QLA_F3_elem_M(*ai,1,k_c)) * xi0;
		  tr11 -= QLA_imag(QLA_F3_elem_M(*ai,1,k_c)) * xi1;
		  ti11 += QLA_real(QLA_F3_elem_M(*ai,1,k_c)) * xi1;
		  tr20 -= QLA_imag(QLA_F3_elem_M(*ai,2,k_c)) * xi0;
		  ti20 += QLA_real(QLA_F3_elem_M(*ai,2,k_c)) * xi0;
		  tr21 -= QLA_imag(QLA_F3_elem_M(*ai,2,k_c)) * xi1;
		  ti21 += QLA_real(QLA_F3_elem_M(*ai,2,k_c)) * xi1;
		}
	      QLA_real(QLA_F3_elem_H(t,0,0)) = tr00;
	      QLA_imag(QLA_F3_elem_H(t,0,0)) = ti00;
	      QLA_real(QLA_F3_elem_H(t,0,1)) = tr01;
	      QLA_imag(QLA_F3_elem_H(t,0,1)) = ti01;
	      QLA_real(QLA_F3_elem_H(t,1,0)) = tr10;
	      QLA_imag(QLA_F3_elem_H(t,1,0)) = ti10;
	      QLA_real(QLA_F3_elem_H(t,1,1)) = tr11;
	      QLA_imag(QLA_F3_elem_H(t,1,1)) = ti11;
	      QLA_real(QLA_F3_elem_H(t,2,0)) = tr20;
	      QLA_imag(QLA_F3_elem_H(t,2,0)) = ti20;
	      QLA_real(QLA_F3_elem_H(t,2,1)) = tr21;
	      QLA_imag(QLA_F3_elem_H(t,2,1)) = ti21;
	    }
	    {
	      int i_c;
	      for(i_c=0;i_c<3;i_c++)
		{
		  QLA_c_peq_c(QLA_F3_elem_D(*ri,i_c,0),QLA_F3_elem_H(t,i_c,0));
		  QLA_c_peq_c(QLA_F3_elem_D(*ri,i_c,1),QLA_F3_elem_H(t,i_c,1));
		  QLA_c_meq_ic(QLA_F3_elem_D(*ri,i_c,2),QLA_F3_elem_H(t,i_c,1));
		  QLA_c_meq_ic(QLA_F3_elem_D(*ri,i_c,3),QLA_F3_elem_H(t,i_c,0));
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
	      QLA_F_Real tr00, tr01, tr10, tr11, tr20, tr21;
	      QLA_F_Real ti00, ti01, ti10, ti11, ti20, ti21;
	      int k_c;
	      tr00 = 0.;
	      ti00 = 0.;
	      tr01 = 0.;
	      ti01 = 0.;
	      tr10 = 0.;
	      ti10 = 0.;
	      tr11 = 0.;
	      ti11 = 0.;
	      tr20 = 0.;
	      ti20 = 0.;
	      tr21 = 0.;
	      ti21 = 0.;
	      for(k_c=0;k_c<3;k_c++)
		{
		  QLA_F_Real xr0, xr1;
		  QLA_F_Real xi0, xi1;
		  xr0 = QLA_real(QLA_F3_elem_H(*bi,k_c,0));
		  xi0 = QLA_imag(QLA_F3_elem_H(*bi,k_c,0));
		  xr1 = QLA_real(QLA_F3_elem_H(*bi,k_c,1));
		  xi1 = QLA_imag(QLA_F3_elem_H(*bi,k_c,1));
		  tr00 += QLA_real(QLA_F3_elem_M(*ai,0,k_c)) * xr0;
		  ti00 += QLA_imag(QLA_F3_elem_M(*ai,0,k_c)) * xr0;
		  tr01 += QLA_real(QLA_F3_elem_M(*ai,0,k_c)) * xr1;
		  ti01 += QLA_imag(QLA_F3_elem_M(*ai,0,k_c)) * xr1;
		  tr10 += QLA_real(QLA_F3_elem_M(*ai,1,k_c)) * xr0;
		  ti10 += QLA_imag(QLA_F3_elem_M(*ai,1,k_c)) * xr0;
		  tr11 += QLA_real(QLA_F3_elem_M(*ai,1,k_c)) * xr1;
		  ti11 += QLA_imag(QLA_F3_elem_M(*ai,1,k_c)) * xr1;
		  tr20 += QLA_real(QLA_F3_elem_M(*ai,2,k_c)) * xr0;
		  ti20 += QLA_imag(QLA_F3_elem_M(*ai,2,k_c)) * xr0;
		  tr21 += QLA_real(QLA_F3_elem_M(*ai,2,k_c)) * xr1;
		  ti21 += QLA_imag(QLA_F3_elem_M(*ai,2,k_c)) * xr1;
		  tr00 -= QLA_imag(QLA_F3_elem_M(*ai,0,k_c)) * xi0;
		  ti00 += QLA_real(QLA_F3_elem_M(*ai,0,k_c)) * xi0;
		  tr01 -= QLA_imag(QLA_F3_elem_M(*ai,0,k_c)) * xi1;
		  ti01 += QLA_real(QLA_F3_elem_M(*ai,0,k_c)) * xi1;
		  tr10 -= QLA_imag(QLA_F3_elem_M(*ai,1,k_c)) * xi0;
		  ti10 += QLA_real(QLA_F3_elem_M(*ai,1,k_c)) * xi0;
		  tr11 -= QLA_imag(QLA_F3_elem_M(*ai,1,k_c)) * xi1;
		  ti11 += QLA_real(QLA_F3_elem_M(*ai,1,k_c)) * xi1;
		  tr20 -= QLA_imag(QLA_F3_elem_M(*ai,2,k_c)) * xi0;
		  ti20 += QLA_real(QLA_F3_elem_M(*ai,2,k_c)) * xi0;
		  tr21 -= QLA_imag(QLA_F3_elem_M(*ai,2,k_c)) * xi1;
		  ti21 += QLA_real(QLA_F3_elem_M(*ai,2,k_c)) * xi1;
		}
	      QLA_real(QLA_F3_elem_H(t,0,0)) = tr00;
	      QLA_imag(QLA_F3_elem_H(t,0,0)) = ti00;
	      QLA_real(QLA_F3_elem_H(t,0,1)) = tr01;
	      QLA_imag(QLA_F3_elem_H(t,0,1)) = ti01;
	      QLA_real(QLA_F3_elem_H(t,1,0)) = tr10;
	      QLA_imag(QLA_F3_elem_H(t,1,0)) = ti10;
	      QLA_real(QLA_F3_elem_H(t,1,1)) = tr11;
	      QLA_imag(QLA_F3_elem_H(t,1,1)) = ti11;
	      QLA_real(QLA_F3_elem_H(t,2,0)) = tr20;
	      QLA_imag(QLA_F3_elem_H(t,2,0)) = ti20;
	      QLA_real(QLA_F3_elem_H(t,2,1)) = tr21;
	      QLA_imag(QLA_F3_elem_H(t,2,1)) = ti21;
	    }
	    {
	      int i_c;
	      for(i_c=0;i_c<3;i_c++)
		{
		  QLA_c_peq_c(QLA_F3_elem_D(*ri,i_c,0),QLA_F3_elem_H(t,i_c,0));
		  QLA_c_peq_c(QLA_F3_elem_D(*ri,i_c,1),QLA_F3_elem_H(t,i_c,1));
		  QLA_c_meq_c(QLA_F3_elem_D(*ri,i_c,2),QLA_F3_elem_H(t,i_c,1));
		  QLA_c_peq_c(QLA_F3_elem_D(*ri,i_c,3),QLA_F3_elem_H(t,i_c,0));
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
	      QLA_F_Real tr00, tr01, tr10, tr11, tr20, tr21;
	      QLA_F_Real ti00, ti01, ti10, ti11, ti20, ti21;
	      int k_c;
	      tr00 = 0.;
	      ti00 = 0.;
	      tr01 = 0.;
	      ti01 = 0.;
	      tr10 = 0.;
	      ti10 = 0.;
	      tr11 = 0.;
	      ti11 = 0.;
	      tr20 = 0.;
	      ti20 = 0.;
	      tr21 = 0.;
	      ti21 = 0.;
	      for(k_c=0;k_c<3;k_c++)
		{
		  QLA_F_Real xr0, xr1;
		  QLA_F_Real xi0, xi1;
		  xr0 = QLA_real(QLA_F3_elem_H(*bi,k_c,0));
		  xi0 = QLA_imag(QLA_F3_elem_H(*bi,k_c,0));
		  xr1 = QLA_real(QLA_F3_elem_H(*bi,k_c,1));
		  xi1 = QLA_imag(QLA_F3_elem_H(*bi,k_c,1));
		  tr00 += QLA_real(QLA_F3_elem_M(*ai,0,k_c)) * xr0;
		  ti00 += QLA_imag(QLA_F3_elem_M(*ai,0,k_c)) * xr0;
		  tr01 += QLA_real(QLA_F3_elem_M(*ai,0,k_c)) * xr1;
		  ti01 += QLA_imag(QLA_F3_elem_M(*ai,0,k_c)) * xr1;
		  tr10 += QLA_real(QLA_F3_elem_M(*ai,1,k_c)) * xr0;
		  ti10 += QLA_imag(QLA_F3_elem_M(*ai,1,k_c)) * xr0;
		  tr11 += QLA_real(QLA_F3_elem_M(*ai,1,k_c)) * xr1;
		  ti11 += QLA_imag(QLA_F3_elem_M(*ai,1,k_c)) * xr1;
		  tr20 += QLA_real(QLA_F3_elem_M(*ai,2,k_c)) * xr0;
		  ti20 += QLA_imag(QLA_F3_elem_M(*ai,2,k_c)) * xr0;
		  tr21 += QLA_real(QLA_F3_elem_M(*ai,2,k_c)) * xr1;
		  ti21 += QLA_imag(QLA_F3_elem_M(*ai,2,k_c)) * xr1;
		  tr00 -= QLA_imag(QLA_F3_elem_M(*ai,0,k_c)) * xi0;
		  ti00 += QLA_real(QLA_F3_elem_M(*ai,0,k_c)) * xi0;
		  tr01 -= QLA_imag(QLA_F3_elem_M(*ai,0,k_c)) * xi1;
		  ti01 += QLA_real(QLA_F3_elem_M(*ai,0,k_c)) * xi1;
		  tr10 -= QLA_imag(QLA_F3_elem_M(*ai,1,k_c)) * xi0;
		  ti10 += QLA_real(QLA_F3_elem_M(*ai,1,k_c)) * xi0;
		  tr11 -= QLA_imag(QLA_F3_elem_M(*ai,1,k_c)) * xi1;
		  ti11 += QLA_real(QLA_F3_elem_M(*ai,1,k_c)) * xi1;
		  tr20 -= QLA_imag(QLA_F3_elem_M(*ai,2,k_c)) * xi0;
		  ti20 += QLA_real(QLA_F3_elem_M(*ai,2,k_c)) * xi0;
		  tr21 -= QLA_imag(QLA_F3_elem_M(*ai,2,k_c)) * xi1;
		  ti21 += QLA_real(QLA_F3_elem_M(*ai,2,k_c)) * xi1;
		}
	      QLA_real(QLA_F3_elem_H(t,0,0)) = tr00;
	      QLA_imag(QLA_F3_elem_H(t,0,0)) = ti00;
	      QLA_real(QLA_F3_elem_H(t,0,1)) = tr01;
	      QLA_imag(QLA_F3_elem_H(t,0,1)) = ti01;
	      QLA_real(QLA_F3_elem_H(t,1,0)) = tr10;
	      QLA_imag(QLA_F3_elem_H(t,1,0)) = ti10;
	      QLA_real(QLA_F3_elem_H(t,1,1)) = tr11;
	      QLA_imag(QLA_F3_elem_H(t,1,1)) = ti11;
	      QLA_real(QLA_F3_elem_H(t,2,0)) = tr20;
	      QLA_imag(QLA_F3_elem_H(t,2,0)) = ti20;
	      QLA_real(QLA_F3_elem_H(t,2,1)) = tr21;
	      QLA_imag(QLA_F3_elem_H(t,2,1)) = ti21;
	    }
	    {
	      int i_c;
	      for(i_c=0;i_c<3;i_c++)
		{
		  QLA_c_peq_c(QLA_F3_elem_D(*ri,i_c,0),QLA_F3_elem_H(t,i_c,0));
		  QLA_c_peq_c(QLA_F3_elem_D(*ri,i_c,1),QLA_F3_elem_H(t,i_c,1));
		  QLA_c_meq_ic(QLA_F3_elem_D(*ri,i_c,2),QLA_F3_elem_H(t,i_c,0));
		  QLA_c_peq_ic(QLA_F3_elem_D(*ri,i_c,3),QLA_F3_elem_H(t,i_c,1));
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
	      QLA_F_Real tr00, tr01, tr10, tr11, tr20, tr21;
	      QLA_F_Real ti00, ti01, ti10, ti11, ti20, ti21;
	      int k_c;
	      tr00 = 0.;
	      ti00 = 0.;
	      tr01 = 0.;
	      ti01 = 0.;
	      tr10 = 0.;
	      ti10 = 0.;
	      tr11 = 0.;
	      ti11 = 0.;
	      tr20 = 0.;
	      ti20 = 0.;
	      tr21 = 0.;
	      ti21 = 0.;
	      for(k_c=0;k_c<3;k_c++)
		{
		  QLA_F_Real xr0, xr1;
		  QLA_F_Real xi0, xi1;
		  xr0 = QLA_real(QLA_F3_elem_H(*bi,k_c,0));
		  xi0 = QLA_imag(QLA_F3_elem_H(*bi,k_c,0));
		  xr1 = QLA_real(QLA_F3_elem_H(*bi,k_c,1));
		  xi1 = QLA_imag(QLA_F3_elem_H(*bi,k_c,1));
		  tr00 += QLA_real(QLA_F3_elem_M(*ai,0,k_c)) * xr0;
		  ti00 += QLA_imag(QLA_F3_elem_M(*ai,0,k_c)) * xr0;
		  tr01 += QLA_real(QLA_F3_elem_M(*ai,0,k_c)) * xr1;
		  ti01 += QLA_imag(QLA_F3_elem_M(*ai,0,k_c)) * xr1;
		  tr10 += QLA_real(QLA_F3_elem_M(*ai,1,k_c)) * xr0;
		  ti10 += QLA_imag(QLA_F3_elem_M(*ai,1,k_c)) * xr0;
		  tr11 += QLA_real(QLA_F3_elem_M(*ai,1,k_c)) * xr1;
		  ti11 += QLA_imag(QLA_F3_elem_M(*ai,1,k_c)) * xr1;
		  tr20 += QLA_real(QLA_F3_elem_M(*ai,2,k_c)) * xr0;
		  ti20 += QLA_imag(QLA_F3_elem_M(*ai,2,k_c)) * xr0;
		  tr21 += QLA_real(QLA_F3_elem_M(*ai,2,k_c)) * xr1;
		  ti21 += QLA_imag(QLA_F3_elem_M(*ai,2,k_c)) * xr1;
		  tr00 -= QLA_imag(QLA_F3_elem_M(*ai,0,k_c)) * xi0;
		  ti00 += QLA_real(QLA_F3_elem_M(*ai,0,k_c)) * xi0;
		  tr01 -= QLA_imag(QLA_F3_elem_M(*ai,0,k_c)) * xi1;
		  ti01 += QLA_real(QLA_F3_elem_M(*ai,0,k_c)) * xi1;
		  tr10 -= QLA_imag(QLA_F3_elem_M(*ai,1,k_c)) * xi0;
		  ti10 += QLA_real(QLA_F3_elem_M(*ai,1,k_c)) * xi0;
		  tr11 -= QLA_imag(QLA_F3_elem_M(*ai,1,k_c)) * xi1;
		  ti11 += QLA_real(QLA_F3_elem_M(*ai,1,k_c)) * xi1;
		  tr20 -= QLA_imag(QLA_F3_elem_M(*ai,2,k_c)) * xi0;
		  ti20 += QLA_real(QLA_F3_elem_M(*ai,2,k_c)) * xi0;
		  tr21 -= QLA_imag(QLA_F3_elem_M(*ai,2,k_c)) * xi1;
		  ti21 += QLA_real(QLA_F3_elem_M(*ai,2,k_c)) * xi1;
		}
	      QLA_real(QLA_F3_elem_H(t,0,0)) = tr00;
	      QLA_imag(QLA_F3_elem_H(t,0,0)) = ti00;
	      QLA_real(QLA_F3_elem_H(t,0,1)) = tr01;
	      QLA_imag(QLA_F3_elem_H(t,0,1)) = ti01;
	      QLA_real(QLA_F3_elem_H(t,1,0)) = tr10;
	      QLA_imag(QLA_F3_elem_H(t,1,0)) = ti10;
	      QLA_real(QLA_F3_elem_H(t,1,1)) = tr11;
	      QLA_imag(QLA_F3_elem_H(t,1,1)) = ti11;
	      QLA_real(QLA_F3_elem_H(t,2,0)) = tr20;
	      QLA_imag(QLA_F3_elem_H(t,2,0)) = ti20;
	      QLA_real(QLA_F3_elem_H(t,2,1)) = tr21;
	      QLA_imag(QLA_F3_elem_H(t,2,1)) = ti21;
	    }
	    {
	      int i_c;
	      for(i_c=0;i_c<3;i_c++)
		{
		  QLA_c_peq_c(QLA_F3_elem_D(*ri,i_c,0),QLA_F3_elem_H(t,i_c,0));
		  QLA_c_peq_c(QLA_F3_elem_D(*ri,i_c,1),QLA_F3_elem_H(t,i_c,1));
		  QLA_c_peq_c(QLA_F3_elem_D(*ri,i_c,2),QLA_F3_elem_H(t,i_c,0));
		  QLA_c_peq_c(QLA_F3_elem_D(*ri,i_c,3),QLA_F3_elem_H(t,i_c,1));
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
	      QLA_F_Real tr00, tr01, tr10, tr11, tr20, tr21;
	      QLA_F_Real ti00, ti01, ti10, ti11, ti20, ti21;
	      int k_c;
	      tr00 = 0.;
	      ti00 = 0.;
	      tr01 = 0.;
	      ti01 = 0.;
	      tr10 = 0.;
	      ti10 = 0.;
	      tr11 = 0.;
	      ti11 = 0.;
	      tr20 = 0.;
	      ti20 = 0.;
	      tr21 = 0.;
	      ti21 = 0.;
	      for(k_c=0;k_c<3;k_c++)
		{
		  QLA_F_Real xr0, xr1;
		  QLA_F_Real xi0, xi1;
		  xr0 = QLA_real(QLA_F3_elem_H(*bi,k_c,0));
		  xi0 = QLA_imag(QLA_F3_elem_H(*bi,k_c,0));
		  xr1 = QLA_real(QLA_F3_elem_H(*bi,k_c,1));
		  xi1 = QLA_imag(QLA_F3_elem_H(*bi,k_c,1));
		  tr00 += QLA_real(QLA_F3_elem_M(*ai,0,k_c)) * xr0;
		  ti00 += QLA_imag(QLA_F3_elem_M(*ai,0,k_c)) * xr0;
		  tr01 += QLA_real(QLA_F3_elem_M(*ai,0,k_c)) * xr1;
		  ti01 += QLA_imag(QLA_F3_elem_M(*ai,0,k_c)) * xr1;
		  tr10 += QLA_real(QLA_F3_elem_M(*ai,1,k_c)) * xr0;
		  ti10 += QLA_imag(QLA_F3_elem_M(*ai,1,k_c)) * xr0;
		  tr11 += QLA_real(QLA_F3_elem_M(*ai,1,k_c)) * xr1;
		  ti11 += QLA_imag(QLA_F3_elem_M(*ai,1,k_c)) * xr1;
		  tr20 += QLA_real(QLA_F3_elem_M(*ai,2,k_c)) * xr0;
		  ti20 += QLA_imag(QLA_F3_elem_M(*ai,2,k_c)) * xr0;
		  tr21 += QLA_real(QLA_F3_elem_M(*ai,2,k_c)) * xr1;
		  ti21 += QLA_imag(QLA_F3_elem_M(*ai,2,k_c)) * xr1;
		  tr00 -= QLA_imag(QLA_F3_elem_M(*ai,0,k_c)) * xi0;
		  ti00 += QLA_real(QLA_F3_elem_M(*ai,0,k_c)) * xi0;
		  tr01 -= QLA_imag(QLA_F3_elem_M(*ai,0,k_c)) * xi1;
		  ti01 += QLA_real(QLA_F3_elem_M(*ai,0,k_c)) * xi1;
		  tr10 -= QLA_imag(QLA_F3_elem_M(*ai,1,k_c)) * xi0;
		  ti10 += QLA_real(QLA_F3_elem_M(*ai,1,k_c)) * xi0;
		  tr11 -= QLA_imag(QLA_F3_elem_M(*ai,1,k_c)) * xi1;
		  ti11 += QLA_real(QLA_F3_elem_M(*ai,1,k_c)) * xi1;
		  tr20 -= QLA_imag(QLA_F3_elem_M(*ai,2,k_c)) * xi0;
		  ti20 += QLA_real(QLA_F3_elem_M(*ai,2,k_c)) * xi0;
		  tr21 -= QLA_imag(QLA_F3_elem_M(*ai,2,k_c)) * xi1;
		  ti21 += QLA_real(QLA_F3_elem_M(*ai,2,k_c)) * xi1;
		}
	      QLA_real(QLA_F3_elem_H(t,0,0)) = tr00;
	      QLA_imag(QLA_F3_elem_H(t,0,0)) = ti00;
	      QLA_real(QLA_F3_elem_H(t,0,1)) = tr01;
	      QLA_imag(QLA_F3_elem_H(t,0,1)) = ti01;
	      QLA_real(QLA_F3_elem_H(t,1,0)) = tr10;
	      QLA_imag(QLA_F3_elem_H(t,1,0)) = ti10;
	      QLA_real(QLA_F3_elem_H(t,1,1)) = tr11;
	      QLA_imag(QLA_F3_elem_H(t,1,1)) = ti11;
	      QLA_real(QLA_F3_elem_H(t,2,0)) = tr20;
	      QLA_imag(QLA_F3_elem_H(t,2,0)) = ti20;
	      QLA_real(QLA_F3_elem_H(t,2,1)) = tr21;
	      QLA_imag(QLA_F3_elem_H(t,2,1)) = ti21;
	    }
	    {
	      int i_c;
	      for(i_c=0;i_c<3;i_c++)
		{
		  QLA_c_peq_c(QLA_F3_elem_D(*ri,i_c,0),QLA_F3_elem_H(t,i_c,0));
		  QLA_c_peq_c(QLA_F3_elem_D(*ri,i_c,1),QLA_F3_elem_H(t,i_c,1));
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
	      QLA_F_Real tr00, tr01, tr10, tr11, tr20, tr21;
	      QLA_F_Real ti00, ti01, ti10, ti11, ti20, ti21;
	      int k_c;
	      tr00 = 0.;
	      ti00 = 0.;
	      tr01 = 0.;
	      ti01 = 0.;
	      tr10 = 0.;
	      ti10 = 0.;
	      tr11 = 0.;
	      ti11 = 0.;
	      tr20 = 0.;
	      ti20 = 0.;
	      tr21 = 0.;
	      ti21 = 0.;
	      for(k_c=0;k_c<3;k_c++)
		{
		  QLA_F_Real xr0, xr1;
		  QLA_F_Real xi0, xi1;
		  xr0 = QLA_real(QLA_F3_elem_H(*bi,k_c,0));
		  xi0 = QLA_imag(QLA_F3_elem_H(*bi,k_c,0));
		  xr1 = QLA_real(QLA_F3_elem_H(*bi,k_c,1));
		  xi1 = QLA_imag(QLA_F3_elem_H(*bi,k_c,1));
		  tr00 += QLA_real(QLA_F3_elem_M(*ai,0,k_c)) * xr0;
		  ti00 += QLA_imag(QLA_F3_elem_M(*ai,0,k_c)) * xr0;
		  tr01 += QLA_real(QLA_F3_elem_M(*ai,0,k_c)) * xr1;
		  ti01 += QLA_imag(QLA_F3_elem_M(*ai,0,k_c)) * xr1;
		  tr10 += QLA_real(QLA_F3_elem_M(*ai,1,k_c)) * xr0;
		  ti10 += QLA_imag(QLA_F3_elem_M(*ai,1,k_c)) * xr0;
		  tr11 += QLA_real(QLA_F3_elem_M(*ai,1,k_c)) * xr1;
		  ti11 += QLA_imag(QLA_F3_elem_M(*ai,1,k_c)) * xr1;
		  tr20 += QLA_real(QLA_F3_elem_M(*ai,2,k_c)) * xr0;
		  ti20 += QLA_imag(QLA_F3_elem_M(*ai,2,k_c)) * xr0;
		  tr21 += QLA_real(QLA_F3_elem_M(*ai,2,k_c)) * xr1;
		  ti21 += QLA_imag(QLA_F3_elem_M(*ai,2,k_c)) * xr1;
		  tr00 -= QLA_imag(QLA_F3_elem_M(*ai,0,k_c)) * xi0;
		  ti00 += QLA_real(QLA_F3_elem_M(*ai,0,k_c)) * xi0;
		  tr01 -= QLA_imag(QLA_F3_elem_M(*ai,0,k_c)) * xi1;
		  ti01 += QLA_real(QLA_F3_elem_M(*ai,0,k_c)) * xi1;
		  tr10 -= QLA_imag(QLA_F3_elem_M(*ai,1,k_c)) * xi0;
		  ti10 += QLA_real(QLA_F3_elem_M(*ai,1,k_c)) * xi0;
		  tr11 -= QLA_imag(QLA_F3_elem_M(*ai,1,k_c)) * xi1;
		  ti11 += QLA_real(QLA_F3_elem_M(*ai,1,k_c)) * xi1;
		  tr20 -= QLA_imag(QLA_F3_elem_M(*ai,2,k_c)) * xi0;
		  ti20 += QLA_real(QLA_F3_elem_M(*ai,2,k_c)) * xi0;
		  tr21 -= QLA_imag(QLA_F3_elem_M(*ai,2,k_c)) * xi1;
		  ti21 += QLA_real(QLA_F3_elem_M(*ai,2,k_c)) * xi1;
		}
	      QLA_real(QLA_F3_elem_H(t,0,0)) = tr00;
	      QLA_imag(QLA_F3_elem_H(t,0,0)) = ti00;
	      QLA_real(QLA_F3_elem_H(t,0,1)) = tr01;
	      QLA_imag(QLA_F3_elem_H(t,0,1)) = ti01;
	      QLA_real(QLA_F3_elem_H(t,1,0)) = tr10;
	      QLA_imag(QLA_F3_elem_H(t,1,0)) = ti10;
	      QLA_real(QLA_F3_elem_H(t,1,1)) = tr11;
	      QLA_imag(QLA_F3_elem_H(t,1,1)) = ti11;
	      QLA_real(QLA_F3_elem_H(t,2,0)) = tr20;
	      QLA_imag(QLA_F3_elem_H(t,2,0)) = ti20;
	      QLA_real(QLA_F3_elem_H(t,2,1)) = tr21;
	      QLA_imag(QLA_F3_elem_H(t,2,1)) = ti21;
	    }
	    {
	      int i_c;
	      for(i_c=0;i_c<3;i_c++)
		{
		  QLA_c_peq_c(QLA_F3_elem_D(*ri,i_c,0),QLA_F3_elem_H(t,i_c,0));
		  QLA_c_peq_c(QLA_F3_elem_D(*ri,i_c,1),QLA_F3_elem_H(t,i_c,1));
		  QLA_c_peq_ic(QLA_F3_elem_D(*ri,i_c,2),QLA_F3_elem_H(t,i_c,1));
		  QLA_c_peq_ic(QLA_F3_elem_D(*ri,i_c,3),QLA_F3_elem_H(t,i_c,0));
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
	      QLA_F_Real tr00, tr01, tr10, tr11, tr20, tr21;
	      QLA_F_Real ti00, ti01, ti10, ti11, ti20, ti21;
	      int k_c;
	      tr00 = 0.;
	      ti00 = 0.;
	      tr01 = 0.;
	      ti01 = 0.;
	      tr10 = 0.;
	      ti10 = 0.;
	      tr11 = 0.;
	      ti11 = 0.;
	      tr20 = 0.;
	      ti20 = 0.;
	      tr21 = 0.;
	      ti21 = 0.;
	      for(k_c=0;k_c<3;k_c++)
		{
		  QLA_F_Real xr0, xr1;
		  QLA_F_Real xi0, xi1;
		  xr0 = QLA_real(QLA_F3_elem_H(*bi,k_c,0));
		  xi0 = QLA_imag(QLA_F3_elem_H(*bi,k_c,0));
		  xr1 = QLA_real(QLA_F3_elem_H(*bi,k_c,1));
		  xi1 = QLA_imag(QLA_F3_elem_H(*bi,k_c,1));
		  tr00 += QLA_real(QLA_F3_elem_M(*ai,0,k_c)) * xr0;
		  ti00 += QLA_imag(QLA_F3_elem_M(*ai,0,k_c)) * xr0;
		  tr01 += QLA_real(QLA_F3_elem_M(*ai,0,k_c)) * xr1;
		  ti01 += QLA_imag(QLA_F3_elem_M(*ai,0,k_c)) * xr1;
		  tr10 += QLA_real(QLA_F3_elem_M(*ai,1,k_c)) * xr0;
		  ti10 += QLA_imag(QLA_F3_elem_M(*ai,1,k_c)) * xr0;
		  tr11 += QLA_real(QLA_F3_elem_M(*ai,1,k_c)) * xr1;
		  ti11 += QLA_imag(QLA_F3_elem_M(*ai,1,k_c)) * xr1;
		  tr20 += QLA_real(QLA_F3_elem_M(*ai,2,k_c)) * xr0;
		  ti20 += QLA_imag(QLA_F3_elem_M(*ai,2,k_c)) * xr0;
		  tr21 += QLA_real(QLA_F3_elem_M(*ai,2,k_c)) * xr1;
		  ti21 += QLA_imag(QLA_F3_elem_M(*ai,2,k_c)) * xr1;
		  tr00 -= QLA_imag(QLA_F3_elem_M(*ai,0,k_c)) * xi0;
		  ti00 += QLA_real(QLA_F3_elem_M(*ai,0,k_c)) * xi0;
		  tr01 -= QLA_imag(QLA_F3_elem_M(*ai,0,k_c)) * xi1;
		  ti01 += QLA_real(QLA_F3_elem_M(*ai,0,k_c)) * xi1;
		  tr10 -= QLA_imag(QLA_F3_elem_M(*ai,1,k_c)) * xi0;
		  ti10 += QLA_real(QLA_F3_elem_M(*ai,1,k_c)) * xi0;
		  tr11 -= QLA_imag(QLA_F3_elem_M(*ai,1,k_c)) * xi1;
		  ti11 += QLA_real(QLA_F3_elem_M(*ai,1,k_c)) * xi1;
		  tr20 -= QLA_imag(QLA_F3_elem_M(*ai,2,k_c)) * xi0;
		  ti20 += QLA_real(QLA_F3_elem_M(*ai,2,k_c)) * xi0;
		  tr21 -= QLA_imag(QLA_F3_elem_M(*ai,2,k_c)) * xi1;
		  ti21 += QLA_real(QLA_F3_elem_M(*ai,2,k_c)) * xi1;
		}
	      QLA_real(QLA_F3_elem_H(t,0,0)) = tr00;
	      QLA_imag(QLA_F3_elem_H(t,0,0)) = ti00;
	      QLA_real(QLA_F3_elem_H(t,0,1)) = tr01;
	      QLA_imag(QLA_F3_elem_H(t,0,1)) = ti01;
	      QLA_real(QLA_F3_elem_H(t,1,0)) = tr10;
	      QLA_imag(QLA_F3_elem_H(t,1,0)) = ti10;
	      QLA_real(QLA_F3_elem_H(t,1,1)) = tr11;
	      QLA_imag(QLA_F3_elem_H(t,1,1)) = ti11;
	      QLA_real(QLA_F3_elem_H(t,2,0)) = tr20;
	      QLA_imag(QLA_F3_elem_H(t,2,0)) = ti20;
	      QLA_real(QLA_F3_elem_H(t,2,1)) = tr21;
	      QLA_imag(QLA_F3_elem_H(t,2,1)) = ti21;
	    }
	    {
	      int i_c;
	      for(i_c=0;i_c<3;i_c++)
		{
		  QLA_c_peq_c(QLA_F3_elem_D(*ri,i_c,0),QLA_F3_elem_H(t,i_c,0));
		  QLA_c_peq_c(QLA_F3_elem_D(*ri,i_c,1),QLA_F3_elem_H(t,i_c,1));
		  QLA_c_peq_c(QLA_F3_elem_D(*ri,i_c,2),QLA_F3_elem_H(t,i_c,1));
		  QLA_c_meq_c(QLA_F3_elem_D(*ri,i_c,3),QLA_F3_elem_H(t,i_c,0));
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
	      QLA_F_Real tr00, tr01, tr10, tr11, tr20, tr21;
	      QLA_F_Real ti00, ti01, ti10, ti11, ti20, ti21;
	      int k_c;
	      tr00 = 0.;
	      ti00 = 0.;
	      tr01 = 0.;
	      ti01 = 0.;
	      tr10 = 0.;
	      ti10 = 0.;
	      tr11 = 0.;
	      ti11 = 0.;
	      tr20 = 0.;
	      ti20 = 0.;
	      tr21 = 0.;
	      ti21 = 0.;
	      for(k_c=0;k_c<3;k_c++)
		{
		  QLA_F_Real xr0, xr1;
		  QLA_F_Real xi0, xi1;
		  xr0 = QLA_real(QLA_F3_elem_H(*bi,k_c,0));
		  xi0 = QLA_imag(QLA_F3_elem_H(*bi,k_c,0));
		  xr1 = QLA_real(QLA_F3_elem_H(*bi,k_c,1));
		  xi1 = QLA_imag(QLA_F3_elem_H(*bi,k_c,1));
		  tr00 += QLA_real(QLA_F3_elem_M(*ai,0,k_c)) * xr0;
		  ti00 += QLA_imag(QLA_F3_elem_M(*ai,0,k_c)) * xr0;
		  tr01 += QLA_real(QLA_F3_elem_M(*ai,0,k_c)) * xr1;
		  ti01 += QLA_imag(QLA_F3_elem_M(*ai,0,k_c)) * xr1;
		  tr10 += QLA_real(QLA_F3_elem_M(*ai,1,k_c)) * xr0;
		  ti10 += QLA_imag(QLA_F3_elem_M(*ai,1,k_c)) * xr0;
		  tr11 += QLA_real(QLA_F3_elem_M(*ai,1,k_c)) * xr1;
		  ti11 += QLA_imag(QLA_F3_elem_M(*ai,1,k_c)) * xr1;
		  tr20 += QLA_real(QLA_F3_elem_M(*ai,2,k_c)) * xr0;
		  ti20 += QLA_imag(QLA_F3_elem_M(*ai,2,k_c)) * xr0;
		  tr21 += QLA_real(QLA_F3_elem_M(*ai,2,k_c)) * xr1;
		  ti21 += QLA_imag(QLA_F3_elem_M(*ai,2,k_c)) * xr1;
		  tr00 -= QLA_imag(QLA_F3_elem_M(*ai,0,k_c)) * xi0;
		  ti00 += QLA_real(QLA_F3_elem_M(*ai,0,k_c)) * xi0;
		  tr01 -= QLA_imag(QLA_F3_elem_M(*ai,0,k_c)) * xi1;
		  ti01 += QLA_real(QLA_F3_elem_M(*ai,0,k_c)) * xi1;
		  tr10 -= QLA_imag(QLA_F3_elem_M(*ai,1,k_c)) * xi0;
		  ti10 += QLA_real(QLA_F3_elem_M(*ai,1,k_c)) * xi0;
		  tr11 -= QLA_imag(QLA_F3_elem_M(*ai,1,k_c)) * xi1;
		  ti11 += QLA_real(QLA_F3_elem_M(*ai,1,k_c)) * xi1;
		  tr20 -= QLA_imag(QLA_F3_elem_M(*ai,2,k_c)) * xi0;
		  ti20 += QLA_real(QLA_F3_elem_M(*ai,2,k_c)) * xi0;
		  tr21 -= QLA_imag(QLA_F3_elem_M(*ai,2,k_c)) * xi1;
		  ti21 += QLA_real(QLA_F3_elem_M(*ai,2,k_c)) * xi1;
		}
	      QLA_real(QLA_F3_elem_H(t,0,0)) = tr00;
	      QLA_imag(QLA_F3_elem_H(t,0,0)) = ti00;
	      QLA_real(QLA_F3_elem_H(t,0,1)) = tr01;
	      QLA_imag(QLA_F3_elem_H(t,0,1)) = ti01;
	      QLA_real(QLA_F3_elem_H(t,1,0)) = tr10;
	      QLA_imag(QLA_F3_elem_H(t,1,0)) = ti10;
	      QLA_real(QLA_F3_elem_H(t,1,1)) = tr11;
	      QLA_imag(QLA_F3_elem_H(t,1,1)) = ti11;
	      QLA_real(QLA_F3_elem_H(t,2,0)) = tr20;
	      QLA_imag(QLA_F3_elem_H(t,2,0)) = ti20;
	      QLA_real(QLA_F3_elem_H(t,2,1)) = tr21;
	      QLA_imag(QLA_F3_elem_H(t,2,1)) = ti21;
	    }
	    {
	      int i_c;
	      for(i_c=0;i_c<3;i_c++)
		{
		  QLA_c_peq_c(QLA_F3_elem_D(*ri,i_c,0),QLA_F3_elem_H(t,i_c,0));
		  QLA_c_peq_c(QLA_F3_elem_D(*ri,i_c,1),QLA_F3_elem_H(t,i_c,1));
		  QLA_c_peq_ic(QLA_F3_elem_D(*ri,i_c,2),QLA_F3_elem_H(t,i_c,0));
		  QLA_c_meq_ic(QLA_F3_elem_D(*ri,i_c,3),QLA_F3_elem_H(t,i_c,1));
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
	      QLA_F_Real tr00, tr01, tr10, tr11, tr20, tr21;
	      QLA_F_Real ti00, ti01, ti10, ti11, ti20, ti21;
	      int k_c;
	      tr00 = 0.;
	      ti00 = 0.;
	      tr01 = 0.;
	      ti01 = 0.;
	      tr10 = 0.;
	      ti10 = 0.;
	      tr11 = 0.;
	      ti11 = 0.;
	      tr20 = 0.;
	      ti20 = 0.;
	      tr21 = 0.;
	      ti21 = 0.;
	      for(k_c=0;k_c<3;k_c++)
		{
		  QLA_F_Real xr0, xr1;
		  QLA_F_Real xi0, xi1;
		  xr0 = QLA_real(QLA_F3_elem_H(*bi,k_c,0));
		  xi0 = QLA_imag(QLA_F3_elem_H(*bi,k_c,0));
		  xr1 = QLA_real(QLA_F3_elem_H(*bi,k_c,1));
		  xi1 = QLA_imag(QLA_F3_elem_H(*bi,k_c,1));
		  tr00 += QLA_real(QLA_F3_elem_M(*ai,0,k_c)) * xr0;
		  ti00 += QLA_imag(QLA_F3_elem_M(*ai,0,k_c)) * xr0;
		  tr01 += QLA_real(QLA_F3_elem_M(*ai,0,k_c)) * xr1;
		  ti01 += QLA_imag(QLA_F3_elem_M(*ai,0,k_c)) * xr1;
		  tr10 += QLA_real(QLA_F3_elem_M(*ai,1,k_c)) * xr0;
		  ti10 += QLA_imag(QLA_F3_elem_M(*ai,1,k_c)) * xr0;
		  tr11 += QLA_real(QLA_F3_elem_M(*ai,1,k_c)) * xr1;
		  ti11 += QLA_imag(QLA_F3_elem_M(*ai,1,k_c)) * xr1;
		  tr20 += QLA_real(QLA_F3_elem_M(*ai,2,k_c)) * xr0;
		  ti20 += QLA_imag(QLA_F3_elem_M(*ai,2,k_c)) * xr0;
		  tr21 += QLA_real(QLA_F3_elem_M(*ai,2,k_c)) * xr1;
		  ti21 += QLA_imag(QLA_F3_elem_M(*ai,2,k_c)) * xr1;
		  tr00 -= QLA_imag(QLA_F3_elem_M(*ai,0,k_c)) * xi0;
		  ti00 += QLA_real(QLA_F3_elem_M(*ai,0,k_c)) * xi0;
		  tr01 -= QLA_imag(QLA_F3_elem_M(*ai,0,k_c)) * xi1;
		  ti01 += QLA_real(QLA_F3_elem_M(*ai,0,k_c)) * xi1;
		  tr10 -= QLA_imag(QLA_F3_elem_M(*ai,1,k_c)) * xi0;
		  ti10 += QLA_real(QLA_F3_elem_M(*ai,1,k_c)) * xi0;
		  tr11 -= QLA_imag(QLA_F3_elem_M(*ai,1,k_c)) * xi1;
		  ti11 += QLA_real(QLA_F3_elem_M(*ai,1,k_c)) * xi1;
		  tr20 -= QLA_imag(QLA_F3_elem_M(*ai,2,k_c)) * xi0;
		  ti20 += QLA_real(QLA_F3_elem_M(*ai,2,k_c)) * xi0;
		  tr21 -= QLA_imag(QLA_F3_elem_M(*ai,2,k_c)) * xi1;
		  ti21 += QLA_real(QLA_F3_elem_M(*ai,2,k_c)) * xi1;
		}
	      QLA_real(QLA_F3_elem_H(t,0,0)) = tr00;
	      QLA_imag(QLA_F3_elem_H(t,0,0)) = ti00;
	      QLA_real(QLA_F3_elem_H(t,0,1)) = tr01;
	      QLA_imag(QLA_F3_elem_H(t,0,1)) = ti01;
	      QLA_real(QLA_F3_elem_H(t,1,0)) = tr10;
	      QLA_imag(QLA_F3_elem_H(t,1,0)) = ti10;
	      QLA_real(QLA_F3_elem_H(t,1,1)) = tr11;
	      QLA_imag(QLA_F3_elem_H(t,1,1)) = ti11;
	      QLA_real(QLA_F3_elem_H(t,2,0)) = tr20;
	      QLA_imag(QLA_F3_elem_H(t,2,0)) = ti20;
	      QLA_real(QLA_F3_elem_H(t,2,1)) = tr21;
	      QLA_imag(QLA_F3_elem_H(t,2,1)) = ti21;
	    }
	    {
	      int i_c;
	      for(i_c=0;i_c<3;i_c++)
		{
		  QLA_c_peq_c(QLA_F3_elem_D(*ri,i_c,0),QLA_F3_elem_H(t,i_c,0));
		  QLA_c_peq_c(QLA_F3_elem_D(*ri,i_c,1),QLA_F3_elem_H(t,i_c,1));
		  QLA_c_meq_c(QLA_F3_elem_D(*ri,i_c,2),QLA_F3_elem_H(t,i_c,0));
		  QLA_c_meq_c(QLA_F3_elem_D(*ri,i_c,3),QLA_F3_elem_H(t,i_c,1));
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
	      QLA_F_Real tr00, tr01, tr10, tr11, tr20, tr21;
	      QLA_F_Real ti00, ti01, ti10, ti11, ti20, ti21;
	      int k_c;
	      tr00 = 0.;
	      ti00 = 0.;
	      tr01 = 0.;
	      ti01 = 0.;
	      tr10 = 0.;
	      ti10 = 0.;
	      tr11 = 0.;
	      ti11 = 0.;
	      tr20 = 0.;
	      ti20 = 0.;
	      tr21 = 0.;
	      ti21 = 0.;
	      for(k_c=0;k_c<3;k_c++)
		{
		  QLA_F_Real xr0, xr1;
		  QLA_F_Real xi0, xi1;
		  xr0 = QLA_real(QLA_F3_elem_H(*bi,k_c,0));
		  xi0 = QLA_imag(QLA_F3_elem_H(*bi,k_c,0));
		  xr1 = QLA_real(QLA_F3_elem_H(*bi,k_c,1));
		  xi1 = QLA_imag(QLA_F3_elem_H(*bi,k_c,1));
		  tr00 += QLA_real(QLA_F3_elem_M(*ai,0,k_c)) * xr0;
		  ti00 += QLA_imag(QLA_F3_elem_M(*ai,0,k_c)) * xr0;
		  tr01 += QLA_real(QLA_F3_elem_M(*ai,0,k_c)) * xr1;
		  ti01 += QLA_imag(QLA_F3_elem_M(*ai,0,k_c)) * xr1;
		  tr10 += QLA_real(QLA_F3_elem_M(*ai,1,k_c)) * xr0;
		  ti10 += QLA_imag(QLA_F3_elem_M(*ai,1,k_c)) * xr0;
		  tr11 += QLA_real(QLA_F3_elem_M(*ai,1,k_c)) * xr1;
		  ti11 += QLA_imag(QLA_F3_elem_M(*ai,1,k_c)) * xr1;
		  tr20 += QLA_real(QLA_F3_elem_M(*ai,2,k_c)) * xr0;
		  ti20 += QLA_imag(QLA_F3_elem_M(*ai,2,k_c)) * xr0;
		  tr21 += QLA_real(QLA_F3_elem_M(*ai,2,k_c)) * xr1;
		  ti21 += QLA_imag(QLA_F3_elem_M(*ai,2,k_c)) * xr1;
		  tr00 -= QLA_imag(QLA_F3_elem_M(*ai,0,k_c)) * xi0;
		  ti00 += QLA_real(QLA_F3_elem_M(*ai,0,k_c)) * xi0;
		  tr01 -= QLA_imag(QLA_F3_elem_M(*ai,0,k_c)) * xi1;
		  ti01 += QLA_real(QLA_F3_elem_M(*ai,0,k_c)) * xi1;
		  tr10 -= QLA_imag(QLA_F3_elem_M(*ai,1,k_c)) * xi0;
		  ti10 += QLA_real(QLA_F3_elem_M(*ai,1,k_c)) * xi0;
		  tr11 -= QLA_imag(QLA_F3_elem_M(*ai,1,k_c)) * xi1;
		  ti11 += QLA_real(QLA_F3_elem_M(*ai,1,k_c)) * xi1;
		  tr20 -= QLA_imag(QLA_F3_elem_M(*ai,2,k_c)) * xi0;
		  ti20 += QLA_real(QLA_F3_elem_M(*ai,2,k_c)) * xi0;
		  tr21 -= QLA_imag(QLA_F3_elem_M(*ai,2,k_c)) * xi1;
		  ti21 += QLA_real(QLA_F3_elem_M(*ai,2,k_c)) * xi1;
		}
	      QLA_real(QLA_F3_elem_H(t,0,0)) = tr00;
	      QLA_imag(QLA_F3_elem_H(t,0,0)) = ti00;
	      QLA_real(QLA_F3_elem_H(t,0,1)) = tr01;
	      QLA_imag(QLA_F3_elem_H(t,0,1)) = ti01;
	      QLA_real(QLA_F3_elem_H(t,1,0)) = tr10;
	      QLA_imag(QLA_F3_elem_H(t,1,0)) = ti10;
	      QLA_real(QLA_F3_elem_H(t,1,1)) = tr11;
	      QLA_imag(QLA_F3_elem_H(t,1,1)) = ti11;
	      QLA_real(QLA_F3_elem_H(t,2,0)) = tr20;
	      QLA_imag(QLA_F3_elem_H(t,2,0)) = ti20;
	      QLA_real(QLA_F3_elem_H(t,2,1)) = tr21;
	      QLA_imag(QLA_F3_elem_H(t,2,1)) = ti21;
	    }
	    {
	      int i_c;
	      for(i_c=0;i_c<3;i_c++)
		{
		  QLA_c_peq_c(QLA_F3_elem_D(*ri,i_c,2),QLA_F3_elem_H(t,i_c,0));
		  QLA_c_peq_c(QLA_F3_elem_D(*ri,i_c,3),QLA_F3_elem_H(t,i_c,1));
		}
	    }
	  }
      } break;
      }
    }
  }
}
