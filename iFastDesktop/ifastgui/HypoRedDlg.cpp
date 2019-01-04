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
//    Copyright 2002 by DST Canada, Inc.
//
//******************************************************************************
//
// ^FILE   : HypoRedDlg.h
// ^AUTHOR : Robert Kovacs
// ^DATE   : 10/29/02
//
// ^CLASS    : HypoRedDlg
// ^SUBCLASS : HypoRedDlg
//
// ^CLASS DESCRIPTION : 
//
//******************************************************************************

#include "stdafx.h"

#ifndef IFASTGUI_H
   #include "mfdstc.h"
#endif

#ifndef HYPOREDDLG_H
   #include "HypoRedDlg.h"
#endif

#include <uibase\dsttabctrl.h>
#include <uibase\dstlistctrl.h>
#include <ifastcbo\dstcworksession.hpp>

#ifndef DSTCWORKSESSION_HPP
   #include <ifastcbo\DSTCWorkSession.hpp>
#endif

#include <ifastbp\HypoRedProcessIncludes.h>
#include <ifastbp\HypoRedProcess.hpp>
extern CLASS_IMPORT const I_CHAR* CMD_GUI_HYPO_RED;
#include <bfproc\concretedialogcreator.hpp>
static ConcreteDialogCreator< HypoRedDlg > dlgCreator( CMD_GUI_HYPO_RED );

#ifdef _DEBUG
   #define new DEBUG_NEW
   #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


namespace
{
   const I_CHAR * const YES               = I_( "Y" );
   const I_CHAR * const NO                = I_( "N" );
   const I_CHAR * const CLASSNAME         = I_( "HypoRedDlg" );
   const I_CHAR * const SUMMARY_DETAIL    = I_( "SummaryDetailTab" );
   const I_CHAR * const LV_HOLDINGS       = I_( "HoldingsList" );
   const I_CHAR * const LV_SUMMARY        = I_( "SummaryListCtrl" );
   const I_CHAR * const LV_DETAILS        = I_( "DetailsListCtrl" );
   const I_CHAR * const LV_TOTAL          = I_( "TotalListCtrl" );
   const I_CHAR * const LV_ERRORS         = I_( "ErrorsListCtrl" );
   const I_CHAR * const CRITERIA_SCREEN   = I_( "CriteriaScreen" );
   const I_CHAR * const HOLDINGS_SCREEN   = I_( "HoldingsScreen" );
   const I_CHAR * const RESULTS_SCREEN    = I_( "ResultsScreen" );
   const I_CHAR * const UNITS             = I_( "U" );

}

namespace CND
{  // Conditions used

}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId HypoRedHoldingsHeadingSet;
   extern CLASS_IMPORT const BFTextFieldId HypoRedSummaryAmountHeadingSet;
   extern CLASS_IMPORT const BFTextFieldId HypoRedSummaryUnitsHeadingSet;
   extern CLASS_IMPORT const BFTextFieldId HypoRedDetailAmountHeadingSet;
   extern CLASS_IMPORT const BFTextFieldId HypoRedDetailUnitsHeadingSet;
   extern CLASS_IMPORT const BFTextFieldId HypoRedTotalHeadingSet;
   extern CLASS_IMPORT const BFTextFieldId HypoRedErrorHeadingSet;
   extern CLASS_IMPORT const BFDecimalFieldId OverridePrcntFree;
   extern CLASS_IMPORT const BFTextFieldId HypoRedSummaryAmountHeadingSetWithLSIF;
   extern CLASS_IMPORT const BFTextFieldId HypoRedDetailAmountHeadingSetWithLSIF;
   extern CLASS_IMPORT const BFTextFieldId HypoRedSummaryUnitsHeadingSetWithLSIF;
   extern CLASS_IMPORT const BFTextFieldId HypoRedDetailUnitsHeadingSetWithLSIF;
   extern CLASS_IMPORT const BFTextFieldId HypoRedTotalHeadingSetWithLSIF;
   extern CLASS_IMPORT const BFTextFieldId isLSIF;
   extern CLASS_IMPORT const BFTextFieldId HypoRedSummaryAmountHeadingSetWithCB;
   extern CLASS_IMPORT const BFTextFieldId HypoRedDetailAmountHeadingSetWithCB;
   extern CLASS_IMPORT const BFTextFieldId HypoRedTotalHeadingSetWithCB;
}


namespace UAF
{
   extern CLASS_IMPORT I_CHAR * const HYPOTHETICAL_REDEMPTION;
}

//******************************************************************************

HypoRedDlg::HypoRedDlg( CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: BaseMainDlg( HypoRedDlg::IDD, pParent, pGIC, pGIParent, rCommand, CLASSNAME ), m_strScreenType(NULL_STRING), m_hAccel( 0 ), 
   _idHypoRedSummaryAmountHeadingSet (0), _idHypoRedDetailAmountHeadingSet (0), _idHypoRedSummaryUnitsHeadingSet (0),
   _idHypoRedDetailUnitsHeadingSet (0), _idHypoRedTotalHeadingSet (0)

  
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );

   CString strTemp;
   strTemp.LoadString(TXT_SUMMARY);
   m_strSummary = strTemp;
   strTemp.LoadString(TXT_DETAIL);
   m_strDetail = strTemp;
   //{{AFX_DATA_INIT(HypoRedDlg)
   // NOTE: the ClassWizard will add member initialization here
   //}}AFX_DATA_INIT
}

//******************************************************************************
HypoRedDlg::~HypoRedDlg()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}
//******************************************************************************

void HypoRedDlg::DoDataExchange(CDataExchange* pDX)
{
   BaseMainDlg::DoDataExchange( pDX );
   //{{AFX_DATA_MAP(HypoRedDlg)
   // NOTE: the ClassWizard will add DDX and DDV calls here
   //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(HypoRedDlg, BaseMainDlg)
//{{AFX_MSG_MAP(HypoRedDlg)
   ON_BN_CLICKED(ID_BTN_REFRESH, OnBtnRefresh)
   ON_BN_CLICKED(IDC_BTN_NEXT, OnBtnNext)
   ON_BN_CLICKED(IDC_BTN_CALCULATE, OnBtnCalculate)
   ON_BN_CLICKED(IDC_RADIO_AMOUNT, OnRadioAmount)
   ON_BN_CLICKED(IDC_RADIO_UNITS, OnRadioUnits)
   //}}AFX_MSG_MAP
   ON_COMMAND(ID_ACCEL_SUMMARY, OnAccelSummary)
   ON_COMMAND(ID_ACCEL_DETAIL,  OnAccelDetails)

END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// HypoRedDlg message handlers


//******************************************************************************
void HypoRedDlg::OnPostInitDialog()
{
   TRACE_METHOD( CLASSNAME, I_( "OnPostInitDialog" ) );
   CWaitCursor wait;
   SetUserAccesFunctionCode(UAF::HYPOTHETICAL_REDEMPTION);
   if( !m_hAccel )
      m_hAccel = LoadAccelerators( NULL, MAKEINTRESOURCE( IDR_ACCEL_HYPO_RED ) );
   addControls();
   doRefresh(this, HYPO_RED::TXT_ACCT_NUM_CHANGED);

}

//******************************************************************************
SEVERITY HypoRedDlg::doInit()
{
   SEVERITY sevRtn = NO_CONDITION;

   DString strIsLSIF;

  // if isLSIF then use *WithLSIF sets, else previous HypoRed headings 
  
   getParent()->getField(this, IFASTBP_PROC::CRITERIA, ifds::isLSIF, strIsLSIF, false);
   if (strIsLSIF == YES)
   {
      _idHypoRedSummaryAmountHeadingSet   = ifds::HypoRedSummaryAmountHeadingSetWithLSIF;
      _idHypoRedDetailAmountHeadingSet    = ifds::HypoRedDetailAmountHeadingSetWithLSIF;
      _idHypoRedSummaryUnitsHeadingSet    = ifds::HypoRedSummaryUnitsHeadingSetWithLSIF;
      _idHypoRedDetailUnitsHeadingSet     = ifds::HypoRedDetailUnitsHeadingSetWithLSIF;
      _idHypoRedTotalHeadingSet           = ifds::HypoRedTotalHeadingSetWithLSIF;
   }
   else
   {
      _idHypoRedSummaryAmountHeadingSet   = ifds::HypoRedSummaryAmountHeadingSet;
      _idHypoRedDetailAmountHeadingSet    = ifds::HypoRedDetailAmountHeadingSet;
      _idHypoRedSummaryUnitsHeadingSet    = ifds::HypoRedSummaryUnitsHeadingSet;
      _idHypoRedDetailUnitsHeadingSet     = ifds::HypoRedDetailUnitsHeadingSet;
      _idHypoRedTotalHeadingSet           = ifds::HypoRedTotalHeadingSet;
   }

   return(sevRtn);
}
//******************************************************************************
void HypoRedDlg::addControls( )
{
   TRACE_METHOD( CLASSNAME, I_( "addControls" ) );    

   //list controls
   AddListControl( CLASSNAME,IDC_LV_HOLDINGS, LV_HOLDINGS, ifds::HypoRedHoldingsHeadingSet,IFASTBP_PROC::HOLDINGS_LIST,
                   0,true, LISTFLAG_NOT_AUTO_ADD );
   AddListControl( CLASSNAME,IDC_LV_SUMMARY, LV_SUMMARY, _idHypoRedSummaryAmountHeadingSet,IFASTBP_PROC::SUMMARY_LIST,
                   0,true,LISTFLAG_NOT_AUTO_ADD );
   AddListControl( CLASSNAME,IDC_LV_DETAILS, LV_DETAILS, _idHypoRedDetailAmountHeadingSet,IFASTBP_PROC::DETAILS_LIST,
                   IDC_LV_SUMMARY,true,LISTFLAG_NOT_AUTO_ADD );
   AddListControl( CLASSNAME,IDC_LV_TOTAL, LV_TOTAL, _idHypoRedTotalHeadingSet,IFASTBP_PROC::TOTAL_LIST,
                   0,true,LISTFLAG_NOT_AUTO_ADD );
   AddListControl( CLASSNAME,IDC_LV_ERRORS, LV_ERRORS, ifds::HypoRedErrorHeadingSet,IFASTBP_PROC::ERRORS_LIST,
                   0,true,LISTFLAG_NOT_AUTO_ADD );

   //controls
   AddControl( CTRL_DATE,  IDC_DTP_TRADE_DATE, IFASTBP_PROC::CRITERIA,      ifds::TradeDate, 
      CTRLFLAG_AUTO_UPDATE_ON_CHANGE );    
   AddControl( CTRL_COMBO, IDC_CMB_FULLRED,    IFASTBP_PROC::CRITERIA,      ifds::FullRed   ,
      CTRLFLAG_AUTO_UPDATE_ON_CHANGE | CTRLFLAG_INITCOMBO_BY_SUB_LIST );    
   AddControl( CTRL_COMBO, IDC_CMB_REDCODE,    IFASTBP_PROC::CRITERIA,      ifds::RedCode   , 
      CTRLFLAG_AUTO_UPDATE_ON_CHANGE | CTRLFLAG_INITCOMBO_BY_SUB_LIST );    
   AddControl( CTRL_COMBO, IDC_CMB_GROSS,      IFASTBP_PROC::CRITERIA,      ifds::GrossOrNet, 
      CTRLFLAG_AUTO_UPDATE_ON_CHANGE | CTRLFLAG_INITCOMBO_BY_SUB_LIST );    
   AddControl( CTRL_COMBO, IDC_CMB_AMT_TYPE,   IFASTBP_PROC::CRITERIA,      ifds::AmtType   , 
      CTRLFLAG_AUTO_UPDATE_ON_CHANGE | CTRLFLAG_INITCOMBO_BY_SUB_LIST );    
   AddControl( CTRL_COMBO, IDC_CMB_FREE,       IFASTBP_PROC::CRITERIA,      ifds::AcctLvlDSC, 
      CTRLFLAG_AUTO_UPDATE_ON_CHANGE | CTRLFLAG_INITCOMBO_BY_SUB_LIST );    
   AddControl( CTRL_EDIT,  IDC_EDT_AMOUNT,     IFASTBP_PROC::HOLDINGS_LIST, ifds::Amount,      
      CTRLFLAG_AUTO_UPDATE_ON_CHANGE, IDC_LV_HOLDINGS );

   //tab control
   DSTTabCtrl* pTabCtrl = AddTabControl(CLASSNAME, IDC_TAB_HYPO_RED, SUMMARY_DETAIL);
   if (pTabCtrl)
   {
      positionTabToControl(IDC_TAB_HYPO_RED, IDC_LV_SUMMARY);
      pTabCtrl->AddTab(m_strSummary);
      pTabCtrl->AddTab(m_strDetail);
      pTabCtrl->registerListControl(IDC_LV_SUMMARY, m_strSummary);
      pTabCtrl->registerListControl(IDC_LV_DETAILS, m_strDetail);
   }

   addControlGroupIDForPermissionCheck(0);
   addControlGroupIDForPermissionCheck(IDC_LV_HOLDINGS);

   //rule : Only show DSC override control if OverridePrcntFree generic control type is 1
   DString strOverridePercentFree;
   int nShowDSCFree = SW_HIDE;
   dynamic_cast<DSTCWorkSession *>(getBFWorkSession())->getOption ( ifds::OverridePrcntFree,
      strOverridePercentFree, BF::HOST, false);
   if (strOverridePercentFree.strip() == I_("1"))
      nShowDSCFree = SW_SHOW;
   GetDlgItem(IDC_TXT_DSC_FREE)->ShowWindow(nShowDSCFree);
   GetDlgItem(IDC_CMB_FREE)->ShowWindow(nShowDSCFree);

}
//******************************************************************************

void HypoRedDlg::SetDlgCaption()
{
   TRACE_METHOD( CLASSNAME, I_( "SetDlgCaption" ) );

   DString strShrNum, strAccountNum, dstrEntityName;
   CString strName;
   getParent()->getField(this, IFASTBP_PROC::MFACCOUNT, ifds::ShrNum, strShrNum, false);
   getParent()->getField(this, IFASTBP_PROC::MFACCOUNT, ifds::AccountNum, strAccountNum, false);

   dynamic_cast<DSTCWorkSession *>(getBFWorkSession())->
      getFirstSequenced01AccountholderEntityName(getDataGroupId(),
      strAccountNum,dstrEntityName);

   SetShrAcctCaption(strShrNum, strAccountNum, dstrEntityName);
}

//******************************************************************************

bool HypoRedDlg::doRefresh( GenericInterface * rpGICaller, 
                             const I_CHAR * szOriginalCommand )
{
   TRACE_METHOD( CLASSNAME, I_( "doRefresh" ) );

   DString szCommand(szOriginalCommand);
   if (szCommand == HYPO_RED::TXT_ACCT_NUM_CHANGED)
   {
      SetDlgCaption();
      showCriteria();
   }
   else
   {
      if (getCurrentScreenType() == HOLDINGS_SCREEN)
         showHoldings();
      else if (getCurrentScreenType() == RESULTS_SCREEN)
         showResults();
      else
         showCriteria();
   }


   return(true);
}

//******************************************************************************
void HypoRedDlg::OnBtnRefresh() 
{
   TRACE_METHOD( CLASSNAME, I_( "OnBtnRefresh" ) );

   GetDlgItem(ID_BTN_REFRESH)->SetFocus();
   CWaitCursor wait;

   getParent()->reset(this, IFASTBP_PROC::CRITERIA);
   ReregisterObservers();
   showCriteria();
   CheckPermission();
}

//******************************************************************************
void HypoRedDlg::OnBtnNext() 
{
   TRACE_METHOD( CLASSNAME, I_( "OnBtnNext" ) );

   GetDlgItem(IDC_BTN_NEXT)->SetFocus();

   DString strValidCriteria;
   getParent()->getField(this, ifds::ValidHypoCriteria, strValidCriteria, false);
   if (strValidCriteria == NO)
   {
      CString strValidCriteria;
      strValidCriteria.LoadString(TXT_VALID_CRITERIA);
      AfxMessageBox(strValidCriteria, MB_OK | MB_ICONSTOP);
      GetDlgItem(IDC_DTP_TRADE_DATE)->SetFocus();
      return;
   }

   CWaitCursor wait;

   showHoldings();
   DSTListCtrl *pHoldingList = GetList(IDC_LV_HOLDINGS);
   if (!pHoldingList->GetItemCount())
   {
      //show error empty list
      CString strError;
      strError.LoadString(TXT_NO_FUND_HOLDINGS);
      AfxMessageBox(strError, MB_OK | MB_ICONSTOP);
      OnBtnRefresh();
      return;
   }

}

//******************************************************************************
void HypoRedDlg::OnBtnCalculate() 
{
   TRACE_METHOD( CLASSNAME, I_( "OnBtnCalculate" ) );

   GetDlgItem(IDC_BTN_CALCULATE)->SetFocus();
   CWaitCursor wait;
   SetMessageStatusBar( IDS_TXT_PROC_RED );

   DSTListCtrl *pHoldingList = GetList(IDC_LV_HOLDINGS);
   if (pHoldingList->GetMaxErrorState() > WARNING)
   {
      //show error wrong amount
      SetMessageStatusBar( NULL_STRING );
      CString strError;
      strError.LoadString(TXT_WRONG_AMOUNT);
      AfxMessageBox(strError, MB_OK | MB_ICONSTOP);
      GetList(IDC_LV_HOLDINGS)->SetFocus();
      return;
   }

   DString strValidHoldings;
   getParent()->getField(this, ifds::ValidHypoRed, strValidHoldings, false);
   if (strValidHoldings == YES)
      showResults();
   else
   {
      SetMessageStatusBar( NULL_STRING );
      CString strAtLeastOneAmount;
      strAtLeastOneAmount.LoadString(TXT_AT_LEAST_ONE_AMOUNT);
      AfxMessageBox(strAtLeastOneAmount, MB_OK | MB_ICONSTOP);
      GetList(IDC_LV_HOLDINGS)->SetFocus();
   }
   SetMessageStatusBar( NULL_STRING );
}

//******************************************************************************
void HypoRedDlg::OnRadioAmount() 
{
   TRACE_METHOD( CLASSNAME, I_( "OnRadioAmount" ) );

   ReInitListControl(IDC_LV_SUMMARY, _idHypoRedSummaryAmountHeadingSet, IFASTBP_PROC::SUMMARY_LIST, LV_SUMMARY);
   ReInitListControl(IDC_LV_DETAILS, _idHypoRedDetailAmountHeadingSet, IFASTBP_PROC::DETAILS_LIST, LV_DETAILS);
   LoadListControl(IDC_LV_SUMMARY);
   LoadListControl(IDC_LV_DETAILS);
}

//******************************************************************************
void HypoRedDlg::OnRadioUnits() 
{
   TRACE_METHOD( CLASSNAME, I_( "OnRadioUnits" ) );

   ReInitListControl(IDC_LV_SUMMARY, _idHypoRedSummaryUnitsHeadingSet, IFASTBP_PROC::SUMMARY_LIST, LV_SUMMARY);
   ReInitListControl(IDC_LV_DETAILS, _idHypoRedDetailUnitsHeadingSet, IFASTBP_PROC::DETAILS_LIST, LV_DETAILS);
   LoadListControl(IDC_LV_SUMMARY);
   LoadListControl(IDC_LV_DETAILS);
}

//******************************************************************************
void HypoRedDlg::showCriteria()
{
   TRACE_METHOD( CLASSNAME, I_( "showCriteria" ) );

   //tab control
   ShowTabCtrl(IDC_TAB_HYPO_RED, false);

   //list controls
   GetList(IDC_LV_HOLDINGS)->ShowWindow(false);
   GetList(IDC_LV_SUMMARY)->ShowWindow(false);
   GetList(IDC_LV_DETAILS)->ShowWindow(false);
   GetList(IDC_LV_TOTAL)->ShowWindow(false);
   GetList(IDC_LV_ERRORS)->ShowWindow(false);

   //radio buttons
   GetDlgItem(IDC_RADIO_AMOUNT)->ShowWindow(SW_HIDE);
   GetDlgItem(IDC_RADIO_UNITS)->ShowWindow(SW_HIDE);

   //static controls, frames (group boxes)
   GetDlgItem(IDC_STATIC_AMT_TYPE)->ShowWindow(SW_HIDE);
   GetDlgItem(IDC_STATIC_AMOUNT)->ShowWindow(SW_HIDE);
   GetDlgItem(IDC_GRAND_TOTAL)->ShowWindow(SW_HIDE);
   GetDlgItem(IDC_ERRORS)->ShowWindow(SW_HIDE);

   //edit controls
   GetControl(IDC_EDT_AMOUNT)->Show(false);

   ConnectControlsToData();
   ConnectListToData( IDC_LV_HOLDINGS, false ); 
   ConnectListToData( IDC_LV_SUMMARY,  false ); 
   ConnectListToData( IDC_LV_DETAILS,  false ); 
   ConnectListToData( IDC_LV_TOTAL,    false ); 
   ConnectListToData( IDC_LV_ERRORS,   false ); 

   LoadControls();

   //buttons
   GetDlgItem(IDC_BTN_NEXT)->EnableWindow(true);
   GetDlgItem(IDC_BTN_CALCULATE)->EnableWindow(false);

   m_strScreenType = CRITERIA_SCREEN;
   GetDlgItem(IDC_DTP_TRADE_DATE)->SetFocus();

   CheckPermission();
}

//******************************************************************************
void HypoRedDlg::showHoldings()
{
   TRACE_METHOD( CLASSNAME, I_( "showHoldings" ) );

   //tab control
   ShowTabCtrl(IDC_TAB_HYPO_RED, false);

   //list controls
   GetList(IDC_LV_HOLDINGS)->ShowWindow(SW_SHOW);
   GetList(IDC_LV_SUMMARY)->ShowWindow(SW_HIDE);
   GetList(IDC_LV_DETAILS)->ShowWindow(SW_HIDE);
   GetList(IDC_LV_TOTAL)->ShowWindow(SW_HIDE);
   GetList(IDC_LV_ERRORS)->ShowWindow(SW_HIDE);

   //radio buttons
   GetDlgItem(IDC_RADIO_AMOUNT)->ShowWindow(SW_HIDE);
   GetDlgItem(IDC_RADIO_UNITS)->ShowWindow(SW_HIDE);

   //static controls, frames (group boxes)
   GetDlgItem(IDC_STATIC_AMT_TYPE)->ShowWindow(SW_HIDE);
   GetDlgItem(IDC_STATIC_AMOUNT)->ShowWindow(SW_SHOW);
   GetDlgItem(IDC_GRAND_TOTAL)->ShowWindow(SW_HIDE);
   GetDlgItem(IDC_ERRORS)->ShowWindow(SW_HIDE);

   //edit controls
   GetControl(IDC_EDT_AMOUNT)->Show(true);

   ConnectControlsToData();
   ConnectListToData( IDC_LV_HOLDINGS, true ); 
   ConnectListToData( IDC_LV_SUMMARY,  false ); 
   ConnectListToData( IDC_LV_DETAILS,  false ); 
   ConnectListToData( IDC_LV_TOTAL,    false ); 
   ConnectListToData( IDC_LV_ERRORS,   false ); 

   LoadControls();
   LoadListControl(IDC_LV_HOLDINGS);

   //buttons
   GetDlgItem(IDC_BTN_NEXT)->EnableWindow(false);

   //enable Calculate button only if there is at least one holding in the list
   GetDlgItem(IDC_BTN_CALCULATE)->EnableWindow(GetList(IDC_LV_HOLDINGS)->GetItemCount());

   m_strScreenType = HOLDINGS_SCREEN;
   GetList(IDC_LV_HOLDINGS)->SetFocus();

   CheckPermission();
}

//******************************************************************************
void HypoRedDlg::showResults()
{
   TRACE_METHOD( CLASSNAME, I_( "showResults" ) );

   //tab control
   ShowTabCtrl(IDC_TAB_HYPO_RED, true);

   showChargebackCommission();

   //list controls (summary and details are registered with the tab control, so the tab control will
   //enable / disable them
   GetList(IDC_LV_HOLDINGS)->ShowWindow(SW_SHOW);
   GetList(IDC_LV_TOTAL)->ShowWindow(SW_SHOW);
   GetList(IDC_LV_ERRORS)->ShowWindow(SW_SHOW);

   //radio buttons
   GetDlgItem(IDC_RADIO_AMOUNT)->ShowWindow(SW_SHOW);
   GetDlgItem(IDC_RADIO_UNITS)->ShowWindow(SW_SHOW);
   checkRB();

   //buttons
   GetDlgItem(IDC_BTN_NEXT)->EnableWindow(false);
   GetDlgItem(IDC_BTN_CALCULATE)->EnableWindow(false);

   //static controls, frames (group boxes)
   GetDlgItem(IDC_STATIC_AMT_TYPE)->ShowWindow(SW_SHOW);
   GetDlgItem(IDC_STATIC_AMOUNT)->ShowWindow(SW_HIDE);
   GetDlgItem(IDC_GRAND_TOTAL)->ShowWindow(SW_SHOW);
   GetDlgItem(IDC_ERRORS)->ShowWindow(SW_SHOW);

   //edit controls
   GetControl(IDC_EDT_AMOUNT)->Show(false);

   ConnectControlsToData();
   ConnectListToData( IDC_LV_HOLDINGS, true ); 

   //only connect summary list if it is not empty
   int nItems = getParent()->getNumberOfItemsInList(this, IFASTBP_PROC::SUMMARY_LIST);
   ConnectListToData( IDC_LV_SUMMARY, nItems != 0 );

   ConnectListToData( IDC_LV_TOTAL,   true ); 
   ConnectListToData( IDC_LV_ERRORS,  true ); 

   LoadControls();
   LoadListControl(IDC_LV_HOLDINGS);
   LoadTabControl(IDC_TAB_HYPO_RED, m_strSummary);
   LoadListControl(IDC_LV_SUMMARY);
   LoadListControl(IDC_LV_TOTAL);
   LoadListControl(IDC_LV_ERRORS);

   m_strScreenType = RESULTS_SCREEN;
   GetList(IDC_LV_SUMMARY)->SetFocus();

   CheckPermission();
}

//******************************************************************************
void HypoRedDlg::OnAccelSummary() 
{
	if (getCurrentScreenType() != RESULTS_SCREEN)
		return;

   LoadTabControl( IDC_TAB_HYPO_RED, m_strSummary );
   int nItems = getParent()->getNumberOfItemsInList(this, IFASTBP_PROC::SUMMARY_LIST);
   ConnectListToData( IDC_LV_SUMMARY, nItems != 0 );
   LoadListControl(IDC_LV_SUMMARY);
}

//******************************************************************************
void HypoRedDlg::OnAccelDetails() 
{
	if (getCurrentScreenType() != RESULTS_SCREEN)
		return;

   LoadTabControl( IDC_TAB_HYPO_RED, m_strDetail );
   int nItems = getParent()->getNumberOfItemsInList(this, IFASTBP_PROC::DETAILS_LIST);
   ConnectListToData( IDC_LV_DETAILS, nItems != 0 );
   LoadListControl(IDC_LV_DETAILS);
}

//******************************************************************************
BOOL HypoRedDlg::PreTranslateMessage(MSG* pMsg) 
{
   BOOL isTranslated = FALSE;

   // make sure that certain accelerator keys are processed correctly
   if( m_hAccel != NULL )
   {
      isTranslated = ::TranslateAccelerator( m_hWnd, m_hAccel, pMsg );
   }

   if( !isTranslated )
   {
      // pass message down the chain
      isTranslated = BaseMainDlg::PreTranslateMessage( pMsg );
   }

   return(isTranslated);
}
//******************************************************************************

void HypoRedDlg::ControlUpdated( UINT controlID, const DString &strValue )
{
	TRACE_METHOD( CLASSNAME, I_( "ControlUpdated" ) );

	switch( controlID )
   {
      case IDC_EDT_AMOUNT:
         {
				DSTListCtrl *pList = GetList(IDC_LV_HOLDINGS);
				POSITION pos = pList->GetFirstSelectedItemPosition();
				int nSelectedItem = pList->GetNextSelectedItem(pos);
				if (nSelectedItem >= 0)
					GetList(IDC_LV_HOLDINGS)->RefreshCurrentItem(false);
         }
         break;

		default:
         break;
   }
}

//******************************************************************************
bool HypoRedDlg::doDisableControl(UINT nID, bool bIsNew)
{
	TRACE_METHOD( CLASSNAME, I_( "doDisableControl" ) );

	//rules :
	//when showing criteria screen all the criteria fields are updateable
	//when showing holdings screen the Amount edit is updateable, all other controls are read-only
	//when showing results, all the controls are read-only
	if( nID == IDC_DTP_TRADE_DATE || nID == IDC_CMB_FULLRED || nID == IDC_CMB_GROSS ||
		nID == IDC_CMB_AMT_TYPE || nID == IDC_CMB_REDCODE || nID == IDC_CMB_FREE)
   {
      return (getCurrentScreenType() != CRITERIA_SCREEN);
   }
	else if (nID == IDC_DTP_TRADE_DATE)
      return (getCurrentScreenType() != HOLDINGS_SCREEN);


   return(false);
}

//******************************************************************************
void HypoRedDlg::tabSelectionChanged(UINT tabControlID, const DString& strPageName)
{
	TRACE_METHOD( CLASSNAME, I_( "tabSelectionChanged" ) );

   if (tabControlID != IDC_TAB_HYPO_RED)
      return;
   if (strPageName == m_strSummary)
   {
      int nItems = getParent()->getNumberOfItemsInList(this, IFASTBP_PROC::SUMMARY_LIST);
      ConnectListToData( IDC_LV_SUMMARY, nItems != 0);
      LoadListControl(IDC_LV_SUMMARY);
   }
   else if (strPageName == m_strDetail)
   {
      int nItems = getParent()->getNumberOfItemsInList(this, IFASTBP_PROC::DETAILS_LIST);
      ConnectListToData( IDC_LV_DETAILS, nItems != 0 );
      LoadListControl(IDC_LV_DETAILS);
   }
   else assert(0);
}

//******************************************************************************
void HypoRedDlg::checkRB()
{
   //rule : Amount or Units RB should default to the AmountType in Criteria
   DString strAmtType;
   getParent()->getField(this, IFASTBP_PROC::CRITERIA, ifds::AmtType, strAmtType, false);
   bool bCheckUnits = strAmtType == UNITS;
	CButton* pRB = (CButton*) GetDlgItem(IDC_RADIO_AMOUNT);
	if (pRB)
		pRB->SetCheck(!bCheckUnits);
	pRB = (CButton*) GetDlgItem(IDC_RADIO_UNITS);
	if (pRB)
		pRB->SetCheck(bCheckUnits);
   if (bCheckUnits)
      OnRadioUnits();
   else
      OnRadioAmount();
}

//******************************************************************************
void HypoRedDlg::showChargebackCommission()
{
   DString strIsLSIF;
   getParent()->getField(this, IFASTBP_PROC::CRITERIA, ifds::isLSIF, strIsLSIF, false);

   if (strIsLSIF == NO)
   {
      //bool bHasChargeBackFund = false;
      //HypoRedProcess* pHypoRedProcess = dynamic_cast<HypoRedProcess*>(getParent());
      //if(pHypoRedProcess)
      {
         //bHasChargeBackFund = pHypoRedProcess->hasChargeBackFund();
         //if (bHasChargeBackFund)
         {
            _idHypoRedSummaryAmountHeadingSet = ifds::HypoRedSummaryAmountHeadingSetWithCB;
            _idHypoRedDetailAmountHeadingSet  = ifds::HypoRedDetailAmountHeadingSetWithCB;
            _idHypoRedTotalHeadingSet         = ifds::HypoRedTotalHeadingSetWithCB;
         }
         //else
         //{
         //   _idHypoRedSummaryAmountHeadingSet = ifds::HypoRedSummaryAmountHeadingSet;
         //   _idHypoRedDetailAmountHeadingSet  = ifds::HypoRedDetailAmountHeadingSet;
         //   _idHypoRedTotalHeadingSet		  = ifds::HypoRedTotalHeadingSet;
         //}

         ReInitListControl(IDC_LV_SUMMARY, _idHypoRedSummaryAmountHeadingSet, IFASTBP_PROC::SUMMARY_LIST, LV_SUMMARY);
         ReInitListControl(IDC_LV_DETAILS, _idHypoRedDetailAmountHeadingSet, IFASTBP_PROC::DETAILS_LIST, LV_DETAILS);
         ReInitListControl(IDC_LV_TOTAL, _idHypoRedTotalHeadingSet, IFASTBP_PROC::TOTAL_LIST, LV_TOTAL);
      }
   }
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/HypoRedDlg.cpp-arc  $
// 
//    Rev 1.4   Sep 15 2005 15:13:24   popescu
// Incident#403519 - added CLASSNAME as the fifth parameter to  BaseMainDlg constructor
// 
//    Rev 1.3   May 10 2004 13:46:24   AGUILAAM
// PET985_FN01-1: LSIF HypoCalc enhancement - added clawback fields
// 
//    Rev 1.2   Mar 21 2003 18:37:44   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.1   Nov 25 2002 09:43:26   KOVACSRO
// Added implementation.
// 
//    Rev 1.0   Oct 29 2002 10:55:14   KOVACSRO
// Initial Revision
// 
*/