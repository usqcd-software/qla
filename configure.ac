# Process this file with autoconf to produce a configure script.

AC_INIT([qla],[1.5.0],[detar@physics.utah.edu])
AC_CONFIG_AUX_DIR(config)
AM_INIT_AUTOMAKE

AC_CONFIG_SRCDIR(include/qla.h)
AC_CONFIG_SRCDIR(lib/random/QLA_random.c)
AC_CONFIG_HEADERS([include/qla_config.h])

dnl --enable-sse
AC_ARG_ENABLE(
  sse,
  AC_HELP_STRING([--enable-sse],
    [use SSE instructions in certain routines (requires gcc)]),
  AC_SUBST(OPT_SSE, [$enableval]),
  AC_SUBST(OPT_SSE, [no])
)

dnl --enable-sse2
AC_ARG_ENABLE(
  sse2,
  AC_HELP_STRING([--enable-sse2],
    [use SSE and SSE2 instructions in certain routines (requires gcc)]),
  AC_SUBST(OPT_SSE2, [$enableval]),
  AC_SUBST(OPT_SSE2, [no])
)
if test "X$OPT_SSE2" != "Xno"; then OPT_SSE="yes"; fi

dnl --enable-440
AC_ARG_ENABLE(
  440,
  AC_HELP_STRING([--enable-440],
    [use PPC 440 instructions in certain routines (for QCDOC and BlueGene/L)]),
  AC_SUBST(OPT_440, [$enableval]),
  AC_SUBST(OPT_440, [no])
)

dnl --enable-nc=<ColorLib>
AC_ARG_ENABLE(
  nc,
  AC_HELP_STRING([--enable-nc],
    [make just the libraries necessary for the given color]),
  AC_SUBST(NC, [$enableval]),
  AC_SUBST(NC, [all])
)
if test "X$NC" = Xn -o "X$NC" = X1; then NC="N"; fi
if test `expr match $NC '[0-9]*$' \& $NC \> 3` -ne 0; then NC="N"; fi
if test "X$NC" != X2 -a "X$NC" != X3 -a "X$NC" != XN; then NC="all"; fi 

# Checks for programs.
AC_CHECK_TOOL(AR, ar, [ar])
AC_PROG_RANLIB
AC_PATH_PROG([PERL], [perl], [perl])
AC_PATH_PROG([M4], [m4], [m4])
AC_PATH_PROGS([LATEX], [latex2e latex], [latex])
if ! set | grep '^CFLAGS='; then ac_CFLAGS_not_set=1; fi
AC_PROG_CC([c99 gcc])
if test "X$ac_CFLAGS_not_set" = "X1"; then
  if test "X$GCC" = "Xyes"; then
    CFLAGS="-std=c99 -O2"
  else
    CFLAGS=-O
  fi
fi
if test "X$GNUCC" = "X"; then
  if test "X$GCC" = "Xyes"; then GNUCC="$CC"; else
    AC_PATH_PROG([GNUCC], [gcc], [gcc])
  fi
fi

# Checks for libraries.

# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.

AC_C_RESTRICT

# Checks for library functions.

# set makefile variables
AM_CONDITIONAL(OPT_SSE, [test "X$OPT_SSE" != "Xno"])
AM_CONDITIONAL(OPT_SSE2, [test "X$OPT_SSE2" != "Xno"])
AM_CONDITIONAL(OPT_440, [test "X$OPT_440" != "Xno"])
AM_CONDITIONAL(NC2, [test "X$NC" = "X2" -o "X$NC" = "Xall"])
AM_CONDITIONAL(NC3, [test "X$NC" = "X3" -o "X$NC" = "Xall"])
AM_CONDITIONAL(NCN, [test "X$NC" = "XN" -o "X$NC" = "Xall"])

# configuration files
AC_CONFIG_FILES(Makefile)
AC_CONFIG_FILES(bin/Makefile)
AC_CONFIG_FILES(bin/qla-config)
AC_CONFIG_FILES(doc/Makefile)
AC_CONFIG_FILES(examples/Makefile)
AC_CONFIG_FILES(include/Makefile)
AC_CONFIG_FILES(lib/Makefile)
AC_CONFIG_FILES(lib/c99/Makefile)
AC_CONFIG_FILES(lib/cmath/Makefile)
AC_CONFIG_FILES(lib/random/Makefile)
AC_CONFIG_FILES(lib/qla_int/Makefile)
AC_CONFIG_FILES(lib/qla_f/Makefile)
AC_CONFIG_FILES(lib/qla_f2/Makefile)
AC_CONFIG_FILES(lib/qla_f3/Makefile)
AC_CONFIG_FILES(lib/qla_fn/Makefile)
AC_CONFIG_FILES(lib/qla_d/Makefile)
AC_CONFIG_FILES(lib/qla_d2/Makefile)
AC_CONFIG_FILES(lib/qla_d3/Makefile)
AC_CONFIG_FILES(lib/qla_dn/Makefile)
AC_CONFIG_FILES(lib/qla_q/Makefile)
AC_CONFIG_FILES(lib/qla_q2/Makefile)
AC_CONFIG_FILES(lib/qla_q3/Makefile)
AC_CONFIG_FILES(lib/qla_qn/Makefile)
AC_CONFIG_FILES(lib/qla_df/Makefile)
AC_CONFIG_FILES(lib/qla_df2/Makefile)
AC_CONFIG_FILES(lib/qla_df3/Makefile)
AC_CONFIG_FILES(lib/qla_dfn/Makefile)
AC_CONFIG_FILES(lib/qla_dq/Makefile)
AC_CONFIG_FILES(lib/qla_dq2/Makefile)
AC_CONFIG_FILES(lib/qla_dq3/Makefile)
AC_CONFIG_FILES(lib/qla_dqn/Makefile)
AC_CONFIG_FILES(lib/optimized/Makefile)
AC_CONFIG_FILES(lib/optimized/c/Makefile)
AC_CONFIG_FILES(lib/optimized/sse/Makefile)
AC_CONFIG_FILES(lib/optimized/sse2/Makefile)
AC_CONFIG_FILES(lib/optimized/440/Makefile)
AC_CONFIG_FILES(test/Makefile)
AC_CONFIG_FILES(test/src/Makefile)
AC_CONFIG_FILES(test/int/Makefile)
AC_CONFIG_FILES(test/scalar/Makefile)
AC_CONFIG_FILES(test/tensor2/Makefile)
AC_CONFIG_FILES(test/tensor3/Makefile)
AC_CONFIG_FILES(test/tensorN/Makefile)

AC_OUTPUT
