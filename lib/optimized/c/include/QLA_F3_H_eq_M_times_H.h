#include "QLA_F3_V_eq_M_times_V.h"

#define vptr(x) ((QLA_F3_ColorVector *)(x))

#define QLA_F3_H_eq_M_times_H(aa,bb,cc) \
{ \
  QLA_F3_V_eq_M_times_V(vptr(aa),bb,vptr(cc)); \
  QLA_F3_V_eq_M_times_V((vptr(aa)+1),bb,(vptr(cc)+1)); \
}
