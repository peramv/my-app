
#ifndef FREEUNITDLG_H
#define FREEUNITDLG_H

#ifndef BASEMAINDLG_H
   #include <ifastgui\BaseMainDlg.h>
#endif
//#ifndef LISTCTRL_H
//   #include <uibase\listctrl.h>
//#endif  
#include <uibase\dstlistctrl.h>
class FreeUnitDlg : public BaseMainDlg
{
// Construction
public:
   FreeUnitDlg(CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand);

// Dialog Data
   //{{AFX_DATA(FreeUnitDlg)
   enum
   {
      IDD = IDD_FREE_UNIT1
   };
   CButton m_BtnMore;
//   ListViewControl m_FundList;
   //}}AFX_DATA

// Overrides
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(FreeUnitDlg)
protected:
   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
   //}}AFX_VIRTUAL

// Implementation
protected:
   virtual bool doRefresh( GenericInterface * /*rpGICaller*/, 
                           const I_CHAR * /*szOriginalCommand*/ );

   // Generated message map functions
   //{{AFX_MSG(FreeUnitDlg)
 //  afx_msg void OnItemchangedLvFunda(NMHDR* pNMHDR, LRESULT* pResult);
   afx_msg void OnMore();
	afx_msg void OnBtnInvSummary();
   virtual BOOL OnInitDialog();
   //}}AFX_MSG
   virtual bool Ok()
   {
      // just return true for now
      return(true);
   }
   virtual void OnPostInitDialog();
   virtual bool GetOverrideItemString(long lSubstituteId, const DString &ColumnKey, DString &strOut);
   virtual SEVERITY doInit();
	virtual void DoListItemChanged(
                           UINT listControlID,
                           const DString &strKey,
                           bool bIsNewItem ,
                           bool bIsDummyItem
                           );

   //{{AFX_MSG(FreeUnitDlg)
   afx_msg void OnRbFundLevel();
   afx_msg void OnRbAccountLevel();
   //}}AFX_MSG

   DECLARE_MESSAGE_MAP()

   bool ListViewControlFilter( long lSubstituteId, const DString * );

   private:

   DString AccountNum;
   DString m_PrcntFreeHolding;
   DString m_DSCFeeLevel;
   bool m_IsAccountLevel;
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/FreeUnitDlg.h-arc  $
 * 
 *    Rev 1.8   May 02 2005 08:43:14   hernando
 * PET1024 FN10 - Acct Level/Fund Level DSC Enhancement.
 * 
 *    Rev 1.7   Feb 26 2004 17:09:24   ZHANGCEL
 * PET1001 - FN01 : Added logic to launch Inventory Summary screen 
 * 
 *    Rev 1.6   Nov 10 2003 13:10:02   linmay
 * fix Format issue, and clean code
 * 
 *    Rev 1.4   Mar 21 2003 18:36:42   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.3   Oct 09 2002 23:55:42   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.2   19 Mar 2002 13:44:40   PURDYECH
 * Added #pragma once include guard
 * Removed compile time "including..." message.
 * 
 *    Rev 1.1   Apr 03 2000 14:13:32   DT24433
 * removed unused headers, added revision block
 * 
 */

#endif // FREEUNITDLG_H
