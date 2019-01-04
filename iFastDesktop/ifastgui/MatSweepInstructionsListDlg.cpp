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
//    Copyright 2004 by International Financial Data Services.
//
//******************************************************************************
//
// ^FILE   :DocumentListDlg.cpp
// ^AUTHOR : 
// ^DATE   : 
//
// ----------------------------------------------------------
//
// ^CLASS    : MatSweepInstructionsListDlg
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :  
//
//******************************************************************************

#include "stdafx.h"
#include "mfdstc.h"

#include "matsweepinstructionslistdlg.h"
#include <configmanager.hpp>
#include <uibase\DSTEdit.h>
#include <uibase\ifdslistctrl.h>

#include <ifastbp\mfcaninterprocparam.hpp>
#include <ifastbp\MatSweepInstructionsListProcessincludes.h>
#include <ifastbp\MatSweepInstructionsListProcess.hpp>
#include <configmanager.hpp>
#include <ifastcsi\csisession.h>
#include <ifastcsi\ifastcsi.h>
#include <uibase\dstgridwnd.h>
#include <uibase\dstlistctrl.h>
#include <ifastcbo\dstcommonfunction.hpp>
#include <ifastbp\mfcaninterprocparam.hpp>
#include <ifastcbo\MFAccount.hpp>
#include <uibase\dstedit.h>
#include <ifastcbo\dstcworksession.hpp>
#include <assert.h>
#include <ifastgui\ifasthistoricalinfo.hpp>

#ifndef INCLUDED_ASSERT_H
#define INCLUDED_ASSERT_H
#include <assert.h>
#endif

extern CLASS_IMPORT const I_CHAR* CMD_GUI_MATSWP_INSTRUCTIONS;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_MATSWP_INSTR;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_MATSWP_INSTR_DETLS;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_BANK_INSTRUCTIONS;

#include <bfproc\concretedialogcreator.hpp>
static ConcreteDialogCreator< MatSweepInstructionsListDlg > dlgCreator( CMD_GUI_MATSWP_INSTRUCTIONS ); 

#ifdef _DEBUG
   #define new DEBUG_NEW
   #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

namespace
{
   const I_CHAR * const CLASSNAME				= I_("MatSweepInstructionsListDlg");
   const I_CHAR *LV_MATSWP_INSTRUCTIONS_LIST	= I_( "MatSWPInstructions List" );
   const I_CHAR *LV_MATSWP_INSTR_DETL_LIST		= I_( "MatSWPInstrDetl List" );
   const I_CHAR * const ACCOUNT				= I_( "A" );
   const I_CHAR * const INVESTMENT				= I_( "I" );
   const I_CHAR * const EFT					= I_( "E" );
   const I_CHAR * const CHEQUE					= I_( "S" );
   const I_CHAR * const YES					= I_( "1" );
   const I_CHAR * const PERCENT			    = I_( "P" );
   const I_CHAR * const SWEEP_INSTR			= I_( "SWP" );
}

namespace DETAILS_CONTROLS
{
	//group of controls with fields part of a trade object 
	const UINT BANK		= 1;
	const UINT ADDRESS	= 2;

}
namespace BANKTYPE
{
   extern CLASS_IMPORT I_CHAR * const MATURITY_INSTRUCTIONS;
}

namespace UAF
{
   extern CLASS_IMPORT I_CHAR * const MATURITYSWPEEP_INSTR;
}

namespace ifds
{
	extern CLASS_IMPORT const BFTextFieldId DocListExists;
}

namespace CND
{  // Conditions used
	//   extern const int GUI_ERR_INVALID_FIELD_ENTRY;
   extern const long GUI_ERR_UNKNOWN_EXCEPTION;
}
//*****************************************************************************
// Public methods
//*****************************************************************************
MatSweepInstructionsListDlg::MatSweepInstructionsListDlg( CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: BaseMainDlg( MatSweepInstructionsListDlg::IDD, pParent, pGIC, pGIParent, rCommand, CLASSNAME )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   //{{AFX_DATA_INIT(MatSweepInstructionsListDlg)
   //}}AFX_DATA_INIT
}

//*****************************************************************************
void MatSweepInstructionsListDlg::DoDataExchange( CDataExchange* pDX )
{
	BaseMainDlg::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(MatSweepInstructionsListDlg)
	//}}AFX_DATA_MAP
}

//*****************************************************************************
BEGIN_MESSAGE_MAP(MatSweepInstructionsListDlg, BaseMainDlg)
//{{AFX_MSG_MAP(MatSweepInstructionsListDlg)
ON_BN_CLICKED(IDC_BTN_ADD, OnBtnAdd)
ON_BN_CLICKED(IDC_BTN_DELETE, OnBtnDelete)
ON_BN_CLICKED(IDC_BTN_COPY, OnBtnCopy)
ON_BN_CLICKED(IDC_BTN_ADD_DETL, OnBtnAddDetl)
ON_BN_CLICKED(IDC_BTN_DELETE_DETL, OnBtnDeleteDetl)
ON_BN_CLICKED(IDC_BTN_BANK, OnBtnBank)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//*****************************************************************************
// Message handlers
//*****************************************************************************
BOOL MatSweepInstructionsListDlg::OnInitDialog() 
{
	TRACE_METHOD( CLASSNAME, ONINITDIALOG );
	BaseMainDlg::OnInitDialog(); 

	AddListControl (CLASSNAME, IDC_LV_INSTRUCTIONS, LV_MATSWP_INSTRUCTIONS_LIST, 
         ifds::MatSweepInstructListHeading, IFASTBP_PROC::MAT_SWEEP_INSTRUCTIONS_LIST);
	AddListControl (CLASSNAME, IDC_LV_INSTR_DETAILS, LV_MATSWP_INSTR_DETL_LIST, 
         ifds::MatSweepInstructDetailsListHeading, IFASTBP_PROC::MAT_SWEEP_INSTR_DETAILS_LIST, IDC_LV_INSTRUCTIONS);

	// instruction details...
	AddControl (CTRL_DATE, IDC_DTP_EFFECTIVE_DATE, IFASTBP_PROC::MAT_SWEEP_INSTRUCTIONS_LIST, 
         ifds::EffectiveDate, CTRLFLAG_DEFAULT, 
         IDC_LV_INSTRUCTIONS);
	AddControl (CTRL_EDIT,IDC_EDT_FUND, IFASTBP_PROC::MAT_SWEEP_INSTRUCTIONS_LIST, 
         ifds::Fund, CTRLFLAG_DEFAULT, 
         IDC_LV_INSTRUCTIONS);
	AddControl (CTRL_EDIT,IDC_EDT_CLASS, IFASTBP_PROC::MAT_SWEEP_INSTRUCTIONS_LIST, 
         ifds::Class, CTRLFLAG_DEFAULT, 
         IDC_LV_INSTRUCTIONS);
	AddControl (CTRL_COMBO, IDC_CMB_INSTR_TYPE, IFASTBP_PROC::MAT_SWEEP_INSTRUCTIONS_LIST, 
         ifds::MatSwpInstructionType, CTRLFLAG_DEFAULT |CTRLFLAG_INITCOMBO_BY_SUB_LIST, 
         IDC_LV_INSTRUCTIONS);
	AddControl (CTRL_COMBO, IDC_CMB_SPLIT_TYPE, IFASTBP_PROC::MAT_SWEEP_INSTRUCTIONS_LIST, 
         ifds::SplitType, CTRLFLAG_DEFAULT | CTRLFLAG_INITCOMBO_BY_SUB_LIST, 
         IDC_LV_INSTRUCTIONS);
	AddControl (CTRL_COMBO,IDC_CMB_CASHSWPBAL, IFASTBP_PROC::MAT_SWEEP_INSTRUCTIONS_LIST, 
         ifds::CashSweepBal, CTRLFLAG_DEFAULT | CTRLFLAG_INITCOMBO_BY_SUB_LIST, 
         IDC_LV_INSTRUCTIONS);
	AddControl (CTRL_EDIT,IDC_EDT_SEL_AMOUNT, IFASTBP_PROC::MAT_SWEEP_INSTRUCTIONS_LIST, 
         ifds::SelectedAmt, CTRLFLAG_DEFAULT, 
         IDC_LV_INSTRUCTIONS);
	AddControl (CTRL_EDIT, IDC_EDT_FUND_NUMBER, IFASTBP_PROC::MAT_SWEEP_INSTRUCTIONS_LIST, 
		 ifds::FromFundNumber, CTRLFLAG_DEFAULT, 
		 IDC_LV_INSTRUCTIONS);

	// instruciton allocation details...
	AddControl (CTRL_EDIT, IDC_EDT_FUND_TO, IFASTBP_PROC::MAT_SWEEP_INSTR_DETAILS_LIST, 
         ifds::FundTo, CTRLFLAG_DEFAULT, 
         IDC_LV_INSTR_DETAILS);
	AddControl (CTRL_EDIT, IDC_EDT_CLASS_TO, IFASTBP_PROC::MAT_SWEEP_INSTR_DETAILS_LIST, 
         ifds::ClassTo, CTRLFLAG_DEFAULT, 
         IDC_LV_INSTR_DETAILS);
	AddControl (CTRL_EDIT, IDC_EDT_ACCOUNT, IFASTBP_PROC::MAT_SWEEP_INSTR_DETAILS_LIST, 
         ifds::AccountTo, CTRLFLAG_DEFAULT, 
         IDC_LV_INSTR_DETAILS);
	AddControl (CTRL_EDIT, IDC_EDT_PERCENT, IFASTBP_PROC::MAT_SWEEP_INSTR_DETAILS_LIST, 
         ifds::Percentage, CTRLFLAG_DEFAULT, 
         IDC_LV_INSTR_DETAILS);
	AddControl (CTRL_EDIT, IDC_EDT_FORCED_RATE, IFASTBP_PROC::MAT_SWEEP_INSTR_DETAILS_LIST, 
         ifds::ForcedRateAmt, CTRLFLAG_DEFAULT, IDC_LV_INSTR_DETAILS);
	AddControl (CTRL_EDIT, IDC_EDT_REF_NUMBER, IFASTBP_PROC::MAT_SWEEP_INSTR_DETAILS_LIST, 
         ifds::RefNum, CTRLFLAG_DEFAULT, 
         IDC_LV_INSTR_DETAILS);
	AddControl (CTRL_EDIT, IDC_EDT_FEL, IFASTBP_PROC::MAT_SWEEP_INSTR_DETAILS_LIST, 
         ifds::FELAmt, CTRLFLAG_DEFAULT, IDC_LV_INSTR_DETAILS);
	AddControl (CTRL_EDIT, IDC_EDT_ADDITIONAL_AMT, IFASTBP_PROC::MAT_SWEEP_INSTR_DETAILS_LIST, 
         ifds::AddlAmt, CTRLFLAG_DEFAULT, IDC_LV_INSTR_DETAILS); 	
	AddControl (CTRL_COMBO, IDC_CMB_COMRED, IFASTBP_PROC::MAT_SWEEP_INSTR_DETAILS_LIST, 
         ifds::CommReduction, CTRLFLAG_DEFAULT | CTRLFLAG_INITCOMBO_BY_SUB_LIST, 
         IDC_LV_INSTR_DETAILS);
	AddControl (CTRL_COMBO, IDC_CMB_TERM, IFASTBP_PROC::MAT_SWEEP_INSTR_DETAILS_LIST, 
         ifds::IntInvestTerm, CTRLFLAG_DEFAULT | CTRLFLAG_INITCOMBO_BY_SUB_LIST, 
         IDC_LV_INSTR_DETAILS);
	AddControl (CTRL_COMBO, IDC_CMB_ROLLOVER_TYPE, IFASTBP_PROC::MAT_SWEEP_INSTR_DETAILS_LIST, 
         ifds::RolloverType, CTRLFLAG_DEFAULT |CTRLFLAG_INITCOMBO_BY_SUB_LIST, 
         IDC_LV_INSTR_DETAILS);
	AddControl (CTRL_COMBO, IDC_CMB_FORCED_INDICATOR, IFASTBP_PROC::MAT_SWEEP_INSTR_DETAILS_LIST, 
         ifds::ForcedRate, CTRLFLAG_DEFAULT | CTRLFLAG_INITCOMBO_BY_SUB_LIST, IDC_LV_INSTR_DETAILS);
	AddControl (CTRL_COMBO, IDC_CMB_REMINING, IFASTBP_PROC::MAT_SWEEP_INSTR_DETAILS_LIST, 
         ifds::RemainingFleg, CTRLFLAG_DEFAULT |CTRLFLAG_INITCOMBO_BY_SUB_LIST, IDC_LV_INSTR_DETAILS);
	AddControl (CTRL_COMBO, IDC_CMB_INTEREST_FREQ, IFASTBP_PROC::MAT_SWEEP_INSTR_DETAILS_LIST, 
         ifds::IntCredFreq, CTRLFLAG_DEFAULT |CTRLFLAG_INITCOMBO_BY_SUB_LIST, 
         IDC_LV_INSTR_DETAILS);
	AddControl (CTRL_COMBO, IDC_CMB_INVTYPE, IFASTBP_PROC::MAT_SWEEP_INSTR_DETAILS_LIST, 
         ifds::IntInvestType, CTRLFLAG_DEFAULT |CTRLFLAG_INITCOMBO_BY_SUB_LIST, 
         IDC_LV_INSTR_DETAILS);
	AddControl (CTRL_COMBO, IDC_CMB_CALCTYPE, IFASTBP_PROC::MAT_SWEEP_INSTR_DETAILS_LIST, 
         ifds::IntCalcMthd, CTRLFLAG_DEFAULT | CTRLFLAG_INITCOMBO_BY_SUB_LIST, 
         IDC_LV_INSTR_DETAILS);
	AddControl (CTRL_COMBO, IDC_CMB_PAYTYPE, IFASTBP_PROC::MAT_SWEEP_INSTR_DETAILS_LIST, 
         ifds::PayType, CTRLFLAG_DEFAULT | CTRLFLAG_INITCOMBO_BY_SUB_LIST, 
         IDC_LV_INSTR_DETAILS);	
	AddControl (CTRL_COMBO, IDC_CMB_BUSINESS_TYPE, IFASTBP_PROC::MAT_SWEEP_INSTR_DETAILS_LIST, 
         ifds::BusinessType, CTRLFLAG_DEFAULT |CTRLFLAG_INITCOMBO_BY_SUB_LIST, 
         IDC_LV_INSTR_DETAILS);
	AddControl (CTRL_COMBO, IDC_CMB_CURRENCY, IFASTBP_PROC::MAT_SWEEP_INSTR_DETAILS_LIST, ifds::Currency, 
         CTRLFLAG_DEFAULT | CTRLFLAG_INITCOMBO_BY_SUB_LIST, 
         IDC_LV_INSTR_DETAILS);

	//bank and address....

	AddControl (CTRL_STATIC, IDC_STC_BANK_NAME_LBL, CTRLFLAG_GUI_FIELD);
	AddControl (CTRL_STATIC, IDC_STC_INST_CODE_LBL, CTRLFLAG_GUI_FIELD);
	AddControl (CTRL_STATIC, IDC_STC_TANSIT_NUM_LBL, CTRLFLAG_GUI_FIELD);
	AddControl (CTRL_STATIC, IDC_STC_BANK_ACCTNUM_LBL, CTRLFLAG_GUI_FIELD);
	AddControl (CTRL_STATIC, IDC_STC_CODE, CTRLFLAG_GUI_FIELD);

	AddControl (CTRL_STATIC, IDC_STC_TRANSNUM, IFASTBP_PROC::MAT_SWEEP_INSTR_DETAILS_LIST, ifds::BankTransitNo, CTRLFLAG_DEFAULT, DETAILS_CONTROLS::BANK);
	AddControl (CTRL_STATIC, IDC_STC_BANK_NAME, IFASTBP_PROC::MAT_SWEEP_INSTR_DETAILS_LIST, ifds::InstName, CTRLFLAG_DEFAULT, DETAILS_CONTROLS::BANK);
	AddControl (CTRL_STATIC, IDC_STC_INSTCODE, IFASTBP_PROC::MAT_SWEEP_INSTR_DETAILS_LIST, ifds::BankIdValue, CTRLFLAG_DEFAULT, DETAILS_CONTROLS::BANK);
	AddControl (CTRL_STATIC, IDC_STC_BANK_ACCTNUMBER, IFASTBP_PROC::MAT_SWEEP_INSTR_DETAILS_LIST, ifds::BankAcctNum, CTRLFLAG_DEFAULT, DETAILS_CONTROLS::BANK);
	
	//address code edit box, only allow two digits
	AddControl ( CTRL_EDIT, IDC_EDT_ADDR_CODE, IFASTBP_PROC::MAT_SWEEP_INSTR_DETAILS_LIST, ifds::MatInstrAddrCode, CTRLFLAG_DEFAULT, DETAILS_CONTROLS::ADDRESS);

	AddControl ( CTRL_EDIT, IDC_EDT_FUND_NBR, IFASTBP_PROC::MAT_SWEEP_INSTR_DETAILS_LIST, ifds::FromFundNumber, CTRLFLAG_DEFAULT, IDC_LV_INSTR_DETAILS);
   
	dynamic_cast<DSTEdit*> (GetControl (IDC_EDT_ADDR_CODE))->SetMaxCharNum (2);
	dynamic_cast<DSTEdit*> (GetControl (IDC_EDT_ADDR_CODE))->SetAllowedChars (I_("0123456789"));

	AddControl (CTRL_EDIT, IDC_EDT_ADDRESS, SHAREHOLDER_ADDRESS, ifds::MatInstrAddress, 
                CTRLFLAG_NOT_UPDATABLE | CTRLFLAG_FIELDS_FROM_SUB_LIST | CTRLFLAG_LINE_PACK,
                DETAILS_CONTROLS::ADDRESS);
   
	return TRUE;
}

//******************************************************************************
void MatSweepInstructionsListDlg::OnPostInitDialog()
{
	TRACE_METHOD( CLASSNAME, ONPOSTINITDIALOG );

   SetUserAccesFunctionCode (UAF::MATURITYSWPEEP_INSTR); 
	addControlGroupIDForPermissionCheck (IDC_LV_INSTRUCTIONS);  
	addControlGroupIDForPermissionCheck (IDC_LV_INSTR_DETAILS);  

	GetDlgItem (IDC_EDT_ADDRESS)->EnableWindow (false);


	doRefresh (this, NULL);
}

//**********************************************************************************
bool MatSweepInstructionsListDlg::doRefresh (GenericInterface * rpGICaller, 
                                             const I_CHAR* szOriginalCommand)
{ 
	TRACE_METHOD( CLASSNAME, DOREFRESH );

	SetDlgCaption ();

	ConnectListToData (IDC_LV_INSTRUCTIONS, true);
	LoadListControl (IDC_LV_INSTRUCTIONS);
    ConnectControlsToData (DETAILS_CONTROLS::ADDRESS, true);
    ConnectControlsToData (DETAILS_CONTROLS::BANK, true);

	return true;
}

//**********************************************************************************
void MatSweepInstructionsListDlg::ControlUpdated( UINT controlID, const DString &strValue )
{  
	MAKEFRAMEAUTOPROMOTE2 (CND::IFASTGUI_CONDITION, CLASSNAME,  I_("ControlUpdated"));
	switch (controlID)
	{
		case IDC_CMB_PAYTYPE:
		{
            showBankData ();
			showAddressData ();	
			break;
		}
		case IDC_CMB_SPLIT_TYPE:
		{
			DString dstrSplitType;
			CString strPercentAmountLbl;
			CString strLabel;

			getParent ()->getField( this, IFASTBP_PROC::MAT_SWEEP_INSTRUCTIONS_LIST,  ifds::SplitType, dstrSplitType, false );

			if (dstrSplitType == PERCENT)
				strLabel.LoadString (TXT_SYSTEMATIC_FEE_PERCENT);
			else
				strLabel.LoadString (TXT_AMOUNT);

			strPercentAmountLbl = strLabel + I_(":");

			GetDlgItem (IDC_STC_PERAMT)->SetWindowText (strPercentAmountLbl);
			break;
		}
		case IDC_EDT_ADDR_CODE:
         {
			if (!getParent ()->send (this, I_("RefreshAddress")))
			{
				ConditionMessageBox (FRAMEBELOW (), GETHIGHESTSEVERITY ());
			}
			else
			{
				LoadControl (IDC_EDT_ADDRESS);
				
			}
            break;
         }
		case IDC_EDT_FUND_NBR:
		case IDC_EDT_FUND_TO:
		case IDC_EDT_CLASS_TO:
			{
				DString dstrFundCode, dstrClassCode;

				GetControl (IDC_EDT_FUND_TO)->GetText (dstrFundCode);
				GetControl (IDC_EDT_CLASS_TO)->GetText (dstrClassCode);
				
				if ( !dstrFundCode.empty() && !dstrClassCode.empty() )
				{
					DString dstrFundNumber;
					DSTCWorkSession *dstWorkSession = dynamic_cast<DSTCWorkSession *>( getParent()->getBFWorkSession() );
					dstWorkSession->GetFundNumber( dstrFundCode, dstrClassCode, dstrFundNumber );
					GetDlgItem(IDC_EDT_FUND_NBR)->SetWindowText(dstrFundNumber.c_str());
				}
			}
			break;

		default:
			break;
	}
}

//******************************************************************************
void MatSweepInstructionsListDlg::DoListItemChanged ( UINT listControlID, 
                                                      const DString &strKey, 
                                                      bool bIsNewItem, 
                                                      bool bIsDummyItem)
{
	
	switch (listControlID)
	{
		case IDC_LV_INSTRUCTIONS :
		{
			enableCopyButton (bIsDummyItem);
			enableInstrButtons (bIsDummyItem);

			break;
		}
		case IDC_LV_INSTR_DETAILS:
		{
			enableInstrDetlButtons (bIsDummyItem);
			showBankData ();
			showAddressData ();

			break;
		}

		default:
			break;
   }
}

//**********************************************************************************
void MatSweepInstructionsListDlg::SetDlgCaption()
{
	TRACE_METHOD( CLASSNAME, I_( "SetDlgCaption" ) );

   DString dstrShrNum, 
      dstrEntityName;
   CString strName;

	// Get Entity Name
	if (!m_dstrAccountNum.empty()) 
	{
		dynamic_cast<DSTCWorkSession *>(getBFWorkSession())->getFirstSequenced01AccountholderEntityName(getDataGroupId(), m_dstrAccountNum, dstrEntityName);
	}
	SetShrAcctCaption (dstrShrNum, m_dstrAccountNum, dstrEntityName);

	CString strDialogCaption;
	CString strInstrType;

	GetWindowText( strDialogCaption );

	if (m_strInstrType == SWEEP_INSTR)
		strInstrType.LoadString( ROW_DETAILS_OPTIONS_CASHSWEEP );  
	else
		strInstrType.LoadString( ROW_DETAILS_OPTIONS_MATURITY ); 

	strDialogCaption = strInstrType + strDialogCaption;

	SetWindowText( strDialogCaption );
}

//*****************************************************************************
SEVERITY MatSweepInstructionsListDlg::doInit()
{
	TRACE_METHOD( CLASSNAME, I_("doInit"));

	getParameter (ACCOUNT_NUM, m_dstrAccountNum);
	getParameter (CALLER, m_strCaller);   
	getParameter (INSTR_TYPE, m_strInstrType);
   getParameter (TRADE_LIST_KEY, m_TradeListKey);
	
	return NO_CONDITION;
}

//************************************************************************************
void MatSweepInstructionsListDlg::OnBtnAdd () 
{
	MAKEFRAMEAUTOPROMOTE2 (CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnBtnAdd"));
 
	AddToListControl (IDC_LV_INSTRUCTIONS);
	DString listKey = 
      getParent ()->getCurrentListItemKey (this, IFASTBP_PROC::MAT_SWEEP_INSTRUCTIONS_LIST);
   LoadListControl (IDC_LV_INSTRUCTIONS, &listKey);
}

//************************************************************************************
void MatSweepInstructionsListDlg::OnBtnDelete () 
{
	MAKEFRAMEAUTOPROMOTE2 (CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnBtnDelete"));

	DString listKeyInvestment = getParent ()->getCurrentListItemKey (this, IFASTBP_PROC::MAT_SWEEP_INSTRUCTIONS_LIST);

	setParameter (LIST_KEY_INV, listKeyInvestment);

	if (!getParent ()->send (this, I_("SetTransId")))
	{
		ConditionMessageBox (FRAMEBELOW (), GETHIGHESTSEVERITY ());
	}
	
	DeleteFromListControl (IDC_LV_INSTRUCTIONS);
}
//************************************************************************************
void MatSweepInstructionsListDlg::OnBtnCopy () 
{
	MAKEFRAMEAUTOPROMOTE2 (CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnBtnCopy"));

	DString listKeyInvestment = 
      getParent ()->getCurrentListItemKey (this, IFASTBP_PROC::MAT_SWEEP_INSTRUCTIONS_LIST);

	setParameter (LIST_KEY_INV, listKeyInvestment);
   
	if (!getParent ()->send (this, I_("Clone")))
	{
		ConditionMessageBox (FRAMEBELOW (), GETHIGHESTSEVERITY ());
	}
	else
	{
		LoadListControl (IDC_LV_INSTRUCTIONS);
	}
}

//************************************************************************************
void MatSweepInstructionsListDlg::OnBtnAddDetl () 
{
	TRACE_METHOD( CLASSNAME, I_("OnBtnAddDetl"));

	AddToListControl (IDC_LV_INSTR_DETAILS);
	DString listKey = 
      getParent ()->getCurrentListItemKey (this, IFASTBP_PROC::MAT_SWEEP_INSTR_DETAILS_LIST);
   LoadListControl (IDC_LV_INSTR_DETAILS, &listKey);

}

//************************************************************************************
void MatSweepInstructionsListDlg::OnBtnDeleteDetl () 
{
	TRACE_METHOD( CLASSNAME, I_("OnBtnDeleteDetl"));

	DeleteFromListControl (IDC_LV_INSTR_DETAILS);
}

//**********************************************************************************
void MatSweepInstructionsListDlg::showBankData()
{
	DString dstrPayType;
	CString	strBank = I_("Bank");; // until

	getParent ()->getField( this, IFASTBP_PROC::MAT_SWEEP_INSTR_DETAILS_LIST,  ifds::PayType, dstrPayType, false );
	dstrPayType.stripAll();
	
	int bShow = dstrPayType == EFT ? SW_SHOW : SW_HIDE;

	GetDlgItem (IDC_STC_BANK_NAME_LBL)->ShowWindow (bShow);
	GetDlgItem (IDC_STC_INST_CODE_LBL)->ShowWindow (bShow);
	GetDlgItem (IDC_STC_TANSIT_NUM_LBL)->ShowWindow (bShow);
	GetDlgItem (IDC_STC_BANK_ACCTNUM_LBL)->ShowWindow (bShow);

	GetDlgItem (IDC_STC_TRANSNUM)->ShowWindow (bShow);
	GetDlgItem (IDC_STC_BANK_NAME)->ShowWindow (bShow);
	GetDlgItem (IDC_STC_INSTCODE)->ShowWindow (bShow);
	GetDlgItem (IDC_STC_BANK_ACCTNUMBER)->ShowWindow (bShow);

   DString bankName;
   getParent()->getField( this, IFASTBP_PROC::MAT_SWEEP_INSTR_DETAILS_LIST, ifds::InstName, bankName);
   SetDlgItemText( IDC_STC_BANK_NAME, bankName.c_str() );
   
   DString transNum;
   getParent()->getField( this, IFASTBP_PROC::MAT_SWEEP_INSTR_DETAILS_LIST, ifds::BankTransitNo, transNum);
   SetDlgItemText( IDC_STC_TRANSNUM, transNum.c_str() );

   DString instCode;
   getParent()->getField( this, IFASTBP_PROC::MAT_SWEEP_INSTR_DETAILS_LIST, ifds::BankIdValue, instCode);
   SetDlgItemText( IDC_STC_INSTCODE, instCode.c_str() );
   
   DString bankAcctNum;
   getParent()->getField( this, IFASTBP_PROC::MAT_SWEEP_INSTR_DETAILS_LIST, ifds::BankAcctNum, bankAcctNum);
   SetDlgItemText( IDC_STC_BANK_ACCTNUMBER, bankAcctNum.c_str() );

	if (bShow)
	{
		GetDlgItem (IDC_BTN_BANK)->SetWindowText (strBank);
	}
	GetDlgItem (IDC_BTN_BANK)->ShowWindow (bShow);
	LoadControls (DETAILS_CONTROLS::BANK);

}
//**********************************************************************************
void MatSweepInstructionsListDlg::showAddressData()
{
	DString dstrPayType;		

	getParent ()->getField( this, IFASTBP_PROC::MAT_SWEEP_INSTR_DETAILS_LIST,  ifds::PayType, dstrPayType, false );
	dstrPayType.stripAll();
	
	int bShow = dstrPayType == CHEQUE ? SW_SHOW : SW_HIDE;

	ConnectControlsToData (DETAILS_CONTROLS::ADDRESS, dstrPayType == CHEQUE);

	GetDlgItem (IDC_STC_CODE)->ShowWindow (bShow);
	GetDlgItem (IDC_EDT_ADDR_CODE)->ShowWindow (bShow);
	GetDlgItem (IDC_EDT_ADDR_CODE)->EnableWindow (true);
	GetDlgItem (IDC_EDT_ADDRESS)->ShowWindow (bShow);

	LoadControls (DETAILS_CONTROLS::ADDRESS);
}

//**********************************************************************************
void MatSweepInstructionsListDlg::enableInstrButtons (bool bIsDummyItem)
{
	DString dstrGoodBad, dstrInvStatus;
	bool bEnableAdd = false;
	bool bEnableDelete = false;

	int iItemNumber = getParent()->getNumberOfItemsInList( this, IFASTBP_PROC::MAT_SWEEP_INSTRUCTIONS_LIST);

	if (iItemNumber == 1 && bIsDummyItem)
	{
		bEnableAdd = true;
	}
	else if (iItemNumber > 1 && bIsDummyItem)
	{
		bEnableAdd = true;
		bEnableDelete = true;
	}
	else if (iItemNumber > 0 && !bIsDummyItem)
	{
		DString dstrInstrLevel;

		getParent()->getField (this, IFASTBP_PROC::MAT_SWEEP_INSTRUCTIONS_LIST, ifds::GoodBad,  dstrGoodBad, false);      	
		getParent()->getField (this, IFASTBP_PROC::MAT_SWEEP_INSTRUCTIONS_LIST, ifds::MatInstrLevel,  dstrInstrLevel, false);      	

		dstrGoodBad.strip ().upperCase ();

		bool bAcctLevelInstr = dstrInstrLevel == ACCOUNT && m_strCaller == TRADE ? true : false;

		bEnableAdd = true;
		bEnableDelete = dstrGoodBad == I_("Y") && !bAcctLevelInstr ? true : false;
	}
   getParent()->getField( this, IFASTBP_PROC::MAT_SWEEP_INSTRUCTIONS_LIST, ifds::InvHisStatus, dstrInvStatus, false);
   dstrInvStatus.strip().upperCase();
  
   if (dstrInvStatus == I_("M"))
   {
      bEnableAdd = false;
      bEnableDelete = false;
	  enableControls(false);
   }

	GetDlgItem (IDC_BTN_ADD)->EnableWindow (bEnableAdd);
	GetDlgItem (IDC_BTN_DELETE)->EnableWindow (bEnableDelete);
}

//**********************************************************************************

void MatSweepInstructionsListDlg::enableInstrDetlButtons (bool bIsDummyItem)
{
	DString dstrGoodBad, dstrInvStatus;
	bool bEnableAdd = false;
	bool bEnableDelete = false;

	int iItemNumber = getParent()->getNumberOfItemsInList( this, IFASTBP_PROC:: MAT_SWEEP_INSTR_DETAILS_LIST);

	if (iItemNumber == 1 && bIsDummyItem)
	{
		bEnableAdd = true;
	}
	else if (iItemNumber > 1 && bIsDummyItem)
	{
		bEnableAdd = true;
		bEnableDelete = true;
	}
	else if (iItemNumber > 0 && !bIsDummyItem)
	{
		DString dstrInstrLevel;

		getParent()->getField (this, IFASTBP_PROC::MAT_SWEEP_INSTRUCTIONS_LIST, ifds::GoodBad,  dstrGoodBad, false);      	
		getParent()->getField (this, IFASTBP_PROC::MAT_SWEEP_INSTRUCTIONS_LIST, ifds::MatInstrLevel,  dstrInstrLevel, false);      	

		dstrGoodBad.strip ().upperCase ();

		bool bAcctLevelInstr = dstrInstrLevel == ACCOUNT && m_strCaller == TRADE ? true : false;

		bEnableAdd = dstrGoodBad == I_("Y") && !bAcctLevelInstr ? true : false;;
		bEnableDelete = dstrGoodBad == I_("Y") && !bAcctLevelInstr ? true : false;
	}
    
	getParent()->getField( this, IFASTBP_PROC::MAT_SWEEP_INSTRUCTIONS_LIST, ifds::InvHisStatus, dstrInvStatus, false);
    dstrInvStatus.strip().upperCase();
  
    if (dstrInvStatus == I_("M"))
    {
       bEnableAdd = false;
       bEnableDelete = false;

	   enableControls(false);
    }
	
	GetDlgItem (IDC_BTN_ADD_DETL)->EnableWindow (bEnableAdd);
	GetDlgItem (IDC_BTN_DELETE_DETL)->EnableWindow (bEnableDelete);
}

//**********************************************************************************
void MatSweepInstructionsListDlg::enableCopyButton (bool bIsDummyItem)
{
	bool bEnable = false;

	int iItemNumber = getParent()->getNumberOfItemsInList( this, IFASTBP_PROC::MAT_SWEEP_INSTRUCTIONS_LIST);

	if (iItemNumber > 0 && !bIsDummyItem)
	{
		DString dstrGoodBad;
		DString dstrInstrLevel;
		DString isInstrCopyAllowed;

		getParent()->getField (this, IFASTBP_PROC::MAT_SWEEP_INSTRUCTIONS_LIST, IsInstrCopyAllowed, isInstrCopyAllowed, false);
		getParent()->getField (this, IFASTBP_PROC::MAT_SWEEP_INSTRUCTIONS_LIST, ifds::GoodBad,  dstrGoodBad, false);      	
		getParent()->getField (this, IFASTBP_PROC::MAT_SWEEP_INSTRUCTIONS_LIST, ifds::MatInstrLevel,  dstrInstrLevel, false);      	
		
		dstrGoodBad.strip ().upperCase ();

		if (dstrGoodBad == I_("Y") && dstrInstrLevel == ACCOUNT && 
			(m_strCaller == TRADE || m_strCaller == INV_HISTORY) &&
			isInstrCopyAllowed == I_("Y"))
		{
			bEnable = true;
		}
	}

	GetDlgItem (IDC_BTN_COPY)->EnableWindow (bEnable);
}

//******************************************************************************
void MatSweepInstructionsListDlg::OnBtnBank() 
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OnBtnBank" ) );

   CWaitCursor wait;

   try
   {
	   DString dstrPayType;
      getParent()->getField( this, IFASTBP_PROC::MAT_SWEEP_INSTR_DETAILS_LIST,  ifds::PayType, dstrPayType, false );
	   DString dstrLevel;
      if(m_strCaller == COA)
         dstrLevel = I_("Acct");
      else if(m_strCaller == INV_HISTORY)
         dstrLevel = I_("Proc");
      else 
         dstrLevel = I_("Trade");

//      getParent()->getField( this, IFASTBP_PROC::MAT_SWEEP_INSTRUCTIONS_LIST,  ifds::MatInstrLevel, dstrLevel, false );
	   dstrPayType.stripAll();
	   if(dstrPayType == EFT)
      {
         
         DString dstrPACSWPId;

         DString listKey = getParent()->getCurrentListItemKey(this, IFASTBP_PROC::MAT_SWEEP_INSTRUCTIONS_LIST);
         DString detailsKey = getParent()->getCurrentListItemKey(this, IFASTBP_PROC::MAT_SWEEP_INSTR_DETAILS_LIST);
         if(m_strCaller != COA)
         {
            DString dstrFund;
            getParent()->getField( this, IFASTBP_PROC::MAT_SWEEP_INSTRUCTIONS_LIST, ifds::Fund, dstrFund, false);
            DString dstrClass;
            getParent()->getField( this, IFASTBP_PROC::MAT_SWEEP_INSTRUCTIONS_LIST, ifds::Class, dstrClass, false);
            DString  dstrTransNum;
            getParent()->getField( this, IFASTBP_PROC::MAT_SWEEP_INSTRUCTIONS_LIST, ifds::TransNum, dstrTransNum, false);
            DString dstrTransId;
            getParent()->getField( this, IFASTBP_PROC::MAT_SWEEP_INSTRUCTIONS_LIST, ifds::TransId, dstrTransId, false);
		      DString dstrIntInvestId;
            getParent()->getField( this, IFASTBP_PROC::MAT_SWEEP_INSTRUCTIONS_LIST, ifds::IntInvestId, dstrIntInvestId, false);

            setParameter(MFCAN_IP_PARAM::FUND_CODE,   dstrFund);
            setParameter(MFCAN_IP_PARAM::CLASS_CODE,  dstrClass);
            setParameter(MFCAN_IP_PARAM::TRANS_NUM,   dstrTransNum);
            setParameter(MFCAN_IP_PARAM::TRANS_ID,    dstrTransId);
            setParameter(MFCAN_IP_PARAM::INVEST_ID,   dstrIntInvestId);
         }

         setParameter(MFCAN_IP_PARAM::MAT_INSTR_TYPE, m_strInstrType);
         setParameter(MFCAN_IP_PARAM::MAT_INSTR_LEVEL, dstrLevel);
         setParameter(MFCAN_IP_PARAM::MAT_INSTR_KEY, listKey);
         setParameter(MFCAN_IP_PARAM::MAT_INSTR_DETL_KEY, detailsKey);
         setParameter(MFCAN_IP_PARAM::LIST_KEY, m_TradeListKey);
         setParameter(MFCAN_IP_PARAM::ACCOUNT_NUM, m_dstrAccountNum);
         setParameter(MFCAN_IP_PARAM::BANK_TYPE, BANKTYPE::MATURITY_INSTRUCTIONS);

         E_COMMANDRETURN eRtn = invokeCommand(getParent(), 
            CMD_BPROC_BANK_INSTRUCTIONS, PROC_SUPPORT, true, NULL);

         if (eRtn != CMD_CANCEL)
         {
            showBankData();
            //LoadControl(IDC_TXT_BANK_NAME);
            //LoadControl(IDC_TXT_ACC_NAME);
            //LoadControl(IDC_EDT_ACC_NBR);
            //RefreshListItem(IDC_LV_SYSTEMATIC);
            //Reinit the grid
         }
      }

   }
   catch (ConditionException &ce)
   {
      ConditionMessageBox(ce);
   }
   catch (...)
   {
      DISPLAYCONDITIONFROMFILE( CND::GUI_ERR_UNKNOWN_EXCEPTION );
   }
}

//**********************************************************************************
void MatSweepInstructionsListDlg::enableControls(bool bEnable )
{
	GetDlgItem(IDC_EDT_FUND_NUMBER)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDT_FUND)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDT_CLASS)->EnableWindow(bEnable);
	GetDlgItem(IDC_CMB_INSTR_TYPE)->EnableWindow(bEnable);
	GetDlgItem(IDC_DTP_EFFECTIVE_DATE)->EnableWindow(bEnable);

	GetDlgItem(IDC_CMB_SPLIT_TYPE)->EnableWindow(bEnable);
	GetDlgItem(IDC_CMB_CASHSWPBAL)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDT_SEL_AMOUNT)->EnableWindow(bEnable);
	GetDlgItem(IDC_CMB_ROLLOVER_TYPE)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDT_ACCOUNT)->EnableWindow(bEnable);

	GetDlgItem(IDC_CMB_REMINING)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDT_FUND_NBR)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDT_FUND_TO)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDT_CLASS_TO)->EnableWindow(bEnable);
	GetDlgItem(IDC_CMB_CURRENCY)->EnableWindow(bEnable);

	GetDlgItem(IDC_EDT_PERCENT)->EnableWindow(bEnable);
	GetDlgItem(IDC_CMB_PAYTYPE)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDT_FEL)->EnableWindow(bEnable);
	GetDlgItem(IDC_CMB_INVTYPE)->EnableWindow(bEnable);
	GetDlgItem(IDC_CMB_CALCTYPE)->EnableWindow(bEnable);

	GetDlgItem(IDC_CMB_INTEREST_FREQ)->EnableWindow(bEnable);
	GetDlgItem(IDC_CMB_TERM)->EnableWindow(bEnable);
	GetDlgItem(IDC_CMB_COMRED)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDT_ADDITIONAL_AMT)->EnableWindow(bEnable);
	GetDlgItem(IDC_CMB_FORCED_INDICATOR)->EnableWindow(bEnable);

	GetDlgItem(IDC_EDT_FORCED_RATE)->EnableWindow(bEnable);
	GetDlgItem(IDC_CMB_BUSINESS_TYPE)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDT_REF_NUMBER)->EnableWindow(bEnable);

}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastgui/MatSweepInstructionsListDlg.cpp-arc  $
// 
//    Rev 1.23   Aug 16 2012 15:48:54   kitticha
// IN#2932057 - User should not be able to maintain the instruction when investment is matured.
// 
//    Rev 1.22   Jul 17 2012 15:07:02   kitticha
// IN#2932057 - User should not be able to maintain the instruction when investment is matured.
// 
//    Rev 1.21   May 14 2012 18:28:50   wp040100
// IN 2886441 - Included BayCom/Fund Number 
// 1. Cash Sweep Screen.
// 2. Maturity Interest Instructions Screen.
// 3. GI investment Histroy Screen.
// 
//    Rev 1.20   Apr 11 2012 12:47:54   wp040100
// IN 2886441 - BayCom number display implementation.
// 
//    Rev 1.19   Mar 28 2012 15:26:56   jankovii
// IN 2889383 - P0186477_FN05_Maturity Processing Dsktp issues_LIST 1_Seg_intrnl errr_min issues
// 
//    Rev 1.18   Mar 07 2012 14:19:38   jankovii
// IN 2873354 - P0186477FN03- Deleting Instruction on Processed Investments
// 
//    Rev 1.17   Mar 05 2012 13:42:58   jankovii
// IN 2859411 - P0186477_FN02_Interest Instruction-Err displayed on split type 'Amount' instrctn
// 
//    Rev 1.16   Feb 21 2012 13:10:48   if991250
// Trade Mat Sweep Instr Banks
// 
//    Rev 1.15   Feb 16 2012 17:10:16   if991250
// Trade MatSweep Bank
// 
//    Rev 1.14   Feb 09 2012 13:13:28   jankovii
// IN 2835682 - P0186477FN03 -Database error when accessing Maturity/ Interest Screen
// 
//    Rev 1.13   Feb 06 2012 15:57:08   jankovii
// IN 2835682 - P0186477FN03 -Database error when accessing Maturity/ Interest Screen
// 
//    Rev 1.12   Feb 03 2012 10:43:44   jankovii
// IN 2813743 - P0186477FN03- Can't Access Maturity Instructions thru Investment Hist
// 
//    Rev 1.11   Feb 02 2012 15:08:00   if991250
// Maturity/Interest Instructions banking
// 
//    Rev 1.10   Jan 26 2012 19:30:18   jankovii
// IN 2817696 - P0186477FN03-Cash Sweep Configuration Issues
// 
//    Rev 1.9   Jan 18 2012 16:18:06   jankovii
// IN 2813487 - P0186477FN03 - Cash Sweep DSK Issues
// 
//    Rev 1.8   Jan 11 2012 15:58:16   jankovii
// P0186477 FN03- GIA Maturity/Cash Sweep Instructions
// 
//    Rev 1.7   Jan 10 2012 15:48:02   jankovii
// P0186477 FN03- GIA Maturity/Cash Sweep Instructions
// 
//    Rev 1.6   Dec 20 2011 17:39:36   popescu
// P0186477 FN03- GIA Maturity/Cash Sweep Instructions
// 
//    Rev 1.5   Dec 19 2011 13:45:06   popescu
// P0186477 FN03- GIA Maturity/Cash Sweep Instructions
 * 
 */