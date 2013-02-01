ALL_CFLAGS = -I$(top_srcdir)/include -I$(top_builddir)/include
ALL_LDADD = -L$(top_builddir)/lib -lqla_int -lqla_random -lm

F2_CFLAGS = -DQLA_PrecisionInt=1 -DQLA_Nc=2 $(ALL_CFLAGS)
F2_LDADD = -lqla_f -lqla_f2 -lqla_d -lqla_d2 -lqla_df -lqla_df2 $(ALL_LDADD)

D2_CFLAGS = -DQLA_PrecisionInt=2 -DQLA_Nc=2 $(ALL_CFLAGS)
D2_LDADD = -lqla_d -lqla_d2 -lqla_q -lqla_q2 -lqla_dq -lqla_dq2 $(ALL_LDADD)

F3_CFLAGS = -DQLA_PrecisionInt=1 -DQLA_Nc=3 $(ALL_CFLAGS)
F3_LDADD = -lqla_f -lqla_f3 -lqla_d -lqla_d3 -lqla_df -lqla_df3 $(ALL_LDADD)

D3_CFLAGS = -DQLA_PrecisionInt=2 -DQLA_Nc=3 $(ALL_CFLAGS)
D3_LDADD = -lqla_d -lqla_d3 -lqla_q -lqla_q3 -lqla_dq -lqla_dq3 $(ALL_LDADD)

FN_CFLAGS = -DQLA_PrecisionInt=1 -DQLA_Nc=23 $(ALL_CFLAGS)
FN_LDADD = -lqla_f -lqla_fn -lqla_d -lqla_dn -lqla_df -lqla_dfn $(ALL_LDADD)

DN_CFLAGS = -DQLA_PrecisionInt=2 -DQLA_Nc=23 $(ALL_CFLAGS)
DN_LDADD = -lqla_d -lqla_dn -lqla_q -lqla_qn -lqla_dq -lqla_dqn $(ALL_LDADD)

check_PROGRAMS =
if NC2
  check_PROGRAMS += qla_bench_f2 qla_bench_d2
endif
if NC3
  check_PROGRAMS += qla_bench_f3 qla_bench_d3
endif
if NCN
  check_PROGRAMS += qla_bench_fn qla_bench_dn
endif

qla_bench_f2_SOURCES = qla_bench.c
qla_bench_f2_CFLAGS = $(F2_CFLAGS)
qla_bench_f2_LDADD = $(F2_LDADD)

qla_bench_d2_SOURCES = qla_bench.c
qla_bench_d2_CFLAGS = $(D2_CFLAGS)
qla_bench_d2_LDADD = $(D2_LDADD)

qla_bench_f3_SOURCES = qla_bench.c
qla_bench_f3_CFLAGS = $(F3_CFLAGS)
qla_bench_f3_LDADD = $(F3_LDADD)

qla_bench_d3_SOURCES = qla_bench.c
qla_bench_d3_CFLAGS = $(D3_CFLAGS)
qla_bench_d3_LDADD = $(D3_LDADD)

qla_bench_fn_SOURCES = qla_bench.c
qla_bench_fn_CFLAGS = $(FN_CFLAGS)
qla_bench_fn_LDADD = $(FN_LDADD)

qla_bench_dn_SOURCES = qla_bench.c
qla_bench_dn_CFLAGS = $(DN_CFLAGS)
qla_bench_dn_LDADD = $(DN_LDADD)
