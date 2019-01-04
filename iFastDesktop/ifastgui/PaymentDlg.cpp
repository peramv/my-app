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
//
//******************************************************************************
//
// ^FILE   : PaymentDlg.cpp
// ^AUTHOR : 
// ^DATE   : 11/17/11
//
// ----------------------------------------------------------
//
// ^CLASS    : PaymentDlg
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :  This is the code for adding the Payment Flag on the processed Trade
//
//******************************************************************************
#include "stdafx.h"
#include "mfdstc.h"
#include "PaymentDlg.h"

#include <ifastcsi\csisession.h>
#include <ifastcsi\ifastcsi.h>
#include <ifastcbo\dstcommonfunction.hpp>
#include <ifastbp\mfcaninterprocparam.hpp>
#include <ifastcbo\dstcworksession.hpp>
#include <assert.h>
#include <ifastbp\transhistoryprocessincludes.h>
#include <bfproc\concretedialogcreator.hpp>


#include <ifastgui\ifasthistoricalinfo.hpp>
#include <ifastbp\ifasthistoricalparameters.hpp>

#include <ifastdataimpl\dse_dstc0393_req.hpp>
#ifndef DSTCOMBOBOX_H
   #include <uibase\DSTComboBox.h>
#endif


#ifndef INCLUDED_ASSERT_H
#define INCLUDED_ASSERT_H
#include <assert.h>
#endif

#include <uibase\dstbutton.h>

extern CLASS_IMPORT const I_CHAR* CMD_BPROC_PAYMENT_INFO_FLAG;
extern CLASS_IMPORT const I_CHAR* CMD_GUI_PAYMENT_INFO_FLAG;

extern CLASS_IMPORT const I_CHAR* CMD_BPROC_HISTORICAL_INFO;

#include <bfproc\concretedialogcreator.hpp>
static ConcreteDialogCreator< PaymentDlg > dlgCreator( CMD_GUI_PAYMENT_INFO_FLAG );

#ifdef _DEBUG
   #define new DEBUG_NEW
   #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

namespace
{
   const I_CHAR * const CLASSNAME = I_( "Payment" );
   const I_CHAR * const PENDPROCRECORD_TYPE = I_( "PendProcRecordType" );
   const I_CHAR *pTRANSNUM                       = I_( "TransNum" );   
   const I_CHAR *pACCOUNTNUM        =		I_("AccountNum");   
   const I_CHAR *NRCPT = I_( "NRCPT");
   const I_CHAR *pTRANSID = I_( "TransId" );

}

namespace CND
{  // Conditions used
   extern CLASS_IMPORT const long GUI_ERR_UNKNOWN_EXCEPTION;
}

namespace UAF
{
   extern CLASS_IMPORT I_CHAR * const MMF_PAYMENT_INFO;
   
}

namespace ifds
{	
	extern CLASS_IMPORT const BFNumericFieldId AccountNum;
}
namespace AUDITTYPE
{
   extern CLASS_IMPORT I_CHAR * const TRNDEC;
}

//*****************************************************************************
// Public methods
//*****************************************************************************
PaymentDlg::PaymentDlg( CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: BaseMainDlg( PaymentDlg::IDD, pParent, pGIC, pGIParent, rCommand, CLASSNAME )
,m_bDialogInit (false)
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   //{{AFX_DATA_INIT(PaymentDlg)
   //}}AFX_DATA_INIT
}

//*****************************************************************************
void PaymentDlg::DoDataExchange( CDataExchange* pDX )
{
   BaseMainDlg::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(PaymentDlg)
   //}}AFX_DATA_MAP
}


//*****************************************************************************
BEGIN_MESSAGE_MAP(PaymentDlg, BaseMainDlg)
//{{AFX_MSG_MAP(PaymentDlg)
ON_BN_CLICKED( IDC_BTN_HISTORICAL_PAYMENT_INFO, OnBtnHistoricalPayment )
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//*****************************************************************************
// Message handlers
//*****************************************************************************

BOOL PaymentDlg::OnInitDialog() 
{
	TRACE_METHOD( CLASSNAME, ONINITDIALOG );
	BaseMainDlg::OnInitDialog(); 

	AddControl (CTRL_COMBO, IDC_CMB_PAYMENT_INFO, IFASTBP_PROC::TRANSACTION_UPDATE, ifds::PaymentInfo, CTRLFLAG_INITCOMBO_BY_SUB_LIST); 
	
	return TRUE;
}

void PaymentDlg::OnPostInitDialog()
{
	TRACE_METHOD( CLASSNAME, ONPOSTINITDIALOG );
	DSTCWorkSession *dstWorkSession = dynamic_cast<DSTCWorkSession *>(getParent()->getBFWorkSession());

	SetUserAccesFunctionCode (UAF::MMF_PAYMENT_INFO); 
	
	ConnectControlsToData ();
	LoadControls();		
	
	m_bDialogInit = false;


}


//******************************************************************************
bool PaymentDlg::doRefresh( GenericInterface * rpGICaller,
                                      const I_CHAR* szOriginalCommand)
{ 
   TRACE_METHOD (CLASSNAME, DOREFRESH); 
   
   return true;
}

SEVERITY PaymentDlg::doInit()
{
	TRACE_METHOD( CLASSNAME, I_("doInit"));

	getParameter( pACCOUNTNUM, AccountNum );
	getParameter (PENDPROCRECORD_TYPE, m_RecordType);
   
	m_bDialogInit = true;

	return NO_CONDITION;
}
void PaymentDlg::ControlUpdated( UINT controlID, const DString &strValue )
{
	TRACE_METHOD( CLASSNAME, I_( "ControlUpdated" ) );
	
		 
	switch( controlID )
    {
      case IDC_CMB_PAYMENT_INFO:
         {				
			GetDlgItem(IDC_CMB_PAYMENT_INFO)->EnableWindow(hasUpdatePermission (UAF::MMF_PAYMENT_INFO));
		 }
		 break;
	  default:
         break;
   }
}
//****************************************************************************** 
void PaymentDlg::OnBtnHistoricalPayment ( )
{  
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OnBtnHistoricalPayment" ) ); 
   
   HISTORICAL_VECTOR historicalVector;
   DString dstrKeyIDI,dstrTransID,dstrPendingRid;

   getParent()->getField( this, IFASTBP_PROC::TRANS_LIST, ifds::TransId, dstrTransID );
  
   addIDITagValue(dstrKeyIDI, I_("TransId"), dstrTransID);
   setParameter(MFCAN_IP_PARAM::KEYS, dstrKeyIDI );
   
   
   setParameter(MFCAN_IP_PARAM::RECID, NULL_STRING);
   setParameter(MFCAN_IP_PARAM::TABLEID, I_("TRNDTL"));   
   setParameter(I_("TYPE"), I_("SINGLE" ));//MULTI SINGLE
   
   
   setParameter(MFCAN_IP_PARAM::ACCOUNT_NUM, AccountNum);
   
   
   E_COMMANDRETURN eRtn = invokeCommand (getParent(), 
         CMD_BPROC_HISTORICAL_INFO, PROC_NO_TYPE, false, NULL);
   switch (eRtn)
   {
      case CMD_OK:
      case CMD_CANCEL:
      case CMD_MODELESS_INPROCESS:
         break;
      default:
         // Display error
         ConditionMessageBox( FRAMEBELOW(), GETHIGHESTSEVERITY() );
         break;
   }

}

//*************************************************************************
//              Revision Control Entries
//******************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastgui/PaymentDlg.cpp-arc  $
// 
//    Rev 1.0   Dec 08 2011 00:32:06   wp040032
// Initial revision.
//

