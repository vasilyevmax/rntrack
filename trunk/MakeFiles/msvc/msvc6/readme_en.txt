              How to build RNtrack using MS Visual Studio 6.0
              ===============================================

Contents
========

1. Preparation
2. Building RNtrack using Visual Studio graphic environment
    2.1. Building without script support
    2.2. Building with script support
3. Building RNtrack in a command line
    3.1. Building without script support
    3.2. Building with script support


1. Preparation
==============

First of all you have to generate the project files, makefiles and batch files.
Please run prepare6.js, which is in the same directory with the file you are
reading now. To run prepare6.js just double-click it in the Windows Explorer.
If MS Visual Studio 6.0 has been installed, then the following files are 
generated:

	build.bat
	makefile.dep
	makefile.vc6
	rebuild.bat
	rntrack.dsp
	rntrack.dsw

If it turns out that you have not created VCVARS32.BAT during the Visual Studio
installation, an error message pops up. By the way all error messages pop up as
dialog boxes. If you like to see the messages in a command line, then please
run prepare6.js in a command line this way:

cscript prepare6.js

If ActiveState Perl has already been installed, the following files are also
generated:

	build_perl.bat
	makeperl.dep
	makeperl.vc6
	rebuild_perl.bat
	rntrack_perl.dsp
	rntrack_perl.dsw

If Perl is not installed, you will be able to build RNtrack without script 
support only.

2. Building RNtrack using Visual Studio graphic environment
===========================================================

2.1. Building without script support
------------------------------------

The sequence of actions:
    1. Open Visual Studio.
    2. Select "Open Workspace..." in the File menu. 
    3. Select the directory in which we have generated the files in the opened 
       window and then select the rntrack.dsw file. Press Open.
    4. Select "Set Active Configuration..." in the Build menu.
    5. Click the line with "rntrack - Win32 Release" and press OK. 
    6. Select "Build rntrack.exe" in the Build menu.
You will see the build log in the Build tab of the Visual Studio lower window. 
If after the build has been over you see  

rntrack.exe - 0 error(s)

there, then everything is OK. A subdirectory named Release is created in the 
directory where we have generated files during the preparation step and 
rntrack.exe is there. The job is done!

If you want to clean the results of the previous build and then rebuild 
RNtrack, one of the two actions may be done: a) select Clean in the Build menu 
before executing item 6 in the list of actions above; b) select "Rebuild All" 
in the Build menu instead of executing item 6 in the list of actions above.

2.2. Building with script support
---------------------------------

The sequence of actions is similar to the one in 2.1:
    1. Open Visual Studio.
    2. Select "Open Workspace..." in the File menu. 
    3. Select the directory in which we have generated the files in the opened 
       window and then select the rntrack_perl.dsw file. Press Open.
    4. Select "Set Active Configuration..." in the Build menu.
    5. Click the line with "rntrack_perl - Win32 Release" and press OK. 
    6. Select "Build rntrack_perl.exe" in the Build menu.
You will see the build log in the Build tab of the Visual Studio lower window. 
If after the build has been over you see  

rntrack_perl.exe - 0 error(s)

there, then everything is OK. A subdirectory named Release is created in the 
directory where we have generated files during the preparation step and the
rntrack_perl.exe we need is there.

If you want to clean the results of the previous build and then rebuild 
RNtrack, one of the two actions may be done: a) select Clean in the Build menu 
before executing item 6 in the list of actions above; b) select "Rebuild All" 
in the Build menu instead of executing item 6 in the list of actions above.

3. Building RNtrack in a command line
=====================================

3.1. Building without script support
------------------------------------

Run build.bat in a command line. A log file named build.log is created during
RNtrack build. If it has "rntrack.exe is successfully built" in its last line, 
then everything is OK. You may find rntrack.exe in the Release subdirectory.

If RNtrack has already been built once and you want to delete the results of 
the previous build and then build RNtrack again, please run rebuild.bat.

3.2. Building with script support
---------------------------------

Run build_perl.bat in a command line. A log file named build.log is created 
during RNtrack build. If it has "build_perl.exe is successfully built" in its 
last line, then everything is OK. You may find rntrack_perl.exe in the Release 
subdirectory.

If RNtrack has already been built once and you want to delete the results of 
the previous build and then build RNtrack again, please run rebuild_perl.bat.

