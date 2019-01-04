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
// ^FILE   : WhereUsedDlg.cpp
// ^AUTHOR : Celia Zhang
// ^DATE   : 10/01/99
//
// ----------------------------------------------------------
//
// ^CLASS    : WhereUsedDlg
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :  This is the code for a list selection dialog
//
//******************************************************************************
#include "stdafx.h"

#ifndef IFASTGUI_H
   #include "MFDSTC.h"
#endif
#ifndef WHEREUSEDDLG_H
   #include "WhereUsedDlg.h"
#endif

#ifndef WHEREUSEDPROCESSINCLUDES_H
   #include <ifastbp\WhereUsedProcessIncludes.h>
#endif

#ifndef DSTCLISTCTRL_H
   #include <uibase\DSTListCtrl.h>
#endif

extern CLASS_IMPORT const I_CHAR* CMD_GUI_WHEREUSED;
#include <bfproc\concretedialogcreator.hpp>
static ConcreteDialogCreator< WhereUsedDlg > dlgCreator( CMD_GUI_WHEREUSED );

#ifdef _DEBUG
   #define new DEBUG_NEW
   #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

namespace
{
   const I_CHAR *CLASSNAME = I_( "WhereUsedDlg" );
   const I_CHAR *LV_WHEREUSEDLIST = I_( "WhereUsed List" );
}

namespace CND
{  // Conditions used
//CP20030319   extern CLASS_IMPORT const int GUI_ERR_UNKNOWN_EXCEPTION;
}

//*****************************************************************************
// Public methods
//*****************************************************************************

WhereUsedDlg::WhereUsedDlg( CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: BaseMainDlg( WhereUsedDlg::IDD, pParent, pGIC, pGIParent, rCommand, CLASSNAME )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   //{{AFX_DATA_INIT(WhereUsedDlg)
   //}}AFX_DATA_INIT
   //m_rbFixed = 1;
}

//*****************************************************************************

void WhereUsedDlg::DoDataExchange( CDataExchange* pDX )
{
   BaseMainDlg::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(WhereUsedDlg)
   //}}AFX_DATA_MAP
}

//*****************************************************************************

SEVERITY WhereUsedDlg::doInit()
{
   TRACE_METHOD( CLASSNAME, DOINIT );

   DString dstrEntityName, dstrEntityBirthName;

   getParent()->getParameter( WHEREUSEDPROC::ENTITY_NAME, dstrEntityName );
   m_EntityName = dstrEntityName.c_str();
   getParameter( WHEREUSEDPROC::BIRTHENTITY_NAME, dstrEntityBirthName );
   m_EntityBirthName = dstrEntityBirthName.c_str();
   return(NO_CONDITION);
}

//*****************************************************************************

BEGIN_MESSAGE_MAP(WhereUsedDlg, BaseMainDlg)
//{{AFX_MSG_MAP(WhereUsedDlg)
ON_BN_CLICKED( IDC_BTN_MORE, OnBtnMore )
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//*****************************************************************************
BOOL WhereUsedDlg::OnInitDialog() 
{
   TRACE_METHOD( CLASSNAME, ONINITDIALOG );
   BaseMainDlg::OnInitDialog();
   return(TRUE);
}

//*****************************************************************************
void WhereUsedDlg::OnPostInitDialog()
{
   TRACE_METHOD( CLASSNAME, I_( "OnPostInitDialog" ) );

   SetDlgItemText( IDC_TXT_ENTITYNAME, m_EntityName );
   SetDlgItemText( IDC_ENT_NAME_KANJI, m_EntityName );
   SetDlgItemText( IDC_ENT_NAME_KANA, m_EntityBirthName );
   AddListControl( CLASSNAME, IDC_LV_WHEREUSED, LV_WHEREUSEDLIST, ifds::WhereUsedListHeading, 
                   IFASTBP_PROC::WHEREUSED_LIST, 0, true, LISTFLAG_NOT_UPDATABLE );
   GetDlgItem (IDC_BTN_MORE)->EnableWindow (getParent ()->doMoreRecordsExist (this, 
      IFASTBP_PROC::WHEREUSED_LIST));
   LoadListControl( IDC_LV_WHEREUSED );
}

//*********************************************************************************************

void WhereUsedDlg::OnBtnMore () 
{
   TRACE_METHOD ( CLASSNAME, I_ ("OnBtnMore"));
   CWaitCursor wait;

   static int cursel = GetList (IDC_LV_WHEREUSED)->GetNextItem (-1, 
      LVIS_SELECTED | LVNI_FOCUSED);
   const DString *crtKey = &getParent ()->getCurrentListItemKey (this, 
      IFASTBP_PROC::WHEREUSED_LIST);

   if (getParent ()->performSearch (this, IFASTBP_PROC::WHEREUSED_LIST, 
      SEARCH_NEXT_BLOCK) <= WARNING)
   {
      LoadListControl (IDC_LV_WHEREUSED);
      if (*crtKey != NULL_STRING)
      {
         GetList (IDC_LV_WHEREUSED)->SetSelection (crtKey);
      }
   }
   GetDlgItem (IDC_BTN_MORE)->EnableWindow (getParent ()->doMoreRecordsExist (this, 
      IFASTBP_PROC::WHEREUSED_LIST));
   GetList (IDC_LV_WHEREUSED)->SetSelection (cursel, true, true);
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/WhereUsedDlg.cpp-arc  $
 * 
 *    Rev 1.7   Sep 15 2005 15:16:18   popescu
 * Incident#403519 - added CLASSNAME as the fifth parameter to  BaseMainDlg constructor
 * 
 *    Rev 1.6   May 17 2005 11:30:56   Fengyong
 * #Incident 272055 - Add more button to where used screen
 * 
 *    Rev 1.5   Mar 21 2003 18:42:22   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.4   Oct 09 2002 23:56:18   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.3   22 May 2002 19:16:36   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.2   27 Mar 2002 20:01:32   PURDYECH
 * Process/WindowFactory overhaul
 * 
 *    Rev 1.1   Sep 21 2000 14:22:24   OLTEANCR
 * Added display for entity name
 * 
 *    Rev 1.0   Feb 15 2000 11:01:28   SMITHDAV
 * Initial revision.
// 
//    Rev 1.8   Jan 14 2000 15:55:16   POPESCUS
// fix compiling issue
// 
//    Rev 1.7   Jan 14 2000 08:51:32   POPESCUS
// finally made those dialogs and processes work
// 
//    Rev 1.6   Nov 23 1999 11:57:04   POPESCUS
// Fixed compiling issue
// 
//    Rev 1.5   Nov 22 1999 10:34:58   ZHANGCEL
// Populate list using ListView
// 
//    Rev 1.4   Oct 27 1999 10:09:20   ZHANGCEL
// Populate list using Stingray
// 
//    Rev 1.3   Aug 26 1999 10:22:26   DT24433
// changed getFieldFromCurrentListItem to getField
 * 
 *
 */


