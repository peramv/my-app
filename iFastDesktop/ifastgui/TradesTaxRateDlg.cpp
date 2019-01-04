//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by International Financial Data Services
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2003 by International Financial Data Services
//
//******************************************************************************
//
// ^FILE   : TradesTaxRateDlg.cpp
// ^AUTHOR : 
// ^DATE   : Aug 23, 2003
//
// ^CLASS    : TradesTaxRateDlg
// ^SUBCLASS : BaseMainDlg
//
// ^CLASS DESCRIPTION : 
//
//******************************************************************************

#include "stdafx.h"

#include "mfdstc.h"
#include "TradesTaxRateDlg.h"
#include <ifastbp\TradesTaxRateProcessIncludes.h>
#include <ifastcbo\DSTCommonFunction.hpp>
#include <ifastcsi\ifastcsi.h>
#include <uibase\DSTEdit.h>
#include <uibase\dstbutton.h>
#include <ifastcbo\DSTCWorkSession.hpp>
#include <ifastbp\mfcaninterprocparam.hpp>
extern CLASS_IMPORT const I_CHAR* CMD_GUI_TRADES_TAXRATE;
#include <bfproc\concretedialogcreator.hpp>
static ConcreteDialogCreator< TradesTaxRateDlg > dlgCreator( CMD_GUI_TRADES_TAXRATE );

#ifdef _DEBUG
   #define new DEBUG_NEW
   #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

namespace
{
   const I_CHAR * const CLASSNAME = I_( "TradesTaxRateDlg" );
   const I_CHAR * const YES       = I_( "Y" );
}

namespace CND
{  // Conditions used
   extern const long GUI_ERR_UNKNOWN_EXCEPTION;
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId AddPerm;
   extern CLASS_IMPORT const BFTextFieldId DelPerm;
}

namespace UAF
{
   extern CLASS_IMPORT I_CHAR * const TRADE_TAX_RATE_OVERRIDE;
}

//******************************************************************************
// Constructor
//******************************************************************************
TradesTaxRateDlg::TradesTaxRateDlg( CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
:BaseMainDlg( TradesTaxRateDlg::IDD, pParent, pGIC, pGIParent, rCommand ),
m_bOverride(false)
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );

   //{{AFX_DATA_INIT( TradesTaxRateDlg )
   //}}AFX_DATA_INIT
}

//******************************************************************************
// Destructor
//******************************************************************************
TradesTaxRateDlg::~TradesTaxRateDlg()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************
// Called by MFC framework to exchange and validate dialog data
//******************************************************************************
void TradesTaxRateDlg::DoDataExchange( CDataExchange* pDX )
{
   BaseMainDlg::DoDataExchange( pDX );
   //{{AFX_DATA_MAP( TradesTaxRateDlg )   
   //}}AFX_DATA_MAP
}

//******************************************************************************
// MFC Message Map
//******************************************************************************

BEGIN_MESSAGE_MAP( TradesTaxRateDlg, BaseMainDlg )
//{{AFX_MSG_MAP( TradesTaxRateDlg )
//ON_BN_CLICKED( IDOK, OnBtnOK )
//ON_BN_CLICKED( IDCANCEL, OnBtnCancel )
//ON_BN_CLICKED( IDRESET, OnBtnReset )
ON_BN_CLICKED( IDC_CHK_OVERRIDE, OnChkOverride )
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//******************************************************************************
// Initialization of Dialog, get InterProcess Global data and sets up the 
// caption in the title bar.
//******************************************************************************
BOOL TradesTaxRateDlg::OnInitDialog() 
{
   TRACE_METHOD( CLASSNAME, ONINITDIALOG );
   BaseMainDlg::OnInitDialog();

   return(TRUE);  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}

//******************************************************************************
// Call by based architecture.  Controls are initialized here by calling the
// addControls() method.  The More button is enable/disable based on the CBO
// data.
//******************************************************************************
void TradesTaxRateDlg::OnPostInitDialog()
{
   CWaitCursor wait;
   TRACE_METHOD( CLASSNAME, I_( "OnPostInitDialog" ) );

   SetUserAccesFunctionCode( UAF::TRADE_TAX_RATE_OVERRIDE );

   addControls( );

   ( (CButton* )GetDlgItem( IDC_CHK_OVERRIDE ) )->SetCheck(m_bOverride == 1 );

	if ( hasUpdatePermission(  UAF::TRADE_TAX_RATE_OVERRIDE ) )
	{
		( (CButton* )GetDlgItem( IDC_CHK_OVERRIDE ) )->EnableWindow( true );
	}
	else
	{
		( (CButton* )GetDlgItem( IDC_CHK_OVERRIDE ) )->EnableWindow( false );
	}
}

//******************************************************************************
// doInit method is not used.
//******************************************************************************
SEVERITY TradesTaxRateDlg::doInit()
{   
   return(NO_CONDITION);
}

//******************************************************************************
// This method sets up the custom controls to the correct data set.
//******************************************************************************
void TradesTaxRateDlg::addControls( )
{
   AddControl( CTRL_EDIT,  IDC_EDT_FED_RATE, IFASTBP_PROC::TRADES_LIST, ifds::FedRate, CTRLFLAG_DEFAULT );   
   // Don't allow negatives for this control
	DSTEdit *dstEditFedTaxRate = dynamic_cast< DSTEdit * >( GetDlgItem( IDC_EDT_FED_RATE ) );
	if ( NULL != dstEditFedTaxRate )
	{
		DString dstrPercentageMask = DSTCommonFunctions::getMask( ifds::FedRate );
      int iDecimalPointPos = dstrPercentageMask.find( I_( "." ) );				
		dstEditFedTaxRate->AllowNonnegativeDecimalNumbers( iDecimalPointPos, 
					                                          dstrPercentageMask.length() - iDecimalPointPos - 2 );
	}
	AddControl( CTRL_EDIT,  IDC_EDT_PROV_RATE, IFASTBP_PROC::TRADES_LIST, ifds::ProvRate, CTRLFLAG_DEFAULT);
   // Don't allow negatives for this control
	DSTEdit *dstEditProvTaxRate = dynamic_cast< DSTEdit * >( GetDlgItem( IDC_EDT_PROV_RATE ) );
	if ( NULL != dstEditProvTaxRate )
	{
		DString dstrPercentageMask = DSTCommonFunctions::getMask( ifds::ProvRate );
      int iDecimalPointPos = dstrPercentageMask.find( I_( "." ) );		
		dstEditProvTaxRate->AllowNonnegativeDecimalNumbers( iDecimalPointPos, 
					                                          dstrPercentageMask.length() - iDecimalPointPos - 2 );
	}
	
	AddControl( CTRL_COMBO, IDC_CMB_FED_RATE_TYPE,  IFASTBP_PROC::TRADES_LIST, ifds::TransRatePUDFed,  CTRLFLAG_INITCOMBO_BY_SUB_LIST );
   AddControl( CTRL_COMBO, IDC_CMB_PROV_RATE_TYPE, IFASTBP_PROC::TRADES_LIST, ifds::TransRatePUDProv, CTRLFLAG_INITCOMBO_BY_SUB_LIST);
   //AddControl( CTRL_CHECKBOX, IDC_CHK_OVERRIDE,     IFASTBP_PROC::TRADES_LIST,    ifds::OverrideTax, CTRLFLAG_DEFAULT);
   
   ConnectControlsToData ();
   LoadControls();

   DString dstrOverrideTax;
   getParent()->getField( this, IFASTBP_PROC::TRADES_LIST, ifds::OverrideTax,dstrOverrideTax, false );
   m_bOverride = ( dstrOverrideTax == I_("Y") );
   bool bEnable = (m_bOverride == 1);

   GetDlgItem( IDC_EDT_FED_RATE )->EnableWindow( bEnable );
	GetDlgItem( IDC_EDT_PROV_RATE )->EnableWindow( bEnable );
	GetDlgItem( IDC_CMB_FED_RATE_TYPE )->EnableWindow( bEnable );
	GetDlgItem( IDC_CMB_PROV_RATE_TYPE )->EnableWindow( bEnable );
}

//******************************************************************************
// Method to refresh dialog controls
// @param   GenericInterface *rpGICaller - pointer to the calling object
// @param   const I_CHAR *szOriginalCommand - Not used in this case, but 
//                      can be used to instruct special processing.
//******************************************************************************
bool TradesTaxRateDlg::doRefresh( GenericInterface * rpGICaller, 
                                  const I_CHAR * szOriginalCommand )
{
   LoadControls();

   return(true);
}

//******************************************************************************
BOOL TradesTaxRateDlg::PreTranslateMessage(MSG* pMsg) 
{
   return(BaseMainDlg::PreTranslateMessage( pMsg ));
}

//****************************************************************************** 
void TradesTaxRateDlg::OnChkOverride()
{
	bool  bEnable = true;

	if( ((CButton *) GetDlgItem( IDC_CHK_OVERRIDE ))->GetCheck() != 1 )
	{		
		getParent()->setField( this, IFASTBP_PROC::TRADES_LIST, ifds::OverrideTax, I_("N"), false );
		LoadControls();
		bEnable = false;
	}
	else
	{
		getParent()->setField( this, IFASTBP_PROC::TRADES_LIST, ifds::OverrideTax, I_("Y"), false );
		LoadControls();
	}

	GetDlgItem( IDC_EDT_FED_RATE )->EnableWindow( bEnable );
	GetDlgItem( IDC_EDT_PROV_RATE )->EnableWindow( bEnable );
	GetDlgItem( IDC_CMB_FED_RATE_TYPE )->EnableWindow( bEnable );
	GetDlgItem( IDC_CMB_PROV_RATE_TYPE )->EnableWindow( bEnable );
}


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/TradesTaxRateDlg.cpp-arc  $
// 
//    Rev 1.7   Oct 08 2003 15:27:10   VADEANUM
// PTS 10022550 - Allow only non-negative digits to be entered for Fed and Prov Tax Rate.
// 
//    Rev 1.6   Sep 23 2003 14:08:48   VADEANUM
// PTS 10021831 - Withholding Tax Security Band.
// 
//    Rev 1.5   Sep 20 2003 10:35:16   VADEANUM
// PTS 10021736 - Withholding Tax Default Rates.
// 
//    Rev 1.4   Sep 19 2003 13:42:22   VADEANUM
// PTS 10021736 - Wothholding Tax Default Rates - work in progress.
// 
//    Rev 1.3   Sep 08 2003 12:37:10   FENGYONG
// When override checkbox checked, nomatter if enter the taxrate, the value on the taxrate box will be treate as override value.
// 
//    Rev 1.2   Sep 08 2003 10:25:06   FENGYONG
// Set default value by Override tax flag
// 
//    Rev 1.1   Aug 15 2003 17:37:52   FENGYONG
// Add check box Override
// 
//    Rev 1.0   Aug 15 2003 10:28:00   FENGYONG
// Initial Revision
// 
 */


