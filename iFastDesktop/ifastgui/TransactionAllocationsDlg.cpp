// TransactionAllocationsDlg.cpp : implementation file
//

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
// ^FILE   : TransactionAllocationsDlg.cpp
// ^AUTHOR : Yakov Prager
// ^DATE   : 09/26/99
//
// ----------------------------------------------------------
//
// ^CLASS    : TransactionAllocationsDlg
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :  This is the code for the TransactionAllocationsDlg dialog
//
//******************************************************************************

#include "stdafx.h"

#ifndef DSTCLISTCTRL_H
   #include <uibase\DSTListCtrl.h>
#endif

#ifndef ABSTRACTPROCESS_HPP
   #include <bfproc\AbstractProcess.hpp>
#endif

#ifndef IFASTGUI_H
   #include "mfdstc.h"
#endif

#ifndef TRANSACTIONALLOCATIONSDLG_H
   #include "TransactionAllocationsDlg.h"
#endif

#ifndef TRANSACTIONALLOCATIONSPROCESSINCLUDES_H
   #include <ifastbp\TransactionAllocationsProcessIncludes.h>
#endif

#ifndef SPLITCOMMISSIONSPROCESSINCLUDES_H
   #include <ifastbp\SplitCommissionsProcessIncludes.h>
#endif
#include <ifastbp\mfcaninterprocparam.hpp>
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_SPLITCOMMISSION;
extern CLASS_IMPORT const I_CHAR* CMD_GUI_TRANSACTION_ALLOCATIONS;
#include <bfproc\concretedialogcreator.hpp>
static ConcreteDialogCreator< TransactionAllocationsDlg > dlgCreator( CMD_GUI_TRANSACTION_ALLOCATIONS );

#ifdef _DEBUG
   #define new DEBUG_NEW
   #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

namespace CND
{
   extern const long GUI_ERR_UNKNOWN_EXCEPTION;
}

namespace
{
   const I_CHAR * const CLASSNAME = I_( "TransactionAllocationsDlg" );
   const I_CHAR * const LV_ALLOC = I_( "lvAlloc" );
   const I_CHAR * const LV_ALLOC_DETL = I_( "lvAllocDetl" );
   const I_CHAR * const TRANSACTION_NBR = I_( " Transaction Nbr: " );

//###temporary fix for demo mode
   const I_CHAR *const STUB_MODE = I_( "STUB_MODE" );
   const I_CHAR *const OFFLINE   = I_( "OFFLINE" );
}


//******************************************************************************

TransactionAllocationsDlg::TransactionAllocationsDlg( CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: BaseMainDlg( TransactionAllocationsDlg::IDD, pParent, pGIC, pGIParent, rCommand, CLASSNAME )
, m_hAccel( 0 )
{
   //{{AFX_DATA_INIT(TransactionAllocationsDlg)
   //}}AFX_DATA_INIT
}

//******************************************************************************

void TransactionAllocationsDlg::DoDataExchange(CDataExchange* pDX)
{
   BaseMainDlg::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(TransactionAllocationsDlg)
   //}}AFX_DATA_MAP
}

//******************************************************************************

BEGIN_MESSAGE_MAP(TransactionAllocationsDlg, BaseMainDlg)
//{{AFX_MSG_MAP(TransactionAllocationsDlg)
ON_COMMAND(ID_ACCEL_ALLOC_TYPE, OnAccelAllocType)
ON_COMMAND(ID_ACCEL_FUND, OnAccelFund)
ON_BN_CLICKED(IDC_BTN_SPLIT_COM, OnBtnSplitCom)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//******************************************************************************
// Message handlers
//******************************************************************************
BOOL TransactionAllocationsDlg::OnInitDialog() 
{
   BaseMainDlg::OnInitDialog();

   if( !m_hAccel )
      m_hAccel = LoadAccelerators( NULL, 
                                   MAKEINTRESOURCE( IDR_ACCEL_ALLOCATIONS ) );

   return(TRUE);  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}

//******************************************************************************
SEVERITY TransactionAllocationsDlg::doInit()
{
   TRACE_METHOD( CLASSNAME, DOINIT );

   getParameter(MFCAN_IP_PARAM::CALLER, 
      _dstrParent);
   getParameter(MFCAN_IP_PARAM::LIST_KEY, 
      _dstrParentCurKey);
   return NO_CONDITION;
}

//******************************************************************************
void TransactionAllocationsDlg::OnPostInitDialog()
{
   TRACE_METHOD( CLASSNAME, ONPOSTINITDIALOG );

   CWaitCursor wait;

   GetDlgItem(IDC_BTN_SPLIT_COM)->EnableWindow( false );
   AddListControl(CLASSNAME, IDC_LV_ALLOC, LV_ALLOC, ifds::LV_AccountAllocation, 
                  IFASTBP_PROC::ACCOUNT_ALLOCATIONS_LIST);
   AddListControl(CLASSNAME, IDC_LV_ALLOC_DETL, LV_ALLOC_DETL, ifds::LV_FundAllocation,
                  IFASTBP_PROC::FUND_ALLOCATIONS_LIST, IDC_LV_ALLOC, true, LISTFLAG_NOT_AUTO_ADD);
   GetList(IDC_LV_ALLOC)->setAutoAddFlag(true);
   GetList(IDC_LV_ALLOC_DETL)->setAutoAddFlag(true);
   ShowWindow( SW_SHOW );
   doRefresh(this, NULL);
}

//******************************************************************************

bool TransactionAllocationsDlg::doRefresh( GenericInterface *rpGICaller, 
                                           const I_CHAR *szOriginalCommand )
{
   TRACE_METHOD( CLASSNAME, DOREFRESH );

   CWaitCursor wait;

   SetMessageStatusBar(TXT_ALLOCATIONS_RETRIEVING);
   //when called by the process from doRefresh, 
   if (DString(szOriginalCommand) == I_("ReloadParams"))
   {
      getParameter (MFCAN_IP_PARAM::CALLER, 
         _dstrParent);
      getParameter (MFCAN_IP_PARAM::LIST_KEY, 
         _dstrParentCurKey);
   }

   LoadListControl(IDC_LV_ALLOC);
   SetMessageStatusBar(NULL_STRING);
   SetDlgCaption();
   return true;
}

//******************************************************************************
void TransactionAllocationsDlg::SetDlgCaption()
{
   DString dstrCaption = TRANSACTION_NBR, dstr;

   getParent()->getField(this, BF::NullContainerId, ifds::TransNum, dstr);
   dstr.strip().stripLeading(I_CHAR( '0'));
   dstrCaption += dstr;
   SetCaption(dstrCaption);

}

//******************************************************************************
void TransactionAllocationsDlg::OnAccelAllocType() 
{
   FocusOnControl( IDC_LV_ALLOC ); 
}

//******************************************************************************
void TransactionAllocationsDlg::OnAccelFund() 
{
   FocusOnControl (IDC_LV_ALLOC_DETL);
}

//******************************************************************************
BOOL TransactionAllocationsDlg::PreTranslateMessage(MSG* pMsg) 
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
void TransactionAllocationsDlg::DoListItemChanged(UINT listControlID,
   const DString &strKey, bool bIsNewItem, bool bIsDummyItem)
{
   TRACE_METHOD( CLASSNAME, I_("DoListItemChanged") );

   if (listControlID == IDC_LV_ALLOC)
   {
      //###temporary fix for demo mode: begin ->
      if(isDemoMode())
      {
         GetDlgItem( IDC_BTN_SPLIT_COM )->EnableWindow( false );
      }
      //temporary fix for demo mode: <- end
   } else if (listControlID == IDC_LV_ALLOC_DETL)
   {
      DString m_dstrSplitComm;

      getParent()->getField (this, IFASTBP_PROC::FUND_ALLOCATIONS_LIST, 
         ifds::SplitComm, m_dstrSplitComm, false);         
      GetDlgItem(IDC_BTN_SPLIT_COM)->EnableWindow(m_dstrSplitComm == I_( "Y" ));
   }
}

//******************************************************************************
void TransactionAllocationsDlg::OnBtnSplitCom() 
{

   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OnBtnSplitCom" ) );
   E_COMMANDRETURN eRtn;

   bool bModal = true;   // Default to modeless

   CWaitCursor wait;
   try
   {
      DString dstrAccountNum, dstrTransTypeDesc, dstrTransactionNumber;
      const DString *pAllocCurKey = &(getParent()->getCurrentListItemKey(this, 
         IFASTBP_PROC::FUND_ALLOCATIONS_LIST));

      getParent()->getField(this, BF::NullContainerId, ifds::TransNum, dstrTransactionNumber);
      dstrTransactionNumber.strip().stripLeading( I_CHAR( '0' ) );
      getParent()->getField(this, BF::NullContainerId, ifds::TransType, dstrTransTypeDesc, true);
      dstrTransTypeDesc.stripAll();
      getParent()->getField(this, IFASTBP_PROC::MFACCOUNT_CBO, ifds::AccountNum, dstrAccountNum);
      setParameter(SPLITCOMM::CALLER, _dstrParent == I_( "TransHist") ? 
         SPLITCOMM::TRANSACTION_HISTORY_ALLOCATION : SPLITCOMM::TRANSACTION_PENDING_ALLOCATION);
      setParameter(SPLITCOMM::MAIN_LIST_KEY, _dstrParentCurKey);
      setParameter(SPLITCOMM::ACCOUNT_NUM, dstrAccountNum);
      setParameter(SPLITCOMM::TRANSACTION_TYPE_DESC, dstrTransTypeDesc);
      setParameter(SPLITCOMM::TRANSACTION_NUMBER, dstrTransactionNumber);
      setParameter(SPLITCOMM::ALLOCATION_LIST_KEY, *pAllocCurKey);
      eRtn = getParentProcess()->invokeProcessFromChild(this, CMD_BPROC_SPLITCOMMISSION, PROC_SUPPORT);
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

//************************************************************
//###temporary fix for demo mode: begin ->
bool TransactionAllocationsDlg::isDemoMode()
{
   I_CHAR *rpEnv = NULL;
   rpEnv = i_getenv( STUB_MODE );    // Can return NULL pointer if no variable
   if( rpEnv && !i_strcmp( rpEnv, OFFLINE ) )
      return(true);
   else
      return(false);
}
//temporary fix for demo mode: <- end

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/TransactionAllocationsDlg.cpp-arc  $
 * 
 *    Rev 1.18   Sep 15 2005 15:15:46   popescu
 * Incident#403519 - added CLASSNAME as the fifth parameter to  BaseMainDlg constructor
 * 
 *    Rev 1.17   Sep 01 2003 21:23:58   popescu
 * PET 809 FN 02 CIBC Multi Fund Transfer
 * 
 *    Rev 1.16   Aug 20 2003 17:49:00   popescu
 * Refresh on the dialog did not work,this is not part of a PTS but impacts the inquiry of split commission
 * 
 *    Rev 1.15   May 15 2003 11:39:12   popescu
 * Fix system crash in TransactioAllocationDialog with split commission
 * 
 *    Rev 1.14   May 13 2003 10:07:46   popescu
 * Split commission re-work
 * 
 *    Rev 1.13   Mar 21 2003 18:41:52   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.12   Oct 09 2002 23:56:16   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.11   Sep 25 2002 15:43:02   KOVACSRO
 * PTS 10009965 : fixed crash
 * 
 *    Rev 1.10   22 May 2002 19:16:32   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.9   27 Mar 2002 20:01:28   PURDYECH
 * Process/WindowFactory overhaul
 * 
 *    Rev 1.8   09 Jul 2001 11:01:08   HSUCHIN
 * getField fix for DBR::SplitComm
 * 
 *    Rev 1.7   Jun 06 2001 12:03:00   DINACORN
 * temporary fix for demo mode - disabled IDC_BTN_SPLIT_COM
 * 
 *    Rev 1.6   May 07 2001 16:15:40   HERNANDO
 * Added SetParameter to OnBtnSplitCom.
 * 
 *    Rev 1.5   Mar 23 2001 12:33:48   HSUCHIN
 * disable splitcomm btn when there is not split commission
 * 
 *    Rev 1.4   Mar 22 2001 14:12:44   HSUCHIN
 * hook up to split commission
 * 
 *    Rev 1.3   Mar 18 2001 12:19:12   YINGZ
 * make it work with new account/fund level allocation structure
 * 
 *    Rev 1.2   Mar 18 2001 11:09:02   YINGZ
 * change field names
 * 
 *    Rev 1.1   Oct 04 2000 11:28:18   ZHANGCEL
 * Inserted Fund Number colomn in the list
 * 
 *    Rev 1.0   Feb 15 2000 11:01:26   SMITHDAV
 * Initial revision.
// 
//    Rev 1.6   Feb 02 2000 15:46:46   DT24433
// removed ok/cancel, added revision log section
 * 
 */
