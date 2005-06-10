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
  QLA_ColorMatrix *m;
  QLA_ColorVector *v1, *v2, **v3;
  double time1;
  float cf, flop;
  int i, j, n, c;

  n = 10000;
  if(argc>1) n = atoi(argv[1]);
  cf = 3.e9/n;
  if(argc>2) cf = atof(argv[2]);

  m = (QLA_ColorMatrix *)malloc(n*sizeof(QLA_ColorMatrix));
  v1 = (QLA_ColorVector *)malloc(n*sizeof(QLA_ColorVector));
  v2 = (QLA_ColorVector *)malloc(n*sizeof(QLA_ColorVector));
  v3 = (QLA_ColorVector **)malloc(n*sizeof(QLA_ColorVector*));

  for(i=0; i<n; ++i) {
    set_M(&m[i], i+1);
    set_V(&v1[i], 0);
    set_V(&v2[i], i+1);
    j = ((i|16)+256) % n;
    v3[i] = &v2[j];
  }

  flop = 72;
  c = cf/flop;
  time1 = -clock();
  for(i=0; i<c; ++i) {
    QLA_V_vpeq_M_times_pV(v1, m, v3, n);
  }
  time1 += clock();
  time1 /= CLOCKS_PER_SEC;
  printf("%-25s: ", "QLA_V_vpeq_M_times_pV");
  printf("len=%6i time=%6.2f mflops=%8.2f\n", n, time1, flop*n*c/(1e6*time1));

  flop = 6;
  c = cf/flop;
  time1 = -clock();
  for(i=0; i<c; ++i) {
    QLA_V_vmeq_pV(v1, v3, n);
  }
  time1 += clock();
  time1 /= CLOCKS_PER_SEC;
  printf("%-25s: ", "QLA_V_vmeq_pV");
  printf("len=%6i time=%6.2f mflops=%8.2f\n", n, time1, flop*n*c/(1e6*time1));

  return 0;
}

