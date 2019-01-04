// FreeUnitDlg.cpp : implementation file
//
#include "stdafx.h"
#ifndef IFASTGUI_H
   #include "MFDSTC.h"
#endif

#ifndef FREEUNITDLG_H
   #include "FreeUnitDlg.h"
#endif
#ifndef FREEUNITPROCESSINCLUDES_H
   #include <ifastbp\FreeUnitProcessIncludes.h>
#endif

#ifndef DSTCOMMONFUNCTION_HPP
   #include <ifastcbo\DSTCommonFunction.hpp>
#endif

#ifndef DSTCWORKSESSION_HPP
   #include <ifastcbo\DSTCWorkSession.hpp>
#endif

#ifndef INVENTORYSUMMARYPROCESSINCLUDES_H
   #include <ifastbp\InventorySummaryProcessIncludes.h>
#endif

#include <uibase\ifdslistctrl.h>
#include <uibase\dstbutton.h>

#ifndef INCLUDED_VECTOR
#define INCLUDED_VECTOR
#include <vector>
#endif

extern CLASS_IMPORT const I_CHAR* CMD_GUI_FREEUNIT;
#include <bfproc\concretedialogcreator.hpp>
static ConcreteDialogCreator< FreeUnitDlg > dlgCreator( CMD_GUI_FREEUNIT );

#ifdef _DEBUG
   #define new DEBUG_NEW
   #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

namespace CND
{  // Conditions used
   extern const long GUI_ERR_UNKNOWN_EXCEPTION;
}

extern CLASS_IMPORT const I_CHAR* CMD_BPROC_INVENTORY_SUMMARY;

namespace
{
   const I_CHAR* const CLASSNAME        = I_( "FreeUnitDlg" );
   const I_CHAR* const LV_FREEUNIT      = I_( "List View Free Units");
   const I_CHAR* const FILLFREEUNITLIST = I_( "fillFreeUnitList" );
   const I_CHAR* const YEAR             = I_( "YearDesc" );
   const I_CHAR* const PYEAR            = I_( "Previous Year" );
   const I_CHAR* const ACCNUM           = I_( "AccountNum" );
   const I_CHAR* const TOTAL            = I_( "TOTAL" );
   const I_CHAR* const FUND_NUMBER      = I_( "Baycom" );
   const I_CHAR* const UNIT_TYPE        = I_( "AmountType" );
   const I_CHAR* const RECORDTYPE_MATURED = I_( "MAT" );
   const I_CHAR* const RECORDTYPE_ID      = I_( "ID" );
   const I_CHAR* const RECORDTYPE_DETAIL  = I_( "DETAIL" );
   const I_CHAR* const CURRENCY_NAME	  = I_( "CurrencyName" );
   const I_CHAR* const RECORD_TYPE        = I_( "RecordType" );
   const I_CHAR* const RECORDTYPE_PERCENT = I_( "PFS" );
   const I_CHAR* const RECORDTYPE_FUNDCLSTOTAL = I_( "FUNDCLSTOTAL" );
}

namespace ifds
{
    extern CLASS_IMPORT const BFTextFieldId FreeUnitAcctFundGroupLevelHeadingSet;
    extern CLASS_IMPORT const BFTextFieldId PrcntFeeDipOpt;
}

// Free Unit Details List Control
class LVDetailsData : public IFDSListCtrlRowDataBase
{
public:
   virtual ~LVDetailsData() {}
   DString rxFundCode_, rxClassCode_, rxFundGroup_, RecordType_, PShipCode_, FreeYear_, YearDesc_;
   DString EligibleAmt_, EligibleUnits_, UsedAmt_, UsedUnits_, LeftAmt_, LeftUnits_;
   DString Baycom_, AmountType_, CurrencyName_;

   virtual void update( BaseDlg* pDlg, IFDSListCtrl* pCtrl, const DString* pKey )
   {
      if( pDlg->GetOverrideItemString(ifds::FreeUnitHeadingSet.getId(), I_("YearDesc"), YearDesc_ ) == false )
      {
         pDlg->getParent()->getField( pDlg, pCtrl->getContainerId(), ifds::YearDesc, YearDesc_ );
      }
      if( pDlg->GetOverrideItemString(ifds::FreeUnitHeadingSet.getId(), I_("Baycom"), Baycom_ ) == false )
      {
         pDlg->getParent()->getField( pDlg, pCtrl->getContainerId(), ifds::Baycom, Baycom_ );
      }
      if( pDlg->GetOverrideItemString(ifds::FreeUnitHeadingSet.getId(), I_("AmountType"), AmountType_ ) == false )
      {
         pDlg->getParent()->getField( pDlg, pCtrl->getContainerId(), ifds::AmountType, AmountType_ );
      }
      if( pDlg->GetOverrideItemString(ifds::FreeUnitHeadingSet.getId(), I_("CurrencyName"), CurrencyName_ ) == false )
      {
         pDlg->getParent()->getField( pDlg, pCtrl->getContainerId(), ifds::CurrencyName, CurrencyName_ );
      }
      pDlg->getParent()->getField( pDlg, pCtrl->getContainerId(), ifds::rxFundCode, rxFundCode_ );
      pDlg->getParent()->getField( pDlg, pCtrl->getContainerId(), ifds::rxClassCode, rxClassCode_ );
      pDlg->getParent()->getField( pDlg, pCtrl->getContainerId(), ifds::rxFundGroup, rxFundGroup_ );
      pDlg->getParent()->getField( pDlg, pCtrl->getContainerId(), ifds::RecordType, RecordType_ );
      pDlg->getParent()->getField( pDlg, pCtrl->getContainerId(), ifds::PShipCode, PShipCode_ );
      pDlg->getParent()->getField( pDlg, pCtrl->getContainerId(), ifds::FreeYear, FreeYear_ );
      pDlg->getParent()->getField( pDlg, pCtrl->getContainerId(), ifds::EligibleAmt, EligibleAmt_ );
      pDlg->getParent()->getField( pDlg, pCtrl->getContainerId(), ifds::EligibleUnits, EligibleUnits_ );
      pDlg->getParent()->getField( pDlg, pCtrl->getContainerId(), ifds::UsedAmt, UsedAmt_ );
      pDlg->getParent()->getField( pDlg, pCtrl->getContainerId(), ifds::UsedUnits, UsedUnits_ );
      pDlg->getParent()->getField( pDlg, pCtrl->getContainerId(), ifds::LeftAmt, LeftAmt_ );
      pDlg->getParent()->getField( pDlg, pCtrl->getContainerId(), ifds::LeftUnits, LeftUnits_ );
   }
};

class LVDetailsAdapter : public IFDSListCtrlAdapter< LVDetailsData >
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
      } else if( *pFieldId == ifds::rxFundCode ) {
         result = i_strcmp( pData1->rxFundCode_.c_str(), pData2->rxFundCode_.c_str() );
      } else if( *pFieldId == ifds::rxClassCode ) {
         result = i_strcmp( pData1->rxClassCode_.c_str(), pData2->rxClassCode_.c_str() );
      } else if( *pFieldId == ifds::rxFundGroup ) {
         result = i_strcmp( pData1->rxFundGroup_.c_str(), pData2->rxFundGroup_.c_str() );
      } else if( *pFieldId == ifds::RecordType ) {
         result = i_strcmp( pData1->RecordType_.c_str(), pData2->RecordType_.c_str() );
      } else if( *pFieldId == ifds::PShipCode ) {
         result = i_strcmp( pData1->PShipCode_.c_str(), pData2->PShipCode_.c_str() );
      } else if( *pFieldId == ifds::AmountType ) {
         result = i_strcmp( pData1->AmountType_.c_str(), pData2->AmountType_.c_str() );
      } else if( *pFieldId == ifds::FreeYear ) {
         result = i_strcmp( pData1->FreeYear_.c_str(), pData2->FreeYear_.c_str() );
      } else if( *pFieldId == ifds::YearDesc ) {
         result = i_strcmp( pData1->YearDesc_.c_str(), pData2->YearDesc_.c_str() );
      } else if( *pFieldId == ifds::EligibleAmt ) {
			double dValue1 = DSTCommonFunctions::convertToDouble ( pData1->EligibleAmt_.c_str() );
			double dValue2 = DSTCommonFunctions::convertToDouble ( pData2->EligibleAmt_.c_str() );         			
         result = dValue1 < dValue2 ? -1 : dValue1 > dValue2 ? 1 : 0;
      } else if( *pFieldId == ifds::EligibleUnits ) {
			double dValue1 = DSTCommonFunctions::convertToDouble ( pData1->EligibleUnits_.c_str() );
			double dValue2 = DSTCommonFunctions::convertToDouble ( pData2->EligibleUnits_.c_str() );         			
         result = dValue1 < dValue2 ? -1 : dValue1 > dValue2 ? 1 : 0;
      } else if( *pFieldId == ifds::UsedAmt ) {
			double dValue1 = DSTCommonFunctions::convertToDouble ( pData1->UsedAmt_.c_str() );
			double dValue2 = DSTCommonFunctions::convertToDouble ( pData2->UsedAmt_.c_str() );         			
         result = dValue1 < dValue2 ? -1 : dValue1 > dValue2 ? 1 : 0;
      } else if( *pFieldId == ifds::LeftAmt ) {
			double dValue1 = DSTCommonFunctions::convertToDouble ( pData1->LeftAmt_.c_str() );
			double dValue2 = DSTCommonFunctions::convertToDouble ( pData2->LeftAmt_.c_str() );         			
         result = dValue1 < dValue2 ? -1 : dValue1 > dValue2 ? 1 : 0;
      } else if( *pFieldId == ifds::LeftUnits ) {
			double dValue1 = DSTCommonFunctions::convertToDouble ( pData1->LeftUnits_.c_str() );
			double dValue2 = DSTCommonFunctions::convertToDouble ( pData2->LeftUnits_.c_str() );         			
         result = dValue1 < dValue2 ? -1 : dValue1 > dValue2 ? 1 : 0;
      } else if( *pFieldId == ifds::Baycom ) {
         result = i_strcmp( pData1->Baycom_.c_str(), pData2->Baycom_.c_str() );
      } else if( *pFieldId == ifds::CurrencyName ) {
         result = i_strcmp( pData1->CurrencyName_.c_str(), pData2->CurrencyName_.c_str() );
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
         } else if( *pFieldId == ifds::rxFundCode ) {
            pDispInfo->item.pszText = (I_CHAR*)pData->rxFundCode_.c_str();
         } else if( *pFieldId == ifds::rxClassCode ) {
            pDispInfo->item.pszText = (I_CHAR*)pData->rxClassCode_.c_str();
         } else if( *pFieldId == ifds::rxFundGroup ) {
            pDispInfo->item.pszText = (I_CHAR*)pData->rxFundGroup_.c_str();
         } else if( *pFieldId == ifds::RecordType ) {
            pDispInfo->item.pszText = (I_CHAR*)pData->RecordType_.c_str();
         } else if( *pFieldId == ifds::PShipCode ) {
            pDispInfo->item.pszText = (I_CHAR*)pData->PShipCode_.c_str();
         } else if( *pFieldId == ifds::FreeYear ) {
            pDispInfo->item.pszText = (I_CHAR*)pData->FreeYear_.c_str();
         } else if( *pFieldId == ifds::YearDesc ) {
            pDispInfo->item.pszText = (I_CHAR*)pData->YearDesc_.c_str();
         } else if( *pFieldId == ifds::EligibleAmt ) {
            pDispInfo->item.pszText = (I_CHAR*)pData->EligibleAmt_.c_str();
         } else if( *pFieldId == ifds::EligibleUnits ) {
            pDispInfo->item.pszText = (I_CHAR*)pData->EligibleUnits_.c_str();
         } else if( *pFieldId == ifds::UsedAmt ) {
            pDispInfo->item.pszText = (I_CHAR*)pData->UsedAmt_.c_str();
         } else if( *pFieldId == ifds::UsedUnits ) {
            pDispInfo->item.pszText = (I_CHAR*)pData->UsedUnits_.c_str();
         } else if( *pFieldId == ifds::LeftAmt ) {
            pDispInfo->item.pszText = (I_CHAR*)pData->LeftAmt_.c_str();
         } else if( *pFieldId == ifds::LeftUnits ) {
            pDispInfo->item.pszText = (I_CHAR*)pData->LeftUnits_.c_str();
         } else if( *pFieldId == ifds::Baycom ) {
            pDispInfo->item.pszText = (I_CHAR*)pData->Baycom_.c_str();
         } else if( *pFieldId == ifds::AmountType ) {
            pDispInfo->item.pszText = (I_CHAR*)pData->AmountType_.c_str();
         } else if( *pFieldId == ifds::CurrencyName ) {
            pDispInfo->item.pszText = (I_CHAR*)pData->CurrencyName_.c_str();
         } 
         return( 1 );
      }
      return( 0 );
   }
};

// Totals
class LVTotalsData : public IFDSListCtrlRowDataBase
{
public:
   virtual ~LVTotalsData() {}
   DString RecordType, EligibleAmt, EligibleUnits, UsedAmt, UsedUnits, LeftAmt, LeftUnits;

   virtual void update( BaseDlg* pDlg, IFDSListCtrl* pCtrl, const DString* pKey )
   {
      if( pDlg->GetOverrideItemString(ifds::FreeAmountHeadingSet.getId(), RECORD_TYPE, RecordType ) == false )
      {
         pDlg->getParent()->getField( pDlg, pCtrl->getContainerId(), ifds::RecordType, RecordType );
      }
      pDlg->getParent()->getField( pDlg, pCtrl->getContainerId(), ifds::EligibleAmt, EligibleAmt );
      pDlg->getParent()->getField( pDlg, pCtrl->getContainerId(), ifds::EligibleUnits, EligibleUnits );
      pDlg->getParent()->getField( pDlg, pCtrl->getContainerId(), ifds::UsedAmt, UsedAmt );
      pDlg->getParent()->getField( pDlg, pCtrl->getContainerId(), ifds::UsedUnits, UsedUnits );
      pDlg->getParent()->getField( pDlg, pCtrl->getContainerId(), ifds::LeftAmt, LeftAmt );
      pDlg->getParent()->getField( pDlg, pCtrl->getContainerId(), ifds::LeftUnits, LeftUnits );
   }
};

class LVTotalsAdapter : public IFDSListCtrlAdapter< LVTotalsData >
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
      } else if( *pFieldId == ifds::RecordType ) {
         result = i_strcmp( pData1->RecordType.c_str(), pData2->RecordType.c_str() );
      } else if( *pFieldId == ifds::EligibleAmt ) {
			double dValue1 = DSTCommonFunctions::convertToDouble ( pData1->EligibleAmt.c_str() );
			double dValue2 = DSTCommonFunctions::convertToDouble ( pData2->EligibleAmt.c_str() );         			
         result = dValue1 < dValue2 ? -1 : dValue1 > dValue2 ? 1 : 0;
      } else if( *pFieldId == ifds::EligibleUnits ) {
			double dValue1 = DSTCommonFunctions::convertToDouble ( pData1->EligibleUnits.c_str() );
			double dValue2 = DSTCommonFunctions::convertToDouble ( pData2->EligibleUnits.c_str() );         			
         result = dValue1 < dValue2 ? -1 : dValue1 > dValue2 ? 1 : 0;
      } else if( *pFieldId == ifds::UsedAmt ) {
			double dValue1 = DSTCommonFunctions::convertToDouble ( pData1->UsedAmt.c_str() );
			double dValue2 = DSTCommonFunctions::convertToDouble ( pData2->UsedAmt.c_str() );         			
         result = dValue1 < dValue2 ? -1 : dValue1 > dValue2 ? 1 : 0;
      } else if( *pFieldId == ifds::UsedUnits ) {
			double dValue1 = DSTCommonFunctions::convertToDouble ( pData1->UsedUnits.c_str() );
			double dValue2 = DSTCommonFunctions::convertToDouble ( pData2->UsedUnits.c_str() );         			
         result = dValue1 < dValue2 ? -1 : dValue1 > dValue2 ? 1 : 0;
      } else if( *pFieldId == ifds::LeftAmt ) {
			double dValue1 = DSTCommonFunctions::convertToDouble ( pData1->LeftAmt.c_str() );
			double dValue2 = DSTCommonFunctions::convertToDouble ( pData2->LeftAmt.c_str() );         			
         result = dValue1 < dValue2 ? -1 : dValue1 > dValue2 ? 1 : 0;
      } else if( *pFieldId == ifds::LeftUnits ) {
			double dValue1 = DSTCommonFunctions::convertToDouble ( pData1->LeftUnits.c_str() );
			double dValue2 = DSTCommonFunctions::convertToDouble ( pData2->LeftUnits.c_str() );         			
         result = dValue1 < dValue2 ? -1 : dValue1 > dValue2 ? 1 : 0;
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
         } else if( *pFieldId == ifds::RecordType ) {
            pDispInfo->item.pszText = (I_CHAR*)pData->RecordType.c_str();
         } else if( *pFieldId == ifds::EligibleAmt ) {
            pDispInfo->item.pszText = (I_CHAR*)pData->EligibleAmt.c_str();
         } else if( *pFieldId == ifds::EligibleUnits ) {
            pDispInfo->item.pszText = (I_CHAR*)pData->EligibleUnits.c_str();
         } else if( *pFieldId == ifds::UsedAmt ) {
            pDispInfo->item.pszText = (I_CHAR*)pData->UsedAmt.c_str();
         } else if( *pFieldId == ifds::UsedUnits ) {
            pDispInfo->item.pszText = (I_CHAR*)pData->UsedUnits.c_str();
         } else if( *pFieldId == ifds::LeftAmt ) {
            pDispInfo->item.pszText = (I_CHAR*)pData->LeftAmt.c_str();
         } else if( *pFieldId == ifds::LeftUnits ) {
            pDispInfo->item.pszText = (I_CHAR*)pData->LeftUnits.c_str();
         } 
         return( 1 );
      }
      return( 0 );
   }
};

//************************************************************************************
FreeUnitDlg::FreeUnitDlg( CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: BaseMainDlg( FreeUnitDlg::IDD, pParent, pGIC, pGIParent, rCommand, CLASSNAME ),
m_DSCFeeLevel( NULL_STRING )
{
   //{{AFX_DATA_INIT(FreeUnitDlg)
   // NOTE: the ClassWizard will add member initialization here
   //}}AFX_DATA_INIT
 //  getMore = true;
}

//************************************************************************************
void FreeUnitDlg::DoDataExchange(CDataExchange* pDX)
{
   BaseMainDlg::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(FreeUnitDlg)
//   DDX_Control(pDX, IDC_MORE, m_BtnMore);
   //}}AFX_DATA_MAP
}

//************************************************************************************
BEGIN_MESSAGE_MAP(FreeUnitDlg, BaseMainDlg)
//{{AFX_MSG_MAP(FreeUnitDlg)
ON_BN_CLICKED( IDC_MORE, OnMore )
ON_BN_CLICKED( IDC_BTN_INVENTORY_SUMMARY,OnBtnInvSummary )
ON_BN_CLICKED(IDC_RB_FUND_LEVEL, OnRbFundLevel)
ON_BN_CLICKED(IDC_RB_ACCT_LEVEL, OnRbAccountLevel)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//************************************************************************************
bool FreeUnitDlg::doRefresh( GenericInterface * /*rpGICaller*/, 
                             const I_CHAR * /*szOriginalCommand*/ )
{
   TRACE_METHOD( CLASSNAME, I_("doRefresh"));
   SetMessageStatusBar( TXT_LOAD_FREE_UNITS );
   DString tmpAccount;
   getParameter( ACCNUM, tmpAccount );
   tmpAccount.stripAll();
   if( AccountNum.compare( tmpAccount.c_str()) != 0 )
   {
      AccountNum = tmpAccount;
      GetDlgItem(IDC_MORE)->EnableWindow(getParent()->doMoreRecordsExist( this, BF::AllContainerIds ));
      getParent()->setField (this, BF::NullContainerId, LIST_FILTER, RECORDTYPE_DETAIL);
      LoadListControl( IDC_LV_FUNDA );
   }
   SetMessageStatusBar( NULL_STRING );
   return(true);
}

//************************************************************************************
void FreeUnitDlg::OnRbFundLevel()
{
    GetDlgItem(IDC_LV_FUNDA)->ShowWindow(TRUE);
    GetDlgItem(IDC_LV_AMOUNT)->ShowWindow(TRUE);
    
    GetDlgItem(IDC_LV_ACCT)->ShowWindow(FALSE);
    GetDlgItem(IDC_LV_AMOUNT_ACCT)->ShowWindow(FALSE);

    GetDlgItem(IDC_BTN_INVENTORY_SUMMARY)->EnableWindow(GetList(IDC_LV_FUNDA)->GetItemCount() > 0);

    // Totals Label
    CString cstrLabel;
    cstrLabel.LoadString(IDS_TOTALS_BY_FUND_CLASS);
    GetDlgItem(IDC_TOTAL)->SetWindowText(cstrLabel);

    //Enable more button
    GetDlgItem(IDC_MORE)->EnableWindow(getParent()->doMoreRecordsExist(this, BF::AllContainerIds));
}

//************************************************************************************
void FreeUnitDlg::OnRbAccountLevel()
{
    DString dstrPrcntFreeDipOpt;
    DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
    dstcWorkSession->getOption(ifds::PrcntFeeDipOpt, dstrPrcntFreeDipOpt, getDataGroupId());
    dstrPrcntFreeDipOpt.stripAll();

    GetDlgItem(IDC_LV_FUNDA)->ShowWindow(FALSE);
    GetDlgItem(IDC_LV_AMOUNT)->ShowWindow(FALSE);
    
    GetDlgItem(IDC_LV_ACCT)->ShowWindow(TRUE);
    GetDlgItem(IDC_LV_AMOUNT_ACCT)->ShowWindow(TRUE);

    GetDlgItem(IDC_BTN_INVENTORY_SUMMARY)->EnableWindow(dstrPrcntFreeDipOpt == I_("0") && GetList(IDC_LV_ACCT)->GetItemCount() > 0);

    // Totals Label
    CString cstrLabel;
    cstrLabel.LoadString(IDS_TOTALS);
    GetDlgItem(IDC_TOTAL)->SetWindowText(cstrLabel);

    //Disable more button
    GetDlgItem(IDC_MORE)->EnableWindow(false);
}


//************************************************************************************
void FreeUnitDlg::DoListItemChanged( UINT listControlID,
                                     const DString &strKey,
                                     bool bIsNewItem ,
                                     bool bIsDummyItem )
{
    if( listControlID == IDC_LV_FUNDA)
    {
        LoadListControl(IDC_LV_AMOUNT);
    }
    else if (listControlID == IDC_LV_ACCT)
    {
        LoadListControl(IDC_LV_AMOUNT_ACCT);
    }
}

//************************************************************************************
void FreeUnitDlg::OnMore() 
{
   // TODO: Add your control notification handler code here
   SetMessageStatusBar( TXT_LOAD_FREE_UNITS );
   CWaitCursor wait;
   DString  selectedKey = NULL_STRING;

   TRACE_METHOD( CLASSNAME, I_("OnBtnMore") );

   selectedKey = getParent()->getCurrentListItemKey( this, IFASTBP_PROC::FREEUNIT_LIST );
   if (getParent()->performSearch( this, BF::AllContainerIds, SEARCH_NEXT_BLOCK ) <= WARNING ) 
   {
      getParent()->setField (this, BF::NullContainerId, LIST_FILTER, RECORDTYPE_DETAIL);
      LoadListControl(IDC_LV_FUNDA); 
   }

   GetDlgItem(IDC_MORE)->EnableWindow(getParent()->doMoreRecordsExist( this, BF::AllContainerIds ));
   getParent()->setCurrentListItem( this, IFASTBP_PROC::FREEUNIT_LIST, selectedKey );
   SetMessageStatusBar( NULL_STRING );
}

//************************************************************************************
SEVERITY FreeUnitDlg::doInit()
{
   TRACE_METHOD( CLASSNAME, DOINIT);
   SEVERITY sevRtn = SEVERE_ERROR;
   getParameter( ACCNUM, AccountNum );
   AccountNum.stripAll();

   getParameter(FREEUNITINFOLIT::PRCNTHOLDING_LVL, m_PrcntFreeHolding);

   sevRtn = NO_CONDITION;

   return(sevRtn);
}

//************************************************************************************
BOOL FreeUnitDlg::OnInitDialog() 
{
   TRACE_METHOD( CLASSNAME, ONINITDIALOG );
   BaseMainDlg::OnInitDialog();

   // Standard Title display
   DString dstrShrNum;
   getParent()->getField(this, ifds::ShrNum, dstrShrNum);
   dstrShrNum.stripLeading().stripLeading(I_CHAR('0')).stripTrailing();
   SetAccount( AccountNum );
   DString dstrEntityName;
   DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
   dstcWorkSession->getFirstSequenced01AccountholderEntityName( getDataGroupId(), AccountNum,dstrEntityName );
   SetShrAcctCaption(dstrShrNum, AccountNum, dstrEntityName);

   return(TRUE);
}

//************************************************************************************
void FreeUnitDlg::OnPostInitDialog()
{
   TRACE_METHOD( CLASSNAME, ONPOSTINITDIALOG );
   
   DString dstrPrcntFreeDipOpt;
   DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
   dstcWorkSession->getOption(ifds::PrcntFeeDipOpt, dstrPrcntFreeDipOpt, getDataGroupId());
   dstrPrcntFreeDipOpt.stripAll();
 
   // Radio Buttons
   AddControl( CTRL_CHECKBOX, IDC_RB_ACCT_LEVEL, CTRLFLAG_NOT_UPDATABLE | CTRLFLAG_GUI_FIELD );
   AddControl( CTRL_CHECKBOX, IDC_RB_FUND_LEVEL, CTRLFLAG_NOT_UPDATABLE | CTRLFLAG_GUI_FIELD );

// New List controls
//   IFDSListCtrl* ifdsListControlDetails = new IFDSAdaptedListCtrl< LVDetailsAdapter >( this, CLASSNAME, IDC_LV_FUNDA, 0, LISTFLAG_NOT_UPDATABLE, true /*ShowSelAlways*/, true /*ShowConditions*/);
//   AddIFDSListControl( ifdsListControlDetails, I_("DETAILS"), IFASTBP_PROC::FREEUNIT_LIST, m_IsAccountLevel ? ifds::FreeUnitAcctLevelHeadingSet : ifds::FreeUnitHeadingSet );   
//   IFDSListCtrl* ifdsListControlTotals = new IFDSAdaptedListCtrl< LVTotalsAdapter >( this, CLASSNAME, IDC_LV_AMOUNT, IDC_LV_FUNDA, LISTFLAG_NOT_AUTO_ADD, true /*ShowSelAlways*/, true /*ShowConditions*/);
//   AddIFDSListControl( ifdsListControlTotals, I_("TOTALS"), IFASTBP_PROC::FREEAMOUNT_LIST, m_IsAccountLevel ? ifds::FreeAmountAcctLevelHeadingSet : ifds::FreeAmountHeadingSet );   

   AddListControl( CLASSNAME, IDC_LV_FUNDA, I_("FREE_UNIT_LIST"), ifds::FreeUnitHeadingSet, IFASTBP_PROC::FREEUNIT_LIST, 0, true, 
                   CTRLFLAG_NOT_UPDATABLE);
   AddListControl( CLASSNAME, IDC_LV_ACCT, I_("FREE_UNIT_LIST_ACCT"), dstrPrcntFreeDipOpt == I_("1") ? ifds::FreeUnitAcctFundGroupLevelHeadingSet : ifds::FreeUnitAcctLevelHeadingSet, IFASTBP_PROC::FREEUNIT_ACCT_LIST, 0, true, 
                   CTRLFLAG_NOT_UPDATABLE);

   
   AddListControl( CLASSNAME, IDC_LV_AMOUNT, I_("FREE_AMOUNT_LIST"), ifds::FreeAmountHeadingSet, IFASTBP_PROC::FREEAMOUNT_LIST, 
                   IDC_LV_FUNDA, true, LISTFLAG_NOT_AUTO_ADD);
   AddListControl( CLASSNAME, IDC_LV_AMOUNT_ACCT, I_("FREE_AMOUNT_LIST_ACCT"), ifds::FreeAmountAcctLevelHeadingSet, IFASTBP_PROC::FREEAMOUNT_ACCT_LIST, 
                   IDC_LV_ACCT, true, LISTFLAG_NOT_AUTO_ADD);

   getParent()->setField (this, BF::NullContainerId, LIST_FILTER, RECORDTYPE_DETAIL);
   ShowWindow( SW_SHOW );

   // Set and Disable Radio buttons
   getParent()->getField(this, IFASTBP_PROC::MFACCOUNT_CBO, ifds::DSCFeeLevel, m_DSCFeeLevel, false);
   
   if (dstrPrcntFreeDipOpt.stripAll() == I_("1"))
   {
       bool enableAcctRB = false, 
            enableFundRB = false;

       //Radio buttons based on m_PrcntFreeHolding
       if (m_PrcntFreeHolding == PERCENT_FREE_LVL::ONLY_FUND_GROUP) //Account
       {
           LoadListControl(IDC_LV_ACCT);

           ((CButton* )GetDlgItem(IDC_RB_ACCT_LEVEL))->SetCheck(1);
           OnRbAccountLevel();
           enableAcctRB = true;
       }
       else if (m_PrcntFreeHolding == PERCENT_FREE_LVL::ONLY_FUND)
       {
           LoadListControl(IDC_LV_FUNDA);

           ((CButton* )GetDlgItem(IDC_RB_FUND_LEVEL))->SetCheck(1);
           OnRbFundLevel();
           enableFundRB = true;
       }
       else if (m_PrcntFreeHolding == PERCENT_FREE_LVL::FUND_AND_FNDGRP)
       {
           LoadListControl(IDC_LV_FUNDA);
           LoadListControl(IDC_LV_ACCT);

           ((CButton* )GetDlgItem(IDC_RB_ACCT_LEVEL))->SetCheck(1);
           OnRbAccountLevel();
           enableAcctRB = true;
           enableFundRB = true;
       }

       GetDlgItem(IDC_RB_FUND_LEVEL)->EnableWindow(enableFundRB);
       GetDlgItem(IDC_RB_ACCT_LEVEL)->EnableWindow(enableAcctRB);
   }
   else
   {
       //Radio buttons based on m_DSCFeeLevel
       if (m_DSCFeeLevel.stripAll() == I_("1"))
       {
           LoadListControl(IDC_LV_ACCT);

           ((CButton* )GetDlgItem(IDC_RB_ACCT_LEVEL))->SetCheck(1);
           OnRbAccountLevel();
       }
       else
       {
           LoadListControl(IDC_LV_FUNDA);

           ((CButton* )GetDlgItem(IDC_RB_FUND_LEVEL))->SetCheck(1);
           OnRbFundLevel();
       }

       GetDlgItem( IDC_RB_FUND_LEVEL )->EnableWindow( FALSE );
       GetDlgItem( IDC_RB_ACCT_LEVEL )->EnableWindow( FALSE );
   }
}

//************************************************************************************
bool FreeUnitDlg::GetOverrideItemString( long lSubstituteId, 
										 const DString &ColumnKey, 
										 DString &strOut )
{
   if( lSubstituteId == ifds::FreeUnitHeadingSet.getId() || lSubstituteId == ifds::FreeUnitAcctLevelHeadingSet.getId() )
   {
       BFContainerId containerId;

      if (lSubstituteId == ifds::FreeUnitHeadingSet.getId())
          containerId = IFASTBP_PROC::FREEUNIT_LIST;
      else 
          containerId = IFASTBP_PROC::FREEUNIT_ACCT_LIST;

      if( ColumnKey == YEAR )
      {
         DString temp, dstrRecordType;
         getParent()->getField( this, containerId, ifds::YearDesc, temp );
         getParent()->getField( this, containerId, ifds::RecordType, dstrRecordType, false );
         dstrRecordType.strip().upperCase();
         temp.strip();
         if( dstrRecordType.compare( RECORDTYPE_MATURED ) != 0 && dstrRecordType.compare( RECORDTYPE_ID ) != 0 )
         {
            if( temp.compare( PYEAR ) == 0 )
            {
               CString cstrPrevious;
               cstrPrevious.LoadString( IDS_PREVIOUS );
               strOut = DString( cstrPrevious );
            }
            else
            {
               CString cstrCurrent;
               cstrCurrent.LoadString( IDS_CURRENT );
               strOut = DString( cstrCurrent );
            }
         }
         else
         {
            strOut = NULL_STRING;
         }
         return(true);
      }
      else if( ColumnKey == FUND_NUMBER )
      {
         DString dstrFundCode, dstrClassCode;
         getParent()->getField( this, containerId, ifds::rxFundCode, dstrFundCode );
         getParent()->getField( this, containerId, ifds::rxClassCode, dstrClassCode );
         dstrFundCode.strip().upperCase();
         dstrClassCode.strip().upperCase();
         dynamic_cast<DSTCWorkSession *>(getBFWorkSession())->GetFundNumber ( dstrFundCode, dstrClassCode, strOut );
         return(true);
      }
      else if( ColumnKey == UNIT_TYPE )
      {
         DString dstrAmountType, dstrRecordType, dstrAmountTypeDesc;
         getParent()->getField( this, containerId, ifds::AmountType, dstrAmountType, false );
         getParent()->getField( this, containerId, ifds::AmountType, dstrAmountTypeDesc, true );
         getParent()->getField( this, containerId, ifds::RecordType, dstrRecordType, false );
         dstrAmountType.strip().upperCase();
         dstrRecordType.strip().upperCase();
         if( dstrRecordType.compare( RECORDTYPE_MATURED ) == 0 )
         {
            CString cstrMature;
            cstrMature.LoadString( IDS_MATURE );
            strOut = DString( cstrMature );
         }
         else if( dstrRecordType.compare( RECORDTYPE_ID ) == 0 )
         {
            CString cstrID;
            cstrID.LoadString( IDS_ID );
            strOut = DString( cstrID );
         }
         else if( dstrRecordType.compare( RECORDTYPE_DETAIL ) == 0 )
         {
            if( dstrAmountType.compare( I_("S") ) == 0 )
            {
               CString cstrPercentFree;
               cstrPercentFree.LoadString( IDS_PERCENT_FREE );
               strOut = DString( cstrPercentFree );
            }
            else
            {
               strOut = dstrAmountTypeDesc;
            }
         }
         return(true);
      }
   }
   else if( lSubstituteId == ifds::FreeAmountHeadingSet.getId() || lSubstituteId == ifds::FreeAmountAcctLevelHeadingSet.getId() )
   {
       
      BFContainerId containerId;

      if (lSubstituteId == ifds::FreeAmountHeadingSet.getId())
          containerId = IFASTBP_PROC::FREEAMOUNT_LIST;
      else 
          containerId = IFASTBP_PROC::FREEAMOUNT_ACCT_LIST;

      if( ColumnKey == RECORD_TYPE )
      {
         DString dstrRecordType;
         getParent()->getField( this, containerId, ifds::RecordType, dstrRecordType, false );
         dstrRecordType.strip().upperCase();
         if( dstrRecordType.compare( RECORDTYPE_MATURED ) == 0 )
         {
            CString cstrMature;
            cstrMature.LoadString( IDS_MATURE );
            strOut = DString( cstrMature );
         }
         else if( dstrRecordType.compare( RECORDTYPE_ID ) == 0 )
         {
            CString cstrID;
            cstrID.LoadString( IDS_ID );
            strOut = DString( cstrID );
         }
         else if( dstrRecordType.compare( RECORDTYPE_PERCENT ) == 0 )
         {
            CString cstrPercentFree;
            cstrPercentFree.LoadString( IDS_PERCENT_FREE );
            strOut = DString( cstrPercentFree );
         }
         else if( dstrRecordType.compare( RECORDTYPE_FUNDCLSTOTAL ) == 0 )
         {
            CString cstrFundClassTotal;
            cstrFundClassTotal.LoadString( IDS_FUND_CLASS_TOTAL );
            strOut = DString( cstrFundClassTotal );
         }
         return(true);
      }
   }

   return(false);
}

//************************************************************************************
bool FreeUnitDlg::ListViewControlFilter( long lSubstituteId, const DString * )
{
   bool bRet = true;

   if( lSubstituteId == ifds::FreeAmountHeadingSet.getId() || lSubstituteId == ifds::FreeAmountAcctLevelHeadingSet.getId() )
   {
      bRet = false;
      BFContainerId containerId;

      if (lSubstituteId == ifds::FreeAmountHeadingSet.getId())
          containerId = IFASTBP_PROC::FREEAMOUNT_LIST;
      else if (lSubstituteId == ifds::FreeAmountAcctLevelHeadingSet.getId())
          containerId = IFASTBP_PROC::FREEAMOUNT_ACCT_LIST;

      bool applyFundGroupFilter = m_PrcntFreeHolding == I_("1");
      DString dstrRecordType;
      getParent()->getField( this, containerId, ifds::RecordType, dstrRecordType);
      dstrRecordType.strip().upperCase();

      if( dstrRecordType.compare( RECORDTYPE_MATURED ) == 0 || 
            dstrRecordType.compare( RECORDTYPE_ID ) == 0 ||
		      dstrRecordType.compare( RECORDTYPE_PERCENT ) == 0 ||
            dstrRecordType.compare( RECORDTYPE_FUNDCLSTOTAL ) == 0
	      ) 
	   {
         bRet = true;

         if (lSubstituteId == ifds::FreeAmountAcctLevelHeadingSet.getId() &&
             applyFundGroupFilter)
         {
             DString selectedFundGroup, dstrRxFundGroup;
             getParent()->getField(this, IFASTBP_PROC::FREEUNIT_ACCT_LIST, ifds::rxFundGroup, selectedFundGroup);
             getParent()->getField(this, IFASTBP_PROC::FREEAMOUNT_ACCT_LIST, ifds::rxFundGroup, dstrRxFundGroup);
             bRet = dstrRxFundGroup.strip().upperCase() == selectedFundGroup.strip().upperCase();
         }
	   }
   }
   else if (lSubstituteId == ifds::FreeUnitAcctFundGroupLevelHeadingSet.getId() ||
            lSubstituteId == ifds::FreeUnitHeadingSet.getId() ||
            lSubstituteId == ifds::FreeUnitAcctLevelHeadingSet.getId())
   {
       bRet = false;

       BFContainerId containerId;

       if (lSubstituteId == ifds::FreeUnitAcctFundGroupLevelHeadingSet.getId() ||
           lSubstituteId == ifds::FreeUnitAcctLevelHeadingSet.getId())
           containerId = IFASTBP_PROC::FREEUNIT_ACCT_LIST;
       else if (lSubstituteId == ifds::FreeUnitHeadingSet.getId())
           containerId = IFASTBP_PROC::FREEUNIT_LIST;

       DString dstrRecordType, dstrAmountType;
       getParent()->getField(this, containerId, ifds::RecordType, dstrRecordType);
       getParent()->getField(this, containerId, ifds::AmountType, dstrAmountType, false);
       dstrRecordType.strip().upperCase();
       dstrAmountType.strip().upperCase();

       if (lSubstituteId == ifds::FreeUnitAcctFundGroupLevelHeadingSet.getId() &&
           dstrAmountType == I_("D"))
       {
           bRet = true;
       }
       else if (lSubstituteId == ifds::FreeUnitAcctLevelHeadingSet.getId())
       {
           bRet = true;
       }
       else if (lSubstituteId == ifds::FreeUnitHeadingSet.getId())
       {
           bRet = true;
       }
   }

   return(bRet);
}

//******************************************************************************

void FreeUnitDlg::OnBtnInvSummary() 
{
  MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OnBtnInvSummary" ) );

   try
   {
        E_COMMANDRETURN eRtn = CMD_CANCEL;
		CWaitCursor wait; 
		SetMessageStatusBar( TXT_LOAD_INVENTORY );

        int listId = static_cast<CButton*>(GetDlgItem(IDC_RB_FUND_LEVEL))->GetCheck() ? IDC_LV_FUNDA:IDC_LV_ACCT;
        BFContainerId containerId;

        if (static_cast<CButton*>(GetDlgItem(IDC_RB_FUND_LEVEL))->GetCheck())
            containerId = IFASTBP_PROC::FREEUNIT_LIST;
        else 
            containerId = IFASTBP_PROC::FREEUNIT_ACCT_LIST;
        
		if (GetList(listId)->GetItemCount() > 0)
	    {	   
			DString dstrFundCode, dstrClassCode;
			getParent()->getField( this, containerId, ifds::rxFundCode, dstrFundCode );
			getParent()->getField( this, containerId, ifds::rxClassCode, dstrClassCode );
			dstrFundCode.strip().upperCase();
			dstrClassCode.strip().upperCase();
			setParameter( INV_SUMMARY::ACCOUNT_NUM, AccountNum );
			setParameter( INV_SUMMARY::FUND_CODE, dstrFundCode );
            setParameter( INV_SUMMARY::CLASS_CODE, dstrClassCode );

			eRtn = invokeCommand( getParent(), CMD_BPROC_INVENTORY_SUMMARY, PROC_NO_TYPE, true, NULL );			
			SetMessageStatusBar( NULL_STRING );
			
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
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/FreeUnitDlg.cpp-arc  $
 * 
 *    Rev 1.24   Oct 05 2005 12:47:08   porteanm
 * Incident 421401 - Extra check for the case when 0 Total records are returned without any Detail record.
 * 
 *    Rev 1.23   Sep 15 2005 15:12:24   popescu
 * Incident#403519 - added CLASSNAME as the fifth parameter to  BaseMainDlg constructor
 * 
 *    Rev 1.22   Jun 08 2005 16:46:06   hernando
 * Incident 328781 - Fixed numerical column sorting.  Replaced list with old list control.
 * 
 *    Rev 1.21   May 15 2005 18:16:54   hernando
 * PET1024 FN10 - Replaced description; existed before the enhancement.
 * 
 *    Rev 1.20   May 05 2005 09:54:10   hernando
 * PET1024 FN10 - Override strings for new heading sub sets/fields.
 * 
 *    Rev 1.19   May 04 2005 13:49:48   hernando
 * PET1024 FN10 - Changed when the Totals list box gets loaded.  Fixed some ancient Status Bar display issue.
 * 
 *    Rev 1.18   May 02 2005 08:42:02   hernando
 * PET1024 FN10 - Acct Level/Fund Level DSC Enhancement.
 * 
 *    Rev 1.17   Mar 03 2004 17:22:58   ZHANGCEL
 * PET1001-FN01 -- Disable <InvSummary> button when FreeUnit list is empty
 * 
 *    Rev 1.16   Feb 26 2004 17:09:04   ZHANGCEL
 * PET1001 - FN01 : Added logic to launch Inventory Summary screen 
 * 
 *    Rev 1.15   Jan 09 2004 16:20:20   popescu
 * PTS 10025848, 
 * 1. View 19 returns an extra record with RecordType = 'FundClsTotal' ,the total of ID, Mature and Percent Free figures.
 * 2. Desktop was changed to display this record in the summary section of the screen; description as 'Fund Class Total'.
 * 
 *    Rev 1.14   Nov 10 2003 13:09:38   linmay
 * fix Format issue, and clean code
 * 
 *    Rev 1.12   Mar 21 2003 18:36:40   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.11   Mar 11 2003 15:09:32   popescu
 * Fixed some compilation errors in regards with teh latest base code changes
 * 
 *    Rev 1.10   Oct 09 2002 23:55:42   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.9   Sep 30 2002 11:01:40   PURDYECH
 * BFFieldId no longer has operator long(), so explicit getId() calls are needed in places.
 * 
 *    Rev 1.8   Jun 06 2002 15:28:36   ZHANGCEL
 * PTS 10008377: Sove the problem of the values population in "Total by Fund" section.
 * 
 *    Rev 1.7   May 23 2002 10:39:34   PURDYECH
 * BFData Implementation Verification Corrections
 * 
 *    Rev 1.6   17 Apr 2002 18:23:42   HERNANDO
 * Added 'Unit Type' column, standard Titles, support for Unit Types of 'Mature' and 'ID'.  WILL COME BACK TO REPLACE LITERALS.
 * 
 *    Rev 1.5   27 Mar 2002 20:01:08   PURDYECH
 * Process/WindowFactory overhaul
 * 
 *    Rev 1.4   03 May 2001 14:07:34   SMITHDAV
 * Session management restructuring.
 * 
 *    Rev 1.3   Jul 26 2000 11:14:56   ZHANGCEL
 * Deal with the fund code problem
 * 
 *    Rev 1.2   Jul 07 2000 13:44:56   ZHANGCEL
 * Baycom broblem for C2
 * 
 *    Rev 1.1   Apr 03 2000 14:12:18   DT24433
 * removed unused headers, added revision block
 * 
 */
