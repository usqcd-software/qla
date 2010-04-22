######################################################################
# SciDAC Software Project
# BUILD_QLA Version 0.9
#
# expressions_scalar.pl
#
# Author: C. DeTar
# Date:   09/13/02
######################################################################
#
# Building blocks for arithmetic expressions
# involving complex or real scalars
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

use vars qw/ %carith1 %carith2 %carith3 %eqop_notation /;
use vars qw/ $precision $temp_precision /;
use vars qw/ $var_i /;
use vars qw/ @indent /;

######################################################################

#---------------------------------------------------------------------
# Scalar (real/complex) assignment 
#---------------------------------------------------------------------

sub print_s_eqop_s {
  my($rc_d,$dest,$eqop,$imre,$rc_s,$srce,$conj_s,$prec_d,$prec_s) = @_;

  # If srce is undefined, assign zero.
  if(!defined($srce)){$rc_s = "r"; $srce = "0.";}
  if($rc_s eq "r"){$conj_s = ""; $imre = "";}
  if($prec_d eq '') { $prec_d = $precision; }
  if($prec_s eq '') { $prec_s = $precision; }

  if($rc_d eq "r" && $rc_s eq "r") {
    print QLA_SRC @indent,"$dest $eqop_notation{$eqop} $srce;\n";
  } else {
    my($key) = $eqop.$imre.$rc_s.$conj_s;
    my($macro) = $carith1{$key};
    defined($macro) || die "no carith1 for $key\n";

    if( $rc_d eq "c" && $rc_s eq "c" ) {
      if( $key eq "peqc" || $key eq "meqc" ) {
	if($temp_precision ne '' && $temp_precision ne $prec_s) {
	  ($srce, $prec_s) = &make_cast($srce, 'c', $temp_precision, $prec_s);
	}
      }
      if( $prec_d ne $prec_s && $key eq "eqc" ) {
	$macro =~ s/QLA/QLA_$prec_d$prec_s/;
      }
      if( $prec_d ne $prec_s && ($key eq "peqc" || $key eq "meqc" || $key eq "eqmc") ) {
	if($temp_precision ne '' && $temp_precision ne $prec_d) {
	  &print_prec_conv_macro("$macro(", $dest, ", $srce);", 'C', $prec_d, $prec_s);
	} else {
	  ($srce, $prec_s) = &make_cast($srce, 'c', $prec_d, $prec_s);
	  print QLA_SRC @indent,"$macro($dest,$srce);\n";
	}
      } else {
	print QLA_SRC @indent,"$macro($dest,$srce);\n";
      }
    }
    elsif($rc_d eq "c" || $imre eq "R" || $imre eq "I") {
      print QLA_SRC @indent,"$macro($dest,$srce);\n";
    } else {
      print "$rc_d $dest $key $rc_s $srce $prec_d $prec_s\n";
      die "print_s_eqop_s: can't assign complex to real\n";
    }
  }
}

#---------------------------------------------------------------------
# Scalar (real/complex) assignment: with binary operation
#---------------------------------------------------------------------

sub print_s_eqop_s_op_s {
  my($rc_d,$dest,
     $eqop,$imre,
     $rc_s1,$src1,$conj_s1,
     $op,
     $rc_s2,$src2,$conj_s2,
     $prec_d,$prec_s1,$prec_s2) = @_;

  if($rc_s1 eq "r") {$conj_s1 = "";}
  if($rc_s2 eq "r") {$conj_s2 = "";}

  # Case complex eqop real  or complex eqop complex (*)
  # or real eq real part or imag part of complex
  if($rc_d eq "c" || $imre ne "") {
    my $key = $eqop.$imre.$rc_s1.$conj_s1.$op.$rc_s2.$conj_s2;
    my($macro) = $carith2{$key};
    defined($macro) || die "no carith2 for $key\n";
    if($temp_precision ne '') {
      ($src1, $prec_s1) = &make_cast($src1, $rc_s1, $temp_precision, $prec_s1);
      ($src2, $prec_s2) = &make_cast($src2, $rc_s2, $temp_precision, $prec_s2);
      my $dt = uc($rc_d);
      print_prec_conv_macro("$macro(", $dest, ", $src1, $src2);",
			    $dt, $prec_d, $prec_s1);
    } else {
      ($src1, $prec_s1) = &make_cast($src1, $rc_s1, $prec_d, $prec_s1);
      ($src2, $prec_s2) = &make_cast($src2, $rc_s2, $prec_d, $prec_s2);
      print QLA_SRC @indent,"$macro($dest, $src1, $src2);\n";
    }
  }

  # Case real eqop real
  else{
    # Simple real to real
    if($rc_s1 eq "r" && $rc_s2 eq "r"){
      print QLA_SRC @indent,"$dest $eqop_notation{$eqop} $src1 $op $src2;\n";
    }
    else{
      die "print_s_eqop_s_op_s: can't assign complex to real\n";
    }
  }
}

#---------------------------------------------------------------------
# Scalar (real/complex) assignment: with ternary operation
#---------------------------------------------------------------------

sub print_s_eqop_s_times_s_pm_s {
  my($rc_d,$dest,
     $eqop,
     $rc_s1,$src1,$conj_s1,
     $op,
     $rc_s2,$src2,$conj_s2,
     $op2,
     $rc_s3,$src3,$conj_s3,
     $prec_d,$prec_s1,$prec_s2,$prec_s3) = @_;

  $op eq '*' && ($op2 eq '+' || $op2 eq '-') || 
      die "Supports only s * s +/- s\n";

  if($rc_s1 eq "r"){$conj_s1 = "";}
  if($rc_s2 eq "r"){$conj_s2 = "";}
  if($rc_s3 eq "r"){$conj_s3 = "";}

  # Case complex eqop real or complex eqop complex (*)
  if($rc_d eq "c"){
    my $key = $eqop.$rc_s1.$conj_s1.$op.$rc_s2.$conj_s2.$op2.$rc_s3.$conj_s3;
    my($macro) = $carith3{$key};
    defined($macro) || die "no carith3 for $key\n";
    #print QLA_SRC @indent,"$macro($dest,$src1,$src2,$src3);\n";
    ($src1, $prec_s1) = &make_cast($src1, $rc_s1, $temp_precision, $prec_s1);
    ($src2, $prec_s2) = &make_cast($src2, $rc_s2, $temp_precision, $prec_s2);
    ($src3, $prec_s3) = &make_cast($src3, $rc_s3, $temp_precision, $prec_s3);
    my $dt = uc($rc_d);
    print_prec_conv_macro("$macro(", $dest, ", $src1, $src2, $src3);",
			  $dt, $prec_d, $prec_s1);
  }

  # Case real eqop real
  else{
    if($rc_s1 eq "r" && $rc_s2 eq "r" && $rc_s3 eq "r"){
      print QLA_SRC @indent,"$dest $eqop_notation{$eqop} $src1 $op $src2 $op2 $src3;\n";
    }
    else{
      die "print_s_eqop_s_op_s: can't assign complex to real\n";
    }
  }
}

#---------------------------------------------------------------------
# Real to complex conversion
#---------------------------------------------------------------------

sub print_c_eqop_r_plus_ir {
  my($c,$eqop,$x,$y) = @_;
  my($key,$macro);

  # Null argument defaults to zero
  if($x eq ""){$x = 0.;}
  if($y eq ""){$y = 0.;}

  $key = $eqop."r+ir";
  $macro = $carith2{$key};
  defined($macro) || die "no carith2 for $key\n";
  print QLA_SRC @indent,"$macro($c,$x,$y);\n";
}
