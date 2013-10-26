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
nodist_include_HEADERS = \
 $(top_builddir)/include/qla_f1.h \
 $(top_builddir)/include/qla_f1_generic.h \
 $(top_builddir)/include/qla_f1_color_generic.h \
 $(top_builddir)/include/qla_f1_precision_generic.h \
 $(top_builddir)/include/qla_d1.h \
 $(top_builddir)/include/qla_d1_generic.h \
 $(top_builddir)/include/qla_d1_color_generic.h \
 $(top_builddir)/include/qla_d1_precision_generic.h \
 $(top_builddir)/include/qla_q1.h \
 $(top_builddir)/include/qla_q1_generic.h \
 $(top_builddir)/include/qla_q1_color_generic.h \
 $(top_builddir)/include/qla_q1_precision_generic.h \
 $(top_builddir)/include/qla_df1.h \
 $(top_builddir)/include/qla_df1_color_generic.h \
 $(top_builddir)/include/qla_dq1.h \
 $(top_builddir)/include/qla_dq1_color_generic.h
$(nodist_include_HEADERS): makeheaders
makeheaders:
	$(top_srcdir)/lib/perl/make_virtualNc $(PERL) $(top_srcdir)
clean-local:
	-rm -f $(nodist_include_HEADERS)
endif

SUBDIRS = \
	perl \
	c99 \
	cmath \
	random \
	$(QLA_DIRS) \
	optimized \
	$(QLA_DIRS) \
	.

EXTRA_DIST = make_qla_dirs
