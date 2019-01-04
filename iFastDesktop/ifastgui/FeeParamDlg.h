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
// ^FILE   : FeeParamDlg.h
// ^AUTHOR : Yingbao Li
// ^DATE   : 01/28/02
//
// ^CLASS    : FeeParamDlg
// ^SUBCLASS : 
//
// ^CLASS DESCRIPTION : 
//
//******************************************************************************


#include <ifastgui\BaseMainDlg.h>
#include <ifastgui\ifasthistoricalinfo.hpp>


#if _MSC_VER > 1000
   #pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// FeeParamDlg dialog

class FeeParamDlg : public BaseMainDlg
{
// Construction
public:
   FeeParamDlg(CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand);
   ~FeeParamDlg();

// Dialog Data
   //{{AFX_DATA(FeeParamDlg)
   enum
   {
      IDD = IDD_FEE_PARAM
   };
   // NOTE: the ClassWizard will add data members here
   //}}AFX_DATA


// Overrides
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(FeeParamDlg)
public:
   virtual BOOL PreTranslateMessage(MSG* pMsg);
protected:
   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
   //}}AFX_VIRTUAL

// Implementation
protected:

   // Generated message map functions
   //{{AFX_MSG(FeeParamDlg)
   afx_msg void OnBtnReset();
   afx_msg void OnBtnAddFeeParam();
   afx_msg void OnBtnDelFeeParam();
   afx_msg void OnBtnMoreFeeParam();
   afx_msg void OnBtnAddFeeScale();
   afx_msg void OnBtnDelFeeScale();
   afx_msg void OnBtnAdmDates(); 
   afx_msg void OnBtnHistoricalAccount();
   afx_msg void OnBtnHistoricalScale();

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

   virtual bool GetDataForControl(
                                 UINT controlID,
                                 DString &strValueOut,
                                 bool bFormatted,
                                 int index=0
                                 ) const;


   virtual void ControlUpdated(
                              UINT controlID,
                              const DString &strValue
                              );

   virtual bool GetOverrideItemString(long lSubstituteId, 
                                      const DString &ColumnKey, 
                                      DString &strOut
                                     );
   virtual void DoListItemChanged(
                                 UINT listControlID,
                                 const DString &strKey, 
                                 bool bIsNewItem ,
                                 bool bIsDummyItem
                                 );
	virtual void InitControl(
                         UINT controlID
                         );
	virtual bool SetDataFromControl(
                                UINT controlID,
                                const DString &strValue,
                                bool bFormatted,
                                SEVERITY &sevRtn,
                                int index
                                );
   virtual bool doDisableControl(UINT nID, bool bIsNew);
   virtual bool doDisablePermCheckButton(UINT nID);


private:

   UINT  m_uiClassCodeDialogItem;
   LRESULT OpenFundClassListDlg( WPARAM, LPARAM );
   void SetDlgCaption();
   void addControls( );
   void DispFeeTypeRelated();



};



//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/FeeParamDlg.h-arc  $
//
//   Rev 1.7   Apr 04 2003 16:05:32   PURDYECH
//Sync 1.6.2.0 back to trunk
//
//   Rev 1.6.2.0   Mar 21 2003 18:36:26   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.6.1.0   Mar 05 2003 11:31:22   PURDYECH
//Use IFastHistoricalInfo instead of deriving from IFastBaseMainDlg
//
//   Rev 1.6   Feb 20 2003 09:28:06   YINGBAOL
//add doDisableControl and doDisablePermCheckButton
//
//   Rev 1.5   Jan 29 2003 16:22:26   popescu
//Added the historical button for FeeParamSysDlg and FeeParamDlg
//
//   Rev 1.4   Jan 22 2003 17:49:22   YINGBAOL
//clean some unused code
//
//   Rev 1.3   Jan 03 2003 19:39:30   YINGBAOL
//add logic for commission Group
//
//   Rev 1.2   Oct 09 2002 23:55:40   PURDYECH
//PVCS Database Conversion
//
//   Rev 1.1   Feb 22 2002 14:17:28   YINGBAOL
//add more function
//
*/
