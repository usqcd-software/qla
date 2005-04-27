######################################################################
# SciDAC Software Project
# BUILD_QLA Version 0.9
#
# variable_names.pl
#
# Author: C. DeTar
# Date:   09/13/02
######################################################################
#
# Defines variable names for standard argument lists
# and local variables
#
######################################################################
# Changes:
#
######################################################################
# Supporting files required:

require("datatypes.pl");

######################################################################

# Number of colors argument, if variable
$arg_nc = "nc";

# Macro for prevailing number of colors - used for SU(N)
$macro_nc = "QLA_Nc";

# Constant random number seed argument
$arg_seed = "seed";

# Standard destination and source arguments
%arg_name = (
    'dest',"r",
    'src1',"a",
    'src2',"b",
    'src3',"c",
    );

# Index array arguments for each of the above
%arg_index_name = (
		   'dest', "index".$arg_name{'dest'},
		   'src1', "index".$arg_name{'src1'},
		   'src2', "index".$arg_name{'src2'},
		   'src3', "index".$arg_name{'src3'},
		   );

# Gang index array
$arg_gang_index = "index";

# Vector dimension
$arg_dim = "n";

# Dirac matrix and sign
$arg_mu = "mu";
$arg_sign = "sign";

# Color, spin row and column indices
$var_row_color = "i_c";
$var_row_spin = "i_s";
$var_col_color = "j_c";
$var_col_spin = "j_s";
$var_color2 = "k_c";
$var_spin2 = "k_s";

# Row and column indices for the various types
# These routines return a variable name or a null string
# if the row or column dimension is zero.

sub get_row_color_index {
  local(*arg_def) = @_;
  local($trans,$t) = @arg_def{'trans','t'};

  if( $t &&
      ( $trans eq ""  && $datatype_row_color_dim{$t} ne "0" ||
	$trans eq "t" && $datatype_col_color_dim{$t} ne "0" ) ) {
    $var_row_color;
  } else {
    "";
  }
}

sub get_row_color_index2 {
  local(*arg_def) = @_;
  local($trans,$t) = @arg_def{'trans','t'};

  if( $t &&
      ( $trans eq ""  && $datatype_row_color_dim{$t} ne "0" ||
	$trans eq "t" && $datatype_col_color_dim{$t} ne "0" ) ) {
    $var_color2;
  } else {
    "";
  }
}

# Row and column indices for the various types
sub get_col_color_index {
  local(*arg_def) = @_;
  local($trans,$t) = @arg_def{'trans','t'};

  if( $t &&
      ( $trans eq ""  && $datatype_col_color_dim{$t} ne "0" ||
	$trans eq "t" && $datatype_row_color_dim{$t} ne "0" ) ) {
    $var_col_color;
  } else {
    "";
  }
}

sub get_col_color_index2 {
  local(*arg_def) = @_;
  local($trans,$t) = @arg_def{'trans','t'};

  if( $t &&
      ( $trans eq ""  && $datatype_col_color_dim{$t} ne "0" ||
	$trans eq "t" && $datatype_row_color_dim{$t} ne "0" ) ) {
    $var_color2;
  } else {
    "";
  }
}

sub get_row_spin_index {
  local(*arg_def) = @_;
  local($trans,$t) = @arg_def{'trans','t'};

  if( $t &&
      ( $trans eq ""  && $datatype_row_spin_dim{$t} ne "0" ||
	$trans eq "t" && $datatype_col_spin_dim{$t} ne "0" ) ) {
    $var_row_spin;
  } else {
    "";
  }
}

sub get_row_spin_index2 {
  local(*arg_def) = @_;
  local($trans,$t) = @arg_def{'trans','t'};

  if( $t &&
      ( $trans eq ""  && $datatype_row_spin_dim{$t} ne "0" ||
	$trans eq "t" && $datatype_col_spin_dim{$t} ne "0" ) ) {
    $var_spin2;
  } else {
    "";
  }
}


sub get_col_spin_index {
  local(*arg_def) = @_;
  local($trans,$t) = @arg_def{'trans','t'};

  if( $t &&
      ( $trans eq ""  && $datatype_col_spin_dim{$t} ne "0" ||
	$trans eq "t" && $datatype_row_spin_dim{$t} ne "0" ) ) {
    $var_col_spin;
  } else {
    "";
  }
}

sub get_col_spin_index2 {
  local(*arg_def) = @_;
  local($trans,$t) = @arg_def{'trans','t'};

  if( $t &&
      ( $trans eq ""  && $datatype_col_spin_dim{$t} ne "0" ||
	$trans eq "t" && $datatype_row_spin_dim{$t} ne "0" ) ) {
    $var_spin2;
  } else {
    "";
  }
}

# Assign standard names to indices
sub get_color_spin_indices {
  local(*arg_def) = @_;

  (&get_row_color_index(*arg_def),&get_row_spin_index(*arg_def),
   &get_col_color_index(*arg_def),&get_col_spin_index(*arg_def));
}


######################################################################
# Temporary variable names local to function code
######################################################################

# Integer for looping over main operand vector index
$var_i = "i";

# Complex or real intermediate values
$var_x = "x";
$var_x2 = "x2";

# General intermediate value for global sum
$var_global_sum = "sum";

1;
