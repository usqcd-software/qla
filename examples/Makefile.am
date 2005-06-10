ALL_CFLAGS = -I$(top_srcdir)/include -I$(top_builddir)/include
ALL_LDADD = -L$(top_builddir)/lib -lqla_int -lqla_random -lm

F3_CFLAGS = -DQLA_Precision=1 -DQLA_Nc=3 $(ALL_CFLAGS)
F3_LDADD = -lqla_f -lqla_f3 -lqla_d -lqla_d3 -lqla_df -lqla_df3 $(ALL_LDADD)

check_PROGRAMS = qla_bench_f3

qla_bench_f3_SOURCES = qla_bench.c
qla_bench_f3_CFLAGS = $(F3_CFLAGS)
qla_bench_f3_LDADD = $(F3_LDADD)

