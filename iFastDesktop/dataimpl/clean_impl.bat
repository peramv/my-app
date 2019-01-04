@echo off
setlocal
set _cfg=bad
set _project=mfcan

rem Batch File to clean %1_DataImpl_Gen project
if [%1]==[] set _cfg="%_project%_dataimpl - Win32 Debug"
if [%1]==[DEBUG] set _cfg="%_project%_dataimpl - Win32 Debug"
if [%1]==[debug] set _cfg="%_project%_dataimpl - Win32 Debug"
if [%1]==[RELEASE] set _cfg="%_project%_dataimpl - Win32 Release"
if [%1]==[release] set _cfg="%_project%_dataimpl - Win32 Release"
if [%1]==[SH] set _cfg="%_project%_dataimpl - Win32 SmartHeap Release"
if [%1]==[sh] set _cfg="%_project%_dataimpl - Win32 SmartHeap Release"

if [%_cfg%]==[bad] goto badcfg

:clean          
echo Cleaning %_project%_dataimpl...
nmake /nologo /f %_project%_dataimpl.mak CLEAN CFG=%_cfg%

goto byebye

:badcfg
echo Unsupported configuration: %1
goto noargs
:noargs
echo usage: clean_impl [configuration]
echo     where configuration is DEBUG, RELEASE, or SH

goto byebye
:byebye
endlocal
