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

use strict;

require("headers.pl");

use vars qw/ $have_openmp /;
use vars qw/ %datatype_scalar %datatype_rc /;
use vars qw/ $c_source_path /;
use vars qw/ $arg $arg_nc /;
use vars qw/ $pointer_pfx /;
use vars qw/ @disjoint_list /;
use vars qw/ $tab /;
use vars qw/ $header @headers /;

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
  my($k) = @_;
  #if($k ne ""){print QLA_SRC @indent,"register int $k;\n";}
  #if($k ne ""){print QLA_SRC @indent,"int $k;\n";}
}

sub print_def {
  my($type,$k) = @_;
  #print QLA_SRC @indent,"register $type $k;\n";
  if($type =~ /QLA_.N/) {
    print QLA_SRC @indent,"$type($arg_nc, ($k));\n";
  } else {
    print QLA_SRC @indent,"$type $k;\n";
  }
}

sub print_nonregister_def {
  my($type,$k) = @_;
  if($type =~ /QLA_.N/) {
    print QLA_SRC @indent,"$type($arg_nc, ($k));\n";
  } else {
    print QLA_SRC @indent,"$type $k;\n";
  }
}

#--------------------------------------------------
# Loop control
#--------------------------------------------------

sub open_siteloop {
  my($i,$max)= @_;

  if($i ne "" && $max ne ""){
    if($have_openmp eq "yes") {
      print QLA_SRC "#pragma omp parallel for\n"
    }
    print QLA_SRC @indent,"for(int $i=0; $i<$max; $i++) {\n";
    &open_block();
    &print_align_indx();
  }
}

sub open_siteloop_reduce {
  my($i,$max,$rdef1)= @_;
  my %rdef2 = %{$rdef1};

  if($i ne "" && $max ne "") {
    if($have_openmp eq "yes") {
      my $rvar = $$rdef1{'value'};
      if($$rdef1{'t'} eq 'r') {
        print QLA_SRC "#pragma omp parallel for reduction(+:$rvar)\n";
      } else {
	my $rvar2 = $rvar."_local";
	$rdef2{'value'} = $rvar2;
        print QLA_SRC "#pragma omp parallel\n";
	&open_brace();
	&print_nonregister_def($rdef2{'type'},$rvar2);
	&print_fill(\%rdef2, "zero");
        print QLA_SRC "#pragma omp for\n";
      }
    }
    print QLA_SRC @indent,"for(int $i=0; $i<$max; $i++) {\n";
    &open_block();
    &print_align_indx();
  }
  return \%rdef2;
}

sub close_siteloop_reduce {
  my($i,$max,$rdef1,$rdef2)= @_;

  if($i ne "" && $max ne ""){
    &close_brace();
    if($$rdef1{'value'} ne $$rdef2{'value'}) {
      print QLA_SRC "#pragma omp critical\n";
      &open_brace();
      &print_val_eqop_op_val($rdef1,$eqop_peq,$rdef2,"identity");
      &close_brace();
      &close_brace();
    }
  }
}

sub open_iter {
  my($i,$max,$min)= @_;

  if($i ne "" && $max ne ""){
    if($min eq "" ) { $min = '0'; }
    print QLA_SRC @indent,"for(int $i=$min; $i<$max; $i++) {\n";
    &open_block();
#	&open_brace();
  }
}

sub close_iter {
    my($i)= @_;

    if($i ne ""){
	&close_brace();
#	&close_block();
    }
}

sub print_def_open_iter {
    my($i,$dim_name) = @_;

    if($i ne "" && $dim_name ne ""){
	&print_int_def($i);
	&open_iter($i,$dim_name);
    }
}

sub print_def_open_iter_list {
    while(@_){
	my($i) = shift(@_);
	my($max) = shift(@_);
	&print_int_def($i); &open_iter($i,$max);
    }
}

sub print_close_iter_list {
    my(@list) = @_;

    while(@list){
	my($i) = pop(@list);
	&close_iter($i);
    }
}
#--------------------------------------------------
# Source file handling
#--------------------------------------------------
sub open_src_file {
    my($filename) = "$c_source_path/$def{'src_filename'}";

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
    my($declaration) = @_;

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

sub print_align_top {
  foreach $arg ( 'dest','src1','src2','src3' ) {
    if(defined($def{$arg.'_t'})) {
      if($def{$arg.'_ptr_pfx'} ne $pointer_pfx &&
	 $def{$arg.'_multi'} eq '') {
	#print QLA_SRC "#ifdef __xlc__\n";
	print QLA_SRC @indent,"__alignx(16,$def{$arg.'_name'});\n";
	#print QLA_SRC "#endif\n";
      }
    }
  }
}

sub print_align_indx {
  foreach $arg ( 'dest','src1','src2','src3' ) {
    if(defined($def{$arg.'_t'})) {
      if($def{$arg.'_ptr_pfx'} eq $pointer_pfx &&
	 $def{$arg.'_multi'} eq '') {
	my $value = $def{$arg.'_value'};
	if( !($value =~ s/^\*//) ) {
	  $value = "&".$value;
	}
	print QLA_SRC "#ifdef HAVE_XLC\n";
	print QLA_SRC @indent,"__alignx(16,$value);\n";
	print QLA_SRC "#endif\n";
      }
    }
  }
}

sub print_align_multi {
  foreach $arg ( 'dest','src1','src2','src3' ) {
    if(defined($def{$arg.'_t'})) {
      if($def{$arg.'_multi'} ne '') {
	my $value = $def{$arg.'_value'};
	if( !($value =~ s/^\*//) ) {
	  $value = "&".$value;
	}
	print QLA_SRC "#ifdef HAVE_XLC\n";
	print QLA_SRC @indent,"__alignx(16,$value);\n";
	print QLA_SRC "#endif\n";
      }
    }
  }
}

sub print_very_top_matter {
  my($declaration,$i,$dim_name) = @_;

  &open_src_file;
  &print_function_def($declaration);
  #if($prec ne "") {
  print QLA_SRC "#ifdef HAVE_XLC\n";
  if($#disjoint_list>0) {
    print QLA_SRC "#pragma disjoint(".join(',',@disjoint_list).")\n";
  }
  &print_align_top();
  print QLA_SRC "#endif\n";
  #}
  if(($src1_def{'t'} ne '') && ($datatype_scalar{$src1_def{'t'}})) {
    &make_temp(\%src1_def);
  }
#    &print_def_open_iter($i,$dim_name);
}

sub print_top_matter {
  my($declaration,$i,$dim_name) = @_;

  &print_very_top_matter($declaration,$i,$dim_name);
  #&open_src_file;
  #&print_function_def($declaration);
  #print QLA_SRC "#ifdef HAVE_XLC\n";
  #print QLA_SRC "#pragma disjoint($disjoint_list)\n";
  #&print_align_top();
  #print QLA_SRC "#endif\n";
  if($i ne "" && $dim_name ne ""){
    &print_int_def($i);
    if($have_openmp eq "yes" && $i eq $var_i) {
      print QLA_SRC "#pragma omp parallel for\n"
    }
    &open_iter($i,$dim_name);
  }
  &print_align_indx();
}

sub print_very_end_matter {
    my($i,$dim_name) = @_;

#    if($dim_name ne ""){
#	&close_iter($i);
#    }

    &close_brace();
    &close_src_file;
}

sub print_end_matter {
    my($i,$dim_name) = @_;

    if($dim_name ne ""){
	&close_iter($i);
    }
    
    &close_brace();
    &close_src_file;
}

sub get_var_dec($$$) {
  my($type,$name,$value) = @_;
  if( !($value =~ s/^\*//) ) {
    $value = "&".$value;
  }
  if($type =~ /QLA_.N/) {
      return "$type($arg_nc, ($name)) = $value;\n";
  } else {
      return "$type $name = $value;\n";
  }
}

sub make_temp(\%) {
  my($tdef) = @_;
  my($old_value) = $tdef->{value};
  my($name) = "$tdef->{name}t";

  if( ($def{dim_name} ne "") &&
      (($tdef->{t} eq "r") || ($tdef->{t} eq "c")) &&
      (!$tdef->{temp}) ) {
    $tdef->{value} = $name;
    $tdef->{old_value} = $old_value;
    $tdef->{temp} = 1;
    $tdef->{type} = &datatype_specific($tdef->{t}, $temp_precision);
  }
  if($tdef->{temp}) {
    &print_def($tdef->{type}, $name);
    &print_s_eqop_s($tdef->{rc}, $name, $eqop_eq, "", $tdef->{rc}, $old_value, "", $temp_precision, $precision);
  }
}

sub make_temp_ptr(\%$) {
  #return;
  my($tdef,$name) = @_;
  my($old_value) = $tdef->{value};

  #print "$tdef->{t} $datatype_scalar{$tdef->{t}} $tdef->{temp_ptr}\n";
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

sub make_cast($$$$) {
  my ($v, $rc, $np, $op) = @_;
  my $p = $op;
  if($op eq '') { $op = $precision; }
  if( ($np ne '') && ($np ne $op) ) {
    $v = "QLA_${np}${op}_${rc}($v)";
    $p = $np;
  }
  return ($v,$p);
}

sub print_prec_conv_macro($$$$$$) {
  my ($m1, $d, $m2, $t, $pd, $ps) = @_;
  if($pd eq '') { $pd = $precision; }
  if($ps eq '') { $ps = $precision; }
  if( $pd ne $ps ) {
    my $tt = &datatype_element_specific($t, $ps);
    my $tv = "_t";
    my $rc = $datatype_rc{$t};
    &open_brace;
    &print_def($tt, $tv);
    if($m1=~/_peq_/ || $m1=~/_meq_/) {
      #my ($dc, $pdc) = &make_cast($d, 'c', $ps, $pd);
      #&print_s_eqop_s($rc, $tv, $eqop_eq, "", $rc, $dc, "", $ps, $pdc);
      &print_s_eqop_s($rc, $tv, $eqop_eq, "", $rc, $d, "", $ps, $pd);
    }
    print QLA_SRC @indent, "${m1}${tv}$m2\n";
    #my ($tvc, $psc) = &make_cast($tv, 'c', $pd, $ps);
    #&print_s_eqop_s($rc, $d, $eqop_eq, "", $rc, $tvc, "", $pd, $psc);
    &print_s_eqop_s($rc, $d, $eqop_eq, "", $rc, $tv, "", $pd, $ps);
    &close_brace;
  } else {
    print QLA_SRC @indent, $m1, $d, $m2, "\n";
  }
}

1;
