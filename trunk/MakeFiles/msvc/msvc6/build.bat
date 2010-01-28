rem
rem The build.bat is used to build RNTrack
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
NMAKE /f "rntrack.mak" CFG="rntrack - Win32 Release" >> build.log 2>&1
if errorlevel 1 goto Error
echo. >> build.log
echo ############## rntrack.exe is successfully built ############## >> build.log
:Error
