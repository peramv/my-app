// HistoricalMarketValueDlg.cpp : implementation file
//

//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by International Financial Data Services Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 1999 by International Financial Data Services Inc.
//
//******************************************************************************
//
// ^FILE   : HistoricalMarketValueDlg.cpp
// ^AUTHOR : Yakov Prager
// ^DATE   : 04/29/99
//
// ----------------------------------------------------------
//
// ^CLASS    : HistoricalMarketValueDlg
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :  This is the code for the HistoricalMarketValueDlg dialog
//
//******************************************************************************

#include "stdafx.h"

#ifndef IFASTGUI_H
   #include "mfdstc.h"
#endif

#ifndef CONFIGMANAGER_HPP
   #include <ConfigManager.hpp>
#endif

#ifndef DSTCOMMONFUNCTION_HPP
   #include <ifastcbo\DSTCommonFunction.hpp>
#endif

#ifndef DSTCWORKSESSION_HPP
   #include <ifastcbo\DSTCWorkSession.hpp>
#endif

#ifndef DSTOLEDATETIME_H
   #include <uibase\DSTOleDateTime.h>
#endif

#ifndef HISTORICALMARKETVALUEDLG_H
   #include "HistoricalMarketValueDlg.h"
#endif

#ifndef HISTORICALMARKETVALUEPROCESSINCLUDES_H
   #include <ifastbp\HistoricalMarketValueProcessIncludes.h>
#endif

#ifndef LISTCTRL_H
   #include <uibase\listctrl.h>
#endif

#include <ifastbp\foreigncontentworksheetprocessincludes.h>

#ifndef INCLUDED_ASSERT_H
#define INCLUDED_ASSERT_H
#include <assert.h>
#endif

extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_FOREIGN_CONTENT_WORKSHEET;
extern CLASS_IMPORT const I_CHAR* CMD_GUI_HISTORICAL_MARKET_VALUE;
extern CLASS_IMPORT const I_CHAR *CMD_BPROC_SHARE_LOT_BROWSER;
extern CLASS_IMPORT const I_CHAR *CMD_BPROC_INVEST_INFO;

#include <bfproc\concretedialogcreator.hpp>
static ConcreteDialogCreator< HistoricalMarketValueDlg > dlgCreator(CMD_GUI_HISTORICAL_MARKET_VALUE);

#ifdef _DEBUG
   #define new DEBUG_NEW
   #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

namespace
{
   const I_CHAR * const CLASSNAME = I_("HistoricalMarketValueDlg");
   const I_CHAR * const ONBTNSEARCH = I_("OnBtnSearch");
   const I_CHAR * const SEARCH = I_("search");
   const I_CHAR * const ADJUSTSELECTION = I_("adjustSelection");
   const I_CHAR * const AS_OF_DATE = I_("AsofDate");
   const I_CHAR * const FUND_CODE = I_("FundCode");
   const I_CHAR * const CLASS_CODE = I_("ClassCode");

   const I_CHAR * const LV_FUNDS = I_("LvFunds");

   const I_CHAR * const FULL_REFRESH = I_("FullRefresh");
   const I_CHAR * const PARTIAL_REFRESH = I_("PartialRefresh");

   //const I_CHAR * const JAVA_DATE_FORMAT = I_("MM/dd/yyyy");
   //const I_CHAR * const DATE_FORMAT = I_("MM'/'dd'/'yyy");
   const I_CHAR * const CTIME_FORMAT = I_("%d/%m/%Y");
   const I_CHAR * const Y = I_("Y");
   const I_CHAR * const N = I_("N");
   const I_CHAR * const PERCENT = I_("%");
}

namespace ifds
{   
   extern CLASS_IMPORT const BFTextFieldId ForeignContent;  
   extern CLASS_IMPORT const BFTextFieldId IWTEnable;
   extern CLASS_IMPORT const BFDateFieldId CurrBusDate;
}

namespace CND
{  // Conditions used
   extern const long GUI_ERR_UNKNOWN_EXCEPTION;
}

namespace UAF
{
   extern CLASS_IMPORT I_CHAR * const FOREIGN_CONTENT;
}
/////////////////////////////////////////////////////////////////////////////
// HistoricalMarketValueDlg dialog

/*******************************************************************************************/

HistoricalMarketValueDlg::HistoricalMarketValueDlg( CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: BaseMainDlg( HistoricalMarketValueDlg::IDD, pParent, pGIC, pGIParent, rCommand, CLASSNAME )
{
   TRACE_CONSTRUCTOR(CLASSNAME, NULL_STRING);

   //{{AFX_DATA_INIT(HistoricalMarketValueDlg)
   m_strFrgnACB = _T("");
   //}}AFX_DATA_INIT
}


/*******************************************************************************************/

HistoricalMarketValueDlg::~HistoricalMarketValueDlg()
{
   TRACE_DESTRUCTOR(CLASSNAME);
}


/*******************************************************************************************/

void HistoricalMarketValueDlg::DoDataExchange(CDataExchange* pDX)
{
   BaseMainDlg::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(HistoricalMarketValueDlg)
   DDX_Control(pDX, IDC_DTP_DATE, m_dtpDate);
   DDX_Control(pDX, IDC_LV_FUNDS, m_lvFunds);
   DDX_Text(pDX, IDC_EDT_FOREIGNACB_VALUE, m_strFrgnACB);
   //}}AFX_DATA_MAP
}


/*******************************************************************************************/
BEGIN_MESSAGE_MAP(HistoricalMarketValueDlg, BaseMainDlg)
//{{AFX_MSG_MAP(HistoricalMarketValueDlg)
ON_BN_CLICKED(IDC_BTN_SEARCH, OnBtnSearch)
ON_NOTIFY(LVN_ITEMCHANGED, IDC_LV_FUNDS, OnItemchangedLvFunds)
ON_BN_CLICKED(IDC_RD_UNSETTLE_TRADE_INC, OnRdUnsettleTradeInc)
ON_BN_CLICKED(ID_BTN_FC_WORKSHEET, OnBtnFCWorksheet)
ON_BN_CLICKED(IDC_BTN_HMV_SHARELOTS, OnBtnShareLots)
ON_BN_CLICKED(IDC_BTN_INVEST_INFO, OnBtnInvestInfo)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// HistoricalMarketValueDlg message handlers

BOOL HistoricalMarketValueDlg::OnInitDialog() 
{
   TRACE_METHOD(CLASSNAME, ONINITDIALOG);
   DString strMarket = DSTCommonFunctions::getMarket();

   BaseMainDlg::OnInitDialog();

   DString dstrShrNum;
   getParent()->getField(this,ifds::ShrNum,dstrShrNum);
   dstrShrNum.stripLeading().stripLeading(I_CHAR('0')).stripTrailing();

   DString strAccountNum;
   getParent()->getField(this, ifds::AccountNum, strAccountNum);
   strAccountNum.stripLeading().stripLeading(I_CHAR('0')).stripTrailing();
   SetAccount(strAccountNum);

   DString dstrEntityName;
   dynamic_cast<DSTCWorkSession *>(getBFWorkSession())->getFirstSequenced01AccountholderEntityName(getDataGroupId(), 
                                                                                                    strAccountNum, 
                                                                                                    dstrEntityName);

   SetShrAcctCaption(dstrShrNum, strAccountNum, dstrEntityName);
   DisplayListTitle();
/*
   PriceDateORforeign();
  */
   UpdateData(false);

   //m_dtpDate.ShowWindow(SW_HIDE);

	GenericInterface* Parent = getParent();
	DString dstrForeignContent( NULL_STRING );
	DSTCWorkSession *dstWorkSession = dynamic_cast<DSTCWorkSession *>(getParent()->getBFWorkSession());
 
   dstWorkSession->getOption( ifds::ForeignContent, dstrForeignContent, getParent()->getDataGroupId(), false ); 
	bool bAccessForeignCont = dstrForeignContent.strip().upperCase() == Y && hasReadPermission( UAF::FOREIGN_CONTENT );

   GetDlgItem( ID_BTN_FC_WORKSHEET )->EnableWindow( bAccessForeignCont );  

   return(TRUE);  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}

//*****************************************************************************************
void HistoricalMarketValueDlg::DisplayListTitle()
{

   CString lvColumn;
   int i = 0;
   DString strMarket = DSTCommonFunctions::getMarket();

   lvColumn.LoadString(COL_HISTORICAL_MARKET_VALUE_FUND);
   m_lvFunds.InsertColumn(i, (LPCTSTR) lvColumn, LVCFMT_LEFT, 70);
   i++;
   lvColumn.LoadString(COL_HISTORICAL_MARKET_VALUE_CLASS);
   m_lvFunds.InsertColumn(i, (LPCTSTR) lvColumn, LVCFMT_LEFT, 50);
   i++;
   if(strMarket == MARKET_IDS::CANADA || strMarket == MARKET_IDS::LUXEMBOURG)
   {
      lvColumn.LoadString(COL_CHEQUE_FUNDNUMBER);
      m_lvFunds.InsertColumn(i, (LPCTSTR) lvColumn, LVCFMT_LEFT, 50);
      i++;
   }

   lvColumn.LoadString(IDS_TYPE);
   m_lvFunds.InsertColumn(i, (LPCTSTR) lvColumn, LVCFMT_LEFT, 30);
   i++;
   lvColumn.LoadString(IDS_NUMBER_UNSETTLE_UNITS);
   m_lvFunds.InsertColumn(i, (LPCTSTR) lvColumn, LVCFMT_LEFT, 50);
   i++;
   lvColumn.LoadString(IDS_NUMBER_SETTLE_UNITS);
   m_lvFunds.InsertColumn(i, (LPCTSTR) lvColumn, LVCFMT_LEFT, 50);
   i++;
   lvColumn.LoadString(IDS_ADJUST_COST_BASE);
   m_lvFunds.InsertColumn(i, (LPCTSTR) lvColumn, LVCFMT_LEFT, 50);
   i++;
   lvColumn.LoadString(COL_ALLOCATIONS_PERCENT); //just borrow a string from allocation screen
   m_lvFunds.InsertColumn(i, (LPCTSTR) lvColumn, LVCFMT_LEFT, 50);
   i++;
   lvColumn.LoadString(IDS_CURRENT_MARKET_VALUE); 
   m_lvFunds.InsertColumn(i, (LPCTSTR) lvColumn, LVCFMT_LEFT, 50);
   i++;
   lvColumn.LoadString(COL_ALLOCATIONS_PERCENT); 
   m_lvFunds.InsertColumn(i, (LPCTSTR) lvColumn, LVCFMT_LEFT, 50);
   i++;
   m_lvFunds.LoadSettings(CLASSNAME, LV_FUNDS);
}

//*******************************************************************************************
void HistoricalMarketValueDlg::OnPostInitDialog()
{
   TRACE_METHOD(CLASSNAME, ONPOSTINITDIALOG);

   DString strDate;
   DSTCWorkSession* pDSTCWorkSession = dynamic_cast<DSTCWorkSession *>(getParent()->getBFWorkSession());
   pDSTCWorkSession->getOption (ifds::CurrBusDate, strDate, getParent()->getDataGroupId(), false);
   
   int tmpDay, tmpMonth, tmpYear;

   tmpDay = DSTCommonFunctions::getDayFromUnFormattedDate(strDate);
   tmpMonth = DSTCommonFunctions::getMonthFromUnFormattedDate(strDate);
   tmpYear = DSTCommonFunctions::getYearFromUnFormattedDate(strDate);
   COleDateTime currTime = COleDateTime(tmpYear,tmpMonth,tmpDay,0,0,0);

   m_dtpDate.SetTime(currTime);

   if(!search())
      return;
   adjustSelection();
//	CheckDlgButton(IDC_RD_UNSETTLE_TRADE_INC, 1);
   OnRdUnsettleTradeInc();
   GetDlgItem (IDC_BTN_HMV_SHARELOTS)->EnableWindow(false);
   GetDlgItem (IDC_BTN_INVEST_INFO)->EnableWindow(false);
}

//*******************************************************************************************
void HistoricalMarketValueDlg::adjustSelection()
{
   TRACE_METHOD(CLASSNAME, ADJUSTSELECTION);

   int selNum = 0;

   while(DString(m_lvFunds.GetItemText(selNum, 0)) != m_strInitFundCode 
          || DString(m_lvFunds.GetItemText(selNum, 1)) != m_strInitClassCode)
      ++selNum;
   if(selNum < m_lvFunds.GetItemCount())
      m_lvFunds.SetSelection(selNum);

   //setPriceAndDate(m_strInitFundCode, m_strInitClassCode);
//	setCurrency(m_strInitFundCode, m_strInitClassCode);
   //  PriceDateORforeign();

}


/*******************************************************************************************/
SEVERITY HistoricalMarketValueDlg::doInit()
{
   TRACE_METHOD(CLASSNAME, DOINIT);

   SEVERITY sevRtn = SEVERE_ERROR;

   getParameter(FUND_CODE, m_strInitFundCode);
   getParameter(CLASS_CODE, m_strInitClassCode);

   sevRtn = NO_CONDITION;
   return(sevRtn);
}

/*******************************************************************************************/
void HistoricalMarketValueDlg::OnBtnSearch() 
{
   TRACE_METHOD(CLASSNAME, ONBTNSEARCH);

   DSTOleDateTime odtDate;
   m_dtpDate.GetTime(odtDate);

   time_t *timer = 0;
   DSTOleDateTime odtCurrentDate(time(timer));

   if(odtDate > odtCurrentDate)
   {
      AfxMessageBox(TXT_HISTORICAL_MARKET_VALUE_NO_FUTURE_DATES);
      m_dtpDate.SetFocus();
      return;
   }


   if(!search())
      return;

   m_lvFunds.SetSelection(0);
/*	setPriceAndDate(DString(m_lvFunds.GetItemText(0, 0)), 
                        DString(m_lvFunds.GetItemText(0, 1)));
  setCurrency(DString(m_lvFunds.GetItemText(0, 0)), 
                        DString(m_lvFunds.GetItemText(0, 1)));

   PriceDateORforeign();*/
}

/*******************************************************************************************/
bool HistoricalMarketValueDlg::search()
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTGUI_CONDITION, CLASSNAME, SEARCH);

   CWaitCursor wait;
	// Before doing a new search, clear the list
	m_lvFunds.DeleteAllItems();
   int i = 0;
   DString strMarket = DSTCommonFunctions::getMarket();

   SetMessageStatusBar(TXT_SEARCH_FOR_HISTORICAL_MARKET_VALUE);
   UpdateData(TRUE);

   ////CTime date;
   //COleDateTime date;
   //m_dtpDate.GetTime(date);
   //CString strDate = date.Format(CTIME_FORMAT);
   CString strDate;

   m_dtpDate.GetDateInHostFormat(strDate);
   
   if(strDate == "Invalid DateTime.")
   {
	  AfxMessageBox(TXT_INVALID_DATE);
      return(false);
   }

   DString temp(strDate);
   getParent()->setParameter(AS_OF_DATE, DString(strDate));
   SEVERITY sev = getParent()->performSearch(this, BF::AllContainerIds, SEARCH_START);
   SetMessageStatusBar(NULL_STRING);
   if(sev > WARNING)
	{
		// Promote conditions from performSearch
		ConditionMessageBox(MYFRAME(), GETCURRENTHIGHESTSEVERITY());
      return(false);
	}
   OnRdUnsettleTradeInc(); 

//   m_lvFunds.DeleteAllItems();
/*
   if((sev > WARNING) && (GETCURRENTHIGHESTSEVERITY() == sev))
  {
    SetDlgItemText(IDC_TXT_PRICE_VALUE, NULL_STRING);

      if (strMarket == MARKET_IDS::JAPAN)
      SetDlgItemText(IDC_TXT_PRICE_DATE_VALUE, NULL_STRING);
    
      SetDlgItemText(IDC_TXT_CURRENCY_VALUE, NULL_STRING);
    SetDlgItemText(IDC_EDT_FOREIGNACB_VALUE, NULL_STRING);
      ConditionMessageBox(MYFRAME(), GETCURRENTHIGHESTSEVERITY());
    return false;
  }
   else
   {
    const DString *pKey = &getParent()->getFirstListItemKey(this, 
                                  HISTORICAL_MARKET_VALUE_LIST);	
    if(*pKey == NULL_STRING)
    {
      SetMessageStatusBar(NULL_STRING);
      return false;
    }

    DString str, strFund, strClass;
      getParent()->getField(this, HISTORICAL_MARKET_VALUE_LIST, DBR::FrgnACB, str);
     str.stripAll();
      str = str + I_("%");
      m_strFrgnACB = str.c_str();
    do
    {
      getParent()->getField(this, 
                HISTORICAL_MARKET_VALUE_LIST, DBR::rxFundCode, strFund);
      strFund.stripLeading().stripTrailing().upperCase();
      int numItem = m_lvFunds.GetItemCount();
      int idx = m_lvFunds.InsertItem(numItem, strFund.c_str());
      m_lvFunds.SetItemData(idx, reinterpret_cast< DWORD >(pKey));
         i = 1;
      getParent()->getField(this, 
                HISTORICAL_MARKET_VALUE_LIST, DBR::rxClassCode, strClass);
      strClass.stripLeading().stripTrailing().upperCase();
         
      m_lvFunds.SetItemText(idx, i, strClass.c_str());
         i++;
         if (strMarket == MARKET_IDS::CANADA || strMarket == MARKET_IDS::LUXEMBOURG)
         {
            dynamic_cast<DSTCWorkSession *>(getBFWorkSession())->GetFundNumber (strFund, strClass, str);
            m_lvFunds.SetItemText(idx, i, str.c_str());
            i++;
         }
      getParent()->getField(this, 
                HISTORICAL_MARKET_VALUE_LIST, DBR::SettledUnits, str);
      str.stripLeading().stripTrailing();
      m_lvFunds.SetItemText(idx, i, str.c_str());
         i++;
      getParent()->getField(this, 
                HISTORICAL_MARKET_VALUE_LIST, DBR::SettledValue, str);
      str.stripLeading().stripTrailing();
      m_lvFunds.SetItemText(idx, i, str.c_str());
         i++;
      getParent()->getField(this, 
                HISTORICAL_MARKET_VALUE_LIST, DBR::UnsettledUnits, str);
      str.stripLeading().stripTrailing();
      m_lvFunds.SetItemText(idx, i, str.c_str());
         i++;
      getParent()->getField(this, 
                HISTORICAL_MARKET_VALUE_LIST, DBR::UnsettledValue, str);
      str.stripLeading().stripTrailing();
      m_lvFunds.SetItemText(idx, i, str.c_str());
         i++;
      //if(idx == 0)
      //{
      //	SetCurrency(strFund, strClass);
      //	getParent()->getField(this, 
      //					HISTORICAL_MARKET_VALUE_LIST, DBR::FundNAV, str);
      //	str.stripLeading().stripTrailing();
      //	SetDlgItemText(IDC_TXT_PRICE_VALUE, str.c_str());
      //}
      pKey = &getParent()->getNextListItemKey(this, 
                                  HISTORICAL_MARKET_VALUE_LIST);
    }
    while(*pKey != NULL_STRING);

    SetMessageStatusBar(NULL_STRING);
    UpdateData(FALSE);
    return true;
   }*/
   return(true);
}


/*******************************************************************************************/
void HistoricalMarketValueDlg::OnItemchangedLvFunds(NMHDR* pNMHDR, 
   LRESULT* pResult) 
{
   NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;

   if (pNMListView->uNewState & LVIS_SELECTED)
   {
      DWORD dwKey = m_lvFunds.GetItemData(pNMListView->iItem);
      DString* dstrKey = reinterpret_cast< DString* >(dwKey);
      getParent()->setCurrentListItem(this, IFASTBP_PROC::HISTORICAL_MARKET_VALUE_LIST, 
         *dstrKey);
      //display the fund group related fields
      displayFundGroupFields();
   }
   enableShareLotButton();
   enableInvestInfoButton();
 /*NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
  static DString oldFund, oldClass, oldPrice, oldPriceDate, oldCurrency; 
  int nSelected;
   DString strMarket = DSTCommonFunctions::getMarket();
  
  if (pNMListView->uOldState & LVIS_SELECTED)
   {
    nSelected = pNMListView->iItem;
    oldFund = LPCTSTR(m_lvFunds.GetItemText(nSelected, 0));
    oldClass = LPCTSTR(m_lvFunds.GetItemText(nSelected, 1));
    CString str;
    GetDlgItemText(IDC_TXT_PRICE_VALUE, str);
    oldPrice = LPCTSTR(str);
      if (strMarket == MARKET_IDS::JAPAN)
    {
      GetDlgItemText(IDC_TXT_PRICE_DATE_VALUE, str);
      oldPriceDate = LPCTSTR(str);
    }
     
    GetDlgItemText(IDC_TXT_CURRENCY_VALUE, str);
    oldCurrency = LPCTSTR(str);

    SetDlgItemText(IDC_TXT_PRICE_VALUE, NULL_STRING);
      if (strMarket == MARKET_IDS::JAPAN)
      SetDlgItemText(IDC_TXT_PRICE_DATE_VALUE, NULL_STRING);
    SetDlgItemText(IDC_TXT_CURRENCY_VALUE, NULL_STRING);

      PriceDateORforeign();
   }
   else if (pNMListView->uNewState & LVIS_SELECTED)
   {
    nSelected = pNMListView->iItem;
    DString newFund(m_lvFunds.GetItemText(nSelected, 0));
    DString newClass(m_lvFunds.GetItemText(nSelected, 1));
    if (newFund == oldFund && newClass == oldClass)
    {
      SetDlgItemText(IDC_TXT_PRICE_VALUE, oldPrice.c_str());
         if (strMarket == MARKET_IDS::JAPAN)
        SetDlgItemText(IDC_TXT_PRICE_DATE_VALUE, oldPriceDate.c_str());
      SetDlgItemText(IDC_TXT_CURRENCY_VALUE, oldCurrency.c_str());
    }
    else
    {
      setPriceAndDate(newFund, newClass);
      setCurrency(newFund, newClass);
    }

      PriceDateORforeign();
   }
  */
  *pResult = 0;
}


/*******************************************************************************************/
/*
void HistoricalMarketValueDlg::setCurrency(const DString &strFund, 
                                    const DString &strClass)
{
  DString strDetailsFund, strDetailsClass, strCurrency;
  #ifdef _DEBUG
  bool itemFound = false;
  #endif
  getParent()->getFirstListItemKey(this, FUND_DETAIL_LIST);
  do
  {
    getParent()->getField(this, 
                FUND_DETAIL_LIST, DBR::FundCode, strDetailsFund);
    strDetailsFund.stripLeading().stripTrailing().upperCase();
    if(strDetailsFund == strFund)
    {
      getParent()->getField(this, 
                FUND_DETAIL_LIST, DBR::ClassCode, strDetailsClass);
      strDetailsClass.stripLeading().stripTrailing().upperCase();
      if(strDetailsClass == strClass)
      {
        getParent()->getField(this, 
                FUND_DETAIL_LIST, DBR::Currency, strCurrency);
        strCurrency.stripLeading().stripTrailing();
        SetDlgItemText(IDC_TXT_CURRENCY_VALUE, strCurrency.c_str());
        #ifdef _DEBUG
        itemFound = true;
        #endif
        break;
      }
    }
  }
  while(getParent()->getNextListItemKey(this, 
                          FUND_DETAIL_LIST) != NULL_STRING);
  assert(itemFound);
}


/*******************************************************************************************/
/*void HistoricalMarketValueDlg::setPriceAndDate(const DString &strFund, 
                                    const DString &strClass)
{
  DString strHistFund, strHistClass, strPrice, strPriceDate;
   DString strMarket = DSTCommonFunctions::getMarket();

  #ifdef _DEBUG
  bool itemFound = false;
  #endif
  getParent()->getFirstListItemKey(this, HISTORICAL_MARKET_VALUE_LIST);
  do
  {
    getParent()->getField(this, HISTORICAL_MARKET_VALUE_LIST, 
                              DBR::rxFundCode, strHistFund);
    strHistFund.stripLeading().stripTrailing().upperCase();
    if(strHistFund == strFund)
    {
      getParent()->getField(this, HISTORICAL_MARKET_VALUE_LIST, 
                              DBR::rxClassCode, strHistClass);
      strHistClass.stripLeading().stripTrailing().upperCase();
      if(strHistClass == strClass)
      {
        getParent()->getField(this, 
            HISTORICAL_MARKET_VALUE_LIST, DBR::FundNAV, strPrice);
        strPrice.stripLeading().stripTrailing();
        SetDlgItemText(IDC_TXT_PRICE_VALUE, strPrice.c_str());
            if (strMarket == MARKET_IDS::JAPAN)
        {
          getParent()->getField(this, HISTORICAL_MARKET_VALUE_LIST, 
                                DBR::AsAtDate, strPriceDate);
          strPrice.stripLeading().stripTrailing();
          SetDlgItemText(IDC_TXT_PRICE_DATE_VALUE, strPriceDate.c_str());
        }
        #ifdef _DEBUG
        itemFound = true;
        #endif
        break;
      }
    }
  }
  while(getParent()->getNextListItemKey(this, 
                    HISTORICAL_MARKET_VALUE_LIST) != NULL_STRING);
  assert(itemFound);
}
*/

/*******************************************************************************************/
bool HistoricalMarketValueDlg::doRefresh(GenericInterface * rpGICaller, 
   const I_CHAR * szOriginalCommand)
{
   DString dstrShrNum;
   getParent()->getField(this,ifds::ShrNum,dstrShrNum);
   dstrShrNum.stripLeading().stripLeading(I_CHAR('0')).stripTrailing();

   DString strAccountNum;
   getParent()->getField(this, ifds::AccountNum, strAccountNum);
   strAccountNum.stripLeading().stripLeading(I_CHAR('0')).stripTrailing();
   SetAccount(strAccountNum);   

   DString dstrEntityName;
   dynamic_cast<DSTCWorkSession *>(getBFWorkSession())->getFirstSequenced01AccountholderEntityName(getDataGroupId(), 
                                                                                                    strAccountNum, 
                                                                                                    dstrEntityName);

   SetShrAcctCaption(dstrShrNum, strAccountNum, dstrEntityName);

   getParameter(FUND_CODE, m_strInitFundCode);
   getParameter(CLASS_CODE, m_strInitClassCode);

   //JavaDate currDate;
   //JavaSimpleDateFormat *pTimeDateFormat 
   //										= JavaSimpleDateFormat::US(JAVA_DATE_FORMAT);
   //m_date = (pTimeDateFormat->format(&currDate)).c_str();

   DString strDate;
   DSTCWorkSession* pDSTCWorkSession = dynamic_cast<DSTCWorkSession *>(getParent()->getBFWorkSession());
   pDSTCWorkSession->getOption (ifds::CurrBusDate, strDate, getParent()->getDataGroupId(), false);
   
   int tmpDay, tmpMonth, tmpYear;

   tmpDay = DSTCommonFunctions::getDayFromUnFormattedDate(strDate);
   tmpMonth = DSTCommonFunctions::getMonthFromUnFormattedDate(strDate);
   tmpYear = DSTCommonFunctions::getYearFromUnFormattedDate(strDate);
   COleDateTime currTime = COleDateTime(tmpYear,tmpMonth,tmpDay,0,0,0);

   m_dtpDate.SetTime(currTime);

   if(DString(szOriginalCommand) == FULL_REFRESH)
   {
      /*	m_lvFunds.DeleteAllItems();
        SetDlgItemText(IDC_TXT_PRICE_VALUE, NULL_STRING);
        SetDlgItemText(IDC_TXT_CURRENCY_VALUE, NULL_STRING);
        GetDlgItem(IDC_TXT_PRICE_VALUE)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_TXT_CURRENCY_VALUE)->ShowWindow(SW_HIDE);*/
      if(!search())
         return(false);
   }
   else
      assert(DString(szOriginalCommand) == PARTIAL_REFRESH);

   adjustSelection();

   return(true);
}

/*******************************************************************************************/
/*
void HistoricalMarketValueDlg::PriceDateORforeign()
{
   DString strMarket = DSTCommonFunctions::getMarket();
   if (strMarket == MARKET_IDS::JAPAN)
   {
      GetDlgItem(IDC_TXT_PRICE_DATE)->ShowWindow(SW_SHOW);
    GetDlgItem(IDC_TXT_PRICE_DATE_VALUE)->ShowWindow(SW_SHOW);
      GetDlgItem(IDC_TXT_FOREIGNACB)->ShowWindow(SW_HIDE);
      GetDlgItem(IDC_EDT_FOREIGNACB_VALUE)->ShowWindow(SW_HIDE);
   }
   else if (strMarket == MARKET_IDS::CANADA || strMarket == MARKET_IDS::LUXEMBOURG)
   {
      GetDlgItem(IDC_TXT_PRICE_DATE)->ShowWindow(SW_HIDE);
      GetDlgItem(IDC_TXT_PRICE_DATE_VALUE)->ShowWindow(SW_HIDE);
      GetDlgItem(IDC_TXT_FOREIGNACB)->ShowWindow(SW_SHOW);
      GetDlgItem(IDC_EDT_FOREIGNACB_VALUE)->ShowWindow(SW_SHOW);
   }
}
*/
//****************************************************************************
void HistoricalMarketValueDlg::OnRdUnsettleTradeInc() 
{
   // TODO: Add your control notification handler code here
/*  UINT uState = IsDlgButtonChecked(IDC_RD_UNSETTLE_TRADE_INC);
  if(uState == 0) uState = 1;
  else uState = 0;
  CheckDlgButton(IDC_RD_UNSETTLE_TRADE_INC, uState);
*/
   if(IsDlgButtonChecked(IDC_RD_UNSETTLE_TRADE_INC))
   { //unsettled trades included for FC
      DispHistoryList(true);
      DispHistoryControls(true);
   }
   else
   { //unsettled trades excluded
      DispHistoryList(false); 
      DispHistoryControls(false);
   }
}

//****************************************************************************
void HistoricalMarketValueDlg::OnBtnFCWorksheet()
{
	MAKEFRAMEAUTOPROMOTE2(CND::IFASTGUI_CONDITION, CLASSNAME, I_("OpenBrokerListDlg"));
   CWaitCursor wait;	
   
   try
   {
		SetMessageStatusBar( TXT_LOAD_FOREIGN_CONTENT_WORKSHEET );

		DString dstrShrNum;
		getParent()->getField(this,ifds::ShrNum,dstrShrNum);
		dstrShrNum.stripLeading().stripLeading(I_CHAR('0')).stripTrailing();

		DString dstrAccountNum;
		getParent()->getField(this, ifds::AccountNum, dstrAccountNum );
		dstrAccountNum.stripLeading().stripLeading(I_CHAR('0')).stripTrailing();

		setParameter( FOREIGN_CONTENT_WORKSHEET::ACCOUNT_NUMBER,     dstrAccountNum );
		setParameter( FOREIGN_CONTENT_WORKSHEET::SHAREHOLDER_NUMBER, dstrShrNum );	

      E_COMMANDRETURN eRtn = invokeCommand( getParent(), 
														  CMD_BPROC_FOREIGN_CONTENT_WORKSHEET, 
														  PROC_NO_TYPE, 
														  false,   // modal
														  NULL );
      switch(eRtn)
      {
			case CMD_OK:
         case CMD_MODELESS_INPROCESS:                              
         case CMD_CANCEL:
				break;
         default:
         // Display error
            ConditionMessageBox(FRAMEBELOW(), GETHIGHESTSEVERITY());
            break;
      }
   }
   catch (ConditionException &ce)
   {
      ConditionMessageBox(ce);
   }
   catch (...)
   {
      DISPLAYCONDITIONFROMFILE( CND::GUI_ERR_UNKNOWN_EXCEPTION );
   }
}

//******************************************************************************
void HistoricalMarketValueDlg::DispHistoryList(bool bInclude)
{
   m_lvFunds.DeleteAllItems();
   const BFFieldId idSettleFields[] = {
      ifds::UnsettledUnits,
      ifds::SettledUnits,
      ifds::ACBSettl,
      ifds::ACBSettlPrcnt,
      ifds::SettledValueAcctCurr,
      ifds::MktValSettlPrcnt
   };
   const BFFieldId idTotalFields[] = {
      ifds::UnsettledUnits,
      ifds::SettledUnits,
      ifds::ACBTotal,
      ifds::ACBTotalPrcnt,
      ifds::CombValueAcctCurr,
      ifds::MktValTotalPrcnt
   };
   const DString *pKey = &getParent()->getFirstListItemKey(this, 
      IFASTBP_PROC::HISTORICAL_MARKET_VALUE_LIST); 
   DString strFund,strClass,strMarket;

   strMarket = DSTCommonFunctions::getMarket();
   int i;
   if(*pKey != NULL_STRING)
   {
      do
      {
         getParent()->getField(this, IFASTBP_PROC::HISTORICAL_MARKET_VALUE_LIST, 
            ifds::rxFundCode, strFund);
         strFund.stripLeading().stripTrailing().upperCase();
         int numItem = m_lvFunds.GetItemCount();
         int idx = m_lvFunds.InsertItem(numItem, strFund.c_str());
         m_lvFunds.SetItemData(idx, reinterpret_cast< DWORD >(pKey));
         i = 1;
         getParent()->getField(this, 
            IFASTBP_PROC::HISTORICAL_MARKET_VALUE_LIST, ifds::rxClassCode, strClass);
         strClass.stripLeading().stripTrailing().upperCase();

         m_lvFunds.SetItemText(idx, i, strClass.c_str());
         i++;
         DString strValue;
         if(strMarket == MARKET_IDS::CANADA || strMarket == MARKET_IDS::LUXEMBOURG)
         {
            dynamic_cast<DSTCWorkSession *>(getBFWorkSession())->GetFundNumber (strFund, strClass, strValue);
            m_lvFunds.SetItemText(idx, i, strValue.c_str());
            i++;
         }
         
         CString cstr;
         
         getParent()->getField(this, IFASTBP_PROC::HISTORICAL_MARKET_VALUE_LIST, 
            ifds::Domestic, strValue,false);
         strValue.strip().upperCase();
         if(strValue == Y)
         {
            cstr.LoadString(IDS_DOMESTIC);
         }
         else
         {
            cstr.LoadString(IDS_FOREIGN);
         }
         m_lvFunds.SetItemText(idx, i, cstr);
         i++;

         BFFieldId idField = ifds::NullFieldId; 

		 bool isUnsettled = false; 
         for(int jj = 0; jj <=5; jj++)
         {
            if(bInclude)
               idField = idTotalFields[ jj ];
            else idField = idSettleFields [ jj ];
			
			if (idField == ifds::UnsettledUnits)
				isUnsettled = true;

            bool isFndClassACBAvailable = true;

            if (idField == ifds::ACBSettl || idField == ifds::ACBSettlPrcnt ||
               idField == ifds::ACBTotal || idField == ifds::ACBTotalPrcnt)
            {
               DString fndClassACBAvailable;
   			   DString acctACBAvailable;

               getParent()->getField(this, IFASTBP_PROC::HISTORICAL_MARKET_VALUE_LIST, 
                  ifds::FndClsACBAvailable, fndClassACBAvailable, false);

              getParent()->getField(this, IFASTBP_PROC::HISTORICAL_MARKET_VALUE_LIST, 
                  ifds::AcctACBAvailable, acctACBAvailable, false);

               if (fndClassACBAvailable == I_("Y")) 
               {
                  isFndClassACBAvailable = true;
               } else if (fndClassACBAvailable == I_("N")) 
               {
                  isFndClassACBAvailable = false;
               } else
               {
                  assert(0);
               }
			
			   if (acctACBAvailable == I_("N") && 
				   (idField == ifds::ACBSettlPrcnt || idField == ifds::ACBTotalPrcnt))
				    isFndClassACBAvailable = false;

            }
			
			if (isUnsettled)
			{	if (idField == ifds::ACBSettl)
					getParent()->getField(this, IFASTBP_PROC::HISTORICAL_MARKET_VALUE_LIST, ifds::ACBTotal, strValue);
				else if (idField == ifds::ACBSettlPrcnt)
					getParent()->getField(this, IFASTBP_PROC::HISTORICAL_MARKET_VALUE_LIST, ifds::ACBTotalPrcnt, strValue);
				else if (idField == ifds::SettledValueAcctCurr)
					getParent()->getField(this, IFASTBP_PROC::HISTORICAL_MARKET_VALUE_LIST, ifds::CombValueAcctCurr, strValue);
				else if (idField == ifds::MktValSettlPrcnt)
					getParent()->getField(this, IFASTBP_PROC::HISTORICAL_MARKET_VALUE_LIST, ifds::MktValTotalPrcnt, strValue);
				else 
					getParent()->getField(this, IFASTBP_PROC::HISTORICAL_MARKET_VALUE_LIST, idField, strValue);
			}
			else
				getParent()->getField(this, IFASTBP_PROC::HISTORICAL_MARKET_VALUE_LIST, idField, strValue);

            strValue.stripLeading().stripTrailing();
            if (isFndClassACBAvailable)
            {
			   m_lvFunds.doSetItemText(idx, i, strValue.c_str(), idField );               
            } else 
            {
               CString msg;

               msg.LoadString(TXT_SUPPRESS_ACB_FUND);
               m_lvFunds.SetItemText(idx, i, msg.GetBuffer(0));
            }
            i++;                
         } 
         pKey = &getParent()->getNextListItemKey(this, IFASTBP_PROC::HISTORICAL_MARKET_VALUE_LIST);
      }while(*pKey != NULL_STRING);
   }
}
//********************************************************************************
// this mehtod will display fixed part
// 
void HistoricalMarketValueDlg::DispHistoryControls(bool bInclude)
{
   int iControls[] = {
      IDC_EDT_FCACB,
      IDC_TXT_DOMESTICACB,
      IDC_TXT_FC_ALLOWED,
      IDC_TXT_FC_EXCESS,
      IDC_TXT_ACB_TOTAL,
      IDC_MV_TOTAL,
      IDC_TXT_FC_ALLOWEDACB,
      IDC_FC_EXCESS_ACB
   };
   const BFFieldId idSettleFields[] = {
      ifds::FrgnACBSettl,
      ifds::DomesticACBSettl,
      ifds::FrgnAllowPrcnt,
      ifds::FrgnExcsPrcntSettl,
      ifds::TotalACBSettl,
      ifds::AccountBalance,
      ifds::FrgnAllowACBSettl,
      ifds::FrgnExcsACBSettl  
   };

   const BFFieldId idTotalFields[] = {
      ifds::FrgnACBUnsettl,
      ifds::DomesticACBUnSettl,
      ifds::FrgnAllowPrcnt,
      ifds::FrgnExcsPrcntUnSettl,
      ifds::TotalACBUnSettl,
      ifds::TotalValueAcctCurr,
      ifds::FrgnAllowACBUnSettl,
      ifds::FrgnExcsACBUnsettl  
   };
   DString strValue;
   BFFieldId idField = ifds::NullFieldId;
   for(int i = 0; i < 8; i++)
   {
      bool isAcctACBAvailable = true;
      if(bInclude) 
         idField = idTotalFields[i];
      else 
         idField = idSettleFields[i];

      if (idField == ifds::FrgnACBSettl || idField == ifds::DomesticACBSettl ||
         idField == ifds::TotalACBSettl || idField == ifds::FrgnAllowACBSettl ||
         idField == ifds::FrgnExcsACBSettl || idField == ifds::FrgnACBUnsettl ||
         idField == ifds::DomesticACBUnSettl || idField == ifds::TotalACBUnSettl ||
         idField == ifds::FrgnAllowACBUnSettl || idField == ifds::FrgnExcsACBUnsettl)
      {
         DString acctACBAvailable;

         getParent()->getField(this, IFASTBP_PROC::HISTORICAL_MARKET_VALUE_LIST, 
            ifds::AcctACBAvailable, acctACBAvailable, false);
         if (acctACBAvailable == I_("Y")) 
         {
            isAcctACBAvailable = true;
         } else if (acctACBAvailable == I_("N")) 
         {
            isAcctACBAvailable = false;
         } else
         {
            assert(0);
         }
      }
      if (isAcctACBAvailable)
      {
         getParent()->getField(this, IFASTBP_PROC::HISTORICAL_MARKET_VALUE_LIST, idField, strValue);
         strValue.strip();
         if(i < 4 && strValue != NULL_STRING) strValue += PERCENT;
		 doSetDlgItemText(iControls[ i ], strValue.c_str(), idField);          
      } else 
      {
         CString msg;

         msg.LoadString(TXT_SUPPRESS_ACB_FUND);
         SetDlgItemText(iControls[ i ], msg.GetBuffer(0)); 
      }
   }
   getParent()->getField(this, IFASTBP_PROC::MFACCOUNT_CBO,ifds::CurrencyName, strValue);
   SetDlgItemText(IDC_TXT_CURRENCY_VALUE, strValue.c_str()); 
}

void HistoricalMarketValueDlg::displayFundGroupFields()
{
   DString dstrFundGroup, dstrFundGroupTotalSettledValue;

   getParent()->getField(this, IFASTBP_PROC::HISTORICAL_MARKET_VALUE_LIST, 
      ifds::FundGroup, dstrFundGroup);
   if (dstrFundGroup == NULL_STRING)
   {
      GetDlgItem(IDC_TXT_FUND_GROUP)->ShowWindow(SW_HIDE);
      GetDlgItem(IDC_STATIC_FUND_GROUP)->ShowWindow(SW_HIDE);
      GetDlgItem(IDC_TXT_SBTL_FUND_GROUP)->ShowWindow(SW_HIDE);
      GetDlgItem(IDC_STATIC_SBTL_FUND_GROUP)->ShowWindow(SW_HIDE);
   }
   else 
   {
      GetDlgItem(IDC_TXT_FUND_GROUP)->ShowWindow(SW_SHOW);
      GetDlgItem(IDC_STATIC_FUND_GROUP)->ShowWindow(SW_SHOW);
      GetDlgItem(IDC_TXT_SBTL_FUND_GROUP)->ShowWindow(SW_SHOW);
      GetDlgItem(IDC_STATIC_SBTL_FUND_GROUP)->ShowWindow(SW_SHOW);
      getParent()->getField(this, IFASTBP_PROC::HISTORICAL_MARKET_VALUE_LIST, 
         ifds::FundGroupTotalSettledValue, dstrFundGroupTotalSettledValue);
      SetDlgItemText(IDC_TXT_FUND_GROUP, dstrFundGroup.c_str());
      SetDlgItemText(IDC_TXT_SBTL_FUND_GROUP, dstrFundGroupTotalSettledValue.c_str());
   }
}
//****************************************************************************
void HistoricalMarketValueDlg::enableShareLotButton()
{
	DString dstrFundCode,dstrClassCode,dstrIWTEnable;		

	DSTCWorkSession *dstWorkSession = dynamic_cast<DSTCWorkSession *>(getParent()->getBFWorkSession());
	dstWorkSession->getOption( ifds::IWTEnable, dstrIWTEnable,getParent()->getDataGroupId(), false );

	getParent()->getField (this, IFASTBP_PROC::HISTORICAL_MARKET_VALUE_LIST, ifds::rxFundCode,  dstrFundCode, false);
	getParent()->getField (this, IFASTBP_PROC::HISTORICAL_MARKET_VALUE_LIST, ifds::rxClassCode,  dstrClassCode, false);

	bool bEnable = dstWorkSession->isPerfFeeFund(dstrFundCode,dstrClassCode,getParent()->getDataGroupId()) || 
				   (dstrIWTEnable == I_("Y"));
	GetDlgItem (IDC_BTN_HMV_SHARELOTS)->EnableWindow(bEnable);
}
//****************************************************************************
void HistoricalMarketValueDlg::enableInvestInfoButton()
{
	DString dstrAmtInvAppl;
	getParent()->getField(this, IFASTBP_PROC::HISTORICAL_MARKET_VALUE_LIST, AMT_INV_APPL, dstrAmtInvAppl, false);  

    GetDlgItem (IDC_BTN_INVEST_INFO)->EnableWindow(dstrAmtInvAppl.stripAll() == Y);
}
//*****************************************************************************
void HistoricalMarketValueDlg::OnBtnShareLots()
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OnBtnShareLot" ) ); 
	
	E_COMMANDRETURN eRtn = CMD_OK;
	DString dstrFundCode,dstrClassCode,dstrAsOfDate,dstrTransId,dstrLotType,dstrIWTEnable;
	
	getParent()->getField (this, IFASTBP_PROC::HISTORICAL_MARKET_VALUE_LIST, ifds::rxFundCode,  dstrFundCode, false);
	dstrFundCode.stripAll();

	getParent()->getField (this, IFASTBP_PROC::HISTORICAL_MARKET_VALUE_LIST, ifds::rxClassCode,  dstrClassCode, false);
	dstrClassCode.stripAll();

	getParent()->getField( this, IFASTBP_PROC::HISTORICAL_MARKET_VALUE_LIST, ifds::AsAtDate, dstrAsOfDate );
    dstrAsOfDate.stripAll();

	DString DisplayMaskFormat = GetConfigValueAsString (I_( "LocaleFormats" ), I_( "DisplayMasks" ), I_( "enUS-D" ));
	DisplayMaskFormat.stripAll();
	DisplayMaskFormat = DisplayMaskFormat.lowerCase ();

	DisplayMaskFormat = DisplayMaskFormat.stripAll(I_CHAR('/')); //Removing separator
	DisplayMaskFormat = DisplayMaskFormat.stripAll(I_CHAR('-')); //Removing separator
	
	DString AsOfDate;
	if (DisplayMaskFormat == I_("ddmmyyyy"))
	{
		dstrAsOfDate = dstrAsOfDate.stripAll(I_CHAR('/')); //Removing separator if any
		dstrAsOfDate = dstrAsOfDate.stripAll(I_CHAR('-')); //Removing separator if any

		AsOfDate =  dstrAsOfDate.substr ( 2, 2 ); //month
		AsOfDate += I_("/");
		AsOfDate += dstrAsOfDate.substr ( 0, 2 ); //day
		AsOfDate += I_("/");
		AsOfDate += dstrAsOfDate.substr ( 4, 4 ); //year
	}
	else
	{
		AsOfDate =  dstrAsOfDate;
	}
	DString dstrActiveOnly		= I_("Yes");
	DString dstrAllTransactions = I_("Yes");

	DString strAccountNum;
	getParent()->getField(this, ifds::AccountNum, strAccountNum);

	DString urlParamsIDI;
	addIDITagValue (urlParamsIDI, I_("AccountNum"), strAccountNum);
	addIDITagValue (urlParamsIDI, I_("Fund"), dstrFundCode);
	addIDITagValue (urlParamsIDI, I_("Class"), dstrClassCode);
	addIDITagValue (urlParamsIDI, I_("AsOfDate"), AsOfDate);
	addIDITagValue (urlParamsIDI, I_("ActiveOnly"), dstrActiveOnly);
	addIDITagValue (urlParamsIDI, I_("TransId"), I_("0"));
	addIDITagValue (urlParamsIDI, I_("AllTransactions"), dstrAllTransactions);
	addIDITagValue (urlParamsIDI, I_("screen"), I_("SharelotSummary"));
	addIDITagValue (urlParamsIDI, I_("LotType"), I_(""));

	DSTCWorkSession *dstWorkSession = dynamic_cast<DSTCWorkSession *>(getParent()->getBFWorkSession());   

	DString dstrEntityName;
    dstWorkSession->getFirstSequenced01AccountholderEntityName( getDataGroupId(),strAccountNum,dstrEntityName);

    CString cstrSharelotAcctNum,cstrName;
    cstrSharelotAcctNum.LoadString(TXT_SHARELOT_ACCT_NUM);
    cstrName.LoadString(TXT_ACCT_HOLDER_NAME);
    
	DString screenTitle = DString(cstrSharelotAcctNum) + strAccountNum;
    screenTitle += DString(cstrName) + dstrEntityName;

	setParameter (I_("UrlParams"), urlParamsIDI);
	setParameter (I_("from_screen"), I_("HistoricalMarketValueDlg"));
	setParameter (I_("screen"), I_("SharelotSummary"));
	setParameter (I_("BrowserTitle"), screenTitle );
	
	eRtn = invokeCommand (getParent(), CMD_BPROC_SHARE_LOT_BROWSER, PROC_NO_TYPE, true, NULL);
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
//*****************************************************************************
void HistoricalMarketValueDlg::OnBtnInvestInfo()
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OnBtnInvestInfo" ) ); 
	
	E_COMMANDRETURN eRtn = CMD_OK;
	DString dstrFundCode, dstrClassCode, strAccountNum;
	
	getParent()->getField (this, IFASTBP_PROC::HISTORICAL_MARKET_VALUE_LIST, ifds::rxFundCode,  dstrFundCode, false);
	dstrFundCode.stripAll();

	getParent()->getField (this, IFASTBP_PROC::HISTORICAL_MARKET_VALUE_LIST, ifds::rxClassCode,  dstrClassCode, false);
	dstrClassCode.stripAll();

	getParent()->getField(this, ifds::AccountNum, strAccountNum);

	DString urlParamsIDI;
	addIDITagValue (urlParamsIDI, I_("AccountNum"), strAccountNum);
	addIDITagValue (urlParamsIDI, I_("Fund"), dstrFundCode);
	addIDITagValue (urlParamsIDI, I_("Class"), dstrClassCode);

	DSTCWorkSession *dstWorkSession = dynamic_cast<DSTCWorkSession *>(getParent()->getBFWorkSession());   

	DString dstrEntityName;
    dstWorkSession->getFirstSequenced01AccountholderEntityName( getDataGroupId(),strAccountNum,dstrEntityName);

    CString cstrInvestInfoAcctNum,cstrName;
    cstrInvestInfoAcctNum.LoadString(TXT_INVEST_INFO_ACCT_NUM);
    cstrName.LoadString(TXT_ACCT_HOLDER_NAME);
    
	DString screenTitle = DString(cstrInvestInfoAcctNum) + strAccountNum;
    screenTitle += DString(cstrName) + dstrEntityName;

    addIDITagValue(urlParamsIDI, I_("screen"), I_("AmountInventory"));
    addIDITagValue(urlParamsIDI, I_("from_screen"), I_("HistoricalMarketValueDlg"));
	setParameter (I_("UrlParams"), urlParamsIDI);
	setParameter (I_("BrowserTitle"), screenTitle );
	
    try
    {
        bool bModal = false;   // Default to modeless
        E_COMMANDRETURN eRtn;
        eRtn = invokeCommand(getParent(), CMD_BPROC_INVEST_INFO, PROC_NO_TYPE, true, NULL);
        switch (eRtn)
        {
        case CMD_OK:
        case CMD_CANCEL:
        case CMD_MODELESS_INPROCESS:
            break;
        default:
            // Display error
            ConditionMessageBox(FRAMEBELOW(), GETHIGHESTSEVERITY());
            break;
        }
    }
    catch (ConditionException &ce)
    {
        ConditionMessageBox(ce);
    }
    catch (...)
    {
        DISPLAYCONDITIONFROMFILE(CND::GUI_ERR_UNKNOWN_EXCEPTION);
    }

    SetMessageStatusBar(NULL_STRING);
}
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/HistoricalMarketValueDlg.cpp-arc  $
 * 
 *    Rev 1.43   May 14 2012 17:48:28   wp040027
 * PF - Adding separator in date to launch sharelot screen
 * 
 *    Rev 1.42   Apr 26 2012 11:41:04   wp040027
 * IN2934256: PF- P0188394 XML Parsing Error on clicking Sharelot info
 * 
 *    Rev 1.41   Mar 15 2012 12:33:42   wp040132
 * As per Winnie's suggestion, UrlParamter 'LotType' is passed as empty string. #IN 2873349 - Purchase Sharelot error in Desktop
 * 
 *    Rev 1.40   Feb 28 2012 04:12:20   panatcha
 * P0188394 - iFast Performance Fee - Add screen tag "SharelotSummary" 
 * 
 *    Rev 1.39   Jan 19 2012 11:10:42   wp040027
 * P0188394_Performance Fees - Added 'screen' and 'BrowswerTitle' to launch Sharelot Screen
 * 
 *    Rev 1.38   Jan 18 2012 17:13:18   wp040027
 * P0188394_Performance Fees - Launching valuation dtl/Sharelot Screens
 * 
 *    Rev 1.37   Nov 27 2006 15:00:46   jankovii
 * Incient #767243-Wrong ACB for unsettled trades.
 * 
 *    Rev 1.36   Nov 06 2006 11:11:16   jankovii
 * Incident #750314 - Percent is not valid in Desktop.
 * 
 *    Rev 1.35   Sep 15 2005 15:13:20   popescu
 * Incident#403519 - added CLASSNAME as the fifth parameter to  BaseMainDlg constructor
 * 
 *    Rev 1.34   Jun 24 2005 17:00:22   Fengyong
 * PET1250 FN02 - EuroPean numeric enhancement
 * 
 *    Rev 1.33   Jul 07 2004 13:52:44   VADEANUM
 * PTS 10032102 - Refresh and missing condition.
 * 
 *    Rev 1.32   May 26 2004 18:16:08   YINGBAOL
 * PET985: Add read permission check for foreign content.
 * 
 *    Rev 1.31   Apr 28 2004 14:19:52   VADEANUM
 * PET985 FN01 - LSIF - added ForeignContentWorksheet hook.
 * 
 *    Rev 1.30   Mar 21 2003 18:37:34   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.29   Feb 26 2003 13:47:36   linmay
 * clean up message
 * 
 *    Rev 1.28   Feb 18 2003 11:37:36   popescu
 * The controls related to the FundGroup are to be hidden if the FundGroup is empty, in the HistoricalMarketValueDlg
 * 
 *    Rev 1.27   Feb 18 2003 10:53:40   popescu
 * Fixed a selection bug, related to displaying the FundGroup and the FundGroupTotalSettledValue
 * 
 *    Rev 1.26   Feb 17 2003 14:24:04   popescu
 * Added a field for th calculation of the total market value by FundGroup
 * 
 *    Rev 1.25   Feb 17 2003 11:12:06   popescu
 * Displayed the Fund Group in the HistoricalMarketValue dialog
 * 
 *    Rev 1.24   Feb 07 2003 09:40:12   popescu
 * Changes related to the FndClassACBAvailable flag for Historical Market Value/ ACB
 * 
 *    Rev 1.23   Feb 05 2003 11:08:50   popescu
 * Displaying the ACB string when ACB cannot be calculated
 * 
 *    Rev 1.22   Oct 09 2002 23:55:44   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.21   Sep 04 2002 18:44:58   PURDYECH
 * Corrected incorrect use of BFFieldId arrays.
 * 
 *    Rev 1.20   Aug 29 2002 12:57:22   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.19   Jul 19 2002 15:46:08   KOVACSRO
 * Removed a harmful assertion.
 * 
 *    Rev 1.18   May 31 2002 10:12:12   ZHANGCEL
 * Syn up to 1.16.1.0
 * 
 *    Rev 1.17   22 May 2002 19:16:08   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.16   27 Mar 2002 20:01:12   PURDYECH
 * Process/WindowFactory overhaul
 * 
 *    Rev 1.15   Feb 27 2002 13:14:26   YINGBAOL
 * adjust sequence for Settle/UnSettle Unit in the list
 * 
 *    Rev 1.14   Feb 18 2002 10:35:40   YINGBAOL
 * foreign content enhancement
 * 
 *    Rev 1.13   Feb 05 2002 10:52:16   YINGBAOL
 * view change
 * 
 *    Rev 1.12   Feb 01 2002 15:25:12   YINGBAOL
 * Check in for resource change
 * 
 *    Rev 1.11   28 Dec 2001 15:01:26   KOVACSRO
 * Using only one container.
 * 
 *    Rev 1.10   03 May 2001 14:07:36   SMITHDAV
 * Session management restructuring.
 * 
 *    Rev 1.9   Mar 30 2001 19:22:14   DINACORN
 * Used DSTCommonFunctions MARKET_IDS constants
 * 
 *    Rev 1.8   Oct 19 2000 15:25:22   HUANGSHA
 * fix the crash problem
 * 
 *    Rev 1.7   Sep 29 2000 13:29:20   YINGZ
 * change market from cfds - canada to canada
 * 
 *    Rev 1.6   Jul 31 2000 14:45:04   VADEANUM
 * Title Bar Standards
 * 
 *    Rev 1.5   Jul 07 2000 13:46:02   ZHANGCEL
 * Changed for C2 improvment
 * 
 *    Rev 1.4   Mar 20 2000 14:39:58   HSUCHIN
 * changed GetFundNumber to use the one defined in DSTCommonFunctions
 * 
 *    Rev 1.3   Mar 08 2000 18:43:44   HSUCHIN
 * C2 stuff
 * 
 *    Rev 1.2   Feb 28 2000 14:53:26   DT24433
 * removed Cancel
 * 
 *    Rev 1.1   Feb 16 2000 16:17:40   YINGZ
 * fix date earlier than account active date problem
 * 
 *    Rev 1.0   Feb 15 2000 11:01:16   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.9   Sep 24 1999 10:13:56   PRAGERYA
 * "Milestone" check in
 * 
 *    Rev 1.8   Aug 17 1999 18:17:34   DT24433
 * changed getFieldForCurrentListItem to getField
 * 
 *    Rev 1.7   Aug 04 1999 14:34:00   PRAGERYA
 * Handling date ranges
 * 
 *    Rev 1.6   Jul 23 1999 12:31:42   PRAGERYA
 * Date formatting
 * 
 *    Rev 1.4   Jul 16 1999 13:29:54   PRAGERYA
 * aaa
 * 
 *    Rev 1.3   Jul 16 1999 10:28:28   PRAGERYA
 * Sorting
 * 
 *    Rev 1.2   Jul 14 1999 17:33:12   PRAGERYA
 * Date formatting
 * 
 *    Rev 1.1   Jul 08 1999 10:05:18   SMITHDAV
 * Modify revision history commaent format to old
 * style comment -- I can't seem to get new style comments to work.
 *
 */

