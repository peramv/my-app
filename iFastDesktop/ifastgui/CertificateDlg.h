
#ifndef CERTIFICATEDLG_H
#define CERTIFICATEDLG_H
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
// ^FILE   : CertificateDlg.h
// ^AUTHOR : 
// ^DATE   : 03/04/1999
//
// ^CLASS    : CertificateDlg
// ^SUBCLASS : BaseMainDlg
//
// ^CLASS DESCRIPTION : 
//
//******************************************************************************

#ifndef BASEMAINDLG_H
   #include <ifastgui\BaseMainDlg.h>
#endif

#ifndef LISTCTRL_H
   #include <uibase\listctrl.h>
#endif

#if _MSC_VER > 1000
   #pragma once
#endif // _MSC_VER > 1000

/**
 * Class that display the Entity Maintenance screen.
 *
 * @author 
 * </dd></dl><p><dl><dt><b>Date Created:</b></dt><dd> 03/04/1999</dd></dl>
 * @version 0.1
 */
class CertificateDlg : public BaseMainDlg
{
// Construction
public:
   CertificateDlg(CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand);

// Dialog Data
   //{{AFX_DATA(CertificateDlg)
   enum
   {
      IDD = IDD_CERTIFICATES
   };
   //}}AFX_DATA


// Overrides
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(CertificateDlg)
protected:
   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
   //}}AFX_VIRTUAL

// Implementation
protected:
   // Generated message map functions
   //{{AFX_MSG(CertificateDlg)
   virtual BOOL OnInitDialog();
   afx_msg void OnBtnAdmDates();
   afx_msg void OnBtnChange();
   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()

   /**
     * Loading entity list and first selection
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
                         )
   {  // Nothing to refresh here
      return(true);
   }
   /**
     * This is the implementation for OnOk processing to be done.  BaseMainDlg
     * enforces its actions by making OnOk private.
     * @returns a bool with true = perform Ok, false = stop process
     */
   virtual bool Ok()
   {
      // just return true for now
      return(true);
   }
   virtual bool GetOverrideItemString( long lSubstituteId, 
                                       const DString &dstrColumnKey, DString &dstrOut );


	virtual bool GetDataForControl(
                                 UINT controlID,
                                 DString &strValueOut,
                                 bool bFormatted,
                                 int index
                                 ) const;

private:


};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // CERTIFICATEDLG_H

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/CertificateDlg.h-arc  $
 * 
 *    Rev 1.9   Apr 29 2003 15:02:42   YINGBAOL
 * PTS 10016369 sync. to truck
 * 
 *    Rev 1.8   Mar 21 2003 18:34:10   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.7   Oct 09 2002 23:55:34   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.6   19 Mar 2002 13:44:32   PURDYECH
 * Added #pragma once include guard
 * Removed compile time "including..." message.
 * 
 *    Rev 1.5   Jan 28 2002 11:27:30   YINGBAOL
 * HLLAPI Change
 * 
 *    Rev 1.4   Jun 20 2001 15:52:30   HERNANDO
 * Removed unused functions.
 * 
 *    Rev 1.3   Mar 20 2000 14:15:56   HSUCHIN
 * changed GetfundNumber to use the one in dstcommonfunctions.  Code cleanup
 * 
 *    Rev 1.2   Mar 13 2000 17:28:38   HSUCHIN
 * C2 sync up
 * 
 *    Rev 1.1   Feb 15 2000 18:59:14   MCNABBGL
 * changed comment format
 * 
 *    Rev 1.0   Feb 15 2000 11:01:10   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.2   26 Sep 1999 19:08:00   HICKSBR
 * Add HLLAPI Logic for new Change button
 * 
 *    Rev 1.1   Jul 08 1999 10:04:46   SMITHDAV
 * Modify revision history commaent format to old
 * style comment -- I can't seem to get new style comments to work.
 *
 */
