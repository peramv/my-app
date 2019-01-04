// RESPAcctInfoDlg.cpp : implementation file
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
//    Copyright 2010 by DST Systems, Inc.
//
//******************************************************************************
//
// ^FILE   : RESPAcctInfoDlg.cpp
// ^AUTHOR : 
// ^DATE   : 
//
// ^CLASS    : RESPAcctInfoDlg
// ^SUBCLASS : BaseMainDlg
//
// ^CLASS DESCRIPTION : 
//
//******************************************************************************

#include "stdafx.h"
#include "mfdstc.h"

#include "RESPAcctInfoDlg.h"

#include <ifastcbo\dstcworksession.hpp>
#include <ifastbp\RESPAcctInfoProcessIncludes.h>

extern CLASS_IMPORT const I_CHAR* CMD_GUI_RESP_ACCT_INFO_NASU;
#include <bfproc\concretedialogcreator.hpp>
static ConcreteDialogCreator< RESPAcctInfoDlg > dlgCreator( CMD_GUI_RESP_ACCT_INFO_NASU );

namespace
{
   const I_CHAR *CLASSNAME             = I_( "RESPAcctInfoDlg" );
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId CESGEligible;
   extern CLASS_IMPORT const BFTextFieldId SiblingOnly;
   extern CLASS_IMPORT const BFTextFieldId Pre98Contrib;
   extern CLASS_IMPORT const BFTextFieldId RES2Client;
   extern CLASS_IMPORT const BFTextFieldId RESPPlanNumber;
   extern CLASS_IMPORT const BFTextFieldId RESPInceptionDate;
   extern CLASS_IMPORT const BFTextFieldId RESPMatureDate;
   extern CLASS_IMPORT const BFTextFieldId RESPReportHRDC;
   extern CLASS_IMPORT const BFNumericFieldId LastActiveAccountNum;
   extern CLASS_IMPORT const BFNumericFieldId LastActiveShrNum;
}

//namespace IFASTBP_PROC
//{
//   extern CLASS_IMPORT const BFContainerId ADDR_TAX_JURIS_UPDATE;
//}

extern CLASS_IMPORT const I_CHAR* CMD_BPROC_RESP_ACCT_INFO;

BEGIN_MESSAGE_MAP(RESPAcctInfoDlg, BaseMainDlg)
//{{AFX_MSG_MAP(RESPAcctInfoDlg)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
RESPAcctInfoDlg::RESPAcctInfoDlg( CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: BaseMainDlg( RESPAcctInfoDlg::IDD, pParent, pGIC, pGIParent, rCommand, CLASSNAME )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
}

//******************************************************************************
SEVERITY RESPAcctInfoDlg::doInit()
{
   SEVERITY sevRtn = SEVERE_ERROR;

   sevRtn = NO_CONDITION;

   return(sevRtn);
}

//******************************************************************************
void RESPAcctInfoDlg::OnPostInitDialog()
{
   TRACE_METHOD( CLASSNAME, I_("OnPostInitDialog")); 

   AddControl( CTRL_COMBO, IDC_CMB_SIBLING_ONLY, IFASTBP_PROC::MFACCOUNT_CBO, 
               ifds::SiblingOnly, CTRLFLAG_INITCOMBO_BY_SUB_LIST );
   AddControl( CTRL_COMBO, IDC_CMB_CESG_ELIGIBLE, IFASTBP_PROC::MFACCOUNT_CBO, 
               ifds::CESGEligible, CTRLFLAG_INITCOMBO_BY_SUB_LIST );
   AddControl( CTRL_COMBO, IDC_CMB_PRE98_CONTRIB, IFASTBP_PROC::MFACCOUNT_CBO, 
               ifds::Pre98Contrib, CTRLFLAG_INITCOMBO_BY_SUB_LIST );
               
   doRefresh( this, NULL );
}

//******************************************************************************
BOOL RESPAcctInfoDlg::OnInitDialog()
{
   TRACE_METHOD( CLASSNAME, I_("OnInitDialog"));
   BaseMainDlg::OnInitDialog();

   DSTCWorkSession *pWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());

   DString strAccountNum,strShrNum,strEntityName;

   getGlobal( WORK_GLOBAL, ifds::LastActiveAccountNum, strAccountNum );
   getGlobal( WORK_GLOBAL, ifds::LastActiveShrNum, strShrNum );
   if( strAccountNum != I_( "" ) )
   {
      pWorkSession->getFirstSequenced01AccountholderEntityName( getDataGroupId(), strAccountNum,strEntityName);
   }
   else
   {
      strEntityName = I_( "" );
   }

   SetShrAcctCaption(strShrNum, strAccountNum, strEntityName);

   return(TRUE);
}

//******************************************************************************
void RESPAcctInfoDlg::DoDataExchange(CDataExchange* pDX)
{
   BaseMainDlg::DoDataExchange(pDX);
}

//******************************************************************************
bool RESPAcctInfoDlg::doRefresh( GenericInterface *rpGICaller, 
                                 const I_CHAR *szOriginalCommand )
{
   ConnectControlsToData();
   LoadControls( -1L ); // Using -1 to load all controls

   return(true);  
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
// $Log:   Y:/VCS/BF iFAST/ifastgui/RESPAcctInfoDlg.cpp-arc  $
// 
//    Rev 1.0   Mar 12 2010 14:28:28   dchatcha
// Initial revision.
// 
