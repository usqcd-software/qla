#define mult_c_h(rr, ri, a, b)			\
  mt1 = loadups(foff(&a,0));                    \
  mt2 = shufps(mt1, mt1, 0x0);                  \
  rr = mulps(mt2, b);				\
  mt3 = shufps(mt1, mt1, 0x55);                 \
  ri = mulps(mt3, b)
#define multadd_c_h(rr, ri, a, b)               \
  mt1 = loadups(foff(&a,0));                    \
  mt2 = shufps(mt1, mt1, 0x0);                  \
  rr = addps(rr, mulps(mt2, b));		\
  mt3 = shufps(mt1, mt1, 0x55);                 \
  ri = addps(ri, mulps(mt3, b))

#define mult_c0_h(rr, ri, b)			\
  mt2 = shufps(mt1, mt1, 0x0);                  \
  rr = mulps(mt2, b);				\
  mt3 = shufps(mt1, mt1, 0x55);                 \
  ri = mulps(mt3, b)
#define mult_c1_h(rr, ri, b)			 \
  mt2 = shufps(mt1, mt1, 0xaa);                  \
  rr = mulps(mt2, b);				 \
  mt3 = shufps(mt1, mt1, 0xff);			 \
  ri = mulps(mt3, b)
#define multadd_c0_h(rr, ri, b)               \
  mt2 = shufps(mt1, mt1, 0x0);                  \
  rr = addps(rr, mulps(mt2, b));		\
  mt3 = shufps(mt1, mt1, 0x55);                 \
  ri = addps(ri, mulps(mt3, b))
#define multadd_c1_h(rr, ri, b)               \
  mt2 = shufps(mt1, mt1, 0xaa);                  \
  rr = addps(rr, mulps(mt2, b));		\
  mt3 = shufps(mt1, mt1, 0xff);                 \
  ri = addps(ri, mulps(mt3, b))

#define NP 6
{
  int i;
  for(i=0;i<n;i++) {
    v4sf h1[3], h2[3];
    QLA_F3_DiracFermion *ri = &r[i];
    QLA_F3_ColorMatrix *ai = &a[i];
    QLA_F3_DiracFermion *bi = b[i];
    //prefetchnt(b[i+NP]);
    {
      int i_c;
      for(i_c=0;i_c<3;i_c++) {
	spproj(SP)(h1[i_c], foff(bi,8*i_c));
      }
    }
    prefetchnt(&a[i+NP]);
    {
#if 0
      int i_c;
      for(i_c=0;i_c<3;i_c++) {
	v4sf mti, mt1, mt2, mt3;
	mult_c_h(h2[i_c], mti, QLA_F3_elem_M(*ai,i_c,0), h1[0]);
	multadd_c_h(h2[i_c], mti, QLA_F3_elem_M(*ai,i_c,1), h1[1]);
	multadd_c_h(h2[i_c], mti, QLA_F3_elem_M(*ai,i_c,2), h1[2]);
	mti = shufps(mti, mti, 0xb1);
	h2[i_c] = addsubps(h2[i_c],mti);
      }
#else
      v4sf mti, mt1, mt2, mt3;
      mt1 = loadups(&QLA_F3_elem_M(*ai,0,0));
      mult_c0_h(h2[0], mti, h1[0]);
      multadd_c1_h(h2[0], mti, h1[1]);
      mt1 = loadups(&QLA_F3_elem_M(*ai,0,2));
      multadd_c0_h(h2[0], mti, h1[2]);
      mti = shufps(mti, mti, 0xb1);
      h2[0] = addsubps(h2[0],mti);
      mult_c1_h(h2[1], mti, h1[0]);
      mt1 = loadups(&QLA_F3_elem_M(*ai,1,1));
      multadd_c0_h(h2[1], mti, h1[1]);
      multadd_c1_h(h2[1], mti, h1[2]);
      mti = shufps(mti, mti, 0xb1);
      h2[1] = addsubps(h2[1],mti);
      mt1 = loadups(&QLA_F3_elem_M(*ai,2,0));
      mult_c0_h(h2[2], mti, h1[0]);
      multadd_c1_h(h2[2], mti, h1[1]);
      mt1 = loadups(&QLA_F3_elem_M(*ai,2,1));
      multadd_c1_h(h2[2], mti, h1[2]);
      mti = shufps(mti, mti, 0xb1);
      h2[2] = addsubps(h2[2],mti);
#endif
    }
    prefetch(&r[i+NP]);
    {
      int i_c;
      for(i_c=0; i_c<3; i_c++) {
#ifdef GAMMA_5_PLUS
	storeaps(foff(ri,8*i_c), addps(loadaps(foff(ri,8*i_c)), h2[i_c]));
#elif defined GAMMA_5_MINUS
	storeaps(foff(ri,8*i_c+4), addps(loadaps(foff(ri,8*i_c+4)), h2[i_c]));
#else
	v4sf x1;
	storeaps(foff(ri,8*i_c), addps(loadaps(foff(ri,8*i_c)), h2[i_c]));
	sprecon(SP)(x1, h2[i_c]);
	storeaps(foff(ri,8*i_c+4), addps(loadaps(foff(ri,8*i_c+4)), x1));
#endif
      }
    }
  }
}
#undef mult_c_h
#undef multadd_c_h
#undef mult_c0_h
#undef mult_c1_h
#undef multadd_c0_h
#undef multadd_c1_h
#undef NP
