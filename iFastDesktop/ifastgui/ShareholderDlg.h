#ifndef SHAREHOLDERDLG_H
#define SHAREHOLDERDLG_H
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
// ^FILE   : ShareholderDlg.h
// ^AUTHOR : Mihai Virgil Buzila
// ^DATE   : 03/30/99
//
// ^CLASS    : ShareholderDlg
// ^SUBCLASS : BaseMainDlg
//
// ^CLASS DESCRIPTION : Handles the code for the Fund Info screen
//
// -----------------------------------------------------------------------------
//
//******************************************************************************

#ifndef BASEMAINDLG_H
   #include <ifastgui\BaseMainDlg.h>
#endif

class ShareholderDlg : public BaseMainDlg
{
public:
   /**
    * Standard dialog constructor for DSTC
    */
   ShareholderDlg(CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand);
// Dialog Data
   //{{AFX_DATA(ShareholderDlg)
   enum
   {
      IDD = IDD_SHAREHOLDER
   };
   //}}AFX_DATA


// Overrides
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(ShareholderDlg)
protected:
   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
   //}}AFX_VIRTUAL

// Implementation
protected:
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
   /**
     * Get parameters from InterProcessData.
     * @returns SEVERITY, check conditions if > NO_SEVERITY
     */
   virtual SEVERITY doInit();
   /**
     * This method should be overridden in the derived dialog if there is
     * OnOk processing to be done after the base processing.  Note that the OnOk
     * processing can no longer be "cancelled" at this point.  BaseMainDlg 
     * enforces its actions by making OnOk private.
     * @param bCancelStatus - true = Ok successful, false = Ok failed
     */
   virtual void PostOk(
                      bool /* bOkStatus */
                      );
   // Generated message map functions
   //{{AFX_MSG(ShareholderDlg)
   virtual BOOL OnInitDialog();
   afx_msg void OnBtnAdmDates();
   afx_msg void OnBtnHistorical();
   //}}AFX_MSG
   virtual void OnPostInitDialog();

   virtual void ControlUpdated( UINT controlID, const DString &strValue );

   DECLARE_MESSAGE_MAP()

   private:
   DString m_dstrCreatingShareholder;
   DString m_dstrMarket;
   bool _bManualShr;
   bool _bShrCreated;

   void enableControls();
   void adjustToProcessType();
   void displayGroupRelated();

};


#endif // ShareholderDlg_H
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/ShareholderDlg.h-arc  $
 * 
 *    Rev 1.7   Feb 28 2004 16:09:20   HERNANDO
 * PET965 FN11 - Additional historical enhancement.  Added OnBtnHistorical.
 * 
 *    Rev 1.6   Mar 21 2003 18:40:56   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.5   Oct 09 2002 23:56:14   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.4   Nov 14 2001 15:34:16   YINGBAOL
 * code clean up
 * 
 *    Rev 1.3   Oct 25 2001 15:33:44   YINGBAOL
 * add displayGrroupRelated() method
 * 
 *    Rev 1.2   May 02 2001 10:00:08   OLTEANCR
 * added controlUpdated(..), _bManualShr, _bShrCreated
 * 
 *    Rev 1.1   Feb 15 2000 18:59:44   MCNABBGL
 * changed comment format
 * 
 *    Rev 1.0   Feb 15 2000 11:01:24   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.21   Jan 19 2000 15:32:06   POPESCUS
 * fixes in Shareholder
 * 
 *    Rev 1.20   Dec 09 1999 19:26:02   DT24433
 * various changes
 * 
 *    Rev 1.19   Nov 29 1999 11:26:52   POPESCUS
 * Fixes in NASU flow
 * 
 *    Rev 1.18   Nov 25 1999 17:08:50   POPESCUS
 * 
 *    Rev 1.17   Nov 23 1999 18:05:50   POPESCUS
 * NASU flow
 * 
 *    Rev 1.16   Nov 09 1999 18:41:18   DT24433
 * removed Ok/Cancel
 * 
 *    Rev 1.15   Nov 08 1999 15:20:28   ZHANGCEL
 * modify GetDataForControl
 * 
 *    Rev 1.12   Oct 27 1999 10:13:22   ZHANGCEL
 * New shareholder mechanism
 * 
 *    Rev 1.11   Oct 06 1999 17:15:04   PRAGERYA
 * Market-specific stuff
 * 
 *    Rev 1.10   Sep 24 1999 10:13:58   PRAGERYA
 * "Milestone" check in
 * 
 *    Rev 1.9   Aug 18 1999 12:22:54   PRAGERYA
 * Substitute lists in combo boxes
 * 
 *    Rev 1.8   Aug 08 1999 19:34:06   PRAGERYA
 * All in!
 * 
 *    Rev 1.7   Aug 04 1999 09:40:52   PRAGERYA
 * Implementing dialog
 * 
 *    Rev 1.6   Jul 30 1999 17:28:58   PRAGERYA
 * Coded to the level of Incr1
 * 
 *    Rev 1.5   Jul 27 1999 14:07:28   BUZILA
 * fix
 * 
 *    Rev 1.4   Jul 23 1999 15:31:44   SMITHDAV
 * m21
 * 
 *    Rev 1.1   Jul 08 1999 10:05:54   SMITHDAV
 * Modify revision history commaent format to old
 * style comment -- I can't seem to get new style comments to work.
 *
 */
