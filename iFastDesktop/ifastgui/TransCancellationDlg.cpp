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
// ^FILE   : TransCancellationDlg.cpp
// ^AUTHOR : 
// ^DATE   : 02/28/05
//
// ----------------------------------------------------------
//
// ^CLASS    : TransCancellationDlg
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

#ifndef TransCancellationDlg_H
   #include "TransCancellationDlg.h"
#endif

#ifndef CONFIGMANAGER_HPP
   #include <ConfigManager.hpp>
#endif

#ifndef DSTCOMBOBOX_H
   #include <uibase\DSTComboBox.h>
#endif

#ifndef DSTCOMMONFUNCTION_HPP
   #include <ifastcbo\DSTCommonFunction.hpp>
#endif

#ifndef DSTEDIT_H
   #include <uibase\DSTEdit.h>
#endif

#ifndef DSTCWORKSESSION_HPP
   #include <ifastcbo\DSTCWorkSession.hpp>
#endif

#ifndef SHAREHOLDERPROCESSINCLUDES_H
   #include <ifastbp\TransCancelProcessIncludes.h>
#endif

#include <ifastbp\mfcaninterprocparam.hpp>
#include <ifastgui\ifasthistoricalinfo.hpp>

#ifndef INCLUDED_ASSERT_H
#define INCLUDED_ASSERT_H
#include <assert.h>
#endif

#include <uibase\dstbutton.h>
#include <ifastcbo\DSTCUserSession.hpp>
#include <ifastdbrkr\dstcsecurity.hpp>
#include <ifastdbrkr\dstchost.hpp>

extern CLASS_IMPORT const I_CHAR* CMD_GUI_TRANS_CANCEL;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_DILUTION;

#include <bfproc\concretedialogcreator.hpp>
static ConcreteDialogCreator< TransCancellationDlg > dlgCreator( CMD_GUI_TRANS_CANCEL );

#ifdef _DEBUG
   #define new DEBUG_NEW
   #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

namespace
{
   const I_CHAR * const CLASSNAME = I_( "TransCancellationDlg" );

   const I_CHAR * const YES                      = I_( "Y" );
   const I_CHAR * const NO                       = I_( "N" );

   const I_CHAR *pTRANSNUM                       = I_( "TransNum" );   
   const I_CHAR *pFROMSCREEN                     = I_( "FromScr" ); 

   // Statuses for individual trade cancellation
   const I_CHAR *UNVERIFIED	                      = I_( "01" );
   const I_CHAR *VERIFIED	                      = I_( "02" );      
   const I_CHAR *VERIFIED_AND_REFUNDCALCREQ	      = I_( "15" );   

   //const I_CHAR *DELETE		                      = I_( "03" );
   // Statutes for Bulk Cancellation
   const I_CHAR * CANCEL_UNVERIFIED		          = I_( "04" );
   const I_CHAR * CANCEL_VERIFIED		          = I_( "05" );
   const I_CHAR * CANCELLATION_PROCEEDING		  = I_( "06" );
   const I_CHAR * CANCELLATION_DONE		          = I_( "07" );
   const I_CHAR * REBOOK_UNVERIFIED		          = I_( "08" );
   const I_CHAR * REBOOK_VERIFIED		          = I_( "09" );
   const I_CHAR * REBOOK_PROCEEDING		          = I_( "10" );
   const I_CHAR * REBOOK_PENDING_TRADE_UNVERIFIED = I_( "11" );
   const I_CHAR * REBOOK_PENDING_TRADE_VERIFIED	  = I_( "12" );
   const I_CHAR * REBOOK_DONE		              = I_( "13" );
   const I_CHAR * CANCEL_FAILED		              = I_( "14" );
   const I_CHAR * ALL		                      = I_( "All" );

   const I_CHAR *ACCOUNTABLE                      = I_( "Accountable" );
   const I_CHAR *BACKDATEDREASON                  = I_( "BackDatedReason" );   
   const I_CHAR *SPLITDILUTION                    = I_( "IsSplitDilution" );  
   
   const I_CHAR *RIGHT_TO_CANCEL				  = I_( "82" );
}

namespace CND
{  // Conditions used
   extern CLASS_IMPORT const long GUI_ERR_UNKNOWN_EXCEPTION;
}

namespace ifds
{	
	extern CLASS_IMPORT const BFTextFieldId RemarksLine;
	extern CLASS_IMPORT const BFTextFieldId ReadOnly;
	extern CLASS_IMPORT const BFTextFieldId SplitAcCode;
	extern CLASS_IMPORT const BFTextFieldId XtraActive;
	extern CLASS_IMPORT const BFTextFieldId MCHSRActive;
	extern CLASS_IMPORT const BFTextFieldId ESGSettle;
	extern CLASS_IMPORT const BFTextFieldId IsSplitDilution;
	extern CLASS_IMPORT const BFTextFieldId RecptIssued;

	extern CLASS_IMPORT const BFTextFieldId CancelContribRcpt;
	extern CLASS_IMPORT const BFTextFieldId ExcldRcptPrint;
	extern CLASS_IMPORT const BFTextFieldId RetRcptToSender;
	extern CLASS_IMPORT const BFTextFieldId VerCancTrd;
	extern CLASS_IMPORT const BFTextFieldId CancelGrant;
	extern CLASS_IMPORT const BFTextFieldId RefundOption;
	extern CLASS_IMPORT const BFTextFieldId RefundPayType;
	extern CLASS_IMPORT const BFTextFieldId RefundRVCD;
  extern CLASS_IMPORT const BFTextFieldId FundSERVClient;
}

namespace UAF
{
   extern CLASS_IMPORT I_CHAR * const VERIFY_CANCEL_INSTRUCTION;
   extern CLASS_IMPORT I_CHAR * const CTRBT_RCPT_CANCELLATION;
}

namespace TRADETYPE
{
   extern CLASS_IMPORT I_CHAR * const AUTO_WITHDRAW; 
} 


//*****************************************************************************
// Public methods
//*****************************************************************************
TransCancellationDlg::TransCancellationDlg( CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: BaseMainDlg( TransCancellationDlg::IDD, pParent, pGIC, pGIParent, rCommand, CLASSNAME )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   //{{AFX_DATA_INIT(TransCancellationDlg)
   //}}AFX_DATA_INIT
}

//*****************************************************************************
void TransCancellationDlg::DoDataExchange( CDataExchange* pDX )
{
   BaseMainDlg::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(TransCancellationDlg)
   //}}AFX_DATA_MAP
}

//*****************************************************************************
SEVERITY TransCancellationDlg::doInit()
{
   TRACE_METHOD( CLASSNAME, DOINIT );
   getParent()->getParameter( TRANSCANCEL::CASH_DIV_PAID_AFTER, cashDivPaidAfter_);

   getParameter( TRANSCANCEL::TRADE_DATE, _dstrTradeDate );
   getParameter( TRANSCANCEL::FUND,       _dstrFund );
   getParameter( TRANSCANCEL::CLASS,      _dstrClass );
   getParameter( I_("TRANSTYPE"),         _transType );
   getParameter( I_("SWPSETTLEESGELIG"),  _dstrSWPSettleESGElig );

   getParameter( I_( "TransTradeDate" ),  _dstrTransTradeDate );
   getParameter( I_( "TransSettleDate" ), _dstrTransSettleDate );
   getParameter (I_("GrantExists"),                _grantExists);
   
   return(NO_CONDITION);
}

//*****************************************************************************
BEGIN_MESSAGE_MAP(TransCancellationDlg, BaseMainDlg)
//{{AFX_MSG_MAP(TransCancellationDlg)
ON_BN_CLICKED( IDC_BTN_RESTORE, OnBtnRestore )
ON_BN_CLICKED( IDC_BTN_DILUTION, OnBtnDilution )
ON_BN_CLICKED( IDC_CHK_VERIFY, OnChkVerify )
ON_BN_CLICKED( IDC_CHK_REBOOK, OnChkRebook )
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//*****************************************************************************
// Message handlers
//*****************************************************************************
BOOL TransCancellationDlg::OnInitDialog() 
{
   TRACE_METHOD( CLASSNAME, ONINITDIALOG );

   BaseMainDlg::OnInitDialog();

   return(TRUE);
}

//*****************************************************************************
void TransCancellationDlg::OnPostInitDialog()
{
   TRACE_METHOD( CLASSNAME, ONPOSTINITDIALOG );

   //add the controls not affected by the adjustToProcessType method
   AddControl( CTRL_EDIT, IDC_EDT_TRANSNUM, IFASTBP_PROC::TRANS_CANCEL, 
               ifds::TransNum );
   AddControl( CTRL_COMBO, IDC_CMB_REVERSAL_CODE, IFASTBP_PROC::TRANS_CANCEL, 
               ifds::RvCode, CTRLFLAG_INITCOMBO_BY_SUB_LIST );
   AddControl( CTRL_COMBO, IDC_CMB_ACCOUNTABLE, IFASTBP_PROC::TRANS_CANCEL, 
               ifds::Accountable, CTRLFLAG_INITCOMBO_BY_SUB_LIST );
   AddControl( CTRL_COMBO, IDC_CMB_ONSTMT, IFASTBP_PROC::TRANS_CANCEL, 
               ifds::OnStmt, CTRLFLAG_INITCOMBO_BY_SUB_LIST );
   AddControl( CTRL_COMBO, IDC_CMB_CONFIRMREQ, IFASTBP_PROC::TRANS_CANCEL, 
               ifds::ConfirmRequired,CTRLFLAG_INITCOMBO_BY_SUB_LIST);
   AddControl( CTRL_COMBO, IDC_CMB_CANCEL_CHEQUE, IFASTBP_PROC::TRANS_CANCEL, 
               ifds::CancelCheque,CTRLFLAG_INITCOMBO_BY_SUB_LIST);
   //AddControl( CTRL_EDIT, IDC_EDT_CANCELATION_REMARKS, IFASTBP_PROC::TRANS_CANCEL, 
               //ifds::RemarksLine, CTRLFLAG_FIELDS_FROM_SUB_LIST );
   AddControl( CTRL_COMBO, IDC_CMB_CANCEL_GRANT, IFASTBP_PROC::TRANS_CANCEL, 
               ifds::CancelGrant, CTRLFLAG_INITCOMBO_BY_SUB_LIST);

	AddControl( CTRL_EDIT, IDC_EDT_CANCELATION_REMARKS, IFASTBP_PROC::TRANS_CANCEL, 
               ifds::RemarksLine, CTRLFLAG_FIELDS_FROM_SUB_LIST | CTRLFLAG_WORD_WRAP );
   dynamic_cast<DSTEdit*> (GetControl (IDC_EDT_CANCELATION_REMARKS))->SetMaxCharNum (50);

   AddControl( CTRL_EDIT, IDC_EDT_STATUS, IFASTBP_PROC::TRANS_CANCEL, 
               ifds::TranStatus );

   AddControl( CTRL_COMBO, IDC_CMB_BATCH_TRACE, IFASTBP_PROC::TRANS_CANCEL, 
               ifds::Batch, CTRLFLAG_DEFAULT | CTRLFLAG_INITCOMBO_BY_SUB_LIST  | CTRLFLAG_COMBO_EDIT);
   AddControl( CTRL_COMBO, IDC_CMB_REFUND_PAYTYPE, IFASTBP_PROC::TRANS_CANCEL, 
               ifds::RefundPayType, CTRLFLAG_INITCOMBO_BY_SUB_LIST);
   AddControl( CTRL_COMBO, IDC_CMB_REFUND_OPTION, IFASTBP_PROC::TRANS_CANCEL, 
               ifds::RefundOption, CTRLFLAG_DEFAULT | CTRLFLAG_INITCOMBO_BY_SUB_LIST);


   DSTComboBox *pCmbBatchName = dynamic_cast <DSTComboBox*> (GetControl (IDC_CMB_BATCH_TRACE));

   if (pCmbBatchName)
   {
      pCmbBatchName->LimitText (15);
   }

	AddControl( CTRL_COMBO, IDC_CMB_MCH_FILE, IFASTBP_PROC::TRANS_CANCEL, 
               ifds::MCHFileIndicator, CTRLFLAG_INITCOMBO_BY_SUB_LIST);
	AddControl( CTRL_COMBO, IDC_CMB_SEC_REC_FILE, IFASTBP_PROC::TRANS_CANCEL, 
               ifds::SecRecFileIndicator, CTRLFLAG_INITCOMBO_BY_SUB_LIST);
	AddControl( CTRL_COMBO, IDC_CMB_RBK_MCH_FILE, IFASTBP_PROC::TRANS_CANCEL, 
               ifds::RbkMCHFileIndicator, CTRLFLAG_INITCOMBO_BY_SUB_LIST);
	AddControl( CTRL_COMBO, IDC_CMB_RBK_SEC_REC_FILE, IFASTBP_PROC::TRANS_CANCEL, 
               ifds::RbkSecRecFileIndicator, CTRLFLAG_INITCOMBO_BY_SUB_LIST);

	// Suppress On Report enhancement for PET1334 FN1
	AddControl( CTRL_COMBO, IDC_CMB_ESG_SETTLE, IFASTBP_PROC::TRANS_CANCEL, 
               ifds::ESGSettle, CTRLFLAG_INITCOMBO_BY_SUB_LIST);

//   AddControl( CTRL_STATIC, IDC_TXT_TRACE, IFASTBP_PROC::TRANS_CANCEL, 
//               ifds::Trace );
   

   AddControl( CTRL_COMBO, IDC_CMB_CANCEL_CONTRIB_RECPT, IFASTBP_PROC::TRANS_CANCEL, 
               ifds::CancelContribRcpt, CTRLFLAG_INITCOMBO_BY_SUB_LIST);
   AddControl( CTRL_COMBO, IDC_CMB_EXCLUDE_RECPT_PRINT, IFASTBP_PROC::TRANS_CANCEL, 
               ifds::ExcldRcptPrint, CTRLFLAG_INITCOMBO_BY_SUB_LIST);
   AddControl( CTRL_COMBO, IDC_CMB_RET_RECPT_TO_SENDER, IFASTBP_PROC::TRANS_CANCEL, 
               ifds::RetRcptToSender, CTRLFLAG_INITCOMBO_BY_SUB_LIST);


   AddControl( CTRL_DATE,IDC_DTP_ID_EVENTRECEIPT_DATE , IFASTBP_PROC::TRANS_CANCEL, 
               ifds::EventReceiptDate );
   AddControl( CTRL_EDIT,IDC_EDT_EVENTRECEIPT_TIME , IFASTBP_PROC::TRANS_CANCEL, 
               ifds::EventReceiptTime );
   DSTEdit *edit = dynamic_cast<DSTEdit *>( GetControl (IDC_EDT_EVENTRECEIPT_TIME));
   edit->SetAllowedChars(I_("0123456789:"));
   edit->SetMaxCharNum (8);//HH:mm:ss
           
   DString dstrTransStat, dstrReadOnly, dstrModPerm;
   getParent()->getField (this, IFASTBP_PROC::TRANS_CANCEL, ifds::TranStatus,    dstrTransStat, false ); 
   getParent()->getField (this, IFASTBP_PROC::TRANS_CANCEL, ifds::ReadOnly,      dstrReadOnly, false ); 
   getParent()->getField (this, IFASTBP_PROC::TRANS_CANCEL, ifds::ModPermission, dstrModPerm, false );         
	
	bool bEnableESGSettle = false;
	if( DSTCommonFunctions::getMarket() == MARKET_IDS::CANADA && 
      _transType == TRADETYPE::AUTO_WITHDRAW && _dstrSWPSettleESGElig == I_("Y") ) // Auto withdraw
   {
		bEnableESGSettle = true;
	}
	
	EnableControl( IDC_CMB_ESG_SETTLE, bEnableESGSettle );
	ConnectControlToData( IDC_CMB_ESG_SETTLE, bEnableESGSettle );
   EnableControl( IDC_CMB_CANCEL_GRANT, _grantExists.upperCase() == I_("Y"));

   doRefresh (this, NULL_STRING);
    
   // Flags for the Rebook box
   bool bShowRebook   = false;
   bool bEnableRebook = false;
   // Flags for the Verify box
   int iCheckVerify = 0;
   bool bEnableVerify = false;

   DString  dstrTransNum,dstrRebook;    
   getParent()->getField( this, IFASTBP_PROC::TRANS_CANCEL, ifds::TransNum, dstrTransNum, false );    
   getParent()->getField( this, IFASTBP_PROC::TRANS_CANCEL, ifds::Rebook,   dstrRebook,   false );  
   dstrRebook.stripAll().upperCase();
   // Bulk Cancellation - that will always have TransNum = 0
   if ( 0 == dstrTransNum.asInteger() )
   {	    
	   CString cstrBulkCan, cstrReset;
	   cstrBulkCan.LoadString(TXT_BULK_CANCELLATION);
	   cstrReset.LoadString(TXT_RESET); 
	   
	    GetDlgItem( IDC_STATIC_GEN_1 )->SetWindowText( cstrBulkCan ); 
        GetDlgItem( IDC_BTN_RESTORE )->SetWindowText( cstrReset ); 
		GetDlgItem( IDC_BTN_RESTORE )->EnableWindow( dstrModPerm != NULL_STRING );

		DString dstrXtraActive;
        getParent()->getField( this, IFASTBP_PROC::TRANS_CANCEL, ifds::XtraActive, dstrXtraActive, false ); 
		dstrXtraActive.stripAll().upperCase();

	    /***************** Bulk Rebook Check box*******************************************************/
	    // Show the Bulk Rebook only for Bulk Cancellation
		bShowRebook = true;

	    int iCheckRebook = 0;
	    if ( I_( "Y" ) == dstrRebook )
			iCheckRebook = 1;
		((CButton *) GetDlgItem( IDC_CHK_REBOOK ))->SetCheck( iCheckRebook );				
          
        // Bulk Rebook should be enabled, and allow user to change it 
		// ------> Make sure Restore will reset these too!
		if ( I_( "Y" ) != dstrXtraActive && 
			 ( CANCEL_UNVERIFIED == dstrTransStat ||
			   CANCEL_VERIFIED   == dstrTransStat ||
               CANCELLATION_DONE == dstrTransStat ) )
			bEnableRebook = true;						

        /***************** Verify Check and Edit boxes**************************************************/        
		// Checked/Uncheked
		if ( CANCEL_VERIFIED               == dstrTransStat ||
			 REBOOK_VERIFIED               == dstrTransStat ||
			 REBOOK_PENDING_TRADE_VERIFIED == dstrTransStat )
			 iCheckVerify = 1;        

		// Enabled/Disabled
		if ( I_( "Y" ) != dstrXtraActive &&
			 ( CANCEL_UNVERIFIED == dstrTransStat ||
			   REBOOK_UNVERIFIED == dstrTransStat || 
			   CANCEL_FAILED     == dstrTransStat ) )
			bEnableVerify = true;	        

		// Dilution not allowed for Bulk Cancellation
		GetDlgItem (IDC_BTN_DILUTION)->EnableWindow( false );  				
   }
   else
   {		
	   GetDlgItem( IDC_BTN_RESTORE )->EnableWindow( dstrReadOnly != YES && dstrModPerm != NULL_STRING );

		if ( dstrTransStat == VERIFIED )
			iCheckVerify = 1;
		else
			bEnableVerify = true;		

		// For Individual Cancellation, Dillution allowed based on GenericControl.SplitAcCode 
		DString dstrDilution (YES), dstrFundSERVClient;
		DSTCWorkSession *dstWorkSession = dynamic_cast<DSTCWorkSession *>(getParent()->getBFWorkSession());
		dstWorkSession->getOption (ifds::SplitAcCode, dstrDilution, getParent()->getDataGroupId(), false);
    dstWorkSession->getOption (ifds::FundSERVClient, dstrFundSERVClient, getParent()->getDataGroupId(), false);

    boolean isDilution = (dstrDilution == YES || (dstrDilution == NO && dstrFundSERVClient == YES)); 

		GetDlgItem (IDC_BTN_DILUTION)->EnableWindow(isDilution);  				
   }

   // The Rebook box
   if ( CANCEL_UNVERIFIED != dstrTransStat )
	{
		bool booEnableRebookBasedUNVERIFIED = bEnableRebook && hasReadPermission( UAF::VERIFY_CANCEL_INSTRUCTION ) && dstrModPerm == I_( "2" );
		GetDlgItem( IDC_CHK_REBOOK )->EnableWindow( booEnableRebookBasedUNVERIFIED ); 
		//GetDlgItem( IDC_CMB_RBK_MCH_FILE )->EnableWindow( booEnableRebookBasedUNVERIFIED ); 
		//GetDlgItem( IDC_CMB_RBK_SEC_REC_FILE )->EnableWindow( booEnableRebookBasedUNVERIFIED ); 
	}
		
	else
   {
        DString dstrCurrentUserName, dstrUserName;
        getParent()->getField( this, IFASTBP_PROC::TRANS_CANCEL, ifds::Username, dstrUserName, false ); 
 
		DSTCWorkSession *pDSTCWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
        dstrCurrentUserName = dynamic_cast<const DSTCSecurity *>( pDSTCWorkSession->getSecurity(DSTCHost::getPrimaryHost()))->getUserId();        
         
	    if ( !dstrUserName.empty() &&
			 ( dstrCurrentUserName.stripAll().upperCase() != dstrUserName.stripAll().upperCase() ) )
		 {
			bool booEnableRebookBasedOthers = bEnableRebook && hasReadPermission( UAF::VERIFY_CANCEL_INSTRUCTION ) && dstrModPerm == I_("2");
			GetDlgItem( IDC_CHK_REBOOK )->EnableWindow( booEnableRebookBasedOthers );  // Not when 1, i.e. differrent user, Cancel Unverified  
			//GetDlgItem( IDC_CMB_RBK_MCH_FILE )->EnableWindow( booEnableRebookBasedOthers ); 
			//GetDlgItem( IDC_CMB_RBK_SEC_REC_FILE )->EnableWindow( booEnableRebookBasedOthers ); 		   
			//GetDlgItem( IDC_CHK_REBOOK )->EnableWindow( bEnableRebook && dstrModPerm == I_("2") );  // Not when 1, i.e. differrent user, Cancel Unverified  
		 }
		 else
		 {
			GetDlgItem( IDC_CHK_REBOOK )->EnableWindow( bEnableRebook );  
			GetDlgItem( IDC_CMB_RBK_MCH_FILE )->EnableWindow( bEnableRebook ); 
			GetDlgItem( IDC_CMB_RBK_SEC_REC_FILE )->EnableWindow( bEnableRebook ); 
		 }
   }

	DString dstrMCHSRActive;
	
	DSTCWorkSession *pDSTCWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());

	pDSTCWorkSession->getOption ( ifds::MCHSRActive, dstrMCHSRActive, getParent()->getDataGroupId(), false);
	dstrMCHSRActive.stripAll().upperCase();

	GetDlgItem (IDC_CHK_REBOOK)->ShowWindow( bShowRebook ); 

  	if (dstrMCHSRActive != YES )
	{						
		GetDlgItem (IDC_BULK_REBOOK)->ShowWindow( false );
		GetDlgItem (IDC_CMB_RBK_MCH_FILE)->ShowWindow( false );  
		GetDlgItem (IDC_CMB_RBK_SEC_REC_FILE)->ShowWindow( false );  
		GetDlgItem (IDC_TXT_RBK_MCH_FILE)->ShowWindow( false );
		GetDlgItem (IDC_TXT_RBK_SEC_REC_FILE)->ShowWindow( false );  
	 
		GetDlgItem (IDC_CMB_MCH_FILE)->ShowWindow( false );  
		GetDlgItem (IDC_CMB_SEC_REC_FILE)->ShowWindow( false );  
		GetDlgItem (IDC_TXT_SEC_REC_FILE)->ShowWindow( false );
		GetDlgItem (IDC_TXT_MCH_FILE)->ShowWindow( false );  
		GetDlgItem (IDC_REVERSAL)->ShowWindow( false ); 
	}
	else
	{
		GetDlgItem (IDC_BULK_REBOOK)->ShowWindow( bShowRebook ); 
		GetDlgItem (IDC_CMB_RBK_MCH_FILE)->ShowWindow( bShowRebook );  
		GetDlgItem (IDC_CMB_RBK_SEC_REC_FILE)->ShowWindow( bShowRebook );  
		GetDlgItem (IDC_TXT_RBK_MCH_FILE)->ShowWindow( bShowRebook );
		GetDlgItem (IDC_TXT_RBK_SEC_REC_FILE)->ShowWindow( bShowRebook );  
	}

	// The Verify box
   ((CButton* )GetDlgItem(IDC_CHK_VERIFY))->SetCheck( iCheckVerify );    
   if ( REBOOK_UNVERIFIED != dstrTransStat )
   {
	   if ( CANCEL_FAILED == dstrTransStat )         // Only the Verify check box should be enabled, always
		   GetDlgItem( IDC_CHK_VERIFY )->EnableWindow( bEnableVerify && hasReadPermission( UAF::VERIFY_CANCEL_INSTRUCTION ) && dstrModPerm == I_("2") );   
	   else
		   GetDlgItem( IDC_CHK_VERIFY )->EnableWindow( bEnableVerify && dstrReadOnly != YES && hasReadPermission( UAF::VERIFY_CANCEL_INSTRUCTION ) && dstrModPerm == I_("2") );   
   }
   else
		GetDlgItem( IDC_CHK_VERIFY )->EnableWindow( bEnableVerify && hasReadPermission( UAF::VERIFY_CANCEL_INSTRUCTION ) && dstrModPerm == I_("2") );
   LoadControl (IDC_EDT_STATUS);

   DString dstrVerCancTrd, dstrRecptIssued;
   DSTCWorkSession *dstWorkSession = dynamic_cast<DSTCWorkSession *>(getParent()->getBFWorkSession());
   dstWorkSession->getOption (ifds::VerCancTrd, dstrVerCancTrd, getParent()->getDataGroupId(), false);
   getParent()->getField(this, IFASTBP_PROC::TRANS_CANCEL, ifds::RecptIssued, dstrRecptIssued, false );

   bool bAllowCtrbtRcptCan = hasReadPermission   ( UAF::CTRBT_RCPT_CANCELLATION ) &&  
                                          hasUpdatePermission ( UAF::CTRBT_RCPT_CANCELLATION ) && 
                                          hasCreatePermission ( UAF::CTRBT_RCPT_CANCELLATION );
   DString dstrMarket = DSTCommonFunctions::getMarket();
   GetDlgItem ( IDC_DTP_ID_EVENTRECEIPT_DATE)->ShowWindow( dstrMarket != MARKET_IDS::CANADA ); 
   GetDlgItem ( IDC_EDT_EVENTRECEIPT_TIME   )->ShowWindow( dstrMarket != MARKET_IDS::CANADA );
   GetDlgItem ( IDC_STATIC_EVENTRECEIPT_DATE)->ShowWindow( dstrMarket != MARKET_IDS::CANADA );
   GetDlgItem ( IDC_STATIC_EVENTRECEIPT_TIME)->ShowWindow( dstrMarket != MARKET_IDS::CANADA );

   if (dstrRecptIssued == YES && dstrVerCancTrd != NULL_STRING && NO == dstrVerCancTrd)
   {
         EnableCancellationOption(bAllowCtrbtRcptCan);
   }     
   else
   {
      EnableCancellationOption(false); 
   }
   LoadControls();
}


//*******************************************************************************
void TransCancellationDlg::PostOk( bool /*bOkStatus*/ )
{
}

//******************************************************************************
void TransCancellationDlg::OnBtnRestore() 
{
	CString cstrDoRestore;
	cstrDoRestore.LoadString(TXT_DO_YOU_WANT_RESTORE_TRANSACTION);
	DString dstrWantCancel = DString(cstrDoRestore);

	DString  dstrTransNum;    
	getParent()->getField (this, IFASTBP_PROC::TRANS_CANCEL, ifds::TransNum, dstrTransNum, false ); 
	// Bulk Cancellation - that will always have TransNum = 0
	if ( 0 == dstrTransNum.asInteger() )
	{
		getParent()->send(this, I_("RefreshBulkRebook") );

		ConnectControlsToData();   
		LoadControls();
		/***************** Bulk Rebook Check box*******************************************************/
        int iCheckRebook = 0;  
		DString dstrRebook;
        getParent()->getField (this, IFASTBP_PROC::TRANS_CANCEL, ifds::Rebook, dstrRebook, false );  
		dstrRebook.stripAll().upperCase();
		if ( I_( "Y" ) == dstrRebook )
			iCheckRebook = 1;

		((CButton *) GetDlgItem( IDC_CHK_REBOOK ))->SetCheck( iCheckRebook );	

		/***************** Verify Check and Edit boxes**************************************************/        
		int iCheckVerify = 0;
		bool bEnableVerify = false;
		DString dstrTransStat;
		getParent()->getField (this, IFASTBP_PROC::TRANS_CANCEL, ifds::TranStatus, dstrTransStat, false );  
        // Checked/Uncheked
		if ( CANCEL_VERIFIED == dstrTransStat ||
			 REBOOK_VERIFIED == dstrTransStat )
				iCheckVerify = 1;        

		// Enabled/Disabled
		if ( CANCEL_UNVERIFIED == dstrTransStat ||
			 CANCEL_FAILED     == dstrTransStat ||
			 REBOOK_UNVERIFIED == dstrTransStat )
				bEnableVerify = true;
          
      ((CButton* )GetDlgItem(IDC_CHK_VERIFY))->SetCheck( iCheckVerify );   
		DString dstrModPerm, dstrReadOnly;
		getParent()->getField (this, IFASTBP_PROC::TRANS_CANCEL, ifds::ModPermission, dstrModPerm, false ); 		
		GetDlgItem( IDC_CHK_VERIFY )->EnableWindow( bEnableVerify && hasReadPermission( UAF::VERIFY_CANCEL_INSTRUCTION ) && dstrModPerm == I_("2") );		

      EnableCancellationOption(false);
		//LoadControl (IDC_EDT_STATUS); 
	}		
	else
	{
		if (AfxMessageBox(dstrWantCancel.c_str(), MB_YESNO) == IDYES)
		{
			GetDlgItem (IDC_CHK_VERIFY)->EnableWindow (false);
			getParent()->setField (this, IFASTBP_PROC::TRANS_CANCEL,ifds::TranStatus, I_("03") );			
			
			DString dstrVerCancTrd, dstrRecptIssued, dstrModPerm;
         DSTCWorkSession *dstWorkSession = dynamic_cast<DSTCWorkSession *>(getParent()->getBFWorkSession());
         dstWorkSession->getOption (ifds::VerCancTrd, dstrVerCancTrd, getParent()->getDataGroupId(), false);
         getParent()->getField(this, IFASTBP_PROC::TRANS_CANCEL, ifds::RecptIssued, dstrRecptIssued, false );
		   getParent()->getField (this, IFASTBP_PROC::TRANS_CANCEL, ifds::ModPermission, dstrModPerm, false );
         
         bool bAllowCtrbtRcptCan = hasReadPermission   ( UAF::CTRBT_RCPT_CANCELLATION ) &&  
                                                hasUpdatePermission ( UAF::CTRBT_RCPT_CANCELLATION ) && 
                                                hasCreatePermission ( UAF::CTRBT_RCPT_CANCELLATION );
         
         if (dstrRecptIssued == YES && dstrVerCancTrd != NULL_STRING && NO == dstrVerCancTrd)
         {
            EnableCancellationOption(bAllowCtrbtRcptCan);
         }
         else
         {
            EnableCancellationOption(false);
         }     
		}
		LoadControl (IDC_EDT_STATUS);
   }
}

//******************************************************************************
void TransCancellationDlg::OnBtnDilution() 
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OnBtnDilution" ) ); 

   CWaitCursor wait;   
   SetMessageStatusBar (TXT_LOAD_DILUTION);

   try   
   {
      DString dstrTransNum;      
      getParent()->getField( this, IFASTBP_PROC::TRANS_CANCEL, ifds::TransNum, dstrTransNum, true );
	  dstrTransNum.strip().upperCase();

      	 
     DString dstrTradeDate, dstrFund, dstrClass;
	  if ( 0 == dstrTransNum.asInteger() )
	  {
		setParameter( TRANSCANCEL::BULK_CANCEL, I_( "Y" ) );
		
	    getParent()->getField( this, IFASTBP_PROC::TRANS_CANCEL, ifds::TradeDate, dstrTradeDate, true );
	    getParent()->getField( this, IFASTBP_PROC::TRANS_CANCEL, ifds::Fund,      dstrFund,      true );
	    getParent()->getField( this, IFASTBP_PROC::TRANS_CANCEL, ifds::Class,     dstrClass,     true );
	  }
	  else
	  {
		  setParameter( pTRANSNUM,                dstrTransNum );
		  dstrTradeDate = _dstrTradeDate;
		  dstrFund = _dstrFund;
		  dstrClass = _dstrClass;

	  }
	
	  setParameter( TRANSCANCEL::TRADE_DATE,  dstrTradeDate );
	  setParameter( TRANSCANCEL::FUND,        dstrFund );
	  setParameter( TRANSCANCEL::CLASS,       dstrClass );	    
		
	  setParameter (pFROMSCREEN, I_("TransCancel") );
      setParameter (TRANSCANCEL::CASH_DIV_PAID_AFTER, cashDivPaidAfter_);

	  setParameter( I_( "TransTradeDate" ),  _dstrTransTradeDate );
      setParameter( I_( "TransSettleDate" ), _dstrTransSettleDate );
	  setParameter( I_("TRANSTYPE"),         _transType );
      
      switch (invokeCommand (getParent(), CMD_BPROC_DILUTION, PROC_SUPPORT, true, NULL))
      {
         case CMD_OK:         
         case CMD_MODELESS_INPROCESS:
			 {
				DString dstrAccountable;

                getParameter (ACCOUNTABLE, dstrAccountable);
				getParent()->setField ( this, 
                                        IFASTBP_PROC::TRANS_CANCEL, 
                                        ifds::Accountable, 
                                        dstrAccountable);
				LoadControl (IDC_CMB_ACCOUNTABLE);
				
                DString dstrRvCode;
                getParameter (BACKDATEDREASON, dstrRvCode);
                if (!dstrRvCode.empty())
				{
					getParent()->setField ( this, 
                                            IFASTBP_PROC::TRANS_CANCEL, 
                                            ifds::RvCode, 
                                            dstrRvCode);
					LoadControl (IDC_CMB_REVERSAL_CODE);
				}	

                DString dstrSplitDilution;
				getParameter (SPLITDILUTION, dstrSplitDilution);
                if (!dstrSplitDilution.empty())
				{
					getParent()->setField ( this, 
                                            IFASTBP_PROC::TRANS_CANCEL, 
                                            ifds::IsSplitDilution, 
                                            dstrSplitDilution);
				}		
            break;
			 }
		 case CMD_CANCEL:
         break;
         default:
            // Display error
            ConditionMessageBox( FRAMEBELOW(), GETHIGHESTSEVERITY() );
            break;
      }	
   }
   catch( ConditionException &ce )
   {
      ConditionMessageBox( ce );
   }
   catch( ... )
   {
      DISPLAYCONDITIONFROMFILE( CND::GUI_ERR_UNKNOWN_EXCEPTION );
   }    
   SetMessageStatusBar( NULL_STRING );
}

//******************************************************************************
bool TransCancellationDlg::doRefresh( GenericInterface * rpGICaller,
                                      const I_CHAR* szOriginalCommand)
{ 
   TRACE_METHOD (CLASSNAME, DOREFRESH);
 
   ConnectControlsToData();   
   LoadControls();

   setDlgCaption();

   return true;
}

//*****************************************************************************
void TransCancellationDlg::OnChkVerify () 
{
   DString dstrTransNum;
   getParent()->getField (this, IFASTBP_PROC::TRANS_CANCEL, ifds::TransNum, dstrTransNum, false); 

  DString dstrStatus;
   if ( 0 != dstrTransNum.stripAll().asInteger() )
   {
		DString dstrRVCDSet,dstrRvcd;
		DSTCWorkSession *dstWorkSession = dynamic_cast<DSTCWorkSession *>(getParent()->getBFWorkSession());
		dstWorkSession->getOption( ifds::RefundRVCD, dstrRVCDSet, BF::HOST, false );	     
		getParent()->getField (this, IFASTBP_PROC::TRANS_CANCEL, ifds::RvCode, dstrRvcd, false );
		if( DSTCommonFunctions::codeInList(dstrRvcd,dstrRVCDSet) )
		{
			dstrStatus = ( ((CButton *) GetDlgItem( IDC_CHK_VERIFY ))->GetCheck() == 1 ) ? VERIFIED_AND_REFUNDCALCREQ : UNVERIFIED;
		}
		else
		{
			dstrStatus = ( ((CButton *) GetDlgItem( IDC_CHK_VERIFY ))->GetCheck() == 1 ) ? VERIFIED : UNVERIFIED;
		}
		
		getParent()->setField (this, IFASTBP_PROC::TRANS_CANCEL, ifds::TranStatus, dstrStatus);

       if ( ((CButton *) GetDlgItem( IDC_CHK_VERIFY ))->GetCheck() == 1 )
       {
            DString dstrModPerm, dstrRceptIssued;
            getParent()->getField(this, IFASTBP_PROC::TRANS_CANCEL, ifds::ModPermission,dstrModPerm);
            getParent()->getField(this, IFASTBP_PROC::TRANS_CANCEL, ifds::RecptIssued,dstrRceptIssued);
            bool bAllowCtrbtRcptCan = hasReadPermission   ( UAF::CTRBT_RCPT_CANCELLATION ) &&  
                                          hasUpdatePermission ( UAF::CTRBT_RCPT_CANCELLATION ) && 
                                          hasCreatePermission ( UAF::CTRBT_RCPT_CANCELLATION );
                                                      
            EnableCancellationOption(
                  dstrRceptIssued == YES && 
                  dstrModPerm == I_("2") &&
                  bAllowCtrbtRcptCan);
       }
       else
       {
            EnableCancellationOption(false);
       }

       LoadControl (IDC_EDT_STATUS);
   }
   else		// Bulk Cancellation
   {	   
	   getParent()->getField (this, IFASTBP_PROC::TRANS_CANCEL, ifds::TranStatus, dstrStatus, false );

	   int iCheckVerify = ((CButton *) GetDlgItem( IDC_CHK_VERIFY ))->GetCheck();
	   if ( 1 == iCheckVerify &&
		    ( CANCEL_UNVERIFIED == dstrStatus ||
			  CANCEL_FAILED     == dstrStatus ||
			  REBOOK_UNVERIFIED == dstrStatus ) )
	   {		    
			if ( CANCEL_UNVERIFIED == dstrStatus ||
				 CANCEL_FAILED     == dstrStatus )
				getParent()->setField (this, IFASTBP_PROC::TRANS_CANCEL, ifds::TranStatus, CANCEL_VERIFIED, false); 
			else if ( REBOOK_UNVERIFIED == dstrStatus )
				getParent()->setField (this, IFASTBP_PROC::TRANS_CANCEL, ifds::TranStatus, REBOOK_VERIFIED, false); 			
	   }
	   else if ( 0 == iCheckVerify &&
		         ( CANCEL_VERIFIED               == dstrStatus ||
			       REBOOK_VERIFIED               == dstrStatus ) )
	   {
			if ( CANCEL_VERIFIED == dstrStatus )				
				getParent()->send(this, I_("RefreshBulkRebook") );
			else if ( REBOOK_VERIFIED == dstrStatus )
				getParent()->setField (this, IFASTBP_PROC::TRANS_CANCEL, ifds::TranStatus, REBOOK_UNVERIFIED, false); 			
	   }

	   LoadControl (IDC_EDT_STATUS); 
   }
}

//*****************************************************************************
void TransCancellationDlg::OnChkRebook()
{

	DString dstrRebook = ( ((CButton *) GetDlgItem( IDC_CHK_REBOOK ))->GetCheck() == 1 ) ? I_( "Y" ) : I_( "N" ); 
   getParent()->setField( this, IFASTBP_PROC::TRANS_CANCEL, ifds::Rebook, dstrRebook );
	LoadControl(IDC_CMB_RBK_MCH_FILE);
	LoadControl(IDC_CMB_RBK_SEC_REC_FILE);

}

//*****************************************************************************
void TransCancellationDlg::setDlgCaption()
{
	DString  dstrCaption, dstrTransNum;     
	getParent()->getField (this, IFASTBP_PROC::TRANS_CANCEL, ifds::TransNum, dstrTransNum, false); 

	if ( 0 != dstrTransNum.stripAll().asInteger() )
	{
		// For a single transaction cancellation
		CString cstrTradeCancelTrans;
		cstrTradeCancelTrans.LoadString(TXT_TRADE_CANCELLATION_FOR_TRANSACTION);
		dstrCaption = DString(cstrTradeCancelTrans) + dstrTransNum;
	}
	else
	{
		DString dstrTrade, dstrFund, dstrClass;
		getParent()->getField (this, IFASTBP_PROC::TRANS_CANCEL, ifds::TradeDate, dstrTrade, true ); 
		getParent()->getField (this, IFASTBP_PROC::TRANS_CANCEL, ifds::Fund,      dstrFund,  true ); 
		getParent()->getField (this, IFASTBP_PROC::TRANS_CANCEL, ifds::Class,     dstrClass, true ); 

		// For bulk Cancellation
		CString cstrBulkCancel,cstrFund,cstrClass;
		cstrBulkCancel.LoadString(TXT_BULK_CANCELLATION_TRADE_DATE);
		cstrFund.LoadString(TXT_FUND_TXT);
		cstrClass.LoadString(TXT_CLASS);
		dstrCaption = DString(cstrBulkCancel) + dstrTrade
					+ DString(cstrFund)   + dstrFund
					+ DString(cstrClass)  + dstrClass;
	}

   SetWindowText( dstrCaption.c_str() );
}

void TransCancellationDlg::EnableCancellationOption(bool _bEnable)
{
   //Show if it's enabled, hide it otherwise.
   int iShow = _bEnable?SW_SHOW:SW_HIDE;
   if(_bEnable)
   {
      getParent()->setField(this,
            IFASTBP_PROC::TRANS_CANCEL,
            ifds::CancelContribRcpt,
            YES);
   }
   GetDlgItem(IDC_STC_CANCELLATION_OPTIONS)->EnableWindow(_bEnable);
   GetDlgItem(IDC_CMB_CANCEL_CONTRIB_RECPT)->EnableWindow(_bEnable);
   GetDlgItem(IDC_CMB_EXCLUDE_RECPT_PRINT)->EnableWindow(_bEnable);
   GetDlgItem(IDC_CMB_RET_RECPT_TO_SENDER)->EnableWindow(_bEnable);
   GetDlgItem(IDC_STC_CANCEL_CONTRIB_RECPT)->EnableWindow(_bEnable);
   GetDlgItem(IDC_STC_EXCLUDE_RECPT_PRINT)->EnableWindow(_bEnable);
   GetDlgItem(IDC_STC_RET_RECPT_TO_SENDER)->EnableWindow(_bEnable);

   GetDlgItem(IDC_STC_CANCELLATION_OPTIONS)->ShowWindow(iShow);
   GetDlgItem(IDC_CMB_CANCEL_CONTRIB_RECPT)->ShowWindow(iShow);
   GetDlgItem(IDC_CMB_EXCLUDE_RECPT_PRINT)->ShowWindow(iShow);
   GetDlgItem(IDC_CMB_RET_RECPT_TO_SENDER)->ShowWindow(iShow);
   GetDlgItem(IDC_STC_CANCEL_CONTRIB_RECPT)->ShowWindow(iShow);
   GetDlgItem(IDC_STC_EXCLUDE_RECPT_PRINT)->ShowWindow(iShow);
   GetDlgItem(IDC_STC_RET_RECPT_TO_SENDER)->ShowWindow(iShow);
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/TransCancellationDlg.cpp-arc  $
// 
//    Rev 1.51   May 07 2012 14:18:02   wp040027
// PETP0187485-CPF-Trade Cancellation
// 
//    Rev 1.50   Apr 13 2012 20:00:42   wp040132
// Replaced IDC_STATIC with IDC_STATIC_GEN_1 for Bulk cancellation Label
// 
//    Rev 1.49   Apr 11 2012 12:00:52   wp040132
// IDC_STATIC is not used in the Bulk Cancellation Screen. Hence, commented the code.
// 
//    Rev 1.48   Nov 24 2011 15:53:26   wp040143
// P0186484/FN06 - DESKTOP - iFast Desktop (French Customizations)
// 
//    Rev 1.47   Nov 19 2011 01:48:02   wp040168
// P0186484/FN06 - DESKTOP - iFast Desktop (French Customizations)
// 
//    Rev 1.46   Apr 15 2010 00:01:56   popescu
// PET165541_FN01_QESI - RESP Gap_Dsk_Trading
// 
//    Rev 1.45   May 14 2009 13:08:26   jankovii
// PET 159770 FN05 Auto Batching.
// 
//    Rev 1.44   Jan 16 2008 17:59:04   wongsakw
// Incident 1142459 - Invalid Cancel Receipt
// 
//    Rev 1.43   Dec 11 2007 15:59:18   wongsakw
// PET2360 FN60 Automatically Cancel Contribution Reciept
// 
//    Rev 1.42   Nov 02 2007 11:29:50   jankovii
// IN #1057653 - trade cancellation using split dilution.
// 
//    Rev 1.41   Aug 30 2007 15:22:18   jankovii
// PET 2360 FN11 - Dilution.
// 
//    Rev 1.40   Mar 10 2006 14:44:22   porteanm
// Incident 563764 - TradeDate/SettleDate validation support for a cancelled transaction.
// 
//    Rev 1.39   Mar 06 2006 10:30:40   popescu
// PET1334 - FN01 -- ESG Settlement enhancement - used TRADETYPE::AW
// 
//    Rev 1.38   Mar 02 2006 17:35:50   ZHANGCEL
// PET1334 - FN01 -- ESG Settlement enhancement
// 
//    Rev 1.35   Jan 23 2006 15:14:00   porteanm
// PET1295_FN01: Trade Suppress Indicator for MCH and SR Files -- Changed to hide the four new fields (MCH & SR Files) when gc.TradeDefault2 is inactive
// 
//    Rev 1.34   Jan 23 2006 09:23:46   zhengcon
// PET1295_FN01: Trade Suppress Indicator for MCH and SR Files -- Changed to hide the four new fields (MCH & SR Files) when gc.TradeDefault2 is inactive
// 
//    Rev 1.33   Jan 12 2006 16:15:02   zhengcon
// PET1295_FN01: Trade Suppress Indicator for MCH and SR Files -- Trade Cancellation: Individual and rebook
// 
//    Rev 1.32   Dec 19 2005 11:19:48   porteanm
// Incident 492760 - 2. When Cancel Failed, only the Verify check box shold be enabed, and only for user II who has permission and batch-access.
// 
//    Rev 1.31   Nov 29 2005 12:32:54   porteanm
// PET1286 FN01 - Bulk Cancellation - format date in the title.
// 
//    Rev 1.30   Nov 27 2005 14:17:16   porteanm
// PET1286 FN01 - Bulk Cancellation - rebook.
// 
//    Rev 1.29   Nov 27 2005 10:05:38   porteanm
// PET1286 FN01 - Bulk Cancellation - restore.
// 
//    Rev 1.28   Nov 26 2005 18:16:10   porteanm
// PET1286 FN01 - Bulk Cancellation.
// 
//    Rev 1.27   Nov 24 2005 16:36:20   porteanm
// PET1286 FN01 - Bulk Cancellation.
// 
//    Rev 1.26   Nov 24 2005 16:26:18   porteanm
// PET1286 FN01 - Bulk Cancellation - don't allow changes anymore to REBOOK_PENDING_TRADE_UNVERIFIED since it will be dealt with in th eprocessing - as per email.
// 
//    Rev 1.25   Nov 24 2005 16:22:48   porteanm
// PET1286 FN01 - Bulk Cancellation - verify Check Box.
// 
//    Rev 1.24   Nov 23 2005 17:14:58   porteanm
// PET1286 FN01 - Bulk Cancellation.
// 
//    Rev 1.23   Nov 22 2005 16:09:42   porteanm
// PET1286 FN01 - Bulk Cancellation - disable the Dilution btn for  Bulk.
// 
//    Rev 1.22   Nov 15 2005 16:08:22   porteanm
// PET1286 FN01 - Bulk Cancellation.
// 
//    Rev 1.21   Nov 13 2005 15:56:20   porteanm
// PET 1286 FN01 - Bulk Cancellation.
// 
//    Rev 1.20   Nov 12 2005 15:53:34   porteanm
// PET 1286 FN01 - Bulk Cancellation - The Verify check box behaviour should be rewritten nicer - later.
// 
//    Rev 1.19   Nov 11 2005 17:17:34   porteanm
// PET 1286 FN01 - Bulk Cancellation.
// 
//    Rev 1.18   Nov 10 2005 19:04:30   porteanm
// PET 1286 FN01 - Bulk Cancellation.
// 
//    Rev 1.17   Nov 09 2005 11:58:28   porteanm
// PET 1286 FN01 - Bulk Cancellation.
// 
//    Rev 1.16   Nov 06 2005 15:58:50   porteanm
// PET 1286 FN01 - Bulk Cancellation - work in progress.
// 
//    Rev 1.15   Sep 15 2005 18:12:16   popescu
// Incident# 388632 - trans cancel screen code overhaul
// 
//    Rev 1.14   Sep 15 2005 15:16:02   popescu
// Incident#403519 - added CLASSNAME as the fifth parameter to  BaseMainDlg constructor
// 
//    Rev 1.13   Sep 01 2005 14:02:30   popescu
// Incident# 388632 - trans cancel screen code overhaul
// 
//    Rev 1.12   Jul 20 2005 14:01:44   winnie
// Sync up the fix for 325606 for release 63. Handle the backdatedreson copy from TransCancel at CBO level. Use SplitCode to control dilution instead of AccountableMandatory
// 
//    Rev 1.11   Jul 08 2005 09:42:10   Yingbaol
// PET1235,FN01:Transaction cancellation rebook
// 
//    Rev 1.10   Jun 15 2005 14:49:46   ZHANGCEL
// Incident #322193 - Add logic to set RvCode into BackDatedReason fields
// 
//    Rev 1.9   Jun 01 2005 11:09:44   Fengyong
// Incident #323301 - add code protect, if there is a wrong user setup.
// 
//    Rev 1.8   Apr 20 2005 17:31:00   Fengyong
// #incident 293411 - add message box ask confirm the restore.
// 
//    Rev 1.7   Mar 15 2005 16:21:28   Fengyong
// PET1190 FN05 - Fix Check button crash
// 
//    Rev 1.6   Mar 14 2005 15:23:52   georgeet
// PET1190 FN05 - Syncup with view 337, change non repeat view to repeat
// 
//    Rev 1.5   Mar 09 2005 13:25:22   Fengyong
// PET1190 FN04 - uncomment batch 
// 
//    Rev 1.4   Mar 08 2005 19:03:44   Fengyong
// PET1190 FN04 - Add loadcontrol 
// 
//    Rev 1.3   Mar 08 2005 13:42:44   Fengyong
// PET1190 FN04 - uncomment enhance code after DD sync up
// 
//    Rev 1.2   Mar 07 2005 14:31:56   Fengyong
// PET1190FN04 - set back accountable code from dilution screen
// 
//    Rev 1.1   Mar 04 2005 17:15:18   Fengyong
// PET1190 FN04 - TransCancel Tempery check in for other coder
// 
//    Rev 1.0   Mar 03 2005 18:24:02   Fengyong
// Initial revision.
 */





