#pragma once
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
// ^FILE   : ConfirmationDlg.h
// ^AUTHOR : Mihai Virgil Buzila
// ^DATE   : 03/30/99
//
// ^CLASS    : ConfirmationDlg
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

#include <bfsessn\bfawdsession.hpp>
#include <ifastgui\basemaindlg.h>
#include <uibase\listctrl.h>
#include <afxdtctl.h>
#include <uibase\combobase.h>

class BFAwdInterface;

class ConfirmationDlg : public BaseMainDlg
{
public:
   /**
    * Standard dialog constructor for DSTC
    */
   ConfirmationDlg(CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand);
// Dialog Data
   //{{AFX_DATA(ConfirmationDlg)
   enum
   {
      IDD = IDD_CONFIRMATION
   };
   ListViewControl   m_lvTransactions;
   CButton  m_usingAWD;
   CEdit m_DestAddress;
   ListViewControl   m_lstConfirmation;
   ListViewControl   m_lstFund;
   CString  m_ConfirmationAge;
   CString  m_DeliveryMethod;
   CString  m_CancelledUser;
   CString  m_CancelledDate;
   CString  m_BankDate;
   CString  m_TransNo;
   CString  m_BankAcct;
   //}}AFX_DATA


// Overrides
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(ConfirmationDlg)
protected:
   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
   //}}AFX_VIRTUAL

// Implementation
protected:

   // Generated message map functions
   //{{AFX_MSG(ConfirmationDlg)
   virtual BOOL OnInitDialog();
   afx_msg void OnChkAwdOrRemark();
   afx_msg void OnChkUpdAllCIFRelated();
   afx_msg void OnRbEnd();
   afx_msg void OnRbGetWork();
   afx_msg void OnRbRefresh();
   afx_msg void OnRbNewSearch();
   afx_msg void OnSelchangeCbWuUnit();
   afx_msg void OnSelchangeCbWuWkType();
   afx_msg void OnRbUpdateExisting();
   afx_msg void OnRbCreateNew();
   afx_msg void OnRbCloneUpdate ();
   afx_msg void OnRbUpdateOrig ();
   afx_msg void OnRbNone();
   afx_msg void OnEnChangeRemarkComment();
   afx_msg void OnBtnWrkObject();
//	afx_msg void OnKillFocusEditRemarkComment();

   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()

	   virtual void OnPostInitDialog(){};

   /**
     * Get parameters from InterProcessData.
     * @returns SEVERITY, check conditions if > NO_SEVERITY
     */
//   virtual SEVERITY doInit();
   virtual bool PreOk();
   virtual void PostOk( bool /* bOkStatus */ );
   virtual SEVERITY init2();
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
//###temporary fix for demo mode
   bool isDemoMode();

   // always allow cancel
   virtual bool canCancel()
   {
      return(true);
   }

   void doPaste( UINT controlID );

private:

   void EnableAWD (bool update);
   void UpdateComment();
   void SetComboItem(int id, DString item);
   void SetAWDUpdate();
   void ConfigureAWDControls();
   void GetBusinessArea( const DString &dstrManagementCompany, DString &dstrBusinessArea );
   void displayCloneControls(bool bUsingAwd);
   void initControls();
   void updateStatusList();

   typedef std::map< DString, int > COLUMNMAP;
   typedef COLUMNMAP::iterator COLUMNMAP_ITER;
   COLUMNMAP AwdColumnMap;

   BFAwdSession    *m_pAwdSession;
   bool            m_bCommentAccessible;
   bool            m_bAwdDisabled;
   bool            m_bCreateNew;
   DString         m_dstrAWDEvent;
   DString         m_dstrCalledFrom;
   DString         m_dstrCreatingAcct;
   BFAwdInterface  *m_pAwdInterface;
   const DString*  remarkListkey;
   bool            m_bFromRemarks;
   DString         m_dstrDispRebook;
   DString         m_dstrBulkCancel;
   DString         m_dstrBatchNum;
   bool            m_bRefreshStatusList;
   int             m_FormatRemarksCount;
   DString         m_InvokedBrowserScreen;
   DString         m_CommitParentDataGroups;
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/ConfirmationDlg.h-arc  $
 * 
 *    Rev 1.37   Aug 10 2012 12:21:16   popescu
 * IN#3051211 - P0179630 FN01 - FATCA - Acct Ownership Allocation option is not refreshed
 * 
 *    Rev 1.36   Jan 14 2011 16:46:44   dchatcha
 * PET0165541 FN03 - QESI Phase3, refresh account detail screen after there is update from Govt Amendment screen.
 * 
 *    Rev 1.35   27 May 2009 10:23:18   popescu
 * Autobatch - passed the name of the batch to reebok functionality
 * 
 *    Rev 1.34   24 Oct 2008 15:31:48   kovacsro
 * IN#1403926 - R87 AWD issues regarding remarks formatting
 * 
 *    Rev 1.33   16 May 2008 13:29:26   kovacsro
 * IN#1223298 - formatting remarks
 * 
 *    Rev 1.32   05 May 2008 14:51:30   kovacsro
 * PET2255-FN47 New LIF - moved 'Gain/Loss' from RIF screen into COA
 * 
 *    Rev 1.31   04 Mar 2008 15:25:24   kovacsro
 * IN#1118130 - check AWD comments by default, whenever there's an active AWD object around or the user creates a new AWD object
 * 
 *    Rev 1.30   01 Feb 2008 09:06:20   kovacsro
 * IN#1118094&1114586 - filtering the status list on the queue, bussArea and workType for AWD
 * 
 *    Rev 1.29   16 Jan 2008 09:31:28   kovacsro
 * IN#1103220 - fixed trimming the comments when the size is greater than 700
 * 
 *    Rev 1.28   17 Jul 2007 15:19:10   popescu
 * GAP 6 CIF - AIM
 * 
 *    Rev 1.27   May 05 2006 17:19:12   popescu
 * Incident# 613476 - disable the GetWork and End buttons if user chooses clone and update.
 * 
 *    Rev 1.26   Nov 24 2005 16:22:02   porteanm
 * PET1286 FN01 - Bulk Cancellation.
 * 
 *    Rev 1.25   Aug 17 2005 11:37:08   popescu
 * Incident 377523 - fixed the refresh error 'Dilution Records already exist' after user cancels and rebooks a transaction. Correctly removed the trans cancelation update data at the worksession level.
 * 
 *    Rev 1.24   Jul 08 2005 09:41:28   Yingbaol
 * PET1235,FN01:Transaction cancellation rebook
 * 
 *    Rev 1.23   Jul 19 2004 09:48:36   YINGBAOL
 * PTS10030071: Change the sequence of populating data.
 * 
 *    Rev 1.22   May 27 2004 17:20:58   HERNANDO
 * PET1017 FN01- Remarks-Confirmation change.   Allow Confirmation to view the Added Remark and allow copying it to the AWD object.
 * 
 *    Rev 1.21   May 11 2004 10:54:42   YINGBAOL
 * PET1017:fixed display control while user does not use AWD
 * 
 *    Rev 1.20   May 04 2004 12:13:02   YINGBAOL
 * PET1017:Implement clone function
 * 
 *    Rev 1.19   Mar 31 2004 16:29:22   YINGBAOL
 * PTS10028705: reimplement update shareholder remarks logic.
 * 
 *    Rev 1.18   Jan 12 2004 14:57:46   YINGBAOL
 * PET987: convert to DSTCAWDInterface
 * 
 *    Rev 1.17   Dec 23 2003 08:38:40   HERNANDO
 * PET987 - Added a few functions and variables for this implementation.
 * 
 *    Rev 1.16   Oct 03 2003 11:05:52   VADEANUM
 * PTS 10022399 - Wrong Account # assigned to Remark - replaced RefAccount with AccountNum in order to have the fieldid picked up in DSTCWorkSession::commit() after including the field in the transaction key
 * 
 *    Rev 1.15   Mar 21 2003 18:34:42   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.14   Oct 09 2002 23:55:36   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.13   May 28 2002 12:19:50   PURDYECH
 * BFData Implementation - Phase II
 * 
 *    Rev 1.12   22 May 2002 19:15:54   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.11   Nov 13 2001 14:07:38   HERNANDO
 * Added m_pAwdInterface.
 * 
 *    Rev 1.10   04 Jul 2001 16:45:54   YINGZ
 * implement cancel to give user warning when there are updates
 * 
 *    Rev 1.9   Jun 06 2001 12:01:54   DINACORN
 * temporary fix for demo mode - added isDemoMode()
 * 
 *    Rev 1.8   Jan 03 2001 10:41:08   ZHANGCEL
 * House keeping and new varable added
 * 
 *    Rev 1.7   Oct 11 2000 14:28:02   KOVACSRO
 * Added m_strCalledFrom.
 * 
 *    Rev 1.6   Sep 26 2000 17:22:06   HERNANDO
 * Added AWD Disabled flag.
 * 
 *    Rev 1.5   Sep 20 2000 17:36:08   HERNANDO
 * Added AWD Event member variable.
 * 
 *    Rev 1.4   Aug 25 2000 10:43:22   YINGBAOL
 * add trade screen to NASU flow
 * 
 *    Rev 1.3   Aug 24 2000 15:35:44   HERNANDO
 * Added flag; reflects source revision.
 * 
 *    Rev 1.2   Aug 14 2000 15:24:04   HERNANDO
 * Revised
 * 
 *    Rev 1.1   Feb 15 2000 18:59:18   MCNABBGL
 * changed comment format
 * 
 *    Rev 1.0   Feb 15 2000 11:01:12   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.10   Jan 21 2000 14:36:38   HSUCHIN
 * kills worksession when there is errors committing transactions and some awd stuff
 * 
 *    Rev 1.9   Jan 16 2000 16:58:10   POPESCUS
 * prepared for refresh and cleaned up the code
 * 
 *    Rev 1.8   07 Jan 2000 14:09:34   HSUCHIN
 * latest infra changes and remark updates
 * 
 *    Rev 1.7   04 Jan 2000 17:22:02   HSUCHIN
 * temp check in for dialog changes
 * 
 *    Rev 1.6   23 Dec 1999 15:52:12   HSUCHIN
 * sync up with latest bfbase stuff.  Confirm End call now ends work session by posting a message to dstcview (temp solution).
 * 
 *    Rev 1.5   Nov 25 1999 10:37:22   HSUCHIN
 * support canadian market
 * 
 *    Rev 1.4   Nov 24 1999 19:06:10   HSUCHIN
 * transaction builder called on preok.
 * 
 *    Rev 1.3   Nov 22 1999 15:24:34   HSUCHIN
 * redesigned and OG usage.
 * 
 *    Rev 1.2   Jul 27 1999 16:06:22   BUZILA
 * Increment M2
 * 
 *    Rev 1.1   Jul 08 1999 10:04:52   SMITHDAV
 * Modify revision history comment format to old
 * style comment -- I can't seem to get new style comments to work.
 *
 */
