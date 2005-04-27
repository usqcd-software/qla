######################################################################
# SciDAC Software Project
# BUILD_QLA Version 0.9
#
# headers.pl
#
# Author: C. DeTar
# Date:   09/13/02
######################################################################
#
# Defines macros and accessors built into the generated code
#
######################################################################
# Changes:
#
# If you make changes in the qla_*.h files, update this file as well
######################################################################
# Supporting files required:

require("datatypes.pl");

######################################################################
# Definitions of header files required by the generated code
######################################################################

# Header defining the random types
$QLA_random_header = "<qla_random.h>";

# Header defining the complex math types
$QLA_cmath_header = "<qla_cmath.h>";

# Header defining real and complex types and complex macros
$QLA_complex_header = "<qla_complex.h>";

# Header defining composite types
# This header should pull in the complex header
$QLA_types_header = "<qla_types.h>";

# Current header file (based on global name header_file)
$QLA_this_header = "<$qla_header_file>";

# Headers needed by the library
@headers = (
            "<stdio.h>",
	    "$QLA_types_header",
	    "$QLA_random_header",
	    "$QLA_cmath_header",
	    "<math.h>"
	    );

######################################################################

# Converts a list of strings into comma separated values, suppressing
# any empty strings

sub comma_list {
    local(@s) = ();
    foreach (@_){if($_ ne ""){ push(@s,$_); } }
    join(",",@s);
}

# Constructs accessor for any type

sub make_accessor {
    local(*arg_def,$nc,$ic,$is,$jc,$js) = @_;
    local($indices,$cap_t,@parts,$name);
    local($t,$type,$trans,$value) = 
	@arg_def{'t','type','trans','value'};

    # Apply transpose to indices if needed
    if($trans ne "t"){$indices = &comma_list($ic,$is,$jc,$js);}
    else{$indices = &comma_list($jc,$js,$ic,$is);}

    # No accessor needed if the datatype is not a tensor (no indices)
    if($indices ne ""){
	# Replace full name with abbreviation (always capitalized)
	# Converts type = QLA_F3_ColorMatrix and t = M into QLA_F3_elem_M
	$cap_t = $t; $cap_t =~ tr/[a-z]/[A-Z]/;
	@parts = split("_",$type);
	$parts[2] = "elem";
	$parts[3] = $cap_t;
	$name = join("_",@parts);
	"$name($value,$indices)";
    }
    else{"$value";}
}

#---------------------------------------------------------------------
# Macro names for real and imaginary parts of complex
#---------------------------------------------------------------------

$get_re = "QLA_real";
$get_im = "QLA_imag";

#---------------------------------------------------------------------
# Map of names of functions involving complex types
#---------------------------------------------------------------------

%unary_cmath = (
		'cexp',   'QLA_cexp',
		'clog',   'QLA_clog',
		'csqrt',  'QLA_csqrt',
		'cexp',   'QLA_cexp',
		'cexpi',  'QLA_cexpi',
		);

#------------------------------------------------
# Function names for random numbers (type double)
#------------------------------------------------
$fcn_random = "QLA_random";
$fcn_gaussian = "QLA_gaussian";
$fcn_seed_random = "QLA_seed_random";

######################################################################
# Macro names for complex arithmetic
######################################################################

#----------------
# Arguments (c)
#----------------

%carith0 = (
	    'arg',    "QLA_arg_c",        # arg(c)
	    'norm',   "QLA_norm_c",       # |c|
	    'norm2',  "QLA_norm2_c"       # |c|^2
	    );

#----------------
# Arguments (c,a)
#----------------

%carith1 = (
	    'eqr',     "QLA_c_eq_r",      # c = a (real)
	    'eqc',     "QLA_c_eq_c",      # c = a
	    'eqmc',    "QLA_c_eqm_c",     # c = -a
	    'eq-c',    "QLA_c_eqm_c",     # c = -a
	    'eqm-c',   "QLA_c_eq_c",      # c = a
	    'eqmr',    "QLA_c_eqm_r",     # c = -a (real)
	    'peqr',    "QLA_c_peq_r",     # c += a (real)
	    'peqc',    "QLA_c_peq_c",     # c += a
	    'meqr',    "QLA_c_meq_r",     # c -= a (real)
	    'meqc',    "QLA_c_meq_c",     # c -= a
	    'meq-c',   "QLA_c_peq_c",     # c += a
	    'peq-c',   "QLA_c_meq_c",     # c -= a
	    'eqca',    "QLA_c_eq_ca",     # c = conjg(a)
	    'peqca',   "QLA_c_peq_ca",    # c += conjg(a)
	    'meqca',   "QLA_c_meq_ca",    # c -= conjg(a)
	    'eqmca',   "QLA_c_eqm_ca",    # c =- conjg(a)
	    'eqRc',    "QLA_r_eq_Re_c",   # c = Re(a)
	    'eqIc',    "QLA_r_eq_Im_c",   # c = Im(a)
	    'peqRc',   "QLA_r_peq_Re_c",  # c += Re(a)
	    'peqIc',   "QLA_r_peq_Im_c",  # c += Im(a)
	    'meqRc',   "QLA_r_meq_Re_c",  # c -= Re(a)
	    'meqIc',   "QLA_r_meq_Im_c",  # c -= Im(a)
	    'eqmRc',   "QLA_r_eqm_Re_c",  # c =- Re(a)
	    'eqmIc',   "QLA_r_eqm_Im_c",  # c =- Im(a)
	    'eqic',    "QLA_c_eq_ic",     # c = i*a
	    'eq-ic',   "QLA_c_eqm_ic",    # c = -i*a
	    'peqic',   "QLA_c_peq_ic",    # c += i*a
	    'meqic',   "QLA_c_meq_ic",    # c -= i*a
	    'meq-ic',  "QLA_c_peq_ic",    # c += i*a
	    'peq-ic',  "QLA_c_meq_ic",    # c -= i*a
	    'eqmic',   "QLA_c_eqm_ic",    # c = -i*a
	    'eqm-ic',  "QLA_c_eq_ic",     # c = i*a
	    );

#----------------
# Arguments (c,a,b)
#----------------

%carith2 = (
	    'eqc+c',   "QLA_c_eq_c_plus_c",      # c = a + b
	    'eqmc+c',  "QLA_c_eqm_c_plus_c",     # c = -a - b
	    'peqc+c',  "QLA_c_peq_c_plus_c",     # c += a + b
	    'meqc+c',  "QLA_c_meq_c_plus_c",     # c -= a + b
	    'eqc+ic',  "QLA_c_eq_c_plus_ic",     # c = a + i*b
	    'eqmc+ic', "QLA_c_eqm_c_plus_ic",    # c = -a - i*b
	    'peqc+ic', "QLA_c_peq_c_plus_ic",    # c += a + i*b
	    'meqc+ic', "QLA_c_meq_c_plus_ic",    # c -= a + i*b
	    'eqr+ir',  "QLA_c_eq_r_plus_ir",     # c = complex(a,b)
	    'peqr+ir', "QLA_c_peq_r_plus_ir",    # c += complex(a,b)
	    'eqmr+ir', "QLA_c_eqm_r_plus_ir",    # c =- complex(a,b)
	    'meqr+ir', "QLA_c_meq_r_plus_ir",    # c -= complex(a,b)
	    'eqc-c',   "QLA_c_eq_c_minus_c",     # c = a - b
	    'eqmc-c',  "QLA_c_eqm_c_minus_c",    # c = -a + b
	    'peqc-c',  "QLA_c_peq_c_minus_c",    # c += a - b
	    'meqc-c',  "QLA_c_meq_c_minus_c",    # c -= a - b
	    'eqc-ca',  "QLA_c_eq_c_minus_ca",    # c = a - b*
	    'eqc-ic',  "QLA_c_eq_c_minus_ic",    # c = a - i*b
	    'eqmc-ic', "QLA_c_eqm_c_minus_ic",   # c = -a + i*b
	    'peqc-ic', "QLA_c_peq_c_minus_ic",   # c += a - i*b
	    'meqc-ic', "QLA_c_meq_c_minus_ic",   # c -= a - i*b
	    'eqc*c',   "QLA_c_eq_c_times_c",     # c = a * b
	    'peqc*c',  "QLA_c_peq_c_times_c",    # c += a * b
	    'eqmc*c',  "QLA_c_eqm_c_times_c",    # c = -(a * b)
	    'meqc*c',  "QLA_c_meq_c_times_c",    # c -= a * b
	    'eqRc*c',  "QLA_r_eq_Re_c_times_c",  # c = Re(a * b)
	    'peqRc*c', "QLA_r_peq_Re_c_times_c", # c += Re(a * b)
	    'eqmRc*c', "QLA_r_eqm_Re_c_times_c", # c = -Re(a * b)
	    'meqRc*c', "QLA_r_meq_Re_c_times_c", # c -= Re(a * b)
	    'eqcI*c',  "QLA_r_eq_Im_c_times_c",  # c = Im(a * b)
	    'peqIc*c', "QLA_r_peq_Im_c_times_c", # c += Im(a * b)
	    'eqmIc*c', "QLA_r_eqm_Im_c_times_c", # c = -Im(a * b)
	    'meqIc*c', "QLA_r_meq_Im_c_times_c", # c -= Im(a * b)
	    'eqc/c',   "QLA_c_eq_c_div_c",       # c = a / b
	    'eqc*ca',  "QLA_c_eq_c_times_ca",    # c = a * conjg(b)
	    'peqc*ca', "QLA_c_peq_c_times_ca",   # c += a * conjg(b)
	    'eqmc*ca', "QLA_c_eqm_c_times_ca",   # c = -(a * conjg(b))
	    'meqc*ca', "QLA_c_meq_c_times_ca",   # c -= a * conjg(b)
	    'eqRc*ca', "QLA_r_eq_Re_c_times_ca", # c = Re(a * conjg(b))
	    'peqRc*ca',"QLA_r_peq_Re_c_times_ca",# c += Re(a * conjg(b))
	    'eqmRc*ca',"QLA_r_eqm_Re_c_times_ca",# c = -Re(a * conjg(b))
	    'meqRc*ca',"QLA_r_meq_Re_c_times_ca",# c -= Re(a * conjg(b))
	    'eqIc*ca', "QLA_r_eq_Im_c_times_ca", # c = Im(a * conjg(b))
	    'peqIc*ca',"QLA_r_peq_Im_c_times_ca",# c += Im(a * conjg(b))
	    'eqmIc*ca',"QLA_r_eqm_Im_c_times_ca",# c = -Im(a * conjg(b))
	    'meqIc*ca',"QLA_r_meq_Im_c_times_ca",# c -= Im(a * conjg(b))
	    'eqca*c',  "QLA_c_eq_ca_times_c",    # c = conjg(a) * b
	    'peqca*c', "QLA_c_peq_ca_times_c",   # c += conjg(a) * b
	    'eqmca*c', "QLA_c_eqm_ca_times_c",   # c = -(conjg(a) * b)
	    'meqca*c', "QLA_c_meq_ca_times_c",   # c -= conjg(a) * b
	    'eqRca*c', "QLA_r_eq_Re_ca_times_c", # c = Re(conjg(a) * b)
	    'peqRca*c',"QLA_r_peq_Re_ca_times_c",# c += Re(conjg(a) * b)
	    'eqmRca*c',"QLA_r_eqm_Re_ca_times_c",# c = -Re(conjg(a) * b)
	    'meqRca*c',"QLA_r_meq_Re_ca_times_c",# c -= Re(conjg(a) * b)
	    'eqIca*c', "QLA_r_eq_Im_ca_times_c",  # c = Im(conjg(a) * b)
	    'peqIca*c',"QLA_r_peq_Im_ca_times_c", # c += Im(conjg(a) * b)
	    'eqmIca*c',"QLA_r_eqm_Im_ca_times_c", # c = -Im(conjg(a) * b)
	    'meqIca*c',"QLA_r_meq_Im_ca_times_c", # c -= Im(conjg(a) * b)
	    'eqca*ca', "QLA_c_eq_ca_times_ca",   # c = conjg(a) * conjg(b)
	    'peqca*ca',"QLA_c_peq_ca_times_ca",  # c += conjg(a) * conjg(b)
	    'eqmca*ca',"QLA_c_eqm_ca_times_ca",  # c = -(conjg(a) * conjg(b))
	    'meqca*ca',"QLA_c_meq_ca_times_ca",  # c -= conjg(a) * conjg(b)
	    'eqRca*ca', "QLA_r_eq_Re_ca_times_ca",  # c = Re(conjg(a) * conjg(b))
	    'peqRca*ca',"QLA_r_peq_Re_ca_times_ca", # c += Re(conjg(a) * conjg(b))
	    'eqmRca*ca',"QLA_r_eqm_Re_ca_times_ca", # c = -Re(conjg(a) * conjg(b))
	    'meqRca*ca',"QLA_r_meq_Re_ca_times_ca", # c -= Re(conjg(a) * conjg(b))
	    'eqcIa*ca', "QLA_r_eq_Im_ca_times_ca",  # c = Im(conjg(a) * conjg(b))
	    'peqIca*ca',"QLA_r_peq_Im_ca_times_ca", # c += Im(conjg(a) * conjg(b))
	    'eqmIca*ca',"QLA_r_eqm_Im_ca_times_ca", # c = -Im(conjg(a) * conjg(b))
	    'meqIca*ca',"QLA_r_meq_Im_ca_times_ca", # c -= Im(conjg(a) * conjg(b))
	    'eqc*r',   "QLA_c_eq_c_times_r",     # c = a * b (b real)
	    'peqc*r',  "QLA_c_peq_c_times_r",    # c += a * b (b real)
	    'eqmc*r',  "QLA_c_eqm_c_times_r",    # c = -(a * b) (b real)
	    'meqc*r',  "QLA_c_meq_c_times_r",    # c -= a * b (b real)
	    'peqc*r',  "QLA_c_peq_c_times_r",    # c += a * b (b real)
	    'eqr*c',   "QLA_c_eq_r_times_c",     # c = a * b (a real)
	    'peqr*c',  "QLA_c_peq_r_times_c",    # c += a * b (a real)
	    'eqmr*c',  "QLA_c_eqm_r_times_c",    # c = -(a * b) (a real)
	    'meqr*c',  "QLA_c_meq_r_times_c",    # c -= a * b (a real)
	    'peqr*c',  "QLA_c_peq_r_times_c",    # c += a * b (a real)
	    'eqc/r',   "QLA_c_eq_c_div_r",       # c = a / b (b real)
	    );

#----------------
# Arguments (c,a,x,b)
#----------------

%carith3 = (
	    'eqc*c+c',  "QLA_c_eq_c_times_c_plus_c",  # c = a*x + b
	    'eqc*c-c',  "QLA_c_eq_c_times_c_minus_c", # c = a*x - b
	    'eqc*r+r',  "QLA_c_eq_c_times_r_plus_r",  # c = a*x + b (x real)
	    'eqc*r-r',  "QLA_c_eq_c_times_r_minus_r", # c = a*x - b (x real)
	    'eqr*c+c',  "QLA_c_eq_r_times_c_plus_c",  # c = a*x + b (a real)
	    'eqr*c-c',  "QLA_c_eq_r_times_c_minus_c", # c = a*x - b (a real)
	    );

#------------------------------------------------
# Coordinate directions for gamma matrices
# These definitions may be changed to macro names
#------------------------------------------------

$dir_X = "0";
$dir_Y = "1";
$dir_Z = "2";
$dir_T = "3";
$dir_5 = "-1";

$sign_MINUS = "-1";
$sign_PLUS  = "1";

1;

