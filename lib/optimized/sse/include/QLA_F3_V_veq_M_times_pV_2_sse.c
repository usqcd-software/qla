{
#pragma omp parallel for
  for(int i=0; i<n; i+=2) {
    v4sf a0, a1, a2;
    v4sf bs0, bs1, b0r, b0i, b1r, b1i, b2r, b2i;
    v4sf r0r, r0i;
    v4sf bs2, bs3;
#ifndef LOAD1
    v4sf aa0, aa1, aa2;
#endif

    //prefetchnt(&r[i+NP]);
    //prefetchnt(&a[i+NP]);
    //prefetchnt(b[i+NP]);

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
    //r0r = addps(mulps(a0,b0r),loadpsr(&r[i]));
    r0r = mulps(a0,b0r);
    b0i = shufps(bs0,bs0,0x55);
    r0i = mulps(a0,b0i);

#ifdef LOAD1
    a1 = loadups(foff(&a[i],2));
    a1 = loadhps(a1,foff(&a[i],8));
#else
    aa2 = loadpsa(foff(&a[i],8));
    a1 = shufps(aa0,aa2,0x4e);
#endif
    b1r = shufps(bs0,bs0,0xaa);
    r0r = addps(r0r,mulps(a1,b1r));
    b1i = shufps(bs0,bs0,0xff);
    r0i = addps(r0i,mulps(a1,b1i));

#ifdef LOAD1
    a2 = loadpsa(foff(&a[i],4));
    a2 = loadhps(a2,foff(&a[i],10));
#else
    a2 = shufps(aa1,aa2,0xe4);
#endif
    bs1 = loadups(foff(b[i],2));
    b2r = shufps(bs1,bs1,0xaa);
    r0r = addps(r0r,mulps(a2,b2r));
    b2i = shufps(bs1,bs1,0xff);
    r0i = addps(r0i,mulps(a2,b2i));

    r0i = shufps(r0i, r0i, 0xb1);
    r0r = addsubps(r0r, r0i);
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
    //r0r = addps(mulps(a0,b0r), loadpsr(foff(&r[i],4)));
    r0r = mulps(a0,b0r);
    b0i = shufps(bs0,bs2,0x55);
    r0i = mulps(a0,b0i);

#ifdef LOAD1
    a1 = loadups(foff(&a[i],14));
    a1 = loadhps(a1,foff(&a[i],20));
#else
    aa2 = loadpsa(foff(&a[i],20));
    a1 = shufps(aa0,aa2,0x4e);
#endif
    b1r = shufps(bs0,bs2,0xaa);
    r0r = addps(r0r,mulps(a1,b1r));
    b1i = shufps(bs0,bs2,0xff);
    r0i = addps(r0i,mulps(a1,b1i));

    //prefetchnt(&r[i+12]);
    //prefetchnt(&a[i+12]);
    //prefetchnt(b[i+NP+1]);

#ifdef LOAD1
    a2 = loadpsa(foff(&a[i],16));
    a2 = loadhps(a2,foff(&a[i],22));
#else
    a2 = shufps(aa1,aa2,0xe4);
#endif
    bs3 = loadups(foff(b[i+1],2));
    b2r = shufps(bs1,bs3,0xaa);
    r0r = addps(r0r,mulps(a2,b2r));
    b2i = shufps(bs1,bs3,0xff);
    r0i = addps(r0i,mulps(a2,b2i));

    r0i = shufps(r0i, r0i, 0xb1);
    r0r = addsubps(r0r, r0i);
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
    //r0r = addps(mulps(a0,b0r), loadpsr(foff(&r[i],8)));
    r0r = mulps(a0,b0r);
    b0i = shufps(bs2,bs2,0x55);
    r0i = mulps(a0,b0i);

#ifdef LOAD1
    a1 = loadups(foff(&a[i],26));
    a1 = loadhps(a1,foff(&a[i],32));
#else
    aa2 = loadpsa(foff(&a[i],32));
    a1 = shufps(aa0,aa2,0x4e);
#endif
    b1r = shufps(bs2,bs2,0xaa);
    r0r = addps(r0r,mulps(a1,b1r));
    b1i = shufps(bs2,bs2,0xff);
    r0i = addps(r0i,mulps(a1,b1i));

#ifdef LOAD1
    a2 = loadpsa(foff(&a[i],28));
    a2 = loadhps(a2,foff(&a[i],34));
#else
    a2 = shufps(aa1,aa2,0xe4);
#endif
    b2r = shufps(bs3,bs3,0xaa);
    r0r = addps(r0r,mulps(a2,b2r));
    b2i = shufps(bs3,bs3,0xff);
    r0i = addps(r0i,mulps(a2,b2i));

    r0i = shufps(r0i, r0i, 0xb1);
    r0r = addsubps(r0r, r0i);
    storepsr(foff(&r[i],8), r0r);

  }
}
