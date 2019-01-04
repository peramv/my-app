#pragma once
//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by IFDS, Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 1999 by IFDS, Inc.
//
//******************************************************************************
//
// ^FILE   : AMSBrkLvlDlg.h
// ^AUTHOR : 
// ^DATE   : 
//
// ^CLASS    : AMSBrkLvlDlg
// ^SUBCLASS : BaseMainDlg
//
// ^CLASS DESCRIPTION : Handles the code for the AMSAcctLvl dialog
//
//******************************************************************************

#include <ifastgui\basemaindlg.h>

class AMSBrkLvlDlg : public BaseMainDlg
{

public:

   AMSBrkLvlDlg(CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand);
   ~AMSBrkLvlDlg();

// Dialog Data
   //{{AFX_DATA(AMSBrkLvlDlg)
   enum
   {
      IDD = IDD_AMSBRKLVL
   };
   //}}AFX_DATA

// Overrides
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(AMSBrkLvlDlg)
   virtual BOOL PreTranslateMessage(MSG* pMsg);
protected:
   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
   //}}AFX_VIRTUAL

// Implementation
protected:
   // Generated message map functions
   //{{AFX_MSG(AMSBrkLvlDlg)
   virtual BOOL OnInitDialog();
   afx_msg void OnBtnAdd();
   afx_msg void OnBtnDelete();
   afx_msg void OnBtnReset();
   afx_msg void OnBtnAdmin();
   afx_msg void OnBtnSearch();
   afx_msg void OnBtnMore();
   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()

   bool GetDataForControl(
                                 UINT controlID,
                                 DString &strValueOut,
                                 bool bFormatted,
                                 int index=0
                                 ) const;

   void OnPostInitDialog();

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
                         GenericInterface *rpGICaller, 
                         const I_CHAR *szOriginalCommand
                         );

   bool GetOverrideItemString( long lSubstituteId, const DString &dstrColumnKey, DString &dstrOut );


   virtual void ControlUpdated( UINT controlID, const DString &strValue );

   virtual void DoListItemChanged(
                           UINT listControlID,
                           const DString &strKey,
                           bool bIsNewItem ,
                           bool bIsDummyItem
                           );

    //bool doDisableControl(UINT nID, bool bIsNew);
	//virtual bool doDisablePermCheckButton(UINT nID);
	void doDisableNonPermButtons();


	virtual void DoPreListItemChanged(
                                    UINT listControlID,
                                    const DString &strKey,
                                    bool bIsNewItem,
                                    bool bIsDummyItem
                                    );


private:

   LRESULT OpenBrokerListDlg( WPARAM, LPARAM );
   LRESULT OpenAMSMstrListDlg( WPARAM, LPARAM );
   void EnableControls( bool update );
   void DisplayCaption();
	void setItemChange( bool bChange)
	{
		bItemChange = bChange;
	};
	bool isItemChange()
	{
		return bItemChange == true; 
	};

	bool   bItemChange;
   HACCEL m_hAccel;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/amsbrklvldlg.h-arc  $
//
//   Rev 1.4   Aug 08 2003 10:12:28   YINGBAOL
//change search, refresh mechanism
//
//   Rev 1.3   Apr 16 2003 11:33:28   FENGYONG
//Add more button for broker AMS
//
//   Rev 1.2   Mar 27 2003 11:19:44   FENGYONG
//Add permission control
//
//   Rev 1.1   Mar 21 2003 18:32:38   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.0   Mar 07 2003 16:47:32   FENGYONG
//Initial revision.
//
 * 
 */
