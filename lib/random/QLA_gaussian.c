/******************* QLA_random.c *********************/
/* MILC version 6 */
/* Gaussian normal deviate */
/* Probability distribution exp( -x*x/2 ), so < x^2 > = 1 */

#include <qla_types.h>
#include <qla_random.h>
#include <math.h>

#ifdef OLD_GAUSSIAN

#ifndef M_PI /* Cray X1 math.h doesn't define this by default */
#define M_PI 3.14159265358979323846
#endif
#define TINY 1e-307
QLA_F_Real
QLA_gaussian(QLA_RandomState *prn_pt)
{
  double v,p,r;
  v = QLA_random(prn_pt);
  p = QLA_random(prn_pt)*2.*M_PI;
  r = sqrt(2.*(-log(v+TINY)));
  return (QLA_F_Real)(r*cos(p));
}

#else

QLA_F_Real
QLA_gaussian(QLA_RandomState *rs)
{
#if 0
  static int iset = 1;
  static float gset;
#else
#define iset rs->addend
#define gset rs->scale
#endif

  if(iset != 0) {
    iset = 0;
    double v1, v2, rsq;
    do {
      v1 = (double) QLA_random(rs);
      v2 = (double) QLA_random(rs);
      v1 = 2.0*v1 - 1.0;
      v2 = 2.0*v2 - 1.0;
      rsq = v1*v1 + v2*v2;
    } while( (rsq>=1.0) || (rsq==0.0) );
    double fac = sqrt( -2.0*log(rsq)/rsq );
    gset = (float) (v1*fac);
    return (float) (v2*fac);
  } else {
    iset = 1;
    return gset;
  }
}

#endif
