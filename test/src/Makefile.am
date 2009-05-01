M4SRC = compare.m4 test_int_idx.m4 test_scalar_idx.m4 \
        test_scalar_df_idx.m4 test_scalar_dq_idx.m4 \
        test_tensor_sng.m4 \
        test_tensor_idx1.m4 test_tensor_idx2.m4 \
        test_tensor_idx3.m4 test_tensor_idx4.m4 \
        test_tensor_df_sng.m4 test_tensor_df_idx.m4 \
        test_tensor_dq_sng.m4 test_tensor_dq_idx.m4
CSRC  = compare.c test_int_idx.c test_scalar_idx.c \
        test_scalar_df_idx.c test_scalar_dq_idx.c \
        test_tensor_sng.c \
        test_tensor_idx1.c test_tensor_idx2.c \
        test_tensor_idx3.c test_tensor_idx4.c \
        test_tensor_df_sng.c test_tensor_df_idx.c \
        test_tensor_dq_sng.c test_tensor_dq_idx.c

check-local: $(CSRC)
#	-cp -fp $(srcdir)/../checkcomplete.pl ..

CLEANFILES = $(CSRC)

EXTRA_DIST = $(M4SRC) tensor_args.m4 tensor_idx_defs.m4 \
             protocol_compare.m4 protocol_idx.m4 protocol_tensor_sng.m4 \
             compare.h milc_gamma.h milc_gamma.c \
             test_macros.c test_int_sng.c \
             test_scalar_sng.c test_scalar_df_sng.c test_scalar_dq_sng.c \
             test_tensor_idx.c

.m4.c:
	$(M4) -I$(srcdir) $< > $@

PSNGDEP = protocol_tensor_sng.m4 tensor_args.m4
PIDXDEP = protocol_idx.m4 tensor_args.m4
TIDXDEP = protocol_idx.m4 tensor_idx_defs.m4

compare.c: compare.m4 protocol_compare.m4
test_int_idx.c: test_int_idx.m4 $(PIDXDEP)
test_scalar_idx.c: test_scalar_idx.m4 $(PIDXDEP)
test_scalar_df_idx.c: test_scalar_df_idx.m4 $(PIDXDEP)
test_scalar_dq_idx.c: test_scalar_dq_idx.m4 $(PIDXDEP)
test_tensor_sng.c: test_tensor_sng.m4 $(PSNGDEP)
test_tensor_idx1.c: test_tensor_idx1.m4 $(TIDXDEP)
test_tensor_idx2.c: test_tensor_idx2.m4 $(TIDXDEP)
test_tensor_idx3.c: test_tensor_idx3.m4 $(TIDXDEP)
test_tensor_idx4.c: test_tensor_idx4.m4 $(TIDXDEP)
test_tensor_df_sng.c: test_tensor_df_sng.m4 $(PSNGDEP)
test_tensor_df_idx.c: test_tensor_df_idx.m4 $(PIDXDEP)
test_tensor_dq_sng.c: test_tensor_dq_sng.m4 $(PSNGDEP)
test_tensor_dq_idx.c: test_tensor_dq_idx.m4 $(PIDXDEP)
