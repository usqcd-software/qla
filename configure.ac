# Process this file with autoconf to produce a configure script.

AC_INIT([qla],[1.7.0-a7],[josborn at physics.bu.edu])
AC_CONFIG_AUX_DIR(config)
AM_INIT_AUTOMAKE

AC_CONFIG_SRCDIR(include/qla.h)
AC_CONFIG_SRCDIR(lib/random/QLA_random.c)
AC_CONFIG_HEADERS([include/qla_config.h])


# build environment options

dnl --enable-backend-test-cmd
AC_ARG_ENABLE(
  backend_test_cmd,
  AC_HELP_STRING([--enable-backend-test-cmd=string],[specify the full command to submit test jobs to your system backend otherwise they will run on the frontend]),
  AC_SUBST(BACKEND_TEST_CMD, [$enableval])
  echo "using $BACKEND_TEST_CMD for submitting backend test runs",
)


# library options

dnl --enable-nc=<ColorLib>
AC_ARG_ENABLE(
  nc,
  AC_HELP_STRING([--enable-nc],
    [make just the libraries necessary for the given color]),
  AC_SUBST(NC, [$enableval]),
  AC_SUBST(NC, [all])
)
if test "X$NC" = Xn -o "X$NC" = X1; then NC="N"; fi
if test `expr $NC : '[0-9]*$' \& $NC \> 3` -ne 0; then NC="N"; fi
if test "X$NC" != X2 -a "X$NC" != X3 -a "X$NC" != XN; then NC="all"; fi 


# code options

dnl --enable-c99-complex
AC_ARG_ENABLE(
  c99-complex,
  AC_HELP_STRING([--enable-c99-complex],
    [define QLA_Complex types to be corresponding C99 complex type]),
  AC_SUBST(OPT_C99_COMPLEX, [$enableval]),
  AC_SUBST(OPT_C99_COMPLEX, [no])
)
if test "X$OPT_C99_COMPLEX" != "Xno"; then
  AC_DEFINE_UNQUOTED(USE_C99_COMPLEX, 1, [using C99 complex types])
fi

dnl --enable-temp-precision
AC_ARG_ENABLE(
  temp-precision,
  AC_HELP_STRING([--enable-temp-precision={F|D|Q}],
    [set internal precision for all compuations]),
  AC_SUBST(TEMP_PRECISION, [$enableval])
  echo "using $TEMP_PRECISION precision for temporaries",
)

dnl --enable-sse
AC_ARG_ENABLE(
  sse,
  AC_HELP_STRING([--enable-sse],
    [use SSE instructions in certain routines (requires icc or gcc)]),
  AC_SUBST(OPT_SSE, [$enableval]),
  AC_SUBST(OPT_SSE, [no])
)

dnl --enable-sse2
AC_ARG_ENABLE(
  sse2,
  AC_HELP_STRING([--enable-sse2],
    [use SSE and SSE2 instructions in certain routines (requires icc or gcc)]),
  AC_SUBST(OPT_SSE2, [$enableval]),
  AC_SUBST(OPT_SSE2, [no])
)

dnl --enable-sse3
AC_ARG_ENABLE(
  sse3,
  AC_HELP_STRING([--enable-sse3],
    [use SSE, SSE2 and SSE3 instructions in certain routines (requires icc or gcc)]),
  AC_SUBST(OPT_SSE3, [$enableval]),
  AC_SUBST(OPT_SSE3, [no])
)

if test "X$OPT_SSE3" != "Xno"; then OPT_SSE2="yes"; fi
if test "X$OPT_SSE2" != "Xno"; then OPT_SSE="yes"; fi
if test "X$OPT_SSE3" != "Xno"; then
  AC_DEFINE_UNQUOTED(QLA_SSE_LEVEL, 3, [SSE level])
elif test "X$OPT_SSE2" != "Xno"; then
  AC_DEFINE_UNQUOTED(QLA_SSE_LEVEL, 2, [SSE level])
elif test "X$OPT_SSE" != "Xno"; then
  AC_DEFINE_UNQUOTED(QLA_SSE_LEVEL, 1, [SSE level])
else
  AC_DEFINE_UNQUOTED(QLA_SSE_LEVEL, 0, [SSE level])
fi

dnl --enable-440
AC_ARG_ENABLE(
  440,
  AC_HELP_STRING([--enable-440],
    [use PPC 440 instructions in certain routines (for QCDOC and Blue Gene/L)]),
  AC_SUBST(OPT_440, [$enableval]),
  AC_SUBST(OPT_440, [no])
)

dnl --enable-440d
AC_ARG_ENABLE(
  440d,
  AC_HELP_STRING([--enable-440d],
    [use PPC 440d instructions in certain routines (for Blue Gene/L)]),
  AC_SUBST(OPT_440d, [$enableval]),
  AC_SUBST(OPT_440d, [no])
)
if test "X$OPT_440d" != "Xno"; then
  AC_DEFINE_UNQUOTED(HAVE_440D, 1, [compiling for 440d])
fi

dnl --enable-qpx
AC_ARG_ENABLE(
  qpx,
  AC_HELP_STRING([--enable-qpx],
    [use QPX instructions in certain routines (for Blue Gene/Q)]),
  AC_SUBST(OPT_QPX, [$enableval]),
  AC_SUBST(OPT_QPX, [no])
)
if test "X$OPT_QPX" != "Xno"; then
  AC_DEFINE_UNQUOTED(HAVE_QPX, 1, [compiling for qpx])
fi

dnl --enable-openmp
AC_ARG_ENABLE(
  openmp,
  AC_HELP_STRING([--enable-openmp],
    [generate OpenMP pragmas]),
  AC_SUBST(HAVE_OPENMP, [$enableval]),
  AC_SUBST(HAVE_OPENMP, [no])
)
if test "X$HAVE_OPENMP" != "Xno"; then
  AC_DEFINE_UNQUOTED(HAVE_OPENMP, 1, [using openmp])
fi


# compiler options

dnl --enable-xlc
AC_ARG_ENABLE(
  xlc,
  AC_HELP_STRING([--enable-xlc],
    [use XLC specific optimization features]),
  AC_SUBST(HAVE_XLC, [$enableval]),
  AC_SUBST(HAVE_XLC, [no])
)
if test "X$HAVE_XLC" != "Xno"; then
  AC_DEFINE_UNQUOTED(HAVE_XLC, 1, [using xlc])
fi


# Checks for programs.

AC_CHECK_TOOL(AR, ar, [ar])
AC_PROG_RANLIB
AC_PATH_PROG([PERL], [perl], [perl])
AC_PATH_PROG([M4], [m4], [m4])
AC_PATH_PROGS([LATEX], [latex2e latex], [latex])
#if ! set | grep '^CFLAGS='; then ac_CFLAGS_not_set=1; fi
AC_PROG_CC([c99 cc gcc])
#if test "X$ac_CFLAGS_not_set" = "X1"; then
#  if test "X$GCC" = "Xyes"; then
#    CFLAGS="-std=c99 -O2"
#  else
#    CFLAGS=-O
#  fi
#fi

AC_ARG_VAR(SSE_CC, [CC used for generating optimized SSE routines])
AC_ARG_VAR(SSE_CFLAGS, [CFLAGS used for generating optimized SSE routines])
AC_ARG_VAR(GNUCC, [CC used for compiling older double precision SSE routines (sse2)])
AC_ARG_VAR(TEST_CC, [CC used for library tests])
AC_ARG_VAR(TEST_CFLAGS, [CFLAGS used for library tests])

if test "X$SSE_CC" = "X"; then
  SSE_CC="$CC"
fi
if test "X$SSE_CFLAGS" = "X"; then
  SSE_CFLAGS="$CFLAGS"
fi
if test "X$GNUCC" = "X"; then
  if test "X$GCC" = "Xyes"; then GNUCC="$CC"; else
    AC_PATH_PROG([GNUCC], [gcc], [gcc])
  fi
fi
if test "X$TEST_CC" = "X"; then
  TEST_CC="$CC"
fi
if test "X$TEST_CFLAGS" = "X"; then
  TEST_CFLAGS="$CFLAGS"
fi
AM_PROG_CC_C_O

# Checks for libraries.

# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.

AC_PROG_CC_C99
AC_C_RESTRICT

# Checks for library functions.

# set makefile variables
AM_CONDITIONAL(OPT_SSE, [test "X$OPT_SSE" != "Xno"])
AM_CONDITIONAL(OPT_SSE2, [test "X$OPT_SSE2" != "Xno"])
AM_CONDITIONAL(OPT_440, [test "X$OPT_440" != "Xno"])
AM_CONDITIONAL(OPT_440d, [test "X$OPT_440d" != "Xno"])
AM_CONDITIONAL(OPT_QPX, [test "X$OPT_QPX" != "Xno"])
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
AC_CONFIG_FILES(lib/optimized/Makefile)
AC_CONFIG_FILES(lib/optimized/c/Makefile)
AC_CONFIG_FILES(lib/optimized/sse/Makefile)
AC_CONFIG_FILES(lib/optimized/sse2/Makefile)
AC_CONFIG_FILES(lib/optimized/440/Makefile)
AC_CONFIG_FILES(lib/optimized/440d/Makefile)
AC_CONFIG_FILES(lib/optimized/qpx/Makefile)
AC_CONFIG_FILES(lib/perl/defines.pl)
AC_CONFIG_FILES(lib/perl/Makefile)
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
AC_CONFIG_FILES(lib/random/Makefile)
AC_CONFIG_FILES(test/Makefile)
AC_CONFIG_FILES(test/src/Makefile)
AC_CONFIG_FILES(test/int/Makefile)
AC_CONFIG_FILES(test/scalar/Makefile)
AC_CONFIG_FILES(test/tensor2/Makefile)
AC_CONFIG_FILES(test/tensor3/Makefile)
AC_CONFIG_FILES(test/tensorN/Makefile)

AC_OUTPUT
