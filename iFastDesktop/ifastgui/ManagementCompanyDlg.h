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
//    Copyright 1997 by DST Systems, Inc.
//
//******************************************************************************
//
// ^FILE   : ManagementCompanyDlg.h
// ^AUTHOR : Jerry Leenerts
// ^DATE   : 02/99
//
// ^CLASS    : ManagementCompanyDlg
// ^SUBCLASS : BaseMainDlg
//
// ^CLASS DESCRIPTION : This is the code for the System/MGMT selection dialog
//
//******************************************************************************

#include <ifastgui\basemaindlg.h>
#include <configmanager.hpp>

class ManagementCompanyDlg : public BaseMainDlg
{
public:
   /**
    * Standard dialog constructor for DSTC
    */
   ManagementCompanyDlg(CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand);
// Dialog Data
   //{{AFX_DATA(ManagementCompanyDlg)
   enum
   {
      IDD = IDD_SYSTMGMT
   };
   CListBox  m_Data;
   CListBox  m_ProfileList;
   CStatic  m_CurrentProfile;
   CEdit m_Ext;
   CStatic  m_Current;
   //}}AFX_DATA

// Overrides
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(ManagementCompanyDlg)
protected:
   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
   virtual void PostNcDestroy();
   //}}AFX_VIRTUAL

protected:
   // Generated message map functions
   //{{AFX_MSG(ManagementCompanyDlg)
   afx_msg void OnDblclkLst();
   virtual BOOL OnInitDialog();
   afx_msg void OnSelchangeLbSelction();
   afx_msg void OnSelchangeLbProfiles();
   afx_msg void OnBtnDetails();
   //}}AFX_MSG
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
                         GenericInterface * /*rpGICaller*/, 
                         const I_CHAR * /*szOriginalCommand*/
                         )
   {  // Nothing to refresh here
      return(true);
   }
   /**
     * This method provides post Ok base processing.
     * @param bCancelStatus - true = Ok successful, false = Ok failed
     */
   virtual void PostOk(
                      bool bOkStatus
                      );
   /**
     * This method provides pre processing for base Ok processing.  If PreOk returns
     * false, conditions should be set.
     * @returns a bool with true = perform Ok, false = stop process - check
     *   conditions
     */
   virtual bool PreOk();
private:
   BFData         *m_pRoadData;       // Whiteboard
   DString         m_strManagementCompanyDlg;     // List of Syst/Mgmt
   DString         m_strSelection;    // Return to user the selection
   ConfigManager   *m_pManager;
   ConfigManager   *m_pWorkstation;
   Configuration    m_workstation;
   ConfigManager   *m_pUser;
   Configuration    m_user;
   bool             m_bIsProfile;

   void fillManagementCompanies( const DString& firstKey ); //populate the selection listbox
   void getExtension();                  // Get the extension from the hard drive
   void storeExtension();                // Store the extension
   void storeCompany();                  // Store the company
   void storeProfile();                  // Store the profile
   void selectProfile( DString& );       // Select Profile
   void selectManagementCompany( DString& );
   bool selectManagerProfile( DString& );
   string_vector getProfileListFromXML();
   bool m_LoadResource;
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/ManagementCompanyDlg.h-arc  $
 * 
 *    Rev 1.10   Mar 26 2009 09:25:58   purdyech
 * Sundry tweaks for ZTS - Rel 10
 * 
 *    Rev 1.9   Mar 21 2003 18:38:42   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.8   Oct 09 2002 23:55:48   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.7   22 May 2002 19:16:14   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.6   25 Apr 2002 14:46:00   HERNANDO
 * Added function selectManagementCompany.
 * 
 *    Rev 1.5   19 Mar 2002 13:44:46   PURDYECH
 * Added #pragma once include guard
 * Removed compile time "including..." message.
 * 
 *    Rev 1.4   03 Aug 2001 14:05:04   HSUCHIN
 * bug fix - fixed previous fix
 * 
 *    Rev 1.3   03 Aug 2001 13:10:08   HSUCHIN
 * bug fix - Cancel no longer tires to load resource dll and crashes
 *
 *    Rev 1.2   30 Jul 2001 15:49:54   YINGZ
 * auto change of resources
 * 
 *    Rev 1.1   Feb 15 2000 18:59:32   MCNABBGL
 * changed comment format
 * 
 *    Rev 1.0   Feb 15 2000 11:01:20   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.2   Nov 04 1999 13:45:36   DT24433
 * changed ok to PreOk/PostOk
 * 
 *    Rev 1.1   Jul 08 1999 10:05:28   SMITHDAV
 * Modify revision history commaent format to old
 * style comment -- I can't seem to get new style comments to work.
 *
 */
