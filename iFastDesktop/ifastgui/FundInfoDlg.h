#ifndef FUNDINFODLG_H
#define FUNDINFODLG_H
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
// ^FILE   : FundInfoDlg.h
// ^AUTHOR : Mihai Virgil Buzila
// ^DATE   : 03/30/99
//
// ^CLASS    : FundInfoDlg
// ^SUBCLASS : BaseMainDlg
//
// ^CLASS DESCRIPTION : Handles the code for the Fund Info screen
//
// -----------------------------------------------------------------------------
//
//******************************************************************************

#define LAST_NAME_COLUMN         0
#define FIRST_NAME_COLUMN        1
#define TELEPHONE_NUM_COLUMN     2
#define ADDRESS_COLUMN           3

#ifndef BASEMAINDLG_H
   #include <ifastgui\BaseMainDlg.h>
#endif
#ifndef DSTDATETIMECTRL_H
   #include <uibase\DSTDateTimeCtrl.h>
#endif
#include <uibase\ifdslistctrl.h>

class FundInfoDlg : public BaseMainDlg
{
public:
   /**
    * Standard dialog constructor for DSTC
    */
   FundInfoDlg(CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand);
private:
   //{{AFX_DATA(FundInfoDlg)
   enum
   {
      IDD = IDD_FUNDINFO1
   };
   //}}AFX_DATA


// Overrides
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(FundInfoDlg)
protected:
   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
   virtual BOOL PreTranslateMessage(MSG* pMsg);
   //}}AFX_VIRTUAL

// Implementation
protected:
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
   virtual bool doRefresh( GenericInterface * /*rpGICaller*/, 
                           const I_CHAR * /*szOriginalCommand*/ );

   virtual bool filterListColumn(const BFFieldId &idSubstitute, const DString& dstrTag);

   virtual bool GetDataForControl(  UINT controlID,
                                    DString &strValueOut,
                                    bool bFormatted,
                                    int index       ) const;   
   virtual bool SetDataFromControl(  UINT controlID,
                                     const DString &strValue,
                                     bool bFormatted,
                                     SEVERITY &sevRtn,
                                     int index );

   void ControlUpdated( UINT controlID, const DString &strValue );

   virtual bool GetOverrideItemString(long lSubstituteId, const DString& ColumnKey, DString& strOut );

   // Generated message map functions
   //{{AFX_MSG(FundInfoDlg)
   virtual BOOL OnInitDialog();
   afx_msg void OnBtnMore();
   afx_msg void OnBtnSearch();
   afx_msg void OnBtnAdminDates();
   afx_msg void OnBtnMgmtDetails();
   afx_msg void OnBtnPriceAdditional();
   afx_msg void OnBtnUnitVal();
   afx_msg void OnBtnFactors();
   afx_msg void OnChkAllFunds();
   afx_msg void OnChkMultiDates();
   afx_msg void OnBtnValuationDetails();
   //}}AFX_MSG
   virtual void OnPostInitDialog();

   DECLARE_MESSAGE_MAP()
   virtual void DoListItemChanged (UINT listControlID, const DString &strKey, bool bIsNewItem, bool bIsDummyItem);

private:

   LRESULT OpenFundClassListDlg( WPARAM, LPARAM );

   DString m_FundCode;
   DString m_dstrUFactorCodes;
   bool m_bAllFundsChecked;
   bool m_bMultiDatesChecked;

   typedef std::map< DString, short > MAPFACTORCODES;
   typedef MAPFACTORCODES::iterator MAPFACTORCODES_ITER;
   MAPFACTORCODES m_mapFactorCodes;
   void enableValuationDetailsButton();
};

#endif // FundInfoDlg_H

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/FundInfoDlg.h-arc  $
 * 
 *    Rev 1.8   Jan 18 2012 17:15:40   wp040027
 * P0188394_Performance Fees - Launching valuation dtl/Sharelot Screens
 * 
 *    Rev 1.7   Sep 09 2004 11:53:26   HERNANDO
 * PET1117 FN22 - WKN & ISIN Enhancement.
 * 
 *    Rev 1.6   Nov 20 2003 16:31:58   AGUILAAM
 * PET859_FN17: added factors screen - daily equalization.
 * 
 *    Rev 1.5   Mar 21 2003 18:37:04   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.4   Oct 09 2002 23:55:42   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.3   Mar 20 2000 14:34:32   HSUCHIN
 * changed GetFundNumber to use the one defined in DSTCommon Functions
 * 
 *    Rev 1.2   Mar 13 2000 17:27:44   HSUCHIN
 * C2 sync up
 * 
 *    Rev 1.1   Feb 15 2000 18:59:26   MCNABBGL
 * changed comment format
 * 
 *    Rev 1.0   Feb 15 2000 11:01:16   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.10   Feb 02 2000 14:10:08   DT24433
 * removed ok/cancel
 * 
 *    Rev 1.9   Sep 24 1999 14:25:08   YINGZ
 * make it for c1
 * 
 *    Rev 1.8   Sep 24 1999 09:50:04   YINGBAOL
 * 
 *    Rev 1.7   Aug 11 1999 17:51:18   BUZILA
 * deleted    #include "combobase.h"
 * 
 *    Rev 1.6   Jul 28 1999 17:20:46   BUZILA
 * Changed NAV labels
 * 
 *    Rev 1.5   Jul 20 1999 17:00:20   BUZILA
 * fixed DateTimePicker refresh problem
 * 
 *    Rev 1.4   Jul 16 1999 10:53:20   BUZILA
 * 3
 * 
 *    Rev 1.3   Jul 16 1999 10:23:16   BUZILA
 * 1
 * 
 *    Rev 1.2   Jul 15 1999 13:22:02   BUZILA
 * changed Mgmt Details
 * 
 *    Rev 1.1   Jul 08 1999 10:05:16   SMITHDAV
 * Modify revision history commaent format to old
 * style comment -- I can't seem to get new style comments to work.
 *
 */
