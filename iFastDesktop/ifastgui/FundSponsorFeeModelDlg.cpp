//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by DST Canada, Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2002 by International Financial  Ltd.
//
//******************************************************************************
//
// ^FILE   : FundSponsorFeeModelDlg.h
// ^AUTHOR : 
// ^DATE   : 07/26/04
//
// ^CLASS    : FundSponsorFeeModelDlg
// ^SUBCLASS : BaseMainDlg
//
// ^CLASS DESCRIPTION : 
//
//******************************************************************************

#include "stdafx.h"
#include <assert.h>

#include "mfdstc.h"
#include "fundsponsorfeemodeldlg.h"

#include <uibase\DSTEdit.h>
#include <uibase\DSTListCtrl.h>
#include <uibase\ifdslistctrl.h>
#include <uibase\DSTComboBox.h>

#include <ifastcbo\dstcworksession.hpp>

#include <ifastbp\fundsponsorfeemodelprocess.hpp>
#include <ifastbp\fundsponsorfeemodelprocessinclude.h>
#include <ifastbp\mfcaninterprocparam.hpp>

extern CLASS_IMPORT const I_CHAR* CMD_GUI_FUNDSPONSOR_FEE_MODEL;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_FEE_MODEL;

#include <bfproc\concretedialogcreator.hpp>
static ConcreteDialogCreator< FundSponsorFeeModelDlg > dlgCreator( CMD_GUI_FUNDSPONSOR_FEE_MODEL );

#ifdef _DEBUG
   #define new DEBUG_NEW
   #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

namespace
{
   const I_CHAR * const CLASSNAME							= I_( "FundSponsorFeeModelDlg" );
   const I_CHAR * const YES									= I_( "Y" );
   const I_CHAR * const NO										= I_( "N" );

   const I_CHAR* const  LV_FUNDSPONSOR						= I_( "FundSponsor" );
   const I_CHAR* const  LV_FEE_PARAM						= I_( "FeeParam" );   
   const I_CHAR* const  LV_FEE_SCALE						= I_( "ScaleFee" );
   const I_CHAR* const  PERCENT								= I_( "Percent" );
   const I_CHAR * const FLAT									= I_( "0" );
   const I_CHAR * const PERCENTAGE							= I_( "1" );
   const I_CHAR * const SCALE									= I_( "2" );
   const I_CHAR * const TIER									= I_( "3" );
   const I_CHAR * const FEE_CODE_MANAGEMENT_FEE			= I_("18");
   const I_CHAR * const FEE_CPDE_MANAGEMENT_REBATE		= I_("95");
   const I_CHAR * const FEE_CODE_MANAGEMENT_DISCOUNT	= I_("180");


   const I_CHAR * const NUMBERS = I_("0123456789.");
	const I_CHAR * const	NOT_APPLY  =  I_("NA");
}

namespace CND
{  // Conditions used
   extern const long GUI_ERR_UNKNOWN_EXCEPTION;
}

namespace UAF
{
   extern CLASS_IMPORT I_CHAR * const FUNDSPONSOR_FEE_MODEL;
}
namespace ifds
{   
   extern CLASS_IMPORT const BFTextFieldId FeeModelCode;
   extern CLASS_IMPORT const BFTextFieldId FeeModelDesc;
   extern CLASS_IMPORT const BFTextFieldId Username;
   extern CLASS_IMPORT const BFTextFieldId ModUser;
   extern CLASS_IMPORT const BFTextFieldId SearchModelCode;
   extern CLASS_IMPORT const BFTextFieldId ChargeOption;

   extern CLASS_IMPORT const BFTextFieldId FundGroup;
   extern CLASS_IMPORT const BFTextFieldId FundGroupDesc;
   extern CLASS_IMPORT const BFTextFieldId FeeModelOption;
   extern CLASS_IMPORT const BFTextFieldId FeeCode;
   extern CLASS_IMPORT const BFTextFieldId ParamFeeType;
   extern CLASS_IMPORT const BFDecimalFieldId Rate;
   extern CLASS_IMPORT const BFTextFieldId Currency;

   extern CLASS_IMPORT const BFDateFieldId EffectiveDate;
   extern CLASS_IMPORT const BFDateFieldId StopDate;
   extern CLASS_IMPORT const BFDateFieldId ProcessDate;
   extern CLASS_IMPORT const BFDateFieldId ModDate;

   extern CLASS_IMPORT const BFDecimalFieldId ScaleRate;
   extern CLASS_IMPORT const BFDecimalFieldId UpperBound;
   extern CLASS_IMPORT const BFDecimalFieldId LowerBound;
   extern CLASS_IMPORT const BFDecimalFieldId MinFee;
   extern CLASS_IMPORT const BFDecimalFieldId MaxFee;
   extern CLASS_IMPORT const BFNumericFieldId AccountNum;

   extern CLASS_IMPORT const BFTextFieldId FeeSponsorListSet;
   extern CLASS_IMPORT const BFTextFieldId FeeParamListHeaderSet;
   extern CLASS_IMPORT const BFTextFieldId FeeScaleListSet;
   extern CLASS_IMPORT const BFTextFieldId ChangeOption;
   extern CLASS_IMPORT const BFTextFieldId AccountNumList;
   extern CLASS_IMPORT const BFNumericFieldId ShrNum;
   extern CLASS_IMPORT const BFTextFieldId CommGroup;
   extern CLASS_IMPORT const BFTextFieldId SearchModelDesc;
   extern CLASS_IMPORT const BFDecimalFieldId Level;
   extern CLASS_IMPORT const BFTextFieldId Type;
   
}

class LVFundSponsorData : public IFDSListCtrlRowDataBase
{
public:
   virtual ~LVFundSponsorData() {}
   DString FeeModelCode_;
   DString FeeModelDesc_;
   DString FundGroup_;
   DString FeeModelOption_;

   virtual void update( BaseDlg* pDlg, IFDSListCtrl* pCtrl, const DString* pKey )
   {
      pDlg->getParent()->getField( pDlg, pCtrl->getContainerId(), ifds::FeeModelCode, FeeModelCode_ );
      pDlg->getParent()->getField( pDlg, pCtrl->getContainerId(), ifds::FeeModelDesc, FeeModelDesc_ );
      pDlg->getParent()->getField( pDlg, pCtrl->getContainerId(), ifds::FundGroup, FundGroup_ );      
      pDlg->getParent()->getField( pDlg, pCtrl->getContainerId(), ifds::FeeModelOption, FeeModelOption_ );    
   }
};

class LVFundSponsorAdapter : public IFDSListCtrlAdapter< LVFundSponsorData >
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
      } else if( *pFieldId == ifds::FeeModelCode ) {
         result = i_strcmp( pData1->FeeModelCode_.c_str(), pData2->FeeModelCode_.c_str() );
      } else if( *pFieldId == ifds::FeeModelDesc ) {
         result = i_strcmp( pData1->FeeModelDesc_.c_str(), pData2->FeeModelDesc_.c_str() );
      } else if( *pFieldId == ifds::FundGroup ) {
         result = i_strcmp( pData1->FundGroup_.c_str(), pData2->FundGroup_.c_str() );
      } else if( *pFieldId == ifds::FeeModelOption ) {
         result = i_strcmp( pData1->FeeModelOption_.c_str(), pData2->FeeModelOption_.c_str() );
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
         } else if( *pFieldId == ifds::FeeModelCode ) {
            pDispInfo->item.pszText = (I_CHAR*)pData->FeeModelCode_.c_str();
         } else if( *pFieldId == ifds::FeeModelDesc ) {
            pDispInfo->item.pszText = (I_CHAR*)pData->FeeModelDesc_.c_str();
         } else if( *pFieldId == ifds::FundGroup ) {
            pDispInfo->item.pszText = (I_CHAR*)pData->FundGroup_.c_str();
         } else if( *pFieldId == ifds::FeeModelOption ) {
            pDispInfo->item.pszText = (I_CHAR*)pData->FeeModelOption_.c_str();
         } 

         return( 1 );
      }
      return( 0 );
   }
};


class LVFeeScaleData : public IFDSListCtrlRowDataBase
{
public:
   virtual ~LVFeeScaleData() {}
   DString Level_;
   DString LowerBound_;
   DString UpperBound_;
   DString Rate_;
   DString Type_;

   virtual void update( BaseDlg* pDlg, IFDSListCtrl* pCtrl, const DString* pKey )
   {
      pDlg->getParent()->getField( pDlg, pCtrl->getContainerId(), ifds::Level, Level_ );
      pDlg->getParent()->getField( pDlg, pCtrl->getContainerId(), ifds::LowerBound, LowerBound_ );
      pDlg->getParent()->getField( pDlg, pCtrl->getContainerId(), ifds::UpperBound, UpperBound_ );      
      pDlg->getParent()->getField( pDlg, pCtrl->getContainerId(), ifds::ScaleRate, Rate_ );
      //pDlg->getParent()->getField( pDlg, pCtrl->getContainerId(), ifds::Type, Type_ );      
   }
};

class LVFeeScaleAdapter : public IFDSListCtrlAdapter< LVFeeScaleData >
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
      } else if( *pFieldId == ifds::Level ) {
         result = i_strcmp( pData1->Level_.c_str(), pData2->Level_.c_str() );
      } else if( *pFieldId == ifds::LowerBound ) {
         result = i_strcmp( pData1->LowerBound_.c_str(), pData2->LowerBound_.c_str() );
      } else if( *pFieldId == ifds::UpperBound ) {
         result = i_strcmp( pData1->UpperBound_.c_str(), pData2->UpperBound_.c_str() );
      } else if( *pFieldId == ifds::ScaleRate ) {
         result = i_strcmp( pData1->Rate_.c_str(), pData2->Rate_.c_str() );
      } else if( *pFieldId == ifds::Type ) {
         //result = i_strcmp( pData1->Type_.c_str(), pData2->Type_.c_str() );
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
         } else if( *pFieldId == ifds::Level ) {
            pDispInfo->item.pszText = (I_CHAR*)pData->Level_.c_str();
         } else if( *pFieldId == ifds::LowerBound ) {
            pDispInfo->item.pszText = (I_CHAR*)pData->LowerBound_.c_str();
         } else if( *pFieldId == ifds::UpperBound ) {
            pDispInfo->item.pszText = (I_CHAR*)pData->UpperBound_.c_str();
         } else if( *pFieldId == ifds::ScaleRate ) {
            pDispInfo->item.pszText = (I_CHAR*)pData->Rate_.c_str();
         } else if( *pFieldId == ifds::Type ) {
            pDispInfo->item.pszText = I_("Percent");//(I_CHAR*)pData->Type_.c_str();
         } 
         return( 1 );
      }
      return( 0 );
   }
};

//******************************************************************************

FundSponsorFeeModelDlg::FundSponsorFeeModelDlg( CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: BaseMainDlg( FundSponsorFeeModelDlg::IDD, pParent, pGIC, pGIParent, rCommand, CLASSNAME )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );

   //{{AFX_DATA_INIT(FundSponsorFeeModelDlg)
   // NOTE: the ClassWizard will add member initialization here
   //}}AFX_DATA_INIT
}

//******************************************************************************
FundSponsorFeeModelDlg::~FundSponsorFeeModelDlg()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}
//******************************************************************************

void FundSponsorFeeModelDlg::DoDataExchange(CDataExchange* pDX)
{
   BaseMainDlg::DoDataExchange( pDX );
   //{{AFX_DATA_MAP(FundSponsorFeeModelDlg)
   // NOTE: the ClassWizard will add DDX and DDV calls here
   //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(FundSponsorFeeModelDlg, BaseMainDlg)
//{{AFX_MSG_MAP(FundSponsorFeeModelDlg)
ON_BN_CLICKED(IDC_RESET, OnBtnReset)
ON_BN_CLICKED(IDC_BTN_MORE_FUNDSPONSOR, OnBtnFundSponsorMore)
ON_BN_CLICKED(IDC_ADD_FUND_APONSOR, OnBtnAddFundSponsor)
ON_BN_CLICKED(IDC_BTN_DEL_FUNDSPONSOR, OnBtnDelFundSponsor)
ON_BN_CLICKED(IDC_BTN_MORE_FEE_PARAM, OnBtnFeeParamMore)
ON_BN_CLICKED(IDC_ADD_FEE_PARAM, OnBtnAddFeeParam)
ON_BN_CLICKED(IDC_BTN_DEL_FEE_PARAM, OnBtnDelFeeParam)
ON_BN_CLICKED(IDC_ADD_FEE_SCALE, OnBtnAddScale)
ON_BN_CLICKED(IDC_BTN_DEL_FEE_SCALE, OnBtnDelScale)
ON_BN_CLICKED(IDC__ADMIN, OnBtnAdmDates)
ON_BN_CLICKED(IDC_RD_ACCOUNT, OnRbAccount)
ON_BN_CLICKED(IDC_RD_SHAREHOLDER, OnRbShareholder)
ON_CBN_SELCHANGE (IDC_CMB_ACCOUNT, OnSelchangeCmbAccountNum)
ON_MESSAGE(UM_OPENFEEMODELDLG, OpenFeeModelDlg)
ON_EN_KILLFOCUS(IDC_EDT_SEARCH_MODEL_CODE, OnKillfocusSearchModelCode)
//}}AFX_MSG_MAP

END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// FundSponsorFeeModelDlg message handlers


//******************************************************************************
SEVERITY FundSponsorFeeModelDlg::doInit()
{
   getParameter (FUNDSPONSORFEEMODEL::FROM_SCR, m_fromScr);
   getParameter (FUNDSPONSORFEEMODEL::SEARCHTYPE, m_dstrSearchType);
   getParameter (FUNDSPONSORFEEMODEL::ACCOUNTNUM, m_AcctNum);
   getParameter (FUNDSPONSORFEEMODEL::FEE_MODEL_CODE, m_dstrFeeModelCode);
   getParameter (FUNDSPONSORFEEMODEL::FUND_SPONSOR_CODE, m_dstrFundSponsorCode);
   return NO_CONDITION;
}

//******************************************************************************
void FundSponsorFeeModelDlg::addControls( )
{
   TRACE_METHOD( CLASSNAME, I_( "addControls" ) );

//   AddListControl( CLASSNAME, IDC_LIST_FUND_SPONSOR, LV_FUNDSPONSOR, ifds::FeeSponsorListSet, 
//                   IFASTBP_PROC::FUNDSPONSOR_FEE_MODEL_LIST);
   IFDSListCtrl* pFundSponsorListCtrl = 
      new IFDSAdaptedListCtrl< LVFundSponsorAdapter >(this, CLASSNAME, 
      IDC_LIST_FUND_SPONSOR, 0, 0, true, true);

   AddIFDSListControl ( pFundSponsorListCtrl, LV_FUNDSPONSOR, 
                        IFASTBP_PROC::FUNDSPONSOR_FEE_MODEL_LIST, ifds::FeeSponsorListSet);
   AddListControl ( CLASSNAME,IDC_LIST_FEE_PARAM, LV_FEE_PARAM, ifds::FeeParamListHeaderSet, 
                    IFASTBP_PROC::FUNDSPONSOR_FEE_LIST, IDC_LIST_FUND_SPONSOR, true, LISTFLAG_NOT_AUTO_ADD);
//   AddListControl( CLASSNAME,IDC_LIST_FEE_SCALE,     LV_FEE_SCALE,     ifds::FeeScaleListSet,           IFASTBP_PROC::FEE_SCALE_LIST, 
//                   IDC_LIST_FEE_PARAM, true, LISTFLAG_NOT_AUTO_ADD );

   IFDSListCtrl* pFeeScaleListCtrl = 
      new IFDSAdaptedListCtrl< LVFeeScaleAdapter >(this, CLASSNAME, 
      IDC_LIST_FEE_SCALE, 0, 0, true, true);

   AddIFDSListControl (pFeeScaleListCtrl, LV_FEE_SCALE, IFASTBP_PROC::FEE_SCALE_LIST, ifds::FeeScaleListSet);
   
   AddControl( CTRL_EDIT,    IDC_EDT_MODEL_CODE,   IFASTBP_PROC::FUNDSPONSOR_FEE_MODEL_LIST, 
               ifds::FeeModelCode,0,IDC_LIST_FUND_SPONSOR);
   AddControl( CTRL_STATIC,    IDC_TXT_MODELCODE_DESC,   IFASTBP_PROC::FUNDSPONSOR_FEE_MODEL_LIST, 
               ifds::FeeModelDesc,0,IDC_LIST_FUND_SPONSOR);
   AddControl( CTRL_COMBO,  IDC_CMB_SPONSOR_CODE,   IFASTBP_PROC::FUNDSPONSOR_FEE_MODEL_LIST, 
               ifds::FundGroup,CTRLFLAG_INITCOMBO_BY_SUB_LIST,IDC_LIST_FUND_SPONSOR);
   AddControl( CTRL_STATIC,  IDC_TXT_SPONSOR_DESC,   IFASTBP_PROC::FUNDSPONSOR_FEE_MODEL_LIST, 
               ifds::FundGroupDesc,0,IDC_LIST_FUND_SPONSOR);
   AddControl( CTRL_COMBO,  IDC_CMB_MODEL_OPTION,   IFASTBP_PROC::FUNDSPONSOR_FEE_MODEL_LIST, 
               ifds::FeeModelOption,CTRLFLAG_INITCOMBO_BY_SUB_LIST,IDC_LIST_FUND_SPONSOR);

   AddControl( CTRL_DATE,   IDC_DTP_EFFECTIVE,   IFASTBP_PROC::FUNDSPONSOR_FEE_LIST, 
               ifds::EffectiveDate,0,IDC_LIST_FEE_PARAM);
   AddControl( CTRL_DATE,   IDC_DTP_STOPDATE,   IFASTBP_PROC::FUNDSPONSOR_FEE_LIST, 
               ifds::StopDate,0,IDC_LIST_FEE_PARAM);
   AddControl( CTRL_COMBO,  IDC_CMB_FEE_CODE,  IFASTBP_PROC::FUNDSPONSOR_FEE_LIST,
	   ifds::FeeCode,CTRLFLAG_INITCOMBO_BY_SUB_LIST,IDC_LIST_FEE_PARAM);	
   AddControl( CTRL_COMBO,  IDC_CMB_FEE_TYPE1,  IFASTBP_PROC::FUNDSPONSOR_FEE_LIST,
	   ifds::ParamFeeType,CTRLFLAG_INITCOMBO_BY_SUB_LIST,IDC_LIST_FEE_PARAM);	
   AddControl( CTRL_COMBO,  IDC_CMB_CHARGE_OPTION,  IFASTBP_PROC::FUNDSPONSOR_FEE_LIST,
	   ifds::ChargeOption,CTRLFLAG_INITCOMBO_BY_SUB_LIST,IDC_LIST_FEE_PARAM);	
   AddControl( CTRL_EDIT,    IDC_EDT_VALUE1,   IFASTBP_PROC::FUNDSPONSOR_FEE_LIST, 
               ifds::Rate,0,IDC_LIST_FEE_PARAM);
   AddControl( CTRL_COMBO,    IDC_CMB_CURRENCY,   IFASTBP_PROC::FUNDSPONSOR_FEE_LIST, 
               ifds::Currency,CTRLFLAG_INITCOMBO_BY_SUB_LIST,IDC_LIST_FEE_PARAM);
   AddControl( CTRL_EDIT,    IDC_EDT_FEE_MAX,   IFASTBP_PROC::FUNDSPONSOR_FEE_LIST, 
               ifds::MaxFee,0,IDC_LIST_FEE_PARAM);
   AddControl( CTRL_EDIT,    IDC_EDT_FEE_MIN,   IFASTBP_PROC::FUNDSPONSOR_FEE_LIST, 
               ifds::MinFee,0,IDC_LIST_FEE_PARAM);

   AddControl( CTRL_EDIT,    IDC_EDT_LOWER_BOUND,   IFASTBP_PROC::FEE_SCALE_LIST, 
               ifds::LowerBound,0,IDC_LIST_FEE_SCALE);
   AddControl( CTRL_EDIT,    IDC_EDT_UPPER_BOUND,   IFASTBP_PROC::FEE_SCALE_LIST, 
               ifds::UpperBound,0,IDC_LIST_FEE_SCALE);
   AddControl( CTRL_EDIT,    IDC_EDT_SCALE_RATE,   IFASTBP_PROC::FEE_SCALE_LIST, 
               ifds::ScaleRate,0,IDC_LIST_FEE_SCALE);
   AddControl( CTRL_EDIT,    IDC_EDT_MIN2,   IFASTBP_PROC::FEE_SCALE_LIST, 
               ifds::MinFee,0,IDC_LIST_FEE_SCALE);
   AddControl( CTRL_EDIT,    IDC_EDT_MAX,   IFASTBP_PROC::FEE_SCALE_LIST, 
               ifds::MaxFee,0,IDC_LIST_FEE_SCALE);   

   if (m_fromScr == FUNDSPONSORFEEMODEL::ACCOUNTSCR)
   {
      AddControl ( CTRL_COMBO, IDC_CMB_ACCOUNT, IFASTBP_PROC::SHAREHOLDER_CBO, 
                   ifds::AccountNumList,CTRLFLAG_INITCOMBO_BY_SUB_LIST);
   }
   dynamic_cast<DSTEdit*> (GetControl( IDC_EDT_UPPER_BOUND ) )->SetAllowedChars( NUMBERS );
   dynamic_cast<DSTEdit*> (GetControl( IDC_EDT_SCALE_RATE ) )->SetAllowedChars( NUMBERS );
   dynamic_cast<DSTEdit*> (GetControl( IDC_EDT_LOWER_BOUND ) )->SetAllowedChars( NUMBERS );
   dynamic_cast<DSTEdit*> (GetControl( IDC_EDT_MIN2 ) )->SetAllowedChars( NUMBERS );
   dynamic_cast<DSTEdit*> (GetControl( IDC_EDT_MAX ) )->SetAllowedChars( NUMBERS );
   dynamic_cast<DSTEdit*> (GetControl( IDC_EDT_UPPER_BOUND ) )->SetMaxCharNum( 13 );
   dynamic_cast<DSTEdit*> (GetControl( IDC_EDT_SCALE_RATE ) )->SetMaxCharNum( 13 );
   dynamic_cast<DSTEdit*> (GetControl( IDC_EDT_LOWER_BOUND ) )->SetMaxCharNum( 13 );
   dynamic_cast<DSTEdit*> (GetControl( IDC_EDT_MIN2 ) )->SetMaxCharNum( 13 );
   dynamic_cast<DSTEdit*> (GetControl( IDC_EDT_MAX ) )->SetMaxCharNum( 13 );
   dynamic_cast<DSTEdit*> (GetControl( IDC_EDT_MODEL_CODE ) )->SetMaxCharNum( 6 );
   dynamic_cast<DSTEdit*> (GetControl( IDC_EDT_VALUE1 ) )->SetAllowedChars( I_("0123456789.") );   
   dynamic_cast<DSTEdit*> (GetControl( IDC_EDT_FEE_MAX ) )->SetAllowedChars( I_("0123456789.") );   
   dynamic_cast<DSTEdit*> (GetControl( IDC_EDT_FEE_MIN ) )->SetAllowedChars( I_("0123456789.") );   
}

//******************************************************************************
void FundSponsorFeeModelDlg::OnPostInitDialog()
{
   TRACE_METHOD (CLASSNAME, I_("OnPostInitDialog"));

   if (m_fromScr != FUNDSPONSORFEEMODEL::ACCOUNTSCR)
   {
      SetUserAccesFunctionCode (UAF::FUNDSPONSOR_FEE_MODEL);
      addBtnAddForPermissionCheck (IDC_ADD_FUND_APONSOR, IDC_LIST_FUND_SPONSOR);
      addBtnDeleteForPermissionCheck (IDC_BTN_DEL_FUNDSPONSOR, IDC_LIST_FUND_SPONSOR);
   }
   addControls();
   doRefresh (this, NULL);
}

//******************************************************************************
void FundSponsorFeeModelDlg::SetDlgCaption()
{
   TRACE_METHOD( CLASSNAME, I_( "SetDlgCaption" ) );

   if (m_fromScr == FUNDSPONSORFEEMODEL::ACCOUNTSCR)
   {
      DString strShrNum, 
         strAccountNum, 
         dstrEntityName;

      getParent()->getField(this, IFASTBP_PROC::SHAREHOLDER_CBO, ifds::ShrNum, strShrNum, false);
      
      CButton *pRadioButton = static_cast < CButton* > ( GetDlgItem( IDC_RD_ACCOUNT ) );
      if (pRadioButton->GetCheck())
      {
         getParent()->getField (this, IFASTBP_PROC::MFACCOUNT_CBO, ifds::AccountNum, strAccountNum, false);
         if ( !strAccountNum.strip().empty() ) 
         {
            dynamic_cast <DSTCWorkSession *>(getBFWorkSession())->getFirstSequenced01AccountholderEntityName (getDataGroupId(), strAccountNum, dstrEntityName);
         }
      }
      SetShrAcctCaption (strShrNum, strAccountNum, dstrEntityName);
   }
   else
   {
      CString cstrDlgCaption;
      cstrDlgCaption.LoadString(TXT_SYS_LVL_FUNDSPONSOR_FEE_MODEL);

      SetWindowText( cstrDlgCaption );
   }
}

//******************************************************************************
bool FundSponsorFeeModelDlg::doRefresh( GenericInterface *rpGICaller, 
                                        const I_CHAR * szOriginalCommand)
{
   TRACE_METHOD (CLASSNAME, I_("doRefresh"));

   if (DString(szOriginalCommand) == I_("ReloadParams"))
   {
      getParameter (FUNDSPONSORFEEMODEL::FROM_SCR, m_fromScr);
      getParameter (FUNDSPONSORFEEMODEL::SEARCHTYPE, m_dstrSearchType);
      getParameter (FUNDSPONSORFEEMODEL::ACCOUNTNUM, m_AcctNum);
      getParameter (FUNDSPONSORFEEMODEL::FEE_MODEL_CODE, m_dstrFeeModelCode);
      getParameter (FUNDSPONSORFEEMODEL::FUND_SPONSOR_CODE, m_dstrFundSponsorCode);
   }
   DispSearchTypeRelated ();
   SetDlgCaption();
   if (m_fromScr != FUNDSPONSORFEEMODEL::ACCOUNTSCR) 
   {
      LoadListControl (IDC_LIST_FUND_SPONSOR);
      ListFilterRelateChange (IDC_LIST_FUND_SPONSOR);
   }
   else
   {
//if called from the account we want to postpone the list call
//until we have a fee model code
      SearchModelCodeRelateChange ();
   }
   GetDlgItem (IDC_BTN_MORE_FUNDSPONSOR)->
         EnableWindow (getParent()->doMoreRecordsExist (this, IFASTBP_PROC::FUNDSPONSOR_FEE_MODEL_LIST));
   GetDlgItem (IDC_BTN_MORE_FEE_PARAM)->
         EnableWindow (getParent()->doMoreRecordsExist (this, IFASTBP_PROC::FUNDSPONSOR_FEE_LIST));
   return true;
}

//*******************************************************************************
void FundSponsorFeeModelDlg::DispSearchTypeRelated ()
{
   DString dstrAccountNum, 
      dstrSearchType;

   if (m_fromScr == FUNDSPONSORFEEMODEL::SYSTEM)
   {
      GetDlgItem (IDC_RD_SHAREHOLDER) ->ShowWindow (false);
      GetDlgItem (IDC_RD_ACCOUNT) ->ShowWindow (false);
      GetDlgItem (IDC_CMB_ACCOUNT) ->ShowWindow (false);
      
      bool bShowModelItems = m_dstrSearchType == FUNDSPONSORFEEMODEL::FEE_MODEL_CODE ||
                             m_dstrSearchType == FUNDSPONSORFEEMODEL::FUND_SPONSOR_CODE;
      
      GetDlgItem (IDC_TXT_MODEL_CODE)->ShowWindow (bShowModelItems);
      GetDlgItem (IDC_EDT_SEARCH_MODEL_CODE)->ShowWindow (bShowModelItems);
      GetDlgItem (IDC_TXT_SEARCH_MODEL_CODE)->ShowWindow (bShowModelItems);
      if (m_dstrSearchType == FUNDSPONSORFEEMODEL::FEE_MODEL_CODE)
      {
         CString cstrModelCode;
		 cstrModelCode.LoadString(TXT_MODEL_CODE);
		  GetDlgItem (IDC_TXT_MODEL_CODE)->SetWindowText (cstrModelCode);
         GetDlgItem (IDC_EDT_SEARCH_MODEL_CODE)->SetWindowText (m_dstrFeeModelCode.c_str());
      }
      else if (m_dstrSearchType == FUNDSPONSORFEEMODEL::FUND_SPONSOR_CODE)
      {
         CString cstrFundGrp;
		 cstrFundGrp.LoadString(TXT_FUND_GROUP);
		 GetDlgItem (IDC_TXT_MODEL_CODE)->SetWindowText (cstrFundGrp);
         GetDlgItem (IDC_EDT_SEARCH_MODEL_CODE)->SetWindowText (m_dstrFundSponsorCode.c_str());
      }      
      DString modelDesc;

      getParent()->getField (this, ifds::SearchModelDesc, modelDesc, false);
      GetDlgItem (IDC_TXT_SEARCH_MODEL_CODE)->SetWindowText (modelDesc.c_str());
   }
   else if (m_fromScr == FUNDSPONSORFEEMODEL::ACCOUNTSCR) 
   {
      GetDlgItem( IDC_ADD_FUND_APONSOR )->EnableWindow (false);
      GetDlgItem( IDC_BTN_DEL_FUNDSPONSOR )->EnableWindow (false );

      GetDlgItem( IDC_ADD_FEE_PARAM )->EnableWindow (false);
      GetDlgItem( IDC_BTN_DEL_FEE_PARAM )->EnableWindow (false );
      GetDlgItem( IDC_ADD_FEE_SCALE )->EnableWindow (false);
      GetDlgItem( IDC_BTN_DEL_FEE_SCALE )->EnableWindow (false );

      GetControl( IDC_EDT_MODEL_CODE )->Enable (false);
      GetControl( IDC_CMB_SPONSOR_CODE )->Enable (false);
      GetControl( IDC_CMB_MODEL_OPTION )->Enable (false);

      GetDlgItem( IDC_RD_SHAREHOLDER )->ShowWindow (true);
      GetDlgItem( IDC_RD_ACCOUNT )->ShowWindow (true);
      GetDlgItem( IDC_CMB_ACCOUNT )->ShowWindow (false);

      DString dstrFeeModelCode;
      
      getParent()->getField (this, IFASTBP_PROC::MFACCOUNT_CBO, ifds::FeeModelCode, dstrFeeModelCode, false);
      dstrFeeModelCode.strip();
      CButton *pRadioButton;
      if (!dstrFeeModelCode.empty())
      {
	      pRadioButton = static_cast < CButton* > ( GetDlgItem( IDC_RD_ACCOUNT ) );		  
      }
      else
      {
	      getParent()->getField(this, IFASTBP_PROC::SHAREHOLDER_CBO, ifds::FeeModelCode, dstrFeeModelCode, false);
         pRadioButton = static_cast < CButton* > (GetDlgItem(IDC_RD_SHAREHOLDER));
      }
      pRadioButton->SetCheck (1);
	  CString cstrModelCode;
	  cstrModelCode.LoadString(TXT_MODEL_CODE);
      GetDlgItem (IDC_TXT_MODEL_CODE) ->SetWindowText( cstrModelCode );            
      GetDlgItem (IDC_EDT_SEARCH_MODEL_CODE) ->SetWindowText (dstrFeeModelCode.c_str());
   }    
}

//*********************************************************************************
void FundSponsorFeeModelDlg::ControlUpdated( UINT controlID,
                                             const DString &strValue)
{
   switch( controlID )
   {
      case IDC_CMB_MODEL_OPTION:
         {
            displayModelOptionRelateControls();
            break;
         }
      case IDC_CMB_FEE_TYPE1: 
         {
            displayFeeParamTypeRelatedControls();
            break;
         }
      case IDC_EDT_MODEL_CODE:
         {
            LoadControl (IDC_TXT_MODELCODE_DESC);
            break;
         }
      case IDC_CMB_SPONSOR_CODE:
         {
            LoadControl(IDC_TXT_SPONSOR_DESC);
            break;
         }
      case IDC_CMB_FEE_CODE:
         {
            DString dstrFeeCode;
            bool _bshow = true;

            getParent()->getField (this, IFASTBP_PROC::FUNDSPONSOR_FEE_LIST, ifds::FeeCode, dstrFeeCode, false);
            if (dstrFeeCode == I_("110") || dstrFeeCode == I_("111"))
            {
	            _bshow = false;
            }
            GetDlgItem (IDC_EDT_FEE_MAX)->ShowWindow (_bshow);
            GetDlgItem (IDC_EDT_FEE_MIN)->ShowWindow (_bshow);
            GetDlgItem (IDC_TXT_FEE_MIN)->ShowWindow (_bshow);
            GetDlgItem (IDC_TXT_FEE_MAX)->ShowWindow (_bshow);			  
            break;
         }
      default:
         break;
   }
}
//*********************************************************************************
void FundSponsorFeeModelDlg::displayModelOptionRelateControls ()
{
   bool bShow = false;
   DString dstrFeeModelOption;      
   getParent()->getField(this, IFASTBP_PROC::FUNDSPONSOR_FEE_MODEL_LIST, ifds::FeeModelOption, dstrFeeModelOption, false);
   if( dstrFeeModelOption != I_("") && !ListFilterRelateChange( IDC_LIST_FUND_SPONSOR ) ) 
   {
      bShow = true;
   }
   const DString* dstrKey = &(getParent()->getCurrentListItemKey(this,IFASTBP_PROC::FUNDSPONSOR_FEE_LIST ) );
   
   LoadListControl( IDC_LIST_FEE_PARAM, dstrKey);
   GetDlgItem(IDC_BTN_MORE_FEE_PARAM)->EnableWindow( getParent()->doMoreRecordsExist( this, IFASTBP_PROC::FUNDSPONSOR_FEE_LIST ) );
      
   ShowFeeRelateControls (bShow);
   displayFeeParamTypeRelatedControls();
}
//*********************************************************************************
void FundSponsorFeeModelDlg::displayFeeParamTypeRelatedControls()
{
   bool bShow = false;
   DString dstrFeeType;
   int numListItems = getParent()->getNumberOfItemsInList( this, IFASTBP_PROC::FUNDSPONSOR_FEE_LIST);
   if( numListItems > 0 )
   {
      getParent()->getField(this, IFASTBP_PROC::FUNDSPONSOR_FEE_LIST, ifds::ParamFeeType, dstrFeeType, false);
      if( dstrFeeType == SCALE || dstrFeeType == TIER ) 
      {
         bShow = true;
         LoadListControl( IDC_LIST_FEE_SCALE );         
      }   
      bShow = bShow && !ListFilterRelateChange( IDC_LIST_FEE_PARAM );

      GetDlgItem(IDC_EDT_VALUE1)->ShowWindow(!bShow);
      GetDlgItem(IDC_TXT_VALUE)->ShowWindow(!bShow);

      GetDlgItem(IDC_EDT_FEE_MAX)->ShowWindow(!bShow);
      GetDlgItem(IDC_TXT_FEE_MAX)->ShowWindow(!bShow);
      GetDlgItem(IDC_EDT_FEE_MIN)->ShowWindow(!bShow);
      GetDlgItem(IDC_TXT_FEE_MIN)->ShowWindow(!bShow);
   }
   ShowScaleRelateControls (bShow);   
}
//*********************************************************************************
void FundSponsorFeeModelDlg::ShowScaleRelateControls( bool bShow )
{
   GetDlgItem(IDC_LIST_FEE_SCALE)->ShowWindow (bShow);
   GetDlgItem(IDC_ADD_FEE_SCALE)->ShowWindow (bShow);
   GetDlgItem(IDC_BTN_DEL_FEE_SCALE)->ShowWindow (bShow);
   GetDlgItem(IDC_EDT_LOWER_BOUND)->ShowWindow (bShow);
   GetDlgItem(IDC_EDT_UPPER_BOUND)->ShowWindow (bShow);
   GetDlgItem(IDC_EDT_SCALE_RATE)->ShowWindow (bShow);
   GetDlgItem(IDC_EDT_MIN2)->ShowWindow (bShow);
   GetDlgItem(IDC_EDT_MAX)->ShowWindow (bShow);

   GetDlgItem(IDC_TXT_LOWER_BOUND)->ShowWindow (bShow);
   GetDlgItem(IDC_TXT_MIN)->ShowWindow (bShow);
   GetDlgItem(IDC_TXT_UPPER_BOUND)->ShowWindow (bShow);
   GetDlgItem(IDC_TXT_MAX)->ShowWindow (bShow);
   GetDlgItem(IDC_TXT_RATE)->ShowWindow (bShow);
   GetDlgItem(IDC_TXT_PERCENT)->ShowWindow (bShow);
   if (m_fromScr == FUNDSPONSORFEEMODEL::ACCOUNTSCR) 
   {
      GetDlgItem ( IDC_ADD_FEE_SCALE )->EnableWindow (false);
      GetDlgItem ( IDC_BTN_DEL_FEE_SCALE )->EnableWindow (false);
      GetControl ( IDC_EDT_LOWER_BOUND )->Enable (false);
      GetControl ( IDC_EDT_MIN2 )->Enable (false);
      GetControl ( IDC_EDT_UPPER_BOUND )->Enable (false);
      GetControl ( IDC_EDT_MAX )->Enable (false);
      GetControl ( IDC_EDT_SCALE_RATE )->Enable (false);
   }
}
//*********************************************************************************
void FundSponsorFeeModelDlg::ShowFeeRelateControls( bool bShow )
{
   GetDlgItem(IDC_LIST_FEE_PARAM)->ShowWindow(bShow);
   GetDlgItem(IDC_ADD_FEE_PARAM)->ShowWindow(bShow);
   GetDlgItem(IDC_BTN_DEL_FEE_PARAM)->ShowWindow(bShow);
   GetDlgItem(IDC_BTN_MORE_FEE_PARAM)->ShowWindow(bShow);
   GetDlgItem(IDC_CMB_FEE_CODE)->ShowWindow(bShow);
   GetDlgItem(IDC_CMB_FEE_TYPE1)->ShowWindow(bShow);
   GetDlgItem(IDC_EDT_VALUE1)->ShowWindow(bShow);
   GetDlgItem(IDC_CMB_CHARGE_OPTION)->ShowWindow(bShow);
   GetDlgItem(IDC_DTP_EFFECTIVE)->ShowWindow(bShow);
   GetDlgItem(IDC_DTP_STOPDATE)->ShowWindow(bShow);
   GetDlgItem(IDC_CMB_CURRENCY)->ShowWindow(bShow);   
   GetDlgItem(IDC_EDT_FEE_MAX)->ShowWindow(bShow);
   GetDlgItem(IDC_EDT_FEE_MIN)->ShowWindow(bShow);

   GetDlgItem(IDC_TXT_FEECODE)->ShowWindow(bShow);   
   GetDlgItem(IDC_TXT_FEETYPE)->ShowWindow(bShow);   
   GetDlgItem(IDC_TXT_VALUE)->ShowWindow(bShow);   
   GetDlgItem(IDC_TXT_CHRGEOPTION)->ShowWindow(bShow);   
   GetDlgItem(IDC_TXT_EFFECTIVEDATE)->ShowWindow(bShow);   
   GetDlgItem(IDC_TXT_STOP_DATE)->ShowWindow(bShow);   
   GetDlgItem(IDC_TXT_CURRENCY)->ShowWindow(bShow);
   GetDlgItem(IDC_TXT_FEE_MAX)->ShowWindow(bShow);   
   GetDlgItem(IDC_TXT_FEE_MIN)->ShowWindow(bShow);   

   if( m_fromScr == FUNDSPONSORFEEMODEL::ACCOUNTSCR ) 
   {
      GetDlgItem( IDC_ADD_FEE_PARAM )->EnableWindow( false );
      GetDlgItem( IDC_BTN_DEL_FEE_PARAM )->EnableWindow( false );

      GetControl( IDC_CMB_FEE_CODE )->Enable( false );
      GetControl( IDC_CMB_FEE_TYPE1 )->Enable( false );
      GetControl( IDC_CMB_CHARGE_OPTION )->Enable( false );
      GetControl( IDC_EDT_VALUE1 )->Enable( false );
      GetControl( IDC_CMB_CURRENCY )->Enable( false );
      GetControl( IDC_DTP_EFFECTIVE )->Enable( false );
      GetControl( IDC_DTP_STOPDATE )->Enable( false );
      GetControl( IDC_EDT_FEE_MAX )->Enable( false );
      GetControl( IDC_EDT_FEE_MIN )->Enable( false );
   }
}

//******************************************************************************
BOOL FundSponsorFeeModelDlg::PreTranslateMessage (MSG* pMsg) 
{
/*
   if ( pMsg->message == WM_KEYDOWN && 
       (int) (pMsg->wParam) == VK_F4 && 
       !IsSelectedCtrlUpdateable ())
   {
      return TRUE;
   }
*/
   if (pMsg->message == WM_KEYDOWN && (int)(pMsg->wParam) == VK_F4)
   {
      if (GetFocus() == GetDlgItem (IDC_EDT_MODEL_CODE) && IsSelectedCtrlUpdateable ())
      {
         PostMessage (UM_OPENFEEMODELDLG);
         uFeeModelCtrlID = IDC_EDT_MODEL_CODE;
      }
      else if ( GetFocus() == GetDlgItem (IDC_EDT_SEARCH_MODEL_CODE) &&         
                m_fromScr == FUNDSPONSORFEEMODEL::ACCOUNTSCR)
      {
         PostMessage (UM_OPENFEEMODELDLG);
         uFeeModelCtrlID = IDC_EDT_SEARCH_MODEL_CODE;
      }
   }
   return BaseMainDlg::PreTranslateMessage (pMsg);
}

//******************************************************************
LRESULT FundSponsorFeeModelDlg::OpenFeeModelDlg (WPARAM, LPARAM) 
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTGUI_CONDITION, CLASSNAME, I_("OpenSlsRepListDlg"));
   CWaitCursor wait;

   try
   {
      switch (getParentProcess ()->
                 invokeProcessFromChild ( this, 
                                          CMD_BPROC_FEE_MODEL, 
                                          PROC_SUPPORT))
      {
         case CMD_OK:
         case CMD_MODELESS_INPROCESS:
         {
            DString feeModeCode;

            getParameter (MFCAN_IP_PARAM::FEE_MODEL_CODE, feeModeCode);
            if (uFeeModelCtrlID == IDC_EDT_MODEL_CODE)
            {
               getParent()->setField ( this, 
                                       IFASTBP_PROC::FUNDSPONSOR_FEE_MODEL_LIST, 
                                       ifds::FeeModelCode, 
                                       feeModeCode);
               LoadControl (uFeeModelCtrlID);
            }            
            if (uFeeModelCtrlID == IDC_EDT_SEARCH_MODEL_CODE && m_fromScr == FUNDSPONSORFEEMODEL::ACCOUNTSCR)
            {
               GetDlgItem (IDC_EDT_SEARCH_MODEL_CODE)->SetWindowText (feeModeCode.c_str());
            }                              
            break;
         }
         case CMD_CANCEL:
            break;
         default:
            // Display error
            ConditionMessageBox (FRAMEBELOW(), GETHIGHESTSEVERITY());
            break;
      }
   }
   catch (ConditionException &ce)
   {
      ConditionMessageBox (ce);
   }
   catch (...)
   {
      DISPLAYCONDITIONFROMFILE (CND::GUI_ERR_UNKNOWN_EXCEPTION);
   }
   return 0;
}

//******************************************************************
void FundSponsorFeeModelDlg::OnRbAccount()
{
	TRACE_METHOD( CLASSNAME, I_( "OnRbAccount" ) );
   CWaitCursor wait;

   CButton *pRadioButton = static_cast < CButton* > ( GetDlgItem( IDC_RD_ACCOUNT ) );
   if( pRadioButton->GetCheck() )
   {
      SetDlgCaption();

      GetDlgItem( IDC_CMB_ACCOUNT )->ShowWindow( true );      
      ConnectControlToData( IDC_CMB_ACCOUNT, true );
      LoadControl(IDC_CMB_ACCOUNT);

      DString dstrAcctNum;
      getParent()->getField(this, IFASTBP_PROC::SHAREHOLDER_CBO, ifds::AccountNumList, dstrAcctNum, false);
      if (dstrAcctNum.strip() == NULL_STRING)
      {
         getParent()->getField (this, IFASTBP_PROC::MFACCOUNT_CBO, ifds::AccountNum, dstrAcctNum, false);
      }

      DSTComboBox *dstcomboAcctList = NULL;
      dstcomboAcctList = dynamic_cast< DSTComboBox * > (GetDlgItem (IDC_CMB_ACCOUNT));
      if (dstcomboAcctList != NULL)
      {
         DString tmp;
         GetControlText (IDC_CMB_ACCOUNT, tmp, false, 0);

         if (tmp == NULL_STRING)
         {
            dstcomboAcctList->SetSelectionByData (dstrAcctNum);
         }
         OnSelchangeCmbAccountNum ();
      }      

      DString dstrFeeModelCode;
      getParent()->getField (this, IFASTBP_PROC::MFACCOUNT_CBO, ifds::FeeModelCode, dstrFeeModelCode, false);
      GetDlgItem( IDC_EDT_SEARCH_MODEL_CODE )->SetWindowText( dstrFeeModelCode.c_str() );
      SearchModelCodeRelateChange ();
   }
}

//******************************************************************
void FundSponsorFeeModelDlg::OnRbShareholder()
{
	TRACE_METHOD( CLASSNAME, I_( "OnRbShareholder" ) );
   CWaitCursor wait;

   CButton *pRadioButton = static_cast < CButton* > ( GetDlgItem( IDC_RD_SHAREHOLDER ) );
   if( pRadioButton->GetCheck() )
   {
      SetDlgCaption();
      GetDlgItem( IDC_CMB_ACCOUNT )->ShowWindow( false );
      DString dstrFeeModelCode;
      getParent()->getField(this, IFASTBP_PROC::SHAREHOLDER_CBO, ifds::FeeModelCode, dstrFeeModelCode, false);
      GetDlgItem( IDC_EDT_SEARCH_MODEL_CODE )->SetWindowText( dstrFeeModelCode.c_str() );
      SearchModelCodeRelateChange();
   }
}
//******************************************************************************
void FundSponsorFeeModelDlg::OnBtnReset() 
{
   TRACE_METHOD( CLASSNAME, I_( "OnBtnReset" ) );
   ResetListItem (IDC_LIST_FUND_SPONSOR);
   GetDlgItem( IDC_EDT_MODEL_CODE )->SetFocus();
}
//*********************************************************************************
void FundSponsorFeeModelDlg::OnBtnAddFeeParam()
{
   TRACE_METHOD( CLASSNAME, I_( "OnBtnAddFeeParam" ) );
   
   getParent()->send( this, I_("CLEAR FEE SCALE CONTAINER") ); 
   AddToListControl (IDC_LIST_FEE_PARAM);
}
//********************************************************************************
void FundSponsorFeeModelDlg::OnBtnDelFeeParam()
{
   TRACE_METHOD( CLASSNAME, I_( "OnBtnDelFeeParam" ) );
   
   getParent()->send( this, I_("CLEAR FEE SCALE CONTAINER") );
   
   DeleteFromListControl( IDC_LIST_FEE_PARAM );   
   
   int numListItems = getParent()->getNumberOfItemsInList( this, IFASTBP_PROC::FUNDSPONSOR_FEE_LIST);
   if( numListItems <= 0 )
   {
      ShowScaleRelateControls (false);
   }
   GetDlgItem (IDC_CMB_FEE_CODE)->SetFocus();
}
//**********************************************************************************
void FundSponsorFeeModelDlg::OnBtnFeeParamMore ()
{
   TRACE_METHOD( CLASSNAME, I_( "OnBtnFeeParamMore" ) );
   CWaitCursor wait;
   static int cursel;
   cursel = GetList( IDC_LIST_FEE_PARAM )->GetNextItem(-1, LVIS_SELECTED | LVNI_FOCUSED);  
   const DString *crtKey = &getParent()->getCurrentListItemKey( this,IFASTBP_PROC::FUNDSPONSOR_FEE_LIST );
   if( getParent()->performSearch( this, IFASTBP_PROC::FUNDSPONSOR_FEE_LIST, SEARCH_NEXT_BLOCK ) <= WARNING )
   {
      LoadListControl( IDC_LIST_FEE_PARAM );
      if( *crtKey != NULL_STRING )
      {
         GetList( IDC_LIST_FEE_PARAM )->SetSelection( crtKey );
      }
   }
   GetDlgItem(IDC_BTN_MORE_FEE_PARAM)->EnableWindow( getParent()->doMoreRecordsExist( this, IFASTBP_PROC::FUNDSPONSOR_FEE_LIST ) );
   GetList( IDC_LIST_FEE_PARAM )->SetSelection(cursel, true, true);
   SetMessageStatusBar(NULL_STRING);   

}

//*********************************************************************************
void FundSponsorFeeModelDlg::OnBtnAddFundSponsor()
{
   TRACE_METHOD( CLASSNAME, I_( "OnBtnAddFundSponsor" ) );
   getParent()->send( this, I_("CLEAR FEE PARAMETER CONTAINER") );

   AddToListControl( IDC_LIST_FUND_SPONSOR );

   ShowFeeRelateControls (false);
   ShowScaleRelateControls (false);
   GetDlgItem (IDC_EDT_MODEL_CODE)->SetFocus ();
}

//********************************************************************************
void FundSponsorFeeModelDlg::OnBtnDelFundSponsor()
{
   TRACE_METHOD( CLASSNAME, I_( "OnBtnDelFundSponsor" ) );
   getParent()->send( this, I_("CLEAR FEE PARAMETER CONTAINER") );

   DeleteFromListControl (IDC_LIST_FUND_SPONSOR);      
   ListFilterRelateChange (IDC_LIST_FUND_SPONSOR);
   GetDlgItem (IDC_EDT_MODEL_CODE)->SetFocus();
}

//**********************************************************************************
void FundSponsorFeeModelDlg::OnBtnFundSponsorMore()
{
   TRACE_METHOD (CLASSNAME, I_("OnBtnFundSponsorMore"));

   CWaitCursor wait;
   static int cursel;
   cursel = GetList (IDC_LIST_FUND_SPONSOR)->GetNextItem (-1, LVIS_SELECTED | LVNI_FOCUSED);  
   const DString *crtKey = &getParent()->getCurrentListItemKey (this, IFASTBP_PROC::FUNDSPONSOR_FEE_MODEL_LIST);
   if (getParent()->performSearch (this, IFASTBP_PROC::FUNDSPONSOR_FEE_MODEL_LIST, SEARCH_NEXT_BLOCK) <= WARNING)
   {
      LoadListControl (IDC_LIST_FUND_SPONSOR);
      if (*crtKey != NULL_STRING)
      {
         GetList (IDC_LIST_FUND_SPONSOR)->SetSelection (crtKey);
      }
   }
   GetDlgItem (IDC_BTN_MORE_FUNDSPONSOR)->
         EnableWindow (getParent()->doMoreRecordsExist (this, IFASTBP_PROC::FUNDSPONSOR_FEE_MODEL_LIST));
}
//**********************************************************************************
void FundSponsorFeeModelDlg::OnBtnAddScale()
{
   TRACE_METHOD( CLASSNAME, I_( "OnBtnAddScale" ) );
   AddToListControl( IDC_LIST_FEE_SCALE );
   GetDlgItem( IDC_EDT_LOWER_BOUND )->SetFocus();
}
//**********************************************************************************
void FundSponsorFeeModelDlg::OnBtnDelScale()
{
   TRACE_METHOD( CLASSNAME, I_( "OnBtnDelScale" ) );
   DeleteFromListControl( IDC_LIST_FEE_SCALE );

   GetDlgItem( IDC_EDT_LOWER_BOUND )->SetFocus();
}

//**********************************************************************************
void FundSponsorFeeModelDlg::OnBtnAdmDates() 
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OnBtnAdminDates" ) );
   CWaitCursor wait;
   ShowAdminDates( IFASTBP_PROC::FUNDSPONSOR_FEE_MODEL_LIST );
}

//*********************************************************************************
bool FundSponsorFeeModelDlg::ListViewControlFilter( long lSubstituteId, const DString * )
{
   bool bRet = true;

   if (lSubstituteId == ifds::FeeSponsorListSet.getId())
   {
      if (m_fromScr == FUNDSPONSORFEEMODEL::ACCOUNTSCR) 
      {
         CString csFeeModeCode;

         GetDlgItem (IDC_EDT_SEARCH_MODEL_CODE)->GetWindowText (csFeeModeCode);
         DString feeModelCode_ (csFeeModeCode.GetBuffer ()),
            feeModelCode;

         getParent()->getField ( this, IFASTBP_PROC::FUNDSPONSOR_FEE_MODEL_LIST, 
                                 ifds::FeeModelCode, feeModelCode, false);         
         bRet = feeModelCode_.strip().upperCase() == feeModelCode.strip().upperCase();
      }
   }
   else if( lSubstituteId == ifds::FeeParamListHeaderSet.getId() )
   {    
      DString dstrFeeModelCode, dstrTmp;      
      getParent()->getField( this, IFASTBP_PROC::FUNDSPONSOR_FEE_LIST, ifds::FeeModelCode, dstrFeeModelCode, false);
      getParent()->getField( this, IFASTBP_PROC::FUNDSPONSOR_FEE_MODEL_LIST, ifds::FeeModelCode, dstrTmp, false);
      if(dstrTmp.strip().upperCase() != dstrFeeModelCode.strip().upperCase())
         return false;

      DString dstrFundGroup;      
      getParent()->getField( this, IFASTBP_PROC::FUNDSPONSOR_FEE_LIST, ifds::CommGroup, dstrFundGroup, false);
      getParent()->getField( this, IFASTBP_PROC::FUNDSPONSOR_FEE_MODEL_LIST, ifds::FundGroup, dstrTmp, false);
      if(dstrTmp.strip().upperCase() != dstrFundGroup.strip().upperCase())
         return false;

      return true;
   }
   return bRet;
}

//********************************************************************************
bool FundSponsorFeeModelDlg::GetOverrideItemString(long lSubstituteId, const DString &ColumnKey, DString &strOut)
{
   DString str;  
   if( lSubstituteId == ifds::FeeScaleListSet.getId() )
   {
      if( ColumnKey == I_("Type") )
      {
         strOut = PERCENT;   
         return(true);
      }
   }

   return(false);

}

//********************************************************************************
void FundSponsorFeeModelDlg::OnKillfocusSearchModelCode()
{
   SearchModelCodeRelateChange ();
}

//********************************************************************************
void FundSponsorFeeModelDlg::SearchModelCodeRelateChange ()
{
   CString feeModeCode;
   GetDlgItem (IDC_EDT_SEARCH_MODEL_CODE)->GetWindowText (feeModeCode);
   DString tmp = feeModeCode, 
      dstrDesc = NULL_STRING;

   if (m_fromScr == FUNDSPONSORFEEMODEL::ACCOUNTSCR)
   {
      CButton *pRadioButton = static_cast < CButton* > (GetDlgItem (IDC_RD_SHAREHOLDER));
      if (pRadioButton->GetCheck())
      {                        
         getParent()->setField (this, IFASTBP_PROC::SHAREHOLDER_CBO, ifds::FeeModelCode, tmp);
         getParent()->getField (this, IFASTBP_PROC::SHAREHOLDER_CBO, ifds::FeeModelDesc, dstrDesc, false);
      }
      else 
      {
         getParent()->setField (this, IFASTBP_PROC::MFACCOUNT_CBO, ifds::FeeModelCode, tmp);
         getParent()->getField (this, IFASTBP_PROC::MFACCOUNT_CBO, ifds::FeeModelDesc, dstrDesc, false);
      }
      setParameter (I_("FeeModelCode"), tmp);
      getParent()->send ( this, I_("Refresh_FeeModelCode"));
      GetDlgItem (IDC_TXT_SEARCH_MODEL_CODE)->SetWindowText (dstrDesc.c_str());
      
      DString feeModelExists;

      getParent() ->getField (this, FUNDSPONSORFEEMODEL::FeeModelExists, feeModelExists);

      bool bConnectToData = !tmp.empty() && feeModelExists == I_("Y");

      ConnectListToData (IDC_LIST_FUND_SPONSOR, bConnectToData);
      ConnectListToData (IDC_LIST_FEE_PARAM, bConnectToData);
      if (bConnectToData)
      {
         LoadListControl (IDC_LIST_FUND_SPONSOR);
         ListFilterRelateChange (IDC_LIST_FUND_SPONSOR);
      }
   }
   else
   {
      GetDlgItem (IDC_EDT_SEARCH_MODEL_CODE)->EnableWindow (false);
      getParent()->getField (this, BF::NullContainerId, ifds::SearchModelDesc, dstrDesc, false);
   }
}

//********************************************************************************
void FundSponsorFeeModelDlg::OnSelchangeCmbAccountNum ()
{
   DString dstrAcctNum,
      dstrFeeModelCode;
   
   getParent()->getField (this, IFASTBP_PROC::SHAREHOLDER_CBO, ifds::AccountNumList, dstrAcctNum, false);
   getParent()->setField (this, IFASTBP_PROC::MFACCOUNT_CBO, ifds::AccountNum, dstrAcctNum, false);
   getParent()->getField (this, IFASTBP_PROC::MFACCOUNT_CBO, ifds::FeeModelCode, dstrFeeModelCode, false);

   GetDlgItem (IDC_EDT_SEARCH_MODEL_CODE)->SetWindowText (dstrFeeModelCode.c_str());
   SearchModelCodeRelateChange();
}

//********************************************************************************
bool FundSponsorFeeModelDlg::ListFilterRelateChange (UINT controlID)
{     
   bool noitem = false;
   int numListItems = GetList ( controlID )->GetItemCount();

   if (numListItems <= 0)
   {
      if (controlID == IDC_LIST_FUND_SPONSOR)
      {
         ShowFeeRelateControls (false);
         ShowScaleRelateControls (false);
      }
      if (controlID == IDC_LIST_FEE_PARAM)
      {
         ShowScaleRelateControls (false);
      }
      noitem = true;
   }
   if (noitem)
   {
      numListItems = getParent()->getNumberOfItemsInList (this, IFASTBP_PROC::FUNDSPONSOR_FEE_MODEL_LIST);
      if( numListItems > 0 &&
         ( m_dstrSearchType == FUNDSPONSORFEEMODEL::FUND_SPONSOR_CODE || 
           m_dstrSearchType == FUNDSPONSORFEEMODEL::FEE_MODEL_CODE ) )
      {
         getParent()->send ( this, I_("CLEAR FEE PARAMETER CONTAINER"));

         AddToListControl (IDC_LIST_FUND_SPONSOR);

         ShowFeeRelateControls (false);
         ShowScaleRelateControls (false);
         GetDlgItem (IDC_EDT_MODEL_CODE) ->SetFocus();
      }
   }  
   return noitem;
}
//***************************************************************************

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/FundSponsorFeeModelDlg.cpp-arc  $
// 
//    Rev 1.40   Nov 19 2011 01:34:16   wp040143
// P0186484/FN06 - DESKTOP - iFast Desktop (French Customizations)
// 
//    Rev 1.39   May 19 2006 09:55:04   popescu
// Incident# 626125 - expand the number of allowed chars for fee model code to 6, from 4.
// 
//    Rev 1.38   Sep 15 2005 15:13:10   popescu
// Incident#403519 - added CLASSNAME as the fifth parameter to  BaseMainDlg constructor
// 
//    Rev 1.37   Jul 19 2005 15:51:18   Fengyong
// Incident 352435 - continue fix
// 
//    Rev 1.36   Jul 13 2005 17:38:54   popescu
// Incident 352435 - improved performance on the fund sponsor fee model screen - get rid of the wacky keys
// 
//    Rev 1.35   Apr 27 2005 11:51:20   Fengyong
// #Incident 288891 - do not show max and min for discount rate.
// 
//    Rev 1.34   Apr 22 2005 14:51:06   Fengyong
// #Incident 295493 - if access from account detail screen:
// default to account level fee model if account level fee model is not empty.
// 
//    Rev 1.33   Mar 24 2005 15:58:58   Fengyong
// Incident #260676 - Add max min to fundsponsor fee parameter
// 
//    Rev 1.32   Mar 23 2005 13:08:10   Fengyong
// PET1117FN5 - fix performant issue.
// 
//    Rev 1.31   Jan 27 2005 11:34:14   yingbaol
// PTS10038074: display available records if it they are not in 1st 25 records
// 
//    Rev 1.30   Jan 06 2005 17:27:26   Fengyong
// PET10037441 - Sorting FundSponsorFeeModel and Fee scale list
// 
//    Rev 1.29   Dec 22 2004 09:22:44   yingbaol
// PTS10037147:fix more button at fee param level
// 
//    Rev 1.28   Dec 22 2004 09:19:34   yingbaol
// PTS10037147:Fix more button issue
// 
//    Rev 1.27   Dec 14 2004 18:04:34   Fengyong
// change title of the screen
// 
//    Rev 1.26   Nov 17 2004 15:22:42   Fengyong
// PTS10035878 - Shareholder FeeModelcode
// 
//    Rev 1.25   Nov 02 2004 11:21:52   FENGYONG
// PTS10035397 - Add dummy record for the filter result
// 
//    Rev 1.24   Oct 21 2004 17:19:30   YINGBAOL
// PTS10034903:   keep focus on current list item
// 
//    Rev 1.23   Oct 15 2004 16:18:36   FENGYONG
// PTS 10034766 - disable Add delete button for FeeModel Screen When the parent screen is not main search screen.
// 
//    Rev 1.22   Oct 15 2004 11:42:28   FENGYONG
// PTS 10034800 - scale not update correctly
// 
//    Rev 1.21   Sep 29 2004 11:11:58   FENGYONG
// PET1117FN5 - chnage after ESS walkthrough
// 
//    Rev 1.20   Sep 27 2004 14:08:10   FENGYONG
// fix after code review
// 
//    Rev 1.19   Sep 24 2004 18:50:30   FENGYONG
// fix refresh problem
// 
//    Rev 1.18   Sep 21 2004 17:02:08   FENGYONG
// Add search model desc
// 
//    Rev 1.17   Sep 20 2004 16:49:14   FENGYONG
// change fundgroup to commgroup
// 
//    Rev 1.16   Sep 20 2004 15:37:56   FENGYONG
// Add filter
// 
//    Rev 1.15   Sep 20 2004 11:45:14   FENGYONG
// show fee rate when chnage fee type to percent
// 
//    Rev 1.14   Sep 20 2004 11:37:06   FENGYONG
// enable fee list when chargeoption is NAV
// 
//    Rev 1.13   Sep 17 2004 16:56:44   FENGYONG
// Add protection when no system level fundsponsor and feemodel defined
// 
//    Rev 1.12   Sep 15 2004 16:45:54   FENGYONG
// Add Title bar
// 
//    Rev 1.11   Sep 15 2004 15:47:00   FENGYONG
// duplicate checking not case sensitive
// 
//    Rev 1.10   Sep 15 2004 13:38:58   FENGYONG
// disable add and delete buttons for account level
// 
//    Rev 1.9   Sep 09 2004 16:55:22   FENGYONG
// implemant child relation ship between lists
// 
//    Rev 1.8   Sep 09 2004 12:40:28   FENGYONG
// PET1117 FN5
// 
//    Rev 1.7   Sep 09 2004 10:57:38   FENGYONG
// hide rate when fee type is scale
// 
//    Rev 1.6   Sep 08 2004 16:47:16   FENGYONG
// PET1117 FN5
// 
//    Rev 1.5   Sep 08 2004 15:19:56   FENGYONG
// PET117 FN5
// 
//    Rev 1.4   Sep 02 2004 12:32:50   FENGYONG
// PET1117 FN5 - Client Fee
// 
//    Rev 1.3   Aug 31 2004 17:26:56   FENGYONG
// Temp check in for compile purpose - PET117 FN05 - client Fee
// 
//    Rev 1.2   Aug 11 2004 18:42:40   FENGYONG
// Temp PET 1117 FN5 check in for second coder use
// 
//    Rev 1.1   Aug 10 2004 11:28:46   FENGYONG
// PET 1117 FN5 - Client Condition Fee
// 
//    Rev 1.0   Aug 09 2004 09:56:40   FENGYONG
// Initial Revision
 * 
 */





