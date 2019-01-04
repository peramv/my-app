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
// ^FILE   :BatchDlg.cpp
// ^AUTHOR : 
// ^DATE   : May 4, 2009
//
// ----------------------------------------------------------
//
// ^CLASS    : BatchDlg
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :  
//
//******************************************************************************

#include "stdafx.h"
#include "mfdstc.h"

#include "BatchDlg.h"
#include <configmanager.hpp>
#include <uibase\DSTEdit.h>
#include <uibase\ifdslistctrl.h>

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
#include <uibase\dstcombobox.h>

#include <ifastbp\transhistoryprocessincludes.h>

#ifndef INCLUDED_ASSERT_H
#define INCLUDED_ASSERT_H
#include <assert.h>
#endif

extern CLASS_IMPORT const I_CHAR* CMD_GUI_BATCH;
#include <bfproc\concretedialogcreator.hpp>
static ConcreteDialogCreator< BatchDlg > dlgCreator( CMD_GUI_BATCH ); 

#ifdef _DEBUG
   #define new DEBUG_NEW
   #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

namespace
{
   const I_CHAR * const CLASSNAME			= I_("BatchDlg");
}

namespace UAF
{
   extern CLASS_IMPORT I_CHAR * const BATCH;
}

//*****************************************************************************
// Public methods
//*****************************************************************************
BatchDlg::BatchDlg( CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: BaseMainDlg( BatchDlg::IDD, pParent, pGIC, pGIParent, rCommand, CLASSNAME ),
m_bDialogInit (false)
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   //{{AFX_DATA_INIT(BatchDlg)
   //}}AFX_DATA_INIT
}

//*****************************************************************************
void BatchDlg::DoDataExchange( CDataExchange* pDX )
{
   BaseMainDlg::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(BatchDlg)
   //}}AFX_DATA_MAP
}

//*****************************************************************************
BEGIN_MESSAGE_MAP(BatchDlg, BaseMainDlg)
//{{AFX_MSG_MAP(BatchDlg)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//*****************************************************************************
// Message handlers
//*****************************************************************************
BOOL BatchDlg::OnInitDialog() 
{
	TRACE_METHOD( CLASSNAME, ONINITDIALOG );
	BaseMainDlg::OnInitDialog(); 

	AddControl (CTRL_COMBO, IDC_CMB_BATCH, IFASTBP_PROC::TRANSACTION_UPDATE, ifds::SettleBatch, CTRLFLAG_DEFAULT | CTRLFLAG_INITCOMBO_BY_SUB_LIST  | CTRLFLAG_COMBO_EDIT); 
	
	DSTComboBox *pCmbBatchName = dynamic_cast <DSTComboBox*> (GetControl (IDC_CMB_BATCH));

	if (pCmbBatchName)
	{
		pCmbBatchName->LimitText (10);
	}

	return TRUE;
}

//******************************************************************************
void BatchDlg::OnPostInitDialog()
{
	TRACE_METHOD( CLASSNAME, ONPOSTINITDIALOG );

	SetUserAccesFunctionCode (UAF::BATCH); 
	addControlGroupIDForPermissionCheck(0);

	ConnectControlsToData ();
	LoadControls();		

    m_bDialogInit = false;
}

//*****************************************************************************
bool BatchDlg::doRefresh (GenericInterface * rpGICaller, 
                                 const I_CHAR* szOriginalCommand)
{ 
   TRACE_METHOD( CLASSNAME, DOREFRESH );

   return( true );
}

//*****************************************************************************
SEVERITY BatchDlg::doInit()
{
	TRACE_METHOD( CLASSNAME, I_("doInit"));

	m_bDialogInit = true;

	return NO_CONDITION;
}

//******************************************************************************
/* $Log::  
*/