#ifndef YTDCONTRIBUTIONDLG_H
#define YTDCONTRIBUTIONDLG_H
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
// ^FILE   : YTDContributionDlg.h
// ^AUTHOR : 
// ^DATE   : 04/08/2001
//
// ^CLASS    : YTDContributionDlg
// ^SUBCLASS : YTDContributionDlg
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

class YTDContributionDlg : public BaseMainDlg
{
public:
   /**
    * Constructor
    */
   YTDContributionDlg(CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand);

   /**
    * Destructor
    */
   ~YTDContributionDlg();

   /**
    * Dialog Data
    */
   //{{AFX_DATA(SysIndexDlg)
   enum
   {
      IDD = IDD_YTD_CONTRIBUTIONS
   };
   //}}AFX_DATA

   /**
    * Overrides
    */
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(YTDContributionDlg)
protected:
   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
   //}}AFX_VIRTUAL

protected:

   /**
    * Generated message map functions
    */
   //{{AFX_MSG(SysIndexDlg)
   virtual BOOL OnInitDialog();
   afx_msg void OnBtnMore();
   afx_msg void OnBtnChange();
   afx_msg void OnBtnAdminDates();
   afx_msg void OnBtnViewInqPDF();
   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()

   /**
     * This method initializes the Dialog by call addControls()
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
     * The List controls are refreshed.
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
     * Adds the custom controls used in the dialog
     */
   void addControls( );

   /**
     * Shows Spousal information in the Dialog
     * @param  bool bFlag - True to show Spousal info, false otherwise.
     */
   void ShowSpousal( bool bFlag );

   /**
     * Fill address line depends on the value of field
     *
     */
   bool GetDataForControl(UINT controlID, DString &dstrValueOut, 
                          bool bFormatted, int index) const ;

   void   DisplayDeliveryOption();
   CString constructOption( const BFFieldId &idField,UINT resID );

   void GetTitleDetails(DString &dstrShrNum, DString &dstrAccountNum, DString &dstrEntityName);
};

#endif

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/YTDContributionDlg.h-arc  $
//
//   Rev 1.6   22 Jul 2008 13:53:18   kovacsro
//PET5517FN60C - added Admin/Dates
//
//   Rev 1.5   Dec 02 2004 11:39:00   yingbaol
//PET1137,FN01: add Epost functionalities
//
//   Rev 1.4   Mar 21 2003 18:42:28   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.3   Oct 09 2002 23:56:18   PURDYECH
//PVCS Database Conversion
//
//   Rev 1.2   Nov 20 2001 16:21:36   ZHANGCEL
//Added a new function getDateFromControl()
//
//   Rev 1.1   20 Aug 2001 14:53:46   HSUCHIN
//added comments
//
//   Rev 1.0   18 Aug 2001 09:29:44   HSUCHIN
//Initial revision.
 */
