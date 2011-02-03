rem $Id:$
rem The buildperl.bat is used to build RNTrack with Activestate's Perl
rem

date /T > build.log
pushd smapi
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
echo ############## Building rntrack... >> build.log
NMAKE /f "rntrack.mak" SCRIPTS_ENABLE=1 CFG="rntrack - Win32 Release" >> build.log 2>&1
if errorlevel 1 goto Error
echo. >> build.log
echo ############## rntrack_perl.exe is successfully built ############## >> build.log
:Error
