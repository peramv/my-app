
#ifndef HISTORICALMARKETVALUEDLG_H
#define HISTORICALMARKETVALUEDLG_H
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
// ^FILE   : HistoricalMarketValueDlg.h
// ^AUTHOR : Yakov Prager
// ^DATE   : 04/13/99
//
// ^CLASS    : HistoricalMarketValueDlg
// ^SUBCLASS : BaseMainDlg
//
// ^CLASS DESCRIPTION : Handles the code for the HistoricalMarketValueDlg dialog
//
//
//
// ^METHOD : process()
//
// ^DESCRIPTION : Get the intial stuff. Gets parms from call global.
//                
//
// ^PARAMETERS  :
//    ^^STRINGVECTOR *display - Values to add to list, comes from
//                                CallDataPtr()->_psvParm1
//    ^^string title            - Title of dialog, comes from
//                                CallDataPtr()->_sParm1
//
// ^RETURNS     :
//    ^^ int - Index into string vector of item selected or -1
//             CallDataPtr->iParm1
//
// ^THROWS      :
//
// ^EXAMPLE     :
//
// -----------------------------------------------------------------------------
//
//******************************************************************************

#ifndef BASEMAINDLG_H
   #include <ifastgui\BaseMainDlg.h>
#endif

#ifndef LISTCTRL_H
   #include <uibase\listctrl.h>
#endif

#ifndef DSTDATETIMECTRL_H
   #include <uibase\DSTDateTimeCtrl.h>
#endif

class HistoricalMarketValueDlg : public BaseMainDlg
{
// Construction
public:
   HistoricalMarketValueDlg(CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand);
   ~HistoricalMarketValueDlg();

// Dialog Data
   //{{AFX_DATA(HistoricalMarketValueDlg)
   enum
   {
      IDD = IDD_HISTORICAL_MARKET_VALUE
   };
   DSTDateTimeCtrl m_dtpDate;
   ListViewControl m_lvFunds;
   CString m_strFrgnACB;
   //}}AFX_DATA


// Overrides
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(HistoricalMarketValueDlg)
protected:
   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
   //}}AFX_VIRTUAL

// Implementation
protected:

   // Generated message map functions
   //{{AFX_MSG(HistoricalMarketValueDlg)
   virtual BOOL OnInitDialog();
   afx_msg void OnBtnSearch();
	afx_msg void OnItemchangedLvFunds(NMHDR* pNMHDR, LRESULT* pResult);
   afx_msg void OnRdUnsettleTradeInc();
	afx_msg void OnBtnFCWorksheet();
	afx_msg void OnBtnShareLots();
	afx_msg void OnBtnInvestInfo();
   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()

   /**
   * Loading entity list and first selection
   * This method is invoked by the base architecture after OnInitDialog has 
   * completed.  This should be implemented for time intensive setup so that
   * the screen can display quickly and then do this processing.
   */
   void OnPostInitDialog();

   /**
   * Get parameters from InterProcessData.
   * @returns SEVERITY, check conditions if > NO_SEVERITY
   */
   virtual SEVERITY doInit();
   /**
      * Required implementation for the refresh method.  No refresh activity is
      * performed for this class.
      * @param rpGICaller - A reference pointer to the calling object.
      * @param szOriginalCommand - A string literal representing the original
      * command issuing the refresh (which may provide a hint on whether this
      * object needs to check for refresh).
      * @returns true if successful, call getErrors for errors if false
      */
   virtual bool doRefresh(
                         GenericInterface * /*rpGICaller*/, 
                         const I_CHAR * /*szOriginalCommand*/
                         );

private:
   void DispHistoryList(bool bInclude);
   void DispHistoryControls(bool bInclude);

   bool search();
   void adjustSelection();
   void displayFundGroupFields();
   void enableShareLotButton();
   void enableInvestInfoButton();
//	void setCurrency( const DString &strFund, const DString &strClass );
//	void setPriceAndDate( const DString &strFund, const DString &strClass );
   //  void PriceDateORforeign();
   void DisplayListTitle();
   DString m_strInitFundCode;
   DString m_strInitClassCode;
   DString m_dstrMarket;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HISTORICALMARKETVALUEDLG_H__7DC69581_FE4F_11D2_A320_005004146900__INCLUDED_)

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/HistoricalMarketValueDlg.h-arc  $
 * 
 *    Rev 1.14   Jan 18 2012 17:13:42   wp040027
 * P0188394_Performance Fees - Launching valuation dtl/Sharelot Screens
 * 
 *    Rev 1.13   Apr 28 2004 14:19:12   VADEANUM
 * PET985 FN01 - LSIF - added ForeignContentWorksheet hook.
 * 
 *    Rev 1.12   Mar 21 2003 18:37:36   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.11   Feb 18 2003 10:53:44   popescu
 * Fixed a selection bug, related to displaying the FundGroup and the FundGroupTotalSettledValue
 * 
 *    Rev 1.10   Feb 17 2003 14:24:08   popescu
 * Added a field for th calculation of the total market value by FundGroup
 * 
 *    Rev 1.9   Feb 17 2003 11:12:08   popescu
 * Displayed the Fund Group in the HistoricalMarketValue dialog
 * 
 *    Rev 1.8   Oct 09 2002 23:55:44   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.7   19 Mar 2002 13:44:42   PURDYECH
 * Added #pragma once include guard
 * Removed compile time "including..." message.
 * 
 *    Rev 1.6   Feb 01 2002 15:25:12   YINGBAOL
 * Check in for resource change
 * 
 *    Rev 1.5   Jul 07 2000 13:46:18   ZHANGCEL
 * Changed for C2 improvment
 * 
 *    Rev 1.4   Mar 20 2000 14:39:58   HSUCHIN
 * changed GetFundNumber to use the one defined in DSTCommonFunctions
 * 
 *    Rev 1.3   Mar 08 2000 18:43:44   HSUCHIN
 * C2 stuff
 * 
 *    Rev 1.2   Feb 28 2000 14:55:44   DT24433
 * removed Cancel
 * 
 *    Rev 1.1   Feb 15 2000 18:59:28   MCNABBGL
 * changed comment format
 * 
 *    Rev 1.0   Feb 15 2000 11:01:16   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.6   Oct 23 1999 15:13:04   PRAGERYA
 * Includes changed
 * 
 *    Rev 1.5   Sep 24 1999 10:13:56   PRAGERYA
 * "Milestone" check in
 * 
 *    Rev 1.4   Aug 04 1999 14:34:06   PRAGERYA
 * Handling date ranges
 * 
 *    Rev 1.3   Jul 23 1999 12:31:44   PRAGERYA
 * Date formatting
 * 
 *    Rev 1.1   Jul 08 1999 10:05:20   SMITHDAV
 * Modify revision history commaent format to old
 * style comment -- I can't seem to get new style comments to work.
 *
 */
