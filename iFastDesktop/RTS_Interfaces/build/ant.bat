@echo off

@SET IFASTDESKTOP_PATH=%cd%

call %ANT_HOME%\bin\ant -buildfile %IFASTDESKTOP_PATH%\RTS_Interfaces\build\build.xml

echo Ant build finished
