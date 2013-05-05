  set_fields;
  mem = 2*NC*(1+NC)*REALBYTES;
  flop = FLOP_EIG(NC);
  c = 1 + cf/(flop+mem);
  time1 = dtime();
  for(int i=0; i<c; ++i) {
    QLA_V_veq_eigenvals_M(v1, m1, n);
  }
  time1 = dtime() - time1;
  sum = sum_V(v1, n);
  printf("%-32s:", "QLA_V_veq_eigenvals_M");
  printf("%12g time=%5.2f mem=%5.0f mflops=%5.0f\n",
         sum, time1, mem*n*c/(1e6*time1), flop*n*c/(1e6*time1));

  setMH;
  set_fields;
  mem = 2*NC*(1+NC)*REALBYTES;
  flop = FLOP_EIGH(NC);
  c = 1 + cf/(flop+mem);
  time1 = dtime();
  for(int i=0; i<c; ++i) {
    QLA_V_veq_eigenvalsH_M(v1, m1, n);
  }
  time1 = dtime() - time1;
  sum = sum_V(v1, n);
  printf("%-32s:", "QLA_V_veq_eigenvalsH_M");
  printf("%12g time=%5.2f mem=%5.0f mflops=%5.0f\n",
         sum, time1, mem*n*c/(1e6*time1), flop*n*c/(1e6*time1));

  setM;
  set_fields;
  mem = 4*NC*NC*REALBYTES;
  flop = FLOP_INV(NC);
  c = 1 + cf/(flop+mem);
  time1 = dtime();
  for(int i=0; i<c; ++i) {
    QLA_M_veq_inverse_M(m1, m2, n);
  }
  time1 = dtime() - time1;
  sum = sum_M(m1, n);
  printf("%-32s:", "QLA_M_veq_inverse_M");
  printf("%12g time=%5.2f mem=%5.0f mflops=%5.0f\n",
         sum, time1, mem*n*c/(1e6*time1), flop*n*c/(1e6*time1));

  set_fields;
  mem = 4*NC*NC*REALBYTES;
  flop = FLOP_SQRT(NC);
  c = 1 + cf/(flop+mem);
  time1 = dtime();
  for(int i=0; i<c; ++i) {
    QLA_M_veq_sqrt_M(m1, m2, n);
  }
  time1 = dtime() - time1;
  sum = sum_M(m1, n);
  printf("%-32s:", "QLA_M_veq_sqrt_M");
  printf("%12g time=%5.2f mem=%5.0f mflops=%5.0f\n",
         sum, time1, mem*n*c/(1e6*time1), flop*n*c/(1e6*time1));

  setMPH;
  set_fields;
  mem = 4*NC*NC*REALBYTES;
  flop = FLOP_SQRTPH(NC);
  c = 1 + cf/(flop+mem);
  time1 = dtime();
  for(int i=0; i<c; ++i) {
    QLA_M_veq_sqrtPH_M(m1, m2, n);
  }
  time1 = dtime() - time1;
  sum = sum_M(m1, n);
  printf("%-32s:", "QLA_M_veq_sqrtPH_M");
  printf("%12g time=%5.2f mem=%5.0f mflops=%5.0f\n",
         sum, time1, mem*n*c/(1e6*time1), flop*n*c/(1e6*time1));

  setM;
  set_fields;
  mem = 4*NC*NC*REALBYTES;
  flop = FLOP_RSQRT(NC);
  c = 1 + cf/(flop+mem);
  time1 = dtime();
  for(int i=0; i<c; ++i) {
    QLA_M_veq_invsqrt_M(m1, m2, n);
  }
  time1 = dtime() - time1;
  sum = sum_M(m1, n);
  printf("%-32s:", "QLA_M_veq_invsqrt_M");
  printf("%12g time=%5.2f mem=%5.0f mflops=%5.0f\n",
         sum, time1, mem*n*c/(1e6*time1), flop*n*c/(1e6*time1));

  setMPH;
  set_fields;
  mem = 4*NC*NC*REALBYTES;
  flop = FLOP_RSQRTPH(NC);
  c = 1 + cf/(flop+mem);
  time1 = dtime();
  for(int i=0; i<c; ++i) {
    QLA_M_veq_invsqrtPH_M(m1, m2, n);
  }
  time1 = dtime() - time1;
  sum = sum_M(m1, n);
  printf("%-32s:", "QLA_M_veq_invsqrtPH_M");
  printf("%12g time=%5.2f mem=%5.0f mflops=%5.0f\n",
         sum, time1, mem*n*c/(1e6*time1), flop*n*c/(1e6*time1));

  setM;
  set_fields;
  mem = 4*NC*NC*REALBYTES;
  flop = FLOP_EXP(NC);
  c = 1 + cf/(flop+mem);
  time1 = dtime();
  for(int i=0; i<c; ++i) {
    QLA_M_veq_exp_M(m1, m2, n);
  }
  time1 = dtime() - time1;
  sum = sum_M(m1, n);
  printf("%-32s:", "QLA_M_veq_exp_M");
  printf("%12g time=%5.2f mem=%5.0f mflops=%5.0f\n",
         sum, time1, mem*n*c/(1e6*time1), flop*n*c/(1e6*time1));

  setMA;
  set_fields;
  mem = 4*NC*NC*REALBYTES;
  flop = FLOP_EXPA(NC);
  c = 1 + cf/(flop+mem);
  time1 = dtime();
  for(int i=0; i<c; ++i) {
    QLA_M_veq_expA_M(m1, m2, n);
  }
  time1 = dtime() - time1;
  sum = sum_M(m1, n);
  printf("%-32s:", "QLA_M_veq_expA_M");
  printf("%12g time=%5.2f mem=%5.0f mflops=%5.0f\n",
         sum, time1, mem*n*c/(1e6*time1), flop*n*c/(1e6*time1));

  setMTA;
  set_fields;
  mem = 4*NC*NC*REALBYTES;
  flop = FLOP_EXPTA(NC);
  c = 1 + cf/(flop+mem);
  time1 = dtime();
  for(int i=0; i<c; ++i) {
    QLA_M_veq_expTA_M(m1, m2, n);
  }
  time1 = dtime() - time1;
  sum = sum_M(m1, n);
  printf("%-32s:", "QLA_M_veq_expTA_M");
  printf("%12g time=%5.2f mem=%5.0f mflops=%5.0f\n",
         sum, time1, mem*n*c/(1e6*time1), flop*n*c/(1e6*time1));

  setM;
  set_fields;
  mem = 4*NC*NC*REALBYTES;
  flop = FLOP_LOG(NC);
  c = 1 + cf/(flop+mem);
  time1 = dtime();
  for(int i=0; i<c; ++i) {
    QLA_M_veq_log_M(m1, m2, n);
  }
  time1 = dtime() - time1;
  sum = sum_M(m1, n);
  printf("%-32s:", "QLA_M_veq_log_M");
  printf("%12g time=%5.2f mem=%5.0f mflops=%5.0f\n",
         sum, time1, mem*n*c/(1e6*time1), flop*n*c/(1e6*time1));

  set_fields;
  mem = 2*NC*(2+NC)*REALBYTES;
  flop = FLOP_INVV(NC);
  c = 1 + cf/(flop+mem);
  time1 = dtime();
  for(int i=0; i<c; ++i) {
    QLA_V_veq_M_inverse_V(v1, m1, v2, n);
  }
  time1 = dtime() - time1;
  sum = sum_V(v1, n);
  printf("%-32s:", "QLA_V_veq_M_inverse_V");
  printf("%12g time=%5.2f mem=%5.0f mflops=%5.0f\n",
         sum, time1, mem*n*c/(1e6*time1), flop*n*c/(1e6*time1));

  set_fields;
  mem = 6*NC*NC*REALBYTES;
  flop = FLOP_INVM(NC);
  c = 1 + cf/(flop+mem);
  time1 = dtime();
  for(int i=0; i<c; ++i) {
    QLA_M_veq_M_inverse_M(m1, m2, m3, n);
  }
  time1 = dtime() - time1;
  sum = sum_M(m1, n);
  printf("%-32s:", "QLA_M_veq_M_inverse_M");
  printf("%12g time=%5.2f mem=%5.0f mflops=%5.0f\n",
         sum, time1, mem*n*c/(1e6*time1), flop*n*c/(1e6*time1));

