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
//    Copyright 1997 by DST Systems, Inc.
//
//******************************************************************************
//
// ^FILE   : FundInfoDlg.cpp
// ^AUTHOR : Mihai Virgil Buzila
// ^DATE   : 03/30/99
//
// ----------------------------------------------------------
//
// ^CLASS    : FundInfoDlg
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :  This is the code for a list selection dialog
//
//******************************************************************************
#include "stdafx.h"

#ifndef IFASTGUI_H
   #include "MFDSTC.h"
#endif

#ifndef FUNDINFODLG_H
   #include "FundInfoDlg.h"
#endif

#ifndef CONFIGMANAGER_HPP
   #include <Configmanager.hpp>
#endif

#ifndef CSISESSION_H
   #include <ifastcsi\CsiSession.h>
#endif

#ifndef DSTCCSI_H
   #include <ifastcsi\ifastcsi.h>
#endif

#ifndef DSTCOMMONFUNCTION_HPP
   #include <ifastcbo\DSTCommonFunction.hpp>
#endif

#ifndef DSTCWORKSESSION_HPP
   #include <ifastcbo\DSTCWorkSession.hpp>
#endif

#ifndef DSTCFUNCS_H
   #include <uibase\DstcFuncs.h>
#endif

#include <uibase\dstbutton.h>

#ifndef FUNDINFOPROCESSINCLUDES_H
   #include <ifastbp\FundInfoProcessIncludes.h>
#endif

extern CLASS_IMPORT const I_CHAR* CMD_GUI_FUNDINFO;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_MGMTDETAILS;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_FUNDCLASS;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_UNITFACTORS;
extern CLASS_IMPORT const I_CHAR *CMD_BPROC_VALUATION_DETAILS_BROWSER;
extern CLASS_IMPORT const I_CHAR *CMD_BPROC_PRICE_ADDITIONAL;

#include <bfproc\concretedialogcreator.hpp>
static ConcreteDialogCreator< FundInfoDlg > dlgCreator( CMD_GUI_FUNDINFO );

#ifdef _DEBUG
   #define new DEBUG_NEW
   #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

namespace
{
   const I_CHAR *CLASSNAME             = I_( "FundInfoDlg" );
   const I_CHAR *LV_FUNDLIST           = I_( "List Funds" );

   const I_CHAR *MODUSER               = I_( "ModUser" );
   const I_CHAR *MODDATE               = I_( "ModDate" );
   const I_CHAR *PROCESSUSER           = I_( "Username" );
   const I_CHAR *PROCESSDATE           = I_( "ProcessDate" );

   const I_CHAR *FUND_CODE             = I_( "FundCode" );
   const I_CHAR *FUND_NUMBER           = I_( "FundNumber" );
   const I_CHAR *CLASS_CODE            = I_( "ClassCode" );
   const I_CHAR *FUND_WKN              = I_( "FundWKN" );
   const I_CHAR *FUND_ISIN             = I_( "FundISIN" );
   const I_CHAR * ZERO				   = I_( "0.00000" );
   const I_CHAR *FUND_CUSIP            = I_( "CUSIP" );
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId PriceProcAtFndGrp;
   extern CLASS_IMPORT const BFTextFieldId UFactorCodes;
   extern CLASS_IMPORT const BFIntegerFieldId DivDates;
   extern CLASS_IMPORT const BFTextFieldId ZeroDistributionAppl;
   extern CLASS_IMPORT const BFBigDecimalFieldId GAV;
   extern CLASS_IMPORT const BFNumericFieldId AltFndIdntfr;
   extern CLASS_IMPORT const BFTextFieldId HasMultiplePrices;
}

namespace CND
{  // Conditions used
   extern const long GUI_ERR_UNKNOWN_EXCEPTION;
   extern const long GUI_ERR_DATA_NOT_FOUND;
}

namespace PRICE_ADDI
{
    extern CLASS_IMPORT I_CHAR * const UNIT_ID;
    extern CLASS_IMPORT I_CHAR * const TRADE_DATE;
    extern CLASS_IMPORT I_CHAR * const FUND_CODE; 
    extern CLASS_IMPORT I_CHAR * const CLASS_CODE;

    extern CLASS_IMPORT I_CHAR * const PRICE_CODE;
    extern CLASS_IMPORT I_CHAR * const UNIT_VALUE;
    extern CLASS_IMPORT I_CHAR * const CHG_FACTOR;

    extern CLASS_IMPORT I_CHAR * const PRICE_CODE2;
    extern CLASS_IMPORT I_CHAR * const UNIT_VALUE2;
    extern CLASS_IMPORT I_CHAR * const CHG_FACTOR2;

    extern CLASS_IMPORT I_CHAR * const PRICE_CODE3;
    extern CLASS_IMPORT I_CHAR * const UNIT_VALUE3;
    extern CLASS_IMPORT I_CHAR * const CHG_FACTOR3;

    extern CLASS_IMPORT I_CHAR * const PRICE_CODE4;
    extern CLASS_IMPORT I_CHAR * const UNIT_VALUE4;
    extern CLASS_IMPORT I_CHAR * const CHG_FACTOR4;

    extern CLASS_IMPORT I_CHAR * const PRICE_CODE5;
    extern CLASS_IMPORT I_CHAR * const UNIT_VALUE5;
    extern CLASS_IMPORT I_CHAR * const CHG_FACTOR5;

	extern CLASS_IMPORT I_CHAR * const PRICE_CODE6;
    extern CLASS_IMPORT I_CHAR * const UNIT_VALUE6;
    extern CLASS_IMPORT I_CHAR * const CHG_FACTOR6;

	extern CLASS_IMPORT I_CHAR * const PRICE_CODE7;
    extern CLASS_IMPORT I_CHAR * const UNIT_VALUE7;
    extern CLASS_IMPORT I_CHAR * const CHG_FACTOR7;

	extern CLASS_IMPORT I_CHAR * const PRICE_CODE8;
    extern CLASS_IMPORT I_CHAR * const UNIT_VALUE8;
    extern CLASS_IMPORT I_CHAR * const CHG_FACTOR8;

	extern CLASS_IMPORT I_CHAR * const PRICE_CODE9;
    extern CLASS_IMPORT I_CHAR * const UNIT_VALUE9;
    extern CLASS_IMPORT I_CHAR * const CHG_FACTOR9;

	extern CLASS_IMPORT I_CHAR * const PRICE_CODE10;
    extern CLASS_IMPORT I_CHAR * const UNIT_VALUE10;
    extern CLASS_IMPORT I_CHAR * const CHG_FACTOR10;

	extern CLASS_IMPORT I_CHAR * const PRICE_CODE11;
    extern CLASS_IMPORT I_CHAR * const UNIT_VALUE11;
    extern CLASS_IMPORT I_CHAR * const CHG_FACTOR11;

	extern CLASS_IMPORT I_CHAR * const PRICE_CODE12;
    extern CLASS_IMPORT I_CHAR * const UNIT_VALUE12;
    extern CLASS_IMPORT I_CHAR * const CHG_FACTOR12;

	extern CLASS_IMPORT I_CHAR * const PRICE_CODE13;
    extern CLASS_IMPORT I_CHAR * const UNIT_VALUE13;
    extern CLASS_IMPORT I_CHAR * const CHG_FACTOR13;


}

/* This will be reserved for later
class LVFundInfoData : public IFDSListCtrlRowDataBase
{
public:
   virtual ~LVFundInfoData() {}
   DString dstrValueAsAt_;
   DString dstrTransType_;
   DString dstrFundCode_;
   DString dstrFundWKN_;
   DString dstrFundISIN_;
   DString dstrUnitValue_;
   DString dstrOfferPrice_;
   DString dstrReinvestmentPrice_;
   DString dstrChange_;
   DString dstrCurrency_;
   DString dstrUnAllocIncome_;
   DString dstr1DAY_, dstr30DY_, dstr7DAY_, dstrDIVN_, dstrEK40_, dstrGNOE_, dstrGNOS_, dstrMF_, dstrOC_;


   virtual void update( BaseDlg* pDlg, IFDSListCtrl* pCtrl, const DString* pKey )
   {
      pDlg->getParent()->getField( pDlg, pCtrl->getContainerId(), ifds::ValueAsAt, dstrValueAsAt_ );
      pDlg->getParent()->getField( pDlg, pCtrl->getContainerId(), ifds::TransType, dstrTransType_ );
      pDlg->getParent()->getField( pDlg, pCtrl->getContainerId(), ifds::FundCode, dstrFundCode_ );
      dstrFundCode_.strip();
      pDlg->getParent()->getField( pDlg, pCtrl->getContainerId(), ifds::FundWKN, dstrFundWKN_ );
      pDlg->getParent()->getField( pDlg, pCtrl->getContainerId(), ifds::FundISIN, dstrFundISIN_ );
      pDlg->getParent()->getField( pDlg, pCtrl->getContainerId(), ifds::UnitValue, dstrUnitValue_ );
//      pDlg->getParent()->getField( pDlg, pCtrl->getContainerId(), ifds::OFFR, dstrOfferPrice_ );
//      pDlg->getParent()->getField( pDlg, pCtrl->getContainerId(), ifds::REIN, dstrReinvestmentPrice_ );
      pDlg->getParent()->getField( pDlg, pCtrl->getContainerId(), ifds::ChgFactor, dstrChange_ );
      pDlg->getParent()->getField( pDlg, pCtrl->getContainerId(), ifds::Currency, dstrCurrency_ );
      pDlg->getParent()->getField( pDlg, pCtrl->getContainerId(), ifds::UnAllocIncome, dstrUnAllocIncome_ );
// Factors
   }
};

class LVFundInfoAdapter : public IFDSListCtrlAdapter< LVFundInfoData >
{
public:
   // required overrides
   virtual int compare( IFDSListBase* pCtrl, int iSortColumn, bool bAscending, RowData* pData1, RowData* pData2, LPARAM lParam1, LPARAM lParam2 )
   {
      int result = 0;

      const BFFieldId* pFieldId = pCtrl->getColumnField( iSortColumn - 1 );
      if( 1 == iSortColumn ) {
         // Condition indicator column.  Sort on image index
         result = ( IFDSListBase::getColumnLVItem( lParam1, iSortColumn - 1)->iImage - 
                    IFDSListBase::getColumnLVItem( lParam2, iSortColumn - 1)->iImage );
      } else if( NULL == pFieldId ) {
         return( 0 );
      } else if( *pFieldId == ifds::ValueAsAt ) {
         result = i_strcmp( pData1->dstrValueAsAt_.c_str(), pData2->dstrValueAsAt_.c_str() );
      } else if( *pFieldId == ifds::TransType ) {
         result = i_strcmp( pData1->dstrTransType_.c_str(), pData2->dstrTransType_.c_str() );
      } else if( *pFieldId == ifds::FundCode ) {
         result = i_strcmp( pData1->dstrFundCode_.c_str(), pData2->dstrFundCode_.c_str() );
      } else if( *pFieldId == ifds::FundWKN ) {
         result = i_strcmp( pData1->dstrFundWKN_.c_str(), pData2->dstrFundWKN_.c_str() );
      } else if( *pFieldId == ifds::FundISIN ) {
         result = i_strcmp( pData1->dstrFundISIN_.c_str(), pData2->dstrFundISIN_.c_str() );
      } else if( *pFieldId == ifds::UnitValue ) {
         result = i_strcmp( pData1->dstrUnitValue_.c_str(), pData2->dstrUnitValue_.c_str() );
      } else if( *pFieldId == ifds::ChgFactor ) {
         result = i_strcmp( pData1->dstrChange_.c_str(), pData2->dstrChange_.c_str() );
      } else if( *pFieldId == ifds::Currency ) {
         result = i_strcmp( pData1->dstrCurrency_.c_str(), pData2->dstrCurrency_.c_str() );
      } else if( *pFieldId == ifds::UnAllocIncome ) {
         result = i_strcmp( pData1->dstrUnAllocIncome_.c_str(), pData2->dstrUnAllocIncome_.c_str() );
      }

      return( bAscending ? result : -result );
   }

   virtual LRESULT onGetDispInfo( IFDSListCtrl* pCtrl, RowData* pData, LV_DISPINFO* pDispInfo )
   {
      if( pDispInfo->item.mask & LVIF_TEXT )
      {
         const BFFieldId* pFieldId = pCtrl->getColumnField( pDispInfo->item.iSubItem );

         if( NULL == pFieldId ) {
            pDispInfo->item.pszText = I_( "" );
         } else if( *pFieldId == ifds::ValueAsAt ) {
            pDispInfo->item.pszText = (I_CHAR*)pData->dstrValueAsAt_.c_str();
         } else if( *pFieldId == ifds::TransType ) {
            pDispInfo->item.pszText = (I_CHAR*)pData->dstrTransType_.c_str();
         } else if( *pFieldId == ifds::FundCode ) {
            pDispInfo->item.pszText = (I_CHAR*)pData->dstrFundCode_.c_str();
         } else if( *pFieldId == ifds::FundWKN ) {
            pDispInfo->item.pszText = (I_CHAR*)pData->dstrFundWKN_.c_str();
         } else if( *pFieldId == ifds::FundISIN ) {
            pDispInfo->item.pszText = (I_CHAR*)pData->dstrFundISIN_.c_str();
         } else if( *pFieldId == ifds::UnitValue ) {
            pDispInfo->item.pszText = (I_CHAR*)pData->dstrUnitValue_.c_str();
         } else if( *pFieldId == ifds::ChgFactor ) {
            pDispInfo->item.pszText = (I_CHAR*)pData->dstrChange_.c_str();
         } else if( *pFieldId == ifds::Currency ) {
            pDispInfo->item.pszText = (I_CHAR*)pData->dstrCurrency_.c_str();
         } else if( *pFieldId == ifds::UnAllocIncome ) {
            pDispInfo->item.pszText = (I_CHAR*)pData->dstrUnAllocIncome_.c_str();
         }
         return( 1 );
      }
      return( 0 );
   }
};
*/

//*****************************************************************************
// Public methods
//*****************************************************************************
FundInfoDlg::FundInfoDlg( CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: BaseMainDlg( FundInfoDlg::IDD, pParent, pGIC, pGIParent, rCommand, CLASSNAME ),
m_bAllFundsChecked( false ),
m_bMultiDatesChecked( false )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   //{{AFX_DATA_INIT(FundInfoDlg)
   //}}AFX_DATA_INIT
   //m_rbFixed = 1;
}

//*****************************************************************************
void FundInfoDlg::DoDataExchange( CDataExchange* pDX )
{
   BaseMainDlg::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(FundInfoDlg)
   //}}AFX_DATA_MAP
}

//*****************************************************************************
SEVERITY FundInfoDlg::doInit()
{
   TRACE_METHOD( CLASSNAME, DOINIT );
   return(NO_CONDITION);
}

//*****************************************************************************
BEGIN_MESSAGE_MAP(FundInfoDlg, BaseMainDlg)
//{{AFX_MSG_MAP(FundInfoDlg)
ON_BN_CLICKED( IDC_BTN_MORE, OnBtnMore)
ON_BN_CLICKED( IDC_BTN_SEARCH, OnBtnSearch)
ON_BN_CLICKED( IDC_BTN_ADMIN_DATES, OnBtnAdminDates)
ON_BN_CLICKED( IDC_BTN_MGMT_DETAILS, OnBtnMgmtDetails)
ON_BN_CLICKED( IDC_BTN_UNIT_VAL, OnBtnUnitVal)
ON_BN_CLICKED( IDC_BTN_FACTORS, OnBtnFactors)
ON_BN_CLICKED( IDC_BTN_VALUATION_DETAILS, OnBtnValuationDetails)
ON_BN_CLICKED( IDC_BTN_PRICE_ADDITIONAL, OnBtnPriceAdditional)
ON_BN_CLICKED( IDC_CHK_ALLFUNDS, OnChkAllFunds)
ON_BN_CLICKED( IDC_CB_MULTI_DATES, OnChkMultiDates)

ON_MESSAGE( UM_OPENFUNDCLASSLISTDLG, OpenFundClassListDlg )

//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//*****************************************************************************
// Message handlers
//*****************************************************************************
BOOL FundInfoDlg::OnInitDialog() 
{
   TRACE_METHOD( CLASSNAME, ONINITDIALOG );
   BaseMainDlg::OnInitDialog();
   return(TRUE);   // return TRUE unless you set the focus to a control
   // EXCEPTION: OCX Property Pages should return FALSE
}

//******************************************************************************
void FundInfoDlg::OnPostInitDialog()
{
   TRACE_METHOD( CLASSNAME, ONPOSTINITDIALOG );
   CWaitCursor wait;

   // Get UFactorCodes
   getParent()->getField( this, IFASTBP_PROC::FI_PROC_GEN_LIST, ifds::UFactorCodes, m_dstrUFactorCodes );
   m_dstrUFactorCodes.upperCase();
   // Build map
   int iPos, iIndex = 0;
   DString dstrCode, dstrList = m_dstrUFactorCodes;
   do 
   {
      iPos = dstrList.find(  I_CHAR(',') );  // index into string
      if( iPos != -1 ) 
      {        
         dstrCode = dstrList.substr(0, iPos);  // get code
         dstrList = dstrList.substr(iPos + 1);   // advance list
      }
      else
      {
         dstrCode = dstrList;
         dstrList = NULL_STRING;
      }
      // Insert into Map here
      ++iIndex;
      m_mapFactorCodes.insert( MAPFACTORCODES::value_type( dstrCode, iIndex ) );
   } while( dstrList.length() );

   AddListControl(CLASSNAME, IDC_LV_FUNDS, I_("FUNDS"), ifds::FundInfoHeading, IFASTBP_PROC::FI_FUND_INFO_LIST, 0, true, LISTFLAG_NOT_AUTO_ADD );
   
/* Reserved for later
   IFDSListCtrl* pCtrl = 
      new IFDSAdaptedListCtrl< LVFundInfoAdapter >
         ( this, CLASSNAME, IDC_LV_FUNDS, 0, LISTFLAG_NOT_UPDATABLE, true, true );
   AddIFDSListControl( pCtrl, 
                       LV_FUNDLIST,
                       IFASTBP_PROC::FI_FUND_INFO_LIST,
                       ifds::FundInfoHeading );
*/
   // Date
   AddControl( CTRL_DATE, IDC_DTP_HIST_DATE, IFASTBP_PROC::FI_PROC_GEN_LIST, ifds::ToDate, CTRLFLAG_GUI_FIELD, 0 );

   // Check boxes
   AddControl( CTRL_CHECKBOX, IDC_CHK_ALLFUNDS, CTRLFLAG_NOT_UPDATABLE | CTRLFLAG_GUI_FIELD );
   AddControl( CTRL_CHECKBOX, IDC_CB_MULTI_DATES, CTRLFLAG_NOT_UPDATABLE | CTRLFLAG_GUI_FIELD );

   // Edits
   AddControl( CTRL_EDIT, IDC_EDT_FUND, IFASTBP_PROC::FI_PROC_GEN_LIST, ifds::FundCode, CTRLFLAG_GUI_FIELD );
   AddControl( CTRL_EDIT, IDC_EDT_CLASS, IFASTBP_PROC::FI_PROC_GEN_LIST, ifds::ClassCode, CTRLFLAG_GUI_FIELD );

   // Market-related display
   DString dstrAltFndIdntfr;
   getParent ()->getField (this, ifds::AltFndIdntfr, dstrAltFndIdntfr, false);
   int iCmdShow = DSTCommonFunctions::getMarket() == MARKET_IDS::LUXEMBOURG ? SW_SHOW : SW_HIDE;
   if( dstrAltFndIdntfr == I_("2") )
   {
		GetDlgItem( IDC_STC_CUSIPNUM )->ShowWindow( iCmdShow );
		GetDlgItem( IDC_EDT_CUSIPNUM )->ShowWindow( iCmdShow );
   }
   else if( dstrAltFndIdntfr == I_("0") )
   {
		GetDlgItem( IDC_TXT_WKN )->ShowWindow( iCmdShow );
		GetDlgItem( IDC_EDT_WKN )->ShowWindow( iCmdShow );
   }
   GetDlgItem( IDC_TXT_ISIN )->ShowWindow( iCmdShow );
   GetDlgItem( IDC_EDT_ISIN )->ShowWindow( iCmdShow );

   if( DSTCommonFunctions::getMarket() == MARKET_IDS::LUXEMBOURG )
   {
      AddControl( CTRL_EDIT, IDC_EDT_WKN, IFASTBP_PROC::FI_PROC_GEN_LIST, ifds::FundWKN, CTRLFLAG_GUI_FIELD );
      AddControl( CTRL_EDIT, IDC_EDT_ISIN, IFASTBP_PROC::FI_PROC_GEN_LIST, ifds::FundISIN, CTRLFLAG_GUI_FIELD );
	  AddControl( CTRL_EDIT, IDC_EDT_CUSIPNUM, IFASTBP_PROC::FI_PROC_GEN_LIST, ifds::CUSIP, CTRLFLAG_GUI_FIELD );
   }

   // Details
   AddControl( CTRL_STATIC, IDC_TXT_FND_LNG_NAME, IFASTBP_PROC::FI_FUND_MASTER_LIST, ifds::ElongName1, 0, IDC_LV_FUNDS );
   AddControl( CTRL_STATIC, IDC_TXT_INCEP_DATE, IFASTBP_PROC::FI_FUND_MASTER_LIST, ifds::EffectiveDate, 0, IDC_LV_FUNDS );
   AddControl( CTRL_STATIC, IDC_TXT_CUSIP, IFASTBP_PROC::FI_FUND_INFO_LIST, ifds::CusipNum, 0, IDC_LV_FUNDS );   
   AddControl( CTRL_STATIC, IDC_TXT_RECORD_DATE, IFASTBP_PROC::FI_FUND_INFO_LIST, ifds::RecordDate, 0, IDC_LV_FUNDS );
   AddControl( CTRL_STATIC, IDC_TXT_EX_DATE, IFASTBP_PROC::FI_FUND_INFO_LIST, ifds::ExDate, 0, IDC_LV_FUNDS );
   AddControl( CTRL_STATIC, IDC_TXT_PAY_DATE, IFASTBP_PROC::FI_FUND_INFO_LIST, ifds::PayDate, 0, IDC_LV_FUNDS );
   AddControl( CTRL_STATIC, IDC_TXT_REINV_DATE, IFASTBP_PROC::FI_FUND_INFO_LIST, ifds::ReInvDate, 0, IDC_LV_FUNDS );
   AddControl( CTRL_STATIC, IDC_TXT_DST_TYPE, IFASTBP_PROC::FI_FUND_INFO_LIST, ifds::DistributionType, 0, IDC_LV_FUNDS );
   AddControl( CTRL_STATIC, IDC_TXT_ZERO_DST, IFASTBP_PROC::FI_FUND_INFO_LIST,ifds::ZeroDistributionAppl,0,IDC_LV_FUNDS );
   AddControl( CTRL_STATIC, IDC_TXT_GAV, IFASTBP_PROC::FI_FUND_INFO_LIST, ifds::GAV, 0, IDC_LV_FUNDS );
   DString strDivDates;
   dynamic_cast<DSTCWorkSession *>(getBFWorkSession())->getOption( ifds::DivDates, 
                                                            strDivDates, getDataGroupId(), false ) ;
   iCmdShow = strDivDates.strip() == I_("1");
   GetDlgItem( IDC_TXT_EX_DATE )->ShowWindow( iCmdShow );
   GetDlgItem( IDC_LBL_EX_DATE )->ShowWindow( iCmdShow );
   GetDlgItem( IDC_TXT_PAY_DATE )->ShowWindow( iCmdShow );
   GetDlgItem( IDC_LBL_PAY_DATE )->ShowWindow( iCmdShow );
   GetDlgItem( IDC_TXT_REINV_DATE )->ShowWindow( iCmdShow );
   GetDlgItem( IDC_LBL_REINV_DATE )->ShowWindow( iCmdShow );

   ConnectControlsToData();
   LoadControls();   

   LoadListControl( IDC_LV_FUNDS );
   if( DSTCommonFunctions::getMarket() == MARKET_IDS::LUXEMBOURG )
   {
      enableValuationDetailsButton();
   }
}

//******************************************************************************

void FundInfoDlg::OnBtnMore() 
{
   TRACE_METHOD( CLASSNAME, I_("OnBtnMore") );

   CWaitCursor wait;

   const DString *crtKey = &getParent()->getCurrentListItemKey( this, IFASTBP_PROC::FI_FUND_INFO_LIST );

   if( getParent()->performSearch( this, IFASTBP_PROC::FI_FUND_INFO_LIST, SEARCH_NEXT_BLOCK ) <= WARNING )
   {
      LoadListControl( IDC_LV_FUNDS );   
      if( *crtKey != NULL_STRING )
      {
         GetList( IDC_LV_FUNDS )->SetSelection( crtKey );
      }
   }
   GetDlgItem( IDC_BTN_MORE )->EnableWindow( getParent()->doMoreRecordsExist( this, BF::AllContainerIds ) );
}

//******************************************************************************

void FundInfoDlg::OnBtnSearch() 
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnBtnSearch" ) );

   SetMessageStatusBar( TXT_SEARCH_FOR_FUND_VALUES );
   CWaitCursor wait;
   DString dstrToDate, dstrFromDate, dstrPrevDatePressed, dstrNextDatePressed;

   if( m_bMultiDatesChecked )
   {
      dstrFromDate = I_( "01011900" ); // ToDate already exists
      dstrPrevDatePressed = I_( "N" );
      dstrNextDatePressed = I_( "N" );
   }
   else
   {
      getParent()->getField(this, IFASTBP_PROC::FI_PROC_GEN_LIST, ifds::ToDate, dstrFromDate );
      dstrPrevDatePressed = I_( "Y" );
      dstrNextDatePressed = I_( "N" );
   }

   // Fund should already be defined.
   getParent()->setField(this, IFASTBP_PROC::FI_PROC_GEN_LIST, ifds::FromDate, dstrFromDate );
   getParent()->setField(this, IFASTBP_PROC::FI_PROC_GEN_LIST, ifds::PrevDatePressed, dstrPrevDatePressed );
   getParent()->setField(this, IFASTBP_PROC::FI_PROC_GEN_LIST, ifds::NextDatePressed, dstrNextDatePressed );

   if (getParent()->performSearch( this, BF::AllContainerIds, SEARCH_START ) > WARNING)
   {
      ConditionMessageBox (MYFRAME(), GETCURRENTHIGHESTSEVERITY());
   }
   else
   {
      GetDlgItem( IDC_BTN_MORE )->EnableWindow( getParent()->doMoreRecordsExist( this, IFASTBP_PROC::FI_FUND_INFO_LIST ) );
   }
   LoadListControl( IDC_LV_FUNDS );
   SetMessageStatusBar (NULL_STRING);
   int iNumListItems = GetList( IDC_LV_FUNDS )->GetItemCount ();
   GetDlgItem (IDC_BTN_FACTORS)->EnableWindow( iNumListItems > 0 );
   GetDlgItem (IDC_BTN_UNIT_VAL)->EnableWindow( iNumListItems > 0 );
   GetDlgItem (IDC_BTN_ADMIN_DATES)->EnableWindow( iNumListItems > 0 );
   setUpdateFlag( false );      // Clears Update for Dialog
}

//******************************************************************************

//******************************************************************************
bool FundInfoDlg::doRefresh( GenericInterface * rpGICaller,const I_CHAR * szOriginalCommand)
{  
   ShowWindow( SW_RESTORE );
   return(true);
}

//******************************************************************************
void FundInfoDlg::OnBtnAdminDates() 
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_(" OnBtnAdminDates() " ) );

   ShowAdminDates( IFASTBP_PROC::FI_FUND_INFO_LIST );
}

//******************************************************************************

void FundInfoDlg::OnBtnMgmtDetails() 
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_(" OnBtnAdminDates() " ) );
   CWaitCursor wait;

   try
   {
      bool bModal = true;   // Default to modeless
      E_COMMANDRETURN eRtn;

      SetMessageStatusBar( TXT_LOAD_MANAGEMENT_DETAILS );      
      setParameter(FUND_CODE_VALUE, m_FundCode );
      eRtn = invokeCommand( getParent(), CMD_BPROC_MGMTDETAILS, PROC_SUPPORT, false, NULL );
      SetMessageStatusBar( NULL_STRING );
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
}//******************************************************************************

void FundInfoDlg::OnBtnPriceAdditional() 
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnBtnPriceAdditional" ) );
   CWaitCursor wait;

   try
   {
      E_COMMANDRETURN eRtn;

      DString tradeDate, fundCode, classCode;
      DString priceCode, unitValue, chgFactor;
      DString priceCode2, unitValue2, chgFactor2;
      DString priceCode3, unitValue3, chgFactor3;
      DString priceCode4, unitValue4, chgFactor4;
      DString priceCode5, unitValue5, chgFactor5;
	  DString priceCode6, unitValue6, chgFactor6;
	  DString priceCode7, unitValue7, chgFactor7;
	  DString priceCode8, unitValue8, chgFactor8;
	  DString priceCode9, unitValue9, chgFactor9;
	  DString priceCode10, unitValue10, chgFactor10;
	  DString priceCode11, unitValue11, chgFactor11;
	  DString priceCode12, unitValue12, chgFactor12;
	  DString priceCode13, unitValue13, chgFactor13;

      getParent()->getField(this, IFASTBP_PROC::FI_FUND_INFO_LIST, ifds::ValueAsAt, tradeDate, false);
      getParent()->getField(this, IFASTBP_PROC::FI_FUND_INFO_LIST, ifds::rxFundCode, fundCode, false);
      getParent()->getField(this, IFASTBP_PROC::FI_FUND_INFO_LIST, ifds::rxClassCode, classCode, false);

      getParent()->getField(this, IFASTBP_PROC::FI_FUND_INFO_LIST, ifds::TransType, priceCode, false);
      getParent()->getField(this, IFASTBP_PROC::FI_FUND_INFO_LIST, ifds::UnitValue, unitValue, false);
      getParent()->getField(this, IFASTBP_PROC::FI_FUND_INFO_LIST, ifds::ChgFactor, chgFactor, false);

      getParent()->getField(this, IFASTBP_PROC::FI_FUND_INFO_LIST, ifds::PriceCode2, priceCode2, false);
      getParent()->getField(this, IFASTBP_PROC::FI_FUND_INFO_LIST, ifds::UnitValue2, unitValue2, false);
      getParent()->getField(this, IFASTBP_PROC::FI_FUND_INFO_LIST, ifds::ChgFactor2, chgFactor2, false);

      getParent()->getField(this, IFASTBP_PROC::FI_FUND_INFO_LIST, ifds::PriceCode3, priceCode3, false);
      getParent()->getField(this, IFASTBP_PROC::FI_FUND_INFO_LIST, ifds::UnitValue3, unitValue3, false);
      getParent()->getField(this, IFASTBP_PROC::FI_FUND_INFO_LIST, ifds::ChgFactor3, chgFactor3, false);

      getParent()->getField(this, IFASTBP_PROC::FI_FUND_INFO_LIST, ifds::PriceCode4, priceCode4, false);
      getParent()->getField(this, IFASTBP_PROC::FI_FUND_INFO_LIST, ifds::UnitValue4, unitValue4, false);
      getParent()->getField(this, IFASTBP_PROC::FI_FUND_INFO_LIST, ifds::ChgFactor4, chgFactor4, false);

      getParent()->getField(this, IFASTBP_PROC::FI_FUND_INFO_LIST, ifds::PriceCode5, priceCode5, false);
      getParent()->getField(this, IFASTBP_PROC::FI_FUND_INFO_LIST, ifds::UnitValue5, unitValue5, false);
      getParent()->getField(this, IFASTBP_PROC::FI_FUND_INFO_LIST, ifds::ChgFactor5, chgFactor5, false);

	  getParent()->getField(this, IFASTBP_PROC::FI_FUND_INFO_LIST, ifds::PriceCode6, priceCode6, false);
      getParent()->getField(this, IFASTBP_PROC::FI_FUND_INFO_LIST, ifds::UnitValue6, unitValue6, false);
      getParent()->getField(this, IFASTBP_PROC::FI_FUND_INFO_LIST, ifds::ChgFactor6, chgFactor6, false);

	  getParent()->getField(this, IFASTBP_PROC::FI_FUND_INFO_LIST, ifds::PriceCode7, priceCode7, false);
      getParent()->getField(this, IFASTBP_PROC::FI_FUND_INFO_LIST, ifds::UnitValue7, unitValue7, false);
      getParent()->getField(this, IFASTBP_PROC::FI_FUND_INFO_LIST, ifds::ChgFactor7, chgFactor7, false);

	  getParent()->getField(this, IFASTBP_PROC::FI_FUND_INFO_LIST, ifds::PriceCode8, priceCode8, false);
      getParent()->getField(this, IFASTBP_PROC::FI_FUND_INFO_LIST, ifds::UnitValue8, unitValue8, false);
      getParent()->getField(this, IFASTBP_PROC::FI_FUND_INFO_LIST, ifds::ChgFactor8, chgFactor8, false);

	  getParent()->getField(this, IFASTBP_PROC::FI_FUND_INFO_LIST, ifds::PriceCode9, priceCode9, false);
      getParent()->getField(this, IFASTBP_PROC::FI_FUND_INFO_LIST, ifds::UnitValue9, unitValue9, false);
      getParent()->getField(this, IFASTBP_PROC::FI_FUND_INFO_LIST, ifds::ChgFactor9, chgFactor9, false);

	  getParent()->getField(this, IFASTBP_PROC::FI_FUND_INFO_LIST, ifds::PriceCode10, priceCode10, false);
      getParent()->getField(this, IFASTBP_PROC::FI_FUND_INFO_LIST, ifds::UnitValue10, unitValue10, false);
      getParent()->getField(this, IFASTBP_PROC::FI_FUND_INFO_LIST, ifds::ChgFactor10, chgFactor10, false);

	  getParent()->getField(this, IFASTBP_PROC::FI_FUND_INFO_LIST, ifds::PriceCode11, priceCode11, false);
      getParent()->getField(this, IFASTBP_PROC::FI_FUND_INFO_LIST, ifds::UnitValue11, unitValue11, false);
      getParent()->getField(this, IFASTBP_PROC::FI_FUND_INFO_LIST, ifds::ChgFactor11, chgFactor11, false);

	  getParent()->getField(this, IFASTBP_PROC::FI_FUND_INFO_LIST, ifds::PriceCode12, priceCode12, false);
      getParent()->getField(this, IFASTBP_PROC::FI_FUND_INFO_LIST, ifds::UnitValue12, unitValue12, false);
      getParent()->getField(this, IFASTBP_PROC::FI_FUND_INFO_LIST, ifds::ChgFactor12, chgFactor12, false);

	  getParent()->getField(this, IFASTBP_PROC::FI_FUND_INFO_LIST, ifds::PriceCode13, priceCode13, false);
      getParent()->getField(this, IFASTBP_PROC::FI_FUND_INFO_LIST, ifds::UnitValue13, unitValue13, false);
      getParent()->getField(this, IFASTBP_PROC::FI_FUND_INFO_LIST, ifds::ChgFactor13, chgFactor13, false);



      setParameter(PRICE_ADDI::TRADE_DATE, tradeDate);
      setParameter(PRICE_ADDI::FUND_CODE, fundCode);
      setParameter(PRICE_ADDI::CLASS_CODE, classCode);

      setParameter(PRICE_ADDI::PRICE_CODE, priceCode);
      setParameter(PRICE_ADDI::UNIT_VALUE, unitValue);
      setParameter(PRICE_ADDI::CHG_FACTOR, chgFactor);

      setParameter(PRICE_ADDI::PRICE_CODE2, priceCode2);
      setParameter(PRICE_ADDI::UNIT_VALUE2, unitValue2);
      setParameter(PRICE_ADDI::CHG_FACTOR2, chgFactor2);

      setParameter(PRICE_ADDI::PRICE_CODE3, priceCode3);
      setParameter(PRICE_ADDI::UNIT_VALUE3, unitValue3);
      setParameter(PRICE_ADDI::CHG_FACTOR3, chgFactor3);

      setParameter(PRICE_ADDI::PRICE_CODE4, priceCode4);
      setParameter(PRICE_ADDI::UNIT_VALUE4, unitValue4);
      setParameter(PRICE_ADDI::CHG_FACTOR4, chgFactor4);

      setParameter(PRICE_ADDI::PRICE_CODE5, priceCode5);
      setParameter(PRICE_ADDI::UNIT_VALUE5, unitValue5);
      setParameter(PRICE_ADDI::CHG_FACTOR5, chgFactor5);

	  setParameter(PRICE_ADDI::PRICE_CODE6, priceCode6);
      setParameter(PRICE_ADDI::UNIT_VALUE6, unitValue6);
      setParameter(PRICE_ADDI::CHG_FACTOR6, chgFactor6);

	  setParameter(PRICE_ADDI::PRICE_CODE7, priceCode7);
      setParameter(PRICE_ADDI::UNIT_VALUE7, unitValue7);
      setParameter(PRICE_ADDI::CHG_FACTOR7, chgFactor7);

	  setParameter(PRICE_ADDI::PRICE_CODE8, priceCode8);
      setParameter(PRICE_ADDI::UNIT_VALUE8, unitValue8);
      setParameter(PRICE_ADDI::CHG_FACTOR8, chgFactor8);

	  setParameter(PRICE_ADDI::PRICE_CODE9, priceCode9);
      setParameter(PRICE_ADDI::UNIT_VALUE9, unitValue9);
      setParameter(PRICE_ADDI::CHG_FACTOR9, chgFactor9);

	  setParameter(PRICE_ADDI::PRICE_CODE10, priceCode10);
      setParameter(PRICE_ADDI::UNIT_VALUE10, unitValue10);
      setParameter(PRICE_ADDI::CHG_FACTOR10, chgFactor10);

	  setParameter(PRICE_ADDI::PRICE_CODE11, priceCode11);
      setParameter(PRICE_ADDI::UNIT_VALUE11, unitValue11);
      setParameter(PRICE_ADDI::CHG_FACTOR11, chgFactor11);

	  setParameter(PRICE_ADDI::PRICE_CODE12, priceCode12);
      setParameter(PRICE_ADDI::UNIT_VALUE12, unitValue12);
      setParameter(PRICE_ADDI::CHG_FACTOR12, chgFactor12);

	  setParameter(PRICE_ADDI::PRICE_CODE13, priceCode13);
      setParameter(PRICE_ADDI::UNIT_VALUE13, unitValue13);
      setParameter(PRICE_ADDI::CHG_FACTOR13, chgFactor13);

      eRtn = invokeCommand(getParent(), CMD_BPROC_PRICE_ADDITIONAL, PROC_SUPPORT, true, NULL);
     
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
}

//******************************************************************************

void FundInfoDlg::OnBtnUnitVal() 
{  
	executeCsiProcess( DcCsiProcesses::FUNDVALUE_TRADE_OR_FUND );
}

//******************************************************************************

void FundInfoDlg::OnBtnFactors() 
{
   MAKEFRAME2 (CND::IFASTGUI_CONDITION, CLASSNAME, I_ ("OnBtnFactors ()"));
   CWaitCursor wait;

   if (!getParent ()->send (this, I_("Factors")))
   {
      // Display error
      ConditionMessageBox (FRAMEBELOW (), GETHIGHESTSEVERITY ());
   }
}

//********************************************************************************

BOOL FundInfoDlg::PreTranslateMessage(MSG* pMsg) 
{
   if( pMsg->message == WM_KEYDOWN && ( int )( pMsg->wParam ) == VK_F4 && !IsSelectedCtrlUpdateable() )
   {
      return( TRUE );
   }

   if( pMsg->message == WM_KEYDOWN && ( int )( pMsg->wParam ) == VK_F4 )
   {
      if(   GetFocus() == GetDlgItem( IDC_EDT_FUND ) 
            || GetFocus() == GetDlgItem( IDC_EDT_FUND_NUMBER ) 
            || GetFocus() == GetDlgItem( IDC_EDT_CLASS ) 
            || GetFocus() == GetDlgItem( IDC_EDT_WKN )
            || GetFocus() == GetDlgItem( IDC_EDT_ISIN )
			|| GetFocus() == GetDlgItem( IDC_EDT_CUSIPNUM )
        )
      {
         PostMessage( UM_OPENFUNDCLASSLISTDLG );      
      }
      return( TRUE );
   }
   return( BaseMainDlg::PreTranslateMessage( pMsg ) );
}  

//********************************************************************************

LRESULT FundInfoDlg::OpenFundClassListDlg( WPARAM, LPARAM )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OpenFundClassListDlg" ) );

   DString dstrMarket = DSTCommonFunctions::getMarket();
   try
   {
      E_COMMANDRETURN eRtn = CMD_CANCEL;
      CWaitCursor wait;
      CString cstrValue;

      setParameter( FUND_CODE, NULL_STRING );
      setParameter( FUND_NUMBER, NULL_STRING );
      setParameter( CLASS_CODE, NULL_STRING );
      GetFocus()->GetWindowText( cstrValue );
      DString dstrValue( cstrValue );
      switch( GetFocus()->GetDlgCtrlID() )
      {
         case IDC_EDT_FUND:
            setParameter( FUND_CODE, dstrValue );
            break;    
         case IDC_EDT_FUND_NUMBER:
            setParameter( FUND_NUMBER, dstrValue );
            break;    
         case IDC_EDT_CLASS:
            setParameter( CLASS_CODE, dstrValue );
            break;    
      }

      eRtn = invokeCommand( getParent(), CMD_BPROC_FUNDCLASS, PROC_SUPPORT, true, NULL );
      switch( eRtn )
      {
         case CMD_OK:
         case CMD_MODELESS_INPROCESS:
            {
               DString dstrFundCode, dstrClassCode, dstrFundNumber, dstrFundISIN, dstrFundWKN, dstrFundCUSIP;
               getParameter( FUND_CODE, dstrFundCode );
               getParameter( CLASS_CODE, dstrClassCode );
               getParameter( FUND_NUMBER, dstrFundNumber );
               getParameter( FUND_ISIN, dstrFundISIN );
               getParameter( FUND_WKN, dstrFundWKN );
			   getParameter( FUND_CUSIP, dstrFundCUSIP);

               if( !dstrFundCode.empty() )
                  getParent()->setField( this, IFASTBP_PROC::FI_PROC_GEN_LIST, ifds::FundCode, dstrFundCode );
               if( !dstrClassCode.empty() )
                  getParent()->setField( this, IFASTBP_PROC::FI_PROC_GEN_LIST, ifds::ClassCode, dstrClassCode );
               if( !dstrFundISIN.empty() )
                  getParent()->setField( this, IFASTBP_PROC::FI_PROC_GEN_LIST, ifds::FundISIN, dstrFundISIN );
               if( !dstrFundWKN.empty() )
                  getParent()->setField( this, IFASTBP_PROC::FI_PROC_GEN_LIST, ifds::FundWKN, dstrFundWKN );
			   if( !dstrFundCUSIP.empty() )
				   getParent()->setField( this, IFASTBP_PROC::FI_PROC_GEN_LIST, ifds::CUSIP, dstrFundCUSIP );

               LoadControl( IDC_EDT_FUND );
               LoadControl( IDC_EDT_CLASS );
               if( DSTCommonFunctions::getMarket() == MARKET_IDS::LUXEMBOURG )
               {
                  LoadControl( IDC_EDT_ISIN );
                  LoadControl( IDC_EDT_WKN );
               }
               break;
            }
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

//********************************************************************************

bool FundInfoDlg::filterListColumn(const BFFieldId &idSubstitute, const DString& dstrTag)
{
   bool bReturn = true;

	if( ifds::FundInfoHeading == idSubstitute )
	{
		if( dstrTag == I_("1DAY") 
          || dstrTag == I_("30DY")
          || dstrTag == I_("7DAY")
          || dstrTag == I_("DIVN")
          || dstrTag == I_("EK40")
          || dstrTag == I_("GNOE")
          || dstrTag == I_("GNOS")
          || dstrTag == I_("MF")
          || dstrTag == I_("OC")
          || dstrTag == I_("OFFR")
          || dstrTag == I_("REIV")
          )
		{
         bReturn = ( m_dstrUFactorCodes.find( dstrTag ) != DString::npos );
		}
      else if( dstrTag == I_("FundLoadGrp") )
      {
         DString dstrPriceProcAtFndGrp;
         getParent()->getField( this, BF::NullContainerId, ifds::PriceProcAtFndGrp, dstrPriceProcAtFndGrp );
         bReturn = (dstrPriceProcAtFndGrp == I_("Y") );
      }
      else if( dstrTag == I_("rxClassCode") )
      {
         DString dstrPriceProcAtFndGrp;
         getParent()->getField( this, BF::NullContainerId, ifds::PriceProcAtFndGrp, dstrPriceProcAtFndGrp );
         bReturn = !(dstrPriceProcAtFndGrp == I_("Y") );
      }
	}	
	return bReturn;
}

//*****************************************************************************

bool FundInfoDlg::GetOverrideItemString( long lSubstituteId, const DString& dstrColumnKey, DString& dstrOut )
{
   if( lSubstituteId == ifds::FundInfoHeading.getId() )
   {
      if( m_dstrUFactorCodes.find( dstrColumnKey ) != DString::npos )
      {
         short nPos = 0;
         // Get the position for Factor Code (dstrColumnKey)
         MAPFACTORCODES_ITER iter = m_mapFactorCodes.begin();
         iter = m_mapFactorCodes.find( dstrColumnKey );
         if( iter != m_mapFactorCodes.end() )
         {
            nPos = (*iter).second;
         }
         // Based on the position, return FactorAmt#
         BFFieldId idField;
         switch( nPos ) // Brute force
         {
            case 1 : idField = ifds::FactorAmt1; break;
            case 2 : idField = ifds::FactorAmt2; break;
            case 3 : idField = ifds::FactorAmt3; break;
            case 4 : idField = ifds::FactorAmt4; break;
            case 5 : idField = ifds::FactorAmt5; break;
         }
         if( ifds::NullFieldId == idField )
         {
            dstrOut = NULL_STRING;
         }
         else
         {
            getParent()->getField( this, IFASTBP_PROC::FI_FUND_INFO_LIST, idField, dstrOut );
         }
         return( true );
      }
      else if( dstrColumnKey == I_("NUMBER") )
      {
         getParent()->getField( this, IFASTBP_PROC::FI_PROC_GEN_LIST, ifds::Baycom, dstrOut );
         return( true );
      }
   }
   return( false );
}

//*****************************************************************************

bool FundInfoDlg::GetDataForControl(
                                    UINT controlID,
                                    DString &dstrValue,
                                    bool bFormatted,
                                    int index
                                    ) const
{
   bool bRtn = false;

   switch( controlID )
   {
      case IDC_CHK_ALLFUNDS:
      case IDC_CB_MULTI_DATES:
         bRtn = true;
         break;
      case IDC_EDT_FUND:
         getParent()->getField( this, IFASTBP_PROC::FI_PROC_GEN_LIST, ifds::FundCode, dstrValue );
         bRtn = true;
         break;
      case IDC_EDT_WKN:
         getParent()->getField( this, IFASTBP_PROC::FI_PROC_GEN_LIST, ifds::FundWKN, dstrValue );
         bRtn = true;
         break;
      case IDC_EDT_ISIN:
         getParent()->getField( this, IFASTBP_PROC::FI_PROC_GEN_LIST, ifds::FundISIN, dstrValue );
         bRtn = true;
         break;
      case IDC_EDT_CLASS:
         getParent()->getField( this, IFASTBP_PROC::FI_PROC_GEN_LIST, ifds::ClassCode, dstrValue );
         bRtn = true;
         break;
      case IDC_DTP_HIST_DATE:
         getParent()->getField( this, IFASTBP_PROC::FI_PROC_GEN_LIST, ifds::ToDate, dstrValue );
         bRtn = true;
         break;
	  case IDC_EDT_CUSIPNUM:
		  getParent()->getField( this, IFASTBP_PROC::FI_PROC_GEN_LIST, ifds::CUSIP, dstrValue );
		  bRtn = true;
		  break;
   }
   return(bRtn);
}

//*****************************************************************************

bool FundInfoDlg::SetDataFromControl(
                                     UINT controlID,
                                     const DString &dstrValue,
                                     bool bFormatted,
                                     SEVERITY &sevRtn,
                                     int index
                                     )
{
   bool bRtn = false;

   switch( controlID )
   {
      case IDC_CHK_ALLFUNDS:
      case IDC_CB_MULTI_DATES:
         bRtn = true;
         break;
      case IDC_EDT_FUND:
         getParent()->setField( this, IFASTBP_PROC::FI_PROC_GEN_LIST, ifds::FundCode, dstrValue );
         bRtn = true;
         break;
      case IDC_EDT_WKN:
         getParent()->setField( this, IFASTBP_PROC::FI_PROC_GEN_LIST, ifds::FundWKN, dstrValue );
         bRtn = true;
         break;
      case IDC_EDT_ISIN:
         getParent()->setField( this, IFASTBP_PROC::FI_PROC_GEN_LIST, ifds::FundISIN, dstrValue );
         bRtn = true;
         break;
      case IDC_EDT_CLASS:
         getParent()->setField( this, IFASTBP_PROC::FI_PROC_GEN_LIST, ifds::ClassCode, dstrValue );
         bRtn = true;
         break;
      case IDC_DTP_HIST_DATE:
         getParent()->setField( this, IFASTBP_PROC::FI_PROC_GEN_LIST, ifds::ToDate, dstrValue );
         bRtn = true;
         break;
	  case IDC_EDT_CUSIPNUM:
		 getParent()->setField( this, IFASTBP_PROC::FI_PROC_GEN_LIST, ifds::CUSIP, dstrValue );
         bRtn = true;
         break;
   }
   return(bRtn);
}

//*****************************************************************************

void FundInfoDlg::ControlUpdated( UINT controlID, const DString &strValue )
{
   setUpdateFlag( false );      // Clears Update for Dialog
}

//*****************************************************************************

void FundInfoDlg::OnChkAllFunds() 
{
   DSTButton *cbAllFunds = dynamic_cast<DSTButton*>( GetControl( IDC_CHK_ALLFUNDS ) );
   m_bAllFundsChecked = ( cbAllFunds->GetCheck() == 1 );

   if( m_bAllFundsChecked )
   {
      getParent()->setField( this, IFASTBP_PROC::FI_PROC_GEN_LIST, ifds::FundCode, NULL_STRING );
      getParent()->setField( this, IFASTBP_PROC::FI_PROC_GEN_LIST, ifds::ClassCode, NULL_STRING );
      getParent()->setField( this, IFASTBP_PROC::FI_PROC_GEN_LIST, ifds::FundISIN, NULL_STRING );
      getParent()->setField( this, IFASTBP_PROC::FI_PROC_GEN_LIST, ifds::FundWKN, NULL_STRING );
      // Clear control text
      LoadControl( IDC_EDT_FUND );
      LoadControl( IDC_EDT_CLASS );
      if( DSTCommonFunctions::getMarket() == MARKET_IDS::LUXEMBOURG )
      {
         LoadControl( IDC_EDT_ISIN );
         LoadControl( IDC_EDT_WKN );
		 LoadControl( IDC_EDT_CUSIPNUM );
      }
   }

   // Refresh display
   GetDlgItem( IDC_STC_FUND )->ShowWindow( m_bAllFundsChecked ? SW_HIDE : SW_SHOW );
   GetDlgItem( IDC_EDT_FUND )->ShowWindow( m_bAllFundsChecked ? SW_HIDE : SW_SHOW );
   GetDlgItem( IDC_STC_FUND_CLASS )->ShowWindow( m_bAllFundsChecked ? SW_HIDE : SW_SHOW );
   GetDlgItem( IDC_EDT_CLASS )->ShowWindow( m_bAllFundsChecked ? SW_HIDE : SW_SHOW );
   // Check Market
   if( DSTCommonFunctions::getMarket() == MARKET_IDS::LUXEMBOURG )
   {
	   DString dstrAltFndIdntfr;
	   getParent ()->getField (this, ifds::AltFndIdntfr, dstrAltFndIdntfr, false);
	   if(dstrAltFndIdntfr == I_("0"))
	   {
			GetDlgItem( IDC_TXT_WKN )->ShowWindow( m_bAllFundsChecked ? SW_HIDE : SW_SHOW );
			GetDlgItem( IDC_EDT_WKN )->ShowWindow( m_bAllFundsChecked ? SW_HIDE : SW_SHOW );
	   }
	   else if (dstrAltFndIdntfr == I_("2"))
	   {
			GetDlgItem( IDC_STC_CUSIPNUM )->ShowWindow( m_bAllFundsChecked ? SW_HIDE : SW_SHOW );
			GetDlgItem( IDC_EDT_CUSIPNUM )->ShowWindow( m_bAllFundsChecked ? SW_HIDE : SW_SHOW );
	   }
      GetDlgItem( IDC_TXT_ISIN )->ShowWindow( m_bAllFundsChecked ? SW_HIDE : SW_SHOW );
      GetDlgItem( IDC_EDT_ISIN )->ShowWindow( m_bAllFundsChecked ? SW_HIDE : SW_SHOW );
   }
}

//*****************************************************************************

void FundInfoDlg::OnChkMultiDates() 
{
   DSTButton *cbMultiDates = dynamic_cast<DSTButton*>( GetControl( IDC_CB_MULTI_DATES ) );
   m_bMultiDatesChecked = ( cbMultiDates->GetCheck() == 1 );
}
//******************************************************************************************
void FundInfoDlg::DoListItemChanged ( UINT listControlID, 
                                           const DString &strKey, 
                                           bool bIsNewItem, 
                                           bool bIsDummyItem)
{
   switch (listControlID)
   {
      case IDC_LV_FUNDS:
      {
         if( DSTCommonFunctions::getMarket() == MARKET_IDS::LUXEMBOURG )
         {
   	      enableValuationDetailsButton();
         }
		 DString dstrGAV  = ZERO ; 
		 getParent()->getField( this, IFASTBP_PROC::FI_FUND_INFO_LIST, ifds::GAV, dstrGAV );
		 GetDlgItem( IDC_TXT_GAV )->ShowWindow( DSTCommonFunctions::convertToDouble( dstrGAV )> 
												DSTCommonFunctions::convertToDouble( ZERO ));

         DString hasMultiplePrices;
         getParent()->getField(this, IFASTBP_PROC::FI_FUND_INFO_LIST, ifds::HasMultiplePrices, hasMultiplePrices, false);
         GetDlgItem(IDC_BTN_PRICE_ADDITIONAL)->EnableWindow(hasMultiplePrices == I_("Y"));
         break;
      }
      default:
         break;
   }
}
//****************************************************************************
void FundInfoDlg::enableValuationDetailsButton()
{
	MAKEFRAME2 (CND::IFASTGUI_CONDITION, CLASSNAME, I_ ("enableValuationDetailsButton()"));

	DString dstrFundCode,dstrClassCode;		

	getParent()->getField (this, IFASTBP_PROC::FI_FUND_INFO_LIST, ifds::rxFundCode,  dstrFundCode, false);
	getParent()->getField (this, IFASTBP_PROC::FI_FUND_INFO_LIST, ifds::rxClassCode,  dstrClassCode, false);

	DSTCWorkSession *dstWorkSession = dynamic_cast<DSTCWorkSession *>(getParent()->getBFWorkSession());
	bool bEnable = dstWorkSession->isPerfFeeFund(dstrFundCode,dstrClassCode,getParent()->getDataGroupId());

	GetDlgItem (IDC_BTN_VALUATION_DETAILS)->EnableWindow(bEnable);
}
//******************************************************************************

void FundInfoDlg::OnBtnValuationDetails() 
{
	MAKEFRAME2 (CND::IFASTGUI_CONDITION, CLASSNAME, I_ ("OnBtnValuationDetails ()"));
	E_COMMANDRETURN eRtn = CMD_OK;
	DString dstrFundCode,dstrClassCode,dstrValueAsAt,dstrTransId,dstrLotType,dstrIWTEnable;

	getParent()->getField( this, IFASTBP_PROC::FI_FUND_INFO_LIST, ifds::rxFundCode, dstrFundCode );
	dstrFundCode.stripAll();

	getParent()->getField( this, IFASTBP_PROC::FI_FUND_INFO_LIST, ifds::rxClassCode, dstrClassCode );
	dstrClassCode.stripAll();

	getParent()->getField( this, IFASTBP_PROC::FI_FUND_INFO_LIST, ifds::ValueAsAt, dstrValueAsAt );
	dstrValueAsAt.stripAll();

	DString DisplayMaskFormat = GetConfigValueAsString (I_( "LocaleFormats" ), I_( "DisplayMasks" ), I_( "enUS-D" ));
	DisplayMaskFormat.stripAll();
	DisplayMaskFormat = DisplayMaskFormat.lowerCase ();

	DisplayMaskFormat = DisplayMaskFormat.stripAll(I_CHAR('/')); //Removing separator if any
	DisplayMaskFormat = DisplayMaskFormat.stripAll(I_CHAR('-')); //Removing separator if any
	
	DString ValueAsAt;
	if (DisplayMaskFormat == I_("ddmmyyyy"))
	{
		dstrValueAsAt = dstrValueAsAt.stripAll(I_CHAR('/')); //Removing separator if any
		dstrValueAsAt = dstrValueAsAt.stripAll(I_CHAR('-')); //Removing separator if any

		ValueAsAt =  dstrValueAsAt.substr ( 2, 2 ); //month
		ValueAsAt += I_("/");
		ValueAsAt += dstrValueAsAt.substr ( 0, 2 ); //day
		ValueAsAt += I_("/");
		ValueAsAt += dstrValueAsAt.substr ( 4, 4 ); //year
	}
	else
	{
		ValueAsAt =  dstrValueAsAt;
	}

	DString urlParamsIDI;
	addIDITagValue (urlParamsIDI, I_("fund"), dstrFundCode);
	addIDITagValue (urlParamsIDI, I_("class"), dstrClassCode);
	addIDITagValue (urlParamsIDI, I_("screen"), I_("ClassSetup_ValuationBasic"));
	addIDITagValue (urlParamsIDI, I_("valnDate"), ValueAsAt);

	CString cstrValuDetlFund,cstrClass;
    cstrValuDetlFund.LoadString(TXT_VALUATION_DTL_FUND);
    cstrClass.LoadString(TXT_VALUATION_DTL_CLASS);
    
	DString screenTitle = DString(cstrValuDetlFund) + dstrFundCode;
    screenTitle += DString(cstrClass) + dstrClassCode;
	
	setParameter (I_("UrlParams"), urlParamsIDI);
	setParameter (I_("from_screen"), I_("FundInfoDlg"));
	setParameter (I_("screen"), I_("ClassSetup_ValuationBasic"));
	setParameter (I_("BrowserTitle"), screenTitle );

	eRtn = invokeCommand (getParent(), CMD_BPROC_VALUATION_DETAILS_BROWSER, PROC_NO_TYPE, true, NULL);
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
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/FundInfoDlg.cpp-arc  $
 * 
 *    Rev 1.31   Aug 10 2012 20:39:04   wp040133
 * ESS_P01999461_FN01_ARROW_Distribution Enhancement
 * Adding the DistributionType for GUI display
 * 
 *    Rev 1.30   May 29 2012 17:40:08   if991250
 * IN# 2958567: Valuation Details available only for Lux
 * 
 *    Rev 1.29   May 14 2012 17:46:06   wp040027
 * PF - Adding separator in date to launch Valn detail screen
 * 
 *    Rev 1.28   Apr 26 2012 11:42:30   wp040027
 * IN2934256: PF- P0188394 XML Parsing Error on clicking Sharelot info
 * 
 *    Rev 1.27   Mar 09 2012 19:08:12   wp040132
 * Valuation Button to be enabled on the first Performance Fee fund/record. IN# 2875136 - Valuation button button in the fund info screen should be enabled since the first record is highlighted by default. But the valuation detail button is disable. User need to click Search 
 * 
 * 
 *    Rev 1.26   Mar 09 2012 13:59:20   wp040132
 * Changed the Url Parameters that are passed from desktop to browser screen. Parameters are changed as per Winnie's suggestion. IN #2877061 - On clicking the Valuation Detail button from the Fund Info screen, system throw Internet Script error.
 * 
 *    Rev 1.25   Jan 19 2012 11:11:24   wp040027
 * P0188394_Performance Fees - Added 'screen' and 'BrowswerTitle' to launch Valuation Details Screen
 * 
 *    Rev 1.24   Jan 18 2012 17:15:16   wp040027
 * P0188394_Performance Fees - Launching valuation dtl/Sharelot Screens
 * 
 *    Rev 1.23   Oct 20 2009 06:25:46   kitticha
 * REL97 IN#1814672 - the CUSIP values are missing
 * 
 *    Rev 1.22   Dec 06 2007 19:42:24   smithdav
 * PET1200 FN02 - Dividend Processing enhancement.
 * 
 *    Rev 1.21   Mar 20 2007 10:53:12   popescu
 * Incident# 847324 - issue with the Fund info screen.
 * 
 *    Rev 1.20   Sep 15 2005 15:13:08   popescu
 * Incident#403519 - added CLASSNAME as the fifth parameter to  BaseMainDlg constructor
 * 
 *    Rev 1.19   Oct 07 2004 15:18:46   HERNANDO
 * PTS10034608 - Corrected column display/mapping and defensive-coding - handle more than 5 factors.
 * 
 *    Rev 1.18   Sep 17 2004 13:39:06   popescu
 * PET1117 FN22 - revert fund factors dialog display to old logic
 * 
 *    Rev 1.17   Sep 09 2004 14:43:48   HERNANDO
 * PET1117 FN22 - Group Code, Class Code, and Fund Number added to list display.
 * 
 *    Rev 1.16   Sep 09 2004 11:51:50   HERNANDO
 * PET1117 FN22 - WKN & ISIN Enhancement.
 * 
 *    Rev 1.15   May 18 2004 11:13:12   VADEANUM
 * PTS 10028913 - Reflection to go directly to Unit Prices in iFast.
 * 
 *    Rev 1.14   Nov 20 2003 16:31:58   AGUILAAM
 * PET859_FN17: added factors screen - daily equalization.
 * 
 *    Rev 1.13   Apr 15 2003 12:22:28   sanchez
 * Sync up with version 1.11.1.0
 * 
 *    Rev 1.12   Mar 21 2003 18:37:00   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.11   Oct 09 2002 23:55:42   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.10   Aug 29 2002 12:57:22   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.9   22 May 2002 19:16:06   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.8   27 Mar 2002 20:01:10   PURDYECH
 * Process/WindowFactory overhaul
 * 
 *    Rev 1.7   Mar 21 2002 13:24:26   YINGBAOL
 * add group Logic
 * 
 *    Rev 1.6   Jan 28 2002 11:27:32   YINGBAOL
 * HLLAPI Change
 * 
 *    Rev 1.5   03 May 2001 14:07:36   SMITHDAV
 * Session management restructuring.
 * 
 *    Rev 1.4   Mar 30 2001 18:38:04   DINACORN
 * Used DSTCommonFunctions MARKET_IDS constants
 * 
 *    Rev 1.3   Sep 29 2000 13:29:20   YINGZ
 * change market from cfds - canada to canada
 * 
 *    Rev 1.2   Mar 20 2000 14:34:32   HSUCHIN
 * changed GetFundNumber to use the one defined in DSTCommon Functions
 * 
 *    Rev 1.1   Mar 13 2000 17:27:42   HSUCHIN
 * C2 sync up
 * 
 *    Rev 1.0   Feb 15 2000 11:01:16   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.29   Feb 02 2000 14:09:12   DT24433
 * removed ok/cancel, use ShowAdminDates
 * 
 *    Rev 1.28   Jan 17 2000 15:22:06   YINGBAOL
 * hllapi change sync
 * 
 *    Rev 1.27   Jan 05 2000 12:07:42   YINGZ
 * get rid of confirmation dlg
 * 
 *    Rev 1.26   Dec 22 1999 11:28:20   YINGBAOL
 * Hllapi Change sync.
 * 
 *    Rev 1.25   Dec 04 1999 15:18:12   BUZILA
 * fix
 * 
 *    Rev 1.24   Dec 03 1999 20:31:26   BUZILA
 * fix more
 * 
 *    Rev 1.23   Nov 30 1999 10:56:00   VASILEAD
 * replace previous version with 1.21
 * 
 *    Rev 1.21   Oct 05 1999 11:12:40   YINGZ
 * fix hour glass problem
 * 
 *    Rev 1.20   Oct 01 1999 14:57:34   YINGZ
 * put false when get transtype so no format will be applied
 * 
 *    Rev 1.19   Sep 28 1999 15:42:32   YINGZ
 * put wait in OnPostInitDialog
 * 
 *    Rev 1.18   Sep 24 1999 14:25:00   YINGZ
 * make it for c1
 * 
 *    Rev 1.17   Sep 24 1999 09:49:58   YINGBAOL
 * add market flag
 * 
 *    Rev 1.16   13 Sep 1999 13:52:56   HUANGSHA
 * Synchronize with M1's changes
 * 
 *    Rev 1.15   Aug 09 1999 17:10:32   BUZILA
 * fixed list IDs
 * 
 *    Rev 1.14   Aug 05 1999 14:19:08   DT24433
 * container changes and resolved name redundancy for fund code
 * 
 *    Rev 1.13   Aug 04 1999 16:09:10   BUZILA
 * field ChgFactor introduced
 * 
 *    Rev 1.12   Jul 30 1999 11:34:20   YINGZ
 * align
 * 
 *    Rev 1.11   Jul 29 1999 17:41:28   BUZILA
 * 1
 * 
 *    Rev 1.10   Jul 28 1999 17:20:46   BUZILA
 * Changed NAV labels
 * 
 *    Rev 1.9   Jul 20 1999 17:00:18   BUZILA
 * fixed DateTimePicker refresh problem
 * 
 *    Rev 1.8   Jul 20 1999 14:24:42   YINGZ
 * add hour glass
 * 
 *    Rev 1.7   Jul 20 1999 11:18:56   VASILEAD
 * New conditions update
 * 
 *    Rev 1.6   Jul 16 1999 10:53:20   BUZILA
 * 3
 * 
 *    Rev 1.5   Jul 16 1999 10:44:06   BUZILA
 * 2
 * 
 *    Rev 1.4   Jul 16 1999 10:23:16   BUZILA
 * 1
 * 
 *    Rev 1.3   Jul 15 1999 16:39:30   BUZILA
 * Fixing Mgmt Detail
 * 
 *    Rev 1.2   09 Jul 1999 14:22:46   BUZILA
 * 1
 * 
 *    Rev 1.1   Jul 08 1999 10:05:16   SMITHDAV
 * Modify revision history commaent format to old
 * style comment -- I can't seem to get new style comments to work.
 *
 */
