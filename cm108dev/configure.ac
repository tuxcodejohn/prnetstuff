AC_INIT([cm108dev],[0.1])
AC_CONFIG_SRCDIR([test1/pttonoff.c])
#AC_CONFIG_HEADERS([src/config.h])
AC_GNU_SOURCE
#AH_TEMPLATE(DEBUG_NOT_ICNOVA,shall be set as long as not on\
            #real icnova platform)
AM_INIT_AUTOMAKE([ color-tests \
                  silent-rules \
                  parallel-tests])
AC_PROG_CC

#AC_CHECK_PROGS(gengetopt, gengetopt, [false])
#GENGETOPT=$gengetopt
#AC_SUBST(GENGETOPT)
AM_PROG_CC_C_O

AC_OUTPUT([
Makefile
test1/Makefile
])

