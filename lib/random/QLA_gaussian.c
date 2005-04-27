/******************* QLA_random.c *********************/
/* MILC version 6 */
/* Gaussian normal deviate */

#include <qla_types.h>
#include <qla_random.h>
#include <math.h>
#ifndef M_PI /* Cray X1 math.h doesn't define this by default */
#define M_PI 3.14159265358979323846
#endif
#define TINY 1e-307

QLA_F_Real QLA_gaussian(QLA_RandomState *prn_pt) {
  double v,p,r;

  v = QLA_random(prn_pt);
  p = QLA_random(prn_pt)*2.*M_PI;
  r = sqrt(2.*(-log(v+TINY)));
  return (QLA_F_Real)(r*cos(p));
}
