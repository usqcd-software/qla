/**************** QLA_F3_V_vpeq_M_times_pV.c ********************/

#include <qla_config.h>
#include <qla_types.h>
#include <qla_random.h>
#include <qla_cmath.h>
#include <math.h>

#define elemVr(a,i) QLA_real(QLA_F3_elem_V(*a,i))
#define elemVi(a,i) QLA_imag(QLA_F3_elem_V(*a,i))
#define elemMr(a,i,j) QLA_real(QLA_F3_elem_M(*a,i,j))
#define elemMi(a,i,j) QLA_imag(QLA_F3_elem_M(*a,i,j))

#define col_mul_r(r,op,a,ii,bi) \
        bix = elemVr(bi,ii); \
	r##0r op elemMr(a,0,ii) * bix; \
	r##0i op elemMi(a,0,ii) * bix; \
	r##1r op elemMr(a,1,ii) * bix; \
	r##1i op elemMi(a,1,ii) * bix; \
	r##2r op elemMr(a,2,ii) * bix; \
	r##2i op elemMi(a,2,ii) * bix

#define col_mul_i(r,op,a,ii,bi) \
        bix = elemVi(bi,ii); \
	r##0r op -(elemMi(a,0,ii) * bix); \
	r##0i op   elemMr(a,0,ii) * bix;  \
	r##1r op -(elemMi(a,1,ii) * bix); \
	r##1i op   elemMr(a,1,ii) * bix;  \
	r##2r op -(elemMi(a,2,ii) * bix); \
	r##2i op   elemMr(a,2,ii) * bix

void
QLA_F3_V_vpeq_M_times_pV(QLA_F3_ColorVector *restrict r,
                         QLA_F3_ColorMatrix *a,
			 QLA_F3_ColorVector *restrict *b,
			 int n)
{
  int i;
  for(i=0; i<n; i++) {
    QLA_F_Real ri0r, ri0i, ri1r, ri1i, ri2r, ri2i;
    QLA_F_Real bix;
    QLA_F3_ColorVector *ri;
    QLA_F3_ColorMatrix *ai;
    QLA_F3_ColorVector *bi;

    ri = &r[i];
    ai = &a[i];
    bi = b[i];

    ri0r = elemVr(ri,0);
    ri0i = elemVi(ri,0);
    ri1r = elemVr(ri,1);
    ri1i = elemVi(ri,1);
    ri2r = elemVr(ri,2);
    ri2i = elemVi(ri,2);

    col_mul_r(ri,+=,ai,0,bi);
    col_mul_i(ri,+=,ai,0,bi);
    col_mul_r(ri,+=,ai,1,bi);
    col_mul_i(ri,+=,ai,1,bi);
    col_mul_r(ri,+=,ai,2,bi);
    col_mul_i(ri,+=,ai,2,bi);

    elemVr(ri,0) = ri0r;
    elemVi(ri,0) = ri0i;
    elemVr(ri,1) = ri1r;
    elemVi(ri,1) = ri1i;
    elemVr(ri,2) = ri2r;
    elemVi(ri,2) = ri2i;
  }
}
