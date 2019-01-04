#ifndef WHEREUSEDDLG_H
#define WHEREUSEDDLG_H
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
// ^FILE   : WhereUsedDlg.h
// ^AUTHOR : Celia Zhang
// ^DATE   : 10/01/99
//
// ^CLASS    : WhereUsedDlg
// ^SUBCLASS : BaseMainDlg
//
// ^CLASS DESCRIPTION : Handles the code for the Fund Info screen
//
// -----------------------------------------------------------------------------
//
//******************************************************************************

#define LAST_NAME_COLUMN         0
#define FIRST_NAME_COLUMN        1
#define TELEPHONE_NUM_COLUMN     2
#define ADDRESS_COLUMN           3


#ifndef BASEMAINDLG_H
   #include <ifastgui\BaseMainDlg.h>
#endif

class WhereUsedDlg : public BaseMainDlg
{
public:
   /**
    * Standard dialog constructor for DSTC
    */
   WhereUsedDlg(CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand);
// Dialog Data
   //{{AFX_DATA(WhereUsedDlg)
   enum
   {
      IDD = IDD_WHEREUSED
   };
   //}}AFX_DATA

// Overrides
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(WhereUsedDlg)
protected:
   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
   //}}AFX_VIRTUAL

// Implementation
protected:
   virtual bool doRefresh(
                         GenericInterface * /*rpGICaller*/, 
                         const I_CHAR * /*szOriginalCommand*/
                         )
   {
      return(true);
   };
   virtual SEVERITY doInit();
   // Generated message map functions
   //{{AFX_MSG(WhereUsedDlg)
   virtual BOOL OnInitDialog();
   afx_msg void OnBtnMore();
   //}}AFX_MSG
   virtual void OnPostInitDialog();
   DECLARE_MESSAGE_MAP()
   private:
   CString   m_strTitle;
   CString   m_EntityName;
   CString   m_EntityBirthName;
};



//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//

#endif // WhereUsedDlg_H
