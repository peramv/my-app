// DiscardMsgDlg.cpp : implementation file
//

#include "stdafx.h"
#include "mfdstc.h"
#include "DiscardMsgDlg.h"

#ifdef _DEBUG
   #define new DEBUG_NEW
   #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// DiscardMsgDlg dialog


DiscardMsgDlg::DiscardMsgDlg(CWnd* pParent /*=NULL*/, UINT msgA, UINT msgB, UINT btn1Caption)
: CDialog(DiscardMsgDlg::IDD, pParent)
{
   //{{AFX_DATA_INIT(DiscardMsgDlg)
   m_MessageA.LoadString( msgA );
   m_MessageB.LoadString( msgB );
   btn1.LoadString( btn1Caption );
   btn2 = "";
   //}}AFX_DATA_INIT
}

DiscardMsgDlg::DiscardMsgDlg(CWnd* pParent /*=NULL*/, UINT msgA, UINT msgB, UINT btn1Caption, UINT btn2Caption)
: CDialog(DiscardMsgDlg::IDD, pParent)
{
   //{{AFX_DATA_INIT(DiscardMsgDlg)
   m_MessageA.LoadString( msgA );
   m_MessageB.LoadString( msgB );
   btn1.LoadString( btn1Caption );
   btn2.LoadString( btn2Caption );
   //}}AFX_DATA_INIT
}

void DiscardMsgDlg::DoDataExchange(CDataExchange* pDX)
{
   CDialog::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(DiscardMsgDlg)
   DDX_Control(pDX, IDC_INFOICON, m_Icon);
   DDX_Text(pDX, IDC_DISCARD_MSGA, m_MessageA);
   DDX_Text(pDX, IDC_DISCARD_MSGB, m_MessageB);
   //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(DiscardMsgDlg, CDialog)
//{{AFX_MSG_MAP(DiscardMsgDlg)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DiscardMsgDlg message handlers

BOOL DiscardMsgDlg::OnInitDialog() 
{
   CDialog::OnInitDialog();

   // TODO: Add extra initialization here
   m_Icon.SetIcon( LoadIcon( NULL, IDI_EXCLAMATION ) );
   if( !btn1.IsEmpty() )
   {
      GetDlgItem (IDOK)->SetWindowText(btn1);
   }
   if( !btn2.IsEmpty() )
   {
      GetDlgItem (IDCANCEL)->SetWindowText(btn2);
   }
   return(TRUE);  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}
