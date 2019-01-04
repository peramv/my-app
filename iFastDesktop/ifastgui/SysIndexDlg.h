#ifndef SYSINDEXDLG_H
#define SYSINDEXDLG_H
//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by DST Canada, Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2001 by DST Canada, Inc.
//
//******************************************************************************
//
// ^FILE   : SysIndexDlg.h
// ^AUTHOR : Mihai Virgil Buzila
// ^DATE   : 05/01/01
//
// ^CLASS    : SysIndexDlg
// ^SUBCLASS : SysIndexDlg
//
// ^CLASS DESCRIPTION : 
//
//******************************************************************************


#ifndef BASEMAINDLG_H
   #include <ifastgui\BaseMainDlg.h>
#endif
#ifndef INCLUDED_VECTOR
   #define INCLUDED_VECTOR
   #include <vector>
#endif
#ifndef __AFXDTCTL_H__
   #include <afxdtctl.h>
#endif
#ifndef DSTDATETIMECTRL_H
   #include <uibase\DSTDateTimeCtrl.h>
#endif
#ifndef COMBOBASE_H
   #include <uibase\combobase.h>
#endif

#ifndef _GXALL_H_
   #include <gxall.h>
#endif


#if _MSC_VER > 1000
   #pragma once
#endif // _MSC_VER > 1000
// SysIndexDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// SysIndexDlg dialog


class SysIndexDlg : public BaseMainDlg
{
// Construction
public:
   SysIndexDlg(CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand);
   ~SysIndexDlg();
// Dialog Data
   //{{AFX_DATA(SysIndexDlg)
   enum
   {
      IDD = IDD_SYSTEMATIC_INDEXING
   };
   //}}AFX_DATA

// Overrides
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(SysIndexDlg)
protected:
   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
   //}}AFX_VIRTUAL

// Implementation
protected:

   // Generated message map functions
   //{{AFX_MSG(SysIndexDlg)
   virtual BOOL OnInitDialog();
   afx_msg void OnBtnAdd();
   afx_msg void OnBtnDel();
   afx_msg void OnBtnReset();
   afx_msg void OnBtnHistorical();
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
                         );
   /**
     * Adds the controls to the dialog
     */
   void addControls( );
   /**
     * reenables the controls based on ID type fields
     */

   virtual bool GetDataForControl(
                                 UINT controlID,
                                 DString &strValueOut,
                                 bool bFormatted,
                                 int index=0
                                 ) const;

   bool GetOverrideItemString(long lSubstituteId, const DString &dstrColumnKey, DString &dstrOut);

/**
   implement here any bussiness rules related to the buttons that were added for permission check (add or delete buttons)
   return true if it should be disabled and false if it should be enabled
   DO NOT call EnableWindow() here
   * @param nID - the control's ID
   */
   bool doDisablePermCheckButton(UINT nID);

private: 

};

#endif
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/SysIndexDlg.h-arc  $
//
//   Rev 1.7   Mar 21 2003 18:41:22   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.6   Oct 09 2002 23:56:14   PURDYECH
//PVCS Database Conversion
//
//   Rev 1.5   23 Nov 2001 14:25:56   KOVACSRO
//perm check changes.
//
//   Rev 1.4   02 Aug 2001 18:28:38   HSUCHIN
//added permission check
//
//   Rev 1.3   04 Jul 2001 16:32:58   HSUCHIN
//added override for StopDate
//
//   Rev 1.2   Jun 01 2001 13:45:28   HERNANDO
//Added OnBtnHistorical.
//
//   Rev 1.1   31 May 2001 19:30:08   HSUCHIN
//code cleanup and many enhancements
//
//   Rev 1.0   03 May 2001 13:47:08   BUZILAMI
//Initial revision.
 * 
 */
