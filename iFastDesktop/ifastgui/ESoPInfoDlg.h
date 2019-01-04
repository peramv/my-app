#ifndef ESOPINFODLG_H
#define ESOPINFODLG_H
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
// ^FILE   : ESoPInfoDlg.h
// ^AUTHOR : Robert Kovacs
// ^DATE   : 07/29/01
//
// ^CLASS    : ESoPInfoDlg
// ^SUBCLASS : 
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

#ifndef DSTDATETIMECTRL_H
   #include <uibase\DSTDateTimeCtrl.h>
#endif
#ifndef COMBOBASE_H
   #include <uibase\combobase.h>
#endif

#if _MSC_VER > 1000
   #pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// ESoPInfoDlg dialog

class ESoPInfoDlg : public BaseMainDlg
{
// Construction
public:
   ESoPInfoDlg(CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand);
   ~ESoPInfoDlg();

// Dialog Data
   //{{AFX_DATA(ESoPInfoDlg)
   enum
   {
      IDD = IDD_ESOP_INFO
   };
   // NOTE: the ClassWizard will add data members here
   //}}AFX_DATA


// Overrides
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(ESoPInfoDlg)
public:
   virtual BOOL PreTranslateMessage(MSG* pMsg);
protected:
   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
   //}}AFX_VIRTUAL

// Implementation
protected:

   // Generated message map functions
   //{{AFX_MSG(ESoPInfoDlg)
   afx_msg void OnBtnReset();
   afx_msg void OnBtnEsopDetails();
   afx_msg void OnBtnHistorical();
   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()
   /**
    * Required implementation for the refresh method.  No refresh activity is
    * performed for this class.
    * @param rpGICaller - A reference pointer to the calling object.
    * @param szOriginalCommand - A string literal representing the original
    * command issuing the refresh (which may provide a hint on whether this
    * object needs to check for refresh).
    * @returns true if successful, call getErrors for errors if false
    */
   bool doRefresh(
                 GenericInterface * /*rpGICaller*/, 
                 const I_CHAR * /*szOriginalCommand*/
                 );
   /**
     * This method is invoked by the base architecture after OnInitDialog has 
     * completed.  This should be implemented for time intensive setup so that
     * the screen can display quickly and then do this processing.
     */
   void OnPostInitDialog();


   /**
     * This method is optional - override if subclass needs to implement.
     * The override should perform any initialization 
     * required, including getting parameters from InterProcessData (they get
     * cleared after this call).
     * @returns SEVERITY, check conditions if > NO_SEVERITY
     */
   SEVERITY doInit();

   void SetDlgCaption();
   void addControls( );

private:

   UINT  m_uiClassCodeDialogItem;
   LRESULT OpenFundClassListDlg( WPARAM, LPARAM );

};
#endif



//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/ESoPInfoDlg.h-arc  $
//
//   Rev 1.4   Mar 21 2003 18:36:14   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.3   Oct 09 2002 23:55:40   PURDYECH
//PVCS Database Conversion
//
//   Rev 1.2   07 Dec 2001 17:26:04   KOVACSRO
//more implementation.
//
//   Rev 1.1   16 Aug 2001 14:29:56   KOVACSRO
//Added some methods.
//
//   Rev 1.0   29 Jul 2001 19:18:26   KOVACSRO
//Initial revision.
*/
