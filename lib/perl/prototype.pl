######################################################################
# SciDAC Software Project
# BUILD_QLA Version 0.9
#
# prototype.pl
#
# Author: C. DeTar
# Date:   09/13/02
######################################################################
# Constructs and writes the function prototype.
# Creates header files
#
# Also loads the global hash table %def and argument hash tables
# %dest_def, %src1_def, %src2_def, %src3_def with argument attributes 
# needed for building the code.
# Our protocol is that from here on the %def and %XXXX_def globals
# are "read only".
#
######################################################################
# Changes:
#
#   10/31/02 C. DeTar Added color-generic header files
#
######################################################################
# Supporting files required:

require("datatypes.pl");
require("indirection.pl");
require("variable_names.pl");
require("operatortypes.pl");

######################################################################
#   Table of keys for %def
######################################################################

# Input and output are relative to the make_prototype call below.
# Most input values may be omitted, in which case default values
# are used.  Default values are given in [].
# Only the dest_t argument with * is required.

#---------------------------------------------------------------------
#  key              purpose
#---------------------------------------------------------------------
#  precision        input   overrides standard D or F or Q precision
#                           label for the function name. [standard type]
#  prefix           output  full function prefix, as in "QLA_F3"
#                           used as a key for the header file pointer
#                           and the source code directory
#  prefix_precision output  partial prefix, as in QLA_F in place of QLA_F3
#                           used to build the color-generic name
#  src_filename     output  name of the source code file
#  func_name        output  function name
#  nc               output  number of colors ("2", "3", or the nc argument)
#  qualifier        input   string to follow eqop in function name [none]
#  op               input   operation between src1 and src2 [none]
#  op2              input   operation between src2 and src3 [none]
#  gang_index_name  output  name of gang indexing argument, if used
#  dim_name         output  name of maximum index argument, if used
#  declaration      output  full function declaration
#
#---------------------------------------------------------------------
#      Destination argument
#---------------------------------------------------------------------
#  dest_t           *input  abbreviation for datatype
#  dest_ptr_pfx     output  pointer prefix
#  dest_idx_pfx     output  index prefix
#  dest_adj         input   "a" indicates adjoint [none] (not used for dest)
#                           forces transpose and complex conjugate
#  dest_trans       input   "t" indicates transpose [none] (not used for dest)
#  dest_conj        input   "a" indicates complex conjugate [none]
#  dest_rc          output  "c" for complex and "r" for real matrix element
#  dest_color       output  1 if datatype carries color.  0 otherwise.
#  dest_sfx         input   string to follow dest_t in function name
#  dest_type        input   overrides the standard datatype [standard datatype]
#                   output  fully qualified datatype
#  dest_name        input   argument name [standard name]
#                   output  argument name
#  dest_index_name  input   index argument name if needed [standard name]
#                   output  index argument name
#  dest_extra_arg   input   extra arguments to follow [none]
#  dest_value       output  fully subscripted destination value
#  dest_mc          output  row color dimension
#  dest_nc          output  column color dimension
#  dest_ms          output  row spin dimension
#  dest_ns          output  column spin dimension
#
#---------------------------------------------------------------------
#      Source argument 1
#---------------------------------------------------------------------
#
#  Same keys as dest, but with "dest" -> "src1"
#
#---------------------------------------------------------------------
#      Source argument 2
#---------------------------------------------------------------------
#
#  Same keys as dest, but with "dest" -> "src2"
#  
#---------------------------------------------------------------------
#      Source argument 3
#---------------------------------------------------------------------
#
#  Same keys as dest, but with "dest" -> "src3"
#  
#---------------------------------------------------------------------


######################################################################
#   Table of keys for %dest_def, %src1_def, %src2_def, %src3_def
######################################################################

#   The keys for %dest_def are obtained from the keys for %def by
#   dropping the 'dest_' string.  Thus 'dest_t' -> 't', etc.
#   Similarly the keys for %src1_def, %src2_def, %src3_def are
#   constructed.

######################################################################

#---------------------------------------------------------------------
# Create a unique identifying macro name from a header file name
#---------------------------------------------------------------------
# e.g. converts "../../include/qla_f3.h" to "_QLA_F3_H"

sub make_id_macro {
    local($file) = @_;
    local($s);

    $s = $file;
    $s =~ s^.*/^^;
    $s =~ tr/[a-z]/[A-Z]/;
    $s =~ s/\./_/;
    $s = "_".$s;
    $s;
}

#---------------------------------------------------------------------
# Open QLA header files
#---------------------------------------------------------------------

sub open_qla_header {
    local($file) = @_;

    open(QLA_HDR,">$file") || die "Can't open $file\n";

    # Convert header file name to a macro for preventing duplicate insertions
    $suppress_header_dups = &make_id_macro($file);
    print QLA_HDR "#ifndef $suppress_header_dups\n";
    print QLA_HDR "#define $suppress_header_dups\n";
}

# The generic header file converts fully generic function names to
# specific function names.
#   e.g. QLA_G_eq_G is mapped to QLA_D3_G_eq_G

# The color-generic header file converts partially generic (color
# omitted) function names to specific function names.
#   e.g. QLA_D_G_eq_G is mapped to QLA_D3_G_eq_G

sub open_generic_defines_header {
    local($file,$do_gen,$do_col_gen) = @_;

    # The fully generic file name takes the header name and adds "_generic"
    # e.g. qla_f3.h -> qla_f3_generic.h
    $generic_header = $file;
    $generic_header =~ s/\.h/_generic.h/;

    # The color-generic file name uses "_color_generic"
    # e.g. qla_f3.h -> qla_f3_color_generic.h
    $color_generic_header = $file;
    $color_generic_header =~ s/\.h/_color_generic.h/;

    $generic_header_stripped = $generic_header;
    $generic_header_stripped =~ s^.*/^^;

    $color_generic_header_stripped = $color_generic_header;
    $color_generic_header_stripped =~ s^.*/^^;

    if($do_gen){
	open(QLA_GEN_HDR,">$generic_header") || 
	    die "Can't open $generic_header\n";
	# Convert header file name to a macro for preventing duplicate insertions
	$suppress_generic_header_dups = &make_id_macro($generic_header);
	print QLA_GEN_HDR "#ifndef $suppress_generic_header_dups\n";
	print QLA_GEN_HDR "#define $suppress_generic_header_dups\n";
    }

    if($do_col_gen){
	open(QLA_COL_GEN_HDR,">$color_generic_header") || 
	    die "Can't open $color_generic_header\n";
	$suppress_color_generic_header_dups = &make_id_macro($color_generic_header);
	print QLA_COL_GEN_HDR "#ifndef $suppress_color_generic_header_dups\n";
	print QLA_COL_GEN_HDR "#define $suppress_color_generic_header_dups\n";
    }

}

#---------------------------------------------------------------------
# Close QLA header files
#---------------------------------------------------------------------

sub close_generic_defines_header {
    local($do_gen,$do_col_gen) = @_;

    if($do_col_gen){
	# Print include directive for color generic header in primary header file
	print QLA_HDR "\n\n/* Translation to color-generic names */\n\n";
	if($request_colors){
	    print QLA_HDR "#if QLA_Colors == ";
	    if($colors eq $colors_n){print QLA_HDR "\'$colors\'";}
	    else{print QLA_HDR "$colors";}
	    print QLA_HDR "\n\n";
	    print QLA_HDR "#include <$color_generic_header_stripped>\n\n";
	    print QLA_HDR "#endif\n";
	}
	print QLA_COL_GEN_HDR "#endif /* $suppress_color_generic_header_dups */\n";
	close(QLA_COL_GEN_HDR);
    }

    if($do_gen){
	# Print include directive for generic header in primary header file
	print QLA_HDR "\n\n/* Translation to fully generic names */\n\n";
	print QLA_HDR "#if QLA_Precision == \'$precision\'";
	if($request_colors){
	    print QLA_HDR " && QLA_Colors == ";
	    if($colors eq $colors_n){print QLA_HDR "\'$colors\'";}
	    else{print QLA_HDR "$colors";}
	}
	print QLA_HDR "\n\n";
	print QLA_HDR "#include <$generic_header_stripped>\n\n";
	print QLA_HDR "#endif\n";

	print QLA_GEN_HDR "#endif /* $suppress_generic_header_dups */\n";
	close(QLA_GEN_HDR);
    }
}

sub close_qla_header {
    print QLA_HDR "#endif /* $suppress_header_dups */\n";
    close(QLA_HDR);
}

#---------------------------------------------------------------------
# Create name for atomic value
#---------------------------------------------------------------------
# Based on the indexing option, construct the scalar value
# from a pointer argument with dereferencing of the pointer result,
# if necessary.
# e.g. if gang_index is in force, convert the pointer name "a"
# to "a[index[i]]".

sub make_atomic_value {
    local($ptr_pfx,$t,$name,$index_name,$gang_index_name,$dim_name) = @_;
    local($index,$scalar_value);

    # If name is null, return null
    if($name eq ""){$scalar_value = "";}

    else{
	# Return dereferenced name if a scalar operation or scalar argument
	if($dim_name eq "" || $datatype_scalar{$t} == 1){
	    $scalar_value = "*$name";
	}
	# Return indexed name if a vector operation
	else{
	    if($gang_index_name eq ""){
		if($index_name eq "") { $index = $var_i; }
		else { $index = "$index_name\[$var_i]"; }
	    }
	    else{
		$index = "$gang_index_name\[$var_i]";
	    }
	    $scalar_value = "$name\[$index]";
	    if($ptr_pfx ne ""){
		$scalar_value = "*$scalar_value";
	    }
	}
    }

    $scalar_value;
}

#---------------------------------------------------------------------
# Construct the function name prefix
#---------------------------------------------------------------------

# Builds the full function prefix and a partial prefix
# for the color-generic name.  The prefix for the fully
# generic name can be built easily from the namespace
# so is not done here.
# e.g. prefix = QLA_F3 and prefix_precision = QLA_F

sub func_prefix {
    local($colorful,$floating,$force_precision) = @_;
    local($prefix,$prefix_precision);

    # Append precision suffix if needed
    $prefix_precision = $namespace;
    if( $force_precision ne ""){
	$prefix_precision .= $dash.$force_precision;
    }
    else{
	if($floating == 1){
	    $prefix_precision .= $dash.$precision;
	}
    }
    # Append color suffix if needed
    $prefix = $prefix_precision;
    if($colorful > 0){
	if($force_precision ne "" || $floating == 1){
	    $prefix .= $colors;
	}
	else{
	    $prefix .= $dash.$colors;
	}
    }
    ("$prefix","$prefix_precision");
}

#---------------------------------------------------------------------
# Create a single argument definition
#---------------------------------------------------------------------

sub make_arg {
    local($type,$ptr,$arg,$index_name) = @_;
    local($string);

    $string = $type;
    if($ptr eq $pointer_pfx){$string = $string." **$arg ";}
    else {$string = $string." *$arg ";}
    if($index_name ne ""){$string = $string.", int *$index_name ";}
    $string;
}

#---------------------------------------------------------------------
# Set maximum dimensions of tensor indices
#---------------------------------------------------------------------

sub max_color_spin_dim {
    local($arg,$trans) = @_;
    local($t) = $def{$arg.'_t'};
    if($trans ne "t"){
	$def{$arg.'_mc'} = &max_row_color_dim($t);
	$def{$arg.'_nc'} = &max_col_color_dim($t);
	$def{$arg.'_ms'} = $datatype_row_spin_dim{$t};
	$def{$arg.'_ns'} = $datatype_col_spin_dim{$t};
    }
    else{
	$def{$arg.'_mc'} = &max_col_color_dim($t);
	$def{$arg.'_nc'} = &max_row_color_dim($t);
	$def{$arg.'_ms'} = $datatype_col_spin_dim{$t};
	$def{$arg.'_ns'} = $datatype_row_spin_dim{$t};
    }
}

#---------------------------------------------------------------------
# Load individual argument hash table from %def
#---------------------------------------------------------------------
# The keys and values are copied from %def, but the prefix 'arg_'
# is dropped in the key.

sub load_arg_hash {
    local(*arg_def,$prefix) = @_;
    local($key,$arg_key);
    local($pfxdash) = $prefix.'_';

    if($def{$prefix.'_t'} ne ""){
	foreach $key ( keys %def ){
	    # For keys with the prefix
	    if($key =~ /^$prefix/){
		$arg_key = $key;
		$arg_key =~ s/$pfxdash//;
		$arg_def{$arg_key} = $def{$key};
	    }
	}
    }
}

#---------------------------------------------------------------------
# Construct the macro map from generic to specific function 
#---------------------------------------------------------------------
sub make_define_map {
    local($name,$name_generic,$declaration) = @_;
    local($nargs,$i,@arglist,$argstring);

    # Map only the name unless we require an extra color argument
    if($def{'nc'} eq $arg_nc){
	# Count arguments by counting commas (don't count 1st arg)
	$nargs = split(',',$declaration) - 1;
	@arglist = ();
	for($i=1;$i<=$nargs;$i++){push(@arglist,"x$i");}
	$argstring = join(',',@arglist);
	("$name_generic($argstring)","$name($macro_nc,$argstring)");
    }
    else{
	($name_generic,$name);
    }
}
#---------------------------------------------------------------------
# Construct the function prototype
#---------------------------------------------------------------------
# Supports up to ternary expressions: r eqop a op b op2 c

# As we build the prototype, collect information in a global hash
# table %def for use in generating the code

sub make_prototype {

    local($indexing,$assgn) = @_;

    local($colorful,$floating);
    local($eqop);
    local($func_name,$declaration);
    local($arg,$v);
    local(%argstring);
    
    ############################################################
    # Function name
    ############################################################

    #----------------------------------------
    # Prefix
    #----------------------------------------

    # Build the automatic color and precision prefix for the 
    # function name and library.
    # A nonnull $def{'precision'} argument overrides the automatic precision
    # prefix, but the color suffix is still possible
    # (e.g. with precision conversion operations)

    # Color label is required if any argument carries color
    $colorful = $datatype_colorful{$def{'src1_t'}} | 
	$datatype_colorful{$def{'src2_t'}} | 
	$datatype_colorful{$def{'src3_t'}} | 
	$datatype_colorful{$def{'dest_t'}};
    # Precision label is required if any argument is floating point
    $floating = $datatype_floatpt{$def{'dest_t'}} | 
	$datatype_floatpt{$def{'src1_t'}} | 
	$datatype_floatpt{$def{'src2_t'}} | 
	$datatype_floatpt{$def{'src3_t'}};
    ($def{'prefix'},$def{'prefix_precision'}) = 
	&func_prefix($colorful,$floating,$def{'precision'});

    # Stop here if prefix does not match target or its alternate
    return 0 if ($def{'prefix'} ne $target && $def{'prefix'} ne $target2);
    
    #----------------------------------------
    # Build strings for each argument in use
    # Set transpose, complex conjugate, real-complex
    #----------------------------------------
    # e.g.  "pGa"
    
    foreach $arg ( 'dest','src1','src2','src3' ){
	if(defined($def{$arg.'_t'})){

	    $def{$arg.'_ptr_pfx'} = $ind_ptr_prefix{"$arg,$indexing"};
	    $def{$arg.'_idx_pfx'} = $ind_idx_prefix{"$arg,$indexing"};
	    $argstring{$arg} = $def{$arg.'_ptr_pfx'}.$def{$arg.'_idx_pfx'}.
		$def{$arg.'_t'}.$def{$arg.'_adj'}.$def{$arg.'_sfx'};

	    # Adjoint forces transpose and complex conjugate
	    if($def{$arg.'_adj'} eq $suffix_adjoint){
		$def{$arg.'_trans'} = "t"; $def{$arg.'_conj'} = "a";
	    }

	    # Specify real or complex matrix elements
	    $def{$arg.'_rc'} = $datatype_rc{$def{$arg.'_t'}};

	    # Specify datatype carrying color
	    $def{$arg.'_color'} = $datatype_colorful{$def{$arg.'_t'}};
	}
    }

    #---------------------------------------------------
    # Build dest and assignment part of the function name
    #---------------------------------------------------
    
    $func_name = $argstring{'dest'};
    $func_name .= $dash.$ind_assignop_prefix{$indexing}.$assgn;
    if($def{'qualifier'} ne ""){$func_name .= $dash.$def{'qualifier'};}
    
    #----------------------------------------
    # Append source parts (with ops)
    #----------------------------------------

    if(defined($def{'src1_t'})){
	$func_name .= $dash.$argstring{'src1'};
    }
    if(defined($def{'src2_t'})){
	$func_name .= $dash.$def{'op'}.$dash.$argstring{'src2'};
    }
    if(defined($def{'src3_t'})){
	$func_name .= $dash.$def{'op2'}.$dash.$argstring{'src3'};
    }

    # The generic name leaves off the color and precision label.
    # We do not create a fully generic name if the precision label is
    # forced - only a color-generic name.

    if($def{'precision'} ne ""){
	$func_name_generic = $def{'prefix'}.$dash.$func_name;
    }
    else{
	$func_name_generic = $namespace.$dash.$func_name;
    }

    # The color-generic name leaves off the color but keeps the
    # precision label

    $func_name_color_generic = $def{'prefix_precision'}.$dash.$func_name;

    # The specific function name has the full prefix

    $func_name = $def{'prefix'}.$dash.$func_name;

    # Save completed function name 

    $def{'func_name'} = $func_name;
    
    ############################################################
    # Declaration
    ############################################################
    
    $declaration = "void $func_name ( ";
    
    # Add nc argument if needed
    
    if($colors eq $colors_n && $colorful > 0){
	$declaration .= "int $arg_nc, ";
	$def{'nc'} = $arg_nc;
    }
    else{
	$def{'nc'} = $colors;
    }
    
    #---------------------------------------------------------------
    # Generate destination and source arguments and array dimensions
    #---------------------------------------------------------------
    
    foreach $arg ( 'dest','src1','src2','src3' ){
	if(defined($def{$arg.'_t'})){
	    # Use standard type, if not specified
	    if( $def{$arg.'_type'} eq "" ) { 
		$def{$arg.'_type'} = &datatype_specific($def{$arg.'_t'}); }
	    
	    # Use default names of arguments, if not specified.
	    if( $def{$arg.'_name'} eq "" ){ 
		$def{$arg.'_name'} = $arg_name{$arg}; }
	    
	    # Use default names of extra index arguments, if needed.
	    if( $def{$arg.'_idx_pfx'} eq $index_pfx ){ 
		$def{$arg.'_index_name'} = $arg_index_name{$arg}; }

	    # Set color-spin index dimensions
	    &max_color_spin_dim($arg,$def{$arg.'_trans'});
	}
    }


    #----------------------------------------
    # Insert destination and source arguments
    #----------------------------------------

    # Destination argument

    $declaration .= &make_arg($def{'dest_type'},
			      $def{'dest_ptr_pfx'},
                              "__restrict__ $def{'dest_name'}",
			      $def{'dest_index_name'});
    $declaration .= $def{'dest_extra_arg'};

    # Source arguments
    
    foreach $arg ( 'src1', 'src2', 'src3' ){
	if(defined($def{$arg.'_t'})){
	    $v = $def{$arg.'_type'};
	    $declaration .= &make_arg(", $v ",
				      $def{$arg.'_ptr_pfx'},$def{$arg.'_name'},
				      $def{$arg.'_index_name'});
	}
	$declaration .= $def{$arg.'_extra_arg'};
    }    
    
    #---------------------------------------------
    # Add gang index array argument, if called for
    #---------------------------------------------
    
    if($ind_needs_gang_index{$indexing} == 1){
	$declaration .= ", int *$arg_gang_index ";
	$def{'gang_index_name'} = $arg_gang_index;
    }
    
    #--------------------------------------------
    # Add array dimension argument, if called for
    #--------------------------------------------
    
    if($ind_needs_dim{$indexing} == 1){
	$declaration .= ", int $arg_dim ";
	$def{'dim_name'} = $arg_dim;
    }
    
    # Close parenthesis
    $declaration .= ")";
    
    ############################################################
    # Print the prototype with comments
    ############################################################

    print QLA_HDR $comment0 if $comment0; $comment0 = "";
    print QLA_HDR $comment1 if $comment1; $comment1 = "";
    print QLA_HDR $comment2 if $comment2; $comment2 = "";
    print QLA_HDR $comment3 if $comment3; $comment3 = "";

    print QLA_HDR "$declaration;\n";
    $def{'declaration'} = $declaration;

    ############################################################
    # Print the map from the generic to specific function names
    ############################################################

    if($func_name ne $func_name_generic){
	@define_map = &make_define_map($func_name,$func_name_generic,
				       $declaration);
	print QLA_GEN_HDR "#define @define_map\n";
    }

    if($func_name ne $func_name_color_generic &&
       $func_name_generic ne $func_name_color_generic){
	@define_map = &make_define_map($func_name,$func_name_color_generic,
				       $declaration);
	print QLA_COL_GEN_HDR "#define @define_map\n";
    }

    ############################################################
    # Build names of indexed, dereferenced values for code
    ############################################################
    
    foreach $arg ( 'dest','src1','src2','src3' ){
	$def{$arg.'_value'} = &make_atomic_value(
             @def{$arg.'_ptr_pfx',$arg.'_t',$arg.'_name',
		  $arg.'_index_name','gang_index_name','dim_name'});
    }
    
    ############################################################
    # Load individual hash tables for arguments
    ############################################################
    
    %dest_def = {}; &load_arg_hash(*dest_def,'dest');
    %src1_def = (); &load_arg_hash(*src1_def,'src1');
    %src2_def = (); &load_arg_hash(*src2_def,'src2');
    %src3_def = (); &load_arg_hash(*src3_def,'src3');

    ############################################################
    # Open source file. Name is function name dot c
    ############################################################
    $def{'src_filename'} = $def{'func_name'}.'.c';

    return 1;
}

1;
