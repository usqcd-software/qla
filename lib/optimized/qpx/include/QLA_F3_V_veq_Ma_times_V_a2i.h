#define OCT4(a,b,c,d) (512*(a)+64*(b)+8*(c)+(d))
#define setpair() V4D perm_pair = vec_gpci(OCT4(0,1,6,7))
#define pair(a,b) vec_perm(a,b,perm_pair)
#define pairx(a,b) vec_sldw(a,b,2)
#define cmulan(r0,r1,a,b) r0 = vec_xmul(a,b); r1 = vec_xxcpnmadd(b,a,v4z)
#define cmaddan(r0,r1,a,b) r0 = vec_xmadd(a,b,r0); r1 = vec_xxcpnmadd(b,a,r1)
#define pair01(x,y) pair(x,y)
#define pair10(x,y) pairx(x,y)
#define pair00(a,b) vec_perm(a,b,perm_pair00)
#define pair11(a,b) vec_perm(a,b,perm_pair11)
#define B2

void
QLA_F3_V_veq_Ma_times_V_a2(QLA_F3_ColorVector *restrict r, QLA_F3_ColorMatrix *restrict a,
			   QLA_F3_ColorVector *restrict b, int n)
{
#ifndef B2
  V4D perm_pair00 = vec_gpci(OCT4(0,1,4,5));
  V4D perm_pair11 = vec_gpci(OCT4(2,3,6,7));
#endif
  V4D v4z = v4splat(0);
  setpair();
#pragma omp parallel for
  for(int i=0; i<n; i+=2) {
    float *ri0 = (float *) &r[i];
    float *ai0 = (float *) &a[i];
    float *bi0 = (float *) &b[i];
    V4D a00 = v4loadf(ai0,0);
    V4D a01 = v4loadf(ai0,16);
    V4D a02 = v4loadf(ai0,32);
    V4D a10 = v4loadf(ai0,48);
    V4D a11 = v4loadf(ai0,64);
    V4D a12 = v4loadf(ai0,80);
    V4D a20 = v4loadf(ai0,96);
    V4D a21 = v4loadf(ai0,112);
    V4D a22 = v4loadf(ai0,128);
#ifndef B2
    V4D b0 = v4loadf(bi0,0);
    V4D b1 = v4loadf(bi0,16);
    V4D b2 = v4loadf(bi0,32);
#else
    V4D b00 = v4load2f(bi0,0);
    V4D b01 = v4load2f(bi0,8);
    V4D b02 = v4load2f(bi0,16);
    V4D b20 = v4load2f(bi0,24);
    V4D b21 = v4load2f(bi0,32);
    V4D b22 = v4load2f(bi0,40);
#endif
    V4D r0, r1, r2;
    V4D r0t, r1t, r2t;

#ifndef B2
    V4D b00 = pair00(b0, b0);
    V4D b01 = pair11(b0, b0);
    V4D b02 = pair00(b1, b1);
#endif
    V4D a011020 = pairx(a01, a02);
    cmulan(r0,r0t, a00, b00);
    cmaddan(r0,r0t, a011020, b01);
    cmaddan(r0,r0t, a10, b02);

#ifndef B2
    V4D b10 = pair01(b0, b1);
    V4D b11 = pair10(b0, b2);
    V4D b12 = pair01(b1, b2);
#else
    V4D b10 = pairx(b00, b20);
    V4D b11 = pairx(b01, b21);
    V4D b12 = pairx(b02, b22);
#endif
    V4D a010111 = pair(a01, a11);
    V4D a021200 = pairx(a02, a20);
    V4D a110211 = pair(a11, a21);
    cmulan(r1,r1t, a010111, b10);
    cmaddan(r1,r1t, a021200, b11);
    cmaddan(r1,r1t, a110211, b12);

#ifndef B2
    V4D b20 = pair11(b1, b1);
    V4D b21 = pair00(b2, b2);
    V4D b22 = pair11(b2, b2);
#endif
    V4D a201210 = pairx(a20, a21);
    cmulan(r2,r2t, a12, b20);
    cmaddan(r2,r2t, a201210, b21);
    cmaddan(r2,r2t, a22, b22);

    v4storef(ri0, 0,v4add(r0,r0t));
    v4storef(ri0,16,v4add(r1,r1t));
    v4storef(ri0,32,v4add(r2,r2t));
  }
}
