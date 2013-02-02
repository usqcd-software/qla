#define OCT4(a,b,c,d) (512*(a)+64*(b)+8*(c)+(d))
#define setpair() V4D perm_pair = vec_gpci(OCT4(0,1,6,7))
#define pair(a,b) vec_perm(a,b,perm_pair)
#define pairx(a,b) vec_sldw(a,b,2)
#define cmadd(r,a,b) r = vec_xmadd(a,b,r); r = vec_xxnpmadd(b,a,r)
#define cmadd2i(r0,r1,a,b) r1 = vec_xmul(a,b); r0 = vec_xxnpmadd(b,a,r0)
#define cmadd2(r0,r1,a,b) r1 = vec_xmadd(a,b,r1); r0 = vec_xxnpmadd(b,a,r0)
#define cmadd2f(r0,r1,a,b) r1 = vec_xmadd(a,b,r1); r0 = vec_xxnpmadd(b,a,r0); r0 = vec_add(r0,r1)
#define mul231(rp,ro,ap,ao,b0,b1,b2) do { \
  V4D r0 = v4loadf(rp,ro); \
  V4D a0 = v4loadf(ap,ao); \
  V4D a1 = v4loadf(ap,ao+16); \
  V4D a2 = v4loadf(ap,ao+32); \
  V4D c0 = pair(a0,a1); \
  V4D r1; \
  cmadd2i(r0,r1, c0, b0);	 \
  V4D c1 = pairx(a0,a2); \
  cmadd2(r0,r1, c1, b1);	 \
  V4D c2 = pair(a1,a2); \
  cmadd2f(r0,r1, c2, b2);			\
  v4storef(rp,ro,r0); \
  } while(0)
#define mul231p(r0,a0,a1,a2,b0,b1,b2) do {	\
  V4D c0 = pair(a0,a1); \
  V4D r1; \
  cmadd2i(r0,r1, c0, b0);	 \
  V4D c1 = pairx(a0,a2); \
  cmadd2(r0,r1, c1, b1);	 \
  V4D c2 = pair(a1,a2); \
  cmadd2f(r0,r1, c2, b2);			\
  } while(0)
#define mul1131(rp,ro,ap,ao,b00,b01,b02,b10,b11,b12) do { \
  V4D r0 = v4loadf(rp,ro); \
  V4D a0 = v4loadf(ap,ao); \
  V4D a1 = v4loadf(ap,ao+16); \
  V4D a2 = v4loadf(ap,ao+32); \
  V4D c0 = pair(a0,a1); \
  V4D b0 = pair(b00,b10); \
  V4D r1; \
  cmadd2i(r0,r1, c0, b0);	 \
  V4D c1 = pairx(a0,a2); \
  V4D b1 = pair(b01,b11); \
  cmadd2(r0,r1, c1, b1);	  \
  V4D c2 = pair(a1,a2); \
  V4D b2 = pair(b02,b12); \
  cmadd2f(r0,r1, c2, b2);	  \
  v4storef(rp,ro,r0); \
  } while(0)
#define mul1131p(r0,a0,a1,a2,b00,b01,b02,b10,b11,b12) do { \
  V4D c0 = pair(a0,a1); \
  V4D b0 = pair(b00,b10); \
  V4D rt; \
  cmadd2i(r0,rt, c0, b0);	 \
  V4D c1 = pairx(a0,a2); \
  V4D b1 = pair(b01,b11); \
  cmadd2(r0,rt, c1, b1);	  \
  V4D c2 = pair(a1,a2); \
  V4D b2 = pair(b02,b12); \
  cmadd2f(r0,rt, c2, b2);	  \
  } while(0)


void
QLA_F3_V_vpeq_M_times_pV_a2(QLA_F3_ColorVector *restrict r, QLA_F3_ColorMatrix *restrict a,
			    QLA_F3_ColorVector *restrict *b, int n)
{
  setpair();
#pragma omp parallel for
  for(int i=0; i<n; i+=2) {
    float *ri0 = (float *) &r[i];
    float *ai0 = (float *) &a[i];
    float *bi0 = (float *) b[i];
    float *bi1 = (float *) b[i+1];
    V4D r0 = v4loadf(ri0,0);
    V4D r1 = v4loadf(ri0,16);
    V4D r2 = v4loadf(ri0,32);
    V4D a00 = v4loadf(ai0,0);
    V4D a01 = v4loadf(ai0,16);
    V4D a02 = v4loadf(ai0,32);
    V4D a10 = v4loadf(ai0,48);
    V4D a11 = v4loadf(ai0,64);
    V4D a12 = v4loadf(ai0,80);
    V4D a20 = v4loadf(ai0,96);
    V4D a21 = v4loadf(ai0,112);
    V4D a22 = v4loadf(ai0,128);
    V4D b00 = v4load2f(bi0,0);
    V4D b01 = v4load2f(bi0,8);
    V4D b02 = v4load2f(bi0,16);
    V4D b10 = v4load2f(bi1,0);
    V4D b11 = v4load2f(bi1,8);
    V4D b12 = v4load2f(bi1,16);
    //mul231 (ri0, 0, ai0, 0, b00,b01,b02);
    mul231p(r0, a00,a01,a02, b00,b01,b02);
    //mul1131(ri0,16, ai0,48, b00,b01,b02, b10,b11,b12);
    mul1131p(r1, a10,a11,a12, b00,b01,b02, b10,b11,b12);
    //mul231 (ri0,32, ai0,96, b10,b11,b12);
    mul231p(r2, a20,a21,a22, b10,b11,b12);
    v4storef(ri0,0,r0);
    v4storef(ri0,16,r1);
    v4storef(ri0,32,r2);
  }
}
