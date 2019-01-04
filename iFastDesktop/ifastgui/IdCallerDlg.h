//{{AFX_INCLUDES()
#include <ifastgui\msmask.h>
//}}AFX_INCLUDES





#ifndef IDCALLERDLG_H
#define IDCALLERDLG_H



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
// ^FILE   : IdCallerDlg.h
// ^AUTHOR : Jerry Leenerts
// ^DATE   : 1/10/99
//
// ^CLASS    : IdCallerDlg
//
// ^CLASS DESCRIPTION : This is the code for the IdCallerDlg screen
//
//
//******************************************************************************

#ifndef BASEMAINDLG_H
   #include <ifastgui\BaseMainDlg.h>
#endif
#include <imm.h>
#include <uibase\DSTEdit.h>
#include <configmanager.hpp>

class IdCallerDlg : public BaseMainDlg
{
public:
   /**
    * Standard dialog constructor for DSTC
    */
   IdCallerDlg(CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand);
   void setCallerInfo( void );         // Sets the info
   /**
     * Required implementation for the refresh method.  Not sure if any refresh
     * activity is required for this class.
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
   //{{AFX_DATA(IdCallerDlg)
   enum
   {
      IDD = IDD_IDCALLER
   };
   CEdit m_ExtensionBusiness;
   CEdit m_ExtensionOperator;
   CEdit m_PhoneBusiness;
   CEdit m_PhoneHome;
   CComboBox m_Relationship;
   CButton   m_Cancel;
   CEdit m_callerName;
   CEdit m_StartDateTime;
   //}}AFX_DATA

// Overrides
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(IdCallerDlg)

protected:
   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
   //}}AFX_VIRTUAL

// Implementation
protected:
   virtual bool PreOk();
   /*
   LRESULT IdCallerDlg::OnMSMaskSetFocus(WPARAM CtrlId, LPARAM );
   LRESULT IdCallerDlg::OnMSMaskKillFocus(WPARAM CtrlId, LPARAM );
   */

private:
   HIMC current;
   HWND        m_hwndParent;
   CString     m_csDealer;
   CString     m_cstrRel;
   BOOL FirstTimeOpen;
   ConfigManager *m_pWorkstation;
   Configuration m_workstation;

   BFData m_awdData;



//	bool Validate( CDataExchange *pDX, int idc );
   LRESULT setCallerName( WPARAM, LPARAM );// Sets the Caller Name
   void storeData( void );             // Stores the data so RR can display it
   void GetBusinessArea( const DString &dstrManagementCompany, DString &dstrBusinessArea );

   // Generated message map functions
   //{{AFX_MSG(IdCallerDlg)
   virtual BOOL OnInitDialog();
   afx_msg void OnBtnInquiryCompleted();
   afx_msg void OnBtnInquiryCompletedEndCall();
   afx_msg void OnBtnEndCall();
   DECLARE_EVENTSINK_MAP()
   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()
};

#endif // IDCALLERDLG_H

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/IdCallerDlg.h-arc  $
 * 
 *    Rev 1.6   Jan 10 2005 11:12:44   hernando
 * PET1189 FN1 - Dual-Monitor changes.
 * 
 *    Rev 1.5   Dec 31 2003 13:56:34   HERNANDO
 * PET910 - AWD Voice integration enhancement.
 * 
 *    Rev 1.4   Mar 21 2003 18:37:52   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.3   Oct 09 2002 23:55:44   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.2   19 Mar 2002 13:44:42   PURDYECH
 * Added #pragma once include guard
 * Removed compile time "including..." message.
 * 
 *    Rev 1.1   Feb 15 2000 18:59:30   MCNABBGL
 * changed comment format
 * 
 *    Rev 1.0   Feb 15 2000 11:01:18   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.3   Dec 08 1999 11:45:44   YINGZ
 * change ok to preok to make it work
 * 
 *    Rev 1.2   Jul 20 1999 13:52:34   YINGZ
 * use new feature in CTelEdit (about ime)
 * 
 *    Rev 1.1   Jul 08 1999 10:05:20   SMITHDAV
 * Modify revision history commaent format to old
 * style comment -- I can't seem to get new style comments to work.
 *
 */
