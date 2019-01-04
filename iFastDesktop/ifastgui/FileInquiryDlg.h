#ifndef FILEINQUIRYDLG_H
#define FILEINQUIRYDLG_H
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
//    Copyright 2002 by DST Canada, Inc.
//
//******************************************************************************
//
// ^FILE   : FileInquiryDlg.h
// ^AUTHOR : Celia Zhang
// ^DATE   : 02/25/2005
//
// ^CLASS    :FileInquiryDlg
// ^SUBCLASS : 
//
// ^CLASS DESCRIPTION : 
//
//******************************************************************************


#include <ifastgui\basemaindlg.h>
#include <uibase\ifdslistctrl.h>

#ifndef INCLUDED_VECTOR
   #define INCLUDED_VECTOR
   #include <vector>
#endif

#if _MSC_VER > 1000
   #pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
//FileInquiryDlg dialog

class FileInquiryDlg : public BaseMainDlg
{
// Construction
public:
  FileInquiryDlg(CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand);
   ~FileInquiryDlg();

// Dialog Data
   //{{AFX_DATA(FileSearchDlg)
   enum
   {
      IDD = IDD_FILE_INQUIRY
   };
   // NOTE: the ClassWizard will add data members here
   //}}AFX_DATA


// Overrides
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(FileSearchDlg)
public:

protected:
   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

   // Generated message map functions
   //{{AFX_MSG(FileSearchDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnMessage();
	afx_msg void OnBtnMore();
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
   
	/**
     * This method can be overridden to respond to data changes in a control.
     * @param controlID - ID of control that is changed.
     * @param strValue - unformatted value of change, this is not meaningful
     *   for a control associated with multiple fields at the same time.
     */
   /*void ControlUpdated(
                           UINT controlID,
                           const DString &strValue
                      );*/
  
private:

   void addControls( );
	
};
#endif



//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/FileInquiryDlg.h-arc  $
//
//   Rev 1.0   Feb 24 2005 17:48:18   ZHANGCEL
//Initial revision.
*/
