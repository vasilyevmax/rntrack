#!/usr/bin/perl

# Write the list of all modified files to ./commit.lst
my @update = qx(svn status -q);
chomp(@update);
open(FH, ">", "./commit.lst") or die "Cannot open the file ./commit.lst: $!";
map {print FH substr($_, 8)."\n";} @update;
close(FH);
