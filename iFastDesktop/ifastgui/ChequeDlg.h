#ifndef CHEQUEDLG_H
#define CHEQUEDLG_H
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
// ^FILE   : ChequeDlg.h
// ^AUTHOR : Mihai Virgil Buzila
// ^DATE   : 03/30/99
//
// ^CLASS    : ChequeDlg
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

class ChequeDlg : public BaseMainDlg
{
public:
   /**
    * Standard dialog constructor for DSTC
    */
   ChequeDlg(CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand);
private:
   //{{AFX_DATA(ChequeDlg)
   enum
   {
      IDD = IDD_CHEQUE
   };
   CButton m_btnAdminDates;
   CButton m_btnTransactions;
   //}}AFX_DATA

// Overrides
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(ChequeDlg)
protected:
   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
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
   // Generated message map functions
   //{{AFX_MSG(ChequeDlg)
   virtual BOOL OnInitDialog();
   afx_msg void OnBtnAdmDates();
   afx_msg void OnBtnTrans();
   afx_msg void OnBtnHistorical();
   afx_msg void OnBtnMore ();
   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()

   virtual void OnPostInitDialog();

   bool GetOverrideItemString( long lSubstituteId, const DString &dstrColumnKey, DString &dstrOut );
   void DoPreListItemChanged( UINT listControlID, const DString &strKey, bool bIsNewItem, bool bIsDummyItem );
   bool ListViewControlFilter( long lSubstituteId, const DString *strKey );

   /**
     * This method may be overridden to provide dialog specific handling
     * when list selection changes.  Note that the item will already be
     * the current item in the list (both list control and list container) and
     * the associated controls will be loaded.  This call does occur prior to
     * any loading of sub-lists.  If you need to affect the loading of controls
     * (connect/disconnect associated controls) for this list use
     * DoPreListItemChanged instead.
     * Avoid doing list control operations during this method.
     * @param listControlID - Control ID of list changing selection
     * @param strKey - reference to string key for item.
    * @param bIsNewItem 
    * @param bIsDummyItem
     */
   void DoListItemChanged(
                                 UINT listControlID,
                                 const DString &strKey,
                                 bool bIsNewItem ,
                                 bool bIsDummyItem
                                 );
private:

   DString m_dstrAccountNum,
   m_dstrSelectedChequeKey;
};

#endif // ChequeDlg_H

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/ChequeDlg.h-arc  $
 * 
 *    Rev 1.14   08 Jan 2009 14:31:20   kovacsro
 * IN#1521695 - GL #1541 - Users received an internal problem error msg from Desktop
 * 
 *    Rev 1.13   Sep 11 2008 16:34:14   jankovii
 * PET 5517 FN71 Stale Cheque.
 * 
 *    Rev 1.12   Sep 09 2008 16:25:04   jankovii
 * PET 5517 FN71 Stale Cheque.
 * 
 *    Rev 1.11   Mar 21 2003 18:34:14   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.10   Oct 09 2002 23:55:34   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.9   Sep 25 2002 14:47:58   HERNANDO
 * Bug fix - Display details list; clean-up, minor fixes.
 * 
 *    Rev 1.8   Sep 13 2002 20:25:10   HERNANDO
 * PTS 10009611 - Added DoPreListItemChanged to clear Address Edit.
 * 
 *    Rev 1.7   Sep 06 2001 14:07:18   ZHANGCEL
 * Added second parameter in ListViewControlFilter()
 * 
 *    Rev 1.6   Dec 13 2000 14:40:00   KOVACSRO
 *  Modified DoListItemChanged.
 * 
 *    Rev 1.5   Jun 09 2000 11:47:32   BUZILA
 * cheque fix
 * 
 *    Rev 1.4   Mar 24 2000 15:41:38   ZHANGCEL
 * C2 changed added
 * 
 *    Rev 1.3   Mar 20 2000 14:19:52   HSUCHIN
 * change GetFundNumber to use the one defined in DSTCommonFunctions
 * 
 *    Rev 1.2   Mar 08 2000 18:20:12   HSUCHIN
 * C2 changes added, but still needs to be converted to use new infra
 * 
 *    Rev 1.1   Feb 15 2000 18:59:16   MCNABBGL
 * changed comment format
 * 
 *    Rev 1.0   Feb 15 2000 11:01:10   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.5   Feb 02 2000 14:37:26   DT24433
 * removed ok/cancel
 * 
 *    Rev 1.4   Oct 24 1999 11:15:18   POPESCUS
 * Erased the remarks button
 * 
 *    Rev 1.3   Aug 09 1999 10:16:36   VASILEAD
 * ?
 * 
 *    Rev 1.2   Jul 19 1999 16:34:16   POPESCUS
 * Fixed user security access to the remarks screen
 * 
 *    Rev 1.1   Jul 08 1999 10:04:48   SMITHDAV
 * Modify revision history commaent format to old
 * style comment -- I can't seem to get new style comments to work.
 *
 */
