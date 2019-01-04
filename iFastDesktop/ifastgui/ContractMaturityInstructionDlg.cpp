//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by International Financial,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2003 by International Financial.
//
//******************************************************************************
//
// ^FILE   : ContractMaturityInstructionDlg.cpp
// ^AUTHOR : Chetan Balepur
// ^DATE   : Jan 23, 2012
//
// ^CLASS    : ContractMaturityInstructionDlg
// ^SUBCLASS : BaseMainDlg
//
// ^CLASS DESCRIPTION : 
//
//******************************************************************************

#include "stdafx.h"

#include "mfdstc.h"
#include <bfproc\AbstractProcess.hpp>
#include <bfproc\ConcreteDialogCreator.hpp>

#include <uibase\DSTListCtrl.h>
#include <uibase\DSTComboBox.h>
#include <uibase\DSTButton.h>

#include <ifastbp\MFCanInterProcParam.hpp>

#include <ifastcbo\DSTCWorkSession.hpp>
#include <ifastcbo\DSTCommonFunction.hpp>

#include <ifastbp\ContractMaturityInstructionsProcessIncludes.h>
#include "ContractMaturityInstructionDlg.h"

extern CLASS_IMPORT const I_CHAR* CMD_GUI_CONTRACT_MATURITY_INSTRUCTIONS;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_FUNDCLASS;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_BANK_INSTRUCTIONS;

static ConcreteDialogCreator< ContractMaturityInstructionDlg > dlgCreator( CMD_GUI_CONTRACT_MATURITY_INSTRUCTIONS );

#ifdef _DEBUG
   #define new DEBUG_NEW
   #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

namespace
{
   const I_CHAR * const CLASSNAME							= I_( "ContractMaturityInstructionDlg" );
   const I_CHAR * const LV_CONTRACT_MATURITY_LIST			= I_( "ContractMaturityInstructionList" );
   const I_CHAR * const INSTR_TYPE							= I_( "InstrType" );
   //const I_CHAR * const CONTRACTMAT_INSTRUCTIONS			= I_( "ConMatInstr" );
   const I_CHAR * const CONT_MAT_INSTR						= I_( "Contract_Mat_Instr" );
   const I_CHAR * const CALLER								= I_( "Caller" );
}

namespace BANKTYPE
{
   extern CLASS_IMPORT I_CHAR * const CONTRACTMAT_INSTRUCTIONS;
}

namespace ifds
{
	extern CLASS_IMPORT const BFTextFieldId ContractMaturityInstrHeading;
}

namespace UAF
{
   //extern CLASS_IMPORT I_CHAR * const CONTRACT_MATURITY_INSTRUCTION;
}

namespace CONTROL_GROUP
{
	const UINT ACC_INFO_GROUP   = 5;
}

namespace CND
{  
   extern const long GUI_ERR_UNKNOWN_EXCEPTION;
}

//******************************************************************************
// Constructor
//******************************************************************************
ContractMaturityInstructionDlg::ContractMaturityInstructionDlg( CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
:BaseMainDlg( ContractMaturityInstructionDlg::IDD, pParent, pGIC, pGIParent, rCommand, CLASSNAME )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );   

   //{{AFX_DATA_INIT( ContractMaturityInstructionDlg )
   //}}AFX_DATA_INIT
}

//******************************************************************************
// Destructor
//******************************************************************************
ContractMaturityInstructionDlg::~ContractMaturityInstructionDlg ()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************
// Called by MFC framework to exchange and validate dialog data
//******************************************************************************
void ContractMaturityInstructionDlg::DoDataExchange( CDataExchange* pDX )
{
   BaseMainDlg::DoDataExchange( pDX );
   //{{AFX_DATA_MAP( ContractMaturityInstructionDlg ) 
   //}}AFX_DATA_MAP
}

//******************************************************************************
// MFC Message Map
//******************************************************************************

BEGIN_MESSAGE_MAP( ContractMaturityInstructionDlg, BaseMainDlg )
//{{AFX_MSG_MAP( ContractMaturityInstructionDlg )
ON_BN_CLICKED(IDC_BTN_ADMIN, OnBtnAdmDates)
ON_BN_CLICKED(IDC_BTN_ADD, OnBtnAdd)
ON_BN_CLICKED(IDC_BTN_DELETE, OnBtnDelete)
ON_BN_CLICKED( IDC_BTN_MORE, OnBtnMore )
ON_BN_CLICKED(IDC_BTN_BANK, OnBtnBank)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()


//******************************************************************************
SEVERITY ContractMaturityInstructionDlg::doInit()
{
	TRACE_METHOD( CLASSNAME, I_("doInit") );

	getParameter (CONMATINS_PROC::ACCOUNT_NUM_VALUE,	m_dstrAccountNum );
	getParameter (CONMATINS_PROC::COT_REC_ID,			m_dstrCotAcctRid);
	getParameter (CONMATINS_PROC::CONTRACT_TYPE,		m_dstrContractType);
	getParameter (CONMATINS_PROC::CONTRACT_TYPE_ID,		m_dstrContractTypeId);
	getParameter (CONMATINS_PROC::POLICY_YEAR,			m_dstrPolicyYear );
	getParameter (CONMATINS_PROC::POLICY_TERM,			m_dstrPolicyTerm );
	getParameter (CONMATINS_PROC::MATURITY_DATE,		m_dstrMaturityDate );

	return NO_CONDITION;
}


//******************************************************************************
void ContractMaturityInstructionDlg::addControls()
{
	//--List Control
	AddListControl (CLASSNAME, IDC_LV_CONTRACT_MATURITY, 
		LV_CONTRACT_MATURITY_LIST,		ifds::ContractMaturityInstrHeading,	IFASTBP_PROC::CONTRACT_MATURITY_INSTRUCTIONS); 
	//--List Control


	AddControl (CTRL_EDIT,	 IDC_EDT_SHAREHOLDERGROUP,	IFASTBP_PROC::MFACCOUNT_CBO,					ifds::AcctGroupName,
		CTRLFLAG_DEFAULT,								CONTROL_GROUP::ACC_INFO_GROUP);

	AddControl (CTRL_EDIT,	 IDC_EDT_BRANCH,			IFASTBP_PROC::MFACCOUNT_CBO,					ifds::BranchName,
		CTRLFLAG_DEFAULT,								CONTROL_GROUP::ACC_INFO_GROUP);

	AddControl (CTRL_EDIT,	 IDC_EDT_BROKER,			IFASTBP_PROC::MFACCOUNT_CBO,					ifds::BrokerName,
		CTRLFLAG_DEFAULT,								CONTROL_GROUP::ACC_INFO_GROUP);

	AddControl (CTRL_EDIT,	 IDC_EDT_CONTRACTTYPE,		IFASTBP_PROC::CONTRACT_MATURITY_INSTRUCTIONS,	ifds::ContractType,
		CTRLFLAG_DEFAULT,								CONTROL_GROUP::ACC_INFO_GROUP);

	AddControl (CTRL_EDIT,   IDC_EDT_POLICYYEAR,		IFASTBP_PROC::CONTRACT_MATURITY_INSTRUCTIONS,	ifds::PolicyYear,
		CTRLFLAG_DEFAULT,								IDC_LV_CONTRACT_MATURITY);

	AddControl (CTRL_EDIT,   IDC_EDT_POLICYTERM, 		IFASTBP_PROC::CONTRACT_MATURITY_INSTRUCTIONS,	ifds::PolicyTerm,
		CTRLFLAG_DEFAULT,								IDC_LV_CONTRACT_MATURITY);

	AddControl (CTRL_DATE,   IDC_DTP_MATURITYDATE,		IFASTBP_PROC::CONTRACT_MATURITY_INSTRUCTIONS,	ifds::MaturityDate,
		CTRLFLAG_DEFAULT,								IDC_LV_CONTRACT_MATURITY);

	AddControl (CTRL_COMBO,	 IDC_CMB_PAYTYPE,			IFASTBP_PROC::CONTRACT_MATURITY_INSTRUCTIONS,	ifds::PayType3,
		CTRLFLAG_INITCOMBO_BY_SUB_LIST,					IDC_LV_CONTRACT_MATURITY);

	AddControl (CTRL_COMBO,	 IDC_CMB_REDCODE,			IFASTBP_PROC::CONTRACT_MATURITY_INSTRUCTIONS,	ifds::RedCode,
		CTRLFLAG_INITCOMBO_BY_SUB_LIST,					IDC_LV_CONTRACT_MATURITY);

	AddControl (CTRL_COMBO,	 IDC_CMB_AMOUNTTYPE,		IFASTBP_PROC::CONTRACT_MATURITY_INSTRUCTIONS,	ifds::PUD1,
		CTRLFLAG_INITCOMBO_BY_SUB_LIST,					IDC_LV_CONTRACT_MATURITY);

	AddControl (CTRL_EDIT,   IDC_EDT_AMOUNT,			IFASTBP_PROC::CONTRACT_MATURITY_INSTRUCTIONS,	ifds::Amount,
		CTRLFLAG_DEFAULT,								IDC_LV_CONTRACT_MATURITY);

	AddControl (CTRL_COMBO,	 IDC_CMB_SOURCEOFFUND,		IFASTBP_PROC::CONTRACT_MATURITY_INSTRUCTIONS,	ifds::SourceOfFunds,
		CTRLFLAG_INITCOMBO_BY_SUB_LIST,					IDC_LV_CONTRACT_MATURITY);

	AddControl (CTRL_COMBO,  IDC_CMB_ADDRESSCODE,		IFASTBP_PROC::ADDRESS_LIST,						ifds::AddrCode,		//IFASTBP_PROC::ADDRESS_LIST
		CTRLFLAG_INITCOMBO_BY_SUB_LIST,					IDC_LV_CONTRACT_MATURITY);

    AddControl (CTRL_EDIT,	 IDC_EDT_ADDRESS,			IFASTBP_PROC::ADDRESS_LIST,						ifds::AddrLine1,	//IFASTBP_PROC::ADDRESS_LIST
		CTRLFLAG_DEFAULT,								IDC_LV_CONTRACT_MATURITY);
	
	AddControl( CTRL_STATIC, IDC_STC_BANK_NAME,			IFASTBP_PROC::CONTRACT_MATURITY_INSTRUCTIONS,	ifds::InstName,	//-- Bank Info
		CTRLFLAG_DEFAULT,								IDC_LV_CONTRACT_MATURITY);

	AddControl( CTRL_STATIC, IDC_STC_INSTITUTION_CODE,	IFASTBP_PROC::CONTRACT_MATURITY_INSTRUCTIONS,	ifds::BankIdNum,	//-- Bank Info
		CTRLFLAG_DEFAULT,								IDC_LV_CONTRACT_MATURITY);

	AddControl( CTRL_STATIC, IDC_STC_TRANSIT_NUMBER,	IFASTBP_PROC::CONTRACT_MATURITY_INSTRUCTIONS,	ifds::TransitNum,//-- Bank Info
		CTRLFLAG_DEFAULT,								IDC_LV_CONTRACT_MATURITY);

	AddControl( CTRL_STATIC, IDC_STC_BANK_ACCOUNT_NO,	IFASTBP_PROC::CONTRACT_MATURITY_INSTRUCTIONS,	ifds::BankAcctNum,	//-- Bank Info
		CTRLFLAG_DEFAULT,								IDC_LV_CONTRACT_MATURITY);
}

//******************************************************************************
BOOL ContractMaturityInstructionDlg::OnInitDialog() 
{
	TRACE_METHOD( CLASSNAME, I_( "OnInitDialog" ) );
	BaseMainDlg::OnInitDialog();
	
	addControls();

	return TRUE;
}

//******************************************************************************
void ContractMaturityInstructionDlg::getFieldsInfo()
{
	TRACE_METHOD( CLASSNAME, I_( "getFieldsInfo" ) );

	DString dstrContractType, dstrAccHldrGroup, dstrBranchName, dstrBrokerName,
			dstrPolicyYear, dstrPolicyTerm, dstrMaturityDate,
			dstrAddrCode, dstrAddress1, dstrAddress2, dstrAddress3, dstrAddress4, dstrAddress5;

	getParent()->getField(this, IFASTBP_PROC::MFACCOUNT_CBO,	ifds::AcctGroupName,	dstrAccHldrGroup,	false);
	getParent()->getField(this, IFASTBP_PROC::MFACCOUNT_CBO,	ifds::BranchName,		dstrBranchName,		false);
	getParent()->getField(this, IFASTBP_PROC::MFACCOUNT_CBO,	ifds::BrokerName,		dstrBrokerName,		false);
	getParent()->getField(this, IFASTBP_PROC::ADDRESS_LIST,		ifds::AddrCode,			dstrAddrCode,		false);
	getParent()->getField(this, IFASTBP_PROC::ADDRESS_LIST,		ifds::AddrLine1,		dstrAddress1,		false);

	getParent()->getField(this, IFASTBP_PROC::ADDRESS_LIST,		ifds::AddrLine2,		dstrAddress2,		false);
	getParent()->getField(this, IFASTBP_PROC::ADDRESS_LIST,		ifds::AddrLine3,		dstrAddress3,		false);
	getParent()->getField(this, IFASTBP_PROC::ADDRESS_LIST,		ifds::AddrLine4,		dstrAddress4,		false);
	getParent()->getField(this, IFASTBP_PROC::ADDRESS_LIST,		ifds::AddrLine5,		dstrAddress5,		false);
	
	dstrContractType.strip();
	dstrAccHldrGroup.strip();
	dstrBranchName.strip();
	dstrBrokerName.strip();
	dstrPolicyYear.strip();
	dstrPolicyTerm.strip();
	dstrMaturityDate.strip();
	dstrAddrCode.strip();
	dstrAddress1.strip();
}
//******************************************************************************
void ContractMaturityInstructionDlg::setDefaultFieldValues()
{
	TRACE_METHOD( CLASSNAME, I_( "setDefaultFieldValues" ) );

	DString dstrAddrCode, dstrAddress1, dstrAddress2, 
			dstrAddress3, dstrAddress4, dstrAddress5;

	getParent()->getField(this, IFASTBP_PROC::ADDRESS_LIST,		ifds::AddrCode,			dstrAddrCode,		false);
	getParent()->getField(this, IFASTBP_PROC::ADDRESS_LIST,		ifds::AddrLine1,		dstrAddress1,		false);
	getParent()->getField(this, IFASTBP_PROC::ADDRESS_LIST,		ifds::AddrLine2,		dstrAddress2,		false);
	getParent()->getField(this, IFASTBP_PROC::ADDRESS_LIST,		ifds::AddrLine3,		dstrAddress3,		false);
	getParent()->getField(this, IFASTBP_PROC::ADDRESS_LIST,		ifds::AddrLine4,		dstrAddress4,		false);
	getParent()->getField(this, IFASTBP_PROC::ADDRESS_LIST,		ifds::AddrLine5,		dstrAddress5,		false);

	getParent()->setField(this, IFASTBP_PROC::CONTRACT_MATURITY_INSTRUCTIONS, ifds::ContractType,	m_dstrContractType, false);
	getParent()->setField(this, IFASTBP_PROC::CONTRACT_MATURITY_INSTRUCTIONS, ifds::PolicyYear,		m_dstrPolicyYear,	false);
	getParent()->setField(this, IFASTBP_PROC::CONTRACT_MATURITY_INSTRUCTIONS, ifds::PolicyTerm,		m_dstrPolicyTerm,	false);
	getParent()->setField(this, IFASTBP_PROC::CONTRACT_MATURITY_INSTRUCTIONS, ifds::MaturityDate,	m_dstrMaturityDate, false);

	getParent()->setField(this, IFASTBP_PROC::CONTRACT_MATURITY_INSTRUCTIONS, ifds::ADCD,			dstrAddrCode,		false);
	getParent()->setField(this, IFASTBP_PROC::CONTRACT_MATURITY_INSTRUCTIONS, ifds::AddrCode,		dstrAddrCode,		false);
	getParent()->setField(this, IFASTBP_PROC::CONTRACT_MATURITY_INSTRUCTIONS, ifds::AddrLine1,		dstrAddress1,		false);
}

//******************************************************************************
bool ContractMaturityInstructionDlg::doRefresh ( GenericInterface * rpGICaller, 
												 const I_CHAR* szOriginalCommand )
{
   TRACE_METHOD( CLASSNAME, DOREFRESH );

	SetAccount( m_dstrAccountNum );
	SetDlgCaption();

	getFieldsInfo();

	int iItemNumber = -1;
    iItemNumber = getParent()->getNumberOfItemsInList( this, IFASTBP_PROC::CONTRACT_MATURITY_INSTRUCTIONS );

	if( iItemNumber != 0 )
	{
		ConnectListToData	( IDC_LV_CONTRACT_MATURITY, true ) ;
		LoadListControl		( IDC_LV_CONTRACT_MATURITY );
	}
	else if ( szOriginalCommand != I_( "DELETE" ) )
	{
		AddToListControl	( IDC_LV_CONTRACT_MATURITY );
	}

	setDefaultFieldValues();
	LoadControls			( IDC_LV_CONTRACT_MATURITY );
	
	ConnectControlsToData ( CONTROL_GROUP::ACC_INFO_GROUP );
	LoadControls ( CONTROL_GROUP::ACC_INFO_GROUP );

	return true;
}
//******************************************************************************
void ContractMaturityInstructionDlg::OnPostInitDialog()
{
	TRACE_METHOD( CLASSNAME, ONPOSTINITDIALOG );

	//SetUserAccesFunctionCode (UAF::CONTRACT_MATURITY_LIST);
	//addControlGroupIDForPermissionCheck (IDC_LV_CONTRACT_MATURITY);

	doRefresh (this, NULL_STRING);

	DString dstrAddrLine1;
	getParent()->getField(this, IFASTBP_PROC::ADDRESS_LIST,	ifds::AddrLine1, dstrAddrLine1,	false);
	
	const DString *Key = &( getParent()->getFirstListItemKey(this, IFASTBP_PROC::CONTRACT_MATURITY_INSTRUCTIONS) );
	do
	{
		getParent()->setField(this, IFASTBP_PROC::CONTRACT_MATURITY_INSTRUCTIONS, ifds::AddrLine1, dstrAddrLine1, false);

	}while( *(Key = &(getParent()->getNextListItemKey(this, IFASTBP_PROC::CONTRACT_MATURITY_INSTRUCTIONS))) != NULL_STRING );
	GetList(IDC_LV_CONTRACT_MATURITY)->RefreshAllItems();

	GetControl(IDC_EDT_CONTRACTTYPE)->Enable(false);
	GetControl(IDC_EDT_SHAREHOLDERGROUP)->Enable(false);

	GetControl(IDC_EDT_BROKER)->Enable(false);
	GetControl(IDC_DTP_MATURITYDATE)->Enable(false);
	
	GetControl(IDC_EDT_POLICYYEAR)->Enable(false);
	GetControl(IDC_EDT_POLICYTERM)->Enable(false);

	GetControl(IDC_CMB_ADDRESSCODE)->Enable(false);
	GetControl(IDC_EDT_ADDRESS)->Enable(false);

	GetControl(IDC_CMB_PAYTYPE)->Enable(true);
	GetControl(IDC_CMB_REDCODE)->Enable(true);
	GetControl(IDC_CMB_SOURCEOFFUND)->Enable(true);
	GetControl(IDC_EDT_AMOUNT)->Enable(true);
}

//******************************************************************************
void ContractMaturityInstructionDlg::SetDlgCaption()
{
	TRACE_METHOD( CLASSNAME, I_( "SetDlgCaption" ) );

    DString dstrShrNum, 
		    dstrEntityName;

	//Get Entity Name
	if ( !m_dstrAccountNum.empty() ) 
		dynamic_cast<DSTCWorkSession *>(getBFWorkSession())->getFirstSequenced01AccountholderEntityName( 
         getDataGroupId(), m_dstrAccountNum, dstrEntityName);

	SetShrAcctCaption(dstrShrNum, m_dstrAccountNum, dstrEntityName);
}

//******************************************************************************
void ContractMaturityInstructionDlg::OnBtnAdd()
{
	TRACE_METHOD( CLASSNAME, I_( "OnBtnAdd" ) );
   
	AddToListControl ( IDC_LV_CONTRACT_MATURITY );

	setDefaultFieldValues();

	//Set AmountType as Dollar I_("D") by default for a new record
	ControlUpdated( IDC_CMB_AMOUNTTYPE, I_("D") );

	LoadListControl  ( IDC_LV_CONTRACT_MATURITY );
	LoadControls     ( IDC_LV_CONTRACT_MATURITY );

	GetList( IDC_LV_CONTRACT_MATURITY )->SetFocus();

	int iNumItem = GetList( IDC_LV_CONTRACT_MATURITY )->GetItemCount();
	GetList( IDC_LV_CONTRACT_MATURITY )->SetSelection( iNumItem -1 );
}
//******************************************************************************
void ContractMaturityInstructionDlg::OnBtnDelete()
{
   TRACE_METHOD( CLASSNAME, I_( "OnBtnDelete" ) );

	DeleteFromListControl( IDC_LV_CONTRACT_MATURITY );

	//Fix for deleting all records
	doRefresh (this, I_( "DELETE" ) );

	setDefaultFieldValues();

	int iItemNumber = 0;
    iItemNumber = getParent()->getNumberOfItemsInList( this, IFASTBP_PROC::CONTRACT_MATURITY_INSTRUCTIONS );

	if( iItemNumber <= 1 )
	{
		DString dstrAddrLine1;
		getParent()->getField(this, IFASTBP_PROC::ADDRESS_LIST,	ifds::AddrLine1, dstrAddrLine1,	false);
		getParent()->setField(this, IFASTBP_PROC::CONTRACT_MATURITY_INSTRUCTIONS, ifds::AddrLine1, dstrAddrLine1, false);

		GetList(IDC_LV_CONTRACT_MATURITY)->RefreshAllItems();
	}
}

//******************************************************************************
void ContractMaturityInstructionDlg::OnBtnMore() 
{
   TRACE_METHOD( CLASSNAME, I_("OnBtnMore"));

   CWaitCursor wait;

	if ( getParent()->performSearch (this, IFASTBP_PROC::CONTRACT_MATURITY_INSTRUCTIONS, SEARCH_NEXT_BLOCK) <= WARNING)
	{
		LoadListControl		( IDC_LV_CONTRACT_MATURITY );
		GetDlgItem(IDC_BTN_MORE)->EnableWindow (getParent()->doMoreRecordsExist(this, IFASTBP_PROC::CONTRACT_MATURITY_INSTRUCTIONS) );
	}
	else
	{
		// Display error
		//ConditionMessageBox (FRAMEBELOW (), GETHIGHESTSEVERITY ());
	}
}

//******************************************************************************
void ContractMaturityInstructionDlg::OnBtnAdmDates() 
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OnBtnAdminDates" ) );

   ShowAdminDates( IFASTBP_PROC::CONTRACT_MATURITY_INSTRUCTIONS );
}

//*****************************************************************************
void ContractMaturityInstructionDlg::ControlUpdated (UINT controlID, const DString &strValue)
{
   switch (controlID)
   {  
	 case IDC_CMB_PAYTYPE:
		 {
			DString dstrPayType;
			getParent()->getField(this, IFASTBP_PROC::CONTRACT_MATURITY_INSTRUCTIONS,	ifds::PayType3,		dstrPayType,	false);
			
			//Enable Banking button only for PayType = EFT
			bool bEnable = dstrPayType == I_("E");

			GetDlgItem (IDC_BTN_BANK)->EnableWindow( bEnable );

			//Clear the banking fields if a banking record is already present and the user chooses to change the paytype
			//Clear the fields for PayType = System or Supress
			if ( !bEnable ) 
			{
				/*
				getParent()->setField( this, IFASTBP_PROC::CONTRACT_MATURITY_INSTRUCTIONS, ifds::InstName,	 I_("") );
				getParent()->setField( this, IFASTBP_PROC::CONTRACT_MATURITY_INSTRUCTIONS, ifds::BankIdNum,	 I_("") );
				getParent()->setField( this, IFASTBP_PROC::CONTRACT_MATURITY_INSTRUCTIONS, ifds::TransitNum, I_("") );
				getParent()->setField( this, IFASTBP_PROC::CONTRACT_MATURITY_INSTRUCTIONS, ifds::BankAcctNum, I_("") );
				*/

				SetDlgItemText( IDC_STC_BANK_NAME,			_T("") );
				SetDlgItemText( IDC_STC_INSTITUTION_CODE,	_T("") );
				SetDlgItemText( IDC_STC_TRANSIT_NUMBER,		_T("") );
				SetDlgItemText( IDC_STC_BANK_ACCOUNT_NO,	_T("") );
			}
		 }
		 break;

      default:
         break;
   }
}

//******************************************************************************
void ContractMaturityInstructionDlg::DoListItemChanged ( UINT listControlID, const DString &strKey, 
														 bool isNewItem, bool bIsDummyItem)
{  
   switch (listControlID)
   {
      case IDC_LV_CONTRACT_MATURITY:
		  {
			 GetDlgItem (IDC_BTN_MORE)->EnableWindow ( getParent()->doMoreRecordsExist (this, 
				 IFASTBP_PROC::CONTRACT_MATURITY_INSTRUCTIONS) );
			 break;
		  }
	  default:
		  break;
   }
}

//******************************************************************************
BOOL ContractMaturityInstructionDlg::PreTranslateMessage( MSG* pMsg ) 
{
	return BaseMainDlg::PreTranslateMessage (pMsg);
}

//******************************************************************************
void ContractMaturityInstructionDlg::getAddress(DString& strAddress) const
{
	DString dstrAddr;

	getParent()->getField( this, IFASTBP_PROC::ADDRESS_LIST, ifds::AddrLine1, dstrAddr );
	strAddress = dstrAddr.strip();

	getParent()->getField( this, IFASTBP_PROC::ADDRESS_LIST, ifds::AddrLine2, dstrAddr );
	strAddress += I_( "\r\n" ) + dstrAddr.strip();

	getParent()->getField( this, IFASTBP_PROC::ADDRESS_LIST, ifds::AddrLine3, dstrAddr );
	strAddress += I_( "\r\n" ) + dstrAddr.strip();

	getParent()->getField( this, IFASTBP_PROC::ADDRESS_LIST, ifds::AddrLine4, dstrAddr );
	strAddress += I_( "\r\n" ) + dstrAddr.strip();

	getParent()->getField( this, IFASTBP_PROC::ADDRESS_LIST, ifds::AddrLine5, dstrAddr );
	strAddress += I_( "\r\n" ) + dstrAddr.strip();
}

//******************************************************************************
bool ContractMaturityInstructionDlg::GetDataForControl( UINT controlID,	 DString &dstrValueOut,
														bool bFormatted, int iIndex ) const
{
   switch( controlID )
   {
	case IDC_EDT_ADDRESS:
		getAddress (dstrValueOut);
		break;
   }

   return false;
}

//******************************************************************************
void ContractMaturityInstructionDlg::OnBtnBank() 
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OnBtnBank" ) );

	CWaitCursor wait;

	try
	{
		SetMessageStatusBar (TXT_LOAD_BANKING);

		DString dstrConMatListKey;
		dstrConMatListKey = getParent()->getCurrentListItemKey(this, IFASTBP_PROC::CONTRACT_MATURITY_INSTRUCTIONS );

		setParameter (CALLER,									BANKTYPE::CONTRACTMAT_INSTRUCTIONS);
		setParameter (MFCAN_IP_PARAM::CON_MAT_INSTR_KEY,		dstrConMatListKey);
		setParameter (MFCAN_IP_PARAM::ACCOUNT_NUM,				m_dstrAccountNum);
		setParameter (MFCAN_IP_PARAM::CON_MAT_INSTR_COTACCTRID,	m_dstrCotAcctRid);
		setParameter (MFCAN_IP_PARAM::CON_MAT_INSTR_TYPE,		m_dstrContractType);
		setParameter (MFCAN_IP_PARAM::CON_MAT_INSTR_TYPEID,		m_dstrContractTypeId);
		setParameter (MFCAN_IP_PARAM::BANK_TYPE,				BANKTYPE::CONTRACTMAT_INSTRUCTIONS);
		setParameter (INSTR_TYPE,								CONT_MAT_INSTR);

		E_COMMANDRETURN eRtn = invokeCommand(getParent(), CMD_BPROC_BANK_INSTRUCTIONS, PROC_SUPPORT, true, NULL);

		SetMessageStatusBar (NULL_STRING);

		if (eRtn != CMD_CANCEL)
		{
			DString dstrBankName;
			getParent()->getField( this, IFASTBP_PROC::CONTRACT_MATURITY_INSTRUCTIONS, ifds::InstName, dstrBankName);
			LoadControl ( IDC_STC_BANK_NAME );
			
			DString dstrInstCode;
			getParent()->getField( this, IFASTBP_PROC::CONTRACT_MATURITY_INSTRUCTIONS, ifds::BankIdNum, dstrInstCode);
			LoadControl ( IDC_STC_INSTITUTION_CODE );
			
			DString dstrTransNum;
			getParent()->getField( this, IFASTBP_PROC::CONTRACT_MATURITY_INSTRUCTIONS, ifds::TransitNum, dstrTransNum);
			LoadControl ( IDC_STC_TRANSIT_NUMBER );
			
			DString dstrBankAcctNum;
			getParent()->getField( this, IFASTBP_PROC::CONTRACT_MATURITY_INSTRUCTIONS, ifds::BankAcctNum, dstrBankAcctNum);
			LoadControl ( IDC_STC_BANK_ACCOUNT_NO );
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

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/ContractMaturityInstructionDlg.cpp-arc  $
// 
//    Rev 1.11   May 28 2012 00:35:38   wp040100
// Removed Comments
// 
//    Rev 1.10   May 04 2012 17:16:16   wp040100
// IN 2915591 - Enabled validations for Bank Account Number and Back Account Holder Name
// 
//    Rev 1.9   Mar 22 2012 18:36:28   wp040100
// P0186484 FN05 - Contract Maturity Instruction Changes
// 
//    Rev 1.8   Mar 19 2012 21:42:22   wp040100
// P0186484 FN05 - Contract Maturity Instruction Changes
// 
//    Rev 1.7   Mar 16 2012 17:46:34   wp040100
// P0186484 FN05 - Contract Maturity Instruction Changes
// 
//    Rev 1.6   Mar 15 2012 19:31:46   wp040100
// IN 2874666 - P0186484 FN05 - Contract Maturity Instruction Changes
// 
//    Rev 1.5   Mar 02 2012 16:33:56   wp040100
// P0186484 FN05 - Contract Maturity Instruction - Banking Screen Integration
// 
//    Rev 1.4   Feb 27 2012 20:20:10   wp040100
// P0186484 FN05 - Contract Maturity Instruction Changes
// 
//    Rev 1.3   Feb 23 2012 14:38:56   wp040100
// P0186484 FN05 - Contract Maturity Instruction Changes
// 
//    Rev 1.2   Feb 22 2012 15:58:34   wp040100
// P0186484 FN05 - Contract Maturity Instruction Changes
// 
//    Rev 1.1   Feb 22 2012 13:49:54   wp040100
// P0186484 FN05 - Contract Maturity Instruction Changes
// 
//    Rev 1.0   Feb 21 2012 15:23:06   wp040100
// Initial revision.
//
//
//
*/