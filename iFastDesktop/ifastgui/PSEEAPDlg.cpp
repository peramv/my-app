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
//    Copyright 2004 by International Financial Data Services.
//
//******************************************************************************
//
// ^FILE   :PSEEAPDlg.cpp
// ^AUTHOR : Serban Popescu
// ^DATE   : April 2010
//
// ----------------------------------------------------------
//
// ^CLASS    : PSEEAPDlg
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :  
//
//******************************************************************************

#include "stdafx.h"
#include "mfdstc.h"

#include "pseeapdlg.h"
#include <configmanager.hpp>
#include <uibase\DSTEdit.h>

#include <ifastbp\mfcaninterprocparam.hpp>
#include <ifastbp\pseeapprocessincludes.h>
#include <ifastbp\pseeapprocess.hpp>
#include <configmanager.hpp>
#include <ifastcsi\csisession.h>
#include <ifastcsi\ifastcsi.h>
#include <uibase\dstgridwnd.h>
#include <uibase\dstlistctrl.h>
#include <ifastcbo\dstcommonfunction.hpp>
#include <ifastbp\mfcaninterprocparam.hpp>
#include <uibase\dstedit.h>
#include <ifastcbo\dstcworksession.hpp>
#include <assert.h>

#ifndef INCLUDED_ASSERT_H
#define INCLUDED_ASSERT_H
#include <assert.h>
#endif

extern CLASS_IMPORT const I_CHAR* CMD_GUI_PSE_EAP;
#include <bfproc\concretedialogcreator.hpp>
static ConcreteDialogCreator< PSEEAPDlg > dlgCreator( CMD_GUI_PSE_EAP ); 

#ifdef _DEBUG
   #define new DEBUG_NEW
   #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

namespace
{
   const I_CHAR * const CLASSNAME = I_("PSEEAPDlg");
}

namespace UAF
{
}

namespace ifds
{
}

//*****************************************************************************
// Public methods
//*****************************************************************************
PSEEAPDlg::PSEEAPDlg( CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: BaseMainDlg( PSEEAPDlg::IDD, pParent, pGIC, pGIParent, rCommand, CLASSNAME )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   //{{AFX_DATA_INIT(PSEEAPDlg)
   //}}AFX_DATA_INIT
}

//*****************************************************************************
void PSEEAPDlg::DoDataExchange( CDataExchange* pDX )
{
   BaseMainDlg::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(PSEEAPDlg)
   //}}AFX_DATA_MAP
}

//*****************************************************************************
BEGIN_MESSAGE_MAP(PSEEAPDlg, BaseMainDlg)
//{{AFX_MSG_MAP(PSEEAPDlg)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//*****************************************************************************
// Message handlers
//*****************************************************************************
BOOL PSEEAPDlg::OnInitDialog() 
{
	TRACE_METHOD( CLASSNAME, ONINITDIALOG );

   BaseMainDlg::OnInitDialog(); 

   if (m_dstrCaller == I_("TradeEntry"))
   {
      AddControl (CTRL_DATE,  IDC_DTP_START_DATE,        IFASTBP_PROC::TRADE, ifds::CourseStart,      CTRLFLAG_DEFAULT);
	   AddControl (CTRL_EDIT,  IDC_EDT_YEAR_LENGTH,       IFASTBP_PROC::TRADE, ifds::CourseLen,        CTRLFLAG_DEFAULT);
	   AddControl (CTRL_COMBO, IDC_CMB_PSE_TYPE,          IFASTBP_PROC::TRADE, ifds::PSEProgramType,   CTRLFLAG_INITCOMBO_BY_SUB_LIST);
	   AddControl (CTRL_COMBO, IDC_CMB_PSE_LENGTH,        IFASTBP_PROC::TRADE, ifds::PSEProgramLen,    CTRLFLAG_INITCOMBO_BY_SUB_LIST);
	   AddControl (CTRL_COMBO, IDC_CMB_PSE_YEAR,          IFASTBP_PROC::TRADE, ifds::PSEProgramYear,   CTRLFLAG_INITCOMBO_BY_SUB_LIST);
      AddControl (CTRL_EDIT,  IDC_EDT_PSTLCODE_COUNTRY,  IFASTBP_PROC::TRADE, ifds::EduInstPstl,      CTRLFLAG_DEFAULT);
   }
   else if (m_dstrCaller == I_("RESPTransactionsDlg"))
   {
      AddControl (CTRL_DATE,  IDC_DTP_START_DATE, IFASTBP_PROC::PSE_EAP_LIST, ifds::CourseStart, CTRLFLAG_DEFAULT);
	   AddControl (CTRL_EDIT,  IDC_EDT_YEAR_LENGTH, IFASTBP_PROC::PSE_EAP_LIST, ifds::CourseLen,  CTRLFLAG_INITCOMBO_BY_SUB_LIST);
	   AddControl (CTRL_COMBO, IDC_CMB_PSE_TYPE, IFASTBP_PROC::PSE_EAP_LIST, ifds::PSEProgramType, CTRLFLAG_INITCOMBO_BY_SUB_LIST);
	   AddControl (CTRL_COMBO, IDC_CMB_PSE_LENGTH, IFASTBP_PROC::PSE_EAP_LIST, ifds::PSEProgramLen, CTRLFLAG_INITCOMBO_BY_SUB_LIST);
	   AddControl (CTRL_COMBO, IDC_CMB_PSE_YEAR, IFASTBP_PROC::PSE_EAP_LIST, ifds::PSEProgramYear, CTRLFLAG_INITCOMBO_BY_SUB_LIST);
      AddControl (CTRL_EDIT,  IDC_EDT_PSTLCODE_COUNTRY, IFASTBP_PROC::PSE_EAP_LIST, ifds::EduInstPstl, CTRLFLAG_DEFAULT);
   }
	return TRUE;
}

//******************************************************************************
void PSEEAPDlg::OnPostInitDialog()
{
	TRACE_METHOD (CLASSNAME, ONPOSTINITDIALOG);

	DSTEdit *pstlEdit = dynamic_cast<DSTEdit *> (GetControl (IDC_EDT_PSTLCODE_COUNTRY));
   DSTEdit *yearLengthEdit = dynamic_cast<DSTEdit *> (GetControl (IDC_EDT_YEAR_LENGTH));

  	if (pstlEdit)
   {
      pstlEdit->SetMaxCharNum (10);
   }
   if (yearLengthEdit)
   {
      yearLengthEdit->SetAllowedChars (I_("0123456789"));
      yearLengthEdit->setMaxNumDigitsAfterDecimalPoint (0);
   }
   doRefresh (this, NULL);
}

//*****************************************************************************
bool PSEEAPDlg::doRefresh (GenericInterface * rpGICaller, 
                           const I_CHAR* szOriginalCommand)
{ 
   TRACE_METHOD( CLASSNAME, DOREFRESH );

   ConnectControlsToData ();
   LoadControls ();
   SetDlgCaption ();
   
   if (m_dstrCaller == I_("RESPTransactionsDlg"))
   {
      GetControl (IDC_DTP_START_DATE)->Enable (false);
      GetControl (IDC_EDT_YEAR_LENGTH)->Enable (false);
      GetControl (IDC_CMB_PSE_TYPE)->Enable (false);
      GetControl (IDC_CMB_PSE_LENGTH)->Enable (false);
      GetControl (IDC_CMB_PSE_YEAR)->Enable (false);
      GetControl (IDC_EDT_PSTLCODE_COUNTRY)->Enable (false);
   }
   return true;
}


//**********************************************************************************
void PSEEAPDlg::ControlUpdated (UINT controlID, const DString &strValue)
{  
}

//**********************************************************************************
void PSEEAPDlg::SetDlgCaption()
{
	TRACE_METHOD( CLASSNAME, I_( "SetDlgCaption" ) );

   DString dstrShrNum, 
      dstrEntityName;

	// Get Entity Name
	if (!m_dstrAccountNum.empty()) 
		dynamic_cast<DSTCWorkSession *>(getBFWorkSession())->getFirstSequenced01AccountholderEntityName( 
         getDataGroupId(), m_dstrAccountNum, dstrEntityName);

	SetShrAcctCaption (dstrShrNum, m_dstrAccountNum, dstrEntityName);
}

//*****************************************************************************
SEVERITY PSEEAPDlg::doInit()
{
	TRACE_METHOD( CLASSNAME, I_("doInit"));

	getParameter (ACCOUNT_NUM, m_dstrAccountNum);
	getParameter (CALLER, m_dstrCaller);

	return NO_CONDITION;
}

//******************************************************************************
void PSEEAPDlg::OnCancel()
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTGUI_CONDITION, 
                           CLASSNAME, 
                           I_("OnCancel"));
   if (getParent()->send (this, I_("Cancel")))
   {
      CDialog::OnCancel();
   }
   else
   {
      // Display error
      ConditionMessageBox (FRAMEBELOW (), GETHIGHESTSEVERITY ());
   }
}

//******************************************************************************
bool PSEEAPDlg::GetDataForControl( UINT controlID, 
                                   DString &dstrValueOut, 
                                   bool bFormatted, 
                                   int index) const
{
   bool bReturn = false;
   return bReturn;
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/PSEEAPDlg.cpp-arc  $
// 
//    Rev 1.6   Jul 06 2010 23:02:32   popescu
// PETP0165541 FN02 IN#2123752 - No need to override getdataforcontrol anymore...
// 
//    Rev 1.5   Jun 11 2010 05:51:04   kitticha
// PETP0165541 FN02 IN#2123752 - PSE Fix.
// 
//    Rev 1.4   May 05 2010 15:27:48   popescu
// RES-QESI Trading - PSE/EAP work - fixes for the dialog
// 
//    Rev 1.3   Apr 30 2010 15:32:16   popescu
// RES-QESI Trading - PSE/EAP work
// 
//    Rev 1.2   Apr 29 2010 23:21:54   popescu
// RES-QESI Trading - PSE/EAP work
// 
//    Rev 1.1   Apr 21 2010 17:21:10   popescu
// RESP-QESI Resp transfer screen
// 
//    Rev 1.0   Apr 20 2010 01:00:58   popescu
// Initial revision.
**/