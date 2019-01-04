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
// ^FILE   : ESoPInfoDlg.h
// ^AUTHOR : Robert Kovacs
// ^DATE   : 07/29/01
//
// ^CLASS    : ESoPInfoDlg
// ^SUBCLASS : BaseMainDlg
//
// ^CLASS DESCRIPTION : 
//
//******************************************************************************

#include "stdafx.h"

#ifndef IFASTGUI_H
   #include "mfdstc.h"
#endif

#ifndef DSTEDIT_H
   #include <uibase\DSTEdit.h>
#endif

#ifndef ESOPINFODLG_H
   #include "ESoPInfoDlg.h"
#endif

#ifndef ESOPINFOPROCESSINCLUDES_H
   #include <ifastbp\ESoPInfoProcessIncludes.h>
#endif

#ifndef ESOPHISTORICALPROCESSINCLUDES_H
   #include <ifastbp\ESoPHistoricalProcessIncludes.h>
#endif

#ifndef FUNDCLASSPROCESSINCLUDES_H
   #include <ifastbp\FundClassProcessIncludes.h>
#endif

extern CLASS_IMPORT const I_CHAR* CMD_BPROC_FUNDCLASS;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_ESOP_HISTORICAL;
extern CLASS_IMPORT const I_CHAR* CMD_GUI_ESOPINFO;
#include <bfproc\concretedialogcreator.hpp>
static ConcreteDialogCreator< ESoPInfoDlg > dlgCreator( CMD_GUI_ESOPINFO );

#ifdef _DEBUG
   #define new DEBUG_NEW
   #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


namespace
{
   const I_CHAR * const CLASSNAME            = I_( "ESoPInfoDlg" );
   const I_CHAR * const YES                  = I_( "Y" );
}

namespace CND
{  // Conditions used
   extern const long GUI_ERR_UNKNOWN_EXCEPTION;
}

namespace UAF
{
   extern CLASS_IMPORT I_CHAR * const ESOP;
}

//******************************************************************************

ESoPInfoDlg::ESoPInfoDlg( CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: BaseMainDlg( ESoPInfoDlg::IDD, pParent, pGIC, pGIParent, rCommand, CLASSNAME )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );

   //{{AFX_DATA_INIT(ESoPInfoDlg)
   // NOTE: the ClassWizard will add member initialization here
   //}}AFX_DATA_INIT
}

//******************************************************************************
ESoPInfoDlg::~ESoPInfoDlg()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}
//******************************************************************************

void ESoPInfoDlg::DoDataExchange(CDataExchange* pDX)
{
   BaseMainDlg::DoDataExchange( pDX );
   //{{AFX_DATA_MAP(ESoPInfoDlg)
   // NOTE: the ClassWizard will add DDX and DDV calls here
   //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(ESoPInfoDlg, BaseMainDlg)
//{{AFX_MSG_MAP(ESoPInfoDlg)
ON_BN_CLICKED(IDC_BTN_RESET, OnBtnReset)
ON_BN_CLICKED(IDC_BTN_ESOP_DETAILS, OnBtnEsopDetails)
ON_BN_CLICKED(IDC_BTN_HISTORICAL, OnBtnHistorical)
//}}AFX_MSG_MAP
ON_MESSAGE( UM_OPENFUNDCLASSLISTDLG, OpenFundClassListDlg )

END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ESoPInfoDlg message handlers


//******************************************************************************
void ESoPInfoDlg::OnPostInitDialog()
{
   TRACE_METHOD( CLASSNAME, I_( "OnPostInitDialog" ) );
   CWaitCursor wait;
   SetUserAccesFunctionCode(UAF::ESOP);
   addControlGroupIDForPermissionCheck(0);
   addControls();
   doRefresh(this, NULL);

}

//******************************************************************************
SEVERITY ESoPInfoDlg::doInit()
{
   SEVERITY sevRtn = SEVERE_ERROR;

   sevRtn = NO_CONDITION;
   return(sevRtn);
}
//******************************************************************************
void ESoPInfoDlg::addControls( )
{
   TRACE_METHOD( CLASSNAME, I_( "addControls" ) );

   AddControl( CTRL_EDIT,  IDC_EDT_ADM_INST,   IFASTBP_PROC::ESOPINFO, ifds::IFASNumber);
   DSTEdit *pEdit = dynamic_cast<DSTEdit *>(GetControl(IDC_EDT_ADM_INST));
   pEdit->SetMaxCharNum(8);
   AddControl( CTRL_STATIC, IDC_TXT_STATUS, IFASTBP_PROC::ESOPINFO, ifds::ESoPStatus );
   AddControl( CTRL_DATE, IDC_DTP_INIT_PURCH, IFASTBP_PROC::ESOPINFO,  ifds::InitPurchDate );    
   AddControl( /*CTRL_DATE*/CTRL_EDIT, IDC_DTP_INIT_INVESTMENT, IFASTBP_PROC::ESOPINFO,  ifds::InitInvestDate, CTRLFLAG_AUTO_UPDATE_ON_CHANGE );    
   AddControl( CTRL_DATE, IDC_DTP_EFFECTIVE_DATE, IFASTBP_PROC::ESOPINFO,  ifds::BankEffectiveDate );    
   AddControl( CTRL_COMBO, IDC_CMB_AUTO_CREATE, IFASTBP_PROC::ESOPINFO, ifds::AutoCreate, CTRLFLAG_INITCOMBO_BY_SUB_LIST );
   AddControl( CTRL_EDIT,  IDC_EDT_FUND_NUMBER, IFASTBP_PROC::ESOPINFO, ifds::FromFundNumber, CTRLFLAG_AUTO_UPDATE_ON_CHANGE);
   pEdit = dynamic_cast<DSTEdit *>(GetControl(IDC_EDT_FUND_NUMBER));
   pEdit->SetAllDigits(true);
   AddControl( CTRL_EDIT,  IDC_EDT_FUND,   IFASTBP_PROC::ESOPINFO, ifds::FundCode, CTRLFLAG_AUTO_UPDATE_ON_CHANGE);
   AddControl( CTRL_EDIT,  IDC_EDT_FUND_DESC,   IFASTBP_PROC::ESOPINFO, ifds::FundName, CTRLFLAG_AUTO_UPDATE_ON_CHANGE);
   AddControl( CTRL_EDIT,  IDC_EDT_CLASS,   IFASTBP_PROC::ESOPINFO, ifds::ClassCode, CTRLFLAG_AUTO_UPDATE_ON_CHANGE);
   AddControl( CTRL_EDIT,  IDC_EDT_AMOUNT,   IFASTBP_PROC::ESOPINFO, ifds::Amount);
   pEdit = dynamic_cast<DSTEdit *>(GetControl(IDC_EDT_AMOUNT));
   pEdit->SetAllowedChars(I_("0123456789."));
   AddControl( CTRL_COMBO, IDC_CMB_SETTLE_CURENCY, IFASTBP_PROC::ESOPINFO, ifds::Currency, CTRLFLAG_INITCOMBO_BY_SUB_LIST );
   AddControl( CTRL_DATE, IDC_DTP_INTERRUPT_DATE, IFASTBP_PROC::ESOPINFO,  ifds::InterruptDate );    
   AddControl( CTRL_COMBO, IDC_CMB_INTERRUPT_CODE, IFASTBP_PROC::ESOPINFO, ifds::InterruptCode, CTRLFLAG_INITCOMBO_BY_SUB_LIST );
   AddControl( /*CTRL_DATE*/CTRL_EDIT, IDC_DTP_CONTRACT_START, IFASTBP_PROC::ESOPINFO, ifds::ContStartDate );    
   AddControl( /*CTRL_DATE*/CTRL_EDIT, IDC_DTP_BLOCK_START, IFASTBP_PROC::ESOPINFO,  ifds::BlockStartDate );    
   AddControl( /*CTRL_DATE*/CTRL_EDIT, IDC_DTP_INACTIVE, IFASTBP_PROC::ESOPINFO, ifds::InactiveDate );    
   AddControl( /*CTRL_DATE*/CTRL_EDIT, IDC_DTP_CONTRACT_END, IFASTBP_PROC::ESOPINFO, ifds::ContEndDate );    
   AddControl( /*CTRL_DATE*/CTRL_EDIT, IDC_DTP_BLOCK_END, IFASTBP_PROC::ESOPINFO,  ifds::BlockEndDate );    
   AddControl( /*CTRL_DATE*/CTRL_EDIT, IDC_DTP_EXPIRE, IFASTBP_PROC::ESOPINFO, ifds::ContExpireDate );    

}
//******************************************************************************

void ESoPInfoDlg::SetDlgCaption()
{
   TRACE_METHOD( CLASSNAME, I_( "SetDlgCaption" ) );
   DString strShrNum, strAccountNum, strEmptyString;
   getParent()->getField(this, IFASTBP_PROC::MFACCOUNT, ifds::ShrNum, strShrNum, false);
   getParent()->getField(this, IFASTBP_PROC::MFACCOUNT, ifds::AccountNum, strAccountNum, false);

   SetShrAcctCaption(strShrNum, strAccountNum, strEmptyString);
}

//******************************************************************************

bool ESoPInfoDlg::doRefresh( GenericInterface * rpGICaller, 
                             const I_CHAR * szOriginalCommand )
{
   TRACE_METHOD( CLASSNAME, I_( "doRefresh" ) );

   SetDlgCaption();
   /*DString strHistExist;
   getField(this, DBR::HistoricalInfoExist, strHistExist, false);
   GetDlgItem(IDC_BTN_HISTORICAL)->EnableWindow(strHistExist.strip() == YES);*/
   ConnectControlsToData();
   LoadControls();

   return(true);
}

//******************************************************************************

BOOL ESoPInfoDlg::PreTranslateMessage( MSG* pMsg ) 
{

   if( pMsg->message == WM_KEYDOWN && ( int )( pMsg->wParam ) == VK_F4 && !IsSelectedCtrlUpdateable() )
      return(TRUE);

   if( pMsg->message == WM_KEYDOWN&&( int )( pMsg->wParam ) == VK_F4 )
   {
      if( GetFocus() == GetDlgItem( IDC_EDT_FUND ) )
      {
         PostMessage( UM_OPENFUNDCLASSLISTDLG );
         m_uiClassCodeDialogItem = IDC_EDT_FUND;
      }
      else if( GetFocus() == GetDlgItem( IDC_EDT_CLASS ) )
      {
         PostMessage( UM_OPENFUNDCLASSLISTDLG );
         m_uiClassCodeDialogItem = IDC_EDT_CLASS;
      }
      else if( GetFocus() == GetDlgItem( IDC_EDT_FUND_NUMBER ) )
      {
         PostMessage( UM_OPENFUNDCLASSLISTDLG );
         m_uiClassCodeDialogItem = IDC_EDT_FUND_NUMBER;
      }
   }

   return(BaseMainDlg::PreTranslateMessage( pMsg ));
}
//******************************************************************************
LRESULT ESoPInfoDlg::OpenFundClassListDlg( WPARAM, LPARAM )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OpenFundClassListDlg" ) );

   try
   {
      E_COMMANDRETURN eRtn = CMD_CANCEL;
      CWaitCursor wait;  

      DString dstrAccountNum;  

      getParent()->getField( this, IFASTBP_PROC::MFACCOUNT, ifds::AccountNum, dstrAccountNum, false );
      dstrAccountNum.strip().stripLeading( I_CHAR( '0' ) );

      setParameter ( FUNDCLASSLIST::ACCT_NUM , dstrAccountNum );
      setParameter ( FUNDCLASSLIST::ONLY_ESOP_ELIGIBLE , YES );

      switch( m_uiClassCodeDialogItem )
      {
         case IDC_EDT_FUND:
            {
               CString cstrFundCode;
               GetDlgItem( m_uiClassCodeDialogItem )->GetWindowText( cstrFundCode );
               DString dstrFundCode = cstrFundCode;
               setParameter( FUNDCLASSLIST::FUND_CODE, dstrFundCode );
               setParameter( FUNDCLASSLIST::CLASS_CODE, NULL_STRING );
               setParameter( FUNDCLASSLIST::FUND_NUMBER, NULL_STRING );
            }
            break;
         case IDC_EDT_CLASS:
            {
               CString cstrFundClass;
               GetDlgItem( m_uiClassCodeDialogItem )->GetWindowText( cstrFundClass );
               DString dstrFundClass = cstrFundClass;
               setParameter( FUNDCLASSLIST::FUND_CODE, NULL_STRING );
               setParameter( FUNDCLASSLIST::CLASS_CODE, dstrFundClass );
               setParameter( FUNDCLASSLIST::FUND_NUMBER, NULL_STRING );
            }
            break;
         case IDC_EDT_FUND_NUMBER:
            {
               CString cstrFundNumber;
               GetDlgItem( m_uiClassCodeDialogItem )->GetWindowText( cstrFundNumber );
               DString dstrFundNumber = cstrFundNumber;
               setParameter( FUNDCLASSLIST::FUND_CODE, NULL_STRING );
               setParameter( FUNDCLASSLIST::CLASS_CODE, NULL_STRING );
               setParameter( FUNDCLASSLIST::FUND_NUMBER, dstrFundNumber );
            }
            break;
      }

      eRtn = invokeCommand( getParent(), CMD_BPROC_FUNDCLASS, PROC_SUPPORT, true, NULL );
      switch( eRtn )
      {
         case CMD_OK:
            {
               DString dstrFundCode, dstrClassCode, dstrFundNumber;
               getParameter ( FUNDCLASSLIST::FUND_CODE, dstrFundCode );
               getParameter ( FUNDCLASSLIST::CLASS_CODE, dstrClassCode );
               getParameter ( FUNDCLASSLIST::FUND_NUMBER, dstrFundNumber );
               //if ( dstrFundCode == NULL_STRING && dstrClassCode == NULL_STRING )
               //dstrFundNumber = NULL_STRING;


               getParent()->setField (this, IFASTBP_PROC::ESOPINFO , ifds::FundCode, dstrFundCode );
               getParent()->setField (this, IFASTBP_PROC::ESOPINFO , ifds::ClassCode, dstrClassCode );
               getParent()->setField (this, IFASTBP_PROC::ESOPINFO , ifds::FromFundNumber, dstrFundNumber );

               //LoadControl ( IDC_EDT_FUND );
               //LoadControl ( IDC_EDT_CLASS );
               //LoadControl ( IDC_EDT_FUND_NUMBER );


            }
         case CMD_CANCEL:
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
   return(0);
}
//******************************************************************************

void ESoPInfoDlg::OnBtnReset() 
{
   TRACE_METHOD( CLASSNAME, I_( "OnBtnReset" ) );

   getParent()->reset(this, IFASTBP_PROC::ESOPINFO);
   ReregisterObservers();
   CheckPermission();
   LoadControls();
}
//******************************************************************************

void ESoPInfoDlg::OnBtnEsopDetails() 
{
   // TODO: Add your control notification handler code here

}
//******************************************************************************

void ESoPInfoDlg::OnBtnHistorical() 
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_(" OnBtnHistorical() " ) );

   try
   {
      E_COMMANDRETURN eRtn = CMD_OK;
      DString strAccountNum;
      getParent()->getField(this, IFASTBP_PROC::MFACCOUNT, ifds::AccountNum, strAccountNum, false);
      setParameter( ESOP_HISTORICAL::ACCOUNT_NUMBER, strAccountNum );
      eRtn = invokeCommand( getParent(), CMD_BPROC_ESOP_HISTORICAL, PROC_NO_TYPE, false, NULL );
      switch( eRtn )
      {
         case CMD_OK:
         case CMD_CANCEL:
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
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/ESoPInfoDlg.cpp-arc  $
// 
//    Rev 1.12   Sep 15 2005 15:11:32   popescu
// Incident#403519 - added CLASSNAME as the fifth parameter to  BaseMainDlg constructor
// 
//    Rev 1.11   Mar 21 2003 18:36:12   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.10   Oct 09 2002 23:55:40   PURDYECH
// PVCS Database Conversion
// 
//    Rev 1.9   22 May 2002 19:16:00   PURDYECH
// BFData Implementation
// 
//    Rev 1.8   27 Mar 2002 20:01:08   PURDYECH
// Process/WindowFactory overhaul
// 
//    Rev 1.7   05 Feb 2002 10:08:32   KOVACSRO
// Hour glass.
// 
//    Rev 1.6   07 Jan 2002 12:39:34   KOVACSRO
// Checking permission after re-registering observers.
// 
//    Rev 1.5   07 Dec 2001 17:25:48   KOVACSRO
// more implementation.
// 
//    Rev 1.4   08 Nov 2001 13:57:28   KOVACSRO
// Reregistering observers after reset.
// 
//    Rev 1.3   24 Sep 2001 12:30:38   KOVACSRO
// minor change.
// 
//    Rev 1.2   14 Sep 2001 17:01:46   KOVACSRO
// Changed some DTP controls into Edit Boxes.
// 
//    Rev 1.1   16 Aug 2001 14:29:36   KOVACSRO
// More implementation.
// 
//    Rev 1.0   29 Jul 2001 19:18:28   KOVACSRO
// Initial revision.
// 


*/





