#!/usr/bin/perl

for $f (glob "QLA_*.h") {
  #print $f, "\n";
  print "#include \"$f\"\n";
}

