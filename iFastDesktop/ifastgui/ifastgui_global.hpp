#pragma once
//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by DST Systems, Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2002 International Financial
//
//******************************************************************************
//
// ^FILE   : ifastgui_global.h
// ^AUTHOR : 
// ^DATE   :
//
// ^CLASS    :
// ^SUBCLASS :
//
// ^DESCRIPTION : This header file contains global definitions to be included by
//                stdafx.h
//
//
//
//******************************************************************************

#pragma warning( disable: 4786 )
#include <uibase\win32uibase_global.hpp>

#undef WIN32UIBASE_LINKAGE
#ifdef WIN32UIBASE_DLL
   #define WIN32UIBASE_LINKAGE CLASS_EXPORT
#else
   #define WIN32UIBASE_LINKAGE CLASS_IMPORT
#endif

#define UM_OPENAMSCODESEARCH    WM_APP + 1300

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastgui/ifastgui_global.hpp-arc  $
//
//   Rev 1.1   Nov 29 2002 11:57:50   HSUCHIN
//fixed revision control log
*/
