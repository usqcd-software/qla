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

require("variable_names.pl");
require("headers.pl");
require("formatting.pl");
require("operatortypes.pl");

######################################################################

#---------------------------------------------------------------------
# Scalar (real/complex) assignment 
#---------------------------------------------------------------------

sub print_s_eqop_s {
    local($rc_d,$dest,$eqop,$imre,$rc_s,$srce,$conj_s) = @_;
    local($key);

    # If srce is undefined, assign zero.
    if(!defined($srce)){$rc_s = "r"; $srce = "0.";}
    if($rc_s eq "r"){$conj_s = ""; $imre = "";}

    # Case complex eqop real  or complex eqop complex (*)

    if($rc_d eq "c"  || $imre eq "R" || $imre eq "I"){
	$key = $eqop.$imre.$rc_s.$conj_s;
	local($macro) = $carith1{$key};
	defined($macro) || die "no carith1 for $key\n";
	print QLA_SRC @indent,"$macro($dest,$srce);\n";
    }

    # Case real eqop real

    else{
	if($rc_s eq "r"){
	    print QLA_SRC @indent,"$dest $eqop_notation{$eqop} $srce;\n";
	}
	else{
	    die "print_s_eqop_s: can't assign complex to real\n";
	}
    }
}

#---------------------------------------------------------------------
# Scalar (real/complex) assignment: with binary operation
#---------------------------------------------------------------------

sub print_s_eqop_s_op_s {
    local($rc_d,$dest,
	  $eqop,$imre,
	  $rc_s1,$src1,$conj_s1,
	  $op,
	  $rc_s2,$src2,$conj_s2) = @_;

    local($key);

    if($rc_s1 eq "r"){$conj_s1 = "";}
    if($rc_s2 eq "r"){$conj_s2 = "";}

    # Case complex eqop real  or complex eqop complex (*)
    # or real eq real part or imag part of complex

    if($rc_d eq "c" || $imre ne ""){
	$key = $eqop.$imre.$rc_s1.$conj_s1.$op.$rc_s2.$conj_s2;
	local($macro) = $carith2{$key};
	defined($macro) || die "no carith2 for $key\n";
	print QLA_SRC @indent,"$macro($dest,$src1,$src2);\n";
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
    local($rc_d,$dest,
	  $eqop,
	  $rc_s1,$src1,$conj_s1,
	  $op,
	  $rc_s2,$src2,$conj_s2,
	  $op2,
	  $rc_s2,$src3,$conj_s3) = @_;

    local($key);

    $op eq '*' && ($op2 eq '+' || $op2 eq '-') || 
	die "Supports only s * s +/- s\n";

    if($rc_s1 eq "r"){$conj_s1 = "";}
    if($rc_s2 eq "r"){$conj_s2 = "";}
    if($rc_s3 eq "r"){$conj_s3 = "";}

    # Case complex eqop real  or complex eqop complex (*)

    if($rc_d eq "c"){
	$key = $eqop.$rc_s1.$conj_s1.$op.$rc_s2.$conj_s2.$op2.$rc_s3.$conj_s3;
	local($macro) = $carith3{$key};
	defined($macro) || die "no carith2 for $key\n";
	print QLA_SRC @indent,"$macro($dest,$src1,$src2,$src3);\n";
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
    local($c,$eqop,$x,$y) = @_;
    local($key,$macro);

    # Null argument defaults to zero
    if($x eq ""){$x = 0.;}
    if($y eq ""){$y = 0.;}
    
    $key = $eqop."r+ir";
    $macro = $carith2{$key};
    defined($macro) || die "no carith2 for $key\n";
    print QLA_SRC @indent,"$macro($c,$x,$y);\n";
}

