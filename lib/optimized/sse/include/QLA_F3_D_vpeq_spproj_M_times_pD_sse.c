{
  if(n) {
    int nn = n;
    if(!is_aligned(a,16)) {
      n = 1;
      nn--;
#include <QLA_F3_D_vpeq_spproj_M_times_pD_1_sse.c>
    }
    n = 2*(nn/2);
    nn -= n;
#include <QLA_F3_D_vpeq_spproj_M_times_pD_2_sse.c>
    if(nn) {
      n = nn;
#include <QLA_F3_D_vpeq_spproj_M_times_pD_1_sse.c>
    }
  }
}
