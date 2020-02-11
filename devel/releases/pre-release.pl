#!/usr/bin/perl
#
# pre-release.pl - The actions to be done before committing new release.
#                  Change version, tag and revision in ChangeLog and readme.txt,
#                  version in hpp/constatnt.hpp and MakeFiles/linux/rntrack.spec
use POSIX qw(strftime);

# Check if there is anything to commit
my @update = qx(svn status -q);
chomp(@update);
if(@update == 0)
{
    print STDERR "There is nothing to commit\n";
    exit(1);
}

# Check whether files "trunk/ChangeLog", "./release.msg" and "./readme.txt" exist
unless(-f "trunk/ChangeLog" && -f "./release.msg" && -f "./readme.txt")
{
    print STDERR "Please provide files trunk/ChangeLog, ./release.msg and ./readme.txt\n";
    exit(1);
}

# Check whether trunk/ChangeLog contains the template line:
# X.XX.XXX XXXX-XX-XX (Subversion rev.XXXX, tag "version-X.XX.XXX")
my @changelog;
my $tplLineIndex = -1;
my $lineNum = -1;
my $templateLine = "X\\.XX\\.XXX XXXX-XX-XX \\(Subversion rev\\.XXXX, tag \\\"version-X\\.XX\\.XXX\\\"\\)";
open(FH, "<", "trunk/ChangeLog") or die "Cannot open the file trunk/ChangeLog: $!";
while(<FH>)
{
    s/[\r\n]//g;
    $tplLineIndex++;
    if(/^$templateLine$/)
    {
        # The line number will be used later
        $lineNum = $tplLineIndex;
    }
    push(@changelog, $_) or die "pre-commit.pl: Not enough memory";
}
close(FH);
if($lineNum == -1)
{
    print STDERR "Template line not found in trunk/ChangeLog\n";
    exit(1);
}

# Check whether ./readme.txt contains the template line:
# Netmail tracker RNtrack X.XX.XXX
my @readme_txt;
my $has_readme_tpl = 0;
my $readmeLine = "Netmail tracker RNtrack X\\.XX\\.XXX";
my $readme_tplLineIndex = -1;
my $readme_lineNum = -1;
open(FH, "<", "./readme.txt") or die "Cannot open the file ./readme.txt: $!";
while(<FH>)
{
    s/[\r\n]//g;
    if(/^$readmeLine$/)
    {
        $has_readme_tpl = 1;
    }
    $readme_tplLineIndex++;
    if(/^$templateLine$/)
    {
        # The line number will be used later
        $readme_lineNum = $readme_tplLineIndex;
    }
    push(@readme_txt, $_) or die "pre-commit.pl: Not enough memory";
}
close(FH);
if($has_readme_tpl == 0)
{
    print STDERR "Template line not found in ./readme.txt\n";
    exit(1);
}
for(my $i = 0; $i < @readme_txt; $i++)
{
    $readme_txt2[$i] = $readme_txt[$i];
}

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

# Increase the version number in "trunk/hpp/constant.hpp"
open(FH, "<", "trunk/hpp/constant.hpp") or die "Cannot open the file trunk/hpp/constant.hpp: $!";
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

die "Version number not found in trunk/hpp/constant.hpp" if($major_ver == 0);

open(FH, ">", "trunk/hpp/constant.hpp") or die "Cannot open the file trunk/hpp/constant.hpp: $!";
map {print FH "$_\n";} @lines;
close(FH);
@lines = ();

# Increase the version number in "trunk/MakeFiles/linux/rntrack.spec"
$major_ver = 0;
open(FH, "<", "trunk/MakeFiles/linux/rntrack.spec") or die "Cannot open the file trunk/MakeFiles/linux/rntrack.spec: $!";
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

die "Version number not found in trunk/MakeFiles/linux/rntrack.spec" if($major_ver == 0);

open(FH, ">", "trunk/MakeFiles/linux/rntrack.spec") or die "Cannot open the file trunk/MakeFiles/linux/rntrack.spec: $!";
map {print FH "$_\n";} @lines;
close(FH);
@lines = ();

$rev++;
my $full_ver = "${major_ver}.${minor_ver}.$patch_num";


# Add all new changes from trunk/ChangeLog to ./readme.txt
my $lineNum2 = $lineNum + 2;
while($changelog[$lineNum2] ne "")
{
    $lineNum2++;
}
if($lineNum2 > $lineNum + 2)
{
    $readme_lineNum += 2;
    splice(@readme_txt, $readme_lineNum, 1, @changelog[($lineNum + 2)..$lineNum2]);
}
# Replace templates in trunk/ChangeLog
my $date = strftime("%F", 0, 0, 0, (localtime)[3,4,5]);
my $newline = "$full_ver $date (Subversion rev.$rev, tag \"version-$full_ver\")";
$changelog[$lineNum] = $newline;
$changelog[$lineNum + 1] = "-" x length($newline);
open(FH, ">", "trunk/ChangeLog") or die "Cannot open the file trunk/ChangeLog: $!";
map {print FH "$_\n";} @changelog;
close(FH);

# Replace templates in ./readme.txt
open(FH, ">", "./readme.txt") or die "Cannot open the file ./readme.txt: $!";
for $line (@readme_txt)
{
    $line =~ s/^$templateLine$/$newline/;
    $line =~ s/X\.XX\.XXX/$full_ver/;
    $line =~ s/X_XX_XXX/${major_ver}_${minor_ver}_$patch_num/;
    print FH "$line\n";
}
close(FH);

# Update trunk/devel/releases/ChangeLog
my @changelog2;
my $tplLineIndex3 = -1;
my $lineNum3 = -1;
open(FH, "<", "trunk/devel/releases/ChangeLog") or die "Cannot open the file trunk/devel/releases/ChangeLog: $!";
while(<FH>)
{
    s/[\r\n]//g;
    $tplLineIndex3++;
    if(/^$templateLine$/)
    {
        # The line number will be used later
        $lineNum3 = $tplLineIndex3;
    }
    push(@changelog2, $_) or die "pre-commit.pl: Not enough memory";
}
close(FH);
splice(@changelog2, $lineNum3 + 2, 1, ("", @changelog[$lineNum..$lineNum2]));
open(FH, ">", "trunk/devel/releases/ChangeLog") or die "Cannot open the file trunk/devel/releases/ChangeLog: $!";
map {print FH "$_\n";} @changelog2;
close(FH);

# Update trunk/devel/releases/readme.txt
my $readme_tplLineIndex = -1;
my $readme_lineNum = -1;
@readme_txt = ();
open(FH, "<", "trunk/devel/releases/readme.txt") or die "Cannot open the file trunk/devel/releases/readme.txt: $!";
while(<FH>)
{
    s/[\r\n]//g;
    $readme_tplLineIndex++;
    if(/^$templateLine$/)
    {
        $readme_lineNum = $readme_tplLineIndex;
    }
    push(@readme_txt, $_) or die "pre-commit.pl: Not enough memory";
}
close(FH);
splice(@readme_txt, $readme_lineNum + 2, 1, ("", @changelog[$lineNum..$lineNum2]));
open(FH, ">", "trunk/devel/releases/readme.txt") or die "Cannot open the file trunk/devel/releases/readme.txt: $!";
map {print FH "$_\n";} @readme_txt;
close(FH);

# Write the list of all modified files to ./release.lst
my @update = qx(svn status -q);
chomp(@update);
open(FH, ">", "./release.lst") or die "Cannot open the file ./release.lst: $!";
map {print FH substr($_, 8)."\n";} @update;
close(FH);

# Replace template in ./release.msg
@update = ();
open(FH, "<", "./release.msg") or die "Cannot open the file ./release.msg: $!";
while(<FH>)
{
    s/X\.XX\.XXX/$full_ver/;
    push(@update, $_);
}
close(FH);
chomp(@update);
open(FH, ">", "./release.msg") or die "Cannot open the file ./release.msg: $!";
print FH $update[0];
close(FH);

# Create new tag
open(FH, ">", "./tag.txt") or die "Cannot open the file ./tag.txt: $!";
print FH "version-$full_ver";
close(FH);

# Create file with the new revision number
open(FH, ">", "./rev.txt") or die "Cannot open the file ./rev.txt: $!";
print FH "$rev";
close(FH);
