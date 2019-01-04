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
//    Copyright 2002 by DST Systems, Inc.
//
//******************************************************************************
//
// ^FILE   : AccrualsDlg.cpp
// ^AUTHOR : 
// ^DATE   : Jan 04, 2002
//
// ----------------------------------------------------------
//
// ^CLASS    : AccrualsDlg
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"

#include "mfdstc.h"
#include <bfproc\AbstractProcess.hpp>
#include "AccrualsDlg.h"
#include <ifastbp\AccrualsProcessIncludes.h>
#include <uibase\DSTComboBox.h>
#include <ifastcbo\DSTCommonFunction.hpp>
#include <ifastcbo\DSTCWorkSession.hpp>
#include <uibase\DSTListCtrl.h>
#include <ifastbp\FundClassProcessIncludes.h>

extern CLASS_IMPORT const I_CHAR* CMD_BPROC_FUNDCLASS;
extern CLASS_IMPORT const I_CHAR* CMD_GUI_ACCRUALS;
#include <bfproc\concretedialogcreator.hpp>
static ConcreteDialogCreator< AccrualsDlg > dlgCreator( CMD_GUI_ACCRUALS );

namespace
{
   const I_CHAR * const CLASSNAME = I_( "AccrualsDlg" );
   const I_CHAR * const LV_INTEREST_ACCRUALS = I_( "InterestAccrualsList" );
   const I_CHAR * const LV_MF_ACCRUALS = I_( "ManagementFeeAccrualsList" );
   const I_CHAR * const LV_MFR_ACCRUALS = I_( "ManagementRebateFeeAccrualsList" );
   const I_CHAR * const ALT_MGMT_FEE_TYPE = I_( "0002" );
   const I_CHAR * const NO = I_( "N" );
   const I_CHAR * const YES = I_( "Y" );
}

namespace CND
{
   extern const long GUI_ERR_UNKNOWN_EXCEPTION;
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId AccrualSummary;
   extern CLASS_IMPORT const BFDecimalFieldId AmtPaid;
   extern CLASS_IMPORT const BFDateFieldId EndDate;
   extern CLASS_IMPORT const BFTextFieldId InterestAccrualHeadingSet;
   extern CLASS_IMPORT const BFTextFieldId MFAccrualHeadingSet;
   extern CLASS_IMPORT const BFTextFieldId MFAltAccrualHeadingSet;
   extern CLASS_IMPORT const BFTextFieldId MFRAccrualHeadingSet;
   extern CLASS_IMPORT const BFNumericFieldId MgmtFeeType;
   extern CLASS_IMPORT const BFDateFieldId StartDate;
}

//******************************************************************************
// MFC Message Map
//******************************************************************************

BEGIN_MESSAGE_MAP(AccrualsDlg, BaseMainDlg)
//{{AFX_MSG_MAP(InterestAccrualDlg)
ON_CBN_SELCHANGE ( IDC_CMB_ACCRUAL_TYPE, OnSelchangeCmbAccrualType )
ON_EN_SETFOCUS ( IDC_EDT_FUND_CODE, OnSetFocusSearchControls )
ON_EN_SETFOCUS ( IDC_EDT_FUND_CODE2, OnSetFocusSearchControls )
ON_EN_SETFOCUS ( IDC_EDT_FUND_NBR, OnSetFocusSearchControls )
ON_EN_SETFOCUS ( IDC_EDT_CLASS_CODE, OnSetFocusSearchControls )
ON_CBN_SETFOCUS ( IDC_CMB_ACCRUAL_TYPE, OnSetFocusSearchControls )
ON_BN_CLICKED ( IDC_DTP_START_DATE, OnSetFocusSearchControls )
ON_BN_CLICKED ( IDC_DTP_END_DATE, OnSetFocusSearchControls )
ON_MESSAGE ( UM_OPENFUNDCLASSLISTDLG, OpenFundClassListDlg )
ON_BN_CLICKED ( IDC_BTN_MORE, OnBtnMore )
ON_BN_CLICKED ( IDC_BTN_SEARCH, OnBtnSearch )
ON_BN_CLICKED ( IDC_RB_DETAILS, OnRbDetails )
ON_BN_CLICKED ( IDC_RB_TOTALS_BY_FUND, OnRbTotalsByFund )
ON_BN_CLICKED ( IDC_CB_INCLUDE_UNSETTLED_TRADES, OnChkIncUnStlTrades )
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//******************************************************************************
// MFC DataExchange Map
//******************************************************************************

void AccrualsDlg::DoDataExchange(CDataExchange* pDX)
{
   BaseMainDlg::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(InterestAccrualDlg)
   DDX_Control(pDX, IDC_RB_DETAILS, m_btn_details);
   DDX_Control(pDX, IDC_RB_TOTALS_BY_FUND, m_btn_totals);
   DDX_Check(pDX, IDC_CB_INCLUDE_UNSETTLED_TRADES, m_includeUnsettledTrades);
   //}}AFX_DATA_MAP
}

//******************************************************************************
// Constructor
//******************************************************************************

AccrualsDlg::AccrualsDlg ( CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
:BaseMainDlg( AccrualsDlg::IDD, pParent, pGIC, pGIParent, rCommand, CLASSNAME )
, _bDetails (true)
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );

   //{{AFX_DATA_INIT(InterestAccrualDlg)
   //}}AFX_DATA_INIT
}

//******************************************************************************
// Destructor
//******************************************************************************

AccrualsDlg::~AccrualsDlg()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************
// Initializes the Dialog by setting up the captions with Account information.
// Sets up all the controls and defaults to interest accruals
// @returns - BOOL true.
//******************************************************************************

BOOL AccrualsDlg::OnInitDialog() 
{
   TRACE_METHOD( CLASSNAME, ONINITDIALOG );

   BaseMainDlg::OnInitDialog();
   DString dstrMarket = DSTCommonFunctions::getMarket();
   _bCanLuxMarket = ( dstrMarket == MARKET_IDS::CANADA || dstrMarket == MARKET_IDS::LUXEMBOURG );

   DString dstrShrNum, dstrAccountNum, dstrEntityName;
   getParent()->getField(this, ifds::ShrNum, dstrShrNum);      
   getParent()->getField( this, ifds::AccountNum, dstrAccountNum );  
   SetAccount( dstrAccountNum );   
   dynamic_cast<DSTCWorkSession *>(getBFWorkSession())->getFirstSequenced01AccountholderEntityName( getDataGroupId(), 
                                                                                                    dstrAccountNum,                                                                                                     dstrEntityName );
   SetShrAcctCaption(dstrShrNum, dstrAccountNum, dstrEntityName);

   addControls( ); 
   ConnectListToData ( IDC_LV_INTEREST_ACCRUED, true );
   ConnectListToData ( IDC_LV_MF, true );
   ConnectListToData ( IDC_LV_MF_REBATE, true );
   loadInterestAccuralSearch ( );
   return(TRUE);
}

//******************************************************************************
// This procedure will show/hide the Fund Number edit box.   When the the Fund
// Number edit box is shown, a smaller version of the Fund Code box 
// ( IDC_EDT_FUND_CODE )is shown and the original Fund Code box 
// ( IDC_EDT_FUND_CODE2 ) is hidden.
// @param   bool bshowFundNbr - Fund Number box shown ( true )
//                              Fund Number box hidden ( false )
// @returns void.
//******************************************************************************

void AccrualsDlg::showFundNumberControl( bool bshowFundNbr )
{      
   GetDlgItem( IDC_EDT_FUND_NBR )->ShowWindow( bshowFundNbr );
   GetDlgItem( IDC_EDT_FUND_CODE )->ShowWindow( !bshowFundNbr );
   GetDlgItem( IDC_EDT_FUND_CODE2 )->ShowWindow( bshowFundNbr );   
}

//******************************************************************************
// All the control hookups are done in this procedure.  This is called by the 
// OnInitDialog function.
// @returns void.
//******************************************************************************

void AccrualsDlg::addControls( )
{
   // Accrual Type is on its own group so that it will not be loaded by ConnectControlsToData

   AddControl( CTRL_COMBO, IDC_CMB_ACCRUAL_TYPE, BF::NullContainerId, ifds::NullFieldId, CTRLFLAG_GUI_FIELD, DO_NOT_CONNECT.getId() );      
   DSTComboBox* pComboBox = dynamic_cast<DSTComboBox*>( GetDlgItem( IDC_CMB_ACCRUAL_TYPE ) );
   pComboBox->FillInSubstituteValues ( BFContainerId( ifds::AccrualType.getId() ) );   

   //Currently we will default to Interest Accrual, but this may need to be change later.
   pComboBox->SetCurSel ( 0 );  

   if( !_bCanLuxMarket )
   {
      AddControl( CTRL_EDIT, IDC_EDT_FUND_CODE, BF::NullContainerId, ifds::NullFieldId, CTRLFLAG_DEFAULT, 0 );
      showFundNumberControl ( false );
   }
   else
   {
      AddControl( CTRL_EDIT, IDC_EDT_FUND_NBR, BF::NullContainerId, ifds::NullFieldId, CTRLFLAG_DEFAULT, 0 );
      AddControl( CTRL_EDIT, IDC_EDT_FUND_CODE2, BF::NullContainerId, ifds::NullFieldId, CTRLFLAG_DEFAULT, 0 );
      showFundNumberControl ( true );
   }
   AddControl( CTRL_EDIT, IDC_EDT_CLASS_CODE, BF::NullContainerId, ifds::NullFieldId, CTRLFLAG_DEFAULT, 0 );
   AddControl( CTRL_DATE, IDC_DTP_START_DATE, BF::NullContainerId, ifds::NullFieldId, CTRLFLAG_DEFAULT, 0 );
   AddControl( CTRL_DATE, IDC_DTP_END_DATE, BF::NullContainerId, ifds::NullFieldId, CTRLFLAG_DEFAULT, 0 );
   m_includeUnsettledTrades = false;

   AddListControl( CLASSNAME, IDC_LV_INTEREST_ACCRUED, LV_INTEREST_ACCRUALS, ifds::InterestAccrualHeadingSet, 
                   IFASTBP_PROC::INTEREST_ACCRUAL_DETAILS_LIST, 0, true, LISTFLAG_NOT_AUTO_ADD);

   DSTCWorkSession *pDSTCWorkSession = dynamic_cast<DSTCWorkSession *>(getParent()->getBFWorkSession());   
   pDSTCWorkSession->getOption( ifds::MgmtFeeType, _dstrMgmtFeeType, getDataGroupId(), false );
   if( _dstrMgmtFeeType == ALT_MGMT_FEE_TYPE )
   {
      AddListControl( CLASSNAME, IDC_LV_MF, LV_MF_ACCRUALS, ifds::MFAltAccrualHeadingSet, 
                      IFASTBP_PROC::MF_ACCRUAL_LIST, 0, true, LISTFLAG_NOT_AUTO_ADD);
   }
   else
   {
      AddListControl( CLASSNAME, IDC_LV_MF, LV_MF_ACCRUALS, ifds::MFAccrualHeadingSet, 
                      IFASTBP_PROC::MF_ACCRUAL_LIST, 0, true, LISTFLAG_NOT_AUTO_ADD);
   }

   AddListControl( CLASSNAME, IDC_LV_MF_REBATE, LV_MFR_ACCRUALS, ifds::MFRAccrualHeadingSet, 
                   IFASTBP_PROC::MF_REBATE_ACCRUAL_LIST, 0, true, LISTFLAG_NOT_AUTO_ADD);

   // The fields are not tied to a list till later.

   AddControl( CTRL_STATIC, IDC_TXT_FIELD1, BF::NullContainerId, ifds::NullFieldId, CTRLFLAG_DEFAULT, 0 );
   AddControl( CTRL_STATIC, IDC_TXT_FIELD2, BF::NullContainerId, ifds::NullFieldId, CTRLFLAG_DEFAULT, 0 );
   AddControl( CTRL_STATIC, IDC_TXT_FIELD3, BF::NullContainerId, ifds::NullFieldId, CTRLFLAG_DEFAULT, 0 );
   AddControl( CTRL_STATIC, IDC_TXT_FIELD4, BF::NullContainerId, ifds::NullFieldId, CTRLFLAG_DEFAULT, 0 );   
   AddControl( CTRL_STATIC, IDC_TXT_FIELD5, BF::NullContainerId, ifds::NullFieldId, CTRLFLAG_DEFAULT, 0 );
   AddControl( CTRL_STATIC, IDC_TXT_FIELD6, BF::NullContainerId, ifds::NullFieldId, CTRLFLAG_DEFAULT, 0 );
   AddControl( CTRL_STATIC, IDC_TXT_FIELD7, BF::NullContainerId, ifds::NullFieldId, CTRLFLAG_DEFAULT, 0 );   
   AddControl( CTRL_STATIC, IDC_TXT_FIELD8, BF::NullContainerId, ifds::NullFieldId, CTRLFLAG_DEFAULT, 0 );   
   AddControl( CTRL_STATIC, IDC_TXT_FIELD9, BF::NullContainerId, ifds::NullFieldId, CTRLFLAG_DEFAULT, 0 );

	GetDlgItem( IDC_BTN_MORE )->EnableWindow( false );
}

//******************************************************************************
// Set the controls to hook to the Interest Accrual Search Criteria CBO
// and the Interest Accruals CBO.
// @returns void.
//******************************************************************************

void AccrualsDlg::loadInterestAccuralSearch( )
{   
   CString cstrLabel;
   GetDlgItem ( IDC_CB_INCLUDE_UNSETTLED_TRADES )->ShowWindow ( true );
   GetDlgItem ( IDC_LV_INTEREST_ACCRUED )->ShowWindow ( true );
   GetDlgItem ( IDC_LV_MF )->ShowWindow ( false );
   GetDlgItem ( IDC_LV_MF_REBATE )->ShowWindow ( false );
   GetDlgItem ( IDC_LBL_FIELD1 )->ShowWindow ( true );
   GetDlgItem ( IDC_TXT_FIELD1 )->ShowWindow ( true );
   cstrLabel.LoadString ( TXT_TOTAL_INTEREST_DISTRIBUTED );
   GetDlgItem ( IDC_LBL_FIELD2 )->SetWindowText ( cstrLabel );   
   GetDlgItem ( IDC_LBL_FIELD2 )->ShowWindow ( true );
   GetDlgItem ( IDC_TXT_FIELD2 )->ShowWindow ( true );
   GetDlgItem ( IDC_LBL_FIELD3 )->ShowWindow ( true );
   GetDlgItem ( IDC_TXT_FIELD3 )->ShowWindow ( true );
   GetDlgItem ( IDC_LBL_FIELD4 )->ShowWindow ( false );
   GetDlgItem ( IDC_TXT_FIELD4 )->ShowWindow ( false );
   GetDlgItem ( IDC_LBL_FIELD5 )->ShowWindow ( false );
   GetDlgItem ( IDC_TXT_FIELD5 )->ShowWindow ( false );
   GetDlgItem ( IDC_LBL_FIELD6 )->ShowWindow ( false );
   GetDlgItem ( IDC_TXT_FIELD6 )->ShowWindow ( false );
   GetDlgItem ( IDC_LBL_FIELD7 )->ShowWindow ( false );
   GetDlgItem ( IDC_TXT_FIELD7 )->ShowWindow ( false );
   GetDlgItem ( IDC_LBL_FIELD8 )->ShowWindow ( false );
   GetDlgItem ( IDC_TXT_FIELD8 )->ShowWindow ( false );
   GetDlgItem ( IDC_LBL_FIELD9 )->ShowWindow ( false );
   GetDlgItem ( IDC_TXT_FIELD9 )->ShowWindow ( false );

   reConnectSearchControls ( IFASTBP_PROC::INTEREST_SEARCH_CRITERIA_CBO );
   reConnectControls ( IFASTBP_PROC::INTEREST_ACCRUAL_DETAILS_LIST, IDC_LV_INTEREST_ACCRUED );
   DString dstrFundCode, dstrClassCode, dstrAccrualSummary;
   getParent()->getField (this, IFASTBP_PROC::INTEREST_SEARCH_CRITERIA_CBO, ifds::FundCode, dstrFundCode, false );
   getParent()->getField (this, IFASTBP_PROC::INTEREST_SEARCH_CRITERIA_CBO, ifds::ClassCode, dstrClassCode, false );  
   setRadioButtons ( IFASTBP_PROC::INTEREST_SEARCH_CRITERIA_CBO );
   getParent()->getField (this, IFASTBP_PROC::INTEREST_SEARCH_CRITERIA_CBO, ifds::AccrualSummary, dstrAccrualSummary, false );
   if( _dstrMgmtFeeType == ALT_MGMT_FEE_TYPE )
      GetDlgItem ( IDC_RB_DETAILS )->EnableWindow ( true );
   if( dstrAccrualSummary == YES )
   {
      _bDetails = true;
      OnRbTotalsByFund();
   }
   else
   {
      _bDetails = false;
      OnRbDetails ();
   }      

}

//******************************************************************************
// Set the controls to hook to the Management Fee Accrual Search Criteria CBO
// and the Management Fee Accruals CBO.
// @returns void.
//******************************************************************************

void AccrualsDlg::loadManagementFeeSearch( )
{   
   CString cstrLabel;
   GetDlgItem ( IDC_CB_INCLUDE_UNSETTLED_TRADES )->ShowWindow ( false );
   GetDlgItem ( IDC_LV_INTEREST_ACCRUED )->ShowWindow ( false );   
   GetDlgItem ( IDC_LV_MF )->ShowWindow ( true );
   GetDlgItem ( IDC_LV_MF_REBATE )->ShowWindow ( false ); 
   if( _dstrMgmtFeeType == ALT_MGMT_FEE_TYPE )
   {
      GetDlgItem ( IDC_LBL_FIELD1 )->ShowWindow ( false );
      GetDlgItem ( IDC_TXT_FIELD1 )->ShowWindow ( false );
      GetDlgItem ( IDC_LBL_FIELD2 )->ShowWindow ( false );
      GetDlgItem ( IDC_TXT_FIELD2 )->ShowWindow ( false );
      GetDlgItem ( IDC_LBL_FIELD3 )->ShowWindow ( false );
      GetDlgItem ( IDC_TXT_FIELD3 )->ShowWindow ( false );
      GetDlgItem ( IDC_LBL_FIELD4 )->ShowWindow ( true );
      GetDlgItem ( IDC_TXT_FIELD4 )->ShowWindow ( true );
      GetDlgItem ( IDC_LBL_FIELD5 )->ShowWindow ( false );
      GetDlgItem ( IDC_TXT_FIELD5 )->ShowWindow ( false );
      GetDlgItem ( IDC_LBL_FIELD6 )->ShowWindow ( false );
      GetDlgItem ( IDC_TXT_FIELD6 )->ShowWindow ( false );
      GetDlgItem ( IDC_LBL_FIELD7 )->ShowWindow ( true );
      GetDlgItem ( IDC_TXT_FIELD7 )->ShowWindow ( true );
      GetDlgItem ( IDC_LBL_FIELD8 )->ShowWindow ( false );
      GetDlgItem ( IDC_TXT_FIELD8 )->ShowWindow ( false );
      GetDlgItem ( IDC_LBL_FIELD9 )->ShowWindow ( false );
      GetDlgItem ( IDC_TXT_FIELD9 )->ShowWindow ( false );
   }
   else
   {
      GetDlgItem ( IDC_LBL_FIELD1 )->ShowWindow ( true );
      GetDlgItem ( IDC_TXT_FIELD1 )->ShowWindow ( true );
      cstrLabel.LoadString ( TXT_TOTAL_MF_PAID );
      GetDlgItem ( IDC_LBL_FIELD2 )->SetWindowText ( cstrLabel );
      GetDlgItem ( IDC_LBL_FIELD2 )->ShowWindow ( true );
      GetDlgItem ( IDC_TXT_FIELD2 )->ShowWindow ( true );
      GetDlgItem ( IDC_LBL_FIELD3 )->ShowWindow ( true );
      GetDlgItem ( IDC_TXT_FIELD3 )->ShowWindow ( true );
      GetDlgItem ( IDC_LBL_FIELD4 )->ShowWindow ( true );
      GetDlgItem ( IDC_TXT_FIELD4 )->ShowWindow ( true );
      GetDlgItem ( IDC_LBL_FIELD5 )->ShowWindow ( true );
      GetDlgItem ( IDC_TXT_FIELD5 )->ShowWindow ( true );
      GetDlgItem ( IDC_LBL_FIELD6 )->ShowWindow ( false );
      GetDlgItem ( IDC_TXT_FIELD6 )->ShowWindow ( false );
      GetDlgItem ( IDC_LBL_FIELD7 )->ShowWindow ( false );
      GetDlgItem ( IDC_TXT_FIELD7 )->ShowWindow ( false );
      GetDlgItem ( IDC_LBL_FIELD8 )->ShowWindow ( true );
      GetDlgItem ( IDC_TXT_FIELD8 )->ShowWindow ( true );
      GetDlgItem ( IDC_LBL_FIELD9 )->ShowWindow ( false );
      GetDlgItem ( IDC_TXT_FIELD9 )->ShowWindow ( false );
   }   
   reConnectSearchControls ( IFASTBP_PROC::MF_SEARCH_CRITERIA_CBO );
   reConnectControls ( IFASTBP_PROC::MF_ACCRUAL_LIST, IDC_LV_MF );
   if( _dstrMgmtFeeType == ALT_MGMT_FEE_TYPE )
   {
      _bDetails = true;
      OnRbTotalsByFund();
      GetDlgItem ( IDC_RB_DETAILS )->EnableWindow ( false );
   }
   else
   {
      DString dstrAccrualSummary;   
      getParent()->getField (this, IFASTBP_PROC::MF_SEARCH_CRITERIA_CBO, ifds::AccrualSummary, dstrAccrualSummary, false );
      if( dstrAccrualSummary == YES )
      {
         _bDetails = true;
         OnRbTotalsByFund();
      }
      else
      {
         _bDetails = false;
         OnRbDetails ();
      }
   }
   setRadioButtons ( IFASTBP_PROC::MF_SEARCH_CRITERIA_CBO ); 
//CP20030319   GetDlgItem( IDC_BTN_MORE )->EnableWindow( getParent()->doMoreRecordsExist( this, 2 ) );
}

//******************************************************************************
// Set the controls to hook to the Management Fee Rebate Accrual Search Criteria 
// CBO and the Management Fee Rebate Accruals CBO.
// @returns void.
//******************************************************************************

void AccrualsDlg::loadManagementFeeRebateSearch( )
{   
   CString cstrLabel;
   GetDlgItem ( IDC_CB_INCLUDE_UNSETTLED_TRADES )->ShowWindow ( false );
   GetDlgItem ( IDC_LV_INTEREST_ACCRUED )->ShowWindow ( false );
   GetDlgItem ( IDC_LV_MF )->ShowWindow ( false );
   GetDlgItem ( IDC_LV_MF_REBATE )->ShowWindow ( true );   
   GetDlgItem ( IDC_LBL_FIELD1 )->ShowWindow ( true );
   GetDlgItem ( IDC_TXT_FIELD1 )->ShowWindow ( true );
   cstrLabel.LoadString ( TXT_TOTAL_INTEREST_DISTRIBUTED );
   GetDlgItem ( IDC_LBL_FIELD2 )->SetWindowText ( cstrLabel );   
   GetDlgItem ( IDC_LBL_FIELD2 )->ShowWindow ( true );
   GetDlgItem ( IDC_TXT_FIELD2 )->ShowWindow ( true );
   GetDlgItem ( IDC_LBL_FIELD3 )->ShowWindow ( true );
   GetDlgItem ( IDC_TXT_FIELD3 )->ShowWindow ( true );
   GetDlgItem ( IDC_LBL_FIELD4 )->ShowWindow ( true );
   GetDlgItem ( IDC_TXT_FIELD4 )->ShowWindow ( true );
   GetDlgItem ( IDC_LBL_FIELD5 )->ShowWindow ( true );
   GetDlgItem ( IDC_TXT_FIELD5 )->ShowWindow ( true );
   GetDlgItem ( IDC_LBL_FIELD6 )->ShowWindow ( true );
   GetDlgItem ( IDC_TXT_FIELD6 )->ShowWindow ( true );
   GetDlgItem ( IDC_LBL_FIELD8 )->ShowWindow ( true );
   GetDlgItem ( IDC_TXT_FIELD8 )->ShowWindow ( true );
   GetDlgItem ( IDC_LBL_FIELD9 )->ShowWindow ( true );
   GetDlgItem ( IDC_TXT_FIELD9 )->ShowWindow ( true );

   if( _dstrMgmtFeeType == ALT_MGMT_FEE_TYPE )
   {
      GetDlgItem ( IDC_LBL_FIELD7 )->ShowWindow ( true );
      GetDlgItem ( IDC_TXT_FIELD7 )->ShowWindow ( true );
      GetDlgItem ( IDC_RB_DETAILS )->EnableWindow ( true );
   }
   else
   {
      GetDlgItem ( IDC_LBL_FIELD7 )->ShowWindow ( false );
      GetDlgItem ( IDC_TXT_FIELD7 )->ShowWindow ( false );
   }
   setRadioButtons ( IFASTBP_PROC::MF_REBATE_SEARCH_CRITERIA_CBO );      
   reConnectSearchControls ( IFASTBP_PROC::MF_REBATE_SEARCH_CRITERIA_CBO );
   reConnectControls ( IFASTBP_PROC::MF_REBATE_ACCRUAL_LIST, IDC_LV_MF_REBATE );
   DString dstrAccrualSummary;
   getParent()->getField (this, IFASTBP_PROC::MF_REBATE_SEARCH_CRITERIA_CBO, ifds::AccrualSummary, dstrAccrualSummary, false );
   if( dstrAccrualSummary == YES )
   {
      _bDetails = true;
      OnRbTotalsByFund();
   }
   else
   {
      _bDetails = false;
      OnRbDetails ();
   }
//CP20030319   GetDlgItem( IDC_BTN_MORE )->EnableWindow( getParent()->doMoreRecordsExist( this, 3 ) );
}

//******************************************************************************
// This will reconnect all the controls related to the search criteria to the
// correct cbo.
// @param   const BFContainerId& idContainer - the Container to attach the search controls.
// @returns void.
//******************************************************************************

void AccrualsDlg::reConnectSearchControls( const BFContainerId& idContainer )
{      
   if( !_bCanLuxMarket )
   {
      ReInitControl ( IDC_EDT_FUND_CODE, idContainer, ifds::FundCode );
      showFundNumberControl ( false );
   }
   else
   {
      ReInitControl ( IDC_EDT_FUND_NBR, idContainer, ifds::FundNumber );      
      ReInitControl ( IDC_EDT_FUND_CODE2, idContainer, ifds::FundCode );
      showFundNumberControl ( true );
   }
   ReInitControl ( IDC_EDT_CLASS_CODE, idContainer, ifds::ClassCode );
   ReInitControl ( IDC_DTP_START_DATE, idContainer, ifds::StartDate );
   ReInitControl ( IDC_DTP_END_DATE, idContainer, ifds::EndDate );   
}

//******************************************************************************
// Reconnects the summary controls to the correct list cbo.
// @param   const BFContainerId& idContainer - the container to attach the summary controls.
//******************************************************************************

void AccrualsDlg::reConnectControls( const BFContainerId& idContainer, UINT idList )
{      
   clearTotalsControls();
   ReInitControl ( IDC_TXT_FIELD1, idContainer, TOTALS_FIELD1 );
   ReInitControl ( IDC_TXT_FIELD2, idContainer, TOTALS_FIELD2 );
   ReInitControl ( IDC_TXT_FIELD3, idContainer, TOTALS_FIELD3 );   
   ReInitControl ( IDC_TXT_FIELD4, idContainer, TOTALS_FIELD4 );
   ReInitControl ( IDC_TXT_FIELD5, idContainer, TOTALS_FIELD5 );
   ReInitControl ( IDC_TXT_FIELD6, idContainer, TOTALS_FIELD6 );
   ReInitControl ( IDC_TXT_FIELD7, idContainer, TOTALS_FIELD7 );
   ReInitControl ( IDC_TXT_FIELD8, idContainer, TOTALS_FIELD8 );
   ReInitControl ( IDC_TXT_FIELD9, idContainer, TOTALS_FIELD9 );
   ConnectControlsToData ();  
   LoadControls();
}

//******************************************************************************
// MFC event - Accrual type combo box selection change.  This procedure will 
// call helper procedures loadInterestAccrualSearch, loadManagementFeeSearch and
// loadManagementFeeRebateSearch to reinit the dialog accordingly.
// @returns void.
//******************************************************************************

void AccrualsDlg::OnSelchangeCmbAccrualType() 
{
   DSTComboBox* pComboBox = dynamic_cast<DSTComboBox*>( GetDlgItem( IDC_CMB_ACCRUAL_TYPE ) );
   int iAccrualType = (*(DString*)pComboBox->GetItemData ( pComboBox->GetCurSel () )).asInteger();
   switch( iAccrualType )
   {
      case 1:
         loadInterestAccuralSearch();
         break;
      case 2:
         loadManagementFeeSearch();
         break;
      case 3:
         loadManagementFeeRebateSearch();
         break;
   }
}

//******************************************************************************
// Sets the radio buttons based on the Accrual Summary field stored in the 
// Accruals Search criteria cbo.
// @param   const BFContainerId& idContainer  - INTEREST_SEARCH_CRITERIA_CBO
//                               MF_SEARCH_CRITERIA_CBO
//                               MF_REBATE_SEARCH_CRITERIA_CBO
// @returns void.
//******************************************************************************

void AccrualsDlg::setRadioButtons( const BFContainerId& idContainer )
{   
   DString dstrAccrualSummary;
   getParent()->getField (this, idContainer, ifds::AccrualSummary, dstrAccrualSummary, false );
   if( dstrAccrualSummary == YES )
   {
      m_btn_details.SetCheck(0);
      m_btn_totals.SetCheck(1);
   }
   else
   {
      m_btn_details.SetCheck(1);
      m_btn_totals.SetCheck(0);
   }
}

//******************************************************************************
// Hides the start date control for All Fund Mode.  Also used to show the
// start date control when a fund/class code is entered.
// @param   bool bHide - Hides start date ( true )
//                       Shows start date (false )
// @returns void.
//******************************************************************************

void AccrualsDlg::hideStartDate( bool bHide )
{      
   GetDlgItem ( IDC_TXT_START_DATE )->ShowWindow ( !bHide );
   ShowControl ( IDC_DTP_START_DATE, !bHide );
}

//******************************************************************************
// Method to refresh dialog controls
// @param   GenericInterface *rpGICaller - pointer to the calling object
// @param   const I_CHAR *szOriginalCommand - Not used in this case, but 
//                      can be used to instruct special processing.
// @returns bool - true.
//******************************************************************************

bool AccrualsDlg::doRefresh( GenericInterface * rpGICaller, 
                             const I_CHAR * szOriginalCommand )
{
   DString dstrMarket = DSTCommonFunctions::getMarket();
   _bCanLuxMarket = ( dstrMarket == MARKET_IDS::CANADA || dstrMarket == MARKET_IDS::LUXEMBOURG );   
   DString dstrShrNum, dstrAccountNum, dstrOldAccountNum, dstrEntityName;
   dstrOldAccountNum = GetAccount();
   getParent()->getField( this, ifds::AccountNum, dstrAccountNum ); 
   if( dstrOldAccountNum == dstrAccountNum )
      return(true);

   getParent()->getField(this, ifds::ShrNum, dstrShrNum); 
   SetAccount( dstrAccountNum );
   dynamic_cast<DSTCWorkSession *>(getBFWorkSession())->getFirstSequenced01AccountholderEntityName( getDataGroupId(), 
                                                                                                    dstrAccountNum,                                                                                                     dstrEntityName );
   SetShrAcctCaption(dstrShrNum, dstrAccountNum, dstrEntityName);   
   ClearControls();
   DSTComboBox* pComboBox = dynamic_cast<DSTComboBox*>( GetDlgItem( IDC_CMB_ACCRUAL_TYPE ) );
   pComboBox->FillInSubstituteValues ( BFContainerId( ifds::AccrualType.getId() ) );   

   //Currently we will default to Interest Accrual, but this may need to be change later.
   pComboBox->SetCurSel ( 0 );  

   GetList ( IDC_LV_INTEREST_ACCRUED )->DeleteAllItems();
   GetList ( IDC_LV_MF )->DeleteAllItems();
   GetList ( IDC_LV_MF_REBATE )->DeleteAllItems();
   loadInterestAccuralSearch ( );   
   return(true);
}

//******************************************************************************
// MFC event - When the FundNbr/Fund/Class controls lose focus, displayStartDate
// will show/hide the start date control
// @returns void.
//******************************************************************************

void AccrualsDlg::OnSetFocusSearchControls ()
{
   SetDefID ( IDC_BTN_SEARCH );
}

//******************************************************************************
// Function which invokes the FundClass process to launch the Fund/Class
// selection dialog.
// @param   WPARAM - parameter to a window procedure or callback function.
//          LPARAM - parameter to a window procedure or callback function.
// @returns LRESULT - return value for window procedure or callback function.
//                    0 always in this case.
//******************************************************************************

LRESULT AccrualsDlg::OpenFundClassListDlg( WPARAM, LPARAM )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OpenFundClassListDlg" ) );

   const BFContainerId& idContainer = getSearchContainerId();

   try
   {
      E_COMMANDRETURN eRtn = CMD_CANCEL;
      CWaitCursor wait;
      DString dstrAccountNum, dstrFundNumber, dstrFundCode, dstrClassCode;
      getParent()->getField( this, ifds::AccountNum, dstrAccountNum );
      getParent()->getField( this, idContainer, ifds::FundNumber, dstrFundNumber );
      getParent()->getField( this, idContainer, ifds::FundCode, dstrFundCode );
      getParent()->getField( this, idContainer, ifds::ClassCode, dstrClassCode );

      dstrAccountNum.strip().stripLeading( I_CHAR( '0' ) );

      setParameter ( FUNDCLASSLIST::ACCT_NUM, dstrAccountNum );

      // Set FUND Code for Fund Dialog
      switch( _currentFocusControl )
      {
         case IDC_EDT_FUND_CODE:
         case IDC_EDT_FUND_CODE2:
            {
               CString cstrFundCode;
               GetDlgItem( _currentFocusControl )->GetWindowText( cstrFundCode );          
               setParameter( FUNDCLASSLIST::FUND_CODE, DString ( cstrFundCode ) );
               setParameter( FUNDCLASSLIST::CLASS_CODE, NULL_STRING );
               setParameter( FUNDCLASSLIST::FUND_NUMBER, NULL_STRING );
            }
            break;
         case IDC_EDT_CLASS_CODE:      
            {
               CString cstrFundClass;
               GetDlgItem( _currentFocusControl )->GetWindowText( cstrFundClass );         
               setParameter( FUNDCLASSLIST::FUND_CODE, NULL_STRING );
               setParameter( FUNDCLASSLIST::CLASS_CODE, DString ( cstrFundClass ) );
               setParameter( FUNDCLASSLIST::FUND_NUMBER, NULL_STRING );
            }
            break;
         case IDC_EDT_FUND_NBR:      
            {
               CString cstrFundNumber;
               GetDlgItem( _currentFocusControl )->GetWindowText( cstrFundNumber );          
               setParameter( FUNDCLASSLIST::FUND_CODE, NULL_STRING );
               setParameter( FUNDCLASSLIST::CLASS_CODE, NULL_STRING );
               setParameter( FUNDCLASSLIST::FUND_NUMBER, DString ( cstrFundNumber ) );
            }
            break;
      }

      setParameter ( FUNDCLASSLIST::MANAGEMENTFEE,  (idContainer==IFASTBP_PROC::MF_SEARCH_CRITERIA_CBO)?YES:NO);
      setParameter ( FUNDCLASSLIST::MANAGEMENTFEE_REBATE, (idContainer==IFASTBP_PROC::MF_REBATE_SEARCH_CRITERIA_CBO)?YES:NO);

      eRtn = invokeCommand( getParent(), CMD_BPROC_FUNDCLASS, PROC_SUPPORT, true, NULL );
      switch( eRtn )
      {
         case CMD_OK:
         case CMD_MODELESS_INPROCESS:
            {
               DString dstrFundCode, dstrClassCode, dstrFundNumber;
               getParameter ( FUNDCLASSLIST::FUND_CODE, dstrFundCode );
               getParameter ( FUNDCLASSLIST::CLASS_CODE, dstrClassCode );
               if( _bCanLuxMarket )
               {
                  getParameter ( FUNDCLASSLIST::FUND_NUMBER, dstrFundNumber );
                  if( dstrFundCode == NULL_STRING && dstrClassCode == NULL_STRING )
                     dstrFundNumber = NULL_STRING;
               }


               if( _bCanLuxMarket &&  dstrFundNumber != NULL_STRING )
                  getParent()->setField( this, idContainer, ifds::FundNumber, dstrFundNumber );
               else
               {
                  getParent()->setField( this, idContainer, ifds::FundCode, dstrFundCode );
                  getParent()->setField( this, idContainer, ifds::ClassCode, dstrClassCode );                  
               }

               if( _bCanLuxMarket )
               {
                  LoadControl ( IDC_EDT_FUND_NBR );
                  LoadControl ( IDC_EDT_FUND_CODE2 );
               }
               else
                  LoadControl ( IDC_EDT_FUND_CODE );
               LoadControl ( IDC_EDT_CLASS_CODE );
               if( dstrFundCode != NULL_STRING && dstrClassCode != NULL_STRING )
               {
                  hideStartDate ( false );
                  LoadControl ( IDC_DTP_START_DATE );
               }
            }
            break;      
         case CMD_CANCEL:
            break;
         default:     
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
   return(0);
}

//******************************************************************************
// MFC Message Map - calls OpenFundClassListDlg when F4 key is pressed.
// @param   MSG *pMsg - MFC message
// @returns BOOL - true when message is processed successfully.
//******************************************************************************

BOOL AccrualsDlg::PreTranslateMessage( MSG*pMsg )
{
   if( pMsg->message == WM_KEYDOWN && ( int )( pMsg->wParam ) == VK_F4 && !IsSelectedCtrlUpdateable() )
      return(TRUE);

   CWnd *pCWnd = GetFocus();

   if( pMsg->message == WM_KEYDOWN&&( int )( pMsg->wParam ) == VK_F4 )
   {
      if( pCWnd == GetDlgItem ( IDC_EDT_FUND_CODE ) )
      {
         PostMessage ( UM_OPENFUNDCLASSLISTDLG );
         _currentFocusControl = IDC_EDT_FUND_CODE;
      }
      else if( pCWnd == GetDlgItem ( IDC_EDT_FUND_CODE2 ) )
      {
         PostMessage ( UM_OPENFUNDCLASSLISTDLG );
         _currentFocusControl = IDC_EDT_FUND_CODE2;
      }
      else if( pCWnd == GetDlgItem ( IDC_EDT_CLASS_CODE ) )
      {
         PostMessage ( UM_OPENFUNDCLASSLISTDLG );
         _currentFocusControl = IDC_EDT_CLASS_CODE;
      }
      else if( pCWnd == GetDlgItem ( IDC_EDT_FUND_NBR ) )
      {
         PostMessage ( UM_OPENFUNDCLASSLISTDLG );
         _currentFocusControl = IDC_EDT_FUND_NBR;
      }
   }
   if( pMsg->message == WM_KEYDOWN&&( int )( pMsg->wParam ) == VK_RETURN )
   {
      if( pCWnd->GetDlgCtrlID() == IDC_EDT_FUND_NBR )
      {
         ProcessControls();         
      }
   }
   return(BaseMainDlg::PreTranslateMessage( pMsg ));
}

//******************************************************************************
// Override which will filter the Interest accruals list box based on the radio
// button selection.  If the Details Radio button is selected, then the list will
// only contain list items with Record Type other than I_("S").  If the totals by
// fund radio button is selected then only the items with record type I_("S") 
// will be shown.
// @param   long lSubstituteId - Which substituion list to filter, in this case
//                only the interest accruals will need filtering.
//          const DString *strKey - The key of the current list item.
// @returns bool - true if the item is to be shown.
//                 false if the item is to be hidden.
//******************************************************************************

bool AccrualsDlg::ListViewControlFilter( long lSubstituteId, const DString *strKey )
{   
   const BFContainerId& idContainer = getListContainer ( m_btn_details.GetCheck()?false:true );

   DString dstrRecType;      
   getParent()->getField( this, idContainer, ifds::RecType, dstrRecType );      
   dstrRecType.strip().upperCase();

   // The following code is an xor statement
   // When the record type is a summary and m_btn_details is true (details), return false (do not show the item )
   // When the record type is not a summary and m_btn_details is true return true (show the item);
   // When the record type is a summary and m_btn_details is false (total by funds), return true (show the item)
   // When the record type is not a summary and m_btn_details is false , return false  ( do not show the item )   
   return(( ( dstrRecType == I_( "S" ) )?1:0) ^ m_btn_details.GetCheck())?true:false;    

   return(true);
}

//******************************************************************************
// MFC event - When the more button is clicked, more items are retrived and 
// inserted to the list box.
// @returns void.
//******************************************************************************

void AccrualsDlg::OnBtnMore() 
{   
   TRACE_METHOD( CLASSNAME, ONBTNMORE );

   CWaitCursor wait;
   SetMessageStatusBar( TXT_SEARCH_FOR_INTEREST_ACRRUED );
   const BFContainerId& idContainer = getListContainer ();
   UINT idList = getActiveListControlId ();

   static int cursel;

   cursel = GetList( idList )->GetNextItem( -1, LVIS_SELECTED | LVNI_FOCUSED );

   const DString *crtKey = &getParent()->getCurrentListItemKey( this, idContainer );

   if( getParent()->performSearch( this, idContainer, SEARCH_NEXT_BLOCK ) <= WARNING )
   {
      LoadListControl( idList );
      if( *crtKey != NULL_STRING )
      {
         GetList( idList )->SetSelection( crtKey );
      }
   }
   GetDlgItem( IDC_BTN_MORE )->EnableWindow( getParent()->doMoreRecordsExist( this, idContainer ) );
   GetList( idList )->SetSelection(cursel, true, true);                 
   SetMessageStatusBar(NULL_STRING); 
}

//******************************************************************************
// MFC event - When the search button is clicked, the list box is cleared and 
// reloaded with the new results. Which list box cleared depends on the accrual
// type.
// @returns void.
//******************************************************************************

void AccrualsDlg::OnBtnSearch() 
{   

   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnBtnSearch" ) );

   SEVERITY eRtn = NO_CONDITION;
   CWaitCursor wait;
   try
   {
      SetMessageStatusBar( TXT_SEARCH_FOR_INTEREST_ACRRUED );
//CP20030319      const BFContainerId& idSearchContainer = getSearchContainerId();
      const BFContainerId& idContainer = getListContainer( _bDetails == false );
      UINT idList = getActiveListControlId();
      ClearControls ( idContainer );
      eRtn = getParent()->performSearch( this, idContainer, SEARCH_START ) ;
      if( eRtn <= WARNING )
      {
         if( eRtn != NO_CONDITION )
         {
            ConditionMessageBox( FRAMEBELOW(), GETHIGHESTSEVERITY() );
         }
         GetDlgItem( IDC_BTN_MORE )->EnableWindow( getParent()->doMoreRecordsExist( this, idContainer ) );
         LoadListControl( idList );
         reConnectControls ( idContainer, idList );
         ConnectControlsToData ( 0 );
         LoadControls( );
      }
      else
      {
         //Show error condition in search??.
         ConditionMessageBox( FRAMEBELOW(), GETHIGHESTSEVERITY() );
      }
      SetMessageStatusBar(NULL_STRING); 
   }
   catch( ConditionException &ce )
   {
      ConditionMessageBox( ce );
   }
   catch( ... )
   {
      DISPLAYCONDITIONFROMFILE( CND::GUI_ERR_UNKNOWN_EXCEPTION );
   }
   SetDefID ( IDOK );
}

//******************************************************************************
// Procedure will only be activated on interest accrual selection.  It will
// reload the list items in the list box with a filter applied.  The filter 
// in this scenario will show all records that do not have a Record Type of I_("S")
// @returns void.
//******************************************************************************

void AccrualsDlg::OnRbDetails() 
{   
   // A Summary field exists in the search criteria cbo to perform a search 
   // which returns only the summary records.  For performance reasons we do
   // not want to use this on the iFast/Desktop.  Since the normal view also
   // returns summary records, we will simply filter them rather than another
   // view call.  This method however causes a minor inconsitency. If the max
   // records return by the view was 100 and there are 99 Summary records. The
   // accruals details will only show one item for accrual details.  The getMore
   // functionality will have to executed to show more of the detailed items.

   SetDefID ( IDC_BTN_SEARCH );
   if( !_bDetails )
   {
      hideStartDate ( false );
      _bDetails = true;
      GetDlgItem( IDC_BTN_SEARCH )->EnableWindow( true );
      if( !_bCanLuxMarket )
      {
         EnableControl( IDC_EDT_FUND_CODE, true );         
      }
      else
      {
         EnableControl( IDC_EDT_FUND_NBR, true );         
         EnableControl( IDC_EDT_FUND_CODE2, true );         
      }
      EnableControl ( IDC_EDT_CLASS_CODE, true );

      getParent()->setField ( this, getSearchContainerId (), ifds::AccrualSummary, NO, false );
      int iActiveListControlId = getActiveListControlId ();
      const BFContainerId& idList = getListContainer();
      switch( iActiveListControlId )
      {
         case IDC_LV_INTEREST_ACCRUED :
            {
               ReInitListControl ( iActiveListControlId, ifds::InterestAccrualHeadingSet, idList, LV_INTEREST_ACCRUALS );                           
            }
            break;
         case IDC_LV_MF :
            {
               if( _dstrMgmtFeeType == ALT_MGMT_FEE_TYPE )
                  ReInitListControl ( iActiveListControlId, ifds::MFAltAccrualHeadingSet, idList, LV_MF_ACCRUALS );
               else
                  ReInitListControl ( iActiveListControlId, ifds::MFAccrualHeadingSet, idList, LV_MF_ACCRUALS );                  
            }
            break;
         case IDC_LV_MF_REBATE :
            {
               ReInitListControl ( iActiveListControlId, ifds::MFRAccrualHeadingSet, idList, LV_MFR_ACCRUALS );                        
            }
            break;
      }      
      int numItems = getParent()->getNumberOfItemsInList ( this, getListContainer ());
      if( numItems > 0 )
      {
         reConnectControls ( idList , iActiveListControlId );
         LoadListControl ( getActiveListControlId () );
         restoreSearchFundCodeValues ();
      }
      else
      {
         clearTotalsControls();
         GetList ( getActiveListControlId () )->DeleteAllItems();
      }      
   }

   // HACK:  WTF???  GUI ListControlIds are not compatible with ContainerIds
//CP20030319   GetDlgItem( IDC_BTN_MORE )->EnableWindow( getParent()->doMoreRecordsExist( this, getActiveListControlId() ) );
}

//******************************************************************************
// Procedure will only be activated on interest accrual selection.  It will
// reload the list items in the list box with a filter applied.  The filter 
// in this scenario will show all records that have a Record Type of I_("S")
// @returns void.
//******************************************************************************

void AccrualsDlg::OnRbTotalsByFund() 
{   
   SetDefID ( IDC_BTN_SEARCH );
   if( _bDetails )
   {
      hideStartDate ( true );
      _bDetails = false;
      m_btn_details.SetCheck(0);      
      getParent()->setField ( this, getSearchContainerId (), ifds::AccrualSummary, YES, false );      
      if( !_bCanLuxMarket )
      {
         ClearControl ( IDC_EDT_FUND_CODE );
         EnableControl( IDC_EDT_FUND_CODE, false );         
      }
      else
      {
         ClearControl ( IDC_EDT_FUND_NBR );
         ClearControl ( IDC_EDT_FUND_CODE2 );
         getParent()->setField ( this, getSearchContainerId (), ifds::FundNumber, NULL_STRING, false );
         EnableControl( IDC_EDT_FUND_NBR, false );         
         EnableControl( IDC_EDT_FUND_CODE2, false );         
      }
      ClearControl ( IDC_EDT_CLASS_CODE );
      EnableControl ( IDC_EDT_CLASS_CODE, false );
      getParent()->setField ( this, getSearchContainerId (), ifds::FundCode, NULL_STRING, false );
      getParent()->setField ( this, getSearchContainerId (), ifds::ClassCode, NULL_STRING, false );      
      int iActiveListControlId = getActiveListControlId ();
      const BFContainerId& idList = getListContainer( true );
      switch( iActiveListControlId )
      {
         case IDC_LV_INTEREST_ACCRUED :
            {
               ReInitListControl ( iActiveListControlId, ifds::InterestAccrualHeadingSet, idList, LV_INTEREST_ACCRUALS );                           
            }
            break;
         case IDC_LV_MF :
            {
               if( _dstrMgmtFeeType == ALT_MGMT_FEE_TYPE )
                  ReInitListControl ( iActiveListControlId, ifds::MFAltAccrualHeadingSet, idList, LV_MF_ACCRUALS );
               else
                  ReInitListControl ( iActiveListControlId, ifds::MFAccrualHeadingSet, idList, LV_MF_ACCRUALS );         
            }
            break;
         case IDC_LV_MF_REBATE :
            {
               ReInitListControl ( iActiveListControlId, ifds::MFRAccrualHeadingSet, idList, LV_MFR_ACCRUALS );         
            }
            break;
      }      

      int numItems = getParent()->getNumberOfItemsInList ( this, getListContainer ( true ));
      // If the list is not empty, then we will load it.
      if( numItems > 0 )
      {
         reConnectControls ( idList, iActiveListControlId );
         // HACK:  WTF????  getListContainer returns a containerID.  ConnectControlsToData wants a 'controlGroupId' 
         // I'm going to assume that it's supposed to use iActiveListControlId ...
//CP20030319         ConnectControlsToData ( getListContainer ( true ) );
         ConnectControlsToData ( iActiveListControlId );
         LoadListControl ( iActiveListControlId );      
      }
      else
      {
         clearTotalsControls();
         GetList ( getActiveListControlId ( ) )->DeleteAllItems();
      }  
      GetDlgItem( IDC_BTN_MORE )->EnableWindow( getParent()->doMoreRecordsExist( this, getListContainer ( true ) ) );
   }
}

//******************************************************************************
// Function will mark the InclUnsettled field in the search criteria cbo 
// I_("Y") or I_("N").  Which search criteria cbo marked will be based on the 
// current accrual type combo selection.
// @returns void.
//******************************************************************************

void AccrualsDlg::OnChkIncUnStlTrades() 
{   
   const BFContainerId& idContainer = getSearchContainerId (); 
   SetDefID ( IDC_BTN_SEARCH );
   m_includeUnsettledTrades = !m_includeUnsettledTrades;
   if( m_includeUnsettledTrades )
      getParent()->setField ( this, idContainer, ifds::InclUnsettled, YES );
   else
      getParent()->setField ( this, idContainer, ifds::InclUnsettled, NO );
}

//******************************************************************************
// This function returns the list cbo id based on the selection in the accrual
// type combo box.
// @returns long - INTEREST_SEARCH_CRITERIA_CBO id
//                 MF_SEARCH_CRITERIA_CBO id
//                 MF_REBATE_SEARCH_CRITERIA_CBO id
//******************************************************************************

const BFContainerId& AccrualsDlg::getListContainer( bool bSummary ) 
{
   TRACE_METHOD( CLASSNAME, I_("getListContainer") );
   DSTComboBox* pComboBox = dynamic_cast<DSTComboBox*>( GetDlgItem( IDC_CMB_ACCRUAL_TYPE ) );
   int iAccrualType = (*(DString*)pComboBox->GetItemData ( pComboBox->GetCurSel () )).asInteger();
   switch( iAccrualType )
   {
      case 1: 
         {
            if( bSummary )
               return( IFASTBP_PROC::INTEREST_ACCRUAL_SUMMARY_LIST );      // old value is 21
            else
               return( IFASTBP_PROC::INTEREST_ACCRUAL_DETAILS_LIST );      // old value is 1
         }
         break;
      case 2:
         {
            if( bSummary )
               return( IFASTBP_PROC::MF_ACCRUAL_SUMMARY_LIST );            // old value is 22
            else
               return( IFASTBP_PROC::MF_ACCRUAL_LIST );                    // old value is 3
         }
         break;
      case 3:
         {
            if( bSummary )
               return( IFASTBP_PROC::MF_REBATE_ACCRUAL_SUMMARY_LIST );     // old value is 23
            else
               return( IFASTBP_PROC::MF_REBATE_ACCRUAL_LIST );             // old value is 4
         }
         break;
   }
   return( BF::NullContainerId );
}

//******************************************************************************
// This function returns the search criteria cbo id based on the selection in the  
// accrual type combo box.
// @returns long - INTEREST_SEARCH_CRITERIA_CBO id
//                 MF_SEARCH_CRITERIA_CBO id
//                 MF_REBATE_SEARCH_CRITERIA_CBO id
//******************************************************************************

const BFContainerId& AccrualsDlg::getSearchContainerId( ) 
{
   TRACE_METHOD( CLASSNAME, I_("getSearchContainerId") );   
   DSTComboBox* pComboBox = dynamic_cast<DSTComboBox*>( GetDlgItem( IDC_CMB_ACCRUAL_TYPE ) );
   int iAccrualType = (*(DString*)pComboBox->GetItemData ( pComboBox->GetCurSel () )).asInteger();
   switch( iAccrualType )
   {
      case 1:             
         return( IFASTBP_PROC::INTEREST_SEARCH_CRITERIA_CBO );
         break;
      case 2:           
         return( IFASTBP_PROC::MF_SEARCH_CRITERIA_CBO );
         break;
      case 3:
         return( IFASTBP_PROC::MF_REBATE_SEARCH_CRITERIA_CBO );
         break;
   }
   return(BF::NullContainerId);
}

//******************************************************************************
// Overrides canCancel so that discard dialog does not show up.
// @returns bool - true.
//******************************************************************************
bool AccrualsDlg::canCancel() 
{   
   return(true);
}

//******************************************************************************
// This function returns the active list control id based on the selection in the  
// accrual type combo box.
// @returns long - IDC_LV_INTEREST_ACCRUED resource control id
//                 IDC_LV_MF_ACCRUED resource control id
//                 IDC_LV_MFR_ACCRUED resource control id
//******************************************************************************

int AccrualsDlg::getActiveListControlId()
{
   TRACE_METHOD( CLASSNAME, I_("getActiveList") );   
   DSTComboBox* pComboBox = dynamic_cast<DSTComboBox*>( GetDlgItem( IDC_CMB_ACCRUAL_TYPE ) );
   int iAccrualType = (*(DString*)pComboBox->GetItemData ( pComboBox->GetCurSel () )).asInteger();
   switch( iAccrualType )
   {
      case 1:             
         return(IDC_LV_INTEREST_ACCRUED);
         break;
      case 2:           
         return(IDC_LV_MF);                      
         break;
      case 3:
         return(IDC_LV_MF_REBATE);          
         break;
   }
   //should not get here.
   assert (0);
   return(0);
}

//******************************************************************************
// This functions clears all the total field information during Accrual type 
// switches or selection of fund by details/totals
// @returns void.
//******************************************************************************

void AccrualsDlg::clearTotalsControls()
{
   ClearControl ( IDC_TXT_FIELD1 );
   ClearControl ( IDC_TXT_FIELD2 );
   ClearControl ( IDC_TXT_FIELD3 );
   ClearControl ( IDC_TXT_FIELD4 );
   ClearControl ( IDC_TXT_FIELD5 );
   ClearControl ( IDC_TXT_FIELD6 );
   ClearControl ( IDC_TXT_FIELD7 );
   ClearControl ( IDC_TXT_FIELD8 );
   ClearControl ( IDC_TXT_FIELD9 );
}

//******************************************************************************
// The purpose of this function is to repopulated the FundCode, ClassCode and 
// StartDate information which is cleared up during switches between fund by 
// details/totals.
// @returns void.
//******************************************************************************

void AccrualsDlg::restoreSearchFundCodeValues()
{   
   // bug fix to always use the summary record to get the Fund/Class Code.  This
   // fixes a bug which occurs when only a summary record is returned which should
   // never happen in the first place.
   const BFContainerId& idContainer = getListContainer ( true );
   const BFContainerId& idSearchContainer = getSearchContainerId ();
   DString dstrFundCode, dstrClassCode, dstrStartDate;
 //  getParent()->getField( this, idSearchContainer, ifds::FundCode, dstrFundCode);
 //  getParent()->getField( this, idSearchContainer, ifds::ClassCode, dstrClassCode);
   // We want to get the old start date since setting the fund/class code will
   // automatically change the start date to the last dividate or last MF/MFR date
   // + 1.
   getParent()->getField ( this, idSearchContainer, ifds::StartDate, dstrStartDate);
//   getParent()->setField ( this, idSearchContainer, ifds::FundCode, dstrFundCode, false );
//   getParent()->setField ( this, idSearchContainer, ifds::ClassCode, dstrClassCode, false );
   // Change the start date back to the original start date.
   getParent()->setField ( this, idSearchContainer, ifds::StartDate, dstrStartDate, true );
   // Reload/refresh the start date display.
   LoadControl ( IDC_DTP_START_DATE );
}
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/AccrualsDlg.cpp-arc  $
// 
//    Rev 1.26   Sep 15 2005 15:09:52   popescu
// Incident#403519 - added CLASSNAME as the fifth parameter to  BaseMainDlg constructor
// 
//    Rev 1.25   Oct 27 2004 16:29:28   VADEANUM
// PTS 10034817 - More button disabled at startup.
// 
//    Rev 1.24   Sep 07 2003 14:16:40   YINGBAOL
// fix crash
// 
//    Rev 1.23   Mar 21 2003 18:30:46   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.22   Oct 29 2002 11:40:32   HSUCHIN
// sync up with release 49 - 1.21
// 
//    Rev 1.21   Oct 09 2002 23:55:28   PURDYECH
// PVCS Database Conversion
// 
//    Rev 1.20   Sep 30 2002 11:01:32   PURDYECH
// BFFieldId no longer has operator long(), so explicit getId() calls are needed in places.
// 
//    Rev 1.19   Aug 29 2002 12:57:10   SMITHDAV
// ClientLocale and typed field changes.
// 
//    Rev 1.18   Jun 27 2002 13:27:20   YINGBAOL
// fix select fundCode class code
// 
//    Rev 1.17   May 23 2002 10:39:34   PURDYECH
// BFData Implementation Verification Corrections
// 
//    Rev 1.16   09 May 2002 12:25:10   HSUCHIN
// PTS - 10008094
// 
//    Rev 1.15   26 Apr 2002 11:55:46   HSUCHIN
// bug fix for pinnacle.  Locked details radio button for Management Fee when Mgmt Fee type is 2
// 
//    Rev 1.14   16 Apr 2002 14:50:40   HSUCHIN
// added more enhancement/info to dialog
// 
//    Rev 1.13   04 Apr 2002 13:50:26   HSUCHIN
// bug fix and added support for Pinnacle
// 
//    Rev 1.12   01 Apr 2002 16:26:38   HSUCHIN
// sync up with 1.10.1.0
// 
//    Rev 1.11   28 Mar 2002 15:34:48   HSUCHIN
// bug fix for hiding/showing start date
// 
//    Rev 1.10   20 Mar 2002 16:44:18   HSUCHIN
// bug fix for details option showing summary records
// 
//    Rev 1.9   15 Mar 2002 09:05:30   HSUCHIN
// bug fix for startdate visibility
// 
//    Rev 1.8   12 Mar 2002 15:46:32   HSUCHIN
// bug fix for onrbtotals to clear out fund controls on click
// 
//    Rev 1.7   12 Mar 2002 10:25:16   HSUCHIN
// changed the way the radio buttons function and support for summary accruals containers
// 
//    Rev 1.6   08 Mar 2002 12:35:22   HSUCHIN
// bug fix for refresh
// 
//    Rev 1.5   08 Mar 2002 09:33:20   HSUCHIN
// hide PST exemption for now
// 
//    Rev 1.4   07 Mar 2002 16:36:48   HSUCHIN
// bug fixes and enhancements
// 
//    Rev 1.3   06 Mar 2002 17:16:40   HSUCHIN
// bug fix - controls not displaying data properly
// 
//    Rev 1.2   27 Feb 2002 16:10:16   HSUCHIN
// bug fix reconnectcontrols
// 
//    Rev 1.1   26 Feb 2002 16:55:42   HSUCHIN
// finalized for MF/MFR, minor changes and fixes
// 
//    Rev 1.0   21 Feb 2002 16:08:30   HSUCHIN
// Initial revision.
*/