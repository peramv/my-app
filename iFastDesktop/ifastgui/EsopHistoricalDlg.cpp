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
//    Copyright 2001 by DST Canada, Inc.
//
//******************************************************************************
//
// ^FILE   : ESoPHistoricalDlg.h
// ^AUTHOR : Robert Kovacs
// ^DATE   : 07/29/01
//
// ^CLASS    : ESoPHistoricalDlg
// ^SUBCLASS : BaseMainDlg
//
// ^CLASS DESCRIPTION : 
//
//******************************************************************************


#include "stdafx.h"

#ifndef IFASTGUI_H
   #include "mfdstc.h"
#endif

#ifndef DSTLISTCTRL_H
   #include <uibase\dstlistctrl.h>
#endif

#ifndef ESOPHISTORICALDLG_H
   #include "ESoPHistoricalDlg.h"
#endif

#ifndef ESOPHISTORICALPROCESSINCLUDES_H
   #include <ifastbp\ESoPHistoricalProcessIncludes.h>
#endif

extern CLASS_IMPORT const I_CHAR* CMD_GUI_ESOP_HISTORICAL;
#include <bfproc\concretedialogcreator.hpp>
static ConcreteDialogCreator< EsopHistoricalDlg > dlgCreator( CMD_GUI_ESOP_HISTORICAL );

#ifdef _DEBUG
   #define new DEBUG_NEW
   #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


namespace
{
   const I_CHAR * const CLASSNAME               = I_( "ESoPHistoricalDlg" );
   const I_CHAR * const LV_ESOP_HISTORICAL_LIST = I_( "ESoPHistoricalList" );

}

namespace CND
{  // Conditions used
//CP20030319   extern CLASS_IMPORT const long GUI_ERR_UNKNOWN_EXCEPTION;
}

namespace UAF
{
   extern CLASS_IMPORT I_CHAR * const ESOP;
   extern CLASS_IMPORT I_CHAR * const ACCOUNT_DETAIL;
}

//******************************************************************************
EsopHistoricalDlg::EsopHistoricalDlg( CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: BaseMainDlg( EsopHistoricalDlg::IDD, pParent, pGIC, pGIParent, rCommand, CLASSNAME )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );

   //{{AFX_DATA_INIT(EsopHistoricalDlg)
   // NOTE: the ClassWizard will add member initialization here
   //}}AFX_DATA_INIT
}

//******************************************************************************
EsopHistoricalDlg::~EsopHistoricalDlg()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}
//******************************************************************************

void EsopHistoricalDlg::DoDataExchange(CDataExchange* pDX)
{
   BaseMainDlg::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(EsopHistoricalDlg)
   // NOTE: the ClassWizard will add DDX and DDV calls here
   //}}AFX_DATA_MAP
}
//******************************************************************************


BEGIN_MESSAGE_MAP(EsopHistoricalDlg, BaseMainDlg)
//{{AFX_MSG_MAP(EsopHistoricalDlg)e
// NOTE: the ClassWizard will add message map macros here
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//******************************************************************************
void EsopHistoricalDlg::OnPostInitDialog()
{
   TRACE_METHOD( CLASSNAME, I_( "OnPostInitDialog" ) );

   AddListControl( CLASSNAME, IDC_LV_ESOP_HISTORICAL_ACCOUNT, LV_ESOP_HISTORICAL_LIST, ifds::EsopHistoricalHeadingSet, IFASTBP_PROC::ESOP_HISTORICAL_LIST );
   DSTListCtrl *pDSTListCtrl = const_cast< DSTListCtrl *> (GetList( IDC_LV_ESOP_HISTORICAL_ACCOUNT ));
   pDSTListCtrl->setAutoAddFlag(true);
   doRefresh(this, NULL);  

}

//******************************************************************************

bool EsopHistoricalDlg::doRefresh( GenericInterface * rpGICaller, 
                                   const I_CHAR * szOriginalCommand )
{
   TRACE_METHOD( CLASSNAME, I_( "doRefresh" ) );

   setCaption();
   LoadListControl(IDC_LV_ESOP_HISTORICAL_ACCOUNT);

   return(true);
}
//******************************************************************************

void EsopHistoricalDlg::setCaption()
{
   TRACE_METHOD( CLASSNAME, I_( "setCaption" ) );

   DString strShrNum, strAccountNum, strEntity;
   getParent()->getField(this, IFASTBP_PROC::MFACCOUNT, ifds::ShrNum, strShrNum, false);
   getParent()->getField(this, IFASTBP_PROC::MFACCOUNT, ifds::AccountNum, strAccountNum, false);
   getParent()->getField(this, IFASTBP_PROC::MFACCOUNT, ifds::Name, strEntity, false);
   SetShrAcctCaption(strShrNum, strAccountNum, strEntity);  
}
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/EsopHistoricalDlg.cpp-arc  $
// 
//    Rev 1.6   Sep 15 2005 15:11:30   popescu
// Incident#403519 - added CLASSNAME as the fifth parameter to  BaseMainDlg constructor
// 
//    Rev 1.5   Mar 21 2003 18:36:08   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.4   Oct 09 2002 23:55:38   PURDYECH
// PVCS Database Conversion
// 
//    Rev 1.3   22 May 2002 19:16:00   PURDYECH
// BFData Implementation
// 
//    Rev 1.2   27 Mar 2002 20:01:08   PURDYECH
// Process/WindowFactory overhaul
// 
//    Rev 1.1   07 Dec 2001 17:24:26   KOVACSRO
// more implementation.

*/
