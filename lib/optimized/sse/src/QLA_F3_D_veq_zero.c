/**************** QLA_F3_D_veq_zero.c ********************/

#include <qla_types.h>
#include <qla_random.h>
#include <qla_cmath.h>
#include <qla_sse.h>
#include <math.h>

void
QLA_F3_D_veq_zero(QLA_F3_DiracFermion *restrict r, int n)
{
  if(is_aligned(r,16)) {
    v4sf x0 = setss(0);
    int i;
    for(i=0; i<n; i++) {
      QLA_F3_DiracFermion *ri = &r[i];
      storeaps(ri, x0);
      storeaps(foff(ri,4), x0);
      storeaps(foff(ri,8), x0);
      storeaps(foff(ri,12), x0);
      storeaps(foff(ri,16), x0);
      storeaps(foff(ri,20), x0);
    }
  } else {
    float *fpt = (float *)r;
    if((((size_t)fpt)&3)!=0) {
      int i, l;
      l = 24*n;
      for(i=0; i<l; i++) {
	fpt[i] = 0.0f;
      }
    } else {
      v4sf x0 = setss(0);
      int i, l, r1, r2;
      l = 24*n;
      r2 = (((size_t)fpt)&15)>>2;
      r1 = (4-r2)&3;
      r2 = l-r2;
      for(i=0; i<r1; i++) {
	fpt[i] = 0.0f;
      }
      for(; i<r2; i+=4) {
	storeaps(&fpt[i], x0);
      }
      for(; i<l; i++) {
	fpt[i] = 0.0f;
      }
    }
  }
}
