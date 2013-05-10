/**************** QLA_M_eq_invsqrtPH_M.c ********************/
// assumes all eigenvalues of input matrix are real and positive

#include <stdio.h>
#include <qla_config.h>
#include <qla_types.h>
#include <qla_random.h>
#include <qla_cmath.h>
#include <math.h>
#include <float.h>

#if QLA_Precision == 'F'
#  define QLAP(y) QLA_F ## _ ## y
#  define QLAPX(x,y) QLA_F ## x ## _ ## y
#  define EPS FLT_EPSILON
#  define fabsP fabsf
#  define sqrtP sqrtf
#  define cbrtP cbrtf
#  define acosP acosf
#else
#  define QLAP(y) QLA_D ## _ ## y
#  define QLAPX(x,y) QLA_D ## x ## _ ## y
#  define EPS DBL_EPSILON
#  define fabsP fabs
#  define sqrtP sqrt
#  define cbrtP cbrt
#  define acosP acos
#endif

#if QLA_Colors == 2
# if QLA_Precision == 'F'
#  include <qla_f2.h>
# else
#  include <qla_d2.h>
# endif
# define QLAPC(x) QLAPX(2,x)
#elif QLA_Colors == 3
# if QLA_Precision == 'F'
#  include <qla_f3.h>
# else
#  include <qla_d3.h>
# endif
# define QLAPC(x) QLAPX(3,x)
#else
# if QLA_Precision == 'F'
#  include <qla_fn.h>
# else
#  include <qla_dn.h>
# endif
# define QLAPC(x) QLAPX(N,x)
#endif

#if QLA_Colors == 'N'
#  define QLAN(x,...) QLAPC(x)(nc, __VA_ARGS__)
#  define NCVAR nc,
#  define NCARG int nc,
#  define NC nc
#else
#  define QLAN(x,...) QLAPC(x)(__VA_ARGS__)
#  define NCVAR
#  define NCARG
#  define NC QLA_Colors
#endif
#define QLA3(x,...) QLAPX(3,x)(__VA_ARGS__)

#define M_eq_d(x,d) {QLA_Complex zz; QLA_c_eq_r(zz,d); QLAN(M_eq_c, x, &zz);}
#define M_eq_d_times_M(x,d,a) {QLA_Real rr=(d); QLAN(M_eq_r_times_M, x, &rr, a);}
#define M_peq_d_times_M(x,d,a) {QLA_Real rr=(d); QLAN(M_peq_r_times_M, x, &rr, a);}

static double
maxev2(NCARG QLAN(ColorMatrix,(*a)))
{
  // flops: 4*n*n
  double fnorm = 0;
  for(int i=0; i<NC; i++) {
    for(int j=0; j<NC; j++) {
      fnorm += QLA_norm2_c(QLA_elem_M(*a,i,j));
    }
  }
  return fnorm;
}

#if (QLA_Colors == 3) || (QLA_Colors == 'N')
static void
getfs(QLA_Real *f0, QLA_Real *f1, QLA_Real *f2,
      QLA_Real tr, QLA_Real p2, QLA_Real det)
{
  // flops: 45  sqrt: 4  div: 2  sincos: 1  acos: 1
  // q = (1.5p2-0.5tr^2)/9 = (3p2-tr^2)/18
  // r = (-27det-2tr^3+9tr(tr^2-p2)/2)/54 = -0.5*det +5tr^3/(4*27)-tr*p2/12
  QLA_Real tr3 = (1./3.)*tr;
  QLA_Real p23 = (1./3.)*p2;
  QLA_Real tr32 = tr3*tr3;
  QLA_Real q = 0.5*(p23-tr32);
  QLA_Real r = 0.25*tr3*(5*tr32-p2) - 0.5*det;
  QLA_Real sq = sqrtP(fabsP(q));
  QLA_Real sq3 = sq*sq*sq;
  if(sq3>fabsP(r)) {
    QLA_Real t = acosP(r/sq3);
    QLA_Complex sct = QLAP(cexpi)((1./3.)*t);
    QLA_Real sqc = sq*QLA_real(sct);
    QLA_Real sqs = 1.73205080756887729352*sq*QLA_imag(sct);  // sqrt(3)
    QLA_Real l0 = tr3 - 2*sqc;
    QLA_Real ll = tr3 + sqc;
    QLA_Real l1 = ll + sqs;
    QLA_Real l2 = ll - sqs;
    QLA_Real sl0 = sqrtP(fabsP(l0));
    QLA_Real sl1 = sqrtP(fabsP(l1));
    QLA_Real sl2 = sqrtP(fabsP(l2));
    QLA_Real u = sl0 + sl1 + sl2;
    //QLA_Real v = sl0*(sl1+sl2) + sl1*sl2;
    QLA_Real w = sl0*sl1*sl2;
    //QLA_Real d = u*v-w;
    QLA_Real d = w*(sl0+sl1)*(sl0+sl2)*(sl1+sl2);
    QLA_Real di = 1./d;
    //*f0 = (0.5*(tr*tr-p2)*u+w*(tr+v))*di;
    *f0 = (w*u*u+l0*sl0*(l1+l2)+l1*sl1*(l0+l2)+l2*sl2*(l0+l1))*di;
    *f1 = -(tr*u+w)*di;
    *f2 = u*di;
  } else {
    if(r==0) {  // possibly all zero, but assume all equal to tr3
      *f0 = 1/sqrtP(fabsP(tr3));
      *f1 = 0;
      *f2 = 0;
    } else {
      QLA_Real a = -cbrtP(r);
      QLA_Real l0 = tr3 + 2*a;
      QLA_Real l1 = tr3 - a;
      QLA_Real sl0 = sqrtP(fabsP(l0));
      QLA_Real sl1 = sqrtP(fabsP(l1));
      QLA_Real sl01 = sl0 + sl1;
      QLA_Real p01 = sl0 * sl1;
      QLA_Real t = p01*sl01;
      // let it divide by zero, if the input matrix is singular
      QLA_Real ti = 1/t;
      *f2 = 0;
      *f1 = -ti;
      *f0 = (p01+l0+l1)*ti;
    }
  }
}

static void
QLA_invsqrtPH_3x3(QLA3(ColorMatrix,(*fn)), QLA3(ColorMatrix,(*m)))
{
  // flops: 312
  QLA_Complex m00, m01, m02, m10, m11, m12, m20, m21, m22;
  QLA_Complex mm00, mm01, mm02, mm10, mm11, mm12, mm20, mm21, mm22;
  QLA_Real f0, f1, f2;

  QLA_c_eq_c(m00, QLA_elem_M(*m,0,0));
  QLA_c_eq_c(m01, QLA_elem_M(*m,0,1));
  QLA_c_eq_c(m02, QLA_elem_M(*m,0,2));
  QLA_c_eq_c(m10, QLA_elem_M(*m,1,0));
  QLA_c_eq_c(m11, QLA_elem_M(*m,1,1));
  QLA_c_eq_c(m12, QLA_elem_M(*m,1,2));
  QLA_c_eq_c(m20, QLA_elem_M(*m,2,0));
  QLA_c_eq_c(m21, QLA_elem_M(*m,2,1));
  QLA_c_eq_c(m22, QLA_elem_M(*m,2,2));

  QLA_Real tr = QLA_real(m00) + QLA_real(m11) + QLA_real(m22);

#define mul(i,j) \
  QLA_c_eq_c_times_c(mm##i##j, m##i##0, m##0##j); \
  QLA_c_peq_c_times_c(mm##i##j, m##i##1, m##1##j); \
  QLA_c_peq_c_times_c(mm##i##j, m##i##2, m##2##j);
  mul(0,0);
  mul(0,1);
  mul(0,2);
  mul(1,0);
  mul(1,1);
  mul(1,2);
  mul(2,0);
  mul(2,1);
  mul(2,2);
#undef mul

  QLA_Real p2 = QLA_real(mm00) + QLA_real(mm11) + QLA_real(mm22);

  QLA_Complex det0, det1, det2;
  QLA_Real det;
  QLA_c_eq_c_times_c (det2, m00, m11);
  QLA_c_meq_c_times_c(det2, m01, m10);
  QLA_c_eq_c_times_c (det1, m02, m10);
  QLA_c_meq_c_times_c(det1, m00, m12);
  QLA_c_eq_c_times_c (det0, m01, m12);
  QLA_c_meq_c_times_c(det0, m02, m11);
  QLA_r_eq_Re_c_times_c (det, det2, m22);
  QLA_r_peq_Re_c_times_c(det, det1, m21);
  QLA_r_peq_Re_c_times_c(det, det0, m20);

  getfs(&f0, &f1, &f2, tr, p2, det);

#define mul(i,j) \
  QLA_c_eq_r_times_c(QLA_elem_M(*fn,i,j), f2, mm##i##j); \
  QLA_c_peq_r_times_c(QLA_elem_M(*fn,i,j), f1, m##i##j);
  mul(0,0);
  mul(0,1);
  mul(0,2);
  mul(1,0);
  mul(1,1);
  mul(1,2);
  mul(2,0);
  mul(2,1);
  mul(2,2);
#undef mul
  QLA_c_peq_r(QLA_elem_M(*fn,0,0), f0);
  QLA_c_peq_r(QLA_elem_M(*fn,1,1), f0);
  QLA_c_peq_r(QLA_elem_M(*fn,2,2), f0);
}
#endif

void
QLAPC(M_eq_invsqrtPH_M)(NCARG QLAN(ColorMatrix,(*restrict r)), QLAN(ColorMatrix,(*restrict a)))
{
#ifdef HAVE_XLC
#pragma disjoint(*r, *a)
  __alignx(16,r);
  __alignx(16,a);
#endif

  if(NC==1) {
    // flops: 0  sqrt: 1  div: 1
    QLA_Real s = 1/sqrtP(fabsP(QLA_real(QLA_elem_M(*a,0,0))));
    QLA_c_eq_r(QLA_elem_M(*r,0,0), s);
    return;
  }
  if(NC==2) {
    // flops: 23  sqrt: 2  div: 1
    QLA_Complex a00, a01, a10, a11;
    QLA_Real tr, sdet, det, c0, c1;
    QLA_c_eq_c(a00, QLA_elem_M(*a,0,0));
    QLA_c_eq_c(a01, QLA_elem_M(*a,0,1));
    QLA_c_eq_c(a10, QLA_elem_M(*a,1,0));
    QLA_c_eq_c(a11, QLA_elem_M(*a,1,1));
    QLA_r_eq_Re_c_times_c (det, a00, a11);
    QLA_r_meq_Re_c_times_c(det, a01, a10);
    tr = QLA_real(a00) + QLA_real(a11);
    sdet = sqrtP(fabsP(det));
    // c0 = (l2/sl1-l1/sl2)/(l2-l1) = (l2+sl1*sl2+l1)/(sl1*sl2*(sl1+sl2))
    // c1 = (1/sl2-1/sl1)/(l2-l1) = -1/(sl1*sl2*(sl1+sl2))
    c1 = 1/(sdet*sqrtP(fabsP(tr+2*sdet)));
    c0 = (tr+sdet)*c1;
    c1 = -c1;
    // c0 + c1*a
    QLA_c_eq_c_times_r_plus_r(QLA_elem_M(*r,0,0), a00, c1, c0);
    QLA_c_eq_c_times_r(QLA_elem_M(*r,0,1), a01, c1);
    QLA_c_eq_c_times_r(QLA_elem_M(*r,1,0), a10, c1);
    QLA_c_eq_c_times_r_plus_r(QLA_elem_M(*r,1,1), a11, c1, c0);
    return;
  }
#if (QLA_Colors == 3) || (QLA_Colors == 'N')
  if(NC==3) {
    // flops: 357  sqrt: 4  div: 2  sincos: 1  acos: 1
    QLA_invsqrtPH_3x3((QLA3(ColorMatrix,(*))) r, (QLA3(ColorMatrix,(*))) a);
    return;
  }
#endif

  // flops: 1+4*n*n*(1+c)  sqrt: 2  div: 1
  // MpeqM: 1+c  MeqdtM: 1+c  MpeqdtM: 1  MtM: c  Minv: 1  MinvM: c
  // flops: 12n3+9.5n2+2.5n+4 + c(20n3+5.5n2+2.5n)
  double ds = maxev2(NCVAR a);
  //printf("ds = %g\n", ds);
  if(ds == 0) {
    M_eq_d(r, 1./0.);
    return;
  }
  ds = sqrt(ds);

  QLAN(ColorMatrix,x);
  QLAN(ColorMatrix,e);
  QLAN(ColorMatrix,xi);
  QLAN(ColorMatrix,t1);
  QLAN(ColorMatrix,t2);

  // x = 1
  M_eq_d(&x, 1);
  // e = 0.5*ds/b - 0.5
  QLAN(M_eq_inverse_M, &xi, a);
  M_eq_d(&e, -0.5);
  M_peq_d_times_M(&e, 0.5*ds, &xi);
  QLAN(M_peq_M, &x, &e);

  double enorm, estop = EPS;
  int maxit = 20;
  int nit = 0;
  do {  // e = -0.5 e x^-1 e; x += e
    nit++;
    //QLAN(M_eq_inverse_M, &xi, &x);
    //QLAN(M_eq_M_times_M, &t1, &xi, &e);
    QLAN(M_eq_M_inverse_M, &t1, &x, &e);
    QLAN(M_eq_M_times_M, &t2, &e, &t1);
    M_eq_d_times_M(&e, -0.5, &t2);
    QLAN(M_peq_M, &x, &e);
    enorm = maxev2(NCVAR &e);
    //printf("%i enorm = %g\n", nit, enorm);
  } while(nit<maxit && enorm>estop);

  M_eq_d_times_M(r, 1/sqrt(ds), &x);

#if 0
  QLAN(M_eq_M_times_M, &x, r, r);
  QLAN(M_meq_M, &x, a);
  enorm = maxev(NCVAR &x);
  printf("%i %g %g %g\n", nit, enorm, enorm/ds, EPS);
#endif
}
