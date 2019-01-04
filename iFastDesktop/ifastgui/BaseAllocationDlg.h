
#ifndef BASEALLOCATIONDLG_H
#define BASEALLOCATIONDLG_H
//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by International Financial, Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2003 by International Financial.
//
//******************************************************************************
//
// ^FILE   : BaseAllocationDlg.h
// ^AUTHOR : Yingbao  Li
// ^DATE   : May 26,2003
//
// ^CLASS    : BaseAllocationDlg
// ^SUBCLASS : BaseMainDlg
//
// ^CLASS DESCRIPTION : 
//
//******************************************************************************

#ifndef BASEMAINDLG_H
   #include <ifastgui\BaseMainDlg.h>
#endif

#ifndef COMBOBASE_H
   #include <uibase\combobase.h>
#endif


class BaseAllocationDlg : public BaseMainDlg
{
public:
	BaseAllocationDlg(UINT nIDD, CWnd* pParent, GenericInterfaceContainer* pGIC, 
		GenericInterface* pGIParent, const Command& rCommand);
	~BaseAllocationDlg(){
	}
	/**
   implement here any bussiness rules related to the buttons that were added for
	permission check (add or delete buttons)
   return true if it should be disabled and false if it should be enabled
   DO NOT call EnableWindow() here
   * @param nID - the control's ID
   */
//   virtual bool doDisablePermCheckButton(UINT nID);

// Dialog Data
	//{{AFX_DATA(AddressBookDlg)
	enum { IDD = IDD_FROM_ALLOCATION };
	//}}AFX_DATA

// Overrides
	// ClassWizard generated virtual function overrides
protected:
	//{{AFX_VIRTUAL(AddressBookDlg)
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
 
	//}}AFX_VIRTUAL
// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(AddressBookDlg)

	afx_msg void OnBtnDefAlloc();
	afx_msg void OnBtnResetFrom();
	afx_msg void OnBtnAddFromAlloc();
	afx_msg void OnBtnDelFromAlloc();
	afx_msg void OnReplaceAsDefaultFromAlloc(); 

	virtual BOOL OnInitDialog();
   virtual BOOL PreTranslateMessage(MSG* pMsg);


	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
   
   void OnPostInitDialog();
   virtual SEVERITY doInit();
   //**
    // * Required implementation for the refresh method.  No refresh activity is
    // * performed for this class.
   //  * @param rpGICaller - A reference pointer to the calling object.
    // * @param szOriginalCommand - A string literal representing the original
    // * command issuing the refresh (which may provide a hint on whether this
   //  * object needs to check for refresh).
   //  * @returns true if successful, call getErrors for errors if false
   virtual bool doRefresh(
      GenericInterface * /*rpGICaller*/, 
      const I_CHAR * //*szOriginalCommand
      );
  
	virtual bool PreOk();
	virtual bool GetOverrideItemString(long lSubstituteId, 
		const DString &ColumnKey, 
		DString &strOut);
	virtual bool GetDataForControl(UINT controlID,  
		DString &strValueOut, 
		bool bFormatted, 
		int index ) const;

	virtual bool doDisablePermCheckButton(UINT nID);

	virtual void ControlUpdated( UINT controlID, const DString &strValue );


protected: // will be override in derived class
	virtual void addControls();
	virtual void	setDlgTitle( );
   virtual LRESULT OpenFundClassDlg( WPARAM, LPARAM );
	bool    bIsGoodStatus();


private:
   UINT   m_uiClassCodeDialogItem; 
	DString _curRRIFInfoKey;
	BOOL    _bReplaceAsDefault;


};

#endif


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/BaseAllocationDlg.h-arc  $
//
//   Rev 1.0   Jun 09 2003 11:19:26   YINGBAOL
//Initial revision.
//

*/