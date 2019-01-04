@echo off
setlocal

set _project=mfcan

echo Cleaning %_project%_dataimpl...
nmake /nologo /f \dstcprojects\businesscomponents\%_project%\%_project%_dataimpl\%_project%_dataimpl_gen.mak CLEAN 

goto byebye

:byebye
endlocal
