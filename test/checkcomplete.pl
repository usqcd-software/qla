#! /usr/bin/perl

# Scan test results and compare with header file to verify completeness
# Does not work with results of macro tests

# Arguments
($testresultfile,$headerfile,$pc) = @ARGV;

# Usage
defined($testresultfile) && defined($headerfile) || 
    die "Usage $0 <testresultfile> <headerfile> \n";

open(TESTRESULT,$testresultfile) || die "Can't open $testresultfile\n";

# Build hash table with module names and results
$n = 0;
%result = (); %error = (); %tols = ();
while(<TESTRESULT>){
    # Parse line
    # Mostly OK/FAIL name
    # Exception OK MACRO name
    ($ok,$name,$diff,$tol) = split(" ",$_);
    if($name eq "MACRO"){next;}
    # Convert generic name to specific name
    # by adding color-precision label, if it was specified on the command line
    if($pc ne ""){
	@elements = split("_",$name);
	# If name has DF or FD, $pc should be only a color label
	if($elements[1] eq "DF" || $elements[1] eq "FD"){
	    $elements[1] .= $pc;
	}
	# Same for DQ or QD
	elsif($elements[1] eq "DQ" || $elements[1] eq "QD"){
	    $elements[1] .= $pc;
	}
	# Otherwise, $pc should be inserted as the full label
	else{
	    # e.g. with pc = F, converts QLA_R_eq_R to QLA_F_R_eq_R
	    splice(@elements,1,0,$pc);
	}
	$name = join("_",@elements);
    }
    if(!defined($result{$name})){
	$n++;
	$result{$name} = $ok;
	if($diff ne ""){
	    $error{$name} = $diff;
	}
	if($tol ne ""){
	    $tols{$name} = $tol;
	}
    }
    else{
	if($ok ne "OK"){
	    $result{$name} = $ok;
	    $error{$name} = $diff;
	    $tols{$name} = $tol;
	}
    }
}

close(TESTRESULT);

open(HEADER,$headerfile) || die "Can't open $headerfile\n";

while(<HEADER>){
    # Parse line
    ($void,$prototype) = split(" ",$_);
    # Look only at lines beginning with "void"
    if($void ne "void"){next;}
    # Parse prototype
    # Strip argument list, leaving specific function name
    ($name) = split('\(',$prototype);
    if($result{$name} eq ""){print "WARNING: untested $name\n";}
    elsif($result{$name} eq "FAIL"){
      if($error{$name}<10*$tols{$name}) {
	printf "WARNING: FAILED %-32s with error %e\n", $name, $error{$name};
      } else {
	printf "ERROR:   FAILED %-32s with error %e\n", $name, $error{$name};
      }
    }
}

close(HEADER);

print "Checked $n subroutines in $headerfile\n";
