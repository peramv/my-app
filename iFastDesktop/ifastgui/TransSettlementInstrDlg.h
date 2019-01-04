#ifndef TRANSSETTLOCDLG_H
#define TRANSSETTLOCDLG_H
//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by International Financial Data Services,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2003 by International Financial Data Services
//
//******************************************************************************
//
// ^FILE   : TransSettlementInstrDlg.h
// ^AUTHOR : Monica Vadeanu
// ^DATE   : November 10, 2003
//
// ^CLASS    : TransSettlementInstrDlg
// ^SUBCLASS : 
//
// ^CLASS DESCRIPTION : 
//
//******************************************************************************


#ifndef BASEMAINDLG_H
   #include <ifastgui\BaseMainDlg.h>
#endif
#ifndef INCLUDED_VECTOR
   #define INCLUDED_VECTOR
   #include <vector>
#endif

#if _MSC_VER > 1000
   #pragma once
#endif // _MSC_VER > 1000

class TransSettlementInstrDlg : public BaseMainDlg
{
// Construction
public:
   TransSettlementInstrDlg( CWnd* pParent, 
                            GenericInterfaceContainer* pGIC, 
                            GenericInterface* pGIParent, 
                            const Command& rCommand);
   ~TransSettlementInstrDlg();

// Dialog Data
   //{{AFX_DATA(TransSettlementInstrDlg)
   enum
   {
      IDD = IDD_SETTLEMENT_INSTRUCTION_TRADE
   };
   // NOTE: the ClassWizard will add data members here
   //}}AFX_DATA


// Overrides
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(TransSettlementInstrDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
   virtual void OnCancel();
	protected:
   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

   // Generated message map functions
   //{{AFX_MSG(TransSettlementInstrDlg)
	/////////////afx_msg void OnBtnRefresh();	
	afx_msg void OnRbFromAccount();
   afx_msg void OnRbToAccount();
	afx_msg void OnBtnReset();
	/*afx_msg void OnCmbSelChangeSettlLoc();
	afx_msg void OnCmbSelChangeClearingMethod();
	afx_msg void OnKillFocusEditDeliveryTo();
	afx_msg void OnKillFocusEditForAccount();
	afx_msg void OnKillFocusEditInFavourOf();	
   */
	//}}AFX_MSG   
   DECLARE_MESSAGE_MAP()
   
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

	bool doRefresh( GenericInterface *, 
                   const I_CHAR *);
   	   
private:

	void SetDlgCaption();   
   /*
	void setFromToFields( const DString &dstrFieldValue, 
		                   const BFFieldId &fieldIdFrom, 
								 const BFFieldId &fieldIdTo );
   */

	DString _dstrFromScreen;
	DString _dstrPendingHist;
	DString _dstrFromClearingAccount;
	DString _dstrToClearingAccount;
   DString _dstrSide;
};
#endif

//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastgui/TransSettlementInstrDlg.h-arc  $
//
//   Rev 1.2   Nov 29 2004 20:31:10   popescu
//PET 1117/06/56 fees/trades processing
//
//   Rev 1.1   Nov 24 2004 21:36:58   popescu
//PET 1117/06/56. trade processing, settle location
//
//   Rev 1.0   Oct 14 2004 12:32:02   VADEANUM
//Initial revision.
//
//   Rev 1.2   Dec 08 2003 12:37:40   VADEANUM
//PET859 FN1 - Settlement Location at Trade Level support.
//
//   Rev 1.1   Nov 27 2003 12:56:28   VADEANUM
//PET859 FN1 - Settlement Location at Trade Level support.
//
//   Rev 1.0   Nov 10 2003 14:42:02   VADEANUM
//Initial revision.
//
