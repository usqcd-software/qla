/******************* QLA_random.c *********************/
/* MILC version 6 */
/* Return random number uniform on [0,1] */

/*  C language random number generator for parallel processors */
/*  exclusive or of feedback shift register and integer congruence
    generator.  Use a different multiplier on each generator, and make sure
    that fsr is initialized differently on each generator.  */

#include <qla_types.h>
#include <qla_random.h>

#ifdef OLD_GAUSSIAN
#define ADDEND prn_pt->addend
#define SCALE prn_pt->scale
#else
#define ADDEND 12345
#define SCALE (1.0f/((float)0x1000000))
#endif

QLA_F_Real
QLA_random(QLA_RandomState *prn_pt)
{
  int t = ( ((prn_pt->r5 >> 7) | (prn_pt->r6 << 17)) ^
	    ((prn_pt->r4 >> 1) | (prn_pt->r5 << 23)) ) & 0xffffff;
  prn_pt->r6 = prn_pt->r5;
  prn_pt->r5 = prn_pt->r4;
  prn_pt->r4 = prn_pt->r3;
  prn_pt->r3 = prn_pt->r2;
  prn_pt->r2 = prn_pt->r1;
  prn_pt->r1 = prn_pt->r0;
  prn_pt->r0 = t;
  int s = prn_pt->ic_state * prn_pt->multiplier + ADDEND;
  prn_pt->ic_state = s;
  return( SCALE*(t ^ ((s>>8)&0xffffff)) );
}
