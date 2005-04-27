######################################################################
# SciDAC Software Project
# BUILD_QLA Version 0.9
#
# indirection.pl
#
# Author: C. DeTar
# Date:   09/13/02
######################################################################
#
# Defines tables of vector indexing patterns for QLA operations
# and their attributes
#
######################################################################
# Changes:
#
######################################################################
# Supporting files required:

######################################################################
# Here is an example of a scalar unary function prototype:

#  QLA_F3_M_peq_M(restrict StaggeredPropagatorF3 *r, StaggeredPropagatorF3 *a);

# This function does  *r += *a

# The vector equivalent treats r and a as arrays with indexing from 1 to n,
# resulting in the usage

#  QLA_F3_M_vpeq_M(r,a,n);
#    to get r[i] += a[i] for i = 1...n

#  The "v" prefix on the replacement operator distinguishes this case.

# Indirect addressing is accomplished through indexing and/or pointers
# There are several variants.  The names are constructed by attaching
# a prefix to the replacement operator or to the operand abbreviations.
# Thus we have, for example

#  QLA_F3_xM_peq_M(r,indexr,a,n);
#    to get r[indexr[i]] += a[i] for i = 1...n

# This gives destination indexing.  Similarly for source indexing
#  QLA_F3_M_peq_xM(r,a,indexa,n);
#    to get r[i] += a[indexa[i]] for i = 1...n

# We also have gang-indexing through
#  QLA_F3_M_xpeq_M(r,a,index,n);
#    to get r[index[i]] += a[index[i]] for i = 1...n

# Note that in this case the "x" is prefix to the replacement operator.

# Pointers apply to the source operand in the vector case and the
# gang-indexed case
#  QLA_F3_M_vpeq_pM(r,a,n)
#    to get r[i] += *(a[i]) for i = 1...n
#  QLA_F3_M_xpeq_pM(r,a,index,n)
#    to get r[index[i]] += *(a[index[i]]) for i = 1...n

######################################################################

$index_pfx = 'x';
$pointer_pfx = 'p';
$vector_pfx = 'v';

@ind_names = (
		      'scalar',
		      'vector',
		      'gang_index',
		      'dest_index',
		      'src1_index',
		      'src2_index',
		      'src3_index',
		      'dest_src1_index',
		      'dest_src2_index',
		      'dest_src3_index',
		      'src1_src2_index',
		      'src1_src3_index',
		      'src2_src3_index',
		      'dest_src1_src2_index',
		      'dest_src1_src3_index',
		      'dest_src2_src3_index',
		      'src1_src2_src3_index',
		      'dest_src1_src2_src3_index',
		      'vector_src1_ptr',
		      'vector_src2_ptr',
		      'vector_src3_ptr',
		      'vector_src1_src2_ptr',
		      'vector_src1_src3_ptr',
		      'vector_src2_src3_ptr',
		      'vector_src1_src2_src3_ptr',
		      'gang_index_src1_ptr',
		      'gang_index_src2_ptr',
		      'gang_index_src3_ptr',
		      'gang_index_src1_src2_ptr',
		      'gang_index_src1_src3_ptr',
		      'gang_index_src2_src3_ptr',
		      'gang_index_src1_src2_src3_ptr',
		      );

# Scalar variant
$ind_scalar = 'scalar';

# Gang index
$ind_gang_index = 'gang_index';

######################################################################
# Build subsets of indexing variants
######################################################################

#------------------------------------------
# Full binary operation  
#------------------------------------------
# They do not mention src3

@ind_binary_list = ();
foreach $indexing ( @ind_names ){
    if($indexing =~ /src3/){next;}
    push(@ind_binary_list,$indexing);
}

#------------------------------------------
# Binary operation with src1 unindexed
#------------------------------------------
# They do not mention src1 or src3

@ind_binary_src1_const_list = ();
foreach $indexing ( @ind_names ){
    if($indexing =~ /src3/ || $indexing =~ /src1/){next;}
    push(@ind_binary_src1_const_list,$indexing);
}

#------------------------------------------
# Full unary operation
#------------------------------------------
# They do not mention src2 or src3

@ind_unary_list = ();
foreach $indexing ( @ind_names ){
    if($indexing =~ /src3/ || $indexing =~ /src2/){next;}
    push(@ind_unary_list,$indexing);
}

#------------------------------------------
# Binary with nonindexed lhs (e.g. inner products)
#------------------------------------------
# They do not mention dest or src3

@ind_binary_reduction_list = ();
foreach $indexing ( @ind_names ){
    if($indexing =~ /src3/ || $indexing =~ /dest/){next;}
    push(@ind_binary_reduction_list,$indexing);
}

#------------------------------------------
# Ternary operation with src1 unindexed
#------------------------------------------
# They do not mention src1

@ind_ternary_src1_const_list = ();
foreach $indexing ( @ind_names ){
    if($indexing =~ /src1/){next;}
    push(@ind_ternary_src1_const_list,$indexing);
}

#------------------------------------------
# Nonindexed rhs (e.g. fills)
#------------------------------------------

@ind_fill_list = (
			  'scalar',
			  'vector',
			  'gang_index',
			  );

#------------------------------------------
# Unary with nonindexed lhs (e.g. norms)
#------------------------------------------

@ind_unary_reduction_list = (
				     'scalar',
				     'vector',
				     'gang_index',
				     'vector_src1_ptr',
				     'gang_index_src1_ptr'
				     );


######################################################################
# Tables of prefixes for components of function name
######################################################################

#------------------------------------------
# Assignment operator prefixes
#------------------------------------------
# Uses $index_pfx for all gang indexing
# Uses $vector_pfx for all vector indexing
# Otherwise null

%ind_assignop_prefix = ();
foreach $indexing ( @ind_names ){
    if($indexing =~ /gang_index/){
	$ind_assignop_prefix{$indexing} = $index_pfx;
    }
    elsif($indexing =~ /vector/){
	$ind_assignop_prefix{$indexing} = $vector_pfx;
    }
}    

#------------------------------------------
# index prefixes
#------------------------------------------
# Uses $index_pfx for all types with "arg = dest, src1, ..." and "ptr"

%ind_idx_prefix = ();
foreach $arg ( 'dest','src1','src2','src3' ){
    foreach $indexing ( @ind_names ){
	if($indexing =~ /gang_index/){next;}
	if($indexing =~ /$arg/ && $indexing =~ /index/){
	    $ind_idx_prefix{"$arg,$indexing"} = $index_pfx;
	}
    }
}

#------------------------------------------
# pointer prefixes
#------------------------------------------
# Uses $pointer_pfx for all types with "arg = dest, src1, ..." and "ptr"

%ind_ptr_prefix = ();
foreach $arg ( 'dest','src1','src2','src3' ){
    foreach $indexing ( @ind_names ){
	if($indexing =~ /$arg/ && $indexing =~ /ptr/){
	    $ind_ptr_prefix{"$arg,$indexing"} = $pointer_pfx;
	}
    }
}

######################################################################
# Tables of requirements for the argument list
######################################################################

#------------------------------------------
# types needing an index dimension argument
#------------------------------------------
# These types have "vector" or "index" in the name

%ind_needs_dim = ();
foreach $indexing ( @ind_names ){
    if($indexing =~ /vector/ || $indexing =~ /index/){
	$ind_needs_dim{$indexing} = 1;
    }
    else{
	$ind_needs_dim{$indexing} = 0;
    }
}

#------------------------------------------
# types needing a gang index argument
#------------------------------------------
# These types have "gang_index" in the name

%ind_needs_gang_index = ();
foreach $indexing ( @ind_names ){
    if($indexing =~ /gang_index/){
	$ind_needs_gang_index{$indexing} = 1;
    }
    else{
	$ind_needs_gang_index{$indexing} = 0;
    }
}

1;
