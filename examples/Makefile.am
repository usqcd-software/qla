ALL_CFLAGS = -I$(top_srcdir)/include -I$(top_builddir)/include
ALL_LDADD = -L$(top_builddir)/lib -lqla_int -lqla_cmath -lqla_random -lm

F1_CFLAGS = -DQLA_PrecisionInt=1 -DQLA_Nc=1 $(ALL_CFLAGS)
F1_LDADD = -lqla_dfn -lqla_fn -lqla_dn -lqla_df -lqla_f -lqla_d $(ALL_LDADD)

D1_CFLAGS = -DQLA_PrecisionInt=2 -DQLA_Nc=1 $(ALL_CFLAGS)
D1_LDADD = -lqla_dqn -lqla_dn -lqla_qn -lqla_dq -lqla_d -lqla_q $(ALL_LDADD)

F2_CFLAGS = -DQLA_PrecisionInt=1 -DQLA_Nc=2 $(ALL_CFLAGS)
F2_LDADD = -lqla_df2 -lqla_f2 -lqla_d2 -lqla_df -lqla_f -lqla_d $(ALL_LDADD)

D2_CFLAGS = -DQLA_PrecisionInt=2 -DQLA_Nc=2 $(ALL_CFLAGS)
D2_LDADD = -lqla_dq2 -lqla_d2 -lqla_q2 -lqla_dq -lqla_d -lqla_q $(ALL_LDADD)

F3_CFLAGS = -DQLA_PrecisionInt=1 -DQLA_Nc=3 $(ALL_CFLAGS)
F3_LDADD = -lqla_df3 -lqla_f3 -lqla_d3 -lqla_df -lqla_f -lqla_d $(ALL_LDADD)

D3_CFLAGS = -DQLA_PrecisionInt=2 -DQLA_Nc=3 $(ALL_CFLAGS)
D3_LDADD = -lqla_dq3 -lqla_d3 -lqla_q3 -lqla_dq -lqla_d -lqla_q $(ALL_LDADD)

FN_CFLAGS = -DQLA_PrecisionInt=1 -DQLA_Nc=4 $(ALL_CFLAGS)
FN_LDADD = -lqla_dfn -lqla_fn -lqla_dn -lqla_df -lqla_f -lqla_d $(ALL_LDADD)

DN_CFLAGS = -DQLA_PrecisionInt=2 -DQLA_Nc=4 $(ALL_CFLAGS)
DN_LDADD = -lqla_dqn -lqla_dn -lqla_qn -lqla_dq -lqla_d -lqla_q $(ALL_LDADD)

check_PROGRAMS =
if NC2
  check_PROGRAMS += qla_bench_f2 qla_bench_d2
endif
if NC3
  check_PROGRAMS += qla_bench_f3 qla_bench_d3
endif
if NCN
  check_PROGRAMS += qla_bench_fn qla_bench_dn qla_bench_f1 qla_bench_d1
endif

qla_bench_f1_SOURCES = qla_bench.c
qla_bench_f1_CFLAGS = $(F1_CFLAGS)
qla_bench_f1_LDADD = $(F1_LDADD)

qla_bench_d1_SOURCES = qla_bench.c
qla_bench_d1_CFLAGS = $(D1_CFLAGS)
qla_bench_d1_LDADD = $(D1_LDADD)

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

EXTRA_DIST = benchfuncs.c
