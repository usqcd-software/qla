/**************** QLA_F3_V_vmeq_pV.c ********************/

#include <qla_types.h>
#include <qla_cmath.h>
#include <qla_sse.h>
#include <math.h>
#include <stdlib.h>

#if 0
typedef int v2si __attribute__ ((mode(V2SI)));
typedef int v4si __attribute__ ((mode(V4SI)));
typedef float v4sf __attribute__ ((mode(V4SF)));

#define loadaps(a) __builtin_ia32_loadaps((float *)(a))
#define loadups(a) __builtin_ia32_loadups((float *)(a))
#define loadlps(a,b) __builtin_ia32_loadlps(a, (v2si *)(b))
#define loadhps(a,b) __builtin_ia32_loadhps(a, (v2si *)(b))

#define storeaps(a,b) __builtin_ia32_storeaps((float *)(a),b)
#define storeups(a,b) __builtin_ia32_storeups((float *)(a),b)
#define storelps(a,b) __builtin_ia32_storelps((v2si *)(a),b)
#define storehps(a,b) __builtin_ia32_storehps((v2si *)(a),b)

#define foff(a,n) (((float *)(a))+(n))
#endif

void
QLA_F3_V_vmeq_pV( QLA_F3_ColorVector *restrict r,
		  QLA_F3_ColorVector **a,
		  int n )
{
  size_t m, x = (size_t)r;
  int u8, u16;
  int i, nb, nn;

  m = 0x7;
  u8 = x&m;
  m = 0xf;
  u16 = x&m;

  if( u16 && !u8 ) {
    nb = 1;
  } else {
    nb = 0;
  }

  if((n-nb)&1) {
    nn = n-1;
  } else {
    nn = n;
  }

  //printf("u8=%i u16=%i nb=%i nn=%i\n", u8, u16, nb, nn);

  for(i=0; i<nb; i++) {
    v4sf r0, r1;
    r0 = subps( loadups(foff(&r[i],0)), loadups(foff(a[i],0)) );
    storeups(foff(&r[i],0),r0);
    r1 = subps( loadups(foff(&r[i],2)), loadups(foff(a[i],2)) );
    storehps(foff(&r[i],4),r1);
  }

  if(u8) {
    v4sf r0,r1=setss(0),r2;
    for( ; i<nn; i+=2) {

      r0 = subps( loadups(foff(&r[i],0)), loadups(foff(a[i],0)) );
      storeups(foff(&r[i],0),r0);

      r1 = loadlps(r1,foff(a[i],4));
      r1 = loadhps(r1,foff(a[i+1],0));
      r1 = subps( loadups(foff(&r[i],4)), r1 );
      storeups(foff(&r[i],4),r1);

      r2 = subps( loadups(foff(&r[i],8)), loadups(foff(a[i+1],2)) );
      storeups(foff(&r[i],8),r2);
    }
  } else {
    v4sf r0,r1=setss(0),r2;
    for( ; i<nn; i+=2) {

      r0 = subps( loadaps(foff(&r[i],0)), loadups(foff(a[i],0)) );
      storeaps(foff(&r[i],0),r0);

      r1 = loadlps(r1,foff(a[i],4));
      r1 = loadhps(r1,foff(a[i+1],0));
      r1 = subps( loadaps(foff(&r[i],4)), r1 );
      storeaps(foff(&r[i],4),r1);

      r2 = subps( loadaps(foff(&r[i],8)), loadups(foff(a[i+1],2)) );
      storeaps(foff(&r[i],8),r2);
    }
  }

  for( ; i<n; i++) {
    v4sf r0, r1;
    r0 = subps( loadups(foff(&r[i],0)), loadups(foff(a[i],0)) );
    storeups(foff(&r[i],0),r0);
    r1 = subps( loadups(foff(&r[i],2)), loadups(foff(a[i],2)) );
    storehps(foff(&r[i],4),r1);
  }
}
