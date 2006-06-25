######################################################################
# SciDAC Software Project
# BUILD_QLA Version 0.9
#
# expressions_gamma.pl
#
# Author: C. DeTar
# Date:   09/13/02
######################################################################
#
# Building blocks for arithmetic expressions involving gamma matrices
#
######################################################################
# Changes:
#
######################################################################
# Supporting files required:

require("variable_names.pl");
require("headers.pl");
require("formatting.pl");
require("datatypes.pl");

######################################################################
# A specific gamma matrix implementation
######################################################################
# Gamma matrix conventions
#
#
# gamma(XUP) 			eigenvectors	eigenvalue
# 	     0  0  0  i		( 1, 0, 0,-i)	 1
#            0  0  i  0		( 0, 1,-i, 0)	 1
#            0 -i  0  0		( 1, 0, 0,+i)	-1
#           -i  0  0  0		( 0, 1,+i ,0)	-1
#
# gamma(YUP)			eigenvectors	eigenvalue
# 	     0  0  0 -1		( 1, 0, 0,-1)	 1
#            0  0  1  0		( 0, 1, 1, 0)	 1
#            0  1  0  0		( 1, 0, 0, 1)	-1
#           -1  0  0  0		( 0, 1,-1, 0)	-1
#
# gamma(ZUP)			eigenvectors	eigenvalue
# 	     0  0  i  0		( 1, 0,-i, 0)	 1
#            0  0  0 -i		( 0, 1, 0,+i)	 1
#           -i  0  0  0		( 1, 0,+i, 0)	-1
#            0  i  0  0		( 0, 1, 0,-i)	-1
#
# gamma(TUP)			eigenvectors	eigenvalue
# 	     0  0  1  0		( 1, 0, 1, 0)	 1
#            0  0  0  1		( 0, 1, 0, 1)	 1
#            1  0  0  0		( 1, 0,-1, 0)	-1
#            0  1  0  0		( 0, 1, 0,-1)	-1
#
# gamma(FIVE) 			eigenvectors	eigenvalue
# 	     1  0  0  0
#            0  1  0  0
#            0  0 -1  0
#            0  0  0 -1

# identity matrix
@ident =  ( [ [ 1, 0],[ 0, 0],[ 0, 0],[ 0, 0] ],
	    [ [ 0, 0],[ 1, 0],[ 0, 0],[ 0, 0] ],
	    [ [ 0, 0],[ 0, 0],[ 1, 0],[ 0, 0] ],
	    [ [ 0, 0],[ 0, 0],[ 0, 0],[ 1, 0] ] );

# gamma_{x,y,z,t,5}
@gamma = (
	  [ [ [ 0, 0],[ 0, 0],[ 0, 0],[ 0, 1] ],
	    [ [ 0, 0],[ 0, 0],[ 0, 1],[ 0, 0] ],
	    [ [ 0, 0],[ 0,-1],[ 0, 0],[ 0, 0] ],
	    [ [ 0,-1],[ 0, 0],[ 0, 0],[ 0, 0] ] ],

	  [ [ [ 0, 0],[ 0, 0],[ 0, 0],[-1, 0] ],
	    [ [ 0, 0],[ 0, 0],[ 1, 0],[ 0, 0] ],
	    [ [ 0, 0],[ 1, 0],[ 0, 0],[ 0, 0] ],
	    [ [-1, 0],[ 0, 0],[ 0, 0],[ 0, 0] ] ],

	  [ [ [ 0, 0],[ 0, 0],[ 0, 1],[ 0, 0] ],
	    [ [ 0, 0],[ 0, 0],[ 0, 0],[ 0,-1] ],
	    [ [ 0,-1],[ 0, 0],[ 0, 0],[ 0, 0] ],
	    [ [ 0, 0],[ 0, 1],[ 0, 0],[ 0, 0] ] ],

	  [ [ [ 0, 0],[ 0, 0],[ 1, 0],[ 0, 0] ],
	    [ [ 0, 0],[ 0, 0],[ 0, 0],[ 1, 0] ],
	    [ [ 1, 0],[ 0, 0],[ 0, 0],[ 0, 0] ],
	    [ [ 0, 0],[ 1, 0],[ 0, 0],[ 0, 0] ] ],

 	  [ [ [ 1, 0],[ 0, 0],[ 0, 0],[ 0, 0] ],
	    [ [ 0, 0],[ 1, 0],[ 0, 0],[ 0, 0] ],
	    [ [ 0, 0],[ 0, 0],[-1, 0],[ 0, 0] ],
	    [ [ 0, 0],[ 0, 0],[ 0, 0],[-1, 0] ] ]
	 );

sub cmuladd(@@@) {
  my ($r, $a, $b) = @_;
  #printf("%g %g\n", $a->[0], $a->[1]);
  #printf("%g %g\n", $b->[0], $b->[1]);
  #printf("%g %g\n", $r->[0], $r->[1]);
  $r->[0] += $a->[0]*$b->[0] - $a->[1]*$b->[1];
  $r->[1] += $a->[0]*$b->[1] + $a->[1]*$b->[0];
  return @{$r};
}

sub mult_gamma(@@) {
  my ($a, $b) = @_;
  my @r = ();
  for(my $i=0; $i<4; $i++) {
    for(my $j=0; $j<4; $j++) {
      my @s = (0,0);
      for(my $k=0; $k<4; $k++) {
	@s = cmuladd([@s], $a->[$i][$k], $b->[$k][$j]);
	#printf("a %g %g\n", $a->[$i][$k][0], $a->[$i][$k][1]);
	#printf("b %g %g\n", $b->[$k][$j][0], $b->[$k][$j][1]);
	#printf("s %g %g\n", $s[0], $s[1]);
      }
      $r[$i][$j] = [ @s ];
      #printf("%g %g\n", $r[$row][$i][0], $r[$row][$i][1]);
    }
  }
  return @r;
}

sub get_gamma($) {
  my ($g) = @_;
  my @r = @ident;
  #printf("%i\n", $g);
  for(my $i=0; $i<4; $i++) {
    if($g & (1<<$i)) {
      #printf("%i\n", $i);
      @r = mult_gamma([@r], $gamma[$i]);
    }
  }
  return @r;
}

sub get_gamma_row($$) {
  my ($g, $row) = @_;
  my @t = get_gamma($g);
  my $col = -1;
  my $op = "";
  for(my $i=0; $i<4; $i++) {
    #printf("%g %g\n", $t[$row][$i][0], $t[$row][$i][1]);
    if($t[$row][$i][0]==1) {
      $col = $i;
      $op = 'c';
      break;
    }
    if($t[$row][$i][0]==-1) {
      $col = $i;
      $op = '-c';
      break;
    }
    if($t[$row][$i][1]==1) {
      $col = $i;
      $op = 'ic';
      break;
    }
    if($t[$row][$i][1]==-1) {
      $col = $i;
      $op = '-ic';
      break;
    }
  }
  return ($op, $col);
}

sub get_gamma_col($$) {
  my ($g, $col) = @_;
  my @t = get_gamma($g);
  my $row = -1;
  my $op = "";
  for(my $i=0; $i<4; $i++) {
    #printf("%g %g\n", $t[$row][$i][0], $t[$row][$i][1]);
    if($t[$i][$col][0]==1) {
      $row = $i;
      $op = 'c';
      break;
    }
    if($t[$i][$col][0]==-1) {
      $row = $i;
      $op = '-c';
      break;
    }
    if($t[$i][$col][1]==1) {
      $row = $i;
      $op = 'ic';
      break;
    }
    if($t[$i][$col][1]==-1) {
      $row = $i;
      $op = '-ic';
      break;
    }
  }
  return ($op, $row);
}

######################################################################
# Spin projection and reconstruction
######################################################################

# The projection takes the inner product with the eigenvector.
# Note a complex conjugate is required for projection

sub print_spproj_c_eqop_c_op_c {
    local($ic,$eqop,$op,$dest_s,$src1_s,$src2_s) = @_;
    local($dest_elem_value,$src1_elem_value,$src2_elem_value);
    local($macro);

    $dest_elem_value = &make_accessor(*dest_def,$def{'nc'},$ic,$dest_s,"","");
    $src1_elem_value = &make_accessor(*src1_def,$def{'nc'},$ic,$src1_s,"","");
    $src2_elem_value = &make_accessor(*src1_def,$def{'nc'},$ic,$src2_s,"","");

    $macro = $carith2{$eqop.$op};
    #defined($macro) || die "no carith2 macro for $eqop$op\n";
    if(defined($macro)) {
      print QLA_SRC @indent,"$macro($dest_elem_value,\n";
      print QLA_SRC @indent,"      $src1_elem_value,$src2_elem_value);\n";
    } else {
      $macro = $carith1{$eqop.$op};
      defined($macro) || die "no carith2 or carith1 macro for $eqop$op\n";
      print QLA_SRC @indent,"$macro($dest_elem_value,$src1_elem_value);\n";
    }
}

sub print_spproj_dirs {
  local($ic,$eqop,$dir,$op0,$src01_s,$src02_s,$op1,$src11_s,$src12_s) = @_;

  &print_spproj_c_eqop_c_op_c($ic,$eqop,$op0,0,$src01_s,$src02_s);
  &print_spproj_c_eqop_c_op_c($ic,$eqop,$op1,1,$src11_s,$src12_s);
}

sub print_val_assign_spproj_dirs {
  local(*dest_def, *src1_def, $sign, $dir, $eqop) = @_;
  if($sign==$sign_PLUS) {
    &print_spproj_dirs($ic,$eqop,$dir_X,'c+ic',0,3,'c+ic',1,2) if($dir==$dir_X);
    &print_spproj_dirs($ic,$eqop,$dir_Y,'c-c' ,0,3,'c+c' ,1,2) if($dir==$dir_Y);
    &print_spproj_dirs($ic,$eqop,$dir_Z,'c+ic',0,2,'c-ic',1,3) if($dir==$dir_Z);
    &print_spproj_dirs($ic,$eqop,$dir_T,'c+c' ,0,2,'c+c' ,1,3) if($dir==$dir_T);
    &print_spproj_dirs($ic,$eqop,$dir_S,'c'   ,0,0,'c'   ,1,1) if($dir==$dir_S);
  } else {
    &print_spproj_dirs($ic,$eqop,$dir_X,'c-ic',0,3,'c-ic',1,2) if($dir==$dir_X);
    &print_spproj_dirs($ic,$eqop,$dir_Y,'c+c' ,0,3,'c-c' ,1,2) if($dir==$dir_Y);
    &print_spproj_dirs($ic,$eqop,$dir_Z,'c-ic',0,2,'c+ic',1,3) if($dir==$dir_Z);
    &print_spproj_dirs($ic,$eqop,$dir_T,'c-c' ,0,2,'c-c' ,1,3) if($dir==$dir_T);
    &print_spproj_dirs($ic,$eqop,$dir_S,'c'   ,2,2,'c'   ,3,3) if($dir==$dir_S);
  }
}

sub print_sprecon_c_eqop_op_c {
    local($ic,$maxic,$eqop,$op,$dest_s,$src1_s) = @_;

    local($dest_elem_value,$src1_elem_value);
    local($macro);

    $dest_elem_value = &make_accessor(*dest_def,$def{'nc'},$ic,$dest_s,"","");
    $src1_elem_value = &make_accessor(*src1_def,$def{'nc'},$ic,$src1_s,"","");

    if( $op eq '0' ) {
      if( ($eqop eq "eq") || ($eqop eq "eqm") ) {
	$macro = $carith1{'eqr'};
	print QLA_SRC @indent, "$macro($dest_elem_value,0.0);\n";
      }
    } else {
      $macro = $carith1{$eqop.$op};
      defined($macro) || die "no carith1 macro for $eqop$op.\n";
      print QLA_SRC @indent,"$macro($dest_elem_value,$src1_elem_value);\n";
    }
}

sub print_sprecon_dirs {
    local($ic,$maxic,$eqop,$dir,$op0,$op1,$op2,$op3,$h0,$h1,$h2,$h3) = @_;

    &print_sprecon_c_eqop_op_c($ic,$maxic,$eqop,$op0,0,$h0);
    &print_sprecon_c_eqop_op_c($ic,$maxic,$eqop,$op1,1,$h1);
    &print_sprecon_c_eqop_op_c($ic,$maxic,$eqop,$op2,2,$h2);
    &print_sprecon_c_eqop_op_c($ic,$maxic,$eqop,$op3,3,$h3);
}

sub print_val_assign_sprecon_dirs {
  local(*dest_def, *src1_def, $sign, $dir, $eqop) = @_;
  if($sign==$sign_PLUS) {
    &print_sprecon_dirs($ic,$maxic,$eqop,$dir_X, 'c', 'c', '-ic', '-ic',
			0, 1, 1, 0) if($dir==$dir_X);
    &print_sprecon_dirs($ic,$maxic,$eqop,$dir_Y, 'c', 'c', 'c'  , '-c',
			0, 1, 1, 0) if($dir==$dir_Y);
    &print_sprecon_dirs($ic,$maxic,$eqop,$dir_Z, 'c', 'c', '-ic', 'ic',
			0, 1, 0, 1) if($dir==$dir_Z);
    &print_sprecon_dirs($ic,$maxic,$eqop,$dir_T, 'c', 'c', 'c'  , 'c',
			0, 1, 0, 1) if($dir==$dir_T);
    &print_sprecon_dirs($ic,$maxic,$eqop,$dir_S, 'c', 'c', '0'  , '0',
			0, 1, 0, 1) if($dir==$dir_S);
  } else {
    &print_sprecon_dirs($ic,$maxic,$eqop,$dir_X, 'c', 'c', 'ic' , 'ic',
			0, 1, 1, 0) if($dir==$dir_X);
    &print_sprecon_dirs($ic,$maxic,$eqop,$dir_Y, 'c', 'c', '-c' , 'c',
			0, 1, 1, 0) if($dir==$dir_Y);
    &print_sprecon_dirs($ic,$maxic,$eqop,$dir_Z, 'c', 'c', 'ic' , '-ic',
			0, 1, 0, 1) if($dir==$dir_Z);
    &print_sprecon_dirs($ic,$maxic,$eqop,$dir_T, 'c', 'c', '-c' , '-c',
			0, 1, 0, 1) if($dir==$dir_T);
    &print_sprecon_dirs($ic,$maxic,$eqop,$dir_S, '0', '0', 'c'  , 'c',
			0, 1, 0, 1) if($dir==$dir_S);

  }
}

sub print_spin_dir {
  local($sign, $dir, $eqop, $spfunc) = @_;

  print QLA_SRC @indent,"case $dir: {\n";
  &open_block();
  &$spfunc($sign, $dir, $eqop);
  &close_block();
  print QLA_SRC @indent,"} break;\n";
}

sub print_val_assign_spin {
  local($eqop,$mu,$sign,$spfunc) = @_;

  print QLA_SRC @indent,"if($sign==$sign_PLUS) {\n";

  # Up directions

  &open_block();
  print QLA_SRC @indent,"switch($mu) {\n";

  for($i=0; $i<5; $i++) {
    &print_spin_dir($sign_PLUS, $i, $eqop, $spfunc);
  }

  &open_block();
  &close_brace();
  &close_brace();

  print QLA_SRC @indent,"else {\n";

  # Down directions

  &open_block();
  print QLA_SRC @indent,"switch($mu) {\n";

  for($i=0; $i<5; $i++) {
    &print_spin_dir($sign_MINUS, $i, $eqop, $spfunc);
  }

  &open_block();
  &close_brace();
  &close_brace();
}

######################################################################
# Left and right multiplication by gamma matrices
######################################################################

sub print_mult_gamma_c_eqop_op_c {
    local($eqop,$op,$ic,$jc,$dest_is,$dest_js,$src1_is,$src1_js) = @_;

    $dest_elem_value = &make_accessor(*dest_def,$def{'nc'},
				      $ic,$dest_is,$jc,$dest_js);
    $src1_elem_value = &make_accessor(*src1_def,$def{'nc'},
				      $ic,$src1_is,$jc,$src1_js);
    local($macro) = $carith1{$eqop.$op};
    defined($macro) || die "No carith1 macro for $macro\n";
    print QLA_SRC @indent,"$macro($dest_elem_value,$src1_elem_value);\n";
}

sub print_val_assign_gamma_times_dirs {
  local(*dest_def, *src1_def, $eqop, $leftright, $g) = @_;

  local($ic,$is,$jc,$js) = &get_color_spin_indices(*dest_def);
  local($maxic,$maxis,$maxjc,$maxjs) = @dest_def{'mc','ms','nc','ns'};

  if($leftright eq "right") {

    &print_int_def($ic);
    &print_int_def($is);
    &print_int_def($jc);
    if($ic ne "") { &open_iter($ic,$maxic); }
    if($is ne "") { &open_iter($is,$maxis); }
    if($jc ne "") { &open_iter($jc,$maxjc); }

    for($dest_s=0; $dest_s<4; $dest_s++) {
      ($opt, $jst) = get_gamma_col($g, $dest_s);
      &print_mult_gamma_c_eqop_op_c($eqop,$opt,$ic,$jc,$is,$dest_s,$is,$jst);
    }

    if($jc ne "") { &close_iter($jc); }
    if($is ne "") { &close_iter($is); }
    if($ic ne "") { &close_iter($ic); }

  } else {  # left

    &print_int_def($ic);
    &print_int_def($jc);
    &print_int_def($js);
    if($ic ne "") { &open_iter($ic,$maxic); }
    if($jc ne "") { &open_iter($jc,$maxjc); }
    if($js ne "") { &open_iter($js,$maxjs); }

    for($dest_s=0; $dest_s<4; $dest_s++) {
      ($opt, $ist) = get_gamma_row($g, $dest_s);
      &print_mult_gamma_c_eqop_op_c($eqop,$opt,$ic,$jc,$dest_s,$js,$ist,$js);
    }

    if($js ne "") { &close_iter($js); }
    if($jc ne "") { &close_iter($jc); }
    if($ic ne "") { &close_iter($ic); }

  }
}

sub print_gamma_times {
  local($eqop, $leftright, $g, $gfunc) = @_;

  print QLA_SRC @indent,"case $g: {\n";
  &open_block();
  &$gfunc($eqop, $leftright, $g);
  &close_block();
  print QLA_SRC @indent,"} break;\n";
}

sub print_val_assign_gamma_times {
  local($eqop,$mu,$leftright,$gfunc) = @_;

  print QLA_SRC @indent,"switch($mu) {\n";

  for($i=0; $i<16; $i++) {
    print_gamma_times($eqop, $leftright, $i, $gfunc);
  }

  print QLA_SRC @indent,"default:\n";
  &open_block();
  print QLA_SRC @indent,"printf(\"Gamma matrix %d not supported\\n\",$mu);\n";

  &close_brace();
}

1;
