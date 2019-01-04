
#ifndef TRANSACTIONALLOCATIONSDLG_H
#define TRANSACTIONALLOCATIONSDLG_H
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
//    Copyright 1999 by DST Systems, Inc.
//
//******************************************************************************
//
// ^FILE   : TransactionAllocationsDlg.h
// ^AUTHOR : Yakov Prager
// ^DATE   : 09/26/99
//
// ^CLASS    : TransactionAllocationsDlg
// ^SUBCLASS : BaseMainDlg
//
// ^CLASS DESCRIPTION : Handles the code for the TransactionAllocationsDlg dialog
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

//#ifndef ALLOCATIONSHELPER_H
//	#include "AllocationsHelper.h"
//#endif

#if _MSC_VER > 1000
   #pragma once
#endif // _MSC_VER > 1000

class TransactionAllocationsDlg : public BaseMainDlg
{
// Construction
public:
   TransactionAllocationsDlg(CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand);

// Dialog Data
   //{{AFX_DATA(TransactionAllocationsDlg)
   enum
   {
      IDD = IDD_TRANSACTION_ALLOCATIONS
   };
   //}}AFX_DATA

// Overrides
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(TransactionAllocationsDlg)
public:
   virtual BOOL PreTranslateMessage(MSG* pMsg);
protected:
   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
   //}}AFX_VIRTUAL

// Implementation
protected:

   // Generated message map functions
   //{{AFX_MSG(TransactionAllocationsDlg)
   afx_msg void OnAccelAllocType();
   afx_msg void OnAccelFund();
   virtual BOOL OnInitDialog();
   afx_msg void OnBtnSplitCom();
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

   void DoListItemChanged(
                         UINT listControlID,
                         const DString &strKey, 
                         bool bIsNewItem , 
                         bool bIsDummyItem
                         );

//###temporary fix for demo mode
   bool isDemoMode();

private:
   void SetDlgCaption();

   HACCEL m_hAccel;
   DString m_dstrMarket;
   DString m_dstrSettledCurrency;
   DString _dstrParent;
   DString _dstrParentCurKey;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/TransactionAllocationsDlg.h-arc  $
 * 
 *    Rev 1.11   Aug 20 2003 17:49:02   popescu
 * Refresh on the dialog did not work,this is not part of a PTS but impacts the inquiry of split commission
 * 
 *    Rev 1.10   Mar 21 2003 18:41:54   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.9   Oct 09 2002 23:56:16   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.8   Sep 25 2002 15:43:18   KOVACSRO
 * cleanup.
 * 
 *    Rev 1.7   19 Mar 2002 13:44:58   PURDYECH
 * Added #pragma once include guard
 * Removed compile time "including..." message.
 * 
 *    Rev 1.6   Jun 06 2001 12:03:38   DINACORN
 * temporary fix for demo mode - added isDemoMode()
 * 
 *    Rev 1.5   Mar 23 2001 12:33:52   HSUCHIN
 * disable splitcomm btn when there is not split commission
 * 
 *    Rev 1.4   Mar 22 2001 14:12:48   HSUCHIN
 * hook up to split commission
 * 
 *    Rev 1.3   Mar 18 2001 12:19:14   YINGZ
 * make it work with new account/fund level allocation structure
 * 
 *    Rev 1.2   Mar 18 2001 11:09:04   YINGZ
 * change field names
 * 
 *    Rev 1.1   Feb 15 2000 18:59:50   MCNABBGL
 * changed comment format
 * 
 *    Rev 1.0   Feb 15 2000 11:01:26   SMITHDAV
 * Initial revision.
// 
//    Rev 1.4   Feb 02 2000 15:49:02   DT24433
// removed ok/cancel, added revision log section
 * 
 */
