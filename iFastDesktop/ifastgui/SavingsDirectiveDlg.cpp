//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by International Financial Data Services,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2005 by International Financial Data Services
//
//
//******************************************************************************
//
// ^FILE   : SavingsDirectiveDlg.cpp
// ^AUTHOR : 
// ^DATE   : 11/22/05
//
// ----------------------------------------------------------
//
// ^CLASS    : SavingsDirectiveDlg
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :  This is the code for a list selection dialog
//
//******************************************************************************
#include "stdafx.h"

#ifndef IFASTGUI_H
   #include "MFDSTC.h"
#endif

#ifndef SavingsDirectiveDlg_H
   #include "SavingsDirectiveDlg.h"
#endif

#ifndef CONFIGMANAGER_HPP
   #include <ConfigManager.hpp>
#endif

#ifndef DSTCOMBOBOX_H
   #include <uibase\DSTComboBox.h>
#endif

#ifndef DSTCOMMONFUNCTION_HPP
   #include <ifastcbo\DSTCommonFunction.hpp>
#endif

#ifndef DSTEDIT_H
   #include <uibase\DSTEdit.h>
#endif

#ifndef DSTCWORKSESSION_HPP
   #include <ifastcbo\DSTCWorkSession.hpp>
#endif

#include <ifastbp\SavingsDirectiveProcessIncludes.h>


#include <ifastbp\mfcaninterprocparam.hpp>
#include <ifastgui\ifasthistoricalinfo.hpp>

#ifndef INCLUDED_ASSERT_H
#define INCLUDED_ASSERT_H
#include <assert.h>
#endif

#include <uibase\dstbutton.h>

extern CLASS_IMPORT const I_CHAR* CMD_BPROC_SAVINGS_DIRECTIVE;
extern CLASS_IMPORT const I_CHAR* CMD_GUI_SAVINGS_DIRECTIVE;

#include <bfproc\concretedialogcreator.hpp>
static ConcreteDialogCreator< SavingsDirectiveDlg > dlgCreator( CMD_GUI_SAVINGS_DIRECTIVE );

#ifdef _DEBUG
   #define new DEBUG_NEW
   #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

namespace
{
   const I_CHAR * const CLASSNAME = I_( "SavingsDirectiveDlg" );

   const I_CHAR * const YES                      = I_( "Y" );
   const I_CHAR * const NO                       = I_( "N" );

   const I_CHAR *pTRANSNUM                       = I_( "TransNum" );   
   const I_CHAR *pFROMSCREEN                     = I_( "FromScr" ); 

}

namespace CND
{  // Conditions used
   extern CLASS_IMPORT const long GUI_ERR_UNKNOWN_EXCEPTION;
}

namespace ifds
{	

}

namespace UAF
{
   extern CLASS_IMPORT I_CHAR * const SAVINGS_DIRECTIVE;
}


//*****************************************************************************
// Public methods
//*****************************************************************************
SavingsDirectiveDlg::SavingsDirectiveDlg( CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: BaseMainDlg( SavingsDirectiveDlg::IDD, pParent, pGIC, pGIParent, rCommand, CLASSNAME )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   //{{AFX_DATA_INIT(SavingsDirectiveDlg)
   //}}AFX_DATA_INIT
}

//*****************************************************************************
void SavingsDirectiveDlg::DoDataExchange( CDataExchange* pDX )
{
   BaseMainDlg::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(SavingsDirectiveDlg)
   //}}AFX_DATA_MAP
}

//*****************************************************************************
SEVERITY SavingsDirectiveDlg::doInit()
{
   TRACE_METHOD( CLASSNAME, DOINIT );

   getParameter( SAVINGS_DIRECTIVE::ACCOUNTNUM, _accountNum );
   getParameter( SAVINGS_DIRECTIVE::TRANSID, _transID );

   return(NO_CONDITION);
}

//*****************************************************************************
BEGIN_MESSAGE_MAP(SavingsDirectiveDlg, BaseMainDlg)
//{{AFX_MSG_MAP(SavingsDirectiveDlg)
ON_BN_CLICKED( IDC_RESET, OnBtnReset )  
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//*****************************************************************************
// Message handlers
//*****************************************************************************
void SavingsDirectiveDlg::OnPostInitDialog()
{
   TRACE_METHOD( CLASSNAME, ONPOSTINITDIALOG );

   //add the controls not affected by the adjustToProcessType method
	AddControl( CTRL_EDIT,  IDC_EDT_TIS,       IFASTBP_PROC::SAVINGS_DIRECTIVE,ifds::TIS );
	AddControl( CTRL_EDIT,  IDC_EDT_COST,      IFASTBP_PROC::SAVINGS_DIRECTIVE,ifds::Cost );
	AddControl( CTRL_COMBO, IDC_CMB_COST_TYPE, IFASTBP_PROC::SAVINGS_DIRECTIVE,ifds::CostType, CTRLFLAG_INITCOMBO_BY_SUB_LIST );
	AddControl( CTRL_COMBO, IDC_CMB_TIS_TYPE,  IFASTBP_PROC::SAVINGS_DIRECTIVE,ifds::TISType,  CTRLFLAG_INITCOMBO_BY_SUB_LIST );
   
    bool bFlag = hasUpdatePermission( UAF::SAVINGS_DIRECTIVE );
    EnableControl( IDC_EDT_TIS,       bFlag );
    EnableControl( IDC_EDT_COST,      bFlag );
    EnableControl( IDC_CMB_COST_TYPE, bFlag );
    EnableControl( IDC_CMB_TIS_TYPE,  bFlag );
   
	DSTEdit *dstTIS = dynamic_cast< DSTEdit * >( GetDlgItem( IDC_EDT_TIS ) );
	if ( NULL != dstTIS )
	{
		DString dstrPercentageMask = DSTCommonFunctions::getMask( ifds::TIS );
      int iDecimalPointPos = dstrPercentageMask.find( I_( "." ) );		
		dstTIS->AllowNonnegativeDecimalNumbers( iDecimalPointPos, 
					                                          dstrPercentageMask.length() - iDecimalPointPos - 2 );
	}

	DSTEdit *dstCost = dynamic_cast< DSTEdit * >( GetDlgItem( IDC_EDT_COST ) );
	if ( NULL != dstCost )
	{
		DString dstrPercentageMask = DSTCommonFunctions::getMask( ifds::Cost );
      int iDecimalPointPos = dstrPercentageMask.find( I_( "." ) );		
		dstCost->AllowNonnegativeDecimalNumbers( iDecimalPointPos, 
					                                          dstrPercentageMask.length() - iDecimalPointPos - 2 );
	}

	doRefresh (this, NULL_STRING);

}

//*******************************************************************************
void SavingsDirectiveDlg::PostOk( bool /*bOkStatus*/ )
{
}




//******************************************************************************
bool SavingsDirectiveDlg::doRefresh( GenericInterface * rpGICaller,
                                      const I_CHAR* szOriginalCommand)
{ 
   TRACE_METHOD (CLASSNAME, DOREFRESH);
 
   ConnectControlsToData();
   LoadControls();

   if (I_("Refresh") == DString (szOriginalCommand))
	{
		getParameter( SAVINGS_DIRECTIVE::ACCOUNTNUM, _accountNum );
		getParameter( SAVINGS_DIRECTIVE::TRANSID, _transID );
	}
	setDlgCaption();
   return true;
}


//******************************************************************************
void SavingsDirectiveDlg::setDlgCaption()
{
	TRACE_METHOD( CLASSNAME, I_( "SetDlgCaption" ) );

	CString cstrAcct, cstrTransid;
	cstrAcct.LoadString(TXT_ACCOUNT_CAPTION);
	cstrTransid.LoadString(TXT_TRANS_ID);
	DString dstrCaption = DString(cstrAcct) + _accountNum +
				DString(cstrTransid) + _transID ; 

   SetCaption(dstrCaption);
}




//****************************************************************************** 
void SavingsDirectiveDlg::OnBtnReset ( )
{
   TRACE_METHOD(CLASSNAME, I_("OnBtnReset"));

   CWaitCursor wait;
   
   getParent()->send(this,I_("Reset") );

   ReInitControl( IDC_CMB_TIS_TYPE,
						IFASTBP_PROC::SAVINGS_DIRECTIVE, 
						ifds::TISType );		

   ReInitControl( IDC_EDT_TIS,
						IFASTBP_PROC::SAVINGS_DIRECTIVE, 
						ifds::TIS );		

   ReInitControl( IDC_CMB_COST_TYPE,
						IFASTBP_PROC::SAVINGS_DIRECTIVE, 
						ifds::CostType );		

   ReInitControl( IDC_EDT_COST,
						IFASTBP_PROC::SAVINGS_DIRECTIVE, 
						ifds::Cost );		

 

}


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/SavingsDirectiveDlg.cpp-arc  $
// 
//    Rev 1.5   Nov 19 2011 01:38:44   wp040143
// P0186484/FN06 - DESKTOP - iFast Desktop (French Customizations)
// 
//    Rev 1.4   Jan 20 2006 11:10:12   AGUILAAM
// IN 512857 - fixed reset functionality
// 
//    Rev 1.3   Jan 10 2006 16:27:10   AGUILAAM
// IN 513452 - refresh Savings Directive screen based on highlighted trade when EUSD button is clicked
// 
//    Rev 1.2   Jan 10 2006 11:45:10   AGUILAAM
// IN 512857 - removed duplicate "Savings Directive" from screen title
// 
//    Rev 1.1   Dec 07 2005 11:19:44   porteanm
// PET 1228 FN02 - Enable the 4 controls only when user has permissions.
// 
//    Rev 1.0   Nov 29 2005 17:03:52   AGUILAAM
// Initial revision.
// 
//
*/





