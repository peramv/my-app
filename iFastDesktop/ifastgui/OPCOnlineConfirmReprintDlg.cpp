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
// ^FILE   : OPCOnlineConfirmReprintDlg.cpp
// ^AUTHOR : Monica Porteanu
// ^DATE   : May 2005
//
// ----------------------------------------------------------
//
// ^CLASS    : OPCOnlineConfirmReprintDlg
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :  This is the code for a list selection dialog

//******************************************************************************
#include "stdafx.h"


#ifndef IFASTGUI_H
   #include "mfdstc.h"
#endif

#include "OPCOnlineConfirmReprintDlg.h"

#include <bfproc\abstractprocess.hpp>
#include <ifastbp\mfcaninterprocparam.hpp>
#include <ifastbp\OPCConfirmReprintprocessincludes.h>

#include <ifastcbo\DSTCommonFunction.hpp>
#include <ifastcbo\dstcworksession.hpp>

#include <uibase\DSTEdit.h>

extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_OPC_ONLINE_CONFIRM_REPRINT;
extern CLASS_IMPORT const I_CHAR* CMD_GUI_OPC_ONLINE_CONFIRM_REPRINT;
#include <bfproc\concretedialogcreator.hpp>
static ConcreteDialogCreator<OPCOnlineConfirmReprintDlg> dlgCreator( CMD_GUI_OPC_ONLINE_CONFIRM_REPRINT );

#ifdef _DEBUG
   #define new DEBUG_NEW
   #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

namespace
{
   const I_CHAR * const CLASSNAME = I_("OPCOnlineConfirmReprintDlg");   
}

namespace CND
{  // Conditions used
   extern const long GUI_ERR_UNKNOWN_EXCEPTION;
}

//*****************************************************************************
// Public methods
//*****************************************************************************
OPCOnlineConfirmReprintDlg::OPCOnlineConfirmReprintDlg( CWnd* pParent, 
						  					            GenericInterfaceContainer* pGIC, 
												        GenericInterface* pGIParent, 
												        const Command& rCommand )
: OPCConfirmReprintDlg( pParent, pGIC, pGIParent, rCommand), 
m_pWndItemInFocus(NULL)
{
   TRACE_CONSTRUCTOR(CLASSNAME, NULL_STRING);
   //{{AFX_DATA_INIT(OPCOnlineConfirmReprintDlg)
   //}}AFX_DATA_INIT
}

//*****************************************************************************
void OPCOnlineConfirmReprintDlg::DoDataExchange(CDataExchange* pDX)
{
   BaseMainDlg::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(OPCOnlineConfirmReprintDlg)
   //}}AFX_DATA_MAP
}

//*****************************************************************************
SEVERITY OPCOnlineConfirmReprintDlg::doInit()
{
   TRACE_METHOD(CLASSNAME, DOINIT);

   getParameter( OPC_ONLINE_CONFIRM_REPRINT::TRANSID, _dstrTransId );
   getParameter( OPC_ONLINE_CONFIRM_REPRINT::FUND,    _dstrFund );	
   getParameter( OPC_ONLINE_CONFIRM_REPRINT::CLASS,   _dstrClass );	
	   
   return NO_CONDITION;
}

//*****************************************************************************
BEGIN_MESSAGE_MAP(OPCOnlineConfirmReprintDlg, BaseMainDlg)
//{{AFX_MSG_MAP(OPCOnlineConfirmReprintDlg)
ON_BN_CLICKED(IDC_BTN_RESET, OnBtnReset)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()


//*****************************************************************************
// Message handlers
//*****************************************************************************
BOOL OPCOnlineConfirmReprintDlg::OnInitDialog() 
{
   TRACE_METHOD(CLASSNAME, ONINITDIALOG);

   BaseMainDlg::OnInitDialog();

   return TRUE;
}

//*****************************************************************************
void OPCOnlineConfirmReprintDlg::OnPostInitDialog()
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
bool OPCOnlineConfirmReprintDlg::doRefresh(GenericInterface *rpGICaller, 
   const I_CHAR *szOriginalCommand)
{ 
   TRACE_METHOD(CLASSNAME, DOREFRESH);

   //when called by the process from doRefresh, 	
   if (DString(szOriginalCommand) == I_("ReloadParams"))
   {
         getParameter( OPC_ONLINE_CONFIRM_REPRINT::TRANSID, _dstrTransId );
		 getParameter( OPC_ONLINE_CONFIRM_REPRINT::FUND,    _dstrFund );	
		 getParameter( OPC_CONFIRM_REPRINT::CLASS,          _dstrClass );	
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
void OPCOnlineConfirmReprintDlg::SetDlgCaption()
{
   DString dstrCaption = I_("Transaction Confirms"); 

	//DString dstrEntityName;
   /*	
   dynamic_cast<DSTCWorkSession *>(getBFWorkSession())->getFirstSequenced01AccountholderEntityName( getDataGroupId(),
																																	 _dstrAccount,
																																	 dstrEntityName );
	*/

   //SetShrAcctCaption( _dstrShareholder, _dstrAccount, dstrEntityName );
}

//****************************************************************
void OPCOnlineConfirmReprintDlg::OnBtnReset()
{
   TRACE_METHOD(CLASSNAME, I_("OnBtnReset"));

   CWaitCursor wait;

   //ResetListItem(IDC_LV_SHR_FUND_SPONSOR_AGREEMENT_LIST);
}

//******************************************************************
BOOL OPCOnlineConfirmReprintDlg::PreTranslateMessage(MSG* pMsg) 
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
// $Log:   Y:/VCS/BF iFAST/ifastgui/OPCOnlineConfirmReprintDlg.cpp-arc  $
// 
//    Rev 1.0   May 06 2005 13:12:20   porteanm
// Initial revision.
// 


