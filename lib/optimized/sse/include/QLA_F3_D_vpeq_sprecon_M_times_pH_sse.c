{
  if(n) {
    int nn = n;
    if(!is_aligned(a,16)) {
      n = 1;
      nn--;
#include <QLA_F3_D_vpeq_sprecon_M_times_pH_1_sse.c>
      r += n; a += n; b += n;
    }
    n = 2*(nn/2);
    nn -= n;
#include <QLA_F3_D_vpeq_sprecon_M_times_pH_2_sse.c>
    if(nn) {
      r += n; a += n; b += n;
      n = nn;
#include <QLA_F3_D_vpeq_sprecon_M_times_pH_1_sse.c>
    }
  }
}
