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
//    Copyright 2000 by DST Systems, Inc.
//
//******************************************************************************
//
// ^FILE   : GuaranteeInfoDlg1.cpp
// ^AUTHOR : 
// ^DATE   : 
//
// ^CLASS    : 
// ^SUBCLASS :       
//
// ^CLASS DESCRIPTION : 
//
//******************************************************************************
// GuaranteeInfoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "mfdstc.h"
#include "GuaranteeInfoDlg1.h"
#include <ifastbp\GuaranteeInfoProcessIncludes.h>

#ifndef CONTRACTINFOPROCESSINCLUDES_H
   #include <ifastbp\ContractInfoProcessIncludes.h>
#endif

#ifndef DSTLISTCTRL_H
   #include <uibase\dstlistctrl.h>
#endif

#include <uibase\DSTGridWnd.h>

#ifndef DSTCOMMONFUNCTION_HPP
   #include <ifastcbo\DSTCommonFunction.hpp>
#endif

#ifndef DSTCWORKSESSION_HPP
   #include <ifastcbo\DSTCWorkSession.hpp>
#endif

//HllApi
#include <ifastcsi\CsiSession.h>
#include <ifastcsi\ifastcsi.h>

extern CLASS_IMPORT const I_CHAR* CMD_BPROC_CONTRACTINFO;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_ENTITY;
extern CLASS_IMPORT const I_CHAR* CMD_GUI_GUARANTEEINFO1;
#include <bfproc\concretedialogcreator.hpp>
static ConcreteDialogCreator< GuaranteeInfoDlg1 > dlgCreator( CMD_GUI_GUARANTEEINFO1 );

#ifdef _DEBUG
   #define new DEBUG_NEW
   #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


namespace
{
   // trace literals
   const I_CHAR * const CLASSNAME        = I_( "GuaranteeInfoDlg1" );
   const I_CHAR * const LV_GUARANTEE     = I_( "GuaranteeInfoList" );
   const I_CHAR * const LV_ACCTGUARANTEE = I_( "AcctGuaranteeInfoList" );
   const I_CHAR * const SPACE_STRING     = I_( " " ); 
   const I_CHAR * const MFDSTC           = I_( "MFDSTC" );   
   const I_CHAR * const CANADA           = I_("Canada");
   const I_CHAR * const JAPAN            = I_("Japan");
   const I_CHAR * const MARKET           = I_( "Market" );
   const I_CHAR * const TRANSTYPE        = I_( "TransType" );
   const I_CHAR * const FUND_NUMBER      = I_( "Baycom" );
   const I_CHAR * const TRANSID          = I_( "TransactionId" );
   const I_CHAR * const GUARAMTATMATUR   = I_( "GuarAmtAtMatur" );

   // Define GuaranteeRedDetailTop's code
   const I_CHAR * const POLICYPERIOD     = I_( "PolicyPeriod" );
   const I_CHAR * const ACCOUNTVALUE     = I_( "AccountValue" );

   // Define GuaranteeRedDetailLeft's code
   const I_CHAR * const BEFOREREDNAV     = I_( "BeforeRedNAV" );
   const I_CHAR * const AMTREDAPLNAV     = I_( "AmtRedAplNAV" );
   const I_CHAR * const REDPERCENTNAV    = I_( "RedPercentNAV" );
   const I_CHAR * const AFTERREDNAV      = I_( "AfterRedNAV" );
   const I_CHAR * const GUARANTEED       = I_( "GUARANTEE" );
   const I_CHAR * const BEFOREREDGUR     = I_( "BeforeRedGUR" );
   const I_CHAR * const REDUCTIONGUR     = I_( "ReductionGUR" );
   const I_CHAR * const AFTERREDGUR      = I_( "AfterRedGUR" );

   // Define GuaranteeGADetailTop's code
   const I_CHAR * const ATTRIBUTE        = I_( "Attribute" );
   const I_CHAR * const VALUE            = I_( "Value" );

   // Define GuaranteeGADetailLeft's code   
   const I_CHAR * const PROCESSDATE      = I_( "ProcessDate" );
   const I_CHAR * const PREVIOUSGUAR     = I_( "GuarBefRedPeriod" );
   const I_CHAR * const CHANGEAMOUNT     = I_( "GuarRedctnPeriod" );
   const I_CHAR * const NEWGUARANTEE     = I_( "GuarAftRedPeriod" );

   // Define GuarTesetListHeading's code
   const I_CHAR * const RESETMATURDATE   = I_( "ResetMaturDate" );
   const I_CHAR * const RESETNAV         = I_( "ResetNAV" );
   const I_CHAR * const PREVGUAR         = I_( "PrevGuar" );
   const I_CHAR * const RESETGUARAMOUNT  = I_( "ResetGuarAmount" );
   const I_CHAR * const GUARTOT          = I_( "GuarTot" );

   const I_CHAR* const GR_GUARREDDETAIL  = I_( "GridGuaranteeEdDetails" );
   const I_CHAR* const GR_GUARGADETAIL   = I_( "GridGuaranteeGADetails" );
   const I_CHAR* const GR_GUARRESETLIST  = I_( "GridGuaranteeESetList" );
   const int REPEAT_RECORDS              = 25;
}

namespace CND
{  // Conditions used
   extern const long GUI_ERR_UNKNOWN_EXCEPTION;
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId GuaranteeAcctListHeading;

   extern CLASS_IMPORT const BFTextFieldId GuaranteeGADetailTop;
   extern CLASS_IMPORT const BFTextFieldId GuaranteeGADetailLeft;
}

/////////////////////////////////////////////////////////////////////////////
// GuaranteeInfoDlg dialog
/***********************************************************************/

GuaranteeInfoDlg1::GuaranteeInfoDlg1(CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: BaseMainDlg( GuaranteeInfoDlg1::IDD, pParent, pGIC, pGIParent, rCommand )
, m_rbPolicyYearTerm( true )
, m_rbContract( false )
, _count1( 0 )
, _count2( 0 )
, _strTotal( NULL_STRING )
, _dTotal( 0 )
{
   //{{AFX_DATA_INIT(GuaranteeInfoDlg)
   //}}AFX_DATA_INIT

}

/***********************************************************************/
void GuaranteeInfoDlg1::DoDataExchange(CDataExchange* pDX)
{
   BaseMainDlg::DoDataExchange(pDX);

   //{{AFX_DATA_MAP(GuaranteeInfoDlg)
   //	DDX_Radio(pDX, IDC_BYPOL_YEAR_TERM, m_rbRbYearTerm);
   //}}AFX_DATA_MAP
}
//**********************************************************************

/***********************************************************************/
BEGIN_MESSAGE_MAP(GuaranteeInfoDlg1, BaseMainDlg)
//{{AFX_MSG_MAP(GuaranteeInfoDlg)
ON_BN_CLICKED(IDC_BTN_CONTRACT, OnBtnContract)
ON_BN_CLICKED(IDC_BTN_ENTITY, OnBtnEntity)
ON_BN_CLICKED(IDC_BTN_MORE, OnBtnMore)
ON_BN_CLICKED(IDC_BTN_SEG_OPTIONS, OnBtnSegOptions)
ON_BN_CLICKED(IDC_BYCONTRACT, OnRbContract)
ON_BN_CLICKED(IDC_BYPOL_YEAR_TERM, OnRbYearTerm)

//}}AFX_MSG_MAP
END_MESSAGE_MAP()



/////////////////////////////////////////////////////////////////////////////
// GuaranteeInfoDlg message handlers
/***********************************************************************/
SEVERITY GuaranteeInfoDlg1::doInit()
{
   TRACE_METHOD( CLASSNAME, I_("doInit"));
   SEVERITY sevRtn = SEVERE_ERROR;
   // getParameter( GUARANTEE::KEY_PARAM, m_dstrKey );
   getParameter( GUARANTEE::SHAREHOLD_NUMBER, m_dstrShareHoldNum );
   getParameter( GUARANTEE::ACCOUNT_NUMBER, m_dstrAccountNumber );
   getParameter( GUARANTEE::GUAR_ACCT_TOTAL, m_dstrGuarAcctTotal );
   sevRtn = NO_CONDITION;
   return(sevRtn);
}

//***********************************************************************
void GuaranteeInfoDlg1::OnRbContract()
{
   m_rbContract = true;
   m_rbPolicyYearTerm = false;
   const DString *pdstrKey = &(getParent()->getFirstListItemKey(this, IFASTBP_PROC::GUARANTEEINFO_LIST));
   if( *pdstrKey != NULL_STRING )
   {
      _count2 = 0;
      _dTotal = 0;

      LoadListControl( IDC_LV_GUARANTEE, NULL );

      // int numGuarListItems = getParent()->getNumberOfItemsInList( this, GUARANTEEINFO_LIST);

      if( _count2 < REPEAT_RECORDS )
         GetDlgItem( IDC_BTN_MORE )->EnableWindow( false );
      else
         GetDlgItem( IDC_BTN_MORE )->EnableWindow( true );
   }
   else
   {
      GetDlgItem( IDC_BTN_MORE )->EnableWindow( false );
      GetDlgItem( IDC_GD_GUARREDDETAIL )->ShowWindow( SW_HIDE );
	  GetDlgItem( IDC_GD_GUARGADETAIL )->ShowWindow( SW_HIDE );
      GetDlgItem( IDC_GD_GUARRESETLIST )->ShowWindow( SW_HIDE );
   }

}
//***********************************************************************
void GuaranteeInfoDlg1::OnRbYearTerm()
{
   m_rbPolicyYearTerm = true;
   m_rbContract = false;
   const DString *pdstrKey = &(getParent()->getFirstListItemKey(this, IFASTBP_PROC::GUARANTEEINFO_LIST));
   if( *pdstrKey != NULL_STRING )
   {
      _count1 = 0;
      _dTotal = 0;
      LoadListControl( IDC_LV_GUARANTEE, NULL );
      DString _strTotal = DSTCommonFunctions::doubleToDString( ifds::GuarAmount, _dTotal );
      GetDlgItem(IDC_STATIC_CONTR_GUARAMT)->SetWindowText( _strTotal.c_str() );

      //int numGuarListItems = getParent()->getNumberOfItemsInList( this, GUARANTEEINFO_LIST);
      if( _count1 < REPEAT_RECORDS )
         GetDlgItem( IDC_BTN_MORE )->EnableWindow( false );
      else
         GetDlgItem( IDC_BTN_MORE )->EnableWindow( true );
   }
   else
   {
      GetDlgItem( IDC_BTN_MORE )->EnableWindow( false );
      GetDlgItem( IDC_GD_GUARREDDETAIL )->ShowWindow( SW_HIDE );
	  GetDlgItem( IDC_GD_GUARGADETAIL )->ShowWindow( SW_HIDE );
      GetDlgItem( IDC_GD_GUARRESETLIST )->ShowWindow( SW_HIDE );
   }

}
//***********************************************************************

BOOL GuaranteeInfoDlg1::OnInitDialog() 
{
   TRACE_METHOD( CLASSNAME, ONINITDIALOG );

   BaseMainDlg::OnInitDialog();


   // set AccountNum, ShareHolderNum and Entity Name in the title bar
   setTitleBar ( );

   return(TRUE);  // return TRUE unless you set the focus to a control
   // EXCEPTION: OCX Property Pages should return FALSE
}

//*****************************************************************************
void GuaranteeInfoDlg1::setTitleBar ( )
{

   m_dstrShareHoldNum.stripLeading().stripLeading(I_CHAR('0')).stripTrailing();
   m_dstrAccountNumber.stripLeading(I_CHAR('0')).stripTrailing();

   SetAccount( m_dstrAccountNumber );

   DString dstrEntityName;
   dynamic_cast<DSTCWorkSession *>(getBFWorkSession())->
   getFirstSequenced01AccountholderEntityName(getDataGroupId(),
                                              m_dstrAccountNumber,dstrEntityName);

   SetShrAcctCaption(m_dstrShareHoldNum, m_dstrAccountNumber, dstrEntityName);

}

//*****************************************************************************
void GuaranteeInfoDlg1::OnPostInitDialog()
{
   TRACE_METHOD( CLASSNAME, ONPOSTINITDIALOG );


   CButton *pRadioButton = static_cast < CButton* > ( GetDlgItem( IDC_BYPOL_YEAR_TERM ) );
   //CheckRadioButton( IDC_BYPOL_YEAR_TERM, IDC_BYCONTRACT, IDC_BYPOL_YEAR_TERM );
   pRadioButton->SetCheck( 1 );

   AddGrid( CLASSNAME, IDC_GD_GUARREDDETAIL, GR_GUARREDDETAIL, IFASTBP_PROC::GUARANTEEINFO_LIST,
            0, ifds::GuaranteeRedDetailTop, ifds::GuaranteeRedDetailLeft );
   DSTGridWnd * grdWnd = GetGrid( IDC_GD_GUARREDDETAIL );
   grdWnd->SetRowHeight(0,7,25);
//   grdWnd->SetColWidth(0,0,270);
//   grdWnd->SetColWidth(1,1,250);
//  grdWnd->SetColWidth(2,2,250);
  
   AddGrid( CLASSNAME,                            // dialogName
	        IDC_GD_GUARRESETLIST,                 // controlID
			GR_GUARRESETLIST,                     // gridName
			IFASTBP_PROC::GUARANTEEINFO_LIST,     // idContainer
            0,                                    // controlGroupID
			ifds::GuarResetListHeading,           // idTopSubstitution
			ifds::NullFieldId,                    // idLeftSubstitution
			0 );                                  // gridType - list, NOT attrib                           


   grdWnd = GetGrid( IDC_GD_GUARRESETLIST );
//   grdWnd->SetColWidth(0,0,160);
   grdWnd->SetColWidth(1,1,150);
   grdWnd->SetColWidth(2,2,160);
   grdWnd->SetColWidth(3,3,160);
   grdWnd->SetColWidth(4,4,160);
   grdWnd->SetColWidth(5,5,160);


   //IDC_GD_GUARGADETAIL
   AddGrid( CLASSNAME, 
	        IDC_GD_GUARGADETAIL, 
			GR_GUARGADETAIL, 
			IFASTBP_PROC::GUARANTEEINFO_LIST,
            0,        // IDC_LV_TRANSACTIONS
			ifds::GuaranteeGADetailTop, 
			ifds::GuaranteeGADetailLeft );

   AddControl( CTRL_STATIC, IDC_STATIC_GUARAMTATMATUR, IFASTBP_PROC::GUARANTEEINFO_LIST, ifds::GuarAcctTotal );
   AddControl( CTRL_STATIC, IDC_STATIC_CONTR_GUARAMT, IFASTBP_PROC::GUARANTEEINFO_LIST, ifds::GuarAmount );
   AddControl( CTRL_STATIC, IDC_STATIC_TRANS_TYPE_DESC, IFASTBP_PROC::GUARANTEEINFO_LIST, ifds::TransType );
   AddControl( CTRL_STATIC, IDC_STATIC_TRADE_DATE_VALUE, IFASTBP_PROC::GUARANTEEINFO_LIST, ifds::TradeDate );
   AddControl( CTRL_STATIC, IDC_STATIC_MATUR_DATE_VALUE, IFASTBP_PROC::GUARANTEEINFO_LIST, ifds::MaturityDate );


   AddListControl( CLASSNAME, IDC_LV_ACCTGUARANTEE, LV_ACCTGUARANTEE, ifds::GuaranteeAcctListHeading,
                   IFASTBP_PROC::GUARANTEE_SUMMARY, 0, true, LISTFLAG_NOT_UPDATABLE);
   AddListControl( CLASSNAME, IDC_LV_GUARANTEE, LV_GUARANTEE, ifds::GuaranteeListHeading,
                   IFASTBP_PROC::GUARANTEEINFO_LIST, IDC_LV_ACCTGUARANTEE, true, LISTFLAG_NOT_UPDATABLE);

   m_dstrGuarAcctTotal.strip().stripLeading('0');

   m_dstrGuarAcctTotal.formatStringUsingMask(I_("9,999,999,999,999.99"));

   GetDlgItem(IDC_STATIC_GUARAMTATMATUR)->SetWindowText( m_dstrGuarAcctTotal.c_str() );

   LoadListControl( IDC_LV_ACCTGUARANTEE, NULL );

   CWnd *MoreBut=GetDlgItem(IDC_BTN_MORE);
   if( _count1 > REPEAT_RECORDS )
   {
      MoreBut->EnableWindow(true);
   }
   else
   {
      MoreBut->EnableWindow(false);
   }
   int numGuarListItems = getParent()->getNumberOfItemsInList( this, IFASTBP_PROC::GUARANTEEINFO_LIST);
   if( numGuarListItems == 0 )
   {
      GetDlgItem( IDC_GD_GUARREDDETAIL )->ShowWindow( SW_HIDE );
	  GetDlgItem( IDC_GD_GUARGADETAIL )->ShowWindow( SW_HIDE );
      GetDlgItem( IDC_GD_GUARRESETLIST )->ShowWindow( SW_HIDE );
      GetDlgItem( IDC_STATIC_ELSE )->ShowWindow( SW_SHOW );
   }

}

/*******************************************************************************************/
void GuaranteeInfoDlg1::AdjustControl()
{

   CWnd *StControl;
	int numGuarListItems = getParent()->getNumberOfItemsInList( this, IFASTBP_PROC::GUARANTEEINFO_LIST);
   if ( numGuarListItems > 0 )
   {
		DString dstrTransType, dstrRecType, dstrTransId;
		getParent()->getField(this, IFASTBP_PROC::GUARANTEEINFO_LIST, ifds::TransType, dstrTransType, false);
		dstrTransType.stripAll();
		if (dstrTransType == I_("AF") || dstrTransType == I_("DF") || 
			 dstrTransType == I_("PW") || dstrTransType == I_("TO"))
		{
			GetDlgItem( IDC_GD_GUARREDDETAIL )->ShowWindow( SW_SHOW );
			GetDlgItem( IDC_GD_GUARGADETAIL )->ShowWindow( SW_HIDE );
			GetDlgItem( IDC_GD_GUARRESETLIST )->ShowWindow( SW_HIDE );
			GetDlgItem( IDC_STATIC_ELSE )->ShowWindow( SW_HIDE );

			ConnectControlsToData();
			LoadControls( -1L );   
			LoadControl( IDC_STATIC_MATUR_DATE_VALUE);

			// For "AF", "DF", "PW" and "TO", Redemption Detail screen will only have 
			// each "S" an "D" record types and the detail record is the next one of the 
			// current record with "S".
			m_dstrKey = getParent()->getNextListItemKey(this, IFASTBP_PROC::GUARANTEEINFO_LIST);
			LoadGrid( IDC_GD_GUARREDDETAIL );  // Load next record to the grid
     
			// Change text to "Guaranteed account total:"
			StControl = GetDlgItem( IDC_STATIC_GUARACC_TOTAL ) ;
			StControl->ShowWindow( SW_SHOW );
			StControl->SetWindowText(I_( "Guaranteed account total: "));

			// Change text to "Guarantee Redubion Details"
			StControl = GetDlgItem( IDC_STATIC_GUARACC_DETAIL ) ;
			StControl->ShowWindow( SW_SHOW );
			StControl->SetWindowText(I_( "&Guarantee Reduction Details "));

		}		
		else if (dstrTransType == I_("RS"))
		{
			GetDlgItem( IDC_GD_GUARREDDETAIL )->ShowWindow( SW_HIDE );
			GetDlgItem( IDC_GD_GUARGADETAIL )->ShowWindow( SW_HIDE );
			GetDlgItem( IDC_GD_GUARRESETLIST )->ShowWindow( SW_SHOW );
			GetDlgItem( IDC_STATIC_ELSE )->ShowWindow( SW_HIDE );

	//      ShowOrHide(true);
			ConnectControlsToData();
			LoadControls( -1L );   
			LoadControl( IDC_STATIC_MATUR_DATE_VALUE);

			// Since "RS" transactions may have multiple history records, So Reset Detail
			// Info will have one "S" and multiple "D" record and they are located together
			m_dstrKey = getParent()->getNextListItemKey(this, IFASTBP_PROC::GUARANTEEINFO_LIST);
			m_bFirst = true;
			LoadGrid( IDC_GD_GUARRESETLIST );

			// Change text to "Guaranteed reset total:"
			StControl = GetDlgItem( IDC_STATIC_GUARACC_TOTAL ) ;
			StControl->ShowWindow( SW_SHOW );
			StControl->SetWindowText(I_( "Guaranteed reset total: "));

			// Change text to "Guarantee reset Details"
			StControl = GetDlgItem( IDC_STATIC_GUARACC_DETAIL ) ;
			StControl->ShowWindow( SW_SHOW );
			StControl->SetWindowText(I_( "&Guarantee Reset Details "));

		}
		else if ( dstrTransType == I_("GA") )
		{
			GetDlgItem( IDC_GD_GUARREDDETAIL )->ShowWindow( SW_HIDE );
			GetDlgItem( IDC_GD_GUARGADETAIL )->ShowWindow( SW_SHOW );
			GetDlgItem( IDC_GD_GUARRESETLIST )->ShowWindow( SW_HIDE );
			GetDlgItem( IDC_STATIC_ELSE )->ShowWindow( SW_HIDE );

			ConnectControlsToData();
			LoadControls( -1L );   
			//LoadControl( IDC_STATIC_MATUR_DATE_VALUE);
			
			m_dstrKey = getParent()->getNextListItemKey(this, IFASTBP_PROC::GUARANTEEINFO_LIST);
			LoadGrid( IDC_GD_GUARGADETAIL );  // Load next record to the grid

            // Change text to "Guarantee Redubion Details"
			StControl = GetDlgItem( IDC_STATIC_GUARACC_DETAIL ) ;
			StControl->ShowWindow( SW_SHOW );
			StControl->SetWindowText(I_( "&Guarantee Adjustment Details "));
		}
		else 
		{
			GetDlgItem( IDC_GD_GUARREDDETAIL )->ShowWindow( SW_HIDE );
			GetDlgItem( IDC_GD_GUARGADETAIL )->ShowWindow( SW_HIDE );
			GetDlgItem( IDC_GD_GUARRESETLIST )->ShowWindow( SW_HIDE );
		  // ConnectControlToData( IDC_STATIC_GUARAMTATMATUR, true);
		  // LoadControl(IDC_STATIC_GUARAMTATMATUR);
			GetDlgItem( IDC_STATIC_ELSE )->ShowWindow( SW_SHOW );

			// Set text for IDC_STATIC_GUARACC_TOTAL
			StControl = GetDlgItem( IDC_STATIC_GUARACC_TOTAL ) ;
			StControl->ShowWindow( SW_SHOW );
			StControl->SetWindowText(I_( "Guaranteed account total: "));
		}
	}
}

/*******************************************************************************************/
bool GuaranteeInfoDlg1::GetDataForControl(
                                         UINT controlID,
                                         DString &strValueOut,
                                         bool bFormatted,
                                         int index
                                         ) const
{
   strValueOut = NULL_STRING;
   DString dstr;

   switch( controlID )
   {
      case IDC_STATIC_MATUR_DATE_VALUE:
         getParent()->getField(this, IFASTBP_PROC::GUARANTEEINFO_LIST, ifds::TransType, dstr, false);
         dstr.stripAll();
         if( dstr == I_("RS") )
            getParent()->getField(this, IFASTBP_PROC::GUARANTEEINFO_LIST, ifds::ResetMaturDate, dstr);
         else
            getParent()->getField(this, IFASTBP_PROC::GUARANTEEINFO_LIST, ifds::MaturityDate, dstr);
         strValueOut = dstr.stripAll();
         break;

      case IDC_STATIC_GUARAMTATMATUR:
         strValueOut = m_dstrGuarAcctTotal;
         break;
      default :
         return(false);
   }    
   return(true);
}

/*******************************************************************************************/
bool GuaranteeInfoDlg1::GetOverrideItemString( long lSubstituteId, const DString& ColumnKey, DString& strOut )
{
   if( lSubstituteId == ifds::GuaranteeListHeading.getId() )
   {
      if( ColumnKey == TRANSTYPE )
      {
         DString dstrValue;
         getParent()->getField(this, IFASTBP_PROC::GUARANTEEINFO_LIST, ifds::TransType, dstrValue, false);
         dstrValue.stripAll();
         strOut = dstrValue;
         return(true);
      }
      if( ColumnKey == FUND_NUMBER )
      {
         DString dstrFundCode, dstrClassCode;
         getParent()->getField( this, IFASTBP_PROC::GUARANTEEINFO_LIST, ifds::FundCode, dstrFundCode );
         getParent()->getField( this, IFASTBP_PROC::GUARANTEEINFO_LIST, ifds::ClassCode, dstrClassCode );
         dstrFundCode.strip().upperCase();
         dstrClassCode.strip().upperCase();
         dynamic_cast<DSTCWorkSession *>(getBFWorkSession())->GetFundNumber( dstrFundCode, dstrClassCode, strOut );
         return(true);
      }
      if( ColumnKey == TRANSID )
      {
         DString dstrValue;
         getParent()->getField(this, IFASTBP_PROC::GUARANTEEINFO_LIST, ifds::TransactionId, dstrValue, false);
         dstrValue.strip().stripLeading( '0' );
         strOut = dstrValue;
         return(true);
      }
      if( ColumnKey == GUARAMTATMATUR )
      {
         DString dstrValue;
         getParent()->getField(this, IFASTBP_PROC::GUARANTEEINFO_LIST, ifds::GuarAmtAtMatur , dstrValue, false);
         dstrValue.strip().stripLeading( '0' );
         dstrValue.formatStringUsingMask(I_("9,999,999,999,999.99")); 
         strOut = dstrValue;
         return(true);
      }
   }
   return(false);
}


//*******************************************************************************/
void GuaranteeInfoDlg1::OnBtnContract() 
{
   // TODO: Add your control notification handler code here
   TRACE_METHOD( CLASSNAME, I_("OnBtnContract"));
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_(" OnBtnContract() " ) );

   // For the user click Entity button at ContractInfoDlg
//   setParameter( GUARANTEE::KEY_PARAM, m_dstrKey );

   setParameter( GUARANTEE::ACCOUNT_NUMBER, m_dstrAccountNumber);
   setParameter( GUARANTEE::SHAREHOLD_NUMBER, m_dstrShareHoldNum );
   SetMessageStatusBar( TXT_LOAD_CONTRACT );

   try
   {
      bool bModal = false;   // Default to modeless
      E_COMMANDRETURN eRtn;
      eRtn = invokeCommand( getParent(), CMD_BPROC_CONTRACTINFO, PROC_NO_TYPE, bModal, NULL );
      switch( eRtn )
      {
         case CMD_OK:
         case CMD_CANCEL:
         case CMD_MODELESS_INPROCESS:
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

/***********************************************************************/
void GuaranteeInfoDlg1::OnBtnEntity() 
{
   // TODO: Add your control notification handler code here

   TRACE_METHOD( CLASSNAME, I_("OnBtnEntity"));
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_(" OnBtnEntity() " ) );

//   setParameter( GUARANTEE::KEY_PARAM, m_dstrKey );
   setParameter( GUARANTEE::ACCOUNT_NUMBER, m_dstrAccountNumber);

   SetMessageStatusBar( TXT_LOAD_ENTITY );

   try
   {
      bool bModal = false;   // default is modaless
      E_COMMANDRETURN eRtn;
      eRtn = invokeCommand( getParent(), CMD_BPROC_ENTITY, PROC_NO_TYPE, bModal, NULL );
      switch( eRtn )
      {
         case CMD_OK:
         case CMD_CANCEL:
         case CMD_MODELESS_INPROCESS:
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

/***********************************************************************/
void GuaranteeInfoDlg1::OnBtnMore() 
{
   // TODO: Add your control notification handler code here
   TRACE_METHOD( CLASSNAME, I_("OnBtnMore"));

   CWaitCursor wait;
   SetMessageStatusBar( TXT_LOAD_GUARANTEE );
   getParent()->getData( this, NULL );
   const DString *crtKey = &getParent()->getCurrentListItemKey( this, IFASTBP_PROC::GUARANTEEINFO_LIST );
   LoadListControl( IDC_LV_GUARANTEE, NULL );
   if( *crtKey != NULL_STRING )
   {
      bool MoreRecordsExist=getParent()->doMoreRecordsExist( this, BF::NullContainerId );
      CWnd *MoreBut=GetDlgItem(IDC_BTN_MORE);
      MoreBut->EnableWindow(MoreRecordsExist);
      GetList( IDC_LV_GUARANTEE )->SetSelection( crtKey );
//      AdjustControl();
   }

   SetMessageStatusBar(NULL_STRING);  
}

/***********************************************************************/
void GuaranteeInfoDlg1::OnBtnSegOptions() 
{
   setCsiParameter( DcCsiParameters::ACCOUNT_NUMBER, DStringA(m_dstrAccountNumber) );
   executeCsiProcess( DcCsiProcesses::GUARANTEE_TRANSACTION);  
}

/**********************************************************************************/
void GuaranteeInfoDlg1::DoListItemChanged( UINT listControlID, const DString &strKey, 
                                           bool bIsNewItem , bool bIsDummyItem)
{
   TRACE_METHOD( CLASSNAME, I_("DoListItemChanged"));
   AdjustControl();
   if( listControlID == IDC_LV_ACCTGUARANTEE )
   {
      _count1 = 0;
      _count2 = 0;
      _dTotal = 0;

   }
   if( _dTotal != 0 )
   {
      DString _strTotal = DSTCommonFunctions::doubleToDString( ifds::GuarAmount, _dTotal );
      GetDlgItem(IDC_STATIC_CONTR_GUARAMT)->SetWindowText( _strTotal.c_str() );
   }
}

/**********************************************************************************/
void GuaranteeInfoDlg1::GetCellProperties( UINT ctrlId, const DString &rowKey,
                                           const DString &colKey, BFContainerId& idContainer, BFFieldId &idField,
                                           DString& listItemKey, int& nCellState, UINT& cellCtrlType,
                                           int& nCtrlInitMode, BFFieldId &idSubstitution,DString& comboList,
                                           DString& mask )
{
   idContainer = IFASTBP_PROC::GUARANTEEINFO_LIST;
//   const DString *Key = &getParent()->getNextListItemKey( this, GUARANTEEINFO_LIST );

//   listItemKey =GetList( IDC_LV_GUARANTEE )->GetCurrentKey();
   nCellState = DSTGridWnd::READ_ONLY;
   if( ctrlId == IDC_GD_GUARREDDETAIL )
   {
      listItemKey = m_dstrKey;
      if( rowKey == BEFOREREDNAV )    // Row "Before Redemtion"
      {
         if( colKey == POLICYPERIOD )idField = ifds::NAVBefRedPeriod;
         if( colKey == ACCOUNTVALUE )idField = ifds::NAVBefRedAcct;
      }
      if( rowKey == AMTREDAPLNAV )    // Row "Amount of Redemption Applied"
      {
         if( colKey == POLICYPERIOD )idField = ifds::RedAmountPeriod;
         if( colKey == ACCOUNTVALUE )idField = ifds::RedAmountAcct;
      }
      if( rowKey == REDPERCENTNAV )   // Row "Redemption as percent of NAV"
      {
         if( colKey == POLICYPERIOD ) nCellState = DSTGridWnd::SKIPPED;
         if( colKey == ACCOUNTVALUE )idField = ifds::Percentage;
      }
      if( rowKey == AFTERREDNAV )     // Row "After Redemption"
      {
         if( colKey == POLICYPERIOD )idField = ifds::NAVAftRedPeriod;
         if( colKey == ACCOUNTVALUE )idField = ifds::NAVAftRedAcct;
      }
      if( rowKey == GUARANTEED )       // Row " GUARANTEE"
      {
         if( colKey == POLICYPERIOD ) nCellState = DSTGridWnd::SKIPPED;
         if( colKey == ACCOUNTVALUE ) nCellState = DSTGridWnd::SKIPPED;
      }
      if( rowKey == BEFOREREDGUR )    // Row "Before Redemption"
      {
         if( colKey == POLICYPERIOD )idField = ifds::GuarBefRedPeriod;
         if( colKey == ACCOUNTVALUE )idField = ifds::GuarBefRedAcct;
      }
      if( rowKey == REDUCTIONGUR )    // Row "Reduction"
      {
         if( colKey == POLICYPERIOD )idField = ifds::GuarRedctnPeriod;
         if( colKey == ACCOUNTVALUE )idField = ifds::GuarRedctnAct;
      }
      if( rowKey == AFTERREDGUR )     // Row "After Redemption"
      {
         if( colKey == POLICYPERIOD )idField = ifds::GuarAftRedPeriod;
         if( colKey == ACCOUNTVALUE )idField = ifds::GuarAftRedAcct;
      }
   }
   else if( ctrlId == IDC_GD_GUARGADETAIL )
   {
      if ( colKey == VALUE )
	  {
		if ( rowKey == PROCESSDATE )
			idField = ifds::ProcessDate;
		else if ( rowKey == PREVIOUSGUAR )
			idField = ifds::GuarBefRedPeriod;
        else if ( rowKey == CHANGEAMOUNT )
			idField = ifds::GuarRedctnPeriod;
		else if ( rowKey == NEWGUARANTEE )
			idField = ifds::GuarAftRedPeriod;
	  }
   }
   else if( ctrlId == IDC_GD_GUARRESETLIST )
   {
//      getParent()->setCurrentListItem(this, GUARANTEEINFO_LIST, m_dstrKey)
      if( colKey == RESETMATURDATE ) idField = ifds::ResetMaturDate;
      if( colKey == RESETNAV )       idField = ifds::ResetNAV;
      if( colKey == PREVGUAR )       idField = ifds::PrevGuar;
      if( colKey == RESETGUARAMOUNT )idField = ifds::ResetGuarAmount;
      if( colKey == GUARTOT )        idField = ifds::GuarTot;
   }
}

/**********************************************************************************/
bool GuaranteeInfoDlg1::GridControlFilter( UINT ctrlId, const DString &rowKey )
{
   bool bRet = false, bResetRec;
   if( m_bFirst )
      bResetRec = false;

   if( ctrlId == IDC_GD_GUARRESETLIST )
   {
      if( rowKey == m_dstrKey )
      {
         bResetRec = true;
         m_bFirst = false;
      }
      DString dstrRecType;
      getParent()->getField(this, IFASTBP_PROC::GUARANTEEINFO_LIST, ifds::RecType, dstrRecType, false);
      if( dstrRecType == I_( "S" ) )
         bResetRec = false;
      if( dstrRecType == I_( "D" ) && bResetRec == true )
         bRet = true;
      else
         bRet = false;
   }

   return(bRet);
}

//******************************************************************************
bool GuaranteeInfoDlg1::doRefresh( GenericInterface * rpGICaller,const I_CHAR * szOriginalCommand)
{  
   TRACE_METHOD( CLASSNAME, I_("doRefresh"));

   getParameter( GUARANTEE::KEY_PARAM, m_dstrKey );
   getParameter( GUARANTEE::SHAREHOLD_NUMBER, m_dstrShareHoldNum );
   getParameter( GUARANTEE::ACCOUNT_NUMBER, m_dstrAccountNumber );

   // set AccountNum, ShareHolderNum and Entity Name in the title bar
   setTitleBar ( );

   LoadListControl( IDC_LV_ACCTGUARANTEE, NULL );

   const DString *pdstrKey = &(getParent()->getFirstListItemKey(this, IFASTBP_PROC::GUARANTEEINFO_LIST));
   LoadListControl( IDC_LV_GUARANTEE, NULL );

   bool MoreRecordsExist=getParent()->doMoreRecordsExist( this, BF::NullContainerId );
   CWnd *MoreBut=GetDlgItem(IDC_BTN_MORE);
   MoreBut->EnableWindow(MoreRecordsExist);
   //  getParameter( GUARANTEE::KEY_PARAM, m_dstrKey );

   const DString *pdstrKey1 = &(getParent()->getFirstListItemKey(this, IFASTBP_PROC::GUARANTEEINFO_LIST));

   AdjustControl();

   if( m_rbPolicyYearTerm )
      OnRbYearTerm();
   if( m_rbContract )
      OnRbContract();


   return(true);
}
//*********************************************************************************
bool GuaranteeInfoDlg1::ListViewControlFilter( long lSubstituteId, const DString * )
{
   bool bRet = false;

   if( lSubstituteId == ifds::GuaranteeListHeading.getId() )
   {
      if( m_rbContract )
      {

         DString dstrContractType, dstrContractTypeGuar, dstrPolicyYearGuar, dstrPolicyTermGuar, 
         dstrPolicyYear, dstrPolicyTerm, dstrGuarAmt;
         getParent()->getField( this, IFASTBP_PROC::GUARANTEE_SUMMARY, ifds::ContractType, dstrContractType, false);
         getParent()->getField( this, IFASTBP_PROC::GUARANTEEINFO_LIST, ifds::ContractType, dstrContractTypeGuar, false);
         getParent()->getField( this, IFASTBP_PROC::GUARANTEEINFO_LIST, ifds::PolicyYear, dstrPolicyYearGuar, false);
         getParent()->getField( this, IFASTBP_PROC::GUARANTEEINFO_LIST, ifds::PolicyTerm, dstrPolicyTermGuar, false);
         getParent()->getField( this, IFASTBP_PROC::GUARANTEE_SUMMARY, ifds::PolicyYear, dstrPolicyYear, false);
         getParent()->getField( this, IFASTBP_PROC::GUARANTEE_SUMMARY, ifds::PolicyTerm, dstrPolicyTerm, false);

         if( dstrContractType == dstrContractTypeGuar )
         {
            bRet = true;
            _count2 += 1;

            if( ( dstrPolicyYear == dstrPolicyYearGuar ) && ( dstrPolicyTerm == dstrPolicyTermGuar) )
            {
               getParent()->getField( this, IFASTBP_PROC::GUARANTEEINFO_LIST, ifds::GuarAmount, dstrGuarAmt, false);
               double dNumber = DSTCommonFunctions::convertToDouble( dstrGuarAmt );
               _dTotal += dNumber; 
            }
         }
      }
      else if( m_rbPolicyYearTerm )
      {

         DString dstrContractType,dstrPolicyYear, dstrGuarAmt, dstrPolicyTerm,dstrPolicyYearGuar, dstrPolicyTermGuar, dstrContractTypeGuar;
         getParent()->getField( this, IFASTBP_PROC::GUARANTEE_SUMMARY, ifds::ContractType, dstrContractType, false);
         getParent()->getField( this, IFASTBP_PROC::GUARANTEE_SUMMARY, ifds::PolicyYear, dstrPolicyYear, false);
         getParent()->getField( this, IFASTBP_PROC::GUARANTEE_SUMMARY, ifds::PolicyTerm, dstrPolicyTerm, false);
         getParent()->getField( this, IFASTBP_PROC::GUARANTEEINFO_LIST, ifds::ContractType, dstrContractTypeGuar, false);
         getParent()->getField( this, IFASTBP_PROC::GUARANTEEINFO_LIST, ifds::PolicyYear, dstrPolicyYearGuar, false);
         getParent()->getField( this, IFASTBP_PROC::GUARANTEEINFO_LIST, ifds::PolicyTerm, dstrPolicyTermGuar, false);

         if( ( dstrContractType == dstrContractTypeGuar ) && ( dstrPolicyYear == dstrPolicyYearGuar )
             && ( dstrPolicyTerm == dstrPolicyTermGuar) )
         {
            getParent()->getField( this, IFASTBP_PROC::GUARANTEEINFO_LIST, ifds::GuarAmount, dstrGuarAmt, false);
            double dNumber = DSTCommonFunctions::convertToDouble( dstrGuarAmt );

            bRet = true; 
            _count1+= 1;
            _dTotal += dNumber; 
         }
      }
   }
   if( lSubstituteId == ifds::GuaranteeAcctListHeading.getId() )
   {
      /* DString dstrContractType, dstrContractTypeGuarSum;
       getParent()->getField( this, GUARANTEE::CONTRACTINFO_LIST, DBR::ContractType, dstrContractType, false);
       getParent()->getField( this, GUARANTEE::GUARANTEE_SUMMARY, DBR::ContractType, dstrContractTypeGuarSum, false);
 
       if ( dstrContractType == dstrContractTypeGuarSum )*/
      bRet = true;
   }

   return(bRet);
}
//*********************************************************************************

/**********************************************************************************


//*********************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastgui/GuaranteeInfoDlg1.cpp-arc  $
// 
//    Rev 1.21   Jul 06 2005 12:51:32   porteanm
// Incident 350185 - Details for Reset transaction were not displayed.
// 
//    Rev 1.20   Jun 20 2005 15:58:30   porteanm
// PET1024 FN40 - Guarantee Adjustments.
// 
//    Rev 1.19   Jun 14 2005 15:30:00   porteanm
// PET1024 FN40 - Guarantee Adjustments.
// 
//    Rev 1.18   Nov 14 2004 15:00:42   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.17   Mar 21 2003 18:37:14   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.16   Nov 29 2002 15:49:10   ZHANGCEL
// Synced up to 1.15
// 
//    Rev 1.15   Oct 09 2002 23:55:42   PURDYECH
// PVCS Database Conversion
// 
//    Rev 1.14   Oct 09 2002 16:02:24   PURDYECH
// BFFieldId fixups
// 
//    Rev 1.13   Aug 29 2002 20:09:24   SMITHDAV
// CellProperties fixes
// 
//    Rev 1.12   Aug 29 2002 18:27:54   SMITHDAV
// Additional fixes.
// 
//    Rev 1.11   Aug 29 2002 18:14:30   SMITHDAV
// Additional FieldId fixes.
// 
//    Rev 1.10   22 May 2002 19:16:08   PURDYECH
// BFData Implementation
// 
//    Rev 1.9   27 Mar 2002 20:01:12   PURDYECH
// Process/WindowFactory overhaul
// 
//    Rev 1.8   Jan 28 2002 11:27:34   YINGBAOL
// HLLAPI Change
// 
//    Rev 1.7   Dec 13 2001 16:22:46   ZHANGCEL
// format GuarAmtAmtMatur and GuarAmtTotal using Mask (9,999,999,999,.99) in order to show formated value for those two fields
// 
//    Rev 1.6   Nov 14 2001 14:48:00   ZHANGCEL
// Strip the leading zero of TransactionId
// 
//    Rev 1.5   Oct 19 2001 16:09:34   ZHANGCEL
// Set Row height of grid to fit the contents of GaranteeDetail List
// 
//    Rev 1.4   Sep 06 2001 14:09:20   ZHANGCEL
// Added second parameter in ListViewControlFilter()
// 
//    Rev 1.3   Aug 21 2001 16:53:38   OLTEANCR
// added logic for More button & Contarct Guarantee Total display
// 
//    Rev 1.2   Aug 07 2001 15:38:26   OLTEANCR
// fixed list load issue
// 
//    Rev 1.1   Jul 30 2001 09:32:28   OLTEANCR
// added logic for radio buttons
// 
//    Rev 1.0   Jul 17 2001 10:00:30   OLTEANCR
// Initial revision.
 * 
 *    Rev 1.13   Dec 13 2000 14:42:44   KOVACSRO
 * Modified DoListItemChanged.
 * 
 *    Rev 1.12   Nov 30 2000 10:19:20   ZHANGCEL
 * Change the method for the title bar setting and clean the code up
 * 
 *    Rev 1.11   Oct 31 2000 09:34:16   DINACORN
 * Replace "Shareholder nbr" with Shareholder Number
 * 
 *    Rev 1.10   Oct 27 2000 17:36:18   ZHANGCEL
 * Bug fixed
 * 
 *    Rev 1.9   Aug 01 2000 16:02:20   ZHANGCEL
 * Bug fixed
 * 
 *    Rev 1.8   Jul 28 2000 16:48:10   ZHANGCEL
 * Fund number and bug fixed
 * 
 *    Rev 1.7   Apr 05 2000 12:43:06   DT24433
 * removed unused headers
 * 
 *    Rev 1.6   Mar 30 2000 15:18:08   ZHANGCEL
 * Change logic for getting detail records
 * 
 *    Rev 1.5   Mar 28 2000 10:16:12   ZHANGCEL
 * fix on loading the Grid
 * 
 *    Rev 1.4   Mar 22 2000 12:56:24   BUZILA
 * Grid changes
 * 
 *    Rev 1.3   Mar 17 2000 16:54:04   ZHANGCEL
 * Checked in for release
 * 
 *    Rev 1.1   Mar 08 2000 17:12:28   ZHANGCEL
 * Improve revision
// 
//    Rev 1.4   Mar 03 2000 15:54:22   ZHANGCEL
// Bug fixed
// 
//    Rev 1.3   Feb 22 2000 17:43:00   ZHANGCEL
// Changed fields type
// 
//    Rev 1.2   Feb 04 2000 14:08:36   ZHANGCEL
// "Milestone" Check In
 * 
 *
 */
