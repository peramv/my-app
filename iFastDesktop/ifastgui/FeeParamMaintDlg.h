#pragma once
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
//    Copyright 2002 by International Financial Ltd.
//
//******************************************************************************
//
// ^FILE   : FeeParamMaintDlg.h
// ^AUTHOR : 
// ^DATE   : 07/26/04
//
// ^CLASS    : FeeParamMaintDlg
// ^SUBCLASS : 
//
// ^CLASS DESCRIPTION : 
//
//******************************************************************************


#include <ifastgui\basemaindlg.h>
#include <ifastgui\ifasthistoricalinfo.hpp>


#if _MSC_VER > 1000
   #pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// FeeParamMaintDlg dialog

class FeeParamMaintDlg : public BaseMainDlg
{
// Construction
public:
   FeeParamMaintDlg(CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand);
   ~FeeParamMaintDlg();

// Dialog Data
   //{{AFX_DATA(FeeParamMaintDlg)
   enum
   {
      IDD = IDD_FEE_PARAM_MAINT
   };
   // NOTE: the ClassWizard will add data members here
   //}}AFX_DATA

   virtual bool canCancel();

// Overrides
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(FeeParamMaintDlg)
protected:
   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
   //}}AFX_VIRTUAL

// Implementation
protected:

   // Generated message map functions
   //{{AFX_MSG(FeeParamMaintDlg)
   afx_msg void OnBtnReset();
   afx_msg void OnBtnAdd();
   afx_msg void OnBtnDel();
   afx_msg void OnBtnAdmDatesScale();
   afx_msg void OnBtnAdmDatesThrshld(); 
   afx_msg void OnBtnAddThrshld();
   afx_msg void OnBtnDelThrshld();
   afx_msg void OnBtnAddScale();
   afx_msg void OnBtnDelScale();
   afx_msg void OnBtnHistThrshld();
   afx_msg void OnBtnHistScale();

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
   bool doDisablePermCheckButton(UINT nID);


   /**
     * This method is optional - override if subclass needs to implement.
     * The override should perform any initialization 
     * required, including getting parameters from InterProcessData (they get
     * cleared after this call).
     * @returns SEVERITY, check conditions if > NO_SEVERITY
     */
   SEVERITY doInit();
   void DispScaleFeeTypeRelated ();


   virtual void ControlUpdated(
                              UINT controlID,
                              const DString &strValue
                              );
   void DoListItemChanged(UINT listControlID,
                          const DString &strKey,
                          bool bIsNewItem ,
                          bool bIsDummyItem);

private:

   void SetDlgCaption();
   void addControls( );
   DString m_FeeType;
};

