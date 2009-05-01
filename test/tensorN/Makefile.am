c = n
NC = 4
CC = @TEST_CC@
CFLAGS = @TEST_CFLAGS@
AM_CFLAGS = -I$(top_srcdir)/test/src -I$(top_srcdir)/include

SRCDIR = ../../lib
QLAEXTRA = $(SRCDIR)/libqla_int.a \
           $(SRCDIR)/libqla_random.a \
           $(SRCDIR)/libqla_cmath.a \
           -lm $(SRCDIR)/libqla_c99.a
QLAF = $(SRCDIR)/libqla_f.a $(SRCDIR)/libqla_f$(c).a
QLAD = $(SRCDIR)/libqla_d.a $(SRCDIR)/libqla_d$(c).a
QLAQ = $(SRCDIR)/libqla_q.a $(SRCDIR)/libqla_q$(c).a
QLADF = $(QLAD) $(QLAF) $(SRCDIR)/libqla_df$(c).a
QLADQ = $(QLAD) $(QLAQ) $(SRCDIR)/libqla_dq$(c).a

check_PROGRAMS = test_tensor_f_sng test_tensor_f_idx \
                 test_tensor_d_sng test_tensor_d_idx \
                 test_tensor_q_sng test_tensor_q_idx \
                 test_tensor_df_sng test_tensor_df_idx \
                 test_tensor_dq_sng test_tensor_dq_idx

TESTS_ENVIRONMENT = @BACKEND_TEST_CMD@
TESTS = $(check_PROGRAMS)

distclean-local:
	-rm -f *.result

CMPSRC = ../src/compare.c
SNGSRC = ../src/test_tensor_sng.c ../src/milc_gamma.c
IDXSRC = ../src/test_tensor_idx.c \
         ../src/test_tensor_idx1.c ../src/test_tensor_idx2.c \
         ../src/test_tensor_idx3.c ../src/test_tensor_idx4.c

# f
nodist_test_tensor_f_sng_SOURCES = $(SNGSRC) $(CMPSRC)
test_tensor_f_sng_CFLAGS = $(AM_CFLAGS) -DQLA_Precision=\'F\' -DQLA_Nc=$(NC)
test_tensor_f_sng_LDADD = $(QLADF) $(QLAEXTRA)

nodist_test_tensor_f_idx_SOURCES = $(IDXSRC) $(CMPSRC)
test_tensor_f_idx_CFLAGS = $(AM_CFLAGS) -DQLA_Precision=\'F\' -DQLA_Nc=$(NC)
test_tensor_f_idx_LDADD = $(QLADF) $(QLAEXTRA)

# d
nodist_test_tensor_d_sng_SOURCES = $(SNGSRC) $(CMPSRC)
test_tensor_d_sng_CFLAGS = $(AM_CFLAGS) -DQLA_Precision=\'D\' -DQLA_Nc=$(NC)
test_tensor_d_sng_LDADD = $(QLADQ) $(QLAEXTRA)

nodist_test_tensor_d_idx_SOURCES = $(IDXSRC) $(CMPSRC)
test_tensor_d_idx_CFLAGS = $(AM_CFLAGS) -DQLA_Precision=\'D\' -DQLA_Nc=$(NC)
test_tensor_d_idx_LDADD = $(QLADQ) $(QLAEXTRA)

# q
nodist_test_tensor_q_sng_SOURCES = $(SNGSRC) $(CMPSRC)
test_tensor_q_sng_CFLAGS = $(AM_CFLAGS) -DQLA_Precision=\'Q\' -DQLA_Nc=$(NC)
test_tensor_q_sng_LDADD = $(QLAQ) $(QLAEXTRA)

nodist_test_tensor_q_idx_SOURCES = $(IDXSRC) $(CMPSRC)
test_tensor_q_idx_CFLAGS = $(AM_CFLAGS) -DQLA_Precision=\'Q\' -DQLA_Nc=$(NC)
test_tensor_q_idx_LDADD = $(QLAQ) $(QLAEXTRA)

# df
nodist_test_tensor_df_sng_SOURCES = ../src/test_tensor_df_sng.c $(CMPSRC)
test_tensor_df_sng_CFLAGS = $(AM_CFLAGS) -DQLA_Nc=$(NC)
test_tensor_df_sng_LDADD = $(QLADF) $(QLAEXTRA)

nodist_test_tensor_df_idx_SOURCES = ../src/test_tensor_df_idx.c $(CMPSRC)
test_tensor_df_idx_CFLAGS = $(AM_CFLAGS) -DQLA_Nc=$(NC)
test_tensor_df_idx_LDADD = $(QLADF) $(QLAEXTRA)

# dq
nodist_test_tensor_dq_sng_SOURCES = ../src/test_tensor_dq_sng.c $(CMPSRC)
test_tensor_dq_sng_CFLAGS = $(AM_CFLAGS) -DQLA_Nc=$(NC)
test_tensor_dq_sng_LDADD = $(QLADQ) $(QLAEXTRA)

nodist_test_tensor_dq_idx_SOURCES = ../src/test_tensor_dq_idx.c $(CMPSRC)
test_tensor_dq_idx_CFLAGS = $(AM_CFLAGS) -DQLA_Nc=$(NC)
test_tensor_dq_idx_LDADD = $(QLADQ) $(QLAEXTRA)

