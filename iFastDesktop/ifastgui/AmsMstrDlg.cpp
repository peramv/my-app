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
//    Copyright 2002 by International Financial Data Services.
//
//******************************************************************************
//
// ^FILE   : AMsMstrDlg.cpp
// ^AUTHOR : Yingbao Li
// ^DATE   : Nov. 7,2002
//
// ----------------------------------------------------------
//
// ^CLASS    : AmsMstrDlg
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :  
//
//******************************************************************************
#include "stdafx.h"
#include "mfdstc.h"
#include "AmsMstrDlg.h"

#include <configmanager.hpp>
#include <bfproc\abstractprocess.hpp>

#include <ifastcbo\dstcommonfunction.hpp>
#include <ifastcbo\dstcworksession.hpp>
#include <ifastcbo\mgmtco.hpp>

#include <ifastbp\AmsMstProcessincludes.h>
#include <ifastbp\mfcaninterprocparam.hpp>

#include <uibase\dstcombobox.h>
#include <uibase\dstedit.h>
#include <uibase\DSTListCtrl.h>

#include <ifastdataimpl\dse_dstc0083_vw.hpp>

#ifndef INCLUDED_ASSERT_H
#define INCLUDED_ASSERT_H
#include <assert.h>
#endif

extern CLASS_IMPORT const I_CHAR* CMD_GUI_AMS_GLOBAL;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_AMS_LMT_OVERRIDE;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_AMS_DELTA_ALLOC;

#include <bfproc\concretedialogcreator.hpp>
static ConcreteDialogCreator< AmsMstrDlg > dlgCreator( CMD_GUI_AMS_GLOBAL );

#ifdef _DEBUG
   #define new DEBUG_NEW
   #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


namespace
{
   const I_CHAR * const CLASSNAME			= I_("AmsMstrDlg");
   const I_CHAR * const YES					= I_("Y");
   const I_CHAR * const NO					   = I_("N");
   const I_CHAR * const FUND_CODE			= I_("FundCode");
   const I_CHAR * const CLASS_CODE        = I_("ClassCode");
   const I_CHAR * const FUND_NUMBER       = I_("FundNumber");
   const I_CHAR * const CURRENC				= I_("Currency");
   const I_CHAR * const PERCENT				= I_("Percentage");
   const I_CHAR * const TARGET_ASSET		= I_("RO");
   const I_CHAR * const FUND_OF_FUNDS		= I_("FOF");
   const I_CHAR * const REBALANCE			= I_("RB");
   const I_CHAR * const THRESHOLD_AMT		= I_("ThresholdAmt");
   const I_CHAR * const IDI_LABEL1			= I_( "LABEL1" );
   const UINT AMS_MST_SEARCH				   = 2001;
   const I_CHAR * const SEARCH_TYPE_EFFECTIVE_DATE	= I_( "EffectiveDate" );
   const I_CHAR * const MarketValueWeight   = I_("M");
}

namespace CND
{  
   // Conditions used
   extern const long GUI_ERR_UNKNOWN_EXCEPTION;
   extern const long GUI_SEARCH_CRITERIAS_NOT_DEFINED1;
}

namespace ifds
{   
   extern CLASS_IMPORT const BFTextFieldId AssocFundNum;
}

namespace UAF
{
   extern CLASS_IMPORT I_CHAR * const AMS_GLOBAL;
}

namespace AMS_LMT_Para
{
	const I_CHAR * const AMS_CODE	  = I_("AMSCode");
	const I_CHAR * const AMS_REC_ID = I_("AMSRecId");
   const I_CHAR * const FROM_SCR	  = I_( "FromScr" );
}

namespace AMS_DELTA_ALLOC_Para
{
	const I_CHAR * const AMS_CODE	    = I_("AMSCode");
	const I_CHAR * const AMS_TYPE	    = I_("AMSType");
	const I_CHAR * const AMS_EFFECTIVE_DATE = I_("EffectiveDate");
	const I_CHAR * const ACCOUNT_NUM    = I_("AccountNum");
	const I_CHAR * const AMS_REC_ID     = I_("AMSRecId");
	const I_CHAR * const AMS_SEARCH_DATE = I_("AMSSearchDate");
	const I_CHAR * const AMS_SEARCH_CODE = I_("AMSSearchCode");
}

//*****************************************************************************
// Public methods
//*****************************************************************************
AmsMstrDlg::AmsMstrDlg(CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: BaseMainDlg( AmsMstrDlg::IDD, pParent, pGIC, pGIParent, rCommand, CLASSNAME )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
  
   //{{AFX_DATA_INIT(AmsMstrDlg)
   //}}AFX_DATA_INIT 

   m_bAddCopy = false;

}

//*****************************************************************************
void AmsMstrDlg::DoDataExchange( CDataExchange* pDX )
{
   BaseMainDlg::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(AmsMstrDlg)

   //}}AFX_DATA_MAP
}

//*****************************************************************************
SEVERITY AmsMstrDlg::doInit()
{
   TRACE_METHOD( CLASSNAME, DOINIT );
   getParameter( AMS_Para::FROM_SCR, _dstrFromScr );
   return(NO_CONDITION);
}

//*****************************************************************************
BEGIN_MESSAGE_MAP(AmsMstrDlg, BaseMainDlg)
//{{AFX_MSG_MAP(AmsMstrDlg)

ON_BN_CLICKED( IDC_BTN_SEARCH, OnBtnSearch )
ON_BN_CLICKED( IDC_BTN_RESET,  OnBtnReset )
ON_BN_CLICKED( IDC_BTN_MORE,  OnBtnMore )
ON_BN_CLICKED( IDC_BTN_AMS_ADD,  OnBtnAddAms )
ON_BN_CLICKED( IDC_BTN_AMS_DEL,  OnBtnDelAms )
ON_BN_CLICKED( IDC_BTN_ALLOC_ADD,  OnBtnAddAlloc )
ON_BN_CLICKED( IDC_BTN_ALLOC_DEL,  OnBtnDelAlloc )
ON_MESSAGE( UM_OPENFUNDCLASSLISTDLG, OpenFundClassListDlg )
ON_BN_CLICKED( IDC_BTN_LIMITATION,  OnBtnLmtOverride )
ON_BN_CLICKED( IDC_BTN_ADM_DATES,  OnBtnAdmDates )
ON_BN_CLICKED( IDC_BTN_HISTORICAL,  OnBtnHistorical )
ON_BN_CLICKED( IDC_BTN_AMS_ADD_COPY,  OnBtnAddCopy )
ON_BN_CLICKED( IDC_BTN_DELTA, onBtnDeltaAlloc)
ON_CBN_SELCHANGE(IDC_CMB_TARGET_MIX_OPT, OnSelchangeTargetMixOpt)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//*****************************************************************************
// Message handlers
//*****************************************************************************
BOOL AmsMstrDlg::OnInitDialog() 
{
   TRACE_METHOD( CLASSNAME, ONINITDIALOG );

   BaseMainDlg::OnInitDialog();
   return(TRUE);
}

//*****************************************************************************
void AmsMstrDlg::OnBtnSearch()
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OnBtnSearch" ) );
   CWaitCursor wait;

   BaseControl* pBControl = dynamic_cast<BaseControl*>(GetFocus());
   if( pBControl )  pBControl->Store();
	bool bSearch = true;
	DString dtrUpdated;
	getParent()->getField(this,BF::NullContainerId,AMS_PROC::updated,dtrUpdated,false );
	if(dtrUpdated.strip() == YES )
	{
		if( AfxMessageBox(TXT_WARNING_LOST_CHANGE,MB_YESNO ) == IDNO )
		{
			bSearch = false;
		}
	}

	if( bSearch )
	{		
		SEVERITY sev = getParent()->performSearch( this, IFASTBP_PROC::AMS_MST_LIST, SEARCH_START );
		if( sev  <= WARNING )
		{
			LoadListControl(IDC_LST_AMSINFO);
            GetDlgItem(IDC_BTN_MORE)->EnableWindow( getParent()->doMoreRecordsExist( this, BF::AllContainerIds ) );
			getParent()->getField(this,IFASTBP_PROC::AMS_MST_SEARCH,ifds::EffectiveDate,_dstrEffectiveDate,false);
			getParent()->getField(this,IFASTBP_PROC::AMS_MST_SEARCH,ifds::AMSType,_dstrAmsType,false);
			getParent()->getField(this,IFASTBP_PROC::AMS_MST_SEARCH,ifds::AMSCode,_dstrAmsCode,false);
			SetDefID(IDOK);

		}
		else
		{      
			 LoadListControl(IDC_LST_AMSINFO);
			 LoadControls(AMS_MST_SEARCH); 
			 SetDefID(IDC_BTN_SEARCH);

		}

		setUpdateFlag(false);
	}
}

//********************************************************************************
void AmsMstrDlg::OnBtnMore()
{
   TRACE_METHOD( CLASSNAME, I_("OnBtnMore"));
   CWaitCursor wait;

   const DString *crtKey = &getParent()->getCurrentListItemKey( this, IFASTBP_PROC::AMS_MST_LIST );

   if( getParent()->performSearch( this, IFASTBP_PROC::AMS_MST_LIST, SEARCH_NEXT_BLOCK ) <= WARNING )
   {
      LoadListControl(IDC_LST_AMSINFO);   
   }
   GetDlgItem(IDC_BTN_MORE)->EnableWindow( getParent()->doMoreRecordsExist( this, BF::AllContainerIds ) );
}

//******************************************************************************
void AmsMstrDlg::OnBtnReset()
{
   TRACE_METHOD( CLASSNAME, I_("OnBtnReset"));

	ResetListItem( IDC_LST_AMSINFO );
}

//*********************************************************************
void AmsMstrDlg::OnBtnAddAms()
{
	TRACE_METHOD( CLASSNAME, I_("OnBtnAddAms") );
	AddToListControl( IDC_LST_AMSINFO );
}

//**********************************************************************
void AmsMstrDlg::OnBtnDelAms()
{
  TRACE_METHOD( CLASSNAME, I_("OnBtnDelAms") );

  DeleteFromListControl( IDC_LST_AMSINFO ); 
}

//************************************************************************
void AmsMstrDlg::OnBtnAddAlloc()
{
  TRACE_METHOD( CLASSNAME, I_("OnBtnAddAlloc") );
  AddToListControl( IDC_LIST_ALLOCATION );
  EnableAllocationEditControls(true);
}

//************************************************************************
void AmsMstrDlg::OnBtnDelAlloc()
{
  TRACE_METHOD( CLASSNAME, I_("OnBtnDelAlloc") );
  DeleteFromListControl( IDC_LIST_ALLOCATION ); 
  EnableAllocationControls();
}

//*****************************************************************************
void AmsMstrDlg::OnPostInitDialog()
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OnInit" ) );

   TRACE_METHOD( CLASSNAME, ONPOSTINITDIALOG );
   SetUserAccesFunctionCode(UAF::AMS_GLOBAL);
   addBtnAddForPermissionCheck(IDC_BTN_AMS_ADD_COPY, IDC_LST_AMSINFO);
   addBtnAddForPermissionCheck(IDC_BTN_AMS_ADD, IDC_LST_AMSINFO);
   addBtnDeleteForPermissionCheck(IDC_BTN_AMS_DEL, IDC_LST_AMSINFO);
	addBtnAddForPermissionCheck(IDC_BTN_ALLOC_ADD, IDC_LIST_ALLOCATION);
	addBtnDeleteForPermissionCheck(IDC_BTN_ALLOC_DEL, IDC_LIST_ALLOCATION);
	addControlsForSearchCriteria();
	DisplaySearchRelated();
	addControls( );
	GetDlgItem(IDC_BTN_MORE)->EnableWindow( getParent()->doMoreRecordsExist( this, BF::AllContainerIds ) );

	getParent()->setParameter( AMS_Para::FROM_SCR, _dstrFromScr );

	SEVERITY sev = NO_CONDITION;
   sev = getParent()->performSearch( this, IFASTBP_PROC::AMS_MST_LIST, SEARCH_START );
	if( sev  <= WARNING )
	{
		GetDlgItem(IDC_BTN_MORE)->EnableWindow( getParent()->doMoreRecordsExist( this, BF::AllContainerIds ) );

		LoadListControl(IDC_LST_AMSINFO);
	}
	else
	{      
		 ConditionMessageBox( MYFRAME(), GETCURRENTHIGHESTSEVERITY() );
	}

 }

//******************************************************************************
void AmsMstrDlg::LoadAMSAllocationCombo()
{
	CString cstrYes, cstrNo;
	cstrYes.LoadString(IDS_TXT_YES);
	cstrNo.LoadString(IDS_TXT_NO);
	CComboBox* cb=static_cast<CComboBox*>(GetDlgItem(IDC_CMB_FUND_ALLOC));
	cb->AddString(cstrYes);
	cb->AddString(cstrNo);
	CComboBox* cbDefault=static_cast<CComboBox*>(GetDlgItem(IDC_CMB_DEFAULT_ALLOC));
	cbDefault->InsertString(0,cstrYes);
	cbDefault->InsertString(1,cstrNo);
	cbDefault->InsertString(2,I_(""));
	DString dstrValue;
	getParent()->getField(this,ifds::FundAlloc,dstrValue,false);
	dstrValue.strip().upperCase();
	if (dstrValue == NO)
		cb->SetCurSel(1);
	else
		cb->SetCurSel(0);
	getParent()->getField(this,ifds::DefaultAlloc,dstrValue,false);
	dstrValue.strip().upperCase();
	if (dstrValue == YES)
		cbDefault->SetCurSel(0);
	else
		cbDefault->SetCurSel(1);
  }

//******************************************************************************
bool AmsMstrDlg::doRefresh( GenericInterface * rpGICaller,
                            const I_CHAR* szOriginalCommand )
{ 
   TRACE_METHOD( CLASSNAME, DOREFRESH );
   return(true);
}

//********************************************************************************
bool AmsMstrDlg::addControls( )
{ 
   TRACE_METHOD( CLASSNAME, I_("addControls") );

   AddListControl(CLASSNAME, IDC_LST_AMSINFO, I_("AMS_MSTR_INFO"), ifds::AMSGlobalHeading, 
		IFASTBP_PROC::AMS_MST_LIST );
   AddListControl(CLASSNAME, IDC_LIST_ALLOCATION, I_("AMS_FUND_ALLOC"), 
		ifds::AMSFundAllocHeading, IFASTBP_PROC::AMS_ALLOCATION_LIST,IDC_LST_AMSINFO,true,
		LISTFLAG_NOT_AUTO_ADD );

   AddControl( CTRL_EDIT, IDC_EDT_AMSCODE, IFASTBP_PROC::AMS_MST_LIST, 
               ifds::AMSCode, 0 , IDC_LST_AMSINFO);

    AddControl( CTRL_EDIT, IDC_EDT_ENGLISH_SHORT_NAME, IFASTBP_PROC::AMS_MST_LIST, 
               ifds::EnglishShortName, 0 , IDC_LST_AMSINFO);
    AddControl( CTRL_EDIT, IDC_EDT_ENGLISH_NAME, IFASTBP_PROC::AMS_MST_LIST, 
               ifds::EnglishName, 0 , IDC_LST_AMSINFO);
    AddControl( CTRL_EDIT, IDC_EDT_ENGLISH_LONG_NAME, IFASTBP_PROC::AMS_MST_LIST, 
               ifds::EnglishLongName, 0 , IDC_LST_AMSINFO);
    AddControl( CTRL_EDIT, IDC_EDT_FRENCH_SHORT_NAME, IFASTBP_PROC::AMS_MST_LIST, 
               ifds::FrenchShortName, 0 , IDC_LST_AMSINFO);
    AddControl( CTRL_EDIT, IDC_EDT_FRENCH_NAME, IFASTBP_PROC::AMS_MST_LIST, 
               ifds::FrenchName, 0 , IDC_LST_AMSINFO);
    AddControl( CTRL_EDIT, IDC_EDT_FRENCH_LONG_NAME, IFASTBP_PROC::AMS_MST_LIST, 
               ifds::FrenchLongName, 0 , IDC_LST_AMSINFO);

	 AddControl( CTRL_COMBO, IDC_CMB_FUND_ALLOC, IFASTBP_PROC::AMS_MST_LIST, 
               ifds::FundAlloc, CTRLFLAG_INITCOMBO_BY_SUB_LIST , IDC_LST_AMSINFO);
	 AddControl( CTRL_COMBO, IDC_CMB_DEFAULT_ALLOC, IFASTBP_PROC::AMS_MST_LIST, 
               ifds::DefaultAlloc, CTRLFLAG_INITCOMBO_BY_SUB_LIST , IDC_LST_AMSINFO);
   AddControl( CTRL_COMBO, IDC_CMB_AMS_GLOBAL_TRADE_PRNT_FUND, IFASTBP_PROC::AMS_MST_LIST, 
      ifds::ParentFndClsTrdg, CTRLFLAG_INITCOMBO_BY_SUB_LIST , IDC_LST_AMSINFO);

   AddControl( CTRL_EDIT, IDC_EDT_FOREIGN_FUND_NUM, IFASTBP_PROC::AMS_MST_LIST, 
               ifds::ForeignRelFundNum, 0 , IDC_LST_AMSINFO);
   AddControl( CTRL_EDIT, IDC_EDT_FOREIGN_FUND, IFASTBP_PROC::AMS_MST_LIST, 
               ifds::ForeignRelFund, 0 , IDC_LST_AMSINFO);
   AddControl( CTRL_EDIT, IDC_EDT_FOREIGN_CLASS, IFASTBP_PROC::AMS_MST_LIST, 
               ifds::ForeignRelClass, 0 , IDC_LST_AMSINFO);

   AddControl( CTRL_EDIT, IDC_EDT_ASSOC_FUND_NUM, IFASTBP_PROC::AMS_MST_LIST, 
               ifds::AssocFundNum, 0 , IDC_LST_AMSINFO);
   AddControl( CTRL_EDIT, IDC_EDT_ASSOC_FUND, IFASTBP_PROC::AMS_MST_LIST, 
               ifds::AssocFund, 0 , IDC_LST_AMSINFO);
   AddControl( CTRL_EDIT, IDC_EDT_ASSOC_CLASS, IFASTBP_PROC::AMS_MST_LIST, 
               ifds::AssocClass, 0 , IDC_LST_AMSINFO);

   AddControl( CTRL_EDIT, IDC_EDT_THRESHOLD, IFASTBP_PROC::AMS_MST_LIST, 
               ifds::Percentage, 0 , IDC_LST_AMSINFO);
   dynamic_cast<DSTEdit *>(GetControl(IDC_EDT_THRESHOLD))->SetAllowedChars(I_("0123456789."));
   AddControl( CTRL_EDIT, IDC_EDT_THRESHOLD_AMT, IFASTBP_PROC::AMS_MST_LIST, 
               ifds::ThresholdAmt, 0 , IDC_LST_AMSINFO);
   dynamic_cast<DSTEdit *>(GetControl(IDC_EDT_THRESHOLD_AMT))->SetAllowedChars(I_("0123456789."));

   AddControl( CTRL_DATE, IDC_DTP_EFFECTIVE_DATE, IFASTBP_PROC::AMS_MST_LIST, 
               ifds::EffectiveDate, 0 , IDC_LST_AMSINFO);
   AddControl( CTRL_DATE, IDC_DTP_GRAND_FATHERED_DATE, IFASTBP_PROC::AMS_MST_LIST, 
               ifds::GrandFatheredDate, 0 , IDC_LST_AMSINFO);
   AddControl( CTRL_COMBO, IDC_CMB_VERIFY_PRECREATE, IFASTBP_PROC::AMS_MST_LIST, 
               ifds::VerifyPrecreate, CTRLFLAG_INITCOMBO_BY_SUB_LIST , IDC_LST_AMSINFO);
   AddControl( CTRL_COMBO, IDC_CMB_WIRE_ELIG, IFASTBP_PROC::AMS_MST_LIST, 
               ifds::WireEleg, CTRLFLAG_INITCOMBO_BY_SUB_LIST , IDC_LST_AMSINFO);

   AddControl( CTRL_COMBO, IDC_CMB_REB_FREQ, IFASTBP_PROC::AMS_MST_LIST, 
               ifds::SchedSetupFreqID, CTRLFLAG_INITCOMBO_BY_SUB_LIST , IDC_LST_AMSINFO);
   AddControl( CTRL_DATE, IDC_DTP_NEXT_REB_DATE, IFASTBP_PROC::AMS_MST_LIST, 
               ifds::NextRebDate, 0 , IDC_LST_AMSINFO);
   AddControl( CTRL_DATE, IDC_DTP_LAST_REB_DATE, IFASTBP_PROC::AMS_MST_LIST, 
               ifds::LastRebDate, 0 , IDC_LST_AMSINFO);

   AddControl( CTRL_COMBO, IDC_CMB_CURRENCY, IFASTBP_PROC::AMS_MST_LIST, 
               ifds::Currency, CTRLFLAG_INITCOMBO_BY_SUB_LIST | CTRLFLAG_AUTO_UPDATE_ON_CHANGE ,
					IDC_LST_AMSINFO);

   AddControl( CTRL_COMBO, IDC_CMB_REBAL_REQ, IFASTBP_PROC::AMS_MST_LIST,
				ifds::RebalReq, CTRLFLAG_INITCOMBO_BY_SUB_LIST, IDC_LST_AMSINFO);

   AddControl( CTRL_COMBO, IDC_CMB_TARGET_MIX_OPT, IFASTBP_PROC::AMS_MST_LIST,
				ifds::TargetMixOption, CTRLFLAG_INITCOMBO_BY_SUB_LIST, IDC_LST_AMSINFO);

   AddControl( CTRL_EDIT, IDC_EDT_FUND_NUMBER, IFASTBP_PROC::AMS_ALLOCATION_LIST, 
               ifds::ToFundNumber, 0 , IDC_LIST_ALLOCATION);

   AddControl( CTRL_EDIT, IDC_EDT_FUND, IFASTBP_PROC::AMS_ALLOCATION_LIST, 
               ifds::FundCode, 0 , IDC_LIST_ALLOCATION);
   AddControl( CTRL_EDIT, IDC_EDT_CLASS, IFASTBP_PROC::AMS_ALLOCATION_LIST, 
               ifds::ClassCode, 0 , IDC_LIST_ALLOCATION);
   AddControl( CTRL_EDIT, IDC_EDT_FUND_PERCENT, IFASTBP_PROC::AMS_ALLOCATION_LIST, 
               ifds::AllocPercentage, 0 , IDC_LIST_ALLOCATION);

   AddControl( CTRL_STATIC, IDC_TXT_FUND_TOTAL_PRC_VAL, BF::NullContainerId, 
               ifds::TotPercentage, 0 , IDC_LIST_ALLOCATION);

   

   dynamic_cast<DSTEdit *>(GetControl(IDC_EDT_FUND_PERCENT))->SetAllowedChars(I_("0123456789."));

	dynamic_cast<DSTEdit *>(GetControl(IDC_EDT_AMSCODE))->SetMaxCharNum(4);
	dynamic_cast<DSTEdit *>(GetControl(IDC_EDT_ENGLISH_SHORT_NAME))->SetMaxCharNum(8);
	dynamic_cast<DSTEdit *>(GetControl(IDC_EDT_FRENCH_SHORT_NAME))->SetMaxCharNum(8);
	dynamic_cast<DSTEdit *>(GetControl(IDC_EDT_ENGLISH_NAME))->SetMaxCharNum(20);
	dynamic_cast<DSTEdit *>(GetControl(IDC_EDT_ENGLISH_LONG_NAME))->SetMaxCharNum(40);
	dynamic_cast<DSTEdit *>(GetControl(IDC_EDT_FRENCH_NAME))->SetMaxCharNum(20);
	dynamic_cast<DSTEdit *>(GetControl(IDC_EDT_FRENCH_LONG_NAME))->SetMaxCharNum(40);

   return(true);
}

//********************************************************************************
void AmsMstrDlg::ControlUpdated( UINT controlID, const DString &strValue )
{
   if( m_bAddCopy ) return;

   switch( controlID )
   {
		case IDC_EDT_FUND_PERCENT:
			LoadControl( IDC_TXT_FUND_TOTAL_PRC_VAL );
			break;

		case IDC_CMB_FUND_ALLOC:
         DisplayAmsFundClass();
			EnableAllocationControls();
			LoadControl( IDC_CMB_DEFAULT_ALLOC );
         LoadControl(IDC_CMB_AMS_GLOBAL_TRADE_PRNT_FUND);
			break;

		case IDC_CMB_USING:
			DisplaySearchRelated();
			SetDefID(IDC_BTN_SEARCH);
			break;

		case IDC_EDT_SEARCH_AMSCODE:
		case IDC_DTP_SEARCH_EFFECTIVE_DATE:
		case IDC_CMB_TYPE:
			SetDefID(IDC_BTN_SEARCH);
			break;
      case IDC_CMB_AMS_GLOBAL_TRADE_PRNT_FUND:
         DisplayAmsFundClass();
			EnableAllocationControls();
			LoadControl(IDC_CMB_DEFAULT_ALLOC);
         break;
      default:
         break;
   }
}

//********************************************************************************
void AmsMstrDlg::setDlgTitle()
{

}

//******************************************************************************
LRESULT AmsMstrDlg::OpenFundClassListDlg( WPARAM, LPARAM )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OpenFundClassListDlg" ) );

   DString strMarket = DSTCommonFunctions::getMarket();
   try
   {
      E_COMMANDRETURN eRtn = CMD_CANCEL;
      CWaitCursor wait;      

	  bool bExcFund = m_uiDialogItem == IDC_EDT_FOREIGN_FUND 
					   || m_uiDialogItem == IDC_EDT_FOREIGN_CLASS 
					   || m_uiDialogItem == IDC_EDT_FOREIGN_FUND_NUM;

     bool bAssocFund = m_uiDialogItem == IDC_EDT_ASSOC_FUND 
					     || m_uiDialogItem == IDC_EDT_ASSOC_CLASS 
					     || m_uiDialogItem == IDC_EDT_ASSOC_FUND_NUM;

      CString cstr;
      GetDlgItem( m_uiDialogItem )->GetWindowText( cstr );
		DString dstr = cstr;

      // Set Search Parameters (Code, Class, Number) for Fund Class Dialog
      switch( m_uiDialogItem )
      {
         case IDC_EDT_FUND_NUMBER:
		   case IDC_EDT_FOREIGN_FUND_NUM:
         case IDC_EDT_ASSOC_FUND_NUM:
				setParameter( FUND_NUMBER, dstr );
				break;
         case IDC_EDT_FUND:
		   case IDC_EDT_FOREIGN_FUND:
         case IDC_EDT_ASSOC_FUND:
				setParameter( FUND_CODE, dstr );
				break;
		 case IDC_EDT_CLASS:
		 case IDC_EDT_FOREIGN_CLASS:
       case IDC_EDT_ASSOC_CLASS: 
				setParameter( CLASS_CODE, dstr );
				break;    
      }

      eRtn = invokeCommand( getParent(), CMD_BPROC_FUNDCLASS, PROC_SUPPORT, true, NULL );
      switch( eRtn )
      {
         case CMD_OK:
         case CMD_MODELESS_INPROCESS:
            {
               DString dstrFundCode,dstrClassCode,dstrFundNumber;
               getParameter ( FUND_CODE, dstrFundCode );
               getParameter ( CLASS_CODE, dstrClassCode );
               getParameter ( FUND_NUMBER, dstrFundNumber );

			  if (bExcFund)
			  {
					getParent()->setField( this, IFASTBP_PROC::AMS_MST_LIST, 
								ifds::ForeignRelFundNum, dstrFundNumber );
					getParent()->setField( this, IFASTBP_PROC::AMS_MST_LIST, 
								ifds::ForeignRelFund, dstrFundCode );
					getParent()->setField( this, IFASTBP_PROC::AMS_MST_LIST, 
			  					ifds::ForeignRelClass, dstrClassCode );											
					LoadControl ( IDC_EDT_FOREIGN_FUND_NUM );
					LoadControl ( IDC_EDT_FOREIGN_FUND );
					LoadControl ( IDC_EDT_FOREIGN_CLASS );
			  }
           else if ( bAssocFund )
           {
               getParent()->setField( this, IFASTBP_PROC::AMS_MST_LIST, 
								ifds::AssocFundNum, dstrFundNumber );
					getParent()->setField( this, IFASTBP_PROC::AMS_MST_LIST, 
								ifds::AssocFund, dstrFundCode );
					getParent()->setField( this, IFASTBP_PROC::AMS_MST_LIST, 
			  					ifds::AssocClass, dstrClassCode );											
					LoadControl ( IDC_EDT_ASSOC_FUND_NUM );
					LoadControl ( IDC_EDT_ASSOC_FUND );
					LoadControl ( IDC_EDT_ASSOC_CLASS );
           }
			  else
			  {
					if( strMarket == MARKET_IDS::CANADA || strMarket == MARKET_IDS::LUXEMBOURG )
					{
						getParent()->setField( this, IFASTBP_PROC::AMS_ALLOCATION_LIST, 
									ifds::ToFundNumber, dstrFundNumber );
					}

					getParent()->setField( this, IFASTBP_PROC::AMS_ALLOCATION_LIST, 
								ifds::FundCode, dstrFundCode );
					getParent()->setField( this, IFASTBP_PROC::AMS_ALLOCATION_LIST, 
			  					ifds::ClassCode, dstrClassCode );	
					LoadControl ( IDC_EDT_FUND_NUMBER );
					LoadControl ( IDC_EDT_FUND );
					LoadControl ( IDC_EDT_CLASS );

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
BOOL AmsMstrDlg::PreTranslateMessage(MSG* pMsg) 
{
   if( pMsg->message == WM_KEYDOWN && ( int )( pMsg->wParam ) == VK_F4 && !IsSelectedCtrlUpdateable() )
      return(TRUE);

   if( pMsg->message == WM_KEYDOWN&&( int )( pMsg->wParam ) == VK_F4 )
   {
      if( GetFocus() == GetDlgItem( IDC_EDT_FUND_NUMBER ) )
      {
         PostMessage( UM_OPENFUNDCLASSLISTDLG );      
         m_uiDialogItem = IDC_EDT_FUND_NUMBER;
      }
      else if( GetFocus() == GetDlgItem( IDC_EDT_FUND ) )
      {
         PostMessage( UM_OPENFUNDCLASSLISTDLG );      
         m_uiDialogItem = IDC_EDT_FUND;
      }
      else if( GetFocus() == GetDlgItem( IDC_EDT_CLASS ) )
      {
         PostMessage( UM_OPENFUNDCLASSLISTDLG );      
         m_uiDialogItem = IDC_EDT_CLASS;
      }
	  else if( GetFocus() == GetDlgItem( IDC_EDT_FOREIGN_FUND_NUM ) )
      {
         PostMessage( UM_OPENFUNDCLASSLISTDLG );      
         m_uiDialogItem = IDC_EDT_FOREIGN_FUND_NUM;
      }
      else if( GetFocus() == GetDlgItem( IDC_EDT_FOREIGN_FUND ) )
      {
         PostMessage( UM_OPENFUNDCLASSLISTDLG );      
         m_uiDialogItem = IDC_EDT_FOREIGN_FUND;
      }
      else if( GetFocus() == GetDlgItem( IDC_EDT_FOREIGN_CLASS ) )
      {
         PostMessage( UM_OPENFUNDCLASSLISTDLG );      
         m_uiDialogItem = IDC_EDT_FOREIGN_CLASS;
      }
      else if( GetFocus() == GetDlgItem( IDC_EDT_ASSOC_FUND_NUM ) )
      {
         PostMessage( UM_OPENFUNDCLASSLISTDLG );      
         m_uiDialogItem = IDC_EDT_ASSOC_FUND_NUM;
      }
      else if( GetFocus() == GetDlgItem( IDC_EDT_ASSOC_FUND ) )
      {
         PostMessage( UM_OPENFUNDCLASSLISTDLG );      
         m_uiDialogItem = IDC_EDT_ASSOC_FUND;
      }
      else if( GetFocus() == GetDlgItem( IDC_EDT_ASSOC_CLASS ) )
      {
         PostMessage( UM_OPENFUNDCLASSLISTDLG );      
         m_uiDialogItem = IDC_EDT_ASSOC_CLASS;
      }
   }

   return(BaseMainDlg::PreTranslateMessage( pMsg ));
}  

//**********************************************************************************
void AmsMstrDlg::EnableControls( )
{
	if( _dstrFromScr == AMS_Para::AMS_DETAIL )
	{
		GetControl(IDC_EDT_AMSCODE )->Enable( false );
		GetControl(IDC_EDT_THRESHOLD )->Enable( false );
		GetControl(IDC_DTP_EFFECTIVE_DATE )->Enable( false );
		GetControl(IDC_CMB_CURRENCY )->Enable( false );
		GetControl(IDC_EDT_FUND_NUMBER )->Enable( false );
		GetControl(IDC_EDT_FUND )->Enable( false );
		GetControl(IDC_EDT_CLASS )->Enable( false );
		GetControl(IDC_EDT_FUND_PERCENT )->Enable( false );
		GetControl(IDC_CMB_FUND_ALLOC )->Enable( false );
		GetControl(IDC_CMB_DEFAULT_ALLOC )->Enable( false );
		GetControl(IDC_EDT_ENGLISH_SHORT_NAME )->Enable( false );
		GetControl(IDC_EDT_ENGLISH_NAME )->Enable( false );
		GetControl(IDC_EDT_ENGLISH_LONG_NAME )->Enable( false );
		GetControl(IDC_EDT_FRENCH_SHORT_NAME )->Enable( false );
		GetControl(IDC_EDT_FRENCH_NAME )->Enable( false );
		GetControl(IDC_EDT_FRENCH_LONG_NAME )->Enable( false );
		GetControl(IDC_EDT_FOREIGN_FUND_NUM )->Enable( false );
		GetControl(IDC_EDT_FOREIGN_FUND )->Enable( false );
		GetControl(IDC_EDT_FOREIGN_CLASS )->Enable( false );
      GetControl(IDC_EDT_ASSOC_FUND_NUM )->Enable( false );
		GetControl(IDC_EDT_ASSOC_FUND )->Enable( false );
		GetControl(IDC_EDT_ASSOC_CLASS )->Enable( false );
		GetControl(IDC_EDT_THRESHOLD_AMT )->Enable( false );
		GetControl(IDC_DTP_GRAND_FATHERED_DATE)->Enable( false );
		GetControl(IDC_CMB_VERIFY_PRECREATE )->Enable( false );
      GetControl(IDC_CMB_WIRE_ELIG )->Enable( false );
		GetControl(IDC_CMB_REB_FREQ )->Enable( false );
		GetControl(IDC_DTP_NEXT_REB_DATE )->Enable( false );
		GetControl( IDC_DTP_LAST_REB_DATE )->Enable( false );
		GetDlgItem(IDC_BTN_AMS_ADD)->EnableWindow(false);
		GetDlgItem(IDC_BTN_AMS_DEL)->EnableWindow(false);
		GetDlgItem(IDC_BTN_AMS_ADD_COPY)->EnableWindow(false);
		GetDlgItem(IDC_BTN_ALLOC_ADD)->EnableWindow(false);
		GetDlgItem(IDC_BTN_ALLOC_DEL)->EnableWindow(false);
		GetDlgItem(IDC_BTN_RESET)->EnableWindow(false);
	}
}

//**********************************************************************************
void AmsMstrDlg::DisplayAmsCurrencyThreshold()
{
	int iDisp, iDispAssocFundClass = SW_HIDE;

	DString dstrAMSType;
	getParent()->getField(this,IFASTBP_PROC::AMS_MST_LIST,ifds::AMSType,dstrAMSType,false);
	dstrAMSType.strip().upperCase();

	if (dstrAMSType == TARGET_ASSET || dstrAMSType == FUND_OF_FUNDS ) 
	{
		iDisp = SW_HIDE;
		GetDlgItem( IDC_TXT_CURRENCY )->ShowWindow(iDisp );
		GetDlgItem( IDC_CMB_CURRENCY )->ShowWindow(iDisp );

		GetDlgItem( IDC_TXT_THRESHOLD )->ShowWindow(iDisp );
		GetDlgItem( IDC_EDT_THRESHOLD )->ShowWindow(iDisp );
		GetDlgItem( IDC_TXT_THRESHOLD_AMT )->ShowWindow(iDisp );
		GetDlgItem( IDC_EDT_THRESHOLD_AMT )->ShowWindow(iDisp );
	}
	else if ( dstrAMSType == REBALANCE )
	{
		DString dstrValue;
		getParent()->getField(this,ifds::CommonCurrency,dstrValue,false);
		dstrValue.strip().upperCase();
		ConnectControlToData(IDC_CMB_CURRENCY,dstrValue == YES,true );
		iDisp = dstrValue == YES?SW_SHOW:SW_HIDE;

		GetDlgItem( IDC_TXT_CURRENCY )->ShowWindow(iDisp );

		getParent()->getField(this,ifds::DispRBLSysThrshld,dstrValue,false);
		dstrValue.strip().upperCase();
		ConnectControlToData(IDC_EDT_THRESHOLD,dstrValue == YES,true );
		iDisp = dstrValue == YES?SW_SHOW:SW_HIDE;
		GetDlgItem( IDC_TXT_THRESHOLD )->ShowWindow(iDisp );
		GetDlgItem( IDC_TXT_THRESHOLD_AMT )->ShowWindow(iDisp );
		GetDlgItem( IDC_EDT_THRESHOLD_AMT )->ShowWindow(iDisp );

		iDisp = SW_SHOW;
	}
   
	GetDlgItem( IDC_TXT_REB_FREQ )->ShowWindow(iDisp );
	GetDlgItem( IDC_CMB_REB_FREQ )->ShowWindow(iDisp );
	GetDlgItem( IDC_TXT_NEXT_REB_DATE )->ShowWindow(iDisp );
	GetDlgItem( IDC_DTP_NEXT_REB_DATE)->ShowWindow(iDisp );
	GetDlgItem( IDC_TXT_LAST_REB_DATE )->ShowWindow(iDisp );
	GetDlgItem( IDC_DTP_LAST_REB_DATE )->ShowWindow(iDisp );
}

//***********************************************************************************
void AmsMstrDlg::DisplayAmsFundClass() 
{
	DString dstrAMSType, dstrGlobalAssestAlloc;
	getParent()->getField(this,IFASTBP_PROC::AMS_MST_LIST,ifds::AMSType,dstrAMSType,false);
   getParent()->getField(this,IFASTBP_PROC::AMS_MST_LIST,ifds::FundAlloc,dstrGlobalAssestAlloc,false);
	dstrAMSType.strip().upperCase();
   dstrGlobalAssestAlloc.strip().upperCase();

	int iDispForgnFundClass = SW_SHOW;
   int iDispAssocFundClass = SW_SHOW;
   int iDispUseParentFund = SW_HIDE;

   CString cstrAMSGlobalFundLabel;

   bool bUseParentFund = false;


   if(dstrAMSType == REBALANCE && dstrGlobalAssestAlloc == I_("Y"))
   {
      iDispUseParentFund = SW_SHOW;
   }
   else {
      iDispUseParentFund = SW_HIDE;
   }

   GetDlgItem( IDC_STATIC_GEN_17 )->ShowWindow(iDispUseParentFund);
   GetDlgItem( IDC_CMB_AMS_GLOBAL_TRADE_PRNT_FUND )->ShowWindow(iDispUseParentFund);

   DString dstrParentFndClsTrdg;
	getParent()->getField(this,IFASTBP_PROC::AMS_MST_LIST,ifds::ParentFndClsTrdg,dstrParentFndClsTrdg,false);
   dstrParentFndClsTrdg.strip().upperCase();

   if(dstrAMSType == REBALANCE )
   {
      cstrAMSGlobalFundLabel.LoadString(TXT_PARENT_FUND);
      iDispForgnFundClass = SW_SHOW;
   }
   else
   {
      cstrAMSGlobalFundLabel.LoadString(TXT_FUND_OF_FUNDS);
      iDispForgnFundClass = SW_HIDE;
   }

   GetDlgItem( IDC_TXT_ASSOC_FUND )->SetWindowText(cstrAMSGlobalFundLabel);

   GetDlgItem( IDC_TXT_FOREIGN_FUND )->ShowWindow(iDispForgnFundClass);
	GetDlgItem( IDC_TXT_FOREIGN_CLASS )->ShowWindow(iDispForgnFundClass);
	GetDlgItem( IDC_EDT_FOREIGN_FUND_NUM )->ShowWindow(iDispForgnFundClass);
	GetDlgItem( IDC_EDT_FOREIGN_FUND )->ShowWindow(iDispForgnFundClass);
	GetDlgItem( IDC_EDT_FOREIGN_CLASS )->ShowWindow(iDispForgnFundClass);

   // Associated Fund/Class
   GetDlgItem( IDC_TXT_ASSOC_FUND )->ShowWindow( iDispAssocFundClass );	
   GetDlgItem( IDC_EDT_ASSOC_FUND_NUM )->ShowWindow( iDispAssocFundClass );
   GetDlgItem( IDC_EDT_ASSOC_FUND )->ShowWindow( iDispAssocFundClass );
   GetDlgItem( IDC_EDT_ASSOC_CLASS )->ShowWindow( iDispAssocFundClass );

   bool bEnableAssocFund = false;
   if ( (dstrAMSType == REBALANCE && dstrParentFndClsTrdg == I_("01")) ||
        (dstrAMSType == FUND_OF_FUNDS))
   {
      bEnableAssocFund = true;
   }
   else
   {
      bEnableAssocFund = false;
   }

   GetDlgItem( IDC_EDT_ASSOC_FUND_NUM )->EnableWindow(bEnableAssocFund);
   GetDlgItem( IDC_EDT_ASSOC_FUND )->EnableWindow(bEnableAssocFund);
   GetDlgItem( IDC_EDT_ASSOC_CLASS )->EnableWindow(bEnableAssocFund);

   if(!bEnableAssocFund)
   {
      ClearControl( IDC_EDT_ASSOC_FUND_NUM );
      ClearControl( IDC_EDT_ASSOC_FUND );
      ClearControl( IDC_EDT_ASSOC_CLASS );
   }
}

//***********************************************************************************
bool AmsMstrDlg::doDisablePermCheckButton(UINT nID)
{
	if( _dstrFromScr == AMS_Para::AMS_DETAIL )
		return true;

	//Add, Modification, and delete is not allowed for existing AMS Master
	else if( nID == IDC_BTN_ALLOC_ADD || nID == IDC_BTN_ALLOC_DEL )
	{		
		// PTS 10031833:
		// As long as the AMS code in question has not been added to an account, 
		// you should be able to make as many changes as you want to the AMS target mix.  
		// User should also be able to make corrections during the first day of setup.  
		// Once the AMS code in question has been added to an account (except during the first day correction period), you should not be able to modify the AMS target asset mix at the GLOBAL level.  If the asset mix changes, users will be required to place a STOP date on the GLOBAL mix and setup a COPY (with the same AMS code) and new start date (Stop date + 1) and then update the AMS mix accordingly.  
		// (One day correction privileges should still apply to this NEW setup.)
		DString dstrCurrentBusinessDate, dstrEffectiveDate;
		DSTCWorkSession *pDSTWorkSession = dynamic_cast<DSTCWorkSession *>(getParent()->getBFWorkSession());
		if ( NULL != pDSTWorkSession )
			pDSTWorkSession->getOption( ifds::CurrBusDate, dstrCurrentBusinessDate, getDataGroupId(), false );		

		getParent()->getField( this, IFASTBP_PROC::AMS_MST_LIST, ifds::EffectiveDate, dstrEffectiveDate, false );
		
		if( DSTCommonFunctions::CompareDates( dstrEffectiveDate, dstrCurrentBusinessDate ) == DSTCommonFunctions::FIRST_EARLIER )
		{
		  DString dstrStatusCode;
		  getParent()->getField( this, IFASTBP_PROC::AMS_MST_LIST, ifds::AMSCodeInUse, dstrStatusCode, false );
		  if ( dstrStatusCode.strip().upperCase() == YES )
			 return true;
		}

		// If we are not out yet...
		int nItems = getParent()->getNumberOfItemsInList(this, IFASTBP_PROC::AMS_ALLOCATION_LIST);
		if (  nID == IDC_BTN_ALLOC_DEL && nItems == 0 )
			return true;
		DString dstrValue;
		getParent()->getField(this,ifds::FundAlloc,dstrValue,false);
		dstrValue.strip().upperCase();
		if ( nID == IDC_BTN_ALLOC_ADD && dstrValue == NO && nItems == 0 )
			return true;					
	}	
   //Disable the add copy button if the grandfatherdate is stamped or highlight a dummy item.
	else if( nID == IDC_BTN_AMS_ADD_COPY )
    {
		  DString dstrGFStamped, dstrLastEffectiveDate, dstrEffectiveDate;
		  getParent()->getField(this, IFASTBP_PROC::AMS_MST_LIST, ifds::GrandFatherStamped, dstrGFStamped, false);
		  getParent()->getField(this, IFASTBP_PROC::AMS_MST_LIST, ifds::LastEffectiveDate, dstrLastEffectiveDate, false);
		  getParent()->getField(this, IFASTBP_PROC::AMS_MST_LIST, ifds::EffectiveDate, dstrEffectiveDate, false);

		  if(	m_bDummyItem 
			  || dstrGFStamped == YES 
			  || ( DSTCommonFunctions::CompareDates( dstrEffectiveDate, 
                                                     dstrLastEffectiveDate ) 
                   != DSTCommonFunctions::EQUAL )			)
		  {
			  return true;
		  }
	}

	return false;
}

//************************************************************************************
void AmsMstrDlg::DoListItemChanged( UINT listControlID,
                                    const DString &strKey,
                                    bool bIsNewItem ,
                                    bool bIsDummyItem )
{

   if( listControlID == IDC_LST_AMSINFO )
   {
      m_bDummyItem = bIsDummyItem;
      EnableControls();
      DisplayAmsCurrencyThreshold();
      DisplayAmsFundClass();	  
	    EnableDeltaAllocation();
      // History
      GetDlgItem(IDC_BTN_HISTORICAL)->EnableWindow( (bIsNewItem || bIsDummyItem) ? FALSE : TRUE );	   
   }	
}

//*******************************************************************************************
bool AmsMstrDlg::EnableDeltaAllocation()
{
  DString dstrAMSCode, dstrTargetMixOpt, dstrEffDate, dstrGrandFatherStamped, dstrCurBusDate, dstrAMSType, 
          dstrSystemDate, dstr1231999, dstrModDate, bIsAMSUpdated, bIsAMSFundUpdated;
  bool bEnableDelta = true;

  bool bIsDummyItem = getParentProcess()->isCurrentListItemDummy(this, IFASTBP_PROC::AMS_MST_LIST);
  bool bIsNewItem = getParentProcess()->isCurrentListItemNew(this, IFASTBP_PROC::AMS_MST_LIST);
  
  DSTCWorkSession *pDSTWorkSession = dynamic_cast<DSTCWorkSession *>(getParent()->getBFWorkSession());
  if (NULL != pDSTWorkSession)
  {
    pDSTWorkSession->getOption(ifds::CurrBusDate, dstrCurBusDate, getDataGroupId(), false);
    pDSTWorkSession->getDateInHostFormat (dstr1231999, DSTCWorkSession::DATE_TYPE::DAY12319999, getDataGroupId());
    pDSTWorkSession->getDateInHostFormat (dstrSystemDate, DSTCWorkSession::DATE_TYPE::CURRENT_SYSTEM_DAY, getDataGroupId());
  }

  getParent()->getField(this, IFASTBP_PROC::AMS_MST_LIST, ifds::AMSCode, dstrAMSCode, false);
  getParent()->getField(this, IFASTBP_PROC::AMS_MST_LIST, ifds::TargetMixOption, dstrTargetMixOpt, false);
  getParent()->getField(this, IFASTBP_PROC::AMS_MST_LIST, ifds::EffectiveDate, dstrEffDate, false);
  getParent()->getField(this, IFASTBP_PROC::AMS_MST_LIST, ifds::GrandFatherStamped, dstrGrandFatherStamped, false);
  getParent()->getField(this, IFASTBP_PROC::AMS_MST_LIST, ifds::AMSType, dstrAMSType, false);
  getParent()->getField(this, BF::NullContainerId, AMS_DELTA::IsAMSUpdate, bIsAMSUpdated, false);
  getParent()->getField(this, BF::NullContainerId, AMS_DELTA::IsAMSFundUpdate, bIsAMSFundUpdated, false);
  getParent()->getField(this, IFASTBP_PROC::AMS_MST_LIST, ifds::LastAMSModDate, dstrModDate, false);
  if(dstrAMSCode == I_("0001") || (bIsNewItem || bIsDummyItem) || dstrTargetMixOpt != MarketValueWeight 
    || dstrGrandFatherStamped == YES || dstrAMSType != I_("RB"))
  {
    bEnableDelta = false;
  }
  else if(DSTCommonFunctions::CompareDates(dstrEffDate, dstrCurBusDate) != DSTCommonFunctions::FIRST_EARLIER)
  {
    bEnableDelta = false;
  }
  else if(!dstrModDate.empty() && (DSTCommonFunctions::CompareDates(dstrModDate, dstrSystemDate) != DSTCommonFunctions::FIRST_EARLIER))
  {
    bEnableDelta = false;
  }
  else if(bIsAMSUpdated == YES || bIsAMSFundUpdated == YES)
  {
    bEnableDelta = false;
  }

  GetDlgItem(IDC_BTN_DELTA)->EnableWindow(bEnableDelta);

  return bEnableDelta;
}

//*******************************************************************************************
void AmsMstrDlg::OnSelchangeTargetMixOpt()
{
  EnableDeltaAllocation();
}
//*******************************************************************************************
bool AmsMstrDlg::filterListColumn(const BFFieldId &idSubstitute, const DString& dstrTag)
{
	DString dstrValue,dstrAMSType;
	dstrAMSType = _dstrAmsType;

	if( ifds::AMSGlobalHeading == idSubstitute )
	{
		if(dstrTag == CURRENC )
		{
			if (dstrAMSType != TARGET_ASSET)
			{
				getParent()->getField(this,ifds::CommonCurrency,dstrValue,false);
				dstrValue.strip().upperCase();
				return dstrValue == YES;
			}
			else
				return false;
		}
		else if( dstrTag == PERCENT || dstrTag == THRESHOLD_AMT )
		{
			if (dstrAMSType != TARGET_ASSET) 
			{
				getParent()->getField(this,ifds::DispRBLSysThrshld,dstrValue,false);
				dstrValue.strip().upperCase();
				return dstrValue == YES;
			}
			else
				return false;
		}
	}	

   return true;
}

//**********************************************************************************
//Add, Modification, and delete is not allowed for existing AMS Master
//For new AMS Master:
//1. If FundAlloc is "Yes", enable all controls for Alloction (including list,Add,Delete button ,Fund, Class and Total etc)
//2. If FundAlloc is "No":
//·  If the number of item in AMS_ALLOCATION_LIST is 0, disable all controls for allocation, so that user can not add allocation for this case.
//· If the number of item in AMS_Allocation_LIST is greater than 0, enable all controls for allocation. User has to delete allocation list.
void AmsMstrDlg::EnableAllocationControls( )
{
	DString dstrStatusCode;
	bool m_bShow = false;
	getParent()->getField( this, IFASTBP_PROC::AMS_MST_LIST, ifds::AMSCodeInUse, dstrStatusCode, false );
    int nItems = getParent()->getNumberOfItemsInList(this, IFASTBP_PROC::AMS_ALLOCATION_LIST);
	if ( nItems == 0 )
	{
		GetDlgItem( IDC_EDT_FUND_NUMBER )->SetWindowText( NULL_STRING );
		GetDlgItem( IDC_EDT_FUND )->SetWindowText( NULL_STRING );
		GetDlgItem( IDC_EDT_CLASS )->SetWindowText( NULL_STRING );
		GetDlgItem( IDC_EDT_FUND_PERCENT )->SetWindowText( NULL_STRING );
	}

	if ( !dstrStatusCode.empty() ) //existing record
	{
		m_bShow=false;
	}
	else //new record
	{
		 DString dstrValue;
		 getParent()->getField(this,ifds::FundAlloc,dstrValue,false);
		 dstrValue.strip().upperCase();
	 
		if ( dstrValue == YES )
		{
			m_bShow=true;
		}
		else
		{
			if (nItems >0)
			{
				m_bShow=true;			
			}
			else
			{
				m_bShow=false;
			}
		}

		EnableAllocationEditControls( nItems > 0 );
		if (m_bShow)
		{
			addBtnAddForPermissionCheck(IDC_BTN_ALLOC_ADD, IDC_LIST_ALLOCATION);
			addBtnDeleteForPermissionCheck(IDC_BTN_ALLOC_DEL, IDC_LIST_ALLOCATION);
		}
		else
		{
			removeBtnAddFromPermissionCheck(IDC_BTN_ALLOC_ADD);
			removeBtnDeleteFromPermissionCheck(IDC_BTN_ALLOC_DEL) ;
		}

		GetDlgItem(IDC_BTN_ALLOC_ADD)->EnableWindow(m_bShow);
		GetDlgItem(IDC_BTN_ALLOC_DEL)->EnableWindow(nItems >0);
	}
}

//**********************************************************************************
void AmsMstrDlg::EnableAllocationEditControls(bool bShow)
{
	GetControl(IDC_EDT_FUND_NUMBER )->Enable( bShow );
	GetControl(IDC_EDT_FUND )->Enable( bShow );
	GetControl(IDC_EDT_CLASS )->Enable( bShow );
	GetControl(IDC_EDT_FUND_PERCENT )->Enable( bShow );
	GetDlgItem(IDC_LIST_ALLOCATION)->EnableWindow( bShow );
}

//**********************************************************************************
void AmsMstrDlg::OnBtnAdmDates() 
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OnBtnAdminDates" ) );
   CWaitCursor wait;
   ShowAdminDates( IFASTBP_PROC::AMS_MST_LIST );
}

//**********************************************************************************
void AmsMstrDlg::OnBtnHistorical()
{
   TRACE_METHOD( CLASSNAME, I_("OnBtnHistorical"));
   CWaitCursor wait;
   
   IFastHistoricalInfo f;
   f( this, IFASTBP_PROC::AMS_MST_LIST, I_("MULTI") );
}

//**********************************************************************************
void AmsMstrDlg::OnBtnLmtOverride()
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OnBtnLmtOverride" ) );

   CWaitCursor wait;
   E_COMMANDRETURN eRtn;
   bool bModal = true;                               // Default to modal
   try
   {
	  DString dstrAmsCode, dstrAmsType, dstrEffectiveDate;
	  getParent()->getField(this,IFASTBP_PROC::AMS_MST_LIST,ifds::AMSCode, dstrAmsCode,false );

	  setParameter( AMS_LMT_Para::AMS_CODE, dstrAmsCode.strip().upperCase() );
	  setParameter( AMS_LMT_Para::FROM_SCR, _dstrFromScr );

	  setParameter( AMS_Para::EFFECTIVE_DATE, _dstrEffectiveDate );
 	  setParameter( AMS_Para::AMS_CODE, _dstrAmsCode.strip().upperCase() );
	  setParameter( AMS_Para::AMS_TYPE, _dstrAmsType.strip().upperCase() );

     const DString *pCurKey = &(getParent()->getCurrentListItemKey(this, IFASTBP_PROC::AMS_MST_LIST));   
     setParameter( AMS_LMT_Para::AMS_REC_ID, *pCurKey );

     eRtn = invokeCommand(getParent(), CMD_BPROC_AMS_LMT_OVERRIDE, PROC_SUPPORT, true, NULL);
     if( eRtn != CMD_CANCEL )
     {
        LoadListControl(IDC_LST_AMSINFO, pCurKey);
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

//**********************************************************************************
void AmsMstrDlg::OnBtnAddCopy() 
{
      CWaitCursor wait;      
      DString _dstrOrgKey = GetList(IDC_LST_AMSINFO)->GetCurrentKey();
      m_bAddCopy = true;
      AddToListControl( IDC_LST_AMSINFO );
      DString _dstrDestKey = GetList(IDC_LST_AMSINFO)->GetCurrentKey();
      getParent()->setField(this, BF::NullContainerId, AMS_PROC::ORG_KEY, _dstrOrgKey);
      getParent()->setField(this, BF::NullContainerId, AMS_PROC::DEST_KEY, _dstrDestKey);    
      m_bAddCopy = false;
      RefreshListItem( IDC_LST_AMSINFO );
      LoadListControl( IDC_LST_AMSINFO, const_cast<DString*>(&_dstrDestKey) );
}

//****************************************************************************
void AmsMstrDlg::DisplaySearchRelated()
{
	DString dstrSearchBy;
   getParent()->getField(this,IFASTBP_PROC::AMS_MST_SEARCH,ifds::AMSSearchType,dstrSearchBy,false);
   dstrSearchBy.strip();

	UINT nShowEffectiveDate =  (dstrSearchBy == SEARCH_TYPE_EFFECTIVE_DATE)? SW_SHOW:SW_HIDE;

	GetDlgItem( IDC_TXT_SEARCH_EFFECTIVE_DATE )->ShowWindow(nShowEffectiveDate );
	GetDlgItem( IDC_DTP_SEARCH_EFFECTIVE_DATE )->ShowWindow(nShowEffectiveDate );

	GetDlgItem(IDC_EDT_SEARCH_AMSCODE)->ShowWindow( true );
	GetDlgItem( IDC_CMB_TYPE ) ->ShowWindow( true );

	ConnectControlToData(IDC_DTP_SEARCH_EFFECTIVE_DATE ,nShowEffectiveDate?true:false,true);
	ConnectControlToData(IDC_EDT_SEARCH_AMSCODE,true);
	ConnectControlToData(IDC_CMB_TYPE,true);

	LoadControls(AMS_MST_SEARCH);
}

//****************************************************************************
void AmsMstrDlg::addControlsForSearchCriteria()
{
	AddControl( CTRL_COMBO, IDC_CMB_USING, IFASTBP_PROC::AMS_MST_SEARCH, 
               ifds::AMSSearchType, CTRLFLAG_INITCOMBO_BY_SUB_LIST, AMS_MST_SEARCH);

	ConnectControlToData(IDC_CMB_USING,true );
	
	AddControl( CTRL_EDIT,  IDC_EDT_SEARCH_AMSCODE,  IFASTBP_PROC::AMS_MST_SEARCH, 
              ifds::AMSCode,0,AMS_MST_SEARCH); 
    AddControl( CTRL_DATE, IDC_DTP_SEARCH_EFFECTIVE_DATE, IFASTBP_PROC::AMS_MST_SEARCH, 
               ifds::EffectiveDate, 0 , AMS_MST_SEARCH);
	AddControl( CTRL_COMBO, IDC_CMB_TYPE, IFASTBP_PROC::AMS_MST_SEARCH, 
               ifds::AMSType, CTRLFLAG_INITCOMBO_BY_SUB_LIST, AMS_MST_SEARCH);
}

//*****************************************************************************
void AmsMstrDlg::onBtnDeltaAlloc()
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "onBtnDeltaAlloc" ) );

   bool IsDeltaEnabled = EnableDeltaAllocation();
   if(IsDeltaEnabled)
   {
     CWaitCursor wait;
     E_COMMANDRETURN eRtn;
     bool bModal = true; // Default to modal
     try
     {
	     DString dstrAmsCode, dstrAmsType, dstrEffectiveDate,dstrCurDeff,dstrCurAMSCode;
	     getParent()->getField(this,IFASTBP_PROC::AMS_MST_LIST,ifds::AMSCode, dstrAmsCode,false);
	     getParent()->getField(this,IFASTBP_PROC::AMS_MST_LIST,ifds::EffectiveDate,dstrEffectiveDate,false);
	     getParent()->getField(this,IFASTBP_PROC::AMS_MST_LIST,ifds::AMSType,dstrAmsType,false);
	     getParent()->getField(this,IFASTBP_PROC::AMS_MST_SEARCH,ifds::EffectiveDate,dstrCurDeff,false);
	     getParent()->getField(this,IFASTBP_PROC::AMS_MST_SEARCH,ifds::AMSCode,dstrCurAMSCode,false);

	     setParameter( AMS_DELTA_ALLOC_Para::AMS_CODE, dstrAmsCode.strip().upperCase() );
	     setParameter( AMS_DELTA_ALLOC_Para::AMS_EFFECTIVE_DATE, dstrEffectiveDate );
	     setParameter( AMS_DELTA_ALLOC_Para::ACCOUNT_NUM, I_("0"));
	     setParameter( AMS_DELTA_ALLOC_Para::AMS_TYPE, dstrAmsType );
	     setParameter( AMS_DELTA_ALLOC_Para::AMS_SEARCH_DATE, dstrCurDeff);
	     setParameter( AMS_DELTA_ALLOC_Para::AMS_SEARCH_CODE, dstrCurAMSCode);

       const DString *pCurKey = &(getParent()->getCurrentListItemKey(this, IFASTBP_PROC::AMS_MST_LIST));   
       setParameter( AMS_DELTA_ALLOC_Para::AMS_REC_ID, *pCurKey );

       eRtn = invokeCommand(getParent(), CMD_BPROC_AMS_DELTA_ALLOC, PROC_SUPPORT, true, NULL);
       if( eRtn != CMD_CANCEL )
       {
         LoadListControl(IDC_LST_AMSINFO, pCurKey);
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

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/AmsMstrDlg.cpp-arc  $
// 
//    Rev 1.41   11 Sep 2007 13:28:00   popescu
// Incident 1003183 - added WireElig on the Global AMS screen
// 
//    Rev 1.40   Aug 03 2007 09:35:26   smithdav
// PET 2360 FN02
// 
//    Rev 1.39   Jul 18 2007 09:36:24   smithdav
// PET2360 FN02
// 
//    Rev 1.38   Jul 06 2007 15:06:16   smithdav
// PET2360 FN02 - AMS - Make changes to Show/Hide for FOF
// 
//    Rev 1.37   Jun 25 2007 11:53:28   porteanm
// PET 2360 FN02 - AMS
// 
//    Rev 1.36   Jun 22 2007 14:23:34   porteanm
// PET 2360 FN02 - AMS - work in progress.
// 
//    Rev 1.35   Jun 18 2007 14:30:42   porteanm
// PET2360 FN02 - AIM AMS - Syst level.
// 
//    Rev 1.34   Sep 15 2005 15:10:32   popescu
// Incident#403519 - added CLASSNAME as the fifth parameter to  BaseMainDlg constructor
// 
//    Rev 1.33   Jul 16 2004 15:18:40   VADEANUM
// PTS 10031833 - Added 24hr grace period.
// 
//    Rev 1.32   Jul 15 2004 16:31:46   VADEANUM
// PTS 10031833 - AMS Global
// 
//    Rev 1.31   Mar 10 2004 12:09:10   HERNANDO
// PET965 FN11 - Added iFastHistoricalInfo parameter.
// 
//    Rev 1.30   Feb 27 2004 15:56:42   HERNANDO
// PET965 FN11 - Enable/Disable Historical Button based on list item in doListItemChanged.
// 
//    Rev 1.29   Aug 25 2003 14:03:42   linmay
// modified ControlUpdated(), and onBtnSearch() to set default id for search button
// 
//    Rev 1.28   Aug 22 2003 13:33:50   linmay
// added logic for ams search, and cleaned code
// 
//    Rev 1.27   Aug 13 2003 16:20:22   linmay
// modified onbtnamslimitation()
// 
//    Rev 1.25   Aug 13 2003 12:11:50   linmay
// modified onPostInitDlg()
// 
//    Rev 1.23   Aug 05 2003 11:25:48   linmay
// fix bug
// 
//    Rev 1.22   Jul 30 2003 14:19:04   linmay
// added logic for addcopy button
// 
//    Rev 1.20   Jul 18 2003 11:38:12   linmay
// modified for CIBC AMS
// 
//    Rev 1.17.1.5   Jun 16 2003 15:50:42   YINGBAOL
// More button should be enable/disabled at very begin
// 
//    Rev 1.17.1.4   Jun 12 2003 11:05:26   YINGBAOL
// fix
// 
//    Rev 1.17.1.3   Jun 11 2003 11:45:26   YINGBAOL
// Enable Search button when it comes from Account Level AMS screen.
// 
//    Rev 1.17.1.2   Jun 06 2003 18:31:04   YINGBAOL
// more clean up
// 
//    Rev 1.17.1.1   Jun 06 2003 15:23:30   YINGBAOL
// clean code
// 
//    Rev 1.17.1.0   Jun 06 2003 11:29:30   YINGBAOL
// fix amstype issue
// 
//    Rev 1.17   Apr 23 2003 16:08:44   YINGBAOL
// PTS10016351
// 
//    Rev 1.16   Apr 21 2003 09:52:42   YINGBAOL
// reimplement AMSType logic
// 
//    Rev 1.15   Apr 09 2003 14:33:44   linmay
// fix bug for ticket#10014574
// 
//    Rev 1.14   Apr 05 2003 15:04:16   YINGBAOL
// Disable search button when it is launched from account ams screen
// 
//    Rev 1.13   Apr 05 2003 11:37:46   YINGBAOL
// If screen is launched from Account level AMS screen, should not call perform search
// 
//    Rev 1.12   Mar 21 2003 18:32:40   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.11   Jan 16 2003 13:19:40   WINNIE
// fix OnBtnSearch (yingbao )
// 
//    Rev 1.10   Jan 16 2003 13:11:20   WINNIE
// fix AMSType( Yingbao on Winnie's machine)
// 
//    Rev 1.9   Jan 14 2003 18:04:46   YINGBAOL
// disable add and delete buttons and some other control if it is from Acct AMS screen
// 
//    Rev 1.8   Jan 06 2003 16:38:38   linmay
// modified onPostInitDialog()
// 
//    Rev 1.7   Jan 06 2003 11:14:04   linmay
// modified addControls and EnableAllocationControls
// 
//    Rev 1.6   Jan 03 2003 14:48:00   linmay
// modified ControlUpdated
// 
//    Rev 1.5   Jan 03 2003 09:27:12   linmay
// modified OnPostInit function and LoadAMSType function
// 
//    Rev 1.4   Jan 02 2003 15:09:02   linmay
// added EnableAllocationControls
// 
//    Rev 1.3   Dec 27 2002 11:04:28   linmay
// added type, name, allocation
// 
//    Rev 1.2   Dec 02 2002 11:05:44   KOVACSRO
// fixed OpenFundClassListDlg : always set FundCode and ClassCode from FundClass dialog.
// 
//    Rev 1.1   Nov 29 2002 11:15:22   YINGBAOL
// added filterListColumn function
// 
//    Rev 1.0   Nov 25 2002 10:13:06   YINGBAOL
// Initial Revision
// 

 * 
 */





