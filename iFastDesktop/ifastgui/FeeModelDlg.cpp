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
// ^FILE   : FeeModelDlg.h
// ^AUTHOR : 
// ^DATE   : 07/26/04
//
// ^CLASS    : FeeModelDlg
// ^SUBCLASS : BaseMainDlg
//
// ^CLASS DESCRIPTION : 
//
//******************************************************************************

#include "stdafx.h"

#include "mfdstc.h"
#include <uibase\DSTEdit.h>
#include "FeeModelDlg.h"
#include <ifastbp\FeeModelProcessInclude.h>
#include <uibase\DSTListCtrl.h>
#include <uibase\DSTComboBox.h>
#include <ifastcbo/DSTCWorkSession.hpp>
#include <ifastcbo/MgmtCoOptions.hpp>
#include <ifastgui\ifasthistoricalinfo.hpp>
#include <discardmsgdlg.h>
#include <bfproc\abstractprocess.hpp>
#include <ifastbp\feemodelprocess.hpp>
#include <ifastcbo/DSTCUserSession.hpp>

extern CLASS_IMPORT const I_CHAR* CMD_GUI_FEE_MODEL;
#include <bfproc\concretedialogcreator.hpp>
static ConcreteDialogCreator< FeeModelDlg > dlgCreator( CMD_GUI_FEE_MODEL );

#ifdef _DEBUG
   #define new DEBUG_NEW
   #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


extern CLASS_IMPORT const I_CHAR* CMD_BPROC_ACCOUNT_ASSOCIATION;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_FEE_PARAMETER_SYSTEM;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_HOLDING_COMP;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_FEE_MODEL_COPY_TO;


namespace
{
   const I_CHAR * const CLASSNAME                     = I_( "FeeModelDlg" );
   const I_CHAR * const YES                           = I_( "Y" );
   const I_CHAR * const NO                            = I_( "N" );

   const I_CHAR* const  LV_FEE_MODEL_LIST             = I_( "FeeModel" );
   const I_CHAR* const  LV_SCALE_FEE                  = I_( "ScaleFee" );
   const I_CHAR* const  PERCENT                       = I_( "Percent" );
   const I_CHAR * const FLAT                          = I_( "0" );
   const I_CHAR * const PERCENTAGE                    = I_( "1" );
   const I_CHAR * const SCALE                         = I_( "2" );
   const I_CHAR * const TIER                          = I_( "3" );
   const I_CHAR * const FEE_CODE_MANAGEMENT_FEE       = I_("18");
   const I_CHAR * const FEE_CPDE_MANAGEMENT_REBATE    = I_("95");
   const I_CHAR * const FEE_CODE_MANAGEMENT_DISCOUNT  = I_("180");
   const I_CHAR * const FEE_CODE_ADVISORY_FEE         = I_("DF");


   const I_CHAR * const NUMBERS = I_("0123456789.");
   const I_CHAR * const	NOT_APPLY  =  I_("NA");
}

namespace CND
{  // Conditions used
   extern const long GUI_ERR_UNKNOWN_EXCEPTION;
}

namespace UAF
{
   extern CLASS_IMPORT I_CHAR * const FEE_MODEL;
   extern CLASS_IMPORT I_CHAR * const FEE_PARAMETER_SYSTEM;
}

namespace ifds
{   
   extern CLASS_IMPORT const BFTextFieldId FeeModelListSet;
   extern CLASS_IMPORT const BFTextFieldId FeeModelCode;
   extern CLASS_IMPORT const BFTextFieldId FeeModelDesc;
   extern CLASS_IMPORT const BFDateFieldId EffectiveDate;
   extern CLASS_IMPORT const BFDateFieldId StopDate;
   extern CLASS_IMPORT const BFTextFieldId FeeModelType;
   extern CLASS_IMPORT const BFDateFieldId LastProcDate;
   extern CLASS_IMPORT const BFTextFieldId AllowCopy;
   extern CLASS_IMPORT const BFTextFieldId SameDlrBrnRep;
   extern CLASS_IMPORT const BFIntegerFieldId FullMoneyOutApplicable;
}

namespace FEEMOD_FLDS
{
   extern CLASS_IMPORT const BFFieldId FROM_HOLDCOMP;
}
//******************************************************************************

FeeModelDlg::FeeModelDlg( CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: BaseMainDlg( FeeModelDlg::IDD, pParent, pGIC, pGIParent, rCommand, CLASSNAME )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   m_rbSearchBy = 1;
   //{{AFX_DATA_INIT(FeeModelDlg)
   // NOTE: the ClassWizard will add member initialization here
   //}}AFX_DATA_INIT
}

//******************************************************************************
FeeModelDlg::~FeeModelDlg()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}
//******************************************************************************

void FeeModelDlg::DoDataExchange(CDataExchange* pDX)
{
   BaseMainDlg::DoDataExchange( pDX );
   //{{AFX_DATA_MAP(FeeModelDlg)
   // NOTE: the ClassWizard will add DDX and DDV calls here
   DDX_Radio(pDX, IDC_RB_SRC_ALL, m_rbSearchBy);
   //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(FeeModelDlg, BaseMainDlg)
//{{AFX_MSG_MAP(FeeModelDlg)
ON_BN_CLICKED(IDC_BTN_RESET, OnBtnReset)
ON_BN_CLICKED(IDC_BTN_ADD, OnBtnAdd)
ON_BN_CLICKED(IDC_BTN_DEL, OnBtnDel)
ON_BN_CLICKED(IDC_BTN_MORE, OnBtnMore)
ON_BN_CLICKED(IDC_BTN_ADM_DATES, OnBtnAdmDates)
ON_BN_CLICKED(IDC_BTN_SEARCH, OnBtnSearch)
ON_BN_CLICKED(IDC_BTN_ACCOUNT_LIST, OnBtnAccountList)
ON_BN_CLICKED(IDC_BTN_FUND_LIST, OnBtnFundList)
ON_BN_CLICKED(IDC_RB_SRC_ALL,      OnBtnSearchAll)
ON_BN_CLICKED(IDC_RB_SRC_EFF_DATE, OnBtnSearchEffDate)
ON_BN_CLICKED(IDC_BTN_HISTORICAL, OnBtnHistorical)
ON_BN_CLICKED(IDC_CHK_FULL_MONEY_OUT_APPLICABLE, OnChkFullMoneyOutApplicable)
ON_BN_CLICKED(IDC_BTN_COPY_TO_NEW_MODEL,OnBtnCopyToNewModel)
ON_MESSAGE( UM_OPENHLDCOMPSEARCH, OpenHoldingCompDlg)

//}}AFX_MSG_MAP

END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// FeeModelDlg message handlers


//******************************************************************************
void FeeModelDlg::OnPostInitDialog()
{
   TRACE_METHOD( CLASSNAME, I_( "OnPostInitDialog" ) );
   SetUserAccesFunctionCode(UAF::FEE_MODEL);
   addBtnAddForPermissionCheck(IDC_BTN_ADD, IDC_LST_FEE_MODEL);
   addBtnDeleteForPermissionCheck(IDC_BTN_DEL, IDC_LST_FEE_MODEL);

   addControls();
   doRefresh(this, NULL);
   GetDlgItem(IDC_BTN_MORE)->EnableWindow( getParent()->doMoreRecordsExist( this, BF::AllContainerIds ) );
}

//******************************************************************************
void FeeModelDlg::ShowHideControls()
{
   TRACE_METHOD( CLASSNAME, I_( "ShowHideControls" ) );

   bool newItem = true;
   AbstractProcess* pFeeModelProc = dynamic_cast<AbstractProcess*>(getParent());
   if(pFeeModelProc)
   {
      DString dstrSchedSetupFreqAppl;
      pFeeModelProc->getField(this, BF::NullContainerId, ifds::SchedSetupFreqAppl, dstrSchedSetupFreqAppl, false);
      bool bShowSchedule = dstrSchedSetupFreqAppl == I_("Y");
      GetDlgItem(IDC_CMB_SCHEDULE)->ShowWindow(bShowSchedule ? SW_SHOW : SW_HIDE);
      GetDlgItem(IDC_ST_SCHEDULE)->ShowWindow(bShowSchedule ? SW_SHOW : SW_HIDE);
      
      DString dstrCalcRateTypeList;
      pFeeModelProc->getField(this, BF::NullContainerId, ifds::CalcRateTypeList, dstrCalcRateTypeList, false);
      bool bShowCalcRateType = dstrCalcRateTypeList.stripAll() != NULL_STRING;
      GetDlgItem(IDC_ST_CALC_RATE_TYPE)->ShowWindow (bShowCalcRateType ? SW_SHOW : SW_HIDE);
      GetDlgItem(IDC_CMB_CALC_RATE_TYPE)->ShowWindow(bShowCalcRateType ? SW_SHOW : SW_HIDE);


      DString dstrHoldingEntityAppl;
      pFeeModelProc->getField(this, BF::NullContainerId, ifds::HoldingEntityAppl, dstrHoldingEntityAppl, false);
      bool bShowHoldingEntity = dstrHoldingEntityAppl == I_("Y");
      GetDlgItem(IDC_ST_HLD_COMP)->ShowWindow(bShowHoldingEntity ? SW_SHOW : SW_HIDE);
      GetDlgItem(IDC_EDT_HOLDING_COMPANY)->ShowWindow(bShowHoldingEntity ? SW_SHOW : SW_HIDE);

      DString dstrCalcCurrencyAppl;
      pFeeModelProc->getField(this, BF::NullContainerId, ifds::CalcCurrencyAppl, dstrCalcCurrencyAppl, false);
      bool bShowCalcCurrency = dstrCalcCurrencyAppl == I_("Y");
      GetDlgItem(IDC_ST_CALC_CURRENCY)->ShowWindow(bShowCalcCurrency ? SW_SHOW : SW_HIDE);
      GetDlgItem(IDC_CMB_CALC_CURRENCY)->ShowWindow(bShowCalcCurrency ? SW_SHOW : SW_HIDE);

      DString dstrFundGrpTypeList;
      pFeeModelProc->getField(this, BF::NullContainerId, ifds::FundGrpTypeList, dstrFundGrpTypeList, false);
      bool bShowEligibleFundBy = dstrFundGrpTypeList != NULL_STRING;
      GetDlgItem(IDC_ST_ELIGIBLE_FUND_BY)->ShowWindow(bShowEligibleFundBy ? SW_SHOW : SW_HIDE);
      GetDlgItem(IDC_CMB_ELIGIBLE_FUND_BY)->ShowWindow(bShowHoldingEntity ? SW_SHOW : SW_HIDE);

      DString dstrAggregationMethodList;
      pFeeModelProc->getField(this, BF::NullContainerId, ifds::AggregationMethodList, dstrAggregationMethodList, false);
      bool bShowModelAggregationMethod = dstrAggregationMethodList != NULL_STRING;
      GetDlgItem(IDC_ST_AGG_METHOD)->ShowWindow(bShowModelAggregationMethod ? SW_SHOW : SW_HIDE);
      GetDlgItem(IDC_CMB_AGGREGATION_METHOD)->ShowWindow(bShowModelAggregationMethod ? SW_SHOW : SW_HIDE);

      DString dstrFeeModelOptionList;
      pFeeModelProc->getField(this, BF::NullContainerId, ifds::FeeModelOptionList, dstrFeeModelOptionList, false);
      bool bShowProgram = dstrFeeModelOptionList != NULL_STRING;
      GetDlgItem(IDC_ST_PROGRAM)->ShowWindow(bShowProgram ? SW_SHOW : SW_HIDE);
      GetDlgItem(IDC_CMB_PROGRAM)->ShowWindow(bShowProgram ? SW_SHOW : SW_HIDE);

      DString dstrFundGroupType;
      pFeeModelProc->getField(this, BF::NullContainerId, ifds::FundGroupType, dstrFundGroupType, false);
      bool bShowFundGroup = dstrFundGroupType != NULL_STRING;
      GetDlgItem(IDC_ST_FUND_GROUP)->ShowWindow(bShowFundGroup ? SW_SHOW : SW_HIDE);
      GetDlgItem(IDC_CMB_FUND_GROUP)->ShowWindow(bShowFundGroup ? SW_SHOW : SW_HIDE);

      bool isItemNew = pFeeModelProc->isCurrentListItemNew(this, IFASTBP_PROC::FEE_MODEL_LIST);
      GetDlgItem(IDC_BTN_ACCOUNT_LIST)->EnableWindow(!isItemNew);

      bool enableFeeParamSys = getParent()->hasReadPermission(UAF::FEE_PARAMETER_SYSTEM);

      GetDlgItem(IDC_BTN_FUND_LIST)->EnableWindow(!isItemNew && enableFeeParamSys);

      // Checkbox Full Money Out Applicable is only displayed for Advisor Fee.
      DString dstrFeeModelType;
      pFeeModelProc->getField(this, IFASTBP_PROC::FEE_MODEL_LIST, ifds::FeeModelType, dstrFeeModelType, false);
      GetDlgItem(IDC_CHK_FULL_MONEY_OUT_APPLICABLE)->ShowWindow(dstrFeeModelType.stripAll() == FEE_CODE_ADVISORY_FEE ? SW_SHOW : SW_HIDE);
   
      DString dstrFullMoneyOutApplicable; // 0 = Checked, 1 = Unchecked
      pFeeModelProc->getField(this, IFASTBP_PROC::FEE_MODEL_LIST, ifds::FullMoneyOutApplicable, dstrFullMoneyOutApplicable, false);
      ((CButton *)GetDlgItem (IDC_CHK_FULL_MONEY_OUT_APPLICABLE))->SetCheck(dstrFullMoneyOutApplicable.stripAll() == I_("0"));
   
      ((CButton *)GetDlgItem (IDC_CHK_FULL_MONEY_OUT_APPLICABLE))->EnableWindow(hasUpdatePermission(GetUserAccesFunctionCode()));
   }
}

//******************************************************************************
SEVERITY FeeModelDlg::doInit()
{
   SEVERITY sevRtn = SEVERE_ERROR;

   sevRtn = NO_CONDITION;
   getParent()->getParameter( FEEMODEL::FROM_SCR, m_frSCR );

   return(sevRtn);
}
//******************************************************************************
void FeeModelDlg::addControls( )
{
   TRACE_METHOD( CLASSNAME, I_( "addControls" ) );

   AddControl( CTRL_EDIT, IDC_EDT_SRC_FEE_MODEL_CODE, IFASTBP_PROC::FEE_MODEL_SEARCH, ifds::SrcFeeModelCode,0,0);
   AddControl( CTRL_EDIT, IDC_EDT_SRC_FEE_MODEL_DESC, IFASTBP_PROC::FEE_MODEL_SEARCH, ifds::SrcFeeModelDesc,0,0);

   AddControl( CTRL_EDIT, IDC_EDT_SRC_HLD_COMP_CODE, IFASTBP_PROC::FEE_MODEL_SEARCH, ifds::SrcHoldingCompCode,0,0);
   AddControl( CTRL_EDIT, IDC_EDT_SRC_HLD_COMP_DESC, IFASTBP_PROC::FEE_MODEL_SEARCH, ifds::SrcHoldingCompName,0,0);

//   DString dstrIsFromHoldingComp;
//   getParent()->getField(this, BF::NullContainerId, FEEMOD_FLDS::FROM_HOLDCOMP, dstrIsFromHoldingComp, false);
//   if(dstrIsFromHoldingComp == I_("Y"))
//   {
////      GetControl(IDC_EDT_SRC_HLD_COMP_CODE)->SetCtrlReadOnly(true);
//      //EnableControl(IDC_EDT_SRC_HLD_COMP_CODE, false);
//      //EnableControl(IDC_EDT_SRC_HLD_COMP_DESC, false);
//   }

   AddControl( CTRL_CHECKBOX, IDC_RB_SRC_ALL, CTRLFLAG_NOT_UPDATABLE | CTRLFLAG_GUI_FIELD );
   AddControl( CTRL_CHECKBOX, IDC_RB_SRC_EFF_DATE, CTRLFLAG_NOT_UPDATABLE | CTRLFLAG_GUI_FIELD );
   AddControl( CTRL_DATE, IDC_DTP_SRC_EFFECTIVE, IFASTBP_PROC::FEE_MODEL_SEARCH, ifds::AsofDate,0,0);
   
   ConnectControlToData(IDC_DTP_SRC_EFFECTIVE, true);
   LoadControl(IDC_DTP_SRC_EFFECTIVE);

   ConnectControlToData(IDC_EDT_SRC_FEE_MODEL_CODE, true);
   ConnectControlToData(IDC_EDT_SRC_FEE_MODEL_DESC, true);
   ConnectControlToData(IDC_EDT_SRC_HLD_COMP_CODE, true);
   ConnectControlToData(IDC_EDT_SRC_HLD_COMP_DESC, true);

   LoadControl(IDC_EDT_SRC_FEE_MODEL_CODE);
   LoadControl(IDC_EDT_SRC_FEE_MODEL_DESC);
   LoadControl(IDC_EDT_SRC_HLD_COMP_CODE);
   LoadControl(IDC_EDT_SRC_HLD_COMP_DESC);
   

   AddListControl( CLASSNAME,IDC_LST_FEE_MODEL, LV_FEE_MODEL_LIST, ifds::FeeModelListSet, IFASTBP_PROC::FEE_MODEL_LIST, 
                   0, true );

   AddControl( CTRL_EDIT, IDC_EDT_MODEL_CODE,    IFASTBP_PROC::FEE_MODEL_LIST, ifds::FeeModelCode,0,IDC_LST_FEE_MODEL);
   AddControl( CTRL_EDIT, IDC_EDT_DESCRIPTION,   IFASTBP_PROC::FEE_MODEL_LIST, ifds::FeeModelDesc,0,IDC_LST_FEE_MODEL);
   AddControl( CTRL_COMBO,IDC_CMB_FEE_MODEL_TYPE,IFASTBP_PROC::FEE_MODEL_LIST, ifds::FeeModelType,CTRLFLAG_INITCOMBO_BY_SUB_LIST,IDC_LST_FEE_MODEL);
   AddControl( CTRL_DATE, IDC_DTP_EFFECTIVE,     IFASTBP_PROC::FEE_MODEL_LIST, ifds::EffectiveDate,0,IDC_LST_FEE_MODEL);
   AddControl( CTRL_DATE, IDC_DTP_STOP,          IFASTBP_PROC::FEE_MODEL_LIST, ifds::StopDate,0,IDC_LST_FEE_MODEL);

   AddControl(CTRL_EDIT,   IDC_EDT_HOLDING_COMPANY,   IFASTBP_PROC::FEE_MODEL_LIST, ifds::HoldingCompCode,0,IDC_LST_FEE_MODEL);

   AddControl( CTRL_COMBO, IDC_CMB_PROGRAM,           IFASTBP_PROC::FEE_MODEL_LIST, ifds::Program,       CTRLFLAG_INITCOMBO_BY_SUB_LIST,IDC_LST_FEE_MODEL);

   AddControl( CTRL_COMBO, IDC_CMB_CALC_CURRENCY,     IFASTBP_PROC::FEE_MODEL_LIST, ifds::CalcCurrency,  CTRLFLAG_INITCOMBO_BY_SUB_LIST,IDC_LST_FEE_MODEL);
   AddControl( CTRL_COMBO, IDC_CMB_ELIGIBLE_FUND_BY,  IFASTBP_PROC::FEE_MODEL_LIST, ifds::EligibleFundBy,CTRLFLAG_INITCOMBO_BY_SUB_LIST,IDC_LST_FEE_MODEL);
   AddControl( CTRL_COMBO, IDC_CMB_FUND_GROUP,        IFASTBP_PROC::FEE_MODEL_LIST, ifds::FeeModelFundGroup,CTRLFLAG_INITCOMBO_BY_SUB_LIST,IDC_LST_FEE_MODEL);
   AddControl( CTRL_COMBO, IDC_CMB_AGGREGATION_METHOD,IFASTBP_PROC::FEE_MODEL_LIST, ifds::ModelAggregationMethod,CTRLFLAG_INITCOMBO_BY_SUB_LIST,IDC_LST_FEE_MODEL);

   AddControl( CTRL_COMBO, IDC_CMB_SCHEDULE,          IFASTBP_PROC::FEE_MODEL_LIST, ifds::ScheduleFreqID,CTRLFLAG_INITCOMBO_BY_SUB_LIST,IDC_LST_FEE_MODEL);
   AddControl( CTRL_COMBO, IDC_CMB_CALC_RATE_TYPE,    IFASTBP_PROC::FEE_MODEL_LIST, ifds::CalcRateType,CTRLFLAG_INITCOMBO_BY_SUB_LIST,IDC_LST_FEE_MODEL);
   AddControl( CTRL_CHECKBOX, IDC_CHK_FULL_MONEY_OUT_APPLICABLE, IFASTBP_PROC::FEE_MODEL_LIST, ifds::FullMoneyOutApplicable, CTRLFLAG_DEFAULT, IDC_LST_FEE_MODEL);

   dynamic_cast<DSTEdit*>(GetControl( IDC_EDT_MODEL_CODE ) )->SetMaxCharNum( 6 );

}

//*********************************************************************************
void FeeModelDlg::ControlUpdated(UINT controlID,
                                 const DString &strValue )
{
   switch( controlID )
   {
      case IDC_CMB_FEE_MODEL_TYPE: 
         {
            ShowHideControls();
         }
         break; 

      default:
         break;

   }
}
//******************************************************************************
void FeeModelDlg::SetDlgCaption()
{
   TRACE_METHOD( CLASSNAME, I_( "SetDlgCaption" ) );
/*   DString strShrNum, strAccountNum, strEmptyString,dstrEntityName;
   getParent()->getField(this, IFASTBP_PROC::MFACOUNT, ifds::ShrNum, strShrNum, false);
   getParent()->getField(this, IFASTBP_PROC::MFACOUNT, ifds::AccountNum, strAccountNum, false);
   getParent()->getField( this, FEEPARAM::PRIMARY_ACCOUNT_OWNER, dstrEntityName );

   SetShrAcctCaption(strShrNum, strAccountNum, dstrEntityName);*/
}

//******************************************************************************

bool FeeModelDlg::doRefresh( GenericInterface * rpGICaller, 
                             const I_CHAR * szOriginalCommand )
{
   TRACE_METHOD( CLASSNAME, I_( "doRefresh" ) );

   SetDlgCaption();
   ConnectControlsToData();
   LoadListControl(IDC_LST_FEE_MODEL);

   return(true);
}

//******************************************************************************
void FeeModelDlg::OnBtnReset() 
{
   TRACE_METHOD( CLASSNAME, I_( "OnBtnReset" ) );
   ResetListItem( IDC_LST_FEE_MODEL );
   GetList( IDC_LST_FEE_MODEL )->SetFocus();  
}

//*********************************************************************************

void FeeModelDlg::OnBtnAdd()
{
   TRACE_METHOD( CLASSNAME, I_( "OnBtnAdd" ) );
   AddToListControl( IDC_LST_FEE_MODEL );
   GetList( IDC_LST_FEE_MODEL )->SetFocus();
}

//********************************************************************************
void FeeModelDlg::OnBtnDel()
{
   TRACE_METHOD( CLASSNAME, I_( "OnBtnDel" ) );
   bool bDelete = true;
	//CString cstr;
	//cstr.LoadString( TXT_WARNING_LOST_CHANGE );

   AbstractProcess* parent = (AbstractProcess*)getParent();
      
   bool isNew =  parent->isCurrentListItemNew(this, IFASTBP_PROC::FEE_MODEL_LIST);   
   
   
   if( !isNew && IDNO == AfxMessageBox( TXT_FEE_MODEL_DEL_WARNING, MB_YESNO ) )
		bDelete = false;

   if(bDelete)
   {
      DeleteFromListControl( IDC_LST_FEE_MODEL );
   }
   GetList( IDC_LST_FEE_MODEL )->SetFocus();
}

//**********************************************************************************
void FeeModelDlg::OnBtnMore()
{
   TRACE_METHOD( CLASSNAME, I_( "OnBtnMore" ) );
   CWaitCursor wait;
   static int cursel;
   cursel = GetList( IDC_LST_FEE_MODEL )->GetNextItem(-1, LVIS_SELECTED | LVNI_FOCUSED);  
   const DString *crtKey = &getParent()->getCurrentListItemKey( this,IFASTBP_PROC::FEE_MODEL_LIST );
   if( getParent()->performSearch( this, BF::AllContainerIds, SEARCH_NEXT_BLOCK ) <= WARNING )
   {
      LoadListControl( IDC_LST_FEE_MODEL );
      if( *crtKey != NULL_STRING )
      {
         GetList( IDC_LST_FEE_MODEL )->SetSelection( crtKey );
      }
   }
   GetDlgItem(IDC_BTN_MORE)->EnableWindow( getParent()->doMoreRecordsExist( this, BF::AllContainerIds ) );
   GetList( IDC_LST_FEE_MODEL )->SetSelection(cursel, true, true);
   SetMessageStatusBar(NULL_STRING);   

}

//**********************************************************************************
void FeeModelDlg::OnBtnAdmDates() 
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OnBtnAdminDates" ) );
   CWaitCursor wait;
   ShowAdminDates( IFASTBP_PROC::FEE_MODEL_LIST );
}

//**********************************************************************************
void FeeModelDlg::OnBtnSearch() 
{
   TRACE_METHOD( CLASSNAME, I_( "OnBtnSearch" ) );
   bool bSearch = true;
   if(getParent()->workSessionHasUpdates())
   {
	   CString cstr;
	   cstr.LoadString( TXT_WARNING_LOST_CHANGE );
		if( IDNO == AfxMessageBox( TXT_WARNING_LOST_CHANGE, MB_YESNO ) )
			bSearch = false;
      else
         resetChanges();
   }
   if(bSearch)
   {
      CWaitCursor wait;
      static int cursel;
      if( getParent()->performSearch( this, BF::AllContainerIds, SEARCH_START ) <= WARNING )
      {
         LoadListControl( IDC_LST_FEE_MODEL);
         GetDlgItem(IDC_BTN_MORE)->EnableWindow( getParent()->doMoreRecordsExist( this, BF::AllContainerIds ) );
      }
      SetMessageStatusBar(NULL_STRING);   
   }
}

//**********************************************************************************
bool FeeModelDlg::doDisablePermCheckButton(UINT nID)
{
   if(nID == IDC_BTN_ADD)
   {      
      if( m_frSCR.upperCase() != I_("SYSTEM") )
      {
         return false;
      }
   }

   if(nID == IDC_BTN_DEL)
   {      
      DString dstrLastProcDate;
      getParent()->getField(this, IFASTBP_PROC::FEE_MODEL_LIST, ifds::LastProcDate, dstrLastProcDate, false);
      if(dstrLastProcDate != NULL_STRING)
         return true;
   }

   return false;
}

//**********************************************************************************
void FeeModelDlg::OnBtnAccountList() 
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OnBtnFeeModel" ) );

   bool bSearch = true;
   if(getParent()->workSessionHasUpdates())
   {
	   CString cstr;
	   cstr.LoadString( TXT_WARNING_LOST_CHANGE );
		if( IDNO == AfxMessageBox( TXT_WARNING_LOST_CHANGE, MB_YESNO ) )
			bSearch = false;
      else
         resetChanges();
   }
   if(bSearch)
   {
      try
      {
         E_COMMANDRETURN eRtn = CMD_CANCEL;
         CWaitCursor wait;  

         DString dstrFeeModelCode;

         getParent()->getField(this, IFASTBP_PROC::FEE_MODEL_LIST, ifds::FeeModelCode, dstrFeeModelCode, false);

         DString dstrParamsIDI;
         addIDITagValue (dstrParamsIDI, I_("BrowserTitle"), I_("Fee Model Association"));
         addIDITagValue (dstrParamsIDI, I_("screen"),       I_("AcctAssociate"));
         addIDITagValue (dstrParamsIDI, I_("from_screen"),  I_("FeeModelDlg"));
         addIDITagValue (dstrParamsIDI, I_("FeeModelCode"), dstrFeeModelCode);
         setParameter (I_("UrlParams"), dstrParamsIDI);

         CString cstrBrowserTitle;
         cstrBrowserTitle.LoadString(TXT_FEE_MODEL_ASSOCIATION_TITLE);
         setParameter(I_("BrowserTitle"), DString(cstrBrowserTitle));

         eRtn = invokeCommand( getParent(), CMD_BPROC_ACCOUNT_ASSOCIATION, PROC_SUPPORT, true, NULL );
         switch( eRtn )
         {
            case CMD_OK:
            case CMD_MODELESS_INPROCESS:
               {
               }
            case CMD_CANCEL:
               break;

            default:
               // Display error
               ConditionMessageBox( FRAMEBELOW(), GETHIGHESTSEVERITY() );
               break;
         }

         BFWorkSession * worksession = getBFWorkSession();
         if(worksession->getHadTrxnError() || worksession->getIsEndSession())
         {
            PostMessage( WM_COMMAND, IDCANCEL );
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
}

//**********************************************************************************
void FeeModelDlg::OnBtnFundList() 
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OnBtnFeeModel" ) );

   bool bSearch = true;
   if(getParent()->workSessionHasUpdates())
   {
	   CString cstr;
	   cstr.LoadString( TXT_WARNING_LOST_CHANGE );
		if( IDNO == AfxMessageBox( TXT_WARNING_LOST_CHANGE, MB_YESNO ) )
			bSearch = false;
      else
         resetChanges();
   }
   if(bSearch)
   {
      try
      {
         E_COMMANDRETURN eRtn = CMD_CANCEL;
         CWaitCursor wait;  

         DString dstrFeeModelCode;

         getParent()->getField(this, IFASTBP_PROC::FEE_MODEL_LIST, ifds::FeeModelCode, dstrFeeModelCode, false);
         setParameter (MFCAN_IP_PARAM::FEE_MODEL_CODE, dstrFeeModelCode);
         DString dstrHoldingCompCode;
         FeeModelProcess* pFeeModelProcess = dynamic_cast<FeeModelProcess*>(getParent());
         if(pFeeModelProcess)
         {
            dstrHoldingCompCode = pFeeModelProcess->getHoldingCompCode(); 
         }

         setParameter (MFCAN_IP_PARAM::HOLDING_COMP_CODE, dstrHoldingCompCode);

         eRtn = invokeCommand( getParent(), CMD_BPROC_FEE_PARAMETER_SYSTEM, PROC_MAINT, true, NULL );
         switch( eRtn )
         {
            case CMD_OK:
            case CMD_MODELESS_INPROCESS:
               {
               }
            case CMD_CANCEL:
               break;

            default:
               // Display error
               ConditionMessageBox( FRAMEBELOW(), GETHIGHESTSEVERITY() );
               break;
         }
         BFWorkSession * worksession = getBFWorkSession();
         if(worksession->getHadTrxnError() || worksession->getIsEndSession())
         {
            PostMessage( WM_COMMAND, IDCANCEL );
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
}

void FeeModelDlg::OnBtnSearchAll() 
{
   TRACE_METHOD( CLASSNAME, I_( "OnBtnSearchAll" ) );
   // TODO: Add your control notification handler code here
   getParent()->setField( this, IFASTBP_PROC::FEE_MODEL_SEARCH, ifds::SearchAll, I_("Y"));
   getParent()->setField( this, IFASTBP_PROC::FEE_MODEL_SEARCH, ifds::AsofDate, I_("12319999"));
   LoadControl(IDC_DTP_SRC_EFFECTIVE);

}

void FeeModelDlg::OnBtnSearchEffDate() 
{
   TRACE_METHOD( CLASSNAME, I_( "OnBtnSearchEffDate" ) );
   // TODO: Add your control notification handler code here
   getParent()->setField( this, IFASTBP_PROC::FEE_MODEL_SEARCH, ifds::SearchAll, I_("N"));
	DString dstrCurBusDate;
   DSTCWorkSession *dstWorkSession = dynamic_cast<DSTCWorkSession *>(getParent()->getBFWorkSession());
	dstWorkSession->getMgmtCoOptions()->getField(ifds::CurrBusDate, dstrCurBusDate, BF::HOST);
   dstrCurBusDate.strip();
   getParent()->setField( this, IFASTBP_PROC::FEE_MODEL_SEARCH, ifds::AsofDate, dstrCurBusDate );
   LoadControl(IDC_DTP_SRC_EFFECTIVE);

}


//******************************************************************************
void FeeModelDlg::OnBtnHistorical()
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OnBtnHistorical" ) );

   E_COMMANDRETURN eRtn = CMD_CANCEL;

   IFastHistoricalInfo historicalInfo;
   historicalInfo( this, IFASTBP_PROC::FEE_MODEL_LIST, I_("SINGLE") );
}

bool FeeModelDlg::canCancel()
{
   BFWorkSession * worksession = getBFWorkSession();
   if(!worksession->getHadTrxnError() && !worksession->getIsEndSession() && getParent()->workSessionHasUpdates())
   {
      DiscardMsgDlg discardDlg(NULL, TXT_DISCARD_MSGA, TXT_DISCARD_MSGB, TXT_DISCARD);

      return(discardDlg.DoModal() != IDCANCEL);         
   }

   return(true);
}

bool FeeModelDlg::isKillWorkSessiononTxnError()
{
   DString dstrHoldingCompCode;
   FeeModelProcess* pFeeModelProcess = dynamic_cast<FeeModelProcess*>(getParent());
   if(pFeeModelProcess)
   {
      dstrHoldingCompCode = pFeeModelProcess->getHoldingCompCode(); 
   }
   return dstrHoldingCompCode == NULL_STRING;
};

//******************************************************************************
void FeeModelDlg::DoListItemChanged(UINT listControlID, const DString &strKey,
                                       bool bIsNewItem, bool bIsDummyItem)
{
   if(listControlID ==  IDC_LST_FEE_MODEL)
   {
      ShowHideControls();

      AbstractProcess* pFeeModelProc = dynamic_cast<AbstractProcess*>(getParent());
      if(pFeeModelProc)
      {
         DString dstrAllowCopy;
         pFeeModelProc->getField(this, IFASTBP_PROC::FEE_MODEL_LIST, ifds::AllowCopy, dstrAllowCopy, false);
         dstrAllowCopy.strip().upperCase();
         ((CButton *)GetDlgItem (IDC_BTN_COPY_TO_NEW_MODEL))->EnableWindow(dstrAllowCopy==I_("Y") && !bIsNewItem);
      }
   }
}

//******************************************************************************
void FeeModelDlg::resetChanges() 
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "resetChanges" ) );
   const BFDataGroupId& dataGroupId = getParent()->getDataGroupId(); 
   DSTCWorkSession* pDSTCWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());   
   pDSTCWorkSession->reset(dataGroupId, true);
	const DString *crtKey = &getParent()->getCurrentListItemKey( this, IFASTBP_PROC::FEE_MODEL_LIST);
   
   if (crtKey && !(*crtKey).empty())
	{
		LoadListControl(IDC_LST_FEE_MODEL);
		GetList (IDC_LST_FEE_MODEL)->SetSelection (crtKey);
	 	getParent()->setCurrentListItem (this, IFASTBP_PROC::FEE_MODEL_LIST, *crtKey);
	}
}

//************************************************************************************
LRESULT FeeModelDlg::OpenHoldingCompDlg( WPARAM, LPARAM ) 
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OpenHoldingCompDlg" ) );

   try
   {
      E_COMMANDRETURN eRtn = CMD_CANCEL;

      DString dstrHoldingCompCode;

      GetControlText( IDC_EDT_HOLDING_COMPANY, dstrHoldingCompCode);
      setParameter( MFCAN_IP_PARAM::HOLDING_COMP_CODE, dstrHoldingCompCode );


      //invoke the broker dialog and process
      eRtn = invokeCommand( getParent(), CMD_BPROC_HOLDING_COMP, PROC_SUPPORT, true, NULL );
      switch( eRtn )
      {
         case CMD_OK:
         case CMD_MODELESS_INPROCESS:
            {
               //get the broker code that the user selected from the branch list and 
               //set the field on the FeeParamSys object
               DString dstrHoldingCompCodeNew;

               getParameter( MFCAN_IP_PARAM::HOLDING_COMP_CODE, dstrHoldingCompCodeNew);
               if( !dstrHoldingCompCodeNew.empty() )
               {
                  SetControlText(IDC_EDT_HOLDING_COMPANY, dstrHoldingCompCodeNew);
               }
               break;
            }
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
   return(0);
}

//******************************************************************************
BOOL FeeModelDlg::PreTranslateMessage (MSG* pMsg) 
{

   if( pMsg->message == WM_KEYDOWN && ( int )( pMsg->wParam ) == VK_F4 && !IsSelectedCtrlUpdateable() )
      return(TRUE);

   if( pMsg->message == WM_KEYDOWN&&( int )( pMsg->wParam ) == VK_F4 )
   {
      if( GetFocus() == GetDlgItem( IDC_EDT_HOLDING_COMPANY ) )
      {
         PostMessage( UM_OPENHLDCOMPSEARCH );
      }
   }

   return(BaseMainDlg::PreTranslateMessage( pMsg ));
}

//******************************************************************************
void FeeModelDlg::OnChkFullMoneyOutApplicable()
{
    // 0 = Checked, 1 = Unchecked
    DString dstrCheckValue = ((CButton *)GetDlgItem (IDC_CHK_FULL_MONEY_OUT_APPLICABLE))->GetCheck() ? I_("0") : I_("1");

    getParent()->setField(this, IFASTBP_PROC::FEE_MODEL_LIST, ifds::FullMoneyOutApplicable, dstrCheckValue, false);
}

//***************************************************************************
void FeeModelDlg::OnBtnCopyToNewModel()
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OnBtnCopyToNewModel" ) );

   try
   {
      E_COMMANDRETURN eRtn = CMD_CANCEL;
      CWaitCursor wait;  

      DString dstrFeeModelCode, dstrFeeModelRecid, dstrFeeModelDesc;

      getParent()->getField(this, IFASTBP_PROC::FEE_MODEL_LIST, ifds::FeeModelCode, dstrFeeModelCode, false);
      getParent()->getField(this, IFASTBP_PROC::FEE_MODEL_LIST, ifds::FeeModelRecid, dstrFeeModelRecid, false);
      getParent()->getField(this, IFASTBP_PROC::FEE_MODEL_LIST, ifds::FeeModelDesc, dstrFeeModelDesc, false);

      dstrFeeModelCode.strip().upperCase();
      dstrFeeModelRecid.strip().upperCase();
      dstrFeeModelDesc.strip();

      setParameter (I_("FeeModelCode"), dstrFeeModelCode);
      setParameter (I_("FeeModelRecid"), dstrFeeModelRecid);
      setParameter (I_("FeeModelDesc"), dstrFeeModelDesc);

      eRtn = invokeCommand( getParent(), CMD_BPROC_FEE_MODEL_COPY_TO, PROC_NO_TYPE, true, NULL );
      switch( eRtn )
      {
         case CMD_MODELESS_INPROCESS:
         case CMD_OK:
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
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/FeeModelDlg.cpp-arc  $
// 
//    Rev 1.6   May 19 2006 09:54:46   popescu
// Incident# 626125 - expand the number of allowed chars for fee model code to 6, from 4.
// 
//    Rev 1.5   Sep 15 2005 15:12:04   popescu
// Incident#403519 - added CLASSNAME as the fifth parameter to  BaseMainDlg constructor
// 
//    Rev 1.4   Oct 15 2004 16:06:36   FENGYONG
// PTS10034766 - disable add and delete when access FeeModel from fundsponsor fee model screen.
// 
//    Rev 1.3   Sep 15 2004 16:45:30   FENGYONG
// limit FeeModelCode to 4 charactors
// 
//    Rev 1.2   Aug 31 2004 17:23:42   FENGYONG
// change field name
// 
//    Rev 1.1   Aug 10 2004 11:28:16   FENGYONG
// PET 1117 FN5 - Client Condition Fee
// 
//    Rev 1.0   Aug 09 2004 09:55:46   FENGYONG
// Initial Revision
*/





