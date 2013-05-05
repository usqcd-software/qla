  set_fields;
  mem = 16*NC*REALBYTES;
  flop = 8*NC;
  c = 1 + cf/(flop+mem);
  time1 = dtime();
  for(int i=0; i<c; ++i) {
    QLA_D_veq_r_times_D(d1, r1, d2, n);
  }
  time1 = dtime() - time1;
  sum = sum_D(d1, n);
  printf("%-32s:", "QLA_D_veq_r_times_D");
  printf("%12g time=%5.2f mem=%5.0f mflops=%5.0f\n",
         sum, time1, mem*n*c/(1e6*time1), flop*n*c/(1e6*time1));

  set_fields;
  mem = 2*(3+NC)*NC*REALBYTES;
  flop = 8*NC*NC;
  c = 1 + cf/(flop+mem);
  time1 = dtime();
  for(int i=0; i<c; ++i) {
    QLA_V_vpeq_M_times_pV(v1, m1, vp1, n);
  }
  time1 = dtime() - time1;
  sum = sum_V(v1, n);
  printf("%-32s:", "QLA_V_vpeq_M_times_pV");
  printf("%12g time=%5.2f mem=%5.0f mflops=%5.0f\n",
         sum, time1, mem*n*c/(1e6*time1), flop*n*c/(1e6*time1));

  set_fields;
  mem = 4*2*(3+NC)*NC*REALBYTES;
  flop = 4*8*NC*NC;
  c = 1 + cf/(flop+mem);
  time1 = dtime();
  for(int i=0; i<c; ++i) {
    QLA_V_vpeq_nM_times_npV(v1, ma, vpa, n, 4);
  }
  time1 = dtime() - time1;
  sum = sum_V(v1, n);
  printf("%-32s:", "QLA_V_vpeq_nM_times_npV");
  printf("%12g time=%5.2f mem=%5.0f mflops=%5.0f\n",
         sum, time1, mem*n*c/(1e6*time1), flop*n*c/(1e6*time1));

  set_fields;
  mem = 2*(2+NC)*NC*REALBYTES;
  flop = (8*NC-2)*NC;
  c = 1 + cf/(flop+mem);
  time1 = dtime();
  for(int i=0; i<c; ++i) {
    QLA_V_veq_Ma_times_V(v1, m1, v2, n);
  }
  time1 = dtime() - time1;
  sum = sum_V(v1, n);
  printf("%-32s:", "QLA_V_veq_Ma_times_V");
  printf("%12g time=%5.2f mem=%5.0f mflops=%5.0f\n",
         sum, time1, mem*n*c/(1e6*time1), flop*n*c/(1e6*time1));

  set_fields;
  mem = 6*NC*REALBYTES;
  flop = 2*NC;
  c = 1 + cf/(flop+mem);
  time1 = dtime();
  for(int i=0; i<c; ++i) {
    QLA_V_vmeq_pV(v1, vp1, n);
  }
  time1 = dtime() - time1;
  sum = sum_V(v1, n);
  printf("%-32s:", "QLA_V_vmeq_pV");
  printf("%12g time=%5.2f mem=%5.0f mflops=%5.0f\n",
         sum, time1, mem*n*c/(1e6*time1), flop*n*c/(1e6*time1));

  set_fields;
  mem = 12*NC*REALBYTES;
  flop = 4*NC;
  c = 1 + cf/(flop+mem);
  time1 = dtime();
  for(int i=0; i<c; ++i) {
    QLA_H_veq_spproj_D(h1, d1, 0, 1, n);
  }
  time1 = dtime() - time1;
  sum = sum_H(h1, n);
  printf("%-32s:", "QLA_H_veq_spproj_D");
  printf("%12g time=%5.2f mem=%5.0f mflops=%5.0f\n",
         sum, time1, mem*n*c/(1e6*time1), flop*n*c/(1e6*time1));

  set_fields;
  mem = 2*(10+NC)*NC*REALBYTES;
  flop = (16*NC+4)*NC;
  c = 1 + cf/(flop+mem);
  time1 = dtime();
  for(int i=0; i<c; ++i) {
    QLA_D_vpeq_sprecon_M_times_pH(d1, m1, hp1,0,1,n);
  }
  time1 = dtime() - time1;
  sum = sum_D(d1,n);
  printf("%-32s:", "QLA_D_vpeq_sprecon_M_times_pH");
  printf("%12g time=%5.2f mem=%5.0f mflops=%5.0f\n",
         sum, time1, mem*n*c/(1e6*time1), flop*n*c/(1e6*time1));

  set_fields;
  mem = 2*(12+NC)*NC*REALBYTES;
  flop = (16*NC+8)*NC;
  c = 1 + cf/(flop+mem);
  time1 = dtime();
  for(int i=0; i<c; ++i) {
    QLA_D_vpeq_spproj_M_times_pD(d1, m1, dp1,0,1,n);
  }
  time1 = dtime() - time1;
  sum = sum_D(d1,n);
  printf("%-32s:", "QLA_D_vpeq_spproj_M_times_pD");
  printf("%12g time=%5.2f mem=%5.0f mflops=%5.0f\n",
         sum, time1, mem*n*c/(1e6*time1), flop*n*c/(1e6*time1));

  set_fields;
  mem = 12*NC*REALBYTES;
  flop = 4*NC;
  c = 1 + cf/(flop+mem);
  time1 = dtime();
  for(int i=0; i<c; ++i) {
    QLA_D_vpeq_spproj_D(d1, d2, 4, 1, n);
  }
  time1 = dtime() - time1;
  sum = sum_D(d1, n);
  printf("%-32s:", "QLA_D_vpeq_spproj_D");
  printf("%12g time=%5.2f mem=%5.0f mflops=%5.0f\n",
         sum, time1, mem*n*c/(1e6*time1), flop*n*c/(1e6*time1));

  set_fields;
  mem = 6*NC*NC*REALBYTES;
  flop = (8*NC-2)*NC*NC;
  c = 1 + cf/(flop+mem);
  time1 = dtime();
  for(int i=0; i<c; ++i) {
    QLA_M_veq_M_times_pM(m1, m2, mp1, n);
  }
  time1 = dtime() - time1;
  sum = sum_M(m1, n);
  printf("%-32s:", "QLA_M_veq_M_times_pM");
  printf("%12g time=%5.2f mem=%5.0f mflops=%5.0f\n",
         sum, time1, mem*n*c/(1e6*time1), flop*n*c/(1e6*time1));

  set_fields;
  mem = 2*NC*REALBYTES;
  flop = 4*NC;
  c = 1 + cf/(flop+mem);
  time1 = dtime();
  for(int i=0; i<c; ++i) {
    QLA_r_veq_norm2_V(r1, v1, n);
  }
  time1 = dtime() - time1;
  sum = *r1;
  printf("%-32s:", "QLA_r_veq_norm2_V");
  printf("%12g time=%5.2f mem=%5.0f mflops=%5.0f\n",
         sum, time1, mem*n*c/(1e6*time1), flop*n*c/(1e6*time1));

  set_fields;
  mem = 4*NC*REALBYTES;
  flop = 8*NC;
  c = 1 + cf/(flop+mem);
  time1 = dtime();
  for(int i=0; i<c; ++i) {
    QLA_c_veq_V_dot_V(c1, v1, v2, n);
  }
  time1 = dtime() - time1;
  sum = QLA_norm2_c(*c1);
  printf("%-32s:", "QLA_c_veq_V_dot_V");
  printf("%12g time=%5.2f mem=%5.0f mflops=%5.0f\n",
         sum, time1, mem*n*c/(1e6*time1), flop*n*c/(1e6*time1));

  set_fields;
  mem = 2+2*NC*NC*REALBYTES;
  flop = FLOP_DET(NC);
  c = 1 + cf/(flop+mem);
  time1 = dtime();
  for(int i=0; i<c; ++i) {
    QLA_C_veq_det_M(c1, m1, n);
  }
  time1 = dtime() - time1;
  sum = sum_C(c1, n);
  printf("%-32s:", "QLA_C_veq_det_M");
  printf("%12g time=%5.2f mem=%5.0f mflops=%5.0f\n",
         sum, time1, mem*n*c/(1e6*time1), flop*n*c/(1e6*time1));

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

