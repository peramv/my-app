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
// ^FILE   : DirectTradingDlg.cpp
// ^AUTHOR : 
// ^DATE   : 
//
// ----------------------------------------------------------
//
// ^CLASS    : DirectTradingDlg
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :  
//
//******************************************************************************

#include "stdafx.h"

#ifndef MFCANINTERPROCPARAM_HPP
   #include <ifastbp\MFCANInterProcParam.hpp>
#endif

#ifndef ABSTRACTPROCESS_HPP
   #include <bfproc\AbstractProcess.hpp>
#endif

#ifndef DSTCFUNCS_H
   #include <uibase\DstcFuncs.h>
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

#ifndef DSTLISTCTRL_H
   #include <uibase\DSTListCtrl.h>
#endif

#ifndef DSTSTATIC_H
   #include <uibase\DSTStatic.h>
#endif

#ifndef DSTCWORKSESSION_HPP
   #include <ifastcbo\DSTCWorkSession.hpp>
#endif

#ifndef IFASTGUI_H
   #include "MFDSTC.h"
#endif

#include <ifastdataimpl\dse_substitute_vw.hpp>

#ifndef DirectTradingDLG_H
   #include "DirectTradingDlg.h"
#endif

#ifndef DirectTradingPROCESSINCLUDES_H
   #include <ifastbp\DirectTradingProcessIncludes.h>
#endif

#ifndef DSTGRIDWND_H
   #include <uibase\DSTGridWnd.h>
#endif

#ifndef IDENTIFYACCOUNTSPROCESSINCLUDES_HPP
   #include <ifastbp\IdentAccProcessIncludes.h>
#endif

#include <ifastcbo\mfaccount.hpp>

//HllApi
#include <ifastcsi\CsiSession.h>
#include <ifastcsi\ifastcsi.h>

extern CLASS_IMPORT const I_CHAR* CMD_BPROC_BANK_INSTRUCTIONS;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_DIRECT_TRADING;
extern CLASS_IMPORT const I_CHAR* CMD_GUI_DIRECT_TRADING;

#include <bfproc\concretedialogcreator.hpp>
static ConcreteDialogCreator< DirectTradingDlg > dlgCreator( CMD_GUI_DIRECT_TRADING );

#ifdef _DEBUG
   #define new DEBUG_NEW
   #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

namespace
{
   // trace literals
   const I_CHAR * const CLASSNAME         = I_( "DirectTradingDlg" );

   const I_CHAR *LV_BANKING				  = I_( "BankList" ); 

   const I_CHAR * const YES               = I_( "Y" );
   const I_CHAR * const NO                = I_( "N" );

   const I_CHAR * const STATUS_GOOD       = I_( "Good" );
   const I_CHAR * const STATUS_BAD        = I_( "Bad" );
   const I_CHAR * const LV_DTA_BANKING	  = I_( "DTA Banking List" );
   const I_CHAR * const LV_DTA	  = I_( "Direct Trading Agreement List" );

}                                         

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId DTAType;
   extern CLASS_IMPORT const BFTextFieldId DTA_BankHeader;
   extern CLASS_IMPORT const BFTextFieldId DTA_Header;
   extern CLASS_IMPORT const BFNumericFieldId HoldingTransitNo;
   extern CLASS_IMPORT const BFDateFieldId EffectiveDate;
   extern CLASS_IMPORT const BFDateFieldId StopDate;
   extern CLASS_IMPORT const BFTextFieldId AcctUseCode;
}

namespace CND
{  // Conditions used
   extern const long GUI_ERR_UNKNOWN_EXCEPTION;
}

namespace UAF
{
   extern CLASS_IMPORT I_CHAR * const ACCTDTA;
}

namespace BANKTYPE
{
   extern CLASS_IMPORT I_CHAR * const DIRECT_TRADING;
}


//******************************************************************************

DirectTradingDlg::DirectTradingDlg( CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: BaseMainDlg( DirectTradingDlg::IDD, pParent, pGIC, pGIParent, rCommand, CLASSNAME )
{
   //{{AFX_DATA_INIT(DirectTradingDlg)
   //}}AFX_DATA_INIT
//   m_bFeeLostFocus               = false;
   m_dstrAccountNum              = NULL_STRING;
}

//******************************************************************************

void DirectTradingDlg::DoDataExchange(CDataExchange* pDX)
{
   BaseMainDlg::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(DirectTradingDlg)
   //}}AFX_DATA_MAP
}

//******************************************************************************

BEGIN_MESSAGE_MAP(DirectTradingDlg, BaseMainDlg)
//{{AFX_MSG_MAP(DirectTradingDlg)
ON_BN_CLICKED(ID_BTN_BANK, OnBtnBank)
ON_BN_CLICKED(IDC_BTN_ADM_DATES, OnBtnAdm)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//******************************************************************************

SEVERITY DirectTradingDlg::doInit()
{
   SEVERITY sevRtn = SEVERE_ERROR;

   getParent()->getField(this, ifds::AccountNum, m_dstrAccountNum);
   m_dstrAccountNum.strip();

   sevRtn = NO_CONDITION;
   return(sevRtn);
}

//******************************************************************************

BOOL DirectTradingDlg::OnInitDialog() 
{
   TRACE_METHOD( CLASSNAME, ONINITDIALOG );
   
   BaseMainDlg::OnInitDialog();   
   DisplayTitle();
   return(TRUE);  // return TRUE unless you set the focus to a control
   // EXCEPTION: OCX Property Pages should return FALSE
}

//******************************************************************************

void DirectTradingDlg::OnPostInitDialog()
{

   SetAccount(m_dstrAccountNum);

   //SetUserAccesFunctionCode(UAF::ACCTDTA);
   //Add all controls on the screen to the container
   addControls();

   //populate the DirectTrading data
   populateData();    

}

//******************************************************************************

void DirectTradingDlg::addControls() 
{
   //ListCtrl	
   AddListControl(CLASSNAME, IDC_LV_DTA, LV_DTA, ifds::DTA_Header, IFASTBP_PROC::DIRECT_TRADING_LIST,
                   0,true/*,LISTFLAG_NOT_AUTO_ADD */);
   ConnectListToData( IDC_LV_DTA, true );
   LoadListControl( IDC_LV_DTA );
   AddListControl(CLASSNAME, IDC_LV_DTA_BANKING, LV_DTA_BANKING, ifds::DTA_BankHeader, IFASTBP_PROC::BANK_INSTRUCTIONS_LIST,
                   0,true,LISTFLAG_NOT_AUTO_ADD );
   ConnectListToData( IDC_LV_DTA_BANKING, true );
   LoadListControl( IDC_LV_DTA_BANKING );

   AddControl(CTRL_COMBO, IDC_CMB_DTATYPE, IFASTBP_PROC::DIRECT_TRADING_LIST, ifds::DTAType, CTRLFLAG_INITCOMBO_BY_SUB_LIST);
   AddControl(CTRL_EDIT, IDC_EDT_HOLDINGTRANSNUM,  IFASTBP_PROC::DIRECT_TRADING_LIST, ifds::HoldingTransitNo, 0);
   //Effective Date
   AddControl(CTRL_DATE,  IDC_DTP_EFFECTIVE_DATE, IFASTBP_PROC::DIRECT_TRADING_LIST, ifds::EffectiveDate, 0);
   //Stop Date
   AddControl(CTRL_DATE,  IDC_DTP_STOP_DATE, IFASTBP_PROC::DIRECT_TRADING_LIST, ifds::StopDate, 0);
   
   ConnectControlsToData();
   LoadControls();
}

//******************************************************************************

void DirectTradingDlg::populateData()
{
   /*LoadListControl(IDC_LV_DirectTrading);

   DSTListCtrl* pListCtrl = GetList(IDC_LV_DirectTrading);
   getParent()->getField(this, DirectTradingLIT::LISTKEY, m_dstrCurKey);
   m_dstrCurKey.strip();
   if( m_dstrCurKey.empty() )
   {
      DString dstrTransTypeParam, dstrTransType;
      getParent()->getField(this, DirectTradingLIT::TRANS_TYPE_PARAM, dstrTransTypeParam);
      dstrTransTypeParam.strip();
      if( !dstrTransTypeParam.empty() )
      {
         const DString *pKey = &getParent()->getFirstListItemKey(this, m_lContainerID);
         do
         {
            getParent()->getField(this, m_lContainerID, ifds::TransType, dstrTransType, false);
            if( dstrTransType.strip() == dstrTransTypeParam )
            {
               m_dstrCurKey = *pKey;
               break;
            }
         }
         while( *(pKey = &(getParent()->getNextListItemKey(this, m_lContainerID))) != NULL_STRING );
      }
   }
   pListCtrl->SetSelection(&m_dstrCurKey);
   enableDisableAllocation();
*/
}

//******************************************************************************

void DirectTradingDlg::InitControl(UINT controlID)
{
/*   switch( controlID )
   {
      case IDC_CMB_ADDRESS_CODE:
         fillAddressCode();
         break;
      case IDC_CMB_PLAN:
         fillPlanCode();
         break;
      case IDC_CMB_AT_ACCT_TO:
         initAcctToCombo(IDC_CMB_AT_ACCT_TO);
         break;
   }*/
}


//******************************************************************************

void DirectTradingDlg::ControlUpdated(UINT controlID, const DString &dstrValue)
{
/*
      case IDC_DTP_EFFECTIVE_DATE :
         {
           DString dstrAccountNum;
      	   getParent()->getField(this, ifds::AccountNum, dstrAccountNum);
	       MFAccount * pMFAccount = NULL;
           DSTCWorkSession *dstWorkSession = dynamic_cast<DSTCWorkSession *>(getParent()->getBFWorkSession());
	       if( dstWorkSession->getMFAccount( getDataGroupId(), dstrAccountNum, pMFAccount ) <= WARNING ) {
               if ( pMFAccount->isDTAEligible ( getDataGroupId() ) )
                  LoadListControl(IDC_LV_BANKING);
            }
         }
         break;
      default:
         break;
   }*/
}

//******************************************************************************

bool DirectTradingDlg::doRefresh(GenericInterface * rpGICaller,const I_CHAR * szOriginalCommand)
{  
   return(true);
}


//******************************************************************************
void DirectTradingDlg::OnBtnBank() 
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OnBtnBank" ) );

   CWaitCursor wait;

   try
   {
      setParameter(MFCAN_IP_PARAM::ACCOUNT_NUM, m_dstrAccountNum);
      setParameter(MFCAN_IP_PARAM::BANK_TYPE, BANKTYPE::DIRECT_TRADING);

      E_COMMANDRETURN eRtn = getParentProcess()->invokeProcessFromChild(this, 
               CMD_BPROC_BANK_INSTRUCTIONS, PROC_SUPPORT, true, NULL);

      if (eRtn != CMD_CANCEL)
      {
		 LoadListControl( IDC_LV_DTA_BANKING );
         RefreshListItem(IDC_LV_DTA_BANKING);
      }
   }
   catch (ConditionException &ce)
   {
      ConditionMessageBox(ce);
   }
   catch (...)
   {
      DISPLAYCONDITIONFROMFILE( CND::GUI_ERR_UNKNOWN_EXCEPTION );
   }
}

//******************************************************************************

void DirectTradingDlg::OnBtnAdm() 
{
	ShowAdminDates (IFASTBP_PROC::DIRECT_TRADING_LIST);
}

//******************************************************************************
bool DirectTradingDlg::ListViewControlFilter( long lSubstituteId, const DString * )
{
   if( lSubstituteId == ifds::DTA_BankHeader.getId() )
   {
      // for Automatic Transfer we should filter it out temperally
      DString dstrAcctUse;
      getParent()->getField( this, IFASTBP_PROC::BANK_INSTRUCTIONS_LIST, 
                             ifds::AcctUseCode, dstrAcctUse, false );

      dstrAcctUse.strip().upperCase();
      if(dstrAcctUse != I_("31")) return false;
   }
   return(true);
}

//******************************************************************************
void DirectTradingDlg::DisplayTitle()
{
   TRACE_METHOD( CLASSNAME, I_("DisplayTitle"));

   DString str;
   CString text;

   text.LoadString( TXT_DIRECT_TRADING_TITLE );   
   str = ( LPCTSTR )text + m_dstrAccountNum;

   SetWindowText( str.c_str() );
}
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/DirectTradingDlg.cpp-arc  $
// 
//    Rev 1.4   Sep 15 2005 15:11:20   popescu
// Incident#403519 - added CLASSNAME as the fifth parameter to  BaseMainDlg constructor
// 
//    Rev 1.3   Oct 24 2003 13:12:42   FENGYONG
// Add String TXT_DIRECT_TRADING_TITLE
// 
//    Rev 1.2   Oct 23 2003 18:03:44   FENGYONG
// modify listViewControlFilter  for PET809 FN08
// 
//    Rev 1.1   Oct 16 2003 12:34:24   FENGYONG
// PET809 FN08 Direct Trading enhancement
// 
//    Rev 1.0   Oct 07 2003 09:51:06   FENGYONG
// Initial Revision
 *
 */


