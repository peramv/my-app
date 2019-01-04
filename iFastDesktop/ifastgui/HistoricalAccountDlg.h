
#ifndef HISTORICALACCOUNTDLG_H
#define HISTORICALACCOUNTDLG_H

#ifndef BASEMAINDLG_H
   #include <ifastgui\BaseMainDlg.h>
#endif
#ifndef LISTCTRL_H
   #include <uibase\listctrl.h>
#endif  

class HistoricalAccountDlg : public BaseMainDlg
{
// Construction
public:
   HistoricalAccountDlg(CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand);
   ~HistoricalAccountDlg();

// Dialog Data
   //{{AFX_DATA(HistoricalAccountDlg)
   enum
   {
      IDD = IDD_HISTORICAL_ACCOUNT
   };
   CButton m_btnMore;
   ListViewControl m_lvHistoricalAccount;
   //}}AFX_DATA


// Overrides
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(HistoricalAccountDlg)
protected:
   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
   //}}AFX_VIRTUAL

// Implementation
protected:
   // Generated message map functions
   //{{AFX_MSG(HistoricalAccountDlg)
   virtual BOOL OnInitDialog();
   afx_msg void OnMore();
   //}}AFX_MSG
   virtual void OnPostInitDialog();
   DECLARE_MESSAGE_MAP()
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
                         GenericInterface * rpGICaller,
                         const I_CHAR * szOriginalCommand
                         );
private:
   DString AccountNum;
   DString s_Name;
};

#endif // HISTORICALACCOUNTDLG_H

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/HistoricalAccountDlg.h-arc  $
 * 
 *    Rev 1.4   Mar 21 2003 18:37:22   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.3   Oct 09 2002 23:55:44   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.2   19 Mar 2002 13:44:40   PURDYECH
 * Added #pragma once include guard
 * Removed compile time "including..." message.
 * 
 *    Rev 1.1   Mar 15 2000 15:28:52   DT24433
 * moved getting field display logic to historicalaccountprocess
 * 
 */
