#ifndef IdentAccDlg_H
#define IdentAccDlg_H
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
//    Copyright 2000 by DST Systems, Inc.
//
//******************************************************************************
//
// ^FILE   : IdentAccDlg.h
// ^AUTHOR : Mihai Virgil Buzila
// ^DATE   : 03 Feb 2000
//
// ^CLASS    : IdentAccDlg
// ^SUBCLASS : BaseMainDlg
//
// ^CLASS DESCRIPTION : 
//
// -----------------------------------------------------------------------------
//
//******************************************************************************


#ifndef BASEMAINDLG_H
   #include <ifastgui\BaseMainDlg.h>
#endif

class IdentAccDlg : public BaseMainDlg
{
public:
   // standard constructor
   IdentAccDlg( CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand);
   BOOL PreTranslateMessage( MSG* pMsg );
// Dialog Data
   //{{AFX_DATA(IdentAccDlg)
   enum
   {
      IDD = IDD_IDENT_ACC
   };
   CButton m_BtnNewAccount;
   //}}AFX_DATA

// Overrides
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(IdentAccDlg)
protected:
   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
   //}}AFX_VIRTUAL

// Implementation
   virtual bool ListViewControlFilter( long lSubstituteId, const DString *strKey = NULL  );
protected:
   virtual bool doRefresh( GenericInterface * /*rpGICaller*/, 
                           const I_CHAR * /*szOriginalCommand*/ );
   virtual SEVERITY doInit();
   virtual void DoPreListItemChanged( UINT listControlID, const DString &strKey, bool isNewItem, bool bIsDummyItem );
   virtual void OnPostInitDialog();
   virtual bool GetDataForControl( UINT controlID, 
                                   DString &strValueOut, bool bFormatted, int index ) const;
   virtual bool SetDataFromControl( UINT controlID, const DString &strValue,
                                    bool bFormatted, SEVERITY &sevRtn, int index );
   virtual bool GetOverrideItemString( long lSubstituteId, 
                                       const DString &ColumnKey, DString &strOut );

   virtual bool canCancel()
   {
      return(true);
   }
   // Generated message map functions
   //{{AFX_MSG(IdentAccDlg)
   virtual BOOL OnInitDialog();
   afx_msg void OnBtnGetAccounts();
   afx_msg void OnBtnMore();
   afx_msg void OnBtnSearch();
   afx_msg void OnAccellEntityList();
   afx_msg void OnAccelAccountList();
   afx_msg void OnDblclkLvAccounts(NMHDR* pNMHDR, LRESULT* pResult);
   afx_msg void OnDblclkLvEntities(NMHDR* pNMHDR, LRESULT* pResult);
   afx_msg void OnBtnNewAccount();
   afx_msg void OnBtnNewShareholder();
   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()
   private:
   DString m_dstrMarket;
   HACCEL m_hAccel;
   std::set< DString > listKey;
   bool m_oneSearchUsing;
   GenericInterface *m_rpGIFiller; //Pointer to the Bussiness Process that fills the search criterias
   DString m_label1;
   DString m_label2;
   DString m_searchCode;
   BFContainerId m_usingList;
   DString m_systematic;
   //methods
   void hide1EditField();
   void hide2EditFields();
   void prepareSearchFields( const DString &usingKey );
   void doSearch();
};


#endif // IdentAccDlg_H


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/IdentAccDlg.h-arc  $
 * 
 *    Rev 1.13   Mar 21 2003 18:37:58   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.12   Oct 09 2002 23:55:44   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.11   Sep 06 2001 14:10:16   ZHANGCEL
 * Added second parameter in ListViewControlFilter()
 * 
 *    Rev 1.10   Aug 10 2001 12:54:44   YINGBAOL
 * Disable NASU if it is launched from systematic and allocation
 * 
 *    Rev 1.9   05 Aug 2001 11:37:52   YINGZ
 * allow cancel
 * 
 *    Rev 1.8   Apr 12 2001 10:33:02   YINGZ
 * fix multi entity problem
 * 
 *    Rev 1.7   Dec 13 2000 14:45:28   KOVACSRO
 * Modified DoPreListItemChanged
 * 
 *    Rev 1.6   Oct 11 2000 14:24:32   KOVACSRO
 * Added OnBtnNewAccount and OnBtnNewShareholder.
 * 
 *    Rev 1.5   Sep 01 2000 16:26:54   PETOLESC
 * Removed RButtons.
 * 
 *    Rev 1.4   Apr 26 2000 09:45:02   POPESCUS
 * error message if search criterias are empty
 * 
 *    Rev 1.3   Mar 07 2000 15:45:02   POPESCUS
 * more work on the account search screen
 * 
 *    Rev 1.2   Mar 03 2000 19:34:06   POPESCUS
 * save the work
 * 
 *    Rev 1.1   Mar 03 2000 12:11:10   POPESCUS
 * account search work
 * 
 *    Rev 1.0   Feb 29 2000 15:35:24   BUZILA
 * Initial revision.
// 
*/
