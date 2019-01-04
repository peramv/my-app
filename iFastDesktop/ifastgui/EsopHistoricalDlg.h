#ifndef ESOPHISTORICALDLG_H
#define ESOPHISTORICALDLG_H
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

#if _MSC_VER > 1000
   #pragma once
#endif // _MSC_VER > 1000


class EsopHistoricalDlg : public BaseMainDlg
{
// Construction
public:
   EsopHistoricalDlg(CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand);
   ~EsopHistoricalDlg();

// Dialog Data
   //{{AFX_DATA(EsopHistoricalDlg)
   enum
   {
      IDD = IDD_ESOP_HISTORICAL
   };
   // NOTE: the ClassWizard will add data members here
   //}}AFX_DATA


// Overrides
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(EsopHistoricalDlg)
protected:
   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
   //}}AFX_VIRTUAL

// Implementation
protected:

   // Generated message map functions
   //{{AFX_MSG(EsopHistoricalDlg)
   // NOTE: the ClassWizard will add member functions here
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

private:
   void setCaption();

};

#endif // 
