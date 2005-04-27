#ifndef _MILC_GAMMA_H
#define _MILC_GAMMA_H

void wp_shrink( QLA_HalfFermion *dest, QLA_DiracFermion *src,
		int dir, int sign );
void wp_grow(  QLA_DiracFermion *dest, QLA_HalfFermion *src,
        int dir, int sign );
void mult_by_gamma_left(  QLA_DiracPropagator *dest, QLA_DiracPropagator *src,  int dir );
void mult_by_gamma_right( QLA_DiracPropagator *dest, QLA_DiracPropagator *src, int dir );
void mult_wv_by_gamma_left(  QLA_DiracFermion *dest, QLA_DiracFermion *src,  int dir );
#endif /* _MILC_GAMMA_H */
