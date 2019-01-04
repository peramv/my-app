
#ifndef HISTORICALSYSTEMATICINDEXDLG_H
#define HISTORICALSYSTEMATICINDEXDLG_H

#ifndef BASEMAINDLG_H
   #include <ifastgui\BaseMainDlg.h>
#endif
#ifndef LISTCTRL_H
   #include <uibase\listctrl.h>
#endif  

class HistoricalSystematicIndexDlg : public BaseMainDlg
{
// Construction
public:
   HistoricalSystematicIndexDlg(CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand);
   ~HistoricalSystematicIndexDlg();

// Dialog Data
   //{{AFX_DATA(HistoricalSystematicIndexDlg)
   enum
   {
      IDD = IDD_HISTORICAL_ACCOUNT
   };
   CButton       m_btnMore;
   ListViewControl m_lvHistoricalSystematicIndex;
   //}}AFX_DATA


// Overrides
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(HistoricalSystematicIndexDlg)
protected:
   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
   //}}AFX_VIRTUAL

// Implementation
protected:
   // Generated message map functions
   //{{AFX_MSG(HistoricalSystematicIndexDlg)
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
};

#endif // HISTORICALSYSTEMATICINDEXDLG_H

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/HistoricalSystematicIndexDlg.h-arc  $
//
//   Rev 1.5   Mar 21 2003 18:37:42   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.4   Oct 09 2002 23:55:44   PURDYECH
//PVCS Database Conversion
//
//   Rev 1.3   19 Mar 2002 13:44:42   PURDYECH
//Added #pragma once include guard
//Removed compile time "including..." message.
//
//   Rev 1.2   Jun 01 2001 15:19:06   HERNANDO
//Removed parameters.
//
//   Rev 1.1   May 11 2001 13:01:36   HERNANDO
//_
//
//   Rev 1.0   May 10 2001 14:11:06   HERNANDO
//Initial revision.
 * 
 * 
 */
