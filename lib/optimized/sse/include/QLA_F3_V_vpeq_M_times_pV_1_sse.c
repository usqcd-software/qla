{
  v4sf a0, a1, a2;
  v4sf bs0, bs1, b0r, b0i, b1r, b1i, b2r, b2i;
  v4sf r0r, r0i;
  int i;

#pragma omp parallel for
  for(i=0; i<n; i++) {
    a0 = loadups(foff(&a[i],0));
    a0 = loadhps(a0,foff(&a[i],6));
    bs0 = loadups(b[i]);
    b0r = shufps(bs0,bs0,0x00);
    r0r = loadups(&r[i]);
    r0r = addps(r0r,mulps(a0,b0r));
    b0i = shufps(bs0,bs0,0x55);
    r0i = mulps(a0,b0i);

    a1 = loadups(foff(&a[i],2));
    a1 = loadhps(a1,foff(&a[i],8));
    b1r = shufps(bs0,bs0,0xaa);
    r0r = addps(r0r,mulps(a1,b1r));
    b1i = shufps(bs0,bs0,0xff);
    r0i = addps(r0i,mulps(a1,b1i));

    a2 = loadups(foff(&a[i],4));
    a2 = loadhps(a2,foff(&a[i],10));
    bs1 = loadups(foff(b[i],2));
    b2r = shufps(bs1,bs1,0xaa);
    r0r = addps(r0r,mulps(a2,b2r));
    b2i = shufps(bs1,bs1,0xff);
    r0i = addps(r0i,mulps(a2,b2i));

    r0i = shufps(r0i, r0i, 0xb1);
    r0r = addsubps(r0r, r0i);
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
