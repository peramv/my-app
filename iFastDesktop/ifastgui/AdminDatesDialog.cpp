// ACBDlg.cpp : implementation file
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
// ^FILE   : AdminDatesDialog.cpp
// ^AUTHOR : Yingbao  Li
// ^DATE   : 05/05/1999
//
// ^CLASS    : AdminDatesDialog
// ^SUBCLASS : BaseMainDlg
//
// ^CLASS DESCRIPTION : 
//
//******************************************************************************

#include "stdafx.h"
#include "mfdstc.h"

#ifndef ADMINDATES_H
   #include "AdminDatesDialog.h"
#endif
#ifndef ADMINDATESINCLUDES_H
   #include <ifastbp\admindatesprocessincludes.h>
#endif

extern CLASS_IMPORT const I_CHAR* CMD_GUI_ADMINDATES;
#include <bfproc\concretedialogcreator.hpp>
static ConcreteDialogCreator< AdminDatesDialog > dlgCreator( CMD_GUI_ADMINDATES );

namespace
{
   const I_CHAR *CLASSNAME             = I_( "AdminDatesDialog" );
   const I_CHAR *MODDATE = I_( "MODDATE" );

}

BEGIN_MESSAGE_MAP(AdminDatesDialog, BaseMainDlg)
//{{AFX_MSG_MAP(AdminDatesDialog)

//}}AFX_MSG_MAP
END_MESSAGE_MAP()



//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
AdminDatesDialog::AdminDatesDialog( CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: BaseMainDlg( AdminDatesDialog::IDD, pParent, pGIC, pGIParent, rCommand, CLASSNAME )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
}

//--------------------------------------------
SEVERITY AdminDatesDialog::doInit()
{
   SEVERITY sevRtn = SEVERE_ERROR;

   getParameter( I_("DisplayType"), DisplayType );

   sevRtn = NO_CONDITION;
   return(sevRtn);
}
//-------------------------------------------------

void AdminDatesDialog::OnPostInitDialog()
{

   TRACE_METHOD( CLASSNAME, I_("OnPostInitDialog")); 
   DispInfo();

}

//---------------------------------------------------------------------------
void AdminDatesDialog::DispInfo()
{       
   DString  str;
   if( DisplayType == I_("ProcessDateAndTime") )
   {
      GetDlgItem( IDC_LBL_FIELD1 )->ShowWindow( SW_HIDE ); // Mod Date Label
      GetDlgItem( IDC_LBL_FIELD2 )->ShowWindow( SW_HIDE ); // Process Date #1 Label
      GetDlgItem( IDC_LBL_FIELD3 )->ShowWindow( SW_HIDE ); // Mod User Label
      GetDlgItem( IDC_LBL_FIELD4 )->ShowWindow( SW_HIDE ); // User Name Label
      GetDlgItem( IDC_TXT_MOD_DATE )->ShowWindow( SW_HIDE );
      GetDlgItem( IDC_TXT_PROCESS_DATE )->ShowWindow( SW_HIDE );
      GetDlgItem( IDC_TXT_MOD_USER )->ShowWindow( SW_HIDE );
      GetDlgItem( IDC_TXT_USER_NAME )->ShowWindow( SW_HIDE );
      getParent()->getField( this, PROCESS_DATE, str );
      str.stripAll();   if( str==I_("//") )str=I_("");
      SetDlgItemText( IDC_LBL_FIELD6, str.c_str() );
      getParent()->getField( this, PROCESS_TIME, str );
      str.stripAll();   if( str==I_("//") )str=I_("");
      SetDlgItemText( IDC_LBL_FIELD8, str.c_str() );
      
   }
   else // Default
   {
      GetDlgItem( IDC_LBL_FIELD5 )->ShowWindow( SW_HIDE ); // Process Date #2 Label
      GetDlgItem( IDC_LBL_FIELD6 )->ShowWindow( SW_HIDE ); // Process Date #2 Value
      GetDlgItem( IDC_LBL_FIELD7 )->ShowWindow( SW_HIDE ); // Process Time Label
      GetDlgItem( IDC_LBL_FIELD8 )->ShowWindow( SW_HIDE ); // Process Time Value
      getParent()->getField( this,MOD_DATE, str );
      str.stripAll();  if( str==I_("//") )str=I_("");
      SetDlgItemText( IDC_TXT_MOD_DATE, str.c_str() );
      getParent()->getField( this,MOD_USER, str );
      str.stripAll();   if( str==I_("//") )str=I_("");
      SetDlgItemText( IDC_TXT_MOD_USER, str.c_str() );
      getParent()->getField( this,PROCESS_DATE, str );
      str.stripAll();   if( str==I_("//") )str=I_("");
      SetDlgItemText( IDC_TXT_PROCESS_DATE, str.c_str() );
      getParent()->getField( this,PROCESS_USER, str );
      str.stripAll();   if( str==I_("//") )str=I_("");
      SetDlgItemText( IDC_TXT_USER_NAME, str.c_str() );
   }
}
//---------------------------------------------------------------------------
BOOL AdminDatesDialog::OnInitDialog()
{
   TRACE_METHOD( CLASSNAME, I_("OnInitDialog"));
   BaseMainDlg::OnInitDialog();
   UpdateData(FALSE);
   DispInfo();
   ShowWindow(SW_SHOW);

   return(TRUE);
}

//----------------------------------------------------------------------------

void AdminDatesDialog::DoDataExchange(CDataExchange* pDX)
{
   BaseMainDlg::DoDataExchange(pDX);


}
//-----------------------------------------------------------------------------
bool AdminDatesDialog::doRefresh(
                                GenericInterface * /*rpGICaller*/, 
                                const I_CHAR * //*szOriginalCommand
                                )
{  
   DispInfo();
   ShowWindow(SW_SHOW);
   return(true);
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/AdminDatesDialog.cpp-arc  $
 * 
 *    Rev 1.5   Sep 15 2005 15:10:20   popescu
 * Incident#403519 - added CLASSNAME as the fifth parameter to  BaseMainDlg constructor
 * 
 *    Rev 1.4   Feb 19 2005 18:13:14   hernando
 * PET1117 FN66-68 - Added alternate display; Process Date and ProcessTime.
 * 
 *    Rev 1.3   Mar 21 2003 18:32:06   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.2   Oct 09 2002 23:55:28   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.1   27 Mar 2002 20:00:52   PURDYECH
 * Process/WindowFactory overhaul
 * 
 *    Rev 1.0   Feb 15 2000 11:01:04   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.1   Jul 08 1999 10:04:34   SMITHDAV
 * Modify revision history commaent format to old
 * style comment -- I can't seem to get new style comments to work.
 *
 */
