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
// FILE   : RDSPTransfersDlg.cpp
// AUTHOR : 
// DATE   : 
//
// ----------------------------------------------------------
//
// CLASS  : RDSPTransfersDlg
//
// MEMBER VARIABLES :
//
// CODING COMMENTS  :  
//
//******************************************************************************

#include "stdafx.h"
#include "mfdstc.h"

#include "RDSPTransfersDlg.h"
#include <configmanager.hpp>
#include <uibase\DSTEdit.h>
#include <ifastcsi\csisession.h>
#include <ifastcsi\ifastcsi.h>

#include <ifastbp\mfcaninterprocparam.hpp>
#include <ifastbp\RDSPTransfersProcess.hpp>
#include <ifastbp\RDSPTransfersProcessIncludes.h>
#include <ifastcbo\dstcommonfunction.hpp>
#include <ifastcbo\DSTCWorkSession.hpp>

#include <assert.h>

#ifndef INCLUDED_ASSERT_H
#define INCLUDED_ASSERT_H
#include <assert.h>
#endif

extern CLASS_IMPORT const I_CHAR* CMD_GUI_RDSP_TRANSFER;
#include <bfproc\concretedialogcreator.hpp>
static ConcreteDialogCreator< RDSPTransfersDlg > dlgCreator( CMD_GUI_RDSP_TRANSFER ); 

#ifdef _DEBUG
   #define new DEBUG_NEW
   #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

namespace
{
	const I_CHAR * const CLASSNAME					= I_("RDSPTransfersDlg");
	const I_CHAR * const EXTERNAL_RDSP_TRANSFER_IN	= I_("67");
}

namespace ifds
{

}

namespace UAF
{
	extern CLASS_IMPORT I_CHAR * const RDSP_TRANSFER;
}


//*****************************************************************************
// Public methods
//*****************************************************************************
RDSPTransfersDlg::RDSPTransfersDlg( CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: BaseMainDlg( RDSPTransfersDlg::IDD, pParent, pGIC, pGIParent, rCommand, CLASSNAME ),
m_bDialogInit (false),
m_DecimalDigits (0),
m_TransType (NULL_STRING)
{
	TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
	//{{AFX_DATA_INIT(RDSPTransfersDlg)
	//}}AFX_DATA_INIT
}

//*****************************************************************************
void RDSPTransfersDlg::DoDataExchange( CDataExchange* pDX )
{
	BaseMainDlg::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(RDSPTransfersDlg)
	//}}AFX_DATA_MAP
}

//*****************************************************************************
BEGIN_MESSAGE_MAP(RDSPTransfersDlg, BaseMainDlg)
	//{{AFX_MSG_MAP(RDSPTransfersDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//*****************************************************************************
BOOL RDSPTransfersDlg::OnInitDialog() 
{
	TRACE_METHOD( CLASSNAME, ONINITDIALOG );

	BaseMainDlg::OnInitDialog(); 

	return TRUE;
}

//******************************************************************************
void RDSPTransfersDlg::OnPostInitDialog()
{
	TRACE_METHOD( CLASSNAME, ONPOSTINITDIALOG );

	SetUserAccesFunctionCode (UAF::RDSP_TRANSFER);  

	addControls ();

	setAllowedChars ();

	doRefresh (this, NULL_STRING);

	enableDisableControls();

	m_bDialogInit = false;
}

//*****************************************************************************
void RDSPTransfersDlg::setAllowedChars ()
{
	DSTEdit *edit = NULL;
	int iDecimalPointPos;

	DString dstrContribMask;

	edit = dynamic_cast<DSTEdit *>( GetControl (IDC_EDT_RDSP_CONTRIB));
	edit->SetAllowedChars(I_("0123456789."));
	edit->setInputAllowedUnsignedDecimal();

	dstrContribMask = DSTCommonFunctions::getMask( ifds::NontaxContrib );
	iDecimalPointPos = dstrContribMask.find (I_("."));	
	edit->setMaxNumDigitsBeforeDecimalPoint( iDecimalPointPos - 1 );
	edit->setMaxNumDigitsAfterDecimalPoint( dstrContribMask.length() - iDecimalPointPos - 2 ); 

	DString dstrRolloversMask;

	edit = dynamic_cast<DSTEdit *>( GetControl (IDC_EDT_RDSP_ROLLOVERS));
	edit->SetAllowedChars(I_("0123456789."));
	edit->setInputAllowedUnsignedDecimal();

	dstrRolloversMask = DSTCommonFunctions::getMask( ifds::Rollovers );
	iDecimalPointPos = dstrRolloversMask.find (I_("."));	
	edit->setMaxNumDigitsBeforeDecimalPoint( iDecimalPointPos - 1 );
	edit->setMaxNumDigitsAfterDecimalPoint( dstrRolloversMask.length() - iDecimalPointPos - 2 ); 

	DString dstrGrantMask;

	edit = dynamic_cast<DSTEdit *>( GetControl (IDC_EDT_RDSP_CDS_GRANT));
	edit->SetAllowedChars(I_("0123456789."));
	edit->setInputAllowedUnsignedDecimal();

	dstrGrantMask = DSTCommonFunctions::getMask( ifds::CDSGrant );
	iDecimalPointPos = dstrGrantMask.find (I_("."));	
	edit->setMaxNumDigitsBeforeDecimalPoint( iDecimalPointPos - 1 );
	edit->setMaxNumDigitsAfterDecimalPoint( dstrGrantMask.length() - iDecimalPointPos - 2 ); 

	DString dstrBondMask;

	edit = dynamic_cast<DSTEdit *>( GetControl (IDC_EDT_RDSP_CDS_BOND));
	edit->SetAllowedChars(I_("0123456789."));
	edit->setInputAllowedUnsignedDecimal();

	dstrBondMask = DSTCommonFunctions::getMask( ifds::CDSBond );
	iDecimalPointPos = dstrBondMask.find (I_("."));	
	edit->setMaxNumDigitsBeforeDecimalPoint( iDecimalPointPos - 1 );
	edit->setMaxNumDigitsAfterDecimalPoint( dstrBondMask.length() - iDecimalPointPos - 2 ); 

	DString dstrFmvMask;

	edit = dynamic_cast<DSTEdit *>( GetControl (IDC_EDT_RDSP_FMV));
	edit->SetAllowedChars(I_("0123456789."));
	edit->setInputAllowedUnsignedDecimal();

	dstrFmvMask = DSTCommonFunctions::getMask( ifds::CurrYrFMV );
	iDecimalPointPos = dstrFmvMask.find (I_("."));	
	edit->setMaxNumDigitsBeforeDecimalPoint( iDecimalPointPos - 1 );
	edit->setMaxNumDigitsAfterDecimalPoint( dstrFmvMask.length() - iDecimalPointPos - 2 ); 

	DString dstrPrevYrGrantBondMask;

	edit = dynamic_cast<DSTEdit *>( GetControl (IDC_EDT_RDSP_PREV_YR_GRANT_BOND));
	edit->SetAllowedChars(I_("0123456789."));
	edit->setInputAllowedUnsignedDecimal();

	dstrPrevYrGrantBondMask = DSTCommonFunctions::getMask( ifds::PrevYrGrantBond );
	iDecimalPointPos = dstrPrevYrGrantBondMask.find (I_("."));	
	edit->setMaxNumDigitsBeforeDecimalPoint( iDecimalPointPos - 1 );
	edit->setMaxNumDigitsAfterDecimalPoint( dstrPrevYrGrantBondMask.length() - iDecimalPointPos - 2 ); 

	DString dstrPrevYrContribMask;

	edit = dynamic_cast<DSTEdit *>( GetControl (IDC_EDT_RDSP_PREV_YR_CONTRIB));
	edit->SetAllowedChars(I_("0123456789."));
	edit->setInputAllowedUnsignedDecimal();

	dstrPrevYrContribMask = DSTCommonFunctions::getMask( ifds::PrevYrContrib );
	iDecimalPointPos = dstrPrevYrContribMask.find (I_("."));	
	edit->setMaxNumDigitsBeforeDecimalPoint( iDecimalPointPos - 1 );
	edit->setMaxNumDigitsAfterDecimalPoint( dstrPrevYrContribMask.length() - iDecimalPointPos - 2 ); 

	DString dstrPrevYrNonTaxRedAmtMask;

	edit = dynamic_cast<DSTEdit *>( GetControl (IDC_EDT_RDSP_PREV_YR_NO_TAX_RED));
	edit->SetAllowedChars(I_("0123456789."));
	edit->setInputAllowedUnsignedDecimal();

	dstrPrevYrNonTaxRedAmtMask = DSTCommonFunctions::getMask( ifds::PrevYrNonTaxRedAmt );
	iDecimalPointPos = dstrPrevYrNonTaxRedAmtMask.find (I_("."));	
	edit->setMaxNumDigitsBeforeDecimalPoint( iDecimalPointPos - 1 );
	edit->setMaxNumDigitsAfterDecimalPoint( dstrPrevYrNonTaxRedAmtMask.length() - iDecimalPointPos - 2 ); 	
	
	DString dstrPrevYrTaxRedAmtMask;

	edit = dynamic_cast<DSTEdit *>( GetControl (IDC_EDT_RDSP_PREV_YR_TAX_RED));
	edit->SetAllowedChars(I_("0123456789."));
	edit->setInputAllowedUnsignedDecimal();

	dstrPrevYrTaxRedAmtMask = DSTCommonFunctions::getMask( ifds::PrevYrTaxRedAmt );
	iDecimalPointPos = dstrPrevYrTaxRedAmtMask.find (I_("."));	
	edit->setMaxNumDigitsBeforeDecimalPoint( iDecimalPointPos - 1 );
	edit->setMaxNumDigitsAfterDecimalPoint( dstrPrevYrTaxRedAmtMask.length() - iDecimalPointPos - 2 ); 
	
	DString dstrCurrYrNonTaxRedAmtMask;

	edit = dynamic_cast<DSTEdit *>( GetControl (IDC_EDT_RDSP_NO_TAX_RED));
	edit->SetAllowedChars(I_("0123456789."));
	edit->setInputAllowedUnsignedDecimal();

	dstrCurrYrNonTaxRedAmtMask = DSTCommonFunctions::getMask( ifds::CurrYrNonTaxRedAmt );
	iDecimalPointPos = dstrCurrYrNonTaxRedAmtMask.find (I_("."));	
	edit->setMaxNumDigitsBeforeDecimalPoint( iDecimalPointPos - 1 );
	edit->setMaxNumDigitsAfterDecimalPoint( dstrCurrYrNonTaxRedAmtMask.length() - iDecimalPointPos - 2 );

	DString dstrCurrYrTaxRedAmtMask;

	edit = dynamic_cast<DSTEdit *>( GetControl (IDC_EDT_RDSP_TAX_RED));
	edit->SetAllowedChars(I_("0123456789."));
	edit->setInputAllowedUnsignedDecimal();

	dstrCurrYrTaxRedAmtMask = DSTCommonFunctions::getMask( ifds::CurrYrTaxRedAmt );
	iDecimalPointPos = dstrCurrYrTaxRedAmtMask.find (I_("."));	
	edit->setMaxNumDigitsBeforeDecimalPoint( iDecimalPointPos - 1 );
	edit->setMaxNumDigitsAfterDecimalPoint( dstrCurrYrTaxRedAmtMask.length() - iDecimalPointPos - 2 ); 
}

//*****************************************************************************
void RDSPTransfersDlg::addControls ()
{
	AddControl (CTRL_STATIC, IDC_STC_RDSP_FROM_CONTRACT, CTRLFLAG_GUI_FIELD);
	AddControl (CTRL_EDIT, IDC_EDT_RDSP_FROM_CONTRACT, IFASTBP_PROC::RDSP_TRANSFER, ifds::ExtAccount, CTRLFLAG_DEFAULT);	
	AddControl (CTRL_STATIC, IDC_STC_RDSP_FROM_PLAN, CTRLFLAG_GUI_FIELD);
	AddControl (CTRL_EDIT, IDC_EDT_RDSP_FROM_PLAN, IFASTBP_PROC::RDSP_TRANSFER, ifds::ExtSpecimenPlanNo, CTRLFLAG_DEFAULT);	
	AddControl (CTRL_STATIC, IDC_STC_RDSP_TO_CONTRACT, CTRLFLAG_GUI_FIELD);
	AddControl (CTRL_EDIT, IDC_EDT_RDSP_TO_CONTRACT, IFASTBP_PROC::RDSP_TRANSFER, ifds::AccountNum, CTRLFLAG_DEFAULT);	
	AddControl (CTRL_STATIC, IDC_STC_RDSP_TO_PLAN, CTRLFLAG_GUI_FIELD);
	AddControl (CTRL_EDIT, IDC_EDT_RDSP_TO_PLAN, IFASTBP_PROC::RDSP_TRANSFER, ifds::GrantAmountNA, CTRLFLAG_DEFAULT);	

	AddControl (CTRL_STATIC, IDC_STC_RDSP_TRANSFER_BAL,	CTRLFLAG_GUI_FIELD);
	AddControl (CTRL_STATIC, IDC_STC_RDSP_CONTRIB, CTRLFLAG_GUI_FIELD);
	AddControl (CTRL_EDIT, IDC_EDT_RDSP_CONTRIB, IFASTBP_PROC::RDSP_TRANSFER, ifds::NontaxContrib, CTRLFLAG_DEFAULT);
	AddControl (CTRL_STATIC, IDC_STC_RDSP_ROLLOVERS, CTRLFLAG_GUI_FIELD);
	AddControl (CTRL_EDIT, IDC_EDT_RDSP_ROLLOVERS, IFASTBP_PROC::RDSP_TRANSFER, ifds::Rollovers, CTRLFLAG_DEFAULT);
	AddControl (CTRL_STATIC, IDC_STC_RDSP_CDS_GRANT, CTRLFLAG_GUI_FIELD);
	AddControl (CTRL_EDIT, IDC_EDT_RDSP_CDS_GRANT, IFASTBP_PROC::RDSP_TRANSFER, ifds::CDSGrant, CTRLFLAG_DEFAULT);
	AddControl (CTRL_STATIC, IDC_STC_RDSP_CDS_BOND,	CTRLFLAG_GUI_FIELD);
	AddControl (CTRL_EDIT, IDC_EDT_RDSP_CDS_BOND, IFASTBP_PROC::RDSP_TRANSFER, ifds::CDSBond, CTRLFLAG_DEFAULT);
	AddControl (CTRL_STATIC, IDC_STC_RDSP_BALANCES,	CTRLFLAG_GUI_FIELD);
	AddControl (CTRL_STATIC, IDC_STC_RDSP_FMV, CTRLFLAG_GUI_FIELD);
	AddControl (CTRL_EDIT, IDC_EDT_RDSP_FMV, IFASTBP_PROC::RDSP_TRANSFER, ifds::CurrYrFMV, CTRLFLAG_DEFAULT);

	AddControl (CTRL_STATIC, IDC_STC_RDSP_PREV_YR_GRANT_BOND, CTRLFLAG_GUI_FIELD);
	AddControl (CTRL_EDIT, IDC_EDT_RDSP_PREV_YR_GRANT_BOND, IFASTBP_PROC::RDSP_TRANSFER, ifds::PrevYrGrantBond, CTRLFLAG_DEFAULT);
	AddControl (CTRL_STATIC, IDC_STC_RDSP_PREV_YR_CONTRIB, CTRLFLAG_GUI_FIELD);
	AddControl (CTRL_EDIT, IDC_EDT_RDSP_PREV_YR_CONTRIB, IFASTBP_PROC::RDSP_TRANSFER, ifds::PrevYrContrib, CTRLFLAG_DEFAULT);
	AddControl (CTRL_STATIC, IDC_STC_RDSP_DAP_LDAP, CTRLFLAG_GUI_FIELD);
	AddControl (CTRL_STATIC, IDC_STC_RDSP_PREV_YR_RED, CTRLFLAG_GUI_FIELD);
	AddControl (CTRL_STATIC, IDC_STC_RDSP_NO_TAX_RED, CTRLFLAG_GUI_FIELD);
	AddControl (CTRL_STATIC, IDC_STC_RDSP_TAX_RED, CTRLFLAG_GUI_FIELD);
	AddControl (CTRL_EDIT, IDC_EDT_RDSP_PREV_YR_NO_TAX_RED, IFASTBP_PROC::RDSP_TRANSFER, ifds::PrevYrNonTaxRedAmt, CTRLFLAG_DEFAULT);
	AddControl (CTRL_EDIT, IDC_EDT_RDSP_PREV_YR_TAX_RED, IFASTBP_PROC::RDSP_TRANSFER, ifds::PrevYrTaxRedAmt, CTRLFLAG_DEFAULT);
	AddControl (CTRL_STATIC, IDC_STC_RDSP_DAP_LDAP_CRT,	CTRLFLAG_GUI_FIELD);
	AddControl (CTRL_EDIT, IDC_EDT_RDSP_NO_TAX_RED, IFASTBP_PROC::RDSP_TRANSFER, ifds::CurrYrNonTaxRedAmt, CTRLFLAG_DEFAULT);
	AddControl (CTRL_EDIT, IDC_EDT_RDSP_TAX_RED, IFASTBP_PROC::RDSP_TRANSFER, ifds::CurrYrTaxRedAmt, CTRLFLAG_DEFAULT);

}

//*****************************************************************************
bool RDSPTransfersDlg::doRefresh (GenericInterface * rpGICaller, const I_CHAR* szOriginalCommand)
{ 
	TRACE_METHOD( CLASSNAME, DOREFRESH );

	SetDlgCaption();

	ConnectControlsToData();

	LoadControl (IDC_EDT_RDSP_FROM_CONTRACT);
	LoadControl (IDC_EDT_RDSP_FROM_PLAN);
	LoadControl (IDC_EDT_RDSP_TO_CONTRACT);
	LoadControl (IDC_EDT_RDSP_TO_PLAN);	

	LoadControl (IDC_EDT_RDSP_CONTRIB);
	LoadControl (IDC_EDT_RDSP_ROLLOVERS);
	LoadControl (IDC_EDT_RDSP_CDS_GRANT);
	LoadControl (IDC_EDT_RDSP_CDS_BOND);
	LoadControl (IDC_EDT_RDSP_FMV);

	LoadControl (IDC_EDT_RDSP_PREV_YR_GRANT_BOND);
	LoadControl (IDC_EDT_RDSP_PREV_YR_CONTRIB);
	LoadControl (IDC_EDT_RDSP_PREV_YR_NO_TAX_RED);
	LoadControl (IDC_EDT_RDSP_PREV_YR_TAX_RED);
	LoadControl (IDC_EDT_RDSP_NO_TAX_RED);
	LoadControl (IDC_EDT_RDSP_TAX_RED);

	return true;
}

//******************************************************************************
bool RDSPTransfersDlg::doSend ( GenericInterface *rpGICaller,
							   const I_CHAR *szMessage)
{
	MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTGUI_CONDITION, CLASSNAME, I_("doSend"));

	bool bRet = true;

	bRet = BaseMainDlg::doSend (rpGICaller, szMessage);

	return bRet;
}

//**********************************************************************************
void RDSPTransfersDlg::ControlUpdated( UINT controlID, const DString &strValue )
{  
	MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTGUI_CONDITION, CLASSNAME, I_("ControlUpdated"));

	if( controlID == IDC_EDT_RDSP_CONTRIB ||
		controlID == IDC_EDT_RDSP_ROLLOVERS ||
		controlID == IDC_EDT_RDSP_CDS_GRANT ||
		controlID == IDC_EDT_RDSP_CDS_BOND ||
		controlID == IDC_EDT_RDSP_FMV ||
		controlID == IDC_EDT_RDSP_PREV_YR_GRANT_BOND ||
		controlID == IDC_EDT_RDSP_PREV_YR_CONTRIB ||
		controlID == IDC_EDT_RDSP_PREV_YR_NO_TAX_RED ||
		controlID == IDC_EDT_RDSP_PREV_YR_TAX_RED ||
		controlID == IDC_EDT_RDSP_NO_TAX_RED ||
		controlID == IDC_EDT_RDSP_TAX_RED )
	{	 
		LoadControl (controlID);
	}               	
}

//**********************************************************************************
void RDSPTransfersDlg::SetDlgCaption()
{
	TRACE_METHOD( CLASSNAME, I_( "SetDlgCaption" ) );

	DString dstrShrNum, dstrEntityName;
	CString strName;

	// Get Entity Name
	if ( !m_dstrAccountNum.empty() ) 
		dynamic_cast<DSTCWorkSession *>(getBFWorkSession())->getFirstSequenced01AccountholderEntityName(getDataGroupId(), m_dstrAccountNum, dstrEntityName);

	SetShrAcctCaption(dstrShrNum, m_dstrAccountNum, dstrEntityName);
}

//*****************************************************************************
SEVERITY RDSPTransfersDlg::doInit()
{
	TRACE_METHOD( CLASSNAME, I_("doInit"));

	DString dstrDecimalDigits;

	getParameter (ACCOUNT_NUM, m_dstrAccountNum);
	getParameter (CALLER, m_dstrCaller);
	getParameter (DECIMAL_DIGITS, dstrDecimalDigits);
	getParameter (TRANS_TYPE, m_TransType);
	getParameter (DEPOSIT_TYPE, m_DepositType);
	getParameter (RED_CODE, m_RedemptonCode);
	getParameter (I_( "EffectiveDate" ), m_EffectiveDate);

	if (!dstrDecimalDigits.empty ())
	{
		m_DecimalDigits = dstrDecimalDigits.asInteger();
	}

	m_bDialogInit = true;	

	return NO_CONDITION;
}

//*****************************************************************************
void RDSPTransfersDlg::enableDisableControls()
{
	bool bIsExternalTranferIn = false;

	bIsExternalTranferIn = (m_DepositType == EXTERNAL_RDSP_TRANSFER_IN) ? true : false; // 67 - External RDSP to RDSP Transfer

	GetDlgItem(IDC_EDT_RDSP_FROM_CONTRACT)->EnableWindow(true);
	GetDlgItem(IDC_EDT_RDSP_FROM_PLAN)->EnableWindow(true);
	GetDlgItem(IDC_EDT_RDSP_TO_CONTRACT)->EnableWindow(false);
	GetDlgItem(IDC_EDT_RDSP_TO_PLAN)->EnableWindow(false);
	
	GetDlgItem(IDC_EDT_RDSP_CONTRIB)->EnableWindow(bIsExternalTranferIn);
	GetDlgItem(IDC_EDT_RDSP_ROLLOVERS)->EnableWindow(bIsExternalTranferIn);
	GetDlgItem(IDC_EDT_RDSP_CDS_GRANT)->EnableWindow(bIsExternalTranferIn);
	GetDlgItem(IDC_EDT_RDSP_CDS_BOND)->EnableWindow(bIsExternalTranferIn);
	GetDlgItem(IDC_EDT_RDSP_FMV)->EnableWindow(bIsExternalTranferIn);

	GetDlgItem(IDC_EDT_RDSP_PREV_YR_GRANT_BOND)->EnableWindow(bIsExternalTranferIn);
	GetDlgItem(IDC_EDT_RDSP_PREV_YR_CONTRIB)->EnableWindow(bIsExternalTranferIn);
	GetDlgItem(IDC_EDT_RDSP_PREV_YR_NO_TAX_RED)->EnableWindow(bIsExternalTranferIn);
	GetDlgItem(IDC_EDT_RDSP_PREV_YR_TAX_RED)->EnableWindow(bIsExternalTranferIn);
	GetDlgItem(IDC_EDT_RDSP_NO_TAX_RED)->EnableWindow(bIsExternalTranferIn);
	GetDlgItem(IDC_EDT_RDSP_TAX_RED)->EnableWindow(bIsExternalTranferIn);
}

