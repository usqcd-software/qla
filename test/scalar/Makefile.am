CC = @TEST_CC@
CFLAGS = @TEST_CFLAGS@
AM_CFLAGS = -I$(top_srcdir)/test/src -I$(top_srcdir)/include

SRCDIR = ../../lib
QLAEXTRA = $(SRCDIR)/libqla_int.a \
           $(SRCDIR)/libqla_random.a \
           $(SRCDIR)/libqla_cmath.a \
           -lm $(SRCDIR)/libqla_c99.a
QLAF = $(SRCDIR)/libqla_f.a
QLAD = $(SRCDIR)/libqla_d.a
QLAQ = $(SRCDIR)/libqla_q.a
QLADF = $(QLAF) $(QLAD) $(SRCDIR)/libqla_df.a
QLADQ = $(QLAQ) $(QLAD) $(SRCDIR)/libqla_dq.a

check_PROGRAMS = test_macros \
                 test_scalar_f_sng test_scalar_f_idx \
                 test_scalar_d_sng test_scalar_d_idx \
                 test_scalar_q_sng test_scalar_q_idx \
                 test_scalar_df_sng test_scalar_df_idx \
                 test_scalar_dq_sng test_scalar_dq_idx

TESTS = check_macros check_f check_d check_q check_df check_dq

EXTRA_DIST = $(TESTS)

distclean-local:
	-rm -f results.*

CMPSRC = ../src/compare.c
SNGSRC = ../src/test_scalar_sng.c
IDXSRC = ../src/test_scalar_idx.c

# macros
nodist_test_macros_SOURCES = ../src/test_macros.c $(CMPSRC)
test_macros_CFLAGS = $(AM_CFLAGS) -DQLA_Precision=\'D\'
test_macros_LDADD = -lm

# f
nodist_test_scalar_f_sng_SOURCES = $(SNGSRC) $(CMPSRC)
test_scalar_f_sng_CFLAGS = $(AM_CFLAGS) -DQLA_Precision=\'F\'
test_scalar_f_sng_LDADD = $(QLADF) $(QLAEXTRA)

nodist_test_scalar_f_idx_SOURCES = $(IDXSRC) $(CMPSRC)
test_scalar_f_idx_CFLAGS = $(AM_CFLAGS) -DQLA_Precision=\'F\'
test_scalar_f_idx_LDADD = $(QLADF) $(QLAEXTRA)

# d
nodist_test_scalar_d_sng_SOURCES = $(SNGSRC) $(CMPSRC)
test_scalar_d_sng_CFLAGS = $(AM_CFLAGS) -DQLA_Precision=\'D\'
test_scalar_d_sng_LDADD = $(QLADQ) $(QLAEXTRA)

nodist_test_scalar_d_idx_SOURCES = $(IDXSRC) $(CMPSRC)
test_scalar_d_idx_CFLAGS = $(AM_CFLAGS) -DQLA_Precision=\'D\'
test_scalar_d_idx_LDADD = $(QLADQ) $(QLAEXTRA)

# q
nodist_test_scalar_q_sng_SOURCES = $(SNGSRC) $(CMPSRC)
test_scalar_q_sng_CFLAGS = $(AM_CFLAGS) -DQLA_Precision=\'Q\'
test_scalar_q_sng_LDADD = $(QLAQ) $(QLAEXTRA)

nodist_test_scalar_q_idx_SOURCES = $(IDXSRC) $(CMPSRC)
test_scalar_q_idx_CFLAGS = $(AM_CFLAGS) -DQLA_Precision=\'Q\'
test_scalar_q_idx_LDADD = $(QLAQ) $(QLAEXTRA)

# df
nodist_test_scalar_df_sng_SOURCES = ../src/test_scalar_df_sng.c $(CMPSRC)
test_scalar_df_sng_LDADD = $(QLADF) $(QLAEXTRA)

nodist_test_scalar_df_idx_SOURCES = ../src/test_scalar_df_idx.c $(CMPSRC)
test_scalar_df_idx_LDADD = $(QLADF) $(QLAEXTRA)

# dq
nodist_test_scalar_dq_sng_SOURCES = ../src/test_scalar_dq_sng.c $(CMPSRC)
test_scalar_dq_sng_LDADD = $(QLADQ) $(QLAEXTRA)

nodist_test_scalar_dq_idx_SOURCES = ../src/test_scalar_dq_idx.c $(CMPSRC)
test_scalar_dq_idx_LDADD = $(QLADQ) $(QLAEXTRA)
