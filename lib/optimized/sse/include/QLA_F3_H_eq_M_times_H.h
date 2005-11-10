#define QLA_F3_H_eq_M_times_H(cc,aa,bb) { \
  int ic__; \
  for(ic__=0; ic__<3; ic__++) { \
    int is__; \
    for(is__=0; is__<QLA_Ns; is__++) { \
      QLA_F_Complex xc__; \
      int jc__; \
      QLA_c_eq_r(xc__,0.); \
      for(jc__=0; jc__<3; jc__++) { \
        QLA_c_peq_c_times_c(xc__, QLA_F3_elem_M(*(aa),ic__,jc__), QLA_F3_elem_H(*(bb),jc__,is__)); \
      } \
      QLA_c_eq_c(QLA_F3_elem_H(*(cc),ic__,is__),xc__); \
    } \
  } \
}
