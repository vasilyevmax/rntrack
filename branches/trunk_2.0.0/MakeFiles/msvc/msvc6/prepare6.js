// $Id$
//
// prepare6.js prepares files for building RNtrack using MSVC 6.0
//

/////////////////////////////////////////////////////////////////////
//                                                                 // 
//                          Declarations                           //
//                                                                 // 
/////////////////////////////////////////////////////////////////////

var ForReading = 1, ForWriting = 2, ForAppending = 8;
var FileFormatSystemDefault = -2, FileFormatUnicode = -1, FileFormatASCII = 0;

//
// function readFromRegistry returns the value of strRegistryKey
// registry key. If the key has not been found, strDefault is returned.
//
function readFromRegistry(strRegistryKey, strDefault)
{
    var wshShell = WScript.CreateObject("WScript.Shell");
    try
    {
        var value = wshShell.RegRead(strRegistryKey);
    }
    catch(e)
    {
        return(strDefault);
    }
    return(value);
}

//
// function WriteToFile writes "text" to the file "filename";
// encoding may take the values: FileFormatSystemDefault,
// FileFormatUnicode, FileFormatASCII
//
function WriteToFile(filename, text, encoding)
{
    var fso = new ActiveXObject("Scripting.FileSystemObject");

    // Create the file and obtain a file object for the file.
    try
    {
        fso.CreateTextFile(filename);
        var fileObj = fso.GetFile(filename);
    }
    catch(e)
    {
        WScript.Echo("Cannot create " + "'" + filename + "'");
        return;
    }

    // Open a text stream for output.
    try
    {
        var ts = fileObj.OpenAsTextStream(ForWriting, encoding);
    }
    catch(e)
    {
        WScript.Echo("Cannot open for writing " + "'" + filename + "'");
        return;
    }

    // Write to the text stream.
    try
    {
        ts.Write(text);
    }
    catch(e)
    {
        WScript.Echo("Error while writing to " + "'" + filename + "'");
    }
    ts.Close();
}

//
// function ReadFromFile returns the text read from the file "filename"
//
function ReadFromFile(filename)
{
    var fso = new ActiveXObject("Scripting.FileSystemObject");

    // Open the file for input.
    try
    {
        var f = fso.OpenTextFile(filename, ForReading);
    }
    catch(e)
    {
        WScript.Echo("Cannot open for reading " + "'" + filename + "'");
        return ("");
    }

    // Read from the file
    try
    {
        if (f.AtEndOfStream)
        {
            f.Close();
            return ("");
        }
        else
        {
            var text = f.ReadAll();
            f.Close();
            return (text);
        }
    }
    catch(e)
    {
        WScript.Echo("Error while reading from " + "'" + filename + "'");
        f.Close();
        return ("");
    }
}


//
// function DeleteFile deletes the file "path"
// and returns the exit code of the operation
//
function DeleteFile(path)
{
    var WshShell = new ActiveXObject("WScript.Shell");
    var cmd = '%comspec% /c del "' + path + '"';
    var bWaitOnReturn = false;
    var intWindowStyle = 0; // Hide the window
    try
    {
        var exitCode = WshShell.Run(cmd, intWindowStyle, bWaitOnReturn);
    }
    catch(e)
    {
        WScript.Echo("Cannot delete '" + path + "'");
    }
    WshShell = null;
    return (exitCode);
}


//
// function RunCmd runs the command "cmd"
// and returns the exit code of the operation.
//
function RunCmd(cmd)
{
    var WshShell = new ActiveXObject("WScript.Shell");
    var intWindowStyle = 0; // Hide the window
    var bWaitOnReturn = true;
    try
    {
        var exitCode = WshShell.Run(cmd, intWindowStyle, bWaitOnReturn);
    }
    catch(e)
    {
        WScript.Echo("Cannot run " + cmd);
        exitCode = -1;
    }
    WshShell = null;
    return (exitCode);
}


//
// function AppendPath appends directory dir to path
// and returns the resulting string
//
function AppendPath(path, dir)
{
    if(path.substr(path.length - 1, 1) == '\\' &&
       dir.substr(0, 1) == '\\')
    {
        return(path + dir.substr(1));
    }
    else if(path.substr(path.length - 1, 1) != '\\' &&
            dir.substr(0, 1) != '\\')
    {
        return(path + '\\' + dir);
    }
    else
    {
        return(path + dir);
    }
}

//
// function GetHereDoc converts a here-document with the name heredocName
// to a string and returns the string
//
function GetHereDoc(heredocName)
{
    var s = new String(heredocName);
    s = s.replace(/function\(\){\/\*\r\n/, '');
    s = s.replace(/\r\n\*\/}$/, '');
    return s;
}

//
// A here-document with a comment for "build.bat"
//
var build_comment = function(){/*
rem build.bat is used to build RNTrack without script support
*/};

//
// A here-document with a comment for "rebuild.bat"
//
var rebuild_comment = function(){/*
rem rebuild.bat is used to build RNTrack without script support
rem after cleaning the old build
*/};

//
// A here-document with a comment for "build_perl.bat"
//
var build_perl_comment = function(){/*
rem build_perl.bat is used to build RNTrack with script support
*/};

//
// A here-document with a comment for "rebuild_perl.bat"
//
var rebuild_perl_comment = function(){/*
rem rebuild_perl.bat is used to build RNTrack with script support
rem after cleaning the old build
*/};


//
// A here-document with smapi cleaning part for "rebuild.bat"
//
var clean_smapi = function(){/*
echo ############## Cleaning the old smapi build... >> ./../build.log
NMAKE /f "smapi.mak" CFG="smapi - Win32 Release" clean >> ./../build.log 2>&1
*/};

//
// A here-document with rntrack cleaning part for "rebuild.bat"
//
var clean_rntrack = function(){/*
echo ############## Cleaning the old @@projectName@@ build... >> build.log
NMAKE /f "@@makefileName@@@@makefileExt@@" CFG="@@projectName@@ - Win32 Release" clean >> build.log 2>&1
*/};

//
// A here-document with a template for "build.bat" and "rebuild.bat"
//
var build_bat = function(){/*
@echo off
rem
@@build_comment@@
rem

@@buildEnv@@

date /T > build.log
pushd smapi
@@clean_smapi@@
echo ############## Building smapi... >> ./../build.log
NMAKE /f "smapi.mak" CFG="smapi - Win32 Release" >> ./../build.log 2>&1
if errorlevel 1 (
popd
goto Error
)
popd
echo. >> build.log
echo ############## smapi.lib is successfully built ############## >> build.log
echo. >> build.log
@@clean_rntrack@@
echo ############## Building @@projectName@@... >> build.log
NMAKE /f "@@makefileName@@@@makefileExt@@" CFG="@@projectName@@ - Win32 Release" >> build.log 2>&1
if errorlevel 1 goto Error
echo. >> build.log
echo ############## @@projectName@@.exe is successfully built ############## >> build.log
:Error
*/};

//
// A here-document for perlconf
//
var perlconf = function(){/*
use Config;
my $perl_incl, $perl_lib;
($perl_incl = $Config::Config{libpth})  =~ s/^@@dquote@@(.*)@@dquote@@$/$1/;
($perl_lib  = $Config::Config{libperl}) =~ s/^@@dquote@@(.*)@@dquote@@$/$1/;
$perl_incl =~ s/\\/\\\\/g;
my $perl_version = "$]";
my ($perl_major, $perl_minor) = split /\./, $perl_version;
$perl_version =~ s/\.//;
$perl_minor += 0;
open(OUT, '>@@file@@') or die  "Cannot open the file @@file@@: $!";
print OUT "perl_incl = \'$perl_incl\'; perl_lib = \'$perl_lib\'; ";
print OUT "perl_version = $perl_version; perl_major = $perl_major; ";
print OUT "perl_minor = $perl_minor;";
close OUT;
*/};


//
// A here-document with a template for "rntrack.dsp"
//
var rntrack_dsp = function(){/*
# Microsoft Developer Studio Project File - Name="@@projectName@@" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=@@projectName@@ - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "@@projectName@@.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "@@projectName@@.mak" CFG="@@projectName@@ - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "@@projectName@@ - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "@@projectName@@ - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "@@projectName@@ - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /I "..\..\..\hpp" /I "..\..\..\src" /I "..\..\..\smapi\h" /I "..\..\..\smapi\src" @@perl_ADD_CPP@@ /D "NDEBUG" /D "_CONSOLE" /D "__NT__" /D "WIN32IOP_H" /D "HAVE_IO_H" /D "WIN32" /D "_MBCS" /D "HAVE_TIME_H" /D "HAVE_SYS_UTIME_H" /D "HAVE_LOCALE_H" /FD /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x419 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib @@perl_ADD_LINK32@@ /nologo /subsystem:console /machine:I386

!ELSEIF  "$(CFG)" == "@@projectName@@ - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /I "..\..\..\hpp" /I "..\..\..\src" /I "..\..\..\smapi\h" /I "..\..\..\smapi\src" @@perl_ADD_CPP@@ /D "_CONSOLE" /D "_DEBUG" /D "__NT__" /D "WIN32IOP_H" /D "HAVE_IO_H" /D "WIN32" /D "_MBCS" /D "HAVE_TIME_H" /D "HAVE_SYS_UTIME_H" /D "HAVE_LOCALE_H" /FR /FD /GZ /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x419 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib @@perl_ADD_LINK32@@ /nologo /version:1.17 /subsystem:console /map /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "@@projectName@@ - Win32 Release"
# Name "@@projectName@@ - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\..\..\src\age.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\aix_conv.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\aka.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\attach.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\badmsg.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\badpkt.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\cfg.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\configure.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\dirent.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\domain.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\fidoaddr.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\filebox.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\getopt.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\help.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\log.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\mask.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\msg.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\msgbase.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\nodelist.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\outbound.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\parsetpl.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\passwd.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\pktbase.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\rntrack.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\scandir.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\script.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\sqbase.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\string.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\tmstamp.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\utils.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vars.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\wildmat.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\..\..\hpp\a_list.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\hpp\age.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\hpp\aix_conv.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\hpp\aka.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\hpp\attach.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\hpp\badmsg.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\hpp\badpkt.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\hpp\cfg.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\smapi\h\compiler.h
# End Source File
# Begin Source File

SOURCE=..\..\..\hpp\configure.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\hpp\constant.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\hpp\dirent\dirent.h
# End Source File
# Begin Source File

SOURCE=..\..\..\hpp\domain.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\hpp\fidoaddr.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\hpp\filebox.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\smapi\h\ftnaddr.h
# End Source File
# Begin Source File

SOURCE=..\..\..\hpp\getopt.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\hpp\help.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\hpp\log.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\hpp\mask.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\hpp\msg.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\smapi\h\msgapi.h
# End Source File
# Begin Source File

SOURCE=..\..\..\hpp\msgbase.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\smapi\h\MSVC.h
# End Source File
# Begin Source File

SOURCE=..\..\..\hpp\mytypes.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\hpp\nodelist.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\hpp\outbound.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\hpp\parsetpl.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\hpp\passwd.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\hpp\pktbase.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\smapi\h\prog.h
# End Source File
# Begin Source File

SOURCE=..\..\..\smapi\h\progprot.h
# End Source File
# Begin Source File

SOURCE=..\..\..\hpp\scandir.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\hpp\script.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\hpp\sqbase.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\smapi\h\stamp.h
# End Source File
# Begin Source File

SOURCE=..\..\..\hpp\string.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\hpp\tmstamp.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\hpp\tpkt.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\smapi\h\typedefs.h
# End Source File
# Begin Source File

SOURCE=..\..\..\smapi\h\typesize.h
# End Source File
# Begin Source File

SOURCE=..\..\..\smapi\h\unused.h
# End Source File
# Begin Source File

SOURCE=..\..\..\hpp\utils.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\hpp\vars.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\hpp\wildmat.hpp
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project

*/};


//
// A here-document with a template for "rntrack.dsw"
//
var rntrack_dsw = function(){/*
Microsoft Developer Studio Workspace File, Format Version 6.00
# WARNING: DO NOT EDIT OR DELETE THIS WORKSPACE FILE!

###############################################################################

Project: "@@projectName@@"=".\@@projectName@@.dsp" - Package Owner=<4>

Package=<5>
{{{
}}}

Package=<4>
{{{
    Begin Project Dependency
    Project_Dep_Name smapi
    End Project Dependency
}}}

###############################################################################

Project: "smapi"=".\smapi\smapi.dsp" - Package Owner=<4>

Package=<5>
{{{
}}}

Package=<4>
{{{
}}}

###############################################################################

Global:

Package=<5>
{{{
}}}

Package=<3>
{{{
}}}

###############################################################################


*/};


//
// A here-document with a template for "makefile.vc6"
//
var makefile_vc6 = function(){/*
# Microsoft Developer Studio Generated NMAKE File, Based on @@projectName@@.dsp
!IF "$(CFG)" == ""
CFG=@@projectName@@ - Win32 Debug
!MESSAGE No configuration specified. Defaulting to @@projectName@@ - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "@@projectName@@ - Win32 Release" && "$(CFG)" != "@@projectName@@ - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "@@makefileName@@@@makefileExt@@" CFG="@@projectName@@ - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "@@projectName@@ - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "@@projectName@@ - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "@@projectName@@ - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\@@projectName@@.exe"

!ELSE 

ALL : "smapi - Win32 Release" "$(OUTDIR)\@@projectName@@.exe"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"smapi - Win32 ReleaseCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
    -@erase "$(INTDIR)\age.obj"
    -@erase "$(INTDIR)\aix_conv.obj"
    -@erase "$(INTDIR)\aka.obj"
    -@erase "$(INTDIR)\attach.obj"
    -@erase "$(INTDIR)\badmsg.obj"
    -@erase "$(INTDIR)\badpkt.obj"
    -@erase "$(INTDIR)\cfg.obj"
    -@erase "$(INTDIR)\configure.obj"
    -@erase "$(INTDIR)\dirent.obj"
    -@erase "$(INTDIR)\domain.obj"
    -@erase "$(INTDIR)\fidoaddr.obj"
    -@erase "$(INTDIR)\filebox.obj"
    -@erase "$(INTDIR)\getopt.obj"
    -@erase "$(INTDIR)\help.obj"
    -@erase "$(INTDIR)\log.obj"
    -@erase "$(INTDIR)\mask.obj"
    -@erase "$(INTDIR)\msg.obj"
    -@erase "$(INTDIR)\msgbase.obj"
    -@erase "$(INTDIR)\nodelist.obj"
    -@erase "$(INTDIR)\outbound.obj"
    -@erase "$(INTDIR)\parsetpl.obj"
    -@erase "$(INTDIR)\passwd.obj"
    -@erase "$(INTDIR)\pktbase.obj"
    -@erase "$(INTDIR)\rntrack.obj"
    -@erase "$(INTDIR)\scandir.obj"
    -@erase "$(INTDIR)\script.obj"
    -@erase "$(INTDIR)\sqbase.obj"
    -@erase "$(INTDIR)\string.obj"
    -@erase "$(INTDIR)\tmstamp.obj"
    -@erase "$(INTDIR)\utils.obj"
    -@erase "$(INTDIR)\vars.obj"
    -@erase "$(INTDIR)\vc60.idb"
    -@erase "$(INTDIR)\wildmat.obj"
    -@erase "$(OUTDIR)\@@projectName@@.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /ML /W3 /GX /O2 /I "..\..\..\hpp" /I "..\..\..\src" /I "..\..\..\smapi\h" /I "..\..\..\smapi\src" @@perl_ADD_CPP@@ /D "NDEBUG" /D "_CONSOLE" /D "__NT__" /D "WIN32IOP_H" /D "HAVE_IO_H" /D "WIN32" /D "_MBCS" /D "HAVE_TIME_H" /D "HAVE_SYS_UTIME_H" /D "HAVE_LOCALE_H" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

RSC=rc.exe
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\@@projectName@@.bsc" 
BSC32_SBRS= \
    
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib @@perl_ADD_LINK32@@ /nologo /subsystem:console /incremental:no /pdb:"$(OUTDIR)\@@projectName@@.pdb" /machine:I386 /out:"$(OUTDIR)\@@projectName@@.exe" 
LINK32_OBJS= \
    "$(INTDIR)\age.obj" \
    "$(INTDIR)\aix_conv.obj" \
    "$(INTDIR)\aka.obj" \
    "$(INTDIR)\attach.obj" \
    "$(INTDIR)\badmsg.obj" \
    "$(INTDIR)\badpkt.obj" \
    "$(INTDIR)\cfg.obj" \
    "$(INTDIR)\configure.obj" \
    "$(INTDIR)\dirent.obj" \
    "$(INTDIR)\domain.obj" \
    "$(INTDIR)\fidoaddr.obj" \
    "$(INTDIR)\filebox.obj" \
    "$(INTDIR)\getopt.obj" \
    "$(INTDIR)\help.obj" \
    "$(INTDIR)\log.obj" \
    "$(INTDIR)\mask.obj" \
    "$(INTDIR)\msg.obj" \
    "$(INTDIR)\msgbase.obj" \
    "$(INTDIR)\nodelist.obj" \
    "$(INTDIR)\outbound.obj" \
    "$(INTDIR)\parsetpl.obj" \
    "$(INTDIR)\passwd.obj" \
    "$(INTDIR)\pktbase.obj" \
    "$(INTDIR)\rntrack.obj" \
    "$(INTDIR)\scandir.obj" \
    "$(INTDIR)\script.obj" \
    "$(INTDIR)\sqbase.obj" \
    "$(INTDIR)\string.obj" \
    "$(INTDIR)\tmstamp.obj" \
    "$(INTDIR)\utils.obj" \
    "$(INTDIR)\vars.obj" \
    "$(INTDIR)\wildmat.obj" \
    ".\smapi\Release\smapi.lib"

"$(OUTDIR)\@@projectName@@.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "@@projectName@@ - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\@@projectName@@.exe" "$(OUTDIR)\@@projectName@@.bsc"

!ELSE 

ALL : "smapi - Win32 Debug" "$(OUTDIR)\@@projectName@@.exe" "$(OUTDIR)\@@projectName@@.bsc"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"smapi - Win32 DebugCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
    -@erase "$(INTDIR)\age.obj"
    -@erase "$(INTDIR)\age.sbr"
    -@erase "$(INTDIR)\aix_conv.obj"
    -@erase "$(INTDIR)\aix_conv.sbr"
    -@erase "$(INTDIR)\aka.obj"
    -@erase "$(INTDIR)\aka.sbr"
    -@erase "$(INTDIR)\attach.obj"
    -@erase "$(INTDIR)\attach.sbr"
    -@erase "$(INTDIR)\badmsg.obj"
    -@erase "$(INTDIR)\badmsg.sbr"
    -@erase "$(INTDIR)\badpkt.obj"
    -@erase "$(INTDIR)\badpkt.sbr"
    -@erase "$(INTDIR)\cfg.obj"
    -@erase "$(INTDIR)\cfg.sbr"
    -@erase "$(INTDIR)\configure.obj"
    -@erase "$(INTDIR)\configure.sbr"
    -@erase "$(INTDIR)\dirent.obj"
    -@erase "$(INTDIR)\dirent.sbr"
    -@erase "$(INTDIR)\domain.obj"
    -@erase "$(INTDIR)\domain.sbr"
    -@erase "$(INTDIR)\fidoaddr.obj"
    -@erase "$(INTDIR)\fidoaddr.sbr"
    -@erase "$(INTDIR)\filebox.obj"
    -@erase "$(INTDIR)\filebox.sbr"
    -@erase "$(INTDIR)\getopt.obj"
    -@erase "$(INTDIR)\getopt.sbr"
    -@erase "$(INTDIR)\help.obj"
    -@erase "$(INTDIR)\help.sbr"
    -@erase "$(INTDIR)\log.obj"
    -@erase "$(INTDIR)\log.sbr"
    -@erase "$(INTDIR)\mask.obj"
    -@erase "$(INTDIR)\mask.sbr"
    -@erase "$(INTDIR)\msg.obj"
    -@erase "$(INTDIR)\msg.sbr"
    -@erase "$(INTDIR)\msgbase.obj"
    -@erase "$(INTDIR)\msgbase.sbr"
    -@erase "$(INTDIR)\nodelist.obj"
    -@erase "$(INTDIR)\nodelist.sbr"
    -@erase "$(INTDIR)\outbound.obj"
    -@erase "$(INTDIR)\outbound.sbr"
    -@erase "$(INTDIR)\parsetpl.obj"
    -@erase "$(INTDIR)\parsetpl.sbr"
    -@erase "$(INTDIR)\passwd.obj"
    -@erase "$(INTDIR)\passwd.sbr"
    -@erase "$(INTDIR)\pktbase.obj"
    -@erase "$(INTDIR)\pktbase.sbr"
    -@erase "$(INTDIR)\rntrack.obj"
    -@erase "$(INTDIR)\rntrack.sbr"
    -@erase "$(INTDIR)\scandir.obj"
    -@erase "$(INTDIR)\scandir.sbr"
    -@erase "$(INTDIR)\script.obj"
    -@erase "$(INTDIR)\script.sbr"
    -@erase "$(INTDIR)\sqbase.obj"
    -@erase "$(INTDIR)\sqbase.sbr"
    -@erase "$(INTDIR)\string.obj"
    -@erase "$(INTDIR)\string.sbr"
    -@erase "$(INTDIR)\tmstamp.obj"
    -@erase "$(INTDIR)\tmstamp.sbr"
    -@erase "$(INTDIR)\utils.obj"
    -@erase "$(INTDIR)\utils.sbr"
    -@erase "$(INTDIR)\vars.obj"
    -@erase "$(INTDIR)\vars.sbr"
    -@erase "$(INTDIR)\vc60.idb"
    -@erase "$(INTDIR)\vc60.pdb"
    -@erase "$(INTDIR)\wildmat.obj"
    -@erase "$(INTDIR)\wildmat.sbr"
    -@erase "$(OUTDIR)\@@projectName@@.bsc"
    -@erase "$(OUTDIR)\@@projectName@@.exe"
    -@erase "$(OUTDIR)\@@projectName@@.ilk"
    -@erase "$(OUTDIR)\@@projectName@@.map"
    -@erase "$(OUTDIR)\@@projectName@@.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "..\..\..\hpp" /I "..\..\..\src" /I "..\..\..\smapi\h" /I "..\..\..\smapi\src" @@perl_ADD_CPP@@ /D "_CONSOLE" /D "_DEBUG" /D "__NT__" /D "WIN32IOP_H" /D "HAVE_IO_H" /D "WIN32" /D "_MBCS" /D "HAVE_TIME_H" /D "HAVE_SYS_UTIME_H" /D "HAVE_LOCALE_H" /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

RSC=rc.exe
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\@@projectName@@.bsc" 
BSC32_SBRS= \
    "$(INTDIR)\age.sbr" \
    "$(INTDIR)\aix_conv.sbr" \
    "$(INTDIR)\aka.sbr" \
    "$(INTDIR)\attach.sbr" \
    "$(INTDIR)\badmsg.sbr" \
    "$(INTDIR)\badpkt.sbr" \
    "$(INTDIR)\cfg.sbr" \
    "$(INTDIR)\configure.sbr" \
    "$(INTDIR)\dirent.sbr" \
    "$(INTDIR)\domain.sbr" \
    "$(INTDIR)\fidoaddr.sbr" \
    "$(INTDIR)\filebox.sbr" \
    "$(INTDIR)\getopt.sbr" \
    "$(INTDIR)\help.sbr" \
    "$(INTDIR)\log.sbr" \
    "$(INTDIR)\mask.sbr" \
    "$(INTDIR)\msg.sbr" \
    "$(INTDIR)\msgbase.sbr" \
    "$(INTDIR)\nodelist.sbr" \
    "$(INTDIR)\outbound.sbr" \
    "$(INTDIR)\parsetpl.sbr" \
    "$(INTDIR)\passwd.sbr" \
    "$(INTDIR)\pktbase.sbr" \
    "$(INTDIR)\rntrack.sbr" \
    "$(INTDIR)\scandir.sbr" \
    "$(INTDIR)\script.sbr" \
    "$(INTDIR)\sqbase.sbr" \
    "$(INTDIR)\string.sbr" \
    "$(INTDIR)\tmstamp.sbr" \
    "$(INTDIR)\utils.sbr" \
    "$(INTDIR)\vars.sbr" \
    "$(INTDIR)\wildmat.sbr"

"$(OUTDIR)\@@projectName@@.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib @@perl_ADD_LINK32@@ /nologo /version:1.17 /subsystem:console /incremental:yes /pdb:"$(OUTDIR)\@@projectName@@.pdb" /map:"$(INTDIR)\@@projectName@@.map" /debug /machine:I386 /out:"$(OUTDIR)\@@projectName@@.exe" /pdbtype:sept 
LINK32_OBJS= \
    "$(INTDIR)\age.obj" \
    "$(INTDIR)\aix_conv.obj" \
    "$(INTDIR)\aka.obj" \
    "$(INTDIR)\attach.obj" \
    "$(INTDIR)\badmsg.obj" \
    "$(INTDIR)\badpkt.obj" \
    "$(INTDIR)\cfg.obj" \
    "$(INTDIR)\configure.obj" \
    "$(INTDIR)\dirent.obj" \
    "$(INTDIR)\domain.obj" \
    "$(INTDIR)\fidoaddr.obj" \
    "$(INTDIR)\filebox.obj" \
    "$(INTDIR)\getopt.obj" \
    "$(INTDIR)\help.obj" \
    "$(INTDIR)\log.obj" \
    "$(INTDIR)\mask.obj" \
    "$(INTDIR)\msg.obj" \
    "$(INTDIR)\msgbase.obj" \
    "$(INTDIR)\nodelist.obj" \
    "$(INTDIR)\outbound.obj" \
    "$(INTDIR)\parsetpl.obj" \
    "$(INTDIR)\passwd.obj" \
    "$(INTDIR)\pktbase.obj" \
    "$(INTDIR)\rntrack.obj" \
    "$(INTDIR)\scandir.obj" \
    "$(INTDIR)\script.obj" \
    "$(INTDIR)\sqbase.obj" \
    "$(INTDIR)\string.obj" \
    "$(INTDIR)\tmstamp.obj" \
    "$(INTDIR)\utils.obj" \
    "$(INTDIR)\vars.obj" \
    "$(INTDIR)\wildmat.obj" \
    ".\smapi\Debug\smapi.lib"

"$(OUTDIR)\@@projectName@@.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(CFG)" == "@@projectName@@ - Win32 Release" || "$(CFG)" == "@@projectName@@ - Win32 Debug"
SOURCE=..\..\..\src\age.cpp

!IF  "$(CFG)" == "@@projectName@@ - Win32 Release"


"$(INTDIR)\age.obj" : $(SOURCE) "$(INTDIR)"
    $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "@@projectName@@ - Win32 Debug"


"$(INTDIR)\age.obj" "$(INTDIR)\age.sbr" : $(SOURCE) "$(INTDIR)"
    $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\src\aix_conv.cpp

!IF  "$(CFG)" == "@@projectName@@ - Win32 Release"


"$(INTDIR)\aix_conv.obj" : $(SOURCE) "$(INTDIR)"
    $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "@@projectName@@ - Win32 Debug"


"$(INTDIR)\aix_conv.obj"    "$(INTDIR)\aix_conv.sbr" : $(SOURCE) "$(INTDIR)"
    $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\src\aka.cpp

!IF  "$(CFG)" == "@@projectName@@ - Win32 Release"


"$(INTDIR)\aka.obj" : $(SOURCE) "$(INTDIR)"
    $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "@@projectName@@ - Win32 Debug"


"$(INTDIR)\aka.obj" "$(INTDIR)\aka.sbr" : $(SOURCE) "$(INTDIR)"
    $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\src\attach.cpp

!IF  "$(CFG)" == "@@projectName@@ - Win32 Release"


"$(INTDIR)\attach.obj" : $(SOURCE) "$(INTDIR)"
    $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "@@projectName@@ - Win32 Debug"


"$(INTDIR)\attach.obj"  "$(INTDIR)\attach.sbr" : $(SOURCE) "$(INTDIR)"
    $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\src\badmsg.cpp

!IF  "$(CFG)" == "@@projectName@@ - Win32 Release"


"$(INTDIR)\badmsg.obj" : $(SOURCE) "$(INTDIR)"
    $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "@@projectName@@ - Win32 Debug"


"$(INTDIR)\badmsg.obj"  "$(INTDIR)\badmsg.sbr" : $(SOURCE) "$(INTDIR)"
    $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\src\badpkt.cpp

!IF  "$(CFG)" == "@@projectName@@ - Win32 Release"


"$(INTDIR)\badpkt.obj" : $(SOURCE) "$(INTDIR)"
    $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "@@projectName@@ - Win32 Debug"


"$(INTDIR)\badpkt.obj"  "$(INTDIR)\badpkt.sbr" : $(SOURCE) "$(INTDIR)"
    $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\src\cfg.cpp

!IF  "$(CFG)" == "@@projectName@@ - Win32 Release"


"$(INTDIR)\cfg.obj" : $(SOURCE) "$(INTDIR)"
    $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "@@projectName@@ - Win32 Debug"


"$(INTDIR)\cfg.obj" "$(INTDIR)\cfg.sbr" : $(SOURCE) "$(INTDIR)"
    $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\src\configure.cpp

!IF  "$(CFG)" == "@@projectName@@ - Win32 Release"


"$(INTDIR)\configure.obj" : $(SOURCE) "$(INTDIR)"
    $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "@@projectName@@ - Win32 Debug"


"$(INTDIR)\configure.obj"   "$(INTDIR)\configure.sbr" : $(SOURCE) "$(INTDIR)"
    $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\src\dirent.c

!IF  "$(CFG)" == "@@projectName@@ - Win32 Release"


"$(INTDIR)\dirent.obj" : $(SOURCE) "$(INTDIR)"
    $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "@@projectName@@ - Win32 Debug"


"$(INTDIR)\dirent.obj"  "$(INTDIR)\dirent.sbr" : $(SOURCE) "$(INTDIR)"
    $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\src\domain.cpp

!IF  "$(CFG)" == "@@projectName@@ - Win32 Release"


"$(INTDIR)\domain.obj" : $(SOURCE) "$(INTDIR)"
    $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "@@projectName@@ - Win32 Debug"


"$(INTDIR)\domain.obj"  "$(INTDIR)\domain.sbr" : $(SOURCE) "$(INTDIR)"
    $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\src\fidoaddr.cpp

!IF  "$(CFG)" == "@@projectName@@ - Win32 Release"


"$(INTDIR)\fidoaddr.obj" : $(SOURCE) "$(INTDIR)"
    $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "@@projectName@@ - Win32 Debug"


"$(INTDIR)\fidoaddr.obj"    "$(INTDIR)\fidoaddr.sbr" : $(SOURCE) "$(INTDIR)"
    $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\src\filebox.cpp

!IF  "$(CFG)" == "@@projectName@@ - Win32 Release"


"$(INTDIR)\filebox.obj" : $(SOURCE) "$(INTDIR)"
    $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "@@projectName@@ - Win32 Debug"


"$(INTDIR)\filebox.obj" "$(INTDIR)\filebox.sbr" : $(SOURCE) "$(INTDIR)"
    $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\src\getopt.cpp

!IF  "$(CFG)" == "@@projectName@@ - Win32 Release"


"$(INTDIR)\getopt.obj" : $(SOURCE) "$(INTDIR)"
    $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "@@projectName@@ - Win32 Debug"


"$(INTDIR)\getopt.obj"  "$(INTDIR)\getopt.sbr" : $(SOURCE) "$(INTDIR)"
    $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\src\help.cpp

!IF  "$(CFG)" == "@@projectName@@ - Win32 Release"


"$(INTDIR)\help.obj" : $(SOURCE) "$(INTDIR)"
    $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "@@projectName@@ - Win32 Debug"


"$(INTDIR)\help.obj"    "$(INTDIR)\help.sbr" : $(SOURCE) "$(INTDIR)"
    $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\src\log.cpp

!IF  "$(CFG)" == "@@projectName@@ - Win32 Release"


"$(INTDIR)\log.obj" : $(SOURCE) "$(INTDIR)"
    $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "@@projectName@@ - Win32 Debug"


"$(INTDIR)\log.obj" "$(INTDIR)\log.sbr" : $(SOURCE) "$(INTDIR)"
    $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\src\mask.cpp

!IF  "$(CFG)" == "@@projectName@@ - Win32 Release"


"$(INTDIR)\mask.obj" : $(SOURCE) "$(INTDIR)"
    $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "@@projectName@@ - Win32 Debug"


"$(INTDIR)\mask.obj"    "$(INTDIR)\mask.sbr" : $(SOURCE) "$(INTDIR)"
    $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\src\msg.cpp

!IF  "$(CFG)" == "@@projectName@@ - Win32 Release"


"$(INTDIR)\msg.obj" : $(SOURCE) "$(INTDIR)"
    $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "@@projectName@@ - Win32 Debug"


"$(INTDIR)\msg.obj" "$(INTDIR)\msg.sbr" : $(SOURCE) "$(INTDIR)"
    $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\src\msgbase.cpp

!IF  "$(CFG)" == "@@projectName@@ - Win32 Release"


"$(INTDIR)\msgbase.obj" : $(SOURCE) "$(INTDIR)"
    $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "@@projectName@@ - Win32 Debug"


"$(INTDIR)\msgbase.obj" "$(INTDIR)\msgbase.sbr" : $(SOURCE) "$(INTDIR)"
    $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\src\nodelist.cpp

!IF  "$(CFG)" == "@@projectName@@ - Win32 Release"


"$(INTDIR)\nodelist.obj" : $(SOURCE) "$(INTDIR)"
    $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "@@projectName@@ - Win32 Debug"


"$(INTDIR)\nodelist.obj"    "$(INTDIR)\nodelist.sbr" : $(SOURCE) "$(INTDIR)"
    $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\src\outbound.cpp

!IF  "$(CFG)" == "@@projectName@@ - Win32 Release"


"$(INTDIR)\outbound.obj" : $(SOURCE) "$(INTDIR)"
    $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "@@projectName@@ - Win32 Debug"


"$(INTDIR)\outbound.obj"    "$(INTDIR)\outbound.sbr" : $(SOURCE) "$(INTDIR)"
    $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\src\parsetpl.cpp

!IF  "$(CFG)" == "@@projectName@@ - Win32 Release"


"$(INTDIR)\parsetpl.obj" : $(SOURCE) "$(INTDIR)"
    $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "@@projectName@@ - Win32 Debug"


"$(INTDIR)\parsetpl.obj"    "$(INTDIR)\parsetpl.sbr" : $(SOURCE) "$(INTDIR)"
    $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\src\passwd.cpp

!IF  "$(CFG)" == "@@projectName@@ - Win32 Release"


"$(INTDIR)\passwd.obj" : $(SOURCE) "$(INTDIR)"
    $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "@@projectName@@ - Win32 Debug"


"$(INTDIR)\passwd.obj"  "$(INTDIR)\passwd.sbr" : $(SOURCE) "$(INTDIR)"
    $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\src\pktbase.cpp

!IF  "$(CFG)" == "@@projectName@@ - Win32 Release"


"$(INTDIR)\pktbase.obj" : $(SOURCE) "$(INTDIR)"
    $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "@@projectName@@ - Win32 Debug"


"$(INTDIR)\pktbase.obj" "$(INTDIR)\pktbase.sbr" : $(SOURCE) "$(INTDIR)"
    $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\src\rntrack.cpp

!IF  "$(CFG)" == "@@projectName@@ - Win32 Release"


"$(INTDIR)\rntrack.obj" : $(SOURCE) "$(INTDIR)"
    $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "@@projectName@@ - Win32 Debug"


"$(INTDIR)\rntrack.obj" "$(INTDIR)\rntrack.sbr" : $(SOURCE) "$(INTDIR)"
    $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\src\scandir.cpp

!IF  "$(CFG)" == "@@projectName@@ - Win32 Release"


"$(INTDIR)\scandir.obj" : $(SOURCE) "$(INTDIR)"
    $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "@@projectName@@ - Win32 Debug"


"$(INTDIR)\scandir.obj" "$(INTDIR)\scandir.sbr" : $(SOURCE) "$(INTDIR)"
    $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\src\script.cpp

!IF  "$(CFG)" == "@@projectName@@ - Win32 Release"


"$(INTDIR)\script.obj" : $(SOURCE) "$(INTDIR)"
    $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "@@projectName@@ - Win32 Debug"


"$(INTDIR)\script.obj"  "$(INTDIR)\script.sbr" : $(SOURCE) "$(INTDIR)"
    $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\src\sqbase.cpp

!IF  "$(CFG)" == "@@projectName@@ - Win32 Release"


"$(INTDIR)\sqbase.obj" : $(SOURCE) "$(INTDIR)"
    $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "@@projectName@@ - Win32 Debug"


"$(INTDIR)\sqbase.obj"  "$(INTDIR)\sqbase.sbr" : $(SOURCE) "$(INTDIR)"
    $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\src\string.cpp

!IF  "$(CFG)" == "@@projectName@@ - Win32 Release"


"$(INTDIR)\string.obj" : $(SOURCE) "$(INTDIR)"
    $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "@@projectName@@ - Win32 Debug"


"$(INTDIR)\string.obj"  "$(INTDIR)\string.sbr" : $(SOURCE) "$(INTDIR)"
    $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\src\tmstamp.cpp

!IF  "$(CFG)" == "@@projectName@@ - Win32 Release"


"$(INTDIR)\tmstamp.obj" : $(SOURCE) "$(INTDIR)"
    $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "@@projectName@@ - Win32 Debug"


"$(INTDIR)\tmstamp.obj" "$(INTDIR)\tmstamp.sbr" : $(SOURCE) "$(INTDIR)"
    $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\src\utils.cpp

!IF  "$(CFG)" == "@@projectName@@ - Win32 Release"


"$(INTDIR)\utils.obj" : $(SOURCE) "$(INTDIR)"
    $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "@@projectName@@ - Win32 Debug"


"$(INTDIR)\utils.obj"   "$(INTDIR)\utils.sbr" : $(SOURCE) "$(INTDIR)"
    $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\src\vars.cpp

!IF  "$(CFG)" == "@@projectName@@ - Win32 Release"


"$(INTDIR)\vars.obj" : $(SOURCE) "$(INTDIR)"
    $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "@@projectName@@ - Win32 Debug"


"$(INTDIR)\vars.obj"    "$(INTDIR)\vars.sbr" : $(SOURCE) "$(INTDIR)"
    $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\src\wildmat.cpp

!IF  "$(CFG)" == "@@projectName@@ - Win32 Release"


"$(INTDIR)\wildmat.obj" : $(SOURCE) "$(INTDIR)"
    $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "@@projectName@@ - Win32 Debug"


"$(INTDIR)\wildmat.obj" "$(INTDIR)\wildmat.sbr" : $(SOURCE) "$(INTDIR)"
    $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

!IF  "$(CFG)" == "@@projectName@@ - Win32 Release"

"smapi - Win32 Release" : 
   cd ".\smapi"
   $(MAKE) /$(MAKEFLAGS) /F .\smapi.mak CFG="smapi - Win32 Release" 
   cd ".."

"smapi - Win32 ReleaseCLEAN" : 
   cd ".\smapi"
   $(MAKE) /$(MAKEFLAGS) /F .\smapi.mak CFG="smapi - Win32 Release" RECURSE=1 CLEAN 
   cd ".."

!ELSEIF  "$(CFG)" == "@@projectName@@ - Win32 Debug"

"smapi - Win32 Debug" : 
   cd ".\smapi"
   $(MAKE) /$(MAKEFLAGS) /F .\smapi.mak CFG="smapi - Win32 Debug" 
   cd ".."

"smapi - Win32 DebugCLEAN" : 
   cd ".\smapi"
   $(MAKE) /$(MAKEFLAGS) /F .\smapi.mak CFG="smapi - Win32 Debug" RECURSE=1 CLEAN 
   cd ".."

!ENDIF 


!ENDIF 


*/};



/////////////////////////////////////////////////////////////////////
//                                                                 // 
//                           Main program                          //
//                                                                 // 
/////////////////////////////////////////////////////////////////////

var msvcDir = readFromRegistry("HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\VisualStudio\\6.0\\Setup\\Microsoft Visual C++\\ProductDir", "");

if(msvcDir == "")
{
    WScript.Echo("Cannot find MS Visual Studio 6.0");
}
else
{
    var vcvars32 = msvcDir + "\\Bin\\VCVARS32.BAT";
    var fsObj = WScript.CreateObject("Scripting.FileSystemObject")
    if(!fsObj.FileExists(vcvars32))
    {
        WScript.Echo("You did not generate VCVARS32.BAT during Visual Studio installation. Please do it.");
    }
    else
    {
        var projName = 'rntrack';
        var makefileName = "makefile";
        var makefileExt = ".vc6";
        var scriptFullName = WScript.ScriptFullName;
        var posBackslash = scriptFullName.lastIndexOf("\\");
        var scriptPath = scriptFullName.substring(0, posBackslash + 1);
        
        // Generate build.bat
        var call_vcvars32 = 'call "' + vcvars32 +'"';
        var s_build_bat = GetHereDoc(build_bat);
        s_build_bat = s_build_bat.replace(/@@build_comment@@/, GetHereDoc(build_comment));
        s_build_bat = s_build_bat.replace(/@@buildEnv@@/, call_vcvars32);
        s_build_bat = s_build_bat.replace(/@@clean_smapi@@\r\n/, "");
        s_build_bat = s_build_bat.replace(/@@clean_rntrack@@\r\n/, "");
        s_build_bat = s_build_bat.replace(/@@makefileName@@/g, makefileName);
        s_build_bat = s_build_bat.replace(/@@makefileExt@@/g, makefileExt);
        s_build_bat = s_build_bat.replace(/@@projectName@@/g, projName);
        WriteToFile(scriptPath + "build.bat", s_build_bat, FileFormatASCII);

        // Generate rebuild.bat
        s_build_bat = GetHereDoc(build_bat);
        s_build_bat = s_build_bat.replace(/@@build_comment@@/, GetHereDoc(rebuild_comment));
        s_build_bat = s_build_bat.replace(/@@buildEnv@@/, call_vcvars32);
        s_build_bat = s_build_bat.replace(/@@clean_smapi@@/, GetHereDoc(clean_smapi));
        var s_clean_rntrack = GetHereDoc(clean_rntrack);
        s_build_bat = s_build_bat.replace(/@@clean_rntrack@@/, s_clean_rntrack);
        s_build_bat = s_build_bat.replace(/@@makefileName@@/g, makefileName);
        s_build_bat = s_build_bat.replace(/@@makefileExt@@/g, makefileExt);
        s_build_bat = s_build_bat.replace(/@@projectName@@/g, projName);
        WriteToFile(scriptPath + "rebuild.bat", s_build_bat, FileFormatASCII);

        // Generate rntrack.dsp
        var perl_ADD_CPP = "";
        var perl_ADD_LINK32 = "";
        var s_rntrack_dsp = GetHereDoc(rntrack_dsp);
        s_rntrack_dsp = s_rntrack_dsp.replace(/@@projectName@@/g, projName);
        s_rntrack_dsp = s_rntrack_dsp.replace(/@@perl_ADD_CPP@@ /g, perl_ADD_CPP);
        s_rntrack_dsp = s_rntrack_dsp.replace(/@@perl_ADD_LINK32@@ /g, perl_ADD_LINK32);
        WriteToFile(scriptPath + projName + ".dsp", s_rntrack_dsp, FileFormatASCII);
        
        // Generate rntrack.dsw
        var s_rntrack_dsw = GetHereDoc(rntrack_dsw);
        s_rntrack_dsw = s_rntrack_dsw.replace(/@@projectName@@/g, projName);
        WriteToFile(scriptPath + projName + ".dsw", s_rntrack_dsw, FileFormatASCII);

        // Generate makefile.vc6
        var s_makefile_vc6 = GetHereDoc(makefile_vc6);
        s_makefile_vc6 = s_makefile_vc6.replace(/@@projectName@@/g, projName);
        s_makefile_vc6 = s_makefile_vc6.replace(/@@makefileName@@/g, makefileName);
        s_makefile_vc6 = s_makefile_vc6.replace(/@@makefileExt@@/g, makefileExt);
        s_makefile_vc6 = s_makefile_vc6.replace(/@@perl_ADD_CPP@@ /g, perl_ADD_CPP);
        s_makefile_vc6 = s_makefile_vc6.replace(/@@perl_ADD_LINK32@@ /g, perl_ADD_LINK32);
        WriteToFile(scriptPath + makefileName + makefileExt, s_makefile_vc6, FileFormatASCII);
    
        // Read ActiveState Perl program directory from registry
        var perlReg = "HKEY_LOCAL_MACHINE\\SOFTWARE\\ActiveState\\ActivePerl\\";
        var perlVer = readFromRegistry(perlReg + "CurrentVersion", "");
        if(perlVer == "")
        {
            WScript.Echo("ActiveState Perl is not installed");
            WScript.Quit(0);
        }

        // Read the directory where Perl is installed
        var perlPath = readFromRegistry(perlReg + perlVer + "\\", "");
        // Prepare perlconf - a Perl script producing
        // the Perl environment variables
        var perlvars = GetHereDoc(perlconf);
        perlvars = perlvars.replace(/[\r\n]+/g, "");
        perlvars = perlvars.replace(/"/g, '\\\"');
        perlvars = perlvars.replace(/@@dquote@@/g, '\\\"');
        // Perl environment variables will be written
        // to a temporary file "perlvars.js"
        var perlvarsPath = AppendPath(scriptPath, "perlvars.js");
        perlvars = perlvars.replace(/@@file@@/g, perlvarsPath);
        
        // Run perlconf to create perlvars.js with declarations
        // of perl config variables
        var cmd = 'perl -e "' + perlvars + '"';
        var exitCode = RunCmd(cmd);
        if(exitCode > 0)
        {
            WScript.Echo("Error at running " + cmd);
            WScript.Quit(1);
        }
        else
        {
            var perl_incl, perl_lib, perl_version, perl_major, perl_minor;
            // Retrieve the values of the variables declared in the previous line
            var js_line = ReadFromFile(perlvarsPath);
            if(js_line == "")
            {
                WScript.Echo("Cannot read perl variables");
                WScript.Quit(1);
            }
            with (js_line)
            {
                eval(js_line);
            }
            // Check that some values were assigned
            if(typeof(perl_incl) == "undefined" || 
               typeof(perl_lib) == "undefined" ||
               typeof(perl_version) == "undefined" || 
               typeof(perl_major) == "undefined" ||
               typeof(perl_minor) == "undefined")
            {
                WScript.Echo("Perl variables have got no values");
                WScript.Quit(1);
            }
                            
            DeleteFile(perlvarsPath);
            
            projName = 'rntrack_perl';
            makefileName = "makeperl";
            makefileExt = ".vc6";
            
            perl_incl = AppendPath(perlPath, perl_incl);
            perl_incl = AppendPath(perl_incl, "CORE");
            
            // Generate build_perl.bat
            s_build_bat = GetHereDoc(build_bat);
            s_build_bat = s_build_bat.replace(/@@build_comment@@/, GetHereDoc(build_perl_comment));
            s_build_bat = s_build_bat.replace(/@@buildEnv@@/, call_vcvars32);
            s_build_bat = s_build_bat.replace(/@@clean_smapi@@\r\n/, "");
            s_build_bat = s_build_bat.replace(/@@clean_rntrack@@\r\n/, "");
            s_build_bat = s_build_bat.replace(/@@makefileName@@/g, makefileName);
            s_build_bat = s_build_bat.replace(/@@makefileExt@@/g, makefileExt);
            s_build_bat = s_build_bat.replace(/@@projectName@@/g, projName);
            WriteToFile(scriptPath + "build_perl.bat", s_build_bat, FileFormatASCII);

            // Generate rebuild_perl.bat
            s_build_bat = GetHereDoc(build_bat);
            s_build_bat = s_build_bat.replace(/@@build_comment@@/, GetHereDoc(rebuild_perl_comment));
            s_build_bat = s_build_bat.replace(/@@buildEnv@@/, call_vcvars32);
            s_build_bat = s_build_bat.replace(/@@clean_smapi@@/, GetHereDoc(clean_smapi));
            s_clean_rntrack = GetHereDoc(clean_rntrack);
            s_build_bat = s_build_bat.replace(/@@clean_rntrack@@/, s_clean_rntrack);
            s_build_bat = s_build_bat.replace(/@@makefileName@@/g, makefileName);
            s_build_bat = s_build_bat.replace(/@@makefileExt@@/g, makefileExt);
            s_build_bat = s_build_bat.replace(/@@projectName@@/g, projName);
            WriteToFile(scriptPath + "rebuild_perl.bat", s_build_bat, FileFormatASCII);

            // Generate rntrack_perl.dsp
            perl_ADD_CPP = "/I \"" + perl_incl + '"';
            perl_ADD_CPP += " /D __PERL_VERSION__=" + perl_version;
            perl_ADD_CPP += " /D __PERL_MAJOR__=" + perl_major;
            perl_ADD_CPP += " /D __PERL_MINOR__=" + perl_minor;
            perl_ADD_LINK32 = perl_lib + " /libpath:\"" + perl_incl + '"';
            s_rntrack_dsp = GetHereDoc(rntrack_dsp);
            s_rntrack_dsp = s_rntrack_dsp.replace(/@@projectName@@/g, projName);
            s_rntrack_dsp = s_rntrack_dsp.replace(/@@perl_ADD_CPP@@/g, perl_ADD_CPP);
            s_rntrack_dsp = s_rntrack_dsp.replace(/@@perl_ADD_LINK32@@/g, perl_ADD_LINK32);
            WriteToFile(scriptPath + projName + ".dsp", s_rntrack_dsp, FileFormatASCII);
            
            // Generate rntrack_perl.dsw
            var s_rntrack_dsw = GetHereDoc(rntrack_dsw);
            s_rntrack_dsw = s_rntrack_dsw.replace(/@@projectName@@/g, projName);
            WriteToFile(scriptPath + projName + ".dsw", s_rntrack_dsw, FileFormatASCII);

            // Generate makeperl.vc6
            var s_makefile_vc6 = GetHereDoc(makefile_vc6);
            s_makefile_vc6 = s_makefile_vc6.replace(/@@projectName@@/g, projName);
            s_makefile_vc6 = s_makefile_vc6.replace(/@@makefileName@@/g, makefileName);
            s_makefile_vc6 = s_makefile_vc6.replace(/@@makefileExt@@/g, makefileExt);
            s_makefile_vc6 = s_makefile_vc6.replace(/@@perl_ADD_CPP@@/g, perl_ADD_CPP);
            s_makefile_vc6 = s_makefile_vc6.replace(/@@perl_ADD_LINK32@@/g, perl_ADD_LINK32);
            WriteToFile(scriptPath + makefileName + makefileExt, s_makefile_vc6, FileFormatASCII);
        }
    }
}
