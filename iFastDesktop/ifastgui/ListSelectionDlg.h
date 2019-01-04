
#ifndef LISTSELECTIONDLG_H
#define LISTSELECTIONDLG_H
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
// ^FILE   : ListSelectionDlg.h
// ^AUTHOR : Jerry Leenerts
// ^DATE   : 12/98
//
// ^CLASS    : ListSelectionDlg
// ^SUBCLASS : BaseMainDlg
//
// ^CLASS DESCRIPTION : Handles the code for a simple list selection dialog
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

class ListSelectionDlg : public BaseMainDlg
{
public:
   /**
    * Standard dialog constructor for DSTC
    */
   ListSelectionDlg(CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand);
// Dialog Data
   //{{AFX_DATA(ListSelectionDlg)
   enum
   {
      IDD = IDD_LIST_SELECTION
   };
   CListBox  m_Values;
   //}}AFX_DATA


// Overrides
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(ListSelectionDlg)
protected:
   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
   //}}AFX_VIRTUAL

// Implementation
protected:
   virtual bool Cancel();
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
                         )
   {  // Nothing to refresh here
      return(true);
   }
   /**
     * This is the implementation for OnOk processing to be done.  BaseMainDlg
     * enforces its actions by making OnOk private.
     * @returns a bool with true = perform Ok, false = stop process
     */
   virtual bool PreOk();

   // Generated message map functions
   //{{AFX_MSG(ListSelectionDlg)
   virtual BOOL OnInitDialog();
   afx_msg void OnDblclkLstValue();
   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()

   private:
   DString m_strTitle;       // Title of dialog
   STRINGVECTOR *m_psvDisplay;
   int m_mode;

   enum
   {
      NO_MODE, STRING_VECTOR
   };
};

#endif // LISTSELECTIONDLG_H

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/ListSelectionDlg.h-arc  $
 * 
 *    Rev 1.5   Mar 21 2003 18:38:26   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.4   Oct 09 2002 23:55:46   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.3   19 Mar 2002 13:44:44   PURDYECH
 * Added #pragma once include guard
 * Removed compile time "including..." message.
 * 
 *    Rev 1.2   Feb 13 2001 10:14:46   BUZILAMI
 * added BankAcct and made the dialog to do Ok processing on List double click
 * 
 *    Rev 1.1   Feb 15 2000 18:59:30   MCNABBGL
 * changed comment format
 * 
 *    Rev 1.0   Feb 15 2000 11:01:18   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.2   Nov 12 1999 15:17:36   YINGZ
 * change ok to preok
 * 
 *    Rev 1.1   Jul 08 1999 10:05:24   SMITHDAV
 * Modify revision history commaent format to old
 * style comment -- I can't seem to get new style comments to work.
 *
 */
