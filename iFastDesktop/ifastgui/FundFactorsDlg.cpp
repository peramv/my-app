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
//    Copyright 1999 by DST Systems, Inc.
//
//******************************************************************************
//
// ^FILE   : FundFactorsDlg.cpp
// ^AUTHOR : Amelia Aguila
// ^DATE   : 20/11/2003
//
// ----------------------------------------------------------
//
// ^CLASS    : FundFactorsDlg
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :  This is the code for a list selection dialog

//******************************************************************************
#include "stdafx.h"


#ifndef IFASTGUI_H
   #include "MFDSTC.h"
#endif

#include <bfproc\AbstractProcess.hpp>
#include "FundFactorsDlg.h"
#include "ifastbp\fundinfoprocessincludes.h"
#include <ifastdataimpl\dse_dstc0313_vwrepeat_record.hpp>
#include <ifastcbo\DSTCommonFunction.hpp>

extern CLASS_IMPORT const I_CHAR* CMD_GUI_FUND_FACTORS;

#include <bfproc\concretedialogcreator.hpp>
static ConcreteDialogCreator< FundFactorsDlg > dlgCreator( CMD_GUI_FUND_FACTORS );

#ifdef _DEBUG
   #define new DEBUG_NEW
   #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

namespace
{
   const I_CHAR * const CLASSNAME = I_( "FundFactorsDlg" );
   const I_CHAR *LV_UNITFACTORS = I_( "Unit Factors" );
}

namespace CND
{  // Conditions used
   extern const long GUI_ERR_UNKNOWN_EXCEPTION;
}


class LVUnitFactorData : public IFDSListCtrlRowDataBase
{
public:
   virtual ~LVUnitFactorData() {}
   DString dstrUnitFactor_;
   DString dstrFactorRate_;

   virtual void update( BaseDlg* pDlg, IFDSListCtrl* pCtrl, const DString* pKey )
   {
      pDlg->getParent()->getField( pDlg, pCtrl->getContainerId(), ifds::UnitFactor, dstrUnitFactor_ );
      pDlg->getParent()->getField( pDlg, pCtrl->getContainerId(), ifds::FactorRate, dstrFactorRate_ );
   }
};

class LVUnitFactorAdapter : public IFDSListCtrlAdapter< LVUnitFactorData >
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
      } else if( *pFieldId == ifds::UnitFactor ) {
         result = i_strcmp( pData1->dstrUnitFactor_.c_str(), pData2->dstrUnitFactor_.c_str() );
      } else if( *pFieldId == ifds::FactorRate ) {
         double dFactorRate1 = DSTCommonFunctions::convertToDouble( pData1->dstrFactorRate_ );
         double dFactorRate2 = DSTCommonFunctions::convertToDouble( pData2->dstrFactorRate_ );
         result = ( dFactorRate1 == dFactorRate2) ? 0 : ( dFactorRate1 < dFactorRate2 ? -1 : 1 );
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
         } else if( *pFieldId == ifds::UnitFactor ) {
            pDispInfo->item.pszText = (I_CHAR*)pData->dstrUnitFactor_.c_str();
         } else if( *pFieldId == ifds::FactorRate ) {
            pDispInfo->item.pszText = (I_CHAR*)pData->dstrFactorRate_.c_str();
         }
         return( 1 );
      }
      return( 0 );
   }
};


//*****************************************************************************
// Public methods
//*****************************************************************************
FundFactorsDlg::FundFactorsDlg( CWnd* pParent, GenericInterfaceContainer* pGIC, 
                               GenericInterface* pGIParent, const Command& rCommand )
: BaseMainDlg( FundFactorsDlg::IDD, pParent, pGIC, pGIParent, rCommand, CLASSNAME )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   //{{AFX_DATA_INIT(FundFactorsDlg)
   //}}AFX_DATA_INIT
}

//*****************************************************************************
void FundFactorsDlg::DoDataExchange( CDataExchange* pDX )
{
   BaseMainDlg::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(FundFactorsDlg)
   //}}AFX_DATA_MAP

}

//*****************************************************************************
SEVERITY FundFactorsDlg::doInit()
{
   TRACE_METHOD( CLASSNAME, DOINIT );

   return NO_CONDITION;
}

//*****************************************************************************
BEGIN_MESSAGE_MAP( FundFactorsDlg, BaseMainDlg )
//{{AFX_MSG_MAP(FundFactorsDlg)

//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//*****************************************************************************
// Message handlers
//*****************************************************************************
BOOL FundFactorsDlg::OnInitDialog() 
{
   TRACE_METHOD( CLASSNAME, ONINITDIALOG );

   BaseMainDlg::OnInitDialog();

   return(TRUE);
}

//*****************************************************************************
void FundFactorsDlg::OnPostInitDialog()
{
   TRACE_METHOD( CLASSNAME, ONPOSTINITDIALOG );

   AddControl (CTRL_STATIC, IDC_STC_CDNDIV, IFASTBP_PROC::FI_FUND_INFO_LIST, 
      ifds::CanDividend);
   AddControl (CTRL_STATIC, IDC_STC_INELIGDIV, IFASTBP_PROC::FI_FUND_INFO_LIST, 
      ifds::InelgDividend);
   AddControl (CTRL_STATIC, IDC_STC_CDNINT, IFASTBP_PROC::FI_FUND_INFO_LIST, 
      ifds::CanInterest);
   AddControl (CTRL_STATIC, IDC_STC_RETOFCAP, IFASTBP_PROC::FI_FUND_INFO_LIST, 
      ifds::ROC);
   AddControl (CTRL_STATIC, IDC_STC_FXINT, IFASTBP_PROC::FI_FUND_INFO_LIST, 
      ifds::ForeignInterest);
   AddControl (CTRL_STATIC, IDC_STC_EQUALAMT, IFASTBP_PROC::FI_FUND_INFO_LIST, 
      ifds::EqualizationAmt);
   AddControl (CTRL_STATIC, IDC_STC_PDAMT, IFASTBP_PROC::FI_FUND_INFO_LIST, 
      ifds::PaidAmt);
   AddControl (CTRL_STATIC, IDC_STC_FXAMOUNT, IFASTBP_PROC::FI_FUND_INFO_LIST, 
      ifds::ForeignDividend);
   AddControl (CTRL_STATIC, IDC_STC_TAXCAPGAINS, IFASTBP_PROC::FI_FUND_INFO_LIST, 
      ifds::TaxCapGain);
   AddControl (CTRL_STATIC, IDC_STC_FXWTHTAX, IFASTBP_PROC::FI_FUND_INFO_LIST, 
      ifds::ForeignTax);
   AddControl (CTRL_STATIC, IDC_STC_OTHINCOME, IFASTBP_PROC::FI_FUND_INFO_LIST, 
      ifds::OthIncome);
   AddControl (CTRL_STATIC, IDC_STC_REALIZEGAIN, IFASTBP_PROC::FI_FUND_INFO_LIST, 
      ifds::RealizeGain);
   AddControl (CTRL_STATIC, IDC_STC_MGMTFEE, IFASTBP_PROC::FI_FUND_INFO_LIST, 
      ifds::MgmtFee);
   AddControl (CTRL_STATIC, IDC_STC_ACCRINCOME, IFASTBP_PROC::FI_FUND_INFO_LIST, 
      ifds::AccrualIncome);
   AddControl (CTRL_STATIC, IDC_STC_TRUSTFEE, IFASTBP_PROC::FI_FUND_INFO_LIST, 
      ifds::TrusteeFee);

/*
   AddListControl(CLASSNAME, IDC_LST_FACTORS, I_("UNIT_FACTORS"), ifds::UnitFactorHeading, IFASTBP_PROC::UNIT_FACTORS_LIST );
*/
   IFDSListCtrl* pCtrl = 
      new IFDSAdaptedListCtrl< LVUnitFactorAdapter >
         ( this, CLASSNAME, IDC_LST_FACTORS, 0, LISTFLAG_NOT_UPDATABLE, true, true );
   AddIFDSListControl( pCtrl, 
                       LV_UNITFACTORS,
                       IFASTBP_PROC::UNIT_FACTORS_LIST,
                       ifds::UnitFactorHeading );

   doRefresh( this, NULL_STRING );
}


//******************************************************************************
bool FundFactorsDlg::doRefresh( GenericInterface *rpGICaller, 
   const I_CHAR *szOriginalCommand )
{ 
   TRACE_METHOD( CLASSNAME, DOREFRESH );
   ConnectControlsToData ();
   LoadControls ();
   LoadListControl( IDC_LST_FACTORS );
   SetDlgCaption();
   return true;
}

//*************************************************************************
void FundFactorsDlg::SetDlgCaption()
{
    DString FundCode; 
    getParent()->getField( this, IFASTBP_PROC::FI_FUND_INFO_LIST, 
                     ifds::rxFundCode, FundCode);
    SetCaption(I_(" ") + FundCode);
 
}

//*************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/FundFactorsDlg.cpp-arc  $
// 
//    Rev 1.3   Sep 15 2005 15:13:04   popescu
// Incident#403519 - added CLASSNAME as the fifth parameter to  BaseMainDlg constructor
// 
//    Rev 1.2   Oct 07 2004 15:10:50   HERNANDO
// PTS10034608 - Changed dialog caption.
// 
//    Rev 1.1   Sep 09 2004 11:43:40   HERNANDO
// PET1117 FN22 - WKN & ISIN Enhancement.
// 
//    Rev 1.0   Nov 20 2003 16:28:58   AGUILAAM
// Initial revision.
// 
*/

