#ifndef TAXRATESDLG_H
#define TAXRATESDLG_H

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
// ^FILE   : TaxRatesDlg.h
// ^AUTHOR : Dan Petolescu
// ^DATE   : 12/16/1999
//
// ^CLASS    : TaxRatesDlg
// ^SUBCLASS : BaseMainDlg
//
// ^CLASS DESCRIPTION : 
//
//******************************************************************************


#ifndef BASEMAINDLG_H
   #include <ifastgui\BaseMainDlg.h>
#endif

#if _MSC_VER > 1000
   #pragma once
#endif // _MSC_VER > 1000



class TaxRatesDlg : public BaseMainDlg
{
// Construction
public:
   TaxRatesDlg(CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand);

// Dialog Data
   //{{AFX_DATA(TaxRatesDlg)
   enum
   {
      IDD = IDD_TAXRATES
   };
   //}}AFX_DATA

// Overrides
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(TaxRatesDlg)
public:
   virtual BOOL PreTranslateMessage(MSG* pMsg);
protected:
   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
   //}}AFX_VIRTUAL

// Implementation
protected:

   // Generated message map functions
   //{{AFX_MSG(TaxRatesDlg)
   afx_msg void OnBtnMore();
   afx_msg void OnBtnChange();
   afx_msg void OnBtnAdmDates();
   virtual BOOL OnInitDialog();
   afx_msg void OnAccelListTaxrates();
   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()

   void OnPostInitDialog();

   virtual SEVERITY doInit(); 
   virtual bool doRefresh( GenericInterface * /*rpGICaller*/,  const I_CHAR * /*szOriginalCommand*/ );

   virtual bool Ok()
   {
      // just return true for now
      return(true);
   }
private:
   void DisplayTitle();
   HACCEL m_hAccel;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif //TAXRATESDLG_H

//******************************************************************************
///              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/TaxRatesDlg.h-arc  $
 * 
 *    Rev 1.4   Mar 21 2003 18:41:38   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.3   Oct 09 2002 23:56:16   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.2   Dec 04 2000 15:04:36   OLTEANCR
 * no change
 * 
 *    Rev 1.1   Mar 22 2000 09:02:50   PETOLESC
 * Added Tax Rates and RESP dialogs.
// 
//    Rev 1.1   Mar 07 2000 11:11:48   PETOLESC
// Corrected QA issues.
// 
//    Rev 1.0   Dec 29 1999 17:23:58   PETOLESC
// Initial revision.
 * 
 *
 */
