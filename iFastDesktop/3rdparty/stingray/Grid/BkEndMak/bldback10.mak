##############################################################################																	
# 
# Build wizard generated file. 
# DO NOT EDIT MANUALLY!!!
#
# Rogue Wave Software								 
# http://www.roguewave.com
#
# Objective Grid Library
#
##############################################################################
#
# Copyright (c) 1997-2012 Rogue Wave Software, Inc.  All Rights Reserved.
#
# This computer software is owned by Rogue Wave Software, Inc. and is protected by
# U.S. copyright laws and other laws and by international treaties. This
# computer software is furnished by Rogue Wave Software, Inc. pursuant to a written
# license agreement and may be used, copied, transmitted, and stored
# only in accordance with the terms of such license agreement and with
# the inclusion of the above copyright notice.  This computer software or
# any other copies thereof may not be provided or otherwise made available
# to any other person.
#
# U.S. Government Restricted Rights.  This computer software:
#      (a) was developed at private expense and is in all respects the
#          proprietary information of Rogue Wave Software, Inc.;
#      (b) was not developed with government funds;
#      (c) is a trade secret of Rogue Wave Software, Inc. for all purposes of the
#          Freedom of Information Act; and
#      (d) is a commercial item and thus, pursuant to Section 12.212
#          of the Federal Acquisition Regulations (FAR) and DFAR
#          Supplement Section 227.7202, Government’s use, duplication or
#          disclosure of the computer software is subject to the restrictions
#          set forth by Rogue Wave Software, Inc.
#
##############################################################################
#
# Generated Makefile for configuration gxstndrd
# bldback10.mak : Builds the 32-Bit or 64-Bit Objective Grid VC++ 10.0 library 
#                 variants
#
##############################################################################
# Build wizard preprocessor variables are all of the following form:
# 
#
# The available preprocessors are listed below:
# LINK32_OBJS  	= object files to add for the LINK32_OBJS environment var
# SOURCE_CODE	= source code dependencies
# ODL_CODE	= .odl dependencies
# TLB_TARGETS	= .tlb files built from the .odl source
# PREPROCESS_DEFINES = conditional preprocessor defines from build wizard
#
# Build targets: syntax:
# MDSLUR = "MFC DLL, OG Lib, Unicode Release"
# available configurations:
# MLSLAR
# MLSLAD
# MDSLAR
# MDSLAD
# MDSDAR
# MDSDAD
# MLSLUR
# MLSLUD
# MDSLUR
# MDSLUD
# MDSDUR
# MDSDUD
##############################################################################

!INCLUDE <CompilerMSVC10.mak>

##############################################################################
# Preliminary Init
#
!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF

!IFDEF MFCLIB
!IFDEF MAKEDLL
!MESSAGE
!MESSAGE Warning! MFC must be linked dynamically for extension DLL builds.
!MESSAGE Build has been modified for dynamic link.
!MESSAGE
!UNDEF MFCLIB
!ENDIF
!ENDIF

#
# Determine the appropriate build target based on the definition of the
# following 4 environment variables: MFCLIB, GXLIB, UNICODE, and DEBUG
#


!IFDEF MFCLIB										

# Use MFC as a static library....
# Note: MFC LIB/OG DLL not allowed due to extension DLL limitations
													
!IFDEF UNICODE

# MFC as static lib, OG as static lib, unicode
													
!IFDEF RELEASE
# MFC LIB/OG LIB/UNICODE/RELEASE
BUILDTARG=og1301u
!ELSE
# MFC LIB/OG LIB/UNICODE/DEBUG
BUILDTARG=og1301ud
!ENDIF												

!ELSE

# MFC as static lib, OG as static lib, ANSI

!IFDEF RELEASE										
# MFC LIB/OG LIB/ANSI/RELEASE
BUILDTARG=og1301
!ELSE
# MFC LIB/OG LIB/ANSI/DEBUG
BUILDTARG=og1301d							
!ENDIF

# end ANSI
!ENDIF

# end MFC lib
!ELSE

# MFC as DLL

!IFDEF MAKEDLL

# MFC as DLL, OG as DLL

!IFDEF UNICODE										

# MFC as DLL, OG as DLL, UNICODE

!IFDEF RELEASE										
# MFC DLL/OG DLL/UNICODE/RELEASE
BUILDTARG=og1301asu
!ELSE
# MFC DLL/OG DLL/UNICODE/DEBUG
BUILDTARG=og1301asud
!ENDIF				

!ELSE												

# MFC as DLL, OG as DLL, ANSI

!IFDEF RELEASE										
# MFC DLL/OG DLL/ANSI/RELEASE
BUILDTARG=og1301as
!ELSE
# MFC DLL/OG DLL/ANSI/DEBUG
BUILDTARG=og1301asd
!ENDIF												

# end ANSI
!ENDIF												

!ELSE

# MFC as DLL, OG as LIB

!IFDEF UNICODE

# MFC as DLL, OG as LIB, UNICODE

!IFDEF RELEASE
# MFC DLL/OG LIB/UNICODE/RELEASE
BUILDTARG=og1301au
!ELSE
# MFC DLL/OG LIB/UNICODE/DEBUG
BUILDTARG=og1301aud
!ENDIF

!ELSE

# MFC as DLL, OG as LIB, ANSI

!IFDEF RELEASE
# MFC DLL/OG LIB/ANSI/RELEASE
BUILDTARG=og1301a
!ELSE
# MFC DLL/OG LIB/ANSI/DEBUG
BUILDTARG=og1301ad
!ENDIF

# end ANSI
!ENDIF

# end OG LIB
!ENDIF

# end MFC DLL
!ENDIF


#
# Set temporary output directory based on target 
#
ROOT_OUTDIR=$(OBJ_OUTPUT_DIR)
OUTDIR=$(ROOT_OUTDIR)\$(BUILDTARG)
INTDIR=$(ROOT_OUTDIR)\$(BUILDTARG)

##############################################################################
# Tool Configuration
#
RSC=rc.exe
CPP=cl.exe
SCPP=..\bin\slx.exe

# Use midl.exe for VC++ 9.x or greater
MTL=midl.exe

!IFDEF MAKEDLL
BUILDTARG_EXT=$(BUILDTARG).dll
LINK32=link.exe -dll

!ELSE
BUILDTARG_EXT=$(BUILDTARG).lib
LINK32=link.exe -lib
!ENDIF

##############################################################################
# Environment feedback
#

!IFDEF MFCLIB
MSG1=MFC Library
!ELSE
MSG1=MFC DLL
!ENDIF

!IFDEF MAKEDLL
MSG2=OG DLL
!ELSE
MSG2=OG Library
!ENDIF

!IFDEF UNICODE
MSG3=UNICODE
!ELSE
MSG3=ANSI
!ENDIF

!IFDEF RELEASE
MSG4=Release
!ELSE
MSG4=Debug
!ENDIF

!MESSAGE
!MESSAGE ---------------------------------------------------------------------
!MESSAGE | Rogue Wave Software
!MESSAGE | Objective Grid 13.0.1
!MESSAGE | http://www.roguewave.com
!MESSAGE |
!MESSAGE | Building $(CMDLINE_OS_TEXT)-bit target $(BUILDTARG_EXT)
!MESSAGE | $(MSG1), $(MSG2), $(MSG3), $(MSG4)
!MESSAGE ---------------------------------------------------------------------
!MESSAGE

##############################################################################
# Compile Flags
#

#
# Flags specific to Debug or Release:
#
!IFDEF RELEASE

# Use mktyplib203 for VC++ 9.x or greater
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 $(CMDLINE_OS_FLAG)

!IFDEF MAKEDLL
RELDBG_CPP=/D "NDEBUG" /O1
!ELSE
RELDBG_CPP=/D "NDEBUG" /O1
!ENDIF

!ELSE

# Use mktyplib203 for VC++ 9.x or greater
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 $(CMDLINE_OS_FLAG) 

RELDBG_CPP=/D "_DEBUG" /Zi /Od /Fd"$(INTDIR)\$(BUILDTARG).pdb"

# If program database flag was explicitly set...
!IFDEF USE_PROGRAM_DATABASE

!IFDEF MAKEDLL
!MESSAGE Program Database generation enabled. 
!MESSAGE Note this may cause a failure to watch MFC base types in debugger.
!ENDIF

RELDBG_CPP=/D "_DEBUG" /Zi /Od /Fd"$(INTDIR)\$(BUILDTARG).pdb"

!ELSE

!IFDEF MAKEDLL
# Use integrated C 7.0 debugging for DLLs, allows proper debug watch on MFC types

RELDBG_CPP=/D "_DEBUG" /Z7 /Od

!ELSE
# Use Program Database for static libraries, c 7.0 not necessary for proper debug watch 

RELDBG_CPP=/D "_DEBUG" /Zi /Od /Fd"$(INTDIR)\$(BUILDTARG).pdb"

!ENDIF
!ENDIF
!ENDIF

#
# Flags specific to ASCII or Unicode:
#
!IFDEF UNICODE
CHARSET_CPP=/D "UNICODE" /D "_UNICODE"
!ELSE
CHARSET_CPP=/D "_MBCS"
!ENDIF

#
# Flags specific to LIB or DLL builds
#
!IFDEF MAKEDLL
MAKELIBDLL_CPP=/D "_GXDLL" /D "_SFLDLL" /D "_AFXEXT" /D "_AFXDLL" /D "_RWDLL"
!ELSE
!IFDEF MFCLIB
MAKELIBDLL_CPP=
!ELSE
MAKELIBDLL_CPP=/D "_AFXDLL"
!ENDIF
!ENDIF

# Resolve Multithreaded library setting
!IFDEF MFCLIB
!IFDEF RELEASE
MT_CPP=/MT
!ELSE
MT_CPP=/MTd
!ENDIF
!ELSE
!IFDEF RELEASE
MT_CPP=/MD
!ELSE
MT_CPP=/MDd
!ENDIF
!ENDIF

# These flags are common to all configurations:
#
COMMON_CPP=/nologo /D "WIN32" /D "_WINDOWS" $(GXPRO_FLAGS) $(CMDLINE_OS_WARNING) $(CMDLINE_GLOBAL_COMPILE_OPTIONS) /c /EHa /GR \
/Fp"$(INTDIR)/$(BUILDTARG).pch" /Fo"$(INTDIR)/" \
/I "..\..\include" /I "..\..\src"

CUSTOM_CPP=/D"SEC_NO_TMPL_EXPLICIT_INST" /D"_GX_CHECKBOX_RESOURCES" /D"_GX_RADIOBTN_RESOURCES" /D"_GX_CALENDAR_RESOURCES" /D"_GX_CALCULATOR_RESOURCES" /D"COMPILER_OPTION_RTTI" /D"_GX_SELECTRANGE_RESOURCES" /D"_GX_RESIZECELL_RESOURCES" /D"_GX_EXCELAFILL_RESOURCES" /D"_GX_TABWND_RESOURCES" /D"_GX_OLEDND_RESOURCES" /D"_GX_IMOUSE_RESOURCES" /D"_GX_PROPERTYDIALOG_RESOURCES" /D"_GX_STYLESHEET_RESOURCES" /D"_GX_TABWNDSER_RESOURCES" /D"_GX_ARROWHEADER_RESOURCES" /D"WINDOWS_VISTA_OS" 

# Composite for below:
CPP_PCH_PROJ=$(COMMON_CPP) $(CUSTOM_CPP) $(MT_CPP) $(MAKELIBDLL_CPP) $(CHARSET_CPP) $(RELDBG_CPP)
CPP_PROJ=$(CPP_PCH_PROJ) /Yu"stdafx.h"

##############################################################################
# Linker flags
#

# Set linker flags to allow static library or DLL build:

# DLL
!IFDEF MAKEDLL

!IFDEF RELEASE
LINK32_DEBUG_FLAG=
!ELSE
LINK32_DEBUG_FLAG=/debug
!ENDIF

# Use the program database if explicitly set to. Note that using integrated
# c 7.0 debug info instead results in more reliable debug watching of MFC types,
# but does have the caveat of a larger dll size
!IFDEF USE_PROGRAM_DATABASE

LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:no\
 /pdb:"$(OUTDIR)/$(BUILDTARG).pdb" $(LINK32_DEBUG_FLAG) $(CMDLINE_OS_MACHINE)\
 /out:"$(OUTDIR)/$(BUILDTARG).dll" /implib:"$(OUTDIR)/$(BUILDTARG).lib" /IGNORE:4221 /IGNORE:4217 /IGNORE:4049

# Dll build
!ELSE

LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:no\
 $(LINK32_DEBUG_FLAG) $(CMDLINE_OS_MACHINE) \
 /out:"$(OUTDIR)/$(BUILDTARG).dll" /implib:"$(OUTDIR)/$(BUILDTARG).lib" /IGNORE:4221 /IGNORE:4217 /IGNORE:4049

!ENDIF

# Static Library:
!ELSE
LINK32_FLAGS=/nologo /out:"$(OUTDIR)/$(BUILDTARG).lib" /IGNORE:4221
!ENDIF

##############################################################################
# Root Dependency:
#

ALL :  "$(OUTDIR)\$(BUILDTARG)" 

"$(OUTDIR)" :
	if not exist "$(ROOT_OUTDIR)/$(NULL)" mkdir "$(ROOT_OUTDIR)"
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

##############################################################################
# Misc Flags
#	

CPP_OBJS=.\$(BUILDTARG)/
CPP_SBRS=.\.
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)/$(BUILDTARG).bsc" 
BSC32_SBRS= \

LINK32_OBJS= \
	"$(INTDIR)\Stdafx.obj"\
	"$(INTDIR)\gxdll.res"\
	"$(INTDIR)\gxdll.obj"\
	"$(INTDIR)\gxfactry.obj"\
	"$(INTDIR)\gxAdoEng.obj"\
	"$(INTDIR)\gxdbegrid.obj"\
	"$(INTDIR)\gxdbEngine.obj"\
	"$(INTDIR)\gxScrCurEng.obj"\
	"$(INTDIR)\expreval.obj"\
	"$(INTDIR)\exprfunc.obj"\
	"$(INTDIR)\exprpars.obj"\
	"$(INTDIR)\exprprnt.obj"\
	"$(INTDIR)\exprscan.obj"\
	"$(INTDIR)\exprutil.obj"\
	"$(INTDIR)\fncstat.obj"\
	"$(INTDIR)\fnexcel.obj"\
	"$(INTDIR)\fnfina.obj"\
	"$(INTDIR)\fnfina2.obj"\
	"$(INTDIR)\fnlogic.obj"\
	"$(INTDIR)\fnlogica.obj"\
	"$(INTDIR)\fnmath.obj"\
	"$(INTDIR)\fnmatrix.obj"\
	"$(INTDIR)\fnmisc.obj"\
	"$(INTDIR)\fnmisc2.obj"\
	"$(INTDIR)\fnstat.obj"\
	"$(INTDIR)\fnstat2.obj"\
	"$(INTDIR)\fnstring.obj"\
	"$(INTDIR)\gxengine.obj"\
	"$(INTDIR)\gxscell.obj"\
	"$(INTDIR)\gxsclear.obj"\
	"$(INTDIR)\gxsdate.obj"\
	"$(INTDIR)\gxsdrand.obj"\
	"$(INTDIR)\gxserror.obj"\
	"$(INTDIR)\gxsfunc.obj"\
	"$(INTDIR)\gxslgamm.obj"\
	"$(INTDIR)\gxsmatrx.obj"\
	"$(INTDIR)\gxsmove.obj"\
	"$(INTDIR)\gxsrecal.obj"\
	"$(INTDIR)\gxsREGEX.obj"\
	"$(INTDIR)\gxsrngn.obj"\
	"$(INTDIR)\gxsrngut.obj"\
	"$(INTDIR)\gxsSTAT.obj"\
	"$(INTDIR)\gxsstr.obj"\
	"$(INTDIR)\gxabstr.obj"\
	"$(INTDIR)\gxadofrg.obj"\
	"$(INTDIR)\GxAdoGrd.obj"\
	"$(INTDIR)\gxadoinl.obj"\
	"$(INTDIR)\GxAdoVal.obj"\
	"$(INTDIR)\GxAdovw.obj"\
	"$(INTDIR)\GxAdownd.obj"\
	"$(INTDIR)\gxapatr.obj"\
	"$(INTDIR)\Gxapp.obj"\
	"$(INTDIR)\gxautscr.obj"\
	"$(INTDIR)\gxbinres.obj"\
	"$(INTDIR)\gxbroinf.obj"\
	"$(INTDIR)\gxbrovw.obj"\
	"$(INTDIR)\gxbrownd.obj"\
	"$(INTDIR)\GXbrowse.obj"\
	"$(INTDIR)\gxcalc.obj"\
	"$(INTDIR)\gxcalcsi.obj"\
	"$(INTDIR)\gxcbmbtn.obj"\
	"$(INTDIR)\gxccbbox.obj"\
	"$(INTDIR)\gxccbchk.obj"\
	"$(INTDIR)\gxccbtab.obj"\
	"$(INTDIR)\gxccbwnd.obj"\
	"$(INTDIR)\gxccbwtb.obj"\
	"$(INTDIR)\gxccheck.obj"\
	"$(INTDIR)\gxccombo.obj"\
	"$(INTDIR)\gxcedhot.obj"\
	"$(INTDIR)\gxcedit.obj"\
	"$(INTDIR)\gxcedspn.obj"\
	"$(INTDIR)\gxcharro.obj"\
	"$(INTDIR)\gxchbmbt.obj"\
	"$(INTDIR)\gxchbtn.obj"\
	"$(INTDIR)\gxchcbbt.obj"\
	"$(INTDIR)\gxchcbwb.obj"\
	"$(INTDIR)\gxchead.obj"\
	"$(INTDIR)\gxchfrm.obj"\
	"$(INTDIR)\gxchhsbt.obj"\
	"$(INTDIR)\gxchild.obj"\
	"$(INTDIR)\gxchkex.obj"\
	"$(INTDIR)\gxchsfrm.obj"\
	"$(INTDIR)\gxclbox.obj"\
	"$(INTDIR)\gxclear.obj"\
	"$(INTDIR)\gxclsite.obj"\
	"$(INTDIR)\Gxcmask.obj"\
	"$(INTDIR)\GXCMD.obj"\
	"$(INTDIR)\GXCOLL.obj"\
	"$(INTDIR)\gxcorabs.obj"\
	"$(INTDIR)\gxcorbuf.obj"\
	"$(INTDIR)\gxcorclp.obj"\
	"$(INTDIR)\gxcorcur.obj"\
	"$(INTDIR)\gxcordim.obj"\
	"$(INTDIR)\gxcordra.obj"\
	"$(INTDIR)\GXCORE.obj"\
	"$(INTDIR)\gxcoret.obj"\
	"$(INTDIR)\gxcorfit.obj"\
	"$(INTDIR)\gxcorfr.obj"\
	"$(INTDIR)\gxcorfri.obj"\
	"$(INTDIR)\gxcorinf.obj"\
	"$(INTDIR)\gxcormsg.obj"\
	"$(INTDIR)\gxcorprn.obj"\
	"$(INTDIR)\gxcorscr.obj"\
	"$(INTDIR)\gxcorsel.obj"\
	"$(INTDIR)\gxcorsiz.obj"\
	"$(INTDIR)\gxcorsty.obj"\
	"$(INTDIR)\gxcpassw.obj"\
	"$(INTDIR)\gxcpmov.obj"\
	"$(INTDIR)\gxcpmovd.obj"\
	"$(INTDIR)\gxcprgrs.obj"\
	"$(INTDIR)\gxcpush.obj"\
	"$(INTDIR)\gxcradio.obj"\
	"$(INTDIR)\gxcrdex.obj"\
	"$(INTDIR)\gxcrgnam.obj"\
	"$(INTDIR)\gxcrtf.obj"\
	"$(INTDIR)\gxcstat.obj"\
	"$(INTDIR)\gxctabls.obj"\
	"$(INTDIR)\gxctctrl.obj"\
	"$(INTDIR)\gxctplug.obj"\
	"$(INTDIR)\Gxctrl.obj"\
	"$(INTDIR)\gxctwnd.obj"\
	"$(INTDIR)\gxcurbas.obj"\
	"$(INTDIR)\gxcurctl.obj"\
	"$(INTDIR)\gxcvedit.obj"\
	"$(INTDIR)\gxcvrcel.obj"\
	"$(INTDIR)\gxcvrdra.obj"\
	"$(INTDIR)\gxcwrap.obj"\
	"$(INTDIR)\GXDATA.obj"\
	"$(INTDIR)\gxdbdyna.obj"\
	"$(INTDIR)\GXDBFORG.obj"\
	"$(INTDIR)\gxdbgrid.obj"\
	"$(INTDIR)\gxdbinl.obj"\
	"$(INTDIR)\gxdbrfxd.obj"\
	"$(INTDIR)\gxdbval.obj"\
	"$(INTDIR)\gxdbvw.obj"\
	"$(INTDIR)\gxdbwnd.obj"\
	"$(INTDIR)\gxddib.obj"\
	"$(INTDIR)\gxdelayr.obj"\
	"$(INTDIR)\gxdib.obj"\
	"$(INTDIR)\gxdoc.obj"\
	"$(INTDIR)\gxdraold.obj"\
	"$(INTDIR)\gxdrawro.obj"\
	"$(INTDIR)\Gxdrawx.obj"\
	"$(INTDIR)\gxdrgwnd.obj"\
	"$(INTDIR)\gxDSplit.obj"\
	"$(INTDIR)\gxDTabWnd.obj"\
	"$(INTDIR)\gxdtbase.obj"\
	"$(INTDIR)\gxdtbox.obj"\
	"$(INTDIR)\gxdtcal.obj"\
	"$(INTDIR)\gxdtctrl.obj"\
	"$(INTDIR)\gxdtmpl.obj"\
	"$(INTDIR)\gxdxsty.obj"\
	"$(INTDIR)\gxdxtext.obj"\
	"$(INTDIR)\gxexfil.obj"\
	"$(INTDIR)\gxfltcel.obj"\
	"$(INTDIR)\gxformat.obj"\
	"$(INTDIR)\gxfradpt.obj"\
	"$(INTDIR)\gxfreeze.obj"\
	"$(INTDIR)\gxgmouse.obj"\
	"$(INTDIR)\gxgmousw.obj"\
	"$(INTDIR)\gxgscrlt.obj"\
	"$(INTDIR)\gxhide.obj"\
	"$(INTDIR)\GXHINT.obj"\
	"$(INTDIR)\gxhinti.obj"\
	"$(INTDIR)\GxHtmlW.obj"\
	"$(INTDIR)\gximouse.obj"\
	"$(INTDIR)\gximousw.obj"\
	"$(INTDIR)\gxinfbm.obj"\
	"$(INTDIR)\gxinfspl.obj"\
	"$(INTDIR)\gxinfwnd.obj"\
	"$(INTDIR)\gxinl.obj"\
	"$(INTDIR)\gxmapdwp.obj"\
	"$(INTDIR)\gxmapdws.obj"\
	"$(INTDIR)\gxmapsh.obj"\
	"$(INTDIR)\gxmapsw.obj"\
	"$(INTDIR)\gxmarked.obj"\
	"$(INTDIR)\gxmoverc.obj"\
	"$(INTDIR)\gxmrgcel.obj"\
	"$(INTDIR)\gxMultiMonitor.obj"\
	"$(INTDIR)\gxoledrg.obj"\
	"$(INTDIR)\gxolesrc.obj"\
	"$(INTDIR)\gxoleusr.obj"\
	"$(INTDIR)\GXPARAM.obj"\
	"$(INTDIR)\gxparcop.obj"\
	"$(INTDIR)\gxparser.obj"\
	"$(INTDIR)\GXPgBrak.obj"\
	"$(INTDIR)\gxplugin.obj"\
	"$(INTDIR)\GXPRNDEV.obj"\
	"$(INTDIR)\gxprndi.obj"\
	"$(INTDIR)\gxprof.obj"\
	"$(INTDIR)\GXPRP.obj"\
	"$(INTDIR)\GXPRPDLG.obj"\
	"$(INTDIR)\GXRANGE.obj"\
	"$(INTDIR)\gxscrltp.obj"\
	"$(INTDIR)\gxseldrg.obj"\
	"$(INTDIR)\gxselgrx.obj"\
	"$(INTDIR)\gxselrgu.obj"\
	"$(INTDIR)\gxsizeu.obj"\
	"$(INTDIR)\gxsort.obj"\
	"$(INTDIR)\gxsort2.obj"\
	"$(INTDIR)\gxsortd.obj"\
	"$(INTDIR)\gxspan.obj"\
	"$(INTDIR)\GXSplit.obj"\
	"$(INTDIR)\GXSTYDLG.obj"\
	"$(INTDIR)\gxstygd2.obj"\
	"$(INTDIR)\gxstygd3.obj"\
	"$(INTDIR)\gxstygdi.obj"\
	"$(INTDIR)\gxstyle2.obj"\
	"$(INTDIR)\GXSTYLES.obj"\
	"$(INTDIR)\gxstymap.obj"\
	"$(INTDIR)\gxstyse5.obj"\
	"$(INTDIR)\gxstyser.obj"\
	"$(INTDIR)\gxstyua.obj"\
	"$(INTDIR)\gxstyuai.obj"\
	"$(INTDIR)\GXTBEAM.obj"\
	"$(INTDIR)\gxtbgadp.obj"\
	"$(INTDIR)\gxtbmgr.obj"\
	"$(INTDIR)\GXTIME.obj"\
	"$(INTDIR)\gxtime1.obj"\
	"$(INTDIR)\gxtime2.obj"\
	"$(INTDIR)\gxtmpl.obj"\
	"$(INTDIR)\gxttn.obj"\
	"$(INTDIR)\gxtwnd.obj"\
	"$(INTDIR)\gxupdopt.obj"\
	"$(INTDIR)\GXVIEW.obj"\
	"$(INTDIR)\gxviewt.obj"\
	"$(INTDIR)\Gxvw.obj"\
	"$(INTDIR)\gxvwhnd.obj"\
	"$(INTDIR)\GXWAIT.obj"\
	"$(INTDIR)\gxwaiti.obj"\
	"$(INTDIR)\gxwnd.obj"\
	"$(INTDIR)\gxwndhnd.obj"\
	"$(INTDIR)\gxCvrdPattn.obj"\
	"$(INTDIR)\gxhgfr.obj"\
	"$(INTDIR)\gxHierGrid.obj"\
	"$(INTDIR)\gxpmctrl.obj"\
	"$(INTDIR)\gxxmlser.obj"\


##############################################################################
# Linker
#	
"$(OUTDIR)\$(BUILDTARG)" : "$(OUTDIR)" $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

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

##############################################################################
# Source Code Compilation
#

#
# Precompiled Header
#
SOURCE=.\grid\Stdafx.cpp
DEP_CPP_STDAF=\
	"grid\stdafx.h"\
	
# Add Yc"" for precompiled header:
BuildCmds= \
	$(CPP) $(CPP_PCH_PROJ) /Yc $(SOURCE) \
	
"$(INTDIR)\Stdafx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

#
# Configured Source Files
#

SOURCE="..\src\grid\BkEndMak\gxdll.cpp"
"$(INTDIR)\gxdll.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\BkEndMak\gxfactry.cpp"
"$(INTDIR)\gxfactry.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\dbe\gxAdoEng.cpp"
"$(INTDIR)\gxAdoEng.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\dbe\gxdbegrid.cpp"
"$(INTDIR)\gxdbegrid.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\dbe\gxdbEngine.cpp"
"$(INTDIR)\gxdbEngine.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\dbe\gxScrCurEng.cpp"
"$(INTDIR)\gxScrCurEng.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\engine\expreval.cpp"
"$(INTDIR)\expreval.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\engine\exprfunc.cpp"
"$(INTDIR)\exprfunc.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\engine\exprpars.cpp"
"$(INTDIR)\exprpars.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\engine\exprprnt.cpp"
"$(INTDIR)\exprprnt.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\engine\exprscan.cpp"
"$(INTDIR)\exprscan.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\engine\exprutil.cpp"
"$(INTDIR)\exprutil.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\engine\fncstat.cpp"
"$(INTDIR)\fncstat.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\engine\fnexcel.cpp"
"$(INTDIR)\fnexcel.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\engine\fnfina.cpp"
"$(INTDIR)\fnfina.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\engine\fnfina2.cpp"
"$(INTDIR)\fnfina2.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\engine\fnlogic.cpp"
"$(INTDIR)\fnlogic.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\engine\fnlogica.cpp"
"$(INTDIR)\fnlogica.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\engine\fnmath.cpp"
"$(INTDIR)\fnmath.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\engine\fnmatrix.cpp"
"$(INTDIR)\fnmatrix.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\engine\fnmisc.cpp"
"$(INTDIR)\fnmisc.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\engine\fnmisc2.cpp"
"$(INTDIR)\fnmisc2.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\engine\fnstat.cpp"
"$(INTDIR)\fnstat.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\engine\fnstat2.cpp"
"$(INTDIR)\fnstat2.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\engine\fnstring.cpp"
"$(INTDIR)\fnstring.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\engine\gxengine.cpp"
"$(INTDIR)\gxengine.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\engine\gxscell.cpp"
"$(INTDIR)\gxscell.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\engine\gxsclear.cpp"
"$(INTDIR)\gxsclear.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\engine\gxsdate.cpp"
"$(INTDIR)\gxsdate.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\engine\gxsdrand.cpp"
"$(INTDIR)\gxsdrand.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\engine\gxserror.cpp"
"$(INTDIR)\gxserror.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\engine\gxsfunc.cpp"
"$(INTDIR)\gxsfunc.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\engine\gxslgamm.cpp"
"$(INTDIR)\gxslgamm.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\engine\gxsmatrx.cpp"
"$(INTDIR)\gxsmatrx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\engine\gxsmove.cpp"
"$(INTDIR)\gxsmove.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\engine\gxsrecal.cpp"
"$(INTDIR)\gxsrecal.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\engine\gxsREGEX.cpp"
"$(INTDIR)\gxsREGEX.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\engine\gxsrngn.cpp"
"$(INTDIR)\gxsrngn.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\engine\gxsrngut.cpp"
"$(INTDIR)\gxsrngut.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\engine\gxsSTAT.cpp"
"$(INTDIR)\gxsSTAT.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\engine\gxsstr.cpp"
"$(INTDIR)\gxsstr.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\gxabstr.cpp"
"$(INTDIR)\gxabstr.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\gxadofrg.cpp"
"$(INTDIR)\gxadofrg.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\GxAdoGrd.cpp"
"$(INTDIR)\GxAdoGrd.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\gxadoinl.cpp"
"$(INTDIR)\gxadoinl.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\GxAdoVal.cpp"
"$(INTDIR)\GxAdoVal.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\GxAdovw.cpp"
"$(INTDIR)\GxAdovw.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\GxAdownd.cpp"
"$(INTDIR)\GxAdownd.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\gxapatr.cpp"
"$(INTDIR)\gxapatr.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\Gxapp.cpp"
"$(INTDIR)\Gxapp.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\gxautscr.cpp"
"$(INTDIR)\gxautscr.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\gxbinres.cpp"
"$(INTDIR)\gxbinres.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\gxbroinf.cpp"
"$(INTDIR)\gxbroinf.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\gxbrovw.cpp"
"$(INTDIR)\gxbrovw.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\gxbrownd.cpp"
"$(INTDIR)\gxbrownd.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\GXbrowse.cpp"
"$(INTDIR)\GXbrowse.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\gxcalc.cpp"
"$(INTDIR)\gxcalc.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\gxcalcsi.cpp"
"$(INTDIR)\gxcalcsi.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\gxcbmbtn.cpp"
"$(INTDIR)\gxcbmbtn.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\gxccbbox.cpp"
"$(INTDIR)\gxccbbox.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\gxccbchk.cpp"
"$(INTDIR)\gxccbchk.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\gxccbtab.cpp"
"$(INTDIR)\gxccbtab.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\gxccbwnd.cpp"
"$(INTDIR)\gxccbwnd.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\gxccbwtb.cpp"
"$(INTDIR)\gxccbwtb.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\gxccheck.cpp"
"$(INTDIR)\gxccheck.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\gxccombo.cpp"
"$(INTDIR)\gxccombo.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\gxcedhot.cpp"
"$(INTDIR)\gxcedhot.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\gxcedit.cpp"
"$(INTDIR)\gxcedit.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\gxcedspn.cpp"
"$(INTDIR)\gxcedspn.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\gxcharro.cpp"
"$(INTDIR)\gxcharro.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\gxchbmbt.cpp"
"$(INTDIR)\gxchbmbt.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\gxchbtn.cpp"
"$(INTDIR)\gxchbtn.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\gxchcbbt.cpp"
"$(INTDIR)\gxchcbbt.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\gxchcbwb.cpp"
"$(INTDIR)\gxchcbwb.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\gxchead.cpp"
"$(INTDIR)\gxchead.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\gxchfrm.cpp"
"$(INTDIR)\gxchfrm.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\gxchhsbt.cpp"
"$(INTDIR)\gxchhsbt.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\gxchild.cpp"
"$(INTDIR)\gxchild.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\gxchkex.cpp"
"$(INTDIR)\gxchkex.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\gxchsfrm.cpp"
"$(INTDIR)\gxchsfrm.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\gxclbox.cpp"
"$(INTDIR)\gxclbox.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\gxclear.cpp"
"$(INTDIR)\gxclear.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\gxclsite.cpp"
"$(INTDIR)\gxclsite.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\Gxcmask.cpp"
"$(INTDIR)\Gxcmask.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\GXCMD.cpp"
"$(INTDIR)\GXCMD.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\GXCOLL.cpp"
"$(INTDIR)\GXCOLL.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\gxcorabs.cpp"
"$(INTDIR)\gxcorabs.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\gxcorbuf.cpp"
"$(INTDIR)\gxcorbuf.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\gxcorclp.cpp"
"$(INTDIR)\gxcorclp.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\gxcorcur.cpp"
"$(INTDIR)\gxcorcur.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\gxcordim.cpp"
"$(INTDIR)\gxcordim.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\gxcordra.cpp"
"$(INTDIR)\gxcordra.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\GXCORE.cpp"
"$(INTDIR)\GXCORE.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\gxcoret.cpp"
"$(INTDIR)\gxcoret.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\gxcorfit.cpp"
"$(INTDIR)\gxcorfit.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\gxcorfr.cpp"
"$(INTDIR)\gxcorfr.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\gxcorfri.cpp"
"$(INTDIR)\gxcorfri.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\gxcorinf.cpp"
"$(INTDIR)\gxcorinf.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\gxcormsg.cpp"
"$(INTDIR)\gxcormsg.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\gxcorprn.cpp"
"$(INTDIR)\gxcorprn.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\gxcorscr.cpp"
"$(INTDIR)\gxcorscr.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\gxcorsel.cpp"
"$(INTDIR)\gxcorsel.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\gxcorsiz.cpp"
"$(INTDIR)\gxcorsiz.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\gxcorsty.cpp"
"$(INTDIR)\gxcorsty.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\gxcpassw.cpp"
"$(INTDIR)\gxcpassw.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\gxcpmov.cpp"
"$(INTDIR)\gxcpmov.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\gxcpmovd.cpp"
"$(INTDIR)\gxcpmovd.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\gxcprgrs.cpp"
"$(INTDIR)\gxcprgrs.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\gxcpush.cpp"
"$(INTDIR)\gxcpush.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\gxcradio.cpp"
"$(INTDIR)\gxcradio.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\gxcrdex.cpp"
"$(INTDIR)\gxcrdex.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\gxcrgnam.cpp"
"$(INTDIR)\gxcrgnam.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\gxcrtf.cpp"
"$(INTDIR)\gxcrtf.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\gxcstat.cpp"
"$(INTDIR)\gxcstat.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\gxctabls.cpp"
"$(INTDIR)\gxctabls.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\gxctctrl.cpp"
"$(INTDIR)\gxctctrl.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\gxctplug.cpp"
"$(INTDIR)\gxctplug.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\Gxctrl.cpp"
"$(INTDIR)\Gxctrl.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\gxctwnd.cpp"
"$(INTDIR)\gxctwnd.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\gxcurbas.cpp"
"$(INTDIR)\gxcurbas.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\gxcurctl.cpp"
"$(INTDIR)\gxcurctl.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\gxcvedit.cpp"
"$(INTDIR)\gxcvedit.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\gxcvrcel.cpp"
"$(INTDIR)\gxcvrcel.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\gxcvrdra.cpp"
"$(INTDIR)\gxcvrdra.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\gxcwrap.cpp"
"$(INTDIR)\gxcwrap.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\GXDATA.cpp"
"$(INTDIR)\GXDATA.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\gxdbdyna.cpp"
"$(INTDIR)\gxdbdyna.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\GXDBFORG.cpp"
"$(INTDIR)\GXDBFORG.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\gxdbgrid.cpp"
"$(INTDIR)\gxdbgrid.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\gxdbinl.cpp"
"$(INTDIR)\gxdbinl.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\gxdbrfxd.cpp"
"$(INTDIR)\gxdbrfxd.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\gxdbval.cpp"
"$(INTDIR)\gxdbval.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\gxdbvw.cpp"
"$(INTDIR)\gxdbvw.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\gxdbwnd.cpp"
"$(INTDIR)\gxdbwnd.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\gxddib.cpp"
"$(INTDIR)\gxddib.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\gxdelayr.cpp"
"$(INTDIR)\gxdelayr.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\gxdib.cpp"
"$(INTDIR)\gxdib.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\gxdoc.cpp"
"$(INTDIR)\gxdoc.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\gxdraold.cpp"
"$(INTDIR)\gxdraold.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\gxdrawro.cpp"
"$(INTDIR)\gxdrawro.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\Gxdrawx.cpp"
"$(INTDIR)\Gxdrawx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\gxdrgwnd.cpp"
"$(INTDIR)\gxdrgwnd.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\gxDSplit.cpp"
"$(INTDIR)\gxDSplit.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\gxDTabWnd.cpp"
"$(INTDIR)\gxDTabWnd.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\gxdtbase.cpp"
"$(INTDIR)\gxdtbase.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\gxdtbox.cpp"
"$(INTDIR)\gxdtbox.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\gxdtcal.cpp"
"$(INTDIR)\gxdtcal.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\gxdtctrl.cpp"
"$(INTDIR)\gxdtctrl.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\gxdtmpl.cpp"
"$(INTDIR)\gxdtmpl.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\gxdxsty.cpp"
"$(INTDIR)\gxdxsty.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\gxdxtext.cpp"
"$(INTDIR)\gxdxtext.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\gxexfil.cpp"
"$(INTDIR)\gxexfil.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\gxfltcel.cpp"
"$(INTDIR)\gxfltcel.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\gxformat.cpp"
"$(INTDIR)\gxformat.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\gxfradpt.cpp"
"$(INTDIR)\gxfradpt.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\gxfreeze.cpp"
"$(INTDIR)\gxfreeze.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\gxgmouse.cpp"
"$(INTDIR)\gxgmouse.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\gxgmousw.cpp"
"$(INTDIR)\gxgmousw.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\gxgscrlt.cpp"
"$(INTDIR)\gxgscrlt.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\gxhide.cpp"
"$(INTDIR)\gxhide.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\GXHINT.cpp"
"$(INTDIR)\GXHINT.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\gxhinti.cpp"
"$(INTDIR)\gxhinti.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\GxHtmlW.cpp"
"$(INTDIR)\GxHtmlW.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\gximouse.cpp"
"$(INTDIR)\gximouse.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\gximousw.cpp"
"$(INTDIR)\gximousw.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\gxinfbm.cpp"
"$(INTDIR)\gxinfbm.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\gxinfspl.cpp"
"$(INTDIR)\gxinfspl.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\gxinfwnd.cpp"
"$(INTDIR)\gxinfwnd.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\gxinl.cpp"
"$(INTDIR)\gxinl.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\gxmapdwp.cpp"
"$(INTDIR)\gxmapdwp.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\gxmapdws.cpp"
"$(INTDIR)\gxmapdws.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\gxmapsh.cpp"
"$(INTDIR)\gxmapsh.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\gxmapsw.cpp"
"$(INTDIR)\gxmapsw.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\gxmarked.cpp"
"$(INTDIR)\gxmarked.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\gxmoverc.cpp"
"$(INTDIR)\gxmoverc.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\gxmrgcel.cpp"
"$(INTDIR)\gxmrgcel.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\gxMultiMonitor.cpp"
"$(INTDIR)\gxMultiMonitor.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\gxoledrg.cpp"
"$(INTDIR)\gxoledrg.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\gxolesrc.cpp"
"$(INTDIR)\gxolesrc.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\gxoleusr.cpp"
"$(INTDIR)\gxoleusr.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\GXPARAM.cpp"
"$(INTDIR)\GXPARAM.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\gxparcop.cpp"
"$(INTDIR)\gxparcop.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\gxparser.cpp"
"$(INTDIR)\gxparser.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\GXPgBrak.cpp"
"$(INTDIR)\GXPgBrak.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\gxplugin.cpp"
"$(INTDIR)\gxplugin.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\GXPRNDEV.cpp"
"$(INTDIR)\GXPRNDEV.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\gxprndi.cpp"
"$(INTDIR)\gxprndi.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\gxprof.cpp"
"$(INTDIR)\gxprof.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\GXPRP.cpp"
"$(INTDIR)\GXPRP.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\GXPRPDLG.cpp"
"$(INTDIR)\GXPRPDLG.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\GXRANGE.cpp"
"$(INTDIR)\GXRANGE.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\gxscrltp.cpp"
"$(INTDIR)\gxscrltp.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\gxseldrg.cpp"
"$(INTDIR)\gxseldrg.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\gxselgrx.cpp"
"$(INTDIR)\gxselgrx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\gxselrgu.cpp"
"$(INTDIR)\gxselrgu.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\gxsizeu.cpp"
"$(INTDIR)\gxsizeu.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\gxsort.cpp"
"$(INTDIR)\gxsort.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\gxsort2.cpp"
"$(INTDIR)\gxsort2.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\gxsortd.cpp"
"$(INTDIR)\gxsortd.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\gxspan.cpp"
"$(INTDIR)\gxspan.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\GXSplit.cpp"
"$(INTDIR)\GXSplit.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\GXSTYDLG.cpp"
"$(INTDIR)\GXSTYDLG.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\gxstygd2.cpp"
"$(INTDIR)\gxstygd2.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\gxstygd3.cpp"
"$(INTDIR)\gxstygd3.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\gxstygdi.cpp"
"$(INTDIR)\gxstygdi.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\gxstyle2.cpp"
"$(INTDIR)\gxstyle2.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\GXSTYLES.cpp"
"$(INTDIR)\GXSTYLES.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\gxstymap.cpp"
"$(INTDIR)\gxstymap.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\gxstyse5.cpp"
"$(INTDIR)\gxstyse5.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\gxstyser.cpp"
"$(INTDIR)\gxstyser.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\gxstyua.cpp"
"$(INTDIR)\gxstyua.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\gxstyuai.cpp"
"$(INTDIR)\gxstyuai.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\GXTBEAM.cpp"
"$(INTDIR)\GXTBEAM.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\gxtbgadp.cpp"
"$(INTDIR)\gxtbgadp.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\gxtbmgr.cpp"
"$(INTDIR)\gxtbmgr.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\GXTIME.cpp"
"$(INTDIR)\GXTIME.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\gxtime1.cpp"
"$(INTDIR)\gxtime1.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\gxtime2.cpp"
"$(INTDIR)\gxtime2.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\gxtmpl.cpp"
"$(INTDIR)\gxtmpl.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\gxttn.cpp"
"$(INTDIR)\gxttn.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\gxtwnd.cpp"
"$(INTDIR)\gxtwnd.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\gxupdopt.cpp"
"$(INTDIR)\gxupdopt.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\GXVIEW.cpp"
"$(INTDIR)\GXVIEW.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\gxviewt.cpp"
"$(INTDIR)\gxviewt.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\Gxvw.cpp"
"$(INTDIR)\Gxvw.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\gxvwhnd.cpp"
"$(INTDIR)\gxvwhnd.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\GXWAIT.cpp"
"$(INTDIR)\GXWAIT.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\gxwaiti.cpp"
"$(INTDIR)\gxwaiti.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\gxwnd.cpp"
"$(INTDIR)\gxwnd.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\gxwndhnd.cpp"
"$(INTDIR)\gxwndhnd.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\HierGrid\gxCvrdPattn.cpp"
"$(INTDIR)\gxCvrdPattn.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\HierGrid\gxhgfr.cpp"
"$(INTDIR)\gxhgfr.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\HierGrid\gxHierGrid.cpp"
"$(INTDIR)\gxHierGrid.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\HierGrid\gxpmctrl.cpp"
"$(INTDIR)\gxpmctrl.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)

SOURCE="..\src\grid\xmlser\gxxmlser.cpp"
"$(INTDIR)\gxxmlser.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)\$(BUILDTARG).pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)




#
# Resource File compilation
#

!IFDEF UNICODE
RES_DEFINE_UNICODE=/D "UNICODE"
!ELSE
RES_DEFINE_UNICODE=
!ENDIF

!IFDEF RELEASE
RES_DEFINE_DEBUG=/D "NDEBUG"
!ELSE
RES_DEFINE_DEBUG=/D "_DEBUG"
!ENDIF

RSC_PROJ=/l 0x509 /fo"$(INTDIR)\Gxdll.res" /i "..\include\grid" $(RES_DEFINE_DEBUG) /d "_AFXDLL" $(RES_DEFINE_UNICODE)

SOURCE=..\src\grid\gxdll.rc
"$(INTDIR)\Gxdll.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)

#
# Type Library compilation
#


# End Source Code Compilation
##############################################################################
