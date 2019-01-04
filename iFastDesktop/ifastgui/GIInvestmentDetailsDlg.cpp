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
//    Copyright 2011 by International Financial Data Services.
//
//******************************************************************************
//
// ^FILE   : GIInvestmentDetailsDlg.cpp
// ^CLASS  : GIInvestmentDetailsDlg
//
//******************************************************************************
#include "stdafx.h"
#include "mfdstc.h"
#include "giinvestmentdetailsdlg.h"

#include <uibase\dstedit.h>
#include <uibase\dstlistctrl.h>
#include <uibase\dstcombobox.h>
#include <uibase\dstcfuncs.h>
#include <uibase\ifdslistctrl.h>

#include <ifastbp\giinvestmentdetailsprocessincludes.h>
#include <ifastcbo\dstcommonfunction.hpp>
#include <uibase\DSTGridWnd.h>
#include <uibase\DSTOleDateTime.h>

#include <ifastcbo\dstcworksession.hpp>
#include <ifastcbo\mgmtcooptions.hpp>


#include <ifastbp\giinvestmentdetailsprocess.hpp>

#ifndef INCLUDED_ASSERT_H
#define INCLUDED_ASSERT_H
#include <assert.h>
#endif

extern CLASS_IMPORT const I_CHAR* CMD_GUI_GI_INVESTMENT_DETAILS; 
#include <bfproc\concretedialogcreator.hpp>
static ConcreteDialogCreator< GIInvestmentDetailsDlg > dlgCreator( CMD_GUI_GI_INVESTMENT_DETAILS ); 

#ifdef _DEBUG
   #define new DEBUG_NEW
   #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

namespace
{
   const I_CHAR * const CLASSNAME                     = I_("GIInvestmentDetailsDlg");

   const I_CHAR * const INVESTMENT_TYPE_FIX           = I_( "F" );
   const I_CHAR * const INVESTMENT_TYPE_PROGESSIVE    = I_( "P" );
   const I_CHAR * const FORCED_RATE_CONFIG_DERIVED    = I_( "1" );
   const I_CHAR * const FORCED_RATE_FORCED            = I_( "2" );
}

namespace CND
{
   extern CLASS_IMPORT const long GUI_ERR_UNKNOWN_EXCEPTION;
}

namespace ifds
{
   extern CLASS_IMPORT const BFDecimalFieldId ProgressiveIntRate;
   extern CLASS_IMPORT const BFNumericFieldId ProgressiveInvTerm;
   extern CLASS_IMPORT const BFTextFieldId ProgressiveIntRateDetailsList;
   extern CLASS_IMPORT const BFDateFieldId GIMaturityDate;
   extern CLASS_IMPORT const BFTextFieldId GIRedemInvSelectAmountType;
}

namespace GI_CONTROLS
{
//group of controls with fields part of a trade object 
   const UINT GI = 1;
}

//*****************************************************************************
// Public methods
//*****************************************************************************
GIInvestmentDetailsDlg::GIInvestmentDetailsDlg(CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand)
: BaseMainDlg( GIInvestmentDetailsDlg::IDD, pParent, pGIC, pGIParent, rCommand, CLASSNAME )
,m_dstrCaller(NULL_STRING)
,m_dstrAccountNum (NULL_STRING),m_ReadOnly(true)
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
}

//*****************************************************************************
void GIInvestmentDetailsDlg::DoDataExchange( CDataExchange* pDX )
{
   BaseMainDlg::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(GIInvestmentDetailsDlg)
   //}}AFX_DATA_MAP
}
//*****************************************************************************
BEGIN_MESSAGE_MAP(GIInvestmentDetailsDlg, BaseMainDlg)
//{{AFX_MSG_MAP(GIInvestmentDetailsDlg)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//*****************************************************************************
SEVERITY GIInvestmentDetailsDlg::doInit()
{
   TRACE_METHOD(CLASSNAME, DOINIT);

   getParameter (ACCOUNT_NUM, m_dstrAccountNum);
   getParameter (CALLER, m_dstrCaller);

   return (NO_CONDITION); /*sevRtn*/
}

//*****************************************************************************
BOOL GIInvestmentDetailsDlg::OnInitDialog() 
{
   TRACE_METHOD( CLASSNAME, ONINITDIALOG );
   BaseMainDlg::OnInitDialog(); 
   
   if(getParent())
      m_ReadOnly = ((GIInvestmentDetailsProcess*)getParent())->isReadOnly();

   AddControl ( CTRL_EDIT,  IDC_EDT_AMT_FROM, IFASTBP_PROC::GI_INVESTMENT_DETAILS_LIST, ifds::SelInvAmount, 
   CTRLFLAG_DEFAULT, GI_CONTROLS::GI);
   AddControl ( CTRL_COMBO, IDC_CMB_USE, IFASTBP_PROC::GI_INVESTMENT_DETAILS_LIST, ifds::IsInvSelected,
   CTRLFLAG_DEFAULT | CTRLFLAG_INITCOMBO_BY_SUB_LIST, GI_CONTROLS::GI);
   
   GetDlgItem (IDC_STATIC_GEN_11)->ShowWindow (!m_ReadOnly);//Amount
   GetDlgItem (IDC_STATIC_GEN_18)->ShowWindow (!m_ReadOnly); //Selected

   GetControl (IDC_EDT_AMT_FROM)->Show (!m_ReadOnly);
   GetControl (IDC_CMB_USE)->Show (!m_ReadOnly);

   AddControl ( CTRL_COMBO, IDC_CMB_AMOUNT_TYPE, IFASTBP_PROC::GI_INVESTMENT_DETAILS_LIST, ifds::GIRedemInvSelectAmountType, 
      CTRLFLAG_DEFAULT | CTRLFLAG_INITCOMBO_BY_SUB_LIST, GI_CONTROLS::GI);
   
   GetDlgItem (IDC_ST_TOTALS)->ShowWindow (!m_ReadOnly); 
   
   return TRUE; 
}
//******************************************************************************
void GIInvestmentDetailsDlg::OnPostInitDialog()
{
   TRACE_METHOD( CLASSNAME, ONPOSTINITDIALOG );
   AddListControl(CLASSNAME, IDC_LV_INVESTMENT_DETAILS,   I_("INVESTMENT_DETAILS"), ifds::GIInvestmentDetailsHeading, IFASTBP_PROC::GI_INVESTMENT_DETAILS_LIST, 0, true, LISTFLAG_NOT_AUTO_ADD );
   
   if(!m_ReadOnly)
      AddListControl(CLASSNAME, IDC_LV_SELECTED_INVESTMENTS, I_("SELECTED_INVESTMENTS"), ifds::GISelectedInvestmentsHeading, IFASTBP_PROC::GI_SELECTED_INVESTMENTS_LIST, 0, true, LISTFLAG_NOT_AUTO_ADD );

   GetDlgItem (IDC_LV_SELECTED_INVESTMENTS)->ShowWindow (!m_ReadOnly); 

   doRefresh (this, NULL);

   LoadListControl(IDC_LV_INVESTMENT_DETAILS);
   
   if(!m_ReadOnly)
      LoadListControl(IDC_LV_SELECTED_INVESTMENTS);
   
   LoadControl(IDC_CMB_AMOUNT_TYPE);
}

//*****************************************************************************
bool GIInvestmentDetailsDlg::doRefresh(GenericInterface * rpGICaller, const I_CHAR* szOriginalCommand )
{ 
   TRACE_METHOD( CLASSNAME, DOREFRESH );
   ConnectControlsToData ();
   LoadControls ();

   if(getParent ()->getNumberOfItemsInList(this, IFASTBP_PROC::GI_INVESTMENT_DETAILS_LIST) > 0)
   {
      ConnectControlsToData (GI_CONTROLS::GI);
   }
      
   SetDlgCaption ();
   return true;
}

//**********************************************************************************
void GIInvestmentDetailsDlg::SetDlgCaption()
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

//******************************************************************************
void GIInvestmentDetailsDlg::OnCancel()
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
void GIInvestmentDetailsDlg::ControlUpdated(UINT controlID, const DString &strValue )
{
   switch( controlID )
   {
   case IDC_CMB_AMOUNT_TYPE:
         {
            LoadListControl(IDC_LV_INVESTMENT_DETAILS);
         }
      break;
   case IDC_CMB_USE:
         LoadControl( IDC_EDT_AMT_FROM );
         break;

   default:
         break;
   }
}

void GIInvestmentDetailsDlg::DoListItemChanged( UINT listControlID,
                                              const DString &strKey, 
                                              bool isNewItem,
                                              bool bIsDummyItem)
{
   DString strMarket = DSTCommonFunctions::getMarket();

   switch( listControlID )
   {
      case IDC_LV_INVESTMENT_DETAILS:
      {
         getParent()->send( this, I_("CalculateTotals") );
         if(!m_ReadOnly)
            LoadListControl(IDC_LV_SELECTED_INVESTMENTS);

         if(!m_ReadOnly)
         {
            ConnectControlToData(IDC_EDT_AMT_FROM, true);
            LoadControl( IDC_EDT_AMT_FROM );
            LoadControl( IDC_CMB_USE );
         }
         else
         {
            ConnectControlToData(IDC_EDT_AMT_FROM, false);
            ConnectControlToData( IDC_CMB_USE, false);
         }
      }
   }
}


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/GIInvestmentDetailsDlg.cpp-arc  $
// 
//    Rev 1.7   Mar 21 2012 16:28:56   if991250
// IN 2885623 - GI Money Out - Error handling
// 
//    Rev 1.6   Mar 20 2012 16:43:30   if991250
// IN 2885623 - GI Money Oout
// 
//    Rev 1.5   Mar 12 2012 18:11:24   if991250
// GI Money Out
// 
//    Rev 1.4   Mar 08 2012 17:48:14   if991250
// GI Money Out
// 
//    Rev 1.3   Mar 08 2012 15:14:12   if991250
// Account Commitment
// 
//    Rev 1.2   Mar 08 2012 10:03:50   if991250
// GI Money Out
// 
//    Rev 1.1   Feb 17 2012 10:38:38   if991250
// GI Invest
// 
//    Rev 1.0   Jan 12 2012 10:25:56   jankovii
// Initial revision.
**/