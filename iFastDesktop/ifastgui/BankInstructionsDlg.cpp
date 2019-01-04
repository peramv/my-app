//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by DST Canada, Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2001 by DST Canada, Inc.
//
//******************************************************************************
//
// ^FILE   : BankInstructionsDlg.cpp
// ^AUTHOR : Mihai Virgil Buzila
// ^DATE   : 02/09/01
//
// ^CLASS    : BankInstructionsDlg
// ^SUBCLASS : BaseMainDlg
//
// ^CLASS DESCRIPTION : 
//
//******************************************************************************

#include "stdafx.h"
#include "mfdstc.h"
#include "bankinstructionsdlg.h"
#include <ifastbp\bankinstructionsprocess.hpp>
#include <ifastbp\bankinstructionsprocessincludes.h>
#include <configmanager.hpp>
#include <ifastcsi\csisession.h>
#include <ifastcsi\ifastcsi.h>
#include <uibase\dstgridwnd.h>
#include <uibase\dstlistctrl.h>
#include <ifastcbo\dstcommonfunction.hpp>
#include <ifastbp\mfcaninterprocparam.hpp>
#include <uibase\dstedit.h>
#include <ifastcbo\dstcworksession.hpp>
#include <assert.h>
#include <ifastbp\rrif_lif_lrif_infoprocessincludes.h>
#include <ifastcbo\financialinstitution.hpp>
// borrow remarke status set
//#include <ifastdataimpl\dse_dstc0005_vwrepeat_record.hpp>

extern CLASS_IMPORT const I_CHAR* CMD_BPROC_SYSTEMATIC;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_DISTRIBUTION;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_FINANCIAL_INSTITUTION_SEARCH;
extern CLASS_IMPORT const I_CHAR* CMD_GUI_BANK_INSTRUCTIONS;
#include <bfproc\concretedialogcreator.hpp>
static ConcreteDialogCreator< BankInstructionsDlg > dlgCreator (CMD_GUI_BANK_INSTRUCTIONS);

#ifdef _DEBUG
   #define new DEBUG_NEW
   #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

namespace
{
   const I_CHAR * const CLASSNAME            = I_ ("BankInstructionsDlg");
   const I_CHAR * const LV_BANK_INSTR        = I_ ("BankAcounts");
   const I_CHAR * const GR_BANK_OPTIONS      = I_ ("BankOptions");
   const I_CHAR * const ACCOUNT_NUM          = I_ ("AccountNum");
   const I_CHAR * const MOD_USER             = I_ ("ModUser");
   const I_CHAR * const MOD_DATE             = I_ ("ModDate");
   const I_CHAR * const USER_NAME            = I_ ("Username");
   const I_CHAR * const PROCESS_DATE         = I_ ("ProcessDate");
   const I_CHAR * const CASH_FUND_TO_CODE    = I_ ("CASH");//FILT
   const I_CHAR * const EFT_PAY_TYPE         = I_ ("E");
   const I_CHAR * const BANKACCTNUM          = I_ ("BANKINSTRDLG_HNum");
   const I_CHAR * const BANKACCTTYPE         = I_ ("BANKINSTRDLG_HType");
   const I_CHAR * const USE                  = I_ ("Use");
   const I_CHAR * const STATUS               = I_ ("Status");
   const I_CHAR * const CFDS_CAN             = I_ ("Canada");
   const I_CHAR * const MSDW_JAP             = I_ ("MSDW - Japan");
   const I_CHAR * const TRANS_TYPE           = I_ ("TransactionType");
   const I_CHAR * const USER_ACCESS_CODE     = I_ ("UserAccessCode");
}

namespace TRADETYPE
{
   extern CLASS_IMPORT I_CHAR * const PURCHASE;
   extern CLASS_IMPORT I_CHAR * const PAC;
   extern CLASS_IMPORT I_CHAR * const SWP;
   extern CLASS_IMPORT I_CHAR * const AUTO_TRANSFER;
   extern CLASS_IMPORT I_CHAR * const REDEMPTION;
   extern CLASS_IMPORT I_CHAR * const EXCHANGE;
   extern CLASS_IMPORT I_CHAR * const TRANSFER;
   extern CLASS_IMPORT I_CHAR * const SAVING_PLAN;
   extern CLASS_IMPORT I_CHAR * const ADMIN_FEE;
   extern CLASS_IMPORT I_CHAR * const REDEMPTION_LIKE;   //   = I_("PW,AW,AF,RL,AF91"); // redemption, swp, admin fee, rollover
   extern CLASS_IMPORT I_CHAR * const PURCHASE_LIKE;     //   = I_("ED,RC");  //purchase, reinvest purchase
   extern CLASS_IMPORT I_CHAR * const EXCHANGE_LIKE;     //   = I_("TI,TO,EI,EO,XR,TR,AFTR");
}

namespace CND
{  // Conditions used
   extern const long GUI_ERR_UNKNOWN_EXCEPTION;
}

namespace UAF
{
   extern CLASS_IMPORT I_CHAR * const BANKING_INSTRUCTION;
   extern CLASS_IMPORT I_CHAR * const RIF_LIF_LRIF_FIELD_INFO;
   extern CLASS_IMPORT I_CHAR * const RIF_LIF_LRIF_INFO;
   extern CLASS_IMPORT I_CHAR * const DISTRIBUTION;
   extern CLASS_IMPORT I_CHAR * const PAC;
   extern CLASS_IMPORT I_CHAR * const SWP;
   extern CLASS_IMPORT I_CHAR * const SAVING_PLAN;
   extern CLASS_IMPORT I_CHAR * const AUTOMATIC_TRANSFER;
   extern CLASS_IMPORT I_CHAR * const TRANSACTION_HISTORY;
   extern CLASS_IMPORT I_CHAR * const PENDING_TRADE;
   extern CLASS_IMPORT I_CHAR * const TRADING_PURCHASE;
   extern CLASS_IMPORT I_CHAR * const TRADING_EXCHANGE;
   extern CLASS_IMPORT I_CHAR * const TRADING_REDEMPTION;
   extern CLASS_IMPORT I_CHAR * const BANK_ACCT_NAME;
   extern CLASS_IMPORT I_CHAR * const DIRECT_TRADING_AGREEMENT;
   extern CLASS_IMPORT I_CHAR * const FUND_GROUP_BANK_INSTR;
   extern CLASS_IMPORT I_CHAR * const TRADE_BANKING;
   extern CLASS_IMPORT I_CHAR * const REG_AGENT;
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId DirectDepositBankApplicable;
   extern CLASS_IMPORT const BFTextFieldId BankInstrComboSettlementBroker;
   extern CLASS_IMPORT const BFTextFieldId BankInstrComboSettlementBranch;
   extern CLASS_IMPORT const BFTextFieldId BankInstrComboSettlementSlsrep;
   extern CLASS_IMPORT const BFTextFieldId PayInstructExists;
   extern CLASS_IMPORT const BFTextFieldId BankInstrComboAccountCommitment;
   extern CLASS_IMPORT const BFTextFieldId RegAgent;
   extern CLASS_IMPORT const BFTextFieldId BankInstrComboRegAgent;
   extern CLASS_IMPORT const BFTextFieldId PayInstrOption;
   extern CLASS_IMPORT const BFTextFieldId DefaultBankingLevel;
   extern CLASS_IMPORT const BFTextFieldId BankingLevel;
   extern CLASS_IMPORT const BFTextFieldId rxBankingEntity;
   extern CLASS_IMPORT const BFTextFieldId BankInstrComboDefaultNoRRIFAcct;
}

namespace MFCAN_IP_PARAM
{
   extern CLASS_IMPORT const I_CHAR * const DIRCT_DEPST_APPLIC;
}

namespace AcctUseCode
{
   extern CLASS_IMPORT const I_CHAR * const DIRECT_DEPOSIT;
}

namespace BANKTYPE
{
   extern CLASS_IMPORT I_CHAR *  const SHAREHOLDER ;
   extern CLASS_IMPORT I_CHAR *  const ACCOUNT ;
}
namespace BANKINGLEVEL
{
   extern CLASS_IMPORT I_CHAR * const SHAREHOLDER_LEVEL;
   extern CLASS_IMPORT I_CHAR * const ACCOUNT_LEVEL;
   extern CLASS_IMPORT I_CHAR * const SHAREHOLDER_AND_ACCOUNT_LEVEL;
}
namespace BANKENTITY
{
   I_CHAR * const SHAREHOLDER = I_("10");
   I_CHAR * const  ACCOUNT  = I_("14");
}
//******************************************************************************
BankInstructionsDlg::BankInstructionsDlg (CWnd* pParent, GenericInterfaceContainer* pGIC, 
   GenericInterface* pGIParent, const Command& rCommand)
: BaseMainDlg (BankInstructionsDlg::IDD, pParent, pGIC, pGIParent, rCommand, CLASSNAME), 
m_strUserAccessCode (NULL_STRING), 
m_dstrBankInstructionsListSelectionKey (NULL_STRING),
m_bEnableHistory( true ),
m_pFont (NULL),
m_bShrBank(-1),
m_bShrDummyList_Added(false),
m_bAcctDummyList_Added(false),
m_bFromPostinitDlg(false)
{
   TRACE_CONSTRUCTOR (CLASSNAME, NULL_STRING);
   
   //{{AFX_DATA_INIT (BankInstructionsDlg)
   //}}AFX_DATA_INIT
}


//******************************************************************************
BankInstructionsDlg::~BankInstructionsDlg ()
{
   TRACE_DESTRUCTOR (CLASSNAME);
   if (m_pFont)
   {
      delete m_pFont;
   }
}


//******************************************************************************
void BankInstructionsDlg::DoDataExchange (CDataExchange* pDX)
{
   BaseMainDlg::DoDataExchange (pDX);
   //{{AFX_DATA_MAP (BankInstructionsDlg)
    DDX_Radio(pDX, IDC_RB_SHR_BANKING, m_bShrBank);
   //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP (BankInstructionsDlg, BaseMainDlg)
//{{AFX_MSG_MAP (BankInstructionsDlg)
ON_BN_CLICKED (IDC_BTN_ADD, OnBtnAdd)
ON_BN_CLICKED (IDC_BTN_DEL, OnBtnDel)
ON_BN_CLICKED (IDC_BTN_TO, OnBtnTo)
ON_BN_CLICKED (IDC_BTN_ADM_DATES, OnBtnAdmDates)
ON_BN_CLICKED (IDC_BTN_RESET, OnBtnReset)
ON_CBN_SELCHANGE (IDC_CMB_CB_ID_TYPE, OnSelchangeCmbCbIdType)
ON_CBN_SELCHANGE (IDC_CMB_ID_TYPE, OnSelchangeCmbIdType)
ON_MESSAGE (UM_OPENBANKSEARCH, OpenBankListDlg)
ON_BN_CLICKED( IDC_BTN_HISTORICAL, OnBtnHistorical )
ON_BN_CLICKED(IDC_RB_ACCT_BANKING, OnChkAcctBanking)
ON_BN_CLICKED(IDC_RB_SHR_BANKING, OnChkShrBanking)
//}}AFX_MSG_MAP
END_MESSAGE_MAP ()


//******************************************************************************
BOOL BankInstructionsDlg::OnInitDialog () 
{
   TRACE_METHOD (CLASSNAME, ONINITDIALOG);
   BaseMainDlg::OnInitDialog ();
   //For the To buttons use a slightly smaller Font
   m_pFont = new CFont;
   if (m_pFont)
   {
      CString strFaceName ("MS Sans Serif");

      m_pFont->CreatePointFont (8, strFaceName);
      GetDlgItem (IDC_BTN_TO)->SetFont (m_pFont);
   }
   return (TRUE);  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}

//******************************************************************************
SEVERITY BankInstructionsDlg::doInit ()
{
   getParameter ( USER_ACCESS_CODE, 
                  m_strUserAccessCode);

   getParameter ( MFCAN_IP_PARAM::SELECTION_KEY, 
                  m_dstrBankInstructionsListSelectionKey);

   getParameter ( MFCAN_IP_PARAM::SPONSORDESC, 
                  m_fundSponsorDesc);

   return NO_CONDITION;
}

//******************************************************************************
void BankInstructionsDlg::OnPostInitDialog ()
{
   TRACE_METHOD (CLASSNAME, I_ ("OnPostInitDialog"));
   m_bFromPostinitDlg = true;    

   //add controls
   AddListControl ( CLASSNAME, 
                    IDC_LV_BANK_INSTR, 
                    LV_BANK_INSTR, 
                    ifds::BankInstrHeadingSet, 
                    IFASTBP_PROC::BANK_INSTRUCTIONS_LIST, 
                    0, 
                    true);
   AddControl ( CTRL_COMBO, 
                IDC_BANK_INSTR_TYPE, 
                BF::NullContainerId, 
                ifds::BankInstrComboDefault, 
                CTRLFLAG_INITCOMBO_BY_SUB_LIST | CTRLFLAG_GUI_FIELD);
   AddControl ( CTRL_COMBO, 
                IDC_CMB_USE, 
                IFASTBP_PROC::BANK_INSTRUCTIONS_LIST, 
                ifds::AcctUseCode, 
                CTRLFLAG_INITCOMBO_BY_SUB_LIST | CTRLFLAG_AUTO_UPDATE_ON_CHANGE, 
                IDC_LV_BANK_INSTR);
   AddControl ( CTRL_COMBO, 
                IDC_CMB_ID_TYPE, 
                IFASTBP_PROC::BANK_INSTRUCTIONS_LIST, 
                ifds::BankIdType, 
                CTRLFLAG_INITCOMBO_BY_SUB_LIST, 
                IDC_LV_BANK_INSTR);
   AddControl ( CTRL_EDIT, 
                IDC_EDT_ID_NUMBER, 
                IFASTBP_PROC::BANK_INSTRUCTIONS_LIST, 
                ifds::BankIdValue, 
                0, 
                IDC_LV_BANK_INSTR);
   AddControl ( CTRL_EDIT, 
                IDC_EDT_INST_NBR, 
                IFASTBP_PROC::BANK_INSTRUCTIONS_LIST, 
                ifds::BankIdValue, 
                0, 
                IDC_LV_BANK_INSTR);
   AddControl ( CTRL_EDIT, 
                IDC_EDT_TRANSIT_NBR, 
                IFASTBP_PROC::BANK_INSTRUCTIONS_LIST, 
                ifds::TransitNo, 
                0, 
                IDC_LV_BANK_INSTR);
   AddControl ( CTRL_EDIT, 
                IDC_EDT_BANK_NAME, 
                IFASTBP_PROC::BANK_INSTRUCTIONS_LIST, 
                ifds::InstName, 
                0, 
                IDC_LV_BANK_INSTR);
   AddControl ( CTRL_EDIT, 
                IDC_EDT_BANK_ADDRESS, 
                IFASTBP_PROC::BANK_INSTRUCTIONS_LIST, 
                ifds::BankAddr,
                CTRLFLAG_FIELDS_FROM_SUB_LIST, 
                IDC_LV_BANK_INSTR);
   AddControl ( CTRL_EDIT, 
                IDC_EDIT_POSTAL, 
                IFASTBP_PROC::BANK_INSTRUCTIONS_LIST, 
                ifds::BankPostal, 
                0, 
                IDC_LV_BANK_INSTR);
   AddControl ( CTRL_COMBO, 
                IDC_COMBO_COUNTRY, 
                IFASTBP_PROC::BANK_INSTRUCTIONS_LIST, 
                ifds::BankCountry, 
                CTRLFLAG_INITCOMBO_BY_SUB_LIST, 
                IDC_LV_BANK_INSTR);
   AddControl ( CTRL_EDIT, 
                IDC_EDT_ACC_NBR, 
                IFASTBP_PROC::BANK_INSTRUCTIONS_LIST, 
                ifds::BankAcctNum, 
                0, 
                IDC_LV_BANK_INSTR);
   AddControl ( CTRL_EDIT, 
                IDC_EDT_ACC_NAMES, 
                IFASTBP_PROC::BANK_INSTRUCTIONS_LIST, 
                ifds::BankAcctName, 
                0, 
                IDC_LV_BANK_INSTR);
   AddControl ( CTRL_COMBO, 
                IDC_CMB_CB_ID_TYPE, 
                IFASTBP_PROC::BANK_INSTRUCTIONS_LIST, 
                ifds::BankIdTypeCB, 
                CTRLFLAG_INITCOMBO_BY_SUB_LIST | CTRLFLAG_INITCOMBO_WITH_BLANK, 
                IDC_LV_BANK_INSTR);
   AddControl ( CTRL_EDIT, 
                IDC_EDT_CB_ID_NUMBER, 
                IFASTBP_PROC::BANK_INSTRUCTIONS_LIST, 
                ifds::BankIdValueCB, 
                0, 
                IDC_LV_BANK_INSTR
              );
   AddControl ( CTRL_EDIT, 
                IDC_EDT_CB_INST_NBR, 
                IFASTBP_PROC::BANK_INSTRUCTIONS_LIST, 
                ifds::BankIdValueCB, 
                0, 
                IDC_LV_BANK_INSTR);
   AddControl ( CTRL_EDIT, 
                IDC_EDT_CB_TRANSIT_NBR, 
                IFASTBP_PROC::BANK_INSTRUCTIONS_LIST, 
                ifds::TransitNoCB, 
                0, 
                IDC_LV_BANK_INSTR);
   AddControl ( CTRL_EDIT,  
                IDC_EDT_CB_NAME, 
                IFASTBP_PROC::BANK_INSTRUCTIONS_LIST, 
                ifds::InstNameCB, 
                0, 
                IDC_LV_BANK_INSTR);
   AddControl ( CTRL_EDIT, 
                IDC_EDT_CB_ADDRESS,  
                IFASTBP_PROC::BANK_INSTRUCTIONS_LIST, 
                ifds::BankAddrCB, 
                CTRLFLAG_FIELDS_FROM_SUB_LIST, 
                IDC_LV_BANK_INSTR);
   AddControl ( CTRL_EDIT, 
                IDC_EDIT_POSTAL_CB, 
                IFASTBP_PROC::BANK_INSTRUCTIONS_LIST, 
                ifds::BankPostalCB, 
                0, 
                IDC_LV_BANK_INSTR);
   AddControl ( CTRL_COMBO, 
                IDC_COMBO_COUNTRY_CB, 
                IFASTBP_PROC::BANK_INSTRUCTIONS_LIST, 
                ifds::BankCountryCB, 
                CTRLFLAG_INITCOMBO_BY_SUB_LIST, 
                IDC_LV_BANK_INSTR);
   AddControl ( CTRL_EDIT, 
                IDC_EDT_FFC, 
                IFASTBP_PROC::BANK_INSTRUCTIONS_LIST, 
                ifds::FFC, 
                0, 
                IDC_LV_BANK_INSTR);
   AddControl ( CTRL_EDIT, 
                IDC_EDT_INSTRUCTIONS, 
                IFASTBP_PROC::BANK_INSTRUCTIONS_LIST, 
                ifds::PayReason, 
                CTRLFLAG_FIELDS_FROM_SUB_LIST, 
                IDC_LV_BANK_INSTR);
//the options grid
   AddGrid ( CLASSNAME, 
             IDC_GRD_OPTIONS, 
             GR_BANK_OPTIONS, 
             IFASTBP_PROC::BANK_INSTRUCTIONS_LIST, 
             IDC_LV_BANK_INSTR, 
             ifds::BankOptionsHeadingSet, 
             ifds::BankOptionsFieldsHeadingSet);

   DSTGridWnd *grdWnd = GetGrid (IDC_GRD_OPTIONS);
   CGXGridParam* cgxParam = grdWnd->GetParam ();

   grdWnd->setUseCBOSubstitutions ();
   grdWnd->GetParam ()->EnableTrackRowHeight (0);
   grdWnd->SetRowHeight (0,39,20);
   cgxParam->EnableMoveRows (FALSE);
   cgxParam->EnableMoveCols (FALSE);
   addBtnAddForPermissionCheck (IDC_BTN_ADD, IDC_LV_BANK_INSTR);
   addBtnDeleteForPermissionCheck (IDC_BTN_DEL, IDC_LV_BANK_INSTR);  
   DString dstrBankingInstrType;
   getParent()->getField(this,IFASTBP_PROC::BANK_INSTRUCTIONS_LIST, ifds::BankInstrType, dstrBankingInstrType);
   if( BANKTYPE::ACCOUNT == dstrBankingInstrType || BANKTYPE::SHAREHOLDER == dstrBankingInstrType) 
      setDefaultFilterForBankingInstrLevel();     
   else 
       m_bShrBank = -1;     
   doRefresh (this, NULL);   
   m_bFromPostinitDlg = false;
}

//******************************************************************************
bool BankInstructionsDlg::doRefresh ( GenericInterface * rpGICaller, 
                                      const I_CHAR * szOriginalCommand)
{
   DString bankInstrType;
 

   getParent ()->getField ( this, 
                            IFASTBP_PROC::BANK_INSTRUCTIONS_LIST, 
                            ifds::BankInstrType, 
                            bankInstrType);

   if (bankInstrType == BANKTYPE::BROKER)
   {
      ReInitControl (IDC_BANK_INSTR_TYPE, BF::NullContainerId, ifds::BankInstrComboBroker);
   }
   else if (bankInstrType == BANKTYPE::BRANCH)
   {
      ReInitControl (IDC_BANK_INSTR_TYPE, BF::NullContainerId, ifds::BankInstrComboBranch);
   }
   else if (bankInstrType == BANKTYPE::SALESREP)
   {
      ReInitControl (IDC_BANK_INSTR_TYPE, BF::NullContainerId, ifds::BankInstrComboSlsRep);
   }
   else if (bankInstrType == BANKTYPE::TRANSACTION)
   {
      ReInitControl (IDC_BANK_INSTR_TYPE, BF::NullContainerId, ifds::BankInstrComboTransaction);
   }
   else if (bankInstrType == BANKTYPE::PENDING_TRADE)
   {
      ReInitControl (IDC_BANK_INSTR_TYPE, BF::NullContainerId, ifds::BankInstrComboPendingTransaction);     
   }
   else if (bankInstrType == BANKTYPE::MATURITY_INSTRUCTIONS)
   {
      ReInitControl (IDC_BANK_INSTR_TYPE, BF::NullContainerId, ifds::BankInstrComboMaturityInterest);     
   }
   else if (bankInstrType == BANKTYPE::ACCOUNT_COMMITMENT)
   {
      ReInitControl (IDC_BANK_INSTR_TYPE, BF::NullContainerId, ifds::BankInstrComboAccountCommitment);     
   }
   else if (bankInstrType == BANKTYPE::CONTRACTMAT_INSTRUCTIONS)
   {
      ReInitControl (IDC_BANK_INSTR_TYPE, BF::NullContainerId, ifds::BankInstrComboContMatInstr);
   }
   else if (bankInstrType == BANKTYPE::TRADE)
   {
      DString tradesTransType;

      getParent ()->getField ( this, 
                               IFASTBP_PROC::BANK_INSTRUCTIONS_LIST,
                               ifds::TradesTransType, 
                               tradesTransType, 
                               false);
      if (tradesTransType == TRADETYPE::ADMIN_FEE)
      {
         ReInitControl (IDC_BANK_INSTR_TYPE, BF::NullContainerId, ifds::BankInstrComboAdminFee);
      }
      else
      {
         DString payToEntity;

         getParent ()->getField ( this, 
                                 IFASTBP_PROC::BANK_INSTRUCTIONS_LIST,
                                 ifds::PayToEntity, 
                                 payToEntity, 
                                 false);
         if (payToEntity == PAY_TO::BROKER)
         {
            ReInitControl (IDC_BANK_INSTR_TYPE, BF::NullContainerId, ifds::BankInstrComboTradeBroker);
         }
         else if (payToEntity == PAY_TO::BRANCH)
         {
            ReInitControl (IDC_BANK_INSTR_TYPE, BF::NullContainerId, ifds::BankInstrComboTradeBranch);
         }
         else if (payToEntity == PAY_TO::SALESREP)
         {
            ReInitControl (IDC_BANK_INSTR_TYPE, BF::NullContainerId, ifds::BankInstrComboTradeSlsrep);
         }
         else
         {
            ReInitControl (IDC_BANK_INSTR_TYPE, BF::NullContainerId, ifds::BankInstrComboTrade);
         }
      }
   }
   else if (bankInstrType == BANKTYPE::CLIENT)
   {
      ReInitControl (IDC_BANK_INSTR_TYPE, BF::NullContainerId, ifds::BankInstrComboClient);
   }
   else if (bankInstrType == BANKTYPE::FUND)
   {
      ReInitControl (IDC_BANK_INSTR_TYPE, BF::NullContainerId, ifds::BankInstrComboFund);
   }
   else if (bankInstrType == BANKTYPE::FUND_CLASS) 
   {
      ReInitControl (IDC_BANK_INSTR_TYPE, BF::NullContainerId, ifds::BankInstrComboFundClass);
   }
   else if (bankInstrType == BANKTYPE::SETTLEMENT)
   {
      DString payInstructExists;

      getParent ()->getField ( this, 
                               IFASTBP_PROC::BANK_INSTRUCTIONS_LIST,
                               ifds::PayInstructExists, 
                               payInstructExists, 
                               false);
      if ( payInstructExists.strip().upperCase() == I_("Y") )
      {
         DString payToEntity;

         getParent ()->getField ( this, 
                                  IFASTBP_PROC::BANK_INSTRUCTIONS_LIST,
                                  ifds::PayToEntity, 
                                  payToEntity, 
                                  false);

         if (payToEntity == PAY_TO::BROKER)
         {
            ReInitControl (IDC_BANK_INSTR_TYPE, BF::NullContainerId, ifds::BankInstrComboSettlementBroker);
         }
         else if (payToEntity == PAY_TO::BRANCH)
         {
            ReInitControl (IDC_BANK_INSTR_TYPE, BF::NullContainerId, ifds::BankInstrComboSettlementBranch);
         }
         else if (payToEntity == PAY_TO::SALESREP)
         {
            ReInitControl (IDC_BANK_INSTR_TYPE, BF::NullContainerId, ifds::BankInstrComboSettlementSlsrep);
         }
         else
         {
            ReInitControl (IDC_BANK_INSTR_TYPE, BF::NullContainerId, ifds::BankInstrComboSettlement);
         }
      }
      else
      {
         ReInitControl (IDC_BANK_INSTR_TYPE, BF::NullContainerId, ifds::BankInstrComboSettlement);
      }
   }
   else if (bankInstrType == BANKTYPE::DIRECT_TRADING)
   {
      ReInitControl (IDC_BANK_INSTR_TYPE, BF::NullContainerId, ifds::BankInstrComboDirectTrading);
   }
   else if (bankInstrType == BANKTYPE::FUND_GROUP)
   {
      ReInitControl (IDC_BANK_INSTR_TYPE, BF::NullContainerId, ifds::BankInstrComboFundGroup);
   }
   else if (bankInstrType == BANKTYPE::FUND_SPONSOR)
   {
      ReInitControl (IDC_BANK_INSTR_TYPE, BF::NullContainerId, ifds::BankInstrComboFundSponsor);
   }
   else if (bankInstrType == BANKTYPE::REG_AGENT)
   { 
	   ReInitControl (IDC_BANK_INSTR_TYPE, BF::NullContainerId, ifds::BankInstrComboRegAgent);
   }
   else //check whether the account we have is RRIF account
   {      
      DString dstrIsRRIFAccount;

      getParent ()->getField ( this, 
                               IFASTBP_PROC::BANK_INSTRUCTIONS_LIST, 
                               ifds::IsRRIFAccount, 
                               dstrIsRRIFAccount);
      if (dstrIsRRIFAccount == I_ ("N"))
      {
         if( 0 == m_bShrBank)
            ReInitControl ( IDC_BANK_INSTR_TYPE, BF::NullContainerId, ifds::BankInstrComboDefaultNoRRIF);
         if( 1 == m_bShrBank)
             ReInitControl ( IDC_BANK_INSTR_TYPE, BF::NullContainerId, ifds::BankInstrComboDefaultNoRRIFAcct);
      }
   }

   // display caption
   SetDlgCaption ();
   LoadListControl ( IDC_LV_BANK_INSTR, 
                     &m_dstrBankInstructionsListSelectionKey);
   ConnectControlToData (IDC_BANK_INSTR_TYPE, true); 
   LoadControl (IDC_BANK_INSTR_TYPE); 
   //check what happened after filtering
   if ( BANKTYPE::SHAREHOLDER == bankInstrType ||
        BANKTYPE::ACCOUNT     == bankInstrType )
   {
      DSTListCtrl *pPIDSTListCtrl = GetList(IDC_LV_BANK_INSTR);

      if (pPIDSTListCtrl)
      {
         if (pPIDSTListCtrl->GetItemCount() <= 0)
         {
            //add a new row if list is empty, to simulate
            //the normal behaviour
            AddToListControl (IDC_LV_BANK_INSTR);
         }
         m_bShrDummyList_Added  = BANKTYPE::SHAREHOLDER == bankInstrType;
         m_bAcctDummyList_Added = BANKTYPE::ACCOUNT     == bankInstrType;
      }
   }
   if(1 == m_bShrBank)
      ((CButton* )GetDlgItem(IDC_RB_ACCT_BANKING))->SetCheck( 1 );
   if(0 == m_bShrBank)
      ((CButton* )GetDlgItem(IDC_RB_SHR_BANKING))->SetCheck( 1 );
   return true;
}

//******************************************************************************
void BankInstructionsDlg::SetToBtnCaption (const DString& dstrBankType)
{
   CString cstrBtnCaption;
   cstrBtnCaption.LoadString (TXT_TO_BTN_CAPTION);
   
   
   DString btnCaption (cstrBtnCaption.GetBuffer (0)), 
      caller;

   getParent ()->getField ( this, 
                            ifds::CallerName, 
                            caller
                          );
   {
	   btnCaption = btnCaption + I_ (":") + caller;
   }
   GetDlgItem (IDC_BTN_TO)->SetWindowText (btnCaption.c_str ());
}

//******************************************************************************
void BankInstructionsDlg::SetDlgCaption ()
{
   DString bankInstrType, 
      caption;

   getParent ()->getField ( this, 
                            IFASTBP_PROC::BANK_INSTRUCTIONS_LIST,
                            ifds::BankInstrType, 
                            bankInstrType
                          );
   if ( bankInstrType == BANKTYPE::SHAREHOLDER ||
        bankInstrType == BANKTYPE::ACCOUNT ||
        bankInstrType == BANKTYPE::DIRECT_TRADING ||
        bankInstrType == BANKTYPE::RRIF ||
        bankInstrType == BANKTYPE::TRADE ||
        bankInstrType == BANKTYPE::DISTRIBUTION ||
        bankInstrType == BANKTYPE::SYSTEMATIC   ||
        bankInstrType == BANKTYPE::TRANSACTION  ||
        bankInstrType == BANKTYPE::PENDING_TRADE ||
        bankInstrType == BANKTYPE::SETTLEMENT ||
        bankInstrType == BANKTYPE::MATURITY_INSTRUCTIONS ||
        bankInstrType == BANKTYPE::ACCOUNT_COMMITMENT ||
		bankInstrType == BANKTYPE::CONTRACTMAT_INSTRUCTIONS
      )
   {
      DString dstAcctNum, 
         dstShrNum, 
         dstEntityName;

      getParent ()->getField ( this, 
                               IFASTBP_PROC::BANK_INSTRUCTIONS_LIST, 
                               ifds::AccountNum, 
                               dstAcctNum
                             );
      getParent ()->getField ( this, 
                               IFASTBP_PROC::BANK_INSTRUCTIONS_LIST, 
                               ifds::ShrNum, 
                               dstShrNum
                             );
      getParent ()->getField ( this, 
                               IFASTBP_PROC::BANK_INSTRUCTIONS_LIST, 
                               ifds::Name, 
                               dstEntityName
                             );
      SetShrAcctCaption (dstShrNum, dstAcctNum, dstEntityName);
//already set the caption, just return here
      return;
   }
   else if ( bankInstrType == BANKTYPE::BROKER ||
             bankInstrType == BANKTYPE::BRANCH ||
             bankInstrType == BANKTYPE::SALESREP
           )
   {
      DString dstBroker, dstBranch, dstSlsRep;

      getParent ()->getField ( this, 
                               IFASTBP_PROC::BANK_INSTRUCTIONS_LIST, 
                               ifds::BrokerCode, 
                               dstBroker
                             );
	  CString cstrBrkr;
	  cstrBrkr.LoadString(TXT_BROKER_TXT);
	  caption += DString(cstrBrkr);;
      caption += dstBroker;
      if ( bankInstrType == BANKTYPE::BRANCH ||
           bankInstrType == BANKTYPE::SALESREP
         )
      {
         getParent ()->getField ( this, 
                                  IFASTBP_PROC::BANK_INSTRUCTIONS_LIST, 
                                  ifds::BranchCode, 
                                  dstBranch
                                );
	 CString cstrBranch;
	 cstrBranch.LoadString(TXT_BRANCH_TXT);
	 caption+=DString(cstrBranch);
         caption += dstBranch;
         if (bankInstrType == BANKTYPE::SALESREP)
         {
            getParent ()->getField ( this, 
                                     IFASTBP_PROC::BANK_INSTRUCTIONS_LIST, 
                                     ifds::SalesRepCode, 
                                     dstSlsRep
                                   );
			CString cstrSalesRep;
			cstrSalesRep.LoadString(TXT_SALES_REP);
            
			caption+=DString(cstrSalesRep);
            caption += dstSlsRep;
         }
      }
   }
   else if ( bankInstrType == BANKTYPE::FUND || 
             bankInstrType == BANKTYPE::FUND_CLASS
           )
   {
      DString strFundCode, strFundName;

      getParent ()->getField ( this, 
                               IFASTBP_PROC::BANK_INSTRUCTIONS_LIST, 
                               ifds::FundCode, 
                               strFundCode
                             );
      dynamic_cast <DSTCWorkSession *> (getBFWorkSession ())->
            getFundName (strFundCode, strFundName);
		
	  CString cstrFundcode;
	  cstrFundcode.LoadString(TXT_FUND_CODE);
	  caption+=DString(cstrFundcode);

	  
      caption += strFundCode;
     
		CString cstrFundName;
		cstrFundName.LoadString(TXT_FUND_NAME);
		caption+=DString(cstrFundName);

      caption += strFundName;
   }
   else if (bankInstrType == BANKTYPE::CLIENT)
   {
      
	   CString cstrClient;
	   cstrClient.LoadString(TXT_CLIENT);
	   caption+=DString(cstrClient);
   }
   else if (bankInstrType == BANKTYPE::FUND_GROUP)
   {
      DString dstrFundGroup;

      getParent ()->getField (this, IFASTBP_PROC::BANK_INSTRUCTIONS_LIST, ifds::FundGroup, dstrFundGroup);
      
	  CString cstrFundGroup;
	  cstrFundGroup.LoadString(TXT_FUND_GROUP);
	  caption+=DString(cstrFundGroup);
      caption += dstrFundGroup;
    }
   else if (bankInstrType == BANKTYPE::FUND_SPONSOR)
   {
      DString dstrFundSponsor;

      //getParent ()->getField (this, IFASTBP_PROC::BANK_INSTRUCTIONS_LIST, ifds::FundGroup, dstrFundSponsor);
      
	  CString cstrFundSponsor;
		cstrFundSponsor.LoadString(TXT_FUND_SPONSOR);
		caption+=DString(cstrFundSponsor);

      caption += m_fundSponsorDesc;
    }
   else if (bankInstrType == BANKTYPE::REG_AGENT)
   {
	   DString dstrRegAgent;
	   CString cstrRegAgent;
	   getParent()->getField (this, IFASTBP_PROC::BANK_INSTRUCTIONS_LIST, ifds::RegAgent, dstrRegAgent);
	   cstrRegAgent.LoadString(TXT_REG_AGENT);
	   caption+=DString(cstrRegAgent);
	   caption+=dstrRegAgent;
   }
   SetCaption (caption);
}

//******************************************************************************
void BankInstructionsDlg::OnBtnAdd () 
{
   setParameter( I_("SetFromGUI"), NULL_STRING ); 
   if( 0 == m_bShrBank ) //Shrholder bank addition
    {
     getParent()->setField(this, IFASTBP_PROC::BANK_INSTRUCTIONS_LIST, ifds::BankInstrType, BANKTYPE::SHAREHOLDER, false);
    }
   if( 1 == m_bShrBank ) //Account bank addition
      getParent()->setField(this, IFASTBP_PROC::BANK_INSTRUCTIONS_LIST, ifds::BankInstrType, BANKTYPE::ACCOUNT, false);
  
   //ConnectControlsToData(IDC_BANK_INSTR_TYPE);
   AddToListControl (IDC_LV_BANK_INSTR);
}

//******************************************************************************
void BankInstructionsDlg::OnBtnDel () 
{
   setParameter( I_("SetFromGUI"), NULL_STRING ); 
   if( 0 == m_bShrBank ) //Shrholder bank delete
      getParent()->setField(this, IFASTBP_PROC::BANK_INSTRUCTIONS_LIST, ifds::BankInstrType, BANKTYPE::SHAREHOLDER, false);
   if( 1 == m_bShrBank ) //Account bank delete
      getParent()->setField(this, IFASTBP_PROC::BANK_INSTRUCTIONS_LIST, ifds::BankInstrType, BANKTYPE::ACCOUNT, false);

   DeleteFromListControl (IDC_LV_BANK_INSTR);
}

//******************************************************************************
void BankInstructionsDlg::OnBtnTo () 
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTGUI_CONDITION, CLASSNAME, I_ ("OnBtnTo ()"));

   if (getParent ()->send (this, CLONE))
   {
      DString caller;

      getParent ()->getField ( this, 
                               IFASTBP_PROC::BANK_INSTRUCTIONS_LIST,
                               ifds::CallerName, 
                               caller);
      getParent ()->setField ( this, 
                               ifds::BankInstrType, 
                               caller, 
                               false);
      LoadControl (IDC_BANK_INSTR_TYPE);
      LoadListControl (IDC_LV_BANK_INSTR);
      SetToBtnCaption (caller);
   }
   else 
   {
      // Display error
      ConditionMessageBox (FRAMEBELOW (), GETHIGHESTSEVERITY ());
   }
}

//******************************************************************************
void BankInstructionsDlg::OnBtnReset () 
{
   ResetListItem (IDC_LV_BANK_INSTR);
   LoadListControl (IDC_LV_BANK_INSTR);
   showFields ();
   showCBFields ();
}

//******************************************************************************
void BankInstructionsDlg::OnBtnAdmDates () 
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTGUI_CONDITION, 
                           CLASSNAME, I_ ("OnBtnAdmDates ()")
                         );

   ShowAdminDates (IFASTBP_PROC::BANK_INSTRUCTIONS_LIST);
}

//******************************************************************************
BOOL BankInstructionsDlg::PreTranslateMessage (MSG* pMsg) 
{

   if (pMsg->message == WM_KEYDOWN && (int) (pMsg->wParam) == VK_F4 && 
         !IsSelectedCtrlUpdateable ())
   {
      return TRUE;
   }

   if (pMsg->message == WM_KEYDOWN && (int) (pMsg->wParam) == VK_F4)
   {
      CWnd * cwndFocus = GetFocus ();
      int focusCtrlId = 0;

      if (cwndFocus)
      {
         focusCtrlId = cwndFocus->GetDlgCtrlID ();
         if (focusCtrlId == IDC_EDT_ID_NUMBER || 
             focusCtrlId == IDC_EDT_INST_NBR || 
             focusCtrlId == IDC_EDT_CB_ID_NUMBER || 
             focusCtrlId == IDC_EDT_CB_INST_NBR ||
             focusCtrlId == IDC_EDT_TRANSIT_NBR ||
             focusCtrlId == IDC_EDT_CB_TRANSIT_NBR)
         {
            PostMessage (UM_OPENBANKSEARCH, focusCtrlId);
         }
      }
   }
   return BaseMainDlg::PreTranslateMessage (pMsg);
}

//******************************************************************************
LRESULT BankInstructionsDlg::OpenBankListDlg (WPARAM wparam, LPARAM)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTGUI_CONDITION, CLASSNAME, I_ ("OpenBankListDlg"));
   CWaitCursor wait;
   
   try
   {
      BFFieldId idBankIdType = ifds::NullFieldId;
      bool transitSearch = wparam == IDC_EDT_TRANSIT_NBR || 
         wparam == IDC_EDT_CB_TRANSIT_NBR;

      if (wparam == IDC_EDT_ID_NUMBER || wparam == IDC_EDT_INST_NBR ||
         wparam == IDC_EDT_TRANSIT_NBR)
      {
         idBankIdType = ifds::BankIdType;
      }
      else if (wparam == IDC_EDT_CB_ID_NUMBER || wparam == IDC_EDT_CB_INST_NBR ||
         wparam == IDC_EDT_CB_TRANSIT_NBR)
      {
         idBankIdType = ifds::BankIdTypeCB;
      }
      DString dstrBankType;

      getParent ()->getField (this, IFASTBP_PROC::BANK_INSTRUCTIONS_LIST,
         idBankIdType, dstrBankType, false);
      dstrBankType.strip ();
      transitSearch ? setParameter (I_ ("FICategory"), FI_CATEGORY::BANK_TRANSIT) :
         setParameter (I_ ("FICategory"), FI_CATEGORY::BANK);
      setParameter (I_ ("FIType"), dstrBankType);
      
      if (transitSearch)
      {
         CString instCode;
         DString dstrInstCode;

//get the institution number
         if (wparam == IDC_EDT_TRANSIT_NBR)
         {
            GetControlText (IDC_EDT_INST_NBR, dstrInstCode);
         }
         else if (wparam == IDC_EDT_CB_TRANSIT_NBR)
         {
            GetControlText (IDC_EDT_CB_INST_NBR, dstrInstCode);
         }
         setParameter (I_ ("FICode"), dstrInstCode);
      }
      switch (getParentProcess ()->invokeProcessFromChild (this, 
         CMD_BPROC_FINANCIAL_INSTITUTION_SEARCH, PROC_SUPPORT))
      {
         case CMD_OK:
         case CMD_MODELESS_INPROCESS:
         {
            DString dstInstNo, 
               dstTransitNo;

            getParameter (I_("InstCode"), dstInstNo);
            getParameter (I_("TransitNo"), dstTransitNo);
            if (transitSearch)
            {
//set the institution number
               if (wparam == IDC_EDT_TRANSIT_NBR)
               {
                  SetControlText (IDC_EDT_INST_NBR, dstInstNo);
               }
               else if (wparam == IDC_EDT_CB_TRANSIT_NBR)
               {
                  GetControlText (IDC_EDT_CB_INST_NBR, dstInstNo);
               }
//set transit   
               SetControlText (wparam, dstTransitNo);
            }
            else
            {
               // Set the institution number
               SetControlText (wparam, dstInstNo);

            // Set transit
               if (wparam == IDC_EDT_INST_NBR)
               {
                  SetControlText (IDC_EDT_TRANSIT_NBR, dstTransitNo);
                  LoadControl (IDC_EDT_TRANSIT_NBR);
               }
               else if (wparam == IDC_EDT_CB_INST_NBR)
               {
                  GetControlText (IDC_EDT_CB_TRANSIT_NBR, dstTransitNo);
                  LoadControl (IDC_EDT_CB_TRANSIT_NBR);
               }	
            }
            LoadControl (wparam);

            break;
         }
         case CMD_CANCEL:
         {
            break;
         }
         default:
         {
            // Display error
            ConditionMessageBox (FRAMEBELOW (), GETHIGHESTSEVERITY ());
            break;
         }
      }
   }
   catch (ConditionException &ce)
   {
      ConditionMessageBox (ce);
   }
   catch (...)
   {
      DISPLAYCONDITIONFROMFILE (CND::GUI_ERR_UNKNOWN_EXCEPTION);
   }
   return 0;
}

//******************************************************************************
void BankInstructionsDlg::DoPreListItemChanged (UINT listControlID, 
   const DString &strKey, bool bIsNewItem, bool bIsDummyItem)
{
}

//******************************************************************************
void BankInstructionsDlg::DoListItemChanged (UINT listControlID, 
   const DString &strKey, bool bIsNewItem, bool bIsDummyItem)
{
   SetUserAccesFuncCode ();
   showCBFields ();
   showFields ();
   if( bIsNewItem )
   {
     DString dstrAcctNum;
     //getParent()->getField(this,IFASTBP_PROC::BANK_INSTRUCTIONS_LIST, ifds::AccountNum, dstrAcctNum, false);
     //getParent()->setField(this, IFASTBP_PROC::BANK_INSTRUCTIONS_LIST, ifds::rxAcctNum, dstrAcctNum, false); 
     if( m_bShrBank == 1  && !bIsDummyItem)
     {
       //getParent()->setField(this, IFASTBP_PROC::BANK_INSTRUCTIONS_LIST, ifds::BankInstrType, BANKTYPE::ACCOUNT, false); 
       getParent()->setField(this, IFASTBP_PROC::BANK_INSTRUCTIONS_LIST, ifds::rxBankingEntity, BANKENTITY::ACCOUNT, false); 
     }
     else if ( m_bShrBank == 0 && !bIsDummyItem)
     {
     // getParent()->setField(this, IFASTBP_PROC::BANK_INSTRUCTIONS_LIST, ifds::BankInstrType,BANKTYPE::SHAREHOLDER, false); 
      getParent()->setField(this, IFASTBP_PROC::BANK_INSTRUCTIONS_LIST, ifds::rxBankingEntity, BANKENTITY::SHAREHOLDER, false); 
     }
    }  
   // Historical Button
   GetDlgItem(IDC_BTN_HISTORICAL)->EnableWindow( m_bEnableHistory && !(bIsNewItem || bIsDummyItem) );
}

//******************************************************************************
bool BankInstructionsDlg::GetDataForControl ( UINT controlID,
                                              DString &strValueOut, 
                                              bool bFormatted, 
                                              int index
                                            ) const
{
   bool bReturn = false;
   strValueOut = NULL_STRING;

   switch (controlID)
   {
      case IDC_BANK_INSTR_TYPE:
      {
         getParent ()->getField ( this, 
                                  IFASTBP_PROC::BANK_INSTRUCTIONS_LIST, 
                                  ifds::BankInstrType, 
                                  strValueOut
                                );
         bReturn = true;
         break;
      }
      case IDC_EDT_ID_NUMBER:
      case IDC_EDT_INST_NBR:
         {
            DString dstrBankIDType;
            int nMaxLength, nAllMaxLength;
            bool bIsAllDigits;
            getParent ()->getField ( this, 
                                     IFASTBP_PROC::BANK_INSTRUCTIONS_LIST, 
                                     ifds::BankIdType, 
                                     dstrBankIDType, 
                                     false
                                   );

            if (FinancialInstitution::getBankIdNumInfo ( dstrBankIDType, 
                                                         nMaxLength, 
                                                         bIsAllDigits, 
                                                         nAllMaxLength
                                                        )
               )
            {
               if (bIsAllDigits)
               {
                  getParent ()->getField ( this, 
                                           IFASTBP_PROC::BANK_INSTRUCTIONS_LIST, 
                                           ifds::BankIdValue, 
                                           strValueOut, 
                                           false
                                         );
                  strValueOut.padLeft (nMaxLength, I_('0'));
                  bReturn = true;
               }
            }
            break;
         }
      case IDC_EDT_TRANSIT_NBR:
         {
            DString dstrBankIDType;
            int nMaxLength, nAllMaxLength;
            bool bIsAllDigits;
            getParent ()->getField ( this, 
                                     IFASTBP_PROC::BANK_INSTRUCTIONS_LIST, 
                                     ifds::BankIdType, 
                                     dstrBankIDType, 
                                     false
                                   );
            if ( FinancialInstitution::getBankTransitNumInfo ( dstrBankIDType, 
                                                               nMaxLength, 
                                                               bIsAllDigits, 
                                                               nAllMaxLength
                                                             )
               )
            {
               if (bIsAllDigits)
               {
                  getParent ()->getField ( this, 
                                           IFASTBP_PROC::BANK_INSTRUCTIONS_LIST, 
                                           ifds::TransitNo, 
                                           strValueOut, 
                                           false
                                         );
                  strValueOut.padLeft (nMaxLength, I_('0'));
                  bReturn = true;
               }
            }
            break;
         }
      default :
         break;
   }
   strValueOut.strip ();
   return bReturn;
}

//******************************************************************************
bool BankInstructionsDlg::SetDataFromControl ( UINT controlID,
                                               const DString &strValue, 
                                               bool bFormatted, 
                                               SEVERITY &sevRtn,
                                               int index
                                             )
{
   bool bReturn = false;

   sevRtn = NO_CONDITION;
   switch (controlID)
   {
      case IDC_BANK_INSTR_TYPE:
      
      {
         bool bIsBanking4AcctOrShr = ( BANKTYPE::SHAREHOLDER == strValue)  || ( BANKTYPE::ACCOUNT == strValue ) ;
         GetDlgItem(IDC_RB_ACCT_BANKING)->ShowWindow( bIsBanking4AcctOrShr );
         GetDlgItem(IDC_RB_SHR_BANKING)->ShowWindow ( bIsBanking4AcctOrShr );
         GetDlgItem(IDC_STC_BANKING_GRP)->ShowWindow( bIsBanking4AcctOrShr );
         if( ! bIsBanking4AcctOrShr ) 
         {
            m_bShrBank = -1;
            ((CButton* )GetDlgItem(IDC_RB_ACCT_BANKING))->SetCheck(0);
            ((CButton* )GetDlgItem(IDC_RB_SHR_BANKING))->SetCheck(0);            
         }
         else if( bIsBanking4AcctOrShr && (-1 == m_bShrBank))
         {
           DSTCWorkSession *dstWorkSession = dynamic_cast<DSTCWorkSession *>(getParent()->getBFWorkSession());
           DString dstrEnvLvlBanking;
           dstWorkSession->getOption ( ifds::BankingLevel, dstrEnvLvlBanking, getParent()->getDataGroupId(), false);
           DString dstrDefaultBankingLevel;
           if(dstWorkSession)
                dstWorkSession->getOption (ifds::DefaultBankingLevel, dstrDefaultBankingLevel, getParent()->getDataGroupId(), false);
           m_bShrBank = 0;
           if( BANKENTITY::ACCOUNT == dstrDefaultBankingLevel)
               m_bShrBank = 1; 
           //m_bShrDummyList_Added = false;
           //m_bAcctDummyList_Added = false;
         }
         if ( 0 == m_bShrBank )
             getParent ()->setField (this, ifds::BankInstrType, BANKTYPE::SHAREHOLDER );
         else if ( 1 == m_bShrBank  )
             getParent ()->setField (this, ifds::BankInstrType, BANKTYPE::ACCOUNT);
         else
             getParent ()->setField (this, ifds::BankInstrType, strValue);

         SetToBtnCaption (strValue);
//clear banking info
// Hack. DSTEdit::DoClear doesn't clear non-updateable control.
         GetDlgItem (IDC_EDT_BANK_NAME)->SetWindowText (NULL_STRING);   
         GetDlgItem (IDC_EDT_BANK_ADDRESS)->SetWindowText (NULL_STRING);
         GetDlgItem (IDC_EDIT_POSTAL)->SetWindowText (NULL_STRING);
         GetDlgItem (IDC_EDT_INST_NBR)->SetWindowText (NULL_STRING);
         GetDlgItem (IDC_EDT_TRANSIT_NBR)->SetWindowText (NULL_STRING);
         GetDlgItem (IDC_EDT_ACC_NBR)->SetWindowText (NULL_STRING);
         GetDlgItem (IDC_EDT_ACC_NAMES)->SetWindowText (NULL_STRING);
//clear correspondent info
// Hack. DSTEdit::DoClear doesn't clear non-updateable control.
         GetDlgItem (IDC_EDT_CB_NAME)->SetWindowText (NULL_STRING);
         GetDlgItem (IDC_EDT_CB_ADDRESS)->SetWindowText (NULL_STRING);
         GetDlgItem (IDC_EDIT_POSTAL_CB)->SetWindowText (NULL_STRING);
         GetDlgItem (IDC_EDT_CB_INST_NBR)->SetWindowText (NULL_STRING);
         GetDlgItem (IDC_EDT_CB_TRANSIT_NBR)->SetWindowText (NULL_STRING);
         LoadListControl (IDC_LV_BANK_INSTR);
         bReturn = true;
         break;
      }
      case IDC_EDT_ID_NUMBER:
      case IDC_EDT_INST_NBR:
         {
            DString dstrBankIDType;
            int nMaxLength, nAllMaxLength;
            bool bIsAllDigits;
            getParent ()->getField (this, IFASTBP_PROC::BANK_INSTRUCTIONS_LIST, 
               ifds::BankIdType, dstrBankIDType, false);

            if (FinancialInstitution::getBankIdNumInfo (dstrBankIDType, 
               nMaxLength, bIsAllDigits, nAllMaxLength))
            {
               if( bIsAllDigits )
               {
                  DString dstrPaddedValue( strValue );
                  dstrPaddedValue.padLeft( nMaxLength, I_('0') );
                  getParent ()->setField (this, IFASTBP_PROC::BANK_INSTRUCTIONS_LIST, 
                     ifds::BankIdValue, dstrPaddedValue, false);
                  bReturn = true;
               }
            }
            break;
         }
      case IDC_EDT_TRANSIT_NBR:
         {
            DString dstrBankIDType;
            int nMaxLength, nAllMaxLength;
            bool bIsAllDigits;
            getParent ()->getField (this, IFASTBP_PROC::BANK_INSTRUCTIONS_LIST, 
               ifds::BankIdType, dstrBankIDType, false);

            if (FinancialInstitution::getBankTransitNumInfo (dstrBankIDType, 
               nMaxLength, bIsAllDigits, nAllMaxLength))
            {
               if( bIsAllDigits )
               {
                  DString dstrPaddedValue( strValue );
                  dstrPaddedValue.padLeft( nMaxLength, I_('0') );
                  getParent ()->setField (this, IFASTBP_PROC::BANK_INSTRUCTIONS_LIST, 
                     ifds::TransitNo, dstrPaddedValue, false);
                  bReturn = true;
               }
            }
            break;
         }

      default :
         break;
   }
   return bReturn;
}

//******************************************************************************
void BankInstructionsDlg::showControl (int ctrlId, bool show)
{
   CWnd * ptr = NULL;

   ptr = GetDlgItem (ctrlId);
   ptr->ShowWindow (show ? SW_SHOW : SW_HIDE);
   ptr->EnableWindow (show);
}

//******************************************************************************
void BankInstructionsDlg::showFields ()
{
   DString dstBankIDType (NULL_STRING);
   getParent ()->getField ( this, 
                            IFASTBP_PROC::BANK_INSTRUCTIONS_LIST, 
                            ifds::BankIdType, dstBankIDType, false);
   CString str;
   bool bTwoIDControls = FinancialInstitution::hasTransits (FI_CATEGORY::BANK, dstBankIDType);
   if (dstBankIDType.strip () == I_ ("03") || dstBankIDType == I_ ("06"))
   {
//      bTwoIDControls = true;
      str.LoadString (IDS_LBL_INSTIT_NBR);
   }
   else if (dstBankIDType == I_ ("01"))
   {
//      bTwoIDControls = false;
      str.LoadString (IDS_LBL_ABA_NBR);
   }
   else if (dstBankIDType == I_ ("04"))
   {
//      bTwoIDControls = false;
      str.LoadString (IDS_LBL_SWIFT_CODE);
   }
   else if (dstBankIDType == I_ ("02") || dstBankIDType == I_ ("05") || 
            dstBankIDType == I_ ("07") || dstBankIDType == I_ ("08") || 
            dstBankIDType == I_ ("10") || dstBankIDType == I_ ("09") || 
			dstBankIDType == I_ ("20"))
   {
//      bTwoIDControls = false;
      str.LoadString (IDS_LBL_NBR);
   }
   else
   {
//      bTwoIDControls = false;
      str.LoadString (IDS_LBL_NBR);
   }

   showControl (IDC_TXT_TRANSIT, bTwoIDControls);
   ConnectControlToData (IDC_EDT_ID_NUMBER,   !bTwoIDControls, true);
   ConnectControlToData (IDC_EDT_INST_NBR,    bTwoIDControls,  true);
   ConnectControlToData (IDC_EDT_TRANSIT_NBR, bTwoIDControls,  true);


   DSTEdit *pEdit = NULL;
   int nMaxLength = 0;

   bool bIsAllDigits = false;
   DString strTemp;

   if (bTwoIDControls)
   {
      modifyControlStyle (dstBankIDType, IDC_EDT_INST_NBR);
      modifyControlStyle (dstBankIDType, IDC_EDT_TRANSIT_NBR);
      LoadControl (IDC_EDT_INST_NBR);
      LoadControl (IDC_EDT_TRANSIT_NBR);
   }
   else
   {
      modifyControlStyle (dstBankIDType, IDC_EDT_ID_NUMBER);
      LoadControl (IDC_EDT_ID_NUMBER);
   }

   modifyControlStyle (dstBankIDType, IDC_EDT_ACC_NBR);
   SetDlgItemText (IDC_TXT_ID_NUMBER, str);
}

//******************************************************************************
void BankInstructionsDlg::modifyControlStyle (const DString& dstBankIDType, UINT nID)
{
   DSTEdit *pEdit = NULL;
   int nMaxLength = 0;
   int nAllMaxLength = 0;
   bool bIsAllDigits = false;
   DString strTemp;
   BaseControl* pBaseControl = NULL;
   BFFieldId idField = ifds::NullFieldId;

   if (dstBankIDType.empty ())
      return;

   pBaseControl = GetControl (nID);
   idField = pBaseControl->GetFieldID (0);
   if ((idField == ifds::BankIdValue) || (idField == ifds::BankIdValueCB))
   {
      if (FinancialInstitution::getBankIdNumInfo (dstBankIDType, 
         nMaxLength, bIsAllDigits, nAllMaxLength))
      {
         pEdit = dynamic_cast<DSTEdit *> (pBaseControl);
         getParent ()->getField (this, IFASTBP_PROC::BANK_INSTRUCTIONS_LIST, 
            idField, strTemp, false);
         if (strTemp.strip ().empty ())
            pEdit->SetMaxCharNum (nMaxLength);
         else
            pEdit->SetMaxCharNum (nAllMaxLength);
         pEdit->SetAllDigits (bIsAllDigits);
      }
   }
   else if ((idField == ifds::TransitNo) || (idField == ifds::TransitNoCB))
   {
      if (FinancialInstitution::getBankTransitNumInfo (dstBankIDType, 
         nMaxLength, bIsAllDigits, nAllMaxLength))
      {
         pEdit = dynamic_cast<DSTEdit *> (pBaseControl);
         getParent ()->getField (this, IFASTBP_PROC::BANK_INSTRUCTIONS_LIST, 
            idField, strTemp, false);
         if (strTemp.strip ().stripLeading ('0').empty ())
            pEdit->SetMaxCharNum (nMaxLength);
         else
            pEdit->SetMaxCharNum (nAllMaxLength);
         pEdit->SetAllDigits (bIsAllDigits);
      }
   }
   else if ((idField == ifds::BankAcctNum) || (idField == ifds::BankIdValueCB))
   {
      if (FinancialInstitution::getBankAccNumInfo (dstBankIDType, 
         nMaxLength, bIsAllDigits, nAllMaxLength))
      {
         pEdit = dynamic_cast<DSTEdit *> (pBaseControl);
         getParent ()->getField (this, IFASTBP_PROC::BANK_INSTRUCTIONS_LIST, 
            idField, strTemp, false);
         if (strTemp.strip ().empty ())
            pEdit->SetMaxCharNum (nMaxLength);
         else
            pEdit->SetMaxCharNum (nAllMaxLength);
         pEdit->SetAllDigits (bIsAllDigits);
      }
   }
}

//******************************************************************************
void BankInstructionsDlg::showCBFields ()
{
   DString dstBankIDType (NULL_STRING);
   CString str;
   getParent ()->getField (this, IFASTBP_PROC::BANK_INSTRUCTIONS_LIST, 
      ifds::BankIdTypeCB, dstBankIDType, false);
   bool bTwoIDControls = false;
   if (dstBankIDType.strip () == I_ ("03") || dstBankIDType == I_ ("06"))
   {
      bTwoIDControls = true;
      str.LoadString (IDS_LBL_INSTIT_NBR);
   }
   else if (dstBankIDType == I_ ("01"))
   {
      bTwoIDControls = false;
      str.LoadString (IDS_LBL_ABA_NBR);
   }
   else if (dstBankIDType == I_ ("04"))
   {
      bTwoIDControls = false;
      str.LoadString (IDS_LBL_SWIFT_CODE);
   }
   else if (dstBankIDType == I_ ("02") || dstBankIDType == I_ ("05") || 
            dstBankIDType == I_ ("07") || dstBankIDType == I_ ("08") || 
            dstBankIDType == I_ ("10") || dstBankIDType == I_ ("09") || 
			dstBankIDType == I_ ("20"))
   {
      bTwoIDControls = false;
      str.LoadString (IDS_LBL_NBR);
   }
   else
   {
      bTwoIDControls = false;
      str.LoadString (IDS_LBL_NBR);
   }

   showControl (IDC_TXT_CB_TRANSIT, bTwoIDControls);
   ConnectControlToData (IDC_EDT_CB_ID_NUMBER,   !bTwoIDControls, true);
   ConnectControlToData (IDC_EDT_CB_INST_NBR,    bTwoIDControls,  true);
   ConnectControlToData (IDC_EDT_CB_TRANSIT_NBR, bTwoIDControls,  true);

   DSTEdit *pEdit = NULL;
   int nMaxLength = 0;
   bool bIsAllDigits = false;

   if (bTwoIDControls)
   {
      modifyControlStyle (dstBankIDType, IDC_EDT_CB_INST_NBR);
      modifyControlStyle (dstBankIDType, IDC_EDT_CB_TRANSIT_NBR);
      LoadControl (IDC_EDT_CB_INST_NBR);
      LoadControl (IDC_EDT_CB_TRANSIT_NBR);
   }
   else
   {
      modifyControlStyle (dstBankIDType, IDC_EDT_CB_ID_NUMBER);
      LoadControl (IDC_EDT_CB_ID_NUMBER);
   }

   SetDlgItemText (IDC_TXT_CB_ID_NUMBER, str);
}

//******************************************************************************
void BankInstructionsDlg::GetCellProperties ( UINT ctrlId, 
                                              const DString &rowKey, 
                                              const DString &colKey, 
                                              BFContainerId &idContainer,
                                              BFFieldId &fieldId,
                                              DString &listItemKey,
                                              int &nCellState,
                                              UINT &cellCtrlType, 
                                              int &nCtrlInitMode,
                                              BFFieldId &substitutionId,
                                              DString &comboList, 
                                              DString &mask,
                                              int& nComboSortingMode,
                                              DString& dstrAllowedChar)	 
{
   dstrAllowedChar = NULL_STRING;
   if (colKey  == _T ("Options"))
   {
      nCellState  = DSTGridWnd::CELL_STATE::SKIPPED;
   }
   else if (colKey  == _T ("Value"))
   {
      DString bankInstrType, strAcctUseCode;

      getParent ()->getField ( this, 
                              IFASTBP_PROC::BANK_INSTRUCTIONS_LIST, 
                              ifds::BankInstrType, 
                              bankInstrType );
                             
      getParent()->getField ( this, 
                              IFASTBP_PROC::BANK_INSTRUCTIONS_LIST, 
                              ifds::AcctUseCode, 
                              strAcctUseCode,
                              false );

      strAcctUseCode.strip().upperCase();   
      if (rowKey == _T ("BankAcctType"))
      {
         idContainer       = IFASTBP_PROC::BANK_INSTRUCTIONS_LIST;
         fieldId           = ifds::BankAcctType;
         substitutionId    = ifds::BankAcctType;
         
         if (strAcctUseCode == AcctUseCode::DIRECT_DEPOSIT && 
             bankInstrType  == BANKTYPE::TRADE)
         {
            nCellState     = DSTGridWnd::CELL_STATE::READ_ONLY;
         }
         else
         {
            nCellState     = DSTGridWnd::CELL_STATE::USE_FIELD_PROPERTY;
         }

         cellCtrlType      = GX_IDS_CTRL_CBS_DROPDOWNLIST;
      }
      else if (rowKey == _T ("BankAcctCurrency"))
      {
         idContainer       = IFASTBP_PROC::BANK_INSTRUCTIONS_LIST;
         fieldId           = ifds::BankAcctCurrency;
         substitutionId    = ifds::BankAcctCurrency;
         nCellState        = DSTGridWnd::CELL_STATE::USE_FIELD_PROPERTY;
         cellCtrlType      = GX_IDS_CTRL_CBS_DROPDOWNLIST;
      }
      else if (rowKey == _T ("EffectiveDate"))
      {
         idContainer = IFASTBP_PROC::BANK_INSTRUCTIONS_LIST;
         fieldId     = ifds::EffectiveDate;
         nCellState  = DSTGridWnd::CELL_STATE::USE_FIELD_PROPERTY;
         cellCtrlType = GX_IDS_CTRL_DATETIME;
      }
      else if (rowKey == _T ("StopDate"))
      {
         idContainer = IFASTBP_PROC::BANK_INSTRUCTIONS_LIST;
         fieldId     = ifds::StopDate;
         nCellState  = DSTGridWnd::CELL_STATE::USE_FIELD_PROPERTY;
         cellCtrlType = GX_IDS_CTRL_DATETIMENOCAL;
      }
      else if (rowKey == _T ("TemplateNumber"))
      {
         idContainer = IFASTBP_PROC::BANK_INSTRUCTIONS_LIST;
         fieldId     = ifds::TemplateNumber;
         nCellState  = DSTGridWnd::CELL_STATE::USE_FIELD_PROPERTY;
         cellCtrlType = GX_IDS_CTRL_EDIT;
      }
      else if (rowKey == _T ("ACHProcessor"))
      {
         idContainer       = IFASTBP_PROC::BANK_INSTRUCTIONS_LIST;
         fieldId           = ifds::ACHProcessor;
         substitutionId    = ifds::ACHProcessor;
         nCellState        = DSTGridWnd::CELL_STATE::USE_FIELD_PROPERTY;
         cellCtrlType      = GX_IDS_CTRL_CBS_DROPDOWNLIST;
      }
      else if (rowKey == _T ("BankContact"))
      {
         idContainer = IFASTBP_PROC::BANK_INSTRUCTIONS_LIST;
         fieldId     = ifds::BankContact;
         nCellState  = DSTGridWnd::CELL_STATE::USE_FIELD_PROPERTY;
         cellCtrlType = GX_IDS_CTRL_EDIT;
      }
      else if (rowKey == _T ("BankContactCB"))
      {
         idContainer = IFASTBP_PROC::BANK_INSTRUCTIONS_LIST;
         fieldId     = ifds::BankContactCB;
         nCellState  = DSTGridWnd::CELL_STATE::USE_FIELD_PROPERTY;
         cellCtrlType = GX_IDS_CTRL_EDIT;
      }
      else if (rowKey == _T ("PayMethod"))
      {
         idContainer       = IFASTBP_PROC::BANK_INSTRUCTIONS_LIST;
         fieldId           = ifds::PayMethod;
         nCellState        = DSTGridWnd::CELL_STATE::USE_FIELD_PROPERTY;
         cellCtrlType      = GX_IDS_CTRL_CBS_DROPDOWNLIST;
      }
	  else if (rowKey == _T ("VerifyStat"))
      {
         idContainer       = IFASTBP_PROC::BANK_INSTRUCTIONS_LIST;
         fieldId           = ifds::VerifyStat;
		 
		 if (false) // add checking for permissions.
         {
            nCellState     = DSTGridWnd::CELL_STATE::READ_ONLY;
         }
         else
         {
            nCellState     = DSTGridWnd::CELL_STATE::USE_FIELD_PROPERTY;
         }
         
         cellCtrlType      = GX_IDS_CTRL_CBS_DROPDOWNLIST;
      }
   }
}

//******************************************************************************
void BankInstructionsDlg::OnSelchangeCmbCbIdType () 
{
   showCBFields ();
}

//******************************************************************************
void BankInstructionsDlg::OnSelchangeCmbIdType () 
{
   showFields ();
}

//******************************************************************************
void BankInstructionsDlg::ControlUpdated (UINT ControlID, const DString &strValue)
{
   switch (ControlID)
   {
      case IDC_BANK_INSTR_TYPE:
      {
        DString dstrBankingInstrType;
        getParent()->getField(this,IFASTBP_PROC::BANK_INSTRUCTIONS_LIST, ifds::BankInstrType, dstrBankingInstrType);
        if( BANKTYPE::ACCOUNT == dstrBankingInstrType || BANKTYPE::SHAREHOLDER == dstrBankingInstrType) 
            setDefaultFilterForBankingInstrLevel(!m_bFromPostinitDlg); 
         DString dstrBankInstrType;
         getParent ()->getField ( this, 
                                  IFASTBP_PROC::BANK_INSTRUCTIONS_LIST, 
                                  ifds::BankInstrType, 
                                  dstrBankInstrType
                                );
         bool bShow = ( BANKTYPE::SHAREHOLDER == dstrBankInstrType)  || ( BANKTYPE::ACCOUNT == dstrBankInstrType ) ;
         GetDlgItem(IDC_RB_ACCT_BANKING)->ShowWindow( bShow );
         GetDlgItem(IDC_RB_SHR_BANKING)->ShowWindow( bShow );
         GetDlgItem(IDC_STC_BANKING_GRP)->ShowWindow( bShow );
         if( ! bShow ) 
         {
            setParameter( I_("SetFromGUI"), NULL_STRING ); 
            m_bShrBank = -1;
            ((CButton* )GetDlgItem(IDC_RB_ACCT_BANKING))->SetCheck(0);
            ((CButton* )GetDlgItem(IDC_RB_SHR_BANKING))->SetCheck(0);            
         }
         SetUserAccesFuncCode ();
         CheckPermission ();
         break;
      }
      case IDC_CMB_USE:
      {
         DString dstrValue;

         getParent ()->getField ( this, 
                                  IFASTBP_PROC::BANK_INSTRUCTIONS_LIST, 
                                  ifds::BankInstrType, 
                                  dstrValue
                                );
         if ( dstrValue == BANKTYPE::SHAREHOLDER ||
              dstrValue == BANKTYPE::ACCOUNT|| 
              dstrValue == BANKTYPE::DIRECT_TRADING
            )
         {
            DSTGridWnd * pDSTGridWnd = 
               dynamic_cast< DSTGridWnd * > (GetDlgItem (IDC_GRD_OPTIONS));

            if (pDSTGridWnd) 
            {
               pDSTGridWnd->reloadCell (_T ("ACHProcessor"), _T ("Value"));
            }
         }
         break;
      }
      case IDC_EDT_TRANSIT_NBR:
      case IDC_EDT_ID_NUMBER:
      case IDC_EDT_INST_NBR:
         LoadControl( ControlID );
         break;
      case   IDC_RB_ACCT_BANKING:
      case   IDC_RB_SHR_BANKING:
             if( BANKTYPE::ACCOUNT == strValue)
                 ReInitControl ( IDC_BANK_INSTR_TYPE, BF::NullContainerId, ifds::BankInstrComboDefaultNoRRIFAcct);
             if( BANKTYPE::SHAREHOLDER == strValue)
                 ReInitControl ( IDC_BANK_INSTR_TYPE, BF::NullContainerId, ifds::BankInstrComboDefaultNoRRIF);
             ConnectControlToData (IDC_BANK_INSTR_TYPE, true); 
             LoadControl (IDC_BANK_INSTR_TYPE);
             break;
      default:
         break;
   }
}

//******************************************************************************
void BankInstructionsDlg::GridControlUpdated ( UINT ctrlId,
                                               const DString &rowKey, 
                                               const DString &colKey,
                                               const DString &strNewValue, 
                                               bool bFormatted,
                                               SEVERITY nSeverity
                                             )
{
   if (rowKey == _T ("BankAcctCurrency") && 
       colKey == _T ("Value") && nSeverity <= WARNING)
   {
      DSTGridWnd * grdWnd = GetGrid (IDC_GRD_OPTIONS);
      //refresh ACHProcessor cell
      grdWnd->reloadCell (_T ("ACHProcessor"), colKey);
   }
}

//******************************************************************************
void BankInstructionsDlg::SetUserAccesFuncCode ()
{
   TRACE_METHOD (CLASSNAME, I_ ("SetUserAccesFuncCode"));
   DString bankInstrType;

   if (dynamic_cast<CListCtrl*> (GetDlgItem (IDC_LV_BANK_INSTR))->GetItemCount () == 0)
   {
      SetUserAccesFunctionCode (NULL);
   }
   else
   {
      getParent ()->getField ( this, 
                               IFASTBP_PROC::BANK_INSTRUCTIONS_LIST, 
                               ifds::BankInstrType, 
                               bankInstrType
                             );
      if (bankInstrType == BANKTYPE::DISTRIBUTION)
      {
         DString caller;

         getParent()->getField(this, ifds::CallerName, caller);
         m_bEnableHistory = (caller == BANKTYPE::DISTRIBUTION);
         SetUserAccesFunctionCode (UAF::DISTRIBUTION);
      }
      else if (bankInstrType == BANKTYPE::SYSTEMATIC)
      {
         DString strTransType;
         
         m_bEnableHistory = false;
         getParent ()->getField ( this, 
                                  IFASTBP_PROC::BANK_INSTRUCTIONS_LIST, 
                                  ifds::TransType, 
                                  strTransType, 
                                  false
                                );
         if (strTransType == TRADETYPE::PAC)
         {
            SetUserAccesFunctionCode (UAF::PAC);
         }
         else if (strTransType == TRADETYPE::SWP)
         {
            SetUserAccesFunctionCode (UAF::SWP);
         }
         else if (strTransType == TRADETYPE::AUTO_TRANSFER)
         {
            SetUserAccesFunctionCode (UAF::AUTOMATIC_TRANSFER);
         }
         else if (strTransType == TRADETYPE::SAVING_PLAN)
         {
            SetUserAccesFunctionCode (UAF::SAVING_PLAN);
         }
         else
         {
            SetUserAccesFunctionCode (NULL);
         }
      }
      else if (bankInstrType == BANKTYPE::TRANSACTION)
      {
         SetUserAccesFunctionCode (UAF::TRANSACTION_HISTORY);
         m_bEnableHistory = false;
      }
      else if (bankInstrType == BANKTYPE::PENDING_TRADE)
      {
         SetUserAccesFunctionCode (UAF::PENDING_TRADE);
         m_bEnableHistory = false;
      }
      else if (bankInstrType == BANKTYPE::RRIF)
      {
         SetUserAccesFunctionCode (UAF::RIF_LIF_LRIF_INFO);
         m_bEnableHistory = false;
      }
      else if (bankInstrType == BANKTYPE::TRADE)
      {
         DString tradesTransType;

         m_bEnableHistory = false;
         getParent ()->getField ( this, 
                                  IFASTBP_PROC::BANK_INSTRUCTIONS_LIST,
                                  ifds::TradesTransType, 
                                  tradesTransType, 
                                  false
                                );

         if (DSTCommonFunctions::codeInList( tradesTransType, TRADETYPE::PURCHASE_LIKE ) )
         {
            SetUserAccesFunctionCode (UAF::TRADE_BANKING);
         }
         else if (DSTCommonFunctions::codeInList( tradesTransType, TRADETYPE::REDEMPTION_LIKE ) )
         {
            SetUserAccesFunctionCode (UAF::TRADE_BANKING);
         }
         else if (DSTCommonFunctions::codeInList( tradesTransType, TRADETYPE::EXCHANGE_LIKE ) )
         {
            SetUserAccesFunctionCode (UAF::TRADE_BANKING);
         }
         else 
         {
            assert (0);//should always have a valid value
         }
      }
      else if (bankInstrType == BANKTYPE::FUND_GROUP ||
               bankInstrType == BANKTYPE::FUND_SPONSOR)
      {
         SetUserAccesFunctionCode (UAF::FUND_GROUP_BANK_INSTR);
      }
      /*else if (bankInstrType == BANKTYPE::FUND)
      {
        SetUserAccesFunctionCode (UAF::BANKING_FUND);
      }*/
      else if (bankInstrType == BANKTYPE::SETTLEMENT)
      {
         //SetUserAccesFunctionCode ((I_CHAR *)m_strUserAccessCode.c_str ());
         SetUserAccesFunctionCode ( UAF::TRADE_BANKING );
         m_bEnableHistory = false;
      }
      else
      {
         DString acctUseCode;

         getParent()->getField ( this, 
                                 IFASTBP_PROC::BANK_INSTRUCTIONS_LIST,
                                 ifds::AcctUseCode, 
                                 acctUseCode, 
                                 false);
         if (acctUseCode == AcctUseCode::DIRECT_TRADING)
         {
            SetUserAccesFunctionCode (UAF::DIRECT_TRADING_AGREEMENT);
            m_bEnableHistory = false;
         }
         else
         {
            SetUserAccesFunctionCode (UAF::BANKING_INSTRUCTION);
            m_bEnableHistory = true;
         }
      }
   }  
}

//******************************************************************************
bool BankInstructionsDlg::doDisablePermCheckButton (UINT nID)
{
   bool bReturn = false;

   DString bankInstrType,
      caller;

   getParent ()->getField ( this, 
                            IFASTBP_PROC::BANK_INSTRUCTIONS_LIST,
                            ifds::BankInstrType, 
                            bankInstrType
                          );

   getParent ()->getField ( this, 
                            ifds::CallerName, 
                            caller
                          );

   if (nID == IDC_BTN_ADD || nID == IDC_BTN_DEL)
   {
      if (caller == BANKTYPE::SETTLEMENT && 
          ( bankInstrType == BANKTYPE::BROKER   || 
            bankInstrType == BANKTYPE::BRANCH   ||
            bankInstrType == BANKTYPE::SALESREP ))
      {
         bReturn = true;
      }
      else
      {
         bReturn = 
            bankInstrType == BANKTYPE::TRANSACTION    ||
            bankInstrType == BANKTYPE::PENDING_TRADE  ||
            bankInstrType == BANKTYPE::TRADE          ||
            bankInstrType == BANKTYPE::DISTRIBUTION   || 
            bankInstrType == BANKTYPE::SYSTEMATIC     ||
            bankInstrType == BANKTYPE::SETTLEMENT     ||
            bankInstrType == BANKTYPE::RRIF    ||
            bankInstrType == BANKTYPE::MATURITY_INSTRUCTIONS ||
            bankInstrType == BANKTYPE::ACCOUNT_COMMITMENT ||
			bankInstrType == BANKTYPE::CONTRACTMAT_INSTRUCTIONS;
      }
   }
   return bReturn;
}

//******************************************************************************
void BankInstructionsDlg::doDisableNonPermButtons ()
{
   DString bankInstrType,
      caller;

   getParent ()->getField ( this, 
                            IFASTBP_PROC::BANK_INSTRUCTIONS_LIST,
                            ifds::BankInstrType, 
                            bankInstrType
                          );
   getParent ()->getField ( this, 
                            IFASTBP_PROC::BANK_INSTRUCTIONS_LIST,
                            ifds::CallerName, 
                            caller
                          );

   if ( bankInstrType == BANKTYPE::SETTLEMENT ||
        bankInstrType == BANKTYPE::MATURITY_INSTRUCTIONS ||
        bankInstrType == BANKTYPE::ACCOUNT_COMMITMENT ||
		bankInstrType == BANKTYPE::CONTRACTMAT_INSTRUCTIONS ||
         ( caller != bankInstrType && 
           ( bankInstrType == BANKTYPE::RRIF ||
             bankInstrType == BANKTYPE::DISTRIBUTION ||
             bankInstrType == BANKTYPE::SYSTEMATIC 
           )
         )
      )
   {
      GetDlgItem (IDC_BTN_ADM_DATES)->EnableWindow (false);
      GetDlgItem (IDC_BTN_RESET)->EnableWindow (false);
   }
   else
   {
      bool bEnable = 
            bankInstrType != BANKTYPE::TRANSACTION &&
            bankInstrType != BANKTYPE::PENDING_TRADE &&
            !bIsRedRegAgentInst();

      GetDlgItem (IDC_BTN_RESET)->EnableWindow (bEnable);
      GetDlgItem (IDC_BTN_ADM_DATES)->EnableWindow (bEnable); 
   }

   DString cloneBankInstructions;

   getParent ()->getField ( this, 
                            ifds::CloneBankInstructions, 
                            cloneBankInstructions
                          );

   GetDlgItem (IDC_BTN_TO)->EnableWindow (cloneBankInstructions == I_ ("Y"));
}

//******************************************************************************
bool BankInstructionsDlg::GetOverrideItemString ( long lSubstituteId, 
                                                  const DString &ColumnKey, 
                                                  DString &strOut)
{
   bool retVal = false;
   if (lSubstituteId ==  ifds::BankInstrHeadingSet.getId ())
   {
      if (ColumnKey == I_ ("AcctUseCode"))
      {
         DString dstBIType;
         getParent ()->getField (this, IFASTBP_PROC::BANK_INSTRUCTIONS_LIST,
            ifds::BankInstrType, dstBIType);
         if (dstBIType == BANKTYPE::TRANSACTION || 
             dstBIType == BANKTYPE::PENDING_TRADE)
         {
            CString cStr;
            GetDlgItem (IDC_BANK_INSTR_TYPE)->GetWindowText (cStr);

            strOut = cStr;      
            retVal = true;
         }
      }
      else if (ColumnKey ==  I_ ("Status"))
      {
         DString dstEffectiveDate, dstStopDate, dstCurrBusDate;
         getParent ()->getField (this, IFASTBP_PROC::BANK_INSTRUCTIONS_LIST,
            ifds::EffectiveDate, dstEffectiveDate, false);
         getParent ()->getField (this, IFASTBP_PROC::BANK_INSTRUCTIONS_LIST,
            ifds::StopDate, dstStopDate, false);
         dynamic_cast<DSTCWorkSession *> (getBFWorkSession ())->
         getDateInHostFormat (dstCurrBusDate, 
                              DSTCWorkSession::DATE_TYPE::CURRENT_BUSINESS_DAY, 
                              getDataGroupId ());
         DSTCommonFunctions::DATE_ORDER rtn  = DSTCommonFunctions::CompareDates (dstEffectiveDate, dstCurrBusDate);
         DSTCommonFunctions::DATE_ORDER rtn1 = DSTCommonFunctions::CompareDates (dstCurrBusDate, dstStopDate);
         if (rtn < DSTCommonFunctions::SECOND_EARLIER && (rtn1 == DSTCommonFunctions::FIRST_EARLIER || rtn1 == DSTCommonFunctions::EQUAL))
            strOut = I_ ("Active");
         else
            strOut = I_ ("Inactive");

         retVal = true;
      }
      else if (ColumnKey == I_("BankIdValue"))
      {
         DString dstrBankIDType;
         int nMaxLength, nAllMaxLength;
         bool bIsAllDigits;
         getParent ()->getField (this, IFASTBP_PROC::BANK_INSTRUCTIONS_LIST, 
            ifds::BankIdType, dstrBankIDType, false);

         if (FinancialInstitution::getBankIdNumInfo (dstrBankIDType, 
            nMaxLength, bIsAllDigits, nAllMaxLength))
         {
            if( bIsAllDigits )
            {
               getParent ()->getField (this, IFASTBP_PROC::BANK_INSTRUCTIONS_LIST, 
                  ifds::BankIdValue, strOut, false);
               strOut.padLeft( nMaxLength, I_('0') );
               retVal = true;
            }
         }
      }
   }
   return (retVal);
}

//******************************************************************************
bool BankInstructionsDlg::doDisableControl (UINT nID, bool bIsNew)
{
   //disable all controls if the caller is default and the type is 
   //one of the RRIF/Systematic/Distribution
   //and other combination
   DString caller, bankInstrType, strAcctUseCode;

   getParent ()->getField ( this, 
                            IFASTBP_PROC::BANK_INSTRUCTIONS_LIST, 
                            ifds::BankInstrType, 
                            bankInstrType
                          );
   getParent ()->getField ( this, 
                            ifds::CallerName, 
                            caller
                          );

   getParent()->getField ( this, 
                           IFASTBP_PROC::BANK_INSTRUCTIONS_LIST, 
                           ifds::AcctUseCode, 
                           strAcctUseCode,
                           false );

   strAcctUseCode.strip().upperCase();

   bool disable = 
      ((caller == BANKTYPE::SHAREHOLDER || caller ==  BANKTYPE::ACCOUNT )&& 
         (bankInstrType == BANKTYPE::DISTRIBUTION || 
         bankInstrType == BANKTYPE::SYSTEMATIC ||
         bankInstrType == BANKTYPE::RRIF)) ||
      (caller == BANKTYPE::DISTRIBUTION &&
          (bankInstrType == BANKTYPE::SYSTEMATIC ||
         bankInstrType == BANKTYPE::RRIF)) ||
      (caller == BANKTYPE::RRIF && 
         (bankInstrType == BANKTYPE::SYSTEMATIC ||
         bankInstrType == BANKTYPE::DISTRIBUTION)) ||
      (caller == BANKTYPE::SYSTEMATIC &&
         (bankInstrType == BANKTYPE::RRIF ||
         bankInstrType == BANKTYPE::DISTRIBUTION));
         

   //check whether we are in the below situation, 
   //and decide about disable flag
   if (!disable) 
   {
      if (nID == IDC_EDT_ACC_NAMES)
      {
         DString strBankType;

         getParent ()->getField (this, IFASTBP_PROC::BANK_INSTRUCTIONS_LIST,
            ifds::BankInstrType, strBankType, false);
         //for Broker, Branch, Salesrep, Fund and Client bank, 
         //name always updateable
         if (strBankType == BANKTYPE::BROKER     || 
             strBankType == BANKTYPE::BRANCH     ||
             strBankType == BANKTYPE::SALESREP   ||
             strBankType == BANKTYPE::FUND       ||
             strBankType == BANKTYPE::CLIENT     ||
             strBankType == BANKTYPE::FUND_GROUP ||
             strBankType == BANKTYPE::FUND_SPONSOR ||
			 strBankType == BANKTYPE::REG_AGENT)
         {
            disable = false;
         }
         else
         {
            if (strAcctUseCode == AcctUseCode::DIRECT_DEPOSIT && 
                strBankType    == BANKTYPE::TRADE )
            {
               disable = true;
            }
            else
            {
               //for all the other banks, have to check BANK_ACCT_NAME permission
               disable = bIsNew ? !hasCreatePermission (UAF::BANK_ACCT_NAME) : 
                                  !hasUpdatePermission (UAF::BANK_ACCT_NAME);
            }
         }
      }
      else if( nID == IDC_EDT_ACC_NBR   || 
               nID == IDC_EDT_ID_NUMBER ||
               nID == IDC_EDT_INST_NBR  ||
               nID == IDC_EDT_TRANSIT_NBR )
      {
         DString strBankType;

         getParent ()->getField (this, IFASTBP_PROC::BANK_INSTRUCTIONS_LIST,
            ifds::BankInstrType, strBankType, false);

         if( strAcctUseCode == AcctUseCode::DIRECT_DEPOSIT && 
             strBankType    == BANKTYPE::TRADE )
         {
            disable = true;
         }
         else
         {
            disable = false;
         }
      }
   }
   return disable;
}

//******************************************************************************
bool BankInstructionsDlg::ListViewControlFilter ( long lSubstituteId, 
                                                  const DString *strKey
                                                )
{
   bool bShow = true;
     
   if (lSubstituteId == ifds::BankInstrHeadingSet.getId ())
   {
      DString dstrFilter, dstrxAcctNumber, dstrCurrAcctNum;
      getParent ()->getField ( this, 
                               IFASTBP_PROC::BANK_INSTRUCTIONS_LIST, 
                               ifds::AccountNum, 
                               dstrCurrAcctNum
                             );
      if( 0 == m_bShrBank )
      {
       getParent()->getField (this, IFASTBP_PROC::BANK_INSTRUCTIONS_LIST, ifds::rxBankingEntity, dstrFilter, false);
       bShow = (BANKENTITY::SHAREHOLDER == dstrFilter  );
       if(!(dynamic_cast<BankInstructionsProcess*>(getParent())->hasBankingInstr()) && !m_bShrDummyList_Added)
       { 
        m_bShrDummyList_Added = true;                 
        AddToListControl (IDC_LV_BANK_INSTR);    
        DSTListCtrl *rpList = GetList( IDC_LV_BANK_INSTR );	
        if(rpList)
           rpList->SetItemCount(0)  ;        
       }
      }
      if( 1  == m_bShrBank)
      {
       getParent()->getField (this, IFASTBP_PROC::BANK_INSTRUCTIONS_LIST, ifds::rxBankingEntity, dstrFilter, false); 
       getParent()->getField (this, IFASTBP_PROC::BANK_INSTRUCTIONS_LIST, ifds::rxAcctNum, dstrxAcctNumber, false);  
       bShow = (BANKENTITY::ACCOUNT == dstrFilter && (dstrxAcctNumber == dstrCurrAcctNum) ); 
       if(!(dynamic_cast<BankInstructionsProcess*>(getParent())->hasBankingInstr(dstrCurrAcctNum)) && !m_bAcctDummyList_Added)
        { 
          m_bAcctDummyList_Added = true;           
          AddToListControl (IDC_LV_BANK_INSTR);
          DSTListCtrl *rpList = GetList( IDC_LV_BANK_INSTR );	
          if(rpList)
           rpList->SetItemCount(0)  ;          
        }
      }
   }
   return bShow;
}

//******************************************************************************
void BankInstructionsDlg::OnBtnHistorical()
{
   TRACE_METHOD( CLASSNAME, I_("OnBtnHistorical"));
   CWaitCursor wait;

   DString bankInstrType;
   getParent ()->getField ( this, 
                            IFASTBP_PROC::BANK_INSTRUCTIONS_LIST, 
                            ifds::BankInstrType, 
                            bankInstrType
                          );

   IFastHistoricalInfo f;

   f ( this, 
       bankInstrType == BANKTYPE::DISTRIBUTION ? IFASTBP_PROC::ACCOUNT_DISTRIBUTION : 
                                                 IFASTBP_PROC::BANK_INSTRUCTIONS_LIST,
       I_("SINGLE")
   );

}

/******************************************************************************
Input:None
Output:None
Return:bool
Functionality:Detrmines if the Banking Instructions is for Redirect to RegAgent .
******************************************************************************/
bool BankInstructionsDlg::bIsRedRegAgentInst()
{
	  DString dstrPayInstrOption,bankInstrType;  
	  getParent ()->getField ( this, 
                            IFASTBP_PROC::BANK_INSTRUCTIONS_LIST, 
                            ifds::BankInstrType, 
                            bankInstrType);
	  getParent ()->getField ( this, 
                               IFASTBP_PROC::BANK_INSTRUCTIONS_LIST,
                               ifds::PayInstrOption, 
                               dstrPayInstrOption, 
                               false);
	  return ((dstrPayInstrOption == I_("03"))&& //redirect to reg agent
			  (bankInstrType == BANKTYPE::TRADE));  

}
//******************************************************************************
void BankInstructionsDlg::OnChkAcctBanking()
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OnChkAcctBanking" ) );
   
   UpdateData();
   setParameter( I_("SetFromGUI"), I_("Y")); 
   m_bShrBank  = 1;   
   ((CButton* )GetDlgItem(IDC_RB_ACCT_BANKING))->SetCheck(1);
   ((CButton* )GetDlgItem(IDC_RB_SHR_BANKING))->SetCheck(0);
   getParent()->setField(this, IFASTBP_PROC::BANK_INSTRUCTIONS_LIST, ifds::BankInstrType, BANKTYPE::ACCOUNT, false); 
   LoadListControl ( IDC_LV_BANK_INSTR); 
   ControlUpdated (IDC_RB_ACCT_BANKING, BANKTYPE::ACCOUNT );
   setUpdateFlag(false);
}
//******************************************************************************
void BankInstructionsDlg::OnChkShrBanking()
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OnChkShrBanking" ) );
   
   UpdateData();
   setParameter( I_("SetFromGUI"), I_("Y")); 
   m_bShrBank  = 0;  
   ((CButton* )GetDlgItem(IDC_RB_ACCT_BANKING))->SetCheck(0);
   ((CButton* )GetDlgItem(IDC_RB_SHR_BANKING))->SetCheck(1);  
   getParent()->setField(this, IFASTBP_PROC::BANK_INSTRUCTIONS_LIST, ifds::BankInstrType, BANKTYPE::SHAREHOLDER, false);
   LoadListControl ( IDC_LV_BANK_INSTR);
   ControlUpdated (IDC_RB_ACCT_BANKING, BANKTYPE::SHAREHOLDER );
   setUpdateFlag(false);
}
//******************************************************************************
void BankInstructionsDlg::setDefaultFilterForBankingInstrLevel(bool bSetDummyBankInstrTypeField /*= true */)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "setDefaultFilterForBankingInstrLevel" ) );
   
   UpdateData();
   setParameter( I_("SetFromGUI"), I_("Y")); 
   //I_CHAR* dstrMessage; 
   DSTCWorkSession *dstWorkSession = dynamic_cast<DSTCWorkSession *>(getParent()->getBFWorkSession());
   DString dstrCurrAcctNum;
   getParent ()->getField ( this, IFASTBP_PROC::BANK_INSTRUCTIONS_LIST, ifds::AccountNum, dstrCurrAcctNum );
   DString dstrEnvLvlBanking;
   dstWorkSession->getOption ( ifds::BankingLevel, dstrEnvLvlBanking, getParent()->getDataGroupId(), false);
   DString dstrDefaultBankingLevel;
   if(dstWorkSession)
      dstWorkSession->getOption (ifds::DefaultBankingLevel, dstrDefaultBankingLevel, getParent()->getDataGroupId(), false);
   if(( BANKINGLEVEL::ACCOUNT_LEVEL == dstrEnvLvlBanking || 
        BANKENTITY::ACCOUNT ==  dstrDefaultBankingLevel  ) &&  (0 != m_bShrBank) )
   {
       m_bShrBank  = 1;
       ((CButton* )GetDlgItem(IDC_RB_ACCT_BANKING))->SetCheck(1);
       ((CButton* )GetDlgItem(IDC_RB_SHR_BANKING))->SetCheck(0);        
       if(!dynamic_cast<BankInstructionsProcess*>(getParent())->hasBankingInstr(dstrCurrAcctNum) && bSetDummyBankInstrTypeField )  
           getParent()->setField(this, IFASTBP_PROC::BANK_INSTRUCTIONS_LIST, ifds::BankInstrType, BANKTYPE::ACCOUNT, false);        
   }
   if(  (BANKINGLEVEL::SHAREHOLDER_LEVEL == dstrEnvLvlBanking ||
        BANKENTITY::SHAREHOLDER ==  dstrDefaultBankingLevel ) && (1 != m_bShrBank))
   {
       m_bShrBank  = 0;
       ((CButton* )GetDlgItem(IDC_RB_ACCT_BANKING))->SetCheck(0);
       ((CButton* )GetDlgItem(IDC_RB_SHR_BANKING))->SetCheck(1);    
       if(!dynamic_cast<BankInstructionsProcess*>(getParent())->hasBankingInstr() && bSetDummyBankInstrTypeField )
           getParent()->setField(this, IFASTBP_PROC::BANK_INSTRUCTIONS_LIST, ifds::BankInstrType, BANKTYPE::SHAREHOLDER, false);    
   } 
   ((CButton* )GetDlgItem(IDC_RB_ACCT_BANKING))->EnableWindow(BANKINGLEVEL::SHAREHOLDER_AND_ACCOUNT_LEVEL == dstrEnvLvlBanking );
   ((CButton* )GetDlgItem(IDC_RB_SHR_BANKING))->EnableWindow( BANKINGLEVEL::SHAREHOLDER_AND_ACCOUNT_LEVEL == dstrEnvLvlBanking );
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/BankInstructionsDlg.cpp-arc  $
 * 
 *    Rev 1.101   May 25 2012 16:21:36   wp040100
 * IN 2826540 Fixes
 * 
 *    Rev 1.100   May 07 2012 06:03:16   popescu
 * PETP0187485 - Trade Entry And Processing
 * 
 *    Rev 1.99   Apr 24 2012 21:34:06   wp040039
 * PETP0187485 - Trade Entry And Processing
 * 
 *    Rev 1.98   Apr 04 2012 22:48:04   wp040039
 * PETP0187485-Registartion Agent  Banking
 * 
 *    Rev 1.97   Mar 02 2012 16:34:20   wp040100
 * P0186484 FN05 - Contract Maturity Instruction - Banking Screen Integration
 * 
 *    Rev 1.96   Feb 24 2012 18:45:32   if991250
 * Account Commitment
 * 
 *    Rev 1.95   Feb 02 2012 15:08:20   if991250
 * Maturity/Interest Instructions banking
 * 
 *    Rev 1.94   Nov 25 2011 15:54:48   wp040168
 * P0186484/FN06 - DESKTOP - iFast Desktop (French Customizations)
 * 
 *    Rev 1.93   Nov 21 2011 21:17:48   wp040168
 * P0186484/FN06 - DESKTOP - iFast Desktop (French Customizations)
 * 
 *    Rev 1.92   Nov 19 2011 01:31:10   wp040168
 * P0186484/FN06 - DESKTOP - iFast Desktop (French Customizations)
 * 
 *    Rev 1.91   Jul 05 2010 02:27:50   dchatcha
 * IN# 1984105 - Settlement from Broker trade will bring out shareholder default bank.
 * 
 *    Rev 1.90   Nov 17 2009 15:17:30   jankovii
 * PET0166583 FN01 Static Data Changes Banking 
 * 
 *    Rev 1.89   Sep 03 2009 04:17:24   dchatcha
 * N#1808381 - R95 - Investor Authorization - User allowed to override banking details, Institution number and transit number must be disabled as well.
 * 
 *    Rev 1.88   Aug 28 2009 05:28:00   dchatcha
 * IN#1808381 - R95 - Investor Authorization - User allowed to override banking details, additional checking against trade bank.
 * 
 *    Rev 1.87   Aug 27 2009 11:15:42   dchatcha
 * IN#1808381 - R95 - Investor Authorization - User allowed to override banking details
 * 
 *    Rev 1.86   Jul 28 2009 07:24:02   dchatcha
 * PET 157825 - FN 13 - Dilution Allocation Enhancements, Default NO_SORT for combo box type.
 * 
 *    Rev 1.85   Jul 24 2009 01:19:56   dchatcha
 * PET 157825 - FN 13 - Dilution Allocation Enhancements, Sorting combo in grid.
 * 
 *    Rev 1.84   24 Jun 2009 15:42:24   sibuhatm
 * We have Modified the stop date status for current business date and stop date issue.
 * 
 * Modified files are
 * BankInstructionsDlg.cpp
 * 
 *    Rev 1.83   04 Jan 2008 11:13:52   kovacsro
 * PET 2315 FN30 - UK dealer band
 * 
 *    Rev 1.82   Jan 25 2007 15:24:52   popescu
 * Incident# 800774 - user can enter alphanumeric characters for new bank ids added for the MFS repatriation project
 * 
 *    Rev 1.81   Nov 02 2006 11:45:50   ZHANGCEL
 * PET2217 FN26 - Add a new parameter for Bank Instruction title display
 * 
 *    Rev 1.80   Oct 20 2006 16:57:20   AGUILAAM
 * Multiple debit account
 * 
 *    Rev 1.79   Oct 18 2006 15:54:30   popescu
 * PET 2217/26 STP Multiple Debit Accounts - fund sponsor banking
 * 
 *    Rev 1.78   Sep 07 2006 21:38:54   popescu
 * STP 2192/02
 * 
 *    Rev 1.77   Jul 31 2006 15:36:16   ZHANGCEL
 * PET2192 FN11 -- MgmtCo Banking related changes
 * 
 *    Rev 1.76   Apr 12 2006 14:10:10   AGUILAAM
 * IN 592786 - EFT should be supported for AW trades
 * 
 *    Rev 1.75   Nov 08 2005 12:14:24   zhengcon
 * fixed incident #441809 (work order #70983), the problem is caused by accounts without shareholder banking when try to do a settlement
 * 
 *    Rev 1.74   Sep 15 2005 15:10:36   popescu
 * Incident#403519 - added CLASSNAME as the fifth parameter to  BaseMainDlg constructor
 * 
 *    Rev 1.73   May 12 2005 11:58:36   porteanm
 * Incident 265740 - Bank search.
 * 
 *    Rev 1.72   Nov 30 2004 11:33:46   hernando
 * PTS10033887 - Pad Institution Number and Transit Number with zeros.  (Synchronized with 1.69.1.0)
 * 
 *    Rev 1.71   Nov 07 2004 15:02:18   popescu
 * PTS10033887 - Pad Bank ID/Transit with zeros if digits only.
 * 
 *    Rev 1.70   Nov 04 2004 17:42:10   popescu
 * PET 1117/06, Trade processing
 * 
 *    Rev 1.68   Oct 12 2004 14:52:34   YINGBAOL
 * PTS10033887:don't strip leading '0' for BankIdValue
 * 
 *    Rev 1.67   Sep 23 2004 17:11:38   HERNANDO
 * PET1094 FN06 - Changed Caption from Fund Sponsor to Fund Group.
 * 
 *    Rev 1.66   Sep 21 2004 17:24:02   WINNIE
 * PET 1094 FN8 - Admin Fee changes should not affect Client level banking
 * 
 *    Rev 1.65   Sep 21 2004 13:27:46   HERNANDO
 * PET1094 FN06 - Absatzmeldung Files enhancement.
 * 
 *    Rev 1.64   Sep 08 2004 17:45:42   ZHANGCEL
 * PET1094-FN8 -- AdminFee related changes
 * 
 *    Rev 1.63   May 07 2004 15:44:28   FENGYONG
 * PTS 10029835
 * 
 *    Rev 1.62   Mar 10 2004 14:03:06   HERNANDO
 * PET965 FN11 - As per Serban's suggestion, the Historical Button will be disabled for Distributions if the caller isn't Distributions.  This means, to view the Bank Instructions, the user must go to Distributions Options then Banking.
 * 
 *    Rev 1.61   Mar 09 2004 16:33:16   popescu
 * PET 965, FN 11, confirmation doesn't show -up anymore after switching to distribution/systematic banking, view mode from shareholder banking
 * 
 *    Rev 1.60   Mar 02 2004 16:26:28   HERNANDO
 * PET965 FN11 - Additional historical enhancement.
 * 
 *    Rev 1.59   Mar 02 2004 11:15:50   YINGBAOL
 * PET965.FN1 SSB profile restriction, central permission check at process layer.
 * 
 *    Rev 1.58   Feb 28 2004 16:58:40   HERNANDO
 * PET965 FN11 - Additional historical enhancement.
 * 
 *    Rev 1.57   Feb 14 2004 13:57:16   popescu
 * PET965.FN1 SSB Profile restriction, re-added the banking files to avoid branching
 * 
 *    Rev 1.57   Feb 09 2004 10:16:16   FENGYONG
 * PET965.FN1 SSB Profile restriction
 * 
 *    Rev 1.56   Jan 12 2004 17:55:20   popescu
 * PTS 10020577, added F4 institution search and F4 transit search on banking instriuctions screen, for corresponding edit fields
 * 
 *    Rev 1.55   Oct 23 2003 18:01:08   FENGYONG
 * PET809 FN08 Direct trading enhancement
 * 
 *    Rev 1.54   Oct 19 2003 16:45:00   popescu
 * CIBC, PET809, FN 13 banking work
 * 
 *    Rev 1.53   Oct 06 2003 12:44:30   popescu
 * Added banking support for DirectTrading enhancement
 * 
 *    Rev 1.52   Oct 04 2003 16:01:54   popescu
 * CIBC PET 809, FN 13;
 * also cleaned-up BankSearch and BankList objects,
 * replaced with FinancialInstitutionList
 * 
 *    Rev 1.51   Sep 26 2003 13:59:54   popescu
 * Fixed the occurence of wrong choices in the acctusage field for pending trade banking; this under PTS 10020130; 
 * 
 *    Rev 1.50   Aug 27 2003 18:16:32   HERNANDO
 * PTS 10020706 - Clear non-updateable Edit Controls manually since DSTEdit::DoClear doesn't clear them.
 * 
 *    Rev 1.49   Aug 07 2003 18:35:46   popescu
 * added new param that will help set the UI selection on the desired bank
 * 
 *    Rev 1.48   Aug 07 2003 15:06:16   popescu
 * few changes for settlement banking
 * 
 *    Rev 1.47   Jul 31 2003 22:03:02   popescu
 * Fund/Class search changes....
 * 
 *    Rev 1.46   Jun 25 2003 16:27:22   popescu
 * refresh improvements
 * 
 *    Rev 1.45   Jun 18 2003 17:45:18   popescu
 * RRIF Banking Enhancement , business rules, bug fixes 
 * 
 *    Rev 1.44   Jun 10 2003 11:50:48   popescu
 * for now, when searching for fund/class banking use the BankInstrComboFund substitution list for the bank type combo box
 * 
 *    Rev 1.43   Jun 03 2003 20:59:32   popescu
 * Added the NotOnHost Banking Instructions CBO and List; dummy banks are derived from these objects for common processing
 * 
 *    Rev 1.42   Jun 01 2003 17:08:20   popescu
 * Systematic & Distribution banking work
 * 
 *    Rev 1.41   May 31 2003 20:30:54   popescu
 * RRIF work part ||
 * 
 *    Rev 1.40   May 31 2003 11:55:36   popescu
 * RRIF bank work
 * 
 *    Rev 1.39   May 27 2003 14:30:26   popescu
 * For refresh
 * 
 *    Rev 1.38   May 27 2003 13:14:08   popescu
 * RRIF Banking work
 * 
 *    Rev 1.37   May 23 2003 10:04:30   popescu
 * Part of bank instructions cleaning up process, moved the bank types into the ifastids project
 * 
 *    Rev 1.36   May 22 2003 14:13:44   popescu
 * Replaced name 'BankInstr' with 'BankInstructions'; 
 * simplified child lists getters for the Shareholder object
// 
//    Rev 1.57   Mar 21 2003 18:33:04   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.56   Feb 04 2003 17:20:34   KOVACSRO
// SWIFT enhancement - enable ACHProcessor for default redemption bank
// 
//    Rev 1.55   Oct 09 2002 23:55:30   PURDYECH
// PVCS Database Conversion
// 
//    Rev 1.54   Sep 30 2002 11:01:34   PURDYECH
// BFFieldId no longer has operator long (), so explicit getId () calls are needed in places.
// 
//    Rev 1.53   Sep 11 2002 09:53:00   KOVACSRO
// Added settlement bank to permission check
// 
//    Rev 1.52   Aug 30 2002 13:50:26   SMITHDAV
// ClientLocale and Typed field changes.
// 
//    Rev 1.51   Aug 30 2002 12:11:26   KOVACSRO
// No permission check for settlement bank.
// 
//    Rev 1.50   Aug 06 2002 11:54:52   KOVACSRO
// Changed the rule for bank acct name : for broker, branch, sales rep.,fund and client bank always updateable; for any other bank, check permission
// 
//    Rev 1.49   Jul 24 2002 17:08:24   KOVACSRO
// Added more logic for bank acct name.
// 
//    Rev 1.48   Jul 24 2002 14:38:00   KOVACSRO
// PTS 10008759 : added BankAcctName user id access code in order to enable/disable bank account name control.
// 
//    Rev 1.47   Jul 05 2002 12:00:28   KOVACSRO
// CMB_USE changes to dynamically load AcctUse subst. list.
// 
//    Rev 1.46   Jul 05 2002 08:43:06   PURDYECH
// Removed invalid include file (dataelementproperties.hpp)
// 
//    Rev 1.45   Jun 18 2002 16:41:44   HSUCHIN
// Load caption properly for settlement
// 
//    Rev 1.44   Jun 16 2002 13:08:18   HSUCHIN
// locked add/del/admin dates for settlement bank
// 
//    Rev 1.43   Jun 13 2002 17:57:04   KOVACSRO
// Added a blank to BankIdTypeCB combo box.
// 
//    Rev 1.42   Jun 13 2002 17:13:00   HSUCHIN
// added settlement support
// 
//    Rev 1.41   Jun 07 2002 17:54:06   KOVACSRO
// Removed bank info since it belongs to our CBOs, rather than gui layer.
// 
//    Rev 1.40   03 Jun 2002 15:24:44   KOVACSRO
// Added PayMethod
// 
//    Rev 1.39   31 May 2002 12:27:16   KOVACSRO
// PostalCode and CountryCode out from grid.
// 
//    Rev 1.38   24 May 2002 17:12:40   KOVACSRO
// fund and client banking.
// 
//    Rev 1.37   23 May 2002 11:07:34   KOVACSRO
// BFData
// 
//    Rev 1.36.1.0   May 23 2002 10:41:22   PURDYECH
// BFData Implementation Verification Corrections
// 
//    Rev 1.36   22 Apr 2002 16:59:22   KOVACSRO
// Moved the autoAddFlag to ControlUpdated. doDisablePermCheckButton () should only do what it's name says.
// 
//    Rev 1.35   Apr 08 2002 17:02:46   HERNANDO
// Added getBankIdNumInfo, getBankTransitNumInfo, and getBankAccNumInfo from DSTCommonFunctions.  Made getBankAccNumInfo Market dependent.
// 
//    Rev 1.34   27 Mar 2002 20:57:12   PURDYECH
// Process/Dialog Factory overhaul
// 
//    Rev 1.33.1.0   27 Mar 2002 20:00:56   PURDYECH
// Process/WindowFactory overhaul
// 
//    Rev 1.33   Jan 10 2002 11:58:56   HERNANDO
// Commented-out (Removed) OnSelchangeCmbUse - Prevents redundant load of Grid.
// 
//    Rev 1.32   23 Nov 2001 14:21:38   KOVACSRO
// perm check changes.
// 
//    Rev 1.31   06 Nov 2001 17:21:08   KOVACSRO
// Bug fixed for refresh.
// 
//    Rev 1.30   20 Jun 2001 16:45:02   YINGZ
// add saving plan
// 
//    Rev 1.29   14 Jun 2001 11:58:04   SMITHDAV
// Removed references to UserAccessProcess.
// 
//    Rev 1.28   13 Jun 2001 11:04:54   KOVACSRO
// Added trading permission check, if the screen was launched from trading.
// 
//    Rev 1.27   22 May 2001 15:00:46   KOVACSRO
// Syncup SSB (1.25.1)
// 
//    Rev 1.26   14 May 2001 14:59:18   YINGZ
// code sync up
// 
//    Rev 1.25   14 May 2001 14:42:48   KOVACSRO
// Bug fixed for CB fields.
// 
//    Rev 1.24   14 May 2001 11:18:36   KOVACSRO
// Modified logic for max. number of chars user can enter for Bank Info.
// 
//    Rev 1.23   10 May 2001 11:07:46   KOVACSRO
// lenght and IsDigit for BankIdVal and TransitNo.
// 
//    Rev 1.22   01 May 2001 15:50:08   BUZILAMI
// fix Active column of the list should be bsed on Stop date too
// 
//    Rev 1.21   26 Apr 2001 13:23:10   BUZILAMI
// disable add and delete buttons for trade bank
// 
//    Rev 1.20   26 Apr 2001 10:35:52   BUZILAMI
// fix
// 
//    Rev 1.19   19 Apr 2001 17:13:02   KOVACSRO
// perm. check stuff.
// 
//    Rev 1.18   16 Apr 2001 12:42:54   KOVACSRO
// F4 key perm. check.
// 
//    Rev 1.17   12 Apr 2001 15:28:22   BUZILAMI
// Trading bank changes
// 
//    Rev 1.16   10 Apr 2001 14:13:14   KOVACSRO
// made grid work.
// 
//    Rev 1.15   Apr 09 2001 15:16:06   YINGBAOL
// implement acctUse etc. for TransactionBank
// 
//    Rev 1.14   06 Apr 2001 16:30:00   BUZILAMI
// fix
// 
//    Rev 1.13   Apr 06 2001 12:57:42   YINGBAOL
// lauch bank search dialog
// 
//    Rev 1.12   Apr 05 2001 16:02:08   YINGBAOL
// fix bugs
// 
//    Rev 1.11   04 Apr 2001 16:06:30   BUZILAMI
// uncommented the code that launches BankSearch
// 
//    Rev 1.10   Apr 04 2001 15:30:42   WINNIE
// remove disable bankinfo logic, should implement in the CBO instead
// 
//    Rev 1.9   Apr 03 2001 15:26:00   YINGBAOL
// add BankTransaction Logic
// 
//    Rev 1.8   30 Mar 2001 17:09:36   BUZILAMI
// Systematic bank changes
// 
//    Rev 1.7   27 Mar 2001 16:46:10   KOVACSRO
// perm. check stuff
// 
//    Rev 1.6   27 Mar 2001 12:08:08   KOVACSRO
// small change
// 
//    Rev 1.5   27 Mar 2001 11:46:56   BUZILAMI
// BankSearch launch preparation
// 
//    Rev 1.4   20 Mar 2001 16:01:36   BUZILAMI
// Bank Address changes
// 
//    Rev 1.3   16 Mar 2001 16:27:06   BUZILAMI
// Added SetDlgCaption
// 
//    Rev 1.2   07 Mar 2001 15:44:40   BUZILAMI
// Broker, Branch, SlsRep Bank Instructions changes
// 
//    Rev 1.1   Feb 22 2001 15:24:44   BUZILAMI
// added search for bank using Broker, Branch and sales Rep
// 
//    Rev 1.0   Feb 21 2001 15:58:42   BUZILAMI
// Initial revision.
// 
 * 
 */


