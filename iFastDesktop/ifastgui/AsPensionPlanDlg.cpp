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
// ^FILE   : AsPensionPlanDlg.cpp
// ^AUTHOR : Karen Jan
// ^DATE   : July 24, 2001
//
// ----------------------------------------------------------
//
// ^CLASS    : AsPensionPlanDlg
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :  
//
//******************************************************************************
#include "stdafx.h"

#include "mfdstc.h"
#include "aspensionplandlg.h"
#include <ifastbp\aspensionplanprocessincludes.h>
#include <ifastcbo\dstcworksession.hpp>
#include <ifastcbo\mfaccount.hpp>
#include <assert.h>

extern CLASS_IMPORT const I_CHAR* CMD_GUI_AS_PENSION_PLAN;
#include <bfproc\concretedialogcreator.hpp>
static ConcreteDialogCreator< AsPensionPlanDlg > dlgCreator( CMD_GUI_AS_PENSION_PLAN );

#ifdef _DEBUG
   #define new DEBUG_NEW
   #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

namespace
{
   const I_CHAR * const CLASSNAME = I_( "AsPensionPlanDlg" );
}

namespace UAF
{
   extern CLASS_IMPORT I_CHAR * const AS_PENSION_PLAN; 
}

/////////////////////////////////////////////////////////////////////////////
// AsPensionPlanDlg dialog



/////////////////////////////////////////////////////////////////////////////
// AsPensionPlanDlg message handlers
AsPensionPlanDlg::AsPensionPlanDlg(CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: BaseMainDlg( AsPensionPlanDlg::IDD, pParent, pGIC, pGIParent, rCommand, CLASSNAME )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   //{{AFX_DATA_INIT(AsPensionPlanDlg)
   //}}AFX_DATA_INIT
}

//******************************************************************************

AsPensionPlanDlg::~AsPensionPlanDlg()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************
void AsPensionPlanDlg::DoDataExchange( CDataExchange* pDX )
{
   BaseMainDlg::DoDataExchange( pDX );
   //{{AFX_DATA_MAP( AsPensionPlanDlg )
   //}}AFX_DATA_MAP
}

//******************************************************************************
BEGIN_MESSAGE_MAP(AsPensionPlanDlg, BaseMainDlg)
//{{AFX_MSG_MAP(AsPensionPlanDlg)
// NOTE: the ClassWizard will add message map macros here
ON_BN_CLICKED( IDC_BTN_RESET, OnBtnReset )

//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//******************************************************************************
BOOL AsPensionPlanDlg::OnInitDialog() 
{
   TRACE_METHOD( CLASSNAME, ONINITDIALOG );
   BaseMainDlg::OnInitDialog();

   return(TRUE);  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}


/***********************************************************************/

SEVERITY AsPensionPlanDlg::doInit()
{
   TRACE_METHOD( CLASSNAME, I_("doInit"));
   SEVERITY sevRtn = SEVERE_ERROR;

   sevRtn = NO_CONDITION;
   return(sevRtn);
}

/***********************************************************************/

SEVERITY AsPensionPlanDlg::init2() {

   return(NO_CONDITION);
}

//******************************************************************************
void AsPensionPlanDlg::OnPostInitDialog()
{
   TRACE_METHOD( CLASSNAME, I_( "OnPostInitDialog" ) );

   SetUserAccesFunctionCode(UAF::AS_PENSION_PLAN);  
   addControlGroupIDForPermissionCheck(0);

   setDlgTitle();

   //addControls & enable or disable controls
   AddControl( CTRL_DATE, IDC_COMBO_START_DATE, IFASTBP_PROC::ASPENSIONPLAN, ifds::StartDate, CTRLFLAG_AUTO_UPDATE_ON_CHANGE );
   AddControl( CTRL_DATE, IDC_COMBO_END_DATE, IFASTBP_PROC::ASPENSIONPLAN, ifds::EndDate, CTRLFLAG_AUTO_UPDATE_ON_CHANGE );
   AddControl( CTRL_COMBO, IDC_COMBO_STATUS, IFASTBP_PROC::ASPENSIONPLAN, ifds::ASStatus, CTRLFLAG_INITCOMBO_BY_SUB_LIST | CTRLFLAG_AUTO_UPDATE_ON_CHANGE);
   AddControl( CTRL_DATE, IDC_COMBO_MATURITY_DATE, IFASTBP_PROC::ASPENSIONPLAN, ifds::MaturDate, CTRLFLAG_AUTO_UPDATE_ON_CHANGE );

   ConnectControlsToData();
   LoadControls();
   enableControls();

}

//******************************************************************************
void AsPensionPlanDlg::OnBtnReset() 
{
   TRACE_METHOD( CLASSNAME, I_("OnBtnReset"));
   getParent()->reset(this, IFASTBP_PROC::ASPENSIONPLAN);
   ReregisterObservers();
   CheckPermission();
   doRefresh( this, NULL_STRING );
}

//**********************************************************************
bool  AsPensionPlanDlg::doRefresh( GenericInterface * /*rpGICaller*/, 
                                   const I_CHAR * /*szOriginalCommand*/ )
{
   setDlgTitle();
   LoadControls();

   return(true);
}

//******************************************************************************
void AsPensionPlanDlg::enableControls()
{

   GetDlgItem( IDC_COMBO_START_DATE )->EnableWindow( true );
   GetDlgItem( IDC_COMBO_STATUS )->EnableWindow( true );
   GetDlgItem( IDC_COMBO_END_DATE )->EnableWindow( true );
   GetDlgItem( IDC_COMBO_MATURITY_DATE )->EnableWindow( true );
   GetDlgItem( IDOK )->EnableWindow( true );
   GetDlgItem( IDCANCEL )->EnableWindow( true );
   GetDlgItem( IDC_BTN_RESET )->EnableWindow( true );

}

//*****************************************************************************
void AsPensionPlanDlg::setDlgTitle( )
{
   DString strAccountNum, strShrNum, strEntityName;
   getParent()->getField(this, ifds::AccountNum, strAccountNum );
   getParent()->getField(this, ifds::ShrNum, strShrNum );
   getParent()->getField(this, ifds::EntityName, strEntityName );

   SetShrAcctCaption(strShrNum, strAccountNum, strEntityName);
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/AsPensionPlanDlg.cpp-arc  $
// 
//    Rev 1.8   Sep 15 2005 15:10:32   popescu
// Incident#403519 - added CLASSNAME as the fifth parameter to  BaseMainDlg constructor
// 
//    Rev 1.7   Mar 21 2003 18:32:52   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.6   Oct 09 2002 23:55:30   PURDYECH
// PVCS Database Conversion
// 
//    Rev 1.5   22 May 2002 19:15:44   PURDYECH
// BFData Implementation
// 
//    Rev 1.4   27 Mar 2002 20:00:54   PURDYECH
// Process/WindowFactory overhaul
// 
//    Rev 1.3   07 Jan 2002 11:44:00   KOVACSRO
// Fixed 'Reset' problem.
// 
//    Rev 1.2   04 Jan 2002 17:25:58   KOVACSRO
// Changed the way of displaying the title.
// 
//    Rev 1.1   Sep 18 2001 08:51:20   JANKAREN
// Added permission
// 
//    Rev 1.0   Aug 23 2001 13:04:08   JANKAREN
// Initial revision.
// 
// 
 * 
 */
