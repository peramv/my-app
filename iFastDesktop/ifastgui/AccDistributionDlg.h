
#ifndef DISTRIBUTIONDLG_H
#define DISTRIBUTIONDLG_H
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
//    Copyright 1997 by DST Systems, Inc.
//
//******************************************************************************
//
// ^FILE   : AccDistributionDlg.h
// ^AUTHOR : Zijian Ying
// ^DATE   : 04/23/1999
//
// ^CLASS    : AccDistributionDlg
// ^SUBCLASS : BaseMainDlg
//
// ^CLASS DESCRIPTION : 
//
//******************************************************************************

#ifndef BASEMAINDLG_H
   #include <ifastgui\BaseMainDlg.h>
#endif
#include <ifastgui\ifasthistoricalinfo.hpp>

class AccDistributionDlg : public BaseMainDlg
{
// Construction
public:
   AccDistributionDlg(CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand);

// Dialog Data
   //{{AFX_DATA(AccDistributionDlg)
   enum
   {
      IDD = IDD_DISTRIBUTION
   };
   int m_rbInputMethod;
   //}}AFX_DATA
   virtual bool GetOverrideItemString(long lSubstituteId, const DString& ColumnKey, DString& strOut);
   //virtual bool ListViewControlFilter( DSTListCtrl& ListCtrl );


// Overrides
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(AccDistributionDlg)
public:
   virtual BOOL PreTranslateMessage(MSG* pMsg);
protected:
   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
   //}}AFX_VIRTUAL

// Implementation
protected:

   // Generated message map functions
   //{{AFX_MSG(AccDistributionDlg)
   virtual BOOL OnInitDialog();
   afx_msg void OnBtnBank();
   afx_msg void OnBtnAddress();
   afx_msg void OnBtnReset();
   afx_msg void OnBtnAdmindate();
   afx_msg void OnAccelFrom();
   afx_msg void OnAccelTo();
   afx_msg void OnBtnAddTo();
   afx_msg void OnBtnAddFrom();
   afx_msg void OnBtnDeleteFrom();
   afx_msg void OnBtnDeleteTo();
   afx_msg void OnBtnMoreFrom();
   afx_msg void OnBtnMoreTo();
   afx_msg void OnKillfocusCmbTransType();
   afx_msg void OnKillfocusEdtAddressCode();
   afx_msg void OnBtnHistorical();
   afx_msg void OnAllFundsMode();
   afx_msg void OnRbPercentage();
   afx_msg void OnRbDistribRate();
   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()

   void OnPostInitDialog();

   /**
      * This method should be overridden in the derived dialog if there is
      * OnOk processing to be done prior to base processing.  If PreOk returns
      * false, conditions should be set.
      * BaseMainDlg enforces its actions by making OnOk private.
      * @returns a bool with true = perform Ok, false = stop process - check
      *   conditions
      */
   virtual bool PreOk();

   virtual SEVERITY doInit();
   virtual bool doRefresh(
                         GenericInterface * /*rpGICaller*/, 
                         const I_CHAR * /*szOriginalCommand*/
                         );
   virtual void ControlUpdated( UINT controlID, const DString &strValue );
   virtual bool GetDataForControl( UINT controlID, DString &strValueOut,
                                   bool bFormatted, int index = 0 ) const; 
   virtual void DoListItemChanged(
                                 UINT listControlID,
                                 const DString &strKey,
                                 bool bIsNewItem, 
                                 bool bIsDummyItem
                                 );
   /**
      * This method should be overridden if there are any controls which the 
      * derived dialog supports outside of the base architecture.  This would
      * typicaly be if the derived dialog is supporting data not stored in the
      * parent process.  The data provided is in display format.
      * The default implementation is to return false - no override.
      * @param controlID - Control to get data for.
      * @param strValue - String with data to validate/save.
      * @param sevRtn - SEVERITY returned if override was true.
      * @param bFormatted - true = data in display format, false = data in
      * host format
      * @returns true if override provided for the specified control, false
      * otherwise
      */
   bool SetDataFromControl( UINT controlID, const DString &dstrValue,
                            bool bFormatted, SEVERITY &sevRtn, int iIndex );

   void OnClose();
   void PostCancel();
   void doDisableNonPermButtons();
   bool doDisablePermCheckButton(UINT nID);
   void showHideDistribRateControls ();
   void switchInputMethod (bool bOnRbInputMethod);
   void hideDistribRateControls ();
   bool isMoneyMarketFund(const DString &fundCode);

private:
   void GetDivChqAddrCode(DString& dstrAddrCode) const;
   void    GetMailingAddress(DString& strAddress) const;
   void    CalcTotalPercent( DString &dstrOutTotalPercent ) const;
   void    AdjustControlsToPaymentType( const DString &dstrPaymentType );
   void    ShowBankRelated( bool bShow );
   void    CalcTotalDistribRate( DString &dstrOutTotalDistribRate ) const; 
   void	   getLastIDRate( DString &dstrOutRecentDistribRate ) const;
   void    setRadioButton();
   LRESULT  OpenFundClassListDlg( WPARAM, LPARAM );

   HACCEL  m_hAccel;
   UINT    m_uiDialogItem;
   bool    m_bScreenClose;
   bool    m_bEsc;
   DString m_dstrCaller;
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/AccDistributionDlg.h-arc  $
 * 
 *    Rev 1.21   Nov 25 2010 13:58:22   jankovii
 * PET175778FN01 - Upstreaming Phase 2
 * 
 *    Rev 1.20   23 Feb 2009 15:29:14   kovacsro
 * P0155543_FN01_ Account Level Distribution 
 * 
 *    Rev 1.18   Feb 26 2008 14:59:16   daechach
 * In# 1160207 - Desktop distribution - Added 'More' button to account distribution screen.
 * 
 *    Rev 1.17   21 Dec 2007 14:43:42   kovacsro
 * PET2400FN01 - account level distribution instruction
 * 
 *    Rev 1.16   Feb 28 2004 16:14:24   HERNANDO
 * PET965 FN11 - Additional historical enhancement.  Added OnBtnHistorical.
 * 
 *    Rev 1.15   Jun 12 2003 15:48:40   popescu
 * Fix crash related to refresh the current list item during a set focus on the currency combo 
 * 
 *    Rev 1.14   Mar 21 2003 18:30:24   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.13   Oct 09 2002 23:55:26   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.12   Jul 12 2002 15:37:24   YINGBAOL
 * PTS10008890
 * 
 *    Rev 1.11   18 Apr 2002 15:27:28   HSUCHIN
 * Added support for Management Fee Rebate Distribution
 * 
 *    Rev 1.10   19 Mar 2002 13:44:24   PURDYECH
 * Added #pragma once include guard
 * Removed compile time "including..." message.
 * 
 *    Rev 1.9   Apr 16 2001 17:32:02   HERNANDO
 * Added ShowBankRelated fn.
 * 
 *    Rev 1.8   Dec 13 2000 14:33:40   KOVACSRO
 * 1. Modified DoListItemChanged.
 * 
 *    Rev 1.7   Jul 25 2000 16:15:14   HERNANDO
 * Sets parameters for Search Fund
 * 
 *    Rev 1.6   Jun 05 2000 11:58:58   HSUCHIN
 * code clean up
 * 
 *    Rev 1.5   Jun 05 2000 10:24:54   HSUCHIN
 * fund search dlg implement.  fund/class combo boxes removed.
 * 
 *    Rev 1.4   Apr 05 2000 09:42:48   DT24433
 * changed to use hasPermission
 * 
 *    Rev 1.3   Mar 20 2000 13:30:08   HSUCHIN
 * changed GetFundNumber to use DSTCommonFunction's version
 * 
 *    Rev 1.2   Mar 07 2000 16:23:34   HSUCHIN
 * added Fund Number for C2
 * 
 *    Rev 1.1   Feb 15 2000 18:59:02   MCNABBGL
 * changed comment format
 * 
 *    Rev 1.0   Feb 15 2000 11:01:04   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.24   Feb 03 2000 16:07:54   YINGZ
 * code clean up
 * 
 *    Rev 1.23   Jan 25 2000 16:42:06   YINGZ
 * add reset, refresh, admindate, focus etc
 * 
 *    Rev 1.22   Jan 22 2000 18:42:40   YINGZ
 * bug fix
 * 
 *    Rev 1.21   Jan 20 2000 10:32:50   PRAGERYA
 * For Zijian
 * 
 *    Rev 1.20   Jan 18 2000 18:11:36   PRAGERYA
 * For release
 * 
 *    Rev 1.19   Jan 11 2000 18:02:58   PRAGERYA
 * Bugs fixed
 * 
 *    Rev 1.18   Jan 10 2000 17:00:22   PRAGERYA
 * For Zijian
 * 
 *    Rev 1.17   Jan 10 2000 09:46:16   PRAGERYA
 * Again...
 * 
 *    Rev 1.16   Jan 09 2000 16:42:50   PRAGERYA
 * Made compilable!
 * 
 *    Rev 1.15   Jan 07 2000 20:33:44   PRAGERYA
 * For Mihai
 * 
 *    Rev 1.14   Dec 30 1999 12:40:48   YINGBAOL
 * split list sync
 * 
 *    Rev 1.13   Dec 22 1999 10:16:24   YINGBAOL
 * 
 *    Rev 1.12   Dec 13 1999 10:41:14   YINGBAOL
 * 
 *    Rev 1.11   Dec 07 1999 11:50:10   DT24433
 * changed to use DSTListCtrl parm in filter method
 * 
 */

#endif // ACCDISTRIBUTIONDLG_H
