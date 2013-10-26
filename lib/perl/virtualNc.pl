#!/usr/bin/perl

($infile, $outfile) = @ARGV;

($def = $outfile) =~ s|.*/(qla_.*).h|_$1_H|;
$def = uc $def;
($p = $outfile) =~ s|.*qla_([dfq]+).*|$1|;
$P = uc $p;
($P0 = $P) =~ s/(.).*/$1/;
($P1 = $P) =~ s/.*(.)/$1/;

sub get_name_args($) {
  ($prot) = @_;

  $len = length($prot);
  $par = 0;
  for($i=$len-1; $i>0; $i--) {
    if(substr($prot,$i,1) eq ')') {
      if($par==0) { $j = $i; }
      ++$par;
    }
    if(substr($prot,$i,1) eq '(') {
      --$par;
      last if($par==0);
    }
  }
  $args = substr($prot,$i+1,$j-$i-1);
  $prot = substr($prot,0,$i);
  $name = $prot;
  $name =~ s/.*[\s]+[*]*([^\s]+)[\s]*/$1/;
  return($name,$args);
}

sub count_paren($) {
  ($string) = @_;
  $string = "dummy".$string."dummy";
  my($op, $cp) = (0,0);
  my(@t);
  @t = split(/\(/, $string);
  $op = $#t;
  @t = split(/\)/, $string);
  $cp = $#t;
  return ($op, $cp);
}

sub get_arg_lists($$) {
  ($args, $name) = @_;
  my(@list, $op, $cp);
  my($pl) = 0;
  for(split(',',$args)) {
    $arg = $_;
    ($op, $cp) = count_paren($_);
    $pl += $op - $cp;
    if($pl==0) {
      $arg =~ s/.*[^\w]([\w]+)[^\w]*$/$1/;
      if($arg ne "void") { push @list, $arg; }
    }
  }
  # remove initial 'nc'
  shift @list;
  @olist = @list;

  if( ($name=~/spproj/) || ($name=~/sprecon/)  || ($name=~/colorvec/) ||
      ($name=~/elem/)   || ($name=~/spintrace/) || ($name=~/antiherm/) ||
      ($name=~/inverse/) || ($name=~/invsqrt/)  || ($name=~/invsqrtPH/) ||
      ($name=~/times_nV/) || ($name=~/P_times/)  || ($name=~/Pa_times/) ||
      ($name=~/times_npV/)
      ) {
    $oname = $name;
    unshift @olist, '1';
  } else {
    $hasspin = 0;
    @on = ();
    $an = 0;
    for(split('_',$name)) {
      $t = $_;
      /^[p]?[HDP][a]?$/ && $hasspin++;
      /^[hdp][a]?$/ && $hasspin++;
      /^[p]?[VM][a]?$/ && do {
	$t =~ s/[VM]/C/;
	($ppn = $name) =~ s/.*QLA_([DFQ]+).*/$1/;
	if($an==0) { ($pn = $ppn) =~ s/(.).*/$1/; }
	else { ($pn = $ppn) =~ s/.*(.)/$1/; }
	$ct = "QLA_${pn}_Complex *";
	/^p/ && ($ct .= "*");
	$olist[$an] = "($ct)($olist[$an])";
      };
      /^[vm][a]?$/ && do {
	$t =~ s/[vm]/c/;
	($ppn = $name) =~ s/.*QLA_([DFQ]+).*/$1/;
	if($an==0) { ($pn = $ppn) =~ s/(.).*/$1/; }
	else { ($pn = $ppn) =~ s/.*(.)/$1/; }
	$ct = "QLA_${pn}_Complex *";
	/^p/ && ($ct .= "*");
	$olist[$an] = "($ct)($olist[$an])";
      };
      /^[p]?[ISRCVHDMP][a]?$/ && $an++;
      /^[srcvhdmp][a]?$/ && $an++;
      push @on, $t;
    }
    if($hasspin>0) {
      unshift @olist, '1';
    } else {
      $on[1] =~ s/N//;
    }
    $oname = join("_",@on);
    $oname =~ s/transpose_C/C/;
    $oname =~ s/transpose_pC/pC/;
    $oname =~ s/conj_C/Ca/;
    $oname =~ s/conj_pC/pCa/;
    $oname =~ s/trace_C/C/;
    $oname =~ s/trace_pC/pC/;
    $oname =~ s/det_C/C/;
    $oname =~ s/det_pC/pC/;
    $oname =~ s/eigenvals_C/C/;
    $oname =~ s/eigenvals_pC/pC/;
    $oname =~ s/eigenvalsH_C/C/;
    $oname =~ s/eigenvalsH_pC/pC/;
    $oname =~ s/sqrt_C/csqrt_C/;
    $oname =~ s/sqrt_pC/csqrt_pC/;
    $oname =~ s/sqrtPH_C/csqrt_C/;
    $oname =~ s/sqrtPH_pC/csqrt_pC/;
    $oname =~ s/exp_C/cexp_C/;
    $oname =~ s/exp_pC/cexp_pC/;
    $oname =~ s/expA_C/cexp_C/;
    $oname =~ s/expA_pC/cexp_pC/;
    $oname =~ s/expTA_C/cexp_C/;
    $oname =~ s/expTA_pC/cexp_pC/;
    $oname =~ s/log_C/clog_C/;
    $oname =~ s/log_pC/clog_pC/;
  }
  return (join(", ",@list),join(", ",@olist),$oname);
}

open(INFILE, "<".$infile);
open(OUTFILE, ">".$outfile);

print OUTFILE "#ifndef $def\n";
print OUTFILE "#define $def\n\n";
print OUTFILE "#include <qla_f.h>\n";
print OUTFILE "#include <qla_d.h>\n";
print OUTFILE "#include <qla_q.h>\n";
print OUTFILE "#include <qla_fn.h>\n";
print OUTFILE "#include <qla_dn.h>\n";
print OUTFILE "#include <qla_qn.h>\n";
print OUTFILE "#include <qla_dfn.h>\n";
print OUTFILE "#include <qla_dqn.h>\n\n";
print OUTFILE "/* the following line is used by the test suite */\n";
print OUTFILE "/* BEGIN_MACROS */\n\n";

while(<INFILE>) {

  chomp;
  /\*\// && do { # possible end comment
    if($in_comment) {
      $in_comment = 0;
      s/^.*\*\///;
    } else {
      s/\/\*.*\*\///;
    }
  };
  next if $in_comment;
  /\/\*/ && do { # possible begin comment
    $in_comment = 1;
    s/\/\*.*$//;
  };
  /^\s*$/ && next;
  /^\s*\#/ && next;
  /^\s*extern\s*"C"/ && next;
  /^\s*}/ && next;

  ($name, $args) = get_name_args($_);
  #print $name, ":", $args, "\n";
  ($nname = $name) =~ s/(QLA_[FDQ]+)N/${1}1/;
  ($narglist, $oarglist, $oname) = get_arg_lists($args, $name);
  #print $gname, " : ", $arglist, "\n";
  print OUTFILE "#define ", $nname, "( ", $narglist, " ) \\\n";
  print OUTFILE "        ", $oname, "( ", $oarglist, " )\n";
}

print OUTFILE "\n/* the following line is used by the test suite */\n";
print OUTFILE "/* END_MACROS */\n";

if($P0 eq $P1) {
  print OUTFILE <<EOF;

/* Translation to precision-generic names */
#if QLA_Precision == '$P'
#include <qla_${p}1_precision_generic.h>
#endif

/* Translation to color-generic names */
#if QLA_Colors == 1
#include <qla_${p}1_color_generic.h>
#endif

/* Translation to fully generic names */
#if QLA_Precision == '${P}' && QLA_Colors == 1
#include <qla_${p}1_generic.h>
#endif

#endif /* $def */
EOF
} else {
  print OUTFILE <<EOF;

/* Translation to color-generic names */
#if QLA_Colors == 1
#include <qla_${p}1_color_generic.h>
#endif

#endif /* $def */
EOF
}

close INFILE;
close OUTFILE;
