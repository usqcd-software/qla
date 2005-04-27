#define evr(x,i) QLA_real(QLA_F3_elem_V((*(x)),i))
#define evi(x,i) QLA_imag(QLA_F3_elem_V((*(x)),i))
#define emr(x,i,j) QLA_real(QLA_F3_elem_M((*(x)),i,j))
#define emi(x,i,j) QLA_imag(QLA_F3_elem_M((*(x)),i,j))

//#define XLC
//#define NATIVEDOUBLE

#ifdef NATIVEDOUBLE
#define temp_t double
#ifdef XLC
#define multa(a,b,c) a = __fmadd(b,c,a)
#define mults(a,b,c) a = __fnmsub(b,c,a)
#else
#define multa(a,b,c) a += b*c
#define mults(a,b,c) a -= b*c
#endif
#else
#define temp_t float
#ifdef XLC
#define multa(a,b,c) a = __fmadds(b,c,a)
#define mults(a,b,c) a = __fnmsubs(b,c,a)
#else
#define multa(a,b,c) a += b*c
#define mults(a,b,c) a -= b*c
#endif
#endif

#if 0
#define QLA_F3_V_peq_M_times_V(aa,bb,cc) \
{ \
  mult_col(aa, bb, cc, 0) \
  mult_col(aa, bb, cc, 1) \
  mult_col(aa, bb, cc, 2) \
}
#endif

#if 0
#define QLA_F3_V_peq_M_times_V(aa,bb,cc) \
{ \
  temp_t aar0 = evr(aa,0); \
  temp_t aai0 = evi(aa,0); \
  temp_t aar1 = evr(aa,1); \
  temp_t aai1 = evi(aa,1); \
  temp_t aar2 = evr(aa,2); \
  temp_t aai2 = evi(aa,2); \
  mult_colv(bb, cc, 0) \
  mult_colv(bb, cc, 1) \
  mult_colv(bb, cc, 2) \
  evr(aa,0) = aar0; \
  evi(aa,0) = aai0; \
  evr(aa,1) = aar1; \
  evi(aa,1) = aai1; \
  evr(aa,2) = aar2; \
  evi(aa,2) = aai2; \
}
#endif

#define QLA_F3_V_peq_M_times_V(aa,bb,cc) \
{ \
  temp_t aar0, aai0, aar1, aai1, aar2, aai2; \
  { \
  temp_t bbr0, bbi0, bbr1, bbi1, bbr2, bbi2; \
  temp_t ccr, cci; \
  aar0 = evr(aa,0); \
  bbr0 = emr(bb,0,0); \
  ccr = evr(cc,0); \
  multa(aar0, bbr0, ccr); \
  aai0 = evi(aa,0); \
  cci = evi(cc,0); \
  multa(aai0, bbr0, cci); \
  aar1 = evr(aa,1); \
  bbr1 = emr(bb,1,0); \
  multa(aar1, bbr1, ccr); \
  aai1 = evi(aa,1); \
  multa(aai1, bbr1, cci); \
  aar2 = evr(aa,2); \
  bbr2 = emr(bb,2,0); \
  multa(aar2, bbr2, ccr); \
  aai2 = evi(aa,2); \
  multa(aai2, bbr2, cci); \
  bbi0 = emi(bb,0,0); \
  mults(aar0, bbi0, cci); \
  bbi1 = emi(bb,1,0); \
  multa(aai0, bbi0, ccr); \
  mults(aar1, bbi1, cci); \
  bbi2 = emi(bb,2,0); \
  multa(aai1, bbi1, ccr); \
  mults(aar2, bbi2, cci); \
  multa(aai2, bbi2, ccr); \
  } \
  mult_colv(bb, cc, 1) \
  mult_colv(bb, cc, 2) \
  evr(aa,0) = aar0; \
  evi(aa,0) = aai0; \
  evr(aa,1) = aar1; \
  evi(aa,1) = aai1; \
  evr(aa,2) = aar2; \
  evi(aa,2) = aai2; \
}

#define mult_colv(bb,cc,col) \
{ \
  temp_t bbr0, bbi0, bbr1, bbi1, bbr2, bbi2; \
  temp_t ccr, cci; \
  ccr = evr(cc,col); \
  cci = evi(cc,col); \
  bbr0 = emr(bb,0,col); \
  multa(aar0, bbr0, ccr); \
  bbr1 = emr(bb,1,col); \
  multa(aai0, bbr0, cci); \
  multa(aar1, bbr1, ccr); \
  bbr2 = emr(bb,2,col); \
  multa(aai1, bbr1, cci); \
  multa(aar2, bbr2, ccr); \
  bbi0 = emi(bb,0,col); \
  multa(aai2, bbr2, cci); \
  mults(aar0, bbi0, cci); \
  bbi1 = emi(bb,1,col); \
  multa(aai0, bbi0, ccr); \
  mults(aar1, bbi1, cci); \
  bbi2 = emi(bb,2,col); \
  multa(aai1, bbi1, ccr); \
  mults(aar2, bbi2, cci); \
  multa(aai2, bbi2, ccr); \
}

#define mult_c_crcv2(bb,col) \
 temp_t bbr0 = emr(bb,0,col); \
 multa(aar0, bbr0, ccr); \
 temp_t bbr1 = emr(bb,1,col); \
 multa(aai0, bbr0, cci); \
 multa(aar1, bbr1, ccr); \
 temp_t bbr2 = emr(bb,2,col); \
 multa(aai1, bbr1, cci); \
 multa(aar2, bbr2, ccr); \
 multa(aai2, bbr2, cci);

#define mult_c_rrfv(cc,col) \
 multa(aar0, bbr0, cc); \
 multa(aar1, bbr1, cc); \
 multa(aar2, bbr2, cc);

#define mult_c_irfv(cc,col) \
 multa(aai0, bbr0, cc); \
 multa(aai1, bbr1, cc); \
 multa(aai2, bbr2, cc);

#define mult_c_rifv(bb,cc,col) \
 mults(aar0, emi(bb,0,col), cc); \
 mults(aar1, emi(bb,1,col), cc); \
 mults(aar2, emi(bb,2,col), cc);

#define mult_c_iifv(bb,cc,col) \
 multa(aai0, emi(bb,0,col), cc); \
 multa(aai1, emi(bb,1,col), cc); \
 multa(aai2, emi(bb,2,col), cc);

#define mult_col(aa,bb,cc,col) \
  mult_c_rrf(aa, bb, evr(cc,col), col) \
  mult_c_irf(aa, bb, evi(cc,col), col) \
  mult_c_rif(aa, bb, evi(cc,col), col) \
  mult_c_iif(aa, bb, evr(cc,col), col)

#define mult_c_rrf(aa,bb,cc,col) \
 multa(evr(aa,0), emr(bb,0,col), cc); \
 multa(evr(aa,1), emr(bb,1,col), cc); \
 multa(evr(aa,2), emr(bb,2,col), cc);

#define mult_c_irf(aa,bb,cc,col) \
 multa(evi(aa,0), emr(bb,0,col), cc); \
 multa(evi(aa,1), emr(bb,1,col), cc); \
 multa(evi(aa,2), emr(bb,2,col), cc);

#define mult_c_rif(aa,bb,cc,col) \
 mults(evr(aa,0), emi(bb,0,col), cc); \
 mults(evr(aa,1), emi(bb,1,col), cc); \
 mults(evr(aa,2), emi(bb,2,col), cc);

#define mult_c_iif(aa,bb,cc,col) \
 multa(evi(aa,0), emi(bb,0,col), cc); \
 multa(evi(aa,1), emi(bb,1,col), cc); \
 multa(evi(aa,2), emi(bb,2,col), cc);
