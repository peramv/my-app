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
// ^FILE   : OPCConfirmReprintDlg.cpp
// ^AUTHOR : Monica Porteanu
// ^DATE   : May 2005
//
// ----------------------------------------------------------
//
// ^CLASS    : OPCConfirmReprintDlg
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :  This is the code for a list selection dialog

//******************************************************************************
#include "stdafx.h"


#ifndef IFASTGUI_H
   #include "mfdstc.h"
#endif

#include "OPCConfirmReprintDlg.h"

#include <bfproc\abstractprocess.hpp>
#include <ifastbp\mfcaninterprocparam.hpp>
#include <ifastbp\ConfirmReprintprocessincludes.h>

#include <ifastcbo\DSTCommonFunction.hpp>
#include <ifastcbo\dstcworksession.hpp>

#include <uibase\DSTEdit.h>

//extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_OPC_CONFIRM_REPRINT;
extern CLASS_IMPORT const I_CHAR* CMD_GUI_OPC_CONFIRM_REPRINT;
#include <bfproc\concretedialogcreator.hpp>
static ConcreteDialogCreator<OPCConfirmReprintDlg> dlgCreator( CMD_GUI_OPC_CONFIRM_REPRINT );

#ifdef _DEBUG
   #define new DEBUG_NEW
   #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

namespace
{
   const I_CHAR * const CLASSNAME = I_("OPCConfirmReprintDlg");   
}

namespace CND
{  // Conditions used
   extern const long GUI_ERR_UNKNOWN_EXCEPTION;
}

//*****************************************************************************
void OPCConfirmReprintDlg::DoDataExchange(CDataExchange* pDX)
{
   BaseMainDlg::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(OPCConfirmReprintDlg)
   //}}AFX_DATA_MAP
}

//*****************************************************************************
BEGIN_MESSAGE_MAP(OPCConfirmReprintDlg, BaseMainDlg)
//{{AFX_MSG_MAP(OPCConfirmReprintDlg)
ON_BN_CLICKED(IDC_BTN_RESET, OnBtnReset)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//*****************************************************************************
// Public methods
//*****************************************************************************
OPCConfirmReprintDlg::OPCConfirmReprintDlg( CWnd* pParent, 
											GenericInterfaceContainer* pGIC, 
											GenericInterface* pGIParent, 
											const Command& rCommand )
: ConfirmReprintDlg( pParent, pGIC, pGIParent, rCommand), 
m_pWndItemInFocus(NULL)
{
   TRACE_CONSTRUCTOR(CLASSNAME, NULL_STRING);   
}

//*****************************************************************************
// Message handlers
//*****************************************************************************
void OPCConfirmReprintDlg::OnPostInitDialog()
{
   TRACE_METHOD(CLASSNAME, ONPOSTINITDIALOG);
 
   
   AddControl( CTRL_COMBO, 
		       IDC_CMB_NEW_REQUEST, 
			   IFASTBP_PROC::OPC_CONFIRM_REPRINT, 
               ifds::OPCConfirmReprint, 
			   CTRLFLAG_DEFAULT | CTRLFLAG_INITCOMBO_BY_SUB_LIST );	

   AddControl( CTRL_COMBO, 
		       IDC_CMB_CLIENT_COPY, 
			   IFASTBP_PROC::OPC_CONFIRM_REPRINT, 
               ifds::ClientCopy, 
			   CTRLFLAG_DEFAULT | CTRLFLAG_INITCOMBO_BY_SUB_LIST );	

   AddControl( CTRL_COMBO, 
		       IDC_CMB_BROKER_COPY, 
			   IFASTBP_PROC::OPC_CONFIRM_REPRINT, 
               ifds::BrokerCopy, 
			   CTRLFLAG_DEFAULT | CTRLFLAG_INITCOMBO_BY_SUB_LIST );	

   AddControl( CTRL_COMBO, 
		       IDC_CMB_SALES_REP_COPY, 
			   IFASTBP_PROC::OPC_CONFIRM_REPRINT, 
               ifds::SalesRepCopy, 
			   CTRLFLAG_DEFAULT | CTRLFLAG_INITCOMBO_BY_SUB_LIST );	

   AddControl( CTRL_STATIC, 
		       IDC_TXT_USER_NAME, 
			   IFASTBP_PROC::OPC_CONFIRM_REPRINT, 
               ifds::RequestedBy, 
			   CTRLFLAG_DEFAULT ); 

   AddControl( CTRL_STATIC, 
		       IDC_TXT_REPRINT_DATE, 
			   IFASTBP_PROC::OPC_CONFIRM_REPRINT, 
               ifds::SchedReprintDate, 
			   CTRLFLAG_DEFAULT );  

   doRefresh(this, NULL);
}


//******************************************************************************
bool OPCConfirmReprintDlg::doRefresh(GenericInterface *rpGICaller, 
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

   ConnectControlsToData();	
   LoadControl( IDC_CMB_NEW_REQUEST );
   LoadControl( IDC_CMB_CLIENT_COPY );
   LoadControl( IDC_CMB_BROKER_COPY );
   LoadControl( IDC_CMB_SALES_REP_COPY );
   LoadControl( IDC_TXT_USER_NAME );
   LoadControl( IDC_TXT_REPRINT_DATE );
	
   SetDlgCaption();	
	
   return true;
}

//****************************************************************
void OPCConfirmReprintDlg::OnBtnReset()
{
   TRACE_METHOD(CLASSNAME, I_("OnBtnReset"));

   CWaitCursor wait;
   
   getParent()->send(this,I_("Reset") );
   
   ReInitControl( IDC_CMB_NEW_REQUEST,
	              IFASTBP_PROC::OPC_CONFIRM_REPRINT, 
				  ifds::OPCConfirmReprint );		

   ReInitControl( IDC_CMB_CLIENT_COPY,
	              IFASTBP_PROC::OPC_CONFIRM_REPRINT, 
				  ifds::ClientCopy );		

   ReInitControl( IDC_CMB_BROKER_COPY,
	              IFASTBP_PROC::OPC_CONFIRM_REPRINT, 
				  ifds::BrokerCopy );		

   ReInitControl( IDC_CMB_SALES_REP_COPY,
	              IFASTBP_PROC::OPC_CONFIRM_REPRINT, 
				  ifds::SalesRepCopy );		   	

   doRefresh(this, NULL);
}

//******************************************************************
BOOL OPCConfirmReprintDlg::PreTranslateMessage(MSG* pMsg) 
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
// $Log:   Y:/VCS/BF iFAST/ifastgui/OPCConfirmReprintDlg.cpp-arc  $
// 
//    Rev 1.4   May 25 2005 14:56:16   porteanm
// PET OPC Confirm Reprint - Reset.
// 
//    Rev 1.3   May 24 2005 12:58:18   porteanm
// PET OPC Confirm Reprint - Renamed OPC files. Changed class hierarchy.
// 
//    Rev 1.2   May 06 2005 13:11:46   porteanm
// PET OPC Confirm Reprint - Typos for Release 63.
// 
//    Rev 1.1   May 05 2005 17:36:12   porteanm
// PET OPC Confirm Reprint - New screen for Release 63.
// 
//    Rev 1.0   May 05 2005 11:18:46   porteanm
// Initial revision.
// 

