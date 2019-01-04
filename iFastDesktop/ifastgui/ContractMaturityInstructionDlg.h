#pragma once
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
//    Copyright 2003 by International Financial, Inc.
//
//******************************************************************************
//
// ^FILE   : ContractMaturityInstructionDlg.h
// ^AUTHOR : Chetan Balepur
// ^DATE   : Jan 23, 2012
//
// ^CLASS    : ContractMaturityInstructionDlg
// ^SUBCLASS : BaseMainDlg
//
// ^CLASS DESCRIPTION : 
//
//******************************************************************************


#include <ifastgui\basemaindlg.h>
#include <ifastgui\ifasthistoricalinfo.hpp>
#include <uibase\ifdslistctrl.h>

#if _MSC_VER > 1000
   #pragma once
#endif // _MSC_VER > 1000

class ContractMaturityInstructionDlg : public BaseMainDlg
{
public:

	//Standard dialog constructor for DSTC
	ContractMaturityInstructionDlg(CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand);
	~ContractMaturityInstructionDlg(); 

   // Dialog Data
   //{{AFX_DATA(ContractMaturityInstructionDlg)
   enum
   {
      IDD = IDD_CONTRACT_MATURITY_INSTRUCTION
   };    
   //}}AFX_DATA

   // Overrides
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(ContractMaturityInstructionDlg)

protected:
   virtual BOOL PreTranslateMessage(MSG* pMsg);
   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
   //}}AFX_VIRTUAL
   
// Implementation
protected:

   // Generated message map functions
   //{{AFX_MSG(ContractMaturityInstructionDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnAdd();
	afx_msg void OnBtnDelete();
	afx_msg void OnBtnAdmDates(); 
	afx_msg void OnBtnMore();
	afx_msg void OnBtnBank();
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
    virtual bool doRefresh( GenericInterface * /*rpGICaller*/, 
                            const I_CHAR * /*szOriginalCommand*/ );

	virtual SEVERITY doInit();

	void OnPostInitDialog();
	void DoListItemChanged ( UINT listControlID,
							 const DString &strKey, 
							 bool isNewItem,
							 bool bIsDummyItem);

	virtual void ControlUpdated ( UINT controlID,	 const DString &strValue);
	virtual bool GetDataForControl ( UINT controlID,  DString &dstrValueOut,
									 bool bFormatted, int iIndex ) const;
private:
	void SetDlgCaption();
	void getFieldsInfo();
	void setDefaultFieldValues();
	void addControls();
	void getAddress(DString& strAddress) const;

	DString m_dstrAccountNum,
			m_dstrCotAcctRid,
			m_dstrContractType,
			m_dstrContractTypeId,
			m_dstrPolicyYear,
			m_dstrPolicyTerm,
			m_dstrMaturityDate;
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/ContractMaturityInstructionDlg.h-arc  $
//
//   Rev 1.5   Mar 22 2012 18:36:08   wp040100
//P0186484 FN05 - Contract Maturity Instruction Changes
//
//   Rev 1.4   Mar 02 2012 16:33:28   wp040100
//P0186484 FN05 - Contract Maturity Instruction - Banking Screen Integration
//
//   Rev 1.3   Feb 27 2012 20:19:28   wp040100
//P0186484 FN05 - Contract Maturity Instruction Changes
//
//   Rev 1.2   Feb 23 2012 14:38:40   wp040100
//P0186484 FN05 - Contract Maturity Instruction Changes
//
//   Rev 1.1   Feb 22 2012 13:50:22   wp040100
//P0186484 FN05 - Contract Maturity Instruction Changes
//
//   Rev 1.0   Feb 21 2012 15:21:20   wp040100
//Initial revision.
//
//
 */
