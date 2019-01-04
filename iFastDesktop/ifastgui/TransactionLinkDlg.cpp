// TransactionLinkDlg.cpp : implementation file
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
// ^FILE   :TransactionLinkDlg.cpp
// ^AUTHOR : Yingbao  Li
// ^DATE   : 11/05/1999
//
// ^CLASS    : TransactionLinkDlg
// ^SUBCLASS : BaseMainDlg
//
// ^CLASS DESCRIPTION : 
//
//******************************************************************************


#include "stdafx.h"
#include "mfdstc.h"
#include "TransactionLinkDlg.h"
#include <ifastbp\TransactionLinkProcessIncludes.h>


#include <bfproc\concretedialogcreator.hpp>
static ConcreteDialogCreator< TransactionLinkDlg > dlgCreator( CMD_GUI_TRANS_LINK );

#ifdef _DEBUG
   #undef THIS_FILE
static char THIS_FILE[]=__FILE__;
   #define new DEBUG_NEW
#endif

namespace
{  
   const I_CHAR *CLASSNAME             = I_( "TransactionLinkDialog" );
}
namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId TransLinkHeading;
}

TransactionLinkDlg::TransactionLinkDlg( CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: BaseMainDlg( TransactionLinkDlg::IDD, pParent, pGIC, pGIParent, rCommand, CLASSNAME )
{
   
}

//***************************************************************
//  Afx Data Exchange
//***************************************************************


void TransactionLinkDlg::DoDataExchange(CDataExchange* pDX)
{
   BaseMainDlg::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(TransactionLinkDlg)
   //}}AFX_DATA_MAP
}

//******************************************************************************

BEGIN_MESSAGE_MAP(TransactionLinkDlg, BaseMainDlg)
//{{AFX_MSG_MAP(TransactionLinkDlg)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//******************************************************************************
// Message handlers
//******************************************************************************

//******************************************************************************
// Protected methods
//******************************************************************************

BOOL TransactionLinkDlg::OnInitDialog() 
{
   TRACE_METHOD( CLASSNAME, I_("OnInitDialog") );
   BaseMainDlg::OnInitDialog();
 
   setWinTitle();

   return(TRUE);  
}

//******************************************************************************
void TransactionLinkDlg::OnPostInitDialog()
{
   TRACE_METHOD( CLASSNAME, ONPOSTINITDIALOG );
   AddListControl( CLASSNAME, IDC_LST_TRANS_LINK, I_( "TransactionLink" ), 
                  ifds::TransLinkHeading, IFASTBP_PROC::TRANSACTION_LINK_LIST,
                  0,true,LISTFLAG_NOT_AUTO_ADD
                  );
   ConnectControlsToData();  
   LoadListControl(IDC_LST_TRANS_LINK);
   UpdateData(FALSE);
}

//******************************************************************************
SEVERITY TransactionLinkDlg::doInit()
{
   
   getParameter( TRANS_LINK_PARAM::ACCOUNT_NUM, accountNum_ );
   getParameter( TRANS_LINK_PARAM::TRANS_NUM, transNum_ );
   return(NO_CONDITION);
}


//******************************************************************************
bool TransactionLinkDlg::doRefresh(
                                    GenericInterface * /*rpGICaller*/, 
                                    const I_CHAR * //*szOriginalCommand
                                    )
{  

   return(true);
}

//******************************************************************************
void TransactionLinkDlg::setWinTitle()
{
   CString cstr;
   cstr.LoadString( TXT_ACCOUNT_NBR );  
   DString caption = GetBaseCaption();
   caption = caption + (LPCTSTR)cstr;
   caption += I_("=") + accountNum_+I_(";");
   cstr.LoadString( TXT_TRANS_TRANSNUM );
   
   caption = caption +( LPCTSTR )cstr + I_("=") + transNum_;
   SetWindowText( caption.c_str() );
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/TransactionLinkDlg.cpp-arc  $
// 
//    Rev 1.1   Sep 15 2005 15:16:00   popescu
// Incident#403519 - added CLASSNAME as the fifth parameter to  BaseMainDlg constructor
// 
//    Rev 1.0   Jul 06 2005 16:43:56   Yingbaol
// Initial revision.
 * 
 
 */
