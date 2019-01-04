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
// ^FILE   : TransSettLocDlg.h
// ^AUTHOR : Monica Vadeanu
// ^DATE   : November 10, 2003
//
// ^CLASS    : TransSettLocDlg
// ^SUBCLASS : TransSettLocDlg
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
#include "TransSettLocDlg.h"

#include <ifastbp\TransSettLocProcessIncludes.h>

#include <ifastcbo\dstcworksession.hpp>

extern CLASS_IMPORT const I_CHAR* CMD_GUI_SETTLEMENT_LOCATION_TRADE;
#include <bfproc\concretedialogcreator.hpp>
static ConcreteDialogCreator< TransSettLocDlg > dlgCreator( CMD_GUI_SETTLEMENT_LOCATION_TRADE );

#ifdef _DEBUG
   #define new DEBUG_NEW
   #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


namespace
{
   const I_CHAR * const CLASSNAME = I_( "TransSettLocDlg" );   
}

//******************************************************************************
TransSettLocDlg::TransSettLocDlg( CWnd* pParent, 
											 GenericInterfaceContainer* pGIC, 
											 GenericInterface* pGIParent, 
											 const Command& rCommand )
: BaseMainDlg( TransSettLocDlg::IDD, pParent, pGIC, pGIParent, rCommand )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );

	//{{AFX_DATA_INIT(TransSettLocDlg)
   // NOTE: the ClassWizard will add member initialization here
   //}}AFX_DATA_INIT
}

//******************************************************************************
TransSettLocDlg::~TransSettLocDlg()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************
void TransSettLocDlg::DoDataExchange(CDataExchange* pDX)
{
   BaseMainDlg::DoDataExchange( pDX );
   //{{AFX_DATA_MAP(TransSettLocDlg)
   // NOTE: the ClassWizard will add DDX and DDV calls here
   //}}AFX_DATA_MAP
}

//******************************************************************************
BEGIN_MESSAGE_MAP(TransSettLocDlg, BaseMainDlg)
//{{AFX_MSG_MAP(TransSettLocDlg)	
ON_BN_CLICKED(IDC_RB_FROM_ACCOUNT, OnRbFromAccount)
ON_BN_CLICKED(IDC_RB_TO_ACCOUNT, OnRbToAccount)
ON_BN_CLICKED(IDC_BTN_RESET, OnBtnReset)
ON_CBN_SELCHANGE(IDC_CMB_SETTLEMENT_LOCATION, OnCmbSelChangeSettlLoc)
ON_CBN_SELCHANGE(IDC_CMB_SETTLEMENT_METHOD, OnCmbSelChangeClearingMethod)
ON_EN_KILLFOCUS(IDC_EDT_DELIVERY, OnKillFocusEditDeliveryTo)
ON_EN_KILLFOCUS(IDC_EDT_FOR_ACCOUNT, OnKillFocusEditForAccount)
ON_EN_KILLFOCUS(IDC_EDT_IN_FAVOUR_OF, OnKillFocusEditInFavourOf)
	//}}AFX_MSG_MAP	
END_MESSAGE_MAP()

//******************************************************************************
void TransSettLocDlg::OnPostInitDialog()
{
   TRACE_METHOD( CLASSNAME, I_( "OnPostInitDialog" ) );
   CWaitCursor wait;
   
	DString dstr;
	getParent()->getField( this, IFASTBP_PROC::ORIGINAL_TRADE_CBO, ifds::TransNum, dstr );   
	dstr.strip();
   SetDlgItemText( IDC_TXT_TRANS_NUM, dstr.c_str() );

	AddControl( CTRL_COMBO, 
	            IDC_CMB_SETTLEMENT_LOCATION,    
					IFASTBP_PROC::FROM_TRANS_SETTLEMENT_LOCATION_CBO,      
					ifds::FrSettlLocCode,
		         CTRLFLAG_AUTO_UPDATE_ON_CHANGE | CTRLFLAG_INITCOMBO_BY_SUB_LIST ); 		

	AddControl( CTRL_COMBO, 
	            IDC_CMB_SETTLEMENT_METHOD,    
					IFASTBP_PROC::FROM_TRANS_SETTLEMENT_LOCATION_CBO,      
					ifds::FrClearingMethod,
		         CTRLFLAG_AUTO_UPDATE_ON_CHANGE | CTRLFLAG_INITCOMBO_BY_SUB_LIST );
	
	AddControl( CTRL_EDIT,  
	            IDC_EDT_DELIVERY,     
					IFASTBP_PROC::FROM_TRANS_SETTLEMENT_LOCATION_CBO, 
					ifds::FrDeliveryTo );  
	dynamic_cast<DSTEdit *>( GetControl( IDC_EDT_DELIVERY ) )->SetMaxCharNum( 35 );

	AddControl( CTRL_EDIT,  
	            IDC_EDT_FOR_ACCOUNT,     
					IFASTBP_PROC::FROM_TRANS_SETTLEMENT_LOCATION_CBO, 
					ifds::FrForAccount );  		         
	dynamic_cast<DSTEdit *>( GetControl( IDC_EDT_FOR_ACCOUNT ) )->SetMaxCharNum( 35 );

	AddControl( CTRL_EDIT,  
	            IDC_EDT_IN_FAVOUR_OF,     
					IFASTBP_PROC::FROM_TRANS_SETTLEMENT_LOCATION_CBO, 
					ifds::FrInFavourOf );  
	dynamic_cast<DSTEdit *>( GetControl( IDC_EDT_IN_FAVOUR_OF ) )->SetMaxCharNum( 35 );
	
	// Check From Account is a Clearing Account
	// If not, and Transfer and To Account is a Clearing Account, then enable To Account
   CButton *pFromAccountRadioButton = static_cast < CButton* >( GetDlgItem( IDC_RB_FROM_ACCOUNT ) );
	CButton *pToAccountRadioButton = static_cast < CButton* >( GetDlgItem( IDC_RB_TO_ACCOUNT ) );
	if ( NULL != pFromAccountRadioButton )
	{
		if ( 0 != _dstrFromClearingAccount.stripAll().length() )
		{
			pFromAccountRadioButton->EnableWindow( true );		
			pFromAccountRadioButton->SetCheck( 1 );
			DString dstr = I_( "From Account" );
			SetDlgItemText( IDC_SETTL_INSTR_TRADE_GROUP_BOX, dstr.c_str() );

			OnRbFromAccount();
		}
	}
	if ( NULL != pToAccountRadioButton )
	{
		// To Account will be enabled when Transfer (Exchange) to a Clearing Account
		if ( 0 != _dstrToClearingAccount.stripAll().length() )
		{
			pToAccountRadioButton->EnableWindow( true );		

			if ( 0 != _dstrFromClearingAccount.stripAll().length() )
				pToAccountRadioButton->SetCheck( 0 );
			else if ( 0 == _dstrFromClearingAccount.stripAll().length() )
			{
				pToAccountRadioButton->SetCheck( 1 );
				DString dstr = I_( "To Account" );
				SetDlgItemText( IDC_SETTL_INSTR_TRADE_GROUP_BOX, dstr.c_str() );
				OnRbToAccount();
			}
		}
		else if ( 0 == _dstrToClearingAccount.stripAll().length() ) 	
			pToAccountRadioButton->EnableWindow( false );		
	}			

	if ( I_( "TradesDlg" ) != _dstrFromScreen ) 
	{		
		GetDlgItem( IDC_BTN_RESET )->EnableWindow( false );		      
	}	
	else
	{	
		GetDlgItem( IDC_BTN_RESET )->EnableWindow( true );		      
	}
}

//******************************************************************************
SEVERITY TransSettLocDlg::doInit()
{
   SEVERITY sevRtn = NO_CONDITION;

	getParameter( TRANS_SETTLEMENT_LOCATION::FROM_SCREEN,           _dstrFromScreen );
	getParameter( TRANS_SETTLEMENT_LOCATION::PENDING_HISTORY,       _dstrPendingHist );
	getParameter( TRANS_SETTLEMENT_LOCATION::FROM_CLEARING_ACCOUNT, _dstrFromClearingAccount );
	getParameter( TRANS_SETTLEMENT_LOCATION::TO_CLEARING_ACCOUNT,   _dstrToClearingAccount );

   return(sevRtn);
}

//******************************************************************************
bool TransSettLocDlg::doRefresh( GenericInterface * rpGICaller, 
                                  const I_CHAR * szOriginalCommand )
{
	CButton *pFromAccountRadioButton = static_cast < CButton* >( GetDlgItem( IDC_RB_FROM_ACCOUNT ) );	
	if ( NULL != pFromAccountRadioButton )
	{
		int iFromCheckStatus = pFromAccountRadioButton->GetCheck();
		if ( 1 == iFromCheckStatus )
			OnRbFromAccount();
	}
	else 
	{
		CButton *pToAccountRadioButton = static_cast < CButton* >( GetDlgItem( IDC_RB_TO_ACCOUNT ) );
		if ( NULL != pToAccountRadioButton )
		{
			int iToCheckStatus = pToAccountRadioButton->GetCheck();
			if ( 1 == iToCheckStatus )
				OnRbToAccount();
		}
	}	

   return(true);
}

//******************************************************************************
void TransSettLocDlg::SetDlgCaption()
{
   TRACE_METHOD( CLASSNAME, I_( "SetDlgCaption" ) );

	DString dstrDlgCaption;
	if ( 0 != _dstrFromClearingAccount.stripAll().length() &&
		  0 == _dstrToClearingAccount.stripAll().length() )
	{
		dstrDlgCaption = I_( "Settlement Location at Transaction Level, from Clearing Account: " )
			            + _dstrFromClearingAccount;
	}
	else if ( 0 == _dstrFromClearingAccount.stripAll().length() &&
	     	    0 != _dstrToClearingAccount.stripAll().length() )
	{
		dstrDlgCaption = I_( "Settlement Location at Transaction Level, to Clearing Account: " )
			            + _dstrToClearingAccount;
	}
	else if ( 0 != _dstrFromClearingAccount.stripAll().length() &&
		       0 != _dstrToClearingAccount.stripAll().length() )
	{
		dstrDlgCaption = I_( "Settlement Location at Transaction Level, from Clearing Account: " )
			            + _dstrFromClearingAccount
							+ I_( ", to Clearing Account: " )
							+ _dstrToClearingAccount;
	}
	
	SetWindowText( dstrDlgCaption.c_str() );
}

//******************************************************************************
BOOL TransSettLocDlg::PreTranslateMessage(MSG* pMsg) 
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
void TransSettLocDlg::OnRbFromAccount()
{
	TRACE_METHOD( CLASSNAME, I_( "OnRbFromAccount" ) );
   CWaitCursor wait;

	CButton *pFromAccountRadioButton = static_cast < CButton* > ( GetDlgItem( IDC_RB_FROM_ACCOUNT ) );
	CButton *pToAccountRadioButton = static_cast < CButton* > ( GetDlgItem( IDC_RB_TO_ACCOUNT ) );
	if ( NULL != pFromAccountRadioButton )
	{
		pFromAccountRadioButton->SetCheck( 1 );
		DString dstr = I_( "From Account" );
		SetDlgItemText( IDC_SETTL_INSTR_TRADE_GROUP_BOX, dstr.c_str() );
	}
	if ( NULL != pToAccountRadioButton )	
		pToAccountRadioButton->SetCheck( 0 );	
	

	ReInitControl( IDC_CMB_SETTLEMENT_LOCATION,
                  IFASTBP_PROC::FROM_TRANS_SETTLEMENT_LOCATION_CBO,
                  ifds::FrSettlLocCode );
   	
	ReInitControl( IDC_CMB_SETTLEMENT_METHOD,
                  IFASTBP_PROC::FROM_TRANS_SETTLEMENT_LOCATION_CBO,
                  ifds::FrClearingMethod );

	ReInitControl( IDC_EDT_DELIVERY,
                  IFASTBP_PROC::FROM_TRANS_SETTLEMENT_LOCATION_CBO,
                  ifds::FrDeliveryTo );
	
	ReInitControl( IDC_EDT_FOR_ACCOUNT,
                  IFASTBP_PROC::FROM_TRANS_SETTLEMENT_LOCATION_CBO,
                  ifds::FrForAccount );

	ReInitControl( IDC_EDT_IN_FAVOUR_OF,
                  IFASTBP_PROC::FROM_TRANS_SETTLEMENT_LOCATION_CBO,
                  ifds::FrInFavourOf );

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
									  dstrTransType );  
		dstrTransType.stripAll();
		if ( dstrTransType == I_( "Transfer" ) || 			  
			  dstrTransType == I_( "AllFundTransfer" ) )
		{
			DString dstr = I_( "From and To free format Instructions will be the same for a Transfer" );	
			AfxMessageBox( dstr.c_str(), MB_OK );
		}
		else if ( dstrTransType == I_( "Exchange" ) )
		{
			DString dstr = I_( "From and To Instructions will be the same for an Exchange" );	
			AfxMessageBox( dstr.c_str(), MB_OK );
		}
	}
}

//******************************************************************************
void TransSettLocDlg::OnRbToAccount()
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
		DString dstr = I_( "To Account" );
		SetDlgItemText( IDC_SETTL_INSTR_TRADE_GROUP_BOX, dstr.c_str() );
	}
	

	ReInitControl( IDC_CMB_SETTLEMENT_LOCATION,
                  IFASTBP_PROC::TO_TRANS_SETTLEMENT_LOCATION_CBO,
                  ifds::ToSettlLocCode );   	

	ReInitControl( IDC_CMB_SETTLEMENT_METHOD,
                  IFASTBP_PROC::TO_TRANS_SETTLEMENT_LOCATION_CBO,
                  ifds::ToClearingMethod );

	ReInitControl( IDC_EDT_DELIVERY,
                  IFASTBP_PROC::TO_TRANS_SETTLEMENT_LOCATION_CBO,
                  ifds::ToDeliveryTo );
	
	ReInitControl( IDC_EDT_FOR_ACCOUNT,
                  IFASTBP_PROC::TO_TRANS_SETTLEMENT_LOCATION_CBO,
                  ifds::ToForAccount );

	ReInitControl( IDC_EDT_IN_FAVOUR_OF,
                  IFASTBP_PROC::TO_TRANS_SETTLEMENT_LOCATION_CBO,
                  ifds::ToInFavourOf );

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
		if ( dstrTransType == I_( "Transfer" ) || 			  
			  dstrTransType == I_( "AllFundTransfer" ) )
		{
			DString dstr = I_( "From and To free format Instructions will be the same for a Transfer" );	
			AfxMessageBox( dstr.c_str(), MB_OK );					
		}
		else if ( dstrTransType == I_( "Exchange" ) )
		{
			DString dstr = I_( "From and To Instructions will be the same for an Exchange" );	
			AfxMessageBox( dstr.c_str(), MB_OK );
		}
	}
}

//******************************************************************************
void TransSettLocDlg::OnBtnReset()
{
	if ( 0 != _dstrFromClearingAccount.stripAll().length() )	
		getParent()->reset( this, IFASTBP_PROC::FROM_TRANS_SETTLEMENT_LOCATION_CBO );

	if ( 0 != _dstrToClearingAccount.stripAll().length() )
		getParent()->reset( this, IFASTBP_PROC::TO_TRANS_SETTLEMENT_LOCATION_CBO );
	
	doRefresh( this, NULL );
}

//******************************************************************************
void TransSettLocDlg::OnCmbSelChangeSettlLoc()
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
											     IFASTBP_PROC::FROM_TRANS_SETTLEMENT_LOCATION_CBO, 
												  ifds::FrSettlLocCode, 
											     dstrSettlLocCode,
												  false );  
					getParent()->setField( this, 
											     IFASTBP_PROC::TO_TRANS_SETTLEMENT_LOCATION_CBO, 
												  ifds::ToSettlLocCode, 
											     dstrSettlLocCode, 
												  false );  
				}
			}
		}
	}	
}

//******************************************************************************
void TransSettLocDlg::OnCmbSelChangeClearingMethod()
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
										     IFASTBP_PROC::FROM_TRANS_SETTLEMENT_LOCATION_CBO, 
											  ifds::FrClearingMethod, 
										     dstrSettlLocCode,
											  false );  
				getParent()->setField( this, 
										     IFASTBP_PROC::TO_TRANS_SETTLEMENT_LOCATION_CBO, 
											  ifds::ToClearingMethod, 
										     dstrSettlLocCode, 
											  false );  
			}
		}
	}
}

//******************************************************************************
void TransSettLocDlg::OnKillFocusEditDeliveryTo()
{	
	CString cstrDeliveryTo;
	GetDlgItem(IDC_EDT_DELIVERY)->GetWindowText( cstrDeliveryTo );
	DString dstrDeliveryTo( cstrDeliveryTo );			

	setFromToFields( dstrDeliveryTo, ifds::FrDeliveryTo, ifds::ToDeliveryTo );		
}

//******************************************************************************
void TransSettLocDlg::OnKillFocusEditForAccount()
{
	CString cstrForAccount;
	GetDlgItem( IDC_EDT_FOR_ACCOUNT )->GetWindowText( cstrForAccount );
	DString dstrForAccount( cstrForAccount );			

	setFromToFields( dstrForAccount, ifds::FrForAccount, ifds::ToForAccount );
}

//******************************************************************************
void TransSettLocDlg::OnKillFocusEditInFavourOf()	
{
	CString cstrInFavourOf;
	GetDlgItem( IDC_EDT_IN_FAVOUR_OF )->GetWindowText( cstrInFavourOf );
	DString dstrInFavourOf( cstrInFavourOf );			

	setFromToFields( dstrInFavourOf, ifds::FrInFavourOf, ifds::ToInFavourOf );
}

//******************************************************************************
void TransSettLocDlg::setFromToFields( const DString &dstrFieldValue, 
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
										     IFASTBP_PROC::FROM_TRANS_SETTLEMENT_LOCATION_CBO, 
										     fieldIdFrom, 
										     dstrFieldValue );  
				getParent()->setField( this, 
										     IFASTBP_PROC::TO_TRANS_SETTLEMENT_LOCATION_CBO, 
										     fieldIdTo, 
										     dstrFieldValue );  

			}
		}
	}
}

//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastgui/TransSettLocDlg.cpp-arc  $
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
