######################################################################
# SciDAC Software Project
# BUILD_QLA Version 0.9
#
# datatypes.pl
#
# Author: C. DeTar
# Date:   09/13/02
######################################################################
#
# Database of data types and their characteristics
# 
#
######################################################################
# Changes:
#
######################################################################
# Supporting files required:

######################################################################

# Spin dimension
$spins = 4;
$halfspins = 2;

# The variable color label
$colors_n = 'N';

# Color choices
@colors_supported = ( '2','3',$colors_n );

# Floating point precision choices
$precision_float_abbrev  = 'F';
$precision_double_abbrev = 'D';
$precision_longdouble_abbrev = 'Q';

######################################################################
# List of datatype abbreviations

# Type abbreviations
$datatype_integer_abbrev = 'I';
$datatype_real_abbrev = 'R';
$datatype_complex_abbrev = 'C';
$datatype_colorvector_abbrev = 'V';
$datatype_halffermion_abbrev = 'H';
$datatype_diracfermion_abbrev = 'D';
$datatype_colormatrix_abbrev = 'M';
$datatype_diracpropagator_abbrev = 'P';
$datatype_randomstate_abbrev = 'S';

@datatype_abbrev = (
    $datatype_integer_abbrev,
    $datatype_real_abbrev,
    $datatype_complex_abbrev,
    $datatype_colorvector_abbrev,
    $datatype_halffermion_abbrev,
    $datatype_diracfermion_abbrev,
    $datatype_colormatrix_abbrev,
    $datatype_diracpropagator_abbrev,
    $datatype_randomstate_abbrev
		    );

# Arithmetic datatypes
@datatype_arithmetic_abbrev = (
    $datatype_integer_abbrev,
    $datatype_real_abbrev,
    $datatype_complex_abbrev,
    $datatype_colorvector_abbrev,
    $datatype_halffermion_abbrev,
    $datatype_diracfermion_abbrev,
    $datatype_colormatrix_abbrev,
    $datatype_diracpropagator_abbrev,
		   );

# Corresponding scalar (nonindexed) datatype abbreviations
# All are lower case transliterations

%datatype_scalar_abbrev = ();
foreach $t ( @datatype_abbrev ){
    $s = $t;  $s =~ tr/[A-Z]/[a-z]/;
    $datatype_scalar_abbrev{$t} = $s;
}

# For quick identification of scalar (nonindexed) datatypes
%datatype_scalar = ();
foreach $t ( @datatype_abbrev ){
    $datatype_scalar{$t} = 0;
    $datatype_scalar{$datatype_scalar_abbrev{$t}} = 1;
}

# Generic datatypes in terms of abbreviations

%datatype_generic_name = (
  $datatype_integer_abbrev, 'QLA_Int',
  $datatype_real_abbrev, 'QLA_Real',
  $datatype_complex_abbrev, 'QLA_Complex',
  $datatype_colorvector_abbrev, 'QLA_ColorVector',
  $datatype_halffermion_abbrev, 'QLA_HalfFermion',
  $datatype_diracfermion_abbrev, 'QLA_DiracFermion',
  $datatype_colormatrix_abbrev, 'QLA_ColorMatrix',
  $datatype_diracpropagator_abbrev, 'QLA_DiracPropagator',
  $datatype_randomstate_abbrev, 'QLA_RandomState',
		      );

# Append scalar types - the names are identical
foreach $t ( keys %datatype_generic_name ){
    $s = $datatype_scalar_abbrev{$t};
    $datatype_generic_name{$s} = $datatype_generic_name{$t};
}

# Floating point datatypes 

%datatype_floatpt = (
     $datatype_integer_abbrev,0,  
     $datatype_real_abbrev,1,
     $datatype_complex_abbrev,1,
     $datatype_colorvector_abbrev,1,
     $datatype_halffermion_abbrev,1,
     $datatype_diracfermion_abbrev,1,
     $datatype_colormatrix_abbrev,1,
     $datatype_diracpropagator_abbrev,1,
     $datatype_randomstate_abbrev,0,
			   );

# Append scalar types - the values are identical
foreach $t ( keys %datatype_floatpt ){
    $s = $datatype_scalar_abbrev{$t};
    $datatype_floatpt{$s} = $datatype_floatpt{$t};
}

# Specify real or complex for datatype element
%datatype_rc = (
   $datatype_integer_abbrev,"r",
   $datatype_real_abbrev,"r",
   $datatype_complex_abbrev,"c",
   $datatype_colorvector_abbrev,"c",
   $datatype_halffermion_abbrev,"c",
   $datatype_diracfermion_abbrev,"c",
   $datatype_colormatrix_abbrev,"c",
   $datatype_diracpropagator_abbrev,"c",
   $datatype_randomstate_abbrev,"r"
			   );
# Append scalar types - the values are identical
foreach $t ( keys %datatype_rc ){
    $s = $datatype_scalar_abbrev{$t};
    $datatype_rc{$s} = $datatype_rc{$t};
}

# Dimension of row color index
%datatype_row_color_dim = (
   $datatype_integer_abbrev,0,
   $datatype_real_abbrev,0,
   $datatype_complex_abbrev,0,
   $datatype_colorvector_abbrev,$colors,
   $datatype_halffermion_abbrev,$colors,
   $datatype_diracfermion_abbrev,$colors,
   $datatype_colormatrix_abbrev,$colors,
   $datatype_diracpropagator_abbrev,$colors,
   $datatype_randomstate_abbrev,0
			   );
# Append scalar types - the values are identical
foreach $t ( keys %datatype_row_color_dim ){
    $s = $datatype_scalar_abbrev{$t};
    $datatype_row_color_dim{$s} = $datatype_row_color_dim{$t};
}

# Return constant or variable for maximum color index
sub max_row_color_dim {
    local($t) = @_;

    if($datatype_row_color_dim{$t} eq $colors){$def{'nc'};}
    else {$datatype_row_color_dim{$t}};
}

# Dimension of column color index
%datatype_col_color_dim = (
  $datatype_integer_abbrev,0,
  $datatype_real_abbrev,0,
  $datatype_complex_abbrev,0,
  $datatype_colorvector_abbrev,0,
  $datatype_halffermion_abbrev,0,
  $datatype_diracfermion_abbrev,0,
  $datatype_colormatrix_abbrev,$colors,
  $datatype_diracpropagator_abbrev,$colors,
  $datatype_randomstate_abbrev,0
    );

# Append scalar types - the values are identical
foreach $t ( keys %datatype_col_color_dim ){
    $s = $datatype_scalar_abbrev{$t};
    $datatype_col_color_dim{$s} = $datatype_col_color_dim{$t};
}

# Return constant or variable for maximum color index
sub max_col_color_dim {
  local($t) = @_;
  # nc is either 2, 3, or the color argument
  if($datatype_col_color_dim{$t} eq $colors){$def{'nc'};}
  else {$datatype_col_color_dim{$t}};
}

# Dimension of spin row index
%datatype_row_spin_dim = (
  $datatype_integer_abbrev,0,
  $datatype_real_abbrev,0,
  $datatype_complex_abbrev,0,
  $datatype_colorvector_abbrev,0,
  $datatype_halffermion_abbrev,$halfspins,
  $datatype_diracfermion_abbrev,$spins,
  $datatype_colormatrix_abbrev,0,
  $datatype_diracpropagator_abbrev,$spins,
  $datatype_randomstate_abbrev,0
    );

# Append scalar types - the values are identical
foreach $t ( keys %datatype_row_spin_dim ){
  $s = $datatype_scalar_abbrev{$t};
  $datatype_row_spin_dim{$s} = $datatype_row_spin_dim{$t};
}

# Dimension of spin column index
%datatype_col_spin_dim = (
   $datatype_integer_abbrev,0,
   $datatype_real_abbrev,0,
   $datatype_complex_abbrev,0,
   $datatype_colorvector_abbrev,0,
   $datatype_halffermion_abbrev,0,
   $datatype_diracfermion_abbrev,0,
   $datatype_colormatrix_abbrev,0,
   $datatype_diracpropagator_abbrev,$spins,
   $datatype_randomstate_abbrev,0
    );

# Append scalar types - the values are identical
foreach $t ( keys %datatype_col_spin_dim ){
    $s = $datatype_scalar_abbrev{$t};
    $datatype_col_spin_dim{$s} = $datatype_col_spin_dim{$t};
}

# Datatypes carrying color
# They have a nonzero row or column dimension
%datatype_colorful = ();
foreach $t ( @datatype_abbrev )
{
    $s = $datatype_scalar_abbrev{$t};

    if($datatype_row_color_dim{$t} ne "0" ||
       $datatype_col_color_dim{$t} ne "0")
    {$datatype_colorful{$t} = 1;}
    else{$datatype_colorful{$t} = 0;}

    if($datatype_row_color_dim{$s} ne "0" ||
       $datatype_col_color_dim{$s} ne "0")
    {$datatype_colorful{$s} = 1;}
    else{$datatype_colorful{$s} = 0;}
}

# Datatypes having distinct adjoints in the same class
@datatype_adjoint_abbrev = (
     $datatype_complex_abbrev,
     $datatype_colormatrix_abbrev,
     $datatype_diracpropagator_abbrev,
		   );

# Datatypes allowing distinct transpose in the same class
@datatype_transpose_abbrev = (
       $datatype_colormatrix_abbrev,
       $datatype_diracpropagator_abbrev,
		       );

# Build list of nonscalar floating point types 
@datatype_floatpt_abbrev = ();
foreach $t ( @datatype_abbrev ){
    if($datatype_floatpt{$t} == 1){push(@datatype_floatpt_abbrev,$t);}
}

# Types closing under multiplication by complex

@datatype_mult_complex_abbrev = (
     $datatype_complex_abbrev,
     $datatype_colorvector_abbrev,
     $datatype_halffermion_abbrev,
     $datatype_diracfermion_abbrev,
     $datatype_colormatrix_abbrev,
     $datatype_diracpropagator_abbrev,
		     );

# Types closing under self multiplication 

@datatype_mult_self_abbrev = (
  $datatype_integer_abbrev,
  $datatype_colormatrix_abbrev,
  $datatype_diracpropagator_abbrev,
			  );

# Types closing under left multiplication by colormatrix field 

@datatype_left_mult_colormatrix_abbrev = (
     $datatype_colorvector_abbrev,
     $datatype_halffermion_abbrev,
     $datatype_diracfermion_abbrev,
     $datatype_colormatrix_abbrev,
     $datatype_diracpropagator_abbrev,
			     );

# Types closing under right multiplication by colormatrix field 

@datatype_right_mult_colormatrix_abbrev = (
     $datatype_colormatrix_abbrev,
     $datatype_diracpropagator_abbrev,
			     );

# Array datatypes

@datatype_array_element_abbrev = (
    $datatype_colormatrix_abbrev,
    $datatype_halffermion_abbrev,
    $datatype_diracfermion_abbrev,
    $datatype_colorvector_abbrev,
    $datatype_diracpropagator_abbrev,
				  );

# Datatypes with multiple color column vectors

@datatype_color_column_abbrev = (
    $datatype_colormatrix_abbrev,
    $datatype_halffermion_abbrev,
    $datatype_diracfermion_abbrev,
    $datatype_diracpropagator_abbrev,
				  );

# Datatypes with multiple Dirac column vectors

@datatype_dirac_column_abbrev = (
    $datatype_diracpropagator_abbrev,
				 );

# Promotion table for precision
%precision_promotion = (
   $precision_float_abbrev, $precision_double_abbrev,
   $precision_double_abbrev, $precision_double_abbrev
#   $precision_double_abbrev, $precision_longdouble_abbrev
			);

# Construction of specific datatype name from abbreviated generic name
# e.g. M -> QLA_F3_ColorMatrix
# They are based on the prevailing precision and color
# unless overridden.
# (e.g. the specific type departs from the rule when 
# converting double to float and vice versa)
# Depends on globals
#
#    $precision
#    $colors

sub datatype_specific {
    local($t,$force_precision) = @_;

    local($type,$pc);
    $type = $datatype_generic_name{$t};
    $pc = "";
    if($datatype_floatpt{$t} == 1){
	if($force_precision ne "") { $pc = $force_precision; }
	else { $pc = $precision; }
    }
    if($datatype_row_color_dim{$t} ne "0"){
	$pc .= $colors;
    }
    if($pc ne ""){$pc = $pc."_";}
    $type =~ s/QLA_/QLA_$pc/;
    $type;
}

sub datatype_element_specific_abbr {
    local($t) = @_;
    local($elem_t);

    if($datatype_rc{$t} eq "c"){$elem_t = $datatype_complex_abbrev;}
    else{$elem_t = $datatype_real_abbrev;}
    return $elem_t;
}

sub datatype_element_specific {
    local($t,$force_precision) = @_;
    return &datatype_specific(&datatype_element_specific_abbr($t),$force_precision);
}

1;
