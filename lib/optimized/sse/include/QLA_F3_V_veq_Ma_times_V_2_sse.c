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
    //prefetchnt(&r[i+NP]);
    //prefetchnt(&a[i+NP]);
    //prefetchnt(b[i+NP]);

    a0 = loadpsa(foff(&a[i],0));
    bs0 = loadups(&b[i]);
    b0r = shufps(bs0,bs0,0x00);
    r0r = mulps(a0,b0r);
    b0i = shufps(bs0,bs0,0x55);
    r0i = mulps(a0,b0i);

    aa0 = loadpsa(foff(&a[i],4));
    aa1 = loadpsa(foff(&a[i],8));
    a1 = shufps(aa0,aa1,0x4e);
    b1r = shufps(bs0,bs0,0xaa);
    r0r = addps(r0r,mulps(a1,b1r));
    b1i = shufps(bs0,bs0,0xff);
    r0i = addps(r0i,mulps(a1,b1i));

    a2 = loadpsa(foff(&a[i],12));
    bs1 = loadups(foff(&b[i],2));
    b2r = shufps(bs1,bs1,0xaa);
    r0r = addps(r0r,mulps(a2,b2r));
    b2i = shufps(bs1,bs1,0xff);
    r0i = addps(r0i,mulps(a2,b2i));

    r0i = shufps(r0i, r0i, 0xb1);
    r0i = addps(r0i, sign02(r0r));
    storepsr(&r[i], r0i);


    aa2 = loadpsa(foff(&a[i],16));
    a0 = shufps(aa0,aa2,0xe4);
    bs2 = loadups(&b[i+1]);
    b0r = shufps(bs0,bs2,0x00);
    r0r = mulps(a0,b0r);
    b0i = shufps(bs0,bs2,0x55);
    r0i = mulps(a0,b0i);

    a0 = loadpsa(foff(&a[i],20));
    aa0 = loadpsa(foff(&a[i],24));
    a1 = shufps(aa1,aa0,0x4e);
    b1r = shufps(bs0,bs2,0xaa);
    r0r = addps(r0r,mulps(a1,b1r));
    b1i = shufps(bs0,bs2,0xff);
    r0i = addps(r0i,mulps(a1,b1i));

    //prefetchnt(&r[i+12]);
    //prefetchnt(&a[i+12]);
    //prefetchnt(b[i+NP+1]);

    aa1 = loadpsa(foff(&a[i],28));
    a2 = shufps(aa2,aa1,0xe4);
    bs3 = loadups(foff(&b[i+1],2));
    b2r = shufps(bs1,bs3,0xaa);
    r0r = addps(r0r,mulps(a2,b2r));
    b2i = shufps(bs1,bs3,0xff);
    r0i = addps(r0i,mulps(a2,b2i));

    r0i = shufps(r0i, r0i, 0xb1);
    r0i = addps(r0i, sign02(r0r));
    storepsr(foff(&r[i],4), r0i);


    b0r = shufps(bs2,bs2,0x00);
    r0r = mulps(a0,b0r);
    b0i = shufps(bs2,bs2,0x55);
    r0i = mulps(a0,b0i);

    a1 = shufps(aa0,aa1,0x4e);
    b1r = shufps(bs2,bs2,0xaa);
    r0r = addps(r0r,mulps(a1,b1r));
    b1i = shufps(bs2,bs2,0xff);
    r0i = addps(r0i,mulps(a1,b1i));

    a2 = loadpsa(foff(&a[i],32));
    b2r = shufps(bs3,bs3,0xaa);
    r0r = addps(r0r,mulps(a2,b2r));
    b2i = shufps(bs3,bs3,0xff);
    r0i = addps(r0i,mulps(a2,b2i));

    r0i = shufps(r0i, r0i, 0xb1);
    r0i = addps(r0i, sign02(r0r));
    storepsr(foff(&r[i],8), r0i);

  }
}
