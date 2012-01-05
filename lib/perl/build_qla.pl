#!/usr/bin/env perl

######################################################################
# SciDAC Software Project
# Build QLA Version 0.9
#
# headers.pl
#
# Author: C. DeTar
# Date:   09/13/02
######################################################################
#
# Generates the C-encoded QLA library routines and associated headers
#
# 1. C source files for a single target library are built.
# 2. The associated header file with function prototypes is built.
# 3. Where appropriate, a separate header "defines" file is also built
#    for mapping specific function names to generic names.
#
######################################################################
# Changes
#
######################################################################
# To do:

# need to work out conventions for paths to headers
# scalar constant multiplies look just like scalar multiplies - keep?
# summing a scalar does nothing - drop this?
# need proper runtime error handling (e.g. gamma matrix routines)
#	
#
######################################################################
# Parse the argument list and set global colors and namespace
######################################################################

die "Usage: $0 <prefix> <header_file> <c_source_path>\n" if $#ARGV < 2;

($target,$qla_header_file,$c_source_path) = @ARGV;
($namespace,$pc) = split("_",$target);

# We build code only for routines matching the target.
# We allow the permutations DF -> FD and DQ -> QD, however.
$target2 = $target; 

if ($target2 =~ /DF/){$target =~ s/DF/FD/;}
if ($target2 =~ /FD/){$target =~ s/FD/DF/;}

if ($target2 =~ /DQ/){$target =~ s/DQ/QD/;}
if ($target2 =~ /QD/){$target =~ s/QD/DQ/;}

$request_precision = $request_colors = $pc;
# Strip any color label (integer or "N"), leaving just the precision code
$request_precision =~ s/\d//; $request_precision =~ s/N//;
# Strip the precision label, leaving just the color code
$request_colors =~ s/$request_precision//;

# $request_precision and $request_colors are used to set parameters
# in the target header file.
# $precision and $colors are used to construct trial prefixes and types
# prior to filtering out procedures not matching the target

# Even if the target precision is not specified in the
# argument list, we still create trial function names before filtering
# so we set a global default value.
# We also need a prevailing precision for deciding how to promote
# precision in global reductions.  In this case we take the lower precision

($precision,$colors) = ($request_precision,$request_colors);
$precision = "F" if ($precision eq "DF" || $precision eq "FD");
$precision = "D" if ($precision eq "DQ" || $precision eq "QD");
$precision = "F" if !$precision;
$colors = "3" if ! $colors;

# We don't want a generic defines file for the integer or DF libraries
$do_generic_defines = 1;
$do_color_generic_defines = 1;
if($request_precision eq "DF" || $request_precision eq "FD"){
    $do_generic_defines = 0;
}
if($request_precision eq "DQ" || $request_precision eq "QD"){
    $do_generic_defines = 0;
}
if(!$request_precision && !$request_colors){
    $do_generic_defines = 0;
    $do_color_generic_defines = 0;
}
if(!$request_colors){
    $do_color_generic_defines = 0;
}

#  We do only a very limited set of functions for Q precision 
if($precision eq "Q"){$quadprecision = 1;}
else{$quadprecision = 0;}

######################################################################
# Supporting files required
######################################################################

$path = "./";
$path = $1 if ( $0 =~ m|(.*/)[^/]*| );
push @INC, $path;

require("../perl/defines.pl") if -f "../perl/defines.pl";
require($path."datatypes.pl");
require($path."operatortypes.pl");
require($path."indirection.pl");
require($path."prototype.pl");

######################################################################
# Comment lines for the header files
######################################################################

sub header0 {
    local($string) = @_;

    $comment0 = 
	"\n".
	"/***************************************************************/\n".
	"/* $string */\n".
	"/***************************************************************/\n".
	"\n";
    $comment1 = "";
    $comment2 = "";
    $comment3 = "";
}

sub header1 {
    local($string) = @_;

    $comment1 =
	"\n".
	"/*===================================================*/\n".
	"/* $string */\n".
	"/*===================================================*/\n".
	"\n";
    $comment2 = "";
    $comment3 = "";
}

sub header2 {
    local($string) = @_;

    $comment2 = 
	"\n".
	"/*---------------------------------------------------*/\n".
	"/* $string */\n".
	"/*---------------------------------------------------*/\n".
	"\n";
    $comment3 = "";
}

sub header3 {
    local($string) = @_;

    $comment3 =
	"\n".
	"/* $string */\n".
	"\n".
	"\n";
}

######################################################################
# Main procedure
######################################################################

# Note: Each stanza below is intended to be independent of the other.

#---------------------------------------------------------------------
# Open QLA header file
#---------------------------------------------------------------------

&open_qla_header($qla_header_file);
if($do_generic_defines || $do_color_generic_defines){
    &open_generic_defines_header($qla_header_file,
				 $do_generic_defines,
				 $do_color_generic_defines);
}

######################################################################
&header0("Level 1 Linear Algebra API $namespace precision $request_precision color $request_colors");
######################################################################

#=====================================================================
&header1("Unary Operations");
#=====================================================================

#---------------------------------------------------------------------
&header2("Elementary unary functions real to real");
#---------------------------------------------------------------------

require("make_code_unary.pl");

if(!$quadprecision){

@assign_list = ( $eqop_eq );
@data_list   = ( $datatype_real_abbrev );
@unary_fcns = ( 'cos','sin','tan','acos','asin','atan',
		'sqrt','fabs','exp','log','sign',
		'cosh', 'sinh', 'tanh', 'log10', 'floor', 'ceil');

foreach $unary_fcn ( @unary_fcns ){
    foreach $assgn ( @assign_list ){
	foreach $t ( @data_list ){
	    &header3( "$unary_fcn");
	    foreach $indexing ( @ind_unary_list ){
		%def = ();
		($def{'dest_t'},$def{'src1_t'}) = ($t,$t);
		$def{'qualifier'} = $unary_fcn;
		if(&make_prototype($indexing,$assgn)){
		    &make_code_unary_fcn($assgn,$unary_fcn);
		}
	    }
	}
    }
}
}
#---------------------------------------------------------------------
&header2("Elementary binary functions reals to real");
#---------------------------------------------------------------------

require("make_code_binary.pl");

if(!$quadprecision){

$assgn = $eqop_eq;

$t = $datatype_real_abbrev;
$dest_t = $t;
$src1_t = $t;
$src2_t = $t;

foreach $op ( "mod", "max", "min", "pow", "atan2" ){
    &header3(" $datatype_generic_name{$t} (r = a $op b)");
    foreach $indexing ( @ind_binary_list ){
	%def = ();
	($def{'dest_t'},$def{'src1_t'},$def{'src2_t'}) = 
	    ($dest_t,$src1_t,$src2_t);
	$def{'op'} = $op;
	if(&make_prototype($indexing,$assgn)){
	    &make_code_binary_elementary($assgn);
	}
    }
}

# Special case takes an int for the second argument

$assgn = $eqop_eq;

$t = $datatype_real_abbrev;
$dest_t = $t;
$src1_t = $t;
$src2_t = $datatype_integer_abbrev;

foreach $op ( "ldexp" ){
    &header3(" $datatype_generic_name{$t} [r = a $op b (int)]");
    foreach $indexing ( @ind_binary_list ){
	%def = ();
	($def{'dest_t'},$def{'src1_t'},$def{'src2_t'}) = 
	    ($dest_t,$src1_t,$src2_t);
	$def{'op'} = $op;
	if(&make_prototype($indexing,$assgn)){
	    &make_code_binary_elementary($assgn);
	}
    }
}
}

#---------------------------------------------------------------------
&header2("Elementary unary functions real to complex");
#---------------------------------------------------------------------

require("make_code_unary.pl");

if(!$quadprecision){

@assign_list = ( $eqop_eq );
@unary_fcns = ( 'cexpi' );

foreach $unary_fcn ( @unary_fcns ){
    foreach $assgn ( @assign_list ){
	&header3(" $unary_fcn ");
	foreach $indexing ( @ind_unary_list ){
	    %def = ();
	    ($def{'dest_t'},$def{'src1_t'}) = 
		($datatype_complex_abbrev,$datatype_real_abbrev);
	    $def{'qualifier'} = $unary_fcn;
	    if(&make_prototype($indexing,$assgn)){
		&make_code_unary_fcn($assgn,$unary_fcn);
	    }
	}
    }
}
}
#---------------------------------------------------------------------
&header2("Elementary unary functions complex to real");
#---------------------------------------------------------------------

require("make_code_unary.pl");

if(!$quadprecision){

@assign_list = ( $eqop_eq );
@unary_fcns = ( 'norm', 'arg' );

foreach $unary_fcn ( @unary_fcns ){
    foreach $assgn ( @assign_list ){
	&header3(" $unary_fcn ");
	foreach $indexing ( @ind_unary_list ){
	    %def = ();
	    ($def{'dest_t'},$def{'src1_t'}) = 
		($datatype_real_abbrev,$datatype_complex_abbrev);
	    $def{'qualifier'} = $unary_fcn;
	    if(&make_prototype($indexing,$assgn)){
		&make_code_unary_fcn($assgn,$unary_fcn);
	    }
	}
    }
}
}
#---------------------------------------------------------------------
&header2("Elementary unary functions complex to complex");
#---------------------------------------------------------------------

require("make_code_unary.pl");

if(!$quadprecision){

@assign_list = ( $eqop_eq );
@data_list   = ( $datatype_complex_abbrev );
@unary_fcns = ( 'cexp', 'csqrt', 'clog' );

foreach $unary_fcn ( @unary_fcns ){
    foreach $assgn ( @assign_list ){
	foreach $t ( @data_list ){
	    &header3(" $unary_fcn ");
	    foreach $indexing ( @ind_unary_list ){
		%def = ();
		($def{'dest_t'},$def{'src1_t'}) = ($t,$t);
		$def{'qualifier'} = $unary_fcn;
		if(&make_prototype($indexing,$assgn)){
		    &make_code_unary_fcn($assgn,$unary_fcn);
		}
	    }
	}
    }
}
}

#---------------------------------------------------------------------
&header2("Copying and incrementing");
#---------------------------------------------------------------------

require("make_code_unary.pl");

# copy random state

@assign_list = ( $eqop_eq );
@data_list   = ( $datatype_randomstate_abbrev );

foreach $assgn ( @assign_list ){
  $eqop_notation = $eqop_notation{$assgn};

  foreach $t ( @data_list ){
    &header3(" r $eqop_notation a ($datatype_generic_name{$t}) ");
    foreach $indexing ( @ind_unary_list ){
      %def = ();
      ($def{'dest_t'},$def{'src1_t'}) = ($t,$t);
      if(&make_prototype($indexing,$assgn)){
	&make_code_unary($assgn,"identity");
      }

    }
  }
}

# rest

@assign_list = @eqop_all;
@data_list   = @datatype_arithmetic_abbrev;

foreach $assgn ( @assign_list ){
  $eqop_notation = $eqop_notation{$assgn};

  foreach $t ( @data_list ){
    &header3(" r $eqop_notation a ($datatype_generic_name{$t}) ");
    foreach $indexing ( @ind_unary_list ){
      %def = ();
      ($def{'dest_t'},$def{'src1_t'}) = ($t,$t);
      if(&make_prototype($indexing,$assgn)){
	&make_code_unary($assgn,"identity");
      }

    }
  }
}

#---------------------------------------------------------------------
&header2("Hermitian conjugate");
#---------------------------------------------------------------------

require("make_code_unary.pl");

if(!$quadprecision){

  @assign_list = @eqop_all;
  @data_list   = @datatype_adjoint_abbrev;

  foreach $assgn ( @assign_list ){
    $eqop_notation = $eqop_notation{$assgn};

    foreach $t ( @data_list ){
      &header3(" r = hconj(a) ($datatype_generic_name{$t}) ");
      foreach $indexing ( @ind_unary_list ){
	%def = ();
	($def{'dest_t'},$def{'src1_t'}) = ($t,$t);
	$def{'src1_adj'} = $suffix_adjoint;
	if(&make_prototype($indexing,$assgn)){
	  &make_code_unary($assgn,"adjoint");
	}
      }
    }
  }
}

#---------------------------------------------------------------------
&header2("Transpose");
#---------------------------------------------------------------------

require("make_code_unary.pl");

if(!$quadprecision){

  @assign_list = @eqop_all;
  @data_list   = @datatype_transpose_abbrev;
  $qualifier = "transpose";

  foreach $assgn ( @assign_list ){
    $eqop_notation = $eqop_notation{$assgn};
    
    foreach $t ( @data_list ){
      &header3(" r $eqop_notation{$assgn} transpose(a) ($datatype_generic_name{$t}) ");
      foreach $indexing ( @ind_unary_list ){
	%def = ();
	($def{'dest_t'},$def{'src1_t'}) = ($t,$t);
	$def{'qualifier'} = $qualifier;
	$def{'src1_trans'} = "t";
	if(&make_prototype($indexing,$assgn)){
	  &make_code_unary($assgn,"transpose");
	}
      }
    }
  }
}

#---------------------------------------------------------------------
&header2("Complex conjugate");
#---------------------------------------------------------------------

require("make_code_unary.pl");

if(!$quadprecision){

  @assign_list = @eqop_all;
  @data_list   = @datatype_mult_complex_abbrev;
  $qualifier = "conj";

  foreach $assgn ( @assign_list ){
    $eqop_notation = $eqop_notation{$assgn};

    foreach $t ( @data_list ){
      next if($t eq $datatype_complex_abbrev); # same as adjoint
      $srce_t = $t;
      $dest_t = $t;
      &header3(" r $eqop_notation{$assgn} complconj(a) ($datatype_generic_name{$t}) ");
      foreach $indexing ( @ind_unary_list ){
	%def = ();
	($def{'dest_t'},$def{'src1_t'}) = ($srce_t,$dest_t);
	$def{'qualifier'} = $qualifier;
	$def{'src1_conj'} = "a";
	if(&make_prototype($indexing,$assgn)){
	  &make_code_unary($assgn,"complconj");
	}
      }
    }
  }
}

#---------------------------------------------------------------------
&header2("Local squared norm");
#---------------------------------------------------------------------

require("make_code_binary.pl");

if(!$quadprecision){
  @assign_list = @eqop_all;
  @data_list   = (@datatype_mult_complex_abbrev);
  $dest_t = $datatype_real_abbrev;

  foreach $assgn ( @assign_list ){
    $eqop_notation = $eqop_notation{$assgn};

    foreach $t ( @data_list ){
      $src1_t = $t;

      &header3(" $datatype_generic_name{$t} (r = norm2 a)");
      foreach $indexing ( @ind_unary_list ){
	%def = ();
	($def{'dest_t'},$def{'src1_t'}) = ($dest_t,$src1_t);
	$def{'qualifier'} = "norm2";
	if(&make_prototype($indexing,$assgn)){
	  %src2_def = %src1_def;
	  &make_code_binary_dot($assgn,"R");
	}
      }
    }
  }
}

#=====================================================================
&header1("Type conversion and component extraction");
#=====================================================================

#---------------------------------------------------------------------
&header2("Convert float to double");
#---------------------------------------------------------------------

require("make_code_unary.pl");

if(!$quadprecision){
@assign_list = ( $eqop_eq );
@data_list   = @datatype_floatpt_abbrev;

foreach $assgn ( @assign_list ){
    $eqop_notation = $eqop_notation{$assgn};

    foreach $t ( @data_list ){
	foreach $indexing ( @ind_unary_list ){
	    %def = ();
	    ($def{'dest_t'},$def{'src1_t'}) = ($t,$t);
	    $def{'precision'} = $precision_double_abbrev.$precision_float_abbrev;

	    $def{'dest_type'} = &datatype_specific($t,$precision_double_abbrev);
	    $def{'src1_type'} = &datatype_specific($t,$precision_float_abbrev);
	    
	    if(&make_prototype($indexing,$assgn)){
		&make_code_unary($assgn,"identity");
	    }
	}
    }
}
}

#---------------------------------------------------------------------
&header2("Convert double to float");
#---------------------------------------------------------------------

require("make_code_unary.pl");

if(!$quadprecision){

@assign_list = ( $eqop_eq );
@data_list   = @datatype_floatpt_abbrev;

foreach $assgn ( @assign_list ){
    $eqop_notation = $eqop_notation{$assgn};

    foreach $t ( @data_list ){
	foreach $indexing ( @ind_unary_list ){
	    %def = ();
	    $def{'precision'} = $precision_float_abbrev.$precision_double_abbrev;
	    ($def{'dest_t'},$def{'src1_t'}) = ($t,$t);
	
	    $def{'dest_type'} = &datatype_specific($t,$precision_float_abbrev);
	    $def{'src1_type'} = &datatype_specific($t,$precision_double_abbrev);
	    if(&make_prototype($indexing,$assgn)){
		&make_code_unary($assgn,"identity");
	    }
	}
	
    }
}

}

#---------------------------------------------------------------------
&header2("Convert long double to double");
#---------------------------------------------------------------------

require("make_code_unary.pl");

if(!$quadprecision){

@assign_list = ( $eqop_eq );
@data_list   = @datatype_floatpt_abbrev;

foreach $assgn ( @assign_list ){
    $eqop_notation = $eqop_notation{$assgn};

    foreach $t ( @data_list ){
	foreach $indexing ( @ind_unary_list ){
	    %def = ();
	    $def{'precision'} = $precision_double_abbrev.$precision_longdouble_abbrev;
	    ($def{'dest_t'},$def{'src1_t'}) = ($t,$t);
	
	    $def{'dest_type'} = &datatype_specific($t,$precision_double_abbrev);
	    $def{'src1_type'} = &datatype_specific($t,$precision_longdouble_abbrev);
	    if(&make_prototype($indexing,$assgn)){
		&make_code_unary($assgn,"identity");
	    }
	}
	
    }
}
}

#---------------------------------------------------------------------
&header2("Convert real to complex (zero imaginary part)");
#---------------------------------------------------------------------

require("make_code_real_complex.pl");

if(!$quadprecision){

$assgn = $eqop_eq;

foreach $indexing ( @ind_unary_list ){
    %def = ();
    ($def{'dest_t'},$def{'src1_t'}) = 
	($datatype_complex_abbrev,$datatype_real_abbrev);

    if(&make_prototype($indexing,$assgn)){
	&make_code_real2complex($assgn);
    }
}
}

#---------------------------------------------------------------------
&header2("Convert real and imaginary to complex");
#---------------------------------------------------------------------

require("make_code_real_complex.pl");

if(!$quadprecision){

$assgn = $eqop_eq;

foreach $indexing ( @ind_binary_list ){
    %def = ();
    ($def{'dest_t'},$def{'src1_t'},$def{'src2_t'}) = 
	($datatype_complex_abbrev,$datatype_real_abbrev,$datatype_real_abbrev);
    $def{'op'} = "plus_i";

    if(&make_prototype($indexing,$assgn)){
	&make_code_real2complex($assgn);
    }
}
}

#---------------------------------------------------------------------
&header2("Real part of complex");
#---------------------------------------------------------------------

require("make_code_real_complex.pl");

if(!$quadprecision){

$assgn = $eqop_eq;

foreach $indexing ( @ind_unary_list ){
    %def = ();
    ($def{'dest_t'},$def{'src1_t'}) = 
	($datatype_real_abbrev,$datatype_complex_abbrev);
    $def{'qualifier'} = "re";

    if(&make_prototype($indexing,$assgn)){
	&make_code_imre_part($assgn,"R");
    }
}
}
#---------------------------------------------------------------------
&header2("Imaginary part of complex");
#---------------------------------------------------------------------

require("make_code_real_complex.pl");

if(!$quadprecision){

$assgn = $eqop_eq;

foreach $indexing ( @ind_unary_list ){
    %def = ();
    ($def{'dest_t'},$def{'src1_t'}) = 
	($datatype_real_abbrev,$datatype_complex_abbrev);
    $def{'qualifier'} = "im";

    if(&make_prototype($indexing,$assgn)){
	&make_code_imre_part($assgn,"I");
    }
}
}

#---------------------------------------------------------------------
&header2("Integer to real");
#---------------------------------------------------------------------

require("make_code_unary.pl");

if(!$quadprecision){

$assgn = $eqop_eq;

foreach $indexing ( @ind_unary_list ){
    %def = ();
    ($def{'dest_t'},$def{'src1_t'}) = 
	($datatype_real_abbrev,$datatype_integer_abbrev);

    if(&make_prototype($indexing,$assgn)){
	&make_code_unary($assgn,"identity");
    }
}
}
#---------------------------------------------------------------------
&header2("Real to integer");
#---------------------------------------------------------------------

require("make_code_unary.pl");

if(!$quadprecision){

$assgn = $eqop_eq;

# Truncation

foreach $indexing ( @ind_unary_list ){
    %def = ();
    ($def{'dest_t'},$def{'src1_t'}) = 
	($datatype_integer_abbrev,$datatype_real_abbrev);
    $def{'qualifier'} = "trunc";

    if(&make_prototype($indexing,$assgn)){
	&make_code_unary($assgn,"identity");
    }
}

# Rounding

foreach $indexing ( @ind_unary_list ){
    %def = ();
    ($def{'dest_t'},$def{'src1_t'}) = 
	($datatype_integer_abbrev,$datatype_real_abbrev);
    $def{'qualifier'} = "round";

    # The round function is new with C 99, so may need to be supplied
    if(&make_prototype($indexing,$assgn)){
	&make_code_unary_fcn($assgn,"round");
    }
}
}

#---------------------------------------------------------------------
&header2("Accessing and inserting array components");
#---------------------------------------------------------------------

require("make_code_unary.pl");

if(!$quadprecision){

@assign_list = ( $eqop_eq );
@data_list   = ( @datatype_array_element_abbrev );

$elem_t = $datatype_complex_abbrev;
$qualifier = "elem";

foreach $assgn ( @assign_list ){
    foreach $array_t ( @data_list ){

        # Argument list for array elements
	
	%array_def = ('t',$array_t,'trans',"");
	($ic,$is,$jc,$js) = &get_color_spin_indices(*array_def);

	$args = "";
	if($ic ne ""){ $args .= ", int $ic"; }
	if($is ne ""){ $args .= ", int $is"; }
	if($jc ne ""){ $args .= ", int $jc"; }
	if($js ne ""){ $args .= ", int $js"; }

	&header3(" Accessor for $datatype_generic_name{$array_t} ");
	
	foreach $indexing ( @ind_unary_list ){
	    %def = ();
	    ($def{'dest_t'},$def{'src1_t'}) = ($elem_t,$array_t);
	    $def{'qualifier'} = $qualifier;
	    $def{'src1_extra_arg'} = $args;

	    if(&make_prototype($indexing,$assgn)){
		&make_code_getset_component($assgn,$ic,$is,$jc,$js,"getmatelem");
	    }
	}
	
	&header3(" Insertion into  $datatype_generic_name{$array_t} ");
	foreach $indexing ( @ind_unary_list ){
	    %def = ();
	    ($def{'dest_t'},$def{'src1_t'}) = ($array_t,$elem_t);
	    $def{'qualifier'} = $qualifier;
	    $def{'src1_extra_arg'} = $args;

	    if(&make_prototype($indexing,$assgn)){
		&make_code_getset_component($assgn,$ic,$is,$jc,$js,"setmatelem");
	    }
	}
    }
}
}
#---------------------------------------------------------------------
&header2("Accessing and inserting color column vectors");
#---------------------------------------------------------------------

require("make_code_unary.pl");

if(!$quadprecision){

@assign_list = ( $eqop_eq );
@data_list   = ( @datatype_color_column_abbrev );

$elem_t = $datatype_colorvector_abbrev;
$qualifier = "colorvec";

foreach $assgn ( @assign_list ){
    foreach $array_t ( @data_list ){

        # Argument list for array elements
	
	%array_def = ('t',$array_t,'trans',"");
	($ic,$is,$jc,$js) = &get_color_spin_indices(*array_def);

	$args = "";
	# (Define, but don't insert a color row index argument)
	if($is ne ""){ $args .= ", int $is"; }
	if($jc ne ""){ $args .= ", int $jc"; }
	if($js ne ""){ $args .= ", int $js"; }

	&header3(" Extract color vector from $datatype_generic_name{$array_t} ");
	
	foreach $indexing ( @ind_unary_list ){
	    %def = ();
	    ($def{'dest_t'},$def{'src1_t'}) = ($elem_t,$array_t);
	    $def{'qualifier'} = $qualifier;
	    $def{'src1_extra_arg'} = $args;

	    if(&make_prototype($indexing,$assgn)){
		&make_code_getset_component($assgn,$ic,$is,$jc,$js,"getcolorvec");
	    }
	}
	
	&header3(" Insert color vector into  $datatype_generic_name{$array_t} ");
	foreach $indexing ( @ind_unary_list ){
	    %def = ();
	    ($def{'dest_t'},$def{'src1_t'}) = ($array_t,$elem_t);
	    $def{'qualifier'} = $qualifier;
	    $def{'src1_extra_arg'} = $args;

	    if(&make_prototype($indexing,$assgn)){
		&make_code_getset_component($assgn,$ic,$is,$jc,$js,"setcolorvec");
	    }
	}
    }
}

}
#---------------------------------------------------------------------
&header2("Accessing and inserting Dirac vectors");
#---------------------------------------------------------------------

require("make_code_unary.pl");

if(!$quadprecision){

@assign_list = ( $eqop_eq );
@data_list   = ( @datatype_dirac_column_abbrev );

$elem_t = $datatype_diracfermion_abbrev;
$qualifier = "diracvec";

foreach $assgn ( @assign_list ){
    foreach $array_t ( @data_list ){

        # Argument list for array elements
	
	%array_def = ('t',$array_t,'trans',"");
	($ic,$is,$jc,$js) = &get_color_spin_indices(*array_def);

	$args = "";
	# (Define, but don't insert a color row index argument)
	# (Define, but don't insert a spin row index argument)
	if($jc ne ""){ $args .= ", int $jc"; }
	if($js ne ""){ $args .= ", int $js"; }

	&header3(" Extract Dirac vector from $datatype_generic_name{$array_t} ");
	
	foreach $indexing ( @ind_unary_list ){
	    %def = ();
	    ($def{'dest_t'},$def{'src1_t'}) = ($elem_t,$array_t);
	    $def{'qualifier'} = $qualifier;
	    $def{'src1_extra_arg'} = $args;

	    if(&make_prototype($indexing,$assgn)){
		&make_code_getset_component($assgn,$ic,$is,$jc,$js,"getdiracvec");
	    }
	}
	
	&header3(" Insert Dirac vector into  $datatype_generic_name{$array_t} ");
	foreach $indexing ( @ind_unary_list ){
	    %def = ();
	    ($def{'dest_t'},$def{'src1_t'}) = ($array_t,$elem_t);
	    $def{'qualifier'} = $qualifier;
	    $def{'src1_extra_arg'} = $args;

	    if(&make_prototype($indexing,$assgn)){
		&make_code_getset_component($assgn,$ic,$is,$jc,$js,"setdiracvec");
	    }
	}
    }
}
}
#---------------------------------------------------------------------
&header2("Trace of color matrix");
#---------------------------------------------------------------------

require("make_code_real_complex.pl");

if(!$quadprecision){

$assgn = $eqop_eq;

# re_trace

foreach $indexing ( @ind_unary_list ){
    %def = ();
    ($def{'dest_t'},$def{'src1_t'}) = 
	($datatype_real_abbrev,$datatype_colormatrix_abbrev);
    $def{'qualifier'} = "re_trace";

    if(&make_prototype($indexing,$assgn)){
	&make_code_colormatrix_trace($assgn,"R");
    }
}

# im_trace

foreach $indexing ( @ind_unary_list ){
    %def = ();
    ($def{'dest_t'},$def{'src1_t'}) = 
	($datatype_real_abbrev,$datatype_colormatrix_abbrev);
    $def{'qualifier'} = "im_trace";

    if(&make_prototype($indexing,$assgn)){
	&make_code_colormatrix_trace($assgn,"I");
    }
}

# full trace

foreach $indexing ( @ind_unary_list ){
    %def = ();
    ($def{'dest_t'},$def{'src1_t'}) = 
	($datatype_complex_abbrev,$datatype_colormatrix_abbrev);
    $def{'qualifier'} = "trace";

    if(&make_prototype($indexing,$assgn)){
	&make_code_colormatrix_trace($assgn,"");
    }
}
}

#---------------------------------------------------------------------
&header2("Traceless antihermitian part of colormatrix matrix");
#---------------------------------------------------------------------

require("make_code_unary.pl");

if(!$quadprecision) {
  $assgn = $eqop_eq;
  foreach $indexing ( @ind_unary_list ) {
    %def = ();
    ($def{'dest_t'},$def{'src1_t'}) = 
	($datatype_colormatrix_abbrev,$datatype_colormatrix_abbrev);
    $def{'qualifier'} = "antiherm";

    if(&make_prototype($indexing,$assgn)){
      &make_code_antiherm_part($assgn);
    }
  }
}

#---------------------------------------------------------------------
&header2("Matrix determinant");
#---------------------------------------------------------------------

require("make_code_unary.pl");

if(!$quadprecision) {

  $assgn = $eqop_eq;

  foreach $indexing ( @ind_unary_list ) {
    %def = ();
    ($def{'dest_t'},$def{'src1_t'}) = 
	($datatype_complex_abbrev,$datatype_colormatrix_abbrev);
    $def{'qualifier'} = "det";

    if(&make_prototype($indexing,$assgn)) {
      &make_code_matrix_det($assgn);
    }
  }
}

#---------------------------------------------------------------------
&header2("Matrix functions");
#---------------------------------------------------------------------

require("make_code_unary.pl");

if(!$quadprecision) {

  $assgn = $eqop_eq;
  @funcs = ( "inverse", "sqrt", "invsqrt", "exp", "log" );
  foreach $func ( @funcs ) {
    foreach $indexing ( @ind_unary_list ) {
      %def = ();
      ($def{'dest_t'},$def{'src1_t'}) = 
	  ($datatype_colormatrix_abbrev,$datatype_colormatrix_abbrev);
      $def{'qualifier'} = $func;
      if(&make_prototype($indexing,$assgn)) {
	&make_code_matrix_func($assgn,$func);
      }
    }
  }
}

#---------------------------------------------------------------------
&header2("Spin trace of Dirac propagator");
#---------------------------------------------------------------------

require("make_code_real_complex.pl");

if(!$quadprecision){

$assgn = $eqop_eq;

foreach $indexing ( @ind_unary_list ){
    %def = ();
    ($def{'dest_t'},$def{'src1_t'}) = 
	($datatype_colormatrix_abbrev,$datatype_diracpropagator_abbrev);
    $def{'qualifier'} = "spintrace";

    if(&make_prototype($indexing,$assgn)){
	&make_code_spin_trace($assgn,"");
    }
}
}
#---------------------------------------------------------------------
&header2("Dirac spin projection");
#---------------------------------------------------------------------

require("make_code_unary.pl");
require("variable_names.pl");

if(!$quadprecision){

#$assgn = $eqop_eq;
@assign_list = @eqop_all;

foreach $assgn ( @assign_list ){
  foreach $indexing ( @ind_unary_list ){
    %def = ();
    ($def{'dest_t'},$def{'src1_t'}) = 
	($datatype_halffermion_abbrev,$datatype_diracfermion_abbrev);
    $def{'src1_extra_arg'} = ", int $arg_mu, int $arg_sign ";
    $def{'qualifier'} = "spproj";
    if(&make_prototype($indexing,$assgn)){
	&make_code_spproj_sprecon($assgn,$arg_mu,$arg_sign);
    }
  }
}
}
#---------------------------------------------------------------------
&header2("Dirac spin reconstruction");
#---------------------------------------------------------------------

require("make_code_unary.pl");
require("variable_names.pl");

if(!$quadprecision){

#@assign_list = ( $eqop_eq, $eqop_peq );
@assign_list = @eqop_all;

foreach $assgn ( @assign_list ){
    foreach $indexing ( @ind_unary_list ){
	%def = ();
	($def{'dest_t'},$def{'src1_t'}) = 
	    ($datatype_diracfermion_abbrev,$datatype_halffermion_abbrev);
	$def{'src1_extra_arg'} = ", int $arg_mu, int $arg_sign ";
	$def{'qualifier'} = "sprecon";
	if(&make_prototype($indexing,$assgn)){
	    &make_code_spproj_sprecon($assgn,$arg_mu,$arg_sign);
	}
    }
}
}
#---------------------------------------------------------------------
&header2("Dirac spin projection with reconstruction");
#---------------------------------------------------------------------

require("make_code_binary.pl");
require("variable_names.pl");

if(!$quadprecision){

#@assign_list = ( $eqop_eq, $eqop_peq );
@assign_list = @eqop_all;

foreach $assgn ( @assign_list ){
  foreach $indexing ( @ind_binary_list ){
    %def = ();
    $def{'dest_t'} = $datatype_diracfermion_abbrev;
    $def{'src1_t'} = $datatype_diracfermion_abbrev;
    $def{'src1_extra_arg'} = ", int $arg_mu, int $arg_sign ";
    $def{'qualifier'} = "spproj";
    if(&make_prototype($indexing,$assgn)) {
      &make_code_wilsonspin($assgn,$arg_mu,$arg_sign);
    }
  }
}
}
#---------------------------------------------------------------------
&header2("Matrix multiply and Dirac spin projection");
#---------------------------------------------------------------------

require("make_code_binary.pl");
require("variable_names.pl");

if(!$quadprecision){

#@assign_list = ( $eqop_eq, $eqop_peq );
@assign_list = @eqop_all;

foreach $assgn ( @assign_list ){
  foreach $indexing ( @ind_binary_list ){
    foreach $adj ( 0, 1 ) {
    %def = ();
    $def{'dest_t'} = $datatype_halffermion_abbrev;
    $def{'src1_t'} = $datatype_colormatrix_abbrev;
    if($adj) { $def{'src1_adj'} = $suffix_adjoint; }
    $def{'src2_t'} = $datatype_diracfermion_abbrev;
    $def{'src2_extra_arg'} = ", int $arg_mu, int $arg_sign ";
    $def{'qualifier'} = "spproj";
    $def{'op'} = "times";
    if(&make_prototype($indexing,$assgn)) {
      &make_code_spproj_sprecon_mult($assgn,$arg_mu,$arg_sign);
    }
    }
  }
}
}
#---------------------------------------------------------------------
&header2("Matrix multiply and Dirac spin reconstruction");
#---------------------------------------------------------------------

require("make_code_binary.pl");
require("variable_names.pl");

if(!$quadprecision){

#@assign_list = ( $eqop_eq, $eqop_peq );
@assign_list = @eqop_all;

foreach $assgn ( @assign_list ){
  foreach $indexing ( @ind_binary_list ){
    foreach $adj ( 0, 1 ) {
    %def = ();
    $def{'dest_t'} = $datatype_diracfermion_abbrev;
    $def{'src1_t'} = $datatype_colormatrix_abbrev;
    if($adj) { $def{'src1_adj'} = $suffix_adjoint; }
    $def{'src2_t'} = $datatype_halffermion_abbrev;
    $def{'src2_extra_arg'} = ", int $arg_mu, int $arg_sign ";
    $def{'qualifier'} = "sprecon";
    $def{'op'} = "times";
    if(&make_prototype($indexing,$assgn)) {
      &make_code_spproj_sprecon_mult($assgn,$arg_mu,$arg_sign);
    }
    }
  }
}
}
#---------------------------------------------------------------------
&header2("Matrix multiply and Dirac spin projection with reconstruction");
#---------------------------------------------------------------------

require("make_code_binary.pl");
require("variable_names.pl");

if(!$quadprecision){

#@assign_list = ( $eqop_eq, $eqop_peq );
@assign_list = @eqop_all;

foreach $assgn ( @assign_list ){
  foreach $indexing ( @ind_binary_list ){
    foreach $adj ( 0, 1 ) {
    %def = ();
    $def{'dest_t'} = $datatype_diracfermion_abbrev;
    $def{'src1_t'} = $datatype_colormatrix_abbrev;
    if($adj) { $def{'src1_adj'} = $suffix_adjoint; }
    $def{'src2_t'} = $datatype_diracfermion_abbrev;
    $def{'src2_extra_arg'} = ", int $arg_mu, int $arg_sign ";
    $def{'qualifier'} = "spproj";
    $def{'op'} = "times";
    if(&make_prototype($indexing,$assgn)) {
      &make_code_wilsonspin_mult($assgn,$arg_mu,$arg_sign);
    }
    }
  }
}
}
#=====================================================================
&header1("Binary Operations with Constants ");
#=====================================================================

#---------------------------------------------------------------------
&header2("Multiplication by real constant");
#---------------------------------------------------------------------

require("make_code_binary.pl");

if(!$quadprecision){
  @assign_list = @eqop_all;
  @data_list   = @datatype_arithmetic_abbrev;

  $real_scalar_abbrev = $datatype_scalar_abbrev{$datatype_real_abbrev};
  $integer_scalar_abbrev = $datatype_scalar_abbrev{$datatype_integer_abbrev};

  foreach $assgn ( @assign_list ){
    $eqop_notation = $eqop_notation{$assgn};

    foreach $t ( @data_list ){
      &header3(" $datatype_generic_name{$t} r $eqop_notation c a (real c) ");
      if($datatype_floatpt{$t} == 1){
	$src1_t = $real_scalar_abbrev;
      }
      else{
	$src1_t = $integer_scalar_abbrev;
      }

      foreach $indexing ( @ind_binary_src1_const_list ){
	%def = ();
	($def{'dest_t'},$def{'src1_t'},$def{'src2_t'}) = 
	    ($t,$src1_t,$t);
	$def{'op'} = "times";
	if(&make_prototype($indexing,$assgn)){
	  &make_code_binary($assgn);
	}
      }
    }
  }
}

#---------------------------------------------------------------------
&header2("Multiplication by complex constant");
#---------------------------------------------------------------------

require("make_code_binary.pl");

if(!$quadprecision) {
  @assign_list = @eqop_all;
  @data_list   = @datatype_mult_complex_abbrev;

  $complex_const_type = &datatype_specific($datatype_complex_abbrev);
  $complex_scalar_abbrev = $datatype_scalar_abbrev{$datatype_complex_abbrev};

  foreach $assgn ( @assign_list ){
    $eqop_notation = $eqop_notation{$assgn};
    &header3(" r $eqop_notation ca (complex c) ");

    $src1_t = $complex_scalar_abbrev;

    foreach $t ( @data_list ){
      $dest_t = $t;
      $src2_t = $t;
      &header3(" $datatype_generic_name{$t} r $eqop_notation c a (complex c)");

      foreach $indexing ( @ind_binary_src1_const_list ){
	%def = ();
	($def{'dest_t'},$def{'src1_t'},$def{'src2_t'}) = 
	    ($dest_t,$src1_t,$src2_t);
	$def{'op'} = "times";
	if(&make_prototype($indexing,$assgn)){
	  &make_code_binary($assgn);
	}
      }
    }
  }
}

#---------------------------------------------------------------------
&header2("Multiplication by i");
#---------------------------------------------------------------------

require("make_code_unary.pl");

if(!$quadprecision){
@assign_list = @eqop_all;
@data_list   = @datatype_mult_complex_abbrev;

foreach $assgn ( @assign_list ){
    $eqop_notation = $eqop_notation{$assgn};
    &header3(" r $eqop_notation i a ");

    foreach $t ( @data_list ){
	$dest_t = $t;
	$src1_t = $t;
	&header3(" $datatype_generic_name{$t} r $eqop_notation i a ");
	
	foreach $indexing ( @ind_unary_list ){
	    %def = ();
	    ($def{'dest_t'},$def{'src1_t'}) = ($dest_t,$src1_t);
	    $def{'qualifier'} = "i";
	    if(&make_prototype($indexing,$assgn)){
		&make_code_unary($assgn,"i");
	    }
	}
    }
}
}

#---------------------------------------------------------------------
&header2("Left multiplication by gamma matrix");
#---------------------------------------------------------------------

require("make_code_unary.pl");
require("variable_names.pl");

if(!$quadprecision){
@assign_list = ( $eqop_eq );
@data_list   = ( $datatype_diracfermion_abbrev,
		 $datatype_diracpropagator_abbrev );

foreach $assgn ( @assign_list ){
    foreach $t ( @data_list  ){
	&header3(" $datatype_generic_name{$t} (r = gamma*a)");
	
	foreach $indexing ( @ind_unary_list ){
	    %def = ();
	    ($def{'dest_t'},$def{'src1_t'}) = ($t,$t);
	    $def{'qualifier'} = "gamma".$dash."times";
	    $def{'src1_extra_arg'} = ", int $arg_mu";
	    if(&make_prototype($indexing,$assgn)){
		&make_code_mult_gamma($assgn,$arg_mu,"left");
	    }
	}
    }
}
}

#---------------------------------------------------------------------
&header2("Right multiplication by gamma matrix");
#---------------------------------------------------------------------

require("make_code_unary.pl");
require("variable_names.pl");

if(!$quadprecision){
@assign_list = ( $eqop_eq );
@data_list   = ( $datatype_diracpropagator_abbrev );

foreach $assgn ( @assign_list ){
    foreach $t ( @data_list  ){
	$srce_t = $t;
	$dest_t = $t;
	&header3(" $datatype_generic_name{$t} (r = a*gamma)");
	
	foreach $indexing ( @ind_unary_list ){
	    %def = ();
	    ($def{'dest_t'},$def{'src1_t'}) = ($srce_t,$dest_t);
	    $def{'src1_sfx'} = $dash."times".$dash."gamma";
	    $def{'src1_extra_arg'} = ", int $arg_mu";
	    if(&make_prototype($indexing,$assgn)){
		&make_code_mult_gamma($assgn,$arg_mu,"right");
	    }
	}
    }
}
}

#---------------------------------------------------------------------
&header1("Binary Operations with Fields ");
#---------------------------------------------------------------------

#---------------------------------------------------------------------
&header2("Addition and Subtraction");
#---------------------------------------------------------------------

require("make_code_binary.pl");

@assign_list = ( $eqop_eq );
@data_list   = @datatype_arithmetic_abbrev;

if(!$quadprecision){
  foreach $assgn ( @assign_list ){
    foreach $t ( @data_list ){

      &header3(" $datatype_generic_name{$t} (r = a + b) ");
      foreach $indexing ( @ind_binary_list ){
	%def = ();
	($def{'dest_t'},$def{'src1_t'},$def{'src2_t'}) = ($t,$t,$t);
	$def{'op'} = "plus";
	if(&make_prototype($indexing,$assgn)){
	  &make_code_binary($assgn);
	}
      }

      &header3(" $datatype_generic_name{$t} (r = a - b)");
      foreach $indexing ( @ind_binary_list ){
	%def = ();
	($def{'dest_t'},$def{'src1_t'},$def{'src2_t'}) = ($t,$t,$t);
	$def{'op'} = "minus";
	if(&make_prototype($indexing,$assgn)){
	  &make_code_binary($assgn);
	}
      }
    }
  }
}

#---------------------------------------------------------------------
&header2("Division of scalar fields");
#---------------------------------------------------------------------

require("make_code_binary.pl");

if(!$quadprecision){

@assign_list = ( $eqop_eq );
@data_list   = ( $datatype_real_abbrev, 
		 $datatype_complex_abbrev, 
		 $datatype_integer_abbrev);

foreach $assgn ( @assign_list ){
    foreach $t ( @data_list  ){
	foreach $indexing ( @ind_binary_list ){
	    %def = ();
	    ($def{'dest_t'},$def{'src1_t'},$def{'src2_t'}) = ($t,$t,$t);
	    $def{'op'} = "divide";
	    if(&make_prototype($indexing,$assgn)){
		&make_code_binary($assgn);
	    }
	}
    }
}
}

#---------------------------------------------------------------------
&header2("Multiplication by an integer field");
#---------------------------------------------------------------------

require("make_code_binary.pl");

if(!$quadprecision){
  @assign_list = @eqop_all;

  @src1_field_list = ($datatype_integer_abbrev);
  @src2_field_list = ($datatype_integer_abbrev);

  foreach $assgn ( @assign_list ){
    $eqop_notation = $eqop_notation{$assgn};

    foreach $s1 ( @src1_field_list ){
      foreach $s2 ( @src2_field_list ){
	&header3(" $datatype_generic_name{$s2} r $eqop_notation f a ($datatype_generic_name{$s1} f)");

	foreach $indexing ( @ind_binary_list ){
	  %def = ();
	  ($def{'dest_t'},$def{'src1_t'},$def{'src2_t'}) = 
	      ($s2,$s1,$s2);
	  $def{'op'} = "times";
	  if(&make_prototype($indexing,$assgn)){
	    &make_code_binary($assgn);
	  }
	}
      }
    }
  }
}

#---------------------------------------------------------------------
&header2("Multiplication by a real field");
#---------------------------------------------------------------------

require("make_code_binary.pl");

if(!$quadprecision){
  @assign_list = @eqop_all;

  @src1_field_list = ($datatype_real_abbrev);
  @src2_field_list = ($datatype_real_abbrev,
		      $datatype_complex_abbrev,
		      $datatype_colorvector_abbrev,
		      $datatype_halffermion_abbrev,
		      $datatype_diracfermion_abbrev,
		      $datatype_colormatrix_abbrev,
		      $datatype_diracpropagator_abbrev);

  foreach $assgn ( @assign_list ){
    $eqop_notation = $eqop_notation{$assgn};

    foreach $s1 ( @src1_field_list ){
      foreach $s2 ( @src2_field_list ){
	&header3(" $datatype_generic_name{$s2} r $eqop_notation f a ($datatype_generic_name{$s1} f)");

	foreach $indexing ( @ind_binary_list ){
	  %def = ();
	  ($def{'dest_t'},$def{'src1_t'},$def{'src2_t'}) = 
	      ($s2,$s1,$s2);
	  $def{'op'} = "times";
	  if(&make_prototype($indexing,$assgn)){
	    &make_code_binary($assgn);
	  }
	}
      }
    }
  }
}

#---------------------------------------------------------------------
&header2("Multiplication: uniform complex types");
#---------------------------------------------------------------------

require("make_code_binary.pl");

if(!$quadprecision){

  @assign_list = @eqop_all;
  @data_list   = ($datatype_complex_abbrev,
		  $datatype_colormatrix_abbrev,
		  $datatype_diracpropagator_abbrev);

  foreach $assgn ( @assign_list ){
    $eqop_notation = $eqop_notation{$assgn};
    foreach $t ( @data_list ){
      foreach $adj1 ( 0, 1 ) {
	foreach $adj2 ( 0, 1 ) {
	  &header3(" $datatype_generic_name{$t} (r $eqop_notation a * b)");
	  foreach $indexing ( @ind_binary_list ){
	    %def = ();
	    ($def{'dest_t'},$def{'src1_t'},$def{'src2_t'}) = ($t,$t,$t);
	    $def{'src1_adj'} = $suffix_adjoint if($adj1);
	    $def{'src2_adj'} = $suffix_adjoint if($adj2);
	    $def{'op'} = "times";
	    if(&make_prototype($indexing,$assgn)){
	      &make_code_binary($assgn);
	    }
	  }
	}
      }
    }
  }
}

#---------------------------------------------------------------------
&header2("Multiplication by a complex field");
#---------------------------------------------------------------------

require("make_code_binary.pl");

if(!$quadprecision){
  @assign_list = @eqop_all;

  @src1_field_list = ($datatype_complex_abbrev);
  @src2_field_list = ($datatype_colorvector_abbrev,
		      $datatype_halffermion_abbrev,
		      $datatype_diracfermion_abbrev,
		      $datatype_colormatrix_abbrev,
		      $datatype_diracpropagator_abbrev);

  foreach $assgn ( @assign_list ){
    $eqop_notation = $eqop_notation{$assgn};

    foreach $s1 ( @src1_field_list ){
      foreach $s2 ( @src2_field_list ){
	&header3(" $datatype_generic_name{$s2} r $eqop_notation f a ($datatype_generic_name{$s1} f)");

	foreach $indexing ( @ind_binary_list ){
	  %def = ();
	  ($def{'dest_t'},$def{'src1_t'},$def{'src2_t'}) = 
	      ($s2,$s1,$s2);
	  $def{'op'} = "times";
	  if(&make_prototype($indexing,$assgn)){
	    &make_code_binary($assgn);
	  }
	}
      }
    }
  }
}

#---------------------------------------------------------------------
&header2("Color matrix field times vector field");
#---------------------------------------------------------------------

require("make_code_binary.pl");

if(!$quadprecision){
  @assign_list = @eqop_all;

  @src1_field_list = ($datatype_colormatrix_abbrev);
  @src2_field_list = ($datatype_colorvector_abbrev,
		      $datatype_halffermion_abbrev,
		      $datatype_diracfermion_abbrev);

  foreach $assgn ( @assign_list ){
    $eqop_notation = $eqop_notation{$assgn};

    foreach $s1 ( @src1_field_list ){
      foreach $adj ( 0, 1 ) {
	foreach $s2 ( @src2_field_list ){
	  &header3(" $datatype_generic_name{$s2} r $eqop_notation (adj) f a ($datatype_generic_name{$s1} f)");
	  foreach $indexing ( @ind_binary_list ){
	    %def = ();
	    ($def{'dest_t'},$def{'src1_t'},$def{'src2_t'}) = 
		($s2,$s1,$s2);
	    $def{'src1_adj'} = $suffix_adjoint if($adj);
	    $def{'op'} = "times";
	    if(&make_prototype($indexing,$assgn)){
	      &make_code_binary($assgn);
	    }
	  }
	}
      }
    }
  }
}

#---------------------------------------------------------------------
&header2("Multiplication of color matrix field and propagator field");
#---------------------------------------------------------------------

require("make_code_binary.pl");

if(!$quadprecision){
  @assign_list = @eqop_all;
  @data_list = ($datatype_colormatrix_abbrev,
		$datatype_diracpropagator_abbrev);

  foreach $s1 ( @data_list ) {
    foreach $s2 ( @data_list ) {
      next if($s1 eq $s2);
      foreach $assgn ( @assign_list ){
	$eqop_notation = $eqop_notation{$assgn};
	foreach $adj1 ( 0, 1 ) {
	  foreach $adj2 ( 0, 1 ) {
	    &header3(" DiracPropagator r $eqop_notation f a (ColorMatrix f or a)");
	    foreach $indexing ( @ind_binary_list ){
	      %def = ();
	      ($def{'dest_t'},$def{'src1_t'},$def{'src2_t'}) = 
		  ($datatype_diracpropagator_abbrev,$s1,$s2);
	      $def{'src1_adj'} = $suffix_adjoint if($adj1);
	      $def{'src2_adj'} = $suffix_adjoint if($adj2);
	      $def{'op'} = "times";
	      if(&make_prototype($indexing,$assgn)){
		&make_code_binary($assgn);
	      }
	    }
	  }
	}
      }
    }
  }
}

#---------------------------------------------------------------------
&header2("Color matrix from outer product");
#---------------------------------------------------------------------

require("make_code_binary.pl");

if(!$quadprecision){
@assign_list = @eqop_all;

foreach $assgn ( @assign_list ){
    $eqop_notation = $eqop_notation{$assgn};
    
    &header3(" $datatype_generic_name{$t} (r $eqop_notation a * b)");
    
    foreach $indexing ( @ind_binary_list ){
	%def = ();
	$def{'dest_t'} = $datatype_colormatrix_abbrev;
	$def{'src1_t'} = $datatype_colorvector_abbrev;
	$def{'src2_t'} = $datatype_colorvector_abbrev;
	$def{'src2_adj'} = $suffix_adjoint;
	$def{'op'} = "times";
	if(&make_prototype($indexing,$assgn)){
	    &make_code_binary($assgn);
	}
    }
}
}

#---------------------------------------------------------------------
&header2("Local inner product");
#---------------------------------------------------------------------

require("make_code_binary.pl");

if(!$quadprecision){
@assign_list = @eqop_all;
@data_list   = ($datatype_complex_abbrev,@datatype_array_element_abbrev);

# Full inner product

foreach $assgn ( @assign_list ){
    foreach $t ( @data_list ){

	# Destination type is real or complex.  Integer dot maps to real.
	if($datatype_rc{$t} eq "c"){$dest_t = $datatype_complex_abbrev;}
	else                       {$dest_t = $datatype_real_abbrev;}
	&header3(" $datatype_generic_name{$t} (c = trace adj(a) dot b)");
	foreach $indexing ( @ind_binary_list ){
	    %def = ();
	    ($def{'dest_t'},$def{'src1_t'},$def{'src2_t'}) = ($dest_t,$t,$t);
	    $def{'op'} = "dot";
	    if(&make_prototype($indexing,$assgn)){
		&make_code_binary_dot($assgn,"");
	    }
	}
    }
}

# Real part of inner product

foreach $assgn ( @assign_list ){
    foreach $t ( @data_list ){
	
	# Destination type is real.  If result is already real, skip it.
	if($datatype_rc{$t} eq "c"){$dest_t = $datatype_real_abbrev;}
	else                       {next;}
	&header3(" $datatype_generic_name{$t} (c = Re trace adj(a) dot b)");
	foreach $indexing ( @ind_binary_list ){
	    %def = ();
	    ($def{'dest_t'},$def{'src1_t'},$def{'src2_t'}) = ($dest_t,$t,$t);
	    $def{'qualifier'} = "re";
	    $def{'op'} = "dot";
	    if(&make_prototype($indexing,$assgn)){
		&make_code_binary_dot($assgn,"R");
	    }
	}
    }
}
}


#=====================================================================
&header1("Ternary Operations");
#=====================================================================

#---------------------------------------------------------------------
&header2("Addition and Subtraction with Real Scalar Multiplication");
#---------------------------------------------------------------------

require("make_code_ternary.pl");

if(!$quadprecision){
@assign_list = ( $eqop_eq );
@data_list   = @datatype_arithmetic_abbrev;

$real_scalar_abbrev = $datatype_scalar_abbrev{$datatype_real_abbrev};
$integer_scalar_abbrev = $datatype_scalar_abbrev{$datatype_integer_abbrev};

foreach $assgn ( @assign_list ){
    $eqop_notation = $eqop_notation{$assgn};
    foreach $t ( @data_list ){
	if($datatype_floatpt{$t} == 1){
	    $src1_t = $real_scalar_abbrev;
	}
	else{
	    $src1_t = $integer_scalar_abbrev;
	}


	&header3(" $datatype_generic_name{$t} r $eqop_notation (a*b + c) (real a) ");
	foreach $indexing ( @ind_ternary_src1_const_list ){
	    %def = ();
	    ($def{'dest_t'},$def{'src1_t'},$def{'src2_t'},$def{'src3_t'}) = 
		($t,$src1_t,$t,$t);
	    $def{'op'} = "times";
	    $def{'op2'} = "plus";
	    if(&make_prototype($indexing,$assgn)){
		&make_code_ternary($assgn);
	    }
	}
	
	&header3(" $datatype_generic_name{$t} r $eqop_notation (a*b - c) (real a) ");
	
	foreach $indexing ( @ind_ternary_src1_const_list ){
	    %def = ();
	    ($def{'dest_t'},$def{'src1_t'},$def{'src2_t'},$def{'src3_t'}) = 
		($t,$src1_t,$t,$t);
	    $def{'op'} = "times";
	    $def{'op2'} = "minus";
	    if(&make_prototype($indexing,$assgn)){
		&make_code_ternary($assgn);
	    }
	}
    }
}
}

#---------------------------------------------------------------------
&header2("Addition and Subtraction with Complex Scalar Multiplication");
#---------------------------------------------------------------------

require("make_code_ternary.pl");

if(!$quadprecision){
@assign_list = ( $eqop_eq );
@data_list   = @datatype_mult_complex_abbrev;

$complex_scalar_abbrev = $datatype_scalar_abbrev{$datatype_complex_abbrev};

foreach $assgn ( @assign_list ){
    $eqop_notation = $eqop_notation{$assgn};
    foreach $t ( @data_list ){
	$src1_t = $complex_scalar_abbrev;
	&header3(" $datatype_generic_name{$t} r $eqop_notation (a*b + c) (complex a) ");
	foreach $indexing ( @ind_ternary_src1_const_list ){
	    %def = ();
	    ($def{'dest_t'},$def{'src1_t'},$def{'src2_t'},$def{'src3_t'}) = 
		($t,$src1_t,$t,$t);
	    $def{'op'} = "times";
	    $def{'op2'} = "plus";
	    if(&make_prototype($indexing,$assgn)){
		&make_code_ternary($assgn);
	    }
	}
	
	&header3(" $datatype_generic_name{$t} r $eqop_notation (a*b - c) (complex a) ");
	
	foreach $indexing ( @ind_ternary_src1_const_list ){
	    %def = ();
	    ($def{'dest_t'},$def{'src1_t'},$def{'src2_t'},$def{'src3_t'}) = 
		($t,$src1_t,$t,$t);
	    $def{'op'} = "times";
	    $def{'op2'} = "minus";
	    if(&make_prototype($indexing,$assgn)){
		&make_code_ternary($assgn);
	    }
	}
    }
}
}
#=====================================================================
&header1("Boolean and Bit Operations");
#=====================================================================

#---------------------------------------------------------------------
&header2("Elementary binary operations on integers");
#---------------------------------------------------------------------

require("make_code_binary.pl");

if(!$quadprecision){
$assgn = $eqop_eq;

$t = $datatype_integer_abbrev;
$dest_t = $t;
$src1_t = $t;
$src2_t = $t;

foreach $op ( "lshift", "rshift" ){
    &header3(" $datatype_generic_name{$t} (r = a $op b)");

    foreach $indexing ( @ind_binary_list ){
	%def = ();
	($def{'dest_t'},$def{'src1_t'},$def{'src2_t'}) = 
	    ($dest_t,$src1_t,$src2_t);
	$def{'op'} = $op;
	if(&make_prototype($indexing,$assgn)){
	    &make_code_binary_elementary($assgn);
	}
    }
}

foreach $op ( "mod", "max", "min" ){
    &header3(" $datatype_generic_name{$t} (r = a $op b)");
    foreach $indexing ( @ind_binary_list ){
	%def = ();
	($def{'dest_t'},$def{'src1_t'},$def{'src2_t'}) = ($t,$t,$t);
	$def{'op'} = $op;
	if(&make_prototype($indexing,$assgn)){
	    &make_code_binary_elementary($assgn);
	}
    }
}
}
#---------------------------------------------------------------------
&header2("Comparisons of integers and reals");
#---------------------------------------------------------------------

require("make_code_binary.pl");

if(!$quadprecision){
$assgn = $eqop_eq;

$t = $datatype_integer_abbrev;
$dest_t = $datatype_integer_abbrev;
$src1_t = $t;
$src2_t = $t;

foreach $op ( "eq", "ne", "gt", "lt", "ge", "le" ){
    &header3(" $datatype_generic_name{$t} (r = a $op b)");
    foreach $indexing ( @ind_binary_list ){
	%def = ();
	($def{'dest_t'},$def{'src1_t'},$def{'src2_t'}) = ($dest_t,$t,$t);
	$def{'op'} = $op;
	if(&make_prototype($indexing,$assgn)){
	    &make_code_binary_elementary($assgn);
	}
    }
}

$t = $datatype_real_abbrev;
$dest_t = $datatype_integer_abbrev;
$src1_t = $t;
$src2_t = $t;

foreach $op ( "eq", "ne", "gt", "lt", "ge", "le" ){
    &header3(" $datatype_generic_name{$t} (r = a $op b)");
    foreach $indexing ( @ind_binary_list ){
	%def = ();
	($def{'dest_t'},$def{'src1_t'},$def{'src2_t'}) = ($dest_t,$t,$t);
	$def{'op'} = $op;
	if(&make_prototype($indexing,$assgn)){
	    &make_code_binary_elementary($assgn);
	}
    }
}
}
#---------------------------------------------------------------------
&header2("Boolean Operations");
#---------------------------------------------------------------------

require("make_code_binary.pl");

if(!$quadprecision){
$assgn = $eqop_eq;

$t = $datatype_integer_abbrev;
$dest_t = $t;
$src1_t = $t;
$src2_t = $t;

foreach $op ( "or", "and", "xor" ){
    &header3(" $datatype_generic_name{$t} (r = a $op b)");
    foreach $indexing ( @ind_binary_list ){
	%def = ();
	($def{'dest_t'},$def{'src1_t'},$def{'src2_t'}) = 
	    ($dest_t,$src1_t,$src2_t);
	$def{'op'} = $op;
	if(&make_prototype($indexing,$assgn)){
	    &make_code_binary_elementary($assgn);
	}
    }
}

require("make_code_unary.pl");

foreach $indexing ( @ind_unary_list ){
	%def = ();
	($def{'dest_t'},$def{'src1_t'}) = ($t,$t);
	$def{'qualifier'} = "not";;
	if(&make_prototype($indexing,$assgn)){
	    &make_code_boolean_not($assgn);
	}
}
}

#---------------------------------------------------------------------
&header2("Copymask");
#---------------------------------------------------------------------

require("make_code_binary.pl");

if(!$quadprecision){
  @assign_list = ( $eqop_eq );
  @data_list   = ( @datatype_abbrev );

  $src2_t = $datatype_integer_abbrev;

  foreach $assgn ( @assign_list ){
    foreach $t ( @data_list ){
      &header3(" $datatype_generic_name{$t} (r = a mask b)");
      foreach $indexing ( @ind_binary_list ){
	%def = ();
	($def{'dest_t'},$def{'src1_t'},$def{'src2_t'}) = ($t,$t,$src2_t);
	$def{'op'} = "mask";
	if(&make_prototype($indexing,$assgn)){
	  &make_code_binary_elementary($assgn);
	}
      }
    }
  }
}

#=====================================================================
&header1("Reductions              ");
#=====================================================================

#---------------------------------------------------------------------
&header2("Global squared norm uniform precision");
#---------------------------------------------------------------------

require("make_code_unary.pl");

if(!$quadprecision){
@assign_list = ($eqop_eq);
@data_list   = @datatype_arithmetic_abbrev;

$real_scalar_abbrev = $datatype_scalar_abbrev{$datatype_real_abbrev};

foreach $assgn ( @assign_list ){
    $eqop_notation = $eqop_notation{$assgn};

    foreach $t ( @data_list ){
	$src1_t = $t;
	$dest_t = $real_scalar_abbrev;
	
	&header3(" $datatype_generic_name{$t} (r = sum norm2 a)");
	foreach $indexing ( @ind_unary_reduction_list ){
	    %def = ();
	    ($def{'dest_t'},$def{'src1_t'}) = ($dest_t,$t);
	    $def{'qualifier'} = "norm2";
	    if(&make_prototype($indexing,$assgn)){
		&make_code_norm2_global_sum($assgn);
	    }
	}
    }
}
}
#---------------------------------------------------------------------
&header2("Global squared norm float to double precision");
#---------------------------------------------------------------------

require("make_code_unary.pl");

if(!$quadprecision){
@assign_list = ($eqop_eq);
@data_list   = @datatype_arithmetic_abbrev;

$real_scalar_abbrev = $datatype_scalar_abbrev{$datatype_real_abbrev};

foreach $assgn ( @assign_list ){
    $eqop_notation = $eqop_notation{$assgn};

    foreach $t ( @data_list ){
	# No integers
	if($datatype_floatpt{$t} == 0){next;}

	$src1_t = $t;
	$dest_t = $real_scalar_abbrev;
	
	&header3(" $datatype_generic_name{$t} (r = sum norm2 a)");
	foreach $indexing ( @ind_unary_reduction_list ){
	    %def = ();
	    $def{'precision'} = $precision_double_abbrev.$precision_float_abbrev;
	    $def{'dest_type'} = &datatype_specific($dest_t,$precision_double_abbrev);
	    $def{'src1_type'} = &datatype_specific($src1_t,$precision_float_abbrev);

	    ($def{'dest_t'},$def{'src1_t'}) = ($dest_t,$src1_t);
	    $def{'qualifier'} = "norm2";
	    if(&make_prototype($indexing,$assgn)){
		&make_code_norm2_global_sum($assgn);
	    }
	}
    }
}
}
#---------------------------------------------------------------------
&header2("Global squared norm double to long double precision");
#---------------------------------------------------------------------

require("make_code_unary.pl");

if(!$quadprecision){
@assign_list = ($eqop_eq);
@data_list   = @datatype_arithmetic_abbrev;

$real_scalar_abbrev = $datatype_scalar_abbrev{$datatype_real_abbrev};

foreach $assgn ( @assign_list ){
    $eqop_notation = $eqop_notation{$assgn};

    foreach $t ( @data_list ){
	# No integers
	if($datatype_floatpt{$t} == 0){next;}

	$src1_t = $t;
	$dest_t = $real_scalar_abbrev;
	
	&header3(" $datatype_generic_name{$t} (r = sum norm2 a)");
	foreach $indexing ( @ind_unary_reduction_list ){
	    %def = ();
	    $def{'precision'} = $precision_longdouble_abbrev.$precision_double_abbrev;
	    $def{'dest_type'} = &datatype_specific($dest_t,$precision_longdouble_abbrev);
	    $def{'src1_type'} = &datatype_specific($src1_t,$precision_double_abbrev);

	    ($def{'dest_t'},$def{'src1_t'}) = ($dest_t,$src1_t);
	    $def{'qualifier'} = "norm2";
	    if(&make_prototype($indexing,$assgn)){
		&make_code_norm2_global_sum($assgn);
	    }
	}
    }
}
}
#---------------------------------------------------------------------
&header2("Global inner product uniform precision");
#---------------------------------------------------------------------



require("make_code_binary.pl");

if(!$quadprecision){
@assign_list = ($eqop_eq);
@data_list   = @datatype_arithmetic_abbrev;
$complex_scalar_type = &datatype_specific($datatype_complex_abbrev);
$complex_scalar_abbrev = $datatype_scalar_abbrev{$datatype_complex_abbrev};

# Full inner product

foreach $assgn ( @assign_list ){
    foreach $t ( @data_list ){
	
	# Destination type is real or complex.  Integer dot maps to real.
	if($datatype_rc{$t} eq "c"){$dest_t = $complex_scalar_abbrev;}
	else                       {$dest_t = $real_scalar_abbrev;}
	&header3(" $datatype_generic_name{$t} (c = trace adj(a) dot b)");
	foreach $indexing ( @ind_binary_reduction_list ){
	    %def = ();
	    ($def{'dest_t'},$def{'src1_t'},$def{'src2_t'}) = ($dest_t,$t,$t);
	    $def{'op'} = "dot";
	    if(&make_prototype($indexing,$assgn)){
		&make_code_binary_dot_global($assgn,"");
	    }
	}
    }
}

# Real part of inner product

$real_scalar_abbrev = $datatype_scalar_abbrev{$datatype_real_abbrev};

foreach $assgn ( @assign_list ){
    foreach $t ( @data_list ){
	
	# Destination type is real.  If result is already real, skip it.
	if($datatype_rc{$t} eq "c"){$dest_t = $real_scalar_abbrev;}
	else                       {next;}
	&header3(" $datatype_generic_name{$t} (c = Re trace adj(a) dot b)");
	foreach $indexing ( @ind_binary_reduction_list ){
	    %def = ();
	    ($def{'dest_t'},$def{'src1_t'},$def{'src2_t'}) = ($dest_t,$t,$t);
	    $def{'qualifier'} = "re";
	    $def{'op'} = "dot";
	    if(&make_prototype($indexing,$assgn)){
		&make_code_binary_dot_global($assgn,"R");
	    }
	}
    }
}
}
#---------------------------------------------------------------------
&header2("Global inner product float to double");
#---------------------------------------------------------------------

require("make_code_binary.pl");

if(!$quadprecision){
@assign_list = ($eqop_eq);
@data_list   = @datatype_arithmetic_abbrev;
$complex_scalar_type = &datatype_specific($datatype_complex_abbrev);
$complex_scalar_abbrev = $datatype_scalar_abbrev{$datatype_complex_abbrev};

# Full inner product

foreach $assgn ( @assign_list ){
    foreach $t ( @data_list ){
	
	# Destination type is real or complex.  No integers.
	if($datatype_floatpt{$t} == 0){next;}
	if($datatype_rc{$t} eq "c"){$dest_t = $complex_scalar_abbrev;}
	else                       {$dest_t = $real_scalar_abbrev;}
	&header3(" $datatype_generic_name{$t} (c = trace adj(a) dot b)");
	foreach $indexing ( @ind_binary_reduction_list ){
	    %def = ();
	    $def{'precision'} = $precision_double_abbrev.$precision_float_abbrev;
	    $def{'dest_type'} = &datatype_specific($dest_t,$precision_double_abbrev);
	    $def{'src1_type'} = &datatype_specific($t,$precision_float_abbrev);
	    ($def{'dest_t'},$def{'src1_t'},$def{'src2_t'}) = ($dest_t,$t,$t);
	    $def{'op'} = "dot";
	    if(&make_prototype($indexing,$assgn)){
		&make_code_binary_dot_global($assgn,"");
	    }
	}
    }
}

# Real part of inner product

foreach $assgn ( @assign_list ){
    foreach $t ( @data_list ){
	
	# Destination type is real.  If result is already real, skip it.
	# No integers.
	if($datatype_floatpt{$t} == 0){next;}
	if($datatype_rc{$t} eq "c"){$dest_t = $real_scalar_abbrev;}
	else                       {next;}
	&header3(" $datatype_generic_name{$t} (c = Re trace adj(a) dot b)");
	foreach $indexing ( @ind_binary_reduction_list ){
	    %def = ();
	    $def{'precision'} = $precision_double_abbrev.$precision_float_abbrev;
	    $def{'dest_type'} = &datatype_specific($dest_t,$precision_double_abbrev);
	    $def{'src1_type'} = &datatype_specific($t,$precision_float_abbrev);
	    ($def{'dest_t'},$def{'src1_t'},$def{'src2_t'}) = ($dest_t,$t,$t);
	    $def{'qualifier'} = "re";
	    $def{'op'} = "dot";
	    if(&make_prototype($indexing,$assgn)){
		&make_code_binary_dot_global($assgn,"R");
	    }
	}
    }
}
}
#---------------------------------------------------------------------
&header2("Global inner product double to long double");
#---------------------------------------------------------------------

require("make_code_binary.pl");

if(!$quadprecision){
@assign_list = ($eqop_eq);
@data_list   = @datatype_arithmetic_abbrev;
$complex_scalar_type = &datatype_specific($datatype_complex_abbrev);
$complex_scalar_abbrev = $datatype_scalar_abbrev{$datatype_complex_abbrev};

# Full inner product

foreach $assgn ( @assign_list ){
    foreach $t ( @data_list ){
	
	# Destination type is real or complex. No integers.
	if($datatype_floatpt{$t} == 0){next;}
	if($datatype_rc{$t} eq "c"){$dest_t = $complex_scalar_abbrev;}
	else                       {$dest_t = $real_scalar_abbrev;}
	&header3(" $datatype_generic_name{$t} (c = trace adj(a) dot b)");
	foreach $indexing ( @ind_binary_reduction_list ){
	    %def = ();
	    $def{'precision'} = $precision_longdouble_abbrev.$precision_double_abbrev;
	    $def{'dest_type'} = &datatype_specific($dest_t,$precision_longdouble_abbrev);
	    $def{'src1_type'} = &datatype_specific($t,$precision_double_abbrev);
	    ($def{'dest_t'},$def{'src1_t'},$def{'src2_t'}) = ($dest_t,$t,$t);
	    $def{'op'} = "dot";
	    if(&make_prototype($indexing,$assgn)){
		&make_code_binary_dot_global($assgn,"");
	    }
	}
    }
}

# Real part of inner product

foreach $assgn ( @assign_list ){
    foreach $t ( @data_list ){
	
	# Destination type is real.  If result is already real, skip it.
	# No integers.
	if($datatype_floatpt{$t} == 0){next;}
	if($datatype_rc{$t} eq "c"){$dest_t = $real_scalar_abbrev;}
	else                       {next;}
	&header3(" $datatype_generic_name{$t} (c = Re trace adj(a) dot b)");
	foreach $indexing ( @ind_binary_reduction_list ){
	    %def = ();
	    $def{'precision'} = $precision_longdouble_abbrev.$precision_double_abbrev;
	    $def{'dest_type'} = &datatype_specific($dest_t,$precision_longdouble_abbrev);
	    $def{'src1_type'} = &datatype_specific($t,$precision_double_abbrev);
	    ($def{'dest_t'},$def{'src1_t'},$def{'src2_t'}) = ($dest_t,$t,$t);
	    $def{'qualifier'} = "re";
	    $def{'op'} = "dot";
	    if(&make_prototype($indexing,$assgn)){
		&make_code_binary_dot_global($assgn,"R");
	    }
	}
    }
}
}

#---------------------------------------------------------------------
&header2("Global sum uniform precision");
#---------------------------------------------------------------------

require("make_code_unary.pl");

if(!$quadprecision){

@assign_list = ($eqop_eq);
@data_list   = @datatype_arithmetic_abbrev;

$assgn = $eqop_eq;

foreach $assgn ( @assign_list ){
    foreach $t ( @data_list ){

	if($datatype_floatpt{$t} == 1){
	    $dest_t = $datatype_scalar_abbrev{$t};
	}
	# Exception - accumulate integer sums as real to prevent overflow
	else {
	    $dest_t = $datatype_scalar_abbrev{$datatype_real_abbrev};
	}

	&header3(" $datatype_generic_name{$t} (r = sum a)");
	foreach $indexing ( @ind_unary_reduction_list ){
	    %def = ();
	    ($def{'dest_t'},$def{'src1_t'}) = ($dest_t,$t);
	    $def{'qualifier'} = "sum";
	    if(&make_prototype($indexing,$assgn)){
		&make_code_norm2_global_sum($assgn);
	    }
	}
    }
}
}

#---------------------------------------------------------------------
&header2("Global sum float to double");
#---------------------------------------------------------------------

require("make_code_unary.pl");

if(!$quadprecision){

@assign_list = ($eqop_eq);
@data_list   = @datatype_arithmetic_abbrev;

$assgn = $eqop_eq;

foreach $assgn ( @assign_list ){
    foreach $t ( @data_list ){
	# No integers
	if($datatype_floatpt{$t} == 0){next;}

	$dest_t = $datatype_scalar_abbrev{$t};

	&header3(" $datatype_generic_name{$t} (r = sum a)");
	foreach $indexing ( @ind_unary_reduction_list ){
	    %def = ();
	    $def{'precision'} = $precision_double_abbrev.$precision_float_abbrev;
	    $def{'dest_type'} = &datatype_specific($dest_t,$precision_double_abbrev);
	    $def{'src1_type'} = &datatype_specific($t,$precision_float_abbrev);
	    ($def{'dest_t'},$def{'src1_t'}) = ($dest_t,$t);
	    $def{'qualifier'} = "sum";
	    if(&make_prototype($indexing,$assgn)){
		&make_code_norm2_global_sum($assgn);
	    }
	}
    }
}
}

#---------------------------------------------------------------------
&header2("Global sum double to long double");
#---------------------------------------------------------------------

require("make_code_unary.pl");

if(!$quadprecision){

@assign_list = ($eqop_eq);
@data_list   = @datatype_arithmetic_abbrev;

$assgn = $eqop_eq;

foreach $assgn ( @assign_list ){
    foreach $t ( @data_list ){
	# No integers
	if($datatype_floatpt{$t} == 0){next;}

	$dest_t = $datatype_scalar_abbrev{$t};

	&header3(" $datatype_generic_name{$t} (r = sum a)");
	foreach $indexing ( @ind_unary_reduction_list ){
	    %def = ();
	    $def{'precision'} = $precision_longdouble_abbrev.$precision_double_abbrev;
	    $def{'dest_type'} = &datatype_specific($dest_t,$precision_longdouble_abbrev);
	    $def{'src1_type'} = &datatype_specific($t,$precision_double_abbrev);
	    ($def{'dest_t'},$def{'src1_t'}) = ($dest_t,$t);
	    $def{'qualifier'} = "sum";
	    if(&make_prototype($indexing,$assgn)){
		&make_code_norm2_global_sum($assgn);
	    }
	}
    }
}
}
#=====================================================================
&header1("Fills                   ");
#=====================================================================

#---------------------------------------------------------------------
&header2("Zero fills");
#---------------------------------------------------------------------

require("make_code_unary.pl");

@assign_list = ( $eqop_eq );
@data_list   = @datatype_arithmetic_abbrev;

foreach $assgn ( @assign_list ){
    foreach $t ( @data_list ){
	
	&header3(" $datatype_generic_name{$t} (r = zero)");
	foreach $indexing ( @ind_fill_list ){
	    %def = ();
	    $def{'dest_t'} = $t;
	    $def{'qualifier'} = "zero";
	    if(&make_prototype($indexing,$assgn)){
		&make_code_unary($assgn,"zero");
	    }
	}
    }
}

#---------------------------------------------------------------------
&header2("Constant fills");
#---------------------------------------------------------------------

require("make_code_unary.pl");

if(!$quadprecision){
@assign_list = ( $eqop_eq );
@data_list   = @datatype_arithmetic_abbrev;

foreach $assgn ( @assign_list ){
    foreach $t ( @data_list ){
	
	&header3(" $datatype_generic_name{$t} (r = const)");
	foreach $indexing ( @ind_fill_list ){
	    %def = ();
	    ($def{'dest_t'},$def{'src1_t'}) = ($t,$datatype_scalar_abbrev{$t});
	    if(&make_prototype($indexing,$assgn)){
		&make_code_unary($assgn,"identity");
	    }
	}
    }
}

$assgn = $eqop_eq;
$dest_t = $datatype_colormatrix_abbrev;
$srce_t = $datatype_scalar_abbrev{$datatype_complex_abbrev};

&header3(" diag($datatype_generic_name{$dest_t}) = const");
foreach $indexing ( @ind_fill_list ){
    %def = ();
    ($def{'dest_t'},$def{'src1_t'}) = ($dest_t,$srce_t);
    if(&make_prototype($indexing,$assgn)){
	&make_code_unary($assgn,"diagfill");
    }
}
}

#---------------------------------------------------------------------
&header2("Uniform random number fills");
#---------------------------------------------------------------------

require("make_code_unary.pl");

if(!$quadprecision){
$assgn = $eqop_eq;

$t = $datatype_real_abbrev;

foreach $indexing ( @ind_unary_list ){
    %def = ();
    $def{'dest_t'} = $t;
    $def{'src1_t'} = $datatype_randomstate_abbrev;
    $def{'qualifier'} = "random";
    if(&make_prototype($indexing,$assgn)){
	&make_code_unary($assgn,"random");
    }
}
}

#---------------------------------------------------------------------
&header2("Gaussian random number fills");
#---------------------------------------------------------------------
require("make_code_unary.pl");

@assign_list = ( $eqop_eq );
@data_list   = @datatype_floatpt_abbrev;

foreach $assgn ( @assign_list ){
    foreach $t ( @data_list ){
	
	&header3(" $datatype_generic_name{$t} (r = gaussian random) ");
	foreach $indexing ( @ind_unary_list ){
	    %def = ();
	    $def{'dest_t'} = $t;
	    $def{'src1_t'} = $datatype_randomstate_abbrev;
	    $def{'qualifier'} = "gaussian";
	    if(&make_prototype($indexing,$assgn)){
		&make_code_unary($assgn,"gaussian");
	    }
	}
    }
}

#---------------------------------------------------------------------
&header2("Seeding the random number generator from an integer array");
#---------------------------------------------------------------------
require("make_code_unary.pl");

if(!$quadprecision){
@assign_list = ( $eqop_eq );
@data_list   = ( $datatype_integer_abbrev );

foreach $assgn ( @assign_list ){
    foreach $t ( @data_list ){
	&header3(" $datatype_generic_name{$t} (r = seed generator from a) ");
	foreach $indexing ( @ind_unary_list ){
	    %def = ();
	    $def{'dest_t'} = $datatype_randomstate_abbrev;
	    $def{'dest_extra_arg'} = ", int $arg_seed";
	    $def{'src1_t'} = $t;
	    $def{'qualifier'} = "seed".$dash.
		$datatype_scalar_abbrev{$datatype_integer_abbrev};
	    if(&make_prototype($indexing,$assgn)){
		&make_code_unary($assgn,"seed");
	    }
	}
    }
}
}
######################################################################

if($do_generic_defines || $do_color_generic_defines){
    &close_generic_defines_header($do_generic_defines,
				  $do_color_generic_defines);
}

&close_qla_header;
######################################################################


## copy specialized files
use File::Copy;

$codedir="$path/code-templates";

@files = (
  "C_eq_det_M.c",
  "M_eq_inverse_M.c",
  "M_eq_sqrt_M.c",
  "M_eq_invsqrt_M.c",
  "M_eq_exp_M.c",
  "M_eq_log_M.c"
    );

@targets = (
  "F2 D2 F3 D3 FN DN",
  "F2 D2 F3 D3 FN DN",
  "F2 D2 F3 D3 FN DN",
  "F2 D2 F3 D3 FN DN",
  "F2 D2 F3 D3 FN DN",
  "F2 D2 F3 D3 FN DN"
    );

for($i=0; $i<=$#files; $i++) {
  $f = $files[$i];
  $ts = $targets[$i];
#  printf("%i %s %s\n", $i, $f, $ts);
  foreach $t ( split(' ',$ts) ) {
#    printf("%i %s %s\n", $i, $f, $t);
#    printf("%s %s\n", $t, $pc);
    if($t eq $pc) {
#      printf("copyfile %s %s\n", $f, $t);
      $of = "QLA_${t}_$f";
      $fin = "$codedir/$f";
      $fout = "$c_source_path/$of";
      printf("copy %s %s\n", $fin, $fout);
      copy($fin,$fout) or die "Copy failed: $!";
    }
  }
}
