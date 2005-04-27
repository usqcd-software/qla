/******************* QLA_random.c *********************/
/* MILC version 6 */
/* Return random number uniform on [0,1] */

/*  C language random number generator for parallel processors */
/*  exclusive or of feedback shift register and integer congruence
    generator.  Use a different multiplier on each generator, and make sure
    that fsr is initialized differently on each generator.  */

#include <qla_types.h>
#include <qla_random.h>

QLA_F_Real QLA_random(QLA_RandomState *prn_pt) {
  register int t,s;
  
  t = ( ((prn_pt->r5 >> 7) | (prn_pt->r6 << 17)) ^
	((prn_pt->r4 >> 1) | (prn_pt->r5 << 23)) ) & 0xffffff;
  prn_pt->r6 = prn_pt->r5;
  prn_pt->r5 = prn_pt->r4;
  prn_pt->r4 = prn_pt->r3;
  prn_pt->r3 = prn_pt->r2;
  prn_pt->r2 = prn_pt->r1;
  prn_pt->r1 = prn_pt->r0;
  prn_pt->r0 = t;
  s = prn_pt->ic_state * prn_pt->multiplier + prn_pt->addend;
  prn_pt->ic_state = s;
  return( prn_pt->scale*(t ^ ((s>>8)&0xffffff)) );
}
