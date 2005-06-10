/**************** QLA_F3_V_vpeq_M_times_V.c ********************/

#include <qla_types.h>
#include <qla_cmath.h>
#include <math.h>
#include <stdlib.h>

//#define LOAD1

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

#define movlhps(a,b) __builtin_ia32_movlhps(a,b)
#define movhlps(a,b) __builtin_ia32_movhlps(a,b)

#define shufps(a,b,c) __builtin_ia32_shufps(a,b,c)
#define xorps(a,b) __builtin_ia32_xorps(a,(v4sf)(b))
#define addps(a,b) __builtin_ia32_addps(a,b)

static v4si _sse_sgn13 = {0x80000000, 0x00000000, 0x80000000, 0x00000000};

#define foff(a,n) (((float *)(a))+(n))
#define prefetch(a,n) __builtin_prefetch(((char *)(a))+n,0,0)

#define loadpsa(a) loadaps(a)
#define loadpsr(a) loadaps(a)
#define storepsr(a,b) storeaps(a,b)
inline static void
QLA_F3_V_vpeq_M_times_pV_2aa( QLA_F3_ColorVector *__restrict__ r,
			      QLA_F3_ColorMatrix *a,
			      QLA_F3_ColorVector **b,
			      int n )
{
  v4sf a0, a1, a2;
  v4sf bs0, bs1, b0r, b0i, b1r, b1i, b2r, b2i;
  v4sf r0r, r0i;
  v4sf bs2, bs3;
#ifndef LOAD1
  v4sf aa0, aa1, aa2;
#endif
  int i;

  for(i=0; i<n; i+=2) {

#ifdef LOAD1
    a0 = loadpsa(foff(&a[i],0));
    a0 = loadhps(a0,foff(&a[i],6));
#else
    aa0 = loadpsa(foff(&a[i],0));
    aa1 = loadpsa(foff(&a[i],4));
    a0 = shufps(aa0,aa1,0xe4);
#endif
    bs0 = loadups(b[i]);
    b0r = shufps(bs0,bs0,0x00);
    r0r = a0*b0r + loadpsr(&r[i]);
    b0i = shufps(bs0,bs0,0x55);
    r0i = a0*b0i;

#ifdef LOAD1
    a1 = loadups(foff(&a[i],2));
    a1 = loadhps(a1,foff(&a[i],8));
#else
    aa2 = loadpsa(foff(&a[i],8));
    a1 = shufps(aa0,aa2,0x4e);
#endif
    b1r = shufps(bs0,bs0,0xaa);
    r0r += a1*b1r;
    b1i = shufps(bs0,bs0,0xff);
    r0i += a1*b1i;

#ifdef LOAD1
    a2 = loadpsa(foff(&a[i],4));
    a2 = loadhps(a2,foff(&a[i],10));
#else
    a2 = shufps(aa1,aa2,0xe4);
#endif
    bs1 = loadups(foff(b[i],2));
    b2r = shufps(bs1,bs1,0xaa);
    r0r += a2*b2r;
    b2i = shufps(bs1,bs1,0xff);
    r0i += a2*b2i;

    r0i = shufps(r0i, r0i, 0xb1);
    r0r += xorps(r0i, _sse_sgn13);
    storepsr(&r[i], r0r);

#ifdef LOAD1
    a0 = loadpsa(foff(&a[i],12));
    a0 = loadhps(a0,foff(&a[i],18));
#else
    aa0 = loadpsa(foff(&a[i],12));
    aa1 = loadpsa(foff(&a[i],16));
    a0 = shufps(aa0,aa1,0xe4);
#endif
    bs2 = loadups(b[i+1]);
    b0r = shufps(bs0,bs2,0x00);
    r0r = a0*b0r + loadpsr(foff(&r[i],4));
    b0i = shufps(bs0,bs2,0x55);
    r0i = a0*b0i;

#ifdef LOAD1
    a1 = loadups(foff(&a[i],14));
    a1 = loadhps(a1,foff(&a[i],20));
#else
    aa2 = loadpsa(foff(&a[i],20));
    a1 = shufps(aa0,aa2,0x4e);
#endif
    b1r = shufps(bs0,bs2,0xaa);
    r0r += a1*b1r;
    b1i = shufps(bs0,bs2,0xff);
    r0i += a1*b1i;

#ifdef LOAD1
    a2 = loadpsa(foff(&a[i],16));
    a2 = loadhps(a2,foff(&a[i],22));
#else
    a2 = shufps(aa1,aa2,0xe4);
#endif
    bs3 = loadups(foff(b[i+1],2));
    b2r = shufps(bs1,bs3,0xaa);
    r0r += a2*b2r;
    b2i = shufps(bs1,bs3,0xff);
    r0i += a2*b2i;

    r0i = shufps(r0i, r0i, 0xb1);
    r0r += xorps(r0i, _sse_sgn13);
    storepsr(foff(&r[i],4), r0r);


#ifdef LOAD1
    a0 = loadpsa(foff(&a[i],24));
    a0 = loadhps(a0,foff(&a[i],30));
#else
    aa0 = loadpsa(foff(&a[i],24));
    aa1 = loadpsa(foff(&a[i],28));
    a0 = shufps(aa0,aa1,0xe4);
#endif
    b0r = shufps(bs2,bs2,0x00);
    r0r = a0*b0r + loadpsr(foff(&r[i],8));
    b0i = shufps(bs2,bs2,0x55);
    r0i = a0*b0i;

#ifdef LOAD1
    a1 = loadups(foff(&a[i],26));
    a1 = loadhps(a1,foff(&a[i],32));
#else
    aa2 = loadpsa(foff(&a[i],32));
    a1 = shufps(aa0,aa2,0x4e);
#endif
    b1r = shufps(bs2,bs2,0xaa);
    r0r += a1*b1r;
    b1i = shufps(bs2,bs2,0xff);
    r0i += a1*b1i;

#ifdef LOAD1
    a2 = loadpsa(foff(&a[i],28));
    a2 = loadhps(a2,foff(&a[i],34));
#else
    a2 = shufps(aa1,aa2,0xe4);
#endif
    b2r = shufps(bs3,bs3,0xaa);
    r0r += a2*b2r;
    b2i = shufps(bs3,bs3,0xff);
    r0i += a2*b2i;

    r0i = shufps(r0i, r0i, 0xb1);
    r0r += xorps(r0i, _sse_sgn13);
    storepsr(foff(&r[i],8), r0r);

  }
}

#undef loadpsa
#undef loadpsr
#undef storepsr
#define loadpsa(a) loadups(a)
#define loadpsr(a) loadaps(a)
#define storepsr(a,b) storeaps(a,b)
inline static void
QLA_F3_V_vpeq_M_times_pV_2au( QLA_F3_ColorVector *__restrict__ r,
			      QLA_F3_ColorMatrix *a,
			      QLA_F3_ColorVector **b,
			      int n )
{
  v4sf a0, a1, a2;
  v4sf bs0, bs1, b0r, b0i, b1r, b1i, b2r, b2i;
  v4sf r0r, r0i;
  v4sf bs2, bs3;
#ifndef LOAD1
  v4sf aa0, aa1, aa2;
#endif
  int i;

  for(i=0; i<n; i+=2) {

#ifdef LOAD1
    a0 = loadpsa(foff(&a[i],0));
    a0 = loadhps(a0,foff(&a[i],6));
#else
    aa0 = loadpsa(foff(&a[i],0));
    aa1 = loadpsa(foff(&a[i],4));
    a0 = shufps(aa0,aa1,0xe4);
#endif
    bs0 = loadups(b[i]);
    b0r = shufps(bs0,bs0,0x00);
    r0r = a0*b0r + loadpsr(&r[i]);
    b0i = shufps(bs0,bs0,0x55);
    r0i = a0*b0i;

#ifdef LOAD1
    a1 = loadups(foff(&a[i],2));
    a1 = loadhps(a1,foff(&a[i],8));
#else
    aa2 = loadpsa(foff(&a[i],8));
    a1 = shufps(aa0,aa2,0x4e);
#endif
    b1r = shufps(bs0,bs0,0xaa);
    r0r += a1*b1r;
    b1i = shufps(bs0,bs0,0xff);
    r0i += a1*b1i;

#ifdef LOAD1
    a2 = loadpsa(foff(&a[i],4));
    a2 = loadhps(a2,foff(&a[i],10));
#else
    a2 = shufps(aa1,aa2,0xe4);
#endif
    bs1 = loadups(foff(b[i],2));
    b2r = shufps(bs1,bs1,0xaa);
    r0r += a2*b2r;
    b2i = shufps(bs1,bs1,0xff);
    r0i += a2*b2i;

    r0i = shufps(r0i, r0i, 0xb1);
    r0r += xorps(r0i, _sse_sgn13);
    storepsr(&r[i], r0r);

#ifdef LOAD1
    a0 = loadpsa(foff(&a[i],12));
    a0 = loadhps(a0,foff(&a[i],18));
#else
    aa0 = loadpsa(foff(&a[i],12));
    aa1 = loadpsa(foff(&a[i],16));
    a0 = shufps(aa0,aa1,0xe4);
#endif
    bs2 = loadups(b[i+1]);
    b0r = shufps(bs0,bs2,0x00);
    r0r = a0*b0r + loadpsr(foff(&r[i],4));
    b0i = shufps(bs0,bs2,0x55);
    r0i = a0*b0i;

#ifdef LOAD1
    a1 = loadups(foff(&a[i],14));
    a1 = loadhps(a1,foff(&a[i],20));
#else
    aa2 = loadpsa(foff(&a[i],20));
    a1 = shufps(aa0,aa2,0x4e);
#endif
    b1r = shufps(bs0,bs2,0xaa);
    r0r += a1*b1r;
    b1i = shufps(bs0,bs2,0xff);
    r0i += a1*b1i;

#ifdef LOAD1
    a2 = loadpsa(foff(&a[i],16));
    a2 = loadhps(a2,foff(&a[i],22));
#else
    a2 = shufps(aa1,aa2,0xe4);
#endif
    bs3 = loadups(foff(b[i+1],2));
    b2r = shufps(bs1,bs3,0xaa);
    r0r += a2*b2r;
    b2i = shufps(bs1,bs3,0xff);
    r0i += a2*b2i;

    r0i = shufps(r0i, r0i, 0xb1);
    r0r += xorps(r0i, _sse_sgn13);
    storepsr(foff(&r[i],4), r0r);


#ifdef LOAD1
    a0 = loadpsa(foff(&a[i],24));
    a0 = loadhps(a0,foff(&a[i],30));
#else
    aa0 = loadpsa(foff(&a[i],24));
    aa1 = loadpsa(foff(&a[i],28));
    a0 = shufps(aa0,aa1,0xe4);
#endif
    b0r = shufps(bs2,bs2,0x00);
    r0r = a0*b0r + loadpsr(foff(&r[i],8));
    b0i = shufps(bs2,bs2,0x55);
    r0i = a0*b0i;

#ifdef LOAD1
    a1 = loadups(foff(&a[i],26));
    a1 = loadhps(a1,foff(&a[i],32));
#else
    aa2 = loadpsa(foff(&a[i],32));
    a1 = shufps(aa0,aa2,0x4e);
#endif
    b1r = shufps(bs2,bs2,0xaa);
    r0r += a1*b1r;
    b1i = shufps(bs2,bs2,0xff);
    r0i += a1*b1i;

#ifdef LOAD1
    a2 = loadpsa(foff(&a[i],28));
    a2 = loadhps(a2,foff(&a[i],34));
#else
    a2 = shufps(aa1,aa2,0xe4);
#endif
    b2r = shufps(bs3,bs3,0xaa);
    r0r += a2*b2r;
    b2i = shufps(bs3,bs3,0xff);
    r0i += a2*b2i;

    r0i = shufps(r0i, r0i, 0xb1);
    r0r += xorps(r0i, _sse_sgn13);
    storepsr(foff(&r[i],8), r0r);

  }
}

#undef loadpsa
#undef loadpsr
#undef storepsr
#define loadpsa(a) loadups(a)
#define loadpsr(a) loadups(a)
#define storepsr(a,b) storeups(a,b)
inline static void
QLA_F3_V_vpeq_M_times_pV_2uu( QLA_F3_ColorVector *__restrict__ r,
			      QLA_F3_ColorMatrix *a,
			      QLA_F3_ColorVector **b,
			      int n )
{
  v4sf a0, a1, a2;
  v4sf bs0, bs1, b0r, b0i, b1r, b1i, b2r, b2i;
  v4sf r0r, r0i;
  v4sf bs2, bs3;
#ifndef LOAD1
  v4sf aa0, aa1, aa2;
#endif
  int i;

  for(i=0; i<n; i+=2) {

#ifdef LOAD1
    a0 = loadpsa(foff(&a[i],0));
    a0 = loadhps(a0,foff(&a[i],6));
#else
    aa0 = loadpsa(foff(&a[i],0));
    aa1 = loadpsa(foff(&a[i],4));
    a0 = shufps(aa0,aa1,0xe4);
#endif
    bs0 = loadups(b[i]);
    b0r = shufps(bs0,bs0,0x00);
    r0r = a0*b0r + loadpsr(&r[i]);
    b0i = shufps(bs0,bs0,0x55);
    r0i = a0*b0i;

#ifdef LOAD1
    a1 = loadups(foff(&a[i],2));
    a1 = loadhps(a1,foff(&a[i],8));
#else
    aa2 = loadpsa(foff(&a[i],8));
    a1 = shufps(aa0,aa2,0x4e);
#endif
    b1r = shufps(bs0,bs0,0xaa);
    r0r += a1*b1r;
    b1i = shufps(bs0,bs0,0xff);
    r0i += a1*b1i;

#ifdef LOAD1
    a2 = loadpsa(foff(&a[i],4));
    a2 = loadhps(a2,foff(&a[i],10));
#else
    a2 = shufps(aa1,aa2,0xe4);
#endif
    bs1 = loadups(foff(b[i],2));
    b2r = shufps(bs1,bs1,0xaa);
    r0r += a2*b2r;
    b2i = shufps(bs1,bs1,0xff);
    r0i += a2*b2i;

    r0i = shufps(r0i, r0i, 0xb1);
    r0r += xorps(r0i, _sse_sgn13);
    storepsr(&r[i], r0r);

#ifdef LOAD1
    a0 = loadpsa(foff(&a[i],12));
    a0 = loadhps(a0,foff(&a[i],18));
#else
    aa0 = loadpsa(foff(&a[i],12));
    aa1 = loadpsa(foff(&a[i],16));
    a0 = shufps(aa0,aa1,0xe4);
#endif
    bs2 = loadups(b[i+1]);
    b0r = shufps(bs0,bs2,0x00);
    r0r = a0*b0r + loadpsr(foff(&r[i],4));
    b0i = shufps(bs0,bs2,0x55);
    r0i = a0*b0i;

#ifdef LOAD1
    a1 = loadups(foff(&a[i],14));
    a1 = loadhps(a1,foff(&a[i],20));
#else
    aa2 = loadpsa(foff(&a[i],20));
    a1 = shufps(aa0,aa2,0x4e);
#endif
    b1r = shufps(bs0,bs2,0xaa);
    r0r += a1*b1r;
    b1i = shufps(bs0,bs2,0xff);
    r0i += a1*b1i;

#ifdef LOAD1
    a2 = loadpsa(foff(&a[i],16));
    a2 = loadhps(a2,foff(&a[i],22));
#else
    a2 = shufps(aa1,aa2,0xe4);
#endif
    bs3 = loadups(foff(b[i+1],2));
    b2r = shufps(bs1,bs3,0xaa);
    r0r += a2*b2r;
    b2i = shufps(bs1,bs3,0xff);
    r0i += a2*b2i;

    r0i = shufps(r0i, r0i, 0xb1);
    r0r += xorps(r0i, _sse_sgn13);
    storepsr(foff(&r[i],4), r0r);


#ifdef LOAD1
    a0 = loadpsa(foff(&a[i],24));
    a0 = loadhps(a0,foff(&a[i],30));
#else
    aa0 = loadpsa(foff(&a[i],24));
    aa1 = loadpsa(foff(&a[i],28));
    a0 = shufps(aa0,aa1,0xe4);
#endif
    b0r = shufps(bs2,bs2,0x00);
    r0r = a0*b0r + loadpsr(foff(&r[i],8));
    b0i = shufps(bs2,bs2,0x55);
    r0i = a0*b0i;

#ifdef LOAD1
    a1 = loadups(foff(&a[i],26));
    a1 = loadhps(a1,foff(&a[i],32));
#else
    aa2 = loadpsa(foff(&a[i],32));
    a1 = shufps(aa0,aa2,0x4e);
#endif
    b1r = shufps(bs2,bs2,0xaa);
    r0r += a1*b1r;
    b1i = shufps(bs2,bs2,0xff);
    r0i += a1*b1i;

#ifdef LOAD1
    a2 = loadpsa(foff(&a[i],28));
    a2 = loadhps(a2,foff(&a[i],34));
#else
    a2 = shufps(aa1,aa2,0xe4);
#endif
    b2r = shufps(bs3,bs3,0xaa);
    r0r += a2*b2r;
    b2i = shufps(bs3,bs3,0xff);
    r0i += a2*b2i;

    r0i = shufps(r0i, r0i, 0xb1);
    r0r += xorps(r0i, _sse_sgn13);
    storepsr(foff(&r[i],8), r0r);

  }
}

inline static void
QLA_F3_V_vpeq_M_times_pV_1u( QLA_F3_ColorVector *__restrict__ r,
			     QLA_F3_ColorMatrix *a,
			     QLA_F3_ColorVector **b,
			     int n )
{
  v4sf a0, a1, a2;
  v4sf bs0, bs1, b0r, b0i, b1r, b1i, b2r, b2i;
  v4sf r0r, r0i;
  int i;

  for(i=0; i<n; i++) {
    a0 = loadups(foff(&a[i],0));
    a0 = loadhps(a0,foff(&a[i],6));
    bs0 = loadups(b[i]);
    b0r = shufps(bs0,bs0,0x00);
    r0r = loadups(&r[i]);
    r0r += a0*b0r;
    b0i = shufps(bs0,bs0,0x55);
    r0i = a0*b0i;

    a1 = loadups(foff(&a[i],2));
    a1 = loadhps(a1,foff(&a[i],8));
    b1r = shufps(bs0,bs0,0xaa);
    r0r += a1*b1r;
    b1i = shufps(bs0,bs0,0xff);
    r0i += a1*b1i;

    a2 = loadups(foff(&a[i],4));
    a2 = loadhps(a2,foff(&a[i],10));
    bs1 = loadups(foff(b[i],2));
    b2r = shufps(bs1,bs1,0xaa);
    r0r += a2*b2r;
    b2i = shufps(bs1,bs1,0xff);
    r0i += a2*b2i;

    r0i = shufps(r0i, r0i, 0xb1);
    r0r += xorps(r0i, _sse_sgn13);
    storeups(&r[i], r0r);

    *foff(&r[i],4) +=
      + (*foff(&a[i],12)) * (*foff(b[i],0))
      - (*foff(&a[i],13)) * (*foff(b[i],1))
      + (*foff(&a[i],14)) * (*foff(b[i],2))
      - (*foff(&a[i],15)) * (*foff(b[i],3))
      + (*foff(&a[i],16)) * (*foff(b[i],4))
      - (*foff(&a[i],17)) * (*foff(b[i],5));
    *foff(&r[i],5) +=
      + (*foff(&a[i],12)) * (*foff(b[i],1))
      + (*foff(&a[i],13)) * (*foff(b[i],0))
      + (*foff(&a[i],14)) * (*foff(b[i],3))
      + (*foff(&a[i],15)) * (*foff(b[i],2))
      + (*foff(&a[i],16)) * (*foff(b[i],5))
      + (*foff(&a[i],17)) * (*foff(b[i],4));
  }
}

void
QLA_F3_V_vpeq_M_times_pV( QLA_F3_ColorVector *__restrict__ r,
			  QLA_F3_ColorMatrix *a,
			  QLA_F3_ColorVector **b,
			  int n )
{
  size_t s8=0x7, s16=0xf;
  size_t sr = (size_t)r;
  size_t sa = (size_t)a;
  int r16, a16, ra8;
  int nb1, n1, nb2, n2;

  r16 = ((sr&s16)==0);
  a16 = ((sa&s16)==0);
  ra8 = ((sr&s8)==0)&&((sa&s8)==0);
  //printf("%p %p %i %i\n", r, a, a8, a16);

  if( ra8 && !r16 ) nb1 = 1;
  else nb1 = 0;
  n1 = n - nb1;
  if(n1&1) n1--;
  nb2 = nb1 + n1;
  n2 = n - nb2;

  if(nb1) QLA_F3_V_vpeq_M_times_pV_1u(r, a, b, nb1);
  if(n1) {
    if(ra8) {
      if( r16 == a16 ) {
	QLA_F3_V_vpeq_M_times_pV_2aa(r+nb1, a+nb1, b+nb1, n1);
      } else {
	QLA_F3_V_vpeq_M_times_pV_2au(r+nb1, a+nb1, b+nb1, n1);
      }
    } else {
      QLA_F3_V_vpeq_M_times_pV_2uu(r+nb1, a+nb1, b+nb1, n1);
    }
  }
  if(n2) QLA_F3_V_vpeq_M_times_pV_1u(r+nb2, a+nb2, b+nb2, n2);

}
