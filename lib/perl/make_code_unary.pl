######################################################################
# SciDAC Software Project
# BUILD_QLA Version 0.9
#
# make_code_unary.pl
#
# Author: C. DeTar
# Date:   09/13/02
######################################################################
#
# Top level code generation for unary operation
#
######################################################################
# Changes:
#
######################################################################
# Supporting files required:

require("formatting.pl");
require("variable_names.pl");
require("expressions_scalar.pl");
require("expressions_tensor.pl");
require("expressions_gamma.pl");
require("datatypes.pl");
require("headers.pl");

######################################################################

#---------------------------------------------------------------------
# Code for standard assignment (with operators)
#---------------------------------------------------------------------

sub make_code_unary {
  local($eqop,$qualifier) = @_;

  &print_top_matter($def{'declaration'},$var_i,$def{'dim_name'});
  if($def{dim_name} ne "") {
    make_temp_ptr(*dest_def,$def{dest_name});
    make_temp_ptr(*src1_def,$def{src1_name});
  }
  &print_val_eqop_op_val(*dest_def,$eqop,*src1_def,$qualifier);
  &print_end_matter($var_i,$def{'dim_name'});
}

#---------------------------------------------------------------------
# Code for traceless antihermitian part of gauge matrix
#---------------------------------------------------------------------

sub make_code_antiherm_part {
    local($eqop) = @_;

    &print_top_matter($def{'declaration'},$var_i,$def{'dim_name'});
    &print_g_eqop_antiherm_g($eqop);
    &print_end_matter($var_i,$def{'dim_name'});
}

#---------------------------------------------------------------------
# Code for assignment from or to individual matrix or vector elements
#---------------------------------------------------------------------

sub make_code_getset_component {
    local($eqop,$ic,$is,$jc,$js,$qualifier) = @_;
    
    &print_top_matter($def{'declaration'},$var_i,$def{'dim_name'});
    &print_val_getset_component(*dest_def,$eqop,*src1_def,
				$ic,$is,$jc,$js,$qualifier);
    &print_end_matter($var_i,$def{'dim_name'});
}

#---------------------------------------------------------------------
# Code for elementary function of real or complex
#---------------------------------------------------------------------

# (These functions all take double precision arguments)

sub make_code_unary_fcn {
    local($eqop,$unary_fcn) = @_;

    local($dest_value,$src1_value) = ($dest_def{'value'},$src1_def{'value'});
    local($temp_dest_type,$temp_src1_type,$macro,$math_name);

    ($rc_d,$rc_s1) = ($dest_def{'rc'},$src1_def{'rc'});

    &print_top_matter($def{'declaration'},$var_i,$def{'dim_name'});

    # Use macros for functions mapping complex -> real

    $macro = $carith0{$unary_fcn};
    if($rc_d eq "r" && $rc_s1 eq "c" && defined($macro)){
	print QLA_SRC @indent,"$dest_value = $macro($src1_value);\n";
    }
    else{
	# Type conversion for a complex result requires an intermediate
	$temp_dest_type = &datatype_specific($dest_def{'t'},
					     $precision_double_abbrev);
	if($rc_d eq "c" && $temp_dest_type ne $dest_def{'type'}){
	    &print_def($temp_dest_type,$var_x2);
	}
	# If type conversion to double is needed, define intermediate
	$temp_src1_type = &datatype_specific($src1_def{'t'},
					     $precision_double_abbrev);
	if($temp_src1_type ne $src1_def{'type'}){
	    # (Can't be a register variable)
	    print QLA_SRC @indent,"$temp_src1_type $var_x;\n";
	    &print_s_eqop_s($rc_s1,$var_x,$eqop_eq,"",
			    $rc_s1,$src1_value,"");
	    $src1_value = $var_x;
	}

	# Pass pointers for complex arguments
	if($rc_s1 eq "c"){
	    $src1_value = "&($src1_value)";
	}
	
	# Use function name from table - defaults to given name
	$math_name = $unary_cmath{$unary_fcn};
	if(!defined($math_name)){$math_name = $unary_fcn;}

	# Exception: build inline sign function (of reals)

	if($math_name eq "sign"){
	    $src1_value = "$src1_value >= 0 ? 1. : -1.";
	}
	else{
	    $src1_value = "$math_name($src1_value)";
	}
	
	# Type conversion for a complex result uses the intermediate
	if($rc_d eq "c" && $temp_dest_type ne $dest_def{'type'}){
	    print QLA_SRC @indent,"$var_x2 = $src1_value;\n";
	    &print_s_eqop_s($rc_d,$dest_value,$eqop_eq,"",
			    $rc_d,$var_x2,"");
	}
	else{
	    print QLA_SRC @indent,"$dest_value = $src1_value;\n";
	}
    }
    &print_end_matter($var_i,$def{'dim_name'});
}

#---------------------------------------------------------------------
# Code for Dirac spin projection and reconstruction
#---------------------------------------------------------------------

sub spproj_func {
  local($sign, $dir, $eqop) = @_;
  &print_def_open_iter($var_i,$def{'dim_name'});
  if($def{dim_name} ne "") {
    make_temp_ptr(*dest_def,$def{dest_name});
    make_temp_ptr(*src1_def,$def{src1_name});
  }
  $ic = &get_row_color_index(*src1_def);
  &print_int_def($ic);
  $maxic = $src1_def{'mc'};
  &open_iter($ic,$maxic);
  print_val_assign_spproj_dirs(*dest_def, *src1_def, $sign, $dir, $eqop);
  &close_iter($ic);
  if($def{'dim_name'} ne "") {
    &close_iter($var_i);
  }
}

sub sprecon_func {
  local($sign, $dir, $eqop) = @_;
  &print_def_open_iter($var_i,$def{'dim_name'});
  if($def{dim_name} ne "") {
    make_temp_ptr(*dest_def,$def{dest_name});
    make_temp_ptr(*src1_def,$def{src1_name});
  }
  $ic = &get_row_color_index(*src1_def);
  &print_int_def($ic);
  $maxic = $src1_def{'mc'};
  &open_iter($ic,$maxic);
  print_val_assign_sprecon_dirs(*dest_def, *src1_def, $sign, $dir, $eqop);
  &close_iter($ic);
  if($def{'dim_name'} ne "") {
    &close_iter($var_i);
  }
}

sub make_code_spproj_sprecon {
    local($eqop,$mu,$sign,$qualifier) = @_;

    &print_very_top_matter($def{'declaration'},$var_i,$def{'dim_name'});

    if($def{'qualifier'} eq "spproj") {
      &print_val_assign_spin($eqop, $mu, $sign, \&spproj_func);
    } else {
      &print_val_assign_spin($eqop, $mu, $sign, \&sprecon_func);
    }

    &print_very_end_matter($var_i,$def{'dim_name'});
}

#-----------------------------------------------------------------------
# Code for Wilson spin multiply
#-----------------------------------------------------------------------

sub wilsonspin_func {
  local($sign, $dir, $eqop) = @_;
  &print_def_open_iter($var_i,$def{'dim_name'});
  if($def{dim_name} ne "") {
    make_temp_ptr(*dest_def,$def{dest_name});
    make_temp_ptr(*src1_def,$def{src1_name});
  }
  $ic = &get_row_color_index(*src1_def);
  &print_int_def($ic);
  $maxic = $src1_def{'mc'};
  &open_iter($ic,$maxic);
  print_def($mytemp{type}, $mytemp{value});
  print_val_assign_spproj_dirs(*mytemp, *src1_def, $sign, $dir, "eq");
  print_val_assign_sprecon_dirs(*dest_def, *mytemp, $sign, $dir, $eqop);
  &close_iter($ic);
  if($def{'dim_name'} ne "") {
    &close_iter($var_i);
  }
}

sub make_code_wilsonspin {
    local($eqop,$mu,$sign) = @_;
    %mytemp = ();

    &load_arg_hash(*mytemp,'src1');
    $mytemp{t} = $datatype_halffermion_abbrev;
    $mytemp{type} = &datatype_specific($mytemp{t});
    $mytemp{value} = "t";

    &print_very_top_matter($def{'declaration'},$var_i,$def{'dim_name'});

    &print_val_assign_spin($eqop, $mu, $sign, \&wilsonspin_func);

    &print_very_end_matter($var_i,$def{'dim_name'});
}

#---------------------------------------------------------------------
# Code for left or right multiplication by gamma matrix
#---------------------------------------------------------------------

sub mult_gamma_func {
  local($eqop, $leftright, $g) = @_;

  &print_def_open_iter($var_i,$def{'dim_name'});
  if($def{dim_name} ne "") {
    make_temp_ptr(*dest_def,$def{dest_name});
    make_temp_ptr(*src1_def,$def{src1_name});
  }

  print_val_assign_gamma_times_dirs(*dest_def,*src1_def,$eqop,$leftright,$g);

  if($def{'dim_name'} ne "") {
    &close_iter($var_i);
  }
}

sub make_code_mult_gamma {
    local($eqop,$mu,$leftright) = @_;

    &print_very_top_matter($def{'declaration'},$var_i,$def{'dim_name'});
    &print_val_assign_gamma_times($eqop, $mu, $leftright, \&mult_gamma_func);
    &print_very_end_matter($var_i,$def{'dim_name'});
}

#---------------------------------------------------------------------
# Code for norm2 reduction or global sum
#---------------------------------------------------------------------

sub make_code_norm2_global_sum {
    local($eqop) = @_;

    local($global_type);
    local(%global_def) = %dest_def;

    # The global variable inherits dest attributes, except for type and name
    # We accumulate global sums in the next higher precision relative to src1
    local($higher_precision) = $precision_promotion{$precision};
    $global_type = &datatype_specific($dest_t,$higher_precision);
    $global_def{'type'} = $global_type;
    $global_def{'value'} = $var_global_sum;

    &open_src_file;
    &print_function_def($def{'declaration'});
    &print_nonregister_def($global_type,$var_global_sum);
    &print_fill(*global_def,"zero");

    &open_brace();
    &open_block();
    &print_def_open_iter($var_i,$def{'dim_name'});

    # Accumulate reduced result in global variable
    if($def{'qualifier'} eq "norm2"){
	# dest must be real in this case
	&print_val_eqop_norm2_val(*global_def,$eqop_peq,*src1_def);
    }
    elsif($def{'qualifier'} eq "sum"){
	&print_val_eqop_op_val(*global_def,$eqop_peq,*src1_def,"identity");
    }
    else{
	die "Can't do $def{'qualifier'}\n";
    }

    if($def{'dim_name'} ne ""){&close_iter($var_i);}

    &close_block();
    &close_brace();

    &open_brace();
    &open_block();

    # Assign reduced result to dest
    &print_val_eqop_op_val(*dest_def,$eqop,*global_def,"identity");

    &close_block();
    &close_brace();

    &close_brace();
    &close_src_file;
}

#---------------------------------------------------------------------
# Build code for c eqop not a
#---------------------------------------------------------------------

sub make_code_boolean_not {
    local($eqop) = @_;

    &print_top_matter($def{'declaration'},$var_i,$def{'dim_name'});
    # Only integer operands supported here
    &print_s_eqop_s("r",$dest_def{'value'},$eqop,"","r",
		    "! $src1_def{'value'}");
    &print_end_matter($var_i,$def{'dim_name'});
}

1;
