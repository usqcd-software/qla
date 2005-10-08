######################################################################
# SciDAC Software Project
# BUILD_QLA Version 0.9
#
# formatting.pl
#
# Author: C. DeTar
# Date:   09/13/02
######################################################################
#
# A variety of functions for controlling code format
# and generating simple loops and variable definitions
#
######################################################################
# Changes:
#
######################################################################
# Supporting files required:

require("headers.pl");

######################################################################

#--------------------------------------------------
# Indentation and braces
#--------------------------------------------------

sub open_block {
    push(@indent,$tab);
}

sub close_block {
    pop(@indent);
}

sub open_brace {
    print QLA_SRC @indent,"{\n";
    &open_block();
}

sub close_brace {
    &close_block();
    print QLA_SRC @indent,"}\n";
}

#--------------------------------------------------
# Simple declarations
#--------------------------------------------------

sub print_int_def {
    local($k) = @_;
    #if($k ne ""){print QLA_SRC @indent,"register int $k;\n";}
    if($k ne ""){print QLA_SRC @indent,"int $k;\n";}
}

sub print_def {
    local($type,$k) = @_;
    #print QLA_SRC @indent,"register $type $k;\n";
    print QLA_SRC @indent,"$type $k;\n";
}

sub print_nonregister_def {
    local($type,$k) = @_;
    print QLA_SRC @indent,"$type $k;\n";
}

#--------------------------------------------------
# Loop control
#--------------------------------------------------

sub open_iter {
    local($i,$max)= @_;

    if($i ne ""){
	print QLA_SRC @indent,"for($i=0;$i<$max;$i++)\n";
	&open_block();
	&open_brace();
    }
}

sub close_iter {
    local($i)= @_;

    if($i ne ""){
	&close_brace();
	&close_block();
    }
}

sub print_def_open_iter {
    local($i,$dim_name) = @_;

    if($i ne "" && $dim_name ne ""){
	&print_int_def($i);
	&open_iter($i,$dim_name);
    }
}

sub print_def_open_iter_list {
    while(@_){
	local($i) = shift(@_);
	local($max) = shift(@_);
	&print_int_def($i); &open_iter($i,$max);
    }
}

sub print_close_iter_list {
    local(@list) = @_;

    while(@list){
	local($i) = pop(@list);
	&close_iter($i);
    }
}
#--------------------------------------------------
# Source file handling
#--------------------------------------------------
sub open_src_file {
    local($filename) = "$c_source_path/$def{'src_filename'}";

    open(QLA_SRC,">$filename") || 
	die "Can't open $filename\n";
}

sub close_src_file {
    close(QLA_SRC);
}

#--------------------------------------------------
# Function definition, top and bottom
#--------------------------------------------------

sub print_function_def {
    local($declaration) = @_;

    @indent = ();
    $tab = "  ";

    print QLA_SRC @indent,"/**************** $def{'func_name'}.c ********************/\n";
    print QLA_SRC @indent,"\n";
    foreach $header ( @headers ){
	print QLA_SRC @indent,"#include $header\n";
    }
    print QLA_SRC @indent,"\n";
    print QLA_SRC @indent,"$declaration\n";
    &open_brace();
}

sub print_top_matter {
    local($declaration,$i,$dim_name) = @_;

    &open_src_file;
    &print_function_def($declaration);
    &print_def_open_iter($i,$dim_name);
}

sub print_end_matter {
    local($i,$dim_name) = @_;

    if($dim_name ne ""){
	&close_iter($i);
    }
    
    &close_brace();
    &close_src_file;
}

sub print_very_top_matter {
    local($declaration,$i,$dim_name) = @_;

    &open_src_file;
    &print_function_def($declaration);
#    &print_def_open_iter($i,$dim_name);
}

sub print_very_end_matter {
    local($i,$dim_name) = @_;

#    if($dim_name ne ""){
#	&close_iter($i);
#    }

    &close_brace();
    &close_src_file;
}

sub get_var_dec($$$) {
  my($type,$name,$value) = @_;
  if( !($value =~ s/^\*//) ) {
    $value = "&".$value;
  }
  return "$type $name = $value;\n";
}

sub make_temp_ptr(\%$) {
  my($tdef,$name) = @_;
  my($old_value) = $tdef->{value};

  if( ($def{dim_name} ne "") &&
      ($tdef->{t} ne "") &&
      (!$datatype_scalar{$tdef->{t}}) &&
      (!$tdef->{temp_ptr}) ) {
    $tdef->{value} = "*${name}i";
    $tdef->{old_value} = $old_value;
    $tdef->{temp_ptr} = 1;
  }
  if($tdef->{temp_ptr}) {
    print QLA_SRC @indent, get_var_dec($tdef->{type}, $tdef->{value},
				       $tdef->{old_value});
  }
}

1;
