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
//    Copyright 1997 by DST Systems, Inc.
//
//******************************************************************************
//
// ^FILE   : DstcGlobal.h
// ^AUTHOR : Jerry Leenerts
// ^DATE   : 01-99
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
#include <conditionmanager.hpp>
#include <vector>
#include <list>

#undef WIN32UIBASE_LINKAGE
#ifdef WIN32UIBASE_DLL
   #define WIN32UIBASE_LINKAGE CLASS_EXPORT
#else
   #define WIN32UIBASE_LINKAGE CLASS_IMPORT
#endif

namespace CND
{
   extern WIN32UIBASE_LINKAGE const I_CHAR *GUI_CONDITION;  // Used for component name
}

// Common declaration of stl based classes
typedef std::vector< DString > STRINGVECTOR;

// User messages used throughout road runner
#define UM_IDDATA                 WM_APP +  1    // Passing data from ID Caller to Search Screen
#define UM_FUNCTIONKEYPRESSED     WM_APP +  3    // A function key was pressed
#define UM_READY                  WM_APP + 18    // We are through initializing RoadRunner
#define UM_LAUNCHDETAILS          WM_APP + 19    // Launches details after a new shareholder setup
#define UM_LAUNCHTRADING          WM_APP + 20    // Launches Trading after a new shareholder setup
#define UM_HOLDING_COMP           WM_APP + 21    // Re Launches Holding Company

// Use when dialog needs to post itself a message to set focus to another
//  control (typically when you can't set focus within a message handler).
//  If more than one control might need focus, send control id via the PostMessage.
#define UM_FOCUS                  WM_APP + 27
#define UM_EXPANDCASE             WM_APP + 28    // Tells the search screen to tell the AWD session to expand the case
#define UM_MSMASKSETFOCUS         WM_APP + 29    // Tells the parent dlg that mask edit got wm_setfucus
#define UM_MSMASKKILLFOCUS        WM_APP + 30    // Tells the parent dlg that mask edit got wm_setfucus

// The following message is posted at the end of BaseDlg's OnInitDialog.
//  BaseDlg will trap this message and invoke the virtual method
//  OnPostInitDialog.  This allows dialogs to postpone intensive operations
//  until after the OnInitDialog.
#define UM_POSTINITDIALOG           WM_APP + 201

// The following message is used to post an end session message to main window.
// This prevents depending on a resource ID
#define UM_ENDSESSION               WM_APP + 202
#define WM_VIEWITEMSELECTED         WM_APP + 203  // Used by CTimerListCtrl
#define UM_NEWSEARCH                WM_APP + 204  // Used by Confirmation to perform New Search while retaining AWD work obj

#define UM_OPENBRANCHLISTDLG        WM_APP + 1292
#define UM_OPENBROKERLISTDLG        WM_APP + 1293
#define UM_OPENSLSREPLISTDLG        WM_APP + 1294
#define WM_LAUNCH_IDENT_ACC         WM_APP + 1295
#define UM_OPENFUNDLISTDLG          WM_APP + 1296 // Launch Fund List Dialog
#define UM_OPENFUNDCLASSLISTDLG     WM_APP + 1297
#define UM_OPENBANKSEARCH           WM_APP + 1298

#define UM_OPENSELECTADDRESSDLG     WM_APP + 1299   
#define UM_ENDCURRENTSESSION        WM_APP + 1300   
#define UM_OPENFEEMODELDLG          WM_APP + 1301   
#define UM_OPENENTITYSEARCHDLG      WM_APP + 1302   
#define UM_OPENBROKERADDRESSDLG     WM_APP + 1303   
#define UM_OPENADDRESSSEARCHDLG     WM_APP + 1304   // Launch Address Search Dialog
#define UM_OPENFUNDGROUPDLG         WM_APP + 1305   
#define UM_OPENALERTMESSAGEDLG      WM_APP + 1306   // Alert box for unclaimed property
#define UM_OPENFNDBRKRLISTDLG       WM_APP + 1307
#define UM_IFDSSTATUSBARCHANGE      WM_APP + 1308   // update on logging tab that cause status change
#define UM_OPENASSOCIDHELPER        WM_APP + 1309   // update on logging tab that cause status change
#define UM_OPENHLDCOMPSEARCH        WM_APP + 1310
#define UM_OPENEXTERNALINSTITUTION  WM_APP + 1311


//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/uibase/win32uibase_global.hpp-arc  $
//
//   Rev 1.10   Apr 15 2010 18:11:00   popescu
//PET165541_FN01_QESI - RESP Gap_Dsk_Trading - F4 Browser screen helper...
//
//   Rev 1.9   Dec 22 2009 05:31:02   dchatcha
//IN# 1952546 - Indicator to show that the database DSK is connected to is scrambled.
//
//   Rev 1.8   Mar 25 2009 07:18:44   kitticha
//IN#1588682 - Small Enhancement - Feature search screen for Fund Broker Search.
//
//   Rev 1.7   Nov 06 2008 02:15:48   daechach
//PET5517 FN71 Unclaimed Property Phase 2
//
//   Rev 1.6   Nov 20 2006 13:47:30   jankovii
//PET 2287 FN01 - Grupo Mundial Trade Aggregation.
//
//   Rev 1.5   Mar 02 2005 17:57:02   porteanm
//PET 1171 FN01 - EUSD Address Search support.
//
//   Rev 1.4   Oct 19 2004 15:12:06   FENGYONG
//PET1117 FN54 - Fund Broker Static
//
//   Rev 1.3   Aug 10 2004 11:36:32   FENGYONG
//PET1117 FN5 - Client Condition Fee
//
//   Rev 1.2   May 11 2004 14:28:20   FENGYONG
//PET1046 FN1 - transfer-switch -Rel57
//
//   Rev 1.1   Oct 09 2002 17:42:56   PURDYECH
//New PVCS Database
//
//   Rev 1.0   Sep 10 2002 14:30:48   PURDYECH
//Initial revision.
//
