echo on
setlocal

rem if "%WEBLOGIC_HOME%" == "" set WEBLOGIC_HOME=c:\bea\weblogic81

rem if not exist "%WEBLOGIC_HOME%\server\bin\setWLSEnv.cmd" goto badexit 

rem call "%WEBLOGIC_HOME%\server\bin\setWLSEnv.cmd"

set classPath
set ANT_OPTS=-Xmx512m

C:\apache-ant-1.6.5\bin\ant -f build.xml %1

goto goodexit

rem :badexit
rem echo WebLogic setWLSEnv.cmd was not found 


:goodexit

endlocal

