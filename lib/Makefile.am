QLA_C0_DIRS = qla_f qla_d qla_q qla_df qla_dq
QLA_C2_DIRS = qla_f2 qla_d2 qla_q2 qla_df2 qla_dq2
QLA_C3_DIRS = qla_f3 qla_d3 qla_q3 qla_df3 qla_dq3
QLA_CN_DIRS = qla_fn qla_dn qla_qn qla_dfn qla_dqn
QLA_ALL_DIRS = $(QLA_C0_DIRS) $(QLA_C2_DIRS) $(QLA_C3_DIRS) $(QLA_CN_DIRS)

QLA_DIRS = qla_int $(QLA_C0_DIRS)
if NC2
  QLA_DIRS += $(QLA_C2_DIRS)
endif
if NC3
  QLA_DIRS += $(QLA_C3_DIRS)
endif
if NCN
  QLA_DIRS += $(QLA_CN_DIRS)
endif

SUBDIRS = \
	c99 \
	cmath \
	random \
	$(QLA_DIRS) \
	optimized \
	$(QLA_DIRS)

EXTRA_DIST = make_qla_dirs perl

