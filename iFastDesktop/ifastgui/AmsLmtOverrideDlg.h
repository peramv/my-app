
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
//    Copyright 2002 by International Financial Data Service
//
//******************************************************************************
//
// ^FILE   : AmsLmtOverrideDlg.h
// ^AUTHOR : Yingbao Li
// ^DATE   : Nov. 12,2002
//
// ^CLASS    : AmsLmtOverrideDlg
// ^SUBCLASS : BaseMainDlg
//
// ^CLASS DESCRIPTION : Handles the code for the Fund Info screen
//
// -----------------------------------------------------------------------------
//
//******************************************************************************


#ifndef BASEMAINDLG_H
   #include <ifastgui\BaseMainDlg.h>
#endif
#include <ifastgui\ifasthistoricalinfo.hpp>

class AmsLmtOverrideDlg : public BaseMainDlg
{
public:
   /**
    * Standard dialog constructor for DSTC
    */
   AmsLmtOverrideDlg(CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand);
// Dialog Data
   //{{AFX_DATA(SettlementDlg)
   enum
   {
      IDD = IDD_AMS_LMT_OVERRIDE
   };
   //}}AFX_DATA


// Overrides
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(AmsLmtOverrideDlg)
protected:
   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
   //}}AFX_VIRTUAL

// Implementation
protected:

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
     * Get parameters from InterProcessData.
     * @returns SEVERITY, check conditions if > NO_SEVERITY
     */
   virtual SEVERITY doInit();

   /**
     * This method should be overridden in the derived dialog if there is
     * OnOk processing to be done after the base processing.  Note that the OnOk
     * processing can no longer be "cancelled" at this point.  BaseMainDlg 
     * enforces its actions by making OnOk private.
     * @param bCancelStatus - true = Ok successful, false = Ok failed
     */
   //  virtual void PostOk(
   //     bool /* bOkStatus */
   //     );
   // Generated message map functions
   //{{AFX_MSG(SettlementDlg)
   virtual BOOL OnInitDialog();
   afx_msg void OnBtnReset();
   afx_msg void OnBtnAdd();
   afx_msg void OnBtnDel();
   afx_msg void OnBtnAdmDates();
   afx_msg void OnBtnHistorical();
   afx_msg void OnBtnMore();

   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()

   virtual void OnPostInitDialog();
   virtual void DoListItemChanged(
                           UINT listControlID,
                           const DString &strKey,
                           bool bIsNewItem ,
                           bool bIsDummyItem
                           );
   virtual bool doDisablePermCheckButton(UINT nID);

	virtual void ControlUpdated(UINT controlID, const DString &strValue);

private:
	bool addControls();
	void setDlgTitle();
    void EnableControls( );

    DString _dstrAmsCode;
    DString _dstrAmsType;
    DString _dstrEffectiveDate;
	DString _dstrFromScr; 

};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/AmsLmtOverrideDlg.h-arc  $
//
//   Rev 1.3   Feb 17 2004 16:35:22   VADEANUM
//PTS 10026510 - AMS Limitation, Override Fund Level
//
//   Rev 1.2   Aug 13 2003 16:16:16   linmay
//added enablecontrol(), dodisablepermcheckbutton, dolistitemchanged()
//
//   Rev 1.1   Aug 11 2003 12:47:04   linmay
//added onbtnmore
//
//   Rev 1.0   Jul 23 2003 09:26:28   linmay
//Initial Revision
//
*/