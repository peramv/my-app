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
// ^FILE   :TradeSettlementLocationsDlg.cpp
// ^AUTHOR : 
// ^DATE   :July, 2009 
//
// ----------------------------------------------------------
//
// ^CLASS    : TradeSettlementLocationsDlg
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :  
//
//******************************************************************************

#include "stdafx.h"
#include "mfdstc.h"

#include "TradeSettlementLocationsDlg.h"
#include <configmanager.hpp>
#include <uibase\DSTEdit.h>
#include <uibase\ifdslistctrl.h>

#include <ifastbp\mfcaninterprocparam.hpp>
#include <configmanager.hpp>
#include <ifastcsi\csisession.h>
#include <ifastcsi\ifastcsi.h>
#include <uibase\dstgridwnd.h>
#include <uibase\dstlistctrl.h>
#include <ifastcbo\dstcommonfunction.hpp>
#include <ifastbp\mfcaninterprocparam.hpp>
#include <ifastbp\TradeSettleLocationsProcessincludes.h>
#include <uibase\dstedit.h>
#include <ifastcbo\dstcworksession.hpp>
#include <assert.h>

#ifndef INCLUDED_ASSERT_H
#define INCLUDED_ASSERT_H
#include <assert.h>
#endif

extern CLASS_IMPORT const I_CHAR* CMD_GUI_TRADE_SETTLEMENT_LOCATIONS;
#include <bfproc\concretedialogcreator.hpp>
static ConcreteDialogCreator< TradeSettlementLocationsDlg > dlgCreator( CMD_GUI_TRADE_SETTLEMENT_LOCATIONS ); 

#ifdef _DEBUG
   #define new DEBUG_NEW
   #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

namespace
{
   const I_CHAR * const CLASSNAME			= I_("TradeSettlementLocationsDlg");
   const I_CHAR * const CALLER				= I_("Caller");
   const I_CHAR * const TRANS_HISTORY_DLG	= I_("TransactionHistoryDlg");
   const I_CHAR * const DECIMAL_DIGITS  	= I_("DecimalDigits");
   
   const I_CHAR *LV_TRADE_SETTLEMENT_LOCATIONS = I_( "Trade Settlement Locations" );
}

namespace UAF
{
   extern CLASS_IMPORT I_CHAR * const TRADE_SETTLEMENT_LOCS;
}

namespace ifds
{
	extern CLASS_IMPORT const BFTextFieldId TradeSettleLocationsListHeading;
}

//*****************************************************************************
// Public methods
//*****************************************************************************
TradeSettlementLocationsDlg::TradeSettlementLocationsDlg( CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: BaseMainDlg( TradeSettlementLocationsDlg::IDD, pParent, pGIC, pGIParent, rCommand, CLASSNAME ),
m_Caller (NULL_STRING),
m_DecimalDigits (0)
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   //{{AFX_DATA_INIT(TradeSettlementLocationsDlg)
   //}}AFX_DATA_INIT
}

//*****************************************************************************
void TradeSettlementLocationsDlg::DoDataExchange( CDataExchange* pDX )
{
   BaseMainDlg::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(TradeSettlementLocationsDlg)
   //}}AFX_DATA_MAP
}

//*****************************************************************************
BEGIN_MESSAGE_MAP(TradeSettlementLocationsDlg, BaseMainDlg)
//{{AFX_MSG_MAP(TradeSettlementLocationsDlg)
ON_BN_CLICKED(IDC_BTN_ADD, OnBtnAdd)
ON_BN_CLICKED(IDC_BTN_DELETE, OnBtnDelete)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//*****************************************************************************
// Message handlers
//*****************************************************************************
BOOL TradeSettlementLocationsDlg::OnInitDialog() 
{
	TRACE_METHOD( CLASSNAME, ONINITDIALOG );
	BaseMainDlg::OnInitDialog(); 

	AddListControl (CLASSNAME, IDC_LV_SETTLEMNT_LOCATIONS, LV_TRADE_SETTLEMENT_LOCATIONS, ifds::TradeSettleLocationsListHeading, IFASTBP_PROC::TRADE_MULTI_SETTLEMENT_LOC_LIST, 0, true);

	AddControl (CTRL_COMBO, IDC_CMB_SETTL_LOCATIONS, IFASTBP_PROC::TRADE_MULTI_SETTLEMENT_LOC_LIST, ifds::SettleLocCode, CTRLFLAG_INITCOMBO_BY_SUB_LIST, IDC_LV_SETTLEMNT_LOCATIONS);
	AddControl (CTRL_EDIT,IDC_EDT_AMOUNT, IFASTBP_PROC::TRADE_MULTI_SETTLEMENT_LOC_LIST, ifds::TransClrSettlAmt, CTRLFLAG_DEFAULT, IDC_LV_SETTLEMNT_LOCATIONS);
	AddControl (CTRL_EDIT,IDC_EDT_INFAVOROF, IFASTBP_PROC::TRADE_MULTI_SETTLEMENT_LOC_LIST, ifds::InFavourOf, CTRLFLAG_DEFAULT, IDC_LV_SETTLEMNT_LOCATIONS);
	
	return TRUE;
}

//******************************************************************************
void TradeSettlementLocationsDlg::OnPostInitDialog()
{
	TRACE_METHOD( CLASSNAME, ONPOSTINITDIALOG );

	SetUserAccesFunctionCode (UAF::TRADE_SETTLEMENT_LOCS); 
	addControlGroupIDForPermissionCheck (IDC_LV_SETTLEMNT_LOCATIONS);  

  	DSTEdit *edit = dynamic_cast<DSTEdit *>( GetControl (IDC_EDT_AMOUNT));
	edit->SetAllowedChars(I_("0123456789."));
	edit->setInputAllowedUnsignedDecimal();
    edit->setMaxNumDigitsAfterDecimalPoint(m_DecimalDigits);

	ConnectControlsToData ();
	LoadControls ();
	doRefresh (this, NULL_STRING);
}

//*****************************************************************************
void TradeSettlementLocationsDlg::OnBtnAdd() 
{
	TRACE_METHOD( CLASSNAME, I_("OnBtnAdd") );  

	AddToListControl (IDC_LV_SETTLEMNT_LOCATIONS);
}

//*****************************************************************************
void TradeSettlementLocationsDlg::OnBtnDelete() 
{
	TRACE_METHOD( CLASSNAME, I_("OnBtnDelete") );   

	DeleteFromListControl (IDC_LV_SETTLEMNT_LOCATIONS);
}
//*****************************************************************************
bool TradeSettlementLocationsDlg::doRefresh (GenericInterface * rpGICaller, 
                                 const I_CHAR* szOriginalCommand)
{ 
	TRACE_METHOD( CLASSNAME, DOREFRESH );

	bool bEnable = m_Caller == TRANS_HISTORY_DLG ? false : true;

	GetDlgItem (IDC_BTN_ADD)->EnableWindow (bEnable);
	GetDlgItem (IDC_BTN_DELETE)->EnableWindow (bEnable);
	GetDlgItem (IDOK)->EnableWindow (bEnable);

	LoadListControl (IDC_LV_SETTLEMNT_LOCATIONS);

	return true;
}


//**********************************************************************************
void TradeSettlementLocationsDlg::ControlUpdated( UINT controlID, const DString &strValue )
{  
}

//*****************************************************************************
SEVERITY TradeSettlementLocationsDlg::doInit()
{
	TRACE_METHOD( CLASSNAME, I_("doInit"));

	DString dstrDecimalDigits;

	getParameter (CALLER, m_Caller);
	getParameter (DECIMAL_DIGITS, dstrDecimalDigits);
		
	if (!dstrDecimalDigits.empty ())
	{
		m_DecimalDigits = dstrDecimalDigits.asInteger();
	}

	return NO_CONDITION;
}
//******************************************************************************
/* $Log::   
*/