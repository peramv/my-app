// RebookParamDlg.cpp : implementation file
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
//    Copyright 2005 by DST Systems, Inc.
//
//******************************************************************************
//
// ^FILE   :RebookParamDlg.cpp
// ^AUTHOR : Yingbao  Li
// ^DATE   : 26/06/2006
//
// ^CLASS    : RebookParamDlg
// ^SUBCLASS : BaseMainDlg
//
// ^CLASS DESCRIPTION : 
//
//******************************************************************************


#include "stdafx.h"
#include "mfdstc.h"
#include "RebookParamDlg.h"
#include <ifastbp\RebookParamProcessIncludes.h>


extern CLASS_IMPORT const I_CHAR* CMD_GUI_REBOOK_PARAM;
#include <bfproc\concretedialogcreator.hpp>
static ConcreteDialogCreator< RebookParamDlg > dlgCreator( CMD_GUI_REBOOK_PARAM );

#ifdef _DEBUG
   #undef THIS_FILE
static char THIS_FILE[]=__FILE__;
   #define new DEBUG_NEW
#endif

namespace
{  
   const I_CHAR *CLASSNAME             = I_( "RebookParamDialog" );
   const I_CHAR *YES                   = I_( "Y" );
   const I_CHAR *NO                    = I_( "N" );
};

RebookParamDlg::RebookParamDlg( CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: BaseMainDlg( RebookParamDlg::IDD, pParent, pGIC, pGIParent, rCommand, CLASSNAME )
{
   
}

//***************************************************************
//  Afx Data Exchange
//***************************************************************


void RebookParamDlg::DoDataExchange(CDataExchange* pDX)
{
   BaseMainDlg::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(RebookParamDlg)
   //}}AFX_DATA_MAP
}

//******************************************************************************

BEGIN_MESSAGE_MAP(RebookParamDlg, BaseMainDlg)
//{{AFX_MSG_MAP(RebookParamDlg)

	ON_BN_CLICKED(IDC_RD_SAME_ACCOUNT_TRANSTYPE, OnRbSameAccountTransType)
	ON_BN_CLICKED(IDC_RD_DIFF_ACCOUNT_TRANSTYPE, OnRbDiffAccountTransType)


//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//******************************************************************************
// Message handlers
//******************************************************************************

//******************************************************************************
// Protected methods
//******************************************************************************

BOOL RebookParamDlg::OnInitDialog() 
{
   TRACE_METHOD( CLASSNAME, I_("OnInitDialog") );
   BaseMainDlg::OnInitDialog();
   setDlgTitle();
   MoveDialog(GUIPOS_VERTICAL,-250);            
 
   return(TRUE);  
}

//******************************************************************************
void RebookParamDlg::OnPostInitDialog()
{
   TRACE_METHOD( CLASSNAME, ONPOSTINITDIALOG );
   DString use(NULL_STRING);
   getParent()->getField(this,RebookField::UseSameAccountTransType,use);
   bool bSelSame = use == YES? true:false;
   ((CButton* )GetDlgItem(IDC_RD_SAME_ACCOUNT_TRANSTYPE))->SetCheck(bSelSame);
   ((CButton* )GetDlgItem(IDC_RD_DIFF_ACCOUNT_TRANSTYPE))->SetCheck(!bSelSame);
   DString commRebate,estateAlloc,rebookExist,rebookCopy;
   getParent()->getField(this, RebookField::IsCommissionRebate,commRebate,false );
   getParent()->getField(this, RebookField::IsEstateAllocation,estateAlloc,false );
   getParent()->getField(this, RebookField::RebookExist,rebookExist,false );
   getParent()->getField(this, RebookField::RebookCopy,rebookCopy,false );
   commRebate.strip().upperCase();
   estateAlloc.strip().upperCase();
   rebookExist.strip().upperCase();
   rebookCopy.strip().upperCase();
   CString cDisp1,cDisp2;
   if (estateAlloc == YES)
   {
      cDisp1.LoadString (IDS_WARN_ESTATE_ALLOC);  
   }
   if (commRebate == YES)
   {
      cDisp1.LoadString (IDS_WARN_COMM_REBATE);
   }
   if (rebookExist == YES)
   {
      cDisp2.LoadString (IDS_WARN_REBOOK_ALREADY_EXIST);
   }
   if (rebookCopy == NO)
   {
	    CButton* pRB = (CButton*) GetDlgItem(IDC_RD_SAME_ACCOUNT_TRANSTYPE);
		pRB->SetCheck(0);
		pRB->EnableWindow(false);
		OnRbDiffAccountTransType();
		((CButton* )GetDlgItem(IDC_RD_DIFF_ACCOUNT_TRANSTYPE))->SetCheck(true);
   }
   if (!cDisp2.IsEmpty() && !cDisp1.IsEmpty())
   {
         CWnd* wnd = GetDlgItem(IDC_WARN_REBOOK );
         wnd->SetWindowText( cDisp1 );
         wnd = GetDlgItem(IDC_WARN_REBOOK2 );
         wnd->SetWindowText( cDisp2 );
   }
   else if( !cDisp1.IsEmpty() && cDisp2.IsEmpty() )
   {
      CWnd* wnd = GetDlgItem(IDC_WARN_REBOOK );
      wnd->SetWindowText( cDisp1 );
   }
   else if ( !cDisp2.IsEmpty()&& cDisp1.IsEmpty() )
   {
      CWnd* wnd = GetDlgItem(IDC_WARN_REBOOK );
      wnd->SetWindowText( cDisp2 );   
   }
}

//******************************************************************************
SEVERITY RebookParamDlg::doInit()
{
   
   getParameter( TRANS_REBOOK_PARAM::ACCOUNT_NUM, accountNum_ );
   getParameter( TRANS_REBOOK_PARAM::TRANS_NUM, transNum_ );
   return(NO_CONDITION);
}


//******************************************************************************
bool RebookParamDlg::doRefresh(
                                    GenericInterface * /*rpGICaller*/, 
                                    const I_CHAR * //*szOriginalCommand
                                    )
{  
   return(true);
}

//******************************************************************************
void RebookParamDlg::setDlgTitle()
{
   CString cstr;
   cstr.LoadString( TXT_ACCOUNT_NBR );
   DString caption;   
   caption = GetBaseCaption() + ( LPCTSTR )cstr +I_("=")+ accountNum_+I_(";");
   cstr.LoadString( TXT_TRANS_TRANSNUM );
   caption  +=( LPCTSTR )cstr;
   caption +=I_("=")+transNum_;
   SetWindowText( caption.c_str() );
}
//*******************************************************************************
void RebookParamDlg::OnRbSameAccountTransType()
{
   getParent()->setField(this,RebookField::UseSameAccountTransType,YES);
}
//*******************************************************************************
void RebookParamDlg::OnRbDiffAccountTransType()
{
   getParent()->setField(this,RebookField::UseSameAccountTransType,NO);
}
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/RebookParamDlg.cpp-arc  $
// 
//    Rev 1.5   Sep 15 2005 15:14:44   popescu
// Incident#403519 - added CLASSNAME as the fifth parameter to  BaseMainDlg constructor
// 
//    Rev 1.4   Sep 07 2005 10:55:02   popescu
// Incident # 397151 - split the warnings message regarding comm rebate and estate allocation in two messages
// 
//    Rev 1.3   Aug 17 2005 14:36:40   Yingbaol
// PET1235,FN01:minor changes for same account and transtype radio button.
// 
//    Rev 1.2   Jul 25 2005 11:38:38   Yingbaol
// PET1235,FN01:move the Rebook param  to the middle of  CRT
// 
//    Rev 1.1   Jul 18 2005 10:49:16   Yingbaol
// PEt1235,FN01: change window title
// 
//    Rev 1.0   Jul 06 2005 16:41:24   Yingbaol
// Initial revision.
 * 
 
 */
