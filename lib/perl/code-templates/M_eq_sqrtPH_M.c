/**************** QLA_M_eq_sqrtPH_M.c ********************/
// assumes all eigenvalues of input matrix are real and non-negative

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
#  define acosP acosf
#else
#  define QLAP(y) QLA_D ## _ ## y
#  define QLAPX(x,y) QLA_D ## x ## _ ## y
#  define EPS DBL_EPSILON
#  define fabsP fabs
#  define sqrtP sqrt
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

static void
getfs(QLA_Real *f0, QLA_Real *f1, QLA_Real *f2,
      QLA_Real tr, QLA_Real p2, QLA_Real det)
{
  // flops: 38  sqrt: 4  div: 2  sincos: 1  acos: 1
  // e2 = 0.5*(tr^2 - p2)
  // p3 = tr*p2 - tr*e2 + 3*det = 1.5*tr*p2 - 0.5*tr^3 + 3*det
  // s = p2/6 - tr^2/18 = 0.5*(p23-tr3^2)
  // r = p3/6 - tr*p2/6 + tr^3/27 = det/2 + tr*p2/12 -5 tr^3/108
  //   = 0.5*det + 0.25*tr3*(p2-5*tr3^2)
  QLA_Real tr3 = (1./3.)*tr;
  QLA_Real p23 = (1./3.)*p2;
  QLA_Real tr32 = tr3*tr3;
  QLA_Real s = 0.5*(p23-tr32);
  QLA_Real r = 0.5*det + 0.25*tr3*(p2-5*tr32);
  QLA_Real ss = sqrtP(fabsP(s));
  QLA_Real s32 = ss*ss*ss;
  QLA_Real t = acosP(r/s32);
  QLA_Complex sct = QLAP(cexpi)((1./3.)*t);
  QLA_Real ssc = ss*QLA_real(sct);
  QLA_Real sss = 1.73205080756887729352*ss*QLA_imag(sct);  // sqrt(3)
  QLA_Real g0 = tr3 + 2*ssc;
  QLA_Real gg = tr3 - ssc;
  QLA_Real g1 = gg + sss;
  QLA_Real g2 = gg - sss;
  QLA_Real sg0 = sqrtP(fabsP(g0));
  QLA_Real sg1 = sqrtP(fabsP(g1));
  QLA_Real sg2 = sqrtP(fabsP(g2));
  QLA_Real u = sg0 + sg1 + sg2;
  QLA_Real v = sg0*(sg1+sg2) + sg1*sg2;
  QLA_Real w = sg0*sg1*sg2;
  QLA_Real d = u*v-w;
  QLA_Real di = 1./d;
  *f0 = u*w*di;
  *f1 = 0.5*(u*u+tr)*di;
  *f2 = -di;
}

static void
QLA_sqrtPH_3x3(QLA3(ColorMatrix,(*fn)), QLA3(ColorMatrix,(*m)))
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

void
QLAPC(M_eq_sqrtPH_M)(NCARG QLAN(ColorMatrix,(*restrict r)), QLAN(ColorMatrix,(*restrict a)))
{
#ifdef HAVE_XLC
#pragma disjoint(*r, *a)
  __alignx(16,r);
  __alignx(16,a);
#endif

  if(NC==1) {
    // flops: 0  sqrt: 1
    QLA_Real s = sqrtP(fabsP(QLA_real(QLA_elem_M(*a,0,0))));
    QLA_c_eq_r(QLA_elem_M(*r,0,0), s);
    return;
  }
  if(NC==2) {
    // flops: 21  sqrt: 2  div: 1
    QLA_Complex a00, a01, a10, a11;
    QLA_Real tr, det, sdet, c0, c1;
    QLA_c_eq_c(a00, QLA_elem_M(*a,0,0));
    QLA_c_eq_c(a01, QLA_elem_M(*a,0,1));
    QLA_c_eq_c(a10, QLA_elem_M(*a,1,0));
    QLA_c_eq_c(a11, QLA_elem_M(*a,1,1));
    tr = QLA_real(a00) + QLA_real(a11);
    QLA_r_eq_Re_c_times_c (det, a00, a11);
    QLA_r_meq_Re_c_times_c(det, a01, a10);
    sdet = sqrtP(fabsP(det));
    // c0 = (l2*sl1-l1*sl2)/(l2-l1) = sl1*sl2/(sl1+sl2)
    // c1 = (sl2-sl1)/(l2-l1) = 1/(sl1+sl2)
    c1 = 1/sqrtP(fabsP(tr+2*sdet));
    c0 = sdet*c1;
    // c0 + c1*a
    QLA_c_eq_c_times_r_plus_r(QLA_elem_M(*r,0,0), a00, c1, c0);
    QLA_c_eq_c_times_r(QLA_elem_M(*r,0,1), a01, c1);
    QLA_c_eq_c_times_r(QLA_elem_M(*r,1,0), a10, c1);
    QLA_c_eq_c_times_r_plus_r(QLA_elem_M(*r,1,1), a11, c1, c0);
    return;
  }
  if(NC==3) {
    // flops: 350  sqrt: 4  div: 2  sincos: 1  acos: 1
    QLA_sqrtPH_3x3((QLA3(ColorMatrix,(*))) r, (QLA3(ColorMatrix,(*))) a);
    return;
  }

  // flops: 4n2(1+c)  sqrt: 2  div: 1
  // MpeqM: 1+c  MeqdtM: 2+c  MpeqdtM: 1  MtM: c  Minv: 0  MinvM: c
  // flops: 12n2+3 + c(20n3+5.5n2+2.5n)
  double ds = maxev2(NCVAR a);
  //printf("ds = %g\n", ds);
  if(ds == 0) {
    QLAN(M_eq_zero, r);
    return;
  }
  ds = sqrt(ds);

  QLAN(ColorMatrix,x);
  QLAN(ColorMatrix,e);
  //QLAN(ColorMatrix,xi);
  QLAN(ColorMatrix,t1);
  QLAN(ColorMatrix,t2);

  M_eq_d_times_M(&x, 1/ds, a);   // x = b/ds = A
  M_eq_d(&e, 0.5);
  M_peq_d_times_M(&e, -0.5, &x); // e = 0.5 - 0.5 * x
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

  M_eq_d_times_M(r, sqrt(ds), &x);

#if 0
  QLAN(M_eq_M_times_M, &x, r, r);
  QLAN(M_meq_M, &x, a);
  enorm = maxev(NCVAR &x);
  printf("%i %g %g %g\n", nit, enorm, enorm/ds, EPS);
#endif
}
