// TaxRatesDlg.cpp : implementation file
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
//    Copyright 1999 by DST Systems, Inc.
//
//******************************************************************************
//
// ^FILE   : TaxRatesDlg.cpp
// ^AUTHOR : Dan Petolescu
// ^DATE   : 12/16/1999
//
// ^CLASS    : TaxRatesDlg
// ^SUBCLASS : BaseMainDlg         
//
// ^CLASS DESCRIPTION : 
//
//******************************************************************************

#include "stdafx.h"
#include "mfdstc.h"
#include "TaxRatesDlg.h"
#include <ifastbp\TaxRatesProcessIncludes.h>


#ifndef CONDITIONMESSAGEDIALOG_H
   #include <uibase\ConditionMessageDialog.h>
#endif

#ifndef DSTLISTCTRL_H
   #include <uibase\dstlistctrl.h>
#endif

//HllApi
#include <ifastcsi\CsiSession.h>
#include <ifastcsi\ifastcsi.h>

extern CLASS_IMPORT const I_CHAR* CMD_BPROC_ADMINDATES;
extern CLASS_IMPORT const I_CHAR* CMD_GUI_TAXRATES;
#include <bfproc\concretedialogcreator.hpp>
static ConcreteDialogCreator< TaxRatesDlg > dlgCreator( CMD_GUI_TAXRATES );

#ifdef _DEBUG
   #define new DEBUG_NEW
   #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



/////////////////////////////////////////////////////////////////////////////
// TaxRatesDlg 

namespace
{
   // trace literals
   const I_CHAR *CLASSNAME = I_( "TaxRatesDlg" );
   const I_CHAR *LV_TAXRATES = I_( "TaxRatesList" ); 

   const I_CHAR * const MODUSER               = I_( "ModUser" );
   const I_CHAR * const MODDATE               = I_( "ModDate" );
   const I_CHAR * const PROCESSUSER           = I_( "Username" );
   const I_CHAR * const PROCESSDATE           = I_( "ProcessDate" );

   const I_CHAR *Y = I_( "Y" );
   const I_CHAR *N = I_( "N" );
   const I_CHAR *SEPARATOR = I_( " " );
   const I_CHAR *M1 = I_("-1");
   const I_CHAR *SPACE = I_(" ");

   const I_CHAR *MFDSTC = I_( "MFDSTC" );   
   const I_CHAR *CANADA = I_("Canada");
   const I_CHAR *JAPAN = I_("Japan");
   const I_CHAR *MARKET = I_( "Market" );
}

namespace CND
{  // Conditions used
   extern const long GUI_ERR_UNKNOWN_EXCEPTION;
}

//******************************************************************************
TaxRatesDlg::TaxRatesDlg( CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: BaseMainDlg( TaxRatesDlg::IDD, pParent, pGIC, pGIParent, rCommand, CLASSNAME )
, m_hAccel( 0 )
{
   //{{AFX_DATA_INIT(TaxRatesDlg)
   //}}AFX_DATA_INIT
}


//******************************************************************************
void TaxRatesDlg::DoDataExchange(CDataExchange* pDX)
{
   BaseMainDlg::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(TaxRatesDlg)
   //}}AFX_DATA_MAP
}


//******************************************************************************
BEGIN_MESSAGE_MAP(TaxRatesDlg, BaseMainDlg)
//{{AFX_MSG_MAP(TaxRatesDlg)
ON_BN_CLICKED(IDC_BTN_MORE, OnBtnMore)
ON_BN_CLICKED(IDC_BTN_CHANGE, OnBtnChange)
ON_BN_CLICKED(IDC_BTN_ADM_DATES, OnBtnAdmDates)
ON_COMMAND(ID_ACCEL_LIST_TAXRATES, OnAccelListTaxrates)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//******************************************************************************
SEVERITY TaxRatesDlg::doInit()
{
   TRACE_METHOD( CLASSNAME, I_("doInit"));
   SEVERITY sevRtn = SEVERE_ERROR;

   sevRtn = NO_CONDITION;
   return(sevRtn);
}

//******************************************************************************
BOOL TaxRatesDlg::OnInitDialog() 
{
   TRACE_METHOD( CLASSNAME, I_("OnInitDialog"));
   BaseMainDlg::OnInitDialog();

   if( !m_hAccel )
      m_hAccel = LoadAccelerators( NULL, MAKEINTRESOURCE( IDR_ACCEL_TAXRATES ) );

   return(TRUE);
}

//******************************************************************************
void TaxRatesDlg::OnPostInitDialog()
{
   TRACE_METHOD( CLASSNAME, I_("OnPostInitDialog")); 

   AddListControl( CLASSNAME, IDC_LV_TAXRATES, LV_TAXRATES, ifds::TaxRatesHeadingSet, IFASTBP_PROC::TAXRATES_LIST );
   AddControl( CTRL_COMBO, IDC_CMB_PAMTTHREASHOLD, IFASTBP_PROC::TAXRATES_LIST, ifds::PAmtThreasholdDesc,  CTRLFLAG_INITCOMBO_BY_SUB_LIST | CTRLFLAG_NOT_UPDATABLE, (UINT)IDC_LV_TAXRATES );
   AddControl( CTRL_EDIT,  IDC_EDT_EFFECTIVEDATE,  IFASTBP_PROC::TAXRATES_LIST, ifds::EffectiveDate,       CTRLFLAG_NOT_UPDATABLE,                              (UINT)IDC_LV_TAXRATES );
   AddControl( CTRL_EDIT,  IDC_EDT_LOWERBOUND,     IFASTBP_PROC::TAXRATES_LIST, ifds::LowerBound,          CTRLFLAG_NOT_UPDATABLE,                              (UINT)IDC_LV_TAXRATES );
   AddControl( CTRL_EDIT,  IDC_EDT_UPPERBOUND,     IFASTBP_PROC::TAXRATES_LIST, ifds::UpperBound,          CTRLFLAG_NOT_UPDATABLE,                              (UINT)IDC_LV_TAXRATES );
   AddControl( CTRL_EDIT,  IDC_EDT_FEDINCRATE,     IFASTBP_PROC::TAXRATES_LIST, ifds::FedIncRate,          CTRLFLAG_NOT_UPDATABLE,                              (UINT)IDC_LV_TAXRATES );
   AddControl( CTRL_EDIT,  IDC_EDT_PROVINCRATE,    IFASTBP_PROC::TAXRATES_LIST, ifds::ProvIncRate,         CTRLFLAG_NOT_UPDATABLE,                              (UINT)IDC_LV_TAXRATES );
   AddControl( CTRL_EDIT,  IDC_EDT_TAXJURISDICTION,IFASTBP_PROC::TAXRATES_LIST, ifds::TaxJurisCode,        CTRLFLAG_NOT_UPDATABLE,                              (UINT)IDC_LV_TAXRATES );
   AddControl( CTRL_EDIT,  IDC_EDT_COUNTRY,        IFASTBP_PROC::TAXRATES_LIST, ifds::TaxJurisName,        CTRLFLAG_NOT_UPDATABLE,                              (UINT)IDC_LV_TAXRATES );
   AddControl( CTRL_EDIT,  IDC_EDT_FEDREDRATE,     IFASTBP_PROC::TAXRATES_LIST, ifds::FedRedRate,          CTRLFLAG_NOT_UPDATABLE,                              (UINT)IDC_LV_TAXRATES );
   AddControl( CTRL_EDIT,  IDC_EDT_PROVREDRATE,    IFASTBP_PROC::TAXRATES_LIST, ifds::ProvRedRate,         CTRLFLAG_NOT_UPDATABLE,                              (UINT)IDC_LV_TAXRATES );
   AddControl( CTRL_EDIT,  IDC_EDT_LUMPPENRATE,    IFASTBP_PROC::TAXRATES_LIST, ifds::LumpPenRate,         CTRLFLAG_NOT_UPDATABLE,                              (UINT)IDC_LV_TAXRATES );
   AddControl( CTRL_EDIT,  IDC_EDT_PROCESSDATE,    IFASTBP_PROC::TAXRATES_LIST, ifds::ProcessDate,         CTRLFLAG_NOT_UPDATABLE,                              (UINT)IDC_LV_TAXRATES );
   AddControl( CTRL_EDIT,  IDC_EDT_PERPENRATE,     IFASTBP_PROC::TAXRATES_LIST, ifds::PerPenRate,          CTRLFLAG_NOT_UPDATABLE,                              (UINT)IDC_LV_TAXRATES );
   doRefresh( this, NULL_STRING );

   GetDlgItem(IDC_EDT_EFFECTIVEDATE)->EnableWindow(false);
   GetDlgItem(IDC_EDT_LOWERBOUND)->EnableWindow(false);
   GetDlgItem(IDC_EDT_UPPERBOUND)->EnableWindow(false);
   GetDlgItem(IDC_EDT_FEDINCRATE)->EnableWindow(false);
   GetDlgItem(IDC_EDT_PROVINCRATE)->EnableWindow(false);
   GetDlgItem(IDC_EDT_TAXJURISDICTION)->EnableWindow(false);
   GetDlgItem(IDC_EDT_COUNTRY)->EnableWindow(false);
   GetDlgItem(IDC_EDT_FEDREDRATE)->EnableWindow(false);
   GetDlgItem(IDC_EDT_PROVREDRATE)->EnableWindow(false);
   GetDlgItem(IDC_EDT_LUMPPENRATE)->EnableWindow(false);
   GetDlgItem(IDC_EDT_PROCESSDATE)->EnableWindow(false);
   GetDlgItem(IDC_EDT_PERPENRATE)->EnableWindow(false);
   GetDlgItem(IDC_CMB_PAMTTHREASHOLD)->EnableWindow(false);



}

//******************************************************************************
bool TaxRatesDlg::doRefresh( GenericInterface *rpGICaller, const I_CHAR *szOriginalCommand )
{  
   ConnectControlsToData();
   LoadListControl( IDC_LV_TAXRATES );
   LoadControls();
   return(true);
}

//******************************************************************************
void TaxRatesDlg::OnBtnMore() 
{
   TRACE_METHOD( CLASSNAME, I_("OnBtnMore"));
   CWaitCursor wait;

   const DString *crtKey = &getParent()->getCurrentListItemKey( this, IFASTBP_PROC::TAXRATES_LIST );

   SetMessageStatusBar( TXT_LOAD_TAXRATES );
   if( getParent()->performSearch( this, BF::AllContainerIds, SEARCH_NEXT_BLOCK ) <= WARNING )
   {
      LoadListControl( IDC_LV_TAXRATES );
      if( *crtKey != NULL_STRING )
      {
         GetList( IDC_LV_TAXRATES )->SetSelection( crtKey );
      }
   }
   SetMessageStatusBar(NULL_STRING); 
}

//******************************************************************************
void TaxRatesDlg::OnBtnChange() 
{
   AfxMessageBox(TXT_NOT_IMPLEMENTED);

/*	SetMessageStatusBar( TXT_LOAD_HLLAPI );
  CsiSession& csiSession = CsiSession::getInstance();

   csiSession.executeProcess( DcCsiProcesses::TAX_RATE_INFORMATION );
  csiSession.clearParameters();
  SetMessageStatusBar( NULL_STRING );
*/
} 

//******************************************************************************
void TaxRatesDlg::OnBtnAdmDates()
{
   // ShowAdminDates( TAXRATES_LIST );

   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( " OnBtnAdmDates() " ) );
   CWaitCursor wait;
   DString str;
   GenericInterface* rpParent = getParent();

   rpParent->getField( this, IFASTBP_PROC::TAXRATES_LIST, ifds::ModName, str );
   setParameter( MODUSER, str );

   rpParent->getField( this, IFASTBP_PROC::TAXRATES_LIST, ifds::ModDate, str );
   setParameter( MODDATE, str );

   rpParent->getField( this, IFASTBP_PROC::TAXRATES_LIST, ifds::ProcessDate, str );
   setParameter( PROCESSDATE, str );

   rpParent->getField( this, IFASTBP_PROC::TAXRATES_LIST, ifds::Username, str );
   setParameter( PROCESSUSER, str );
   try
   {
      E_COMMANDRETURN eRtn;
      SetMessageStatusBar( TXT_LOAD_ADMIN_DATES );
      eRtn = invokeCommand( rpParent, CMD_BPROC_ADMINDATES, PROC_NO_TYPE,
                            true /*modal*/, NULL );
      SetMessageStatusBar( NULL_STRING );
      switch( eRtn )
      {
         case CMD_OK:
         case CMD_CANCEL:
            break;
         case CMD_MODELESS_INPROCESS:
            break;
         default:
            // Display error
            ConditionMessageBox( FRAMEBELOW(), GETHIGHESTSEVERITY() );
            break;
      }
   }
   catch( ConditionException &ce )
   {
      ConditionMessageBox( ce );
   }
   catch( ... )
   {
      DISPLAYCONDITIONFROMFILE( CND::GUI_ERR_UNKNOWN_EXCEPTION );
   }
}

//******************************************************************************
void TaxRatesDlg::DisplayTitle()
{
   TRACE_METHOD( CLASSNAME, I_("DisplayTitle"));

   SetAccountCaption();
}

//******************************************************************************
void TaxRatesDlg::OnAccelListTaxrates() 
{
   FocusOnControl( IDC_LV_TAXRATES );
}

//******************************************************************************
BOOL TaxRatesDlg::PreTranslateMessage(MSG* pMsg) 
{

   BOOL isTranslated = FALSE;

   // make certain accelerator keys are processed correctly
   if( m_hAccel != NULL )
   {
      isTranslated = ::TranslateAccelerator( m_hWnd, m_hAccel, pMsg );
   }

   if( !isTranslated )
   {
      // pass message down the chain
      isTranslated = BaseMainDlg::PreTranslateMessage( pMsg );
   }
   return(isTranslated);
}


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/TaxRatesDlg.cpp-arc  $
 * 
 *    Rev 1.8   Sep 15 2005 15:15:32   popescu
 * Incident#403519 - added CLASSNAME as the fifth parameter to  BaseMainDlg constructor
 * 
 *    Rev 1.7   Mar 21 2003 18:41:36   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.6   Feb 26 2003 11:24:02   linmay
 * clean up message
 * 
 *    Rev 1.5   Oct 09 2002 23:56:16   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.4   22 May 2002 19:16:30   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.3   27 Mar 2002 20:01:26   PURDYECH
 * Process/WindowFactory overhaul
 * 
 *    Rev 1.2   Dec 04 2000 15:02:12   OLTEANCR
 * fixed OnBtnAdmindate, disabled fields
 * 
 *    Rev 1.1   Mar 22 2000 09:02:50   PETOLESC
 * Added Tax Rates and RESP dialogs.
// 
//    Rev 1.1   Mar 07 2000 11:11:46   PETOLESC
// Corrected QA issues.
// 
//    Rev 1.0   Dec 29 1999 17:23:50   PETOLESC
// Initial revision.
 * 
 *
 */
