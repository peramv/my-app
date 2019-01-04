
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
// ^FILE   : FeeParamSysDlg.cpp
// ^AUTHOR : Yingbao Li, May Lin
// ^DATE   : 01/09/03
//
// ^CLASS    : FeeParamSysDlg
// ^SUBCLASS : IFastBaseMainDlg
//
// ^CLASS DESCRIPTION : 
//
//******************************************************************************

#include "stdafx.h"

#ifndef IFASTGUI_H
   #include "mfdstc.h"
#endif

#ifndef DSTEDIT_H
   #include <uibase\DSTEdit.h>
#endif

#ifndef FEEPARAMSYSDLG_H
   #include "FeeParamSysDlg.h"
#endif

#ifndef FEEPARAMSYSINCLUDES_H
   #include <ifastbp\FeeParamSysProcessInclude.hpp>
#endif

#ifndef FUNDCLASSPROCESSINCLUDES_H
   #include <ifastbp\FundClassProcessIncludes.h>
#endif
#ifndef DSTLISCTRL_H
   #include <uibase\DSTListCtrl.h>
#endif

#include <configmanager.hpp>
#include <ifastbp\mfcaninterprocparam.hpp>
#include <ifastcbo\dstcommonfunction.hpp>
#include <ifastcbo\DSTCWorkSession.hpp>
#include <ifastcbo\mgmtcooptions.hpp>
#include <bfproc\AbstractProcess.hpp>
#include <uibase\DSTComboBox.h>
#include <uibase\dstgridwnd.h>
#include <uibase\dsttabctrl.h>
#include <discardmsgdlg.h>
#include <ifastbp\feeparamsysprocess.hpp>
#include <ifastcbo\MgmtCoOptions.hpp>
#include <ifastcbo\MgmtCo.hpp>

extern CLASS_IMPORT const I_CHAR* CMD_BPROC_FUNDCLASS;
extern CLASS_IMPORT const I_CHAR* CMD_GUI_FEE_PARAMETER_SYSTEM;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_BROKER;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_SLSREP;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_BRANCH;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_FEE_PARAM_MAINT;

#include <bfproc\concretedialogcreator.hpp>
static ConcreteDialogCreator< FeeParamSysDlg > dlgCreator( CMD_GUI_FEE_PARAMETER_SYSTEM );

#ifdef _DEBUG
   #define new DEBUG_NEW
   #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


namespace
{
   const I_CHAR * const CLASSNAME						   = I_( "FeeParamSysDlg" );
   const I_CHAR* const  LV_SYSTEM_FEE					   = I_( "SystemFee" );
   const I_CHAR* const  LV_SCALE_FEE					   = I_( "ScaleFee" );
   const I_CHAR* const  PERCENT							   = I_( "Percent" );
   const I_CHAR * const FEE_CODE_MANAGEMENT_FEE			= I_( "18" );
   const I_CHAR * const FEE_CODE_SALE_CHARGE_FEE		= I_( "69" );
   const I_CHAR * const FEE_CPDE_MANAGEMENT_REBATE		= I_( "95" );
   const I_CHAR * const FEE_CODE_MANAGEMENT_DISCOUNT	= I_( "180" );
   const UINT SYSTEM_FEE_SEARCH							   = 2001;
   const I_CHAR * const YES								   = I_( "Y" );
   const I_CHAR * const NO								      = I_( "N" );
   const I_CHAR * const BASEDON_SCALE					   = I_( "1" );


   const I_CHAR * const NUMBERS							   = I_( "0123456789." );
   const I_CHAR * const NUMBERS_NEG 					   = I_( "-0123456789." );
   const I_CHAR * const	NOT_APPLY						   = I_( "NA" );
   const I_CHAR * const SEARCH_TYPE_ALL					= I_( "All" );
   const I_CHAR * const SEARCH_TYPE_FUND_CLASS			= I_( "FundClass" );
   const I_CHAR * const SEARCH_TYPE_BROKER				= I_( "Broker" );
   const I_CHAR * const SEARCH_TYPE_FEE_CODE			   = I_( "FeeCode" );
   const I_CHAR * const SEARCH_TYPE_COMMISSION_GROUP	= I_( "CommGroup" );
   const I_CHAR * const SEARCH_TYPE_SHARE_GROUP			= I_( "ShGroup" );
   const I_CHAR * const SEARCH_TYPE_BRANCH				= I_( "Branch" );
   const I_CHAR * const SEARCH_TYPE_SALES_REP			= I_( "SlsRep" );
   const I_CHAR * const SEARCH_TYPE_FEE_MODEL			= I_( "FeeModelOnly" );
   const I_CHAR * const SEARCH_TYPE_FEE_MODEL_FUND_CLASS = I_( "FeeModelFundClass" );

   const I_CHAR* const TAB_MAIN        = I_("Main");
   const I_CHAR* const TAB_CALCULATION = I_("Calculation");

}

namespace FEETYPE
{
   const I_CHAR * const FLAT                 = I_( "0" );
   const I_CHAR * const PERCENTAGE           = I_( "1" );
   const I_CHAR * const SCALE                = I_( "2" );
   const I_CHAR * const TIER                 = I_( "3" );
   const I_CHAR * const TIER_BY_THRESHOLD    = I_( "4" );
   const I_CHAR * const SCALE_BY_THRESHOLD   = I_( "5" );
}

namespace CND
{  // Conditions used
   extern const long GUI_ERR_UNKNOWN_EXCEPTION;
}

namespace UAF
{
   extern CLASS_IMPORT I_CHAR * const FEE_PARAMETER_SYSTEM;
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId FeeThresholdSysHeading;
   extern CLASS_IMPORT const BFDateFieldId CurrSysDate;
}
//******************************************************************************

FeeParamSysDlg::FeeParamSysDlg( CWnd* pParent, 
                                GenericInterfaceContainer* pGIC, 
                                GenericInterface* pGIParent, 
                                const Command& rCommand )
: BaseMainDlg( FeeParamSysDlg::IDD, pParent, pGIC, pGIParent, rCommand, CLASSNAME )
, m_bScaleListSelectionInProgress (false)
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   m_rbSearchBy = 1;

   //{{AFX_DATA_INIT(FeeParamSysDlg)
   // NOTE: the ClassWizard will add member initialization here
   //}}AFX_DATA_INIT
}

//******************************************************************************
FeeParamSysDlg::~FeeParamSysDlg()
{
   TRACE_DESTRUCTOR( CLASSNAME );
   //if( m_pFont )
   //{
   //   m_pFont->DeleteObject();
   //   delete m_pFont;
   //   m_pFont = NULL;
   //}
}
//******************************************************************************

void FeeParamSysDlg::DoDataExchange(CDataExchange* pDX)
{
   BaseMainDlg::DoDataExchange( pDX );
   //{{AFX_DATA_MAP(FeeParamSysDlg)
   // NOTE: the ClassWizard will add DDX and DDV calls here
   DDX_Radio(pDX, IDC_RB_SRC_ALL, m_rbSearchBy);
   //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(FeeParamSysDlg, BaseMainDlg)
//{{AFX_MSG_MAP(FeeParamSysDlg)
ON_BN_CLICKED(IDC_RESET, OnBtnReset)
ON_BN_CLICKED(IDC_ADD_FEE, OnBtnAddFeeParam)
ON_BN_CLICKED(IDC_DEL_FEE, OnBtnDelFeeParam)
ON_BN_CLICKED(IDC_MORE, OnBtnMoreFeeParam)
ON_BN_CLICKED(IDC__ADMIN, OnBtnAdmDates)
ON_MESSAGE( UM_OPENFUNDCLASSLISTDLG, OpenFundClassListDlg )
ON_MESSAGE( UM_OPENBROKERLISTDLG, OpenBrokerListDlg )
ON_MESSAGE( UM_OPENSLSREPLISTDLG, OpenSlsRepListDlg )
ON_MESSAGE( UM_OPENBRANCHLISTDLG, OpenBranchListDlg )
ON_BN_CLICKED( IDC_BTN_SEARCH, OnBtnSearch )
ON_BN_CLICKED( IDC_BTN_HISTORICAL_SYSTEM_FEE, OnBtnHistoricalSystemFee)
ON_BN_CLICKED( IDC_BTN_DETAILS, OnBtnDetails)
ON_BN_CLICKED(IDC_RB_SRC_ALL,      OnBtnSearchAll)
ON_BN_CLICKED(IDC_RB_SRC_EFF_DATE, OnBtnSearchEffDate)
ON_BN_CLICKED(IDC_BTN_COPY, OnBtnCopy)
//}}AFX_MSG_MAP

END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// FeeParamSysDlg message handlers


//******************************************************************************
void FeeParamSysDlg::OnPostInitDialog()
{
   TRACE_METHOD( CLASSNAME, I_( "OnPostInitDialog" ) );
   SetUserAccesFunctionCode (UAF::FEE_PARAMETER_SYSTEM);
   addBtnAddForPermissionCheck (IDC_ADD_FEE, IDC_SYSTEM_FEE_LIST);
   addBtnDeleteForPermissionCheck (IDC_DEL_FEE, IDC_SYSTEM_FEE_LIST);
   addControlsForSearchCriteria();
   addControls();
   
   DisplaySearchRelated ();
   DispFeeTypeRelated ();
   GetDlgItem (IDC_MORE)->EnableWindow (getParent()->doMoreRecordsExist (this, BF::AllContainerIds));
   EnableControls (m_FeeModelCode != NULL_STRING);
   GetDlgItem (IDC_BTN_COPY)->EnableWindow(false );
   GetDlgItem (IDC_BTN_HISTORICAL_SYSTEM_FEE)->EnableWindow(false );
   SetDefID (IDC_BTN_SEARCH);
   if(m_FeeModelCode != NULL_STRING)
   {
      LoadListControl(IDC_SYSTEM_FEE_LIST); 
   }
}

//**********************************************************************************
bool FeeParamSysDlg::doDisablePermCheckButton(UINT nID)
{
   if(nID == IDC_DEL_FEE)
   {  
      FeeParamSysProcess* pFeeParamSysProcess = dynamic_cast<FeeParamSysProcess*>(getParent());
      if(!pFeeParamSysProcess->canUpdate())
      {
         return true;
      }
   }

   return false;
}


//******************************************************************************
SEVERITY FeeParamSysDlg::doInit()
{
   SEVERITY sevRtn = SEVERE_ERROR;
   
   getParameter ( MFCAN_IP_PARAM::FEE_MODEL_CODE, m_FeeModelCode);

   sevRtn = NO_CONDITION;
   return(sevRtn);
}
//******************************************************************************
void FeeParamSysDlg::addControls( )
{
   TRACE_METHOD( CLASSNAME, I_( "addControls" ) );

   AddListControl( CLASSNAME, IDC_SYSTEM_FEE_LIST, I_("SYSTEM_FEE_LIST"),
                   ifds::FeeParamSysHeading, IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST, 0);
   
   AddListControl( CLASSNAME, IDC_FEE_SCALE_LIST, I_("SYSTEM_FEE_SCALE_LIST"),
                   ifds::FeeScaleSysHeading, IFASTBP_PROC::FEE_PARAM_SYSTEM_SCALE_LIST, IDC_SYSTEM_FEE_LIST, true);
   
   AddListControl( CLASSNAME, IDC_FEE_TRESHOLD_LIST, I_("SYSTEM_FEE_THRESHOLD_LIST"),
                   ifds::FeeThresholdSysHeading, IFASTBP_PROC::FEE_PARAM_SYSTEM_THRESHOLD_LIST, IDC_SYSTEM_FEE_LIST, true);

   AddListControl( CLASSNAME, IDC_FEE_SCALE_THR_LIST, I_("SYSTEM_FEE_SCALE_THR_LIST"),
                   ifds::FeeScaleSysHeading, IFASTBP_PROC::FEE_PARAM_SYSTEM_SCALE_THR_LIST, IDC_FEE_TRESHOLD_LIST, true);

   AddControl( CTRL_COMBO,  IDC_CMB_FEE_CODE,   IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST, 
               ifds::FeeCode,CTRLFLAG_INITCOMBO_BY_SUB_LIST,IDC_SYSTEM_FEE_LIST);
   AddControl( CTRL_COMBO,  IDC_CMB_SHAREHOLDER_GROUP,  IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST,
               ifds::ShGroup,CTRLFLAG_INITCOMBO_BY_SUB_LIST,IDC_SYSTEM_FEE_LIST);
   AddControl( CTRL_STATIC, IDC_TXT_GROUP_NAME, IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST, ifds::ShGroupName,
               0, IDC_SYSTEM_FEE_LIST);

   AddControl( CTRL_EDIT,    IDC_EDT_BROKER,   IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST, 
               ifds::BrokerCode,0,IDC_SYSTEM_FEE_LIST);

   AddControl( CTRL_STATIC,    IDC_TXT_BROKER,   IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST, 
               ifds::BrokerName,0,IDC_SYSTEM_FEE_LIST);

   AddControl( CTRL_EDIT,    IDC_EDT_BRANCH,   IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST, 
               ifds::BranchCode,0,IDC_SYSTEM_FEE_LIST);
   AddControl( CTRL_STATIC, IDC_TXT_BRANCH_NAME, IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST, ifds::BranchName,
               0, IDC_SYSTEM_FEE_LIST);
   AddControl( CTRL_EDIT,    IDC_EDT_SALES_REP,   IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST, 
               ifds::SlsrepCode,0,IDC_SYSTEM_FEE_LIST);
   AddControl( CTRL_STATIC, IDC_TXT_SALES_NAME, IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST, ifds::SlsrepName,
               0, IDC_SYSTEM_FEE_LIST);

   AddControl( CTRL_COMBO,  IDC_CMB_COMM_GROUP,  IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST,
				ifds::CommGroup,CTRLFLAG_INITCOMBO_BY_SUB_LIST,IDC_SYSTEM_FEE_LIST);	
   AddControl( CTRL_EDIT,    IDC_EDT_FUND_NUM,   IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST, 
               ifds::FundNumber,0,IDC_SYSTEM_FEE_LIST);
   AddControl( CTRL_EDIT,    IDC_EDT_FUND,   IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST, 
               ifds::FundCode,0,IDC_SYSTEM_FEE_LIST);
   AddControl( CTRL_EDIT,    IDC_EDT_FUND_CLASS,   IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST, 
               ifds::ClassCode,0,IDC_SYSTEM_FEE_LIST);
   AddControl( CTRL_EDIT,    IDC_EDT_FROM_FUND_NUM,   IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST, 
               ifds::FromFundNumber,0,IDC_SYSTEM_FEE_LIST);
   AddControl( CTRL_EDIT,    IDC_EDT_FROM_FUND,   IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST, 
               ifds::FundFromCode,0,IDC_SYSTEM_FEE_LIST);
   AddControl( CTRL_EDIT,    IDC_EDT_FROM_FUND_CLASS,   IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST, 
               ifds::ClassFromCode,0,IDC_SYSTEM_FEE_LIST);
   AddControl( CTRL_COMBO,    IDC_CMB_SCALE_TYPE,   IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST, 
               ifds::ParamFeeType,CTRLFLAG_INITCOMBO_BY_SUB_LIST,IDC_SYSTEM_FEE_LIST);
   AddControl( CTRL_EDIT,    IDC_EDT_FEE_RATE,   IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST, 
               ifds::Rate,0,IDC_SYSTEM_FEE_LIST);
   AddControl( CTRL_COMBO,  IDC_CMB_DISTRIB_CHANNEL,  IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST,
				   ifds::DistributionChannel, CTRLFLAG_INITCOMBO_BY_SUB_LIST, IDC_SYSTEM_FEE_LIST);	               
//upper/lower bound scale
//invest term scale
   
   //dynamic_cast<DSTEdit*>(GetControl( IDC_EDT_UPPER_BOUND ) )->SetAllowedChars( NUMBERS );
   //dynamic_cast<DSTEdit*>(GetControl( IDC_EDT_SCALE_RATE ) )->SetAllowedChars( NUMBERS );
   //dynamic_cast<DSTEdit*>(GetControl( IDC_EDT_LOWER_BOUND ) )->SetAllowedChars( NUMBERS );
   //dynamic_cast<DSTEdit*>(GetControl( IDC_EDT_MIN) )->SetAllowedChars( NUMBERS );
   //dynamic_cast<DSTEdit*>(GetControl( IDC_EDT_MAX ) )->SetAllowedChars( NUMBERS );

   //dynamic_cast<DSTEdit*>(GetControl( IDC_EDT_UPPER_BOUND ) )->SetMaxCharNum( 13 );
   //dynamic_cast<DSTEdit*>(GetControl( IDC_EDT_SCALE_RATE ) )->SetMaxCharNum( 13 );
   //dynamic_cast<DSTEdit*>(GetControl( IDC_EDT_LOWER_BOUND ) )->SetMaxCharNum( 13 );
   //dynamic_cast<DSTEdit*>(GetControl( IDC_EDT_MIN) )->SetMaxCharNum( 13 );
   //dynamic_cast<DSTEdit*>(GetControl( IDC_EDT_MAX ) )->SetMaxCharNum( 13 );

   //dynamic_cast<DSTEdit*>(GetControl( IDC_EDT_SCALE_INV_TERM ) )->SetAllowedChars( NUMBERS );

   //AddGrid( CLASSNAME, IDC_GRD_FEE_PARAM_SYS, I_("Grid_Attribute"), 
   //         IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST, IDC_SYSTEM_FEE_LIST, ifds::TradingAttributesHeadingSet, 
   //         ifds::SysFeeGridSet );

   //DSTGridWnd * grdWnd = GetGrid( IDC_GRD_FEE_PARAM_SYS );
   //grdWnd->GetParam( )->EnableTrackRowHeight( 0 );
   //grdWnd->SetRowHeight(0,39,20);

   //Alignment of the monthly AIP,SWP
   //m_pFont = new CFont();

   //if (m_pFont)
   //{
   //   CString strFaceName("Courier");
   //   m_pFont->CreatePointFont(10, strFaceName);
   //   GetDlgItem(IDC_TXT_BROKER)->SetFont(m_pFont);
   //   GetDlgItem(IDC_TXT_BRANCH_NAME)->SetFont(m_pFont);
   //   GetDlgItem(IDC_TXT_SALES_NAME)->SetFont(m_pFont);
   //}


   AddControl(CTRL_STATIC, IDC_ST_ON_PARTIAL_WITDRW);
   AddControl( CTRL_COMBO, IDC_CMB_ON_PARTIAL_WITDRW,   IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST,  ifds::OnPW,CTRLFLAG_INITCOMBO_BY_SUB_LIST,IDC_SYSTEM_FEE_LIST);
   AddControl(CTRL_STATIC, IDC_ST_ON_FULL_WITDRW);
   AddControl( CTRL_COMBO, IDC_CMB_ON_FULL_WITDRW,   IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST,  ifds::OnFW,CTRLFLAG_INITCOMBO_BY_SUB_LIST,IDC_SYSTEM_FEE_LIST);
   AddControl(CTRL_STATIC, IDC_ST_HOW_PAID);
   AddControl( CTRL_COMBO, IDC_CMB_HOW_PAID,   IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST,  ifds::HowPaid,CTRLFLAG_INITCOMBO_BY_SUB_LIST,IDC_SYSTEM_FEE_LIST);
   AddControl(CTRL_STATIC, IDC_ST_BASED_ON);
   AddControl( CTRL_COMBO, IDC_CMB_BASED_ON,   IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST,  ifds::BasedOn,CTRLFLAG_INITCOMBO_BY_SUB_LIST,IDC_SYSTEM_FEE_LIST);
   AddControl(CTRL_STATIC, IDC_ST_APPL_METHOD);
   AddControl( CTRL_COMBO, IDC_CMB_APPLIED_METHOD,   IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST,  ifds::AppliedMethod,CTRLFLAG_INITCOMBO_BY_SUB_LIST,IDC_SYSTEM_FEE_LIST);
   AddControl(CTRL_STATIC, IDC_ST_OVERRIDE);
   AddControl( CTRL_COMBO, IDC_CMB_OVERRIDE,   IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST,  ifds::AllowOverrideType,CTRLFLAG_INITCOMBO_BY_SUB_LIST,IDC_SYSTEM_FEE_LIST);
   
   
   AddControl(CTRL_STATIC, IDC_ST_FEE_CODE);
   AddControl(CTRL_DATE,  IDC_DTP_STOP_DATE, IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST, ifds::StopDate, CTRLFLAG_AUTO_UPDATE_ON_CHANGE,IDC_SYSTEM_FEE_LIST);    
   AddControl(CTRL_STATIC, IDC_ST_BRANCH);
   AddControl(CTRL_STATIC, IDC_ST_BROKER);
   AddControl(CTRL_STATIC, IDC_ST_SLS_REP);
   AddControl(CTRL_STATIC, IDC_ST_SHR_GROUP);
   AddControl(CTRL_STATIC, IDC_ST_TRSHLD_AMT);
   AddControl(CTRL_EDIT,   IDC_EDT_TRSHLD_AMT, IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST, ifds::ThresholdAmt,
      0,IDC_SYSTEM_FEE_LIST);
   AddControl(CTRL_STATIC, IDC_ST_TRSHLD_CURR);
   AddControl(CTRL_COMBO, IDC_CMB_TRSHLD_CURR, IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST, ifds::ThresholdCurrency, 
      CTRLFLAG_AUTO_UPDATE_ON_CHANGE | CTRLFLAG_INITCOMBO_BY_SUB_LIST, IDC_SYSTEM_FEE_LIST);    
   AddControl(CTRL_STATIC, IDC_ST_FEE_TYPE);
   AddControl(CTRL_STATIC, IDC_ST_FUND);
   AddControl(CTRL_STATIC, IDC_ST_CLASS);
   AddControl(CTRL_STATIC, IDC_ST_FUND_GROUP);
   AddControl(CTRL_STATIC, IDC_ST_MAX_RATE);
   AddControl(CTRL_EDIT,   IDC_EDT_MAX_RATE,  IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST, ifds::MaxFee,
         0,IDC_SYSTEM_FEE_LIST);
   AddControl(CTRL_STATIC, IDC_ST_FROM_FUND);
   AddControl(CTRL_STATIC, IDC_ST_FROM_CLASS);
   AddControl(CTRL_STATIC, IDC_TXT_FEE_RATE);
   AddControl(CTRL_STATIC, IDC_STC_DISTRIB_CHANNEL);
   AddControl(CTRL_STATIC, IDC_ST_CURRENCY);
   AddControl(CTRL_COMBO, IDC_CMB_CURRENCY, IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST, ifds::Currency, 
         CTRLFLAG_AUTO_UPDATE_ON_CHANGE | CTRLFLAG_INITCOMBO_BY_SUB_LIST, IDC_SYSTEM_FEE_LIST );    
   AddControl(CTRL_EDIT, IDC_EDT_MIN_RATE, IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST, ifds::MinFee,0,IDC_SYSTEM_FEE_LIST);
   AddControl(CTRL_STATIC, IDC_ST_FUND_LINK);
   AddControl(CTRL_STATIC, IDC_ST_EFF_DATE);
   AddControl(CTRL_DATE,  IDC_DTP_EFF_DATE, IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST, ifds::EffectiveDate, 
         CTRLFLAG_AUTO_UPDATE_ON_CHANGE,IDC_SYSTEM_FEE_LIST );    
   AddControl(CTRL_STATIC, IDC_ST_FEE_MODEL);

   AddControl(CTRL_STATIC, IDC_ST_STOP_DATE);
   AddControl(CTRL_STATIC, IDC_ST_MIN_RATE);
   AddControl(CTRL_STATIC, IDC_ST_TAX_INCLUSIVE);

   AddControl(CTRL_EDIT, IDC_EDT_FEE_MODEL, IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST, ifds::FeeModelCode,0,IDC_SYSTEM_FEE_LIST);
   AddControl(CTRL_COMBO, IDC_CMB_TAX_INCLUSIVE, IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST, ifds::TaxInclusive, CTRLFLAG_INITCOMBO_BY_SUB_LIST,IDC_SYSTEM_FEE_LIST);    
   AddControl(CTRL_EDIT, IDC_EDT_FUND_LINK, IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST, ifds::FundLink,0,IDC_SYSTEM_FEE_LIST);
   
   dynamic_cast<DSTEdit*>(GetControl(IDC_EDT_FUND_LINK))->SetMaxCharNum(4);


   AddControl(CTRL_STATIC, IDC_ST_FAM_CODE);
   AddControl(CTRL_EDIT, IDC_EDT_FAMILY_CODE, IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST, ifds::FamilyCode,0,IDC_SYSTEM_FEE_LIST);
   AddControl( CTRL_STATIC, IDC_TXT_FAMILY_NAME, IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST, ifds::FamilyName,0 ,IDC_SYSTEM_FEE_LIST);
   
   AddControl(CTRL_STATIC, IDC_ST_FUND_LIST);
   AddControl(CTRL_COMBO, IDC_CMB_FUND_LIST, IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST, ifds::FundList, CTRLFLAG_INITCOMBO_BY_SUB_LIST,IDC_SYSTEM_FEE_LIST);    

   dynamic_cast<DSTEdit*>(GetControl( IDC_EDT_MIN_RATE ))->SetAllowedChars( NUMBERS );
   dynamic_cast<DSTEdit*>(GetControl( IDC_EDT_MAX_RATE ) )->SetAllowedChars( NUMBERS );
   dynamic_cast<DSTEdit*>(GetControl(IDC_EDT_FEE_RATE))->SetAllowedChars( NUMBERS );
   
   m_pFeeParamSysTabControl = AddTabControl(CLASSNAME, IDC_TAB_FEE_PARAMS, I_("FeeParam"));
	//tab control
	if (m_pFeeParamSysTabControl)
	{
//		positionTabToControl(IDC_TAB_HYPO_RED, IDC_LV_SUMMARY);
		m_pFeeParamSysTabControl->AddTab(TAB_MAIN);
		m_pFeeParamSysTabControl->AddTab(TAB_CALCULATION);

      m_pFeeParamSysTabControl->registerControl(IDC_ST_FEE_CODE, TAB_MAIN);
      m_pFeeParamSysTabControl->registerControl(IDC_CMB_FEE_CODE, TAB_MAIN);
      m_pFeeParamSysTabControl->registerControl(IDC_DTP_STOP_DATE, TAB_MAIN);
      m_pFeeParamSysTabControl->registerControl(IDC_ST_BROKER, TAB_MAIN);
      m_pFeeParamSysTabControl->registerControl(IDC_ST_SHR_GROUP, TAB_MAIN);
      m_pFeeParamSysTabControl->registerControl(IDC_CMB_SHAREHOLDER_GROUP, TAB_MAIN);
      m_pFeeParamSysTabControl->registerControl(IDC_ST_STOP_DATE, TAB_MAIN);
      m_pFeeParamSysTabControl->registerControl(IDC_EDT_BROKER, TAB_MAIN);
      m_pFeeParamSysTabControl->registerControl(IDC_TXT_BROKER, TAB_MAIN);
      m_pFeeParamSysTabControl->registerControl(IDC_ST_TRSHLD_AMT, TAB_MAIN);
      m_pFeeParamSysTabControl->registerControl(IDC_EDT_TRSHLD_AMT, TAB_MAIN);
      m_pFeeParamSysTabControl->registerControl(IDC_ST_BRANCH, TAB_MAIN);
      m_pFeeParamSysTabControl->registerControl(IDC_EDT_BRANCH, TAB_MAIN);
      m_pFeeParamSysTabControl->registerControl(IDC_TXT_BRANCH_NAME, TAB_MAIN);
      m_pFeeParamSysTabControl->registerControl(IDC_ST_TRSHLD_CURR, TAB_MAIN);
      m_pFeeParamSysTabControl->registerControl(IDC_CMB_TRSHLD_CURR, TAB_MAIN);
      m_pFeeParamSysTabControl->registerControl(IDC_ST_SLS_REP, TAB_MAIN);
      m_pFeeParamSysTabControl->registerControl(IDC_EDT_SALES_REP, TAB_MAIN);
      m_pFeeParamSysTabControl->registerControl(IDC_TXT_SALES_NAME, TAB_MAIN);
      m_pFeeParamSysTabControl->registerControl(IDC_ST_FEE_TYPE, TAB_MAIN);
      m_pFeeParamSysTabControl->registerControl(IDC_CMB_SCALE_TYPE, TAB_MAIN);
      m_pFeeParamSysTabControl->registerControl(IDC_ST_FUND, TAB_MAIN);
      m_pFeeParamSysTabControl->registerControl(IDC_EDT_FUND_NUM, TAB_MAIN);
      m_pFeeParamSysTabControl->registerControl(IDC_EDT_FUND, TAB_MAIN);
      m_pFeeParamSysTabControl->registerControl(IDC_ST_CLASS, TAB_MAIN);
      m_pFeeParamSysTabControl->registerControl(IDC_EDT_FUND_CLASS, TAB_MAIN);
      m_pFeeParamSysTabControl->registerControl(IDC_ST_FUND_GROUP, TAB_MAIN);
      m_pFeeParamSysTabControl->registerControl(IDC_CMB_COMM_GROUP, TAB_MAIN);
      m_pFeeParamSysTabControl->registerControl(IDC_TXT_GROUP_NAME, TAB_MAIN);
      m_pFeeParamSysTabControl->registerControl(IDC_ST_MAX_RATE, TAB_MAIN);
      m_pFeeParamSysTabControl->registerControl(IDC_EDT_MAX_RATE, TAB_MAIN);
      m_pFeeParamSysTabControl->registerControl(IDC_ST_FROM_FUND, TAB_MAIN);
      m_pFeeParamSysTabControl->registerControl(IDC_EDT_FROM_FUND_NUM, TAB_MAIN);
      m_pFeeParamSysTabControl->registerControl(IDC_EDT_FROM_FUND, TAB_MAIN);
      m_pFeeParamSysTabControl->registerControl(IDC_ST_FROM_CLASS, TAB_MAIN);
      m_pFeeParamSysTabControl->registerControl(IDC_EDT_FROM_FUND_CLASS, TAB_MAIN);
      m_pFeeParamSysTabControl->registerControl(IDC_ST_MIN_RATE, TAB_MAIN);
      m_pFeeParamSysTabControl->registerControl(IDC_TXT_FEE_RATE, TAB_MAIN);
      m_pFeeParamSysTabControl->registerControl(IDC_EDT_FEE_RATE, TAB_MAIN);
      m_pFeeParamSysTabControl->registerControl(IDC_STC_DISTRIB_CHANNEL, TAB_MAIN);
      m_pFeeParamSysTabControl->registerControl(IDC_CMB_DISTRIB_CHANNEL, TAB_MAIN);
      m_pFeeParamSysTabControl->registerControl(IDC_ST_CURRENCY, TAB_MAIN);
      m_pFeeParamSysTabControl->registerControl(IDC_CMB_CURRENCY, TAB_MAIN);
      m_pFeeParamSysTabControl->registerControl(IDC_EDT_MIN_RATE, TAB_MAIN);
      m_pFeeParamSysTabControl->registerControl(IDC_CMB_TAX_INCLUSIVE, TAB_MAIN);
      m_pFeeParamSysTabControl->registerControl(IDC_ST_FUND_LINK, TAB_MAIN);
      m_pFeeParamSysTabControl->registerControl(IDC_ST_TAX_INCLUSIVE, TAB_MAIN);
      m_pFeeParamSysTabControl->registerControl(IDC_EDT_FUND_LINK, TAB_MAIN);
      m_pFeeParamSysTabControl->registerControl(IDC_ST_EFF_DATE, TAB_MAIN);
      m_pFeeParamSysTabControl->registerControl(IDC_DTP_EFF_DATE, TAB_MAIN);
      m_pFeeParamSysTabControl->registerControl(IDC_ST_FEE_MODEL, TAB_MAIN);
      m_pFeeParamSysTabControl->registerControl(IDC_EDT_FEE_MODEL, TAB_MAIN);
      m_pFeeParamSysTabControl->registerControl(IDC_ST_FAM_CODE, TAB_MAIN);
      m_pFeeParamSysTabControl->registerControl(IDC_EDT_FAMILY_CODE, TAB_MAIN);
      m_pFeeParamSysTabControl->registerControl(IDC_TXT_FAMILY_NAME, TAB_MAIN);
      m_pFeeParamSysTabControl->registerControl(IDC_ST_FUND_LIST, TAB_MAIN);
      m_pFeeParamSysTabControl->registerControl(IDC_CMB_FUND_LIST, TAB_MAIN);    



      m_pFeeParamSysTabControl->registerControl(IDC_ST_ON_PARTIAL_WITDRW,  TAB_CALCULATION);
      m_pFeeParamSysTabControl->registerControl(IDC_CMB_ON_PARTIAL_WITDRW, TAB_CALCULATION);
      m_pFeeParamSysTabControl->registerControl(IDC_ST_ON_FULL_WITDRW,     TAB_CALCULATION);
      m_pFeeParamSysTabControl->registerControl(IDC_CMB_ON_FULL_WITDRW,    TAB_CALCULATION);
      m_pFeeParamSysTabControl->registerControl(IDC_ST_HOW_PAID,           TAB_CALCULATION);
      m_pFeeParamSysTabControl->registerControl(IDC_CMB_HOW_PAID,          TAB_CALCULATION);
      m_pFeeParamSysTabControl->registerControl(IDC_ST_BASED_ON,           TAB_CALCULATION);
      m_pFeeParamSysTabControl->registerControl(IDC_CMB_BASED_ON,          TAB_CALCULATION); 
      m_pFeeParamSysTabControl->registerControl(IDC_ST_APPL_METHOD,        TAB_CALCULATION);
      m_pFeeParamSysTabControl->registerControl(IDC_CMB_APPLIED_METHOD,    TAB_CALCULATION);
      m_pFeeParamSysTabControl->registerControl(IDC_ST_OVERRIDE,           TAB_CALCULATION);
      m_pFeeParamSysTabControl->registerControl(IDC_CMB_OVERRIDE,          TAB_CALCULATION);

      m_pFeeParamSysTabControl->Load(TAB_MAIN);
      m_pFeeParamSysTabControl->SelectTab(TAB_MAIN, true);
	}
}
//******************************************************************************
bool FeeParamSysDlg::GetDataForControl ( UINT controlID,
                                         DString &strValueOut, 
                                         bool bFormatted,
                                         int index) const
{
   bool bRet = false;
   switch( controlID )
   {
	    case	IDC_CMB_SEARCH_PARAM:
         strValueOut = m_dstrSearchBy;
         bRet = true;
         break;;

		case 	IDC_CMB_COMM_GROUP:
			getParent()->getField(this,IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST, ifds::CommGroup, strValueOut,false);
			strValueOut.strip();
			if(strValueOut == NULL_STRING)strValueOut = NOT_APPLY;
			bRet = true;
			break;

   }
   return(bRet);
}

//*******************************************************************************
void FeeParamSysDlg::DispFeeTypeRelated ()
{
   bool bShowScale = false, 
         bShowFeeRate = false,
         bShowTerm = false;  
   bool bShowThreshold = false;
   int nCmdShowScale (SW_HIDE),
      nCmdShowTerm (SW_HIDE);

   const DString *crtKey = &getParent()->getCurrentListItemKey (this,IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST);

   if (crtKey && !(*crtKey).empty())
   {
      DString dstrFeeType,
         basedOn;

      getParent()->getField (this, IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST, ifds::ParamFeeType, dstrFeeType, false);
      getParent()->getField (this, IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST, ifds::BasedOn, basedOn, false);
      dstrFeeType.strip();
      basedOn.strip ();

      bShowScale = dstrFeeType == FEETYPE::SCALE || 
                   dstrFeeType == FEETYPE::TIER || 
                   dstrFeeType == FEETYPE::TIER_BY_THRESHOLD ||
                   dstrFeeType == FEETYPE::SCALE_BY_THRESHOLD ||
                   (dstrFeeType == FEETYPE::PERCENTAGE && basedOn == I_("6")); //investment term

      bShowThreshold = dstrFeeType == FEETYPE::TIER_BY_THRESHOLD ||
         dstrFeeType == FEETYPE::SCALE_BY_THRESHOLD;

      bShowTerm = dstrFeeType == FEETYPE::PERCENTAGE && basedOn == I_("6");
      nCmdShowScale = bShowScale && !bShowTerm ? SW_SHOW : SW_HIDE;
      nCmdShowTerm = bShowTerm ? SW_SHOW : SW_HIDE;
      bShowFeeRate = dstrFeeType == FEETYPE::PERCENTAGE || dstrFeeType == FEETYPE::FLAT;
      GetDlgItem (IDC_BTN_DETAILS)->EnableWindow (bShowScale);
   }
//fee rate
//   ShowControl (IDC_EDT_FEE_RATE, bShowFeeRate);
//   GetDlgItem (IDC_TXT_FEE_RATE )->ShowWindow (bShowFeeRate);
}

//*********************************************************************************
void FeeParamSysDlg::ControlUpdated( UINT controlID,
                                     const DString &strValue)
{
   switch (controlID)
   {
      case IDC_CMB_SCALE_TYPE:
      {
         if (!m_bScaleListSelectionInProgress)
         {
            DispFeeTypeRelated ();
            ConnectScaleControls ();
         }
         break;
      }
      case IDC_CMB_SEARCH_PARAM:
      { 
         DisplaySearchRelated ();
         break;
      }
      case IDC_EDT_BROKER:
      {
         LoadControl (IDC_TXT_BROKER);
         LoadControl (IDC_TXT_BRANCH_NAME);
         LoadControl (IDC_TXT_SALES_NAME);
         break;
      }
      case IDC_EDT_BRANCH:
      {
         LoadControl (IDC_TXT_BRANCH_NAME);
         LoadControl (IDC_TXT_SALES_NAME);
         break;
       }
      case IDC_EDT_SALES_REP:
      {
         LoadControl (IDC_TXT_SALES_NAME);
         break;
      }
      case IDC_CMB_FEE_CODE:
      {
          DString dstrAllowNeg;
          getParent()->getField(this, IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST, FEEPARAMSYS::ALLOW_NEG_RATE, dstrAllowNeg, false);

          if (dstrAllowNeg.stripAll().upperCase() == YES)
          {
              dynamic_cast<DSTEdit*>(GetControl(IDC_EDT_MIN_RATE))->SetAllowedChars( NUMBERS_NEG );
              dynamic_cast<DSTEdit*>(GetControl(IDC_EDT_MAX_RATE))->SetAllowedChars( NUMBERS_NEG );
              dynamic_cast<DSTEdit*>(GetControl(IDC_EDT_FEE_RATE))->SetAllowedChars( NUMBERS_NEG );
          }
          else 
          {
              dynamic_cast<DSTEdit*>(GetControl(IDC_EDT_MIN_RATE))->SetAllowedChars( NUMBERS );
              dynamic_cast<DSTEdit*>(GetControl(IDC_EDT_MAX_RATE))->SetAllowedChars( NUMBERS );
              dynamic_cast<DSTEdit*>(GetControl(IDC_EDT_FEE_RATE))->SetAllowedChars( NUMBERS );
          }
         break;
      }
	 default:
         break;
   }
}

//******************************************************************************
bool FeeParamSysDlg::doRefresh( GenericInterface * rpGICaller, 
                                const I_CHAR * szOriginalCommand)
{
   TRACE_METHOD (CLASSNAME, I_("doRefresh"));

   ConnectControlsToData ();
   LoadListControl (IDC_SYSTEM_FEE_LIST);
   return true;
}

//******************************************************************************
BOOL FeeParamSysDlg::PreTranslateMessage (MSG* pMsg) 
{

   if( pMsg->message == WM_KEYDOWN && ( int )( pMsg->wParam ) == VK_F4 && !IsSelectedCtrlUpdateable() )
      return(TRUE);

   if( pMsg->message == WM_KEYDOWN&&( int )( pMsg->wParam ) == VK_F4 )
   {
      if( GetFocus() == GetDlgItem( IDC_EDT_FUND ) )
      {
         PostMessage( UM_OPENFUNDCLASSLISTDLG );
         m_uiClassCodeDialogItem = IDC_EDT_FUND;
      }
      else if( GetFocus() == GetDlgItem( IDC_EDT_FUND_CLASS ) )
      {
         PostMessage( UM_OPENFUNDCLASSLISTDLG );
         m_uiClassCodeDialogItem = IDC_EDT_FUND_CLASS;
      }
      else if( GetFocus() == GetDlgItem( IDC_EDT_FUND_NUM ) )
      {
         PostMessage( UM_OPENFUNDCLASSLISTDLG );
         m_uiClassCodeDialogItem = IDC_EDT_FUND_NUM;
      }
	  else if( GetFocus() == GetDlgItem( IDC_EDT_FROM_FUND ) )
      {
         PostMessage( UM_OPENFUNDCLASSLISTDLG );
         m_uiClassCodeDialogItem = IDC_EDT_FROM_FUND;
      }
      else if( GetFocus() == GetDlgItem( IDC_EDT_FROM_FUND_CLASS ) )
      {
         PostMessage( UM_OPENFUNDCLASSLISTDLG );
         m_uiClassCodeDialogItem = IDC_EDT_FROM_FUND_CLASS;
      }
      else if( GetFocus() == GetDlgItem( IDC_EDT_FROM_FUND_NUM ) )
      {
         PostMessage( UM_OPENFUNDCLASSLISTDLG );
         m_uiClassCodeDialogItem = IDC_EDT_FROM_FUND_NUM;
      }
	  else if( GetFocus() == GetDlgItem( IDC_EDT_SEARCH_FUND_CODE ) )
      {
         PostMessage( UM_OPENFUNDCLASSLISTDLG );
         m_uiClassCodeDialogItem = IDC_EDT_SEARCH_FUND_CODE;
      }
	  else if( GetFocus() == GetDlgItem( IDC_EDT_SEARCH_CLASS_CODE ) )
      {
         PostMessage( UM_OPENFUNDCLASSLISTDLG );
         m_uiClassCodeDialogItem = IDC_EDT_SEARCH_CLASS_CODE;
      }

	  else if( GetFocus() == GetDlgItem( IDC_EDT_BROKER ) )
      {
         PostMessage( UM_OPENBROKERLISTDLG );
         m_uiClassCodeDialogItem = IDC_EDT_BROKER;
      }
	  else if( GetFocus() == GetDlgItem( IDC_EDT_SEARCH_BROKER ) )
      {
         PostMessage( UM_OPENBROKERLISTDLG );
         m_uiClassCodeDialogItem = IDC_EDT_SEARCH_BROKER;
      }
	  else if( GetFocus() == GetDlgItem( IDC_EDT_BRANCH ) )
      {
         PostMessage( UM_OPENBRANCHLISTDLG );
         m_uiClassCodeDialogItem = IDC_EDT_BRANCH;
      }
	  else if( GetFocus() == GetDlgItem( IDC_EDT_SEARCH_BRANCH ) )
      {
         PostMessage( UM_OPENBRANCHLISTDLG );
         m_uiClassCodeDialogItem = IDC_EDT_SEARCH_BRANCH;
      }
	  else if ( GetFocus() == GetDlgItem( IDC_EDT_SALES_REP ) )
	  {
		  PostMessage( UM_OPENSLSREPLISTDLG );
		  m_uiClassCodeDialogItem = IDC_EDT_SALES_REP;
	  }

	  else if ( GetFocus() == GetDlgItem( IDC_EDT_SEARCH_SALES_REP ) )
	  {
		  PostMessage( UM_OPENSLSREPLISTDLG );
		  m_uiClassCodeDialogItem = IDC_EDT_SEARCH_SALES_REP;
	  }
   }

   return(BaseMainDlg::PreTranslateMessage( pMsg ));
}
//******************************************************************************
LRESULT FeeParamSysDlg::OpenFundClassListDlg (WPARAM, LPARAM)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OpenFundClassListDlg" ) );

   try
   {
      E_COMMANDRETURN eRtn = CMD_CANCEL;
      CWaitCursor wait;  

      bool bFromFund = m_uiClassCodeDialogItem == IDC_EDT_FROM_FUND || m_uiClassCodeDialogItem == IDC_EDT_FROM_FUND_CLASS ;
      bool bFromSearch = m_uiClassCodeDialogItem == IDC_EDT_SEARCH_FUND_CODE || m_uiClassCodeDialogItem == IDC_EDT_SEARCH_CLASS_CODE ;
 
      switch( m_uiClassCodeDialogItem )
      {
         case IDC_EDT_FUND:
	      case IDC_EDT_FROM_FUND:
	      case IDC_EDT_SEARCH_FUND_CODE:
            {
               CString cstrFundCode;
               GetDlgItem( m_uiClassCodeDialogItem )->GetWindowText( cstrFundCode );
               DString dstrFundCode = cstrFundCode;
               setParameter( FUNDCLASSLIST::FUND_CODE, dstrFundCode );
               setParameter( FUNDCLASSLIST::CLASS_CODE, NULL_STRING );
               setParameter( FUNDCLASSLIST::FUND_NUMBER, NULL_STRING );
            }
            break;

         case IDC_EDT_FUND_CLASS:
         case IDC_EDT_FROM_FUND_CLASS:
         case IDC_EDT_SEARCH_CLASS_CODE:

            {
               CString cstrFundClass;
               GetDlgItem( m_uiClassCodeDialogItem )->GetWindowText( cstrFundClass );
               DString dstrFundClass = cstrFundClass;
               setParameter( FUNDCLASSLIST::FUND_CODE, NULL_STRING );
               setParameter( FUNDCLASSLIST::CLASS_CODE, dstrFundClass );
               setParameter( FUNDCLASSLIST::FUND_NUMBER, NULL_STRING );
            }
            break;

         case IDC_EDT_FUND_NUM:
		 case IDC_EDT_FROM_FUND_NUM:
            {
               CString cstrFundNumber;
               GetDlgItem( m_uiClassCodeDialogItem )->GetWindowText( cstrFundNumber );
               DString dstrFundNumber = cstrFundNumber;
               setParameter( FUNDCLASSLIST::FUND_CODE, NULL_STRING );
               setParameter( FUNDCLASSLIST::CLASS_CODE, NULL_STRING );
               setParameter( FUNDCLASSLIST::FUND_NUMBER, dstrFundNumber );
            }
            break;
        
      }

      eRtn = invokeCommand( getParent(), CMD_BPROC_FUNDCLASS, PROC_SUPPORT, true, NULL );
      switch( eRtn )
      {
         case CMD_OK:
         case CMD_MODELESS_INPROCESS:
            {
               DString dstrFundCode, dstrClassCode, dstrFundNumber;
               getParameter ( FUNDCLASSLIST::FUND_CODE, dstrFundCode );
               getParameter ( FUNDCLASSLIST::CLASS_CODE, dstrClassCode );
               getParameter ( FUNDCLASSLIST::FUND_NUMBER, dstrFundNumber );
			   if (bFromFund)  //from fund
			   {
				   getParent()->setField (this,IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST, ifds::FundFromCode, dstrFundCode );
				   getParent()->setField (this,IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST, ifds::ClassFromCode, dstrClassCode );
  				   getParent()->setField (this,IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST, ifds::FromFundNumber, dstrFundNumber );
				   LoadControl(IDC_EDT_FROM_FUND );
				   LoadControl(IDC_EDT_FROM_FUND_CLASS );
				   LoadControl(IDC_EDT_FROM_FUND_NUM );
			   }
			   else if (bFromSearch) //search fund
			   {
				   getParent()->setField (this,IFASTBP_PROC::FEE_PARAM_SEARCH, ifds::FundCode, dstrFundCode );
				   getParent()->setField (this,IFASTBP_PROC::FEE_PARAM_SEARCH, ifds::ClassCode, dstrClassCode );
				   LoadControl(IDC_EDT_SEARCH_FUND_CODE );
				   LoadControl(IDC_EDT_SEARCH_CLASS_CODE );

			   }
			   else		//fund
			   {
				   getParent()->setField (this,IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST, ifds::FundCode, dstrFundCode );
				   getParent()->setField (this,IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST, ifds::ClassCode, dstrClassCode );
               getParent()->setField (this,IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST, ifds::FundNumber, dstrFundNumber );
				   LoadControl(IDC_EDT_FUND );
				   LoadControl(IDC_EDT_FUND_CLASS );
				   LoadControl(IDC_EDT_FUND_NUM );

			   }
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

//******************************************************************
void FeeParamSysDlg::OnBtnHistoricalSystemFee()
{
   TRACE_METHOD( CLASSNAME, I_("OnBtnHistorical"));
   CWaitCursor wait;
   
   IFastHistoricalInfo f;
   f( this, IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST);}

//******************************************************************
void FeeParamSysDlg::OnBtnHistoricalFeeScale()
{
   TRACE_METHOD( CLASSNAME, I_("OnBtnHistorical"));
   CWaitCursor wait;
   
   IFastHistoricalInfo f;
   f( this, IFASTBP_PROC::FEE_PARAM_SYSTEM_SCALE_LIST);}

//******************************************************************************
void FeeParamSysDlg::OnBtnReset() 
{
   TRACE_METHOD( CLASSNAME, I_( "OnBtnReset" ) );

   ResetListItem( IDC_SYSTEM_FEE_LIST );

   	AbstractProcess * pParentProcess = dynamic_cast<AbstractProcess *>(getParentProcess());
	if ( pParentProcess->isCurrentListItemNew(this, IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST) )
	   	getParent()->setField(this,IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST,FEEPARAMSYS::RELOAD_OBJECT, YES,false);

   //DSTGridWnd* ghwnd = dynamic_cast<DSTGridWnd* >(GetDlgItem(IDC_GRD_FEE_PARAM_SYS) );
   //if( ghwnd )
   //   ghwnd->reLoadGrid();

   GetList( IDC_SYSTEM_FEE_LIST )->SetFocus();  
}

//*********************************************************************************
void FeeParamSysDlg::OnBtnAddFeeParam()
{
   TRACE_METHOD( CLASSNAME, I_( "OnBtnAddFeeParam" ) );
   AddToListControl( IDC_SYSTEM_FEE_LIST );
   EnableControls(true);
   GetList (IDC_SYSTEM_FEE_LIST)->SetFocus();
}

//********************************************************************************
void FeeParamSysDlg::OnBtnDelFeeParam()
{
   TRACE_METHOD( CLASSNAME, I_( "OnBtnDelFeeParam" ) );
   DeleteFromListControl( IDC_SYSTEM_FEE_LIST );
   GetList( IDC_SYSTEM_FEE_LIST )->SetFocus();
}

//**********************************************************************************
void FeeParamSysDlg::OnBtnMoreFeeParam()
{
   TRACE_METHOD( CLASSNAME, I_( "OnBtnMoreFeeParam" ) );
   CWaitCursor wait;
   const DString *crtKey = &getParent()->getCurrentListItemKey( this,IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST );
   if( getParent()->performSearch( this, BF::AllContainerIds, SEARCH_NEXT_BLOCK ) <= WARNING )
   {
      LoadListControl( IDC_SYSTEM_FEE_LIST );
      if( *crtKey != NULL_STRING )
      {
         GetList( IDC_SYSTEM_FEE_LIST )->SetSelection( crtKey );
      }
   }
	if( crtKey )getParent()->setCurrentListItem( this,IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST,*crtKey );
   GetDlgItem(IDC_MORE)->EnableWindow( getParent()->doMoreRecordsExist( this, BF::AllContainerIds ) );
   SetMessageStatusBar(NULL_STRING);   

}

//**********************************************************************************
void FeeParamSysDlg::OnBtnAdmDates() 
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OnBtnAdminDates" ) );
   CWaitCursor wait;
   ShowAdminDates( IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST );
}

//******************************************************************************
void FeeParamSysDlg::DoPreListItemChanged ( UINT listControlID,
                                            const DString &strKey,
                                            bool bIsNewItem,
                                            bool bIsDummyItem)
{
}

//************************************************************************************
void FeeParamSysDlg::DoListItemChanged( UINT listControlID,
                                        const DString &strKey, 
                                        bool bIsNewItem ,
                                        bool bIsDummyItem)
{
   if (listControlID == IDC_SYSTEM_FEE_LIST)
   {
      GetDlgItem (IDC_BTN_HISTORICAL_SYSTEM_FEE)->EnableWindow (!bIsNewItem && !bIsDummyItem);


      DSTCWorkSession *dstWorkSession = dynamic_cast<DSTCWorkSession *>(getParent()->getBFWorkSession());
      bool enableCopy = dstWorkSession->hasCreatePermission(UAF::FEE_PARAMETER_SYSTEM);
      GetDlgItem (IDC_BTN_COPY)->EnableWindow (enableCopy);

      DString dstrFeeType;
      DString basedOn;
      getParent()->getField (this, IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST, ifds::ParamFeeType, dstrFeeType, false);
      getParent()->getField (this, IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST, ifds::BasedOn, basedOn, false);
      dstrFeeType.strip();
      basedOn.strip ();
      bool bHasScale = dstrFeeType == FEETYPE::SCALE || 
                       dstrFeeType == FEETYPE::TIER || 
                       dstrFeeType == FEETYPE::TIER_BY_THRESHOLD ||
                       dstrFeeType == FEETYPE::SCALE_BY_THRESHOLD ||
                       (dstrFeeType == FEETYPE::PERCENTAGE && basedOn == I_("6")); //investment term
      

      bool bEnableDetails = bHasScale;

      //FeeParamSysProcess* pFeeParamSysProcess = dynamic_cast<FeeParamSysProcess*>(getParent());
      //if(pFeeParamSysProcess && !pFeeParamSysProcess->canUpdate())
      //{
      //   bEnableDetails = false;
      //}

      GetDlgItem (IDC_BTN_DETAILS)->EnableWindow (bEnableDetails);
   }
   else if (listControlID == IDC_FEE_TRESHOLD_LIST)
   {
      LoadListControl( IDC_FEE_SCALE_THR_LIST, &strKey );
   }
}

//****************************************************************************
bool FeeParamSysDlg::SetDataFromControl( UINT controlID,
                                         const DString &strValue,
                                         bool bFormatted,
                                         SEVERITY &sevRtn,
                                         int index)
{
	bool bRet = false;
	
   switch (controlID)
	{
		case 	IDC_CMB_COMM_GROUP:
		{
			DString dstr;
			if (strValue != NOT_APPLY) dstr = strValue;
			//GetCommGroup(strValue, dstr );
			sevRtn = getParent()->setField( this, IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST, ifds::CommGroup, dstr,false );
         ReloadListControl();
			bRet =  true;
			break;
		}

		case IDC_EDT_FUND_CLASS:
		{
			DString dstr(strValue);
			dstr.strip().upperCase();
			sevRtn = getParent()->setField( this, IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST, ifds::ClassCode, dstr,false );
			ReloadListControl ();
			bRet = true;
			break;
		}
		case IDC_EDT_FUND:
		{
			DString dstr(strValue);
			dstr.strip().upperCase();
			sevRtn = getParent()->setField( this, IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST, ifds::FundCode, dstr,false );
			ReloadListControl();
			bRet = true;
			break;
		}
	default:
		break;
	}
	return bRet;
}

//***************************************************************************
void FeeParamSysDlg::GetCommGroup(const DString& dstrDec,DString& dstrCode )
{
			const DString *pKey=&(getParent()->getFirstListItemKey( this, IFASTBP_PROC::FUND_COMM_GROUP_LIST ));
			if( (*pKey)!=NULL_STRING )
			 {
				DString str,strCode;
				
				do
				{
					getParent()->getField( this, IFASTBP_PROC::FUND_COMM_GROUP_LIST, ifds::GroupName, str );
					str.stripLeading().stripTrailing();
					getParent()->getField( this, IFASTBP_PROC::FUND_COMM_GROUP_LIST, ifds::FundGroup, strCode );
					strCode.strip();
					if(str == dstrDec )
					{
						dstrCode = strCode;
						break;					
					}				
				}while( *(pKey=&(getParent()->getNextListItemKey( this, IFASTBP_PROC::FUND_COMM_GROUP_LIST ))) != NULL_STRING );
			}


}

//****************************************************************************
void FeeParamSysDlg::addControlsForSearchCriteria()
{
	AddControl( CTRL_COMBO, IDC_CMB_SEARCH_PARAM, IFASTBP_PROC::FEE_PARAM_SEARCH, 
               ifds::SysFeeSearchType, CTRLFLAG_INITCOMBO_BY_SUB_LIST, SYSTEM_FEE_SEARCH);
	ConnectControlToData(IDC_CMB_SEARCH_PARAM,true );
	AddControl( CTRL_COMBO, IDC_CMB_SEARCH_FEE_CODE, IFASTBP_PROC::FEE_PARAM_SEARCH, 
               ifds::FeeCode, CTRLFLAG_INITCOMBO_BY_SUB_LIST, SYSTEM_FEE_SEARCH);

	AddControl( CTRL_COMBO, IDC_CMB_SEARCH_COMM_GROUP, IFASTBP_PROC::FEE_PARAM_SEARCH, 
               ifds::CommGroup, CTRLFLAG_INITCOMBO_BY_SUB_LIST, SYSTEM_FEE_SEARCH);

	AddControl( CTRL_COMBO, IDC_CMB_SEARCH_SHAREHOLDER_GROUP, IFASTBP_PROC::FEE_PARAM_SEARCH, 
               ifds::ShGroup, CTRLFLAG_INITCOMBO_BY_SUB_LIST, SYSTEM_FEE_SEARCH);

	AddControl( CTRL_EDIT,  IDC_EDT_SEARCH_BROKER,  IFASTBP_PROC::FEE_PARAM_SEARCH, 
              ifds::BrokerCode,0,SYSTEM_FEE_SEARCH); 
	AddControl( CTRL_EDIT,    IDC_EDT_SEARCH_FUND_CODE, IFASTBP_PROC::FEE_PARAM_SEARCH, 
               ifds::FundCode,0,SYSTEM_FEE_SEARCH);
	AddControl( CTRL_EDIT,    IDC_EDT_SEARCH_CLASS_CODE, IFASTBP_PROC::FEE_PARAM_SEARCH, 
               ifds::ClassCode,0,SYSTEM_FEE_SEARCH);
	AddControl( CTRL_EDIT,  IDC_EDT_SEARCH_BRANCH,  IFASTBP_PROC::FEE_PARAM_SEARCH, 
              ifds::BranchCode,0,SYSTEM_FEE_SEARCH); 
	AddControl( CTRL_EDIT,  IDC_EDT_SEARCH_SALES_REP,  IFASTBP_PROC::FEE_PARAM_SEARCH, 
              ifds::SlsrepCode,0,SYSTEM_FEE_SEARCH); 
	AddControl( CTRL_EDIT,  IDC_EDT_SEARCH_FEE_MODEL,  IFASTBP_PROC::FEE_PARAM_SEARCH, 
              ifds::FeeModelCode,0,SYSTEM_FEE_SEARCH); 

   AddControl( CTRL_CHECKBOX, IDC_RB_SRC_ALL,         CTRLFLAG_NOT_UPDATABLE | CTRLFLAG_GUI_FIELD );
   AddControl( CTRL_CHECKBOX, IDC_RB_SRC_EFF_DATE,    CTRLFLAG_NOT_UPDATABLE | CTRLFLAG_GUI_FIELD );
   AddControl( CTRL_DATE,     IDC_DTP_SRC_EFFECTIVE,  IFASTBP_PROC::FEE_PARAM_SEARCH, ifds::AsofDate,0,0);
   
   ConnectControlToData(IDC_DTP_SRC_EFFECTIVE, true);
   LoadControl(IDC_DTP_SRC_EFFECTIVE);

   ConnectControlToData(IDC_EDT_SEARCH_FEE_MODEL, true);
   LoadControl(IDC_EDT_SEARCH_FEE_MODEL);

   ConnectControlToData(IDC_CMB_SEARCH_PARAM, true);
   LoadControl(IDC_CMB_SEARCH_PARAM);
}

//****************************************************************************
void FeeParamSysDlg::DisplaySearchRelated()
{
   getParent()->getField(this,IFASTBP_PROC::FEE_PARAM_SEARCH,ifds::SysFeeSearchType,m_dstrSearchBy,false);
   m_dstrSearchBy.strip();

	UINT nShowBroker =  (m_dstrSearchBy == SEARCH_TYPE_BROKER || 
						m_dstrSearchBy == SEARCH_TYPE_FUND_CLASS ||
						m_dstrSearchBy == SEARCH_TYPE_BRANCH ||
						m_dstrSearchBy == SEARCH_TYPE_SALES_REP)? SW_SHOW:SW_HIDE;
	UINT nShowFundClass = ( m_dstrSearchBy == SEARCH_TYPE_FUND_CLASS || m_dstrSearchBy == SEARCH_TYPE_FEE_MODEL_FUND_CLASS)? SW_SHOW:SW_HIDE;

	UINT nShowFeeCode = (m_dstrSearchBy == SEARCH_TYPE_FEE_CODE || m_dstrSearchBy == SEARCH_TYPE_COMMISSION_GROUP )? SW_SHOW:SW_HIDE;

	UINT nShowCommGroup = (m_dstrSearchBy == SEARCH_TYPE_COMMISSION_GROUP ||  m_dstrSearchBy == SEARCH_TYPE_FEE_CODE)? SW_SHOW:SW_HIDE;
	UINT nShowShareholderGroup = (m_dstrSearchBy == SEARCH_TYPE_SHARE_GROUP )? SW_SHOW:SW_HIDE;
	UINT nShowBranch =  (m_dstrSearchBy == SEARCH_TYPE_BRANCH ||
						m_dstrSearchBy == SEARCH_TYPE_SALES_REP)? SW_SHOW:SW_HIDE;
	UINT nShowSalesRep =  (m_dstrSearchBy == SEARCH_TYPE_SALES_REP)? SW_SHOW:SW_HIDE;
	UINT nShowFeeModel =  (m_dstrSearchBy == SEARCH_TYPE_FEE_MODEL || m_dstrSearchBy == SEARCH_TYPE_FEE_MODEL_FUND_CLASS)? SW_SHOW:SW_HIDE;


	//FundClass, Broker
   GetDlgItem( IDC_TXT_SEARCH_FUND_CODE )->ShowWindow( nShowFundClass);
   GetDlgItem( IDC_EDT_SEARCH_FUND_CODE )->ShowWindow(  nShowFundClass);

   GetDlgItem( IDC_TXT_SEARCH_BROKER )->ShowWindow( nShowBroker );
   GetDlgItem( IDC_EDT_SEARCH_BROKER )->ShowWindow( nShowBroker );

   GetDlgItem( IDC_TXT_SEARCH_CLASS_CODE )->ShowWindow( nShowFundClass );
   GetDlgItem( IDC_EDT_SEARCH_CLASS_CODE )->ShowWindow( nShowFundClass);
   ConnectControlToData(IDC_EDT_SEARCH_FUND_CODE,nShowFundClass?true:false,true);
   ConnectControlToData(IDC_EDT_SEARCH_BROKER,nShowBroker?true:false,true);
   ConnectControlToData(IDC_EDT_SEARCH_CLASS_CODE,nShowFundClass?true:false,true);

//Fee Code
   GetDlgItem( IDC_TXT_SEARCH_FEE_CODE )->ShowWindow( nShowFeeCode );
   GetDlgItem( IDC_CMB_SEARCH_FEE_CODE )->ShowWindow(  nShowFeeCode);
   ConnectControlToData(IDC_CMB_SEARCH_FEE_CODE, nShowFeeCode?true:false,true);

//Comm Group
   GetDlgItem( IDC_TXT_SEARCH_COMM_GROUP )->ShowWindow(  nShowCommGroup);

   GetDlgItem( IDC_CMB_SEARCH_COMM_GROUP )->ShowWindow( nShowCommGroup );
   ConnectControlToData(IDC_CMB_SEARCH_COMM_GROUP, nShowCommGroup?true:false,true);

	  
//ShareHolder Group
	GetDlgItem( IDC_CMB_SEARCH_SHAREHOLDER_GROUP )->ShowWindow( nShowShareholderGroup );
	GetDlgItem( IDC_TXT_SEARCH_SHAREHOLDER_GROUP )->ShowWindow( nShowShareholderGroup );
	ConnectControlToData(IDC_CMB_SEARCH_SHAREHOLDER_GROUP, nShowShareholderGroup?true:false,true);

//Branch
   GetDlgItem( IDC_TXT_SEARCH_BRANCH )->ShowWindow( nShowBranch );
   GetDlgItem( IDC_EDT_SEARCH_BRANCH )->ShowWindow( nShowBranch );
   ConnectControlToData(IDC_EDT_SEARCH_BRANCH,nShowBranch?true:false,true);

//SalesRep
   GetDlgItem( IDC_TXT_SEARCH_SALES_REP )->ShowWindow( nShowSalesRep );
   GetDlgItem( IDC_EDT_SEARCH_SALES_REP )->ShowWindow( nShowSalesRep );
   ConnectControlToData(IDC_EDT_SEARCH_SALES_REP,nShowSalesRep?true:false,true);

   GetDlgItem(IDC_TXT_SRCH_FEE_MODEL)->ShowWindow(nShowFeeModel);
   GetDlgItem(IDC_EDT_SEARCH_FEE_MODEL)->ShowWindow(nShowFeeModel);
   ConnectControlToData(IDC_EDT_SEARCH_FEE_MODEL, nShowFeeModel ? true : false, true);
   

	LoadControls(SYSTEM_FEE_SEARCH);
}
//****************************************************************************
void FeeParamSysDlg::GetCellProperties( UINT ctrlId, 
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
                                       int& nComboSortingMode ,
                                       DString& dstrAllowedChar)	 
{
   dstrAllowedChar = NULL_STRING;
   if( colKey  == _T("Attribute") )
   {
      nCellState  = DSTGridWnd::CELL_STATE::SKIPPED;
   }
   else if( colKey  == _T("Value") )
   {
      if( rowKey  == _T("EffectiveDate") )
      {
         idContainer = IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST;
         idField     = ifds::EffectiveDate;
         nCellState  = DSTGridWnd::CELL_STATE::USE_FIELD_PROPERTY;
         cellCtrlType = GX_IDS_CTRL_DATETIME;   
      }
      else if( rowKey == _T("StopDate") )
      {
         idContainer = IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST;
         idField     = ifds::StopDate;
         nCellState  = DSTGridWnd::CELL_STATE::USE_FIELD_PROPERTY;
         cellCtrlType = GX_IDS_CTRL_DATETIMENOCAL;   
      }
      else if( rowKey  == _T("HowPaid") )
      {
         idContainer = IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST;
         idField     = ifds::HowPaid;
         nCellState  = DSTGridWnd::CELL_STATE::USE_FIELD_PROPERTY;
         cellCtrlType = GX_IDS_CTRL_CBS_DROPDOWNLIST;
         nCtrlInitMode = DSTGridWnd::COMBO_INIT_MODE::USE_SUBSTITUTION_LIST;
         idSubstitution = ifds::HowPaid;
      }
      else if( rowKey == _T("BasedOn") )
      {
         idContainer = IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST;
         idField     = ifds::BasedOn;
         nCellState  = DSTGridWnd::CELL_STATE::USE_FIELD_PROPERTY;
         cellCtrlType = GX_IDS_CTRL_CBS_DROPDOWNLIST;  
         nCtrlInitMode = DSTGridWnd::COMBO_INIT_MODE::USE_SUBSTITUTION_LIST;
         idSubstitution = ifds::BasedOn;
      }
      else if( rowKey == _T("MinFee") )
      {
         idContainer = IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST;
         idField     = ifds::MinFee;
         nCellState  = DSTGridWnd::CELL_STATE::USE_FIELD_PROPERTY;
         cellCtrlType = GX_IDS_CTRL_EDIT;   
      }
      else if( rowKey == _T("MaxFee") )
      {
         idContainer = IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST;
         idField     = ifds::MaxFee;
         nCellState  = DSTGridWnd::CELL_STATE::USE_FIELD_PROPERTY;
         cellCtrlType = GX_IDS_CTRL_EDIT;   
      }
      else if( rowKey == _T("Currency") )
      {
         idContainer = IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST;
         idField     = ifds::Currency;
         nCellState  = DSTGridWnd::CELL_STATE::USE_FIELD_PROPERTY;
         cellCtrlType = GX_IDS_CTRL_CBS_DROPDOWNLIST;
         nCtrlInitMode = DSTGridWnd::COMBO_INIT_MODE::USE_SUBSTITUTION_LIST;
         idSubstitution = ifds::Currency;
      }
      else if( rowKey  == _T("OnPW") )
      {
         idContainer = IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST;
         idField     = ifds::OnPW;
         nCellState  = DSTGridWnd::CELL_STATE::USE_FIELD_PROPERTY;
         cellCtrlType = GX_IDS_CTRL_CBS_DROPDOWNLIST;
         nCtrlInitMode = DSTGridWnd::COMBO_INIT_MODE::USE_SUBSTITUTION_LIST;
         idSubstitution = ifds::OnPW;
      }
      else if( rowKey  == _T("OnFW") )
      {
         idContainer = IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST;
         idField     = ifds::OnFW;
         nCellState  = DSTGridWnd::CELL_STATE::USE_FIELD_PROPERTY;
         cellCtrlType = GX_IDS_CTRL_CBS_DROPDOWNLIST;
         nCtrlInitMode = DSTGridWnd::COMBO_INIT_MODE::USE_SUBSTITUTION_LIST;
         idSubstitution = ifds::OnFW;
      }
      else if( rowKey  == _T("AllowOverrideType") )
      {
         idContainer = IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST;
         idField     = ifds::AllowOverrideType;
         nCellState  = DSTGridWnd::CELL_STATE::USE_FIELD_PROPERTY;
         cellCtrlType = GX_IDS_CTRL_CBS_DROPDOWNLIST;
         nCtrlInitMode = DSTGridWnd::COMBO_INIT_MODE::USE_SUBSTITUTION_LIST;
         idSubstitution = ifds::AllowOverrideType;
      }
      else if( rowKey == _T("AppliedMethod") )
      {
         idContainer = IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST;
         idField     = ifds::AppliedMethod;
         nCellState  = DSTGridWnd::CELL_STATE::USE_FIELD_PROPERTY;
         cellCtrlType = GX_IDS_CTRL_CBS_DROPDOWNLIST;  
         nCtrlInitMode = DSTGridWnd::COMBO_INIT_MODE::USE_SUBSTITUTION_LIST;
         idSubstitution = ifds::AppliedMethod;
      }
      else if( rowKey  == _T("FundList") )
      {
         idContainer = IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST;
         idField     = ifds::FundList;
         nCellState  = DSTGridWnd::CELL_STATE::USE_FIELD_PROPERTY;
         cellCtrlType = GX_IDS_CTRL_CBS_DROPDOWNLIST;
         nCtrlInitMode = DSTGridWnd::COMBO_INIT_MODE::USE_SUBSTITUTION_LIST;
         idSubstitution = ifds::FundList;
      }
	  else if( rowKey  == _T("ThresholdAmt") )
      {        
		 idContainer = IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST;
         idField     = ifds::ThresholdAmt;
         nCellState  = DSTGridWnd::CELL_STATE::USE_FIELD_PROPERTY;
         cellCtrlType = GX_IDS_CTRL_EDIT;   
      }
	  else if( rowKey == _T("ThresholdCurrency") )
      {
         idContainer = IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST;
         idField     = ifds::ThresholdCurrency;
         nCellState  = DSTGridWnd::CELL_STATE::USE_FIELD_PROPERTY;
         cellCtrlType = GX_IDS_CTRL_CBS_DROPDOWNLIST;  
         nCtrlInitMode = DSTGridWnd::COMBO_INIT_MODE::USE_SUBSTITUTION_LIST;
         idSubstitution = ifds::ThresholdCurrency;
      }
   }
}

//*******************************************************************************
bool FeeParamSysDlg::OnGridSetCellValue( UINT ctrlId,
                                         const DString &rowKey,
                                         const DString &colKey,
                                         const DString &strIn)
{

   //if (IDC_GRD_FEE_PARAM_SYS == ctrlId)
   //{
   //   if (rowKey == _T("BasedOn"))
   //   {
   //      if (!m_bScaleListSelectionInProgress)
   //      {
   //         DispFeeTypeRelated ();
   //         ConnectScaleControls ();
   //      }
   //   }
   //}
   return false;
}

//*****************************************************************************
void FeeParamSysDlg::OnBtnSearch()
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OnBtnSearch" ) );
   BaseControl* pBControl = dynamic_cast<BaseControl*>(GetFocus());
   if( pBControl )  pBControl->Store();
	DString dstrUpdate;
   getParent()->getField(this, BF::NullContainerId, FEEPARAMSYS::HAS_OBJECT_UPDATE, dstrUpdate );
	bool bSearch = true;
	CString cstr;
	cstr.LoadString( TXT_WARNING_LOST_CHANGE );
	if( dstrUpdate == YES  )
	{
		if( IDNO == AfxMessageBox( TXT_WARNING_LOST_CHANGE, MB_YESNO ) )
			bSearch = false;
	}

	if( bSearch )
	{	
		SEVERITY sev = getParent()->performSearch( this, IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST, SEARCH_START );
		if( sev  <= WARNING )
		{
			LoadListControl(IDC_SYSTEM_FEE_LIST); 

			DString dstrValue;
			DSTComboBox* pCmb = dynamic_cast<DSTComboBox* >(GetControl(IDC_CMB_SEARCH_PARAM) );
			if( pCmb )
			{
				int i = pCmb->GetCurSel();
				dstrValue = *reinterpret_cast< DString * >( pCmb->GetItemData( i )  );     
				getParent()->setField(this,IFASTBP_PROC::FEE_PARAM_SEARCH, ifds::SysFeeSearchType,dstrValue,true);
			}
			GetDlgItem(IDC_MORE)->EnableWindow( getParent()->doMoreRecordsExist( this, BF::AllContainerIds ) );
            EnableControls(true);
			setUpdateFlag(false);
			SetDefID(IDOK);
		}
		else
		{
		LoadControls(SYSTEM_FEE_SEARCH);  
		}
	}
}
//************************************************************************************
void FeeParamSysDlg::EnableSearchCriteria(bool bEnable)
{ 
   GetDlgItem(IDC_BTN_SEARCH)->EnableWindow(bEnable);  
}

//************************************************************************************
LRESULT FeeParamSysDlg::OpenBrokerListDlg( WPARAM, LPARAM )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OpenBrokerListDlg" ) );

   try
   {
      E_COMMANDRETURN eRtn = CMD_CANCEL;
      CWaitCursor wait;

      DString dstrBrokerCode;
	  bool bFromSearch = (m_uiClassCodeDialogItem==IDC_EDT_SEARCH_BROKER)?true:false;

      GetControlText( bFromSearch?IDC_EDT_SEARCH_BROKER:IDC_EDT_BROKER, dstrBrokerCode );
	  setParameter( MFCAN_IP_PARAM::BROKER_CODE, dstrBrokerCode );

      //invoke the broker dialog and process
      eRtn = invokeCommand( getParent(), CMD_BPROC_BROKER, PROC_SUPPORT, true, NULL );
      switch( eRtn )
      {
         case CMD_OK:
         case CMD_MODELESS_INPROCESS:
            {
               //get the broker code that the user selected from the branch list and 
               //set the field on the account object
               DString brokerCode;

               getParameter( MFCAN_IP_PARAM::BROKER_CODE, brokerCode );
               if( brokerCode != NULL_STRING )
               {
                  bool success = SetControlText( bFromSearch?IDC_EDT_SEARCH_BROKER:IDC_EDT_BROKER, brokerCode );
                  BaseControl * pBC = dynamic_cast< BaseControl *> (GetDlgItem( IDC_EDT_BROKER ));
                  if( !success && pBC )
                     pBC->Load();
                  if( pBC && pBC->IsToolTipVisible() )
                     pBC->ToggleToolTip();
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


//************************************************************************************
LRESULT FeeParamSysDlg::OpenSlsRepListDlg( WPARAM, LPARAM ) 
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OpenSlsRepListDlg" ) );

   try
   {
      E_COMMANDRETURN eRtn = CMD_CANCEL;

      DString dstrBrokerCode, dstrBranchCode;

	  bool bFromSearch = (m_uiClassCodeDialogItem==IDC_EDT_SEARCH_SALES_REP)?true:false;

      GetControlText( bFromSearch?IDC_EDT_SEARCH_BROKER:IDC_EDT_BROKER, dstrBrokerCode );
      setParameter( MFCAN_IP_PARAM::BROKER_CODE, dstrBrokerCode );
	  
	  if ( bFromSearch )
	  {
	     GetControlText(IDC_EDT_SEARCH_BRANCH, dstrBranchCode );
	  }
	  else
	  {
		  DString strRepByBranch = YES;
		  dynamic_cast<DSTCWorkSession *>(getBFWorkSession())->getOption(  ifds::RepByBranch, strRepByBranch, BF::HOST );
		  if( strRepByBranch == NO )
		  {
			  //get default branch code
				getParent()->getField(this, BF::NullContainerId, FEEPARAMSYS::GET_DEFAULT_BRANCH_CODE, dstrBranchCode );

		  }
		  else
		  {
				GetControlText( IDC_EDT_BRANCH, dstrBranchCode );
		  }
	  }
      setParameter( MFCAN_IP_PARAM::BRANCH_CODE, dstrBranchCode );

      //invoke the broker dialog and process
      eRtn = invokeCommand( getParent(), CMD_BPROC_SLSREP, PROC_SUPPORT, true, NULL );
      switch( eRtn )
      {
         case CMD_OK:
         case CMD_MODELESS_INPROCESS:
            {
               //get the broker code that the user selected from the branch list and 
               //set the field on the FeeParamSys object
               DString dstrAgentCode;

               getParameter( MFCAN_IP_PARAM::SALES_REP_CODE, dstrAgentCode );
               if( !dstrBrokerCode.empty() )
               {
                  bool bSuccess = SetControlText( bFromSearch?IDC_EDT_SEARCH_SALES_REP: IDC_EDT_SALES_REP, dstrAgentCode );
                  BaseControl * pBC = dynamic_cast< BaseControl *> (GetDlgItem( bFromSearch?IDC_EDT_SEARCH_SALES_REP:IDC_EDT_SALES_REP ));
                  if( !bSuccess && pBC )
                     pBC->Load();
                  if( pBC && pBC->IsToolTipVisible() )
                     pBC->ToggleToolTip();
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

//************************************************************************************
LRESULT FeeParamSysDlg::OpenBranchListDlg( WPARAM, LPARAM )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OpenBranchListDlg" ) );
   //don't allow any changes for not updatable Branch !!
   DString strRepByBranch = YES;
   dynamic_cast<DSTCWorkSession *>(getBFWorkSession())->getOption(  ifds::RepByBranch, strRepByBranch, BF::HOST );
   if( strRepByBranch == NO )
      return(-1);
   //
   bool bFromSearch = (m_uiClassCodeDialogItem==IDC_EDT_SEARCH_BRANCH)?true:false;

   try
   {
      E_COMMANDRETURN eRtn = CMD_CANCEL;

      DString dstrBrokerCode;

      GetControlText( bFromSearch?IDC_EDT_SEARCH_BROKER:IDC_EDT_BROKER, dstrBrokerCode );
      setParameter( MFCAN_IP_PARAM::BROKER_CODE, dstrBrokerCode );
      //invoke the broker dialog and process
      eRtn = invokeCommand( getParent(), CMD_BPROC_BRANCH, PROC_SUPPORT, true, NULL );
      switch( eRtn )
      {
         case CMD_OK:
         case CMD_MODELESS_INPROCESS:
            {
               //get the broker code that the user selected from the branch list and 
               //set the field on the FeeParamSys object
               DString branchCode;

               getParameter( MFCAN_IP_PARAM::BRANCH_CODE, branchCode );
               if( !dstrBrokerCode.empty() )
               {
                  bool success = SetControlText(bFromSearch?IDC_EDT_SEARCH_BRANCH: IDC_EDT_BRANCH, branchCode );
                  BaseControl * pBC = dynamic_cast< BaseControl *> (GetDlgItem(bFromSearch?IDC_EDT_SEARCH_BRANCH: IDC_EDT_BRANCH ));
                  if( !success && pBC )
                     pBC->Load();
                  if( pBC && pBC->IsToolTipVisible() )
                     pBC->ToggleToolTip();
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

void FeeParamSysDlg::EnableControls (bool bEnable)
{
   GetDlgItem(IDC_EDT_BROKER)->EnableWindow(bEnable);
   GetDlgItem(IDC_EDT_FUND_NUM)->EnableWindow(bEnable);
   GetDlgItem(IDC_EDT_FROM_FUND_NUM)->EnableWindow(bEnable);
   GetDlgItem(IDC_EDT_FUND)->EnableWindow(bEnable);
   GetDlgItem(IDC_EDT_FROM_FUND)->EnableWindow(bEnable);
   GetDlgItem(IDC_EDT_FUND_CLASS)->EnableWindow(bEnable);
   GetDlgItem(IDC_EDT_FROM_FUND_CLASS)->EnableWindow(bEnable);
   GetDlgItem(IDC_CMB_FEE_CODE)->EnableWindow(bEnable);
   GetDlgItem(IDC_CMB_SHAREHOLDER_GROUP)->EnableWindow(bEnable);
   GetDlgItem(IDC_CMB_COMM_GROUP)->EnableWindow(bEnable);
   GetDlgItem(IDC_CMB_SCALE_TYPE)->EnableWindow(bEnable);
   GetDlgItem(IDC_EDT_FEE_RATE)->EnableWindow(bEnable);
   GetDlgItem(IDC_RESET)->EnableWindow(bEnable);
   GetDlgItem(IDC__ADMIN)->EnableWindow(bEnable);
   GetDlgItem(IDC_EDT_BRANCH)->EnableWindow(bEnable);
   GetDlgItem(IDC_EDT_SALES_REP)->EnableWindow(bEnable);
   GetDlgItem(IDC_STC_DISTRIB_CHANNEL)->EnableWindow(bEnable);
   GetDlgItem(IDC_CMB_DISTRIB_CHANNEL)->EnableWindow(bEnable);
   GetDlgItem(IDC_DTP_EFF_DATE)->EnableWindow(bEnable);
   GetDlgItem(IDC_DTP_STOP_DATE)->EnableWindow(bEnable);
   GetDlgItem(IDC_EDT_TRSHLD_AMT)->EnableWindow(bEnable);
   GetDlgItem(IDC_CMB_TRSHLD_CURR)->EnableWindow(bEnable);
   GetDlgItem(IDC_EDT_MIN_RATE)->EnableWindow(bEnable);
   GetDlgItem(IDC_EDT_MAX_RATE)->EnableWindow(bEnable);
   GetDlgItem(IDC_CMB_TAX_INCLUSIVE)->EnableWindow(bEnable);
   GetDlgItem(IDC_CMB_CURRENCY)->EnableWindow(bEnable);
   GetDlgItem(IDC_EDT_FEE_MODEL)->EnableWindow(bEnable);
   GetDlgItem(IDC_EDT_FUND_LINK)->EnableWindow(bEnable);
   GetDlgItem(IDC_CMB_ON_PARTIAL_WITDRW)->EnableWindow(bEnable);
   GetDlgItem(IDC_CMB_ON_FULL_WITDRW)->EnableWindow(bEnable);
   GetDlgItem(IDC_CMB_HOW_PAID)->EnableWindow(bEnable);
   GetDlgItem(IDC_CMB_BASED_ON)->EnableWindow(bEnable);
   GetDlgItem(IDC_CMB_APPLIED_METHOD)->EnableWindow(bEnable);
   GetDlgItem(IDC_CMB_OVERRIDE)->EnableWindow(bEnable);
   GetDlgItem(IDC_EDT_FAMILY_CODE)->EnableWindow(bEnable);
   GetDlgItem(IDC_CMB_FUND_LIST)->EnableWindow(bEnable);

}

//******************************************************************************
void FeeParamSysDlg::ReloadListControl()
{
	const DString *crtKey = &getParent()->getCurrentListItemKey( this,IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST );
	
   if (crtKey && !(*crtKey).empty())
	{
		 LoadListControl(IDC_SYSTEM_FEE_LIST);
		 GetList (IDC_SYSTEM_FEE_LIST)->SetSelection (crtKey);
	 	 getParent()->setCurrentListItem (this,IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST, *crtKey);
	}
}

//******************************************************************************
void FeeParamSysDlg::ConnectScaleControls ()
{
	DString dstrFeeType,
      basedOn;
   bool bShowScale, 
      bShowInvestTerm;
   bool bShowThreshold = false;

   getParent()->getField (this, IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST, ifds::ParamFeeType, dstrFeeType, false);
   getParent()->getField (this, IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST, ifds::BasedOn, basedOn, false);
	dstrFeeType.strip();
   basedOn.strip ();
   bShowScale = dstrFeeType == FEETYPE::SCALE || 
                dstrFeeType == FEETYPE::TIER || 
                (dstrFeeType == FEETYPE::PERCENTAGE && basedOn == I_("6")); //investment term
   bShowInvestTerm = dstrFeeType == FEETYPE::PERCENTAGE && basedOn == I_("6");
		   
   bShowThreshold = dstrFeeType == FEETYPE::TIER_BY_THRESHOLD ||
      dstrFeeType == FEETYPE::SCALE_BY_THRESHOLD;

   if (bShowScale)
   {
      if (bShowInvestTerm)
      {
         ReInitListControl (IDC_FEE_SCALE_LIST, 
                            ifds::FeeScaleSysInvestTermHeading, 
                            IFASTBP_PROC::FEE_PARAM_SYSTEM_SCALE_LIST,
                            I_("SYSTEM_FEE_SCALE_LIST"));
      }
      else 
      {
         ReInitListControl (IDC_FEE_SCALE_LIST, 
                            ifds::FeeScaleSysHeading, 
                            IFASTBP_PROC::FEE_PARAM_SYSTEM_SCALE_LIST,
                            I_("SYSTEM_FEE_SCALE_LIST"));
      }
      ConnectListToData (IDC_FEE_SCALE_LIST, true, true);
      LoadListControl (IDC_FEE_SCALE_LIST);
         
      DString dstrSameDate;
      DString dstrProcessDate;
      
      getParent()->getField (this, BF::NullContainerId, FEEPARAMSYS::IS_THE_SAME_BUSINESS_DATE, dstrSameDate);
      getParent()->getField (this, IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST, ifds::ProcessDate, dstrProcessDate, false);

	   bool bShowButtons = dstrProcessDate.empty() || dstrSameDate == YES;

      ConnectListToData (IDC_FEE_TRESHOLD_LIST, false, true);
      ConnectListToData (IDC_FEE_SCALE_THR_LIST, false, true);
      

   }
   else if(bShowThreshold)
   {
      ConnectListToData (IDC_FEE_SCALE_LIST, false, true);

      ConnectListToData (IDC_FEE_TRESHOLD_LIST, true, true);
      ConnectListToData (IDC_FEE_SCALE_THR_LIST, true, true);
      LoadListControl (IDC_FEE_TRESHOLD_LIST);
      LoadListControl (IDC_FEE_SCALE_THR_LIST);

   }
   else
   {
      ConnectListToData (IDC_FEE_SCALE_LIST,       false, true);
      ConnectListToData (IDC_FEE_TRESHOLD_LIST,    false, true);
      ConnectListToData (IDC_FEE_SCALE_THR_LIST,   false, true);
   }
}

void FeeParamSysDlg::OnBtnDetails()
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OnBtnDetails" ) );

   try
   {
      E_COMMANDRETURN eRtn = CMD_CANCEL;
      CWaitCursor wait;  


      DString feeParamKey = getParent ()->getCurrentListItemKey (this, IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST);

      setParameter (MFCAN_IP_PARAM::LIST_KEY, feeParamKey);

      DString dstrFeeType;

		getParent()->getField(this,IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST, ifds::ParamFeeType, dstrFeeType,false);
      setParameter (MFCAN_IP_PARAM::FEE_TYPE, dstrFeeType);

      //setParameter ( FUNDCLASSLIST::MANAGEMENTFEE, dstrManagementFee);
      //setParameter ( FUNDCLASSLIST::MANAGEMENTFEE_REBATE, dstrManagementFeeRebate);
      

      eRtn = invokeCommand( getParent(), CMD_BPROC_FEE_PARAM_MAINT, PROC_SUPPORT, true, NULL );
      switch( eRtn )
      {
         case CMD_OK:
         case CMD_MODELESS_INPROCESS:
            {
               ConnectScaleControls();
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
}

void FeeParamSysDlg::OnBtnSearchAll() 
{
   TRACE_METHOD( CLASSNAME, I_( "OnBtnSearchAll" ) );
   // TODO: Add your control notification handler code here
   getParent()->setField( this, IFASTBP_PROC::FEE_PARAM_SEARCH, ifds::SearchAll, I_("Y"));
   getParent()->setField( this, IFASTBP_PROC::FEE_PARAM_SEARCH, ifds::AsofDate, I_("12319999"));
   LoadControl(IDC_DTP_SRC_EFFECTIVE);

}

void FeeParamSysDlg::OnBtnSearchEffDate() 
{
   TRACE_METHOD( CLASSNAME, I_( "OnBtnSearchEffDate" ) );
   // TODO: Add your control notification handler code here
   getParent()->setField( this, IFASTBP_PROC::FEE_PARAM_SEARCH, ifds::SearchAll, I_("N"));
	DString dstrCurBusDate;
   DSTCWorkSession *dstWorkSession = dynamic_cast<DSTCWorkSession *>(getParent()->getBFWorkSession());
	dstWorkSession->getMgmtCoOptions()->getField(ifds::CurrBusDate, dstrCurBusDate, BF::HOST);
   dstrCurBusDate.strip();
   getParent()->setField( this, IFASTBP_PROC::FEE_PARAM_SEARCH, ifds::AsofDate, dstrCurBusDate );
   LoadControl(IDC_DTP_SRC_EFFECTIVE);

}

void FeeParamSysDlg::OnBtnCopy() 
{
   TRACE_METHOD( CLASSNAME, I_( "OnBtnSearchEffDate" ) );
   // TODO: Add your control notification handler code here
   getParent()->send(this, I_("COPY_FEE_PARAM"));

   const DString *crtKey = &getParent()->getCurrentListItemKey (this,IFASTBP_PROC::FEE_PARAM_SYSTEM_LIST);
   LoadListControl(IDC_SYSTEM_FEE_LIST, crtKey);
}


bool FeeParamSysDlg::canCancel()
{
   BFWorkSession * worksession = getBFWorkSession();
   if(!worksession->getHadTrxnError() && !worksession->getIsEndSession())
   {
      FeeParamSysProcess* pFeeParamSysProcess = dynamic_cast<FeeParamSysProcess*>(getParent());
      if(pFeeParamSysProcess && pFeeParamSysProcess->hasTransactionUpdates())
      {
         DiscardMsgDlg discardDlg(NULL, TXT_DISCARD_MSGA, TXT_DISCARD_MSGB, TXT_DISCARD);

         return(discardDlg.DoModal() != IDCANCEL);         
      }
   }
   return(true);
}

bool FeeParamSysDlg::isKillWorkSessiononTxnError()
{
  return m_FeeModelCode == NULL_STRING;
};


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/FeeParamSysDlg.cpp-arc  $
// 
//    Rev 1.54   Dec 13 2011 08:53:38   popescu
// P0186477/FN03 - INA Commission Work
// 
//    Rev 1.53   Dec 01 2011 00:18:16   popescu
// INA - Commission Work
// 
//    Rev 1.52   Oct 07 2011 07:48:36   kitticha
// PETP0186479 FN01 - IA Base Commission.
// 
//    Rev 1.51   Aug 13 2009 11:14:46   jankovii
// PET0164824 FN01 - Eiger iShares Orders and ETF Fields 
// 
//    Rev 1.50   Jul 28 2009 07:29:02   dchatcha
// PET 157825 - FN 13 - Dilution Allocation Enhancements, Default NO_SORT for combo box type.
// 
//    Rev 1.49   Jul 24 2009 12:47:52   dchatcha
// PET 157825 - FN 13 - Dilution Allocation Enhancements, Sorting combo in grid.
// 
//    Rev 1.48   Sep 01 2006 11:32:14   jankovii
// PET 2236 FN02 - Grandfathering Units for Trailer Purposes.
// 
//    Rev 1.47   Nov 01 2005 09:17:40   AGUILAAM
// PET1243_FN00_ABN AMRO Trailer Fee Processing - additional enhancements
// 
//    Rev 1.46   Oct 25 2005 13:34:24   AGUILAAM
// PET1243_FN01_ABN AMRO Funds Trailer Fee Processing; additional enhancements (System Level Fee-Parms screen)
// 
//    Rev 1.45   Sep 15 2005 15:12:10   popescu
// Incident#403519 - added CLASSNAME as the fifth parameter to  BaseMainDlg constructor
// 
//    Rev 1.44   Jun 10 2005 16:08:44   Fengyong
// #incident 288919 - show >40 chars broker name.
// 
//    Rev 1.43   Apr 26 2005 13:38:26   Fengyong
// #Incident 288919 - Allow longger broker name fully visible.
// 
//    Rev 1.42   Sep 23 2004 09:50:30   YINGBAOL
// PET1117:FN05  fix  date issue
// 
//    Rev 1.41   Oct 27 2003 14:49:10   YINGBAOL
// PTS10021667 restricting number of characters for numeric fields, 
// 
//    Rev 1.40   Sep 16 2003 13:32:12   YINGBAOL
// somehow the code has not been checked in
// 
//    Rev 1.39   Sep 16 2003 13:30:30   YINGBAOL
// fix brokername issue
// 
//    Rev 1.38   Jul 21 2003 15:09:50   linmay
// PTS Ticket #10014935
// 
//    Rev 1.37   Jul 10 2003 22:21:38   popescu
// check in for payment instruct, used mfcan_ip_param for some interporcess param passing
// 
//    Rev 1.36   Jun 26 2003 13:30:02   linmay
// fix bug
// 
//    Rev 1.35   Jun 20 2003 16:35:58   linmay
// Sync with 1.31.1.2
// 
//    Rev 1.34   Jun 05 2003 14:50:48   linmay
// sync up with 1.31.1.0
// 
//    Rev 1.33   May 16 2003 18:27:26   YINGBAOL
// change SalesRep to SlsRep
// 
//    Rev 1.32   May 02 2003 15:09:08   linmay
// added logic for new search Option: BranchCode, SalesRepCode
// 
//    Rev 1.31   Mar 25 2003 09:14:38   linmay
// fix bug
// 
//    Rev 1.30   Mar 21 2003 21:30:50   PURDYECH
// Fixing sync up goofs
// 
//    Rev 1.29   Mar 21 2003 20:10:46   PURDYECH
// Sync 1.25.1.0 back to trunk
// 
//    Rev 1.28   Mar 21 2003 11:08:46   YINGBAOL
// change flag for ShGroup
// 
//    Rev 1.27   Mar 19 2003 17:14:08   linmay
// added BrokerName
//
//    Rev 1.25.1.0   Mar 21 2003 18:36:28   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.25   Mar 10 2003 15:17:08   linmay
// added logic for the new field branch...
// 
//    Rev 1.24   Mar 05 2003 11:29:48   PURDYECH
// Use IFastHistoricalInfo instead of deriving from IFastBaseMainDlg
// 
//    Rev 1.23   Feb 17 2003 10:41:46   YINGBAOL
// clean code
// 
//    Rev 1.22   Feb 05 2003 17:11:02   YINGBAOL
// always focus on current select item
// 
//    Rev 1.21   Feb 03 2003 16:37:20   YINGBAOL
// set default button
// 
//    Rev 1.20   Jan 31 2003 09:43:46   linmay
// move  isTheSameBusinessDate() to cbo layer
// 
//    Rev 1.19   Jan 31 2003 09:28:50   linmay
// added  EnableHistoryControl(long ContainerId);
// 
//    Rev 1.18   Jan 29 2003 16:52:10   YINGBAOL
// enable disbale historical button
// 
//    Rev 1.17   Jan 29 2003 16:22:28   popescu
// Added the historical button for FeeParamSysDlg and FeeParamDlg
// 
//    Rev 1.16   Jan 29 2003 15:41:58   linmay
// change BaseOn from text box to combo box
// 
//    Rev 1.15   Jan 27 2003 15:42:28   linmay
// added EnableScaleButtons()
// 
//    Rev 1.14   Jan 24 2003 16:29:10   linmay
// added openfundclassdlg for fund code and class code in search part
// 
//    Rev 1.12   Jan 22 2003 16:27:22   YINGBAOL
// promot error
// 
//    Rev 1.11   Jan 22 2003 13:59:12   linmay
// modified EnableControls()
// 
//    Rev 1.10   Jan 22 2003 12:14:20   linmay
// modified DispFeeTypeRelated()
// 
//    Rev 1.9   Jan 21 2003 16:08:40   linmay
// added FromFundNumber
// 
//    Rev 1.8   Jan 21 2003 11:21:10   YINGBAOL
// fix CommGroup issue
// 
//    Rev 1.7   Jan 20 2003 15:12:08   linmay
// added enablecontrols
// 
//    Rev 1.6   Jan 18 2003 17:30:34   YINGBAOL
// change getCellProperties and Search logic etc..
// 
//    Rev 1.5   Jan 17 2003 18:00:06   linmay
// modified addControls()
// 
//    Rev 1.4   Jan 15 2003 16:21:42   linmay
// added onBtnSearch(), EnableSearchCriteria()
// 
*/