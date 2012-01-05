#! /usr/bin/perl

# Scan test results and compare with header file to verify completeness
# Does not work with results of macro tests

# Arguments
$pc = shift;
$headerfile = shift;
# the rest of @ARGV is the result files
$pc = "" if($pc eq "0");

# Usage
if($#ARGV<0) { die "Usage $0 <pc> <headerfile> <testresultfiles>\n"; }

# Build hash table with module names and results
%result = (); %error = (); %tols = ();

for $testresultfile (@ARGV) {
  open(TESTRESULT,$testresultfile) || die "Can't open $testresultfile\n";
  while(<TESTRESULT>){
    # Parse line
    # Mostly OK/FAIL name
    # Exception OK MACRO name
    $prec = "";
    ($ok,$name,$diff,$tol) = split(" ",$_);
    if($name eq "MACRO") { ($ok,$macro,$prec,$name,$diff,$tol) = split(" ",$_); }
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
    if(!defined($result{$name}) || $ok ne "OK") {
      $result{$name} = $ok;
      $error{$name} = $diff;
      $tols{$name} = $tol;
      $prec{$name} = $prec;
    }
  }
  close(TESTRESULT);
}

open(HEADER,$headerfile) || die "Can't open $headerfile\n";

$begin_macros = 0;
while(<HEADER>){
    # Parse line
    ($void,$prototype) = split(" ",$_);
    # Look only at lines beginning with "void"
    $begin_macros = 1 if($prototype eq "BEGIN_MACROS");
    next if( ($void ne "void") && (($void ne "#define")||(!$begin_macros)) );
    # Parse prototype
    # Strip argument list, leaving specific function name
    ($name) = split('\(',$prototype);
    if($result{$name} eq ""){print "WARNING: untested $name\n";}
    elsif($result{$name} eq "FAIL"){
      $pname = $name;
      if($prec{$name} ne "") { $pname .= " " . $prec{$name}; }
      if($error{$name}<10*$tols{$name}) {
	printf "WARNING: FAILED %-34s with error %e\n", $pname, $error{$name};
      } else {
	printf "ERROR:   FAILED %-34s with error %e\n", $pname, $error{$name};
      }
    }
}

close(HEADER);

$n = keys %result;
print "Checked $n subroutines in $headerfile\n";
