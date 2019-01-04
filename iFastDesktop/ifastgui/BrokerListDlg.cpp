// BrokerListDlg.cpp : implementation file
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
// ^FILE   : BrokerListDlg.cpp
// ^AUTHOR : Winnie Shiu
// ^DATE   : January 18, 2000
//
// ----------------------------------------------------------
//
// ^CLASS    : BrokerListDlg
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :  This is the code for broker Dialog
//
//******************************************************************************


#include "stdafx.h"
#include "mfdstc.h"

#include "brokerlistdlg.h"
#include <ifastbp\brokerprocessincludes.h>
#include <ifastbp\mfcaninterprocparam.hpp>
#include <uibase\dstlistctrl.h>
#include <ifastcbo\DSTCWorkSession.hpp>
#include <ifastcbo\DSTCommonFunction.hpp>
//#include <ifastcbo\MFAccount.hpp>
#include <ifastcbo\MgmtCoOptions.hpp>

extern CLASS_IMPORT const I_CHAR* CMD_GUI_BROKER;
#include <bfproc\concretedialogcreator.hpp>
static ConcreteDialogCreator< BrokerListDlg > dlgCreator(CMD_GUI_BROKER);

#ifdef _DEBUG
   #define new DEBUG_NEW
   #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

namespace
{
   const I_CHAR * const CLASSNAME                     = I_("BrokerListDlg");
   const I_CHAR * const LV_BROKER                     = I_("BrokerList");
   const I_CHAR * const LV_FUND_BROKER                = I_("FundBrokerList");
   const I_CHAR * const STRING_Y                      = I_( "Y" );
   const I_CHAR * const SEARCH_USING_FUND_BROKER_CODE = I_( "0" );
   const I_CHAR * const SEARCH_USING_FUND_BROKER_NAME = I_( "1" );
   const I_CHAR * const SEARCH_USING_FAMILY_CODE      = I_( "0" );
}

namespace CND
{  // Conditions used
}


namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId SearchBroker;
   extern CLASS_IMPORT const BFTextFieldId SearchBrokerUsing;
   extern CLASS_IMPORT const BFTextFieldId BrokerListHeadingNSCC;
   extern CLASS_IMPORT const BFTextFieldId BrokerListHeadingFundBroker;
   extern CLASS_IMPORT const BFTextFieldId BrokerListHeadingFamilyCode; 
   extern CLASS_IMPORT const BFTextFieldId SearchFundBroker;
   extern CLASS_IMPORT const BFTextFieldId SearchFundBrokerUsing;
   extern CLASS_IMPORT const BFTextFieldId BrokerListHeadingFamilyCode;
   extern CLASS_IMPORT const BFTextFieldId SearchFamilyCode;
   extern CLASS_IMPORT const BFTextFieldId SearchFamilyCodeUsing;

}

/////////////////////////////////////////////////////////////////////////////
// BrokerListDlg dialog

//*****************************************************************************
BrokerListDlg::BrokerListDlg(CWnd* pParent, GenericInterfaceContainer* pGIC, 
   GenericInterface* pGIParent, const Command& rCommand)
: BaseMainDlg(BrokerListDlg::IDD, pParent, pGIC, pGIParent, rCommand, CLASSNAME),
m_dstrCaller(NULL_STRING), 
m_strSearchUsing( I_("0") )
{
   //{{AFX_DATA_INIT(BrokerListDlg)
   // NOTE: the ClassWizard will add member initialization here
   //}}AFX_DATA_INIT
}

//*****************************************************************************
void BrokerListDlg::DoDataExchange(CDataExchange* pDX)
{
   BaseMainDlg::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(BrokerListDlg)
   // NOTE: the ClassWizard will add DDX and DDV calls here
   //}}AFX_DATA_MAP
}


//*****************************************************************************
BEGIN_MESSAGE_MAP(BrokerListDlg, BaseMainDlg)
//{{AFX_MSG_MAP(BrokerListDlg)
ON_NOTIFY(NM_DBLCLK, IDC_LV_BROKER, OnDblclkLvBroker)
ON_BN_CLICKED(IDC_BTN_SEARCH, OnBtnSearch)
ON_BN_CLICKED(IDC_BTN_MORE, OnBtnMore)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()


//*****************************************************************************
BOOL BrokerListDlg::OnInitDialog() 
{
   BaseMainDlg::OnInitDialog();

   return(TRUE);
}

//*****************************************************************************
SEVERITY BrokerListDlg::doInit()
{
   TRACE_METHOD(CLASSNAME, DOINIT);

   getParameter(MFCAN_IP_PARAM::CALLER, m_dstrCaller);
   
   return NO_CONDITION;
}

//*****************************************************************************
void BrokerListDlg::OnPostInitDialog()
{
   AddControl(CTRL_COMBO, IDC_CMB_BROKER, BF::NullContainerId, 
      ifds::SearchBroker, CTRLFLAG_INITCOMBO_BY_SUB_LIST | CTRLFLAG_GUI_FIELD);
   AddControl(CTRL_COMBO, IDC_CMB_NAME, BF::NullContainerId, 
      ifds::SearchBrokerUsing, CTRLFLAG_INITCOMBO_BY_SUB_LIST | CTRLFLAG_GUI_FIELD );
   
   GetDlgItem(IDC_BTN_MORE)->EnableWindow(false);
   
   DString dstrNSCCCompliant;
   DSTCWorkSession *dstWorkSession = dynamic_cast<DSTCWorkSession *>(getParent()->getBFWorkSession());
   dstWorkSession->getOption( ifds::NSCCCompliant, dstrNSCCCompliant, getParent()->getDataGroupId(), false );
   if (m_dstrCaller == I_("PaymentInstructions"))
   {
      AddListControl(CLASSNAME, IDC_LV_BROKER, LV_BROKER, ifds::BrokerListHeadingPayments,
         IFASTBP_PROC::BROKER_LIST);
   }
   else if ( dstrNSCCCompliant == STRING_Y ) 
   {
      AddListControl(CLASSNAME, IDC_LV_BROKER, LV_BROKER, ifds::BrokerListHeadingNSCC,
         IFASTBP_PROC::BROKER_LIST);
   }
   else if (m_dstrCaller == I_("AggregatedOrders"))
   {
      ReInitControl( IDC_CMB_BROKER, BF::NullContainerId, ifds::SearchFundBroker, CTRLFLAG_INITCOMBO_BY_SUB_LIST | CTRLFLAG_GUI_FIELD );
      ReInitControl( IDC_CMB_NAME, BF::NullContainerId, ifds::SearchFundBrokerUsing, CTRLFLAG_INITCOMBO_BY_SUB_LIST | CTRLFLAG_GUI_FIELD );
      AddListControl(CLASSNAME, IDC_LV_BROKER, LV_FUND_BROKER, ifds::BrokerListHeadingFundBroker, IFASTBP_PROC::FUND_BROKER_LIST);
   }
   else if(m_dstrCaller == I_("ShrFamily"))
   {
      ReInitControl( IDC_CMB_BROKER, BF::NullContainerId, ifds::SearchFamilyCode, CTRLFLAG_INITCOMBO_BY_SUB_LIST | CTRLFLAG_GUI_FIELD );
      ReInitControl( IDC_CMB_NAME, BF::NullContainerId, ifds::SearchFamilyCodeUsing, CTRLFLAG_INITCOMBO_BY_SUB_LIST | CTRLFLAG_GUI_FIELD );
      AddListControl(CLASSNAME, IDC_LV_BROKER, LV_FUND_BROKER, ifds::BrokerListHeadingFamilyCode, IFASTBP_PROC::FAMILY_CODE_LIST);
   }
   else
   {
      AddListControl(CLASSNAME, IDC_LV_BROKER, LV_BROKER, ifds::BrokerListHeading, IFASTBP_PROC::BROKER_LIST);
   }
     
   doRefresh(this, NULL);
}

//*****************************************************************************
bool BrokerListDlg::GetDataForControl(UINT controlID,
   DString &strValueOut, bool bFormatted, int index) const
{
   bool bRtn = false;

   switch (controlID)
   {
      case IDC_CMB_BROKER:
      case IDC_CMB_NAME:
      {
         strValueOut = I_("0");
         bRtn = true;
         break;
      }
      default:
         break;
   }
   return bRtn;
}

//*****************************************************************************
bool BrokerListDlg::SetDataFromControl( UINT controlID,
                                        const DString &strValue,
                                        bool bFormatted,
                                        SEVERITY &sevRtn,
                                        int index )
{
   bool bRet = false;
   switch (controlID)
   {
      case 	IDC_CMB_BROKER :
         {
            bRet =  true;
            break;
         }
      case IDC_CMB_NAME :
         {
            m_strSearchUsing = strValue;
            bRet =  true;
            break;
         } 
      default:
         break;
   }
   return bRet;

}

//*****************************************************************************
bool BrokerListDlg::doRefresh(GenericInterface *rpGICaller, 
                              const I_CHAR * szOriginalCommand)
{
   DString strDlgCaption;
   /* If calling is from feature search screen with aggregated order and trade date */
   if( m_dstrCaller == I_("AggregatedOrders") )
   {
      CString cstrFundBrkr;
	  cstrFundBrkr.LoadString(TXT_SEARCH_FOR_FUND_BROKERS); 
	  strDlgCaption = DString(cstrFundBrkr);
      EnableControl(IDC_CMB_BROKER, true);
      EnableControl(IDC_CMB_NAME, true);
      FocusOnControl(IDC_CMB_BROKER);
   }
   else if(m_dstrCaller == I_("ShrFamily"))
   {
      CString cstrFamilyCode;
	  cstrFamilyCode.LoadString(TXT_SEARCH_FOR_FAMILY_CODE);
	  strDlgCaption = DString(cstrFamilyCode);
      EnableControl(IDC_CMB_BROKER, true);
      EnableControl(IDC_CMB_NAME, true);
      FocusOnControl(IDC_CMB_BROKER);
   }
   else if(m_dstrCaller == I_("RegPlanTransferSearch"))
   {
      CString cstrBroker;
      cstrBroker.LoadString(TXT_SEARCH_FOR_BROKER);
      strDlgCaption = DString(cstrBroker);
      EnableControl(IDC_CMB_BROKER, true);
      EnableControl(IDC_CMB_NAME, true);
      FocusOnControl(IDC_CMB_BROKER);
   }
   else
   {
      CString cstrBroker;
	  cstrBroker.LoadString(TXT_SEARCH_FOR_BROKER);
	  strDlgCaption = DString(cstrBroker);
      EnableControl(IDC_CMB_BROKER, false);
      EnableControl(IDC_CMB_NAME, false);
      FocusOnControl(IDC_EDT_NAME);
   }
   SetDlgCaption(strDlgCaption);
   ConnectControlsToData();
   LoadControls();
   return true;
}

//*****************************************************************************
void BrokerListDlg::OnDblclkLvBroker(NMHDR* pNMHDR, LRESULT* pResult)
{
   PostMessage(WM_COMMAND, IDOK);
   *pResult = 0;
}

//*****************************************************************************
void BrokerListDlg::OnBtnSearch() 
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnBtnSearch"));

   BFContainerId idContainer = BF::NullContainerId;
   
   GetDlgItem(IDC_BTN_SEARCH)->SetFocus();
   CWaitCursor wait;
   CString editNameValue;
   
   GetDlgItem(IDC_EDT_NAME)->GetWindowText(editNameValue);
   if( m_dstrCaller == I_("AggregatedOrders") )
   {
      idContainer = IFASTBP_PROC::FUND_BROKER_LIST;   
      
      // set parameter for broker process
      setParameter(I_("FundBrokerSearchUsing"), m_strSearchUsing);
      SetMessageStatusBar( TXT_SEARCH_FOR_FUND_BROKERS );
      
      if( m_strSearchUsing == SEARCH_USING_FUND_BROKER_CODE )   // SearchUsing is "FundBrokerCode"
      {
         setParameter(I_("FundBrokerCode"), DString(editNameValue.GetBuffer(0)));      
         setParameter(I_("FundBrokerName"), NULL_STRING);
      }
      if( m_strSearchUsing == SEARCH_USING_FUND_BROKER_NAME )   // SearchUsing is "FundBrokerName"
      {
         setParameter(I_("FundBrokerCode"), NULL_STRING);      
         setParameter(I_("FundBrokerName"), DString(editNameValue.GetBuffer(0)));
      }
   }
   else if(m_dstrCaller == I_("ShrFamily"))
   {
      idContainer = IFASTBP_PROC::FAMILY_CODE_LIST;   
      
      // set parameter for broker process
      setParameter(I_("FamilyCodeSearchUsing"), m_strSearchUsing);
      SetMessageStatusBar( TXT_SEARCH_FOR_FUND_BROKERS );
      
      if( m_strSearchUsing == SEARCH_USING_FAMILY_CODE )   // SearchUsing is "FamilyCode"
      {
         setParameter(I_("FamilyCode"), DString(editNameValue.GetBuffer(0)));      
      }
   }
   else
   {
      idContainer = IFASTBP_PROC::BROKER_LIST; 
      setParameter(I_("BrokerName"), DString(editNameValue.GetBuffer(0)));
      SetMessageStatusBar( TXT_SEARCH_FOR_BROKERS );
   }
      
   if (getParent()->performSearch(this, 
       idContainer, SEARCH_START) > WARNING)
   {
      ConditionMessageBox(MYFRAME(), GETCURRENTHIGHESTSEVERITY());
   }
   else
   {
      LoadListControl(IDC_LV_BROKER);
      GetList(IDC_LV_BROKER)->SetFocus();
      // check remaining record for enable or disable More button
      GetDlgItem (IDC_BTN_MORE)->
         EnableWindow ( getParent()->doMoreRecordsExist (this, idContainer) );
      SetMessageStatusBar( NULL_STRING );
   }
}

//*****************************************************************************
void BrokerListDlg::OnBtnMore()
{
    TRACE_METHOD( CLASSNAME, ONBTNMORE );
    CWaitCursor wait;
    
    BFContainerId idContainer = BF::NullContainerId;
    if( m_dstrCaller == I_("AggregatedOrders") )
    {
      idContainer = IFASTBP_PROC::FUND_BROKER_LIST;
      SetMessageStatusBar( TXT_LOAD_FUND_BROKERS );
    }
    else if(m_dstrCaller == I_("ShrFamily"))
    {
      idContainer = IFASTBP_PROC::FAMILY_CODE_LIST;
      SetMessageStatusBar( TXT_LOAD_FAMILY_CODE );
    }
    else
    {
      idContainer = IFASTBP_PROC::BROKER_LIST;
      SetMessageStatusBar( TXT_LOAD_BROKERS );
    }

    const DString *crtKey = &getParent()->getCurrentListItemKey( this, idContainer );

    if( getParent()->performSearch( this, idContainer, SEARCH_NEXT_BLOCK ) <= WARNING )
    {
       LoadListControl( IDC_LV_BROKER );
       if( *crtKey != NULL_STRING )
       {
          GetList( IDC_LV_BROKER )->SetSelection( crtKey );
       }
       GetDlgItem (IDC_BTN_MORE)->EnableWindow( getParent()->doMoreRecordsExist( this, idContainer ) );
    }
    SetMessageStatusBar( NULL_STRING );
}

//*****************************************************************************
void BrokerListDlg::SetDlgCaption(DString &strDlgCaption)
{
   TRACE_METHOD( CLASSNAME, I_( "SetDlgCaption" ) );
   
   SetWindowText ( strDlgCaption.c_str() );

}

//*****************************************************************************
void BrokerListDlg::ControlUpdated ( UINT controlID, 
                                     const DString &strValue)
{
   if (m_dstrCaller == I_("AggregatedOrders"))
   {
      switch (controlID)
      {
         case IDC_CMB_BROKER :
         {
            break;
         }
         case IDC_CMB_NAME :   // using key is changed
         {
            if( m_strSearchUsing == SEARCH_USING_FUND_BROKER_CODE )
            {
                CString cstrFundBroker;
				cstrFundBroker.LoadString(TXT_FND_BROKER);
				GetDlgItem( IDC_TXT_NAME )->SetWindowText( cstrFundBroker );
            }
            else if ( m_strSearchUsing == SEARCH_USING_FUND_BROKER_NAME )
            {
               CString cstrLastName;
			   cstrLastName.LoadString(TXT_LAST_NAME);
				GetDlgItem( IDC_TXT_NAME )->SetWindowText( cstrLastName );
            }
            GetDlgItem( IDC_EDT_NAME )->SetWindowText( NULL_STRING );
            break;
         } 
      }     // end switch case
   }  // end if
   else if(m_dstrCaller == I_("ShrFamily"))
   {
      switch (controlID)
      {
         case IDC_CMB_BROKER :
         {
            break;
         }
         case IDC_CMB_NAME :   // using key is changed
         {
            if( m_strSearchUsing == SEARCH_USING_FAMILY_CODE )
            {
               GetDlgItem( IDC_TXT_NAME )->SetWindowText( I_("Family Code:") );
            }
            //else if ( m_strSearchUsing == SEARCH_USING_FAMILY_NAME )
            //{
            //   GetDlgItem( IDC_TXT_NAME )->SetWindowText( I_("Family Name:") );
            //}
            GetDlgItem( IDC_EDT_NAME )->SetWindowText( NULL_STRING );
            break;
         } 
      }     // end switch case
   }
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/BrokerListDlg.cpp-arc  $
 * 
 *    Rev 1.15   Nov 19 2011 01:24:22   wp040143
 * P0186484/FN06 - DESKTOP - iFast Desktop (French Customizations)
 * 
 *    Rev 1.14   Nov 08 2011 12:24:14   dchatcha
 * P0188902 FN02 - DYN Household Project
 * 
 *    Rev 1.13   Apr 06 2009 04:14:14   kitticha
 * IN#1588682 - Small Enhancement - Feature search screen for Fund Broker Search. - additional code changes for More button
 * 
 *    Rev 1.12   Mar 25 2009 07:19:56   kitticha
 * IN#1588682 - Small Enhancement - Feature search screen for Fund Broker Search.
 * 
 *    Rev 1.11   Sep 15 2005 15:10:52   popescu
 * Incident#403519 - added CLASSNAME as the fifth parameter to  BaseMainDlg constructor
 * 
 *    Rev 1.10   Jul 06 2005 11:01:44   ZHANGCEL
 * PET1141 - FN05 -- NSCC Broker enhancement
 * 
 *    Rev 1.9   Jul 10 2003 22:21:34   popescu
 * check in for payment instruct, used mfcan_ip_param for some interporcess param passing
 * 
 *    Rev 1.8   Mar 21 2003 18:33:40   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.7   Oct 09 2002 23:55:32   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.6   22 May 2002 19:15:50   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.5   27 Mar 2002 20:01:00   PURDYECH
 * Process/WindowFactory overhaul
 * 
 *    Rev 1.4   05 Dec 2001 11:33:16   KOVACSRO
 * Hour glass.
 * 
 *    Rev 1.3   Nov 03 2000 16:06:58   DINACORN
 * Set Focus on the BrokerList after search was done
 * 
 *    Rev 1.2   Sep 19 2000 18:06:22   DINACORN
 * For F4-BrokerSearch the boxes "Broker" and "Name" must be disabled
 * 
 *    Rev 1.1   Feb 25 2000 11:21:48   POPESCUS
 * fixes
// 
//    Rev 1.2   Jan 24 2000 18:11:32   POPESCUS
// some fixes
// 
//    Rev 1.1   Jan 22 2000 15:42:18   WINNIE
// To get search work
*/