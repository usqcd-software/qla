/**************** QLA_F3_V_veq_M_times_V.c ********************/

#include <qla_types.h>
#include <qla_cmath.h>
#include <qla_sse.h>
#include <math.h>
#include <stdlib.h>

//#define LOAD1

#define NP 8

#define loadpsa(a) loadups(a)
#define loadpsr(a) loadups(a)
#define storepsr(a,b) storeups(a,b)
inline static void
QLA_F3_V_veq_M_times_pV_2uu( QLA_F3_ColorVector *restrict r,
			      QLA_F3_ColorMatrix *a,
			      QLA_F3_ColorVector **b,
			      int n )
#include "QLA_F3_V_veq_M_times_pV_2_sse.c"
#undef loadpsa
#undef loadpsr
#undef storepsr

#define loadpsa(a) loadups(a)
#define loadpsr(a) loadaps(a)
#define storepsr(a,b) storeaps(a,b)
inline static void
QLA_F3_V_veq_M_times_pV_2au( QLA_F3_ColorVector *restrict r,
			      QLA_F3_ColorMatrix *a,
			      QLA_F3_ColorVector **b,
			      int n )
#include "QLA_F3_V_veq_M_times_pV_2_sse.c"
#undef loadpsa
#undef loadpsr
#undef storepsr

#define loadpsa(a) loadaps(a)
#define loadpsr(a) loadaps(a)
#define storepsr(a,b) storeaps(a,b)
inline static void
QLA_F3_V_veq_M_times_pV_2aa( QLA_F3_ColorVector *restrict r,
			      QLA_F3_ColorMatrix *a,
			      QLA_F3_ColorVector **b,
			      int n )
#include "QLA_F3_V_veq_M_times_pV_2_sse.c"
#undef loadpsa
#undef loadpsr
#undef storepsr

inline static void
QLA_F3_V_veq_M_times_pV_1u( QLA_F3_ColorVector *restrict r,
			     QLA_F3_ColorMatrix *a,
			     QLA_F3_ColorVector **b,
			     int n )
#include "QLA_F3_V_veq_M_times_pV_1_sse.c"

void
QLA_F3_V_veq_M_times_pV( QLA_F3_ColorVector *__restrict__ r,
			  QLA_F3_ColorMatrix *a,
			  QLA_F3_ColorVector **b,
			  int n )
{
  size_t s8=0x7, s16=0xf;
  size_t sr = (size_t)r;
  size_t sa = (size_t)a;
  int r16, a16, ra8;
  int nb1, n1, nb2, n2, nn;

  r16 = ((sr&s16)==0);
  a16 = ((sa&s16)==0);
  ra8 = ((sr&s8)==0)&&((sa&s8)==0);
  //printf("%p %p %i %i\n", r, a, a8, a16);

  if( ra8 && !r16 ) nb1 = 1;
  else nb1 = 0;
  n1 = n - nb1;
  if(n1&1) n1--;
  nb2 = nb1 + n1;
  n2 = n - nb2;

  if(nb1) {
    nn = nb1;
    QLA_F3_V_veq_M_times_pV_1u(r, a, b, nn);
    r += nn; a += nn; b += nn;
  }
  if(n1) {
    nn = n1;
    if(ra8) {
      if( r16 == a16 ) {
	QLA_F3_V_veq_M_times_pV_2aa(r, a, b, nn);
      } else {
	QLA_F3_V_veq_M_times_pV_2au(r, a, b, nn);
      }
    } else {
      QLA_F3_V_veq_M_times_pV_2uu(r, a, b, nn);
    }
    r += nn; a += nn; b += nn;
  }
  if(n2) QLA_F3_V_veq_M_times_pV_1u(r, a, b, n2);

}
