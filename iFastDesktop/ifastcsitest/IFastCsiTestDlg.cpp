// DstcCsiTestDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ifastcsitest.h"
#include "ifastcsitestdlg.h"

#include <ifastcsi/ifastcsi.h>
#include <ifastcsi/CsiSession.h>

using namespace DcCsiProcesses;
using namespace DcCsiParameters;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDstcCsiTestDlg dialog

CIFastCsiTestDlg::CIFastCsiTestDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CIFastCsiTestDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDstcCsiTestDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CIFastCsiTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDstcCsiTestDlg)
	DDX_Control(pDX, IDC_PARAMETER_VALUE, m_ParameterValue);
	DDX_Control(pDX, IDC_PARAMETER_NAME, m_ParameterName);
	DDX_Control(pDX, IDC_PROCESS_LIST, m_ProcessList);
	DDX_Control(pDX, IDC_PARAMETER_LIST, m_ParameterList);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CIFastCsiTestDlg, CDialog)
	//{{AFX_MSG_MAP(CDstcCsiTestDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_EXECUTE, OnExecute)
	ON_LBN_SELCHANGE(IDC_PROCESS_LIST, OnSelchangeProcessList)
	ON_LBN_DBLCLK(IDC_PROCESS_LIST, OnDblclkProcessList)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_PARAMETER_LIST, OnItemchangedParameterList)
	ON_EN_CHANGE(IDC_PARAMETER_VALUE, OnChangeParameterValue)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDstcCsiTestDlg message handlers

BOOL CIFastCsiTestDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here

   DstcCsi::RegisterProcesses();
   DstcCsi::RegisterScreens();

   processes.insert(ProcessMap::value_type( MASTER_MENU, ParameterList() ));

   {
      ParameterList &list = (*processes.insert(ProcessMap::value_type( ACCOUNT_INFORMATION, ParameterList() )).first).second;
      list.push_back(ACCOUNT_NUMBER);
   }

   {
      ParameterList &list = (*processes.insert(ProcessMap::value_type( AUTOMATIC_TRANSFER_INFO, ParameterList() )).first).second;
      list.push_back(ACCOUNT_NUMBER);
   }

   {
      ParameterList &list = (*processes.insert(ProcessMap::value_type( BASIC_SHARE_HOLDER, ParameterList() )).first).second;
      list.push_back(ACCOUNT_NUMBER);
   }

   {
      ParameterList &list = (*processes.insert(ProcessMap::value_type( HISTORICAL_ACCOUNT_INFO, ParameterList() )).first).second;
      list.push_back(ACCOUNT_NUMBER);
   }

   {
      ParameterList &list = (*processes.insert(ProcessMap::value_type( BANK_INFORMATION_MENU, ParameterList() )).first).second;
      list.push_back(ACCOUNT_NUMBER);
   }

   {
      ParameterList &list = (*processes.insert(ProcessMap::value_type( BANK_INFORMATION, ParameterList() )).first).second;
      list.push_back(ACCOUNT_NUMBER);
      list.push_back(BANK_ACCOUNT_NUMBER);
   }
   processes.insert(ProcessMap::value_type( NEW_SHAREHOLDER, ParameterList() ));
   processes.insert(ProcessMap::value_type( FUNDVALUE_TRADE_OR_FUND, ParameterList() ));


   {
      ParameterList &list = (*processes.insert(ProcessMap::value_type( PAC_INFORMATION, ParameterList() )).first).second;
      list.push_back(ACCOUNT_NUMBER);
      list.push_back(FUND);
      list.push_back(CLASS);
      list.push_back(START_DATE);
      list.push_back(STOP_DATE);
   }
   
   {
      ParameterList &list = (*processes.insert(ProcessMap::value_type( SWP_INFORMATION, ParameterList() )).first).second;
      list.push_back(ACCOUNT_NUMBER);
      list.push_back(FUND);
      list.push_back(CLASS);
      list.push_back(START_DATE);
      list.push_back(STOP_DATE);
   }
   
   {
      ParameterList &list = (*processes.insert(ProcessMap::value_type( PAC_ALLOCATION, ParameterList() )).first).second;
      list.push_back(ACCOUNT_NUMBER);
      list.push_back(FUND);
      list.push_back(CLASS);
      list.push_back(START_DATE);
      list.push_back(STOP_DATE);
   }
   
   {
      ParameterList &list = (*processes.insert(ProcessMap::value_type( SWP_ALLOCATION, ParameterList() )).first).second;
      list.push_back(ACCOUNT_NUMBER);
      list.push_back(FUND);
      list.push_back(CLASS);
      list.push_back(START_DATE);
      list.push_back(STOP_DATE);
   }

   {
      ParameterList &list = (*processes.insert(ProcessMap::value_type( ALLOCATIONS, ParameterList() )).first).second;
      list.push_back(ACCOUNT_NUMBER);
   }

   {
      ParameterList &list = (*processes.insert(ProcessMap::value_type( TRANSACTION, ParameterList() )).first).second;
      list.push_back(ACCOUNT_NUMBER);
   }

   {
      ParameterList &list = (*processes.insert(ProcessMap::value_type( SHAREHOLDER_REMARKS, ParameterList() )).first).second;
      list.push_back(ACCOUNT_NUMBER);
   }

   {
      ParameterList &list = (*processes.insert(ProcessMap::value_type( DEMOGRAPHIC_INFO, ParameterList() )).first).second;
      list.push_back(ACCOUNT_NUMBER);
   }

   processes.insert(ProcessMap::value_type( TRANSACTION_PROCESSING_MENU, ParameterList() ));
   processes.insert(ProcessMap::value_type( SETTLEMENTS, ParameterList() ));
   processes.insert(ProcessMap::value_type( ORDERS_PROCESSED, ParameterList() ));

   {
      ParameterList &list = (*processes.insert(ProcessMap::value_type( ADDRESS_INFORMATION, ParameterList() )).first).second;
      list.push_back(ACCOUNT_NUMBER);
   }
   
   {
      ParameterList &list = (*processes.insert(ProcessMap::value_type( ADDRESS_ASSIGNMENTS, ParameterList() )).first).second;
      list.push_back(ACCOUNT_NUMBER);
   }
   
   {
      ParameterList &list = (*processes.insert(ProcessMap::value_type( ACCOUNT_ENTITY_RELATIONSHIP, ParameterList() )).first).second;
      list.push_back(ACCOUNT_NUMBER);
   }

   {
      ParameterList &list = (*processes.insert(ProcessMap::value_type( BROKER_INFORMATION, ParameterList() )).first).second;
      list.push_back(BROKER_NUMBER);
   }

   {
      ParameterList &list = (*processes.insert(ProcessMap::value_type( BRANCH_INFORMATION, ParameterList() )).first).second;
      list.push_back(BROKER_NUMBER);
      list.push_back(BRANCH_NUMBER);
   }
   
   {
      ParameterList &list = (*processes.insert(ProcessMap::value_type( SALES_REP_INFORMATION, ParameterList() )).first).second;
      list.push_back(BROKER_NUMBER);
      list.push_back(BRANCH_NUMBER);
      list.push_back(SALES_REP_NUMBER);
   }
   
   {
      ParameterList &list = (*processes.insert(ProcessMap::value_type( WHERE_USED, ParameterList() )).first).second;
      list.push_back(ENTITY_NAME);
   }
   
   {
      ParameterList &list = (*processes.insert(ProcessMap::value_type( ENTITY_MAINTAINANCE, ParameterList() )).first).second;
      list.push_back(ACCOUNT_NUMBER);
      list.push_back(ENTITY_ID);
   }
   
   {
      ParameterList &list = (*processes.insert(ProcessMap::value_type( ADD_DISTRIBUTION_INFO, ParameterList() )).first).second;
      list.push_back(ACCOUNT_NUMBER);
   }
   
   {
      ParameterList &list = (*processes.insert(ProcessMap::value_type( DISTRIBUTION_INFO, ParameterList() )).first).second;
      list.push_back(ACCOUNT_NUMBER);
   }
   
   {
      ParameterList &list = (*processes.insert(ProcessMap::value_type( CERTIFICATE_INFO, ParameterList() )).first).second;
      list.push_back(ACCOUNT_NUMBER);
   }
   {
      ParameterList &list = (*processes.insert(ProcessMap::value_type( DISTRIBUTION_ADD, ParameterList() )).first).second;
      list.push_back(ACCOUNT_NUMBER);
   }
   {
      ParameterList &list = (*processes.insert(ProcessMap::value_type( LOCKED_IN_INFORMATION, ParameterList() )).first).second;
      list.push_back(ACCOUNT_NUMBER);
   }

	{
      ParameterList &list = (*processes.insert(ProcessMap::value_type( CONTRACT_INFORMATION, ParameterList() )).first).second;
      list.push_back(ACCOUNT_NUMBER);
   }

	{
      ParameterList &list = (*processes.insert(ProcessMap::value_type( GUARANTEE_TRANSACTION, ParameterList() )).first).second;
      list.push_back(ACCOUNT_NUMBER);
   }

	{
      ParameterList &list = (*processes.insert(ProcessMap::value_type( RESP_INFORMATION, ParameterList() )).first).second;
      list.push_back(ACCOUNT_NUMBER);
   }

	{
      ParameterList &list = (*processes.insert(ProcessMap::value_type( RESP_TRANS_INFORMATION, ParameterList() )).first).second;
      list.push_back(ACCOUNT_NUMBER);
   }

	{
      ParameterList &list = (*processes.insert(ProcessMap::value_type( LIF_INFO_PROCESS, ParameterList() )).first).second;
      list.push_back(ACCOUNT_NUMBER);
   }

	{
      ParameterList &list = (*processes.insert(ProcessMap::value_type( RRIF_INFO_PROCESS, ParameterList() )).first).second;
      list.push_back(ACCOUNT_NUMBER);
   }
	{
      ParameterList &list = (*processes.insert(ProcessMap::value_type( LRIF_INFO_PROCESS, ParameterList() )).first).second;
      list.push_back(ACCOUNT_NUMBER);
   }

	{
      ParameterList &list = (*processes.insert(ProcessMap::value_type( LIF_ALLOCATION_PROCESS, ParameterList() )).first).second;
      list.push_back(ACCOUNT_NUMBER);
   }

	{
      ParameterList &list = (*processes.insert(ProcessMap::value_type( RRIF_ALLOCATION_PROCESS, ParameterList() )).first).second;
      list.push_back(ACCOUNT_NUMBER);
   }
	{
      ParameterList &list = (*processes.insert(ProcessMap::value_type( LRIF_ALLOCATION_PROCESS, ParameterList() )).first).second;
      list.push_back(ACCOUNT_NUMBER);
   }

	{
      ParameterList &list = (*processes.insert(ProcessMap::value_type( HYPO_REDEMPTION_PROCESS, ParameterList() )).first).second;
      list.push_back(ACCOUNT_NUMBER);
   }

	{
      ParameterList &list = (*processes.insert(ProcessMap::value_type( REDEMPTION_DETAIL, ParameterList() )).first).second;
      list.push_back(ACCOUNT_NUMBER);
	  list.push_back(FUND);
      list.push_back(CLASS);
   }

   processes.insert(ProcessMap::value_type( TRANSACTION_PROCESSING_MENU, ParameterList() ));

   processes.insert(ProcessMap::value_type( CHOOSE_MANAGE_COMP, ParameterList() ));

   processes.insert(ProcessMap::value_type( TAX_RATE_INFORMATION, ParameterList() ));

   processes.insert(ProcessMap::value_type( PATCH_ORDER_ENTRY_INFO, ParameterList() ));

   processes.insert(ProcessMap::value_type( AMS_GLOBAL_ALLOCATION, ParameterList() ));

   m_ParameterName.SetWindowText("");
   m_ParameterValue.SetWindowText("");
   m_ParameterValue.EnableWindow(FALSE);

   m_ParameterList.InsertColumn(0, "Parameter", LVCFMT_LEFT, 137);
   m_ParameterList.InsertColumn(1, "Value", LVCFMT_LEFT, 137);

   refreshProcessList();
   refreshParameterList();
	setSessionParameter();





	return TRUE;  // return TRUE  unless you set the focus to a control
}

//-----------------------------------------------------------------------
void CIFastCsiTestDlg::setSessionParameter()
{

	std::string sesstionTyp,sessionParam;

   HKEY hSessionKey; // handle to the session key
   if( ERROR_SUCCESS != RegOpenKey(HKEY_LOCAL_MACHINE, "SOFTWARE\\DST\\MFDSTC\\CONFIG\\Csi\\", &hSessionKey) )
   {
      return;
   }

   DWORD size, type;
   // find the size of the Session Name
   if( ERROR_SUCCESS == RegQueryValueEx(hSessionKey, "Type", NULL, &type, NULL, &size ) || type!=REG_SZ )
   {
      //  get Session Name
      char *cstrValue = new char[size];
      if( ERROR_SUCCESS == RegQueryValueEx(hSessionKey, "Type", NULL, &type, (LPBYTE)cstrValue, &size ) )
      {
         sesstionTyp = std::string(cstrValue);
      }
      delete[] cstrValue;
   }

   // find the size of the Session Param
   if( ERROR_SUCCESS == RegQueryValueEx(hSessionKey, "Param", NULL, &type, NULL, &size ) || type!=REG_SZ )
   {
      //  get Session Param
      char *cstrValue = new char[size];
      if( ERROR_SUCCESS == RegQueryValueEx(hSessionKey, "Param", NULL, &type, (LPBYTE)cstrValue, &size ) )
      {
         sessionParam = std::string(cstrValue);
      }
      delete[] cstrValue;
   }
   RegCloseKey(hSessionKey);
   CsiSession::getInstance().setSessionConfig( m_hWnd,sesstionTyp,sessionParam,"cfxint" );





} 
void CIFastCsiTestDlg::refreshProcessList()
{
   ProcessMap::iterator &i = processes.begin();
   while (i != processes.end())
   {
      m_ProcessList.AddString((*i).first.c_str());
      i++;
   }

   m_ProcessList.SetCurSel(0);
}

void CIFastCsiTestDlg::refreshParameterList()
{
   m_ParameterList.DeleteAllItems();
   m_ParameterName.SetWindowText("");
   m_ParameterValue.SetWindowText("");
   m_ParameterValue.EnableWindow(FALSE);

   int index = m_ProcessList.GetCurSel();

   if ( index == LB_ERR )
      return;

   char *strBuffer = new char[m_ProcessList.GetTextLen(index)+1];
   m_ProcessList.GetText(index, strBuffer);

   ProcessMap::iterator &processMapIterator = processes.find(strBuffer);
   delete[] strBuffer;

   if (processMapIterator == processes.end())
      return;

   ParameterList list = (*processMapIterator).second;
   ParameterList::iterator &pli = list.begin();

   int n=0;
   while (pli != list.end())
   {
      ParameterMap::iterator &pmi = parameters.find((*pli).c_str());

      if (pmi == parameters.end())
      {
         pmi = parameters.insert(ParameterMap::value_type((*pli).c_str(), "?")).first;
      }

      m_ParameterList.InsertItem(n, (*pmi).first.c_str());
      m_ParameterList.SetItemText(n, 1, (*pmi).second.c_str());
      pli++;
      n++;
   }
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CIFastCsiTestDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CIFastCsiTestDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CIFastCsiTestDlg::OnExecute() 
{

   CWaitCursor wait;
	// TODO: Add your control notification handler code here
   CsiSession& csiSession = CsiSession::getInstance();

   int itemCount = m_ParameterList.GetItemCount();

   for (int i=0; i<itemCount; i++)
   {
      char parameterName[128];
      m_ParameterList.GetItemText(i, 0, parameterName, 128);

      char parameterValue[128];
      m_ParameterList.GetItemText(i, 1, parameterValue, 128);
      csiSession.setParameter(parameterName, parameterValue);
   }

   int index = m_ProcessList.GetCurSel();
   if ( index == LB_ERR )
      return;

   char processName[128];
   m_ProcessList.GetText(index, processName);

   csiSession.executeProcess(processName);
   csiSession.clearParameters();
	
}

void CIFastCsiTestDlg::OnSelchangeProcessList() 
{
	// TODO: Add your control notification handler code here
	refreshParameterList();
}

void CIFastCsiTestDlg::OnDblclkProcessList() 
{
	// TODO: Add your control notification handler code here
	
}

void CIFastCsiTestDlg::OnItemchangedParameterList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	
   int index = m_ParameterList.GetNextItem(-1, LVNI_SELECTED);

   if (index == -1)
   {
      m_ParameterName.SetWindowText("");
      m_ParameterValue.SetWindowText("");
      m_ParameterValue.EnableWindow(FALSE);
   }
   else
   {

      char parameterName[128];
      m_ParameterList.GetItemText(index, 0, parameterName, 128);
      m_ParameterName.SetWindowText(parameterName);

      m_ParameterValue.EnableWindow(TRUE);
      char parameterValue[128];
      m_ParameterList.GetItemText(index, 1, parameterValue, 128);
      m_ParameterValue.SetWindowText(parameterValue);
   }
	*pResult = 0;
}

void CIFastCsiTestDlg::OnChangeParameterValue() 
{
	// TODO: Add your control notification handler code here
	
   int index = m_ParameterList.GetNextItem(-1, LVNI_SELECTED);

   if (index == -1)
      return;

   char parameterName[128];
   m_ParameterList.GetItemText(index, 0, parameterName, 128);
   ParameterMap::iterator &i = parameters.find(parameterName);

   char parameterValue[128];
   m_ParameterValue.GetWindowText(parameterValue, 128);
   m_ParameterList.SetItemText(index, 1, parameterValue);

   (*i).second = parameterValue;

}

void CIFastCsiTestDlg::OnDestroy() 
{
	CDialog::OnDestroy();

	// TODO: Add your message handler code here

//   CsiSession::cleanupInstance();
   CsiSession::getInstance().cleanup();
	
}


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcsitest/IFastCsiTestDlg.cpp-arc  $
// 
//    Rev 1.2   Feb 05 2004 15:33:22   SMITHDAV
// Added host parameter to support dynamic host.
// 
//    Rev 1.1   Dec 02 2003 14:05:16   YINGBAOL
// attachmates enhancement
// 
//    Rev 1.0   Jul 30 2003 14:37:52   PURDYECH
// Initial Revision
 * 
 *    Rev 1.7   Jan 29 2002 10:56:52   JANKAREN
 * Added Redemption Detail
 * 
 *    Rev 1.6   Nov 28 2001 09:59:06   YINGBAOL
 * add AMS Global allocation
 * 
 *    Rev 1.5   May 23 2000 11:03:28   YINGBAOL
 * transaction process menu added
 * 
 *    Rev 1.4   May 05 2000 10:28:12   YINGBAOL
 * add patch order information 
 * 
 *    Rev 1.3   Apr 17 2000 17:12:40   YINGBAOL
 * added redemption
 * 
 *    Rev 1.2   Apr 03 2000 15:48:48   YINGBAOL
 * add RIF LIF Allocation
 * 
 *    Rev 1.1   Mar 07 2000 09:41:20   YINGBAOL
 * Change Synchronize
 * 
 * 
 *
 */