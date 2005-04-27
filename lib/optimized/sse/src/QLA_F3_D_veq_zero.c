/**************** QLA_F3_D_veq_zero.c ********************/

#include <qla_types.h>
#include <qla_random.h>
#include <qla_cmath.h>
#include <math.h>

#define movaps(dest,src) __asm__ ("movaps " #src ", " #dest ::)
#define movapsl(dest,src) __asm__ ("movaps %0, " #dest ::"m" (src))
#define movapss(dest,src) __asm__ ("movaps " #src ", %0" :"=m" (dest):)
#define xorps(dest,src) __asm__ ("xorps " #src ", " #dest ::)

void QLA_F3_D_veq_zero ( QLA_F3_DiracFermion *__restrict__ r , int n )
{
  float *fpt = (float *)r;
  if((((int)fpt)&3)!=0) {
  //if(1) {
    int i, l;
    l = 24*n;
    for(i=0; i<l; i++) {
      fpt[i] = 0.0f;
    }
  } else {
    int i, l, r1, r2;
    l = 24*n;
    r2 = (((int)fpt)&15)>>2;
    r1 = (4-r2)&3;
    r2 = l-r2;
    for(i=0; i<r1; i++) {
      fpt[i] = 0.0f;
    }
    xorps(%%xmm0, %%xmm0);
    for(; i<r2; i+=4) {
      //fpt[i] = 0.0f;
      //fpt[i+1] = 0.0f;
      //fpt[i+2] = 0.0f;
      //fpt[i+3] = 0.0f;
      movapss(fpt[i], %%xmm0);
    }
    for(; i<l; i++) {
      fpt[i] = 0.0f;
    }
  }
}
