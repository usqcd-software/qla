/* QLA test code */
/* for indexed integer routines. */
/* Standalone C code */

#include <qla.h>
#include <stdio.h>
#include <string.h>
#include "compare.h"

#define CHECKeqsngII(a,b,c) {QLA_Int tmp1,tmp2; tmp1 = (a); tmp2 = (b); \
      checkeqsngII(&tmp1,&tmp2,c);}

#define CHECKeqsngSS(a,b,c) {checkeqsngSS(a,b,c);}

QLA_Int max(QLA_Int i1, QLA_Int sI2){
  return i1 > sI2 ? i1 : sI2;
}

QLA_Int min(QLA_Int i1, QLA_Int sI2){
  return i1 < sI2 ? i1 : sI2;
}

int main(){
  QLA_Int sI1 =  271828182;
  QLA_Int sI2 = -845904523;
  QLA_Int sI3 = -536028747;
  QLA_Int sI4 =  13526;
  QLA_Int sI5 = -3;
  QLA_Int sI6 = 7;
  QLA_Int sI7 = 0;
  QLA_Int destI,chkI;

  QLA_RandomState destS,chkS;
  QLA_Int nI1          = 2;

  char name[64];
  
  /* QLA_I_eq_I */
 
  strcpy(name,"QLA_I_eq_I");
  QLA_I_eq_I(&destI,&sI1);
  CHECKeqsngII(destI,sI1,name);

  chkI = destI;
  strcpy(name,"QLA_I_peq_I");
  QLA_I_peq_I(&destI,&sI1);
  CHECKeqsngII(destI,chkI+sI1,name);

  strcpy(name,"QLA_I_eqm_I");
  QLA_I_eqm_I(&destI,&sI1);
  CHECKeqsngII(destI,-sI1,name);

  chkI = destI;
  strcpy(name,"QLA_I_meq_I");
  QLA_I_meq_I(&destI,&sI1);
  CHECKeqsngII(destI,chkI-sI1,name);

  /* QLA_I_eq_i_times_I */
 
  strcpy(name,"QLA_I_eq_i_times_I");
  QLA_I_eq_i_times_I(&destI,&sI1,&sI5);
  CHECKeqsngII(destI,sI1*sI5,name);

  chkI = destI;
  strcpy(name,"QLA_I_peq_i_times_I");
  QLA_I_peq_i_times_I(&destI,&sI1,&sI5);
  CHECKeqsngII(destI,chkI+sI1*sI5,name);

  strcpy(name,"QLA_I_eqm_i_times_I");
  QLA_I_eqm_i_times_I(&destI,&sI1,&sI5);
  CHECKeqsngII(destI,-sI1*sI5,name);

  chkI = destI;
  strcpy(name,"QLA_I_meq_i_times_I");
  QLA_I_meq_i_times_I(&destI,&sI1,&sI5);
  CHECKeqsngII(destI,chkI-sI1*sI5,name);

  strcpy(name,"QLA_I_eq_I_plus_I");
  QLA_I_eq_I_plus_I(&destI,&sI1,&sI2);
  CHECKeqsngII(destI,sI1+sI2,name);

  strcpy(name,"QLA_I_eq_I_minus_I");
  QLA_I_eq_I_minus_I(&destI,&sI1,&sI2);
  CHECKeqsngII(destI,sI1-sI2,name);
  
  strcpy(name,"QLA_I_eq_I_divide_I");
  QLA_I_eq_I_divide_I(&destI,&sI1,&sI2);
  CHECKeqsngII(destI,sI1/sI2,name);

  /* QLA_I_eq_I_times_I */

  strcpy(name,"QLA_I_eq_I_times_I");
  QLA_I_eq_I_times_I(&destI,&sI2,&sI5);
  CHECKeqsngII(destI,sI2*sI5,name);

  chkI = destI;
  strcpy(name,"QLA_I_peq_I_times_I");
  QLA_I_peq_I_times_I(&destI,&sI2,&sI5);
  CHECKeqsngII(destI,chkI+sI2*sI5,name);

  strcpy(name,"QLA_I_eqm_I_times_I");
  QLA_I_eqm_I_times_I(&destI,&sI2,&sI5);
  CHECKeqsngII(destI,-sI2*sI5,name);

  chkI = destI;
  strcpy(name,"QLA_I_meq_I_times_I");
  QLA_I_meq_I_times_I(&destI,&sI2,&sI5);
  CHECKeqsngII(destI,chkI-sI2*sI5,name);

  strcpy(name,"QLA_I_eq_i_times_I_plus_I");
  QLA_I_eq_i_times_I_plus_I(&destI,&sI1,&sI5,&sI2);
  CHECKeqsngII(destI,sI1*sI5+sI2,name);

  strcpy(name,"QLA_I_eq_i_times_I_minus_I");
  QLA_I_eq_i_times_I_minus_I(&destI,&sI1,&sI5,&sI2);
  CHECKeqsngII(destI,sI1*sI5-sI2,name);

  strcpy(name,"QLA_I_eq_I_lshift_I");
  QLA_I_eq_I_lshift_I(&destI,&sI4,&sI6);
  CHECKeqsngII(destI,sI4<<sI6,name);

  strcpy(name,"QLA_I_eq_I_rshift_I");
  QLA_I_eq_I_rshift_I(&destI,&sI4,&sI6);
  CHECKeqsngII(destI,sI4>>sI6,name);

  strcpy(name,"QLA_I_eq_I_mod_I");
  QLA_I_eq_I_mod_I(&destI,&sI1,&sI4);
  CHECKeqsngII(destI,sI1%sI4,name);

  strcpy(name,"QLA_I_eq_I_max_I");
  QLA_I_eq_I_max_I(&destI,&sI2,&sI3);
  CHECKeqsngII(destI,max(sI2,sI3),name);

  strcpy(name,"QLA_I_eq_I_min_I");
  QLA_I_eq_I_min_I(&destI,&sI2,&sI3);
  CHECKeqsngII(destI,min(sI2,sI3),name);

  strcpy(name,"QLA_I_eq_I_eq_I");
  QLA_I_eq_I_eq_I(&destI,&sI1,&sI2);
  CHECKeqsngII(destI,sI1==sI2,name);

  strcpy(name,"QLA_I_eq_I_eq_I");
  QLA_I_eq_I_eq_I(&destI,&sI1,&sI1);
  CHECKeqsngII(destI,sI1==sI1,name);

  strcpy(name,"QLA_I_eq_I_ne_I");
  QLA_I_eq_I_ne_I(&destI,&sI1,&sI2);
  CHECKeqsngII(destI,sI1!=sI2,name);

  strcpy(name,"QLA_I_eq_I_ne_I");
  QLA_I_eq_I_ne_I(&destI,&sI1,&sI1);
  CHECKeqsngII(destI,sI1!=sI1,name);

  strcpy(name,"QLA_I_eq_I_gt_I");
  QLA_I_eq_I_gt_I(&destI,&sI1,&sI2);
  CHECKeqsngII(destI,sI1>sI2,name);

  strcpy(name,"QLA_I_eq_I_gt_I");
  QLA_I_eq_I_gt_I(&destI,&sI2,&sI1);
  CHECKeqsngII(destI,sI2>sI1,name);

  strcpy(name,"QLA_I_eq_I_lt_I");
  QLA_I_eq_I_lt_I(&destI,&sI1,&sI2);
  CHECKeqsngII(destI,sI1<sI2,name);

  strcpy(name,"QLA_I_eq_I_lt_I");
  QLA_I_eq_I_lt_I(&destI,&sI2,&sI1);
  CHECKeqsngII(destI,sI2<sI1,name);

  strcpy(name,"QLA_I_eq_I_ge_I");
  QLA_I_eq_I_ge_I(&destI,&sI1,&sI2);
  CHECKeqsngII(destI,sI1>=sI2,name);

  strcpy(name,"QLA_I_eq_I_ge_I");
  QLA_I_eq_I_ge_I(&destI,&sI2,&sI2);
  CHECKeqsngII(destI,sI2>=sI2,name);

  strcpy(name,"QLA_I_eq_I_le_I");
  QLA_I_eq_I_le_I(&destI,&sI1,&sI2);
  CHECKeqsngII(destI,sI1<=sI2,name);

  strcpy(name,"QLA_I_eq_I_le_I");
  QLA_I_eq_I_le_I(&destI,&sI2,&sI2);
  CHECKeqsngII(destI,sI2<=sI2,name);

  strcpy(name,"QLA_I_eq_I_or_I");
  QLA_I_eq_I_or_I(&destI,&sI1,&sI2);
  CHECKeqsngII(destI,sI1|sI2,name);

  strcpy(name,"QLA_I_eq_I_and_I");
  QLA_I_eq_I_and_I(&destI,&sI1,&sI2);
  CHECKeqsngII(destI,sI1&sI2,name);

  strcpy(name,"QLA_I_eq_I_xor_I");
  QLA_I_eq_I_xor_I(&destI,&sI1,&sI2);
  CHECKeqsngII(destI,sI1^sI2,name);

  strcpy(name,"QLA_I_eq_not_I");
  QLA_I_eq_not_I(&destI,&sI2);
  CHECKeqsngII(destI,!sI2,name);

  strcpy(name,"QLA_I_eq_I_mask_I");
  destI = sI3;
  QLA_I_eq_I_mask_I(&destI,&sI1,&sI7);
  if(sI7){CHECKeqsngII(destI,sI1,name);}
  else{CHECKeqsngII(destI,destI,name);}

  strcpy(name,"QLA_I_eq_I_mask_I");
  destI = sI3;
  QLA_I_eq_I_mask_I(&destI,&sI1,&sI6);
  if(sI6){CHECKeqsngII(destI,sI1,name);}
  else{CHECKeqsngII(destI,destI,name);}

  strcpy(name,"QLA_I_eq_zero");
  QLA_I_eq_zero(&destI);
  CHECKeqsngII(destI,0,name);

  strcpy(name,"QLA_I_eq_i");
  QLA_I_eq_i(&destI,&sI4);
  CHECKeqsngII(destI,sI4,name);

  strcpy(name,"QLA_S_eq_seed_i_I");
  QLA_S_eq_seed_i_I(&destS,sI4,&nI1);
  QLA_seed_random(&chkS,sI4,nI1);
  CHECKeqsngSS(&destS,&chkS,name);

  strcpy(name,"QLA_S_eq_S");
  QLA_S_eq_S(&destS,&chkS);
  CHECKeqsngSS(&destS,&chkS,name);

  return 0;
}

