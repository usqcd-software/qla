#----------------------------------------------------------------------------
# Copyright (c) 2002      SciDAC Software Coordinating Committee
#
#
#
#
#
#
#----------------------------------------------------------------------------
#
# Description:
#      Top level Makefile for testing the code
#
# Authors:  
#      Carleton DeTar & James Osborn
#      University of Utah
#
# Revision History:
#   $Log$
#   Revision 1.2  2005/11/28 22:18:28  osborn
#   Changes to perl code and test suite.  Preparing for 1.5.0.
#
#   Revision 1.1  2005/04/27 17:47:46  osborn
#   (Hopefully) Last set of files added.
#
#   
#   
#   
#
#---------------------------------------------------------------------
#

TDIRS =

if NC2
  TDIRS += tensor2
endif

if NC3
  TDIRS += tensor3
endif

if NCN
  TDIRS += tensorN
endif

SUBDIRS = src int scalar $(TDIRS) .

EXTRA_DIST = README checkcomplete.pl check_all

TESTS = check_all

#distclean-local:
#	-if [ "X$(srcdir)" != "X." ]; then rm -f checkcomplete.pl; fi
