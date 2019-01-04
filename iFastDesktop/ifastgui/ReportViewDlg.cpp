//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by DST Canada, Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2002 by International Financial.
//
//******************************************************************************
//
// ^FILE   : ReportViewDlg.cpp
// ^AUTHOR : 
// ^DATE   : Dec 8, 2002
//
// ^CLASS    : ReportViewDlg
// ^SUBCLASS : BaseMainDlg
//
// ^CLASS DESCRIPTION : 
//
//******************************************************************************

#include "stdafx.h"

#ifndef IFASTGUI_H
   #include "mfdstc.h"
#endif

#ifndef ABSTRACTPROCESS_HPP
   #include <bfproc\AbstractProcess.hpp>
#endif

#ifndef REPORTVIEWDLG_H
   #include "ReportViewDlg.h"
#endif

#ifndef FTPCONNECTION_HPP
   #include "FTPConnection.hpp"
#endif

#include <ifastbp\reportviewprocessincludes.h>
//#include <ifastbp\ftpprocessincludes.h>

extern CLASS_IMPORT const I_CHAR* CMD_GUI_REPORT_VIEW;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_FTP_LOGON;

#include <bfproc\concretedialogcreator.hpp>
static ConcreteDialogCreator< ReportViewDlg > dlgCreator( CMD_GUI_REPORT_VIEW );

#ifdef _DEBUG
   #define new DEBUG_NEW
   #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

namespace
{
   const I_CHAR * const CLASSNAME               = I_( "ReportViewDlg" );
}

namespace CND
{  // Conditions used
//CP20030319   extern CLASS_IMPORT const long GUI_ERR_UNKNOWN_EXCEPTION;
}

//******************************************************************************
// Constructor
//******************************************************************************
ReportViewDlg::ReportViewDlg( CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: BaseMainDlg( ReportViewDlg::IDD, pParent, pGIC, pGIParent, rCommand, CLASSNAME )
, _dstrReportName ( NULL_STRING )
, _dstrReportPath ( NULL_STRING )
, _pFTPConnection ( NULL )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );   
   //{{AFX_DATA_INIT( ReportViewDlg )
   //}}AFX_DATA_INIT
   
}

//******************************************************************************
// Destructor
//******************************************************************************
ReportViewDlg::~ReportViewDlg ()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************
// Called by MFC framework to exchange and validate dialog data
//******************************************************************************
void ReportViewDlg::DoDataExchange( CDataExchange* pDX )
{
   BaseMainDlg::DoDataExchange( pDX );
   //{{AFX_DATA_MAP( ReportViewDlg ) 
   DDX_Control(pDX, IDC_RE_REPORT, m_re_report);
   //}}AFX_DATA_MAP
}

//******************************************************************************
// MFC Message Map
//******************************************************************************

BEGIN_MESSAGE_MAP( ReportViewDlg, BaseMainDlg )
//{{AFX_MSG_MAP( ReportViewDlg )
ON_BN_CLICKED( IDC_BTN_PRINT, OnBtnPrint )
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//******************************************************************************
// Initialization of Dialog, get InterProcess Global data and sets up the 
// caption in the title bar.
//******************************************************************************
BOOL ReportViewDlg::OnInitDialog() 
{
   TRACE_METHOD( CLASSNAME, ONINITDIALOG );
   BaseMainDlg::OnInitDialog();
   CString cstrCaption = GetBaseCaption().c_str();
   cstrCaption += I_(" ");
   cstrCaption += _dstrReportName.c_str();
   SetWindowText( cstrCaption );
   return(TRUE);  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}

//******************************************************************************
// Call by based architecture.  Controls are initialized here by calling the
// addControls() method.  The More button is enable/disable based on the CBO
// data.
//******************************************************************************
void ReportViewDlg::OnPostInitDialog()
{
   CWaitCursor wait;
   TRACE_METHOD( CLASSNAME, I_( "OnPostInitDialog" ) );

   DString dstrDescription;
   getParent()->getField ( this, BF::NullContainerId, ifds::Description, dstrDescription, false );
   
   GetDlgItem (IDC_RE_REPORT)->SetWindowText( dstrDescription.c_str() );
}

//******************************************************************************
// doInit method is not used.
//******************************************************************************
SEVERITY ReportViewDlg::doInit()
{
   getParameter ( REPORT_VIEW::REPORTNAME, _dstrReportName );
   getParameter ( REPORT_VIEW::REPORTPATH, _dstrReportPath );
   return ( NO_CONDITION );
}

//******************************************************************************
// Method to refresh dialog controls
// @param   GenericInterface *rpGICaller - pointer to the calling object
// @param   const I_CHAR *szOriginalCommand - Not used in this case, but 
//                      can be used to instruct special processing.
//******************************************************************************
bool ReportViewDlg::doRefresh( GenericInterface * rpGICaller, 
                                  const I_CHAR * szOriginalCommand )
{
   return(true);
}

//******************************************************************************
// Overrides canCancel so that discard dialog does not show up.
// @returns bool - true.
//******************************************************************************
bool ReportViewDlg::canCancel() 
{   
   return(true);
}

//******************************************************************************
//******************************************************************************
void ReportViewDlg::OnBtnPrint( )
{
   CDC dc;
   CPrintDialog dlg (FALSE);
   if (dlg.DoModal () == IDOK)
      dc.Attach (dlg.GetPrinterDC ());
   else 
      return;
   
// Describe print job to print spooler 
   DOCINFO docInfo; 
   docInfo.cbSize = sizeof(docInfo); 
   docInfo.fwType = 0; 
   docInfo.lpszDocName = _dstrReportName.c_str();
   docInfo.lpszOutput = NULL; 
   docInfo.lpszDatatype = NULL; 

// Start a document 
   
   if (!dc.StartDoc(&docInfo)) { 
      //AfxMessageBox("Couldn't print document."); 
      return; 
   } 

   //store the old map mode to restore later.
   int iOldMapMode = dc.GetMapMode();  

   //map to twips since richedit control uses TWIPS in FormatRange struct
   dc.SetMapMode(MM_TWIPS);            

   // ask printer for size of page printable.
   int nOffsetX = dc.GetDeviceCaps(PHYSICALOFFSETX); 
   int nOffsetY = -dc.GetDeviceCaps(PHYSICALOFFSETY); 
   int nHorzRes = dc.GetDeviceCaps(HORZRES); 
   int nVertRes = -dc.GetDeviceCaps(VERTRES); 

   // create the Crect for printing
   CRect rect(nOffsetX, nOffsetY, nHorzRes, nVertRes); 
   
   // conver the Crect from device units to logical units.
   dc.DPtoLP(&rect); 

   //reset the map mode inorder to print.
   dc.SetMapMode(iOldMapMode); 

   // set up the FormatRange struct for the rich edit control
   FORMATRANGE formatRange;      
   formatRange.hdc = dc.GetSafeHdc();
   formatRange.hdcTarget = dc.GetSafeHdc(); 
   formatRange.rc = rect; 
   formatRange.rcPage = rect; 

   //set to 0 to indicate the beginning of the text.
   long iFormatted = 0; 
   do //spool the pages  
   { 
      // start the new page.
      if (!dc.StartPage()) { 
//         AfxMessageBox("Error starting new page!"); 
         break; 
      } 
      //start from last printed text.
      formatRange.chrg.cpMin = iFormatted;      
      //-1 to format all. 
      formatRange.chrg.cpMax = -1;              
      //format the text to be printed
      iFormatted = m_re_report.FormatRange( &formatRange, TRUE ); 
      //Print the page
      m_re_report.DisplayBand(&rect);           
      // end of page
      dc.EndPage();
      //error with formatting 
      if (iFormatted < 0)  {
         break;                  
      } 
   }  while ( iFormatted < m_re_report.GetTextLength() );

   //clean up the formatRange struct so that the rich edit
   //no longer outputs to the printer.
   m_re_report.FormatRange( NULL, TRUE );
   
   // Print
   dc.EndDoc();    
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/ReportViewDlg.cpp-arc  $
// 
//    Rev 1.4   Sep 15 2005 15:14:52   popescu
// Incident#403519 - added CLASSNAME as the fifth parameter to  BaseMainDlg constructor
// 
//    Rev 1.3   Mar 21 2003 18:39:58   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.2   Dec 10 2002 13:36:10   HSUCHIN
// get data from process.
// 
//    Rev 1.1   Dec 10 2002 09:57:22   HSUCHIN
// removed ftp connection
// 
//    Rev 1.0   Dec 08 2002 22:16:30   HSUCHIN
// Initial Revision
 */


