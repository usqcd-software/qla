######################################################################
# SciDAC Software Project
# BUILD_QLA Version 0.9
#
# expressions_tensor.pl
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

require("variable_names.pl");
require("headers.pl");
require("formatting.pl");
require("operatortypes.pl");
require("expressions_scalar.pl");

######################################################################

#---------------------------------------------------------------------
# Unary assignment (with op)
#---------------------------------------------------------------------

sub print_val_eqop_op_val {
    local(*dest_def,$eqop,*src1_def,$qualifier) = @_;

    local($dest_elem_value,$src1_elem_value);

    # Operand dimensions

    local($mcd,$msd,$ncd,$nsd) = @dest_def{'mc','ms','nc','ns'};
    local($mc1,$ms1,$nc1,$ns1) = @src1_def{'mc','ms','nc','ns'};

    # Color spin indices
    local($ic,$is,$jc,$js) = &get_color_spin_indices(*dest_def);

    # Real or complex matrix element
    local($rc_d,$rc_s1) = ($dest_def{'rc'},$src1_def{'rc'});

    # Check consistency of dimensions
    if($src1_def{'t'} ne "" && $qualifier ne "diagfill" && 
       $qualifier ne "gaussian"&& $qualifier ne "random" 
       && $qualifier ne "seed"){

	$mcd eq $mc1 && $msd eq $ms1 && $ncd eq $nc1 && $nsd eq $ns1 ||
	    die "incompatible types in assignment\n";
    }

    # Open iteration over destination row indices
    &print_int_def($is); &open_iter($is,$msd);
    &print_int_def($ic); &open_iter($ic,$mcd);

    # Open iteration over destination column indices, if needed
    &print_int_def($js); &open_iter($js,$nsd);
    &print_int_def($jc); &open_iter($jc,$ncd);

    $dest_elem_value = &make_accessor(*dest_def,$def{'nc'},$ic,$is,$jc,$js);
    $src1_elem_value = &make_accessor(*src1_def,$def{'nc'},$ic,$is,$jc,$js);

    # Build alternate expression for source if necessary

    if($qualifier eq "zero" || $qualifier eq "diagfill"){
	$src1_elem_value = "0."; $rc_s1 = "r";
    }

    elsif($qualifier eq "random"){
	$src1_elem_value = "$fcn_random(&($src1_def{'value'}))";
	$rc_s1 = "r";  # fcn_random returns real
    }

    elsif($qualifier eq "gaussian"){
	$src1_elem_value = "$fcn_gaussian(&($src1_def{'value'}))";
	$rc_s1 = "r"; # fcn_gaussian returns real
    }

    # Build statement

    # Special case: seeding the random number generator
    if($qualifier eq "seed"){
	print QLA_SRC @indent, "$fcn_seed_random(&($dest_def{'value'}),$arg_seed,$src1_def{'value'});\n";
    }

    # Special case: assign random complex numbers
    elsif(($qualifier eq "random" || $qualifier eq "gaussian") && $rc_d eq "c"){
	&print_c_eqop_r_plus_ir($dest_elem_value,$eqop,
				$src1_elem_value,$src1_elem_value);
    }

    # Special case, multiply by i
    elsif($qualifier eq "i"){
	&print_s_eqop_s($rc_d,$dest_elem_value,$eqop,"i",
			$rc_s1,$src1_elem_value,$src1_def{'conj'});
    }
    
    # Standard case
    else{
	&print_s_eqop_s($rc_d,$dest_elem_value,$eqop,"",
			$rc_s1,$src1_elem_value,$src1_def{'conj'});
    }

    # Close inner tensor index loops
    &close_iter($jc); &close_iter($js);

    # Additional statement if needed
    if($qualifier eq "diagfill"){
	# Add line to set diagonal value
	$src1_elem_value = $src1_def{'value'};
	$rc_s1 = "c";
	$dest_elem_value = &make_accessor(*dest_def,$def{'nc'},$ic,$is,$ic,$is);
	&print_s_eqop_s($rc_d,$dest_elem_value,$eqop,"",
			$rc_s1,$src1_elem_value,$src1_def{'conj'});
    }

    # Close outer tensor index loops
    &close_iter($ic);  &close_iter($is);

}

#---------------------------------------------------------------------
# Antihermitian traceless part (gauge matrix only)
#---------------------------------------------------------------------

sub print_g_eqop_antiherm_g {
    local($eqop) = @_;

    # Color spin indices
    local($ic,$is,$jc,$js) = &get_color_spin_indices(*dest_def);
    local($maxic,$maxjc) = ($dest_def{'mc'},$dest_def{'nc'});

    local($dest_elem_value,$src1_elem_value);
    local($dest_tran_value,$src1_tran_value);

    # type checking
    $dest_def{'t'} eq $datatype_gauge_abbrev &&
	$src1_def{'t'} eq $datatype_gauge_abbrev ||
	die "antiherm supports only gauge field\n";

    $eqop eq $eqop_eq ||
	die "antiherm supports only replacement\n";

    # Define intermediate real for accumulating im(trace)
    $temp_type = &datatype_specific($datatype_real_abbrev);
    &print_def($temp_type,$var_x);
    &print_def($temp_type,$var_x2);

    &print_int_def($ic); 
    # Zero the intermediate value var_x
    &print_s_eqop_s("r",$var_x,$eqop_eq);

    # Loop for trace: answer in var_x
    &open_iter($ic,$maxic);
    $src1_elem_value = &make_accessor(*src1_def,$def{'nc'},$ic,$is,$ic,$js);

    # var_x += Im S_ii
    &print_s_eqop_s("r",$var_x,$eqop_peq,"I",
		    "c",$src1_elem_value,"");
    &close_iter($ic);
    # Divide ImTr by number of colors
    &print_s_eqop_s("r",$var_x,$eqop_eq,"",
		    "r","$var_x/$def{'nc'}","");

    # Loop to remove trace
    &open_iter($ic,$maxic);

    # var_x2 = Im S_ii
    $src1_elem_value = &make_accessor(*src1_def,$def{'nc'},$ic,$is,$ic,$js);
    &print_s_eqop_s("r",$var_x2,$eqop_eq,"I","c",$src1_elem_value,"");

    # var_x2 = var_x2 - ImTr/3
    &print_s_eqop_s("r",$var_x2,$eqop_eq,"","r","$var_x2 - $var_x","");

    # D_ii = i*var_x2
    $dest_elem_value = &make_accessor(*dest_def,$def{'nc'},$ic,$is,$ic,$js);
    &print_c_eqop_r_plus_ir($dest_elem_value,$eqop_eq,"0.",$var_x2);

    &close_iter($ic);

    # Loop for antihermitian projection
    &open_iter($ic,"$maxic-1");
    &print_int_def($jc);
    print QLA_SRC @indent,"for($jc=$ic+1;$jc<$maxjc;$jc++)\n";
    &open_block();
    &open_brace();

    $src1_elem_value = &make_accessor(*src1_def,$def{'nc'},$ic,$is,$jc,$js);
    $src1_tran_value = &make_accessor(*src1_def,$def{'nc'},$jc,$is,$ic,$js);
    $dest_elem_value = &make_accessor(*dest_def,$def{'nc'},$ic,$is,$jc,$js);
    $dest_tran_value = &make_accessor(*dest_def,$def{'nc'},$jc,$is,$ic,$js);

    # D_ij = S_ij - S_ji^*
    &print_s_eqop_s_op_s("c",$dest_elem_value,$eqop_eq,"",
			 "c",$src1_elem_value,"","-",
			 "c",$src1_tran_value,"a");
    # D_ij = D_ij/2
    &print_s_eqop_s_op_s("c",$dest_elem_value,$eqop_eq,"",
			 "c",$dest_elem_value,"","*","r","0.5","");

    # D_ji = -D_ij^*
    &print_s_eqop_s("c",$dest_tran_value,$eqop_eqm,"",
		    "c",$dest_elem_value,"a");

    &close_iter($ic);
    &close_iter($jc);
}

#---------------------------------------------------------------------
# norm2 reduction of any type
#---------------------------------------------------------------------

sub print_val_eqop_norm2_val {

    local(*dest_def,$eqop,*src1_def,$qualifier) = @_;

    local($dest_elem_value,$src1_elem_value);
    local($ic,$is,$jc,$js) = &get_color_spin_indices(*src1_def);
    local($maxic,$maxis,$maxjc,$maxjs) = @src1_def{'mc','ms','nc','ns'};
    local($rc_d,$rc_s1) = ($dest_def{'rc'},$src1_def{'rc'});

    local($srce_value);

    &print_def_open_iter_list($is,$maxis,$ic,$maxic,$js,$maxjs,$jc,$maxjc);

    # Print product for real, norm2 for complex
    $src1_elem_value = &make_accessor(*src1_def,$def{'nc'},$ic,$is,$jc,$js);
    if($rc_s1 eq "r"){
	$srce_value = "($src1_elem_value)*($src1_elem_value)";
    }
    else{
	$srce_value = "$carith0{'norm2'}($src1_elem_value)";
    }

    print QLA_SRC @indent,"$dest_def{'value'} $eqop_notation{$eqop} $srce_value;\n";

    &print_close_iter_list($is,$ic,$js,$jc);
}

#---------------------------------------------------------------------
# Accessing or setting matrix elements or column vectors
#---------------------------------------------------------------------

sub print_val_getset_component {
    local(*dest_def,$eqop,*src1_def,$ic,$is,$jc,$js,$qualifier) = @_;

    local($dest_elem_value,$src1_elem_value);
    local($maxic,$maxis,$maxjc,$maxjs) = @src1_def{'mc','ms','nc','ns'};
    local($rc_d,$rc_s1) = ($dest_def{'rc'},$src1_def{'rc'});
    local($icx,$isx) = ("","");

    # Dirac vector insertion, extraction requires loop over spin row index

    if($qualifier eq "getdiracvec" || $qualifier eq "setdiracvec"){
	&print_int_def($is); &open_iter($is,$maxis);
	$isx = $is;
    }

    # Color and Dirac vector insertion, extraction requires loop over
    # color row index

    if($qualifier eq "getcolorvec" || $qualifier eq "setcolorvec" ||
       $qualifier eq "getdiracvec" || $qualifier eq "setdiracvec"){
	&print_int_def($ic); &open_iter($ic,$maxic);
	$icx = $ic;
    }

    # Extraction
    if($qualifier eq "getcolorvec" || $qualifier eq "getmatelem" ||
       $qualifier eq "getdiracvec"){
	# (For dest here $jc and $js should be null
	$dest_elem_value = &make_accessor(*dest_def,$def{'nc'},
					  $icx,$isx,"","");
	$src1_elem_value = &make_accessor(*src1_def,$def{'nc'},
					  $ic,$is,$jc,$js);
    }
    # Insertion
    else{
	$src1_elem_value = &make_accessor(*src1_def,$def{'nc'},
					  $icx,$isx,"","");
	$dest_elem_value = &make_accessor(*dest_def,$def{'nc'},
					  $ic,$is,$jc,$js);
    }

    &print_s_eqop_s($rc_d,$dest_elem_value,$eqop,"",$rc_s1,$src1_elem_value,"");

    if($qualifier eq "getcolorvec" || $qualifier eq "setcolorvec" ||
       $qualifier eq "getdiracvec" || $qualifier eq "setdiracvec"){
	&close_iter($ic);
    }
    if($qualifier eq "getdiracvec" || $qualifier eq "setdiracvec"){
	&close_iter($is);
    }
}

#---------------------------------------------------------------------
# Trace of matrix type
#---------------------------------------------------------------------

sub print_val_assign_tr {
    local(*dest_def,$eqop,$imre,*src1_def) = @_;

    local($dest_elem_value,$src1_elem_value);
    local($ic,$is,$jc,$js) = &get_color_spin_indices(*src1_def);
    local($maxic,$maxis,$maxjc,$maxjs) = @src1_def{'mc','ms','nc','ns'};
    local($rc_d,$rc_s1) = ($dest_def{'rc'},$src1_def{'rc'});
    local($rc_x) = $rc_d;

    &print_int_def($ic);

    # Define and zero intermediate variable for accumulating trace
    &print_def($dest_def{'type'},$var_x);
    &print_s_eqop_s($rc_x,$var_x,$eqop_eq);

    &open_iter($ic,$maxic);

    &print_int_def($is); &open_iter($is,$maxis);

    # Accumulate trace
    $src1_elem_value = &make_accessor(*src1_def,$def{'nc'},$ic,$is,$ic,$is);
    &print_s_eqop_s($rc_x,$var_x,$eqop_peq,$imre,$rc_s1,$src1_elem_value);

    &close_iter($ic);
    &close_iter($is);

    # Assign result to dest
    &print_s_eqop_s($rc_d,$dest_def{'value'},$eqop,"",$rc_x,$var_x,"");
}

#---------------------------------------------------------------------
# Spin trace of matrix type
#---------------------------------------------------------------------

sub print_val_assign_spin_tr {
    local(*dest_def,$eqop,$imre,*src1_def) = @_;

    local($dest_elem_value,$src1_elem_value);
    local($ic,$is,$jc,$js) = &get_color_spin_indices(*src1_def);
    local($maxic,$maxis,$maxjc,$maxjs) = @src1_def{'mc','ms','nc','ns'};
    local($dest_t) = $dest_def{'t'};
    local($rc_d,$rc_s1) = ($dest_def{'rc'},$src1_def{'rc'});
    local($rc_x) = $rc_d;

    $maxis == $maxjs || die "Can't spintrace when $maxis ne $maxjs\n";

    # Open iteration over color indices

    &print_def_open_iter_list($ic,$maxic,$jc,$maxjc);
    &print_int_def($is);

    # Define and zero intermediate variable for accumulating sum
    &print_def(&datatype_element_specific($dest_t),$var_x);

    # Open iteration over spins

    &print_s_eqop_s($rc_x,$var_x,$eqop_eq);
    &open_iter($is,$maxis);

    # Accumulate trace
    $src1_elem_value = &make_accessor(*src1_def,$def{'nc'},$ic,$is,$jc,$is);
    &print_s_eqop_s($rc_x,$var_x,$eqop_peq,$imre,$rc_s1,$src1_elem_value);

    &close_iter($is);

    # Assign result to dest
    $dest_elem_value = &make_accessor(*dest_def,$def{'nc'},$ic,"",$jc,"");
    &print_s_eqop_s($rc_d,$dest_elem_value,$eqop,"",$rc_x,$var_x,"");

    &print_close_iter_list($ic,$jc);
}

#---------------------------------------------------------------------
#  Auxiliary routines for binary operations
#---------------------------------------------------------------------

# Check multiplication/division by scalar. Detect Kronecker delta.
# IX = const times tensor  XI = tensor times const  XX = tensor times tensor

sub times_pattern {
    local($md,$nd,$m1,$n1,$m2,$n2) = @_;

    if($m2.$n2 eq "00" && $md == $m1 && $nd == $n1){"XI";}
    elsif($m1.$n1 eq "00" && $md == $m2 && $nd == $n2){"IX";}
    elsif($md == $m1 && $nd == $n2 && $n1 == $m2){"XX";}
    else{""};
}

sub dot_pattern {
    local($md,$nd,$m1,$n1,$m2,$n2) = @_;

    if($md == 0 && $nd == 0 && $n1 == $m2){"XX";}
    else{""};
}

# Check addition/subtraction of tensors
sub plus_pattern {
    local($md,$nd,$m1,$n1,$m2,$n2) = @_;

    if($md == $m1 && $md == $m2 && 
       $nd == $n1 && $nd == $n2 ){"XX";}
    else {""};
}

# Construct multiplier and multiplicand for product
sub mult_terms {
    local($cpat,$spat,*arg1_def,*arg2_def,$ic,$is,$jc,$js) = @_;

    local($arg1_elem_value,$arg2_elem_value);
    local($ic1,$is1,$jc1,$js1);
    local($ic2,$is2,$jc2,$js2);
    local($kc,$ks);

    $kc = &get_col_color_index2(*arg1_def);
    $ks = &get_col_spin_index2(*arg1_def);

    if($cpat eq "XX"){ $ic1=$ic; $jc1=$kc; $ic2=$kc; $jc2=$jc;}
    elsif($cpat eq "IX"){$ic1=""; $jc1=""; $ic2=$ic; $jc2=$jc; $kc = "";}
    elsif($cpat eq "XI"){$ic1=$ic; $jc1=$jc; $ic2=""; $jc2=""; $kc = "";}

    if($spat eq "XX"){ $is1=$is; $js1=$ks; $is2=$ks; $js2=$js;}
    elsif($spat eq "IX"){$is1=""; $js1=""; $is2=$is; $js2=$js; $ks = "";}
    elsif($spat eq "XI"){$is1=$is; $js1=$js; $is2=""; $js2=""; $ks = "";}

    $arg1_elem_value = &make_accessor(*arg1_def,$def{'nc'},
				      $ic1,$is1,$jc1,$js1);
    $arg2_elem_value = &make_accessor(*arg2_def,$def{'nc'},
				      $ic2,$is2,$jc2,$js2);

    ($kc,$ks,$arg1_elem_value,$arg2_elem_value);
}

# Construct multiplier and multiplicand for product with trace (dot product)
sub dot_terms {
    local(*arg1_def,*arg2_def) = @_;
    local($arg1_elem_value,$arg2_elem_value);
    local($ic,$is,$jc,$js) = &get_color_spin_indices(*arg2_def);

    $arg1_elem_value = &make_accessor(*arg1_def,$def{'nc'},
				      $jc,$js,$ic,$is);
    $arg2_elem_value = &make_accessor(*arg2_def,$def{'nc'},
				      $ic,$is,$jc,$js);

    ($ic,$is,$jc,$js,$arg1_elem_value,$arg2_elem_value);
}

# Do row-column product
sub print_s_eqop_v_times_v_pm_s {
    local($rc_d,$dest_t,$dest_elem_value,
	  $kc,$maxkc,$ks,$maxks,$eqop,
	  $rc_s1,$src1_elem_value,$conj1,
	  $rc_s2,$src2_elem_value,$conj2,
	  $pm,
	  $rc_s3,$src3_elem_value,$conj3) = @_;

    local($rc_x) = $rc_d;

    local($unroll) = 0;
    local($nout) = 1;
    #if( ($maxkc==2) || ($maxkc==3) ) {
    if(0) {
      $unroll = 1;
      $nout = $maxkc;
    } else {
      &print_int_def($kc);
    }
    &print_int_def($ks);

    # Define and zero intermediate variable for accumulating sum
    $rc_x = $rc_d;
    &print_def(&datatype_element_specific($dest_t),"*$var_x");

    my($loop_eqop);
    if(!defined($src3_elem_value)){
      # Assign accumulated result to dest
      print QLA_SRC @indent,"$var_x = &$dest_elem_value;\n";
      if($eqop eq $eqop_eq) {
	&print_s_eqop_s($rc_x,"*$var_x",$eqop_eq);
	$loop_eqop = $eqop_peq;
      } elsif($eqop eq $eqop_peq) {
	$loop_eqop = $eqop_peq;
      } elsif($eqop eq $eqop_meq) {
	$loop_eqop = $eqop_meq;
      } elsif($eqop eq $eqop_eqm) {
	&print_s_eqop_s($rc_x,"*$var_x",$eqop_eq);
	$loop_eqop = $eqop_meq;
      }
    }
    else{
      die("ternary tensor operations not done!\n");

	# Add or subtract src3 and assign result to dest element
	&print_s_eqop_s_op_s($rc_d,$dest_elem_value,
			     $eqop,"",
			     $rc_x,$var_x,"",
			     $pm,
			     $rc_s3,$src3_elem_value,$conj3);
    }

    &open_iter($ks,$maxks);
    if(!$unroll) {
      &open_iter($kc,$maxkc);
    }
    for(my $i=0; $i<$nout; $i++) {
      local($s1) = $src1_elem_value;
      local($s2) = $src2_elem_value;
      if($unroll) {
	$s1 =~ s/$kc/$i/;
	$s2 =~ s/$kc/$i/;
      }

      # Accumulate product
      &print_s_eqop_s_op_s($rc_x,"*$var_x",
			   $loop_eqop,"",
			   $rc_s1,$s1,$conj1,
			   '*',
			   $rc_s2,$s2,$conj2);

    }
    if(!$unroll) {
      &close_iter($kc);
    }
    &close_iter($ks);
}

# Do row-column dot product with trace
sub print_s_eqop_v_dot_v {
    local($rc_d,$dest_t,$dest_elem_value,
	  $ic,$maxic,$is,$maxis,$jc,$maxjc,$js,$maxjs,
	  $eqop,$imre,
	  $rc_s1,$src1_elem_value,$conj1,
	  $rc_s2,$src2_elem_value,$conj2) = @_;

    local($rc_x) = $rc_d;

    &print_int_def($ic);  &print_int_def($is);
    &print_int_def($jc);  &print_int_def($js);

    &open_iter($ic,$maxic); &open_iter($is,$maxis);
    &open_iter($jc,$maxjc); &open_iter($js,$maxjs);

    # Accumulate product
    &print_s_eqop_s_op_s($rc_x,$var_x,
			 $eqop_peq,$imre,
			 $rc_s1,$src1_elem_value,$conj1,
			 '*',
			 $rc_s2,$src2_elem_value,$conj2);

    &close_iter($is); &close_iter($ic);
    &close_iter($js); &close_iter($jc);
}

#---------------------------------------------------------------------
#  Binary operation between tensors
#---------------------------------------------------------------------

sub print_MV {
    local(*dest_def,$eqop,*src1_def,*src2_def) = @_;

    print QLA_SRC "test\n";
}

sub print_val_eqop_val_op_val {
    local(*dest_def,$eqop,$imre,*src1_def,$op,*src2_def) = @_;

    $inline = 0;
    if($inline) {
#      if( ($op eq "times") && ($src1_def{t} eq "M") ) {
#        if($src2_def{t} eq "V") {
#	  &print_MV(*dest_def,$eqop,*src1_def,*src2_def);
#          return;
#        }
#      }
      local($func) = "$def{prefix}";
      $func .= "_$dest_def{t}$dest_def{adj}";
      $func .= "_$eqop";
      $func .= "_$src1_def{t}$src1_def{adj}";
      $func .= "_$op";
      $func .= "_$src2_def{t}$src2_def{adj}";
      local($args);
      $args = "&$dest_def{value}";
      $args .= ", &$src1_def{value}";
      $args .= ", &$src2_def{value}";
      $args =~ s/&\*//g;
      print QLA_SRC @indent, "$func($args);\n";
#print "$func($args);\n";
#print %dest_def, "\n";
      return;
    }

    local($dest_elem_value,$src1_elem_value,$src2_elem_value);
    local($kc);
    local($rc_d,$rc_s1,$rc_s2) = 
	($dest_def{'rc'},$src1_def{'rc'},$src2_def{'rc'});
    local($rc_x);

    local($mcd,$msd,$ncd,$nsd) = @dest_def{'mc','ms','nc','ns'};
    local($mc1,$ms1,$nc1,$ns1) = @src1_def{'mc','ms','nc','ns'};
    local($mc2,$ms2,$nc2,$ns2) = @src2_def{'mc','ms','nc','ns'};

    local($ic,$is,$jc,$js);
    local($maxic,$maxis,$maxjc,$maxjs);
    local($cpat,$spat);
    local($pmd);

    local($maxkc,$maxks) = ($nc1,$ns1);

    # Operand color/spin dimension consistency checks

    if($op eq "times"){
	$cpat = &times_pattern($mcd,$ncd,$mc1,$nc1,$mc2,$nc2);
	$spat = &times_pattern($msd,$nsd,$ms1,$ns1,$ms2,$ns2);
	$cpat ne "" && $spat ne "" || die "incompatible product types\n";
    }
    elsif($op eq "dot"){
	$cpat = &dot_pattern($mcd,$ncd,$mc1,$nc1,$mc2,$nc2);
	$spat = &dot_pattern($msd,$nsd,$ms1,$ns1,$ms2,$ns2);
	$cpat eq "XX" && $spat eq "XX" || die "incompatible dot product types\n";
    }
    elsif($op eq "plus" || $op eq "minus"){
	$cpat = &plus_pattern($mcd,$ncd,$mc1,$nc1,$mc2,$nc2);
	$spat = &plus_pattern($msd,$nsd,$ms1,$ns1,$ms2,$ns2);
	$cpat eq "XX" && $spat eq "XX" ||
	    die "incompatible addition/subtraction types\n";

    }
    elsif($op eq "divide"){
	# Support division only by real or complex
	$cpat = &times_pattern($mcd,$ncd,$mc1,$nc1,$mc2,$nc2);
	$spat = &times_pattern($msd,$nsd,$ms1,$ns1,$ms2,$ns2);
	$cpat eq "XI" && $spat eq "XI" ||
	    die "incompatible or unsupported division\n";
    }

    # Open iteration over outer tensor indices (but not for dot product)

    if($op ne "dot"){

	($maxic,$maxis,$maxjc,$maxjs) = ($mcd,$msd,$ncd,$nsd);
	($ic,$is,$jc,$js) = &get_color_spin_indices(*dest_def);

	&print_def_open_iter_list($is,$maxis,$ic,$maxic,$js,$maxjs,$jc,$maxjc);
	$dest_elem_value =
	    &make_accessor(*dest_def,$def{'nc'},$ic,$is,$jc,$js);
    }

    if($op eq "times"){

	# Construct multiplier and multiplicand

	($kc,$ks,$src1_elem_value,$src2_elem_value) = 
	    &mult_terms($cpat,$spat,*src1_def,*src2_def,$ic,$is,$jc,$js);

	# If we are summing over kc or ks, need to handle the sum
	if($kc ne "" || $ks ne ""){
	    &print_s_eqop_v_times_v_pm_s(
				 $rc_d,$dest_def{'t'},$dest_elem_value,
				 $kc,$maxkc,$ks,$maxks,$eqop,
				 $rc_s1,$src1_elem_value,$src1_def{'conj'},
				 $rc_s2,$src2_elem_value,$src2_def{'conj'});
	}
	# Otherwise, a simple product
	else{
	    &print_s_eqop_s_op_s($rc_d,$dest_elem_value,
				 $eqop,"",
				 $rc_s1,$src1_elem_value,$src1_def{'conj'},
				 '*',
				 $rc_s2,$src2_elem_value,$src2_def{'conj'});
	}
    }

    elsif($op eq "dot"){
	local($maxic,$maxis,$maxjc,$maxjs) = ($mc2,$ms2,$nc2,$ns2);

	# Destination value (must be scalar, so no indices)

	$dest_elem_value =  &make_accessor(*dest_def,$def{'nc'},"","","","");

	# Construct multiplier and multiplicand

	($ic,$is,$jc,$js,$src1_elem_value,$src2_elem_value) =
	    &dot_terms(*src1_def,*src2_def);

	# If we are summing over ic, jc, is, or js, need to handle the sum
	if($ic ne "" || $is ne "" || $jc ne "" || $js ne ""){
	    &print_s_eqop_v_dot_v(
				 $rc_d,$dest_def{'t'},$dest_elem_value,
				 $ic,$maxic,$is,$maxis,$jc,$maxjc,$js,$maxjs,
				 $eqop,$imre,
				 $rc_s1,$src1_elem_value,$src1_def{'conj'},
				 $rc_s2,$src2_elem_value,$src2_def{'conj'});
	}
	# Otherwise, a simple product
	else{
	    &print_s_eqop_s_op_s($rc_d,$dest_elem_value,
				 $eqop,$imre,
				 $rc_s1,$src1_elem_value,$src1_def{'conj'},
				 '*',
				 $rc_s2,$src2_elem_value,$src2_def{'conj'});
	}
    }

    # Sum or difference of tensors or division by scalar
    elsif($op eq "plus" || $op eq "minus" || $op eq "divide"){
	$src1_elem_value = &make_accessor(*src1_def,$def{'nc'},$ic,$is,$jc,$js);
	$src2_elem_value = &make_accessor(*src2_def,$def{'nc'},$ic,$is,$jc,$js);
	if($op eq "plus"){$pmd = '+';} 
	elsif($op eq "minus"){$pmd = '-';}
	else{$pmd = '/';}
	&print_s_eqop_s_op_s($rc_d,$dest_elem_value,
			     $eqop,"",
			     $rc_s1,$src1_elem_value,$src1_def{'conj'},
			     $pmd,
			     $rc_s2,$src2_elem_value,$src2_def{'conj'});
    }

    else{
	die "Can't do op $op\n";
    }

    if($op ne "dot"){
      &print_close_iter_list($is,$ic,$js,$jc);
    }
}

#---------------------------------------------------------------------
#  Binary operation on integers and reals
#---------------------------------------------------------------------

%bool_binary_op = (
		   'eq', '==',
		   'ne', '!=',
		   'gt', '>',
		   'ge', '>=',
		   'lt', '<',
		   'le', '<=',
		   'or', '|',
		   'and','&',
		   'xor','^',
		   );

sub print_val_eqop_val_op_val_elementary {
    local(*dest_def,$eqop,*src1_def,$op,*src2_def) = @_;
    local($sym);

    if($op eq "lshift"){
	&print_s_eqop_s("r",$dest_def{'value'},$eqop,"","r",
			"$src1_def{'value'} << $src2_def{'value'}");
    }
    elsif($op eq "rshift"){
	&print_s_eqop_s("r",$dest_def{'value'},$eqop,"","r",
			"$src1_def{'value'} >> $src2_def{'value'}");
    }
    elsif($op eq "mod"){
	if($dest_def{'t'} eq $datatype_integer_abbrev &&
	   $src1_def{'t'} eq $datatype_integer_abbrev &&
	   $src2_def{'t'} eq $datatype_integer_abbrev){
	    &print_s_eqop_s("r",$dest_def{'value'},$eqop,"","r",
			    "$src1_def{'value'} % $src2_def{'value'}");
	}
	else{
	    &print_s_eqop_s("r",$dest_def{'value'},$eqop,"","r",
			    "fmod($src1_def{'value'},$src2_def{'value'})");
	}
    }
    elsif($op eq "pow"){
	&print_s_eqop_s("r",$dest_def{'value'},$eqop,"","r",
			"pow($src1_def{'value'},$src2_def{'value'})");
	}
    elsif($op eq "atan2"){
	&print_s_eqop_s("r",$dest_def{'value'},$eqop,"","r",
			"atan2($src1_def{'value'},$src2_def{'value'})");
	}
    elsif($op eq "ldexp"){
	&print_s_eqop_s("r",$dest_def{'value'},$eqop,"","r",
			"ldexp($src1_def{'value'},$src2_def{'value'})");
	}
    elsif($op eq "max"){
	&print_s_eqop_s("r",$dest_def{'value'},$eqop,"","r",
		  "($src1_def{'value'} > $src2_def{'value'} ? $src1_def{'value'} : $src2_def{'value'})");
    }
    elsif($op eq "min"){
	&print_s_eqop_s("r",$dest_def{'value'},$eqop,"","r",
		  "($src1_def{'value'} > $src2_def{'value'} ? $src2_def{'value'} : $src1_def{'value'})");
    }
    elsif($op eq "mask"){
	print QLA_SRC @indent,"if($src2_def{'value'})$dest_def{'value'} = $src1_def{'value'};\n";
    }
    else{
	$sym = $bool_binary_op{$op};
	defined($sym) || die "No boolean support for $op\n";
	&print_s_eqop_s("r",$dest_def{'value'},$eqop,"","r",
		  "( $src1_def{'value'} ".$sym." $src2_def{'value'} )");
    }
}

#---------------------------------------------------------------------
# Ternary tensor operation
#---------------------------------------------------------------------
# Supports only a*b + c and a*b - c

sub print_val_eqop_val_op_val_op2_val {
    local(*dest_def,$eqop,*src1_def,$op,$src2_def,$op2,*src3_def) = @_;

    local($dest_elem_value,$src1_elem_value,$src2_elem_value,$src2_elem_value);
    local($ic,$is,$jc,$js) = &get_color_spin_indices(*dest_def);
    local($kc,$ks);
    local($rc_d,$rc_s1,$rc_s2,$rc_s3) = 
	($dest_def{'rc'},$src1_def{'rc'},$src2_def{'rc'},$src3_def{'rc'});
    local($rc_x);

    local($mcd,$msd,$ncd,$nsd) = @dest_def{'mc','ms','nc','ns'};
    local($mc1,$ms1,$nc1,$ns1) = @src1_def{'mc','ms','nc','ns'};
    local($mc2,$ms2,$nc2,$ns2) = @src2_def{'mc','ms','nc','ns'};
    local($mc3,$ms3,$nc3,$ns3) = @src3_def{'mc','ms','nc','ns'};

    local($kc,$ks);
    local($pm);

    local($maxic,$maxis,$maxjc,$maxjs) = ($mcd,$msd,$ncd,$nsd);
    local($maxkc,$maxks) = ($nc1,$ns1);

    # Operand color/spin dimension consistency checks
    # Also detects patterns for use with multiplication

    if($op eq "times"){
	$cpat = &times_pattern($mcd,$ncd,$mc1,$nc1,$mc2,$nc2);
	$spat = &times_pattern($msd,$nsd,$ms1,$ns1,$ms2,$ns2);
	$cpat ne "" && $spat ne "" || die "incompatible product types\n";
    }
    else{
	die "ternary operations do not support op = $op\n";
    }

    if($op2 eq "plus" || $op2 eq "minus"){
	$mcd == $mc3 && $msd == $ms3 &&
	$ncd == $nc3 && $nsd == $ns3 || 
	die "incompatible addition/subtraction types\n";
    }
    else{
	die "ternary operations do not support op2 = $op2\n";
    }

    if($op2 eq "plus"){$pm = '+';}
    elsif($op2 eq "minus"){$pm = '-';}

    &print_def_open_iter_list($is,$maxis,$ic,$maxic,$js,$maxjs,$jc,$maxjc);
    $dest_elem_value = &make_accessor(*dest_def,$def{'nc'},$ic,$is,$jc,$js);

    # Construct multiplier and multiplicand
    ($kc,$ks,$src1_elem_value,$src2_elem_value) = 
	&mult_terms($cpat,$spat,*src1_def,*src2_def,$ic,$is,$jc,$js);

    # Construct addend
    $src3_elem_value = &make_accessor(*src3_def,$def{'nc'},
				      $ic,$is,$jc,$js);

    # If we are summing over kc or ks, need to handle the sum
    if($kc ne "" || $ks ne ""){
	&print_s_eqop_v_times_v_pm_s(
                             $rc_d,$dest_def{'t'},$dest_elem_value,
			     $kc,$maxkc,$ks,$maxks,$eqop,
			     $rc_s1,$src1_elem_value,$src1_def{'conj'},
			     $rc_s2,$src2_elem_value,$src2_def{'conj'},
			     $pm,
			     $rc_s3,$src3_elem_value,$src3_def{'conj'});
    }

    # Otherwise, a simple product plus or minus arg3
    else{
	&print_s_eqop_s_times_s_pm_s(
                             $rc_d,$dest_elem_value,
			     $eqop,
			     $rc_s1,$src1_elem_value,$src1_def{'conj'},
			     '*',
			     $rc_s2,$src2_elem_value,$src2_def{'conj'},
			     $pm,
			     $rc_s3,$src3_elem_value,$src3_def{'conj'});
    }

    &print_close_iter_list($is,$ic,$js,$jc);
}

#---------------------------------------------------------------------
# Fills for various types
#---------------------------------------------------------------------

sub print_fill {
    local(*dest_def,$qualifier) = @_;

    local($ic,$is,$jc,$js) = &get_color_spin_indices(*dest_def);
    local($maxic,$maxis,$maxjc,$maxjs) = @dest_def{'mc','ms','nc','ns'};
    local($rc_d)  = $dest_def{'rc'};

    &print_def_open_iter_list($is,$maxis,$ic,$maxic,$js,$maxjs,$jc,$maxjc);

    $dest_elem_value = &make_accessor(*dest_def,$def{'nc'},$ic,$is,$jc,$js);

    if($qualifier eq "zero") {
      &print_s_eqop_s($rc_d,$dest_elem_value,$eqop_eq,"","r","0.","");
    }

    &print_close_iter_list($is,$ic,$js,$jc);
}
1;
