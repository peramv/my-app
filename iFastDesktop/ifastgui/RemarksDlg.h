#ifndef REMARKSDLG_H
#define REMARKSDLG_H
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
// ^FILE   : RemarksDlg.h
// ^AUTHOR : Yakov Prager
// ^DATE   : 3/99
//
// ^CLASS    : RemarksDlg
// ^SUBCLASS : BaseMainDlg
//
// ^CLASS DESCRIPTION : Handles the code for the Remarks dialog
//
//******************************************************************************

#ifndef BASEMAINDLG_H
   #include <ifastgui\BaseMainDlg.h>
#endif

#if _MSC_VER > 1000
   #pragma once
#endif

class RemarksDlg : public BaseMainDlg
{
// Construction
public:
   RemarksDlg(CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand);
   ~RemarksDlg();

// Dialog Data
   //{{AFX_DATA(RemarksDlg)
   enum
   {
      IDD = IDD_REMARKS
   };
   CButton m_BtnMore;
   BOOL m_bShareHolderRemarks;
   //}}AFX_DATA

// Overrides
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(RemarksDlg)
   virtual BOOL PreTranslateMessage(MSG* pMsg);
protected:
   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
   //}}AFX_VIRTUAL
	
// Implementation
protected:
   // Generated message map functions
   //{{AFX_MSG(RemarksDlg)
   virtual BOOL OnInitDialog();
   afx_msg void OnBtnAdmDates();
   afx_msg void OnBtnChange();
   afx_msg void OnBtnAdd();
   afx_msg void OnBtnDelete();
   afx_msg void OnAccelRemarkslist();
   afx_msg void OnAccelDetails();
   afx_msg void OnBtnMore();	
   afx_msg void OnEnChangeRemarkComment();
   afx_msg void OnChkShareHolderRemarks();
   afx_msg void OnSelRemarkFilter();
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
                         GenericInterface *rpGICaller, 
                         const I_CHAR *szOriginalCommand
                         );
   virtual void ControlUpdated( UINT controlID, const DString &strValue );

   void doPaste( UINT controlID );
   bool ListViewControlFilter(long lSubstituteId, const DString *strKey);
   bool doDisablePermCheckButton(UINT nID);  

private:
   DString s_Name;
   HACCEL m_hAccel;
   void setAccountNum();
   int m_FormatRemarksCount;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // REMARKSDLG_H

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/RemarksDlg.h-arc  $
 * 
 *    Rev 1.13   24 Oct 2008 10:22:50   kovacsro
 * 1399970 - GL-1254 Desktop Screen (Remarks - odd character )
 * 
 *    Rev 1.12   Mar 26 2004 12:52:30   VADEANUM
 * PTS 10028335 - Inconsistent AccountNum behaviour.
 * 
 *    Rev 1.11   Oct 03 2003 12:24:32   VADEANUM
 * PTS 10022545 - Record created when no Remark entered on the Remarks dialog - assign the AccountNum only when a Comment si entered.
 * 
 *    Rev 1.10   Jul 30 2003 11:27:24   FENGYONG
 * CIBC enhancement PET809_FN46
 * 
 *    Rev 1.9   Mar 21 2003 18:39:46   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.8   Oct 09 2002 23:55:50   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.7   27 Mar 2001 16:52:54   KOVACSRO
 * perm. check stuff
 * 
 *    Rev 1.6   01 Mar 2001 16:43:10   KOVACSRO
 * Modifications for permission check.
 * 
 *    Rev 1.5   Jan 17 2001 09:47:34   KOVACSRO
 * CheckPermision overwritten.
 * 
 *    Rev 1.4   Dec 13 2000 14:47:02   KOVACSRO
 * odified DoListItemChanged.
 * 
 *    Rev 1.3   Dec 05 2000 17:20:54   KOVACSRO
 * AddeddoListItemChanged for  new item permission logic.
 * 
 *    Rev 1.2   Jul 26 2000 17:57:50   HUDAVID
 * added 'More' button
 * 
 *    Rev 1.1   Feb 15 2000 18:59:38   MCNABBGL
 * changed comment format
 * 
 *    Rev 1.0   Feb 15 2000 11:01:22   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.8   Dec 14 1999 12:37:30   DT24433
 * misc cleanup
 * 
 *    Rev 1.7   Dec 10 1999 10:26:10   HSUCHIN
 * added accelerators
 * 
 *    Rev 1.6   Nov 19 1999 16:41:48   YINGZ
 * make it work with new controls
 * 
 *    Rev 1.5   Nov 13 1999 14:12:46   HSUCHIN
 * added add and delete functionality
 * 
 *    Rev 1.4   Nov 10 1999 11:19:22   HSUCHIN
 * modified to update transactions and using the new basedlg and controls
 * 
 *    Rev 1.3   Sep 22 1999 17:12:06   VASILEAD
 * modified to support C1 requirements
 * 
 *    Rev 1.2   Aug 11 1999 15:10:30   BUZILA
 * fix
 * 
 *    Rev 1.1   Jul 08 1999 10:05:48   SMITHDAV
 * Modify revision history commaent format to old
 * style comment -- I can't seem to get new style comments to work.
 *
 */
