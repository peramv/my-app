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
//    Copyright 1997 by DST Systems, Inc.
//
//******************************************************************************
//
// ^FILE   : ProgressCtrlDlg.cpp
// ^AUTHOR : Serban Popescu
// ^DATE   : July 2008
//
// ----------------------------------------------------------
//
// ^CLASS    : ProgressCtrlDlg
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :  This is the code for the ProgressCtrlDlg dialog
//
//
//******************************************************************************

#include "stdafx.h"

#include "mfdstc.h"
#include "progressctrldlg.h"
#include "awdcommon.hpp"
#include "dstcview.h"
#include "mainfrm.h"
#include <ifastcbo\dstcusersession.hpp>
#include <ifastcbo\dstcworksession.hpp>
#include <ifastcbo\dstcglobalsession.hpp>
#include <ifastcbo\mgmtco.hpp>
#include <ifastcbo\fundmasterlist.hpp>
#include <ifastcbo\funddetaillist.hpp>
#include <ifastcbo\mgmtcooptions.hpp>
#include <ifastcbo\mgmtcooptions2.hpp>
#include <ifastcbo\translationlist.hpp>
#include <ifastcbo\supportedproductslist.hpp>
#include <ifastcbo\lsifcodeslist.hpp>
#include <ifastcbo\taxtyperulelist.hpp>
#include <ifastcbo\feesetuptraderuleslist.hpp>
#include <ifastcbo\currencylist.hpp>
#include <ifastcbo\errmsgruleslist.hpp>
#include <ifastcbo\feeparamconfiglist.hpp>
#include <configmanager.hpp>
#include <ifastbp\usersessionprocessincludes.h>
#include <ifastcbo\MgmtCoOptions.hpp>
#include <ifastcbo\TranslationTableByAsyncReading.hpp>

extern CLASS_IMPORT const I_CHAR* CMD_GUI_PROGRESS_CTRL;
#include <bfproc\concretedialogcreator.hpp>
#include <bfproc\genericinterfacecontainer.hpp>
static ConcreteDialogCreator< ProgressCtrlDlg > dlgCreator( CMD_GUI_PROGRESS_CTRL );

#ifdef _DEBUG
   #define new DEBUG_NEW
   #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


namespace
{
   const I_CHAR *CLASSNAME = I_( "ProgressCtrlDlg" );
}

namespace CND
{
   extern CLASS_IMPORT const I_CHAR *IFASTDBRKR_CONDITION;
   extern CLASS_IMPORT const long ERR_SMQ_FRAMEWORK_ERROR;
   extern CLASS_IMPORT const long ERR_UNKNOWN_ERROR;
   extern CLASS_IMPORT const long ERR_DATABASE_UNAVAILABLE;
   extern CLASS_IMPORT const long ERR_DATABASE_NOT_CONNECTED;
   extern CLASS_IMPORT const long ERR_NO_COMPANY_RECORD;
   extern CLASS_IMPORT const long ERR_UNKNOW_RESPONSE_TYPE;
   extern CLASS_IMPORT const long ERR_ACCESS_DENIED_NO_SESSION_RECORD;
   extern CLASS_IMPORT const long ERR_ACCESS_DENIED_PASSWORD_MUST_BE_RESET;
   extern CLASS_IMPORT const long ERR_ACCESS_DENIED_PASS_LOGOFF_TIME;
   extern CLASS_IMPORT const long ERR_NO_USERID;
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId CompanyCode;
   extern CLASS_IMPORT const BFTextFieldId ClientID;
}

//******************************************************************************
// Public methods
//******************************************************************************
ProgressCtrlDlg::ProgressCtrlDlg ( CWnd* pParent, GenericInterfaceContainer* pGIC, 
                                   GenericInterface* pGIParent, const Command& rCommand )
: BaseMainDlg (ProgressCtrlDlg::IDD, pParent, pGIC, pGIParent, rCommand, CLASSNAME),
m_dataLoadTimer (0),
pos (10)
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   //{{AFX_DATA_INIT(ProgressCtrlDlg)
   //}}AFX_DATA_INIT

}

//******************************************************************************
void ProgressCtrlDlg::DoDataExchange(CDataExchange* pDX)
{
   BaseMainDlg::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(ProgressCtrlDlg)
   DDX_Control (pDX, IDC_PROGRESS_CTRL, m_ProgressCtrl);
   //}}AFX_DATA_MAP
}

//******************************************************************************
BEGIN_MESSAGE_MAP(ProgressCtrlDlg, BaseMainDlg)
//{{AFX_MSG_MAP(ProgressCtrlDlg)
   ON_WM_TIMER()
//}}AFX_MSG_MAP
END_MESSAGE_MAP()


//*****************************************************************************
BOOL ProgressCtrlDlg::OnInitDialog ()
{
   TRACE_METHOD( CLASSNAME, ONINITDIALOG );
   CWaitCursor cursor;
   BaseMainDlg::OnInitDialog();
	
   m_ProgressCtrl.SetRange (0, 100);
	m_ProgressCtrl.SetPos (pos);
   if (!m_dataLoadTimer)
   {
      //sets the timer to send an event every second ...
      m_dataLoadTimer = SetTimer (1000, 1000, NULL);
   }
   return true;
}

SEVERITY myLittleFunc( MFCanBFCbo* pDataObject,
                       MgmtCo* pMgmtCo,
                       bool& bShouldStillDisplayProgressBar,
                       SEVERITY sev,
                       SEVERITY& sevMax ) {
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTGUI_CONDITION, I_("ProgressCtrlDlg"), I_("myLittleFunc"));
   if ( sev < SEVERE_ERROR && pDataObject) {
      bShouldStillDisplayProgressBar |= !pDataObject->isAsyncRetrieveDone ();
      if( pDataObject->getRequestMaxSeverity() >= SEVERE_ERROR ) {
         Condition* pCondition = pDataObject->getNotifyCondition();
         if( NULL != pCondition ) {
            long code = pCondition->getCode();
            const I_CHAR* pszComponent = pCondition->getComponentName();
            if( !i_strcmp( pszComponent, CND::IFASTDBRKR_CONDITION ) &&
               ( CND::ERR_SMQ_FRAMEWORK_ERROR == code ||
                 CND::ERR_DATABASE_NOT_CONNECTED == code ||
                 CND::ERR_NO_COMPANY_RECORD == code ||
                 CND::ERR_DATABASE_UNAVAILABLE == code ||
                 CND::ERR_UNKNOW_RESPONSE_TYPE == code ||
                 CND::ERR_ACCESS_DENIED_NO_SESSION_RECORD == code ||
                 CND::ERR_ACCESS_DENIED_PASSWORD_MUST_BE_RESET == code ||
                 CND::ERR_ACCESS_DENIED_PASS_LOGOFF_TIME == code ||
                 CND::ERR_NO_USERID == code ) ) {
                MYFRAME()->addCondition ( new Condition(*pCondition) );
            }
         }
      }
   }
   else if( WARNING < sev ) {
      bShouldStillDisplayProgressBar = false;
      if( NULL != pDataObject ) {
         Condition* pCondition = pDataObject->getNotifyCondition();
         MYFRAME()->addCondition ( new Condition(*pCondition) );
      }
   }
   return( NO_SEVERITY );
}


#define CHECK_ASYNCRETRIEVE(dataobject)\
{\
   dataobject *pDataObject = NULL; \
   SEVERITY sev = pMgmtCo->get##dataobject(pDataObject);\
   myLittleFunc( pDataObject, pMgmtCo, \
                 bShouldStillDisplayProgressBar,\
                 sev,\
                 sevMax );\
}   



//******************************************************************************
void ProgressCtrlDlg::OnTimer (UINT nIDEvent)
{
   BaseMainDlg::OnTimer(nIDEvent);
   CWaitCursor cursor;

   if (nIDEvent == 1000)
   {
      GenericInterface* pGIUserSession = getGIContainer()->findGI( getBFSession(),
                                                                   CMD_BPROC_USER_SESSION);
      assert (pGIUserSession);
      DString companyId;

      DSTCGlobalSession &dstcGlobalSession =
         dynamic_cast<DSTCGlobalSession &> (pGIUserSession->getBFSession()->getGlobalSession());
      pGIUserSession->getField (NULL, SYSTMGMTS, companyId);
      assert (getParent() && getParent ()->getParent ());
      getParent ()->getParent ()->getField (NULL, SYSTMGMTS, companyId);

      MgmtCo* pMgmtCo = dstcGlobalSession.aquireMgmtCo (companyId);

      if (pMgmtCo)
      {
         MAKEFRAMEAUTOPROMOTE2(CND::IFASTGUI_CONDITION, I_("ProgressCtrlDlg"), I_("OnTimer"));
         bool bShouldStillDisplayProgressBar = false;
         SEVERITY sevMax=NO_SEVERITY;

         CHECK_ASYNCRETRIEVE (FundMasterList);
         CHECK_ASYNCRETRIEVE (FundDetailList);
         CHECK_ASYNCRETRIEVE (MgmtCoOptions);
         CHECK_ASYNCRETRIEVE (MgmtCoOptions2);
         CHECK_ASYNCRETRIEVE (TranslationList);
         CHECK_ASYNCRETRIEVE (SupportedProductsList);
         CHECK_ASYNCRETRIEVE (LSIFCodesList);
         CHECK_ASYNCRETRIEVE (TaxTypeRuleList);
         CHECK_ASYNCRETRIEVE (FeeSetupTradeRulesList);
         CHECK_ASYNCRETRIEVE (CurrencyList);
         CHECK_ASYNCRETRIEVE (ErrMsgRulesList);
         CHECK_ASYNCRETRIEVE (FeeParamConfigList);
         CHECK_ASYNCRETRIEVE (MiscInfoExternalInstitutionList);

         if (bShouldStillDisplayProgressBar)
         {
            pos += 10;
            if (pos > 100) //hit the end of the range, reinit
            {
               pos = 10;
            }
         	m_ProgressCtrl.SetPos (pos);
         }
         else
         {
            //kill the timer
            m_ProgressCtrl.SetPos (100);
            KillTimer (m_dataLoadTimer);
            m_dataLoadTimer = 0;
            PostMessage( WM_CLOSE ); // auto-close the dialog
         }
         //always free-up the resources...
         dstcGlobalSession.freeMgmtCo (pMgmtCo);
      }
   }
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/ProgressCtrlDlg.cpp-arc  $
// 
//    Rev 1.5   Jun 08 2012 09:44:58   yingz
// remove the redundent code since it is covered by the fix for  IN2821255. 
// 
//    Rev 1.4   Oct 21 2009 10:32:16   purdyech
// LDAP Authorization Support
// 
//    Rev 1.3   20 Aug 2009 15:25:48   popescu
// 95  - ACL replacement project - 
// 
//    Rev 1.2   24 Jul 2008 12:01:16   popescu
// Incident - 1190617 - set all the data init calls to be asynch
// 
//    Rev 1.1   18 Jul 2008 13:53:32   popescu
// Incident - 1190617 - added a WM_CLOSE message that will automatically close the dialog
// 
//    Rev 1.0   17 Jul 2008 15:11:46   popescu
// Initial revision.
 * 
 *
 */
