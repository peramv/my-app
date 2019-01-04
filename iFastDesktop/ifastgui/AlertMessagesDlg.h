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
// ^FILE   : AlertMessagesDlg.h
// ^AUTHOR : 
// ^DATE   : 04 April 2016
//
// ^CLASS    : AlertMessagesDlg
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

class AlertMessagesDlg : public BaseMainDlg
{

public:

	//******************************************************************************
	// Dialog Data
	//******************************************************************************

	//{{AFX_DATA(ReportDlg)
	enum
	{
		IDD = IDD_ALERT_MESSAGES
	};    
	//}}AFX_DATA

	//******************************************************************************
	// Constructor
	//******************************************************************************

	AlertMessagesDlg(CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(FundBrokerDlg)
public:
	//virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

	//******************************************************************************
	// Destructor
	//******************************************************************************

	~AlertMessagesDlg(); 

	// Implementation
protected:

	//******************************************************************************
	// Overrides
	// ClassWizard generated virtual function overrides
	//******************************************************************************

	//{{AFX_VIRTUAL(AlertMessagesDlg)   
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	//******************************************************************************
	// Generated message map functions
	//******************************************************************************

	//{{AFX_MSG(AlertMessagesDlg)
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

    //virtual bool GetDataForControl( UINT controlID, DString &strValueOut, 
    //                                bool bFormatted, int index ) const;

private:

	//******************************************************************************
	// All the control hookups are done in this procedure.  This is called by the 
	// OnInitDialog function.
	// @returns void.
	//******************************************************************************
	void addControls();
	//void getHeadingList (BFFieldId& idField);

   //BFDate::DATE_FORMAT getDateFormatFromClientLocale(const ClientLocale& rLocale) const;
   //BFDate::DATE_FORMAT inferMaskFormat( const DString& dstrMask ) const;
};