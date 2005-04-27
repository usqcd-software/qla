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
# 	     0  0  0  i		( 1, 0, 0,-i)	+1
#            0  0  i  0		( 0, 1,-i, 0)	+1
#            0 -i  0  0		( 1, 0, 0,+i)	-1
#           -i  0  0  0		( 0, 1,+i ,0)	-1
#
# gamma(YUP)			eigenvectors	eigenvalue
# 	     0  0  0  1		( 1, 0, 0, 1)	 1
#            0  0 -1  0		( 0, 1,-1, 0)	 1
#            0 -1  0  0		( 1, 0, 0,-1)	-1
#            1  0  0  0		( 0, 1, 1, 0)	-1
#
# gamma(ZUP)			eigenvectors	eigenvalue
# 	     0  0  i  0		( 1, 0,-i, 0)	+1
#            0  0  0 -i		( 0, 1, 0,+i)	+1
#           -i  0  0  0		( 1, 0,+i, 0)	-1
#            0  i  0  0		( 0, 1, 0,-i)	-1
#
# gamma(TUP)			eigenvectors	eigenvalue
# 	     0  0  1  0		( 1, 0, 1, 0)	+1
#            0  0  0  1		( 0, 1, 0, 1)	+1
#            1  0  0  0		( 1, 0,-1, 0)	-1
#            0  1  0  0		( 0, 1, 0,-1)	-1
#
# gamma(FIVE) 			eigenvectors	eigenvalue
# 	     1  0  0  0
#            0  1  0  0
#            0  0 -1  0
#            0  0  0 -1

######################################################################
# Spin projection
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
    defined($macro) || die "no carith2 macro for $eqop$op\n";

    print QLA_SRC @indent,"$macro($dest_elem_value,";
    print QLA_SRC @indent,"$src1_elem_value,$src2_elem_value)\n";
}

sub print_spproj_dir {
    local($ic,$eqop,$dir,$op0,$src01_s,$src02_s,$op1,$src11_s,$src12_s) = @_;

    print QLA_SRC @indent,"case $dir:\n";
    &open_block();
    &open_iter($ic,$maxic);
    &print_spproj_c_eqop_c_op_c($ic,$eqop,$op0,0,$src01_s,$src02_s);
    &print_spproj_c_eqop_c_op_c($ic,$eqop,$op1,1,$src11_s,$src12_s);
    &close_iter($ic);
    print QLA_SRC @indent,"break;\n";
    &close_block();
}

sub print_val_assign_spproj {
    local(*dest_def,$eqop,*src1_def,$mu,$sign) = @_;

    $ic = &get_row_color_index(*src1_def);
    &print_int_def($ic);

    $maxic = $src1_def{'mc'};

    print QLA_SRC @indent,"if($sign==$sign_PLUS){\n";

    # Up directions

    &open_block();
    print QLA_SRC @indent,"switch($mu){\n";

    &print_spproj_dir($ic,$eqop,$dir_X,'c+ic',0,3,'c+ic',1,2);
    &print_spproj_dir($ic,$eqop,$dir_Y,'c+c' ,0,3,'c-c' ,1,2);
    &print_spproj_dir($ic,$eqop,$dir_Z,'c+ic',0,2,'c-ic',1,3);
    &print_spproj_dir($ic,$eqop,$dir_T,'c+c' ,0,2,'c+c' ,1,3);

    &open_block();
    &close_brace();
    &close_brace();

    print QLA_SRC @indent,"else{\n";

    # Down directions

    &open_block();
    print QLA_SRC @indent,"switch($mu){\n";

    &print_spproj_dir($ic,$eqop,$dir_X,'c-ic',0,3,'c-ic',1,2);
    &print_spproj_dir($ic,$eqop,$dir_Y,'c-c' ,0,3,'c+c' ,1,2);
    &print_spproj_dir($ic,$eqop,$dir_Z,'c-ic',0,2,'c+ic',1,3);
    &print_spproj_dir($ic,$eqop,$dir_T,'c-c' ,0,2,'c-c' ,1,3);

    &open_block();
    &close_brace();
    &close_brace();
}

######################################################################
# Spin reconstruction
######################################################################

sub print_sprecon_c_eqop_op_c {
    local($ic,$maxic,$eqop,$op,$dest_s,$src1_s) = @_;

    local($dest_elem_value,$src1_elem_value);
    local($macro);

    $dest_elem_value = &make_accessor(*dest_def,$def{'nc'},$ic,$dest_s,"","");
    $src1_elem_value = &make_accessor(*src1_def,$def{'nc'},$ic,$src1_s,"","");

    $macro = $carith1{$eqop.$op};
    defined($macro) || die "no carith1 macro for $eqop$op.\n";

    print QLA_SRC @indent,"$macro($dest_elem_value,$src1_elem_value)\n";
}

sub print_sprecon_dir {
    local($ic,$maxic,$eqop,$dir,$op0,$op1,$op2,$op3,$h0,$h1,$h2,$h3) = @_;

    print QLA_SRC @indent,"case $dir:\n";
    &open_block();
    &open_iter($ic,$maxic);
    &print_sprecon_c_eqop_op_c($ic,$maxic,$eqop,$op0,0,$h0);
    &print_sprecon_c_eqop_op_c($ic,$maxic,$eqop,$op1,1,$h1);
    &print_sprecon_c_eqop_op_c($ic,$maxic,$eqop,$op2,2,$h2);
    &print_sprecon_c_eqop_op_c($ic,$maxic,$eqop,$op3,3,$h3);
    &close_iter($ic);
    print QLA_SRC @indent,"break;\n";
    &close_block();
}

sub print_val_assign_sprecon {
    local(*dest_def,$eqop,*src1_def,$mu,$sign) = @_;

    $ic = &get_row_color_index(*src1_def);
    &print_int_def($ic);

    $maxic = $src1_def{'mc'};

    print QLA_SRC @indent,"if($sign==$sign_PLUS){\n";

    # Up directions

    &open_block();
    print QLA_SRC @indent,"switch($mu){\n";

    &print_sprecon_dir($ic,$maxic,$eqop,$dir_X, 'c', 'c', '-ic', '-ic',
		       0, 1, 1, 0);
    &print_sprecon_dir($ic,$maxic,$eqop,$dir_Y, 'c', 'c', '-c' , 'c',
		       0, 1, 1, 0);
    &print_sprecon_dir($ic,$maxic,$eqop,$dir_Z, 'c', 'c', '-ic', 'ic',
		       0, 1, 0, 1);
    &print_sprecon_dir($ic,$maxic,$eqop,$dir_T, 'c', 'c', 'c'  , 'c',
		       0, 1, 0, 1);

    &open_block();
    &close_brace();
    &close_brace();

    print QLA_SRC @indent,"else{\n";

    # Down directions

    &open_block();
    print QLA_SRC @indent,"switch($mu){\n";

    &print_sprecon_dir($ic,$maxic,$eqop,$dir_X, 'c', 'c', 'ic' , 'ic',
		       0, 1, 1, 0);
    &print_sprecon_dir($ic,$maxic,$eqop,$dir_Y, 'c', 'c', 'c'  , '-c',
		       0, 1, 1, 0);
    &print_sprecon_dir($ic,$maxic,$eqop,$dir_Z, 'c', 'c', 'ic' , '-ic',
		       0, 1, 0, 1);
    &print_sprecon_dir($ic,$maxic,$eqop,$dir_T, 'c', 'c', '-c' , '-c',
		       0, 1, 0, 1);

    &open_block();
    &close_brace();
    &close_brace();

}

######################################################################
# Left and right multiplication by gamma matrices
######################################################################

sub print_lmult_gamma_c_eqop_op_c {
    local(*sp_common,$dest_s,$op,$src1_s,$ic,$jc,$js) = @_;

    local($ic,$maxic,$is,$maxis,$jc,$maxjc,$js,$maxjs,$eqop) = @sp_common;

    $dest_elem_value = &make_accessor(*dest_def,$def{'nc'},
				      $ic,$dest_s,$jc,$js);
    $src1_elem_value = &make_accessor(*src1_def,$def{'nc'},
				      $ic,$src1_s,$jc,$js);
    local($macro) = $carith1{$eqop.$op};
    defined($macro) || die "No carith1 macro for $macro\n";
    print QLA_SRC @indent,"$macro($dest_elem_value,$src1_elem_value)\n";
}

sub print_rmult_gamma_c_eqop_op_c {
    local(*sp_common,$dest_s,$op,$src1_s,$ic,$is,$jc) = @_;

    local($ic,$maxic,$is,$maxis,$jc,$maxjc,$js,$maxjs,$eqop) = @sp_common;

    $dest_elem_value = &make_accessor(*dest_def,$def{'nc'},
				      $ic,$is,$jc,$dest_s);
    $src1_elem_value = &make_accessor(*src1_def,$def{'nc'},
				      $ic,$is,$jc,$src1_s);
    local($macro) = $carith1{$eqop.$op};
    defined($macro) || die "No carith1 macro for $macro\n";
    print QLA_SRC @indent,"$macro($dest_elem_value,$src1_elem_value)\n";
}

sub print_lmult_gamma_dir {
    local(*sp_common,$dir,
	  $op0,$is0,$op1,$is1,$op2,$is2,$op3,$is3) = @_;

    local($ic,$maxic,$is,$maxis,$jc,$maxjc,$js,$maxjs,$eqop) = @sp_common;

    print QLA_SRC @indent,"case $dir:\n";
    &open_block();

    if($ic ne ""){&open_iter($ic,$maxic);}
    if($jc ne ""){&open_iter($jc,$maxjc);}
    if($js ne ""){&open_iter($js,$maxjs);}

    &print_lmult_gamma_c_eqop_op_c(*sp_common,0,$op0,$is0,$ic,$jc,$js);
    &print_lmult_gamma_c_eqop_op_c(*sp_common,1,$op1,$is1,$ic,$jc,$js);
    &print_lmult_gamma_c_eqop_op_c(*sp_common,2,$op2,$is2,$ic,$jc,$js);
    &print_lmult_gamma_c_eqop_op_c(*sp_common,3,$op3,$is3,$ic,$jc,$js);

    if($ic ne ""){&close_iter($ic);}
    if($jc ne ""){&close_iter($jc);}
    if($js ne ""){&close_iter($js);}

    print QLA_SRC @indent,"break;\n";
    &close_block();
}

sub print_rmult_gamma_dir {
    local(*sp_common,$dir,
	  $op0,$js0,$op1,$js1,$op2,$js2,$op3,$js3) = @_;

    local($ic,$maxic,$is,$maxis,$jc,$maxjc,$js,$maxjs,$eqop) = @sp_common;

    print QLA_SRC @indent,"case $dir:\n";
    &open_block();

    if($ic ne ""){&open_iter($ic,$maxic);}
    if($is ne ""){&open_iter($is,$maxis);}
    if($jc ne ""){&open_iter($jc,$maxjc);}

    &print_rmult_gamma_c_eqop_op_c(*sp_common,0,$op0,$js0,$ic,$is,$jc);
    &print_rmult_gamma_c_eqop_op_c(*sp_common,1,$op1,$js1,$ic,$is,$jc);
    &print_rmult_gamma_c_eqop_op_c(*sp_common,2,$op2,$js2,$ic,$is,$jc);
    &print_rmult_gamma_c_eqop_op_c(*sp_common,3,$op3,$js3,$ic,$is,$jc);

    if($ic ne ""){&close_iter($ic);}
    if($is ne ""){&close_iter($is);}
    if($jc ne ""){&close_iter($jc);}

    print QLA_SRC @indent,"break;\n";
    &close_block();
}

sub print_val_assign_gamma_times {
    local(*dest_def,$eqop,*srce_def,$mu,$leftright) = @_;

    local($ic,$is,$jc,$js) = &get_color_spin_indices(*dest_def);
    local($maxic,$maxis,$maxjc,$maxjs) = @dest_def{'mc','ms','nc','ns'};

    &print_int_def($ic);
    if($leftright eq "right"){&print_int_def($is);}
    &print_int_def($jc);
    if($leftright eq "left"){&print_int_def($js);}

    local(@sp_common) = ($ic,$maxic,$is,$maxis,$jc,$maxjc,$js,$maxjs,$eqop);

    if($leftright eq "left"){
	print QLA_SRC @indent,"switch($mu){\n";
	
	&print_lmult_gamma_dir(*sp_common,$dir_X,
			       'ic' ,3,'ic' ,2,'-ic',1,'-ic',0);
	&print_lmult_gamma_dir(*sp_common,$dir_Y,
			       'c'  ,3,'-c' ,2,'-c' ,1,'c'  ,0);
	&print_lmult_gamma_dir(*sp_common,$dir_Z,
			       'ic' ,2,'-ic',3,'-ic',0,'ic' ,1);
	&print_lmult_gamma_dir(*sp_common,$dir_T,
			       'c'  ,2,'c'  ,3,'c'  ,0,'c'  ,1);
	&print_lmult_gamma_dir(*sp_common,$dir_5,
			       'c'  ,0,'c'  ,1,'-c' ,2,'-c' ,3);
	
	print QLA_SRC @indent,"default:\n";
	&open_block();
	print QLA_SRC @indent,"printf(\"Gamma matrix %d not supported\\n\",$mu);\n";

	&close_brace();
	
    }
    elsif($leftright eq "right"){
	print QLA_SRC @indent,"switch($mu){\n";
	
	&print_rmult_gamma_dir(*sp_common,$dir_X,
			       '-ic',3,'-ic',2,'ic' ,1,'ic' ,0);
	&print_rmult_gamma_dir(*sp_common,$dir_Y,
			       'c'  ,3,'-c' ,2,'-c' ,1,'c'  ,0);
	&print_rmult_gamma_dir(*sp_common,$dir_Z,
			       '-ic',2,'ic' ,3,'ic' ,0,'-ic',1);
	&print_rmult_gamma_dir(*sp_common,$dir_T,
			       'c'  ,2,'c'  ,3,'c'  ,0,'c'  ,1);
	&print_rmult_gamma_dir(*sp_common,$dir_5,
			       'c'  ,0,'c'  ,1,'-c' ,2,'-c' ,3);
	
	print QLA_SRC @indent,"default:\n";
	&open_block();
	print QLA_SRC @indent,"printf(\"Gamma matrix %d not supported\\n\",$mu);\n";

	&close_brace();
	
    }
    else{
	die "Bad value of leftright: $leftright\n";
    }
}
1;
