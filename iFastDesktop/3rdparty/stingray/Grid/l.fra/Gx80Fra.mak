# Microsoft Developer Studio Generated NMAKE File, Format Version 4.20
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

!IF "$(CFG)" == ""
CFG=gx70Fra - Win32 Release
!MESSAGE No configuration specified.  Defaulting to gx70Fra - Win32 Release.
!ENDIF 

!IF "$(CFG)" != "gx70Fra - Win32 Release"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "gx70Fra.mak" CFG="gx70Fra - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "gx70Fra - Win32 Release" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 
################################################################################
# Begin Project
# PROP Target_Last_Scanned "gx70Fra - Win32 Release"
RSC=rc.exe
CPP=cl.exe
MTL=mktyplib.exe
# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
OUTDIR=.\Release
INTDIR=.\Release

ALL : "$(OUTDIR)\gx70Fra.dll"

CLEAN : 
	-@erase "$(INTDIR)\GXRESFRA.res"
	-@erase "$(OUTDIR)\gx70Fra.dll"
	-@erase "$(OUTDIR)\gx70Fra.exp"
	-@erase "$(OUTDIR)\gx70Fra.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
# ADD BASE RSC /l 0x813 /d "NDEBUG"
# ADD RSC /l 0x813 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/gx70Fra.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386 /noentry
# SUBTRACT LINK32 /pdb:none
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib /nologo /subsystem:windows /dll /incremental:no\
 /pdb:"$(OUTDIR)/gx70Fra.pdb" /machine:I386 /out:"$(OUTDIR)/gx70Fra.dll"\
 /implib:"$(OUTDIR)/gx70Fra.lib" /noentry 
LINK32_OBJS= \
	"$(INTDIR)\GXRESFRA.res"

"$(OUTDIR)\gx70Fra.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

RSC_PROJ=/l 0x813 /fo"$(INTDIR)/GXRESFRA.res" /d "NDEBUG" 
CPP_PROJ=/nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS"\
 /Fp"$(INTDIR)/gx70Fra.pch" /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=.\.

.c{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.c{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

MTL_PROJ=/nologo /D "NDEBUG" /win32 
################################################################################
# Begin Target

# Name "gx70Fra - Win32 Release"
################################################################################
# Begin Source File

SOURCE=..\..\Include\grid\GXRESFRA.RC
DEP_RSC_GXRES=\
	"..\..\Include\grid\RES\GX3D95.BMP"\
	"..\..\Include\grid\RES\GX3DCTRL.BMP"\
	"..\..\Include\grid\RES\GXARROW.BMP"\
	"..\..\Include\grid\RES\GXCHK31.BMP"\
	"..\..\Include\grid\RES\GXCHK95.BMP"\
	"..\..\Include\grid\RES\GXCHKNT.BMP"\
	"..\..\Include\grid\RES\GXCOLUMN.CUR"\
	"..\..\Include\grid\RES\GXHEIGHT.CUR"\
	"..\..\Include\grid\RES\GXNODROP.CUR"\
	"..\..\Include\grid\RES\GXPENCIL.BMP"\
	"..\..\Include\grid\RES\GXROW.CUR"\
	"..\..\Include\grid\RES\GXSELDRG.CUR"\
	"..\..\Include\grid\RES\GXSPLITH.CUR"\
	"..\..\Include\grid\RES\GXSTAR.BMP"\
	"..\..\Include\grid\RES\GXTTFONT.BMP"\
	"..\..\Include\grid\RES\GXWIDTH.CUR"\
	

"$(INTDIR)\GXRESFRA.res" : $(SOURCE) $(DEP_RSC_GXRES) "$(INTDIR)"
   $(RSC) /l 0x813 /fo"$(INTDIR)/GXRESFRA.res" /i "..\..\Include" /d\
 "NDEBUG" $(SOURCE)


# End Source File
# End Target
# End Project
################################################################################
