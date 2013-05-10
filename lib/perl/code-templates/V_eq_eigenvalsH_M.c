/**************** QLA_V_eq_eigenvalsH_M.c ********************/

#include <stdio.h>
#include <qla_config.h>
#include <qla_types.h>
#include <qla_random.h>
#include <qla_cmath.h>
#include <math.h>

#if QLA_Precision == 'F'
#  define QLAP(y) QLA_F ## _ ## y
#  define QLAPX(x,y) QLA_F ## x ## _ ## y
#  define EPS FLT_EPSILON
#  define fabsP fabsf
#  define sqrtP sqrtf
#  define cbrtP cbrtf
#  define acosP acosf
#  define copysignP copysignf
#else
#  define QLAP(y) QLA_D ## _ ## y
#  define QLAPX(x,y) QLA_D ## x ## _ ## y
#  define EPS DBL_EPSILON
#  define fabsP fabs
#  define sqrtP sqrt
#  define cbrtP cbrt
#  define acosP acos
#  define copysignP copysign
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

/*
static void
printdet(int nc, QLAN(ColorMatrix,(*m)), QLA_Complex *t)
{
  QLA_Complex d, tr;
  if(t) for(int i=0; i<nc; i++) QLA_c_peq_c(QLA_elem_M(*m,i,i), *t);
  QLAN(C_eq_det_M, &d, m);
  QLA_c_eq_r(tr, 0);
  for(int i=0; i<nc; i++) QLA_c_peq_c(tr, QLA_elem_M(*m,i,i));
  if(t) for(int i=0; i<nc; i++) QLA_c_meq_c(QLA_elem_M(*m,i,i), *t);
  printf("det:\t%g\t%g\t%g\t%g\n", QLA_real(d), QLA_imag(d), QLA_real(tr), QLA_imag(tr));
}
*/

static void
QLA_eigenvals_2x2(QLA_Complex *v0, QLA_Complex *v1, QLA_Complex *m00,
		  QLA_Complex *m01, QLA_Complex *m10, QLA_Complex *m11)
{
  // flops: 12  sqrt: 1  div: 1
  QLA_Real tr, det;
  QLA_r_eq_Re_c_times_c (det, *m00, *m11);
  QLA_r_meq_Re_c_times_c(det, *m01, *m10);
  tr = QLA_real(*m00) + QLA_real(*m11);
  if(det==0) {
    QLA_c_eq_r(*v0, 0);
    QLA_c_eq_r(*v1, tr);
  } else {
    QLA_Real s = 0.5*tr;
    // lambda = 0.5*(tr \pm sqrt(tr^2 - 4*det) ) = s \pm sqrt(s^2 - det)
    QLA_Real d = s*s - det;
    QLA_Real sd = sqrtP(fabsP(d));
    QLA_Real l0, l1 = s + copysignP(sd, s);
    l0 = det / l1;
    QLA_c_eq_r(*v0, l0);
    QLA_c_eq_r(*v1, l1);
  }
}

static void
QLA_eigenvals_3x3(QLA_Complex *v0, QLA_Complex *v1, QLA_Complex *v2,
		  QLA_Complex *m00, QLA_Complex *m01, QLA_Complex *m02,
		  QLA_Complex *m10, QLA_Complex *m11, QLA_Complex *m12,
		  QLA_Complex *m20, QLA_Complex *m21, QLA_Complex *m22)
{
  QLA_Complex a00, a11, a22, det0, det1, det2;
  QLA_Real s1, s2, det;
  QLA_c_eq_c(a00, *m00);
  QLA_c_eq_c(a11, *m11);
  QLA_c_eq_c(a22, *m22);
  s1 = (1./3.)*(QLA_real(a00) + QLA_real(a11) + QLA_real(a22));
  QLA_c_meq_r(a00, s1);
  QLA_c_meq_r(a11, s1);
  QLA_c_meq_r(a22, s1);
  QLA_c_eq_c_times_c (det2, a00, a11);
  QLA_c_meq_c_times_c(det2, *m01, *m10);
  QLA_c_eq_c_times_c (det1, *m02, *m10);
  QLA_c_meq_c_times_c(det1, a00, *m12);
  QLA_c_eq_c_times_c (det0, *m01, *m12);
  QLA_c_meq_c_times_c(det0, *m02, a11);
  QLA_r_eq_Re_c_times_c (det, det2, a22);
  QLA_r_peq_Re_c_times_c(det, det1, *m21);
  QLA_r_peq_Re_c_times_c(det, det0, *m20);
  QLA_r_eq_Re_c(s2, det2);
  QLA_r_peq_Re_c_times_c(s2, a00, a22);
  QLA_r_meq_Re_c_times_c(s2, *m02, *m20);
  QLA_r_peq_Re_c_times_c(s2, a11, a22);
  QLA_r_meq_Re_c_times_c(s2, *m12, *m21);
  //#define C(x) QLA_real(x), QLA_imag(x)
  //printf("s1 (%g,%g)\n", C(s1));
  //printf("s2 (%g,%g)\n", C(s2));
  //printf("det (%g,%g)\n", C(det));
  // solve: x^3 + s2 x - det = 0
  QLA_Real q, r;
  q = (-1./3.)*s2;
  r = -0.5*det;
  QLA_Real sq = sqrtP(fabsP(q));
  QLA_Real sq3 = sq*sq*sq;
  if(sq3>fabsP(r)) {
    QLA_Real t = acosP(r/sq3);
    QLA_Complex sct = QLAP(cexpi)((1./3.)*t);
    QLA_Real sqc = sq*QLA_real(sct);
    QLA_Real sqs = 1.73205080756887729352*sq*QLA_imag(sct);  // sqrt(3)
    QLA_Real e0 = s1 - 2*sqc;
    QLA_Real ee = s1 + sqc;
    QLA_Real e1 = ee + sqs;
    QLA_Real e2 = ee - sqs;
    QLA_c_eq_r(*v0, e0);
    QLA_c_eq_r(*v1, e1);
    QLA_c_eq_r(*v2, e2);
  } else {
    // assume sq3 = |r|
    QLA_Real a = -cbrtP(r);
    QLA_c_eq_r(*v0, s1 + 2*a);
    QLA_c_eq_r(*v1, s1 - a);
    QLA_c_eq_r(*v2, s1 - a);
  }
}

void
QLAPC(V_eq_eigenvalsH_M)(NCARG QLAN(ColorVector,(*restrict r)),
			 QLAN(ColorMatrix,(*restrict a)))
{
#ifdef HAVE_XLC
#pragma disjoint(*r, *a)
  __alignx(16,r);
  __alignx(16,a);
#endif

#define V(i)   QLA_elem_V(*r,i)
#define M(i,j) QLA_elem_M(*a,i,j)
#if 1
  if(NC==1) {
    QLA_c_eq_c(V(0), M(0,0));
    return;
  }
  if(NC==2) {
    QLA_eigenvals_2x2(&V(0), &V(1),
		      &M(0,0), &M(0,1),
		      &M(1,0), &M(1,1));
    return;
  }
  if(NC==3) {
    QLA_eigenvals_3x3(&V(0),   &V(1),   &V(2),
		      &M(0,0), &M(0,1), &M(0,2),
		      &M(1,0), &M(1,1), &M(1,2),
		      &M(2,0), &M(2,1), &M(2,2));
    return;
  }
#endif

  // default to QR iteration
  QLAN(ColorMatrix, m);
  QLAN(ColorMatrix, h);
  int rc[NC];

  // copy input, set identity output and row pivot
  for(int i=0; i<NC; i++) {
    for(int j=0; j<NC; j++) {
      QLA_c_eq_c(QLA_elem_M(m,i,j), M(i,j));
    }
    rc[i] = i;
  }
  //printf("a: "); printdet(NC, a, NULL);
  //printf("m: "); printdet(NC, &m, NULL);

  // reduce to Hessenberg
#undef M
#define M(i,j) QLA_elem_M(m,rc[i],rc[j])
  for(int k=0; k<NC-2; k++) {
    QLA_Complex s;
    QLA_Real rmax = QLA_norm2_c(M(k+1,k));
    int imax = k+1;
    for(int i=k+2; i<NC; i++) {
      QLA_Real n2 = QLA_norm2_c(M(i,k));
      if(n2>rmax) { rmax = n2; imax = i; }
    }
    if(rmax==0) continue;
    { int rk = rc[k+1]; rc[k+1] = rc[imax]; rc[imax] = rk; }
    rmax = 1/rmax;
    QLA_c_eq_r_times_ca(s, rmax, M(k+1,k));
    for(int i=k+2; i<NC; i++) {
      QLA_Complex t;
      // row elimination of M(i,k) from M(k+1,k)
      QLA_c_eq_c_times_c(t, s, M(i,k));
      QLA_c_eq_r(M(i,k), 0);
      for(int j=k+1; j<NC; j++) {
        QLA_c_meq_c_times_c(M(i,j), t, M(k+1,j));
      }
      // column update of M(:,k+1) from M(:,i)
      for(int j=0; j<NC; j++) {
        QLA_c_peq_c_times_c(M(j,k+1), t, M(j,i));
      }
      //printf("k: %i  i: %i  ", k, i); printdet(NC, &m);
    }
  }
  for(int i=0; i<NC; i++) {
    for(int j=0; j<NC; j++) {
      QLA_c_eq_c(QLA_elem_M(h,i,j), M(i,j));
    }
  }
  //printf("h: "); printdet(NC, &h);

#undef M
#define M(i,j) QLA_elem_M(h,i,j)

#if 0 // plain QR

#define X(i) M(i,i)
#define Y(i) M(i+1,i)
  QLA_Complex xs[NC-1], ys[NC-1];
  int nits=0, nups;
  do {
    nups = 0;
    for(int i=0; i<NC-1; i++) {
      QLA_Real tx = QLA_norm2_c(X(i));
      QLA_Real ty = QLA_norm2_c(Y(i));
      QLA_Real tx2 = QLA_norm2_c(X(i+1));
      //printf("%i nty%i: %g\n", nits, i, ty/(tx+tx2));
      if(ty<EPS*(tx+tx2)) {
	QLA_c_eq_r(xs[i], 1);
	QLA_c_eq_r(ys[i], 0);
	continue;
      }
      QLA_Real nz = sqrt(tx+ty);
      QLA_Real inz = 1/nz;
      QLA_Complex xst, yst;
      QLA_c_eq_r_times_c(xst, inz, X(i));
      QLA_c_eq_r_times_c(yst, inz, Y(i));
      QLA_c_eq_c(xs[i], xst);
      QLA_c_eq_c(ys[i], yst);
      // multiply rows i,i+1 by [ xst' yst'; -yst xst ]
      QLA_c_eq_r(X(i), nz);
      QLA_c_eq_r(Y(i), 0);
      for(int j=i+1; j<NC; j++) {
	QLA_Complex v0, v1, u0, u1;
	QLA_c_eq_c(v0, M(i,j));
	QLA_c_eq_c(v1, M(i+1,j));
	QLA_c_eq_ca_times_c(u0, xst, v0);
	QLA_c_peq_ca_times_c(u0, yst, v1);
	QLA_c_eq_c_times_c(u1, xst, v1);
	QLA_c_meq_c_times_c(u1, yst, v0);
	QLA_c_eq_c(M(i,j), u0);
	QLA_c_eq_c(M(i+1,j), u1);
      }
      nups++;
    }
    if(nups==0) break;
    // multiply cols j,j+1 by [ xst -yst'; yst xst' ]
    for(int j=0; j<NC-1; j++) {
      QLA_Complex xst, yst;
      QLA_c_eq_c(xst, xs[j]);
      QLA_c_eq_c(yst, ys[j]);
      for(int i=0; i<NC; i++) {
	QLA_Complex v0, v1, u0, u1;
	QLA_c_eq_c(v0, M(i,j));
	QLA_c_eq_c(v1, M(i,j+1));
	QLA_c_eq_c_times_c(u0, xst, v0);
	QLA_c_peq_c_times_c(u0, yst, v1);
	QLA_c_eq_ca_times_c(u1, xst, v1);
	QLA_c_meq_ca_times_c(u1, yst, v0);
	QLA_c_eq_c(M(i,j), u0);
	QLA_c_eq_c(M(i,j+1), u1);
      }
    }
    //printf("h: "); printdet(NC, &h);
  } while(++nits<30);
  for(int i=0; i<NC; i++) {
    QLA_c_eq_c(V(i), M(i,i));
  }

#else  // implicit double shift QR

#define ABS(z) QLA_norm_c(z)
#define NORM2(z) QLA_norm2_c(z)
  // Compute matrix norm for possible use in locating
  //  single small subdiagonal element
  QLA_Real anorm = 0;  
  for(int i=0; i<NC; i++) {
    for(int j=(i==0?0:i-1); j<NC; j++) {
      anorm += ABS(M(i,j));
    }
  }
  int nn = NC - 1;
  QLA_Complex t;  // Gets changed only by an exceptional shift
  QLA_c_eq_r(t, 0);
  while(nn>=0) {  // Begin search for next eigenvalue
    int l, its = 0;
    do {
      for(l=nn; l>0; l--) {  // look for single small subdiagonal element
	QLA_Real s = ABS(M(l-1,l-1)) + ABS(M(l,l));
	if(s==0) s = anorm;
	QLA_Real o = ABS(M(l,l-1));
	//printf("%i %i :\t%g\t%g\t%g\n", nn, l, o, s, o/s);
	if(s+o == s) {
	  QLA_c_eq_r(M(l,l-1), 0);
	  break;
	}
      }
      QLA_Complex x = M(nn,nn);
      if(l==nn) {  // One root found
	QLA_c_eq_c_plus_c(V(nn), x, t);
	nn--;
      } else if(l==nn-1) {  // Two roots found
	QLA_eigenvals_2x2(&V(nn-1), &V(nn), &M(nn-1,nn-1),
			  &M(nn-1,nn), &M(nn,nn-1), &x);
	QLA_c_peq_c(V(nn-1), t);
	QLA_c_peq_c(V(nn), t);
	nn -= 2;
      } else {  // No roots found, continue iteration
	if(its>=100) {
	  printf("too many iterations in %s\n", __func__);
	  for(int i=0; i<=nn; i++) QLA_c_eq_c_plus_c(V(i), M(i,i), t);
	  break;
	}
	QLA_Complex y, w;
	QLA_c_eq_c(y, M(nn-1,nn-1));
	QLA_c_eq_c_times_c(w, M(nn,nn-1), M(nn-1,nn));
	if(its==10 || its==20) {  // Form exceptional shift
	  QLA_c_peq_c(t, x);
	  for(int i=0; i<nn; i++) QLA_c_meq_c(M(i,i), x);
	  QLA_c_eq_r(M(nn,nn), 0);
	  QLA_c_eq_r(x, 0);
	  QLA_c_eq_c(y, M(nn-1,nn-1));
	  QLA_Real s = ABS(M(nn,nn-1)) + ABS(M(nn-1,nn-2));
	  QLA_c_eq_r(x, 0.75*s);
	  QLA_c_eq_c(y, x);
	  QLA_c_eq_r(w, -0.4375*s*s);
	}
	its++;
	// Form shift and look for 2 consecutive small subdiagonal elements
	QLA_Complex p, q, r;
	int m;
	//for(m=nn-2; m>=l; m--) {
	for(m=l; m>=l; m--) {
	  QLA_Complex rr, ss, t1, z = M(m,m);
	  QLA_c_eq_c_minus_c(rr, x, z);
	  QLA_c_eq_c_minus_c(ss, y, z);
	  //p=(r*s-w)/a(m+1,m)+a(m,m+1); // Equation(11.6.23)
	  //q=a(m+1,m+1)-z-r-s;
	  //r=a(m+2,m+1);
	  // multiply all above by a(m+1,m)
	  QLA_c_eq_c_times_c(p, rr, ss);
	  QLA_c_meq_c(p, w);
	  QLA_c_peq_c_times_c(p, M(m+1,m), M(m,m+1));
	  QLA_c_eq_c_minus_c(t1, M(m+1,m+1), z);
	  QLA_c_meq_c_plus_c(t1, rr, ss);
	  QLA_c_eq_c_times_c(q, M(m+1,m), t1);
	  QLA_c_eq_c_times_c(r, M(m+1,m), M(m+2,m+1));
	  //s=abs(p)+abs(q)+abs(r); // Scale to prevent overflow or underflow
	  //p=p/s ;
	  //q=q/s ;
	  //r=r/s ;
	  if(m==l) break;
	  //u=abs(a(m,m-1))*(abs(q)+abs(r)) ;
	  //v=abs(p)*(abs(a(m-1,m-1))+abs(z)+abs(a(m+1,m+1))) ;
	  //if(u+v==v) break; //Equation(11.6.26). 
	}
	//for(int i=m; i<nn-1; i++) {
	//QLA_c_eq_r(M(i+2,i), 0);
	//if(i!=m) QLA_c_eq_r(M(i+2,i-1), 0);
	//}
	//printf("%i before QR: ", its); printdet(NC, &h, &t);
	// Double QR step on rows l to nn and columns m to nn
	for(int k=m; k<nn; k++) {
	  //printf(" %i: ", k); printdet(NC, &h, &t);
	  QLA_Real xx=0;
	  if(k!=m) {
	    p = M(k,k-1);  // Begin setup of Householder vector
	    q = M(k+1,k-1);
	    QLA_c_eq_r(r, 0);
	    if(k+1!=nn) r = M(k+2,k-1);
	    xx = ABS(p) + ABS(q) + ABS(r);
	    if(xx!=0) {  // Scale to prevent overflow or underflow
	      QLA_Real xxi = 1/xx;
	      QLA_c_eq_r_times_c(p, xxi, p);
	      QLA_c_eq_r_times_c(q, xxi, q);
	      QLA_c_eq_r_times_c(r, xxi, r);
	    }
	  }
	  QLA_Real p2 = NORM2(p);
	  QLA_Real s2 = p2 + NORM2(q) + NORM2(r);
	  if(s2!=0) {
	    QLA_Complex s;
	    if(p2>0) {
	      QLA_c_eq_r_times_c(s, sqrt(s2/p2), p);
	    } else {
	      QLA_c_eq_r(s, sqrt(s2));
	    }
	    if(k==m) {
	      if(l!=m) QLA_c_eqm_c(M(k,k-1), M(k,k-1));
	    } else {
	      QLA_c_eq_r_times_c(M(k,k-1), -xx, s);
	      QLA_c_eq_r(M(k+1,k-1), 0);
	      QLA_c_eq_r(M(k+2,k-1), 0);
	    }
	    QLA_c_peq_c(p, s);
	    QLA_c_eq_c_div_c(x, p, s);
	    QLA_c_eq_c_div_c(y, q, s);
	    QLA_c_eq_c_div_c(w, r, s);
	    QLA_Complex t1;
	    QLA_c_eq_c_div_c(t1, q, p);
	    QLA_c_eq_c(q, t1);
	    QLA_c_eq_c_div_c(t1, r, p);
	    QLA_c_eq_c(r, t1);
	    {
	      QLA_c_eq_c(t1, x);
	      QLA_c_peq_ca_times_c(t1, q, y);
	      QLA_c_peq_ca_times_c(t1, r, w);
	      //printf("dot: %g  %g\n", QLA_real(t1), QLA_imag(t1));
	    }
	    for(int j=k; j<=nn; j++) {  // Row modification
	      QLA_c_eq_c(p, M(k,j));
	      QLA_c_peq_ca_times_c(p, q, M(k+1,j));
	      if(k+1!=nn) {
		QLA_c_peq_ca_times_c(p, r, M(k+2,j));
		QLA_c_meq_c_times_c(M(k+2,j), p, w);
	      }
	      QLA_c_meq_c_times_c(M(k+1,j), p, y);
	      QLA_c_meq_c_times_c(M(k,j), p, x);
	    }
	    for(int i=l; i<=(nn<k+3?nn:k+3); i++) {  // Column modification
	      QLA_c_eq_c_times_c(p, x, M(i,k));
	      QLA_c_peq_c_times_c(p, y, M(i,k+1));
	      if(k+1!=nn) {
		QLA_c_peq_c_times_c(p, w, M(i,k+2));
		QLA_c_meq_c_times_ca(M(i,k+2), p, r);
	      }
	      QLA_c_meq_c_times_ca(M(i,k+1), p, q);
	      QLA_c_meq_c(M(i,k), p);
	    }
	  }
	  //printf(" %i: ", k); printdet(NC, &h, &t);
	}
	//printf("after QR: "); printdet(NC, &h, &t);
      }
    } while(l+1<nn);
  }

#endif // end QR type
}
