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
//    Copyright 2003 by International Financial Data Services
//
//******************************************************************************
//
// ^FILE   : TransSettlementInstrDlg.h
// ^AUTHOR : Monica Vadeanu
// ^DATE   : November 10, 2003
//
// ^CLASS    : TransSettlementInstrDlg
// ^SUBCLASS : TransSettlementInstrDlg
//
// ^CLASS DESCRIPTION : 
//
//******************************************************************************

#include "stdafx.h"

#ifndef IFASTGUI_H
   #include "mfdstc.h"
#endif

#include <uibase\DSTEdit.h>
#include <uibase\DSTComboBox.h>
#include "TransSettlementInstrDlg.h"

#include <ifastbp\TransSettlementInstrProcessIncludes.h>

#include <ifastcbo\dstcworksession.hpp>

extern CLASS_IMPORT const I_CHAR* CMD_GUI_SETTLEMENT_LOCATION_TRADE;
#include <bfproc\concretedialogcreator.hpp>
static ConcreteDialogCreator< TransSettlementInstrDlg > dlgCreator( CMD_GUI_SETTLEMENT_LOCATION_TRADE );

#ifdef _DEBUG
   #define new DEBUG_NEW
   #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


namespace
{
   const I_CHAR * const CLASSNAME = I_( "TransSettlementInstrDlg" );
   const I_CHAR * const YES       = I_( "Y" );
   const I_CHAR * const NO        = I_( "N" );
}

namespace TRADETYPE
{
   extern CLASS_IMPORT I_CHAR * const TRANSFER;
   extern CLASS_IMPORT I_CHAR * const EXCHANGE;
   extern CLASS_IMPORT I_CHAR * const ALL_FUND_TRANSFER;
} 

//******************************************************************************
TransSettlementInstrDlg::TransSettlementInstrDlg( CWnd* pParent, 
                                                  GenericInterfaceContainer* pGIC, 
                                                  GenericInterface* pGIParent, 
                                                  const Command& rCommand )
: BaseMainDlg( TransSettlementInstrDlg::IDD, pParent, pGIC, pGIParent, rCommand, CLASSNAME )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );

   //{{AFX_DATA_INIT(TransSettlementInstrDlg)
   // NOTE: the ClassWizard will add member initialization here
   //}}AFX_DATA_INIT
}

//******************************************************************************
TransSettlementInstrDlg::~TransSettlementInstrDlg()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************
void TransSettlementInstrDlg::DoDataExchange(CDataExchange* pDX)
{
   BaseMainDlg::DoDataExchange( pDX );
   //{{AFX_DATA_MAP(TransSettlementInstrDlg)
   // NOTE: the ClassWizard will add DDX and DDV calls here
   //}}AFX_DATA_MAP
}

//******************************************************************************
BEGIN_MESSAGE_MAP(TransSettlementInstrDlg, BaseMainDlg)
//{{AFX_MSG_MAP(TransSettlementInstrDlg)
ON_BN_CLICKED(IDC_RB_FROM_ACCOUNT, OnRbFromAccount)
ON_BN_CLICKED(IDC_RB_TO_ACCOUNT, OnRbToAccount)
ON_BN_CLICKED(IDC_BTN_RESET, OnBtnReset)
//ON_CBN_SELCHANGE(IDC_CMB_SETTLEMENT_LOCATION, OnCmbSelChangeSettlLoc)
//ON_CBN_SELCHANGE(IDC_CMB_SETTLEMENT_METHOD, OnCmbSelChangeClearingMethod)
//ON_EN_KILLFOCUS(IDC_EDT_DELIVERY, OnKillFocusEditDeliveryTo)
//ON_EN_KILLFOCUS(IDC_EDT_FOR_ACCOUNT, OnKillFocusEditForAccount)
//ON_EN_KILLFOCUS(IDC_EDT_IN_FAVOUR_OF, OnKillFocusEditInFavourOf)
   //}}AFX_MSG_MAP
END_MESSAGE_MAP()

//******************************************************************************
void TransSettlementInstrDlg::OnPostInitDialog()
{
   TRACE_METHOD( CLASSNAME, I_( "OnPostInitDialog" ) );
   CWaitCursor wait;

   DString dstr;
   getParent()->getField( this, IFASTBP_PROC::ORIGINAL_TRADE_CBO, ifds::TransNum, dstr);
   dstr.strip();
   SetDlgItemText( IDC_TXT_TRANS_NUM, dstr.c_str() );

   AddControl( CTRL_COMBO,
               IDC_CMB_SETTLEMENT_LOCATION,
               IFASTBP_PROC::ORIGINAL_TRADE_CBO,
               ifds::FrSettlLocCode,
               CTRLFLAG_AUTO_UPDATE_ON_CHANGE | CTRLFLAG_INITCOMBO_BY_SUB_LIST );

   AddControl( CTRL_COMBO,
               IDC_CMB_SETTLEMENT_METHOD,
               IFASTBP_PROC::ORIGINAL_TRADE_CBO,
               ifds::FrClearingMethod,
               CTRLFLAG_AUTO_UPDATE_ON_CHANGE | CTRLFLAG_INITCOMBO_BY_SUB_LIST );
   
   AddControl( CTRL_COMBO,
               IDC_CMB_SETTLEMENT_CODE,
               IFASTBP_PROC::ORIGINAL_TRADE_CBO,
               ifds::FrSettlInstrCode,
               CTRLFLAG_AUTO_UPDATE_ON_CHANGE | CTRLFLAG_INITCOMBO_BY_SUB_LIST );
  
   AddControl( CTRL_EDIT,
               IDC_EDT_ACCOUNT,
               IFASTBP_PROC::ORIGINAL_TRADE_CBO, 
               ifds::FrSettlementAccount, 
               CTRLFLAG_AUTO_UPDATE_ON_CHANGE | CTRLFLAG_DEFAULT );

   AddControl( CTRL_EDIT,
               IDC_EDT_INT_SETL_ACC,
               IFASTBP_PROC::ORIGINAL_TRADE_CBO, 
               ifds::FrInternalSettlementAccount,
               CTRLFLAG_AUTO_UPDATE_ON_CHANGE | CTRLFLAG_DEFAULT );
   
   AddControl( CTRL_EDIT,
               IDC_EDT_DELIVERY,
               IFASTBP_PROC::ORIGINAL_TRADE_CBO, 
               ifds::FrDeliveryTo );
   dynamic_cast<DSTEdit *>( GetControl( IDC_EDT_DELIVERY ) )->SetMaxCharNum( 50 );

   AddControl( CTRL_EDIT,
               IDC_EDT_FOR_ACCOUNT,
               IFASTBP_PROC::ORIGINAL_TRADE_CBO, 
               ifds::FrForAccount );
   dynamic_cast<DSTEdit *>( GetControl( IDC_EDT_FOR_ACCOUNT ) )->SetMaxCharNum( 50 );

   AddControl( CTRL_EDIT,
               IDC_EDT_IN_FAVOUR_OF,
               IFASTBP_PROC::ORIGINAL_TRADE_CBO, 
               ifds::FrInFavourOf );
   dynamic_cast<DSTEdit *>( GetControl( IDC_EDT_IN_FAVOUR_OF ) )->SetMaxCharNum( 50 );

   AddControl( CTRL_EDIT,
               IDC_EDT_PREF_CASH_MSG_TYPE,
               IFASTBP_PROC::ORIGINAL_TRADE_CBO, 
               ifds::FrCashMsgType);
   dynamic_cast<DSTEdit *>( GetControl( IDC_EDT_PREF_CASH_MSG_TYPE ) )->SetMaxCharNum( 25 );

    AddControl( CTRL_EDIT,
               IDC_EDT_INTERMEDIARY_BANK,
               IFASTBP_PROC::ORIGINAL_TRADE_CBO, 
               ifds::FrIntermediaryBank );
   dynamic_cast<DSTEdit *>( GetControl( IDC_EDT_INTERMEDIARY_BANK ) )->SetMaxCharNum( 50 );

    AddControl( CTRL_EDIT,
               IDC_EDT_RECEIVING_BANK,
               IFASTBP_PROC::ORIGINAL_TRADE_CBO, 
               ifds::FrReceivingBank );
   dynamic_cast<DSTEdit *>( GetControl( IDC_EDT_RECEIVING_BANK ) )->SetMaxCharNum( 50 );
    AddControl( CTRL_EDIT,
               IDC_EDT_BENFICIARY,
               IFASTBP_PROC::ORIGINAL_TRADE_CBO, 
               ifds::FrBeneficiary );
   dynamic_cast<DSTEdit *>( GetControl( IDC_EDT_BENFICIARY ) )->SetMaxCharNum( 50 );
 AddControl( CTRL_EDIT,
               IDC_EDT_SPECIAL_INST,
               IFASTBP_PROC::ORIGINAL_TRADE_CBO, 
               ifds::FrSpecialInstructions );
   dynamic_cast<DSTEdit *>( GetControl( IDC_EDT_SPECIAL_INST ) )->SetMaxCharNum( 50 );

	AddControl( CTRL_EDIT,
               IDC_EDT_CSD_LOCATION,
               IFASTBP_PROC::ORIGINAL_TRADE_CBO, 
			   ifds::FrCSDLocation);
   dynamic_cast<DSTEdit *>( GetControl( IDC_EDT_CSD_LOCATION ) )->SetMaxCharNum( 40 );

   AddControl( CTRL_EDIT,
               IDC_EDT_CSD_ACCOUNT_NUM,
               IFASTBP_PROC::ORIGINAL_TRADE_CBO, 
			   ifds::FrCSDAcctNum );
   dynamic_cast<DSTEdit *>( GetControl( IDC_EDT_CSD_ACCOUNT_NUM ) )->SetMaxCharNum( 40 );

   doRefresh (this, NULL_STRING);

   if ( I_( "TradesDlg" ) != _dstrFromScreen ) 
   {
      GetDlgItem( IDC_BTN_RESET )->EnableWindow( false );
   }
   else
   {
      GetDlgItem( IDC_BTN_RESET )->EnableWindow( true );
   }

   CWnd* pDeliveryWnd = GetDlgItem(IDC_EDT_DELIVERY);
   if (NULL != pDeliveryWnd)
   {
       if (DSTEdit* pDSTEditDelivery = dynamic_cast<DSTEdit*>(pDeliveryWnd))
       {
           pDSTEditDelivery->SetRemoveUnwantedCharsAfterPaste(true);
       }
   }

   CWnd* pForAccountWnd = GetDlgItem(IDC_EDT_FOR_ACCOUNT);
   if (NULL != pForAccountWnd)
   {
       if (DSTEdit* pDSTEditForAccount = dynamic_cast<DSTEdit*>(pForAccountWnd))
       {
           pDSTEditForAccount->SetRemoveUnwantedCharsAfterPaste(true);
       }
   }

   CWnd* pInFavorOfWnd = GetDlgItem(IDC_EDT_IN_FAVOR_OF);
   if (NULL != pInFavorOfWnd)
   {
       if (DSTEdit* pDSTEditInFavorOf = dynamic_cast<DSTEdit*>(pInFavorOfWnd))
       {
           pDSTEditInFavorOf->SetRemoveUnwantedCharsAfterPaste(true);
       }
   }

   CWnd* pCsdLocationWnd = GetDlgItem(IDC_EDT_CSD_LOCATION);
   if (NULL != pCsdLocationWnd)
   {
       if (DSTEdit* pDSTEditCsdLocation = dynamic_cast<DSTEdit*>(pCsdLocationWnd))
       {
           pDSTEditCsdLocation->SetRemoveUnwantedCharsAfterPaste(true);
       }
   }

   CWnd* pCsdAccountNumWnd = GetDlgItem(IDC_EDT_CSD_ACCOUNT_NUM);
   if (NULL != pCsdAccountNumWnd)
   {
       if (DSTEdit* pDSTEditCsdAccountNum = dynamic_cast<DSTEdit*>(pCsdAccountNumWnd))
       {
           pDSTEditCsdAccountNum->SetRemoveUnwantedCharsAfterPaste(true);
       }
   }

   CWnd* pCashMsgTypeWnd = GetDlgItem(IDC_EDT_PREF_CASH_MSG_TYPE);
   if (NULL != pCashMsgTypeWnd)
   {
       if (DSTEdit* pDSTEditCashMsgType = dynamic_cast<DSTEdit*>(pCashMsgTypeWnd))
       {
           pDSTEditCashMsgType->SetRemoveUnwantedCharsAfterPaste(true);
       }
   }

   CWnd* pIntermediaryBankWnd = GetDlgItem(IDC_EDT_INTERMEDIARY_BANK);
   if (NULL != pIntermediaryBankWnd)
   {
       if (DSTEdit* pDSTEditIntermediaryBank = dynamic_cast<DSTEdit*>(pIntermediaryBankWnd))
       {
           pDSTEditIntermediaryBank->SetRemoveUnwantedCharsAfterPaste(true);
       }
   }

   CWnd* pReceivingBankWnd = GetDlgItem(IDC_EDT_RECEIVING_BANK);
   if (NULL != pReceivingBankWnd)
   {
       if (DSTEdit* pDSTEditReceivingBank = dynamic_cast<DSTEdit*>(pReceivingBankWnd))
       {
           pDSTEditReceivingBank->SetRemoveUnwantedCharsAfterPaste(true);
       }
   }

   CWnd* pBeneficiaryWnd = GetDlgItem(IDC_EDT_BENEFICIARY);
   if (NULL != pBeneficiaryWnd)
   {
       if (DSTEdit* pDSTEditBeneficiary = dynamic_cast<DSTEdit*>(pBeneficiaryWnd))
       {
           pDSTEditBeneficiary->SetRemoveUnwantedCharsAfterPaste(true);
       }
   }

   CWnd* pSpecialInstWnd = GetDlgItem(IDC_EDT_SPECIAL_INST);
   if (NULL != pSpecialInstWnd)
   {
       if (DSTEdit* pDSTEditSpecialInst = dynamic_cast<DSTEdit*>(pSpecialInstWnd))
       {
           pDSTEditSpecialInst->SetRemoveUnwantedCharsAfterPaste(true);
       }
   }

}

//******************************************************************************
SEVERITY TransSettlementInstrDlg::doInit()
{
   SEVERITY sevRtn = NO_CONDITION;

   getParameter( TRANS_SETTLEMENT_LOCATION::FROM_SCREEN,           _dstrFromScreen );
   getParameter( TRANS_SETTLEMENT_LOCATION::PENDING_HISTORY,       _dstrPendingHist );
   getParameter( TRANS_SETTLEMENT_LOCATION::FROM_CLEARING_ACCOUNT, _dstrFromClearingAccount );
   getParameter( TRANS_SETTLEMENT_LOCATION::TO_CLEARING_ACCOUNT,   _dstrToClearingAccount );
   getParameter( TRANS_SETTLEMENT_LOCATION::SIDE,                  _dstrSide );

   return(sevRtn);
}

//******************************************************************************
bool TransSettlementInstrDlg::doRefresh( GenericInterface * rpGICaller, 
                                         const I_CHAR * szOriginalCommand )
{
   DString IsClearingAcctFrom,
           IsClearingAcctTo;

   getParent ()->getField ( this,
                            IFASTBP_PROC::FROM_ACCOUNT_CBO,
                            IsClearingAcct,
                            IsClearingAcctFrom,
                            false
                           );
   getParent ()->getField ( this,
                            IFASTBP_PROC::TO_ACCOUNT_CBO,
                            IsClearingAcct,
                            IsClearingAcctTo,
                            false
                           );

   CButton *pFromAccountRadioButton = static_cast < CButton* >( GetDlgItem( IDC_RB_FROM_ACCOUNT ) );   
   if ( NULL != pFromAccountRadioButton )
   {
      if (IsClearingAcctFrom == I_("N"))
      {
         pFromAccountRadioButton->EnableWindow (false);
      }
      else
      {
         pFromAccountRadioButton->EnableWindow (true);
         if (_dstrSide == I_("From"))
         {
            OnRbFromAccount ();
         }
      }
   }

   CButton *pToAccountRadioButton = static_cast < CButton* >( GetDlgItem( IDC_RB_TO_ACCOUNT ) );
   if ( NULL != pToAccountRadioButton )
   {
      if (IsClearingAcctTo == I_("N"))
      {
         pToAccountRadioButton->EnableWindow (false);
      }
      else 
      {
         pToAccountRadioButton->EnableWindow (true);
         if (IsClearingAcctFrom == I_("N") || _dstrSide == I_("To"))
         {
            OnRbToAccount ();
         }
      }
   }
   LoadControlErrorState ();
   return true;
}

//******************************************************************************
void TransSettlementInstrDlg::SetDlgCaption()
{
   TRACE_METHOD( CLASSNAME, I_( "SetDlgCaption" ) );

   DString IsClearingAcctFrom,
           IsClearingAcctTo;

   getParent ()->getField ( this,
                            IFASTBP_PROC::FROM_ACCOUNT_CBO,
                            IsClearingAcct,
                            IsClearingAcctFrom,
                            false
                           );

   getParent ()->getField ( this,
                            IFASTBP_PROC::TO_ACCOUNT_CBO,
                            IsClearingAcct,
                            IsClearingAcctTo,
                            false
                           );

   DString dstrDlgCaption;
   if ( 0 != _dstrFromClearingAccount.stripAll().length() &&
        0 == _dstrToClearingAccount.stripAll().length() )
   {

      //dstrDlgCaption = I_( "Settlement Instruction at Transaction Level, from Clearing Account: " )
      //                 + _dstrFromClearingAccount;

      DString strAcctNumType;

      if ( IsClearingAcctFrom == YES )
      {
         
		  CString cstrClrAcct;
		  cstrClrAcct.LoadString(TXT_CLEARING_ACCOUNT);
		  strAcctNumType = DString(cstrClrAcct) + _dstrFromClearingAccount;
      }
      else
      {
         CString cstrNonClrAcct;
		 cstrNonClrAcct.LoadString(TXT_NON_CLEARING_ACCOUNT);
		 strAcctNumType = DString(cstrNonClrAcct) + _dstrFromClearingAccount;
      }
      CString cstrSettlInstrFrom;
      cstrSettlInstrFrom.LoadString(TXT_SETT_INSTR_TRAN_LVL_FROM);
	  dstrDlgCaption = DString(cstrSettlInstrFrom) 
                       + strAcctNumType;
   }
   else if ( 0 == _dstrFromClearingAccount.stripAll().length() &&
             0 != _dstrToClearingAccount.stripAll().length() )
   {

      //dstrDlgCaption = I_( "Settlement Instruction at Transaction Level, to Clearing Account: " )
      //                 + _dstrToClearingAccount;

      DString strAcctNumType;

      if ( IsClearingAcctFrom == YES )
      {
         CString cstrClrAcct;
		 cstrClrAcct.LoadString(TXT_CLEARING_ACCOUNT);
		 strAcctNumType = DString(cstrClrAcct) + _dstrToClearingAccount;
      }
      else
      {
         CString cstrNonClrAcct;
		 cstrNonClrAcct.LoadString(TXT_NON_CLEARING_ACCOUNT);
		 strAcctNumType = DString(cstrNonClrAcct) + _dstrToClearingAccount;
      }

      CString cstrSettlInstrTo;
      cstrSettlInstrTo.LoadString(TXT_SETT_INSTR_TRAN_LVL_TO);
	  dstrDlgCaption = DString(cstrSettlInstrTo) 
                       + strAcctNumType;
   }
   else if ( 0 != _dstrFromClearingAccount.stripAll().length() &&
             0 != _dstrToClearingAccount.stripAll().length() )
   {
      //dstrDlgCaption = I_( "Settlement Instruction at Transaction Level, from " );
      //               + ( IsClearingAcctFrom == YES ) ? I_( "Clearing Account: " ) : I_( "non-Clearing Account: " )
      //               + _dstrFromClearingAccount
      //               + I_( ", to " )
      //               + ( IsClearingAcctTo == YES ) ? I_( "Clearing Account: " ) : I_( "non-Clearing Account: " )
      //               + _dstrToClearingAccount;

      DString strAcctFromTxt,strAcctToTxt;

      if ( IsClearingAcctFrom == YES )
      {
         CString cstrClrAcct;
		 cstrClrAcct.LoadString(TXT_CLEARING_ACCOUNT);
		 strAcctFromTxt = DString(cstrClrAcct) + _dstrFromClearingAccount;
      }
      else
      {
         CString cstrNonClrAcct;
		 cstrNonClrAcct.LoadString(TXT_NON_CLEARING_ACCOUNT);
		 strAcctFromTxt = DString(cstrNonClrAcct) + _dstrFromClearingAccount;
      }

      if ( IsClearingAcctTo == YES )
      {
         CString cstrClrAcct;
		 cstrClrAcct.LoadString(TXT_CLEARING_ACCOUNT);
		 strAcctToTxt = DString(cstrClrAcct) + _dstrToClearingAccount;
      }
      else
      {
         CString cstrNonClrAcct;
		 cstrNonClrAcct.LoadString(TXT_NON_CLEARING_ACCOUNT);
		 strAcctToTxt = DString(cstrNonClrAcct) + _dstrToClearingAccount;
      }

      CString cstrSettlInstrFrom ,cstrTo;
      cstrSettlInstrFrom.LoadString(TXT_SETT_INSTR_TRAN_LVL_FROM);
	  cstrTo.LoadString(TXT_TO_TXT);
	  dstrDlgCaption = DString(cstrSettlInstrFrom)
                       + strAcctFromTxt 
                       + DString(cstrTo)
                       + strAcctToTxt;
   }

   SetWindowText( dstrDlgCaption.c_str() );
}

//******************************************************************************
BOOL TransSettlementInstrDlg::PreTranslateMessage(MSG* pMsg) 
{
   BOOL isTranslated = FALSE;

   // make sure that certain accelerator keys are processed correctly
   if( !isTranslated )
   {
      // pass message down the chain
      isTranslated = BaseMainDlg::PreTranslateMessage( pMsg );
   }

   return(isTranslated);
}

//******************************************************************************
void TransSettlementInstrDlg::OnRbFromAccount()
{
   TRACE_METHOD( CLASSNAME, I_( "OnRbFromAccount" ) );
   CWaitCursor wait;

   CButton *pFromAccountRadioButton = static_cast < CButton* > ( GetDlgItem( IDC_RB_FROM_ACCOUNT ) );
   CButton *pToAccountRadioButton = static_cast < CButton* > ( GetDlgItem( IDC_RB_TO_ACCOUNT ) );
   if ( NULL != pFromAccountRadioButton )
   {
      pFromAccountRadioButton->SetCheck( 1 );
      CString cstrFrmAcct;
	  cstrFrmAcct.LoadString(TXT_FROM_ACCT);
	  SetDlgItemText( IDC_SETTL_INSTR_TRADE_GROUP_BOX, cstrFrmAcct );
   }
   if ( NULL != pToAccountRadioButton )
      pToAccountRadioButton->SetCheck( 0 );

   getParent()->send (this, I_("Validate"));

   ReInitControl( IDC_CMB_SETTLEMENT_LOCATION,
                  IFASTBP_PROC::ORIGINAL_TRADE_CBO,
                  ifds::FrSettlLocCode );

   ReInitControl( IDC_CMB_SETTLEMENT_METHOD,
                  IFASTBP_PROC::ORIGINAL_TRADE_CBO,
                  ifds::FrClearingMethod );

   ReInitControl( IDC_CMB_SETTLEMENT_CODE,
                  IFASTBP_PROC::ORIGINAL_TRADE_CBO,
                  ifds::FrSettlInstrCode );

   ReInitControl( IDC_EDT_DELIVERY,
                  IFASTBP_PROC::ORIGINAL_TRADE_CBO,
                  ifds::FrDeliveryTo );

   ReInitControl( IDC_EDT_FOR_ACCOUNT,
                  IFASTBP_PROC::ORIGINAL_TRADE_CBO,
                  ifds::FrForAccount );

   ReInitControl( IDC_EDT_IN_FAVOUR_OF,
                  IFASTBP_PROC::ORIGINAL_TRADE_CBO,
                  ifds::FrInFavourOf );

   ReInitControl( IDC_EDT_PREF_CASH_MSG_TYPE,
                  IFASTBP_PROC::ORIGINAL_TRADE_CBO,
                  ifds::FrCashMsgType);

   ReInitControl( IDC_EDT_INTERMEDIARY_BANK,
                  IFASTBP_PROC::ORIGINAL_TRADE_CBO,
                  ifds::FrIntermediaryBank );

   ReInitControl( IDC_EDT_RECEIVING_BANK,
                  IFASTBP_PROC::ORIGINAL_TRADE_CBO,
                  ifds::FrReceivingBank );

   ReInitControl( IDC_EDT_BENFICIARY,
                  IFASTBP_PROC::ORIGINAL_TRADE_CBO,
                  ifds::FrBeneficiary );

  ReInitControl( IDC_EDT_SPECIAL_INST,
                  IFASTBP_PROC::ORIGINAL_TRADE_CBO,
                  ifds::FrSpecialInstructions );

  ReInitControl(  IDC_EDT_INT_SETL_ACC,
                  IFASTBP_PROC::ORIGINAL_TRADE_CBO,
                  ifds::FrInternalSettlementAccount,
                  CTRLFLAG_AUTO_UPDATE_ON_CHANGE | CTRLFLAG_DEFAULT);
 
  ReInitControl(  IDC_EDT_ACCOUNT,
                  IFASTBP_PROC::ORIGINAL_TRADE_CBO,
                  ifds::FrSettlementAccount,
                  CTRLFLAG_AUTO_UPDATE_ON_CHANGE | CTRLFLAG_DEFAULT );

   ReInitControl( IDC_EDT_CSD_LOCATION,
                  IFASTBP_PROC::ORIGINAL_TRADE_CBO,
				  ifds::FrCSDLocation );

   ReInitControl( IDC_EDT_CSD_ACCOUNT_NUM,
                  IFASTBP_PROC::ORIGINAL_TRADE_CBO,
				  ifds::FrCSDAcctNum );

   ConnectControlsToData();
   LoadControls();

   SetDlgCaption();

   if ( I_( "TradesDlg" ) == _dstrFromScreen &&
        NULL != pToAccountRadioButton && pToAccountRadioButton->IsWindowEnabled() )
   {
      DString dstrTransType;
      getParent()->getField( this, 
                             IFASTBP_PROC::ORIGINAL_TRADE_CBO, 
                             ifds::TradesTransType, 
                             dstrTransType,
                             false);  //non-formatted
      dstrTransType.stripAll();
      if ( dstrTransType == TRADETYPE::TRANSFER ||
           dstrTransType == TRADETYPE::ALL_FUND_TRANSFER )
      {
         CString cstrTransferMessage;
		 cstrTransferMessage.LoadString(TXT_FROM_TO_INSTR_SAME_FOR_TRANSFER); 
		 AfxMessageBox( cstrTransferMessage, MB_OK );
      }
      else if ( dstrTransType == TRADETYPE::EXCHANGE )
      {
         CString cstrExchangeMessage;
		 cstrExchangeMessage.LoadString(TXT_FROM_TO_INSTR_SAME_FOR_EXCHANGE);
		 AfxMessageBox( cstrExchangeMessage, MB_OK );
      }
   }
}

//******************************************************************************
void TransSettlementInstrDlg::OnRbToAccount()
{
   TRACE_METHOD( CLASSNAME, I_( "OnRbToAccount" ) );
   CWaitCursor wait;

   CButton *pFromAccountRadioButton = static_cast < CButton* > ( GetDlgItem( IDC_RB_FROM_ACCOUNT ) );
   CButton *pToAccountRadioButton = static_cast < CButton* > ( GetDlgItem( IDC_RB_TO_ACCOUNT ) );
   if ( NULL != pFromAccountRadioButton )
         pFromAccountRadioButton->SetCheck( 0 );
   if ( NULL != pToAccountRadioButton )
   {
      pToAccountRadioButton->SetCheck( 1 );
	  CString cstrToAcct;
	  cstrToAcct.LoadString(TXT_TO_ACCT);
      SetDlgItemText( IDC_SETTL_INSTR_TRADE_GROUP_BOX, cstrToAcct );
   }
   
   getParent()->send (this, I_("Validate"));
   
   ReInitControl( IDC_CMB_SETTLEMENT_LOCATION,
                  IFASTBP_PROC::ORIGINAL_TRADE_CBO,
                  ifds::ToSettlLocCode );

   ReInitControl( IDC_CMB_SETTLEMENT_METHOD,
                  IFASTBP_PROC::ORIGINAL_TRADE_CBO,
                  ifds::ToClearingMethod );

   ReInitControl( IDC_CMB_SETTLEMENT_CODE,
                  IFASTBP_PROC::ORIGINAL_TRADE_CBO,
                  ifds::ToSettlInstrCode );

   ReInitControl( IDC_EDT_DELIVERY,
                  IFASTBP_PROC::ORIGINAL_TRADE_CBO,
                  ifds::ToDeliveryTo );

   ReInitControl( IDC_EDT_FOR_ACCOUNT,
                  IFASTBP_PROC::ORIGINAL_TRADE_CBO,
                  ifds::ToForAccount );

   ReInitControl( IDC_EDT_IN_FAVOUR_OF,
                  IFASTBP_PROC::ORIGINAL_TRADE_CBO,
                  ifds::ToInFavourOf );

   ReInitControl( IDC_EDT_PREF_CASH_MSG_TYPE,
                  IFASTBP_PROC::ORIGINAL_TRADE_CBO,
                  ifds::ToCashMsgType);

   ReInitControl( IDC_EDT_INTERMEDIARY_BANK,
                  IFASTBP_PROC::ORIGINAL_TRADE_CBO,
                  ifds::ToIntermediaryBank );

   ReInitControl( IDC_EDT_RECEIVING_BANK,
                  IFASTBP_PROC::ORIGINAL_TRADE_CBO,
                  ifds::ToReceivingBank );

   ReInitControl( IDC_EDT_BENFICIARY,
                  IFASTBP_PROC::ORIGINAL_TRADE_CBO,
                  ifds::ToBeneficiary );

  ReInitControl( IDC_EDT_SPECIAL_INST,
                  IFASTBP_PROC::ORIGINAL_TRADE_CBO,
                  ifds::ToSpecialInstructions );

  ReInitControl( IDC_EDT_INT_SETL_ACC,
                  IFASTBP_PROC::ORIGINAL_TRADE_CBO,
                  ifds::ToInternalSettlementAccount );
 
  ReInitControl( IDC_EDT_ACCOUNT,
                  IFASTBP_PROC::ORIGINAL_TRADE_CBO,
                  ifds::ToSettlementAccount );

   ReInitControl( IDC_EDT_CSD_LOCATION,
                  IFASTBP_PROC::ORIGINAL_TRADE_CBO,
				  ifds::ToCSDLocation );

   ReInitControl( IDC_EDT_CSD_ACCOUNT_NUM,
                  IFASTBP_PROC::ORIGINAL_TRADE_CBO,
				  ifds::ToCSDAcctNum );

   ConnectControlsToData();
   LoadControls();

   SetDlgCaption();

   if ( I_( "TradesDlg" ) == _dstrFromScreen &&
        NULL != pFromAccountRadioButton && pFromAccountRadioButton->IsWindowEnabled() )
   {
      DString dstrTransType;
      getParent()->getField( this, 
                             IFASTBP_PROC::ORIGINAL_TRADE_CBO, 
                             ifds::TradesTransType, 
                             dstrTransType );
      dstrTransType.stripAll();
      if ( dstrTransType == TRADETYPE::TRANSFER ||
           dstrTransType == TRADETYPE::ALL_FUND_TRANSFER )
      {
         CString cstrTransferMessage;
		 cstrTransferMessage.LoadString(TXT_FROM_TO_INSTR_SAME_FOR_TRANSFER);
		 AfxMessageBox( cstrTransferMessage, MB_OK );
      }
      else if ( dstrTransType == TRADETYPE::EXCHANGE )
      {
         CString cstrExchangeMessage;
		 cstrExchangeMessage.LoadString(TXT_FROM_TO_INSTR_SAME_FOR_EXCHANGE);
         AfxMessageBox( cstrExchangeMessage, MB_OK );
      }
   }
}

//******************************************************************************
void TransSettlementInstrDlg::OnBtnReset()
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTGUI_CONDITION, 
                           CLASSNAME, 
                           I_("OnBtnReset")
                         );
   if (getParent()->send (this, I_("Cancel")))
   {
      doRefresh( this, NULL );
   }
   else
   {
      // Display error
      ConditionMessageBox (FRAMEBELOW (), GETHIGHESTSEVERITY ());
   }
}

//******************************************************************************
void TransSettlementInstrDlg::OnCancel()
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTGUI_CONDITION, 
                           CLASSNAME, 
                           I_("OnCancel")
                         );
   if (getParent()->send (this, I_("Cancel")))
   {
      CDialog::OnCancel();
   }
   else
   {
      // Display error
      ConditionMessageBox (FRAMEBELOW (), GETHIGHESTSEVERITY ());
   }
}


/*
//******************************************************************************
void TransSettlementInstrDlg::OnCmbSelChangeSettlLoc()
{
   CButton *pFromAccountRadioButton = static_cast < CButton* >( GetDlgItem( IDC_RB_FROM_ACCOUNT ) );
   CButton *pToAccountRadioButton = static_cast < CButton* >( GetDlgItem( IDC_RB_TO_ACCOUNT ) );
   if ( NULL != pFromAccountRadioButton && pFromAccountRadioButton->IsWindowEnabled() && 
        NULL != pToAccountRadioButton   && pToAccountRadioButton->IsWindowEnabled() )
   {
      if ( I_( "TradesDlg" ) == _dstrFromScreen )
      {
         DString dstrTransType;
         getParent()->getField( this, 
                                IFASTBP_PROC::ORIGINAL_TRADE_CBO, 
                                ifds::TradesTransType, 
                                dstrTransType );   

         if ( dstrTransType.stripAll() == I_( "Exchange" ) )
         {
            DSTComboBox *dstcomboSettlLocCode = dynamic_cast< DSTComboBox * >( GetDlgItem( IDC_CMB_SETTLEMENT_LOCATION ) );
            if( dstcomboSettlLocCode != NULL )
            {
               CString cstrSettlLocCode;
               int iCurrSel = dstcomboSettlLocCode->GetCurSel();
               DString dstrSettlLocCode = *( reinterpret_cast< DString * >( dstcomboSettlLocCode->GetItemData( iCurrSel ) ) );
               
               getParent()->setField( this, 
                                      IFASTBP_PROC::ORIGINAL_TRADE_CBO, 
                                      ifds::FrSettlLocCode, 
                                      dstrSettlLocCode,
                                      false );  
               getParent()->setField( this, 
                                      IFASTBP_PROC::ORIGINAL_TRADE_CBO, 
                                      ifds::ToSettlLocCode, 
                                      dstrSettlLocCode, 
                                      false );
            }
         }
      }
   }
}

//******************************************************************************
void TransSettlementInstrDlg::OnCmbSelChangeClearingMethod()
{
   if ( I_( "TradesDlg" ) == _dstrFromScreen )
   {
      DString dstrTransType;
      getParent()->getField( this, 
                             IFASTBP_PROC::ORIGINAL_TRADE_CBO, 
                             ifds::TradesTransType, 
                             dstrTransType );

      if ( dstrTransType.stripAll() == I_( "Exchange" ) )
      {
         DSTComboBox *dstcomboSettlLocCode = dynamic_cast< DSTComboBox * >( GetDlgItem( IDC_CMB_SETTLEMENT_METHOD ) );
         if( dstcomboSettlLocCode != NULL )
         {               
            CString cstrSettlLocCode;
            int iCurrSel = dstcomboSettlLocCode->GetCurSel();
            DString dstrSettlLocCode = *( reinterpret_cast< DString * >( dstcomboSettlLocCode->GetItemData( iCurrSel ) ) );
               
            getParent()->setField( this, 
                                   IFASTBP_PROC::ORIGINAL_TRADE_CBO, 
                                   ifds::FrClearingMethod, 
                                   dstrSettlLocCode,
                                   false );
            getParent()->setField( this, 
                                   IFASTBP_PROC::ORIGINAL_TRADE_CBO, 
                                   ifds::ToClearingMethod, 
                                   dstrSettlLocCode, 
                                   false );
         }
      }
   }
}

//******************************************************************************
void TransSettlementInstrDlg::OnKillFocusEditDeliveryTo()
{   
   CString cstrDeliveryTo;
   GetDlgItem(IDC_EDT_DELIVERY)->GetWindowText( cstrDeliveryTo );
   DString dstrDeliveryTo( cstrDeliveryTo );

   setFromToFields( dstrDeliveryTo, ifds::FrDeliveryTo, ifds::ToDeliveryTo );
}

//******************************************************************************
void TransSettlementInstrDlg::OnKillFocusEditForAccount()
{
   CString cstrForAccount;
   GetDlgItem( IDC_EDT_FOR_ACCOUNT )->GetWindowText( cstrForAccount );
   DString dstrForAccount( cstrForAccount );

   setFromToFields( dstrForAccount, ifds::FrForAccount, ifds::ToForAccount );
}

//******************************************************************************
void TransSettlementInstrDlg::OnKillFocusEditInFavourOf()   
{
   CString cstrInFavourOf;
   GetDlgItem( IDC_EDT_IN_FAVOUR_OF )->GetWindowText( cstrInFavourOf );
   DString dstrInFavourOf( cstrInFavourOf );         

   setFromToFields( dstrInFavourOf, ifds::FrInFavourOf, ifds::ToInFavourOf );
}

//******************************************************************************
void TransSettlementInstrDlg::setFromToFields( const DString &dstrFieldValue, 
                                               const BFFieldId &fieldIdFrom, 
                                               const BFFieldId &fieldIdTo )
{
   CButton *pFromAccountRadioButton = static_cast < CButton* >( GetDlgItem( IDC_RB_FROM_ACCOUNT ) );
   CButton *pToAccountRadioButton = static_cast < CButton* >( GetDlgItem( IDC_RB_TO_ACCOUNT ) );
   if ( NULL != pFromAccountRadioButton && pFromAccountRadioButton->IsWindowEnabled() && 
        NULL != pToAccountRadioButton   && pToAccountRadioButton->IsWindowEnabled() )
   {
      if ( I_( "TradesDlg" ) == _dstrFromScreen )
      {
         DString dstrTransType;
         getParent()->getField( this, 
                                IFASTBP_PROC::ORIGINAL_TRADE_CBO, 
                                ifds::TradesTransType, 
                                dstrTransType );  
         dstrTransType.stripAll();
         if ( dstrTransType == I_( "Transfer" ) || 
              dstrTransType == I_( "Exchange" ) ||
              dstrTransType == I_( "AllFundTransfer" ) )
         {
            getParent()->setField( this, 
                                   IFASTBP_PROC::ORIGINAL_TRADE_CBO, 
                                   fieldIdFrom, 
                                   dstrFieldValue );  
            getParent()->setField( this, 
                                   IFASTBP_PROC::ORIGINAL_TRADE_CBO, 
                                   fieldIdTo, 
                                   dstrFieldValue );

         }
      }
   }
}
*/

//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastgui/TransSettlementInstrDlg.cpp-arc  $
// 
//    Rev 1.8   Nov 19 2011 01:40:58   wp040143
// P0186484/FN06 - DESKTOP - iFast Desktop (French Customizations)
// 
//    Rev 1.7   19 Dec 2008 13:14:38   popescu
// Incident 1514583 - Extraneous error msg when entering clearing method for transfer
// 
//    Rev 1.6   Jun 12 2008 11:16:10   daechach
// in# 1304478 - PET5815FN02-Screen caption of "Setl Instru at" not correct for non-clearing acc.
// 
//    Rev 1.5   Sep 15 2005 15:16:06   popescu
// Incident#403519 - added CLASSNAME as the fifth parameter to  BaseMainDlg constructor
// 
//    Rev 1.4   Dec 07 2004 17:49:54   aguilaam
// PET1117_FN21: settlement instructions - adjusted edit boxes to accept up to 50 chars
// 
//    Rev 1.3   Nov 29 2004 20:31:08   popescu
// PET 1117/06/56 fees/trades processing
// 
//    Rev 1.2   Nov 25 2004 14:59:32   popescu
// PET 1117/06, settle locations
// 
//    Rev 1.1   Nov 24 2004 21:36:56   popescu
// PET 1117/06/56. trade processing, settle location
// 
//    Rev 1.0   Oct 14 2004 12:32:50   VADEANUM
// Initial revision.
// 
//    Rev 1.5   Jan 22 2004 09:44:46   VADEANUM
// PTS 10026113 - Cancel button enabled. This also fixes the 'x' button.
// 
//    Rev 1.4   Dec 08 2003 14:00:52   VADEANUM
// PET859 FN1 - Settlement Location at Trade Level support.
// 
//    Rev 1.3   Dec 08 2003 12:37:06   VADEANUM
// PET859 FN1 - Settlement Location at Trade Level support.
// 
//    Rev 1.2   Nov 27 2003 13:20:26   VADEANUM
// PET859 FN1 - Settlement Location at Trade Level support - implemented doRefresh().
// 
//    Rev 1.1   Nov 27 2003 12:57:20   VADEANUM
// PET859 FN1 - Settlement Location at Trade Level support.
// 
//    Rev 1.0   Nov 10 2003 14:41:46   VADEANUM
// Initial revision.
//
