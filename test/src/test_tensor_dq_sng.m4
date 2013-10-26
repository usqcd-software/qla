/* QLA test code */
/* for single tensor routines.  Precision conversion */
/* C Code automatically generated from test_df_tensor_sng.m4 */

include(protocol_tensor_sng.m4)
`
#include <qla.h>
#if QLA_Nc == 3
#include <qla_d3.h>
#include <qla_f3.h>
#elif QLA_Nc == 2
#include <qla_d2.h>
#include <qla_f2.h>
#elif QLA_Nc == 1
#include <qla_d1.h>
#include <qla_f1.h>
#else
#include <qla_dn.h>
#include <qla_fn.h>
#endif
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "compare.h"

int main(int argc, char * argv[]){

  int nc = QLA_Nc;
  int ns = 4;

  QLA_Int sI2 = 0;
  QLA_Int sI3 = 7032;

  QLA_Q_Real sRQ1 =  0.17320508075688772;
  QLA_Q_Real sRQ2 =  0.28723479823477934;

  QLA_Q_ColorMatrix         sMQ1/*,sMQ2,sMQ3*/;
  QLA_Q_HalfFermion         sHQ1/*,sHQ2,sHQ3*/;
  QLA_Q_DiracFermion        sDQ1/*,sDQ2,sDQ3*/;
  QLA_Q_ColorVector         sVQ1/*,sVQ2,sVQ3*/;
  QLA_Q_DiracPropagator     sPQ1/*,sPQ2,sPQ3*/;

  QLA_Q_Real                destRQ,chkRQ;
  QLA_Q_Complex             destCQ,chkCQ;
  QLA_Q_ColorMatrix         destMQ,chkMQ;
  QLA_Q_HalfFermion         destHQ,chkHQ;
  QLA_Q_DiracFermion        destDQ,chkDQ;
  QLA_Q_ColorVector         destVQ,chkVQ;
  QLA_Q_DiracPropagator     destPQ,chkPQ;

  QLA_D_ColorMatrix         sMD1,sMD2,sMD3;
  QLA_D_HalfFermion         sHD1,sHD2,sHD3;
  QLA_D_DiracFermion        sDD1,sDD2,sDD3;
  QLA_D_ColorVector         sVD1,sVD2,sVD3;
  QLA_D_DiracPropagator     sPD1,sPD2,sPD3;

  QLA_D_ColorMatrix         destMD,chkMD;
  QLA_D_HalfFermion         destHD,chkHD;
  QLA_D_DiracFermion        destDD,chkDD;
  QLA_D_ColorVector         destVD,chkVD;
  QLA_D_DiracPropagator     destPD,chkPD;

  QLA_RandomState sS1;

  int ic,jc,is,js;

  char name[64];
  FILE *fp;

  char *test_program_name= basename(argv[0]); 
  test_program_name = strcat(test_program_name, ".result");
  if (NULL == (fp = fopen(test_program_name,"w"))) {
    fprintf(stderr, "Error in report function - cannot create \"%s\"\n", test_program_name);
    exit(-1);
  }

  /* Use random number fills to create the test fields */

  QLA_S_eq_seed_i_I(&sS1,sI2,&sI3);

  /* Double precision */

  QLA_D_H_eq_gaussian_S(&sHD1,&sS1);
  QLA_D_H_eq_gaussian_S(&sHD2,&sS1);
  QLA_D_H_eq_gaussian_S(&sHD3,&sS1);
  			   			   
  QLA_D_D_eq_gaussian_S(&sDD1,&sS1);
  QLA_D_D_eq_gaussian_S(&sDD2,&sS1);
  QLA_D_D_eq_gaussian_S(&sDD3,&sS1);
  			   			   
  QLA_D_V_eq_gaussian_S(&sVD1,&sS1);
  QLA_D_V_eq_gaussian_S(&sVD2,&sS1);
  QLA_D_V_eq_gaussian_S(&sVD3,&sS1);
  			   			   
  QLA_D_P_eq_gaussian_S(&sPD1,&sS1);
  QLA_D_P_eq_gaussian_S(&sPD2,&sS1);
  QLA_D_P_eq_gaussian_S(&sPD3,&sS1);
  			   			   
  QLA_D_M_eq_gaussian_S(&sMD1,&sS1);
  QLA_D_M_eq_gaussian_S(&sMD2,&sS1);
  QLA_D_M_eq_gaussian_S(&sMD3,&sS1);
'
  /* "Quad" precision */

  makeGaussianQ(H,sHQ1);
  /*makeGaussianQ(H,sHQ2);*/
  /*makeGaussianQ(H,sHQ3);*/

  makeGaussianQ(D,sDQ1);
  /*makeGaussianQ(D,sDQ2);*/
  /*makeGaussianQ(D,sDQ3);*/

  makeGaussianQ(V,sVQ1);
  /*makeGaussianQ(V,sVQ2);*/
  /*makeGaussianQ(V,sVQ3);*/

  makeGaussianQ(P,sPQ1);
  /*makeGaussianQ(P,sPQ2);*/
  /*makeGaussianQ(P,sPQ3);*/

  makeGaussianQ(M,sMQ1);
  /*makeGaussianQ(M,sMQ2);*/
  /*makeGaussianQ(M,sMQ3);*/

/* Assignments */

alltensors(`chkAssignDQ');

/* Reductions */
alltensors(`chkNorm2QD');
alltensors(`chkDotQD');
alltensors(`chkRealDotQD');
alltensors(`chkSumQD');
`
  return 0;
}
'
