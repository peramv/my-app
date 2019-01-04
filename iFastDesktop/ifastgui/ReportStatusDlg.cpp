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
// ^FILE   : ReportStatusDlg.cpp
// ^AUTHOR : 
// ^DATE   : Nov 21, 2002
//
// ^CLASS    : ReportStatusDlg
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

#ifndef ReportStatusDlg_H
   #include "ReportStatusDlg.h"
#endif

#ifndef DSTCOMMONFUNCTION_HPP
   #include <ifastcbo\DSTCommonFunction.hpp>
#endif

#ifndef DSTCLISTCTRL_H
   #include <uibase\DSTListCtrl.h>
#endif

#ifndef DSTCWORKSESSION_HPP
   #include <ifastcbo\DSTCWorkSession.hpp>
#endif

#ifndef FTPCONNECTION_HPP
   #include "FTPConnection.hpp"
#endif

#include <ifastbp\reportstatusprocessincludes.h>
#include <ifastbp\reportviewprocessincludes.h>
#include <ifastbp\printerprocessincludes.h>
#include <ifastbp\ftplogonprocessincludes.h>

extern CLASS_IMPORT const I_CHAR* CMD_GUI_REPORT_STATUS;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_REPORT_VIEW;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_PRINTER_LIST;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_FTP_LOGON;

#include <bfproc\concretedialogcreator.hpp>
static ConcreteDialogCreator< ReportStatusDlg > dlgCreator( CMD_GUI_REPORT_STATUS );

#ifdef _DEBUG
   #define new DEBUG_NEW
   #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

namespace
{
   const I_CHAR * const CLASSNAME               = I_( "ReportStatusDlg" );
   const I_CHAR * const LV_REPORT_STATUS        = I_( "ReportStatusList" );      
   const I_CHAR * const LV_REPORT_PARAM         = I_( "ReportParamList" );
   const I_CHAR * const YES                     = I_( "Y" );
   const I_CHAR * const NO                      = I_( "N" );      
   const UINT REPORT_STATUS_CRITERIA = 1;
}

namespace CND
{  // Conditions used
//CP20030319   extern CLASS_IMPORT const long GUI_ERR_UNKNOWN_EXCEPTION;
}

//******************************************************************************
// Constructor
//******************************************************************************
ReportStatusDlg::ReportStatusDlg( CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: BaseMainDlg( ReportStatusDlg::IDD, pParent, pGIC, pGIParent, rCommand, CLASSNAME )
, _pFTPConnection ( NULL )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );   
   //{{AFX_DATA_INIT( ReportStatusDlg )
   //}}AFX_DATA_INIT
   
}

//******************************************************************************
// Destructor
//******************************************************************************
ReportStatusDlg::~ReportStatusDlg ()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************
// Called by MFC framework to exchange and validate dialog data
//******************************************************************************
void ReportStatusDlg::DoDataExchange( CDataExchange* pDX )
{
   BaseMainDlg::DoDataExchange( pDX );
   //{{AFX_DATA_MAP( ReportStatusDlg ) 
   //}}AFX_DATA_MAP
}

//******************************************************************************
// MFC Message Map
//******************************************************************************

BEGIN_MESSAGE_MAP( ReportStatusDlg, BaseMainDlg )
//{{AFX_MSG_MAP( ReportStatusDlg )
ON_BN_CLICKED( IDC_BTN_SEARCH, OnBtnSearch )
ON_BN_CLICKED( IDC_BTN_VIEW, OnBtnView )
ON_BN_CLICKED( IDC_BTN_PRINT, OnBtnPrint )
ON_BN_CLICKED( IDC_BTN_MORE, OnBtnMore )
ON_BN_CLICKED( IDC_BTN_REFRESH, OnBtnSearch )
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//******************************************************************************
// Initialization of Dialog, get InterProcess Global data and sets up the 
// caption in the title bar.
//******************************************************************************
BOOL ReportStatusDlg::OnInitDialog() 
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
void ReportStatusDlg::OnPostInitDialog()
{
   CWaitCursor wait;
   TRACE_METHOD( CLASSNAME, I_( "OnPostInitDialog" ) );
   addControls( );
   enableButtons ( false );

}

//******************************************************************************
// doInit method is not used.
//******************************************************************************
SEVERITY ReportStatusDlg::doInit()
{
   return ( NO_CONDITION );
}

//******************************************************************************
// This method sets up the custom controls to the correct data set.
//******************************************************************************
void ReportStatusDlg::addControls( )
{

   AddControl( CTRL_COMBO,  IDC_CMB_MGMT_CO, IFASTBP_PROC::REPORT_STATUS_CRITERIA, ifds::CompanyId, CTRLFLAG_INITCOMBO_BY_SUB_LIST, REPORT_STATUS_CRITERIA );
   AddControl( CTRL_DATE,  IDC_DTP_START_DATE, IFASTBP_PROC::REPORT_STATUS_CRITERIA, ifds::StartDate, CTRLFLAG_DEFAULT, REPORT_STATUS_CRITERIA );

   AddListControl( CLASSNAME, IDC_LV_REPORTS, LV_REPORT_STATUS, ifds::ReportStatusHeadingSet, 
                   IFASTBP_PROC::REPORT_STATUS_LIST, 0, true, LISTFLAG_NOT_AUTO_ADD | LISTFLAG_TIMER );   
   AddListControl( CLASSNAME, IDC_LV_REPORT_PARAM, LV_REPORT_PARAM, ifds::ReportStatusParamHeadingSet, 
                   IFASTBP_PROC::REPORT_PARAM_LIST, IDC_LV_REPORTS, false, LISTFLAG_NOT_AUTO_ADD);   
   ConnectControlsToData ( REPORT_STATUS_CRITERIA );  
   LoadControls( REPORT_STATUS_CRITERIA );   
}

//******************************************************************************
// Method to refresh dialog controls
// @param   GenericInterface *rpGICaller - pointer to the calling object
// @param   const I_CHAR *szOriginalCommand - Not used in this case, but 
//                      can be used to instruct special processing.
//******************************************************************************
bool ReportStatusDlg::doRefresh( GenericInterface * rpGICaller, 
                                  const I_CHAR * szOriginalCommand )
{
   return(true);
}

//******************************************************************************
//******************************************************************************
void ReportStatusDlg::OnBtnSearch ( )
{
   TRACE_METHOD( CLASSNAME, I_("OnBtnSearch") );

   CWaitCursor wait;
   SetMessageStatusBar( TXT_LOAD_REPORTS );
   getParent()->performSearch( this, IFASTBP_PROC::REPORT_STATUS_LIST, SEARCH_START );
   const DString *crtKey = &getParent()->getCurrentListItemKey( this, IFASTBP_PROC::REPORT_STATUS_LIST );
   LoadListControl ( IDC_LV_REPORTS );
   if ( *crtKey != NULL_STRING )
      enableButtons ( true );
   else
      enableButtons ( false );
   GetDlgItem( IDC_BTN_MORE )->EnableWindow( getParent()->doMoreRecordsExist( this, IFASTBP_PROC::REPORT_STATUS_LIST ) );
   SetMessageStatusBar(NULL_STRING);    
}

//******************************************************************************
//******************************************************************************
void ReportStatusDlg::OnBtnMore  ( )
{
   TRACE_METHOD( CLASSNAME, ONBTNMORE );

   CWaitCursor wait; 
   SetMessageStatusBar( TXT_LOAD_REPORTS );

   static int cursel;

   cursel = GetList( IDC_LV_REPORTS )->GetNextItem( -1, LVIS_SELECTED | LVNI_FOCUSED );

   const DString *crtKey = &getParent()->getCurrentListItemKey( this, IFASTBP_PROC::REPORT_STATUS_LIST );

   if( getParent()->performSearch( this, IFASTBP_PROC::REPORT_STATUS_LIST, SEARCH_NEXT_BLOCK ) <= WARNING )
   {
      LoadListControl( IDC_LV_REPORTS );
      if( *crtKey != NULL_STRING )
      {
         GetList( IDC_LV_REPORTS )->SetSelection( crtKey );
      }
   }
   GetDlgItem( IDC_BTN_MORE )->EnableWindow( getParent()->doMoreRecordsExist( this, IFASTBP_PROC::REPORT_STATUS_LIST ) );
   GetList( IDC_LV_REPORTS )->SetSelection(cursel, true, true);
   SetMessageStatusBar(NULL_STRING);
}

//******************************************************************************
// Overrides canCancel so that discard dialog does not show up.
// @returns bool - true.
//******************************************************************************
bool ReportStatusDlg::canCancel() 
{   
   return(true);
}

void ReportStatusDlg::enableButtons( bool bEnable ) 
{   
   GetDlgItem ( IDC_BTN_VIEW )->EnableWindow ( bEnable );
   GetDlgItem ( IDC_BTN_PRINT )->EnableWindow ( bEnable );
   GetDlgItem ( IDC_BTN_MORE )->EnableWindow ( bEnable );
   GetDlgItem ( IDC_BTN_REFRESH )->EnableWindow ( bEnable );
}

void ReportStatusDlg::OnBtnView ( )
{

   DString dstrOutputFileName, dstrOutputFilePath, dstrReportData;

   if ( !_pFTPConnection ) {
      if ( ! openFTP ( ) )
         return;
   } else {            
      if ( !_pFTPConnection->isConnected() )
         if ( ! openFTP ( ) )
            return;
      else
         return;               
   }
   getParent()->getField ( this, IFASTBP_PROC::REPORT_STATUS_LIST, ifds::OutputFileName, dstrOutputFileName, false );
   getParent()->getField ( this, IFASTBP_PROC::REPORT_STATUS_LIST, ifds::OutputFilePath, dstrOutputFilePath, false );
   if ( _pFTPConnection->isConnected() ) {
      DString dstrLoc = dstrOutputFilePath + dstrOutputFileName;
      _pFTPConnection->ReadFile ( dstrLoc, dstrReportData);
   }
   else 
      return;
   setParameter( REPORT_VIEW::REPORTPATH, dstrOutputFilePath );
   setParameter( REPORT_VIEW::REPORTNAME, dstrOutputFileName );
   setParameter( REPORT_VIEW::REPORTDATA, dstrReportData );
   getParentProcess()->invokeProcessFromChild( this, CMD_BPROC_REPORT_VIEW, PROC_SUPPORT ); 
}

void ReportStatusDlg::OnBtnPrint( )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_(" OnBtnPrint() " ) );
   DString dstrPrinterName,dstrCompanyId;
   getParent()->getField ( this, IFASTBP_PROC::REPORT_STATUS_CRITERIA, ifds::CompanyId, dstrCompanyId, false );
   setParameter ( PRINTER::COMPANY, dstrCompanyId );
   setParameter ( PRINTER::LOCAL, NO );
   E_COMMANDRETURN ret = getParentProcess()->invokeProcessFromChild( this, CMD_BPROC_PRINTER_LIST, PROC_SUPPORT ); 
   if ( ret == CMD_OK ) {
      getParameter ( PRINTER::NAME , dstrPrinterName );
      SEVERITY sevRtn = getParent()->setField ( this, IFASTBP_PROC::REPORT_STATUS_LIST, ifds::PrinterName, dstrPrinterName, false );
//      DISPLAYFRAMECONDITIONS ( sevRtn ); 
   }
}
bool ReportStatusDlg::openFTP( )
{
   DString dstrFTPSite, dstrPort, dstrUserId, dstrPwd;
   E_COMMANDRETURN ret = getParentProcess()->invokeProcessFromChild( this, CMD_BPROC_FTP_LOGON, PROC_SUPPORT );
   if ( ret != CMD_OK )
      return false;
   getParameter ( FTP::FTPSITE, dstrFTPSite );
   getParameter ( FTP::FTPPORT, dstrPort );
   getParameter ( FTP::USERID, dstrUserId );
   getParameter ( FTP::PWD, dstrPwd );
   _pFTPConnection = new FTPConnection ( I_("ReportStatusDlg"), dstrFTPSite.c_str() ,dstrPort.asInteger(),dstrUserId.c_str(), dstrPwd.c_str() );
   return true;
}
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/ReportStatusDlg.cpp-arc  $
// 
//    Rev 1.5   Sep 15 2005 15:14:50   popescu
// Incident#403519 - added CLASSNAME as the fifth parameter to  BaseMainDlg constructor
// 
//    Rev 1.4   Mar 21 2003 18:39:54   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.3   Feb 05 2003 14:48:54   ZHANGCEL
// Bug fixed for PTS ticket 10013241 -- Comment out DISPLAYFRAMECONDITIONS ( sevRtn ) in OnBtnPrint( )
// 
//    Rev 1.2   Dec 10 2002 13:36:26   HSUCHIN
// more ftp logic
// 
//    Rev 1.1   Dec 10 2002 09:56:42   HSUCHIN
// added ftp logon
// 
//    Rev 1.0   Dec 08 2002 22:16:26   HSUCHIN
// Initial Revision
 */


