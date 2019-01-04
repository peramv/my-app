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
// ^FILE   : ConfigSelectionDlg.cpp
//
// ----------------------------------------------------------
//
// ^CLASS    : ConfigSelectionDlg
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"

#include "mfdstc.h"
#include "ConfigSelectionDlg.h"
#include "SiteConfig.h"

#ifdef _DEBUG
   #define new DEBUG_NEW
   #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

namespace
{
   //Used in list control
   const I_CHAR *COL_HEADER1 = I_( "Configuration" );
   const I_CHAR *COL_HEADER2 = I_( "File" );

   const I_CHAR *NUL_INSTANCE   = I_( "<<Not Loaded>>" );
   const I_CHAR *NOT_AVAILABLE  = I_( "" );
}

namespace CND
{
}

//******************************************************************************
//              Public Methods
//******************************************************************************

ConfigSelectionDlg::ConfigSelectionDlg(CWnd* pParent /*=NULL*/)
: CDialog(ConfigSelectionDlg::IDD, pParent)
, dstrFileName_(I_(""))
, m_itemCount(0)
{
   //{{AFX_DATA_INIT(ConfigSelectionDlg)
   // NOTE: the ClassWizard will add member initialization here
   //}}AFX_DATA_INIT
}

ConfigSelectionDlg::ConfigSelectionDlg(const DString& dstrFileName, CWnd* pParent /*=NULL*/)
: CDialog(ConfigSelectionDlg::IDD, pParent)
, dstrFileName_(dstrFileName)
, m_itemCount(0)
{
   //{{AFX_DATA_INIT(ConfigSelectionDlg)
   // NOTE: the ClassWizard will add member initialization here
   //}}AFX_DATA_INIT

   // the filespec can be in three forms
   // 1) a specific XML file
   // 2) a file glob
   // 3) a file of filespecs if the filepsec starts with '@'

   addFileToList( dstrFileName );

}

void ConfigSelectionDlg::addFileToList( const DString& dstrFileSpec ) {
   // load the file list
   DWORD dw = 0;
   bool bIsFileList = false;
   DString dstrFileName = dstrFileSpec;
   if( dstrFileSpec.substr(0,1) == I_("@") ) {
      bIsFileList = true;
      dstrFileName = dstrFileSpec.substr(1);
   }
   I_CHAR szDrive[MAX_PATH];
   I_CHAR szDir[MAX_PATH];
   I_CHAR szName[MAX_PATH];
   I_CHAR szExt[MAX_PATH];
   i_splitpath( dstrFileName.c_str(), szDrive, szDir, szName, szExt );
   WIN32_FIND_DATA wfd = {0};
   HANDLE hFind = FindFirstFile( dstrFileName.c_str(), &wfd);
   if( INVALID_HANDLE_VALUE != hFind ) {
      do {
         if( bIsFileList ) {
            DStringA dstrA = dstrFileName.asA();
            FILE* pFile = fopen( dstrA.c_str(), "r");
            char szBuf[256];
            while( pFile != NULL &&
                   fgets(szBuf, sizeof(szBuf)/sizeof(szBuf[0]), pFile ) ) {
               for( int i = 0; szBuf[i] != 0x00; ++i ) {
                  if( szBuf[i] == 0x0a || szBuf[i] == 0x0d ) {
                     szBuf[i] = 0x00;
                     break;
                  }
               }
               DStringA a = szBuf;
               DString dstrFileName = a;
               dstrFileName.strip();
               if( dstrFileName != I_("") &&
                   dstrFileName.substr(1) != I_("#") ) {
                  addFileToList( dstrFileName );
               }
            }
            FindClose(hFind);
            return;   
         }
         
         CString strFile = szDrive;
         strFile += szDir;
         strFile += wfd.cFileName;
         CString strDesc = "Invalid XML File";
         try {
            site::SiteConfig sc;
            sc.init(DStringA(DString(strFile)).c_str(), NULL);
            strDesc = sc.getDescription().c_str();
            strDesc.Trim();
            if( strDesc == _T("") ) {
               strDesc = wfd.cFileName;
            }
         }
         catch( ... ) {}
         // set the dstrFileName_ to this file.  If there is only one valid file in the glob 
         // then this will have that value, and a call to getFileName() will return this value.
         // useful if the user specified a wildcard that only matches one file.
         dstrFileName_ = strFile;
         mapConfigs_[strFile] = strDesc;
      } while( FindNextFile(hFind,&wfd) );
      FindClose(hFind);
   }
   else {
      dw = GetLastError();
   }
}

void ConfigSelectionDlg::DoDataExchange(CDataExchange* pDX)
{
   CDialog::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(ConfigSelectionDlg)
   DDX_Control(pDX, IDC_CONFIG_LIST, m_configList);
   //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(ConfigSelectionDlg, CDialog)
//{{AFX_MSG_MAP(ConfigSelectionDlg)
//ON_BN_CLICKED(IDC_BTN_SAVE, OnBtnSave)
ON_NOTIFY(NM_DBLCLK, IDC_CONFIG_LIST, OnDblclkLbConfigList)
//}}AFX_MSG_MAP
ON_NOTIFY(LVN_ITEMCHANGED, IDC_CONFIG_LIST, OnLvnItemchangedLbConfigList)
END_MESSAGE_MAP()

//******************************************************************************
//              Protected Methods
//******************************************************************************

BOOL ConfigSelectionDlg::OnInitDialog()
{
   CDialog::OnInitDialog();

   m_configList.InsertColumn( 0, COL_HEADER1, LVCFMT_LEFT, 160 );
   m_configList.InsertColumn( 1, COL_HEADER2, LVCFMT_LEFT, 160 );
   DWORD dwStyleEx = m_configList.GetExtendedStyle();
   m_configList.SetExtendedStyle( dwStyleEx | LVS_EX_FULLROWSELECT);

   for( CONFIGFILEMAP_ITER it = mapConfigs_.begin(); it != mapConfigs_.end(); ++it ) {
      int idx = m_configList.InsertItem(m_itemCount++,I_(""));
      m_configList.SetItemText(idx,0,(*it).second);
      m_configList.SetItemText(idx,1,(*it).first);
   }
   return(TRUE);  // Success
}

void ConfigSelectionDlg::OnDblclkLbConfigList(NMHDR* pNMHDR, LRESULT* pResult) 
{
   int urlIndex = m_configList.GetNextItem( -1, LVNI_SELECTED );
   if( -1 == urlIndex ) {
      return;
   }
   // Invoking OnOK() will cause the selection dialog to close on a double-click
   // and return the double-clicked item as the selected configuration.
   // This is the 'expected' behaviour, but when I tested it I discovered that
   // the user has no feedback about *which* configuration was actually selected
   // on the Login screen.  I think that is considerable scope for confusion on the
   // part of our users, so I've commented out the invocation.  Perhaps we need
   // to introduce a new configuration field (WindowTitlePrefix?) that would prefix
   // the titlebar text on each window to provide context for the users
   //   CP 20101203
   //
   // Uncommenting the OnOK() because CP changed his mind.
   //   DS 20180402
   OnOK();
}
//******************************************************************************
//              Private Methods
//******************************************************************************


//*****************************************************************************
//
// ^PRIVATE METHOD : ConfigSelectionDlg::OnOK()
//
// ^DESCRIPTION :
//      Save the Listbox settings
//
// ^PARAMETERS  :
//    ^^void
//
// ^RETURNS     :
//    ^^void
//
// ^THROWS      :
//
// ^EXAMPLE     :
//
//*****************************************************************************

void ConfigSelectionDlg::OnOK() 
{
   int idx = m_configList.GetNextItem(-1,LVNI_SELECTED);
   CString strFile;
   strFile = m_configList.GetItemText(idx,1);
   dstrFileName_ = strFile;
//   m_configList.SaveSettings( ABOUT_DETAILS_DLG, AB_INFOLIST );
   CDialog::OnOK();
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/ConfigSelectionDlg.cpp-arc  $
// 
//    Rev 1.3   Dec 03 2010 07:54:52   purdyech
// Changes to implement view performance tracking and crash handling
// 
//    Rev 1.2   Jan 12 2010 13:49:52   purdyech
// Support @ syntax for configuration file names (file'o'files)
// Display filename as description if description is blank
// 
//    Rev 1.1   Aug 25 2009 08:39:46   purdyech
// show multiple files in selection dialog
 * 
 *    Rev 1.11   Feb 06 2009 14:56:00   purdyech
 * Interim CheckIn for ZTS Support (Chris is goin' on vacation!)
 * 
 *    Rev 1.10   Nov 21 2007 07:37:44   purdyech
 * Added conditional support for exception processing.
 * 
 *    Rev 1.9   Jun 24 2007 09:05:16   purdyech
 * Added AWD AutoLogon feature to desktop
 * 
 *    Rev 1.8   May 14 2007 15:12:46   purdyech
 * PTS 820423 - Extensive changes to Component Dialog
 * 
 *    Rev 1.7   Nov 14 2004 15:00:24   purdyech
 * PET910 - .NET Conversion
 * 
 *    Rev 1.6   May 26 2003 15:32:28   PURDYECH
 * fnGetModuleInfo is no longer exported so we will explicitly reference it 
 * 
 *    Rev 1.5   Mar 21 2003 18:29:50   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.4   Oct 09 2002 23:55:24   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.3   May 28 2002 12:19:44   PURDYECH
 * BFData Implementation - Phase II
 * 
 *    Rev 1.2   22 May 2002 19:15:16   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.1   03 Jul 2001 15:55:04   SMITHDAV
 * Add revision list.
 * 
 *    Rev 1.0   Feb 15 2000 11:01:02   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.2   Jul 12 1999 17:30:56   PRAGERYA
 * DataDictionary constants replaced by ConfigurationConstants
 * 
 *    Rev 1.1   Jul 08 1999 10:04:24   SMITHDAV
 * Modify revision history commaent format to old
 * style comment -- I can't seem to get new style comments to work.
 *
 */


void ConfigSelectionDlg::OnLvnItemchangedLbConfigList(NMHDR *pNMHDR, LRESULT *pResult) {
   LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
   // TODO: Add your control notification handler code here
   *pResult = 0;
}

