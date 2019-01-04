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
// ^FILE   : InventorySummaryDlg.cpp
// ^AUTHOR : Celia Zhang
// ^DATE   : Feb 10, 2004
//
// ^CLASS    : InventorySummaryDlg
// ^SUBCLASS : BaseMainDlg
//
// ^CLASS DESCRIPTION : 
//
//******************************************************************************

#include "stdafx.h"

#include "mfdstc.h"
#include <bfproc\AbstractProcess.hpp>
#include "InventorySummaryDlg.h"
#include <ifastcbo\DSTCommonFunction.hpp>
#include <ifastcbo\fundmasterlist.hpp>
#include <ifastcbo\mgmtco.hpp>
#include <uibase\DSTListCtrl.h>
#include <ifastcbo\DSTCWorkSession.hpp>
#include <uibase\DSTComboBox.h>
#include <uibase\dstbutton.h>
#include <ifastbp\InventorySummaryProcessIncludes.h>
#include <ifastbp\InvDetlDeductionProcessIncludes.h>
#include <ifastcbo\MFAccount.hpp>


extern CLASS_IMPORT const I_CHAR* CMD_GUI_INVENTORY_SUMMARY;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_TRANS_HISTORY;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_INVENTORY_DETAIL_DEDUCTION;

#include <bfproc\concretedialogcreator.hpp>
static ConcreteDialogCreator< InventorySummaryDlg > dlgCreator( CMD_GUI_INVENTORY_SUMMARY );

#ifdef _DEBUG
   #define new DEBUG_NEW
   #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

namespace
{
   const I_CHAR * const CLASSNAME                        = I_( "InventorySummaryDlg" );
   const I_CHAR * const LV_INVENTORY_SUMMARY_LIST        = I_( "InventorySummaryList" );
   const I_CHAR * const LV_INVENTORY_DETAILS_LIST        = I_( "InventoryDetailsList" );
   const I_CHAR * const ONBTNMOREDETAIL                  = I_( "OnBtnMoreDetail" );
   const I_CHAR * const YES                              = I_( "Y" );
   const I_CHAR * const NO                               = I_( "N" );
   const I_CHAR * const CODE_FUND_CATEGORY_LSIF          = I_( "L" );
   const I_CHAR * const ROLLOVER_QUALIFICATION_DATE      = I_( "RollQualDate" );
   const I_CHAR * const OMNIBUS						     = I_( "OM" );
   const I_CHAR * const APPLICABLE                       = I_( "01" );
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId rxFundCode;
   extern CLASS_IMPORT const BFTextFieldId rxClassCode;
   extern CLASS_IMPORT const BFTextFieldId InventorySummHeading;
   extern CLASS_IMPORT const BFTextFieldId InventoryDetailsHeading;
   extern CLASS_IMPORT const BFTextFieldId FundCategory;
   extern CLASS_IMPORT const BFTextFieldId SortBy;
   extern CLASS_IMPORT const BFIntegerFieldId SortByColumn;
   extern CLASS_IMPORT const BFTextFieldId SortOrder;
   extern CLASS_IMPORT const BFTextFieldId RDRAdvice;
   extern CLASS_IMPORT const BFTextFieldId G1G2TrackType;
   extern CLASS_IMPORT const BFTextFieldId AcctType;
   extern CLASS_IMPORT const BFTextFieldId InventorySummHeading;
   extern CLASS_IMPORT const BFTextFieldId SocialCode;
   extern CLASS_IMPORT const BFTextFieldId DisplayRolloverQualificationDate;
}

namespace CND
{  // Conditions used
   extern const long GUI_ERR_UNKNOWN_EXCEPTION;
}

namespace TRADETYPE // See:  ifastids/ifastradeids.cpp
{
   const I_CHAR * const MONEY_OUT_TXN = I_("PW,LR,RR,AF,AF91,MF,AW,TO,EO");
}
const UINT G1G2Controls[] = {
 IDC_TXT_TOTAL_G1BAL,
 IDC_TXT_TOTAL_G2BAL,
 IDC_STC_G1_BALANCE, 
 IDC_STC_G2_BALANCE,
};
static const int _numG1G2Controls = sizeof(G1G2Controls)/sizeof(UINT);
class LVInventorySummaryData : public IFDSListCtrlRowDataBase
{
public:
   virtual ~LVInventorySummaryData() {}

   DString m_dstrTransType, m_dstrPartnership, m_dstrOrigEffectiveDate;
   DString m_dstrMaturityDate, m_dstrRollQualDate;
   DString m_dstrOriginalTotalUnits, m_dstrUsedUnits, m_dstrUnits;
   DString m_dstrRate, m_dstrCommRate, m_dstrFromFund, m_dstrFromClass, m_dstrGroupOrigDate;

   virtual void update( BaseDlg* pDlg, IFDSListCtrl* pCtrl, const DString* pKey )
   {

      pDlg->getParent()->getField( pDlg, pCtrl->getContainerId(), ifds::TransType, m_dstrTransType );
      pDlg->getParent()->getField( pDlg, pCtrl->getContainerId(), ifds::PartnerShip, m_dstrPartnership );
      pDlg->getParent()->getField( pDlg, pCtrl->getContainerId(), ifds::OrigEffectiveDate, m_dstrOrigEffectiveDate );
      pDlg->getParent()->getField( pDlg, pCtrl->getContainerId(), ifds::MaturityDate, m_dstrMaturityDate );
      pDlg->getParent()->getField( pDlg, pCtrl->getContainerId(), ifds::RollQualDate, m_dstrRollQualDate );
      pDlg->getParent()->getField( pDlg, pCtrl->getContainerId(), ifds::OriginalTotalUnits, m_dstrOriginalTotalUnits );
      pDlg->getParent()->getField( pDlg, pCtrl->getContainerId(), ifds::UsedUnits, m_dstrUsedUnits );
      pDlg->getParent()->getField( pDlg, pCtrl->getContainerId(), ifds::Units, m_dstrUnits );
      pDlg->getParent()->getField( pDlg, pCtrl->getContainerId(), ifds::Rate, m_dstrRate );
      pDlg->getParent()->getField( pDlg, pCtrl->getContainerId(), ifds::CommRate, m_dstrCommRate );
      pDlg->getParent()->getField( pDlg, pCtrl->getContainerId(), ifds::FromFund, m_dstrFromFund );
      pDlg->getParent()->getField( pDlg, pCtrl->getContainerId(), ifds::FromClass, m_dstrFromClass );
	  pDlg->getParent()->getField( pDlg, pCtrl->getContainerId(), ifds::GroupOrigDate, m_dstrGroupOrigDate );
   }
};

class LVInventorySummaryAdapter : public IFDSListCtrlAdapter< LVInventorySummaryData >
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
      } else if( *pFieldId == ifds::TransType ) {
         result = i_strcmp( pData1->m_dstrTransType.c_str(), pData2->m_dstrTransType.c_str() );
      } else if( *pFieldId == ifds::PartnerShip ) {
         result = i_strcmp( pData1->m_dstrPartnership.c_str(), pData2->m_dstrPartnership.c_str() );
      } else if( *pFieldId == ifds::OrigEffectiveDate ) {
         int dater_order = DSTCommonFunctions::CompareDates (
               pData1->m_dstrOrigEffectiveDate.c_str(), 
               pData2->m_dstrOrigEffectiveDate.c_str(),
               BFDate::DF_DISPLAY);
         result = dater_order == DSTCommonFunctions::FIRST_EARLIER ? -1 : 
                  dater_order == DSTCommonFunctions::EQUAL ? 0 : 1;
//         result = i_strcmp( pData1->m_dstrOrigEffectiveDate.c_str(), pData2->m_dstrOrigEffectiveDate.c_str() );
      } else if( *pFieldId == ifds::MaturityDate ) {
         int dater_order = DSTCommonFunctions::CompareDates (
               pData1->m_dstrMaturityDate.c_str(), 
               pData2->m_dstrMaturityDate.c_str(),
               BFDate::DF_DISPLAY);
         result = dater_order == DSTCommonFunctions::FIRST_EARLIER ? -1 : 
                  dater_order == DSTCommonFunctions::EQUAL ? 0 : 1;
//         result = i_strcmp( pData1->m_dstrMaturityDate.c_str(), pData2->m_dstrMaturityDate.c_str() );
      } else if( *pFieldId == ifds::RollQualDate ) {
         int dater_order = DSTCommonFunctions::CompareDates (
               pData1->m_dstrRollQualDate.c_str(), 
               pData2->m_dstrRollQualDate.c_str(),
               BFDate::DF_DISPLAY);
         result = dater_order == DSTCommonFunctions::FIRST_EARLIER ? -1 : 
                  dater_order == DSTCommonFunctions::EQUAL ? 0 : 1;
      } else if( *pFieldId == ifds::OriginalTotalUnits ) {
         double otu1 = DSTCommonFunctions::convertToDouble ( pData1->m_dstrOriginalTotalUnits.c_str() );
         double otu2 = DSTCommonFunctions::convertToDouble ( pData2->m_dstrOriginalTotalUnits.c_str() );
         result = otu1 < otu2 ? -1 : otu1 > otu2 ? 1 : 0;
//         result = i_strcmp( pData1->m_dstrOriginalTotalUnits.c_str(), pData2->m_dstrOriginalTotalUnits.c_str() );
      } else if( *pFieldId == ifds::UsedUnits ) {
         double uu1 = DSTCommonFunctions::convertToDouble ( pData1->m_dstrUsedUnits.c_str() );
         double uu2 = DSTCommonFunctions::convertToDouble ( pData2->m_dstrUsedUnits.c_str() );

         result = uu1 < uu2 ? -1 : uu1 > uu2 ? 1 : 0;
//         result = i_strcmp( pData1->m_dstrUsedUnits.c_str(), pData2->m_dstrUsedUnits.c_str() );
      } else if( *pFieldId == ifds::Units ) {
         double u1 = DSTCommonFunctions::convertToDouble ( pData1->m_dstrUnits.c_str() );
         double u2 = DSTCommonFunctions::convertToDouble ( pData2->m_dstrUnits.c_str() );

         result = u1 < u2 ? -1 : u1 > u2 ? 1 : 0;
//         result = i_strcmp( pData1->m_dstrUnits.c_str(), pData2->m_dstrUnits.c_str() );
      } else if( *pFieldId == ifds::Rate ) {
         double r1 = DSTCommonFunctions::convertToDouble ( pData1->m_dstrRate.c_str() );
         double r2 = DSTCommonFunctions::convertToDouble ( pData2->m_dstrRate.c_str() );

         result = r1 < r2 ? -1 : r1 > r2 ? 1 : 0;
//         result = i_strcmp( pData1->m_dstrRate.c_str(), pData2->m_dstrRate.c_str() );
      } else if( *pFieldId == ifds::CommRate ) {
         double cr1 = DSTCommonFunctions::convertToDouble ( pData1->m_dstrCommRate.c_str() );
         double cr2 = DSTCommonFunctions::convertToDouble ( pData2->m_dstrCommRate.c_str() );

         result = cr1 < cr2 ? -1 : cr1 > cr2 ? 1 : 0;
//         result = i_strcmp( pData1->m_dstrCommRate.c_str(), pData2->m_dstrCommRate.c_str() );
      } else if( *pFieldId == ifds::FromFund ) {
         result = i_strcmp( pData1->m_dstrFromFund.c_str(), pData2->m_dstrFromFund.c_str() );
      } else if( *pFieldId == ifds::FromClass ) {
         result = i_strcmp( pData1->m_dstrFromClass.c_str(), pData2->m_dstrFromClass.c_str() );
	  }else if( *pFieldId == ifds::GroupOrigDate ) {
         result = i_strcmp( pData1->m_dstrGroupOrigDate.c_str(), pData2->m_dstrGroupOrigDate.c_str() );
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
         } else if( *pFieldId == ifds::TransType ) {
            pDispInfo->item.pszText = (I_CHAR*)pData->m_dstrTransType.c_str();
         } else if( *pFieldId == ifds::PartnerShip ) {
            pDispInfo->item.pszText = (I_CHAR*)pData->m_dstrPartnership.c_str();
         } else if( *pFieldId == ifds::OrigEffectiveDate ) {
            pDispInfo->item.pszText = (I_CHAR*)pData->m_dstrOrigEffectiveDate.c_str();
         } else if( *pFieldId == ifds::MaturityDate ) {
            pDispInfo->item.pszText = (I_CHAR*)pData->m_dstrMaturityDate.c_str();
         } else if( *pFieldId == ifds::RollQualDate ) {
            pDispInfo->item.pszText = (I_CHAR*)pData->m_dstrRollQualDate.c_str();
         } else if( *pFieldId == ifds::OriginalTotalUnits ) {
            pDispInfo->item.pszText = (I_CHAR*)pData->m_dstrOriginalTotalUnits.c_str();
         } else if( *pFieldId == ifds::UsedUnits ) {
            pDispInfo->item.pszText = (I_CHAR*)pData->m_dstrUsedUnits.c_str();
         } else if( *pFieldId == ifds::Units ) {
            pDispInfo->item.pszText = (I_CHAR*)pData->m_dstrUnits.c_str();
         } else if( *pFieldId == ifds::Rate ) {
            pDispInfo->item.pszText = (I_CHAR*)pData->m_dstrRate.c_str();
         } else if( *pFieldId == ifds::CommRate ) {
            pDispInfo->item.pszText = (I_CHAR*)pData->m_dstrCommRate.c_str();
         } else if( *pFieldId == ifds::FromFund ) {
            pDispInfo->item.pszText = (I_CHAR*)pData->m_dstrFromFund.c_str();
         } else if( *pFieldId == ifds::FromClass ) {
            pDispInfo->item.pszText = (I_CHAR*)pData->m_dstrFromClass.c_str();
         }
	     else if( *pFieldId == ifds::GroupOrigDate ) {
            pDispInfo->item.pszText = (I_CHAR*)pData->m_dstrGroupOrigDate.c_str();
         }

         return( 1 );
      }
      return( 0 );
   }
};

class LVInventoryDetailsData : public IFDSListCtrlRowDataBase
{
public:
   virtual ~LVInventoryDetailsData() {}

   DString m_dstrTransId, m_dstrTransNum, m_dstrTransType, m_dstrTradeDate;
   DString m_dstrSettleDate, m_dstrUnits, m_dstrRate;

   virtual void update( BaseDlg* pDlg, IFDSListCtrl* pCtrl, const DString* pKey )
   {
      pDlg->getParent()->getField( pDlg, pCtrl->getContainerId(), ifds::TransId, m_dstrTransId );
      pDlg->getParent()->getField( pDlg, pCtrl->getContainerId(), ifds::TransNum, m_dstrTransNum );
      pDlg->getParent()->getField( pDlg, pCtrl->getContainerId(), ifds::TransType, m_dstrTransType );
      pDlg->getParent()->getField( pDlg, pCtrl->getContainerId(), ifds::TradeDate, m_dstrTradeDate );
      pDlg->getParent()->getField( pDlg, pCtrl->getContainerId(), ifds::SettleDate, m_dstrSettleDate );
      pDlg->getParent()->getField( pDlg, pCtrl->getContainerId(), ifds::Units, m_dstrUnits );
      pDlg->getParent()->getField( pDlg, pCtrl->getContainerId(), ifds::Rate, m_dstrRate );
   }
};

class LVInventoryDetailsAdapter : public IFDSListCtrlAdapter< LVInventoryDetailsData >
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
      } else if( *pFieldId == ifds::TransId ) {
         result = i_strcmp( pData1->m_dstrTransId.c_str(), pData2->m_dstrTransId.c_str() );
      } else if( *pFieldId == ifds::TransNum ) {
         result = i_strcmp( pData1->m_dstrTransNum.c_str(), pData2->m_dstrTransNum.c_str() );
      } else if( *pFieldId == ifds::TransType ) {
         result = i_strcmp( pData1->m_dstrTransType.c_str(), pData2->m_dstrTransType.c_str() );
      } else if( *pFieldId == ifds::TradeDate ) {
         int dater_order = DSTCommonFunctions::CompareDates (
               pData1->m_dstrTradeDate.c_str(), 
               pData2->m_dstrTradeDate.c_str(),
               BFDate::DF_DISPLAY);
         result = dater_order == DSTCommonFunctions::FIRST_EARLIER ? -1 : 
                  dater_order == DSTCommonFunctions::EQUAL ? 0 : 1;
//         result = i_strcmp( pData1->m_dstrTradeDate.c_str(), pData2->m_dstrTradeDate.c_str() );
      } else if( *pFieldId == ifds::SettleDate ) {
         int dater_order = DSTCommonFunctions::CompareDates (
               pData1->m_dstrSettleDate.c_str(), 
               pData2->m_dstrSettleDate.c_str(),
               BFDate::DF_DISPLAY);
         result = dater_order == DSTCommonFunctions::FIRST_EARLIER ? -1 : 
                  dater_order == DSTCommonFunctions::EQUAL ? 0 : 1;
//         result = i_strcmp( pData1->m_dstrSettleDate.c_str(), pData2->m_dstrSettleDate.c_str() );
      } else if( *pFieldId == ifds::Units ) {
         double u1 = DSTCommonFunctions::convertToDouble ( pData1->m_dstrUnits.c_str() );
         double u2 = DSTCommonFunctions::convertToDouble ( pData2->m_dstrUnits.c_str() );

         result = u1 < u2 ? -1 : u1 > u2 ? 1 : 0;
//         result = i_strcmp( pData1->m_dstrUnits.c_str(), pData2->m_dstrUnits.c_str() );
      } else if( *pFieldId == ifds::Rate ) {
         double r1 = DSTCommonFunctions::convertToDouble ( pData1->m_dstrRate.c_str() );
         double r2 = DSTCommonFunctions::convertToDouble ( pData2->m_dstrRate.c_str() );

         result = r1 < r2 ? -1 : r1 > r2 ? 1 : 0;
//         result = i_strcmp( pData1->m_dstrRate.c_str(), pData2->m_dstrRate.c_str() );
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
         } else if( *pFieldId == ifds::TransId ) {
            pDispInfo->item.pszText = (I_CHAR*)pData->m_dstrTransId.c_str();
         } else if( *pFieldId == ifds::TransNum ) {
            pDispInfo->item.pszText = (I_CHAR*)pData->m_dstrTransNum.c_str();
         } else if( *pFieldId == ifds::TransType ) {
            pDispInfo->item.pszText = (I_CHAR*)pData->m_dstrTransType.c_str();
         } else if( *pFieldId == ifds::TradeDate ) {
            pDispInfo->item.pszText = (I_CHAR*)pData->m_dstrTradeDate.c_str();
         } else if( *pFieldId == ifds::SettleDate ) {
            pDispInfo->item.pszText = (I_CHAR*)pData->m_dstrSettleDate.c_str();
         } else if( *pFieldId == ifds::Units ) {
            pDispInfo->item.pszText = (I_CHAR*)pData->m_dstrUnits.c_str();
         } else if( *pFieldId == ifds::Rate ) {
            pDispInfo->item.pszText = (I_CHAR*)pData->m_dstrRate.c_str();
         } 

         return( 1 );
      }
      return( 0 );
   }
};


//******************************************************************************
// Constructor
//******************************************************************************
InventorySummaryDlg::InventorySummaryDlg( CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
:BaseMainDlg( InventorySummaryDlg::IDD, pParent, pGIC, pGIParent, rCommand, CLASSNAME )
,m_bInventorySummaryListSelectionInProgress(false)
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );   
   //{{AFX_DATA_INIT( InventorySummaryDlg )
   //}}AFX_DATA_INIT
}

//******************************************************************************
// Destructor
//******************************************************************************
InventorySummaryDlg::~InventorySummaryDlg ()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************
// Called by MFC framework to exchange and validate dialog data
//******************************************************************************
void InventorySummaryDlg::DoDataExchange( CDataExchange* pDX )
{
   BaseMainDlg::DoDataExchange( pDX );
   //{{AFX_DATA_MAP( InventorySummaryDlg ) 
   //}}AFX_DATA_MAP
}

//******************************************************************************
// MFC Message Map
//******************************************************************************

BEGIN_MESSAGE_MAP( InventorySummaryDlg, BaseMainDlg )
//{{AFX_MSG_MAP( InventorySummaryDlg )
ON_BN_CLICKED( IDC_BTN_MORE, OnBtnMore )
ON_BN_CLICKED( IDC_BTN_MORE_DETAILS, OnBtnMoreDetail )
ON_BN_CLICKED( IDC_CHK_ACTIVE_ONLY, OnChkActiveOnly )
ON_BN_CLICKED( IDC_BTN_HISTORY, OnBtnTransactionHistory )
ON_CBN_SELCHANGE (IDC_CMB_FUND, OnSelchangeCmbFund)
ON_NOTIFY(NM_DBLCLK, IDC_LV_INVENTORY_DETAILS, OnDblclkLvInventoryDetails)
ON_BN_CLICKED(IDC_BTN_CLAWBACK_INFO, OnBtnInvClawbackInfo)
ON_BN_CLICKED(IDC_CHK_INV_SUMM_SORT_ORDER, OnChkInvSummarySortOrder)

//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//******************************************************************************
// Initialization of Dialog, get InterProcess Global data and sets up the 
// caption in the title bar.
//******************************************************************************
BOOL InventorySummaryDlg::OnInitDialog() 
{
   TRACE_METHOD( CLASSNAME, ONINITDIALOG );

   BaseMainDlg::OnInitDialog();

   DString dstrShrNum, dstrAccountNum, dstrEntityName;
   getParent()->getField(this, IFASTBP_PROC::MFACCOUNT, ifds::ShrNum, dstrShrNum);      
   getParent()->getField( this, IFASTBP_PROC::MFACCOUNT, ifds::AccountNum, dstrAccountNum );  
   SetAccount( dstrAccountNum );   
   dynamic_cast<DSTCWorkSession *>(getBFWorkSession())->getFirstSequenced01AccountholderEntityName( getDataGroupId(),dstrAccountNum,dstrEntityName );
   SetShrAcctCaption(dstrShrNum, dstrAccountNum, dstrEntityName);

   return(TRUE);  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}

//******************************************************************************
// Call by based architecture.  Controls are initialized here by calling the
// addControls() method.  The More button is enable/disable based on the CBO
// data.
//******************************************************************************
void InventorySummaryDlg::OnPostInitDialog()
{
   TRACE_METHOD( CLASSNAME, I_( "OnPostInitDialog" ) );

   CWaitCursor wait;
   addControls( );
   fillFundCombo();
   LoadControl( IDC_TXT_FUND_NAME );
   DisplayLSIFControls();
   GetDlgItem( IDC_BTN_MORE )->EnableWindow( getParent()->doMoreRecordsExist( this, IFASTBP_PROC::INVENTORY_SUMMARY_LIST ) );
   GetDlgItem( IDC_BTN_MORE_DETAILS )->EnableWindow( getParent()->doMoreRecordsExist( this, IFASTBP_PROC::INVENTORY_DETAILS_LIST ) );
   GetDlgItem( IDC_BTN_HISTORY )->EnableWindow( getParent()->getNumberOfItemsInList( this, IFASTBP_PROC::INVENTORY_DETAILS_LIST ) );   
   DString* dstrFundClass = NULL;
   DString dstr;
   CComboBox* cb =static_cast<CComboBox* >(GetDlgItem( IDC_CMB_FUND ) );
   int currSel = cb->GetCurSel();
   if(currSel >= 0)
   {
      dstrFundClass = (DString*)cb->GetItemData(currSel);
   }
   //Copy the key to pass in to getfield which is then replaced by the fund description.
   if ( dstrFundClass ) {
      dstr = *dstrFundClass;
   } else {
      dstr = NULL_STRING;
   }
   setParameter( INV_SUMMARY::FUNDCLASS, dstr );
   DString dstrG1G2TrackType,dstrG1Bal,dstrG2Bal;
   getParent()->getField(this, IFASTBP_PROC::INVENTORY_SUMMARY_LIST, ifds::G1G2TrackType, dstrG1G2TrackType, false);
   getParent()->getField(this, IFASTBP_PROC::INVENTORY_SUMMARY_LIST, ifds::Grp1Shares, dstrG1Bal, false);
   getParent()->getField(this, IFASTBP_PROC::INVENTORY_SUMMARY_LIST, ifds::Grp2Shares, dstrG2Bal, false);
   bool bShow = (!dstrG1Bal.empty() && !dstrG2Bal.empty() && APPLICABLE == dstrG1G2TrackType ) ;
   for(int i = 0; i< _numG1G2Controls; i++ )
   {
      GetDlgItem ( G1G2Controls [i] )->ShowWindow ( bShow );	 
   }
   IFDSListCtrl* pCtrl = dynamic_cast<IFDSListCtrl*>(GetList(IDC_LV_INVENTORY_SUMMARY));
   hideRolloverQualificationDate(pCtrl);
}

//******************************************************************************
// doInit method is not used.
//******************************************************************************
SEVERITY InventorySummaryDlg::doInit()
{
   TRACE_METHOD( CLASSNAME, I_("doInit"));

   getParameter( INV_SUMMARY::FUND_CODE, _dstrFundCode );
   getParameter( INV_SUMMARY::CLASS_CODE, _dstrClassCode );

   return ( NO_CONDITION );
}

//******************************************************************************
// This method sets up the custom controls to the correct data set.
//******************************************************************************
void InventorySummaryDlg::addControls( )
{
   TRACE_METHOD( CLASSNAME, I_( "addControls" ) );
/*
   AddListControl( CLASSNAME, IDC_LV_INVENTORY_SUMMARY, LV_INVENTORY_SUMMARY_LIST, ifds::InventorySummHeading, 
                   IFASTBP_PROC::INVENTORY_SUMMARY_LIST, 0, true, LISTFLAG_NOT_AUTO_ADD | LISTFLAG_NOT_UPDATABLE );   
*/
   IFDSListCtrl* pCtrl = 
      new IFDSAdaptedListCtrl< LVInventorySummaryAdapter >
         ( this, CLASSNAME, IDC_LV_INVENTORY_SUMMARY, 0, /*LISTFLAG_NOT_AUTO_ADD | LISTFLAG_NOT_UPDATABLE*/0, true, true );
   AddIFDSListControl( pCtrl, 
                       LV_INVENTORY_SUMMARY_LIST,
                       IFASTBP_PROC::INVENTORY_SUMMARY_LIST,
                       ifds::InventorySummHeading );

  // DString dstrMarket = DSTCommonFunctions::getMarket();
   //if ( dstrMarket == MARKET_IDS::CANADA ) {
   AddControl( CTRL_STATIC, IDC_TXT_FUND_NBR,          IFASTBP_PROC::INVENTORY_SUMMARY_LIST, ifds::FundNumber,          CTRLFLAG_DEFAULT,               IDC_LV_INVENTORY_SUMMARY );
   //}

   AddControl( CTRL_STATIC, IDC_TXT_TOTAL_UNITS,       IFASTBP_PROC::INVENTORY_SUMMARY_LIST, ifds::UnitsTotal,          CTRLFLAG_DEFAULT,               IDC_LV_INVENTORY_SUMMARY );
   AddControl( CTRL_STATIC, IDC_TXT_INVENTORY_SUMM_ID, IFASTBP_PROC::INVENTORY_SUMMARY_LIST, ifds::InvSummId,           CTRLFLAG_DEFAULT,               IDC_LV_INVENTORY_SUMMARY );
   AddControl( CTRL_STATIC, IDC_TXT_FUND_NAME,         CTRLFLAG_GUI_FIELD, 0 );
   AddControl( CTRL_COMBO,  IDC_CMB_FUND,              CTRLFLAG_GUI_FIELD, 0 );
   AddControl( CTRL_COMBO,  IDC_CMB_INV_SUMM_SORT_BY,  IFASTBP_PROC::INVENTORY_SUMMARY_LIST, ifds::SortBy,              CTRLFLAG_INITCOMBO_BY_SUB_LIST, 0 );
   AddControl( CTRL_STATIC, IDC_TXT_STATUS,            IFASTBP_PROC::INVENTORY_SUMMARY_LIST, ifds::InvStatus,           CTRLFLAG_DEFAULT,               IDC_LV_INVENTORY_SUMMARY );
   AddControl( CTRL_STATIC, IDC_TXT_LAST_ACTIVE_DATE,  IFASTBP_PROC::INVENTORY_SUMMARY_LIST, ifds::LastActiveDate,      CTRLFLAG_DEFAULT,               IDC_LV_INVENTORY_SUMMARY );
   AddControl( CTRL_STATIC, IDC_TXT_FUND_CODE,         IFASTBP_PROC::INVENTORY_SUMMARY_LIST, ifds::FromFund,            CTRLFLAG_DEFAULT,               IDC_LV_INVENTORY_SUMMARY );
   AddControl( CTRL_STATIC, IDC_TXT_CLASS_CODE,        IFASTBP_PROC::INVENTORY_SUMMARY_LIST, ifds::FromClass,           CTRLFLAG_DEFAULT,               IDC_LV_INVENTORY_SUMMARY );
   AddControl( CTRL_STATIC, IDC_TXT_ORIGINAL_RATE,     IFASTBP_PROC::INVENTORY_SUMMARY_LIST, ifds::OrigFundRate,        CTRLFLAG_DEFAULT,               IDC_LV_INVENTORY_SUMMARY );
   AddControl( CTRL_STATIC, IDC_TXT_ORIGINAL_UNITS,    IFASTBP_PROC::INVENTORY_SUMMARY_LIST, ifds::OrigFundUnits,       CTRLFLAG_DEFAULT,               IDC_LV_INVENTORY_SUMMARY );
   AddControl( CTRL_STATIC, IDC_TXT_COMMISSIONABLE,    IFASTBP_PROC::INVENTORY_SUMMARY_LIST, ifds::Commissionable,      CTRLFLAG_DEFAULT,               IDC_LV_INVENTORY_SUMMARY );
   AddControl( CTRL_STATIC, IDC_TXT_RDRAPPLICABLE,     IFASTBP_PROC::INVENTORY_SUMMARY_LIST, ifds::RDRAdvice    ,       CTRLFLAG_DEFAULT, IDC_LV_INVENTORY_SUMMARY );
   AddControl( CTRL_STATIC, IDC_TXT_COMMISSION,        IFASTBP_PROC::INVENTORY_SUMMARY_LIST, ifds::CommRate,            CTRLFLAG_DEFAULT,               IDC_LV_INVENTORY_SUMMARY );

   // PET1046 FN01
   AddControl( CTRL_STATIC, IDC_TXT_TRACE_NUMBER,      IFASTBP_PROC::INVENTORY_SUMMARY_LIST, ifds::TraceNo,             CTRLFLAG_DEFAULT,               IDC_LV_INVENTORY_SUMMARY );
   AddControl( CTRL_STATIC, IDC_TXT_MATURE_DATE,       IFASTBP_PROC::INVENTORY_SUMMARY_LIST, ifds::MatureDate,          CTRLFLAG_DEFAULT,               IDC_LV_INVENTORY_SUMMARY );
   AddControl( CTRL_STATIC, IDC_TXT_TAX_JURIS,         IFASTBP_PROC::INVENTORY_SUMMARY_LIST, ifds::TaxJuris,            CTRLFLAG_DEFAULT,               IDC_LV_INVENTORY_SUMMARY );
   AddControl( CTRL_STATIC, IDC_TXT_RECEIPT_STATUS,    IFASTBP_PROC::INVENTORY_SUMMARY_LIST, ifds::ReceiptStatus,       CTRLFLAG_DEFAULT,               IDC_LV_INVENTORY_SUMMARY );
   AddControl( CTRL_STATIC, IDC_TXT_RECEIPT_NUMBER,    IFASTBP_PROC::INVENTORY_SUMMARY_LIST, ifds::ReceiptNumber,       CTRLFLAG_DEFAULT,               IDC_LV_INVENTORY_SUMMARY );
//   AddControl( CTRL_CHECKBOX, IDC_CHK_ACTIVE_ONLY, CTRLFLAG_NOT_UPDATABLE | CTRLFLAG_GUI_FIELD );
   AddControl( CTRL_STATIC, IDC_TXT_TOTAL_CLAW_BACK,   IFASTBP_PROC::INVENTORY_SUMMARY_LIST, ifds::TotalCBFFreeUnits,   CTRLFLAG_DEFAULT,               IDC_LV_INVENTORY_SUMMARY );

   AddListControl( CLASSNAME, IDC_LV_INVENTORY_DETAILS, LV_INVENTORY_DETAILS_LIST, ifds::InventoryDetailsHeading,
                   IFASTBP_PROC::INVENTORY_DETAILS_LIST, IDC_LV_INVENTORY_SUMMARY, true, LISTFLAG_NOT_AUTO_ADD | LISTFLAG_NOT_UPDATABLE );
   AddControl( CTRL_STATIC, IDC_TXT_TOTAL_G1BAL,       IFASTBP_PROC::INVENTORY_SUMMARY_LIST, ifds::Grp1Shares,          CTRLFLAG_DEFAULT,               IDC_LV_INVENTORY_SUMMARY );
   AddControl( CTRL_STATIC, IDC_TXT_TOTAL_G2BAL,       IFASTBP_PROC::INVENTORY_SUMMARY_LIST, ifds::Grp2Shares,          CTRLFLAG_DEFAULT,               IDC_LV_INVENTORY_SUMMARY );

/*
   IFDSListCtrl* pCtrl2 = 
      new IFDSAdaptedListCtrl< LVInventoryDetailsAdapter >
         ( this, CLASSNAME, IDC_LV_INVENTORY_DETAILS, IDC_LV_INVENTORY_SUMMARY, LISTFLAG_NOT_AUTO_ADD | LISTFLAG_NOT_UPDATABLE, true, true );
   AddIFDSListControl( pCtrl2, 
                       LV_INVENTORY_DETAILS_LIST,
                       IFASTBP_PROC::INVENTORY_DETAILS_LIST,
                       ifds::InventoryDetailsHeading );
*/

   m_bInventorySummaryListSelectionInProgress = true;
   defaultCheckBoxSortOrder();
   LoadListControl ( IDC_LV_INVENTORY_SUMMARY ); 
   reSortListByCombo(); 
   ConnectControlsToData ();  
   LoadControls();
   m_bInventorySummaryListSelectionInProgress = false;
}

//******************************************************************************
// Method to refresh dialog controls
// @param   GenericInterface *rpGICaller - pointer to the calling object
// @param   const I_CHAR *szOriginalCommand - Not used in this case, but 
//                      can be used to instruct special processing.
//******************************************************************************
bool InventorySummaryDlg::doRefresh( GenericInterface * rpGICaller, 
                                  const I_CHAR * szOriginalCommand )
{
   TRACE_METHOD( CLASSNAME, I_( "doRefresh" ) );

   DString dstrShrNum, dstrAccountNum, dstrEntityName;
   getParent()->getField(this, IFASTBP_PROC::MFACCOUNT, ifds::ShrNum, dstrShrNum);      
   getParent()->getField( this, IFASTBP_PROC::MFACCOUNT, ifds::AccountNum, dstrAccountNum );  
   SetAccount( dstrAccountNum );   
   dynamic_cast<DSTCWorkSession *>(getBFWorkSession())->getFirstSequenced01AccountholderEntityName( getDataGroupId(),dstrAccountNum,dstrEntityName );
   SetShrAcctCaption(dstrShrNum, dstrAccountNum, dstrEntityName);

   getParameter( INV_SUMMARY::FUND_CODE, _dstrFundCode );
   getParameter( INV_SUMMARY::CLASS_CODE, _dstrClassCode );
   fillFundCombo( );

   m_bInventorySummaryListSelectionInProgress = true;
   defaultCheckBoxSortOrder();
   LoadListControl ( IDC_LV_INVENTORY_SUMMARY );
   reSortListByCombo();
   m_bInventorySummaryListSelectionInProgress = false;
   DString dstrG1G2TrackType,dstrG1Bal,dstrG2Bal;
   getParent()->getField(this, IFASTBP_PROC::INVENTORY_SUMMARY_LIST, ifds::G1G2TrackType, dstrG1G2TrackType, false);
   getParent()->getField(this, IFASTBP_PROC::INVENTORY_SUMMARY_LIST, ifds::Grp1Shares, dstrG1Bal, false);
   getParent()->getField(this, IFASTBP_PROC::INVENTORY_SUMMARY_LIST, ifds::Grp2Shares, dstrG2Bal, false);
   bool bShow = (!dstrG1Bal.empty() && !dstrG2Bal.empty() && APPLICABLE == dstrG1G2TrackType ) ;
   for(int i = 0; i< _numG1G2Controls; i++ )
   {
      GetDlgItem ( G1G2Controls [i] )->ShowWindow ( bShow );	 
   }
   return(true);
}

//******************************************************************************
void InventorySummaryDlg::OnBtnMore  ( )
{
   TRACE_METHOD( CLASSNAME, ONBTNMORE );

   CWaitCursor wait; 
   SetMessageStatusBar( TXT_LOAD_INVENTORY );

   static int cursel;

   cursel = GetList( IDC_LV_INVENTORY_SUMMARY )->GetNextItem( -1, LVIS_SELECTED | LVNI_FOCUSED );

   const DString *crtKey = &getParent()->getCurrentListItemKey( this, IFASTBP_PROC::INVENTORY_SUMMARY_LIST );

   if( getParent()->performSearch( this, IFASTBP_PROC::INVENTORY_SUMMARY_LIST, SEARCH_NEXT_BLOCK ) <= WARNING )
   {
      m_bInventorySummaryListSelectionInProgress = true;
      LoadListControl( IDC_LV_INVENTORY_SUMMARY );
      if( *crtKey != NULL_STRING )
      {
         GetList( IDC_LV_INVENTORY_SUMMARY )->SetSelection( crtKey );
      }
      m_bInventorySummaryListSelectionInProgress = false;
   }
   GetDlgItem( IDC_BTN_MORE )->EnableWindow( getParent()->doMoreRecordsExist( this, IFASTBP_PROC::INVENTORY_SUMMARY_LIST ) );
   GetList( IDC_LV_INVENTORY_SUMMARY )->SetSelection(cursel, true, true);
   SetMessageStatusBar(NULL_STRING);
}

//******************************************************************************
void InventorySummaryDlg::OnSelchangeCmbFund() 
{
   TRACE_METHOD( CLASSNAME, I_("OnSelchangeCmbRespBen") );

//   CWaitCursor wait;
   SetMessageStatusBar( TXT_LOAD_INVENTORY );  

   // Get Checked
   DString dstrActiveOnly;
   dstrActiveOnly = ( ((CButton *) GetDlgItem( IDC_CHK_ACTIVE_ONLY ))->GetCheck() == 1 ) ? I_("Y") : I_("N");
   setParameter( INV_SUMMARY::ACTIVEONLY, dstrActiveOnly );

   DString* dstrFundClass, dstr;
   CComboBox* cb =static_cast<CComboBox* >(GetDlgItem( IDC_CMB_FUND ) );
   dstrFundClass = (DString*)cb->GetItemData ( cb->GetCurSel() );
   //Copy the key to pass in to getfield which is then replaced by the fund description.
   if ( dstrFundClass ) {
      dstr = *dstrFundClass;
   } else {
      dstr = NULL_STRING;
   }

   DisplayLSIFControls();

   // need to set the key first before overriding dstr.
   setParameter( INV_SUMMARY::FUNDCLASS, dstr );
   getParent()->getField(this, IFASTBP_PROC::INVENTORY_SUMMARY_LIST, INV_SUMMARY::SEARCHFUNDDESC, dstr );
//   SetDlgItemText ( IDC_TXT_FUND_NAME, dstr.c_str() );  
   //GetList ( IDC_LV_INVENTORY_SUMMARY )->DeleteAllItems(); 
   if( !dstr.empty() )
      getParent()->performSearch( this, IFASTBP_PROC::INVENTORY_SUMMARY_LIST, SEARCH_START );
   m_bInventorySummaryListSelectionInProgress = true;   
   LoadListControl ( IDC_LV_INVENTORY_SUMMARY );
   reSortListByCombo();
   GetDlgItem( IDC_BTN_MORE )->EnableWindow( getParent()->doMoreRecordsExist( this, IFASTBP_PROC::INVENTORY_SUMMARY_LIST ) );   
   GetDlgItem( IDC_BTN_MORE_DETAILS )->EnableWindow( getParent()->doMoreRecordsExist( this, IFASTBP_PROC::INVENTORY_DETAILS_LIST ) );   
   GetDlgItem( IDC_BTN_HISTORY )->EnableWindow( getParent()->getNumberOfItemsInList( this, IFASTBP_PROC::INVENTORY_DETAILS_LIST ) );
   m_bInventorySummaryListSelectionInProgress = false;

   SetMessageStatusBar(NULL_STRING); 
   DString dstrG1G2TrackType,dstrG1Bal,dstrG2Bal;
   getParent()->getField(this, IFASTBP_PROC::INVENTORY_SUMMARY_LIST, ifds::G1G2TrackType, dstrG1G2TrackType, false);
   getParent()->getField(this, IFASTBP_PROC::INVENTORY_SUMMARY_LIST, ifds::Grp1Shares, dstrG1Bal, false);
   getParent()->getField(this, IFASTBP_PROC::INVENTORY_SUMMARY_LIST, ifds::Grp2Shares, dstrG2Bal, false);
   bool bShow = (!dstrG1Bal.empty() && !dstrG2Bal.empty() && APPLICABLE == dstrG1G2TrackType ) ;
   for(int i = 0; i< _numG1G2Controls; i++ )
   {
      GetDlgItem ( G1G2Controls [i] )->ShowWindow ( bShow );	 
   }
}

//********************************************************************************************************
void InventorySummaryDlg::fillFundCombo( )
{
   CComboBox* cb =static_cast<CComboBox* >(GetDlgItem( IDC_CMB_FUND ) );
   cb->ResetContent();
   int iIndex;
   DString dstr1,dstr2;
   CString out;

   const DString *pCurKey  = &( getParent()->getCurrentListItemKey( this, IFASTBP_PROC::ACCOUNT_HOLDINGS ) );
   const DString *pKey =&( getParent()->getFirstListItemKey( this, IFASTBP_PROC::ACCOUNT_HOLDINGS ));
   std::set < DString > FundList;
   if( (*pKey)!=NULL_STRING )
   {
      do
      {
         getParent()->getField( this, IFASTBP_PROC::ACCOUNT_HOLDINGS, ifds::rxFundCode, dstr1 );
         dstr1.strip();
         getParent()->getField( this, IFASTBP_PROC::ACCOUNT_HOLDINGS, ifds::rxClassCode, dstr2 );
         dstr2.strip();

         dstr1+=I_(" ")+dstr2;
         if ( FundList.insert ( dstr1 ).second ) {
            iIndex = cb->AddString(dstr1.c_str());
            cb->SetItemData( iIndex, reinterpret_cast< DWORD >( pKey ) );
         }
      }while( *(pKey=&(getParent()->getNextListItemKey( this, IFASTBP_PROC::ACCOUNT_HOLDINGS ))) != NULL_STRING );

      if( (*pCurKey)!=NULL_STRING )
      {
         getParent()->setCurrentListItem(this, IFASTBP_PROC::ACCOUNT_HOLDINGS, *pCurKey);
      }
   }

   // Select the Fund/Class
   out=_dstrFundCode.c_str();
   out+=I_(" ");
   out+=_dstrClassCode.c_str();
   cb->SelectString(0, out);
}

//********************************************************************************************************
void InventorySummaryDlg::OnBtnTransactionHistory()
{

   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OnBtnDetail" ) );

   DString dstrTransId,dstr;
   try
   {
      E_COMMANDRETURN eRtn = CMD_CANCEL;
      CWaitCursor wait;

      DString fundCode, classCode;
      const DString *pKey = &getParent()->getCurrentListItemKey( this, IFASTBP_PROC::INVENTORY_SUMMARY_LIST );
      if( (*pKey)!=NULL_STRING )
      {
         getParent()->getField( this, IFASTBP_PROC::INVENTORY_SUMMARY_LIST, ifds::FromFund, fundCode );
         getParent()->getField( this, IFASTBP_PROC::INVENTORY_SUMMARY_LIST, ifds::FromClass, classCode );

         setParameter( I_( "FundCode" ), fundCode ); 
         setParameter( I_( "ClassCode" ), classCode ); 
         setParameter( I_( "AllFundMode" ), I_("N") );
      }
      else
      {
         assert(0);
      }

      // Trans Id
      getParent()->getField(this, IFASTBP_PROC::INVENTORY_DETAILS_LIST, ifds::TransId, dstrTransId, false);
      setParameter( I_("ReqTransid0"), dstrTransId );

      // Account Number
      DString dstrAccountNum;
      getParent()->getField( this, IFASTBP_PROC::MFACCOUNT, ifds::AccountNum, dstrAccountNum );  
      setParameter( I_("AccountNum"), dstrAccountNum );

      // Disable Not Inventory Information
      setParameter( I_("DisableInvInfo"), I_("N") );

      eRtn = invokeCommand( getParent(), CMD_BPROC_TRANS_HISTORY, PROC_SUPPORT, false, NULL );
      switch( eRtn )
      {
         case CMD_OK:
         case CMD_MODELESS_INPROCESS:
         case CMD_CANCEL:
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
void InventorySummaryDlg::OnBtnMoreDetail()
{
   TRACE_METHOD( CLASSNAME, ONBTNMOREDETAIL );

   CWaitCursor wait; 
   SetMessageStatusBar( TXT_LOAD_INVENTORY );

   static int cursel;

   cursel = GetList( IDC_LV_INVENTORY_DETAILS )->GetNextItem( -1, LVIS_SELECTED | LVNI_FOCUSED );

   const DString *crtKey = &getParent()->getCurrentListItemKey( this, IFASTBP_PROC::INVENTORY_DETAILS_LIST );

   if( getParent()->performSearch( this, IFASTBP_PROC::INVENTORY_DETAILS_LIST, SEARCH_NEXT_BLOCK ) <= WARNING )
   {
      LoadListControl( IDC_LV_INVENTORY_DETAILS );
      if( *crtKey != NULL_STRING )
      {
         GetList( IDC_LV_INVENTORY_DETAILS )->SetSelection( crtKey );
      }
   }
   GetDlgItem( IDC_BTN_MORE_DETAILS )->EnableWindow( getParent()->doMoreRecordsExist( this, IFASTBP_PROC::INVENTORY_DETAILS_LIST ) );
   GetList( IDC_LV_INVENTORY_DETAILS )->SetSelection(cursel, true, true);

   SetMessageStatusBar(NULL_STRING);
}

//******************************************************************************
void InventorySummaryDlg::OnChkActiveOnly()
{
   TRACE_METHOD( CLASSNAME, ONBTNMOREDETAIL );

//   CWaitCursor wait; 
   SetMessageStatusBar( TXT_LOAD_INVENTORY );

   // Get Checked
   DString dstrActiveOnly;
   dstrActiveOnly = ( ((CButton *) GetDlgItem( IDC_CHK_ACTIVE_ONLY ))->GetCheck() == 1 ) ? I_("Y") : I_("N");
   setParameter( INV_SUMMARY::ACTIVEONLY, dstrActiveOnly );


   DString* dstrFundClass, dstr;
   CComboBox* cb =static_cast<CComboBox* >(GetDlgItem( IDC_CMB_FUND ) );
   dstrFundClass = (DString*)cb->GetItemData ( cb->GetCurSel() );
   if( dstrFundClass != (DString *) CB_ERR )
   {
      dstr = *dstrFundClass;
   }
   else
   {
      dstr = NULL_STRING;
   }

   // need to set the key first before overriding dstr.
   setParameter( INV_SUMMARY::FUNDCLASS, dstr );
   getParent()->getField(this, IFASTBP_PROC::INVENTORY_SUMMARY_LIST, INV_SUMMARY::SEARCHFUNDDESC, dstr );
   if( !dstr.empty() )
      getParent()->performSearch( this, IFASTBP_PROC::INVENTORY_SUMMARY_LIST, SEARCH_START );

   m_bInventorySummaryListSelectionInProgress = true;
   LoadListControl ( IDC_LV_INVENTORY_SUMMARY );
   reSortListByCombo();
   GetDlgItem( IDC_BTN_MORE )->EnableWindow( getParent()->doMoreRecordsExist( this, IFASTBP_PROC::INVENTORY_SUMMARY_LIST ) );   
   GetDlgItem( IDC_BTN_MORE_DETAILS )->EnableWindow( getParent()->doMoreRecordsExist( this, IFASTBP_PROC::INVENTORY_DETAILS_LIST ) );   
   GetDlgItem( IDC_BTN_HISTORY )->EnableWindow( getParent()->getNumberOfItemsInList( this, IFASTBP_PROC::INVENTORY_DETAILS_LIST ) );
   m_bInventorySummaryListSelectionInProgress = false;

   SetMessageStatusBar(NULL_STRING);    
}

//******************************************************************************
void InventorySummaryDlg::DoListItemChanged( UINT listControlID,
                                             const DString &strKey,
                                             bool bIsNewItem,
                                             bool bIsDummyItem )
{
   if( listControlID == IDC_LV_INVENTORY_SUMMARY )
   {
      getParent()->send( this, I_("CLEAR DETAILS" ) );
      GetDlgItem( IDC_BTN_CLAWBACK_INFO )->EnableWindow( false );
      GetDlgItem( IDC_BTN_MORE_DETAILS )->EnableWindow( getParent()->doMoreRecordsExist( this, IFASTBP_PROC::INVENTORY_DETAILS_LIST ) );
   }

    if( listControlID == IDC_LV_INVENTORY_DETAILS )      
   {
      // enable Clawback_Info button     
      DString dstrFundCode, dstrFundCategory; 
      int iItemNumber = 0;
      iItemNumber = getParent()->getNumberOfItemsInList( this, IFASTBP_PROC::INVENTORY_SUMMARY_LIST );		
      // This is defense programming, we shouldn't really check this at this point
      if ( 	iItemNumber > 0 )
      {
         getParent()->getField(this, IFASTBP_PROC::INVENTORY_SUMMARY_LIST, ifds::FromFund, dstrFundCode, false );
      }

      if ( dstrFundCode.strip() != I_( "CASH" ) )
      {
         getParent()->setCurrentListItem(this, IFASTBP_PROC::FUND_MASTER_LIST, dstrFundCode );
         getParent()->getField(this, IFASTBP_PROC::FUND_MASTER_LIST, ifds::FundCategory, dstrFundCategory );
      }

      DString dstrTransType;
      getParent()->getField(this, IFASTBP_PROC::INVENTORY_DETAILS_LIST, ifds::TransType, dstrTransType, false );
      bool enableClawbackBtn = ( dstrFundCategory == CODE_FUND_CATEGORY_LSIF  &&
         DSTCommonFunctions::codeInList( dstrTransType, TRADETYPE::MONEY_OUT_TXN ))  ;

      GetDlgItem( IDC_BTN_CLAWBACK_INFO )->EnableWindow( enableClawbackBtn );
   }

}

//******************************************************************************
void InventorySummaryDlg::DisplayLSIFControls()
{
   CComboBox* cb =static_cast<CComboBox* >(GetDlgItem( IDC_CMB_FUND ) );
   CString cstrText;
   cb->GetWindowText( cstrText );
   DString dstrFund( cstrText );
   dstrFund.stripLeading().stripTrailing();
   dstrFund = dstrFund.substr( 0, dstrFund.find(  I_CHAR(' ') ) );

   DString dstrFundCategory;
   if( !dstrFund.empty() )
   {
      getParent()->setCurrentListItem(this, IFASTBP_PROC::FUND_MASTER_LIST, dstrFund);
      getParent()->getField(this, IFASTBP_PROC::FUND_MASTER_LIST, ifds::FundCategory, dstrFundCategory );
   }

   int nCmdShow = ( dstrFundCategory == CODE_FUND_CATEGORY_LSIF ) ? SW_SHOW : SW_HIDE;
   GetDlgItem( IDC_STC_TOTAL_CLAW_BACK )->ShowWindow( nCmdShow );
   GetDlgItem( IDC_TXT_TOTAL_CLAW_BACK )->ShowWindow( nCmdShow );

   GetDlgItem( IDC_STC_LSIF_FRAME )->ShowWindow( nCmdShow );
   GetDlgItem( IDC_STC_TRACE_NUMBER )->ShowWindow( nCmdShow );
   GetDlgItem( IDC_TXT_TRACE_NUMBER )->ShowWindow( nCmdShow );
   GetDlgItem( IDC_STC_MATURE_DATE )->ShowWindow( nCmdShow );
   GetDlgItem( IDC_TXT_MATURE_DATE )->ShowWindow( nCmdShow );
   GetDlgItem( IDC_STC_TAX_JURISDICTION )->ShowWindow( nCmdShow );
   GetDlgItem( IDC_TXT_TAX_JURIS )->ShowWindow( nCmdShow );
   GetDlgItem( IDC_STC_RECEIPT_STATUS )->ShowWindow( nCmdShow );
   GetDlgItem( IDC_TXT_RECEIPT_STATUS )->ShowWindow( nCmdShow );
   GetDlgItem( IDC_STC_RECEIPT_NUMBER )->ShowWindow( nCmdShow );
   GetDlgItem( IDC_TXT_RECEIPT_NUMBER )->ShowWindow( nCmdShow );
}

//******************************************************************************
void InventorySummaryDlg::OnDblclkLvInventoryDetails(NMHDR* pNMHDR, LRESULT* pResult) 
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnDblclkLvInventoryDetails" ) );
   if ( GetList( IDC_LV_INVENTORY_DETAILS )->GetNextSelection() >= 0 )
   {
      GetDlgItem( IDC_BTN_HISTORY )->SetFocus(); 
      OnBtnTransactionHistory();
   }
   *pResult = 0;
}

//******************************************************************************
void InventorySummaryDlg::OnBtnInvClawbackInfo() 
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnBtnInvClawbackInfo" ) ); 

   E_COMMANDRETURN eRtn = CMD_CANCEL;
   CWaitCursor wait;

   DString dstrTransId, dstrAccountNum;
   try
   {
      int iItemNumber = 0;
      iItemNumber = getParent()->getNumberOfItemsInList( this, IFASTBP_PROC::INVENTORY_DETAILS_LIST );		
      if ( iItemNumber > 0 )
      {
         // Trans Id
         getParent()->getField(this, IFASTBP_PROC::INVENTORY_DETAILS_LIST, ifds::TransId, dstrTransId, false);
         getParent()->getField( this, IFASTBP_PROC::MFACCOUNT, ifds::AccountNum, dstrAccountNum );
         setParameter( INV_DETL_DEDUCT::ACCOUNT_NUMBER, dstrAccountNum);
         setParameter( INV_DETL_DEDUCT::TRANS_ID, dstrTransId );

         eRtn = invokeCommand( getParent(), CMD_BPROC_INVENTORY_DETAIL_DEDUCTION, PROC_SUPPORT, true, NULL );
         switch( eRtn )
         {
            case CMD_OK:
            case CMD_MODELESS_INPROCESS:
            case CMD_CANCEL:
               break;
            default:
               // Display error
               ConditionMessageBox( FRAMEBELOW(), GETHIGHESTSEVERITY() );
               break;
         }
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
bool InventorySummaryDlg::GetDataForControl( UINT controlID,
                                             DString &strValueOut,
                                             bool bFormatted,
                                             int index ) const
{
   DString  str;

   bool bReturn = false;
   switch( controlID )
   {
      case IDC_TXT_FUND_NAME:
      {
         CComboBox* cb =static_cast<CComboBox* >(GetDlgItem( IDC_CMB_FUND ) );
         CString cstrText;
         cb->GetWindowText( cstrText );
         DString dstrFund( cstrText );
         dstrFund.stripLeading().stripTrailing();
         dstrFund = dstrFund.substr( 0, dstrFund.find(  I_CHAR(' ') ) );

         FundMasterList *pFundMasterList = NULL;
         dynamic_cast<DSTCWorkSession *>(getBFWorkSession())->getMgmtCo().getFundMasterList( pFundMasterList );
         if( pFundMasterList && !dstrFund.empty() )
         {
            pFundMasterList->getFundName( dstrFund, strValueOut);
         }         
         bReturn = true;
      }
      break;

      case IDC_CMB_FUND:
      {
         bReturn = true;
      }
      break;

      default:
         break;
   }
   return bReturn;
}

//******************************************************************************
void InventorySummaryDlg::ControlUpdated( UINT controlID,
                                          const DString &strValue )
{
   TRACE_METHOD( CLASSNAME, I_( "ControlUpdated" ) );

   switch( controlID )
   {
      case IDC_CMB_FUND:
      {
         LoadControl( IDC_TXT_FUND_NAME );
         setUpdateFlag( false );
      }
      break;
      case IDC_CMB_INV_SUMM_SORT_BY:
      {
         if(!m_bInventorySummaryListSelectionInProgress)
         {
            m_bInventorySummaryListSelectionInProgress = true;
            LoadListControl ( IDC_LV_INVENTORY_SUMMARY );
            reSortListByCombo();
            GetDlgItem( IDC_BTN_MORE )->EnableWindow( getParent()->doMoreRecordsExist( this, IFASTBP_PROC::INVENTORY_SUMMARY_LIST ) );   
            setUpdateFlag( false );
            m_bInventorySummaryListSelectionInProgress = false;
         }
      }
      break;

      default:
         break;
   }
}

//******************************************************************************
 bool InventorySummaryDlg::SetDataFromControl( UINT controlID,
                                               const DString &strValue,
                                               bool bFormatted,
                                               SEVERITY &sevRtn,
                                               int index )
{
   TRACE_METHOD( CLASSNAME, I_( "SetDataFromControl" ) );

   bool bRet = false;
   switch(controlID)
   {
      case IDC_CMB_FUND:
      case IDC_TXT_FUND_NAME:
      {
         bRet =  true;
         break;
      }
      
   default:
      break;

   }
   return bRet;
}

//******************************************************************************
void InventorySummaryDlg::OnChkInvSummarySortOrder()
{
   TRACE_METHOD( CLASSNAME, I_("OnChkInvSummarySortOrder"));

   if(!m_bInventorySummaryListSelectionInProgress)
   {   
      int checkStatus = 
         static_cast<CButton*>(GetDlgItem(IDC_CHK_INV_SUMM_SORT_ORDER))->GetCheck();

      getParent()->setField(this, 
                           IFASTBP_PROC::INVENTORY_SUMMARY_LIST, 
                           ifds::SortOrder,
                           (checkStatus == BST_CHECKED)? I_("D"):I_("A"),
                           false);

      m_bInventorySummaryListSelectionInProgress = true;
      LoadListControl ( IDC_LV_INVENTORY_SUMMARY );
      reSortListByCombo();
      GetDlgItem( IDC_BTN_MORE )->EnableWindow( getParent()->doMoreRecordsExist( this, IFASTBP_PROC::INVENTORY_SUMMARY_LIST ) );   
      m_bInventorySummaryListSelectionInProgress = false;
   }
}

//******************************************************************************
void InventorySummaryDlg::reSortListByCombo(void)
{
   TRACE_METHOD( CLASSNAME, I_("reSortListByCombo"));

   IFDSListCtrl* pCtrl = dynamic_cast<IFDSListCtrl*>(GetList(IDC_LV_INVENTORY_SUMMARY));

   if ( NULL != pCtrl )
   {
      DString strCurSortByColumn,
         strCurSortOrder,
         strSubSt;
      getParent()->getField(this, IFASTBP_PROC::INVENTORY_SUMMARY_LIST, ifds::SortByColumn, strCurSortByColumn, false);
      getParent()->getField(this, IFASTBP_PROC::INVENTORY_SUMMARY_LIST, ifds::SortOrder, strCurSortOrder, false);
      strCurSortOrder.strip().upperCase();
      int iSortByColumn = strCurSortByColumn.strip().asInteger();
      int iAssending = strCurSortOrder == I_("A")? 1 : -1;
      
      pCtrl->SortOnColumn( iSortByColumn*iAssending );
   }
}

//******************************************************************************
void InventorySummaryDlg::defaultCheckBoxSortOrder()
{
   DString strCurSortOrder;
   getParent()->getField(this, 
                        IFASTBP_PROC::INVENTORY_SUMMARY_LIST, 
                        ifds::SortOrder,
                        strCurSortOrder,
                        false);
   if(strCurSortOrder.strip().upperCase() == I_("D"))
   {
      static_cast<CButton*>(GetDlgItem(IDC_CHK_INV_SUMM_SORT_ORDER))->SetCheck(BST_CHECKED);
   }
}
/******************************************************************************
 Input: IFDSListBase pointer
 OutPut:None
 Return:None
 Functionality:Hide RolloverQualificationDate coloums .Robs 
 ******************************************************************************/
void InventorySummaryDlg::hideRolloverQualificationDate(IFDSListBase* const pBaseCtrl)
{
   bool bDisplay;
   DString dstrSubstList,dstrDisplayRolloverQualificationDate;
   getParent()->getField(this, IFASTBP_PROC::INVENTORY_SUMMARY_LIST, ifds::DisplayRolloverQualificationDate, 
						 dstrDisplayRolloverQualificationDate, false);
   bDisplay = (YES == dstrDisplayRolloverQualificationDate) ? true : false ;
   int iColumnNum =0;
   const BFDataFieldProperties*   pBFDataProp = BFDataFieldProperties::get( ifds::InventorySummHeading );
   pBFDataProp->getAllSubstituteValues(dstrSubstList, ClientLocaleContext::get(), 
										true /* No Sort ,get the raw sub order */);
   I_CHAR *temp = const_cast<I_CHAR*> (dstrSubstList.c_str ());
   do
   {
	iColumnNum++;
    DString dstrSubListCode,dstrSubListDescr;   
    temp = parseIdiString (temp, dstrSubListCode, dstrSubListDescr );
	if(DSTCommonFunctions::codeInList (dstrSubListCode, ROLLOVER_QUALIFICATION_DATE))
	{
	  pBaseCtrl->showColumn(iColumnNum, bDisplay );
	} 
   } while (temp && temp != NULL_STRING && *temp);
}
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastgui/InventorySummaryDlg.cpp-arc  $
// 
//    Rev 1.24   May 29 2008 05:54:50   daechach
// PET0006862 Fn02 - Roll Over Qualification Period Enhancement.
// 
//    Rev 1.23   25 Apr 2008 13:19:10   kovacsro
// IN#1112967 - fixed the fund name
// 
//    Rev 1.22   Feb 27 2008 20:23:38   wongsakw
// Inc 1167864 -- Func/Class Appears Twice on FundClass Dropdown list of Inventory Info Screen
// 
//    Rev 1.21   Jan 17 2008 15:20:28   yingz
// fix incident 1129968
// 
//    Rev 1.20   06 Jan 2008 17:45:38   popescu
// Fixed the More button for the inventory details list
// 
//    Rev 1.19   Sep 15 2005 15:13:40   popescu
// Incident#403519 - added CLASSNAME as the fifth parameter to  BaseMainDlg constructor
// 
//    Rev 1.18   Jul 14 2005 17:16:26   popescu
// Incident 357000 - fixed call of inventory screen from transaction history - make it modeless
// 
//    Rev 1.17   May 24 2005 16:36:06   porteanm
// PET OPC Confirm Reprint - Call Transaction History Dlg as non-Modal.
// 
//    Rev 1.16   Apr 26 2005 15:22:50   porteanm
// Incident 297707 - For Non-DVOF funds with a Redemption trade, the Clawback info button should be disabled.
// 
//    Rev 1.15   Apr 01 2005 14:55:52   porteanm
// Incident 279375 - Clawback button for EO.
// 
//    Rev 1.14   Mar 23 2005 15:51:36   porteanm
// Incident # 237748 - Clawback button.
// 
//    Rev 1.13   Feb 21 2005 15:10:40   aguilaam
// PET1198_FN01: LSIF ReasonCode enhancement
// 
//    Rev 1.12   Feb 17 2005 13:16:10   aguilaam
// PET1198_FN01: LSIF Reason Code enhancement. 
// 
//    Rev 1.11   Dec 14 2004 18:01:48   hernando
// PET910 - Checks fund before setting current list item.
// 
//    Rev 1.10   Nov 26 2004 14:10:32   popescu
// PTS 10034524, fix sorting in IFDSListCtrl.; CompareDates method uses the display mask from Reg, to compare two dates.
// 
//    Rev 1.9   Aug 18 2004 16:39:10   popescu
// PTS 10033126, fixed sorting for inventory details list, although the list is not used in the dialog
// 
//    Rev 1.8   Aug 18 2004 16:36:06   popescu
// PTS 10033126, fixed sorting order issue in inventory summary dialog, by correctly implementing the 'compare' method of the IFDSListCtrl for dates and numbers
// 
//    Rev 1.7   Jun 23 2004 09:45:44   HERNANDO
// PTS10031186 - Replaced second list control.
// 
//    Rev 1.6   Jun 08 2004 14:00:44   HERNANDO
// PET1046 FN01 - Using passed in Fund and Class codes.  Enable/Disable Transaction History button appropriately.
// 
//    Rev 1.5   May 25 2004 20:12:18   HERNANDO
// PET1046 FN01 - Changed use of TotalCBFreeUnits.
// 
//    Rev 1.4   May 22 2004 16:20:12   HERNANDO
// PET1046 FN01 - Set the default fund/class.
// 
//    Rev 1.3   May 21 2004 15:35:14   HERNANDO
// PET1046 FN01 - Display the fund description.
// 
//    Rev 1.2   May 19 2004 17:50:50   HERNANDO
// PET1046 FN01 - Added LSIF/Inventory Details.
// 
//    Rev 1.1   Feb 26 2004 17:18:06   ZHANGCEL
// PET1001 - FN01 Change logic in the FillComb
// 
//    Rev 1.0   Feb 24 2004 10:21:30   ZHANGCEL
// Initial revision.
// 
//


