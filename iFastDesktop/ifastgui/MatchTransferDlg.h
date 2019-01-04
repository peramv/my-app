
#ifndef MATCHTRANSFERDLG_H
#define MATCHTRANSFERDLG_H
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
// ^FILE   : MatchTransferDlg.h
// ^AUTHOR : Celia Zhang
// ^DATE   : August 9, 2001
//
// ^CLASS    : MatchTransferDlg
// ^SUBCLASS : BaseMainDlg
//
// ^CLASS DESCRIPTION : 
//
//*****************************************************************************
/////////////////////////////////////////////////////////////////////////////
// MatchTransferDlg dialog


#ifndef BASEMAINDLG_H
   #include <ifastgui\BaseMainDlg.h>
#endif


class MatchTransferDlg : public BaseMainDlg
{
// Construction
public:
   MatchTransferDlg(CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand);

// Dialog Data
   //{{AFX_DATA(MatchTransferDlg)
   enum
   {
      IDD = IDD_MATCHTRANSFER
   };
   // NOTE: the ClassWizard will add data members here
   //}}AFX_DATA


// Overrides
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(MatchTransferDlg)
protected:
   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
   //}}AFX_VIRTUAL

// Implementation
protected:

   // Generated message map functions
   //{{AFX_MSG(MatchTransferDlg)
   virtual BOOL OnInitDialog();
   afx_msg void OnBtnBrowse();
   afx_msg void OnBtnAdmDates();
   afx_msg void OnBtnClose();
   afx_msg void OnDblclkLvAttributes(NMHDR* pNMHDR, LRESULT* pResult);
   afx_msg void OnClickLvAttributes(NMHDR* pNMHDR, LRESULT* pResult);
   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()


   /**
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

   virtual bool GetDataForControl(
                                 UINT controlID,
                                 DString &strValueOut,
                                 bool bFormatted,
                                 int index
                                 ) const;

   virtual bool GetOverrideItemString(
                                     long lSubstituteId, 
                                     const DString& ColumnKey, 
                                     DString& strOut );

   virtual bool ListViewControlFilter(
                                     const BFFieldId &idSubstitute, 
                                     const DString *strKey = NULL  );

   void OnBtnGetAccount();
   
private:
   // private member functions
   void AdjustControl();
   void setTitleBar ( );
   int  WhichDlgShouldBeLaunchedTrans( DString dstrCurSelKey );
   bool DisplayCodeDesc( const BFFieldId &idCode, const BFFieldId &idDesc, DString &strOut );
   bool DisplayItem( const BFFieldId &idField );
   // private member data  
   DString m_dstrAccountNumber;
   DString m_dstrShareHoldNum;
   DString m_dstrTransId;
   DString m_dstrEntityId;
   DString _InquiryOnly;
   bool Ignore;
   E_PROCESSTYPE procType;

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

//*****************************************************************************
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/MatchTransferDlg.h-arc  $
//
//   Rev 1.8   May 11 2004 14:24:52   FENGYONG
//PET1046 FN1 - transfer-switch -Rel57
//
//   Rev 1.7   Mar 01 2004 09:35:32   HERNANDO
//PTS10027400 - Changed function signature.
//
//   Rev 1.6   Mar 21 2003 18:38:48   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.5   Mar 03 2003 14:09:16   KOVACSRO
//Added InquiryOnly
//
//   Rev 1.4   Oct 09 2002 23:55:48   PURDYECH
//PVCS Database Conversion
//
//   Rev 1.3   Aug 29 2002 12:57:24   SMITHDAV
//ClientLocale and typed field changes.
//
//   Rev 1.2   19 Mar 2002 13:44:46   PURDYECH
//Added #pragma once include guard
//Removed compile time "including..." message.
//
//   Rev 1.1   Sep 07 2001 16:27:26   ZHANGCEL
//Added many new functions
//
//   Rev 1.0   Aug 16 2001 17:32:16   ZHANGCEL
//Initial revision.
 * 
 */

#endif // !defined(AFX_ONTRACTINFODLG_H__02C9A811_D7F3_11D3_9AA5_00C04F33D7DE__INCLUDED_)
