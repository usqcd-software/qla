######################################################################
# SciDAC Software Project
# BUILD_QLA Version 0.9
#
# make_code_binary.pl
#
# Author: C. DeTar
# Date:   09/13/02
######################################################################
#
# Top level code generation for binary operation
#
######################################################################
# Changes:
#
######################################################################
# Supporting files required:

require("formatting.pl");
require("variable_names.pl");
require("expressions_tensor.pl");
require("expressions_scalar.pl");

######################################################################

#---------------------------------------------------------------------
# Build code for c eqop a op b
#---------------------------------------------------------------------

sub make_code_binary {
    local($eqop) = @_;

    &print_top_matter($def{'declaration'},$var_i,$def{'dim_name'});

    #if($def{dim_name} ne "") {
    #  make_temp_ptr(%dest_def,$def{dest_name});
    #  make_temp_ptr(%src1_def,$def{src1_name});
    #  make_temp_ptr(%src2_def,$def{src2_name});
    #}

    &print_val_eqop_val_op_val(*dest_def,$eqop,"",
			       *src1_def,$def{'op'},*src2_def);
    &print_end_matter($var_i,$def{'dim_name'});
}


#---------------------------------------------------------------------
# Build code for c eqop trace a dot b
#---------------------------------------------------------------------

sub make_code_binary_dot {
    local($eqop,$imre) = @_;
    local($global_type);
    local(%src1_mod_def) = %src1_def;
    local(%temp_def) = %dest_def;

    # The global variable inherits dest attributes, except for type and name
    # We accumulate global sums in the next higher precision relative to src1
    local($higher_precision) = $precision_promotion{$precision};
    $global_type = &datatype_specific($dest_t,$higher_precision);
    $temp_def{'type'} = $global_type;
    $temp_def{'value'} = $var_x;
    $temp_def{'precision'} = $higher_precision;

    # For the dot product the adjoint of src1 is understood
    $src1_mod_def{'adj'} = "a";
    $src1_mod_def{'conj'} = "a";
    $src1_mod_def{'trans'} = "t";
    $src1_mod_def{'mc'} = $src1_def{'nc'};
    $src1_mod_def{'nc'} = $src1_def{'mc'};
    $src1_mod_def{'ms'} = $src1_def{'ns'};
    $src1_mod_def{'ns'} = $src1_def{'ms'};

    &print_top_matter($def{'declaration'},$var_i,$def{'dim_name'});
    &print_nonregister_def($temp_def{'type'},$temp_def{'value'});
    &print_fill(*temp_def,"zero");

    # Compute dot product
    &open_brace();
    &print_val_eqop_val_op_val(*temp_def,$eqop_eq,$imre,*src1_mod_def,
			       "dot",*src2_def);
    &close_brace();

    # Assign result
    &print_val_eqop_op_val(*dest_def,$eqop,*temp_def,"identity");

    &print_end_matter($var_i,$def{'dim_name'});
}

#---------------------------------------------------------------------
# Build code for reduction c eqop sum trace a dot b
#---------------------------------------------------------------------

sub make_code_binary_dot_global {
    local($eqop,$imre) = @_;
    local($global_type);
    local(%global_def) = %dest_def;
    local(%src1_mod_def) = %src1_def;

    # The global variable inherits dest attributes, except for type and name
    # We accumulate global sums in the next higher precision relative to src1
    local($higher_precision) = $precision_promotion{$precision};
    $global_type = &datatype_specific($dest_t,$higher_precision);
    $global_def{'type'} = $global_type;
    $global_def{'value'} = $var_x;
    $global_def{'precision'} = $higher_precision;

    # For the dot product the adjoint of src1 is understood
    $src1_mod_def{'adj'} = "a";
    $src1_mod_def{'conj'} = "a";
    $src1_mod_def{'trans'} = "t";
    $src1_mod_def{'mc'} = $src1_def{'nc'};
    $src1_mod_def{'nc'} = $src1_def{'mc'};
    $src1_mod_def{'ms'} = $src1_def{'ns'};
    $src1_mod_def{'ns'} = $src1_def{'ms'};

    &open_src_file;
    &print_function_def($def{'declaration'});
    &print_nonregister_def($global_type,$var_x);
    &print_fill(*global_def,"zero");

    &open_brace();
    &open_block();
    &print_def_open_iter($var_i,$def{'dim_name'});

    # Accumulate reduced result in global variable
    &print_val_eqop_val_op_val(*global_def,$eqop_peq,$imre,*src1_mod_def,
			       "dot",*src2_def);

    if($def{'dim_name'} ne ""){
	&close_iter($var_i);
    }

    &close_block();
    &close_brace();

    # Assign reduced result to dest
    &print_val_eqop_op_val(*dest_def,$eqop,*global_def,"identity");
    &close_brace();
    &close_src_file;
}

#---------------------------------------------------------------------
# Build code for c eqop a op b where c, a, b are integers or reals
#---------------------------------------------------------------------

sub make_code_binary_elementary {
    local($eqop) = @_;

    &print_top_matter($def{'declaration'},$var_i,$def{'dim_name'});
    &print_val_eqop_val_op_val_elementary(*dest_def,$eqop,*src1_def,
				      $def{'op'},*src2_def);
    &print_end_matter($var_i,$def{'dim_name'});
}

#-----------------------------------------------------------------------
# Code for matrix multiply with Dirac spin projection and reconstruction
#-----------------------------------------------------------------------

sub spproj_mult_func {
  local($sign, $dir, $eqop) = @_;
  &print_def_open_iter($var_i,$def{'dim_name'});
  &print_align_indx();
  print_def($mytemp{type}, $mytemp{value});
  if($def{dim_name} ne "") {
    make_temp_ptr(%dest_def,$def{dest_name});
    make_temp_ptr(%src1_def,$def{src1_name});
    make_temp_ptr(%src2_def,$def{src2_name});
  }
  $ic = &get_row_color_index(*src2_def);
  $maxic = $src1_def{'mc'};
  &open_brace();
  &print_int_def($ic);
  &open_iter($ic,$maxic);
  print_val_assign_spproj_dirs(*mytemp, *src2_def, $sign, $dir, "eq");
  &close_iter($ic);
  &close_brace();
  &open_brace();
  &print_val_eqop_val_op_val( *dest_def, $eqop, "",
			      *src1_def, $def{'op'}, *mytemp );
  &close_brace();
  if($def{'dim_name'} ne "") {
    &close_iter($var_i);
  }
}

sub sprecon_mult_func {
  local($sign, $dir, $eqop) = @_;
  &print_def_open_iter($var_i,$def{'dim_name'});
  &print_align_indx();
  print_def($mytemp{type}, $mytemp{value});
  if($def{dim_name} ne "") {
    make_temp_ptr(%dest_def,$def{dest_name});
    make_temp_ptr(%src1_def,$def{src1_name});
    make_temp_ptr(%src2_def,$def{src2_name});
  }
  $ic = &get_row_color_index(*src2_def);
  $maxic = $src1_def{'mc'};
  &open_brace();
  &print_val_eqop_val_op_val( *mytemp, "eq", "",
			      *src1_def, $def{'op'}, *src2_def );
  &close_brace();
  &open_brace();
  &print_int_def($ic);
  &open_iter($ic,$maxic);
  print_val_assign_sprecon_dirs(*dest_def, *mytemp, $sign, $dir, $eqop);
  &close_iter($ic);
  &close_brace();
  if($def{'dim_name'} ne "") {
    &close_iter($var_i);
  }
}

sub make_code_spproj_sprecon_mult {
    local($eqop,$mu,$sign,$qualifier) = @_;
    local(%mytemp) = ();

    &print_very_top_matter($def{'declaration'},$var_i,$def{'dim_name'});

    %mytemp = ();
    if($def{'qualifier'} eq "spproj") { &load_arg_hash(*mytemp,'dest'); }
    else { &load_arg_hash(*mytemp,'src2'); }
    $mytemp{type} = &datatype_specific($mytemp{t}, $temp_precision);
    $mytemp{value} = "t";
    $mytemp{precision} = $temp_precision;

    $dest_prec = $temp_precision;
    if($def{'qualifier'} eq "spproj") {
      &print_val_assign_spin($eqop, $mu, $sign, \&spproj_mult_func);
    } else {
      &print_val_assign_spin($eqop, $mu, $sign, \&sprecon_mult_func);
    }
    $dest_prec = '';

    &print_very_end_matter($var_i,$def{'dim_name'});
}

#-----------------------------------------------------------------------
# Code for matrix multiply with Wilson spin multiply
#-----------------------------------------------------------------------

sub wilsonspin_mult_func {
  local($sign, $dir, $eqop) = @_;
  &print_def_open_iter($var_i,$def{'dim_name'});
  &print_align_indx();
  print_def($mytemp1{type}, $mytemp1{value});
  print_def($mytemp2{type}, $mytemp2{value});
  if($def{dim_name} ne "") {
    make_temp_ptr(%dest_def,$def{dest_name});
    make_temp_ptr(%src1_def,$def{src1_name});
    make_temp_ptr(%src2_def,$def{src2_name});
  }
  $ic = &get_row_color_index(*src2_def);
  $maxic = $src1_def{'mc'};
  &open_brace();
  &print_int_def($ic);
  &open_iter($ic,$maxic);
  print_val_assign_spproj_dirs(*mytemp1, *src2_def, $sign, $dir, "eq");
  &close_iter($ic);
  &close_brace();
  &open_brace();
#  $noclose = 1;
  &print_val_eqop_val_op_val( *mytemp2, "eq", "",
			      *src1_def, $def{'op'}, *mytemp1 );
#  $noclose = 0;
#  &close_iter($is);
  &close_brace();
  &open_brace();
  &print_int_def($ic);
  &open_iter($ic,$maxic);
  print_val_assign_sprecon_dirs(*dest_def, *mytemp2, $sign, $dir, $eqop);
  &close_iter($ic);
  &close_brace();
  if($def{'dim_name'} ne "") {
    &close_iter($var_i);
  }
}

sub make_code_wilsonspin_mult {
    local($eqop,$mu,$sign) = @_;
    local(%mytemp1) = ();
    local(%mytemp2) = ();

    &load_arg_hash(*mytemp1,'src2');
    $def{t1_t} = $datatype_halffermion_abbrev;
    &max_color_spin_dim('t1','');
    &load_arg_hash(*mytemp1,'t1');
    $mytemp1{t} = $datatype_halffermion_abbrev;
    $mytemp1{type} = &datatype_specific($mytemp1{t}, $temp_precision);
    $mytemp1{precision} = $temp_precision;
    %mytemp2 = %mytemp1;
    $mytemp1{value} = "t1";
    $mytemp2{value} = "t2";

    &print_very_top_matter($def{'declaration'},$var_i,$def{'dim_name'});

    $dest_prec = $temp_precision;
    &print_val_assign_spin($eqop, $mu, $sign, \&wilsonspin_mult_func);
    $dest_prec = '';

    &print_very_end_matter($var_i,$def{'dim_name'});
}
