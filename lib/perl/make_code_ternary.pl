######################################################################
# SciDAC Software Project
# BUILD_QLA Version 0.9
#
# make_code_ternary.pl
#
# Author: C. DeTar
# Date:   09/13/02
######################################################################
#
# Top level code generation for ternary operation
#
######################################################################
# Changes:
#
######################################################################
# Supporting files required:

use strict;

require("formatting.pl");
require("variable_names.pl");
require("expressions_tensor.pl");

use vars qw/ %def %dest_def %src1_def %src2_def %src3_def /;
use vars qw/ $var_i /;

######################################################################

#---------------------------------------------------------------------
# Build code for c eqop a op b op2 c
#---------------------------------------------------------------------

sub make_code_ternary {
    my($eqop) = @_;

    &print_top_matter($def{'declaration'}, $var_i, $def{'dim_name'});
    &print_val_eqop_val_op_val_op2_val(\%dest_def, $eqop, \%src1_def,
				       $def{'op'}, \%src2_def,
				       $def{'op2'}, \%src3_def);
    &print_end_matter($var_i, $def{'dim_name'});
}
