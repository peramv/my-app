
#ifndef LOGONDLG_H
#define LOGONDLG_H
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
//*******************************************************************************
//
// ^FILE   : logondlg.h
// ^AUTHOR : John Haubrich
// ^DATE   : 06-97
//
// ^CLASS    : LogonDlg
// ^SUBCLASS : BaseMainDlg
//
// ^CLASS DESCRIPTION : Logon and change-of-system/management company object.
//
//********************************************************************************

#ifndef BASEMAINDLG_H
   #include <ifastgui\BaseMainDlg.h>
#endif

/////////////////////////////////////////////////////////////////////////////
// LogonDlg dialog

class LogonDlg : public BaseMainDlg
{
// Construction
public:
   /**
    * Standard dialog constructor for DSTC
    */
   LogonDlg(CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand);
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
// Dialog Data
   //{{AFX_DATA(LogonDlg)
   enum
   {
      IDD = IDD_LOGON
   };
   CStatic  m_XMLConfigTextBox;
   //}}AFX_DATA

// Overrides
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(LogonDlg)
protected:
   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
   virtual void PostNcDestroy();
   //}}AFX_VIRTUAL

// Implementation
protected:
   // Generated message map functions
   //{{AFX_MSG(LogonDlg)
   virtual BOOL OnInitDialog();
   afx_msg void OnBtnDetails();
   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()

   virtual bool GetDataForControl(
                                 UINT controlID,
                                 DString &strValueOut,
                                 bool bFormatted,
                                 int index=0
                                 ) const;
   virtual bool PreOk();
   virtual void PostOk(
                      bool bOkStatus
                      );
   virtual bool SetDataFromControl(
                                  UINT controlID,
                                  const DString &strValue,
                                  bool bFormatted,
                                  SEVERITY &sevRtn,
                                  int index=0
                                  );
   // always allow cancel
   virtual bool canCancel()
   {
      return(true);
   }

private:
   void AWDAutoLogon() const;

   DString m_dstrLanguage;
   DString m_confirmPassword;
};

#endif // LOGONDLG_H

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/LogonDlg.h-arc  $
 * 
 *    Rev 1.9   Sep 16 2011 17:14:54   dchatcha
 * Usability Improvement on iFAST/Desktop
 * 
 *    Rev 1.8   Jun 24 2007 09:05:24   purdyech
 * Added AWD AutoLogon feature to desktop
 * 
 *    Rev 1.7   May 14 2007 15:13:44   purdyech
 * PTS820423 - Added hidden 'Details' button to invoke AboutDetails dialog.
 * 
 *    Rev 1.6   Mar 21 2003 18:38:30   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.5   Oct 09 2002 23:55:46   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.4   19 Mar 2002 13:44:44   PURDYECH
 * Added #pragma once include guard
 * Removed compile time "including..." message.
 * 
 *    Rev 1.3   04 Jul 2001 16:45:54   YINGZ
 * implement cancel to give user warning when there are updates
 * 
 *    Rev 1.2   May 29 2001 11:44:36   HUANGSHA
 * Code Cleanup
 * 
 *    Rev 1.1   Feb 15 2000 18:59:32   MCNABBGL
 * changed comment format
 * 
 *    Rev 1.0   Feb 15 2000 11:01:18   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.4   Nov 04 1999 13:37:58   DT24433
 * changed ok to PreOk/PostOk
 * 
 *    Rev 1.3   Nov 02 1999 17:27:06   YINGZ
 * change override
 * 
 *    Rev 1.2   Oct 18 1999 17:35:02   DT24433
 * initial changes for using control container
 * 
 *    Rev 1.1   Jul 08 1999 10:05:26   SMITHDAV
 * Modify revision history commaent format to old
 * style comment -- I can't seem to get new style comments to work.
 *
 */
