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
//    Copyright 2013 by International Financial, Inc.
//
//******************************************************************************

#include "stdafx.h"
#include "mfdstc.h"

#include "AWDHistoryBrowserDialog.h"
#include <ifastbp\awdhistorybrowserprocessincludes.h>
#include <ifastcbo\dstcworksession.hpp>
#include <ifastcbo\mgmtco.hpp>
#include <bf/log/log.hpp>

extern CLASS_IMPORT const I_CHAR* CMD_GUI_AWDHISTORY_BROWSER;
#include <bfproc\concretedialogcreator.hpp>
static ConcreteDialogCreator< AWDHistoryBrowserDialog > dlgCreator( CMD_GUI_AWDHISTORY_BROWSER );

namespace
{
   const I_CHAR *CLASSNAME				= I_( "AWDHistoryBrowserDialog" );
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId CompanyId;
   extern CLASS_IMPORT const BFTextFieldId AWDPortalURL;
}

BEGIN_MESSAGE_MAP(AWDHistoryBrowserDialog, BaseMainDlg)
//{{AFX_MSG_MAP(AWDHistoryDialog)

//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
AWDHistoryBrowserDialog::AWDHistoryBrowserDialog(CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand)
: BaseMainDlg(AWDHistoryBrowserDialog::IDD, pParent, pGIC, pGIParent, rCommand, CLASSNAME)
{
	TRACE_CONSTRUCTOR(CLASSNAME, NULL_STRING);
}

//************************************************************************************
SEVERITY AWDHistoryBrowserDialog::doInit()
{
	SEVERITY sevRtn = SEVERE_ERROR;
	sevRtn = NO_CONDITION;
	
	getParameter(MFCAN_IP_PARAM::ACCOUNT_NUM, _accountnum);
	//TRANS_NUM is used to pass and receive External Transaction Number in this case
	getParameter(MFCAN_IP_PARAM::TRANS_NUM, _extTransNum);

	DString dstrCompanyId, dstrAWDPortalURL;
	DSTCWorkSession *dstWorkSession = dynamic_cast<DSTCWorkSession *>(getParent()->getBFWorkSession());
	dstWorkSession->getMgmtCo().getField(ifds::CompanyId, dstrCompanyId, BF::HOST);
    dstWorkSession->getOption(ifds::AWDPortalURL, dstrAWDPortalURL, BF::HOST);
	
	dstrAWDPortalURL = dstrAWDPortalURL + I_("gui/ifds-awd/apps/iFAST-AWDHistory/index.html");

	_url = dstrAWDPortalURL+I_("?");
	_url += I_("ifast_env=") + dstrCompanyId;
	if( _extTransNum != NULL_STRING )
    {
        _url += I_("&ifast_ref=") + _extTransNum;
    }
	else
	{
		_url += I_("&ifast_account=") + _accountnum;
	}
	
	return(sevRtn);
}

//************************************************************************************
void AWDHistoryBrowserDialog::OnPostInitDialog()
{
	TRACE_METHOD(CLASSNAME, I_("OnPostInitDialog")); 
	doRefresh(this, NULL);
	m_AwdPortalBrowser.Navigate( _url.c_str(), NULL, NULL, NULL, NULL );
}

//************************************************************************************
BOOL AWDHistoryBrowserDialog::OnInitDialog()
{
	TRACE_METHOD(CLASSNAME, I_("OnInitDialog"));
	BaseMainDlg::OnInitDialog();
	ShowWindow(SW_SHOW);
	//MoveDialog(GUIPOS_TOP, 0);
	return(TRUE);
}

//************************************************************************************
void AWDHistoryBrowserDialog::DoDataExchange(CDataExchange* pDX)
{
	BaseMainDlg::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(AWDHistoryBrowserDialog)
	DDX_Control(pDX, IDC_AWD_PORTAL_BROWSER, m_AwdPortalBrowser);
	//}}AFX_DATA_MAP
}

//************************************************************************************
bool AWDHistoryBrowserDialog::doRefresh(GenericInterface *, const I_CHAR *)
{
	ShowWindow(SW_SHOW);
	SetDlgCaption();
	return(true);
}

//************************************************************************************
void AWDHistoryBrowserDialog::SetDlgCaption()
{
	TRACE_METHOD(CLASSNAME, I_("SetDlgCaption"));
	DString dstrShrNum, dstrEntityName;
	CString strName;

	// Get Entity Name
	if(!_accountnum.empty()) 
		dynamic_cast<DSTCWorkSession *>(getBFWorkSession())->getFirstSequenced01AccountholderEntityName(getDataGroupId(), _accountnum, dstrEntityName);

	SetShrAcctCaption(dstrShrNum, _accountnum, dstrEntityName);
}

//*****************************************************************************