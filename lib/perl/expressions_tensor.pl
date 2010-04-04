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

use strict;

require("variable_names.pl");
require("headers.pl");
require("formatting.pl");
require("operatortypes.pl");
require("expressions_scalar.pl");

use vars qw/ %carith1 %carith2 %carith3 %eqop_notation /;
use vars qw/ $fcn_random $fcn_gaussian $fcn_seed_random $arg_seed /;
use vars qw/ $datatype_integer_abbrev $datatype_real_abbrev /;
use vars qw/ $datatype_complex_abbrev $datatype_gauge_abbrev /;
use vars qw/ $precision $temp_precision $colors /;
use vars qw/ $eqop_eqm $eqop_meq /;
use vars qw/ $var_i /;
use vars qw/ @indent /;


######################################################################

#---------------------------------------------------------------------
# Unary assignment (with op)
#---------------------------------------------------------------------

sub print_val_eqop_op_val {
  my($ddef,$eqop,$s1def,$qualifier) = @_;
  my($dest_elem_value,$src1_elem_value);

  # Operand dimensions
  my($mcd,$msd,$ncd,$nsd) = @$ddef {'mc','ms','nc','ns'};
  my($mc1,$ms1,$nc1,$ns1) = @$s1def{'mc','ms','nc','ns'};

  # Color spin indices
  my($ic,$is,$jc,$js) = &get_color_spin_indices($ddef);

  # Real or complex matrix element
  my($rc_d,$rc_s1) = ($$ddef{'rc'},$$s1def{'rc'});

  # Check consistency of dimensions
  if($$s1def{'t'} ne "" && $qualifier ne "diagfill" && 
     $qualifier ne "gaussian"&& $qualifier ne "random" 
     && $qualifier ne "seed") {
    $mcd eq $mc1 && $msd eq $ms1 && $ncd eq $nc1 && $nsd eq $ns1 ||
	die "incompatible types in assignment\n";
  }

  # Open iteration over destination row indices
  &print_int_def($ic); &open_iter($ic,$mcd);
  &print_int_def($is); &open_iter($is,$msd);

  # Open iteration over destination column indices, if needed
  &print_int_def($jc); &open_iter($jc,$ncd);
  &print_int_def($js); &open_iter($js,$nsd);

  $dest_elem_value = &make_accessor($ddef, $def{'nc'},$ic,$is,$jc,$js);
  $src1_elem_value = &make_accessor($s1def,$def{'nc'},$ic,$is,$jc,$js);

  # Build alternate expression for source if necessary
  if($qualifier eq "zero" || $qualifier eq "diagfill"){
    $src1_elem_value = "0."; $rc_s1 = "r";
  }
  elsif($qualifier eq "random"){
    $src1_elem_value = "$fcn_random(&($$s1def{'value'}))";
    $rc_s1 = "r";  # fcn_random returns real
  }
  elsif($qualifier eq "gaussian"){
    $src1_elem_value = "$fcn_gaussian(&($$s1def{'value'}))";
    $rc_s1 = "r"; # fcn_gaussian returns real
  }

  # Build statement

  # Special case: seeding the random number generator
  if($qualifier eq "seed"){
    print QLA_SRC @indent, "$fcn_seed_random(&($$ddef{'value'}),$arg_seed,$$s1def{'value'});\n";
  }

  # Special case: assign random complex numbers
  elsif(($qualifier eq "random" || $qualifier eq "gaussian") && $rc_d eq "c"){
    &print_c_eqop_r_plus_ir($dest_elem_value,$eqop,
			    $src1_elem_value,$src1_elem_value);
  }

  # Special case, multiply by i
  elsif($qualifier eq "i"){
    &print_s_eqop_s($rc_d,$dest_elem_value,$eqop,"i",
		    $rc_s1,$src1_elem_value,$$s1def{'conj'},
		    $$ddef{'precision'}, $$s1def{'precision'});
  }

  # Standard case
  else{
    &print_s_eqop_s($rc_d,$dest_elem_value,$eqop,"",
		    $rc_s1,$src1_elem_value,$$s1def{'conj'},
		    $$ddef{'precision'}, $$s1def{'precision'});
  }

  # Close inner tensor index loops
  &close_iter($js); &close_iter($jc);

  # Additional statement if needed
  if($qualifier eq "diagfill"){
    # Add line to set diagonal value
    $src1_elem_value = $$s1def{'value'};
    $rc_s1 = "c";
    $dest_elem_value = &make_accessor($ddef,$def{'nc'},$ic,$is,$ic,$is);
    &print_s_eqop_s($rc_d,$dest_elem_value,$eqop,"",
		    $rc_s1,$src1_elem_value,$$s1def{'conj'},
		    $$ddef{'precision'}, $$s1def{'precision'});
  }

  # Close outer tensor index loops
  &close_iter($is);  &close_iter($ic);
}

#---------------------------------------------------------------------
# Antihermitian traceless part (gauge matrix only)
#---------------------------------------------------------------------

sub print_g_eqop_antiherm_g {
  my($eqop) = @_;
  my $ddef  = \%dest_def;
  my $s1def = \%src1_def;

  # Color spin indices
  my($ic,$is,$jc,$js) = &get_color_spin_indices($ddef);
  my($maxic,$maxjc) = ($$ddef{'mc'},$$ddef{'nc'});

  my($dest_elem_value,$src1_elem_value);
  my($dest_tran_value,$src1_tran_value);

  # type checking
  $$ddef{'t'} eq $datatype_gauge_abbrev &&
      $$s1def{'t'} eq $datatype_gauge_abbrev ||
      die "antiherm supports only gauge field\n";

  $eqop eq $eqop_eq ||
      die "antiherm supports only replacement\n";

  &open_brace();

  # Define intermediate real for accumulating im(trace)
  my $temp_type = &datatype_specific($datatype_real_abbrev);
  &print_def($temp_type,$var_x);

  # Zero the intermediate value var_x
  &print_s_eqop_s("r",$var_x,$eqop_eq);

  # Loop for trace: answer in var_x
  &print_int_def($ic);
  &open_iter($ic,$maxic);
  $src1_elem_value = &make_accessor($s1def,$def{'nc'},$ic,$is,$ic,$js);

  # var_x += Im S_ii
  &print_s_eqop_s("r",$var_x,$eqop_peq,"I",
		  "c",$src1_elem_value,"");
  &close_iter($ic);
  # Divide ImTr by number of colors
  &print_s_eqop_s("r",$var_x,$eqop_eq,"",
		  "r","$var_x/$def{'nc'}","");

  # Loop to remove trace
  &open_iter($ic,$maxic);
  &print_def($temp_type,$var_x2);

  # var_x2 = Im S_ii
  $src1_elem_value = &make_accessor($s1def,$def{'nc'},$ic,$is,$ic,$js);
  &print_s_eqop_s("r",$var_x2,$eqop_eq,"I","c",$src1_elem_value,"");

  # var_x2 = var_x2 - ImTr/3
  &print_s_eqop_s("r",$var_x2,$eqop_eq,"","r","$var_x2 - $var_x","");

  # D_ii = i*var_x2
  $dest_elem_value = &make_accessor($ddef,$def{'nc'},$ic,$is,$ic,$js);
  &print_c_eqop_r_plus_ir($dest_elem_value,$eqop_eq,"0.",$var_x2);

  &close_iter($ic);
  &close_brace();

  # Loop for antihermitian projection
  &open_iter($ic,"$maxic-1");
  &print_int_def($jc);
  print QLA_SRC @indent,"for(int $jc=$ic+1;$jc<$maxjc;$jc++) {\n";
  &open_block();

  $src1_elem_value = &make_accessor($s1def,$def{'nc'},$ic,$is,$jc,$js);
  $src1_tran_value = &make_accessor($s1def,$def{'nc'},$jc,$is,$ic,$js);
  $dest_elem_value = &make_accessor($ddef,$def{'nc'},$ic,$is,$jc,$js);
  $dest_tran_value = &make_accessor($ddef,$def{'nc'},$jc,$is,$ic,$js);
  my $px2 = $temp_precision;
  $px2 = $precision if($px2 eq '');
  my $x2_dt = &datatype_element_specific($$ddef{t}, $px2);
  &print_def($x2_dt, $var_x);
  &print_def($x2_dt, $var_x2);

  # D_ij = S_ij - S_ji^*
  &print_s_eqop_s_op_s("c",$var_x,$eqop_eq,"",
		       "c",$src1_elem_value,"","-",
		       "c",$src1_tran_value,"a",
		       $px2, $$s1def{precision}, $$s1def{precision});
  # D_ij = D_ij/2
  &print_s_eqop_s_op_s("c",$var_x2,$eqop_eq,"",
		       "c",$var_x,"","*","r","0.5","",
		       $px2, $px2, $precision);

  &print_s_eqop_s("c",$dest_elem_value,$eqop_eq,"",
		  "c",$var_x2,"", $$ddef{precision}, $px2);

  # D_ji = -D_ij^*
  &print_s_eqop_s("c",$dest_tran_value,$eqop_eqm,"",
		  "c",$var_x2,"a", $$ddef{precision}, $px2);

  &close_iter($ic);
  &close_iter($jc);
}

#---------------------------------------------------------------------
# Matrix determinant
#---------------------------------------------------------------------

sub print_c_eqop_det_m {
  my($eqop) = @_;
  my $ddef  = \%dest_def;
  my $s1def = \%src1_def;

  # type checking
  $$ddef{'t'} eq $datatype_complex_abbrev &&
      $$s1def{'t'} eq $datatype_gauge_abbrev ||
      die "matrix det supports only gauge field\n";

  $eqop eq $eqop_eq ||
      die "matrix det supports only replacement\n";

  my $func = "QLA_${precision}${colors}_C_eq_det_M";
  my $ncvar = "";
  if($def{'nc'} eq $arg_nc) {
    $ncvar = "$arg_nc, ";
  }
  print QLA_SRC @indent,"$func(${ncvar}&($$ddef{'value'}), &($$s1def{'value'}));\n";
}

#---------------------------------------------------------------------
# Matrix inverse
#---------------------------------------------------------------------

sub print_m_eqop_inv_m {
  my($eqop) = @_;
  my $ddef  = \%dest_def;
  my $s1def = \%src1_def;

  # type checking
  $$ddef{'t'} eq $datatype_gauge_abbrev &&
      $$s1def{'t'} eq $datatype_gauge_abbrev ||
      die "matrix inverse supports only gauge field\n";

  $eqop eq $eqop_eq ||
      die "matrix inverse supports only replacement\n";

  my $func = "QLA_${precision}${colors}_M_eq_inverse_M";
  my $ncvar = "";
  if($def{'nc'} eq $arg_nc) {
    $ncvar = "$arg_nc, ";
  }
  print QLA_SRC @indent,"$func(${ncvar}&($$ddef{'value'}), &($$s1def{'value'}));\n";
}

#---------------------------------------------------------------------
# Matrix exponential
#---------------------------------------------------------------------

sub print_m_eqop_exp_m {
  my($eqop) = @_;
  my $ddef  = \%dest_def;
  my $s1def = \%src1_def;

  # type checking
  $$ddef{'t'} eq $datatype_gauge_abbrev &&
      $$s1def{'t'} eq $datatype_gauge_abbrev ||
      die "matrix exp supports only gauge field\n";

  $eqop eq $eqop_eq ||
      die "matrix exp supports only replacement\n";

  my $func = "QLA_${precision}${colors}_M_eq_exp_M";
  my $ncvar = "";
  if($def{'nc'} eq $arg_nc) {
    $ncvar = "$arg_nc, ";
  }
  print QLA_SRC @indent,"$func(${ncvar}&($$ddef{'value'}), &($$s1def{'value'}));\n";
}

#---------------------------------------------------------------------
# Matrix square root
#---------------------------------------------------------------------

sub print_m_eqop_sqrt_m {
  my($eqop) = @_;
  my $ddef  = \%dest_def;
  my $s1def = \%src1_def;

  # type checking
  $$ddef{'t'} eq $datatype_gauge_abbrev &&
      $$s1def{'t'} eq $datatype_gauge_abbrev ||
      die "matrix sqrt supports only gauge field\n";

  $eqop eq $eqop_eq ||
      die "matrix sqrt supports only replacement\n";

  my $func = "QLA_${precision}${colors}_M_eq_sqrt_M";
  my $ncvar = "";
  if($def{'nc'} eq $arg_nc) {
    $ncvar = "$arg_nc, ";
  }
  print QLA_SRC @indent,"$func(${ncvar}&($$ddef{'value'}), &($$s1def{'value'}));\n";
}

#---------------------------------------------------------------------
# Matrix log
#---------------------------------------------------------------------

sub print_m_eqop_log_m {
  my($eqop) = @_;
  my $ddef  = \%dest_def;
  my $s1def = \%src1_def;

  # type checking
  $$ddef{'t'} eq $datatype_gauge_abbrev &&
      $$s1def{'t'} eq $datatype_gauge_abbrev ||
      die "matrix log supports only gauge field\n";

  $eqop eq $eqop_eq ||
      die "matrix log supports only replacement\n";

  my $func = "QLA_${precision}${colors}_M_eq_log_M";
  my $ncvar = "";
  if($def{'nc'} eq $arg_nc) {
    $ncvar = "$arg_nc, ";
  }
  print QLA_SRC @indent,"$func(${ncvar}&($$ddef{'value'}), &($$s1def{'value'}));\n";
}

#---------------------------------------------------------------------
# norm2 reduction of any type
#---------------------------------------------------------------------

sub print_val_eqop_norm2_val {
  my($ddef,$eqop,$s1def,$qualifier) = @_;

  my($dest_elem_value,$src1_elem_value);
  my($ic,$is,$jc,$js) = &get_color_spin_indices($s1def);
  my($maxic,$maxis,$maxjc,$maxjs) = @$s1def{'mc','ms','nc','ns'};
  my($rc_d,$rc_s1) = ($$ddef{'rc'},$$s1def{'rc'});

  &print_def_open_iter_list($ic,$maxic,$is,$maxis,$jc,$maxjc,$js,$maxjs);

  # Print product for real, norm2 for complex
  $src1_elem_value = &make_accessor($s1def,$def{'nc'},$ic,$is,$jc,$js);
  my %temp = %$s1def;
  $temp{value} = $src1_elem_value;
  $temp{t} = $rc_s1;
  &make_temp(\%temp);
  $src1_elem_value = $temp{value};
  my($srce_value);
  if($rc_s1 eq "r"){
    $srce_value = "($src1_elem_value)*($src1_elem_value)";
  }
  else{
    $srce_value = "$carith0{'norm2'}($src1_elem_value)";
  }

  print QLA_SRC @indent,"$$ddef{'value'} $eqop_notation{$eqop} $srce_value;\n";

  &print_close_iter_list($ic,$is,$jc,$js);
}

#---------------------------------------------------------------------
# Accessing or setting matrix elements or column vectors
#---------------------------------------------------------------------

sub print_val_getset_component {
    my($ddef,$eqop,$s1def,$ic,$is,$jc,$js,$qualifier) = @_;

    my($dest_elem_value,$src1_elem_value);
    my($maxic,$maxis,$maxjc,$maxjs) = @$s1def{'mc','ms','nc','ns'};
    my($rc_d,$rc_s1) = ($$ddef{'rc'},$$s1def{'rc'});
    my($icx,$isx) = ("","");

    # Color and Dirac vector insertion, extraction requires loop over
    # color row index

    if($qualifier eq "getcolorvec" || $qualifier eq "setcolorvec" ||
       $qualifier eq "getdiracvec" || $qualifier eq "setdiracvec"){
	&print_int_def($ic); &open_iter($ic,$maxic);
	$icx = $ic;
    }

    # Dirac vector insertion, extraction requires loop over spin row index

    if($qualifier eq "getdiracvec" || $qualifier eq "setdiracvec"){
	&print_int_def($is); &open_iter($is,$maxis);
	$isx = $is;
    }

    # Extraction
    if($qualifier eq "getcolorvec" || $qualifier eq "getmatelem" ||
       $qualifier eq "getdiracvec"){
	# (For dest here $jc and $js should be null
	$dest_elem_value = &make_accessor($ddef,$def{'nc'},
					  $icx,$isx,"","");
	$src1_elem_value = &make_accessor($s1def,$def{'nc'},
					  $ic,$is,$jc,$js);
    }
    # Insertion
    else{
	$src1_elem_value = &make_accessor($s1def,$def{'nc'},
					  $icx,$isx,"","");
	$dest_elem_value = &make_accessor($ddef,$def{'nc'},
					  $ic,$is,$jc,$js);
    }

    &print_s_eqop_s($rc_d,$dest_elem_value,$eqop,"",$rc_s1,$src1_elem_value,"");

    if($qualifier eq "getdiracvec" || $qualifier eq "setdiracvec"){
	&close_iter($is);
    }
    if($qualifier eq "getcolorvec" || $qualifier eq "setcolorvec" ||
       $qualifier eq "getdiracvec" || $qualifier eq "setdiracvec"){
	&close_iter($ic);
    }
}

#---------------------------------------------------------------------
# Trace of matrix type
#---------------------------------------------------------------------

sub print_val_assign_tr {
    my($ddef,$eqop,$imre,$s1def) = @_;

    my($dest_elem_value,$src1_elem_value);
    my($ic,$is,$jc,$js) = &get_color_spin_indices($s1def);
    my($maxic,$maxis,$maxjc,$maxjs) = @$s1def{'mc','ms','nc','ns'};
    my($rc_d,$rc_s1) = ($$ddef{'rc'},$$s1def{'rc'});
    my($rc_x) = $rc_d;

    # Define and zero intermediate variable for accumulating trace
    my($prec, $px, $dest_t, $d_dt, $x_dt);
    $prec = $$ddef{'precision'};
    $prec = $precision if($prec eq '');
    $px = $temp_precision;
    $px = $precision if($px eq '');
    $dest_t = $$ddef{'t'};
    $d_dt = &datatype_element_specific($dest_t, $prec);
    $x_dt = &datatype_element_specific($dest_t, $px);
    &print_def($x_dt, $var_x);

    &print_s_eqop_s($rc_x,$var_x,$eqop_eq);

    &print_int_def($ic);
    &open_iter($ic,$maxic);

    &print_int_def($is); &open_iter($is,$maxis);

    # Accumulate trace
    $src1_elem_value = &make_accessor($s1def,$def{'nc'},$ic,$is,$ic,$is);
    &print_s_eqop_s($rc_x,$var_x,$eqop_peq,$imre,$rc_s1,$src1_elem_value,'',$px);

    &close_iter($is);
    &close_iter($ic);

    # Assign result to dest
    &print_s_eqop_s($rc_d,$$ddef{'value'},$eqop,"",$rc_x,$var_x,"",$prec,$px);
}

#---------------------------------------------------------------------
# Spin trace of matrix type
#---------------------------------------------------------------------

sub print_val_assign_spin_tr {
    my($ddef,$eqop,$imre,$s1def) = @_;

    my($dest_elem_value,$src1_elem_value);
    my($ic,$is,$jc,$js) = &get_color_spin_indices($s1def);
    my($maxic,$maxis,$maxjc,$maxjs) = @$s1def{'mc','ms','nc','ns'};
    my($dest_t) = $$ddef{'t'};
    my($rc_d,$rc_s1) = ($$ddef{'rc'},$$s1def{'rc'});
    my($rc_x) = $rc_d;

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
    $src1_elem_value = &make_accessor($s1def,$def{'nc'},$ic,$is,$jc,$is);
    &print_s_eqop_s($rc_x,$var_x,$eqop_peq,$imre,$rc_s1,$src1_elem_value);

    &close_iter($is);

    # Assign result to dest
    $dest_elem_value = &make_accessor($ddef,$def{'nc'},$ic,"",$jc,"");
    &print_s_eqop_s($rc_d,$dest_elem_value,$eqop,"",$rc_x,$var_x,"");

    &print_close_iter_list($ic,$jc);
}

#---------------------------------------------------------------------
#  Auxiliary routines for binary operations
#---------------------------------------------------------------------

# Check multiplication/division by scalar. Detect Kronecker delta.
# IX = const times tensor  XI = tensor times const  XX = tensor times tensor

sub times_pattern {
    my($md,$nd,$m1,$n1,$m2,$n2) = @_;

    if($m2.$n2 eq "00" && $md == $m1 && $nd == $n1){"XI";}
    elsif($m1.$n1 eq "00" && $md == $m2 && $nd == $n2){"IX";}
    elsif($md == $m1 && $nd == $n2 && $n1 == $m2){"XX";}
    else{""};
}

sub dot_pattern {
    my($md,$nd,$m1,$n1,$m2,$n2) = @_;

    if($md == 0 && $nd == 0 && $n1 == $m2){"XX";}
    else{""};
}

# Check addition/subtraction of tensors
sub plus_pattern {
    my($md,$nd,$m1,$n1,$m2,$n2) = @_;

    if($md == $m1 && $md == $m2 && 
       $nd == $n1 && $nd == $n2 ){"XX";}
    else {""};
}

sub mult_index {
  my($pat,$i,$maxi,$j,$maxj,$k,$maxk) = @_;
  my($i1, $i2, $j1, $j2);
  my($maxi1, $maxi2, $maxj1, $maxj2);
  if($pat eq "XX"){
    $i1 = $i;
    $j1 = $k;
    $i2 = $k;
    $j2 = $j;
    $maxi1 = $maxi;
    $maxj1 = $maxk;
    $maxi2 = $maxk;
    $maxj2 = $maxj;
  } elsif($pat eq "IX") {
    $i1 = "";
    $j1 = "";
    $i2 = $i;
    $j2 = $j;
    $maxi1 = "";
    $maxj1 = "";
    $maxi2 = $maxi;
    $maxj2 = $maxj;
  } elsif($pat eq "XI") {
    $i1 = $i;
    $j1 = $j;
    $i2 = "";
    $j2 = "";
    $maxi1 = $maxi;
    $maxj1 = $maxj;
    $maxi2 = "";
    $maxj2 = "";
  }
  return ($i1,$maxi1,$j1,$maxj1,$i2,$maxi2,$j2,$maxj2)
}

# Construct multiplier and multiplicand for product
sub mult_terms {
  my($cpat,$spat,$arg1_def,$arg2_def,$ic,$is,$jc,$js) = @_;

  my($arg1_elem_value,$arg2_elem_value);
  my($ic1,$is1,$jc1,$js1);
  my($ic2,$is2,$jc2,$js2);
  my($kc,$ks);

  $kc = &get_col_color_index2($arg1_def);
  $ks = &get_col_spin_index2($arg1_def);

  if($cpat eq "XX"){ $ic1=$ic; $jc1=$kc; $ic2=$kc; $jc2=$jc;}
  elsif($cpat eq "IX"){$ic1=""; $jc1=""; $ic2=$ic; $jc2=$jc; $kc = "";}
  elsif($cpat eq "XI"){$ic1=$ic; $jc1=$jc; $ic2=""; $jc2=""; $kc = "";}

  if($spat eq "XX"){ $is1=$is; $js1=$ks; $is2=$ks; $js2=$js;}
  elsif($spat eq "IX"){$is1=""; $js1=""; $is2=$is; $js2=$js; $ks = "";}
  elsif($spat eq "XI"){$is1=$is; $js1=$js; $is2=""; $js2=""; $ks = "";}

  $arg1_elem_value = &make_accessor($arg1_def,$def{'nc'},
				    $ic1,$is1,$jc1,$js1);
  $arg2_elem_value = &make_accessor($arg2_def,$def{'nc'},
				    $ic2,$is2,$jc2,$js2);

  ($kc,$ks,$arg1_elem_value,$arg2_elem_value);
}

# Construct multiplier and multiplicand for product with trace (dot product)
sub dot_terms {
    my($arg1_def,$arg2_def) = @_;
    my($arg1_elem_value,$arg2_elem_value);
    my($ic,$is,$jc,$js) = &get_color_spin_indices($arg2_def);

    $arg1_elem_value = &make_accessor($arg1_def,$def{'nc'},
				      $jc,$js,$ic,$is);
    $arg2_elem_value = &make_accessor($arg2_def,$def{'nc'},
				      $ic,$is,$jc,$js);

    ($ic,$is,$jc,$js,$arg1_elem_value,$arg2_elem_value);
}

# Do row-column product
sub print_s_eqop_v_times_v_pm_s {
  my($rc_d,$dest_t,$dest_elem_value,
     $kc,$maxkc,$ks,$maxks,$eqop,
     $rc_s1,$src1_elem_value,$conj1,
     $rc_s2,$src2_elem_value,$conj2,
     $pm,
     $rc_s3,$src3_elem_value,$conj3,
     $dprec, $s1prec, $s2prec, $s3prec) = @_;

  my($rc_x) = $rc_d;

  my($unroll) = 0;
  my($nout) = 1;

  &print_int_def($kc);
  #if( ($maxkc==2) || ($maxkc==3) ) {
  if(0) {
    $unroll = 1;
    $nout = $maxks;
  } else {
    &print_int_def($ks);
  }

  # Define and zero intermediate variable for accumulating sum
  $rc_x = $rc_d;
  my $xprec = $temp_precision;
  my $d_dt = &datatype_element_specific($dest_t, $dprec);
  my $x_dt = &datatype_element_specific($dest_t, $xprec);
  &print_def($x_dt, $var_x);

  my($loop_eqop);
  #if(!defined($src3_elem_value)){
  if($src3_elem_value == '') {
    # Assign accumulated result to dest
    if($eqop eq $eqop_eq) {
      &print_s_eqop_s($rc_x, $var_x, $eqop_eq);
      $loop_eqop = $eqop_peq;
    } elsif($eqop eq $eqop_peq) {
      &print_s_eqop_s($rc_x, $var_x, $eqop_eq, "", $rc_d, $dest_elem_value, "", $xprec, $dprec);
      $loop_eqop = $eqop_peq;
    } elsif($eqop eq $eqop_meq) {
      &print_s_eqop_s($rc_x, $var_x, $eqop_eq, "", $rc_d, $dest_elem_value, "", $xprec, $dprec);
      $loop_eqop = $eqop_meq;
    } elsif($eqop eq $eqop_eqm) {
      &print_s_eqop_s($rc_x, $var_x, $eqop_eq);
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
			 $rc_s3,$src3_elem_value,$conj3,
			 $dprec,$xprec,$s3prec);
  }

  &open_iter($kc,$maxkc);
  if(!$unroll) {
    &open_iter($ks,$maxks);
  }
  for(my $i=0; $i<$nout; $i++) {
    my($s1) = $src1_elem_value;
    my($s2) = $src2_elem_value;
    if($unroll) {
      $s1 =~ s/$ks/$i/;
      $s2 =~ s/$ks/$i/;
    }

    # Accumulate product
    &print_s_eqop_s_op_s($rc_x, $var_x,
			 $loop_eqop, "",
			 $rc_s1, $s1, $conj1,
			 '*',
			 $rc_s2, $s2, $conj2,
			 $xprec,$s1prec,$s2prec);

  }
  if(!$unroll) {
    &close_iter($ks);
  }
  &close_iter($kc);
  &print_s_eqop_s($rc_d, $dest_elem_value, $eqop_eq, "", $rc_x, $var_x, "", $dprec, $xprec);
}

# Do row-column dot product with trace
sub print_s_eqop_v_dot_v {
  my($rc_d,$dest_t,$dest_elem_value,
     $ic,$maxic,$is,$maxis,$jc,$maxjc,$js,$maxjs,
     $eqop,$imre,
     $rc_s1,$src1_elem_value,$conj1,
     $rc_s2,$src2_elem_value,$conj2,
     $dprec, $s1prec, $s2prec) = @_;

  my($rc_x) = $rc_d;

  &print_int_def($ic);
  &open_iter($ic,$maxic);
  &print_int_def($is);
  &open_iter($is,$maxis);
  &print_int_def($jc);
  &open_iter($jc,$maxjc);
  &print_int_def($js);
  &open_iter($js,$maxjs);

  # Accumulate product
  &print_s_eqop_s_op_s($rc_x,$var_x,
		       $eqop_peq,$imre,
		       $rc_s1,$src1_elem_value,$conj1,
		       '*',
		       $rc_s2,$src2_elem_value,$conj2,
		       $dprec, $s1prec, $s2prec);

  &close_iter($js); &close_iter($jc);
  &close_iter($is); &close_iter($ic);
}

#---------------------------------------------------------------------
#  Binary operation between tensors
#---------------------------------------------------------------------

#%c_eqop = ( "eq"=>"=", "eqm"=>"=-", "peq"=>"+=", "meq"=>"-=" );

sub print_array_def($$$$) {
  my($typeabbr, $var, $ni, $nj) = @_;
  my $ss = "";
  my $ni0 = -1; my $ni1 = 0;
  my $nj0 = -1; my $nj1 = 0;
  if($ni) { $ss .= "[$ni]"; $ni0 = 0; $ni1 = $ni; }
  if($nj) { $ss .= "[$nj]"; $nj0 = 0; $nj1 = $nj; }
  my $unroll = 0;
  if($unroll) {
    my $vt = "";
    for(my $ii=$ni0; $ii<$ni1; $ii++) {
      for(my $jj=$nj0; $jj<$nj1; $jj++) {
	if($vt) { $vt .= ", "; }
	$vt .= "$var";
	if($ii>=0) { $vt .= $ii; }
	if($jj>=0) { $vt .= $jj; }
      }
    }
    print_def(datatype_specific($typeabbr),$vt);
  } else {
    print_def(datatype_specific($typeabbr),$var.$ss);
  }
  return $var.$ss;
}

sub get_array_val($$$) {
  my($var, $vi, $vj) = @_;
  my $ss = "";
  if($vi) { $ss .= "[$vi]"; }
  if($vj) { $ss .= "[$vj]"; }
  return $var.$ss;
}

sub print_c_eq_zero($) {
  my($var) = @_;
  print QLA_SRC @indent, "QLA_c_eq_r($var,0.);\n"
}

sub print_c_op_c_times_r($$$$$) {
  my($d,$op,$s1,$conj1,$s2) = @_;
  if($conj1 eq "") {
    print QLA_SRC @indent, "QLA_c_".$op."_c_times_r($d,$s1,$s2);\n"
  } else {
    my($cop,$copm);
    $cop = $eqop_notation{$op};
    ($copm = $cop) =~ tr/+-/-+/;
    print QLA_SRC @indent, "QLA_real($d) $cop  QLA_real($s1) * $s2;\n";
    print QLA_SRC @indent, "QLA_imag($d) $copm QLA_imag($s1) * $s2;\n";
  }
}

sub print_c_op_c_times_ir($$$$$$) {
  my($d,$op,$s1,$conj1,$s2,$conj2) = @_;
  my($cop,$copm);
  my($cop1,$cop2);
  $cop = $eqop_notation{$op};
  ($copm = $cop) =~ tr/+-/-+/;
  if($conj2 eq "") { $cop1 = $copm; $cop2 = $cop; }
  else { $cop1 = $cop; $cop2 = $copm; }
  if($conj1 ne "") { $cop1 = $cop2; }
  print QLA_SRC @indent, "QLA_real($d) $cop1 QLA_imag($s1) * $s2;\n";
  print QLA_SRC @indent, "QLA_imag($d) $cop2 QLA_real($s1) * $s2;\n";
}

sub print_rr_op_c_times_r($$$$$$) {
  my($dr,$di,$op,$s1,$conj1,$s2) = @_;
  my($cop1,$cop2);
  $cop1 = $eqop_notation{$op};
  if($conj1 eq "") {
    $cop2 = $cop1;
  } else {
    ($cop2 = $cop1) =~ tr/+-/-+/;
  }
  print QLA_SRC @indent, "$dr $cop1 QLA_real($s1) * $s2;\n";
  print QLA_SRC @indent, "$di $cop2 QLA_imag($s1) * $s2;\n";
}

sub print_rr_op_c_times_ir($$$$$$$) {
  my($dr,$di,$op,$s1,$conj1,$s2,$conj2) = @_;
  my($cop,$copm);
  my($cop1,$cop2);
  $cop = $eqop_notation{$op};
  ($copm = $cop) =~ tr/+-/-+/;
  if($conj2 eq "") { $cop1 = $copm; $cop2 = $cop; }
  else { $cop1 = $cop; $cop2 = $copm; }
  if($conj1 ne "") { $cop1 = $cop2; }
  print QLA_SRC @indent, "$dr $cop1 QLA_imag($s1) * $s2;\n";
  print QLA_SRC @indent, "$di $cop2 QLA_real($s1) * $s2;\n";
}

sub print_MV {
  my($ddef,$eqop,$s1def,$s2def) = @_;

  print QLA_SRC "test\n";
}

sub print_val_eqop_val_op_val {
  my($ddef,$eqop,$imre,$s1def,$op,$s2def) = @_;

  my $inline = 1;
  if(!$inline) {
#      if( ($op eq "times") && ($$s1def{t} eq "M") ) {
#        if($$s2def{t} eq "V") {
#	  &print_MV($ddef,$eqop,$s1def,$s2def);
#          return;
#        }
#      }
    my($func) = "$def{prefix}";
    $func .= "_$$ddef{t}$$ddef{adj}";
    $func .= "_$eqop";
    $func .= "_$$s1def{t}$$s1def{adj}";
    $func .= "_$op";
    $func .= "_$$s2def{t}$$s2def{adj}";
    my($args);
    $args = "&$$ddef{value}";
    $args .= ", &$$s1def{value}";
    $args .= ", &$$s2def{value}";
    $args =~ s/&\*//g;
    print QLA_SRC @indent, "$func($args);\n";
    #print "$func($args);\n";
    #print %dest_def, "\n";
    return;
  }

  my($dest_elem_value,$src1_elem_value,$src2_elem_value);
  my($rc_d,$rc_s1,$rc_s2) = 
      ($$ddef{'rc'},$$s1def{'rc'},$$s2def{'rc'});
  my($rc_x);

  my($mcd,$msd,$ncd,$nsd) = @$ddef {'mc','ms','nc','ns'};
  my($mc1,$ms1,$nc1,$ns1) = @$s1def{'mc','ms','nc','ns'};
  my($mc2,$ms2,$nc2,$ns2) = @$s2def{'mc','ms','nc','ns'};

  my($ic,$is,$jc,$js);
  my($maxic,$maxis,$maxjc,$maxjs);
  my($cpat,$spat);
  my($pmd);

  my($kc,$ks);
  my($maxkc,$maxks) = ($nc1,$ns1);

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

  if($op eq "times") {

    # Get outer tensor indices
    ($maxic,$maxis,$maxjc,$maxjs) = ($mcd,$msd,$ncd,$nsd);
    ($ic,$is,$jc,$js) = &get_color_spin_indices($ddef);

    # Construct multiplier and multiplicand
    ($kc,$ks,$src1_elem_value,$src2_elem_value) = 
      &mult_terms($cpat,$spat,$s1def,$s2def,$ic,$is,$jc,$js);

    # If we are summing over kc or ks, need to handle the sum
    if($kc ne "" || $ks ne "") {

      print_def_open_iter_list($ic,$maxic,$is,$maxis,$jc,$maxjc,$js,$maxjs);
      $dest_elem_value =
	  make_accessor($ddef,$def{'nc'},$ic,$is,$jc,$js);
      print_s_eqop_v_times_v_pm_s($rc_d, $$ddef{'t'}, $dest_elem_value,
				  $kc, $maxkc, $ks, $maxks, $eqop,
				  $rc_s1, $src1_elem_value, $$s1def{conj},
				  $rc_s2, $src2_elem_value, $$s2def{conj},
				  '',
				  '','','',
				  $$ddef{precision}, $$s1def{precision}, $$s2def{precision});
#      if(!$noclose) {
      print_close_iter_list($ic,$is,$jc,$js);
#      }

    }
    # Otherwise, a simple product
    else{

      # Open iteration over outer tensor indices
      &print_def_open_iter_list($ic,$maxic,$is,$maxis,$jc,$maxjc,$js,$maxjs);

      $dest_elem_value =
	&make_accessor($ddef,$def{'nc'},$ic,$is,$jc,$js);

#      $prec = $precision;
#      if( ($temp_precision ne '') && ($prec ne $temp_precision) && ($prec ne "") ) {
#	$rc_t = $rc_d;
#	$var_t = $var_x;
#	$prec_t = $temp_precision;
#	$dt_t = &datatype_element_specific($$ddef{'t'}, $prec_t);
#        # Define and prepare temporary variable
#	&print_def($dt_t, $var_t);
#	if( ($eqop eq $eqop_peq) || ($eqop eq $eqop_meq) ) {
#	  &print_s_eqop_s($rc_t, $var_t, $eqop_eq, "", $rc_d, $dest_elem_value, "", $prec_t, $precision);
#	}
#      } else {
#	$rc_t = $rc_d;
#	$var_t = $dest_elem_value;
#      }
#      &print_s_eqop_s_op_s($rc_t,$var_t,
#			   $eqop,"",
#			   $rc_s1,$src1_elem_value,$$s1def{'conj'},
#			   '*',
#			   $rc_s2,$src2_elem_value,$$s2def{'conj'});
#      if( ($temp_precision ne '') && ($prec ne $temp_precision) && ($prec ne "") ) {
#	&print_s_eqop_s($rc_d, $dest_elem_value, $eqop_eq, "", $rc_t, $var_t, "", $precision, $prec_t);
#      }
      &print_s_eqop_s_op_s($rc_d,$dest_elem_value,
			   $eqop,"",
			   $rc_s1,$src1_elem_value,$$s1def{'conj'},
			   '*',
			   $rc_s2,$src2_elem_value,$$s2def{'conj'},
			   $$ddef{precision}, $$s1def{precision}, $$s2def{precision});

#      if(!$noclose) {
      &print_close_iter_list($ic,$is,$jc,$js);
#      }

    }

  }

  elsif($op eq "dot"){
    my($maxic,$maxis,$maxjc,$maxjs) = ($mc2,$ms2,$nc2,$ns2);

    # Destination value (must be scalar, so no indices)
    $dest_elem_value =  &make_accessor($ddef,$def{'nc'},"","","","");

    # Construct multiplier and multiplicand
    ($ic,$is,$jc,$js,$src1_elem_value,$src2_elem_value) =
      &dot_terms($s1def,$s2def);

    # If we are summing over ic, jc, is, or js, need to handle the sum
    if($ic ne "" || $is ne "" || $jc ne "" || $js ne ""){
      &print_s_eqop_v_dot_v($rc_d,$$ddef{'t'},$dest_elem_value,
			    $ic,$maxic,$is,$maxis,$jc,$maxjc,$js,$maxjs,
			    $eqop,$imre,
			    $rc_s1,$src1_elem_value,$$s1def{'conj'},
			    $rc_s2,$src2_elem_value,$$s2def{'conj'},
			    $$ddef{precision}, $$s1def{precision}, $$s2def{precision});
    }
    # Otherwise, a simple product
    else{
      &print_s_eqop_s_op_s($rc_d,$dest_elem_value,
			   $eqop,$imre,
			   $rc_s1,$src1_elem_value,$$s1def{'conj'},
			   '*',
			   $rc_s2,$src2_elem_value,$$s2def{'conj'},
			   $$ddef{precision}, $$s1def{precision}, $$s2def{precision});
    }
  }

  # Sum or difference of tensors or division by scalar
  elsif($op eq "plus" || $op eq "minus" || $op eq "divide"){

    # Open iteration over outer tensor indices
    ($maxic,$maxis,$maxjc,$maxjs) = ($mcd,$msd,$ncd,$nsd);
    ($ic,$is,$jc,$js) = &get_color_spin_indices($ddef);

    &print_def_open_iter_list($ic,$maxic,$is,$maxis,$jc,$maxjc,$js,$maxjs);
    $dest_elem_value =
      &make_accessor($ddef,$def{'nc'},$ic,$is,$jc,$js);

    $src1_elem_value = &make_accessor($s1def,$def{'nc'},$ic,$is,$jc,$js);
    $src2_elem_value = &make_accessor($s2def,$def{'nc'},$ic,$is,$jc,$js);
    if($op eq "plus"){$pmd = '+';} 
    elsif($op eq "minus"){$pmd = '-';}
    else{$pmd = '/';}
    &print_s_eqop_s_op_s($rc_d,$dest_elem_value,
			 $eqop,"",
			 $rc_s1,$src1_elem_value,$$s1def{'conj'},
			 $pmd,
			 $rc_s2,$src2_elem_value,$$s2def{'conj'},
			 $$ddef{precision}, $$s1def{precision}, $$s2def{precision});

#    if(!$noclose) {
    &print_close_iter_list($ic,$is,$jc,$js);
#    }
  }

  else{
    die "Can't do op $op\n";
  }

}

#---------------------------------------------------------------------
#  Binary operation on integers and reals
#---------------------------------------------------------------------

my %bool_binary_op = (
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
    my($ddef,$eqop,$s1def,$op,$s2def) = @_;
    my($sym);

    if($op eq "lshift"){
	&print_s_eqop_s("r",$$ddef{'value'},$eqop,"","r",
			"$$s1def{'value'} << $$s2def{'value'}");
    }
    elsif($op eq "rshift"){
	&print_s_eqop_s("r",$$ddef{'value'},$eqop,"","r",
			"$$s1def{'value'} >> $$s2def{'value'}");
    }
    elsif($op eq "mod"){
	if($$ddef{'t'} eq $datatype_integer_abbrev &&
	   $$s1def{'t'} eq $datatype_integer_abbrev &&
	   $$s2def{'t'} eq $datatype_integer_abbrev){
	    &print_s_eqop_s("r",$$ddef{'value'},$eqop,"","r",
			    "$$s1def{'value'} % $$s2def{'value'}");
	}
	else{
	    &print_s_eqop_s("r",$$ddef{'value'},$eqop,"","r",
			    "fmod($$s1def{'value'},$$s2def{'value'})");
	}
    }
    elsif($op eq "pow"){
	&print_s_eqop_s("r",$$ddef{'value'},$eqop,"","r",
			"pow($$s1def{'value'},$$s2def{'value'})");
	}
    elsif($op eq "atan2"){
	&print_s_eqop_s("r",$$ddef{'value'},$eqop,"","r",
			"atan2($$s1def{'value'},$$s2def{'value'})");
	}
    elsif($op eq "ldexp"){
	&print_s_eqop_s("r",$$ddef{'value'},$eqop,"","r",
			"ldexp($$s1def{'value'},$$s2def{'value'})");
	}
    elsif($op eq "max"){
	&print_s_eqop_s("r",$$ddef{'value'},$eqop,"","r",
		  "($$s1def{'value'} > $$s2def{'value'} ? $$s1def{'value'} : $$s2def{'value'})");
    }
    elsif($op eq "min"){
	&print_s_eqop_s("r",$$ddef{'value'},$eqop,"","r",
		  "($$s1def{'value'} > $$s2def{'value'} ? $$s2def{'value'} : $$s1def{'value'})");
    }
    elsif($op eq "mask"){
	print QLA_SRC @indent,"if($$s2def{'value'}) {\n";
	open_block();
	&print_val_eqop_op_val($ddef,$eqop,$s1def,"");
	close_block();
	print QLA_SRC @indent,"}\n";
    }
    else{
	$sym = $bool_binary_op{$op};
	defined($sym) || die "No boolean support for $op\n";
	&print_s_eqop_s("r",$$ddef{'value'},$eqop,"","r",
		  "( $$s1def{'value'} ".$sym." $$s2def{'value'} )");
    }
}

#---------------------------------------------------------------------
# Ternary tensor operation
#---------------------------------------------------------------------
# Supports only a*b + c and a*b - c

sub print_val_eqop_val_op_val_op2_val {
    my($ddef,$eqop,$s1def,$op,$s2def,$op2,$s3def) = @_;

    my($dest_elem_value,$src1_elem_value,$src2_elem_value,$src3_elem_value);
    my($ic,$is,$jc,$js) = &get_color_spin_indices($ddef);
    my($kc,$ks);
    my($rc_d,$rc_s1,$rc_s2,$rc_s3) = 
	($$ddef{'rc'},$$s1def{'rc'},$$s2def{'rc'},$$s3def{'rc'});
    my($rc_x);

    my($mcd,$msd,$ncd,$nsd) = @$ddef {'mc','ms','nc','ns'};
    my($mc1,$ms1,$nc1,$ns1) = @$s1def{'mc','ms','nc','ns'};
    my($mc2,$ms2,$nc2,$ns2) = @$s2def{'mc','ms','nc','ns'};
    my($mc3,$ms3,$nc3,$ns3) = @$s3def{'mc','ms','nc','ns'};

    my($kc,$ks);
    my($pm);

    my($maxic,$maxis,$maxjc,$maxjs) = ($mcd,$msd,$ncd,$nsd);
    my($maxkc,$maxks) = ($nc1,$ns1);

    # Operand color/spin dimension consistency checks
    # Also detects patterns for use with multiplication

    my($cpat, $spat);
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

    &print_def_open_iter_list($ic,$maxic,$is,$maxis,$jc,$maxjc,$js,$maxjs);
    $dest_elem_value = &make_accessor($ddef,$def{'nc'},$ic,$is,$jc,$js);

    # Construct multiplier and multiplicand
    ($kc,$ks,$src1_elem_value,$src2_elem_value) = 
	&mult_terms($cpat,$spat,$s1def,$s2def,$ic,$is,$jc,$js);

    # Construct addend
    $src3_elem_value = &make_accessor($s3def,$def{'nc'},
				      $ic,$is,$jc,$js);

    # If we are summing over kc or ks, need to handle the sum
    if($kc ne "" || $ks ne ""){
	&print_s_eqop_v_times_v_pm_s(
                             $rc_d,$$ddef{'t'},$dest_elem_value,
			     $kc,$maxkc,$ks,$maxks,$eqop,
			     $rc_s1,$src1_elem_value,$$s1def{'conj'},
			     $rc_s2,$src2_elem_value,$$s2def{'conj'},
			     $pm,
			     $rc_s3,$src3_elem_value,$$s3def{'conj'});
    }

    # Otherwise, a simple product plus or minus arg3
    else{
	&print_s_eqop_s_times_s_pm_s(
                             $rc_d,$dest_elem_value,
			     $eqop,
			     $rc_s1,$src1_elem_value,$$s1def{'conj'},
			     '*',
			     $rc_s2,$src2_elem_value,$$s2def{'conj'},
			     $pm,
			     $rc_s3,$src3_elem_value,$$s3def{'conj'});
    }

    &print_close_iter_list($ic,$is,$jc,$js);
}

#---------------------------------------------------------------------
# Fills for various types
#---------------------------------------------------------------------

sub print_fill {
  my($ddef,$qualifier) = @_;

  my($ic,$is,$jc,$js) = &get_color_spin_indices($ddef);
  my($maxic,$maxis,$maxjc,$maxjs) = @$ddef{'mc','ms','nc','ns'};
  my($rc_d)  = $$ddef{'rc'};

  &print_def_open_iter_list($ic,$maxic,$is,$maxis,$jc,$maxjc,$js,$maxjs);

  my $dest_elem_value = &make_accessor($ddef,$def{'nc'},$ic,$is,$jc,$js);

  if($qualifier eq "zero") {
    &print_s_eqop_s($rc_d,$dest_elem_value,$eqop_eq,"","r","0.","");
  }

  &print_close_iter_list($ic,$is,$jc,$js);
}
1;
