//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by International Financial Data Services,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2005 by International Financial Data Services
//
//******************************************************************************
//
// ^FILE   : ConfirmReprintDlg.cpp
// ^AUTHOR : Monica Porteanu
// ^DATE   : May 2005
//
// ----------------------------------------------------------
//
// ^CLASS    : ConfirmReprintDlg
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :  This is the code for a list selection dialog

//******************************************************************************
#include "stdafx.h"


#ifndef IFASTGUI_H
   #include "mfdstc.h"
#endif

#include "ConfirmReprintDlg.h"

#include <bfproc\abstractprocess.hpp>
#include <ifastbp\mfcaninterprocparam.hpp>
#include <ifastbp\ConfirmReprintprocessincludes.h>

#include <ifastcbo\DSTCommonFunction.hpp>
#include <ifastcbo\dstcworksession.hpp>

#include <uibase\DSTEdit.h>

extern CLASS_IMPORT const I_CHAR* CMD_GUI_CONFIRM_REPRINT;
#include <bfproc\concretedialogcreator.hpp>
static ConcreteDialogCreator<ConfirmReprintDlg> dlgCreator( CMD_GUI_CONFIRM_REPRINT );

#ifdef _DEBUG
   #define new DEBUG_NEW
   #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

namespace
{
   const I_CHAR * const CLASSNAME = I_("ConfirmReprintDlg");   
}

namespace CND
{  // Conditions used
   extern const long GUI_ERR_UNKNOWN_EXCEPTION;
}

//*****************************************************************************
// Public methods
//*****************************************************************************
ConfirmReprintDlg::ConfirmReprintDlg( CWnd* pParent, 
						  			  GenericInterfaceContainer* pGIC, 
									  GenericInterface* pGIParent, 
									  const Command& rCommand )
: BaseMainDlg(ConfirmReprintDlg::IDD, pParent, pGIC, pGIParent, rCommand, CLASSNAME), 
m_pWndItemInFocus(NULL)
{
   TRACE_CONSTRUCTOR(CLASSNAME, NULL_STRING);
   //{{AFX_DATA_INIT(ConfirmReprintDlg)
   //}}AFX_DATA_INIT
}

//*****************************************************************************
void ConfirmReprintDlg::DoDataExchange(CDataExchange* pDX)
{
   BaseMainDlg::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(ConfirmReprintDlg)
   //}}AFX_DATA_MAP
}

//*****************************************************************************
SEVERITY ConfirmReprintDlg::doInit()
{
   TRACE_METHOD(CLASSNAME, DOINIT);

   getParameter( CONFIRM_REPRINT::ACCOUNTNUM, _dstrAccountNum );
   getParameter( CONFIRM_REPRINT::TRANSID,    _dstrTransId );
   getParameter( CONFIRM_REPRINT::FUND,       _dstrFund );	
   getParameter( CONFIRM_REPRINT::CLASS,      _dstrClass );	
	   
   return NO_CONDITION;
}

//*****************************************************************************
BEGIN_MESSAGE_MAP(ConfirmReprintDlg, BaseMainDlg)
//{{AFX_MSG_MAP(ConfirmReprintDlg)
ON_BN_CLICKED(IDC_BTN_RESET, OnBtnReset)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()


//*****************************************************************************
// Message handlers
//*****************************************************************************
BOOL ConfirmReprintDlg::OnInitDialog() 
{
   TRACE_METHOD(CLASSNAME, ONINITDIALOG);

   BaseMainDlg::OnInitDialog();

   return TRUE;
}

//*****************************************************************************
void ConfirmReprintDlg::OnPostInitDialog()
{
   TRACE_METHOD(CLASSNAME, ONPOSTINITDIALOG);
   
   /*
	AddControl( CTRL_COMBO, 
		         IDC_CMB_FUND_SPONSOR_CODE, 
					IFASTBP_PROC::SHR_FUND_SPONSOR_AGREEMENT_LIST, 
               ifds::FundGroup, 
					CTRLFLAG_DEFAULT | CTRLFLAG_INITCOMBO_BY_SUB_LIST, 
               (UINT)IDC_LV_SHR_FUND_SPONSOR_AGREEMENT_LIST);	
   */

   doRefresh(this, NULL);
}


//******************************************************************************
bool ConfirmReprintDlg::doRefresh(GenericInterface *rpGICaller, 
   const I_CHAR *szOriginalCommand)
{ 
   TRACE_METHOD(CLASSNAME, DOREFRESH);

   //when called by the process from doRefresh, 	
   if (DString(szOriginalCommand) == I_("ReloadParams"))
   {
         getParameter( CONFIRM_REPRINT::ACCOUNTNUM, _dstrAccountNum );
         getParameter( CONFIRM_REPRINT::TRANSID,    _dstrTransId );
		 getParameter( CONFIRM_REPRINT::FUND,       _dstrFund );	
		 getParameter( CONFIRM_REPRINT::CLASS,      _dstrClass );	
   }
    
   //this will load the connected controls
   /*
   LoadListControl( IDC_LV_SHR_FUND_SPONSOR_AGREEMENT_LIST );    
   
   DSTListCtrl *pPIDSTListCtrl = GetList( IDC_LV_SHR_FUND_SPONSOR_AGREEMENT_LIST );

   if( pPIDSTListCtrl )
   {
     if( pPIDSTListCtrl->GetItemCount() <= 0 )
     {         
         //add a new row if list is empty, to simulate the normal behaviour
         AddToListControl(IDC_LV_SHR_FUND_SPONSOR_AGREEMENT_LIST);
      }
   }
   */
	
   SetDlgCaption();	
	
   return true;
}

//*************************************************************************
void ConfirmReprintDlg::SetDlgCaption()
{
   DString dstrCaption; 
   CString cstrConfirm,cstrAcct,cstrTranId,cstrFund,cstrClass;
   cstrConfirm.LoadString(TXT_CONFIRMS);
   dstrCaption = DString(cstrConfirm);

   cstrAcct.LoadString(IDS_TXT_ACCT_NUM);
   cstrTranId.LoadString(TXT_TRANS_TRANSID);
   cstrFund.LoadString(TXT_TRANS_FUND);
   cstrClass.LoadString(TXT_TRANS_CLASS);

   dstrCaption = dstrCaption 
			   + DString(cstrAcct)     + _dstrAccountNum			   
			   + DString(cstrTranId) + _dstrTransId
			   + DString(cstrFund)       + _dstrFund
			   + DString(cstrClass)      + _dstrClass;			   
	     
   SetWindowText( dstrCaption.c_str() );
}

//****************************************************************
void ConfirmReprintDlg::OnBtnReset()
{
   TRACE_METHOD(CLASSNAME, I_("OnBtnReset"));

   CWaitCursor wait;

   //ResetListItem(IDC_LV_SHR_FUND_SPONSOR_AGREEMENT_LIST);
}

//******************************************************************
BOOL ConfirmReprintDlg::PreTranslateMessage(MSG* pMsg) 
{
   BOOL isTranslated = FALSE;

   //do not allow F4 on the edit controls that are not updateable   
	if (pMsg->message == WM_KEYDOWN && 
      (int)(pMsg->wParam) == VK_F4 && 
      !IsSelectedCtrlUpdateable())
   {
      return TRUE;
   }   	
	
   return BaseMainDlg::PreTranslateMessage(pMsg);
}

//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastgui/ConfirmReprintDlg.cpp-arc  $
// 
//    Rev 1.4   Nov 19 2011 01:26:00   wp040143
// P0186484/FN06 - DESKTOP - iFast Desktop (French Customizations)
// 
//    Rev 1.3   Sep 15 2005 15:11:08   popescu
// Incident#403519 - added CLASSNAME as the fifth parameter to  BaseMainDlg constructor
// 
//    Rev 1.2   May 30 2005 17:58:18   porteanm
// PET OPC Confirm Reprint - Title bar.
// 
//    Rev 1.1   May 25 2005 17:25:12   porteanm
// OPC Confirm Reprint - Title bar.
// 
//    Rev 1.0   May 24 2005 12:55:12   porteanm
// Initial revision.
// 


