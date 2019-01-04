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
// ^FILE   : EstateAllocationDlg.cpp
// ^CLASS  : EstateAllocationDlg
//
//******************************************************************************
#include "stdafx.h"
#include "mfdstc.h"
#include "estateallocationdlg.h"

#include <uibase\dstedit.h>
#include <uibase\dstlistctrl.h>
#include <uibase\dstcombobox.h>
#include <uibase\dstcfuncs.h>
#include <uibase\ifdslistctrl.h>

#include <ifastbp\estateallocationprocessincludes.h>
#include <ifastcbo\dstcommonfunction.hpp>
#include <uibase\DSTGridWnd.h>
#include <uibase\DSTOleDateTime.h>

#include <ifastcbo\dstcworksession.hpp>
#include <ifastcbo\mgmtcooptions.hpp>


#include <ifastbp\estateallocationprocess.hpp>

#ifndef INCLUDED_ASSERT_H
#define INCLUDED_ASSERT_H
#include <assert.h>
#endif

extern CLASS_IMPORT const I_CHAR* CMD_GUI_ESTATE_ALLOCATION; 
#include <bfproc\concretedialogcreator.hpp>
static ConcreteDialogCreator< EstateAllocationDlg > dlgCreator( CMD_GUI_ESTATE_ALLOCATION ); 

#ifdef _DEBUG
   #define new DEBUG_NEW
   #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CLASS_IMPORT const I_CHAR* CMD_BPROC_ADDRESSES;

namespace
{
   const I_CHAR * const CLASSNAME                     = I_("EstateAllocationDlg");

   const I_CHAR * const INVESTMENT_TYPE_FIX           = I_( "F" );
   const I_CHAR * const INVESTMENT_TYPE_PROGESSIVE    = I_( "P" );
   const I_CHAR * const FORCED_RATE_CONFIG_DERIVED    = I_( "1" );
   const I_CHAR * const FORCED_RATE_FORCED            = I_( "2" );

   const I_CHAR * const ADDR_LEVEL_SHAREHOLDER	      = I_( "S" );
   const I_CHAR * const ADDR_LEVEL_ENTITY	            = I_( "E" );
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
   extern CLASS_IMPORT const BFTextFieldId LV_EstateAllocation;
   extern CLASS_IMPORT const BFTextFieldId Address;
   extern CLASS_IMPORT const BFNumericFieldId ShrNum;
   extern CLASS_IMPORT const BFTextFieldId EntityType;
   extern CLASS_IMPORT const BFNumericFieldId SeqNumber;
   extern CLASS_IMPORT const BFTextFieldId ReadOnly;
}

namespace GI_CONTROLS
{
//group of controls with fields part of a trade object 
   const UINT GI = 1;
}

namespace ADDRLIT
{
   extern IFASTBP_LINKAGE const I_CHAR * const ACCOUNT_NUM;
   extern IFASTBP_LINKAGE const I_CHAR * const ENTITY_ID;
   extern IFASTBP_LINKAGE const I_CHAR * const FROM_ENTITY;
   extern IFASTBP_LINKAGE const I_CHAR * const SHAREHOLDER_NUM;
   extern IFASTBP_LINKAGE const I_CHAR * const SEQ_NUMBER;
   extern IFASTBP_LINKAGE const I_CHAR * const ENTITY_TYPE;

}

namespace NASULIT
{
   extern IFASTBP_LINKAGE const I_CHAR * const CREATING_ACCOUNT;
}
//*****************************************************************************
// Public methods
//*****************************************************************************
EstateAllocationDlg::EstateAllocationDlg(CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand)
: BaseMainDlg( EstateAllocationDlg::IDD, pParent, pGIC, pGIParent, rCommand, CLASSNAME )
,m_dstrCaller(NULL_STRING)
,m_dstrAccountNum (NULL_STRING),m_ReadOnly(true)
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
}

//*****************************************************************************
void EstateAllocationDlg::DoDataExchange( CDataExchange* pDX )
{
   BaseMainDlg::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(EstateAllocationDlg)
   //}}AFX_DATA_MAP
}
//*****************************************************************************
BEGIN_MESSAGE_MAP(EstateAllocationDlg, BaseMainDlg)
//{{AFX_MSG_MAP(EstateAllocationDlg)
ON_BN_CLICKED(IDC_BTN_ADDRESS, OnBtnAddress)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//*****************************************************************************
SEVERITY EstateAllocationDlg::doInit()
{
   TRACE_METHOD(CLASSNAME, DOINIT);

   getParameter (ACCOUNT_NUM, m_dstrAccountNum);
   getParameter (CALLER, m_dstrCaller);

   return (NO_CONDITION); /*sevRtn*/
}

//*****************************************************************************
BOOL EstateAllocationDlg::OnInitDialog() 
{
   TRACE_METHOD( CLASSNAME, ONINITDIALOG );
   BaseMainDlg::OnInitDialog(); 
   

   //AddControl ( CTRL_EDIT,  IDC_EDT_AMT_FROM, IFASTBP_PROC::GI_INVESTMENT_DETAILS_LIST, ifds::SelInvAmount, 
   //CTRLFLAG_DEFAULT, GI_CONTROLS::GI);
   //AddControl ( CTRL_COMBO, IDC_CMB_USE, IFASTBP_PROC::GI_INVESTMENT_DETAILS_LIST, ifds::IsInvSelected,
   //CTRLFLAG_DEFAULT | CTRLFLAG_INITCOMBO_BY_SUB_LIST, GI_CONTROLS::GI);
   
   return TRUE; 
}
//******************************************************************************
void EstateAllocationDlg::OnPostInitDialog()
{
   TRACE_METHOD( CLASSNAME, ONPOSTINITDIALOG );
   AddListControl(CLASSNAME, IDC_LV_ESTATE_ALLOCATION,   I_("ESTATE_ALLOCATION"), ifds::LV_EstateAllocation, IFASTBP_PROC::ESTATE_ALLOCATION, 0, true, LISTFLAG_NOT_AUTO_ADD );

   AddControl ( CTRL_COMBO, IDC_CMB_ADDR_LEVEL, IFASTBP_PROC::ESTATE_ALLOCATION, ifds::BenefAddrLevel, 
   CTRLFLAG_DEFAULT | CTRLFLAG_INITCOMBO_BY_SUB_LIST, IDC_LV_ESTATE_ALLOCATION);
   //AddControl ( CTRL_COMBO, IDC_CMB_ADDR_CODE, IFASTBP_PROC::ESTATE_ALLOCATION, ifds::BenefAddrCode, 
   //CTRLFLAG_DEFAULT | CTRLFLAG_INITCOMBO_BY_SUB_LIST, IDC_LV_ESTATE_ALLOCATION);
   AddControl ( CTRL_EDIT,  IDC_EDT_ADDRESS_CODE,  IFASTBP_PROC::ESTATE_ALLOCATION, ifds::BenefAddrCode,  CTRLFLAG_DEFAULT, IDC_LV_ESTATE_ALLOCATION);
   AddControl ( CTRL_EDIT,  IDC_EDT_PERCENT,  IFASTBP_PROC::ESTATE_ALLOCATION, ifds::BenefPrcnt,  CTRLFLAG_DEFAULT, IDC_LV_ESTATE_ALLOCATION);
   AddControl ( CTRL_EDIT,  IDC_EDT_AMT_FROM, IFASTBP_PROC::ESTATE_ALLOCATION, ifds::BenefAmount, CTRLFLAG_DEFAULT, IDC_LV_ESTATE_ALLOCATION);
   AddControl ( CTRL_EDIT,  IDC_EDT_UNITS,    IFASTBP_PROC::ESTATE_ALLOCATION, ifds::BenefUnits,  CTRLFLAG_DEFAULT, IDC_LV_ESTATE_ALLOCATION);
   AddControl ( CTRL_EDIT,  IDC_EDT_ADDRESS,  IFASTBP_PROC::ESTATE_ALLOCATION, ifds::Address,     CTRLFLAG_NOT_UPDATABLE, IDC_LV_ESTATE_ALLOCATION);

//   doRefresh (this, NULL);

   LoadListControl(IDC_LV_ESTATE_ALLOCATION);
   
   DString dstrReadOnly;
   getParent()->getField(this, IFASTBP_PROC::ESTATE_ALLOCATION, ifds::ReadOnly, dstrReadOnly, false);
   GetDlgItem( IDC_BTN_ADDRESS)->EnableWindow(dstrReadOnly == I_("N"));
   
}

//*****************************************************************************
bool EstateAllocationDlg::doRefresh(GenericInterface * rpGICaller, const I_CHAR* szOriginalCommand )
{ 
   TRACE_METHOD( CLASSNAME, DOREFRESH );
   ConnectControlsToData ();
   LoadControls ();

   SetDlgCaption ();
   return true;
}

//**********************************************************************************
void EstateAllocationDlg::SetDlgCaption()
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
void EstateAllocationDlg::OnCancel()
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
void EstateAllocationDlg::ControlUpdated(UINT controlID, const DString &strValue )
{
   switch( controlID )
   {
   case IDC_CMB_AMOUNT_TYPE:
         {
         }
      break;
   case IDC_CMB_USE:
         break;

   default:
         break;
   }
}

void EstateAllocationDlg::DoListItemChanged( UINT listControlID,
                                              const DString &strKey, 
                                              bool isNewItem,
                                              bool bIsDummyItem)
{
   DString strMarket = DSTCommonFunctions::getMarket();

   switch( listControlID )
   {
      case IDC_LV_INVESTMENT_DETAILS:
      {
      }
   }
}

//******************************************************************************
void EstateAllocationDlg::OnBtnAddress()
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnBtnEntityAddress()" ) );

   try
   {
      DString dstrBenefAddrLevel;
      getParent()->getField(this, IFASTBP_PROC::ESTATE_ALLOCATION, ifds::BenefAddrLevel, dstrBenefAddrLevel, false);

      if(dstrBenefAddrLevel == ADDR_LEVEL_ENTITY)
      {
         DString dstrEntityId, dstrShareholderNum, dstrEntityType, dstrSeqNum;
         getParent()->getField(this, IFASTBP_PROC::ESTATE_ALLOCATION, ifds::BenefEntityID, dstrEntityId, false);   
         getParent()->getField(this,ifds::ShrNum, dstrShareholderNum );

         getParent()->getField(this, IFASTBP_PROC::ESTATE_ALLOCATION, ifds::EntityType, dstrEntityType, false );   
         getParent()->getField(this, IFASTBP_PROC::ESTATE_ALLOCATION, ifds::SeqNumber,  dstrSeqNum, false );   

         dstrShareholderNum.stripLeading().stripLeading(I_CHAR('0')).stripTrailing();               
         
         setParameter( ADDRLIT::ENTITY_ID,        dstrEntityId );
         setParameter( ADDRLIT::ACCOUNT_NUM,      m_dstrAccountNum );      
         setParameter( NASULIT::CREATING_ACCOUNT, I_("N") );
         
         setParameter( ADDRLIT::FROM_ENTITY ,    I_( "Y" ) );   
         setParameter( ADDRLIT::SHAREHOLDER_NUM, dstrShareholderNum);

         setParameter( ADDRLIT::ENTITY_TYPE, dstrEntityType );
         setParameter( ADDRLIT::SEQ_NUMBER,  dstrSeqNum );
      }
      else if(dstrBenefAddrLevel == ADDR_LEVEL_SHAREHOLDER)
      {
         DString dstrEntityId, dstrShareholderNum, dstrEntityType, dstrSeqNum;
         getParent()->getField(this, IFASTBP_PROC::ESTATE_ALLOCATION, ifds::BenefEntityID, dstrEntityId, false);   
         getParent()->getField(this,ifds::ShrNum, dstrShareholderNum );

         setParameter( ADDRLIT::ACCOUNT_NUM,      m_dstrAccountNum );      
         setParameter( NASULIT::CREATING_ACCOUNT, I_("N") );

         setParameter( ADDRLIT::FROM_ENTITY ,    I_( "N" ) );   
         setParameter( ADDRLIT::SHAREHOLDER_NUM, dstrShareholderNum);
      }

      SetMessageStatusBar( TXT_LOAD_ADDRESS_BOOK );

      E_COMMANDRETURN eRtn;
      eRtn = invokeCommand( getParent(), CMD_BPROC_ADDRESSES, PROC_SUPPORT, true, NULL );

      switch( eRtn )
      {
         case CMD_OK:
            getParent()->send (this, I_("RefereshAddress"));
            break;
         case CMD_CANCEL:
            break;
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
/* $Log:   Y:/VCS/BF iFAST/ifastgui/EstateAllocationDlg.cpp-arc  $
// 
//    Rev 1.2   10 Aug 2012 13:09:28   if991250
// Estate Allocation
// 
//    Rev 1.1   29 Jul 2012 23:18:30   if991250
// Estate Allocation Address controls
// 
//    Rev 1.0   25 Jul 2012 15:28:18   if991250
// Initial revision.
// 
**/