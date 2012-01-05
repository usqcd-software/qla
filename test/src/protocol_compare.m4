define(rem,)

rem(`
----------------------------------------------------------------------
     Comparison routines for various types
----------------------------------------------------------------------
')

define(type_R,`QLA_Real')
define(type_C,`QLA_Complex')
define(type_I,`QLA_Int')
define(type_M,`QLA_ColorMatrix')
define(type_H,`QLA_HalfFermion')
define(type_D,`QLA_DiracFermion')
define(type_V,`QLA_ColorVector')
define(type_P,`QLA_DiracPropagator')

define(type_QR,`QLA_Q_Real')
define(type_QC,`QLA_Q_Complex')
define(type_QM,`QLA_Q_ColorMatrix')
define(type_QH,`QLA_Q_HalfFermion')
define(type_QD,`QLA_Q_DiracFermion')
define(type_QV,`QLA_Q_ColorVector')
define(type_QP,`QLA_Q_DiracPropagator')

define(type_DR,`QLA_D_Real')
define(type_DC,`QLA_D_Complex')
define(type_DM,`QLA_D_ColorMatrix')
define(type_DH,`QLA_D_HalfFermion')
define(type_DD,`QLA_D_DiracFermion')
define(type_DV,`QLA_D_ColorVector')
define(type_DP,`QLA_D_DiracPropagator')

define(type_FR,`QLA_F_Real')
define(type_FC,`QLA_F_Complex')
define(type_FM,`QLA_F_ColorMatrix')
define(type_FH,`QLA_F_HalfFermion')
define(type_FD,`QLA_F_DiracFermion')
define(type_FV,`QLA_F_ColorVector')
define(type_FP,`QLA_F_DiracPropagator')

define(for_M_elem, `for(ic=0;ic<nc;ic++)for(jc=0;jc<nc;jc++)')
define(for_H_elem, `for(ic=0;ic<nc;ic++)for(is=0;is<ns/2;is++)')
define(for_D_elem, `for(ic=0;ic<nc;ic++)for(is=0;is<ns;is++)')
define(for_V_elem, `for(ic=0;ic<nc;ic++)')
define(for_P_elem, `for(ic=0;ic<nc;ic++)for(is=0;is<ns;is++)\
   for(jc=0;jc<nc;jc++)for(js=0;js<ns;js++)')

define(M_list, `ic,jc')
define(H_list, `ic,is')
define(D_list, `ic,is')
define(V_list, `ic')
define(P_list, `ic,is,jc,js')

define(elem_M, `QLA_elem_M')
define(elem_H, `QLA_elem_H')
define(elem_D, `QLA_elem_D')
define(elem_V, `QLA_elem_V')
define(elem_P, `QLA_elem_P')

define(elem_QM, `QLA_Q_elem_M')
define(elem_QH, `QLA_Q_elem_H')
define(elem_QD, `QLA_Q_elem_D')
define(elem_QV, `QLA_Q_elem_V')
define(elem_QP, `QLA_Q_elem_P')

define(elem_DM, `QLA_D_elem_M')
define(elem_DH, `QLA_D_elem_H')
define(elem_DD, `QLA_D_elem_D')
define(elem_DV, `QLA_D_elem_V')
define(elem_DP, `QLA_D_elem_P')

define(elem_FM, `QLA_F_elem_M')
define(elem_FH, `QLA_F_elem_H')
define(elem_FD, `QLA_F_elem_D')
define(elem_FV, `QLA_F_elem_V')
define(elem_FP, `QLA_F_elem_P')


rem(`checkequalreal(type,prec)')
define(checkequalreal,`
int checkequal$2$1$1(type_$2$1 *sa, type_$2$1 *sb){
  double diffa = fabs(*sa-*sb);
  double avg = 0.5*(fabs(*sa)+fabs(*sb));
  if(avg==0) diff = 0;
  else diff = diffa/avg;
  checkeq1 = *sa;
  checkeq2 = *sb;
  return (diffa>TOLABS) && (diff>TOLREL);
}
')

rem(`checkequalcomplex(type,prec)')
define(checkequalcomplex,`
int checkequal$2$1$1(type_$2$1 *sa, type_$2$1 *sb){
  int status;
  type_$2R ta, tb;
  ta = QLA_real(*sa);
  tb = QLA_real(*sb);
  status = checkequal$2RR(&ta, &tb);
  if(!status) {
    ta = QLA_imag(*sa);
    tb = QLA_imag(*sb);
    status = checkequal$2RR(&ta, &tb);
  }
  return status;
}
')

rem(`checkequaltensor(type,prec)')
define(checkequaltensor,`
int checkequal$2$1$1(type_$2$1 *sa, type_$2$1 *sb){
  int $1_list,status=0;
  for_$1_elem{
    if((status = checkequal$2CC(&elem_$2$1`('*sa,$1_list`)',
			     &elem_$2$1`('*sb,$1_list`)')))break;
  }
  return status;
}
')

rem(`checkequalsng(type,prec)')
define(checkequalsng,`
int checkeqsng$2$1$1(type_$2$1 *sa, type_$2$1 *sb, char name[], FILE *fp){
  return report(checkequal$2$1$1(sa,sb),name, fp);
}
')

rem(`checkequalidx(type,prec)')
define(checkequalidx,`
int checkeqidx$2$1$1(type_$2$1 sa[], type_$2$1 sb[], char name[], FILE *fp){
  int i,status=0;
  for(i = 0; i < MAX; i++){
    if((status = checkequal$2$1$1(&sa[i],&sb[i])))break;
  }
  return report(status,name, fp);
}
')
