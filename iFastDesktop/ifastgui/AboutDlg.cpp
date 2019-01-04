//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by DST Systems, Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 1997-1998 by DST Systems, Inc.
//
//******************************************************************************
//
// ^FILE   : AboutDlg.cpp
// ^AUTHOR : Terry Erickson
// ^DATE   : 3/31/98
//
// ----------------------------------------------------------
//
// ^CLASS    : AboutDlg
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"

#include "MFDSTC.h"
#include "AboutDlg.h"
#include <ifsupp/AboutPropSheet.h>

#include <ifastcbo\version_app.hpp>

#ifdef _DEBUG
   #define new DEBUG_NEW
   #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

namespace
{
   const unsigned long MAXBUFSIZE = 256;
   const I_CHAR *NUL_INSTANCE   = I_( "Module Not Found" );
   const I_CHAR *NOT_AVAILABLE  = I_( "Not Available" );
}

namespace CND
{
}
/////////////////////////////////////////////////////////////////////////////
// AboutDlg dialog
AboutDlg::AboutDlg(CWnd* pParent /*=NULL*/)
: CDialog(AboutDlg::IDD, pParent)
{
   //{{AFX_DATA_INIT(AboutDlg)
   // NOTE: the ClassWizard will add member initialization here
   //}}AFX_DATA_INIT
}

void AboutDlg::DoDataExchange(CDataExchange* pDX)
{
   CDialog::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(AboutDlg)
   //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(AboutDlg, CDialog)
//{{AFX_MSG_MAP(AboutDlg)
ON_BN_CLICKED(IDC_BTN_DETAILS, OnBtnDetails)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// AboutDlg message handlers

BOOL AboutDlg::OnInitDialog()
{
   CDialog::OnInitDialog();
   SetDlgItemText( IDC_TXT_VERSION, ifds::getAppVersion().c_str() );

   CString revisionNum;
   revisionNum.Format(_T("%lu"), ifds::getAppBuildNumber());
   SetDlgItemText( IDC_ST_REVISION, revisionNum);

   return(TRUE);  //Success
}

void AboutDlg::OnBtnDetails()
{
   CWaitCursor waitCursor;

//   AboutDetailsDlg detailsDlg( this );
//   detailsDlg.DoModal();
   AboutPropSheet::Display();
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/AboutDlg.cpp-arc  $
 * 
 *    Rev 1.6   Feb 13 2012 15:19:28   if991250
 * Showing the revision number
 * 
 *    Rev 1.5   Dec 05 2011 09:00:24   purdyech
 * ControlTextRewriter Logic
 *
 *    Rev 1.4   Feb 06 2009 14:59:10   purdyech
 * Interim CheckIn for ZTS Support (Chris is goin' on vacation!)
 *
 *    Rev 1.3   Sep 23 2003 08:25:28   PURDYECH
 * Use ifds::getAppVersion to display version string.
 *
 *    Rev 1.2   Mar 21 2003 18:30:08   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 *
 *    Rev 1.1   Oct 09 2002 23:55:26   PURDYECH
 * PVCS Database Conversion
 *
 *    Rev 1.0   Feb 15 2000 11:01:02   SMITHDAV
 * Initial revision.
 *
 *    Rev 1.1   Jul 08 1999 10:04:24   SMITHDAV
 * Modify revision history commaent format to old
 * style comment -- I can't seem to get new style comments to work.
 *
 */
