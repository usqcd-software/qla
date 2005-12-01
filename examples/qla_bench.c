#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <qla.h>

void
set_V(QLA_ColorVector *v, int i)
{
  int j;
  for(j=0; j<QLA_Nc; j++) {
    QLA_real(QLA_elem_V(*v,j)) = j+1+cos(i);
    QLA_imag(QLA_elem_V(*v,j)) = j+1+sin(i);
    //QLA_real(QLA_elem_V(*v,j)) = 1;
    //QLA_imag(QLA_elem_V(*v,j)) = 0;
  }
}

void
set_H(QLA_HalfFermion *h, int i)
{
  int j, k;
  for(j=0; j<QLA_Nc; j++) {
    for(k=0; k<(QLA_Ns/2); k++) {
      QLA_real(QLA_elem_H(*h,j,k)) = (j+4)*(k+1)+cos(i);
      QLA_imag(QLA_elem_H(*h,j,k)) = (j+4)*(k+1)+sin(i);
    }
  }
}

void
set_D(QLA_DiracFermion *d, int i)
{
  int j, k;
  for(j=0; j<QLA_Nc; j++) {
    for(k=0; k<QLA_Ns; k++) {
      QLA_real(QLA_elem_D(*d,j,k)) = (j+4)*(k+1)+cos(i);
      QLA_imag(QLA_elem_D(*d,j,k)) = (j+4)*(k+1)+sin(i);
    }
  }
}

void
set_M(QLA_ColorMatrix *m, int i)
{
  int j, k;
  for(j=0; j<QLA_Nc; j++) {
    for(k=0; k<QLA_Nc; k++) {
      QLA_real(QLA_elem_M(*m,j,k)) = (j+4)*(k+1)+cos(i);
      QLA_imag(QLA_elem_M(*m,j,k)) = (j+4)*(k+1)+sin(i);
      //QLA_real(QLA_elem_M(*m,j,k)) = 1;
      //QLA_imag(QLA_elem_M(*m,j,k)) = 0;
    }
  }
}

int
main(int argc, char *argv[])
{
  QLA_ColorMatrix *m1;
  QLA_ColorVector *v1, *v2, **vp1;
  QLA_HalfFermion *h1, *h2, **hp1;
  QLA_DiracFermion *d1, *d2, **dp1;
  double time1;
  float cf, flop;
  int i, j, n, c;

  n = 10000;
  if(argc>1) n = atoi(argv[1]);
  cf = 3.e9/n;
  if(argc>2) cf = atof(argv[2]);

  m1 = (QLA_ColorMatrix *)malloc(n*sizeof(QLA_ColorMatrix));
  v1 = (QLA_ColorVector *)malloc(n*sizeof(QLA_ColorVector));
  v2 = (QLA_ColorVector *)malloc(n*sizeof(QLA_ColorVector));
  vp1 = (QLA_ColorVector **)malloc(n*sizeof(QLA_ColorVector*));
  h1 = (QLA_HalfFermion *)malloc(n*sizeof(QLA_HalfFermion));
  h2 = (QLA_HalfFermion *)malloc(n*sizeof(QLA_HalfFermion));
  hp1 = (QLA_HalfFermion **)malloc(n*sizeof(QLA_HalfFermion*));
  d1 = (QLA_DiracFermion *)malloc(n*sizeof(QLA_DiracFermion));
  d2 = (QLA_DiracFermion *)malloc(n*sizeof(QLA_DiracFermion));
  dp1 = (QLA_DiracFermion **)malloc(n*sizeof(QLA_DiracFermion*));

  for(i=0; i<n; ++i) {
    set_M(&m1[i], i);
    set_V(&v1[i], i);
    set_V(&v2[i], i);
    set_H(&h1[i], i);
    set_H(&h2[i], i);
    set_D(&d1[i], i);
    set_D(&d2[i], i);
    j = ((i|16)+256) % n;
    vp1[i] = &v2[j];
    hp1[i] = &h2[j];
    dp1[i] = &d2[j];
  }

  flop = 72;
  c = cf/flop;
  time1 = -clock();
  for(i=0; i<c; ++i) {
    QLA_V_vpeq_M_times_pV(v1, m1, vp1, n);
  }
  time1 += clock();
  time1 /= CLOCKS_PER_SEC;
  printf("%-32s: ", "QLA_V_vpeq_M_times_pV");
  printf("len=%6i time=%6.2f mflops=%8.2f\n", n, time1, flop*n*c/(1e6*time1));

  flop = 6;
  c = cf/flop;
  time1 = -clock();
  for(i=0; i<c; ++i) {
    QLA_V_vmeq_pV(v1, vp1, n);
  }
  time1 += clock();
  time1 /= CLOCKS_PER_SEC;
  printf("%-32s: ", "QLA_V_vmeq_pV");
  printf("len=%6i time=%6.2f mflops=%8.2f\n", n, time1, flop*n*c/(1e6*time1));

  flop = 24;
  c = cf/flop;
  time1 = -clock();
  for(i=0; i<c; ++i) {
    QLA_H_veq_spproj_D(h1, d1, 0, 1, n);
  }
  time1 += clock();
  time1 /= CLOCKS_PER_SEC;
  printf("%-32s: ", "QLA_H_veq_spproj_D");
  printf("len=%6i time=%6.2f mflops=%8.2f\n", n, time1, flop*n*c/(1e6*time1));

  flop = 156;
  c = cf/flop;
  time1 = -clock();
  for(i=0; i<c; ++i) {
    QLA_D_vpeq_sprecon_M_times_pH(d1, m1, hp1, 0, 1, n);
  }
  time1 += clock();
  time1 /= CLOCKS_PER_SEC;
  printf("%-32s: ", "QLA_D_vpeq_sprecon_M_times_pH");
  printf("len=%6i time=%6.2f mflops=%8.2f\n", n, time1, flop*n*c/(1e6*time1));

  flop = 180;
  c = cf/flop;
  time1 = -clock();
  for(i=0; i<c; ++i) {
    QLA_D_vpeq_spproj_M_times_pD(d1, m1, dp1, 0, 1, n);
  }
  time1 += clock();
  time1 /= CLOCKS_PER_SEC;
  printf("%-32s: ", "QLA_D_vpeq_spproj_M_times_pD");
  printf("len=%6i time=%6.2f mflops=%8.2f\n", n, time1, flop*n*c/(1e6*time1));

  flop = 12;
  c = cf/flop;
  time1 = -clock();
  for(i=0; i<c; ++i) {
    QLA_D_vpeq_spproj_D(d1, d2, 4, 1, n);
  }
  time1 += clock();
  time1 /= CLOCKS_PER_SEC;
  printf("%-32s: ", "QLA_D_vpeq_spproj_D");
  printf("len=%6i time=%6.2f mflops=%8.2f\n", n, time1, flop*n*c/(1e6*time1));

  return 0;
}

