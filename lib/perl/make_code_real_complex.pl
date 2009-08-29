######################################################################
# SciDAC Software Project
# BUILD_QLA Version 0.9
#
# make_code_real_comples.pl
#
# Author: C. DeTar
# Date:   09/13/02
######################################################################
#
# Building blocks for arithmetic expressions
# involving tensors
#
######################################################################
# Changes:
#
######################################################################
# Supporting files required:

require("expressions_tensor.pl");
require("expressions_scalar.pl");

######################################################################

#---------------------------------------------------------------------
# Code for real to complex conversion and vice versa
#---------------------------------------------------------------------

sub make_code_real2complex {
    my($eqop) = @_;
    
    my($dest_value,$src1_value,$src2_value) = 
	($dest_def{'value'},$src1_def{'value'},$src2_def{'value'});

    &print_top_matter($def{'declaration'},$var_i,$def{'dim_name'});
    &print_c_eqop_r_plus_ir($dest_value,$eqop,
			    $src1_value,$src2_value);
    &print_end_matter($var_i,$def{'dim_name'});
}

#---------------------------------------------------------------------
# Code to extract real and imaginary parts
#---------------------------------------------------------------------

sub make_code_imre_part {
    my($eqop,$imre) = @_;
    
    my($dest_value,$src1_value) = ($dest_def{'value'},$src1_def{'value'});
    my($rc_d,$rc_s1) = ($dest_def{'rc'},$src1_def{'rc'});

    &print_top_matter($def{'declaration'},$var_i,$def{'dim_name'});
    &print_s_eqop_s($rc_d,$dest_value,$eqop,$imre,$rc_s1,$src1_value,"");
    &print_end_matter($var_i,$def{'dim_name'});
}

#---------------------------------------------------------------------
# Code to extract trace of colormatrix matrix (full, real, or imag)
#---------------------------------------------------------------------

sub make_code_colormatrix_trace {
    my($eqop,$imre) = @_;

    &print_top_matter($def{'declaration'},$var_i,$def{'dim_name'});
    &print_val_assign_tr(*dest_def,$eqop,$imre,*src1_def);
    &print_end_matter($var_i,$def{'dim_name'});
}

#---------------------------------------------------------------------
# Code to extract spin trace of propagator matrix (full, real, or imag)
#---------------------------------------------------------------------

sub make_code_spin_trace {
    my($eqop,$imre) = @_;

    &print_top_matter($def{'declaration'},$var_i,$def{'dim_name'});
    &print_val_assign_spin_tr(*dest_def,$eqop,$imre,*src1_def);
    &print_end_matter($var_i,$def{'dim_name'});
}

1;
