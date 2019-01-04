# Microsoft Developer Studio Project File - Name="ifastxparser" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=ifastxparser - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "ifastxparser.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ifastxparser.mak" CFG="ifastxparser - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ifastxparser - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "ifastxparser - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "ifastxparser - Win32 SmartHeap Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "ifastxparser - Win32 SmartHeap Symbols" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName "/ifastxparser?PVCS Version Manager?x:\areaproj\bf ifast?"
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "ifastxparser - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "../bin/release"
# PROP BASE Intermediate_Dir "release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "../bin/release"
# PROP Intermediate_Dir "release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "DSTXPARSER_EXPORTS" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GR /GX /O2 /I "." /I ".." /I "../core" /I "../core/ifdscore" /I "../core/ifdscore/win32" /I "../core/3rdparty/boost" /I "../core/3rdparty/xerces" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "DST_UNICODE" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386
# ADD LINK32 xerces-c_2.lib xparser.lib bfproc.lib ifastdbrkr.lib ifastids.lib bfcbo.lib xparser.lib ifastbp.lib bfutil.lib ifdscore.lib bfdata.lib ifast_dataimpl.lib boost_thread.lib boost_regex_vc6_mdi.lib libboost_date_time.lib /nologo /dll /machine:I386 /implib:"../lib/debug/ifastxparser.lib" /libpath:"../lib/debug" /libpath:"../core/3rdparty/xerces" /libpath:"../core/3rdparty/boost/lib"
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Desc=Updating Status
PostBuild_Cmds=if DEFINED _JOBSTATUSFILE echo Finished building ifastxparser (Release) > %_JOBSTATUSFILE% nul
# End Special Build Tool

!ELSEIF  "$(CFG)" == "ifastxparser - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "../bin/debug"
# PROP BASE Intermediate_Dir "debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "../bin/debug"
# PROP Intermediate_Dir "debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "DSTXPARSER_EXPORTS" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GR /GX /ZI /Od /I "." /I ".." /I "../core" /I "../core/ifdscore" /I "../core/ifdscore/win32" /I "../core/3rdparty/boost" /I "../core/3rdparty/xerces" /D "DST_UNICODE" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 xerces-c_2D.lib xparser_d.lib bfproc_d.lib ifastids_d.lib bfcbo_d.lib ifastbp_d.lib ifastdbrkr_d.lib bfutil_d.lib ifdscore_d.lib bfdata_d.lib ifast_dataimpl_d.lib boost_threadd.lib boost_regex_vc6_mdid.lib libboost_date_time.lib /nologo /dll /debug /machine:I386 /out:"../bin/debug/ifastxparser_d.dll" /implib:"../lib/debug/ifastxparser_d.lib" /pdbtype:sept /libpath:"../lib/debug" /libpath:"../core/3rdparty/xerces" /libpath:"../core/3rdparty/boost/lib"
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Desc=Updating Status
PostBuild_Cmds=if DEFINED _JOBSTATUSFILE echo Finished building ifastxparser (Debug) > %_JOBSTATUSFILE% nul
# End Special Build Tool

!ELSEIF  "$(CFG)" == "ifastxparser - Win32 SmartHeap Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "../bin/releaseSH"
# PROP BASE Intermediate_Dir "releaseSH"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "../bin/releaseSH"
# PROP Intermediate_Dir "releaseSH"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GR /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "DST_UNICODE" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GR /GX /O2 /I "." /I ".." /I "../core" /I "../core/ifdscore" /I "../core/ifdscore/win32" /I "../core/3rdparty/boost" /I "../core/3rdparty/xerces" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "DST_UNICODE" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /dll /machine:I386
# ADD LINK32 shdsmpmt.lib xparser_sh.lib xerces-c_2.lib bfproc_sh.lib ifastids_sh.lib bfcbo_sh.lib xparser_sh.lib ifastdbrkr_sh.lib ifastbp_sh.lib bfutil_sh.lib ifdscore_sh.lib bfdata_sh.lib ifast_dataimpl_sh.lib boost_thread.lib boost_regex_vc6_mdi.lib libboost_date_time.lib /nologo /dll /machine:I386 /out:"../bin/releaseSH/ifastxparser_sh.dll" /implib:"../lib/releaseSH/ifastxparser_sh.lib" /libpath:"../lib/releaseSH" /libpath:"../core/3rdparty/smartheap" /libpath:"../core/3rdparty/xerces" /libpath:"../core/3rdparty/boost/lib"
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Desc=Updating Status
PostBuild_Cmds=if DEFINED _JOBSTATUSFILE echo Finished building ifastxparser (SmartHeap Release) > %_JOBSTATUSFILE% nul
# End Special Build Tool

!ELSEIF  "$(CFG)" == "ifastxparser - Win32 SmartHeap Symbols"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "../bin/relSym"
# PROP BASE Intermediate_Dir "relSym"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "../bin/relSym"
# PROP Intermediate_Dir "relSym"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GR /GX /O2 /I "." /I ".." /I "../core" /I "../core/ifdscore" /I "../core/ifdscore/win32" /I "../core/3rdparty/boost" /I "../core/3rdparty/xerces" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "DST_UNICODE" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GR /GX /Zd /I "." /I ".." /I "../core" /I "../core/ifdscore" /I "../core/ifdscore/win32" /I "../core/3rdparty/boost" /I "../core/3rdparty/xerces" /D "_WINDOWS" /D "WIN32" /D "NDEBUG" /D "DST_UNICODE" /D "BFRELSYM" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 shdsmpmt.lib xparser_sym.lib bfproc_sym.lib ifastids_sym.lib bfcbo_sym.lib xparser_sym.lib ifastdbrkr_sym.lib ifastbp_sym.lib bfutil_sym.lib ifdscore_sym.lib bfdata_sym.lib ifast_dataimpl_sym.lib boost_thread.lib boost_regex_vc6_mdi.lib libboost_date_time.lib /nologo /dll /machine:I386 /out:"../bin/relSym/ifastxparser_sym.dll" /implib:"../lib/relSym/ifastxparser_sym.lib" /libpath:"../lib/relSym" /libpath:"../core/3rdparty/smartheap" /libpath:"../core/3rdparty/xerces" /libpath:"../core/3rdparty/boost/lib"
# ADD LINK32 shdsmpmt.lib xparser_sym.lib xerces-c_2.lib bfproc_sym.lib ifastids_sym.lib bfcbo_sym.lib xparser_sym.lib ifastdbrkr_sym.lib ifastbp_sym.lib bfutil_sym.lib ifdscore_sym.lib bfdata_sym.lib ifast_dataimpl_sym.lib boost_thread.lib boost_regex_vc6_mdi.lib libboost_date_time.lib /nologo /dll /debug /machine:I386 /out:"../bin/relSym/ifastxparser_sym.dll" /implib:"../lib/relSym/ifastxparser_sym.lib" /libpath:"../lib/relSym" /libpath:"../core/3rdparty/smartheap" /libpath:"../core/3rdparty/xerces" /libpath:"../core/3rdparty/boost/lib"
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Desc=Updating Status
PostBuild_Cmds=if DEFINED _JOBSTATUSFILE echo Finished building ifastxparser (SmartHeap Symbols) > %_JOBSTATUSFILE% nul
# End Special Build Tool

!ENDIF 

# Begin Target

# Name "ifastxparser - Win32 Release"
# Name "ifastxparser - Win32 Debug"
# Name "ifastxparser - Win32 SmartHeap Release"
# Name "ifastxparser - Win32 SmartHeap Symbols"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\DSTCElementHandlerFactory.cpp
# End Source File
# Begin Source File

SOURCE=.\DSTCPackageHandler.cpp
# End Source File
# Begin Source File

SOURCE=.\DSTCProcessHandler.cpp
# End Source File
# Begin Source File

SOURCE=.\ifastxparser_conditions.cpp
# End Source File
# Begin Source File

SOURCE=.\NASUChildProcessHandler.cpp
# End Source File
# Begin Source File

SOURCE=.\NASUProcessHandler.cpp
# End Source File
# Begin Source File

SOURCE=.\stdafx.cpp
# End Source File
# Begin Source File

SOURCE=.\TradeCBOHandler.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\DSTCElementHandlerFactory.hpp
# End Source File
# Begin Source File

SOURCE=.\DSTCPackageHandler.hpp
# End Source File
# Begin Source File

SOURCE=.\DSTCProcessHandler.hpp
# End Source File
# Begin Source File

SOURCE=.\NASUChildProcessHandler.hpp
# End Source File
# Begin Source File

SOURCE=.\NASUProcessHandler.hpp
# End Source File
# Begin Source File

SOURCE=.\stdafx.h
# End Source File
# Begin Source File

SOURCE=.\TradeCBOHandler.hpp
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project
