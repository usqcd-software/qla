define(rem,)
rem(`
----------------------------------------------------------------------
     Test protocol include file for all indexed routines
----------------------------------------------------------------------
')

include(tensor_args.m4)

rem(`
     For resetting values of test fields
')
define(resetdt,`QLA_$1_veq_$1(argd($1),arg3($1),MAX);
  QLA_$1_veq_$1(argt($1),arg3($1),MAX);')

define(resetdtQ,`
  for(i = 0; i < MAX; i++){
     argdQ($1)[i] = arg3Q($1)[i];
     argtQ($1)[i] = arg3Q($1)[i];
  }
')

define(resetdtD,`QLA_D_$1_veq_$1(argdD($1),arg3D($1),MAX);
  QLA_D_$1_veq_$1(argtD($1),arg3D($1),MAX);')

define(resetdtF,`QLA_F_$1_veq_$1(argdF($1),arg3F($1),MAX);
  QLA_F_$1_veq_$1(argtF($1),arg3F($1),MAX);')

rem(`
     Create random long double array
')
rem(`makeGaussianQarray(t1,name)')
define(makeGaussianQarray,`
  for(i = 0; i < MAX; i++){
    for_$1_elem{
      arg1Q(R) = (QLA_Q_Real)QLA_gaussian(&sS1[i])/3.;
      arg1Q(R) = (QLA_Q_Real)QLA_gaussian(&sS1[i])/3.;
      QLA_c_eq_r_plus_ir($1_elem($2[i]),arg1Q(R),arg2Q(R));
    }
  }
')


rem(`
     Unary set zero
')
rem(`qla_name0(pd,td,pe,eq)')
define(qla_name0,QLA_$1$2_$3$4)

rem(`unaryconstzero(td,eq)')
define(unaryconstzero,`
  /* qla_name0(,$1,,$2) */

  strcpy(name,"qla_name0(,$1,v,$2)");
  resetdt($1)
  qla_name0(,$1,v,$2)(argd($1),MAX);
  for(i = 0; i < MAX; i++){qla_name0(,$1,,$2)(&argt($1)[i]);}
  checkeqidx$1$1(argt($1),argd($1),name,fp);

  strcpy(name,"qla_name0(,$1,x,$2)");
  resetdt($1)
  qla_name0(,$1,x,$2)(argd($1),idxd($1),MAX);
  for(i = 0; i < MAX; i++){qla_name0(,$1,,$2)(&argt($1)[idxd($1)[i]]);}
  checkeqidx$1$1(argt($1),argd($1),name,fp);

')

rem(`
     Unary set const
')
rem(`unaryconst(td,eq)')
define(unaryconst,`/* qla_name0(,$1,,$2) */

  strcpy(name,"qla_name0(,$1,v,$2)");
  resetdt($1)
  qla_name0(,$1,v,$2)(argd($1),&arg4($1),MAX);
  for(i = 0; i < MAX; i++){qla_name0(,$1,,$2)(&argt($1)[i],&arg4($1));}
  checkeqidx$1$1(argt($1),argd($1),name,fp);

  strcpy(name,"qla_name0(,$1,x,$2)");
  resetdt($1)
  qla_name0(,$1,x,$2)(argd($1),&arg4($1),idxd($1),MAX);
  for(i = 0; i < MAX; i++){qla_name0(,$1,,$2)(&argt($1)[idxd($1)[i]],&arg4($1));}
  checkeqidx$1$1(argt($1),argd($1),name,fp);

')

rem(`
     Unary set diag const
')
rem(`unarydiagconst(td,eq)')
define(unarydiagconst,`/* qla_name0(,$1,,$2) */

  strcpy(name,"qla_name0(,$1,v,$2)");
  resetdt($1)
  qla_name0(,$1,v,$2)(argd($1),&arg4(C),MAX);
  for(i = 0; i < MAX; i++){qla_name0(,$1,,$2)(&argt($1)[i],&arg4(C));}
  checkeqidx$1$1(argt($1),argd($1),name,fp);

  strcpy(name,"qla_name0(,$1,x,$2)");
  resetdt($1)
  qla_name0(,$1,x,$2)(argd($1),&arg4(C),idxd($1),MAX);
  for(i = 0; i < MAX; i++){qla_name0(,$1,,$2)(&argt($1)[idxd($1)[i]],&arg4(C));}
  checkeqidx$1$1(argt($1),argd($1),name,fp);

')

rem(`
     Squared norm for complex and tensors (uniform precision)
')

rem(`qla_name1_spec(pd,td,pe,eq,p1,t1,spec)')
define(qla_name1_spec,`QLA$7_$1$2_$3$4_$5$6')

rem(`unaryglobalnorm2(td,eq,t1,spec,precd,prec1)')
define(unaryglobalnorm2,`
  /* qla_name1_spec(,$1,,$2,,$3,$4) */

  strcpy(name,"qla_name1_spec(,$1,v,$2,,$3,$4)");
  qla_name1_spec(,$1,v,$2,,$3,$4)(&argd$5($1),arg2$6($3),MAX);
  /* Accumulate in long double precision */
  argtQ($1)=0; 
  for(i=0;i<MAX;i++){
    for_$3_elem{
      argtQ($1) += QLA_norm2_c($3_elem(arg2$6($3)[i],$3_list));
    }
  }
  argt$5($1) = argtQ($1);
  checkeqsng$5RR(&argd$5($1),&argt$5($1),name,fp);

  strcpy(name,"qla_name1_spec(,$1,x,$2,,$3,$4)");
  qla_name1_spec(,$1,x,$2,,$3,$4)(&argd$5($1),arg2$6($3),idx2($3),MAX);
  /* Accumulate in long double precision */
  argtQ($1)=0;
  for(i=0;i<MAX;i++){
    for_$3_elem{
      argtQ($1) += QLA_norm2_c($3_elem(arg2$6($3)[idx2($3)[i]],$3_list));
    }
  }
  argt$5($1) = argtQ($1);
  checkeqsng$5RR(&argd$5($1),&argt$5($1),name,fp);

  strcpy(name,"qla_name1_spec(,$1,v,$2,p,$3,$4)");
  qla_name1_spec(,$1,v,$2,p,$3,$4)(&argd$5($1),arg2$6p($3),MAX);
  /* Accumulate in long double precision */
  argtQ($1)=0;
  for(i=0;i<MAX;i++){
    for_$3_elem{
      argtQ($1) += QLA_norm2_c($3_elem(*arg2$6p($3)[i],$3_list));
    }
  }
  argt$5($1) = argtQ($1);
  checkeqsng$5RR(&argd$5($1),&argt$5($1),name,fp);

  strcpy(name,"qla_name1_spec(,$1,x,$2,p,$3,$4)");
  qla_name1_spec(,$1,x,$2,p,$3,$4)(&argd$5($1),arg2$6p($3),idx2($3),MAX);
  /* Accumulate in long double precision */
  argtQ($1)=0;
  for(i=0;i<MAX;i++){
    for_$3_elem{
      argtQ($1) += QLA_norm2_c($3_elem(*arg2$6p($3)[idx2($3)[i]],$3_list));
    }
  }
  argt$5($1) = argtQ($1);
  checkeqsng$5RR(&argd$5($1),&argt$5($1),name,fp);

')

rem(`
     Squared norm for reals
')
rem(`unaryglobalnorm2real(td,eq,t1,spec,precd,prec1)')
define(unaryglobalnorm2real,`/* qla_name1_spec(,$1,,$2,,$3,$4) */

  strcpy(name,"qla_name1_spec(,$1,v,$2,,$3,$4)");
  qla_name1_spec(,$1,v,$2,,$3,$4)(&argd$5($1),arg2$6($3),MAX);
  argtQ($1)=0; 
  for(i=0;i<MAX;i++)argtQ($1) += arg2$6($3)[i]*arg2$6($3)[i];
  argt$5($1) = argtQ($1);
  checkeqsng$5RR(&argd$5($1),&argt$5($1),name,fp);

  strcpy(name,"qla_name1_spec(,$1,x,$2,,$3,$4)");
  qla_name1_spec(,$1,x,$2,,$3,$4)(&argd$5($1),arg2$6($3),idx2($3),MAX);
  argtQ($1)=0;
  for(i=0;i<MAX;i++)argtQ($1) += arg2$6($3)[idx2($3)[i]]*arg2$6($3)[idx2($3)[i]];
  argt$5($1) = argtQ($1);
  checkeqsng$5RR(&argd$5($1),&argt$5($1),name,fp);

  strcpy(name,"qla_name1_spec(,$1,v,$2,p,$3,$4)");
  qla_name1_spec(,$1,v,$2,p,$3,$4)(&argd$5($1),arg2$6p($3),MAX);
  argtQ($1)=0;
  for(i=0;i<MAX;i++)argtQ($1) += (*arg2$6p($3)[i])*(*arg2$6p($3)[i]);
  argt$5($1) = argtQ($1);
  checkeqsng$5RR(&argd$5($1),&argt$5($1),name,fp);

  strcpy(name,"qla_name1_spec(,$1,x,$2,p,$3,$4)");
  qla_name1_spec(,$1,x,$2,p,$3,$4)(&argd$5($1),arg2$6p($3),idx2($3),MAX);
  argtQ($1)=0;
  for(i=0;i<MAX;i++)argtQ($1) += (*arg2$6p($3)[idx2($3)[i]])*(*arg2$6p($3)[idx2($3)[i]]);
  argt$5($1) = argtQ($1);
  checkeqsng$5RR(&argd$5($1),&argt$5($1),name,fp);

')

rem(`
     Unary sum for tensors
')
rem(`unarysum(td,eq,t1,spec,precd,prec1)')
define(unarysum,`/* qla_name1_spec(,$1,,$2,,$3,$4) */

  strcpy(name,"qla_name1_spec(,$1,v,$2,,$3,$4)");
  qla_name1_spec(,$1,v,$2,,$3,$4)(&argd$5($1),arg2$6($3),MAX);
  /* Copy arg2$6($3) to argtQ($3) for long double precision accumulation */
  for(i=0;i<MAX;i++){
    for_$3_elem{
      QLA_c_eq_c($3_elem(argtQ($3)[i],$3_list),$3_elem(arg2$6($3)[i],$3_list));
    }
  }
  /* Accumulate argtQ($3) in argtQ($1) */
  for_$3_elem{
     QLA_c_eq_r($3_elem(argtQ($1),$3_list),0.);
  }
  for(i=0;i<MAX;i++){
    for_$3_elem{
       QLA_c_peq_c($3_elem(argtQ($1),$3_list),$3_elem(argtQ($3)[i],$3_list));
    }
  }
  /* Copy argtQ($1) to argt$5($1) for comparison */
  for_$3_elem{
    QLA_c_eq_c($3_elem(argt$5($1),$3_list),$3_elem(argtQ($1),$3_list));
  }
  checkeqsng$5$3$3(&argd$5($1),&argt$5($1),name,fp);

  strcpy(name,"qla_name1_spec(,$1,x,$2,,$3,$4)");
  qla_name1_spec(,$1,x,$2,,$3,$4)(&argd$5($1),arg2$6($3),idx1($3),MAX);
  /* Copy arg2$6($3) to argtQ($3) for long double precision accumulation */
  for(i=0;i<MAX;i++){
    for_$3_elem{
      QLA_c_eq_c($3_elem(argtQ($3)[i],$3_list),$3_elem(arg2$6($3)[idx1($3)[i]],$3_list));
    }
  }
  /* Accumulate argtQ($3) in argtQ($1) */
  for_$3_elem{
     QLA_c_eq_r($3_elem(argtQ($1),$3_list),0.);
  }
  for(i=0;i<MAX;i++){
    for_$3_elem{
       QLA_c_peq_c($3_elem(argtQ($1),$3_list),$3_elem(argtQ($3)[i],$3_list));
    }
  }
  /* Copy argtQ($1) to argt$5($1) for comparison */
  for_$3_elem{
    QLA_c_eq_c($3_elem(argt$5($1),$3_list),$3_elem(argtQ($1),$3_list));
  }
  checkeqsng$5$3$3(&argd$5($1),&argt$5($1),name,fp);

  strcpy(name,"qla_name1_spec(,$1,v,$2,p,$3,$4)");
  qla_name1_spec(,$1,v,$2,p,$3,$4)(&argd$5($1),arg2$6p($3),MAX);
  /* Copy arg2$6($3) to argtQ($3) for long double precision accumulation */
  for(i=0;i<MAX;i++){
    for_$3_elem{
      QLA_c_eq_c($3_elem(argtQ($3)[i],$3_list),$3_elem(*arg2$6p($3)[i],$3_list));
    }
  }
  /* Accumulate argtQ($3) in argtQ($1) */
  for_$3_elem{
     QLA_c_eq_r($3_elem(argtQ($1),$3_list),0.);
  }
  for(i=0;i<MAX;i++){
    for_$3_elem{
       QLA_c_peq_c($3_elem(argtQ($1),$3_list),$3_elem(argtQ($3)[i],$3_list));
    }
  }
  /* Copy argtQ($1) to argt$5($1) for comparison */
  for_$3_elem{
    QLA_c_eq_c($3_elem(argt$5($1),$3_list),$3_elem(argtQ($1),$3_list));
  }
  checkeqsng$5$3$3(&argd$5($1),&argt$5($1),name,fp);

  strcpy(name,"qla_name1_spec(,$1,x,$2,p,$3,$4)");
  qla_name1_spec(,$1,x,$2,p,$3,$4)(&argd$5($1),arg2$6p($3),idx1($3),MAX);
  /* Copy arg2$6($3) to argtQ($3) for long double precision accumulation */
  for(i=0;i<MAX;i++){
    for_$3_elem{
      QLA_c_eq_c($3_elem(argtQ($3)[i],$3_list),$3_elem(*arg2$6p($3)[idx1($3)[i]],$3_list));
    }
  }
  /* Accumulate argtQ($3) in argtQ($1) */
  for_$3_elem{
     QLA_c_eq_r($3_elem(argtQ($1),$3_list),0.);
  }
  for(i=0;i<MAX;i++){
    for_$3_elem{
       QLA_c_peq_c($3_elem(argtQ($1),$3_list),$3_elem(argtQ($3)[i],$3_list));
    }
  }
  /* Copy argtQ($1) to argt$5($1) for comparison */
  for_$3_elem{
    QLA_c_eq_c($3_elem(argt$5($1),$3_list),$3_elem(argtQ($1),$3_list));
  }
  checkeqsng$5$3$3(&argd$5($1),&argt$5($1),name,fp);
')

rem(`
     Unary sum for reals
')
rem(`unarysumreal(td,eq,t1,spec,precd,prec1)')
define(unarysumreal,`/* qla_name1_spec(,$1,,$2,,$3,$4) */

  strcpy(name,"qla_name1_spec(,$1,v,$2,,$3,$4)");
  qla_name1_spec(,$1,v,$2,,$3,$4)(&argd$5($1),arg2$6($3),MAX);
  argtQ($1) = 0;
  for(i=0;i<MAX;i++)argtQ($1) += arg2$6($3)[i];
  argt$5($1) = argtQ($1);
  checkeqsng$5RR(&argd$5($1),&argt$5($1),name,fp);

  strcpy(name,"qla_name1_spec(,$1,x,$2,,$3,$4)");
  qla_name1_spec(,$1,x,$2,,$3,$4)(&argd$5($1),arg2$6($3),idx1($3),MAX);
  argtQ($1) = 0;
  for(i=0;i<MAX;i++)argtQ($1) += arg2$6($3)[idx1($3)[i]];
  argt$5($1) = argtQ($1);
  checkeqsng$5RR(&argd$5($1),&argt$5($1),name,fp);

  strcpy(name,"qla_name1_spec(,$1,v,$2,p,$3,$4)");
  qla_name1_spec(,$1,v,$2,p,$3,$4)(&argd$5($1),arg2$6p($3),MAX);
  argtQ($1) = 0;
  for(i=0;i<MAX;i++)argtQ($1) += *arg2$6p($3)[i];
  argt$5($1) = argtQ($1);
  checkeqsng$5RR(&argd$5($1),&argt$5($1),name,fp);

  strcpy(name,"qla_name1_spec(,$1,x,$2,p,$3,$4)");
  qla_name1_spec(,$1,x,$2,p,$3,$4)(&argd$5($1),arg2$6p($3),idx1($3),MAX);
  argtQ($1) = 0;
  for(i=0;i<MAX;i++)argtQ($1) += *arg2$6p($3)[idx1($3)[i]];
  argt$5($1) = argtQ($1);
  checkeqsng$5RR(&argd$5($1),&argt$5($1),name,fp);
')

rem(`
     Unary sum for integers
')
rem(`unarysumint(td,eq,t1)')
rem(`qla_name1_spec(pd,td,pe,eq,p1,t1,spec)')
define(qla_name_spec,`QLA$7_$1$2_$3$4_$5$6')

rem(`qla_name1(pd,td,pe,eq,p1,t1)')
define(qla_name1,`QLA_$1$2_$3$4_$5$6')

define(unarysumint,`/* qla_name1(,$1,,$2,,$3) */

  strcpy(name,"qla_name1(,$1,v,$2,,$3)");
  qla_name1(,$1,v,$2,,$3)(&argd($1),arg2($3),MAX);
  argt($1) = 0;
  for(i=0;i<MAX;i++)QLA_$3_peq_$3(&argt($1),&arg2($3)[i]);
  checkeqsng$3$3(&argd($1),&argt($1),name,fp);

  strcpy(name,"qla_name1(,$1,x,$2,,$3)");
  qla_name1(,$1,x,$2,,$3)(&argd($1),arg2($3),idx1($3),MAX);
  argt($1) = 0;
  for(i=0;i<MAX;i++)QLA_$3_peq_$3(&argt($1),&arg2($3)[i]);
  checkeqsng$3$3(&argd($1),&argt($1),name,fp);

  strcpy(name,"qla_name1(,$1,v,$2,p,$3)");
  qla_name1(,$1,v,$2,p,$3)(&argd($1),arg2p($3),MAX);
  argt($1) = 0;
  for(i=0;i<MAX;i++)QLA_$3_peq_$3(&argt($1),&arg2($3)[i]);
  checkeqsng$3$3(&argd($1),&argt($1),name,fp);

  strcpy(name,"qla_name1(,$1,x,$2,p,$3)");
  qla_name1(,$1,x,$2,p,$3)(&argd($1),arg2p($3),idx1($3),MAX);
  argt($1) = 0;
  for(i=0;i<MAX;i++)QLA_$3_peq_$3(&argt($1),&arg2($3)[i]);
  checkeqsng$3$3(&argd($1),&argt($1),name,fp);
')

rem(`
     Seed random number generators
')
rem(`unaryseed(td,eq,t1)')
define(unaryseed,`
  /* qla_name1(,$1,,$2,,$3) */

  strcpy(name,"qla_name1(,$1,v,$2,,$3)");
  qla_name1(,$1,v,$2,,$3)(argd($1),arg4($3),nI1,MAX);
  for(i = 0; i < MAX; i++)qla_name1(,$1,,$2,,$3)(&argt($1)[i],arg4($3),&nI1[i]);
  checkeqidx$1$1(argt($1),argd($1),name,fp);

  strcpy(name,"qla_name1(,$1,x,$2,,$3)");
  qla_name1(,$1,x,$2,,$3)(argd($1),arg4($3),nI1,idx1($3),MAX);
  for(i = 0; i < MAX; i++)qla_name1(,$1,,$2,,$3)(&argt($1)[idx1($3)[i]],arg4($3),&nI1[idx1($3)[i]]);
  checkeqidx$1$1(argt($1),argd($1),name,fp);

#ifdef QLA_INDEX_ALL
  strcpy(name,"qla_name1(x,$1,,$2,,$3)");
  qla_name1(x,$1,,$2,,$3)(argd($1),idxd($1),arg4($3),nI1,MAX);
  for(i = 0; i < MAX; i++)qla_name1(,$1,,$2,,$3)(&argt($1)[idxd($1)[i]],arg4($3),&nI1[i]);
  checkeqidx$1$1(argt($1),argd($1),name,fp);

  strcpy(name,"qla_name1(,$1,,$2,x,$3)");
  qla_name1(,$1,,$2,x,$3)(argd($1),arg4($3),nI1,idx1($3),MAX);
  for(i = 0; i < MAX; i++)qla_name1(,$1,,$2,,$3)(&argt($1)[i],arg4($3),&nI1[idx1($3)[i]]);
  checkeqidx$1$1(argt($1),argd($1),name,fp);

  strcpy(name,"qla_name1(x,$1,,$2,x,$3)");
  qla_name1(x,$1,,$2,x,$3)(argd($1),idxd($1),arg4($3),nI1,idx1($3),MAX);
  for(i = 0; i < MAX; i++)qla_name1(,$1,,$2,,$3)(&argt($1)[idxd($1)[i]],arg4($3),&nI1[idx1($3)[i]]);
  checkeqidx$1$1(argt($1),argd($1),name,fp);
#endif

  strcpy(name,"qla_name1(,$1,v,$2,p,$3)");
  qla_name1(,$1,v,$2,p,$3)(argd($1),arg4($3),nI1p,MAX);
  for(i = 0; i < MAX; i++)qla_name1(,$1,,$2,,$3)(&argt($1)[i],arg4($3),nI1p[i]);
  checkeqidx$1$1(argt($1),argd($1),name,fp);

  strcpy(name,"qla_name1(,$1,x,$2,p,$3)");
  qla_name1(,$1,x,$2,p,$3)(argd($1),arg4($3),nI1p,idx1($3),MAX);
  for(i = 0; i < MAX; i++)qla_name1(,$1,,$2,,$3)(&argt($1)[idx1($3)[i]],arg4($3),nI1p[idx1($3)[i]]);
  checkeqidx$1$1(argt($1),argd($1),name,fp);

')

rem(`
     Random number generation
')
rem(`unaryrand(td,eq)')
define(unaryrand,`
  /* qla_name1(,$1,,$2,,S) */

  QLA_S_veq_seed_i_I(arg1(S),arg4(I),nI1,MAX);
  strcpy(name,"qla_name1(,$1,v,$2,,S)");
  qla_name1(,$1,v,$2,,S)(argd($1),arg1(S),MAX);
  QLA_S_veq_seed_i_I(arg1(S),arg4(I),nI1,MAX);
  for(i = 0; i < MAX; i++)qla_name1(,$1,,$2,,S)(&argt($1)[i],&arg1(S)[i]);
  checkeqidx$1$1(argt($1),argd($1),name,fp);

  QLA_S_veq_seed_i_I(arg1(S),arg4(I),nI1,MAX);
  strcpy(name,"qla_name1(,$1,x,$2,,S)");
  qla_name1(,$1,x,$2,,S)(argd($1),arg1(S),idx1(S),MAX);
  QLA_S_veq_seed_i_I(arg1(S),arg4(I),nI1,MAX);
  for(i = 0; i < MAX; i++)qla_name1(,$1,,$2,,S)(&argt($1)[idx1(S)[i]],&arg1(S)[idx1(S)[i]]);
  checkeqidx$1$1(argt($1),argd($1),name,fp);

#ifdef QLA_INDEX_ALL
  QLA_S_veq_seed_i_I(arg1(S),arg4(I),nI1,MAX);
  strcpy(name,"qla_name1(x,$1,,$2,,S)");
  qla_name1(x,$1,,$2,,S)(argd($1),idxd($1),arg1(S),MAX);
  QLA_S_veq_seed_i_I(arg1(S),arg4(I),nI1,MAX);
  for(i = 0; i < MAX; i++)qla_name1(,$1,,$2,,S)(&argt($1)[idxd($1)[i]],&arg1(S)[i]);
  checkeqidx$1$1(argt($1),argd($1),name,fp);

  QLA_S_veq_seed_i_I(arg1(S),arg4(I),nI1,MAX);
  strcpy(name,"qla_name1(,$1,,$2,x,S)");
  qla_name1(,$1,,$2,x,S)(argd($1),arg1(S),idx1(S),MAX);
  QLA_S_veq_seed_i_I(arg1(S),arg4(I),nI1,MAX);
  for(i = 0; i < MAX; i++)qla_name1(,$1,,$2,,S)(&argt($1)[i],&arg1(S)[idx1(S)[i]]);
  checkeqidx$1$1(argt($1),argd($1),name,fp);

  QLA_S_veq_seed_i_I(arg1(S),arg4(I),nI1,MAX);
  strcpy(name,"qla_name1(x,$1,,$2,x,S)");
  qla_name1(x,$1,,$2,x,S)(argd($1),idxd($1),arg1(S),idx1(S),MAX);
  QLA_S_veq_seed_i_I(arg1(S),arg4(I),nI1,MAX);
  for(i = 0; i < MAX; i++)qla_name1(,$1,,$2,,S)(&argt($1)[idxd($1)[i]],&arg1(S)[idx1(S)[i]]);
  checkeqidx$1$1(argt($1),argd($1),name,fp);
#endif

  QLA_S_veq_seed_i_I(arg1(S),arg4(I),nI1,MAX);
  strcpy(name,"qla_name1(,$1,v,$2,p,S)");
  qla_name1(,$1,v,$2,p,S)(argd($1),arg1p(S),MAX);
  QLA_S_veq_seed_i_I(arg1(S),arg4(I),nI1,MAX);
  for(i = 0; i < MAX; i++)qla_name1(,$1,,$2,,S)(&argt($1)[i],arg1p(S)[i]);
  checkeqidx$1$1(argt($1),argd($1),name,fp);

  QLA_S_veq_seed_i_I(arg1(S),arg4(I),nI1,MAX);
  strcpy(name,"qla_name1(,$1,x,$2,p,S)");
  qla_name1(,$1,x,$2,p,S)(argd($1),arg1p(S),idx1(S),MAX);
  QLA_S_veq_seed_i_I(arg1(S),arg4(I),nI1,MAX);
  for(i = 0; i < MAX; i++)qla_name1(,$1,,$2,,S)(&argt($1)[idx1(S)[i]],arg1p(S)[idx1(S)[i]]);
  checkeqidx$1$1(argt($1),argd($1),name,fp);

')


rem(`
     Generic unary operation
')
rem(`unarygen(td,eq,t1)')
define(unarygen,`
  /* qla_name1(,$1,,$2,,$3) */

  strcpy(name,"qla_name1(,$1,v,$2,,$3)");
  resetdt($1)
  qla_name1(,$1,v,$2,,$3)(argd($1),arg1($3),MAX);
  for(i = 0; i < MAX; i++){qla_name1(,$1,,$2,,$3)(&argt($1)[i],&arg1($3)[i]);}
  checkeqidx$1$1(argt($1),argd($1),name,fp);

  strcpy(name,"qla_name1(,$1,x,$2,,$3)");
  resetdt($1)
  qla_name1(,$1,x,$2,,$3)(argd($1),arg1($3),idx1($3),MAX);
  for(i = 0; i < MAX; i++){qla_name1(,$1,,$2,,$3)(&argt($1)[idx1($3)[i]],&arg1($3)[idx1($3)[i]]);}
  checkeqidx$1$1(argt($1),argd($1),name,fp);

#ifdef QLA_INDEX_ALL
  strcpy(name,"qla_name1(x,$1,,$2,,$3)");
  resetdt($1)
  qla_name1(x,$1,,$2,,$3)(argd($1),idxd($1),arg1($3),MAX);
  for(i = 0; i < MAX; i++){qla_name1(,$1,,$2,,$3)(&argt($1)[idxd($1)[i]],&arg1($3)[i]);}
  checkeqidx$1$1(argt($1),argd($1),name,fp);

  strcpy(name,"qla_name1(,$1,,$2,x,$3)");
  resetdt($1)
  qla_name1(,$1,,$2,x,$3)(argd($1),arg1($3),idx1($3),MAX);
  for(i = 0; i < MAX; i++){qla_name1(,$1,,$2,,$3)(&argt($1)[i],&arg1($3)[idx1($3)[i]]);}
  checkeqidx$1$1(argt($1),argd($1),name,fp);

  strcpy(name,"qla_name1(x,$1,,$2,x,$3)");
  resetdt($1)
  qla_name1(x,$1,,$2,x,$3)(argd($1),idxd($1),arg1($3),idx1($3),MAX);
  for(i = 0; i < MAX; i++){qla_name1(,$1,,$2,,$3)(&argt($1)[idxd($1)[i]],&arg1($3)[idx1($3)[i]]);}
  checkeqidx$1$1(argt($1),argd($1),name,fp);
#endif

  strcpy(name,"qla_name1(,$1,v,$2,p,$3)");
  resetdt($1)
  qla_name1(,$1,v,$2,p,$3)(argd($1),arg1p($3),MAX);
  for(i = 0; i < MAX; i++){qla_name1(,$1,,$2,,$3)(&argt($1)[i],arg1p($3)[i]);}
  checkeqidx$1$1(argt($1),argd($1),name,fp);

  strcpy(name,"qla_name1(,$1,x,$2,p,$3)");
  resetdt($1)
  qla_name1(,$1,x,$2,p,$3)(argd($1),arg1p($3),idx1($3),MAX);
  for(i = 0; i < MAX; i++){qla_name1(,$1,,$2,,$3)(&argt($1)[idx1($3)[i]],arg1p($3)[idx1($3)[i]]);}
  checkeqidx$1$1(argt($1),argd($1),name,fp);

')

rem(`unary_spec(td,eq,t1,spec,precd,prec1)')
define(unary_spec,`
  /* qla_name1_spec(,$1,,$2,,$3,$4) */

  strcpy(name,"qla_name1_spec(,$1,v,$2,,$3,$4)");
  resetdt$5($1)
  qla_name1_spec(,$1,v,$2,,$3,$4)(argd$5($1),arg1$6($3),MAX);
  for(i = 0; i < MAX; i++){qla_name1_spec(,$1,,$2,,$3,$4)(&argt$5($1)[i],&arg1$6($3)[i]);}
  checkeqidx$5$1$1(argd$5($1),argt$5($1),name,fp);

  strcpy(name,"qla_name1_spec(,$1,x,$2,,$3,$4)");
  resetdt$5($1)
  qla_name1_spec(,$1,x,$2,,$3,$4)(argd$5($1),arg1$6($3),idx1($3),MAX);
  for(i = 0; i < MAX; i++){qla_name1_spec(,$1,,$2,,$3,$4)(&argt$5($1)[idx1($3)[i]],&arg1$6($3)[idx1($3)[i]]);}
  checkeqidx$5$1$1(argd$5($1),argt$5($1),name,fp);

#ifdef QLA_INDEX_ALL
  strcpy(name,"qla_name1_spec(x,$1,,$2,,$3,$4)");
  resetdt$5($1)
  qla_name1_spec(x,$1,,$2,,$3,$4)(argd$5($1),idxd($1),arg1$6($3),MAX);
  for(i = 0; i < MAX; i++){qla_name1_spec(,$1,,$2,,$3,$4)(&argt$5($1)[idxd($1)[i]],&arg1$6($3)[i]);}
  checkeqidx$5$1$1(argd$5($1),argt$5($1),name,fp);

  strcpy(name,"qla_name1_spec(,$1,,$2,x,$3,$4)");
  resetdt$5($1)
  qla_name1_spec(,$1,,$2,x,$3,$4)(argd$5($1),arg1$6($3),idx1($3),MAX);
  for(i = 0; i < MAX; i++){qla_name1_spec(,$1,,$2,,$3,$4)(&argt$5($1)[i],&arg1$6($3)[idx1($3)[i]]);}
  checkeqidx$5$1$1(argd$5($1),argt$5($1),name,fp);

  strcpy(name,"qla_name1_spec(x,$1,,$2,x,$3,$4)");
  resetdt$5($1)
  qla_name1_spec(x,$1,,$2,x,$3,$4)(argd$5($1),idxd($1),arg1$6($3),idx1($3),MAX);
  for(i = 0; i < MAX; i++){qla_name1_spec(,$1,,$2,,$3,$4)(&argt$5($1)[idxd($1)[i]],&arg1$6($3)[idx1($3)[i]]);}
  checkeqidx$5$1$1(argd$5($1),argt$5($1),name,fp);
#endif

  strcpy(name,"qla_name1_spec(,$1,v,$2,p,$3,$4)");
  resetdt$5($1)
  qla_name1_spec(,$1,v,$2,p,$3,$4)(argd$5($1),arg1$6p($3),MAX);
  for(i = 0; i < MAX; i++){qla_name1_spec(,$1,,$2,,$3,$4)(&argt$5($1)[i],arg1$6p($3)[i]);}
  checkeqidx$5$1$1(argd$5($1),argt$5($1),name,fp);

  strcpy(name,"qla_name1_spec(,$1,x,$2,p,$3,$4)");
  resetdt$5($1)
  qla_name1_spec(,$1,x,$2,p,$3,$4)(argd$5($1),arg1$6p($3),idx1($3),MAX);
  for(i = 0; i < MAX; i++){qla_name1_spec(,$1,,$2,,$3,$4)(&argt$5($1)[idx1($3)[i]],arg1$6p($3)[idx1($3)[i]]);}
  checkeqidx$5$1$1(argd$5($1),argt$5($1),name,fp);

')

rem(`
     Generic unary operation
')
rem(`unary(td,eq,t1)')
define(unary,`unary_spec($1,$2,$3,,,)')


rem(`
     Unary Adjoint
')
rem(`unarya(td,eq,t1)')
define(unarya,`
  /* qla_name1(,$1,,$2,,$3a) */

  strcpy(name,"qla_name1(,$1,v,$2,,$3a)");
  resetdt($1)
  qla_name1(,$1,v,$2,,$3a)(argd($1),arg1($3),MAX);
  for(i = 0; i < MAX; i++){qla_name1(,$1,,$2,,$3a)(&argt($1)[i],&arg1($3)[i]);}
  checkeqidx$1$1(argt($1),argd($1),name,fp);

  strcpy(name,"qla_name1(,$1,x,$2,,$3a)");
  resetdt($1)
  qla_name1(,$1,x,$2,,$3a)(argd($1),arg1($3),idx1($3),MAX);
  for(i = 0; i < MAX; i++){qla_name1(,$1,,$2,,$3a)(&argt($1)[idx1($3)[i]],&arg1($3)[idx1($3)[i]]);}
  checkeqidx$1$1(argt($1),argd($1),name,fp);

#ifdef QLA_INDEX_ALL
  strcpy(name,"qla_name1(x,$1,,$2,,$3a)");
  resetdt($1)
  qla_name1(x,$1,,$2,,$3a)(argd($1),idxd($1),arg1($3),MAX);
  for(i = 0; i < MAX; i++){qla_name1(,$1,,$2,,$3a)(&argt($1)[idxd($1)[i]],&arg1($3)[i]);}
  checkeqidx$1$1(argt($1),argd($1),name,fp);

  strcpy(name,"qla_name1(,$1,,$2,x,$3a)");
  resetdt($1)
  qla_name1(,$1,,$2,x,$3a)(argd($1),arg1($3),idx1($3),MAX);
  for(i = 0; i < MAX; i++){qla_name1(,$1,,$2,,$3a)(&argt($1)[i],&arg1($3)[idx1($3)[i]]);}
  checkeqidx$1$1(argt($1),argd($1),name,fp);

  strcpy(name,"qla_name1(x,$1,,$2,x,$3a)");
  resetdt($1)
  qla_name1(x,$1,,$2,x,$3a)(argd($1),idxd($1),arg1($3),idx1($3),MAX);
  for(i = 0; i < MAX; i++){qla_name1(,$1,,$2,,$3a)(&argt($1)[idxd($1)[i]],&arg1($3)[idx1($3)[i]]);}
  checkeqidx$1$1(argt($1),argd($1),name,fp);
#endif

  strcpy(name,"qla_name1(,$1,v,$2,p,$3a)");
  resetdt($1)
  qla_name1(,$1,v,$2,p,$3a)(argd($1),arg1p($3),MAX);
  for(i = 0; i < MAX; i++){qla_name1(,$1,,$2,,$3a)(&argt($1)[i],arg1p($3)[i]);}
  checkeqidx$1$1(argt($1),argd($1),name,fp);

  strcpy(name,"qla_name1(,$1,x,$2,p,$3a)");
  resetdt($1)
  qla_name1(,$1,x,$2,p,$3a)(argd($1),arg1p($3),idx1($3),MAX);
  for(i = 0; i < MAX; i++){qla_name1(,$1,,$2,,$3a)(&argt($1)[idx1($3)[i]],arg1p($3)[idx1($3)[i]]);}
  checkeqidx$1$1(argt($1),argd($1),name,fp);

')


rem(`
     Unary long double to double
')
rem(`qla_name1DQ(pd,td,pe,eq,p1,t1)')
define(qla_name1DQ,`QLA_DQ_$1$2_$3$4_$5$6')

rem(`unaryDQ(td,eq,t1)')
define(unaryDQ,`
  /* qla_nameDQ1(,$1,,$2,,$3) */

  strcpy(name,"qla_name1DQ(,$1,v,$2,,$3)");
  resetdtD($1)
  qla_name1DQ(,$1,v,$2,,$3)(argdD($1),arg1Q($3),MAX);
  for(i = 0; i < MAX; i++){qla_name1DQ(,$1,,$2,,$3)(&argtD($1)[i],&arg1Q($3)[i]);}
  checkeqidxD$1$1(argtD($1),argdD($1),name,fp);

  strcpy(name,"qla_name1DQ(,$1,x,$2,,$3)");
  resetdtD($1)
  qla_name1DQ(,$1,x,$2,,$3)(argdD($1),arg1Q($3),idx1($3),MAX);
  for(i = 0; i < MAX; i++){qla_name1DQ(,$1,,$2,,$3)(&argtD($1)[idx1($3)[i]],&arg1Q($3)[idx1($3)[i]]);}
  checkeqidxD$1$1(argtD($1),argdD($1),name,fp);

#ifdef QLA_INDEX_ALL
  strcpy(name,"qla_name1DQ(x,$1,,$2,,$3)");
  resetdtD($1)
  qla_name1DQ(x,$1,,$2,,$3)(argdD($1),idxd($1),arg1Q($3),MAX);
  for(i = 0; i < MAX; i++){qla_name1DQ(,$1,,$2,,$3)(&argtD($1)[idxd($1)[i]],&arg1Q($3)[i]);}
  checkeqidxD$1$1(argtD($1),argdD($1),name,fp);

  strcpy(name,"qla_name1DQ(,$1,,$2,x,$3)");
  resetdtD($1)
  qla_name1DQ(,$1,,$2,x,$3)(argdD($1),arg1Q($3),idx1($3),MAX);
  for(i = 0; i < MAX; i++){qla_name1DQ(,$1,,$2,,$3)(&argtD($1)[i],&arg1Q($3)[idx1($3)[i]]);}
  checkeqidxD$1$1(argtD($1),argdD($1),name,fp);

  strcpy(name,"qla_name1DQ(x,$1,,$2,x,$3)");
  resetdtD($1)
  qla_name1DQ(x,$1,,$2,x,$3)(argdD($1),idxd($1),arg1Q($3),idx1($3),MAX);
  for(i = 0; i < MAX; i++){qla_name1DQ(,$1,,$2,,$3)(&argtD($1)[idxd($1)[i]],&arg1Q($3)[idx1($3)[i]]);}
  checkeqidxD$1$1(argtD($1),argdD($1),name,fp);
#endif

  strcpy(name,"qla_name1DQ(,$1,v,$2,p,$3)");
  resetdtD($1)
  qla_name1DQ(,$1,v,$2,p,$3)(argdD($1),arg1Qp($3),MAX);
  for(i = 0; i < MAX; i++){qla_name1DQ(,$1,,$2,,$3)(&argtD($1)[i],arg1Qp($3)[i]);}
  checkeqidxD$1$1(argtD($1),argdD($1),name,fp);

  strcpy(name,"qla_name1DQ(,$1,x,$2,p,$3)");
  resetdtD($1)
  qla_name1DQ(,$1,x,$2,p,$3)(argdD($1),arg1Qp($3),idx1($3),MAX);
  for(i = 0; i < MAX; i++){qla_name1DQ(,$1,,$2,,$3)(&argtD($1)[idx1($3)[i]],arg1Qp($3)[idx1($3)[i]]);}
  checkeqidxD$1$1(argtD($1),argdD($1),name,fp);

')


rem(`
     Binary mult by const
')
rem(`binaryconst(td,eq,tc,t1)')
define(binaryconst,`
  /* qla_name1(,$1,,$2,,$4) */

  strcpy(name,"qla_name1(,$1,v,$2,,$4)");
  resetdt($1)
  qla_name1(,$1,v,$2,,$4)(argd($1),&arg4($3),arg1($4),MAX);
  for(i = 0; i < MAX; i++){qla_name1(,$1,,$2,,$4)(&argt($1)[i],&arg4($3),&arg1($4)[i]);}
  checkeqidx$1$1(argt($1),argd($1),name,fp);

  strcpy(name,"qla_name1(,$1,x,$2,,$4)");
  resetdt($1)
  qla_name1(,$1,x,$2,,$4)(argd($1),&arg4($3),arg1($4),idx1($4),MAX);
  for(i = 0; i < MAX; i++){qla_name1(,$1,,$2,,$4)(&argt($1)[idx1($4)[i]],&arg4($3),&arg1($4)[idx1($4)[i]]);}
  checkeqidx$1$1(argt($1),argd($1),name,fp);

#ifdef QLA_INDEX_ALL
  strcpy(name,"qla_name1(x,$1,,$2,,$4)");
  resetdt($1)
  qla_name1(x,$1,,$2,,$4)(argd($1),idxd($1),&arg4($3),arg1($4),MAX);
  for(i = 0; i < MAX; i++){qla_name1(,$1,,$2,,$4)(&argt($1)[idxd($1)[i]],&arg4($3),&arg1($4)[i]);}
  checkeqidx$1$1(argt($1),argd($1),name,fp);

  strcpy(name,"qla_name1(,$1,,$2,x,$4)");
  resetdt($1)
  qla_name1(,$1,,$2,x,$4)(argd($1),&arg4($3),arg1($4),idx1($4),MAX);
  for(i = 0; i < MAX; i++){qla_name1(,$1,,$2,,$4)(&argt($1)[i],&arg4($3),&arg1($4)[idx1($4)[i]]);}
  checkeqidx$1$1(argt($1),argd($1),name,fp);

  strcpy(name,"qla_name1(x,$1,,$2,x,$4)");
  resetdt($1)
  qla_name1(x,$1,,$2,x,$4)(argd($1),idxd($1),&arg4($3),arg1($4),idx1($4),MAX);
  for(i = 0; i < MAX; i++){qla_name1(,$1,,$2,,$4)(&argt($1)[idxd($1)[i]],&arg4($3),&arg1($4)[idx1($4)[i]]);}
  checkeqidx$1$1(argt($1),argd($1),name,fp);
#endif

  strcpy(name,"qla_name1(,$1,v,$2,p,$4)");
  resetdt($1)
  qla_name1(,$1,v,$2,p,$4)(argd($1),&arg4($3),arg1p($4),MAX);
  for(i = 0; i < MAX; i++){qla_name1(,$1,,$2,,$4)(&argt($1)[i],&arg4($3),arg1p($4)[i]);}
  checkeqidx$1$1(argt($1),argd($1),name,fp);

  strcpy(name,"qla_name1(,$1,x,$2,p,$4)");
  resetdt($1)
  qla_name1(,$1,x,$2,p,$4)(argd($1),&arg4($3),arg1p($4),idx1($4),MAX);
  for(i = 0; i < MAX; i++){qla_name1(,$1,,$2,,$4)(&argt($1)[idx1($4)[i]],&arg4($3),arg1p($4)[idx1($4)[i]]);}
  checkeqidx$1$1(argt($1),argd($1),name,fp);

')

rem(`
     Mult by i
')
rem(`unarytimesi(td,eq,t1)')
define(unarytimesi,`
  /* qla_name1(,$1,,$2,,$3) */

  strcpy(name,"qla_name1(,$1,v,$2,,$3)");
  resetdt($1)
  qla_name1(,$1,v,$2,,$3)(argd($1),arg1($3),MAX);
  for(i = 0; i < MAX; i++){qla_name1(,$1,,$2,,$3)(&argt($1)[i],&arg1($3)[i]);}
  checkeqidx$1$1(argt($1),argd($1),name,fp);

  strcpy(name,"qla_name1(,$1,x,$2,,$3)");
  resetdt($1)
  qla_name1(,$1,x,$2,,$3)(argd($1),arg1($3),idx1($3),MAX);
  for(i = 0; i < MAX; i++){qla_name1(,$1,,$2,,$3)(&argt($1)[idx1($3)[i]],&arg1($3)[idx1($3)[i]]);}
  checkeqidx$1$1(argt($1),argd($1),name,fp);

#ifdef QLA_INDEX_ALL
  strcpy(name,"qla_name1(x,$1,,$2,,$3)");
  resetdt($1)
  qla_name1(x,$1,,$2,,$3)(argd($1),idxd($1),arg1($3),MAX);
  for(i = 0; i < MAX; i++){qla_name1(,$1,,$2,,$3)(&argt($1)[idxd($1)[i]],&arg1($3)[i]);}
  checkeqidx$1$1(argt($1),argd($1),name,fp);

  strcpy(name,"qla_name1(,$1,,$2,x,$3)");
  resetdt($1)
  qla_name1(,$1,,$2,x,$3)(argd($1),arg1($3),idx1($3),MAX);
  for(i = 0; i < MAX; i++){qla_name1(,$1,,$2,,$3)(&argt($1)[i],&arg1($3)[idx1($3)[i]]);}
  checkeqidx$1$1(argt($1),argd($1),name,fp);

  strcpy(name,"qla_name1(x,$1,,$2,x,$3)");
  resetdt($1)
  qla_name1(x,$1,,$2,x,$3)(argd($1),idxd($1),arg1($3),idx1($3),MAX);
  for(i = 0; i < MAX; i++){qla_name1(,$1,,$2,,$3)(&argt($1)[idxd($1)[i]],&arg1($3)[idx1($3)[i]]);}
  checkeqidx$1$1(argt($1),argd($1),name,fp);
#endif

  strcpy(name,"qla_name1(,$1,v,$2,p,$3)");
  resetdt($1)
  qla_name1(,$1,v,$2,p,$3)(argd($1),arg1p($3),MAX);
  for(i = 0; i < MAX; i++){qla_name1(,$1,,$2,,$3)(&argt($1)[i],arg1p($3)[i]);}
  checkeqidx$1$1(argt($1),argd($1),name,fp);

  strcpy(name,"qla_name1(,$1,x,$2,p,$3)");
  resetdt($1)
  qla_name1(,$1,x,$2,p,$3)(argd($1),arg1p($3),idx1($3),MAX);
  for(i = 0; i < MAX; i++){qla_name1(,$1,,$2,,$3)(&argt($1)[idx1($3)[i]],arg1p($3)[idx1($3)[i]]);}
  checkeqidx$1$1(argt($1),argd($1),name,fp);

')

rem(`
     Generic binary 
')
rem(`qla_name2(pd,td,pe,eq,p1,t1,op,p2,t2)')
define(qla_name2,QLA_$1$2_$3$4_$5$6_$7_$8$9)

rem(`binary(td,eq,t1,op,t2,v1,v2)')
define(binary,`
binary1($@)
binary2($@)
')

define(binary1,`
  /* qla_name2(,$1,,$2,,$3,$4,,$5) */

  strcpy(name,"qla_name2(,$1,v,$2,,$3,$4,,$5)");
  resetdt($1)
  qla_name2(,$1,v,$2,,$3,$4,,$5)(argd($1),argx($6),argx($7),MAX);
  for(i = 0; i < MAX; i++){qla_name2(,$1,,$2,,$3,$4,,$5)(&argt($1)[i],&argx($6)[i],&argx($7)[i]);}
  checkeqidx$1$1(argt($1),argd($1),name,fp);

  strcpy(name,"qla_name2(,$1,x,$2,,$3,$4,,$5)");
  resetdt($1)
  qla_name2(,$1,x,$2,,$3,$4,,$5)(argd($1),argx($6),argx($7),idxx($6),MAX);
  for(i = 0; i < MAX; i++){qla_name2(,$1,,$2,,$3,$4,,$5)(&argt($1)[idxx($6)[i]],&argx($6)[idxx($6)[i]],&argx($7)[idxx($6)[i]]);}
  checkeqidx$1$1(argt($1),argd($1),name,fp);

#ifdef QLA_INDEX_ALL
  strcpy(name,"qla_name2(x,$1,,$2,,$3,$4,,$5)");
  resetdt($1)
  qla_name2(x,$1,,$2,,$3,$4,,$5)(argd($1),idxd($1),argx($6),argx($7),MAX);
  for(i = 0; i < MAX; i++){qla_name2(,$1,,$2,,$3,$4,,$5)(&argt($1)[idxd($1)[i]],&argx($6)[i],&argx($7)[i]);}
  checkeqidx$1$1(argt($1),argd($1),name,fp);

  strcpy(name,"qla_name2(,$1,,$2,x,$3,$4,,$5)");
  resetdt($1)
  qla_name2(,$1,,$2,x,$3,$4,,$5)(argd($1),argx($6),idxx($6),argx($7),MAX);
  for(i = 0; i < MAX; i++){qla_name2(,$1,,$2,,$3,$4,,$5)(&argt($1)[i],&argx($6)[idxx($6)[i]],&argx($7)[i]);}
  checkeqidx$1$1(argt($1),argd($1),name,fp);

  strcpy(name,"qla_name2(,$1,,$2,,$3,$4,x,$5)");
  resetdt($1)
  qla_name2(,$1,,$2,,$3,$4,x,$5)(argd($1),argx($6),argx($7),idxx($7),MAX);
  for(i = 0; i < MAX; i++){qla_name2(,$1,,$2,,$3,$4,,$5)(&argt($1)[i],&argx($6)[i],&argx($7)[idxx($7)[i]]);}
  checkeqidx$1$1(argt($1),argd($1),name,fp);

  strcpy(name,"qla_name2(x,$1,,$2,x,$3,$4,,$5)");
  resetdt($1)
  qla_name2(x,$1,,$2,x,$3,$4,,$5)(argd($1),idxd($1),argx($6),idxx($6),argx($7),MAX);
  for(i = 0; i < MAX; i++){qla_name2(,$1,,$2,,$3,$4,,$5)(&argt($1)[idxd($1)[i]],&argx($6)[idxx($6)[i]],&argx($7)[i]);}
  checkeqidx$1$1(argt($1),argd($1),name,fp);

  strcpy(name,"qla_name2(x,$1,,$2,,$3,$4,x,$5)");
  resetdt($1)
  qla_name2(x,$1,,$2,,$3,$4,x,$5)(argd($1),idxd($1),argx($6),argx($7),idxx($7),MAX);
  for(i = 0; i < MAX; i++){qla_name2(,$1,,$2,,$3,$4,,$5)(&argt($1)[idxd($1)[i]],&argx($6)[i],&argx($7)[idxx($7)[i]]);}
  checkeqidx$1$1(argt($1),argd($1),name,fp);
#endif

')

define(binary2,`
#ifdef QLA_INDEX_ALL
  strcpy(name,"qla_name2(,$1,,$2,x,$3,$4,x,$5)");
  resetdt($1)
  qla_name2(,$1,,$2,x,$3,$4,x,$5)(argd($1),argx($6),idxx($6),argx($7),idxx($7),MAX);
  for(i = 0; i < MAX; i++){qla_name2(,$1,,$2,,$3,$4,,$5)(&argt($1)[i],&argx($6)[idxx($6)[i]],&argx($7)[idxx($7)[i]]);}
  checkeqidx$1$1(argt($1),argd($1),name,fp);

  strcpy(name,"qla_name2(x,$1,,$2,x,$3,$4,x,$5)");
  resetdt($1)
  qla_name2(x,$1,,$2,x,$3,$4,x,$5)(argd($1),idxd($1),argx($6),idxx($6),argx($7),idxx($7),MAX);
  for(i = 0; i < MAX; i++){qla_name2(,$1,,$2,,$3,$4,,$5)(&argt($1)[idxd($1)[i]],&argx($6)[idxx($6)[i]],&argx($7)[idxx($7)[i]]);}
  checkeqidx$1$1(argt($1),argd($1),name,fp);
#endif

  strcpy(name,"qla_name2(,$1,v,$2,p,$3,$4,,$5)");
  resetdt($1)
  qla_name2(,$1,v,$2,p,$3,$4,,$5)(argd($1),argxp($6),argx($7),MAX);
  for(i = 0; i < MAX; i++){qla_name2(,$1,,$2,,$3,$4,,$5)(&argt($1)[i],argxp($6)[i],&argx($7)[i]);}
  checkeqidx$1$1(argt($1),argd($1),name,fp);

  strcpy(name,"qla_name2(,$1,v,$2,,$3,$4,p,$5)");
  resetdt($1)
  qla_name2(,$1,v,$2,,$3,$4,p,$5)(argd($1),argx($6),argxp($7),MAX);
  for(i = 0; i < MAX; i++){qla_name2(,$1,,$2,,$3,$4,,$5)(&argt($1)[i],&argx($6)[i],argxp($7)[i]);}
  checkeqidx$1$1(argt($1),argd($1),name,fp);

  strcpy(name,"qla_name2(,$1,v,$2,p,$3,$4,p,$5)");
  resetdt($1)
  qla_name2(,$1,v,$2,p,$3,$4,p,$5)(argd($1),argxp($6),argxp($7),MAX);
  for(i = 0; i < MAX; i++){qla_name2(,$1,,$2,,$3,$4,,$5)(&argt($1)[i],argxp($6)[i],argxp($7)[i]);}
  checkeqidx$1$1(argt($1),argd($1),name,fp);

  strcpy(name,"qla_name2(,$1,x,$2,p,$3,$4,,$5)");
  resetdt($1)
  qla_name2(,$1,x,$2,p,$3,$4,,$5)(argd($1),argxp($6),argx($7),idxx($6),MAX);
  for(i = 0; i < MAX; i++){qla_name2(,$1,,$2,,$3,$4,,$5)(&argt($1)[idxx($6)[i]],argxp($6)[idxx($6)[i]],&argx($7)[idxx($6)[i]]);}
  checkeqidx$1$1(argt($1),argd($1),name,fp);

  strcpy(name,"qla_name2(,$1,x,$2,,$3,$4,p,$5)");
  resetdt($1)
  qla_name2(,$1,x,$2,,$3,$4,p,$5)(argd($1),argx($6),argxp($7),idxx($6),MAX);
  for(i = 0; i < MAX; i++){qla_name2(,$1,,$2,,$3,$4,,$5)(&argt($1)[idxx($6)[i]],&argx($6)[idxx($6)[i]],argxp($7)[idxx($6)[i]]);}
  checkeqidx$1$1(argt($1),argd($1),name,fp);

  strcpy(name,"qla_name2(,$1,x,$2,p,$3,$4,p,$5)");
  resetdt($1)
  qla_name2(,$1,x,$2,p,$3,$4,p,$5)(argd($1),argxp($6),argxp($7),idxx($6),MAX);
  for(i = 0; i < MAX; i++){qla_name2(,$1,,$2,,$3,$4,,$5)(&argt($1)[idxx($6)[i]],argxp($6)[idxx($6)[i]],argxp($7)[idxx($6)[i]]);}
  checkeqidx$1$1(argt($1),argd($1),name,fp);

')

rem(`
     Global dot product for complex values
')
rem(`qla_name2_spec(pd,td,pe,eq,p1,t1,op,p2,t2,spec)')
define(qla_name2_spec,`SP(shift($@))_$1$2_$3$4_$5$6_$7_$8$9')
define(SP,`QLA$9')
define(qla_name2_specPR,`SPPR(shift($@))($1$2_$3$4_$5$6_$7_$8$9)')
define(SPPR,`QLA_PR$9')

rem(`binaryglobaldot(td,eq,t1,op,t2,spec,precd,prec1,prec2)')
define(binaryglobaldot,`
binaryglobaldot1($@)
binaryglobaldot2($@)
')

define(binaryglobaldot1,`
  /* qla_name2_spec(,$1,,$2,,$3,$4,,$5,$6) */

  strcpy(name,"qla_name2_spec(,$1,v,$2,,$3,$4,,$5,$6)");
  QLA_c_eq_r(argdP$8($1),0); 
  for(i = 0; i < MAX; i++){
    qla_name2_specPR(,$1,,$2,,$3,$4,,$5,$8)(&argtP$8($1),&arg1$8($3)[i],&arg2$9($5)[i]);
    QLA_c_peq_c(argdP$8($1),argtP$8($1));
  }
  QLA_c_eq_c(argt$7($1),argdP$8($1));
  qla_name2_spec(,$1,v,$2,,$3,$4,,$5,$6)(&argd$7($1),arg1$8($3),arg2$9($5),MAX);
  checkeqsng$7CC(&argd$7($1),&argt$7($1),name,fp);

  strcpy(name,"qla_name2_spec(,$1,x,$2,,$3,$4,,$5,$6)");
  QLA_c_eq_r(argdP$8($1),0); 
  for(i = 0; i < MAX; i++){
    qla_name2_specPR(,$1,,$2,,$3,$4,,$5,$8)(&argtP$8($1),&arg1$8($3)[idx1($3)[i]],&arg2$9($5)[idx1($3)[i]]);
    QLA_c_peq_c(argdP$8($1),argtP$8($1));
  }
  QLA_c_eq_c(argt$7($1),argdP$8($1));
  qla_name2_spec(,$1,x,$2,,$3,$4,,$5,$6)(&argd$7($1),arg1$8($3),arg2$9($5),idx1($3),MAX);
  checkeqsng$7CC(&argd$7($1),&argt$7($1),name,fp);

#ifdef QLA_INDEX_ALL
  strcpy(name,"qla_name2_spec(,$1,,$2,x,$3,$4,,$5,$6)");
  QLA_c_eq_r(argdP$8($1),0); 
  for(i = 0; i < MAX; i++){
    qla_name2_specPR(,$1,,$2,,$3,$4,,$5,$8)(&argtP$8($1),&arg1$8($3)[idx1($3)[i]],&arg2$9($5)[i]);
    QLA_c_peq_c(argdP$8($1),argtP$8($1));
  }
  QLA_c_eq_c(argt$7($1),argdP$8($1));
  qla_name2_spec(,$1,,$2,x,$3,$4,,$5,$6)(&argd$7($1),arg1$8($3),idx1($3),arg2$9($5),MAX);
  checkeqsng$7CC(&argd$7($1),&argt$7($1),name,fp);

  strcpy(name,"qla_name2_spec(,$1,,$2,,$3,$4,x,$5,$6)");
  QLA_c_eq_r(argdP$8($1),0); 
  for(i = 0; i < MAX; i++){
    qla_name2_specPR(,$1,,$2,,$3,$4,,$5,$8)(&argtP$8($1),&arg1$8($3)[i],&arg2$9($5)[idx2($5)[i]]);
    QLA_c_peq_c(argdP$8($1),argtP$8($1));
  }
  QLA_c_eq_c(argt$7($1),argdP$8($1));
  qla_name2_spec(,$1,,$2,,$3,$4,x,$5,$6)(&argd$7($1),arg1$8($3),arg2$9($5),idx2($5),MAX);
  checkeqsng$7CC(&argd$7($1),&argt$7($1),name,fp);

  strcpy(name,"qla_name2_spec(,$1,,$2,x,$3,$4,x,$5,$6)");
  QLA_c_eq_r(argdP$8($1),0); 
  for(i = 0; i < MAX; i++){
    qla_name2_specPR(,$1,,$2,,$3,$4,,$5,$8)(&argtP$8($1),&arg1$8($3)[idx1($3)[i]],&arg2$9($5)[idx2($5)[i]]);
    QLA_c_peq_c(argdP$8($1),argtP$8($1));
  }
  QLA_c_eq_c(argt$7($1),argdP$8($1));
  qla_name2_spec(,$1,,$2,x,$3,$4,x,$5,$6)(&argd$7($1),arg1$8($3),idx1($3),arg2$9($5),idx2($5),MAX);
  checkeqsng$7CC(&argd$7($1),&argt$7($1),name,fp);
#endif

  strcpy(name,"qla_name2_spec(,$1,v,$2,p,$3,$4,,$5,$6)");
  QLA_c_eq_r(argdP$8($1),0); 
  for(i = 0; i < MAX; i++){
    qla_name2_specPR(,$1,,$2,,$3,$4,,$5,$8)(&argtP$8($1),arg1$8p($3)[i],&arg2$9($5)[i]);
    QLA_c_peq_c(argdP$8($1),argtP$8($1));
  }
  QLA_c_eq_c(argt$7($1),argdP$8($1));
  qla_name2_spec(,$1,v,$2,p,$3,$4,,$5,$6)(&argd$7($1),arg1$8p($3),arg2$9($5),MAX);
  checkeqsng$7CC(&argd$7($1),&argt$7($1),name,fp);

  strcpy(name,"qla_name2_spec(,$1,v,$2,,$3,$4,p,$5,$6)");
  QLA_c_eq_r(argdP$8($1),0); 
  for(i = 0; i < MAX; i++){
    qla_name2_specPR(,$1,,$2,,$3,$4,,$5,$8)(&argtP$8($1),&arg1$8($3)[i],arg2$9p($5)[i]);
    QLA_c_peq_c(argdP$8($1),argtP$8($1));
  }
  QLA_c_eq_c(argt$7($1),argdP$8($1));
  qla_name2_spec(,$1,v,$2,,$3,$4,p,$5,$6)(&argd$7($1),arg1$8($3),arg2$9p($5),MAX);
  checkeqsng$7CC(&argd$7($1),&argt$7($1),name,fp);

')

define(binaryglobaldot2,`
  strcpy(name,"qla_name2_spec(,$1,v,$2,p,$3,$4,p,$5,$6)");
  QLA_c_eq_r(argdP$8($1),0); 
  for(i = 0; i < MAX; i++){
    qla_name2_specPR(,$1,,$2,,$3,$4,,$5,$8)(&argtP$8($1),arg1$8p($3)[i],arg2$9p($5)[i]);
    QLA_c_peq_c(argdP$8($1),argtP$8($1));
  }
  QLA_c_eq_c(argt$7($1),argdP$8($1));
  qla_name2_spec(,$1,v,$2,p,$3,$4,p,$5,$6)(&argd$7($1),arg1$8p($3),arg2$9p($5),MAX);
  checkeqsng$7CC(&argd$7($1),&argt$7($1),name,fp);

  strcpy(name,"qla_name2_spec(,$1,x,$2,p,$3,$4,,$5,$6)");
  QLA_c_eq_r(argdP$8($1),0); 
  for(i = 0; i < MAX; i++){
    qla_name2_specPR(,$1,,$2,,$3,$4,,$5,$8)(&argtP$8($1),arg1$8p($3)[idx1($3)[i]],&arg2$9($5)[idx1($3)[i]]);
    QLA_c_peq_c(argdP$8($1),argtP$8($1));
  }
  QLA_c_eq_c(argt$7($1),argdP$8($1));
  qla_name2_spec(,$1,x,$2,p,$3,$4,,$5,$6)(&argd$7($1),arg1$8p($3),arg2$9($5),idx1($3),MAX);
  checkeqsng$7CC(&argd$7($1),&argt$7($1),name,fp);

  strcpy(name,"qla_name2_spec(,$1,x,$2,,$3,$4,p,$5,$6)");
  QLA_c_eq_r(argdP$8($1),0); 
  for(i = 0; i < MAX; i++){
    qla_name2_specPR(,$1,,$2,,$3,$4,,$5,$8)(&argtP$8($1),&arg1$8($3)[idx1($3)[i]],arg2$9p($5)[idx1($3)[i]]);
    QLA_c_peq_c(argdP$8($1),argtP$8($1));
  }
  QLA_c_eq_c(argt$7($1),argdP$8($1));
  qla_name2_spec(,$1,x,$2,,$3,$4,p,$5,$6)(&argd$7($1),arg1$8($3),arg2$9p($5),idx1($3),MAX);
  checkeqsng$7CC(&argd$7($1),&argt$7($1),name,fp);

  strcpy(name,"qla_name2_spec(,$1,x,$2,p,$3,$4,p,$5,$6)");
  QLA_c_eq_r(argdP$8($1),0); 
  for(i = 0; i < MAX; i++){
    qla_name2_specPR(,$1,,$2,,$3,$4,,$5,$8)(&argtP$8($1),arg1$8p($3)[idx1($3)[i]],arg2$9p($5)[idx1($3)[i]]);
    QLA_c_peq_c(argdP$8($1),argtP$8($1));
  }
  QLA_c_eq_c(argt$7($1),argdP$8($1));
  qla_name2_spec(,$1,x,$2,p,$3,$4,p,$5,$6)(&argd$7($1),arg1$8p($3),arg2$9p($5),idx1($3),MAX);
  checkeqsng$7CC(&argd$7($1),&argt$7($1),name,fp);

')

rem(`
     Global dot product for reals and ints
')
rem(`binaryglobaldotreal(td,eq,t1,op,t2,v1,v2,spec,precd,prec1,prec2)')
define(binaryglobaldotreal,
#if '$3' == 'I'
#define destrP destrD
#define chkrP chkrD
#endif
`
binaryglobaldotreal1($@)
binaryglobaldotreal2($@)
'
#if '$3' == 'I'
#undef destrP
#undef chkrP
#endif
)

define(binaryglobaldotreal1,`
  /* qla_name2_spec(,$1,,$2,,$3,$4,,$5,$6) */

  strcpy(name,"qla_name2_spec(,$1,v,$2,,$3,$4,,$5,$6)");
  argdP$8($1) = 0; 
  for(i = 0; i < MAX; i++){
    qla_name2_specPR(,$1,,$2,,$3,$4,,$5,$8)(&argtP$8($1),&arg1$8($3)[i],&arg2$9($5)[i]);
    argdP$8($1) += argtP$8($1);
  }
  argt$7($1) =  argdP$8($1);
  qla_name2_spec(,$1,v,$2,,$3,$4,,$5,$6)(&argd$7($1),arg1$8($3),arg2$9($5),MAX);
  checkeqsng$7RR(&argd$7($1),&argt$7($1),name,fp);

  strcpy(name,"qla_name2_spec(,$1,x,$2,,$3,$4,,$5,$6)");
  argdP$8($1) = 0; 
  for(i = 0; i < MAX; i++){
    qla_name2_specPR(,$1,,$2,,$3,$4,,$5,$8)(&argtP$8($1),&arg1$8($3)[idx1($3)[i]],&arg2$9($5)[idx1($3)[i]]);
    argdP$8($1) += argtP$8($1);
  }
  argt$7($1) = argdP$8($1);
  qla_name2_spec(,$1,x,$2,,$3,$4,,$5,$6)(&argd$7($1),arg1$8($3),arg2$9($5),idx1($3),MAX);
  checkeqsng$7RR(&argd$7($1),&argt$7($1),name,fp);

#ifdef QLA_INDEX_ALL
  strcpy(name,"qla_name2_spec(,$1,,$2,x,$3,$4,,$5,$6)");
  argdP$8($1) = 0; 
  for(i = 0; i < MAX; i++){
    qla_name2_specPR(,$1,,$2,,$3,$4,,$5,$8)(&argtP$8($1),&arg1$8($3)[idx1($3)[i]],&arg2$9($5)[i]);
    argdP$8($1) += argtP$8($1);
  }
  argt$7($1) = argdP$8($1);
  qla_name2_spec(,$1,,$2,x,$3,$4,,$5,$6)(&argd$7($1),arg1$8($3),idx1($3),arg2$9($5),MAX);
  checkeqsng$7RR(&argd$7($1),&argt$7($1),name,fp);

  strcpy(name,"qla_name2_spec(,$1,,$2,,$3,$4,x,$5,$6)");
  argdP$8($1) = 0; 
  for(i = 0; i < MAX; i++){
    qla_name2_specPR(,$1,,$2,,$3,$4,,$5,$8)(&argtP$8($1),&arg1$8($3)[i],&arg2$9($5)[idx2($5)[i]]);
    argdP$8($1) += argtP$8($1);
  }
  argt$7($1) = argdP$8($1);
  qla_name2_spec(,$1,,$2,,$3,$4,x,$5,$6)(&argd$7($1),arg1$8($3),arg2$9($5),idx2($5),MAX);
  checkeqsng$7RR(&argd$7($1),&argt$7($1),name,fp);

  strcpy(name,"qla_name2_spec(,$1,,$2,x,$3,$4,x,$5,$6)");
  argdP$8($1) = 0; 
  for(i = 0; i < MAX; i++){
    qla_name2_specPR(,$1,,$2,,$3,$4,,$5,$8)(&argtP$8($1),&arg1$8($3)[idx1($3)[i]],&arg2$9($5)[idx2($5)[i]]);
    argdP$8($1) += argtP$8($1);
  }
  argt$7($1) = argdP$8($1);
  qla_name2_spec(,$1,,$2,x,$3,$4,x,$5,$6)(&argd$7($1),arg1$8($3),idx1($3),arg2$9($5),idx2($5),MAX);
  checkeqsng$7RR(&argd$7($1),&argt$7($1),name,fp);
#endif

  strcpy(name,"qla_name2_spec(,$1,v,$2,p,$3,$4,,$5,$6)");
  argdP$8($1) = 0; 
  for(i = 0; i < MAX; i++){
    qla_name2_specPR(,$1,,$2,,$3,$4,,$5,$8)(&argtP$8($1),arg1$8p($3)[i],&arg2$9($5)[i]);
    argdP$8($1) += argtP$8($1);
  }
  argt$7($1) = argdP$8($1);
  qla_name2_spec(,$1,v,$2,p,$3,$4,,$5,$6)(&argd$7($1),arg1$8p($3),arg2$9($5),MAX);
  checkeqsng$7RR(&argd$7($1),&argt$7($1),name,fp);

  strcpy(name,"qla_name2_spec(,$1,v,$2,,$3,$4,p,$5,$6)");
  argdP$8($1) = 0; 
  for(i = 0; i < MAX; i++){
    qla_name2_specPR(,$1,,$2,,$3,$4,,$5,$8)(&argtP$8($1),&arg1$8($3)[i],arg2$9p($5)[i]);
    argdP$8($1) += argtP$8($1);
  }
  argt$7($1) = argdP$8($1);
  qla_name2_spec(,$1,v,$2,,$3,$4,p,$5,$6)(&argd$7($1),arg1$8($3),arg2$9p($5),MAX);
  checkeqsng$7RR(&argd$7($1),&argt$7($1),name,fp);

')

define(binaryglobaldotreal2,`
  strcpy(name,"qla_name2_spec(,$1,v,$2,p,$3,$4,p,$5,$6)");
  argdP$8($1) = 0; 
  for(i = 0; i < MAX; i++){
    qla_name2_specPR(,$1,,$2,,$3,$4,,$5,$8)(&argtP$8($1),arg1$8p($3)[i],arg2$9p($5)[i]);
    argdP$8($1) += argtP$8($1);
  }
  argt$7($1) = argdP$8($1);
  qla_name2_spec(,$1,v,$2,p,$3,$4,p,$5,$6)(&argd$7($1),arg1$8p($3),arg2$9p($5),MAX);
  checkeqsng$7RR(&argd$7($1),&argt$7($1),name,fp);

  strcpy(name,"qla_name2_spec(,$1,x,$2,p,$3,$4,,$5,$6)");
  argdP$8($1) = 0; 
  for(i = 0; i < MAX; i++){
    qla_name2_specPR(,$1,,$2,,$3,$4,,$5,$8)(&argtP$8($1),arg1$8p($3)[idx1($3)[i]],&arg2$9($5)[idx1($3)[i]]);
    argdP$8($1) += argtP$8($1);
  }
  argt$7($1) = argdP$8($1);
  qla_name2_spec(,$1,x,$2,p,$3,$4,,$5,$6)(&argd$7($1),arg1$8p($3),arg2$9($5),idx1($3),MAX);
  checkeqsng$7RR(&argd$7($1),&argt$7($1),name,fp);

  strcpy(name,"qla_name2_spec(,$1,x,$2,,$3,$4,p,$5,$6)");
  argdP$8($1) = 0; 
  for(i = 0; i < MAX; i++){
    qla_name2_specPR(,$1,,$2,,$3,$4,,$5,$8)(&argtP$8($1),&arg1$8($3)[idx1($3)[i]],arg2$9p($5)[idx1($3)[i]]);
    argdP$8($1) += argtP$8($1);
  }
  argt$7($1) = argdP$8($1);
  qla_name2_spec(,$1,x,$2,,$3,$4,p,$5,$6)(&argd$7($1),arg1$8($3),arg2$9p($5),idx1($3),MAX);
  checkeqsng$7RR(&argd$7($1),&argt$7($1),name,fp);

  strcpy(name,"qla_name2_spec(,$1,x,$2,p,$3,$4,p,$5,$6)");
  argdP$8($1) = 0; 
  for(i = 0; i < MAX; i++){
    qla_name2_specPR(,$1,,$2,,$3,$4,,$5,$8)(&argtP$8($1),arg1$8p($3)[idx1($3)[i]],arg2$9p($5)[idx1($3)[i]]);
    argdP$8($1) += argtP$8($1);
  }
  argt$7($1) = argdP$8($1);
  qla_name2_spec(,$1,x,$2,p,$3,$4,p,$5,$6)(&argd$7($1),arg1$8p($3),arg2$9p($5),idx1($3),MAX);
  checkeqsng$7RR(&argd$7($1),&argt$7($1),name,fp);

')

rem(`
     Ternary operation with constant
')
rem(`ternaryconst(td,eq,tc,t1,op,t2)')
define(ternaryconst,`
ternaryconst1($@)
ternaryconst2($@)
')

define(ternaryconst1,`
  /* qla_name2(,$1,,$2,,$4,$5,,$6) */

  strcpy(name,"qla_name2(,$1,v,$2,,$4,$5,,$6)");
  resetdt($1)
  qla_name2(,$1,v,$2,,$4,$5,,$6)(argd($1),&arg4($3),arg1($4),arg2($6),MAX);
  for(i = 0; i < MAX; i++){qla_name2(,$1,,$2,,$4,$5,,$6)(&argt($1)[i],&arg4($3),&arg1($4)[i],&arg2($6)[i]);}
  checkeqidx$1$1(argt($1),argd($1),name,fp);

  strcpy(name,"qla_name2(,$1,x,$2,,$4,$5,,$6)");
  resetdt($1)
  qla_name2(,$1,x,$2,,$4,$5,,$6)(argd($1),&arg4($3),arg1($4),arg2($6),idx1($4),MAX);
  for(i = 0; i < MAX; i++){qla_name2(,$1,,$2,,$4,$5,,$6)(&argt($1)[idx1($4)[i]],&arg4($3),&arg1($4)[idx1($4)[i]],&arg2($6)[idx1($4)[i]]);}
  checkeqidx$1$1(argt($1),argd($1),name,fp);

#ifdef QLA_INDEX_ALL
  strcpy(name,"qla_name2(x,$1,,$2,,$4,$5,,$6)");
  resetdt($1)
  qla_name2(x,$1,,$2,,$4,$5,,$6)(argd($1),idxd($1),&arg4($3),arg1($4),arg2($6),MAX);
  for(i = 0; i < MAX; i++){qla_name2(,$1,,$2,,$4,$5,,$6)(&argt($1)[idxd($1)[i]],&arg4($3),&arg1($4)[i],&arg2($6)[i]);}
  checkeqidx$1$1(argt($1),argd($1),name,fp);

  strcpy(name,"qla_name2(,$1,,$2,x,$4,$5,,$6)");
  resetdt($1)
  qla_name2(,$1,,$2,x,$4,$5,,$6)(argd($1),&arg4($3),arg1($4),idx1($4),arg2($6),MAX);
  for(i = 0; i < MAX; i++){qla_name2(,$1,,$2,,$4,$5,,$6)(&argt($1)[i],&arg4($3),&arg1($4)[idx1($4)[i]],&arg2($6)[i]);}
  checkeqidx$1$1(argt($1),argd($1),name,fp);

  strcpy(name,"qla_name2(,$1,,$2,,$4,$5,x,$6)");
  resetdt($1)
  qla_name2(,$1,,$2,,$4,$5,x,$6)(argd($1),&arg4($3),arg1($4),arg2($6),idx2($6),MAX);
  for(i = 0; i < MAX; i++){qla_name2(,$1,,$2,,$4,$5,,$6)(&argt($1)[i],&arg4($3),&arg1($4)[i],&arg2($6)[idx2($6)[i]]);}
  checkeqidx$1$1(argt($1),argd($1),name,fp);

  strcpy(name,"qla_name2(x,$1,,$2,x,$4,$5,,$6)");
  resetdt($1)
  qla_name2(x,$1,,$2,x,$4,$5,,$6)(argd($1),idxd($1),&arg4($3),arg1($4),idx1($4),arg2($6),MAX);
  for(i = 0; i < MAX; i++){qla_name2(,$1,,$2,,$4,$5,,$6)(&argt($1)[idxd($1)[i]],&arg4($3),&arg1($4)[idx1($4)[i]],&arg2($6)[i]);}
  checkeqidx$1$1(argt($1),argd($1),name,fp);

  strcpy(name,"qla_name2(x,$1,,$2,,$4,$5,x,$6)");
  resetdt($1)
  qla_name2(x,$1,,$2,,$4,$5,x,$6)(argd($1),idxd($1),&arg4($3),arg1($4),arg2($6),idx2($6),MAX);
  for(i = 0; i < MAX; i++){qla_name2(,$1,,$2,,$4,$5,,$6)(&argt($1)[idxd($1)[i]],&arg4($3),&arg1($4)[i],&arg2($6)[idx2($6)[i]]);}
  checkeqidx$1$1(argt($1),argd($1),name,fp);
#endif

')

define(ternaryconst2,`
#ifdef QLA_INDEX_ALL
  strcpy(name,"qla_name2(,$1,,$2,x,$4,$5,x,$6)");
  resetdt($1)
  qla_name2(,$1,,$2,x,$4,$5,x,$6)(argd($1),&arg4($3),arg1($4),idx1($4),arg2($6),idx2($6),MAX);
  for(i = 0; i < MAX; i++){qla_name2(,$1,,$2,,$4,$5,,$6)(&argt($1)[i],&arg4($3),&arg1($4)[idx1($4)[i]],&arg2($6)[idx2($6)[i]]);}
  checkeqidx$1$1(argt($1),argd($1),name,fp);

  strcpy(name,"qla_name2(x,$1,,$2,x,$4,$5,x,$6)");
  resetdt($1)
  qla_name2(x,$1,,$2,x,$4,$5,x,$6)(argd($1),idxd($1),&arg4($3),arg1($4),idx1($4),arg2($6),idx2($6),MAX);
  for(i = 0; i < MAX; i++){qla_name2(,$1,,$2,,$4,$5,,$6)(&argt($1)[idxd($1)[i]],&arg4($3),&arg1($4)[idx1($4)[i]],&arg2($6)[idx2($6)[i]]);}
  checkeqidx$1$1(argt($1),argd($1),name,fp);
#endif

  strcpy(name,"qla_name2(,$1,v,$2,p,$4,$5,,$6)");
  resetdt($1)
  qla_name2(,$1,v,$2,p,$4,$5,,$6)(argd($1),&arg4($3),arg1p($4),arg2($6),MAX);
  for(i = 0; i < MAX; i++){qla_name2(,$1,,$2,,$4,$5,,$6)(&argt($1)[i],&arg4($3),arg1p($4)[i],&arg2($6)[i]);}
  checkeqidx$1$1(argt($1),argd($1),name,fp);

  strcpy(name,"qla_name2(,$1,v,$2,,$4,$5,p,$6)");
  resetdt($1)
  qla_name2(,$1,v,$2,,$4,$5,p,$6)(argd($1),&arg4($3),arg1($4),arg2p($6),MAX);
  for(i = 0; i < MAX; i++){qla_name2(,$1,,$2,,$4,$5,,$6)(&argt($1)[i],&arg4($3),&arg1($4)[i],arg2p($6)[i]);}
  checkeqidx$1$1(argt($1),argd($1),name,fp);

  strcpy(name,"qla_name2(,$1,v,$2,p,$4,$5,p,$6)");
  resetdt($1)
  qla_name2(,$1,v,$2,p,$4,$5,p,$6)(argd($1),&arg4($3),arg1p($4),arg2p($6),MAX);
  for(i = 0; i < MAX; i++){qla_name2(,$1,,$2,,$4,$5,,$6)(&argt($1)[i],&arg4($3),arg1p($4)[i],arg2p($6)[i]);}
  checkeqidx$1$1(argt($1),argd($1),name,fp);

  strcpy(name,"qla_name2(,$1,x,$2,p,$4,$5,,$6)");
  resetdt($1)
  qla_name2(,$1,x,$2,p,$4,$5,,$6)(argd($1),&arg4($3),arg1p($4),arg2($6),idx1($4),MAX);
  for(i = 0; i < MAX; i++){qla_name2(,$1,,$2,,$4,$5,,$6)(&argt($1)[idx1($4)[i]],&arg4($3),arg1p($4)[idx1($4)[i]],&arg2($6)[idx1($4)[i]]);}
  checkeqidx$1$1(argt($1),argd($1),name,fp);

  strcpy(name,"qla_name2(,$1,x,$2,,$4,$5,p,$6)");
  resetdt($1)
  qla_name2(,$1,x,$2,,$4,$5,p,$6)(argd($1),&arg4($3),arg1($4),arg2p($6),idx1($4),MAX);
  for(i = 0; i < MAX; i++){qla_name2(,$1,,$2,,$4,$5,,$6)(&argt($1)[idx1($4)[i]],&arg4($3),&arg1($4)[idx1($4)[i]],arg2p($6)[idx1($4)[i]]);}
  checkeqidx$1$1(argt($1),argd($1),name,fp);

  strcpy(name,"qla_name2(,$1,x,$2,p,$4,$5,p,$6)");
  resetdt($1)
  qla_name2(,$1,x,$2,p,$4,$5,p,$6)(argd($1),&arg4($3),arg1p($4),arg2p($6),idx1($4),MAX);
  for(i = 0; i < MAX; i++){qla_name2(,$1,,$2,,$4,$5,,$6)(&argt($1)[idx1($4)[i]],&arg4($3),arg1p($4)[idx1($4)[i]],arg2p($6)[idx1($4)[i]]);}
  checkeqidx$1$1(argt($1),argd($1),name,fp);

')

rem(`
     For checking vector copy
')
rem(`chkVectorCopy(td)')
define(chkVectorCopy,`
  strcpy(name,"QLA_$1_veq_$1");
  for(i = 0; i < MAX; i++)QLA_$1_eq_zero(&argd($1)[i]);
  QLA_$1_veq_$1(argd($1),arg1($1),MAX);
  for(i = 0; i < MAX; i++)QLA_$1_eq_$1(&argt($1)[i],&arg1($1)[i]);
  checkeqidx$1$1(argd($1),argt($1),name,fp);
')

rem(`
     Extracting element
')
rem(`unary_get_elem(td,eq,t1)')
define(unary_get_elem,`
  /* qla_name1(,$1,,$2,,$3) */

  strcpy(name,"qla_name1(,$1,v,$2,,$3)");
  resetdt($3)
  for_$3_elem{
    qla_name1(,$1,v,$2,,$3)(argd($1),arg1($3),$3_list,MAX);
    for(i = 0; i < MAX; i++){QLA_elem_$3(argt($3)[i],$3_list) = argd($1)[i];}
  }
  QLA_$3_veq_$3(argd($3),arg1($3),MAX);
  checkeqidx$3$3(argt($3),argd($3),name,fp);

  strcpy(name,"qla_name1(,$1,x,$2,,$3)");
  resetdt($3)
  for_$3_elem{
    qla_name1(,$1,x,$2,,$3)(argd($1),arg1($3),$3_list,idx1($3),MAX);
    for(i = 0; i < MAX; i++){QLA_elem_$3(argt($3)[i],$3_list) = argd($1)[i];}
  }
  QLA_$3_xeq_$3(argd($3),arg1($3),idx1($3),MAX);
  checkeqidx$3$3(argt($3),argd($3),name,fp);

#ifdef QLA_INDEX_ALL
  strcpy(name,"qla_name1(x,$1,,$2,,$3)");
  resetdt($3)
  for_$3_elem{
    qla_name1(x,$1,,$2,,$3)(argd($1),idxd($1),arg1($3),$3_list,MAX);
    for(i = 0; i < MAX; i++){QLA_elem_$3(argt($3)[i],$3_list) = argd($1)[i];}
  }
  QLA_x$3_eq_$3(argd($3),idxd($1),arg1($3),MAX);
  checkeqidx$3$3(argt($3),argd($3),name,fp);

  strcpy(name,"qla_name1(,$1,,$2,x,$3)");
  resetdt($3)
  for_$3_elem{
    qla_name1(,$1,,$2,x,$3)(argd($1),arg1($3),idx1($3),$3_list,MAX);
    for(i = 0; i < MAX; i++){QLA_elem_$3(argt($3)[i],$3_list) = argd($1)[i];}
  }
  QLA_$3_eq_x$3(argd($3),arg1($3),idx1($3),MAX);
  checkeqidx$3$3(argt($3),argd($3),name,fp);

  strcpy(name,"qla_name1(x,$1,,$2,x,$3)");
  resetdt($3)
  for_$3_elem{
    qla_name1(x,$1,,$2,x,$3)(argd($1),idxd($1),arg1($3),idx1($3),$3_list,MAX);
    for(i = 0; i < MAX; i++){QLA_elem_$3(argt($3)[i],$3_list) = argd($1)[i];}
  }
  QLA_x$3_eq_x$3(argd($3),idxd($1),arg1($3),idx1($3),MAX);
  checkeqidx$3$3(argt($3),argd($3),name,fp);
#endif

  strcpy(name,"qla_name1(,$1,v,$2,p,$3)");
  resetdt($3)
  for_$3_elem{
    qla_name1(,$1,v,$2,p,$3)(argd($1),arg1p($3),$3_list,MAX);
    for(i = 0; i < MAX; i++){QLA_elem_$3(argt($3)[i],$3_list) = argd($1)[i];}
  }
  QLA_$3_veq_p$3(argd($3),arg1p($3),MAX);
  checkeqidx$3$3(argt($3),argd($3),name,fp);

  strcpy(name,"qla_name1(,$1,x,$2,p,$3)");
  resetdt($3)
  for_$3_elem{
    qla_name1(,$1,x,$2,p,$3)(argd($1),arg1p($3),$3_list,idx1($3),MAX);
    for(i = 0; i < MAX; i++){QLA_elem_$3(argt($3)[i],$3_list) = argd($1)[i];}
  }
  QLA_$3_xeq_p$3(argd($3),arg1p($3),idx1($3),MAX);
  checkeqidx$3$3(argt($3),argd($3),name,fp);
')

rem(`
     Inserting element
')
rem(`unary_set_elem(td,eq,t1)')
define(unary_set_elem,`
  /* qla_name1(,$1,,$2,,$3) */

  strcpy(name,"qla_name1(,$1,v,$2,,$3)");
  resetdt($1)
  for_$1_elem{
    for(i = 0; i < MAX; i++){argt($3)[i] = QLA_elem_$1(arg1($1)[i],$1_list);}
    qla_name1(,$1,v,$2,,$3)(argd($1),argt($3),$1_list,MAX);
  }
  QLA_$1_veq_$1(argt($1),arg1($1),MAX);  
  checkeqidx$1$1(argt($1),argd($1),name,fp);

  strcpy(name,"qla_name1(,$1,x,$2,,$3)");
  resetdt($1)
  for_$1_elem{
    for(i = 0; i < MAX; i++){argt($3)[i] = QLA_elem_$1(arg1($1)[i],$1_list);}
    qla_name1(,$1,x,$2,,$3)(argd($1),argt($3),$1_list,idx1($3),MAX);
  }
  QLA_$1_xeq_$1(argt($1),arg1($1),idx1($3),MAX);
  checkeqidx$1$1(argt($1),argd($1),name,fp);

#ifdef QLA_INDEX_ALL
  strcpy(name,"qla_name1(x,$1,,$2,,$3)");
  resetdt($1)
  for_$1_elem{
    for(i = 0; i < MAX; i++){argt($3)[i] = QLA_elem_$1(arg1($1)[i],$1_list);}
    qla_name1(x,$1,,$2,,$3)(argd($1),idxd($1),argt($3),$1_list,MAX);
  }
  QLA_x$1_eq_$1(argt($1),idxd($1),arg1($1),MAX);
  checkeqidx$1$1(argt($1),argd($1),name,fp);

  strcpy(name,"qla_name1(,$1,,$2,x,$3)");
  resetdt($1)
  for_$1_elem{
    for(i = 0; i < MAX; i++){argt($3)[i] = QLA_elem_$1(arg1($1)[i],$1_list);}
    qla_name1(,$1,,$2,x,$3)(argd($1),argt($3),idx1($3),$1_list,MAX);
  }
  QLA_$1_eq_x$1(argt($1),arg1($1),idx1($3),MAX);
  checkeqidx$1$1(argt($1),argd($1),name,fp);

  strcpy(name,"qla_name1(x,$1,,$2,x,$3)");
  resetdt($1)
  for_$1_elem{
    for(i = 0; i < MAX; i++){argt($3)[i] = QLA_elem_$1(arg1($1)[i],$1_list);}
    qla_name1(x,$1,,$2,x,$3)(argd($1),idxd($1),argt($3),idx1($3),$1_list,MAX);
  }
  QLA_x$1_eq_x$1(argt($1),idxd($1),arg1($1),idx1($3),MAX);
  checkeqidx$1$1(argt($1),argd($1),name,fp);
#endif

  strcpy(name,"qla_name1(,$1,v,$2,p,$3)");
  resetdt($1)
  for_$1_elem{
    for(i = 0; i < MAX; i++){argt($3)[i] = QLA_elem_$1(arg1($1)[i],$1_list);}
    qla_name1(,$1,v,$2,p,$3)(argd($1),argtp($3),$1_list,MAX);
  }
  /* QLA_$1_eq_x$1(argt($1),arg1($1),idx1($3),MAX); */
  for(i=0; i<MAX; i++) { QLA_$1_eq_$1(&argt($1)[i], arg1($1)+idx1($3)[i]); }
  checkeqidx$1$1(argt($1),argd($1),name,fp);

  strcpy(name,"qla_name1(,$1,x,$2,p,$3)");
  /* QLA_$1_eq_x$1(argd($1),arg1($1),idx1($3),MAX); */
  for(i=0; i<MAX; i++) { QLA_$1_eq_$1(&argd($1)[i],arg1($1)+idx1($3)[i]); }
  QLA_$1_xeq_$1(argt($1),argd($1),idx2($3),MAX);
  QLA_$1_veq_$1(argd($1),arg3($1),MAX);
  for_$1_elem{
    for(i = 0; i < MAX; i++){argt($3)[i] = QLA_elem_$1(arg1($1)[i],$1_list);}
    qla_name1(,$1,x,$2,p,$3)(argd($1),argtp($3),$1_list,idx2($3),MAX);
  }
  checkeqidx$1$1(argt($1),argd($1),name,fp);
')

rem(`
     Extracting color vector
')
rem(`unary_get_colorvec(td,eq,t1)')
define(unary_get_colorvec,`
  /* qla_name1(,$1,,$2,,$3) */

  strcpy(name,"qla_name1(,$1,v,$2,,$3)");
  resetdt($3)
  for_$3_colorvec{
    qla_name1(,$1,v,$2,,$3)(argd($1),arg1($3),$3_list_cvec,MAX);
    for(i = 0; i < MAX; i++)for(ic = 0; ic < nc; ic++){
      QLA_elem_$3(argt($3)[i],$3_list) = QLA_elem_$1(argd($1)[i],$1_list);}
  }
  QLA_$3_veq_$3(argd($3),arg1($3),MAX);
  checkeqidx$3$3(argt($3),argd($3),name,fp);

  strcpy(name,"qla_name1(,$1,x,$2,,$3)");
  resetdt($3)
  for_$3_colorvec{
    qla_name1(,$1,x,$2,,$3)(argd($1),arg1($3),$3_list_cvec,idx1($3),MAX);
    for(i = 0; i < MAX; i++)for(ic = 0; ic < nc; ic++){
      QLA_elem_$3(argt($3)[i],$3_list) = QLA_elem_$1(argd($1)[i],$1_list);}
  }
  QLA_$3_xeq_$3(argd($3),arg1($3),idx1($3),MAX);
  checkeqidx$3$3(argt($3),argd($3),name,fp);

#ifdef QLA_INDEX_ALL
  strcpy(name,"qla_name1(x,$1,,$2,,$3)");
  resetdt($3)
  for_$3_colorvec{
    qla_name1(x,$1,,$2,,$3)(argd($1),idxd($1),arg1($3),$3_list_cvec,MAX);
    for(i = 0; i < MAX; i++)for(ic = 0; ic < nc; ic++){
      QLA_elem_$3(argt($3)[i],$3_list) = QLA_elem_$1(argd($1)[i],$1_list);}
  }
  QLA_x$3_eq_$3(argd($3),idxd($1),arg1($3),MAX);
  checkeqidx$3$3(argt($3),argd($3),name,fp);

  strcpy(name,"qla_name1(,$1,,$2,x,$3)");
  resetdt($3)
  for_$3_colorvec{
    qla_name1(,$1,,$2,x,$3)(argd($1),arg1($3),idx1($3),$3_list_cvec,MAX);
    for(i = 0; i < MAX; i++)for(ic = 0; ic < nc; ic++){
      QLA_elem_$3(argt($3)[i],$3_list) = QLA_elem_$1(argd($1)[i],$1_list);}
  }
  QLA_$3_eq_x$3(argd($3),arg1($3),idx1($3),MAX);
  checkeqidx$3$3(argt($3),argd($3),name,fp);

  strcpy(name,"qla_name1(x,$1,,$2,x,$3)");
  resetdt($3)
  for_$3_colorvec{
    qla_name1(x,$1,,$2,x,$3)(argd($1),idxd($1),arg1($3),idx1($3),$3_list_cvec,MAX);
    for(i = 0; i < MAX; i++)for(ic = 0; ic < nc; ic++){
      QLA_elem_$3(argt($3)[i],$3_list) = QLA_elem_$1(argd($1)[i],$1_list);}
  }
  QLA_x$3_eq_x$3(argd($3),idxd($1),arg1($3),idx1($3),MAX);
  checkeqidx$3$3(argt($3),argd($3),name,fp);
#endif

  strcpy(name,"qla_name1(,$1,v,$2,p,$3)");
  resetdt($3)
  for_$3_colorvec{
    qla_name1(,$1,v,$2,p,$3)(argd($1),arg1p($3),$3_list_cvec,MAX);
    for(i = 0; i < MAX; i++)for(ic = 0; ic < nc; ic++){
      QLA_elem_$3(argt($3)[i],$3_list) = QLA_elem_$1(argd($1)[i],$1_list);}
  }
  QLA_$3_veq_p$3(argd($3),arg1p($3),MAX);
  checkeqidx$3$3(argt($3),argd($3),name,fp);

  strcpy(name,"qla_name1(,$1,x,$2,p,$3)");
  resetdt($3)
  for_$3_colorvec{
    qla_name1(,$1,x,$2,p,$3)(argd($1),arg1p($3),$3_list_cvec,idx1($3),MAX);
    for(i = 0; i < MAX; i++)for(ic = 0; ic < nc; ic++){
      QLA_elem_$3(argt($3)[i],$3_list) = QLA_elem_$1(argd($1)[i],$1_list);}
  }
  QLA_$3_xeq_p$3(argd($3),arg1p($3),idx1($3),MAX);
  checkeqidx$3$3(argt($3),argd($3),name,fp);
')

rem(`
     Inserting color vector
')
rem(`unary_set_colorvec(td,eq,t1)')
define(unary_set_colorvec,`
  /* qla_name1(,$1,,$2,,$3) */

  strcpy(name,"qla_name1(,$1,v,$2,,$3)");
  resetdt($1)
  for_$1_colorvec{
    for(i = 0; i < MAX; i++)for(ic = 0; ic < nc; ic++){
      QLA_elem_$3(argt($3)[i],$3_list) = QLA_elem_$1(arg1($1)[i],$1_list);}
    qla_name1(,$1,v,$2,,$3)(argd($1),argt($3),$1_list_cvec,MAX);
  }
  QLA_$1_veq_$1(argt($1),arg1($1),MAX);  
  checkeqidx$1$1(argt($1),argd($1),name,fp);

  strcpy(name,"qla_name1(,$1,x,$2,,$3)");
  resetdt($1)
  for_$1_colorvec{
    for(i = 0; i < MAX; i++)for(ic = 0; ic < nc; ic++){
      QLA_elem_$3(argt($3)[i],$3_list) = QLA_elem_$1(arg1($1)[i],$1_list);}
    qla_name1(,$1,x,$2,,$3)(argd($1),argt($3),$1_list_cvec,idx1($3),MAX);
  }
  QLA_$1_xeq_$1(argt($1),arg1($1),idx1($3),MAX);
  checkeqidx$1$1(argt($1),argd($1),name,fp);

#ifdef QLA_INDEX_ALL
  strcpy(name,"qla_name1(x,$1,,$2,,$3)");
  resetdt($1)
  for_$1_colorvec{
    for(i = 0; i < MAX; i++)for(ic = 0; ic < nc; ic++){
      QLA_elem_$3(argt($3)[i],$3_list) = QLA_elem_$1(arg1($1)[i],$1_list);}
    qla_name1(x,$1,,$2,,$3)(argd($1),idxd($1),argt($3),$1_list_cvec,MAX);
  }
  QLA_x$1_eq_$1(argt($1),idxd($1),arg1($1),MAX);
  checkeqidx$1$1(argt($1),argd($1),name,fp);

  strcpy(name,"qla_name1(,$1,,$2,x,$3)");
  resetdt($1)
  for_$1_colorvec{
    for(i = 0; i < MAX; i++)for(ic = 0; ic < nc; ic++){
      QLA_elem_$3(argt($3)[i],$3_list) = QLA_elem_$1(arg1($1)[i],$1_list);}
    qla_name1(,$1,,$2,x,$3)(argd($1),argt($3),idx1($3),$1_list_cvec,MAX);
  }
  QLA_$1_eq_x$1(argt($1),arg1($1),idx1($3),MAX);
  checkeqidx$1$1(argt($1),argd($1),name,fp);

  strcpy(name,"qla_name1(x,$1,,$2,x,$3)");
  resetdt($1)
  for_$1_colorvec{
    for(i = 0; i < MAX; i++)for(ic = 0; ic < nc; ic++){
      QLA_elem_$3(argt($3)[i],$3_list) = QLA_elem_$1(arg1($1)[i],$1_list);}
    qla_name1(x,$1,,$2,x,$3)(argd($1),idxd($1),argt($3),idx1($3),$1_list_cvec,MAX);
  }
  QLA_x$1_eq_x$1(argt($1),idxd($1),arg1($1),idx1($3),MAX);
  checkeqidx$1$1(argt($1),argd($1),name,fp);
#endif

  strcpy(name,"qla_name1(,$1,v,$2,p,$3)");
  resetdt($1)
  for_$1_colorvec{
    for(i = 0; i < MAX; i++)for(ic = 0; ic < nc; ic++){
      QLA_elem_$3(argt($3)[i],$3_list) = QLA_elem_$1(arg1($1)[i],$1_list);}
    qla_name1(,$1,v,$2,p,$3)(argd($1),argtp($3),$1_list_cvec,MAX);
  }
  /* QLA_$1_eq_x$1(argt($1),arg1($1),idx1($3),MAX); */
  for(i=0; i<MAX; i++) { QLA_$1_eq_$1(&argt($1)[i],arg1($1)+idx1($3)[i]); }
  checkeqidx$1$1(argt($1),argd($1),name,fp);

  strcpy(name,"qla_name1(,$1,x,$2,p,$3)");
  /* QLA_$1_eq_x$1(argd($1),arg1($1),idx1($3),MAX); */
  for(i=0; i<MAX; i++) { QLA_$1_eq_$1(&argd($1)[i],arg1($1)+idx1($3)[i]); }
  QLA_$1_xeq_$1(argt($1),argd($1),idx2($3),MAX);
  QLA_$1_veq_$1(argd($1),arg3($1),MAX);
  for_$1_colorvec{
    for(i=0;i<MAX;i++)for(ic = 0; ic < nc; ic++){
      QLA_elem_$3(argt($3)[i],$3_list) = QLA_elem_$1(arg1($1)[i],$1_list);}
    qla_name1(,$1,x,$2,p,$3)(argd($1),argtp($3),$1_list_cvec,idx2($3),MAX);
  }
  checkeqidx$1$1(argt($1),argd($1),name,fp);
')

rem(`
     Extracting Dirac vector
')
rem(`unary_get_diracvec(td,eq,t1)')
define(unary_get_diracvec,`
  /* qla_name1(,$1,,$2,,$3) */

  strcpy(name,"qla_name1(,$1,v,$2,,$3)");
  resetdt($3)
  for_$3_diracvec{
    qla_name1(,$1,v,$2,,$3)(argd($1),arg1($3),$3_list_dvec,MAX);
    for(i = 0; i < MAX; i++)for(ic=0;ic<nc;ic++)for(is=0;is<ns;is++){
      QLA_elem_$3(argt($3)[i],$3_list) = QLA_elem_$1(argd($1)[i],$1_list);}
  }
  QLA_$3_veq_$3(argd($3),arg1($3),MAX);
  checkeqidx$3$3(argt($3),argd($3),name,fp);

  strcpy(name,"qla_name1(,$1,x,$2,,$3)");
  resetdt($3)
  for_$3_diracvec{
    qla_name1(,$1,x,$2,,$3)(argd($1),arg1($3),$3_list_dvec,idx1($3),MAX);
    for(i = 0; i < MAX; i++)for(ic=0;ic<nc;ic++)for(is=0;is<ns;is++){
      QLA_elem_$3(argt($3)[i],$3_list) = QLA_elem_$1(argd($1)[i],$1_list);}
  }
  QLA_$3_xeq_$3(argd($3),arg1($3),idx1($3),MAX);
  checkeqidx$3$3(argt($3),argd($3),name,fp);

#ifdef QLA_INDEX_ALL
  strcpy(name,"qla_name1(x,$1,,$2,,$3)");
  resetdt($3)
  for_$3_diracvec{
    qla_name1(x,$1,,$2,,$3)(argd($1),idxd($1),arg1($3),$3_list_dvec,MAX);
    for(i = 0; i < MAX; i++)for(ic=0;ic<nc;ic++)for(is=0;is<ns;is++){
      QLA_elem_$3(argt($3)[i],$3_list) = QLA_elem_$1(argd($1)[i],$1_list);}
  }
  QLA_x$3_eq_$3(argd($3),idxd($1),arg1($3),MAX);
  checkeqidx$3$3(argt($3),argd($3),name,fp);

  strcpy(name,"qla_name1(,$1,,$2,x,$3)");
  resetdt($3)
  for_$3_diracvec{
    qla_name1(,$1,,$2,x,$3)(argd($1),arg1($3),idx1($3),$3_list_dvec,MAX);
    for(i = 0; i < MAX; i++)for(ic=0;ic<nc;ic++)for(is=0;is<ns;is++){
      QLA_elem_$3(argt($3)[i],$3_list) = QLA_elem_$1(argd($1)[i],$1_list);}
  }
  QLA_$3_eq_x$3(argd($3),arg1($3),idx1($3),MAX);
  checkeqidx$3$3(argt($3),argd($3),name,fp);

  strcpy(name,"qla_name1(x,$1,,$2,x,$3)");
  resetdt($3)
  for_$3_diracvec{
    qla_name1(x,$1,,$2,x,$3)(argd($1),idxd($1),arg1($3),idx1($3),$3_list_dvec,MAX);
    for(i = 0; i < MAX; i++)for(ic=0;ic<nc;ic++)for(is=0;is<ns;is++){
      QLA_elem_$3(argt($3)[i],$3_list) = QLA_elem_$1(argd($1)[i],$1_list);}
  }
  QLA_x$3_eq_x$3(argd($3),idxd($1),arg1($3),idx1($3),MAX);
  checkeqidx$3$3(argt($3),argd($3),name,fp);
#endif

  strcpy(name,"qla_name1(,$1,v,$2,p,$3)");
  resetdt($3)
  for_$3_diracvec{
    qla_name1(,$1,v,$2,p,$3)(argd($1),arg1p($3),$3_list_dvec,MAX);
    for(i = 0; i < MAX; i++)for(ic=0;ic<nc;ic++)for(is=0;is<ns;is++){
      QLA_elem_$3(argt($3)[i],$3_list) = QLA_elem_$1(argd($1)[i],$1_list);}
  }
  QLA_$3_veq_p$3(argd($3),arg1p($3),MAX);
  checkeqidx$3$3(argt($3),argd($3),name,fp);

  strcpy(name,"qla_name1(,$1,x,$2,p,$3)");
  resetdt($3)
  for_$3_diracvec{
    qla_name1(,$1,x,$2,p,$3)(argd($1),arg1p($3),$3_list_dvec,idx1($3),MAX);
    for(i = 0; i < MAX; i++)for(ic=0;ic<nc;ic++)for(is=0;is<ns;is++){
      QLA_elem_$3(argt($3)[i],$3_list) = QLA_elem_$1(argd($1)[i],$1_list);}
  }
  QLA_$3_xeq_p$3(argd($3),arg1p($3),idx1($3),MAX);
  checkeqidx$3$3(argt($3),argd($3),name,fp);
')

rem(`
     Inserting Dirac vector
')
rem(`unary_set_diracvec(td,eq,t1)')
define(unary_set_diracvec,`
  /* qla_name1(,$1,,$2,,$3) */

  strcpy(name,"qla_name1(,$1,v,$2,,$3)");
  resetdt($1)
  for_$1_diracvec{
    for(i = 0; i < MAX; i++)for(ic=0;ic<nc;ic++)for(is=0;is<ns;is++){
      QLA_elem_$3(argt($3)[i],$3_list) = QLA_elem_$1(arg1($1)[i],$1_list);}
    qla_name1(,$1,v,$2,,$3)(argd($1),argt($3),$1_list_dvec,MAX);
  }
  QLA_$1_veq_$1(argt($1),arg1($1),MAX);  
  checkeqidx$1$1(argt($1),argd($1),name,fp);

  strcpy(name,"qla_name1(,$1,x,$2,,$3)");
  resetdt($1)
  for_$1_diracvec{
    for(i = 0; i < MAX; i++)for(ic=0;ic<nc;ic++)for(is=0;is<ns;is++){
      QLA_elem_$3(argt($3)[i],$3_list) = QLA_elem_$1(arg1($1)[i],$1_list);}
    qla_name1(,$1,x,$2,,$3)(argd($1),argt($3),$1_list_dvec,idx1($3),MAX);
  }
  QLA_$1_xeq_$1(argt($1),arg1($1),idx1($3),MAX);
  checkeqidx$1$1(argt($1),argd($1),name,fp);

#ifdef QLA_INDEX_ALL
  strcpy(name,"qla_name1(x,$1,,$2,,$3)");
  resetdt($1)
  for_$1_diracvec{
    for(i = 0; i < MAX; i++)for(ic=0;ic<nc;ic++)for(is=0;is<ns;is++){
      QLA_elem_$3(argt($3)[i],$3_list) = QLA_elem_$1(arg1($1)[i],$1_list);}
    qla_name1(x,$1,,$2,,$3)(argd($1),idxd($1),argt($3),$1_list_dvec,MAX);
  }
  QLA_x$1_eq_$1(argt($1),idxd($1),arg1($1),MAX);
  checkeqidx$1$1(argt($1),argd($1),name,fp);

  strcpy(name,"qla_name1(,$1,,$2,x,$3)");
  resetdt($1)
  for_$1_diracvec{
    for(i = 0; i < MAX; i++)for(ic=0;ic<nc;ic++)for(is=0;is<ns;is++){
      QLA_elem_$3(argt($3)[i],$3_list) = QLA_elem_$1(arg1($1)[i],$1_list);}
    qla_name1(,$1,,$2,x,$3)(argd($1),argt($3),idx1($3),$1_list_dvec,MAX);
  }
  QLA_$1_eq_x$1(argt($1),arg1($1),idx1($3),MAX);
  checkeqidx$1$1(argt($1),argd($1),name,fp);

  strcpy(name,"qla_name1(x,$1,,$2,x,$3)");
  resetdt($1)
  for_$1_diracvec{
    for(i = 0; i < MAX; i++)for(ic=0;ic<nc;ic++)for(is=0;is<ns;is++){
      QLA_elem_$3(argt($3)[i],$3_list) = QLA_elem_$1(arg1($1)[i],$1_list);}
    qla_name1(x,$1,,$2,x,$3)(argd($1),idxd($1),argt($3),idx1($3),$1_list_dvec,MAX);
  }
  QLA_x$1_eq_x$1(argt($1),idxd($1),arg1($1),idx1($3),MAX);
  checkeqidx$1$1(argt($1),argd($1),name,fp);
#endif

  strcpy(name,"qla_name1(,$1,v,$2,p,$3)");
  resetdt($1)
  for_$1_diracvec{
    for(i = 0; i < MAX; i++)for(ic=0;ic<nc;ic++)for(is=0;is<ns;is++){
      QLA_elem_$3(argt($3)[i],$3_list) = QLA_elem_$1(arg1($1)[i],$1_list);}
    qla_name1(,$1,v,$2,p,$3)(argd($1),argtp($3),$1_list_dvec,MAX);
  }
  /* QLA_$1_eq_x$1(argt($1),arg1($1),idx1($3),MAX); */
  for(i=0; i<MAX; i++) { QLA_$1_eq_$1(&argt($1)[i],arg1($1)+idx1($3)[i]); }
  checkeqidx$1$1(argt($1),argd($1),name,fp);

  strcpy(name,"qla_name1(,$1,x,$2,p,$3)");
  /* QLA_$1_eq_x$1(argd($1),arg1($1),idx1($3),MAX); */
  for(i=0; i<MAX; i++) { QLA_$1_eq_$1(&argd($1)[i],arg1($1)+idx1($3)[i]); }
  QLA_$1_xeq_$1(argt($1),argd($1),idx2($3),MAX);
  QLA_$1_veq_$1(argd($1),arg3($1),MAX);
  for_$1_diracvec{
    for(i = 0; i < MAX; i++)for(ic=0;ic<nc;ic++)for(is=0;is<ns;is++){
      QLA_elem_$3(argt($3)[i],$3_list) = QLA_elem_$1(arg1($1)[i],$1_list);}
    qla_name1(,$1,x,$2,p,$3)(argd($1),argtp($3),$1_list_dvec,idx2($3),MAX);
  }
  checkeqidx$1$1(argt($1),argd($1),name,fp);
')

rem(`
     Spin projection
')
rem(`unary_spproj(td,eq,t1)')
define(unary_spproj,`
  /* qla_name1(,$1,,$2,,$3) */

  strcpy(name,"qla_name1(,$1,v,$2,,$3)");
  resetdt($1)
  for(mu=0;mu<5;mu++)for(sign=-1;sign<2;sign+=2){
    qla_name1(,$1,v,$2,,$3)(argd($1),arg1($3),mu,sign,MAX);
    for(i = 0; i < MAX; i++){qla_name1(,$1,,$2,,$3)(&argt($1)[i],&arg1($3)[i],mu,sign);}
    checkeqidx$1$1(argt($1),argd($1),name,fp);
  }

  strcpy(name,"qla_name1(,$1,x,$2,,$3)");
  resetdt($1)
  for(mu=0;mu<5;mu++)for(sign=-1;sign<2;sign+=2){
    qla_name1(,$1,x,$2,,$3)(argd($1),arg1($3),mu,sign,idx1($3),MAX);
    for(i = 0; i < MAX; i++){qla_name1(,$1,,$2,,$3)(&argt($1)[idx1($3)[i]],&arg1($3)[idx1($3)[i]],mu,sign);}
    checkeqidx$1$1(argt($1),argd($1),name,fp);
  }

#ifdef QLA_INDEX_ALL
  strcpy(name,"qla_name1(x,$1,,$2,,$3)");
  resetdt($1)
  for(mu=0;mu<5;mu++)for(sign=-1;sign<2;sign+=2){
    qla_name1(x,$1,,$2,,$3)(argd($1),idxd($1),arg1($3),mu,sign,MAX);
    for(i = 0; i < MAX; i++){qla_name1(,$1,,$2,,$3)(&argt($1)[idxd($1)[i]],&arg1($3)[i],mu,sign);}
    checkeqidx$1$1(argt($1),argd($1),name,fp);
  }

  strcpy(name,"qla_name1(,$1,,$2,x,$3)");
  resetdt($1)
  for(mu=0;mu<5;mu++)for(sign=-1;sign<2;sign+=2){
    qla_name1(,$1,,$2,x,$3)(argd($1),arg1($3),idx1($3),mu,sign,MAX);
    for(i = 0; i < MAX; i++){qla_name1(,$1,,$2,,$3)(&argt($1)[i],&arg1($3)[idx1($3)[i]],mu,sign);}
    checkeqidx$1$1(argt($1),argd($1),name,fp);
  }

  strcpy(name,"qla_name1(x,$1,,$2,x,$3)");
  resetdt($1)
  for(mu=0;mu<5;mu++)for(sign=-1;sign<2;sign+=2){
    qla_name1(x,$1,,$2,x,$3)(argd($1),idxd($1),arg1($3),idx1($3),mu,sign,MAX);
    for(i = 0; i < MAX; i++){qla_name1(,$1,,$2,,$3)(&argt($1)[idxd($1)[i]],&arg1($3)[idx1($3)[i]],mu,sign);}
    checkeqidx$1$1(argt($1),argd($1),name,fp);
  }
#endif

  strcpy(name,"qla_name1(,$1,v,$2,p,$3)");
  resetdt($1)
  for(mu=0;mu<5;mu++)for(sign=-1;sign<2;sign+=2){
    qla_name1(,$1,v,$2,p,$3)(argd($1),arg1p($3),mu,sign,MAX);
    for(i = 0; i < MAX; i++){qla_name1(,$1,,$2,,$3)(&argt($1)[i],arg1p($3)[i],mu,sign);}
    checkeqidx$1$1(argt($1),argd($1),name,fp);
  }

  strcpy(name,"qla_name1(,$1,x,$2,p,$3)");
  resetdt($1)
  for(mu=0;mu<5;mu++)for(sign=-1;sign<2;sign+=2){
    qla_name1(,$1,x,$2,p,$3)(argd($1),arg1p($3),mu,sign,idx1($3),MAX);
    for(i = 0; i < MAX; i++){qla_name1(,$1,,$2,,$3)(&argt($1)[idx1($3)[i]],arg1p($3)[idx1($3)[i]],mu,sign);}
    checkeqidx$1$1(argt($1),argd($1),name,fp);
  }

')

rem(`
     Spin reconstruction
')
rem(`unary_sprecon(td,eq,t1)')
define(unary_sprecon,`
  /* qla_name1(,$1,,$2,,$3) */

  strcpy(name,"qla_name1(,$1,v,$2,,$3)");
  resetdt($1)
  for(mu=0;mu<5;mu++)for(sign=-1;sign<2;sign+=2){
    qla_name1(,$1,v,$2,,$3)(argd($1),arg1($3),mu,sign,MAX);
    for(i = 0; i < MAX; i++){qla_name1(,$1,,$2,,$3)(&argt($1)[i],&arg1($3)[i],mu,sign);}
    checkeqidx$1$1(argt($1),argd($1),name,fp);
  }

  strcpy(name,"qla_name1(,$1,x,$2,,$3)");
  resetdt($1)
  for(mu=0;mu<5;mu++)for(sign=-1;sign<2;sign+=2){
    qla_name1(,$1,x,$2,,$3)(argd($1),arg1($3),mu,sign,idx1($3),MAX);
    for(i = 0; i < MAX; i++){qla_name1(,$1,,$2,,$3)(&argt($1)[idx1($3)[i]],&arg1($3)[idx1($3)[i]],mu,sign);}
    checkeqidx$1$1(argt($1),argd($1),name,fp);
  }

#ifdef QLA_INDEX_ALL
  strcpy(name,"qla_name1(x,$1,,$2,,$3)");
  resetdt($1)
  for(mu=0;mu<5;mu++)for(sign=-1;sign<2;sign+=2){
    qla_name1(x,$1,,$2,,$3)(argd($1),idxd($1),arg1($3),mu,sign,MAX);
    for(i = 0; i < MAX; i++){qla_name1(,$1,,$2,,$3)(&argt($1)[idxd($1)[i]],&arg1($3)[i],mu,sign);}
    checkeqidx$1$1(argt($1),argd($1),name,fp);
  }

  strcpy(name,"qla_name1(,$1,,$2,x,$3)");
  resetdt($1)
  for(mu=0;mu<5;mu++)for(sign=-1;sign<2;sign+=2){
    qla_name1(,$1,,$2,x,$3)(argd($1),arg1($3),idx1($3),mu,sign,MAX);
    for(i = 0; i < MAX; i++){qla_name1(,$1,,$2,,$3)(&argt($1)[i],&arg1($3)[idx1($3)[i]],mu,sign);}
    checkeqidx$1$1(argt($1),argd($1),name,fp);
  }

  strcpy(name,"qla_name1(x,$1,,$2,x,$3)");
  resetdt($1)
  for(mu=0;mu<5;mu++)for(sign=-1;sign<2;sign+=2){
    qla_name1(x,$1,,$2,x,$3)(argd($1),idxd($1),arg1($3),idx1($3),mu,sign,MAX);
    for(i = 0; i < MAX; i++){qla_name1(,$1,,$2,,$3)(&argt($1)[idxd($1)[i]],&arg1($3)[idx1($3)[i]],mu,sign);}
    checkeqidx$1$1(argt($1),argd($1),name,fp);
  }
#endif

  strcpy(name,"qla_name1(,$1,v,$2,p,$3)");
  resetdt($1)
  for(mu=0;mu<5;mu++)for(sign=-1;sign<2;sign+=2){
    qla_name1(,$1,v,$2,p,$3)(argd($1),arg1p($3),mu,sign,MAX);
    for(i = 0; i < MAX; i++){qla_name1(,$1,,$2,,$3)(&argt($1)[i],arg1p($3)[i],mu,sign);}
    checkeqidx$1$1(argt($1),argd($1),name,fp);
  }

  strcpy(name,"qla_name1(,$1,x,$2,p,$3)");
  resetdt($1)
  for(mu=0;mu<5;mu++)for(sign=-1;sign<2;sign+=2){
    qla_name1(,$1,x,$2,p,$3)(argd($1),arg1p($3),mu,sign,idx1($3),MAX);
    for(i = 0; i < MAX; i++){qla_name1(,$1,,$2,,$3)(&argt($1)[idx1($3)[i]],arg1p($3)[idx1($3)[i]],mu,sign);}
    checkeqidx$1$1(argt($1),argd($1),name,fp);
  }

')

rem(`
     Spin projection with matrix multiply
')
rem(`binary_spproj(td,eq,t1,adj,func,t2)')
define(binary_spproj,`
  /* qla_name2(,$1,,$2,,$3$4,$5,,$6) */

  strcpy(name,"qla_name2(,$1,v,$2,,$3$4,$5,,$6)");
  resetdt($1)
  for(mu=0;mu<5;mu++)for(sign=-1;sign<2;sign+=2){
    qla_name2(,$1,v,$2,,$3$4,$5,,$6)(argd($1),arg1($3),arg1($6),mu,sign,MAX);
    for(i = 0; i < MAX; i++) {
      qla_name2(,$1,,$2,,$3$4,$5,,$6)(&argt($1)[i],&arg1($3)[i],&arg1($6)[i],mu,sign);
    }
    checkeqidx$1$1(argt($1),argd($1),name,fp);
  }

  strcpy(name,"qla_name2(,$1,x,$2,,$3$4,$5,,$6)");
  resetdt($1)
  for(mu=0;mu<5;mu++)for(sign=-1;sign<2;sign+=2){
    qla_name2(,$1,x,$2,,$3$4,$5,,$6)(argd($1),arg1($3),arg1($6),mu,sign,idx1($6),MAX);
    for(i = 0; i < MAX; i++) {
      qla_name2(,$1,,$2,,$3$4,$5,,$6)(&argt($1)[idx1($6)[i]],&arg1($3)[idx1($6)[i]],&arg1($6)[idx1($6)[i]],mu,sign);}
    checkeqidx$1$1(argt($1),argd($1),name,fp);
  }

#ifdef QLA_INDEX_ALL
  strcpy(name,"qla_name2(x,$1,,$2,,$3$4,$5,,$6)");
  resetdt($1)
  for(mu=0;mu<5;mu++)for(sign=-1;sign<2;sign+=2){
    qla_name2(x,$1,,$2,,$3$4,$5,,$6)(argd($1),idxd($1),arg1($3),arg1($6),mu,sign,MAX);
    for(i = 0; i < MAX; i++){
      qla_name2(,$1,,$2,,$3$4,$5,,$6)(&argt($1)[idxd($1)[i]],&arg1($3)[i],&arg1($6)[i],mu,sign);}
    checkeqidx$1$1(argt($1),argd($1),name,fp);
  }

  strcpy(name,"qla_name2(,$1,,$2,x,$3$4,$5,,$6)");
  resetdt($1)
  for(mu=0;mu<5;mu++)for(sign=-1;sign<2;sign+=2){
    qla_name2(,$1,,$2,x,$3$4,$5,,$6)(argd($1),arg1($3),idx1($3),arg1($6),mu,sign,MAX);
    for(i = 0; i < MAX; i++){
      qla_name2(,$1,,$2,,$3$4,$5,,$6)(&argt($1)[i],&arg1($3)[idx1($3)[i]],&arg1($6)[i],mu,sign);}
    checkeqidx$1$1(argt($1),argd($1),name,fp);
  }

  strcpy(name,"qla_name2(,$1,,$2,,$3$4,$5,x,$6)");
  resetdt($1)
  for(mu=0;mu<5;mu++)for(sign=-1;sign<2;sign+=2){
    qla_name2(,$1,,$2,,$3$4,$5,x,$6)(argd($1),arg1($3),arg1($6),idx1($6),mu,sign,MAX);
    for(i = 0; i < MAX; i++){
      qla_name2(,$1,,$2,,$3$4,$5,,$6)(&argt($1)[i],&arg1($3)[i],&arg1($6)[idx1($6)[i]],mu,sign);}
    checkeqidx$1$1(argt($1),argd($1),name,fp);
  }

  strcpy(name,"qla_name2(x,$1,,$2,x,$3$4,$5,,$6)");
  resetdt($1)
  for(mu=0;mu<5;mu++)for(sign=-1;sign<2;sign+=2){
    qla_name2(x,$1,,$2,x,$3$4,$5,,$6)(argd($1),idxd($1),arg1($3),idxd($3),arg1($6),mu,sign,MAX);
    for(i = 0; i < MAX; i++){
      qla_name2(,$1,,$2,,$3$4,$5,,$6)(&argt($1)[idxd($1)[i]],&arg1($3)[idxd($3)[i]],&arg1($6)[i],mu,sign);}
    checkeqidx$1$1(argt($1),argd($1),name,fp);
  }

  strcpy(name,"qla_name2(x,$1,,$2,,$3$4,$5,x,$6)");
  resetdt($1)
  for(mu=0;mu<5;mu++)for(sign=-1;sign<2;sign+=2){
    qla_name2(x,$1,,$2,,$3$4,$5,x,$6)(argd($1),idxd($1),arg1($3),arg1($6),idxd($6),mu,sign,MAX);
    for(i = 0; i < MAX; i++){
      qla_name2(,$1,,$2,,$3$4,$5,,$6)(&argt($1)[idxd($1)[i]],&arg1($3)[i],&arg1($6)[idxd($6)[i]],mu,sign);}
    checkeqidx$1$1(argt($1),argd($1),name,fp);
  }
#endif

  strcpy(name,"qla_name2(,$1,v,$2,p,$3$4,$5,,$6)");
  resetdt($1)
  for(mu=0;mu<5;mu++)for(sign=-1;sign<2;sign+=2){
    qla_name2(,$1,v,$2,p,$3$4,$5,,$6)(argd($1),arg1p($3),arg1($6),mu,sign,MAX);
    for(i = 0; i < MAX; i++){
      qla_name2(,$1,,$2,,$3$4,$5,,$6)(&argt($1)[i],arg1p($3)[i],&arg1($6)[i],mu,sign);}
    checkeqidx$1$1(argt($1),argd($1),name,fp);
  }

  strcpy(name,"qla_name2(,$1,v,$2,,$3$4,$5,p,$6)");
  resetdt($1)
  for(mu=0;mu<5;mu++)for(sign=-1;sign<2;sign+=2){
    qla_name2(,$1,v,$2,,$3$4,$5,p,$6)(argd($1),arg1($3),arg1p($6),mu,sign,MAX);
    for(i = 0; i < MAX; i++){
      qla_name2(,$1,,$2,,$3$4,$5,,$6)(&argt($1)[i],&arg1($3)[i],arg1p($6)[i],mu,sign);}
    checkeqidx$1$1(argt($1),argd($1),name,fp);
  }

  strcpy(name,"qla_name2(,$1,v,$2,p,$3$4,$5,p,$6)");
  resetdt($1)
  for(mu=0;mu<5;mu++)for(sign=-1;sign<2;sign+=2){
    qla_name2(,$1,v,$2,p,$3$4,$5,p,$6)(argd($1),arg1p($3),arg1p($6),mu,sign,MAX);
    for(i = 0; i < MAX; i++){
      qla_name2(,$1,,$2,,$3$4,$5,,$6)(&argt($1)[i],arg1p($3)[i],arg1p($6)[i],mu,sign);}
    checkeqidx$1$1(argt($1),argd($1),name,fp);
  }

  strcpy(name,"qla_name2(,$1,x,$2,p,$3$4,$5,,$6)");
  resetdt($1)
  for(mu=0;mu<5;mu++)for(sign=-1;sign<2;sign+=2){
    qla_name2(,$1,x,$2,p,$3$4,$5,,$6)(argd($1),arg1p($3),arg1($6),mu,sign,idx1($6),MAX);
    for(i = 0; i < MAX; i++){
      qla_name2(,$1,,$2,,$3$4,$5,,$6)(&argt($1)[idx1($6)[i]],arg1p($3)[idx1($6)[i]],&arg1($6)[idx1($6)[i]],mu,sign);}
    checkeqidx$1$1(argt($1),argd($1),name,fp);
  }

  strcpy(name,"qla_name2(,$1,x,$2,,$3$4,$5,p,$6)");
  resetdt($1)
  for(mu=0;mu<5;mu++)for(sign=-1;sign<2;sign+=2){
    qla_name2(,$1,x,$2,,$3$4,$5,p,$6)(argd($1),arg1($3),arg1p($6),mu,sign,idx1($6),MAX);
    for(i = 0; i < MAX; i++){
      qla_name2(,$1,,$2,,$3$4,$5,,$6)(&argt($1)[idx1($6)[i]],&arg1($3)[idx1($6)[i]],arg1p($6)[idx1($6)[i]],mu,sign);}
    checkeqidx$1$1(argt($1),argd($1),name,fp);
  }

  strcpy(name,"qla_name2(,$1,x,$2,p,$3$4,$5,p,$6)");
  resetdt($1)
  for(mu=0;mu<5;mu++)for(sign=-1;sign<2;sign+=2){
    qla_name2(,$1,x,$2,p,$3$4,$5,p,$6)(argd($1),arg1p($3),arg1p($6),mu,sign,idx1($6),MAX);
    for(i = 0; i < MAX; i++){
      qla_name2(,$1,,$2,,$3$4,$5,,$6)(&argt($1)[idx1($6)[i]],arg1p($3)[idx1($6)[i]],arg1p($6)[idx1($6)[i]],mu,sign);}
    checkeqidx$1$1(argt($1),argd($1),name,fp);
  }

')

rem(`
     Mult gamma left
')
rem(`unary_gammal(td,eq,t1)')
define(unary_gammal,`
  /* qla_name1(,$1,,$2_gamma_times,,$3) */

  strcpy(name,"qla_name1(,$1,v,$2_gamma_times,,$3)");
  resetdt($1)
  for(mu=0;mu<16;mu++){
    qla_name1(,$1,v,$2_gamma_times,,$3)(argd($1),arg1($3),mu,MAX);
    for(i = 0; i < MAX; i++){qla_name1(,$1,,$2_gamma_times,,$3)(&argt($1)[i],&arg1($3)[i],mu);}
    checkeqidx$1$1(argt($1),argd($1),name,fp);
  }

  strcpy(name,"qla_name1(,$1,x,$2_gamma_times,,$3)");
  resetdt($1)
  for(mu=0;mu<16;mu++){
    qla_name1(,$1,x,$2_gamma_times,,$3)(argd($1),arg1($3),mu,idx1($3),MAX);
    for(i = 0; i < MAX; i++){qla_name1(,$1,,$2_gamma_times,,$3)(&argt($1)[idx1($3)[i]],&arg1($3)[idx1($3)[i]],mu);}
    checkeqidx$1$1(argt($1),argd($1),name,fp);
  }

#ifdef QLA_INDEX_ALL
  strcpy(name,"qla_name1(x,$1,,$2_gamma_times,,$3)");
  resetdt($1)
  for(mu=0;mu<16;mu++){
    qla_name1(x,$1,,$2_gamma_times,,$3)(argd($1),idxd($1),arg1($3),mu,MAX);
    for(i = 0; i < MAX; i++){qla_name1(,$1,,$2_gamma_times,,$3)(&argt($1)[idxd($1)[i]],&arg1($3)[i],mu);}
    checkeqidx$1$1(argt($1),argd($1),name,fp);
  }

  strcpy(name,"qla_name1(,$1,,$2_gamma_times,x,$3)");
  resetdt($1)
  for(mu=0;mu<16;mu++){
    qla_name1(,$1,,$2_gamma_times,x,$3)(argd($1),arg1($3),idx1($3),mu,MAX);
    for(i = 0; i < MAX; i++){qla_name1(,$1,,$2_gamma_times,,$3)(&argt($1)[i],&arg1($3)[idx1($3)[i]],mu);}
    checkeqidx$1$1(argt($1),argd($1),name,fp);
  }

  strcpy(name,"qla_name1(x,$1,,$2_gamma_times,x,$3)");
  resetdt($1)
  for(mu=0;mu<16;mu++){
    qla_name1(x,$1,,$2_gamma_times,x,$3)(argd($1),idxd($1),arg1($3),idx1($3),mu,MAX);
    for(i = 0; i < MAX; i++){qla_name1(,$1,,$2_gamma_times,,$3)(&argt($1)[idxd($1)[i]],&arg1($3)[idx1($3)[i]],mu);}
    checkeqidx$1$1(argt($1),argd($1),name,fp);
  }
#endif

  strcpy(name,"qla_name1(,$1,v,$2_gamma_times,p,$3)");
  resetdt($1)
  for(mu=0;mu<16;mu++){
    qla_name1(,$1,v,$2_gamma_times,p,$3)(argd($1),arg1p($3),mu,MAX);
    for(i = 0; i < MAX; i++){qla_name1(,$1,,$2_gamma_times,,$3)(&argt($1)[i],arg1p($3)[i],mu);}
    checkeqidx$1$1(argt($1),argd($1),name,fp);
  }

  strcpy(name,"qla_name1(,$1,x,$2_gamma_times,p,$3)");
  resetdt($1)
  for(mu=0;mu<16;mu++){
    qla_name1(,$1,x,$2_gamma_times,p,$3)(argd($1),arg1p($3),mu,idx1($3),MAX);
    for(i = 0; i < MAX; i++){qla_name1(,$1,,$2_gamma_times,,$3)(&argt($1)[idx1($3)[i]],arg1p($3)[idx1($3)[i]],mu);}
    checkeqidx$1$1(argt($1),argd($1),name,fp);
  }

')

rem(`
     Mult gamma right
')
rem(`unary_gammar(td,eq,t1)')
define(unary_gammar,`
  /* qla_name1(,$1,,$2,,$3) */

  strcpy(name,"qla_name1(,$1,v,$2,,$3_times_gamma)");
  resetdt($1)
  for(mu=0;mu<16;mu++){
    qla_name1(,$1,v,$2,,$3_times_gamma)(argd($1),arg1($3),mu,MAX);
    for(i = 0; i < MAX; i++){qla_name1(,$1,,$2,,$3_times_gamma)(&argt($1)[i],&arg1($3)[i],mu);}
    checkeqidx$1$1(argt($1),argd($1),name,fp);
  }

  strcpy(name,"qla_name1(,$1,x,$2,,$3_times_gamma)");
  resetdt($1)
  for(mu=0;mu<16;mu++){
    qla_name1(,$1,x,$2,,$3_times_gamma)(argd($1),arg1($3),mu,idx1($3),MAX);
    for(i = 0; i < MAX; i++){qla_name1(,$1,,$2,,$3_times_gamma)(&argt($1)[idx1($3)[i]],&arg1($3)[idx1($3)[i]],mu);}
    checkeqidx$1$1(argt($1),argd($1),name,fp);
  }

#ifdef QLA_INDEX_ALL
  strcpy(name,"qla_name1(x,$1,,$2,,$3_times_gamma)");
  resetdt($1)
  for(mu=0;mu<16;mu++){
    qla_name1(x,$1,,$2,,$3_times_gamma)(argd($1),idxd($1),arg1($3),mu,MAX);
    for(i = 0; i < MAX; i++){qla_name1(,$1,,$2,,$3_times_gamma)(&argt($1)[idxd($1)[i]],&arg1($3)[i],mu);}
    checkeqidx$1$1(argt($1),argd($1),name,fp);
  }

  strcpy(name,"qla_name1(,$1,,$2,x,$3_times_gamma)");
  resetdt($1)
  for(mu=0;mu<16;mu++){
    qla_name1(,$1,,$2,x,$3_times_gamma)(argd($1),arg1($3),idx1($3),mu,MAX);
    for(i = 0; i < MAX; i++){qla_name1(,$1,,$2,,$3_times_gamma)(&argt($1)[i],&arg1($3)[idx1($3)[i]],mu);}
    checkeqidx$1$1(argt($1),argd($1),name,fp);
  }

  strcpy(name,"qla_name1(x,$1,,$2,x,$3_times_gamma)");
  resetdt($1)
  for(mu=0;mu<16;mu++){
    qla_name1(x,$1,,$2,x,$3_times_gamma)(argd($1),idxd($1),arg1($3),idx1($3),mu,MAX);
    for(i = 0; i < MAX; i++){qla_name1(,$1,,$2,,$3_times_gamma)(&argt($1)[idxd($1)[i]],&arg1($3)[idx1($3)[i]],mu);}
    checkeqidx$1$1(argt($1),argd($1),name,fp);
  }
#endif

  strcpy(name,"qla_name1(,$1,v,$2,p,$3_times_gamma)");
  resetdt($1)
  for(mu=0;mu<16;mu++){
    qla_name1(,$1,v,$2,p,$3_times_gamma)(argd($1),arg1p($3),mu,MAX);
    for(i = 0; i < MAX; i++){qla_name1(,$1,,$2,,$3_times_gamma)(&argt($1)[i],arg1p($3)[i],mu);}
    checkeqidx$1$1(argt($1),argd($1),name,fp);
  }

  strcpy(name,"qla_name1(,$1,x,$2,p,$3_times_gamma)");
  resetdt($1)
  for(mu=0;mu<16;mu++){
    qla_name1(,$1,x,$2,p,$3_times_gamma)(argd($1),arg1p($3),mu,idx1($3),MAX);
    for(i = 0; i < MAX; i++){qla_name1(,$1,,$2,,$3_times_gamma)(&argt($1)[idx1($3)[i]],arg1p($3)[idx1($3)[i]],mu);}
    checkeqidx$1$1(argt($1),argd($1),name,fp);
  }

')
