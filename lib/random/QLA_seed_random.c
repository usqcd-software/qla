/******************* QLA_random.c *********************/
/* MILC version 6 */
/* Seed the generator */

/*  C language random number generator for parallel processors */
/*  exclusive or of feedback shift register and integer congruence
    generator.  Use a different multiplier on each generator, and make sure
    that fsr is initialized differently on each generator.  */

#include <qla_types.h>
#include <qla_random.h>

void QLA_seed_random(QLA_RandomState *prn_pt, int seed, QLA_Int index) {
  /* "index" selects which random number generator - which multiplier */
  seed = (69607+8*index)*seed+12345;
  prn_pt->r0 = (seed>>8) & 0xffffff;
  seed = (69607+8*index)*seed+12345;
  prn_pt->r1 = (seed>>8) & 0xffffff;
  seed = (69607+8*index)*seed+12345;
  prn_pt->r2 = (seed>>8) & 0xffffff;
  seed = (69607+8*index)*seed+12345;
  prn_pt->r3 = (seed>>8) & 0xffffff;
  seed = (69607+8*index)*seed+12345;
  prn_pt->r4 = (seed>>8) & 0xffffff;
  seed = (69607+8*index)*seed+12345;
  prn_pt->r5 = (seed>>8) & 0xffffff;
  seed = (69607+8*index)*seed+12345;
  prn_pt->r6 = (seed>>8) & 0xffffff;
  seed = (69607+8*index)*seed+12345;
  prn_pt->ic_state = seed;
  prn_pt->multiplier = 100005 + 8*index;
  prn_pt->addend = 12345;
  prn_pt->scale = 1.0/((float)0x1000000);
}
