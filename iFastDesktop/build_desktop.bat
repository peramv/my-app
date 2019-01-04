:: This is clean and build stage on the build process

@echo on

@SET FrameworkDir=C:\Windows\Microsoft.NET\Framework\v4.0.30319


:: Delete "Disk Images" Directory and all contents
:: Delete shipset directory 

rmdir /Q /S "Disk Images"
rmdir /Q /S "shipset"
rmdir /Q /S "distrib"


:: Lets start clean

"%FrameworkDir%\msbuild" "ifastgui.sln" /t:Clean /p:Configuration=Release /p:Platform=Win32 /flp:logfile=devenv_out.txt


:: Update version_app.cpp
:: Nasty perl hack to get svn revison

perl -e "@result = `svn info`; @grepResult = grep( /Revision/, @result); @splitResults = split(/: /, $grepResult[0]); print $splitResults[1];" > svnrev.txt
for /f %%i in (svnrev.txt) do set SVNREV=%%i 
perl dtop_brander.pl --rev=%SVNREV%


:: Compare resource files

@echo If result of comparing resource files is not 0 (zero), the build will be stoped. 

perl rccompare.pl "ifastgui\resCanada\ResCanada.rc" "ifastgui\resCanadaFr\ResCanadaFr.rc" 

@echo Result of comparing resource files "ResCanada.rc vs. ResCanadaFr.rc" is: "%ERRORLEVEL%" 
@if not "%ERRORLEVEL%" == "0" goto :eof

perl rccompare.pl "ifastgui\resCommon\ResCommon.rc" "ifastgui\resCommonFr\ResCommonFr.rc" 

@echo Result of comparing resource files "ResCommon.rc vs. ResCommonFr.rc" is: "%ERRORLEVEL%" 
@if not "%ERRORLEVEL%" == "0" goto :eof 


:: Build the projects

"%FrameworkDir%\msbuild" "ifastgui.sln" /t:"Resource - Related Projects\ResCanada" /p:Configuration=Release /p:Platform=Win32 /flp:logfile=devenv_out.txt

:: Check if build succeeded

@echo off
set BUILD_STATUS=%ERRORLEVEL%
if %BUILD_STATUS%==0 echo Build success  
if not %BUILD_STATUS%==0  echo Build failed  
:: If build failed exit immediately
if not %BUILD_STATUS%==0  goto :eof 
@echo on


"%FrameworkDir%\msbuild" "ifastgui.sln" /t:"Resource - Related Projects\ResDll" /p:Configuration=Release /p:Platform=Win32 /flp:logfile=devenv_out.txt

:: Check if build succeeded

@echo off
set BUILD_STATUS=%ERRORLEVEL%
if %BUILD_STATUS%==0 echo Build success  
if not %BUILD_STATUS%==0  echo Build failed  
:: If build failed exit immediately
if not %BUILD_STATUS%==0  goto :eof 
@echo on
del /Q ifastgui\resDll\Release\canada_eng.dll
ren ifastgui\resDll\Release\ResDll.dll canada_eng.dll


"%FrameworkDir%\msbuild" "ifastgui.sln" /t:"Resource - Related Projects\ResCanadaFr" /p:Configuration=Release /p:Platform=Win32 /flp:logfile=devenv_out.txt

:: Check if build succeeded

@echo off
set BUILD_STATUS=%ERRORLEVEL%
if %BUILD_STATUS%==0 echo Build success  
if not %BUILD_STATUS%==0  echo Build failed  
:: If build failed exit immediately
if not %BUILD_STATUS%==0  goto :eof 
@echo on


"%FrameworkDir%\msbuild" "ifastgui.sln" /t:"Resource - Related Projects\ResDll" /p:Configuration=Release /p:Platform=Win32 /flp:logfile=devenv_out.txt

:: Check if build succeeded

@echo off
set BUILD_STATUS=%ERRORLEVEL%
if %BUILD_STATUS%==0 echo Build success  
if not %BUILD_STATUS%==0  echo Build failed  
:: If build failed exit immediately
if not %BUILD_STATUS%==0  goto :eof 
@echo on
del /Q ifastgui\resDll\Release\canada_fr.dll
ren ifastgui\resDll\Release\ResDll.dll canada_fr.dll


"%FrameworkDir%\msbuild" "ifastgui.sln" /t:"Resource - Related Projects\ResEurope" /p:Configuration=Release /p:Platform=Win32 /flp:logfile=devenv_out.txt

:: Check if build succeeded

@echo off
set BUILD_STATUS=%ERRORLEVEL%
if %BUILD_STATUS%==0 echo Build success  
if not %BUILD_STATUS%==0  echo Build failed  
:: If build failed exit immediately
if not %BUILD_STATUS%==0  goto :eof 
@echo on


"%FrameworkDir%\msbuild" "ifastgui.sln" /t:"Resource - Related Projects\ResDll" /p:Configuration=Release /p:Platform=Win32 /flp:logfile=devenv_out.txt

:: Check if build succeeded

@echo off
set BUILD_STATUS=%ERRORLEVEL%
if %BUILD_STATUS%==0 echo Build success  
if not %BUILD_STATUS%==0  echo Build failed  
:: If build failed exit immediately
if not %BUILD_STATUS%==0  goto :eof 
@echo on
del /Q ifastgui\resDll\Release\lux_eng.dll
ren ifastgui\resDll\Release\ResDll.dll lux_eng.dll


"%FrameworkDir%\msbuild" "ifastgui.sln" /p:Configuration=Release /p:Platform=Win32 /flp:logfile=devenv_out.txt

:: Check if build succeeded

@echo off
set BUILD_STATUS=%ERRORLEVEL%
if %BUILD_STATUS%==0 echo Build success  
if not %BUILD_STATUS%==0  echo Build failed  
:: If build failed exit immediately
if not %BUILD_STATUS%==0  goto :eof 
@echo on


:: Create new shipset folder structure

mkdir shipset
mkdir "shipset\win32"
mkdir "shipset\csi"
mkdir "shipset\data"
mkdir "shipset\data\config"

:: Move files into shipset directories

copy "bin\release\*.dll" "shipset\win32"
copy "bin\release\*.exe" "shipset\win32"
copy "bin\release\*.ocx" "shipset\win32"

copy "ifastcsi\ifast.ek*" "shipset\csi"
copy "ifastcsi\guicbie.*" "shipset\csi"

copy "data\*.cnd" "shipset\data"
copy "data\databroker.bin" "shipset\data"
copy "data\*.chm" "shipset\data"
copy "data\*.avi" "shipset\data"
copy "data\config\*" "shipset\data\config"

copy "ifastgui\Road.ico" "shipset\win32"
copy "ifastgui\RoadDoc.ico" "shipset\win32"
copy "ifastgui\resDll\Release\canada_eng.dll" "shipset\win32"
copy "ifastgui\resDll\Release\canada_fr.dll" "shipset\win32"
copy "ifastgui\resDll\Release\lux_eng.dll" "shipset\win32"
copy "ifastcsi\ifast.etb" "shipset\csi"


:: Create zip files

mkdir distrib


:: Delete old setup files

del NSIS_Installer\Setup.exe
del NSIS_Installer\*.zip

set /p Build=<version.txt


:: Create NSIS based installation package

"C:\Program Files (x86)\NSIS\makensis" /Dbuild=%Build% "NSIS_Installer\ifast_desktop.nsi"


:: Get current date

@For /F "tokens=2,3,4 delims=/ " %%A in ('Date /t') do @( 
    Set Month=%%A
    Set Day=%%B
    Set Year=%%C
)

"C:\Program Files (x86)\7-Zip\7z" a NSIS_Installer\iFAST_Desktop_%Build%_%Year%_%Month%_%Day%.zip .\NSIS_Installer\Setup.exe

copy "NSIS_Installer\iFAST_Desktop_%Build%_%Year%_%Month%_%Day%.zip" "distrib"

@net use l: \\172.18.2.6\Scmpvcs\Jenkins_Desktop_Build /user:dstcorfax\subversionbuild 8ui1d@1!

@copy /Y distrib\*.zip l:

@net use l: /d

echo Build Successul
