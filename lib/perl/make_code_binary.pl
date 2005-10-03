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

    if($def{dim_name} ne "") {
      make_temp_ptr(%dest_def,$def{dest_name});
      make_temp_ptr(%src1_def,$def{src1_name});
      make_temp_ptr(%src2_def,$def{src2_name});
    }

    &print_val_eqop_val_op_val(*dest_def,$eqop,"",
			       *src1_def,$def{'op'},*src2_def);
    &print_end_matter($var_i,$def{'dim_name'});
}


#---------------------------------------------------------------------
# Build code for c eqop trace a dot b
#---------------------------------------------------------------------

sub make_code_binary_dot {
    local($eqop,$imre) = @_;
    local(%src1_mod_def) = %src1_def;
    local($t);

    # The dot product is accumulated in a complex or real type
    $t = &datatype_element_specific_abbr($dest_t);
#    $temp_def{'t'} = $datatype_scalar_abbrev{$t};
    $temp_def{'type'} = &datatype_specific($t);
    $temp_def{'value'} = $var_x;
    $temp_def{'rc'} = $dest_def{'rc'};

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
    &print_val_eqop_val_op_val(*temp_def,$eqop,$imre,*src1_mod_def,
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

sub make_code_spproj_sprecon_mult {
    local($eqop,$mu,$sign,$qualifier) = @_;
    local(%mytemp) = ();

    &print_top_matter($def{'declaration'},$var_i,$def{'dim_name'});

    #print QLA_SRC @indent, $src2_def{type}, " t;\n";
    print_def($src2_def{type}, "t");

    %mytemp = ();
    &load_arg_hash(*mytemp,'src2');
    $mytemp{value} = "t";

    if($def{dim_name} ne "") {
      make_temp_ptr(%dest_def,$def{dest_name});
      make_temp_ptr(%src1_def,$def{src1_name});
      make_temp_ptr(%src2_def,$def{src2_name});
    }

    print QLA_SRC @indent, "{\n";
    push @indent, "  ";
    &print_val_eqop_val_op_val( *mytemp, "eq", "",
				*src1_def, $def{'op'}, *src2_def );
    pop @indent;
    print QLA_SRC @indent, "}\n";

    print QLA_SRC @indent, "{\n";
    push @indent, "  ";
    if($def{'qualifier'} eq "spproj") {
      &print_val_assign_spproj( *dest_def, $eqop, *mytemp, $mu, $sign );
    } else {
      &print_val_assign_sprecon( *dest_def, $eqop, *mytemp, $mu, $sign );
    }
    pop @indent;
    print QLA_SRC @indent, "}\n";

    &print_end_matter($var_i,$def{'dim_name'});
}

#-----------------------------------------------------------------------
# Code for matrix multiply with Wilson spin multiply
#-----------------------------------------------------------------------

sub make_code_wilsonspin_mult {
    local($eqop,$mu,$sign) = @_;
    local(%mytemp1) = ();
    local(%mytemp2) = ();

    &load_arg_hash(*mytemp1,'src2');
    $mytemp1{t} = $datatype_halffermion_abbrev;
    $mytemp1{type} = &datatype_specific($mytemp1{t});
    %mytemp2 = %mytemp1;
    $mytemp1{value} = "t1";
    $mytemp2{value} = "t2";

    &print_top_matter($def{'declaration'},$var_i,$def{'dim_name'});

    print_def($mytemp1{type}, $mytemp1{value});
    print_def($mytemp2{type}, $mytemp2{value});

    if($def{dim_name} ne "") {
      make_temp_ptr(%dest_def,$def{dest_name});
      make_temp_ptr(%src1_def,$def{src1_name});
      make_temp_ptr(%src2_def,$def{src2_name});
    }

    print QLA_SRC @indent, "{\n";
    push @indent, "  ";
    &print_val_assign_spproj( *mytemp1, "eq", *src2_def, $mu, $sign );
    pop @indent;
    print QLA_SRC @indent, "}\n";

    print QLA_SRC @indent, "{\n";
    push @indent, "  ";
    &print_val_eqop_val_op_val( *mytemp2, "eq", "",
				*src1_def, $def{'op'}, *mytemp1 );
    pop @indent;
    print QLA_SRC @indent, "}\n";

    print QLA_SRC @indent, "{\n";
    push @indent, "  ";
    &print_val_assign_sprecon( *dest_def, $eqop, *mytemp2, $mu, $sign );
    pop @indent;
    print QLA_SRC @indent, "}\n";

    &print_end_matter($var_i,$def{'dim_name'});
}
