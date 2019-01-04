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
// ^FILE   : PriceAdditionalDlg.h
// ^AUTHOR : 
// ^DATE   : 06 May 2017
//
// ^CLASS    : PriceAdditionalDlg
// ^SUBCLASS : BaseMainDlg
//
// ^CLASS DESCRIPTION : 
//
//******************************************************************************


#include <ifastgui\basemaindlg.h>

#include <bfutil\bfdate.hpp>
#include <uibase\ifdslistctrl.h>

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class PriceAdditionalDlg : public BaseMainDlg
{

public:

	//******************************************************************************
	// Dialog Data
	//******************************************************************************

	//{{AFX_DATA(ReportDlg)
	enum
	{
		IDD = IDD_PRICE_ADDITIONAL
	};    
	//}}AFX_DATA

	//******************************************************************************
	// Constructor
	//******************************************************************************

	PriceAdditionalDlg(CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(FundBrokerDlg)
public:
	//virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

	//******************************************************************************
	// Destructor
	//******************************************************************************

	~PriceAdditionalDlg(); 

	// Implementation
protected:

	//******************************************************************************
	// Overrides
	// ClassWizard generated virtual function overrides
	//******************************************************************************

	//{{AFX_VIRTUAL(PriceAdditionalDlg)   
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	//******************************************************************************
	// Generated message map functions
	//******************************************************************************

	//{{AFX_MSG(PriceAdditionalDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

	SEVERITY doInit();

	void OnPostInitDialog();

	//******************************************************************************
	// Method to refresh dialog controls
	// @param   GenericInterface *rpGICaller - pointer to the calling object
	// @param   const I_CHAR *szOriginalCommand - Not used in this case, but 
	//                      can be used to instruct special processing.
	// @returns bool - true.
	//******************************************************************************

	virtual bool doRefresh(GenericInterface * /*rpGICaller*/, 
						const I_CHAR * /*szOriginalCommand*/ ); 

private:

	//******************************************************************************
	// All the control hookups are done in this procedure.  This is called by the 
	// OnInitDialog function.
	// @returns void.
	//******************************************************************************
	void addControls();
};