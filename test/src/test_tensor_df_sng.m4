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

  QLA_D_ColorMatrix         sMD1,sMD2,sMD3;
  QLA_D_HalfFermion         sHD1,sHD2,sHD3;
  QLA_D_DiracFermion        sDD1,sDD2,sDD3;
  QLA_D_ColorVector         sVD1,sVD2,sVD3;
  QLA_D_DiracPropagator     sPD1,sPD2,sPD3;

  QLA_D_Real                destRD,chkRD;
  QLA_D_Complex             destCD,chkCD;
  QLA_D_ColorMatrix         destMD,chkMD;
  QLA_D_HalfFermion         destHD,chkHD;
  QLA_D_DiracFermion        destDD,chkDD;
  QLA_D_ColorVector         destVD,chkVD;
  QLA_D_DiracPropagator     destPD,chkPD;

  QLA_F_ColorMatrix         sMF1,sMF2,sMF3;
  QLA_F_HalfFermion         sHF1,sHF2,sHF3;
  QLA_F_DiracFermion        sDF1,sDF2,sDF3;
  QLA_F_ColorVector         sVF1,sVF2,sVF3;
  QLA_F_DiracPropagator     sPF1,sPF2,sPF3;

  QLA_F_ColorMatrix         destMF,chkMF;
  QLA_F_HalfFermion         destHF,chkHF;
  QLA_F_DiracFermion        destDF,chkDF;
  QLA_F_ColorVector         destVF,chkVF;
  QLA_F_DiracPropagator     destPF,chkPF;

  QLA_RandomState sS1;

  char name[64];
  FILE *fp;

  char *test_program_name= basename(argv[0]); 
  test_program_name = strcat(test_program_name, ".result");
  if (NULL == (fp = fopen(test_program_name,"w"))) {
    fprintf(stderr, "Error in report function - cannot create \"%s\"\n", test_program_name);
    exit(-1);
  }

  int ic,jc,is,js;

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

  /* Single precision */

  QLA_F_H_eq_gaussian_S(&sHF1,&sS1);
  QLA_F_H_eq_gaussian_S(&sHF2,&sS1);
  QLA_F_H_eq_gaussian_S(&sHF3,&sS1);
  
  QLA_F_D_eq_gaussian_S(&sDF1,&sS1);
  QLA_F_D_eq_gaussian_S(&sDF2,&sS1);
  QLA_F_D_eq_gaussian_S(&sDF3,&sS1);
  
  QLA_F_V_eq_gaussian_S(&sVF1,&sS1);
  QLA_F_V_eq_gaussian_S(&sVF2,&sS1);
  QLA_F_V_eq_gaussian_S(&sVF3,&sS1);
  
  QLA_F_P_eq_gaussian_S(&sPF1,&sS1);
  QLA_F_P_eq_gaussian_S(&sPF2,&sS1);
  QLA_F_P_eq_gaussian_S(&sPF3,&sS1);
  
  QLA_F_M_eq_gaussian_S(&sMF1,&sS1);
  QLA_F_M_eq_gaussian_S(&sMF2,&sS1);
  QLA_F_M_eq_gaussian_S(&sMF3,&sS1);

'

/* Assignments */

alltensors(`chkAssignDF');
alltensors(`chkAssignFD');

/* Reductions */
alltensors(`chkNorm2DF');
alltensors(`chkDotDF');
chkDotDF(M,a);
chkDotDF(P,a);
alltensors(`chkRealDotDF');
alltensors(`chkSumDF');

`
  return 0;
}

'
