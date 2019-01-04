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
//    Copyright 1999 by DST Systems, Inc.
//
//******************************************************************************
//
// ^FILE   : HistoricalDlg.hpp
// ^AUTHOR : Serban Popescu
// ^DATE   : 01/08/03
//
// ^CLASS    : HistoricalDlg
// ^SUBCLASS : BaseMainDlg
//
// ^CLASS DESCRIPTION : Handles the code for the Fund Info screen
//
// -----------------------------------------------------------------------------
//
//******************************************************************************


#include <ifastgui\BaseMainDlg.h>
#include <uibase\ifdslistctrl.h>

class HistoricalDlg : public BaseMainDlg
{
public:
   // standard constructor
   HistoricalDlg( CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand);
// Dialog Data
   //{{AFX_DATA(HistoricalDlgDlg)
   enum
   {
      IDD = IDD_HISTORICAL_INFO
   };
   CButton m_BtnMore;
   //}}AFX_DATA

// Overrides
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(HistoricalDlgDlg)
public:
protected:
   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
   //}}AFX_VIRTUAL

// Implementation
protected:
   virtual bool doRefresh( GenericInterface * /*rpGICaller*/, 
                           const I_CHAR * /*szOriginalCommand*/ );
   virtual SEVERITY doInit();
   virtual void OnPostInitDialog();
   virtual bool ListViewControlFilter( long lSubstituteId, const DString *strKey = NULL );

   // Generated message map functions
   //{{AFX_MSG(HistoricalDlgDlg)
   virtual BOOL OnInitDialog();
   afx_msg void OnBtnMore();
   afx_msg void OnBtnAwdLookup ();
   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()


   private:
//methods
   LRESULT OpenFundListDlg( WPARAM, LPARAM );
   void DisplayCaption();

//properties
};


//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/HistoricalDlg.hpp-arc  $
//
//   Rev 1.9   07 Nov 2007 00:18:42   popescu
//InternlAudit Project - 5563/01 added code for handling the AWD lookup button on the Historical Screen
//
//   Rev 1.8   Mar 03 2004 17:08:20   HERNANDO
//PET965 FN11 - Added ListViewControlFilter to filter-out 'ModDate' and 'ModUser'.  This was implemented until view side can filter this before sending records.  The draw back is that of the 25 records returned, less than 25 may be shown for each view call.  When View fixes this, desktop doesn't have to remove this code.
//
//   Rev 1.7   Feb 28 2004 16:02:04   HERNANDO
//PET965 FN11 - Additional historical enhancement.  Changed list control.
//
//   Rev 1.6   Oct 10 2003 16:19:06   HERNANDO
//PTS 10022670 - Added DisplayCaption.
//
//   Rev 1.5   Mar 21 2003 18:37:26   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.4   Feb 07 2003 14:46:16   HSUCHIN
//rename resource id
//
//   Rev 1.3   Feb 03 2003 11:56:54   popescu
//Displaying the history button only when the item is not new, and adding some txt message for the status bar
//
//   Rev 1.2   Jan 28 2003 16:56:42   popescu
//Fixes for the More button in the Historical Info dialog
//
//   Rev 1.1   Jan 28 2003 13:16:32   popescu
//Historical Info feature implementation
//
//   Rev 1.0   Jan 26 2003 14:10:48   popescu
//Initial Revision
 */
