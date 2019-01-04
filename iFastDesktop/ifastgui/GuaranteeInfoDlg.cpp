//*****************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by International Financial Data Services
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2005 by International Financial Data Services
//
//*****************************************************************************
// ^FILE   : GuaranteeInfoDlg.cpp
// ^AUTHOR : 
// ^DATE   : 
//
// ^CLASS    : 
// ^SUBCLASS :       
//
// ^CLASS DESCRIPTION : 
//
//******************************************************************************
#include "stdafx.h"
#include "mfdstc.h"
#include "GuaranteeInfoDlg.h"
#include <ifastbp\GuaranteeInfoProcessIncludes.h>

#include <ifastbp\ContractInfoProcessIncludes.h>

#include <uibase\dstlistctrl.h>
#include <uibase\DSTGridWnd.h>
#include <uibase\ifdslistctrl.h>

#include <ifastcbo\DSTCommonFunction.hpp>
#include <ifastcbo\DSTCWorkSession.hpp>

//HllApi
#include <ifastcsi\CsiSession.h>
#include <ifastcsi\ifastcsi.h>

extern CLASS_IMPORT const I_CHAR* CMD_BPROC_CONTRACTINFO;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_ENTITY;
extern CLASS_IMPORT const I_CHAR* CMD_GUI_GUARANTEEINFO;
#include <bfproc\concretedialogcreator.hpp>
static ConcreteDialogCreator< GuaranteeInfoDlg > dlgCreator( CMD_GUI_GUARANTEEINFO );

#ifdef _DEBUG
   #define new DEBUG_NEW
   #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


namespace
{
   // trace literals
   const I_CHAR * const CLASSNAME        = I_( "GuaranteeInfoDlg" );
   const I_CHAR * const LV_GUARANTEE     = I_( "GuaranteeInfoList" );
   const I_CHAR * const LV_ACCTGUARANTEE = I_( "AcctGuaranteeInfoList" );   
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


class LVGuaranteeSummaryData : public IFDSListCtrlRowDataBase
{
public:
   virtual ~LVGuaranteeSummaryData() {}
   DString dstrContractType_;
   DString dstrPolicyYear_;
   DString dstrPolicyTerm_;
   DString dstrEffectiveDate_;
   DString dstrIssueDate_;
   DString dstrGuarStatus_;
   DString dstrMaturDate_;
   DString dstrGuarSuspect_;
   DString dstrRequiresGuarUnitAdjust_;

   virtual void update( BaseDlg* pDlg, IFDSListCtrl* pCtrl, const DString* pKey )
   {
      pDlg->getParent()->getField( pDlg, pCtrl->getContainerId(), ifds::ContractType,           dstrContractType_ );
      pDlg->getParent()->getField( pDlg, pCtrl->getContainerId(), ifds::PolicyYear,             dstrPolicyYear_ );
      pDlg->getParent()->getField( pDlg, pCtrl->getContainerId(), ifds::PolicyTerm,             dstrPolicyTerm_ );      
      pDlg->getParent()->getField( pDlg, pCtrl->getContainerId(), ifds::EffectiveDate,          dstrEffectiveDate_ );      
      pDlg->getParent()->getField( pDlg, pCtrl->getContainerId(), ifds::IssueDate,              dstrIssueDate_ );
	  pDlg->getParent()->getField( pDlg, pCtrl->getContainerId(), ifds::GuarStatus,             dstrGuarStatus_ );
	  pDlg->getParent()->getField( pDlg, pCtrl->getContainerId(), ifds::MaturDate,              dstrMaturDate_ );
	  pDlg->getParent()->getField( pDlg, pCtrl->getContainerId(), ifds::GuarSuspect,            dstrGuarSuspect_ );
	  pDlg->getParent()->getField( pDlg, pCtrl->getContainerId(), ifds::RequiresGuarUnitAdjust, dstrRequiresGuarUnitAdjust_ );
   }
};


class LVGuaranteeSummaryAdapter : public IFDSListCtrlAdapter< LVGuaranteeSummaryData >
{
public:
   // required overrides
   virtual int compare( IFDSListBase* pCtrl, int iSortColumn, bool bAscending, RowData* pData1, RowData* pData2, LPARAM lParam1, LPARAM lParam2 )
   {
      int result = 0;

      const BFFieldId* pFieldId = pCtrl->getColumnField( iSortColumn - 1 );
      if( 1 == iSortColumn ) 
	  {
         // Condition indicator column.  Sort on image index
         result = ( IFDSListBase::getColumnLVItem( lParam1, iSortColumn - 1)->iImage - 
                    IFDSListBase::getColumnLVItem( lParam2, iSortColumn - 1)->iImage );
      } 
	  else if( NULL == pFieldId ) 
	  {
         return( 1 );
      } 
      else if( *pFieldId == ifds::ContractType ) 
	  {
         result = i_strcmp( pData1->dstrContractType_.c_str(), pData2->dstrContractType_.c_str() );
      } 
	  else if( *pFieldId == ifds::PolicyYear ) 
	  {
         ///result = i_strcmp( pData1->dstrPolicyYear_.c_str(), pData2->dstrPolicyYear_.c_str() );
         double dblPolicyYear1 = DSTCommonFunctions::convertToDouble ( pData1->dstrPolicyYear_.c_str() );
		 double dblPolicyYear2 = DSTCommonFunctions::convertToDouble ( pData2->dstrPolicyYear_.c_str() );         			
		 if ( dblPolicyYear1 > dblPolicyYear2 )
			result = -1;
		 else if ( dblPolicyYear1 < dblPolicyYear2 )
			result = 1;
		// for equal result will be 0;
      } 
	  else if( *pFieldId == ifds::PolicyTerm ) 
	  {
         /////result = i_strcmp( pData1->dstrPolicyTerm_.c_str(), pData2->dstrPolicyTerm_.c_str() );

		 double dblPolicyTerm1 = DSTCommonFunctions::convertToDouble ( pData1->dstrPolicyTerm_.c_str() );
		 double dblPolicyTerm2 = DSTCommonFunctions::convertToDouble ( pData2->dstrPolicyTerm_.c_str() );         			
		 if ( dblPolicyTerm1 > dblPolicyTerm2 )
			result = -1;
		 else if ( dblPolicyTerm1 < dblPolicyTerm2 )
			result = 1;
		// for equal result will be 0;
      } 
	  else if( *pFieldId == ifds::EffectiveDate ) 
	  {         
         int dater_order = DSTCommonFunctions::CompareDates ( pData1->dstrEffectiveDate_.c_str(), 
															  pData2->dstrEffectiveDate_.c_str(),
															  BFDate::DF_DISPLAY);
         result = dater_order == DSTCommonFunctions::FIRST_EARLIER ? 1 : 
                  dater_order == DSTCommonFunctions::EQUAL ? 0 : -1;
		 // for equal, result will be 0       
      } 
      else if( *pFieldId == ifds::IssueDate ) 
	  {         
         int dater_order = DSTCommonFunctions::CompareDates ( pData1->dstrIssueDate_.c_str(), 
															  pData2->dstrIssueDate_.c_str(),
															  BFDate::DF_DISPLAY);
         result = dater_order == DSTCommonFunctions::FIRST_EARLIER ? 1 : 
                  dater_order == DSTCommonFunctions::EQUAL ? 0 : -1;
		 // for equal, result will be 0       
      }  
	  else if( *pFieldId == ifds::GuarStatus ) 
	  {
         result = i_strcmp( pData1->dstrGuarStatus_.c_str(), pData2->dstrGuarStatus_.c_str() );
      } 
      else if( *pFieldId == ifds::MaturDate ) 
	  {         
         int dater_order = DSTCommonFunctions::CompareDates ( pData1->dstrMaturDate_.c_str(), 
															  pData2->dstrMaturDate_.c_str(),
															  BFDate::DF_DISPLAY);
         result = dater_order == DSTCommonFunctions::FIRST_EARLIER ? 1 : 
                  dater_order == DSTCommonFunctions::EQUAL ? 0 : -1;
		 // for equal, result will be 0       
      }  
	  else if( *pFieldId == ifds::GuarSuspect ) 
	  {
         result = i_strcmp( pData1->dstrGuarSuspect_.c_str(), pData2->dstrGuarSuspect_.c_str() );
      } 
	  else if( *pFieldId == ifds::RequiresGuarUnitAdjust ) 
	  {
         result = i_strcmp( pData1->dstrRequiresGuarUnitAdjust_.c_str(), pData2->dstrRequiresGuarUnitAdjust_.c_str() );
      }	  

      return( bAscending ? result : -result );
   }

virtual LRESULT onGetDispInfo( IFDSListCtrl* pCtrl, RowData* pData, LV_DISPINFO* pDispInfo )
   {
      if( pDispInfo->item.mask & LVIF_TEXT )
      {
         const BFFieldId* pFieldId = pCtrl->getColumnField( pDispInfo->item.iSubItem );

         if( NULL == pFieldId ) 
		 {
            pDispInfo->item.pszText = I_( "" );
         } 
		 else if( *pFieldId == ifds::ContractType ) 
		 {
            pDispInfo->item.pszText = (I_CHAR*)pData->dstrContractType_.c_str();
         } 
		 else if( *pFieldId == ifds::PolicyYear ) 
		 {
            pDispInfo->item.pszText = (I_CHAR*)pData->dstrPolicyYear_.c_str();
         } 
		 else if( *pFieldId == ifds::PolicyTerm ) 
		 {
            pDispInfo->item.pszText = (I_CHAR*)pData->dstrPolicyTerm_.c_str();
         } 
		 else if( *pFieldId == ifds::EffectiveDate ) 
		 {
            pDispInfo->item.pszText = (I_CHAR*)pData->dstrEffectiveDate_.c_str();
         } 
		 else if( *pFieldId == ifds::IssueDate ) 
		 {
            pDispInfo->item.pszText = (I_CHAR*)pData->dstrIssueDate_.c_str();
         } 
		  else if( *pFieldId == ifds::GuarStatus ) 
		 {
            pDispInfo->item.pszText = (I_CHAR*)pData->dstrGuarStatus_.c_str();
         } 
		  else if( *pFieldId == ifds::MaturDate ) 
		 {
            pDispInfo->item.pszText = (I_CHAR*)pData->dstrMaturDate_.c_str();
         } 
		  else if( *pFieldId == ifds::GuarSuspect ) 
		 {
            pDispInfo->item.pszText = (I_CHAR*)pData->dstrGuarSuspect_.c_str();
         } 
		  else if( *pFieldId == ifds::RequiresGuarUnitAdjust ) 
		 {
            pDispInfo->item.pszText = (I_CHAR*)pData->dstrRequiresGuarUnitAdjust_.c_str();
         } 

         return( 1 );
      }
      return( 0 );
   }
};


class LVGuaranteeInfoData : public IFDSListCtrlRowDataBase
{
public:
   virtual ~LVGuaranteeInfoData() {}
   DString dstrTransType_;
   DString dstrTransactionId_;
   DString dstrTradeDate_;
   DString dstrFundCode_;
   DString dstrClassCode_;
   DString dstrBaycom_;
   DString dstrAmountInUnit_;
   DString dstrGuarAmount_;      
   DString dstrMaturityDate_;
   DString dstrGuarAmtAtMatur_;
   

   virtual void update( BaseDlg* pDlg, IFDSListCtrl* pCtrl, const DString* pKey )
   {
      pDlg->getParent()->getField( pDlg, pCtrl->getContainerId(), ifds::TransType,      dstrTransType_ );
      pDlg->getParent()->getField( pDlg, pCtrl->getContainerId(), ifds::TransactionId,  dstrTransactionId_ );
      pDlg->getParent()->getField( pDlg, pCtrl->getContainerId(), ifds::TradeDate,      dstrTradeDate_ );      
      pDlg->getParent()->getField( pDlg, pCtrl->getContainerId(), ifds::FundCode,       dstrFundCode_ );      
      pDlg->getParent()->getField( pDlg, pCtrl->getContainerId(), ifds::ClassCode,      dstrClassCode_ );
	  pDlg->getParent()->getField( pDlg, pCtrl->getContainerId(), ifds::Baycom,         dstrBaycom_ );
	  pDlg->getParent()->getField( pDlg, pCtrl->getContainerId(), ifds::AmountInUnit,   dstrAmountInUnit_ );
	  pDlg->getParent()->getField( pDlg, pCtrl->getContainerId(), ifds::GuarAmount,     dstrGuarAmount_ );	  
	  pDlg->getParent()->getField( pDlg, pCtrl->getContainerId(), ifds::MaturityDate,   dstrMaturityDate_ );
	  pDlg->getParent()->getField( pDlg, pCtrl->getContainerId(), ifds::GuarAmtAtMatur, dstrGuarAmtAtMatur_ );
   }
};


class LVGuaranteeInfoAdapter : public IFDSListCtrlAdapter< LVGuaranteeInfoData >
{
public:
   // required overrides
   virtual int compare( IFDSListBase* pCtrl, int iSortColumn, bool bAscending, RowData* pData1, RowData* pData2, LPARAM lParam1, LPARAM lParam2 )
   {
      int result = 0;

      const BFFieldId* pFieldId = pCtrl->getColumnField( iSortColumn - 1 );
      if( 1 == iSortColumn ) 
	  {
         // Condition indicator column.  Sort on image index
         result = ( IFDSListBase::getColumnLVItem( lParam1, iSortColumn - 1)->iImage - 
                    IFDSListBase::getColumnLVItem( lParam2, iSortColumn - 1)->iImage );
      } 
	  else if( NULL == pFieldId ) 
	  {
         return( 0 );
      } 
      else if( *pFieldId == ifds::TransType ) 
	  {
         result = i_strcmp( pData1->dstrTransType_.c_str(), pData2->dstrTransType_.c_str() );
      } 
	  else if( *pFieldId == ifds::TransactionId ) 
	  {         
         double dblTransactionId1 = DSTCommonFunctions::convertToDouble ( pData1->dstrTransactionId_.c_str() );
		 double dblTransactionId2 = DSTCommonFunctions::convertToDouble ( pData2->dstrTransactionId_.c_str() );         			
		 if ( dblTransactionId1 > dblTransactionId2 )
			result = 1;
		 else if ( dblTransactionId1 < dblTransactionId2 )
			result = -1;
		// for equal result will be 0;
      } 
	  else if( *pFieldId == ifds::TradeDate ) 
	  {         		 
		 int dater_order = DSTCommonFunctions::CompareDates ( pData1->dstrTradeDate_.c_str(), 
															  pData2->dstrTradeDate_.c_str(),
															  BFDate::DF_DISPLAY);
         result = dater_order == DSTCommonFunctions::FIRST_EARLIER ? 1 : 
                  dater_order == DSTCommonFunctions::EQUAL ? 0 : -1;
		 // for equal, result will be 0       
      } 
	  else if( *pFieldId == ifds::FundCode ) 
	  {         
         result = i_strcmp( pData1->dstrFundCode_.c_str(), pData2->dstrFundCode_.c_str() );         
      } 
      else if( *pFieldId == ifds::ClassCode ) 
	  {         
         result = i_strcmp( pData1->dstrClassCode_.c_str(), pData2->dstrClassCode_.c_str() );     
      }  
	  else if( *pFieldId == ifds::Baycom ) 
	  {
         result = i_strcmp( pData1->dstrBaycom_.c_str(), pData2->dstrBaycom_.c_str() );
      } 
	  else if( *pFieldId == ifds::AmountInUnit ) 
	  {         
         double dblAmountInUnit1 = DSTCommonFunctions::convertToDouble ( pData1->dstrAmountInUnit_.c_str() );
		 double dblAmountInUnit2 = DSTCommonFunctions::convertToDouble ( pData2->dstrAmountInUnit_.c_str() );         			
		 if ( dblAmountInUnit1 > dblAmountInUnit2 )
			result = 1;
		 else if ( dblAmountInUnit1 < dblAmountInUnit2 )
			result = -1;
		// for equal result will be 0;
      }  
      else if( *pFieldId == ifds::GuarAmount ) 
	  {         
         double dblAmountInUnit1 = DSTCommonFunctions::convertToDouble ( pData1->dstrGuarAmount_.c_str() );
		 double dblAmountInUnit2 = DSTCommonFunctions::convertToDouble ( pData2->dstrGuarAmount_.c_str() );         			
		 if ( dblAmountInUnit1 > dblAmountInUnit2 )
			result = 1;
		 else if ( dblAmountInUnit1 < dblAmountInUnit2 )
			result = -1;
		// for equal result will be 0;  
      }  
	  else if( *pFieldId == ifds::MaturityDate ) 
	  {
         int dater_order = DSTCommonFunctions::CompareDates ( pData1->dstrMaturityDate_.c_str(), 
															  pData2->dstrMaturityDate_.c_str(),
															  BFDate::DF_DISPLAY);
         result = dater_order == DSTCommonFunctions::FIRST_EARLIER ? 1 : 
                  dater_order == DSTCommonFunctions::EQUAL ? 0 : -1;
		 // for equal, result will be 0    
      } 
	  else if( *pFieldId == ifds::GuarAmtAtMatur ) 
	  {
         double dblGuarAmtAtMatur1 = DSTCommonFunctions::convertToDouble ( pData1->dstrGuarAmtAtMatur_.c_str() );
		 double dblGuarAmtAtMatur2 = DSTCommonFunctions::convertToDouble ( pData2->dstrGuarAmtAtMatur_.c_str() );         			
		 if ( dblGuarAmtAtMatur1 > dblGuarAmtAtMatur2 )
			result = 1;
		 else if ( dblGuarAmtAtMatur1 < dblGuarAmtAtMatur2 )
			result = -1;
		// for equal result will be 0;  
      }	  

      return( bAscending ? result : -result );
   }

virtual LRESULT onGetDispInfo( IFDSListCtrl* pCtrl, RowData* pData, LV_DISPINFO* pDispInfo )
   {
      if( pDispInfo->item.mask & LVIF_TEXT )
      {
         const BFFieldId* pFieldId = pCtrl->getColumnField( pDispInfo->item.iSubItem );

         if( NULL == pFieldId ) 
		 {
            pDispInfo->item.pszText = I_( "" );
         } 
		 else if( *pFieldId == ifds::TransType ) 
		 {
            pDispInfo->item.pszText = (I_CHAR*)pData->dstrTransType_.c_str();
         } 
		 else if( *pFieldId == ifds::TransactionId ) 
		 {
            pDispInfo->item.pszText = (I_CHAR*)pData->dstrTransactionId_.c_str();
         } 
		 else if( *pFieldId == ifds::TradeDate ) 
		 {
            pDispInfo->item.pszText = (I_CHAR*)pData->dstrTradeDate_.c_str();
         } 
		 else if( *pFieldId == ifds::FundCode ) 
		 {
            pDispInfo->item.pszText = (I_CHAR*)pData->dstrFundCode_.c_str();
         } 
		 else if( *pFieldId == ifds::ClassCode ) 
		 {
            pDispInfo->item.pszText = (I_CHAR*)pData->dstrClassCode_.c_str();
         } 
		  else if( *pFieldId == ifds::Baycom ) 
		 {
            pDispInfo->item.pszText = (I_CHAR*)pData->dstrBaycom_.c_str();
         } 
		 else if( *pFieldId == ifds::AmountInUnit ) 
		 {
            pDispInfo->item.pszText = (I_CHAR*)pData->dstrAmountInUnit_.c_str();
         } 
		 else if( *pFieldId == ifds::GuarAmount ) 
		 {
            pDispInfo->item.pszText = (I_CHAR*)pData->dstrGuarAmount_.c_str();
         } 
		  else if( *pFieldId == ifds::MaturityDate ) 
		 {
            pDispInfo->item.pszText = (I_CHAR*)pData->dstrMaturityDate_.c_str();
         } 
		  else if( *pFieldId == ifds::GuarAmtAtMatur ) 
		 {
            pDispInfo->item.pszText = (I_CHAR*)pData->dstrGuarAmtAtMatur_.c_str();
         } 

         return( 1 );
      }
      return( 0 );
   }
};

/***********************************************************************/
GuaranteeInfoDlg::GuaranteeInfoDlg( CWnd* pParent, 
									  GenericInterfaceContainer* pGIC, 
									  GenericInterface* pGIParent, 
									  const Command& rCommand )
: BaseMainDlg( GuaranteeInfoDlg::IDD, pParent, pGIC, pGIParent, rCommand, CLASSNAME )
, _count1( 0 )
, _count2( 0 )
{
   //{{AFX_DATA_INIT(GuaranteeInfoDlg)
   //}}AFX_DATA_INIT
}

/***********************************************************************/
void GuaranteeInfoDlg::DoDataExchange(CDataExchange* pDX)
{
   BaseMainDlg::DoDataExchange(pDX);

   //{{AFX_DATA_MAP(GuaranteeInfoDlg)
   //	DDX_Radio(pDX, IDC_BYPOL_YEAR_TERM, m_rbRbYearTerm);
   //}}AFX_DATA_MAP
}

/***********************************************************************/
BEGIN_MESSAGE_MAP(GuaranteeInfoDlg, BaseMainDlg)
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
SEVERITY GuaranteeInfoDlg::doInit()
{
   TRACE_METHOD( CLASSNAME, I_("doInit"));   

   getParameter( GUARANTEE::SHAREHOLD_NUMBER, m_dstrShareHoldNum );
   getParameter( GUARANTEE::ACCOUNT_NUMBER,   m_dstrAccountNumber );   
      
   return NO_CONDITION;
}

//***********************************************************************
void GuaranteeInfoDlg::OnRbContract()
{     
   const DString *pdstrKey = &(getParent()->getFirstListItemKey(this, IFASTBP_PROC::GUARANTEEINFO_LIST));   
   if( *pdstrKey != NULL_STRING )
   {
      _count2 = 0;      

      LoadListControl( IDC_LV_GUARANTEE, NULL );	  

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
void GuaranteeInfoDlg::OnRbYearTerm()
{     
   const DString *pdstrKey = &(getParent()->getFirstListItemKey(this, IFASTBP_PROC::GUARANTEEINFO_LIST));
   if( *pdstrKey != NULL_STRING )
   {
      _count1 = 0;      
      
	  LoadListControl( IDC_LV_GUARANTEE, NULL );
      	 	        
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
BOOL GuaranteeInfoDlg::OnInitDialog() 
{
   TRACE_METHOD( CLASSNAME, ONINITDIALOG );

   BaseMainDlg::OnInitDialog();

   // set standard title bar
   setTitleBar ( );

   return(TRUE);  // return TRUE unless you set the focus to a control
   // EXCEPTION: OCX Property Pages should return FALSE
}

//*****************************************************************************
void GuaranteeInfoDlg::setTitleBar ( )
{
   m_dstrShareHoldNum.stripLeading().stripLeading(I_CHAR('0')).stripTrailing();
   m_dstrAccountNumber.stripLeading(I_CHAR('0')).stripTrailing();

   SetAccount( m_dstrAccountNumber );

   DString dstrEntityName;
   dynamic_cast<DSTCWorkSession *>(getBFWorkSession())->getFirstSequenced01AccountholderEntityName( getDataGroupId(),
                                                                                                    m_dstrAccountNumber,
																									dstrEntityName );

   SetShrAcctCaption(m_dstrShareHoldNum, m_dstrAccountNumber, dstrEntityName);
}

//*****************************************************************************
void GuaranteeInfoDlg::OnPostInitDialog()
{
   TRACE_METHOD( CLASSNAME, ONPOSTINITDIALOG );
   
   // Guaranteed account total
   AddControl( CTRL_STATIC, 
	           IDC_STATIC_GUARAMTATMATUR, 
			   IFASTBP_PROC::GUARANTEE_SUMMARY_LIST, 
			   ifds::GuarAcctTotal );
  
   // Account Guarantee Summary List   
   IFDSListCtrl* ifdsListControlGuaranteeSummary = new IFDSAdaptedListCtrl< LVGuaranteeSummaryAdapter >( this, CLASSNAME, IDC_LV_ACCTGUARANTEE, 0, 0, true, true );
   AddIFDSListControl( ifdsListControlGuaranteeSummary, LV_ACCTGUARANTEE, IFASTBP_PROC::GUARANTEE_SUMMARY_LIST, ifds::GuaranteeAcctListHeading );   
   // Default the sorting column to Contract Type
   if ( NULL != ifdsListControlGuaranteeSummary )		
		ifdsListControlGuaranteeSummary->SortOnColumn( 0 );

   // Contract Guarantee Total   
   AddControl ( CTRL_STATIC, 
                IDC_STATIC_CONTR_GUARAMT, 
                CTRLFLAG_GUI_FIELD,
				IDC_LV_ACCTGUARANTEE );

   // By PolicyYear/Term OR By Contract
   CButton *pRadioButton = static_cast < CButton* > ( GetDlgItem( IDC_BYPOL_YEAR_TERM ) );   
   pRadioButton->SetCheck( 1 );

   // Guarantee Info   
   /*
   IFDSListCtrl* ifdsListControlGuaranteeInfo = 
	   new IFDSAdaptedListCtrl< LVGuaranteeInfoAdapter >( this, 
	                                                      CLASSNAME, 
														  IDC_LV_GUARANTEE, 
														  IDC_LV_ACCTGUARANTEE, 
														  0, 
														  true, 
														  true );

   
   AddIFDSListControl( ifdsListControlGuaranteeInfo, 
	                   LV_GUARANTEE, 
					   IFASTBP_PROC::GUARANTEEINFO_LIST, 
					   ifds::GuaranteeListHeading );    
   */

   // Guarantee Info
   AddListControl( CLASSNAME, 
	               IDC_LV_GUARANTEE, 
				   LV_GUARANTEE, 
				   ifds::GuaranteeListHeading,
                   IFASTBP_PROC::GUARANTEEINFO_LIST, 
				   IDC_LV_ACCTGUARANTEE, 
				   true, 
				   LISTFLAG_NOT_UPDATABLE );

   // Guarantee Details displayed based on Transaction Type 
   AddControl ( CTRL_STATIC, 
                IDC_STATIC_TRANS_TYPE_DESC, 
                CTRLFLAG_GUI_FIELD,
			    (UINT)IDC_LV_GUARANTEE );
   
   AddControl ( CTRL_STATIC, 
                IDC_STATIC_TRADE_DATE_VALUE, 
                CTRLFLAG_GUI_FIELD,
			    (UINT)IDC_LV_GUARANTEE );
   
   AddControl ( CTRL_STATIC, 
                IDC_STATIC_MATUR_DATE_VALUE, 
                CTRLFLAG_GUI_FIELD,
				(UINT)IDC_LV_GUARANTEE );

   // Redemption      
   AddGrid( CLASSNAME, 
	        IDC_GD_GUARREDDETAIL, 
			GR_GUARREDDETAIL, 
			IFASTBP_PROC::GUARANTEE_DETAIL_LIST,
            0, 
			ifds::GuaranteeRedDetailTop, 
			ifds::GuaranteeRedDetailLeft );
   DSTGridWnd * grdWnd = GetGrid( IDC_GD_GUARREDDETAIL );
   grdWnd->SetRowHeight(0,7,25);

   // Reset
   AddGrid( CLASSNAME,                            // dialogName
	        IDC_GD_GUARRESETLIST,                 // controlID
			GR_GUARRESETLIST,                     // gridName
			IFASTBP_PROC::GUARANTEE_DETAIL_LIST,  // idContainer
            0,                                    // controlGroupID
			ifds::GuarResetListHeading,           // idTopSubstitution
			ifds::NullFieldId,                    // idLeftSubstitution
			0 );                                  // gridType - list, NOT attrib                           
   grdWnd = GetGrid( IDC_GD_GUARRESETLIST );
   grdWnd->SetColWidth(1,1,150);
   grdWnd->SetColWidth(2,2,160);
   grdWnd->SetColWidth(3,3,160);
   grdWnd->SetColWidth(4,4,160);
   grdWnd->SetColWidth(5,5,160);

   //Guaranteed Amount
   AddGrid( CLASSNAME, 
	        IDC_GD_GUARGADETAIL, 
			GR_GUARGADETAIL, 
			IFASTBP_PROC::GUARANTEE_DETAIL_LIST,
            0,        // IDC_LV_TRANSACTIONS
			ifds::GuaranteeGADetailTop, 
			ifds::GuaranteeGADetailLeft );    

   // Load   
   ConnectControlToData( IDC_STATIC_GUARAMTATMATUR, true );
   LoadControl( IDC_STATIC_GUARAMTATMATUR );

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
void GuaranteeInfoDlg::AdjustControl()
{
   CWnd *StControl;

   int numGuarListItems = getParent()->getNumberOfItemsInList( this, IFASTBP_PROC::GUARANTEEINFO_LIST);
   if ( numGuarListItems > 0 )
   {
		DString dstrTransType;
		getParent()->getField(this, IFASTBP_PROC::GUARANTEEINFO_LIST, ifds::TransType, dstrTransType, false);
		dstrTransType.stripAll();

		if ( dstrTransType == I_("AF") || 
			 dstrTransType == I_("DF") || 
			 dstrTransType == I_("PW") || 
			 dstrTransType == I_("TO") )
		{
			GetDlgItem( IDC_GD_GUARREDDETAIL )->ShowWindow( SW_SHOW );
			GetDlgItem( IDC_GD_GUARGADETAIL )->ShowWindow( SW_HIDE );
			GetDlgItem( IDC_GD_GUARRESETLIST )->ShowWindow( SW_HIDE );
			GetDlgItem( IDC_STATIC_ELSE )->ShowWindow( SW_HIDE );

			ConnectControlsToData();
			LoadControls( -1L );   			
						
			// Change text to "Guarantee Reduction Details"
			StControl = GetDlgItem( IDC_STATIC_GUARACC_DETAIL ) ;
			StControl->ShowWindow( SW_SHOW );
			CString cstrGrntRedDet;
			cstrGrntRedDet.LoadString(TXT_GUARANTEE_RED_DET);
			StControl->SetWindowText(cstrGrntRedDet);
          
			GetDlgItem( IDC_STATIC_TRANS_TYPE_DESC )->ShowWindow( SW_SHOW );
			GetDlgItem( IDC_STATIC_TRADE_DATE_VALUE )->ShowWindow( SW_SHOW );
			GetDlgItem( IDC_STATIC_MATUR_DATE_VALUE )->ShowWindow( SW_SHOW ); 

			LoadGrid( IDC_GD_GUARREDDETAIL );  								            			
		}		
		else if (dstrTransType == I_("RS"))
		{
			GetDlgItem( IDC_GD_GUARREDDETAIL )->ShowWindow( SW_HIDE );
			GetDlgItem( IDC_GD_GUARGADETAIL )->ShowWindow( SW_HIDE );
			GetDlgItem( IDC_GD_GUARRESETLIST )->ShowWindow( SW_SHOW );
			GetDlgItem( IDC_STATIC_ELSE )->ShowWindow( SW_HIDE );
	
			ConnectControlsToData();
			LoadControls( -1L );   				
									
            // Change text to "Guarantee reset details"
			StControl = GetDlgItem( IDC_STATIC_GUARACC_DETAIL ) ;
			StControl->ShowWindow( SW_SHOW );
			CString cstrGrntResetDet;
			cstrGrntResetDet.LoadString(TXT_GUARANTEE_RESET_DET);  
			StControl->SetWindowText(cstrGrntResetDet);

			GetDlgItem( IDC_STATIC_TRANS_TYPE_DESC )->ShowWindow( SW_SHOW );
			GetDlgItem( IDC_STATIC_TRADE_DATE_VALUE )->ShowWindow( SW_SHOW );
			GetDlgItem( IDC_STATIC_MATUR_DATE_VALUE )->ShowWindow( SW_SHOW );

			LoadGrid( IDC_GD_GUARRESETLIST );									
		}
		else if ( dstrTransType == I_("GA") )
		{
			GetDlgItem( IDC_GD_GUARREDDETAIL )->ShowWindow( SW_HIDE );
			GetDlgItem( IDC_GD_GUARGADETAIL )->ShowWindow( SW_SHOW );
			GetDlgItem( IDC_GD_GUARRESETLIST )->ShowWindow( SW_HIDE );
			GetDlgItem( IDC_STATIC_ELSE )->ShowWindow( SW_HIDE );

			ConnectControlsToData();
			LoadControls( -1L );   
						
            // Change text to "Guarantee Reduction Details"
			StControl = GetDlgItem( IDC_STATIC_GUARACC_DETAIL ) ;
			StControl->ShowWindow( SW_SHOW );
			CString cstrGrntAdjDet;
			cstrGrntAdjDet.LoadString(TXT_GUARANTEE_ADJ_DET);
			StControl->SetWindowText(cstrGrntAdjDet); 

            GetDlgItem( IDC_STATIC_TRANS_TYPE_DESC )->ShowWindow( SW_SHOW );
			GetDlgItem( IDC_STATIC_TRADE_DATE_VALUE )->ShowWindow( SW_SHOW );
			GetDlgItem( IDC_STATIC_MATUR_DATE_VALUE )->ShowWindow( SW_SHOW );

			LoadGrid( IDC_GD_GUARGADETAIL );  
		}
		else 
		{
			GetDlgItem( IDC_GD_GUARREDDETAIL )->ShowWindow( SW_HIDE );
			GetDlgItem( IDC_GD_GUARGADETAIL )->ShowWindow( SW_HIDE );
			GetDlgItem( IDC_GD_GUARRESETLIST )->ShowWindow( SW_HIDE );		 
			GetDlgItem( IDC_STATIC_ELSE )->ShowWindow( SW_SHOW );	
			GetDlgItem( IDC_STATIC_TRANS_TYPE_DESC )->ShowWindow( SW_HIDE );
			GetDlgItem( IDC_STATIC_TRADE_DATE_VALUE )->ShowWindow( SW_HIDE );
			GetDlgItem( IDC_STATIC_MATUR_DATE_VALUE )->ShowWindow( SW_HIDE );
		}
	}
}

/*******************************************************************************************/
bool GuaranteeInfoDlg::GetDataForControl( UINT controlID,
                                           DString &strValueOut,
                                           bool bFormatted,
                                           int index ) const
{
   strValueOut = NULL_STRING;
   DString dstr;

   switch( controlID )
   {
      case IDC_STATIC_GUARAMTATMATUR:	     
         getParent()->getField( this, IFASTBP_PROC::GUARANTEE_SUMMARY_LIST, ifds::GuarAcctTotal, strValueOut, false );      
		 strValueOut.strip().stripLeading('0');
         strValueOut.formatStringUsingMask(I_("9,999,999,999,999.99"));      
         break;
      case IDC_STATIC_CONTR_GUARAMT:
		 getParent()->getField( this, IFASTBP_PROC::GUARANTEE_SUMMARY_LIST, ifds::GuarContrTotal, strValueOut, false );      
		 strValueOut.strip().stripLeading('0');
         strValueOut.formatStringUsingMask(I_("9,999,999,999,999.99"));      	
		 break;
      case IDC_STATIC_TRANS_TYPE_DESC:
		  getParent()->getField( this, IFASTBP_PROC::GUARANTEEINFO_LIST, ifds::TransType, strValueOut, true );  		  
		  break;
	  case IDC_STATIC_TRADE_DATE_VALUE:          
		  getParent()->getField( this, IFASTBP_PROC::GUARANTEEINFO_LIST, ifds::TradeDate, strValueOut );  
		  strValueOut.stripAll();
		  break;
      case IDC_STATIC_MATUR_DATE_VALUE:
         getParent()->getField( this, IFASTBP_PROC::GUARANTEEINFO_LIST, ifds::TransType, dstr, false );
         dstr.stripAll();
         if( dstr == I_("RS") )
            getParent()->getField( this, IFASTBP_PROC::GUARANTEE_DETAIL_LIST, ifds::ResetMaturDate, dstr );
         else
            getParent()->getField(this, IFASTBP_PROC::GUARANTEEINFO_LIST, ifds::MaturityDate, dstr);
         strValueOut = dstr.stripAll();
         break;            	  
      default :
         return(false);
   }    
   return(true);
}

/*******************************************************************************************/
bool GuaranteeInfoDlg::GetOverrideItemString( long lSubstituteId, 
											   const DString& ColumnKey, 
											   DString& strOut )
{
   if( lSubstituteId == ifds::GuaranteeListHeading.getId() )
   {
      if( ColumnKey == TRANSTYPE )
      {         
         getParent()->getField(this, IFASTBP_PROC::GUARANTEEINFO_LIST, ifds::TransType, strOut, false);
         strOut.stripAll();         
         return(true);
      }
      if( ColumnKey == FUND_NUMBER )
      {
         DString dstrFundCode, dstrClassCode;
         getParent()->getField( this, IFASTBP_PROC::GUARANTEEINFO_LIST, ifds::FundCode,  dstrFundCode );
         getParent()->getField( this, IFASTBP_PROC::GUARANTEEINFO_LIST, ifds::ClassCode, dstrClassCode );
         dstrFundCode.strip().upperCase();
         dstrClassCode.strip().upperCase();
         dynamic_cast<DSTCWorkSession *>(getBFWorkSession())->GetFundNumber( dstrFundCode, dstrClassCode, strOut );
         return(true);
      }
      if( ColumnKey == TRANSID )
      {         
         getParent()->getField(this, IFASTBP_PROC::GUARANTEEINFO_LIST, ifds::TransactionId, strOut, false);
         strOut.strip().stripLeading( '0' );        
         return(true);
      }
      if( ColumnKey == GUARAMTATMATUR )
      {         
         getParent()->getField(this, IFASTBP_PROC::GUARANTEEINFO_LIST, ifds::GuarAmtAtMatur , strOut, false);
         strOut.strip().stripLeading( '0' );
         strOut.formatStringUsingMask(I_("9,999,999,999,999.99"));          
         return(true);
      }
   }

   return(false);
}


//*******************************************************************************/
void GuaranteeInfoDlg::OnBtnContract() 
{
   // TODO: Add your control notification handler code here
   TRACE_METHOD( CLASSNAME, I_("OnBtnContract"));   
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_(" OnBtnContract() " ) );

   setParameter( GUARANTEE::ACCOUNT_NUMBER,   m_dstrAccountNumber);
   setParameter( GUARANTEE::SHAREHOLD_NUMBER, m_dstrShareHoldNum );
   SetMessageStatusBar( TXT_LOAD_CONTRACT );

   try
   {
      bool bModal = false;   // Default to modeless
      E_COMMANDRETURN eRtn;
      eRtn = invokeCommand( getParent(), 
		                    CMD_BPROC_CONTRACTINFO, 
							PROC_NO_TYPE, 
							bModal, 
							NULL );
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
void GuaranteeInfoDlg::OnBtnEntity() 
{
   TRACE_METHOD( CLASSNAME, I_("OnBtnEntity"));   
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_(" OnBtnEntity() " ) );

   setParameter( GUARANTEE::ACCOUNT_NUMBER, m_dstrAccountNumber);

   SetMessageStatusBar( TXT_LOAD_ENTITY );

   try
   {
      bool bModal = false;   // default is modaless
      E_COMMANDRETURN eRtn;
      eRtn = invokeCommand( getParent(), 
		                    CMD_BPROC_ENTITY, 
							PROC_NO_TYPE, 
							bModal, 
							NULL );
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
void GuaranteeInfoDlg::OnBtnMore() 
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
   }

   SetMessageStatusBar(NULL_STRING);  
}

/***********************************************************************/
void GuaranteeInfoDlg::OnBtnSegOptions() 
{
   setCsiParameter( DcCsiParameters::ACCOUNT_NUMBER, DStringA(m_dstrAccountNumber) );
   executeCsiProcess( DcCsiProcesses::GUARANTEE_TRANSACTION);  
}

/**********************************************************************************/
void GuaranteeInfoDlg::DoListItemChanged( UINT listControlID, const DString &strKey, 
                                           bool bIsNewItem , bool bIsDummyItem)
{
   TRACE_METHOD( CLASSNAME, I_("DoListItemChanged"));
   AdjustControl();
   if( listControlID == IDC_LV_ACCTGUARANTEE )
   {
      _count1 = 0;
      _count2 = 0;      

	  ////////LoadControl( IDC_STATIC_CONTR_GUARAMT );
   }     
}

/**********************************************************************************/
void GuaranteeInfoDlg::GetCellProperties( UINT ctrlId, 
                                          const DString &rowKey,
                                          const DString &colKey, 
                                          BFContainerId& idContainer, 
                                          BFFieldId &idField,
                                          DString& listItemKey, 
                                          int& nCellState, 
                                          UINT& cellCtrlType,
                                          int& nCtrlInitMode, 
                                          BFFieldId &idSubstitution,
                                          DString& comboList,
                                          DString& mask,
                                          int& nComboSortingMode,
                                          DString& dstrAllowedChar)	 
{
   // For all grids, we have the same container and all cells are read only
   idContainer = IFASTBP_PROC::GUARANTEE_DETAIL_LIST;
   nCellState  = DSTGridWnd::READ_ONLY;
   dstrAllowedChar = NULL_STRING;
   if( ctrlId == IDC_GD_GUARREDDETAIL )
   {      
      if( rowKey == BEFOREREDNAV )    // Row "Before Redemption"
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
      if( colKey == RESETMATURDATE ) idField = ifds::ResetMaturDate;
      if( colKey == RESETNAV )       idField = ifds::ResetNAV;
      if( colKey == PREVGUAR )       idField = ifds::PrevGuar;
      if( colKey == RESETGUARAMOUNT )idField = ifds::ResetGuarAmount;
      if( colKey == GUARTOT )        idField = ifds::GuarTot;	
   }
}

//******************************************************************************
bool GuaranteeInfoDlg::doRefresh( GenericInterface * rpGICaller,
								   const I_CHAR * szOriginalCommand )
{  
   TRACE_METHOD( CLASSNAME, I_("doRefresh"));
   
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

   const DString *pdstrKey1 = &(getParent()->getFirstListItemKey(this, IFASTBP_PROC::GUARANTEEINFO_LIST));

   AdjustControl();

   OnRbYearTerm();
   
   return(true);
}
//*********************************************************************************
bool GuaranteeInfoDlg::ListViewControlFilter( long lSubstituteId, const DString * )
{
   bool bRet = false;

   if( lSubstituteId == ifds::GuaranteeListHeading.getId() )
   {
      // By PolicyYear/Term OR By Contract
      CButton *pRadioButton = static_cast < CButton* > ( GetDlgItem( IDC_BYPOL_YEAR_TERM ) );         

      if( pRadioButton->GetCheck() )
      {
         DString dstrSummarySegGuarMatRecId, dstrInfoSegGuarMatRecId;
         getParent()->getField( this, IFASTBP_PROC::GUARANTEE_SUMMARY_LIST, ifds::SegGuarMatRecId, dstrSummarySegGuarMatRecId, false);        
         getParent()->getField( this, IFASTBP_PROC::GUARANTEEINFO_LIST,     ifds::SegGuarMatRecId, dstrInfoSegGuarMatRecId, false);
         
		 if( ( dstrSummarySegGuarMatRecId == dstrInfoSegGuarMatRecId ) )
         {            
            bRet = true; 
            _count1+= 1;            
         }		 
      }
      else 
      {                     
			bRet = true;
            _count2 += 1;       			            
      }      
   }
   if( lSubstituteId == ifds::GuaranteeAcctListHeading.getId() )
   {      
      bRet = true;
   }

   return(bRet);
}

//*********************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastgui/GuaranteeInfoDlg.cpp-arc  $
 * 
 *    Rev 1.35   Nov 19 2011 01:35:02   wp040143
 * P0186484/FN06 - DESKTOP - iFast Desktop (French Customizations)
 * 
 *    Rev 1.34   Jul 24 2009 12:46:04   dchatcha
 * PET 157825 - FN 13 - Dilution Allocation Enhancements, Sorting combo in grid.
 * 
 *    Rev 1.33   May 01 2006 15:01:10   porteanm
 * Incident 601725 - Guarantee Details list sorted by multiple fields, not only one. Replaced with the old style list control.
 * 
 *    Rev 1.32   Oct 13 2005 16:46:58   porteanm
 * Incident 393611 - Additional fix - sorting  ifdslistcontrol by Fund/Class.
 * 
 *    Rev 1.31   Sep 15 2005 15:13:12   popescu
 * Incident#403519 - added CLASSNAME as the fifth parameter to  BaseMainDlg constructor
 * 
 *    Rev 1.30   Sep 02 2005 12:16:42   porteanm
 * Incident 393611 - Use of ifdslistcontrol.
 * 
 *    Rev 1.29   Aug 17 2005 16:45:22   porteanm
 * Incident 351033 - Removed Contract and Guarantee, renamed Contract1 and Guarantee1 to Contract and Guarantee.
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
