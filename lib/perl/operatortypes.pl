######################################################################
# SciDAC Software Project
# BUILD_QLA Version 0.9
#
# operatortypes.pl
#
# Author: C. DeTar
# Date:   09/13/02
######################################################################
#
# Defines notation for operators in function names
# 
#
######################################################################
# Changes:
#
######################################################################
# Supporting files required:

######################################################################

# Suffix for adjoint
$suffix_adjoint = 'a';

# Separation character for fields
$dash = "_";

# Abbreviation for replacement operations
$eqop_eq  = 'eq';
$eqop_peq = 'peq';
$eqop_eqm = 'eqm';
$eqop_meq = 'meq';

@eqop_all = ( $eqop_eq, $eqop_peq, $eqop_eqm, $eqop_meq );


# Math symbolic notation for replacement operations
%eqop_notation = (
		  $eqop_eq,  '=',
		  $eqop_peq, '+=',
		  $eqop_eqm, '=-',
		  $eqop_meq, '-='
		  );

