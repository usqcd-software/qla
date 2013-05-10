#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <math.h>
#include <qla.h>
#ifdef _OPENMP
# include <omp.h>
# define __USE_GNU
# include <sched.h>
#endif

#if QLA_Precision == 'F'
#define REALBYTES 4
#else
#define REALBYTES 8
#endif
#define NC QLA_Nc

// flops rdivc: 6 cdivc: 12 csqrt: 11 cpow: 11 cexp: 5 ccosh: 6
// det: 1 0, 2 14, 3 64, n(n*n-1)4/3+3n+3n(n-1)/2+6n+n(n-1)(n-2)4/3+6n(n-1)
// T(n) = n[T(n-1)+8]-2 , n[ 8.5 +10.5n +8n*n ]/3
#define FLOP_DET(n) (n==1?0:(n==2?14:(n==3?64:(n*(8.5+10.5*n+8*n*n)/3))))
// eig: 1 0, 2 56, 3 233, 16n*n*n
#define FLOP_EIG(n) (n==1?0:(n==2?56:(n==3?233:(16*n*n*n))))
// eigh: 1 0, 2 14, 3 233, 16n*n*n
#define FLOP_EIGH(n) (n==1?0:(n==2?14:(n==3?233:(16*n*n*n))))
// inv: 1 6, 2 48, 3 208, n(3(n+1)/2+3+6(n-1)+4(n-1)(n-1)+8n(n-1)+6n)
#define FLOP_INV(n) (n==1?6:(n==2?48:(n==3?208:(n*(12*n*n-2.5*(n-1))))))
// invV: 1 12, 2 60, 3 238, n(3(n+1)/2+3+6(n-1)+4(n-1)(n-1)+8(n-1)+6)
#define FLOP_INVV(n) (n==1?12:(n==2?60:(n==3?238:(n*(4*n*n+7.5*n+0.5)))))
// invM: 1 12, 2 100, 3 309(N=3), n(3(n+1)/2+3+6(n-1)+4(n-1)(n-1)+8n(n-1)+6n)
#define FLOP_INVM(n) (n==1?12:(n==2?100:(n==3?309:(n*(12*n*n-2.5*(n-1))))))
// exp: 1 5, 2 102, 3 699, (44+8(s+b))n3 + 29.5n2 + 2.5n + 3
#define FLOP_EXP(n) (n==1?5:(n==2?102:(n==3?699:(((44*NC+29.5)*NC+2.5)*NC+3))))
// expa: 1 2, 2 53, 3 561, (44+8(s+b))n3 + 29.5n2 + 2.5n + 3
#define FLOP_EXPA(n) (n==1?2:(n==2?53:(n==3?561:(((44*NC+29.5)*NC+2.5)*NC+3))))
// expta: 1 0, 2 21, 3 535, (44+8(s+b))n3 + 29.5n2 + 2.5n + 3
#define FLOP_EXPTA(n) (n==1?0:(n==2?21:(n==3?535:(((44*NC+29.5)*NC+2.5)*NC+3))))
// sqrt: 1 11, 2 124, 3 708(N=3,c=1), (20c)n3+(5.5c+12)n2+(2.5c)n+3
#define FLOP_SQRT(n) (n==1?11:(n==2?124:(n==3?708:(((40*NC+23)*NC+5)*NC+3))))
// sqrtph: 1 1, 2 24, 3 359, (20c)n3+(5.5c+12)n2+(2.5c)n+3
#define FLOP_SQRTPH(n) (n==1?1:(n==2?24:(n==3?359:(((40*NC+23)*NC+5)*NC+3))))
// rsqrt: 1 17, 2 134, 3 1018(N=3,c=1), (20c+12)*n3+(5.5c+9.5)n2+(2.5c+2.5)n+4
#define FLOP_RSQRT(n) (n==1?17:(n==2?134:(n==3?1018:(((52*NC+20.5)*NC+7.5)*NC+4))))
// rsqrtph: 1 2, 2 26, 3 365, (20c+12)*n3+(5.5c+9.5)n2+(2.5c+2.5)n+4
#define FLOP_RSQRTPH(n) (n==1?2:(n==2?26:(n==3?365:((((52*NC+20.5)*NC+7.5)*NC+4)))))
// log: 1 ?, 2 ?, 3 ??, ??
//#define FLOP_LOG(n) (n==1?5:(n==2?102:(n==3?3090:(60*NC*NC*NC))))
#define FLOP_LOG(n) (FLOP_SQRT(n)+FLOP_EXP(n))


#define myalloc(type, n) (type *) aligned_malloc(n*sizeof(type))

#define ALIGN 64
void *
aligned_malloc(size_t n)
{
  size_t m = (size_t) malloc(n+ALIGN);
  size_t r = m % ALIGN;
  if(r) m += (ALIGN - r);
  return (void *)m;
}

double
dtime(void)
{
#ifdef _OPENMP
  return omp_get_wtime();
#else
  struct timeval tv;
  gettimeofday(&tv, NULL);
  return tv.tv_sec + 1e-6*tv.tv_usec;
#endif
}

void
set_R(QLA_Real *r, int i)
{
  *r = 1+cos(i);
}

void
set_C(QLA_Complex *c, int i)
{
  QLA_c_eq_r_plus_ir(*c, 1+cos(i), 1+sin(i));
}

void
set_V(QLA_ColorVector *v, int i)
{
  for(int j=0; j<QLA_Nc; j++) {
    QLA_c_eq_r_plus_ir(QLA_elem_V(*v,j), j+1+cos(i), j+1+sin(i));
    //QLA_real(QLA_elem_V(*v,j)) = 1;
    //QLA_imag(QLA_elem_V(*v,j)) = 0;
  }
}

void
set_H(QLA_HalfFermion *h, int i)
{
  for(int j=0; j<QLA_Nc; j++) {
    for(int k=0; k<(QLA_Ns/2); k++) {
      QLA_c_eq_r_plus_ir(QLA_elem_H(*h,j,k), (j+4)*(k+1)+cos(i), (j+4)*(k+1)+sin(i));
    }
  }
}

void
set_D(QLA_DiracFermion *d, int i)
{
  for(int j=0; j<QLA_Nc; j++) {
    for(int k=0; k<QLA_Ns; k++) {
      QLA_c_eq_r_plus_ir(QLA_elem_D(*d,j,k), (j+4)*(k+1)+cos(i), (j+4)*(k+1)+sin(i));
    }
  }
}

#define MtypeH  1
#define MtypeP  2
#define MtypeA  4
#define MtypeT  8
#define MtypeNZ 16
#define MtypeNN 32
static int Mtype = 0;
#define setM Mtype = 0
#define setMH Mtype = MtypeH
#define setMPH Mtype = MtypeP|MtypeH|MtypeNN|MtypeNZ
#define setMA Mtype = MtypeA
#define setMTA Mtype = MtypeT|MtypeA
#define setMP Mtype = MtypeP|MtypeNN|MtypeNZ
#define setMNZ Mtype = MtypeNZ
#define setMNNH Mtype = MtypeNN|MtypeH

void
set_M(QLA_ColorMatrix *m, int i)
{
#if 0
  static QLA_ColorMatrix t;
  for(int j=0; j<QLA_Nc; j++) {
    for(int k=0; k<QLA_Nc; k++) {
      QLA_c_eq_r_plus_ir(QLA_elem_M(*m,j,k),
			 (((j-k+QLA_Nc+1)*(j+k+1))%19)+cos(i),
			 (((j+4)*(k+1))%17)+sin(i));
      //QLA_real(QLA_elem_M(*m,j,k)) = 1;
      //QLA_imag(QLA_elem_M(*m,j,k)) = 0;
    }
  }
#endif
  for(int j=0; j<QLA_Nc; j++) {
    for(int k=0; k<QLA_Nc; k++) {
      QLA_c_eq_r(QLA_elem_M(*m,j,k), 0);
    }
  }
  QLA_Real step = 1e-5;
  if(Mtype&MtypeNZ) {
    for(int j=0; j<QLA_Nc; j++) {
      QLA_c_peq_r_plus_ir(QLA_elem_M(*m,j,j), step, -step);
    }
  }
  int ii=i;
  if((Mtype&MtypeNN)==0) ii>>=QLA_Nc;
  for(int j=0,k=1; ii; ii>>=1,j++) {
    if(j>=QLA_Nc) { j=0; k*=2; }
    if(ii&1) QLA_c_peq_r_plus_ir(QLA_elem_M(*m,j,j), k*step, -k*step);
  }
  ii = i;
  if((Mtype&MtypeNN)==0) {
    for(int j=0; j<QLA_Nc; j++) {
      if(ii&1) QLA_c_eqm_c(QLA_elem_M(*m,j,j), QLA_elem_M(*m,j,j));
      ii >>= 1;
    }
  }
  if(Mtype&MtypeH) { // make Hermitian
    QLA_ColorMatrix m2;
    QLA_M_eq_M(&m2, m);
    QLA_M_peq_Ma(&m2, m);
    QLA_M_eq_M(m, &m2);
  }
  if((Mtype&MtypeP)&&(Mtype&MtypeH)) { // make positive Hermitian
    QLA_ColorMatrix m2;
    QLA_M_eq_M_times_Ma(&m2, m, m);
    QLA_M_eq_M(m, &m2);
  }
  if(Mtype&MtypeA) { // make anti-Hermitian
    QLA_ColorMatrix m2;
    QLA_M_eq_M(&m2, m);
    QLA_M_meq_Ma(&m2, m);
    QLA_M_eq_M(m, &m2);
  }
  if((Mtype&MtypeT)&&(Mtype&MtypeA)) { // make traceless anti-Hermitian
    QLA_ColorMatrix m2;
    QLA_M_eq_antiherm_M(&m2, m);
    QLA_M_eq_M(m, &m2);
  }
  //QLA_Real n2;
  //QLA_r_eq_norm2_M(&n2, m);
  //printf("%i\t%g\n", i, n2);
}

QLA_Real
sum_C(QLA_Complex *d, int n)
{
  QLA_Real t=0, *r=(QLA_Real *)d;
  int nn = n*sizeof(QLA_Complex)/sizeof(QLA_Real);
  for(int i=0; i<nn; i++) {
    t += r[i];
    //printf("%i\t%g\n", i, r[i]);
  }
  return t/nn;
}

QLA_Real
sum_V(QLA_ColorVector *d, int n)
{
  QLA_Real t=0, *r=(QLA_Real *)d;
  int nn = n*sizeof(QLA_ColorVector)/sizeof(QLA_Real);
  for(int i=0; i<nn; i++) t += r[i];
  return t/nn;
}

QLA_Real
sum_H(QLA_HalfFermion *d, int n)
{
  QLA_Real t=0, *r=(QLA_Real *)d;
  int nn = n*sizeof(QLA_HalfFermion)/sizeof(QLA_Real);
  for(int i=0; i<nn; i++) t += r[i];
  return t/nn;
}

QLA_Real
sum_D(QLA_DiracFermion *d, int n)
{
  QLA_Real t=0, *r=(QLA_Real *)d;
  int nn = n*sizeof(QLA_DiracFermion)/sizeof(QLA_Real);
  for(int i=0; i<nn; i++) t += r[i];
  return t/nn;
}

QLA_Real
sum_M(QLA_ColorMatrix *d, int n)
{
  QLA_Real t=0, *r=(QLA_Real *)d;
  int nn = n*sizeof(QLA_ColorMatrix)/sizeof(QLA_Real);
  for(int i=0; i<nn; i++) t += r[i];
  return t/nn;
}

#define set_fields { \
  _Pragma("omp parallel for") \
  for(int i=0; i<n; ++i) { \
    set_R(&r1[i], i); \
    set_C(&c1[i], i); \
    set_V(&v1[i], i); \
    set_V(&v2[i], i); \
    set_V(&v3[i], i); \
    set_V(&v4[i], i); \
    set_V(&v5[i], i); \
    set_H(&h1[i], i); \
    set_H(&h2[i], i); \
    set_D(&d1[i], i); \
    set_D(&d2[i], i); \
    set_M(&m1[i], i); \
    set_M(&m2[i], i); \
    set_M(&m3[i], i); \
    set_M(&m4[i], i); \
    int j = ((i|16)+256) % n; \
    vp1[i] = &v2[j]; \
    vp2[i] = &v3[j]; \
    vp3[i] = &v4[j]; \
    vp4[i] = &v5[j]; \
    hp1[i] = &h2[j]; \
    dp1[i] = &d2[j]; \
    mp1[i] = &m3[j]; \
  } \
}

int
main(int argc, char *argv[])
{
  QLA_Real sum, *r1;
  QLA_Complex *c1;
  QLA_ColorVector *v1, *v2, *v3, *v4, *v5;
  QLA_ColorVector **vp1, **vp2, **vp3, **vp4;
  QLA_HalfFermion *h1, *h2, **hp1;
  QLA_DiracFermion *d1, *d2, **dp1;
  QLA_ColorMatrix *m1, *m2, *m3, *m4, **mp1;
  double cf0, flop, mem, time1;
  int nmin, nmax, c, nthreads=1;

  nmin = 64;
  if(argc>1) nmin = atoi(argv[1]);
  nmax = 256*1024;
  if(argc>2) nmax = atoi(argv[2]);
  cf0 = 1e9;
  if(argc>3) cf0 *= atof(argv[3]);

  printf("QLA version %s (%i)\n", QLA_version_str(), QLA_version_int());
  printf("QLA_Precision = %c\n", QLA_Precision);
  printf("QLA_Nc = %i\n", QLA_Nc);

#ifdef _OPENMP
  nthreads = omp_get_max_threads();
  printf("OMP threads = %i\n", nthreads);
  printf("omp_get_wtick = %g\n", omp_get_wtick());
#ifdef CPU_ZERO
#pragma omp parallel
  {
    int tid = omp_get_thread_num();
    cpu_set_t set;
    CPU_ZERO(&set);
    CPU_SET(tid, &set);
    sched_setaffinity(0, sizeof(set), &set);
  }
#endif
#endif

  nmin *= nthreads;
  nmax *= nthreads;

  r1 = myalloc(QLA_Real, nmax);
  c1 = myalloc(QLA_Complex, nmax);
  v1 = myalloc(QLA_ColorVector, nmax);
  v2 = myalloc(QLA_ColorVector, nmax);
  v3 = myalloc(QLA_ColorVector, nmax);
  v4 = myalloc(QLA_ColorVector, nmax);
  v5 = myalloc(QLA_ColorVector, nmax);
  vp1 = myalloc(QLA_ColorVector *, nmax);
  vp2 = myalloc(QLA_ColorVector *, nmax);
  vp3 = myalloc(QLA_ColorVector *, nmax);
  vp4 = myalloc(QLA_ColorVector *, nmax);
  h1 = myalloc(QLA_HalfFermion, nmax);
  h2 = myalloc(QLA_HalfFermion, nmax);
  hp1 = myalloc(QLA_HalfFermion *, nmax);
  d1 = myalloc(QLA_DiracFermion, nmax);
  d2 = myalloc(QLA_DiracFermion, nmax);
  dp1 = myalloc(QLA_DiracFermion *, nmax);
  m1 = myalloc(QLA_ColorMatrix, nmax);
  m2 = myalloc(QLA_ColorMatrix, nmax);
  m3 = myalloc(QLA_ColorMatrix, nmax);
  m4 = myalloc(QLA_ColorMatrix, nmax);
  mp1 = myalloc(QLA_ColorMatrix *, nmax);
  //QLA_ColorVector *va[4] = { v2, v3, v4, v5 };
  QLA_ColorVector **vpa[4] = { vp1, vp2, vp3, vp4 };
  QLA_ColorMatrix *ma[4] = { m1, m2, m3, m4 };

  for(int n=nmin; n<=nmax; n*=2) {
    printf("len = %i\n", n);
    printf("len/thread = %i\n", n/nthreads);
    double cf = cf0*nthreads/n;

#include "benchfuncs.c"

  }

  return 0;
}
