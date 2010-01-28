rem
rem The rebuild.bat is used to build RNTrack
rem preliminary cleaning the old build
rem

date /T > build.log
pushd smapi
echo ############## Cleaning the old smapi build... >> ./../build.log
NMAKE /f "smapi.mak" CFG="smapi - Win32 Release" clean >> ./../build.log 2>&1
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
echo ############## Cleaning the old rntrack build... >> build.log
NMAKE /f "rntrack.mak" CFG="rntrack - Win32 Release" clean >> build.log 2>&1
echo ############## Building rntrack... >> build.log
NMAKE /f "rntrack.mak" CFG="rntrack - Win32 Release" >> build.log 2>&1
if errorlevel 1 goto Error
echo. >> build.log
echo ############## rntrack.exe is successfully built ############## >> build.log
:Error
