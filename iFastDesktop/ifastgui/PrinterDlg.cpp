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
// ^FILE   : PrinterDlg.cpp
// ^AUTHOR : 
// ^DATE   : Dec 8, 2002
//
// ^CLASS    : PrinterDlg
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

#ifndef PRINTERDLG_H
   #include "PrinterDlg.h"
#endif

#include <ifastbp\printerprocessincludes.h>
//#include <ifastbp\ftpprocessincludes.h>

extern CLASS_IMPORT const I_CHAR* CMD_GUI_PRINTER_LIST;

#include <bfproc\concretedialogcreator.hpp>
static ConcreteDialogCreator< PrinterDlg > dlgCreator( CMD_GUI_PRINTER_LIST );

#ifdef _DEBUG
   #define new DEBUG_NEW
   #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

namespace
{
   const I_CHAR * const CLASSNAME               = I_( "PrinterDlg" );
   const I_CHAR * const NO                      = I_( "N" );
   const I_CHAR * const LV_PRINTER_LIST         = I_( "PrinterList" );
}

namespace CND
{  // Conditions used
//CP20030319   extern CLASS_IMPORT const long GUI_ERR_UNKNOWN_EXCEPTION;
}

//******************************************************************************
// Constructor
//******************************************************************************
PrinterDlg::PrinterDlg( CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: BaseMainDlg( PrinterDlg::IDD, pParent, pGIC, pGIParent, rCommand, CLASSNAME )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );   
   //{{AFX_DATA_INIT( PrinterDlg )
   //}}AFX_DATA_INIT
   
}

//******************************************************************************
// Destructor
//******************************************************************************
PrinterDlg::~PrinterDlg ()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************
// Called by MFC framework to exchange and validate dialog data
//******************************************************************************
void PrinterDlg::DoDataExchange( CDataExchange* pDX )
{
   BaseMainDlg::DoDataExchange( pDX );
   //{{AFX_DATA_MAP( PrinterDlg )    
   //}}AFX_DATA_MAP
}

//******************************************************************************
// MFC Message Map
//******************************************************************************

BEGIN_MESSAGE_MAP( PrinterDlg, BaseMainDlg )
//{{AFX_MSG_MAP( PrinterDlg )
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//******************************************************************************
// Initialization of Dialog, get InterProcess Global data and sets up the 
// caption in the title bar.
//******************************************************************************
BOOL PrinterDlg::OnInitDialog() 
{
   TRACE_METHOD( CLASSNAME, ONINITDIALOG );
   BaseMainDlg::OnInitDialog();
   return(TRUE);  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}

//******************************************************************************
// Call by based architecture.  Controls are initialized here by calling the
// addControls() method.  The More button is enable/disable based on the CBO
// data.
//******************************************************************************
void PrinterDlg::OnPostInitDialog()
{
   CWaitCursor wait;
   AddListControl( CLASSNAME, IDC_LV_PRINTERS, LV_PRINTER_LIST, ifds::PrinterHeadingSet, 
                   IFASTBP_PROC::PRINTER_LIST, 0, false, LISTFLAG_NOT_AUTO_ADD);    
   LoadListControl ( IDC_LV_PRINTERS );
   //if ( _dstrLocal == NO )
      //GetDlgItem ( IDC_RDO_LOCAL )->EnableWindow ( false );
   TRACE_METHOD( CLASSNAME, I_( "OnPostInitDialog" ) );
}

//******************************************************************************
// doInit method is not used.
//******************************************************************************
SEVERITY PrinterDlg::doInit()
{
   getParameter ( PRINTER::LOCAL, _dstrLocal );
   return ( NO_CONDITION );
}

//******************************************************************************
// Overrides canCancel so that discard dialog does not show up.
// @returns bool - true.
//******************************************************************************
bool PrinterDlg::canCancel() 
{   
   return(true);
}

//******************************************************************************
// Method to refresh dialog controls
// @param   GenericInterface *rpGICaller - pointer to the calling object
// @param   const I_CHAR *szOriginalCommand - Not used in this case, but 
//                      can be used to instruct special processing.
//******************************************************************************
bool PrinterDlg::doRefresh( GenericInterface * rpGICaller, 
                                  const I_CHAR * szOriginalCommand )
{
   return(true);
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/PrinterDlg.cpp-arc  $
// 
//    Rev 1.2   Sep 15 2005 15:14:40   popescu
// Incident#403519 - added CLASSNAME as the fifth parameter to  BaseMainDlg constructor
// 
//    Rev 1.1   Mar 21 2003 18:39:34   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.0   Dec 08 2002 22:16:22   HSUCHIN
// Initial Revision
 */


