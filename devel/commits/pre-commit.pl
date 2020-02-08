#!/usr/bin/perl

sub error()
{
    my $line = shift;
    print STDERR "$line\n";
}

# Check if there is anything to commit
my @status = qx(svn status -q);
chomp(@status);
if(@status == 0)
{
    error("There is nothing to commit");
}
else
{
    for my $line (@status)
    {
        if(substr($line, 0, 1) eq 'C' || substr($line, 1, 1) eq 'C' || substr($line, 6, 1) eq 'C')
        {
            error("There is a conflict. Please resolve it first!");
        }
        if(substr($line, 2, 1) eq 'L')
        {
            error("The working copy directory is locked");
        }
        if(substr($line, 0, 1) eq '!')
        {
            error("An item is missing (removed by non-svn command) or incomplete");
        }
        if(substr($line, 5, 1) =~ /^[KOT]$/)
        {
            error("An item is locked in repository");
        }
    }
}
@status = ();

# Try to update
my @update = qx(svn up);
chomp(@update);
my $rev = 0;
my $conflict = 0;
my $upd = 0;
for my $line (@update)
{
    next if($line =~ /^Updating/);
    my $char = substr($line, 0, 1);
    if($char eq 'C')
    {
        if($confict == 0)
        {
            print STDERR "There is a conflict. Please resolve it first!\n";
            print STDERR "$line\n";
            $conflict = 1;
        }
        else
        {
            print STDERR "There is one more conflict. Please resolve it first!\n";
            print STDERR "$line\n";
        }
    }
    elsif(($char eq 'U' || $char eq 'M') && $upd == 0)
    {
        $upd = 1;
    }
    $rev = $1 if($line =~ /^Updated to revision (\d+)\.$/);
    $rev = $1 if($line =~ /^At revision (\d+)\.$/);
}

if($conflict != 0)
{
    map {print("$_\n");} @update;
    exit(1);
}

if($upd == 1)
{
    print STDERR "There were updates and/or merges. Please test your code\n\n";
    map {print("$_\n");} @update;
    exit(1);
}

if($rev == 0)
{
    print STDERR "Cannot fetch current revision\n";
    exit(1);
}

my $major_ver, $minor_ver, $patch_num, $space, @lines;

# Increase the version number in "./hpp/constant.hpp"
open(FH, "<", "./hpp/constant.hpp") or die "Cannot open the file ./hpp/constant.hpp: $!";
while(<FH>)
{
    s/[\r\n]//g;
    if(/^\#define VERSION\s+\"(\d+)\.(\d+)\.(\d+)\"/)
    {
        $major_ver = $1;
        $minor_ver = $2;
        $patch_num = $major_ver == 2 && $minor_ver == 0 ? $rev - 265 + 1 : $3 + 1;
        s/^\#define VERSION(\s+\"\d+\.\d+)\.\d+\"/\#define VERSION${1}\.$patch_num\"/;
    }
    push(@lines, $_) or die "pre-commit.pl: Not enough memory";
}
close(FH);

error("Version number not found in hpp/constant.hpp") if($major_ver == 0);

open(FH, ">", "./hpp/constant.hpp") or die "Cannot open the file ./hpp/constant.hpp: $!";
map {print FH "$_\n";} @lines;
close(FH);
@lines = ();

# Increase the version number in "./MakeFiles/linux/rntrack.spec"
$major_ver = 0;
open(FH, "<", "./MakeFiles/linux/rntrack.spec") or die "Cannot open the file ./MakeFiles/linux/rntrack.spec: $!";
while(<FH>)
{
    s/[\r\n]//g;
    if(/^Version:\s+(\d+)\.\d+\.\d+$/)
    {
        $major_ver = $1;
        s/^Version:(\s+\d+\.\d+\.)\d+$/Version:${1}$patch_num/;
    }
    push(@lines, $_) or die "pre-commit.pl: Not enough memory";
}
close(FH);

error("Version number not found in MakeFiles/linux/rntrack.spec") if($major_ver == 0);

open(FH, ">", "./MakeFiles/linux/rntrack.spec") or die "Cannot open the file ./MakeFiles/linux/rntrack.spec: $!";
map {print FH "$_\n";} @lines;
close(FH);
