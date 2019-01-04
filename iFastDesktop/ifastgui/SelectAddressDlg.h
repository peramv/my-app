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
//    Copyright 2002 by International Financial Data Services
//
//******************************************************************************
//
// ^FILE   : SelectAddressDlg.h
// ^AUTHOR : Yingbao Li
// ^DATE   : June 10,2002
//
// ^CLASS    : SelectAddressDlg
// ^SUBCLASS : BaseMainDlg
//
// ^CLASS DESCRIPTION : Handles the code for the Remarks dialog
//
//
//
// -----------------------------------------------------------------------------
//

/////////////////////////////////////////////////////////////////////////////
// SelectAddressDlg dialog

#ifndef BASEMAINDLG_H
   #include <ifastgui\BaseMainDlg.h>
#endif

class SelectAddressDlg : public BaseMainDlg
{
// Construction
public:
   SelectAddressDlg(CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand);

// Dialog Data
   //{{AFX_DATA(SelectAddressDlg)
   enum
   {
      IDD = IDD_SELECT_ADDRESS
   };

   // NOTE: the ClassWizard will add data members here
   //}}AFX_DATA


// Overrides
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(SelectAddressDlg)
protected:
   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
   //}}AFX_VIRTUAL

// Implementation
protected:

   // Generated message map functions
   //{{AFX_MSG(SelectAddressDlg)
   afx_msg void OnDblclkAddressList( NMHDR* pNMHDR, LRESULT* pResult );

   //}}AFX_MSG

   void OnPostInitDialog();

   virtual SEVERITY doInit();
   virtual bool doRefresh(
                         GenericInterface * /*rpGICaller*/, 
                         const I_CHAR * /*szOriginalCommand*/
                         )
   {
      return(true);
   }

   virtual bool GetOverrideItemString(long lSubstituteId, const DString &ColumnKey, DString &strOut);


private:
   DString _dstrShrNum;

   DECLARE_MESSAGE_MAP()
   private:



};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/SelectAddressDlg.h-arc  $
//
//   Rev 1.3   Mar 21 2003 18:40:44   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.2   Oct 09 2002 23:56:12   PURDYECH
//PVCS Database Conversion
//
//   Rev 1.1   Jun 14 2002 14:43:52   YINGBAOL
//add _shrNum
//
//   Rev 1.0   Jun 11 2002 11:47:24   YINGBAOL
//Initial revision.
 * 



*/