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
// ^FILE   : SettlementInstrDlg.cpp
// ^AUTHOR : 
// ^DATE   : 
//
// ----------------------------------------------------------
//
// ^CLASS    : SettlementInstrDlg
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :  
//
//******************************************************************************

#include "stdafx.h"
#include "mfdstc.h"

#include "settlementinstrdlg.h"
#include <configmanager.hpp>
#include <uibase\DSTEdit.h>
#include <uibase\ifdslistctrl.h>

#include <ifastbp\mfcaninterprocparam.hpp>
#include <ifastbp\settlementinstrprocessincludes.h>

#ifndef INCLUDED_ASSERT_H
#define INCLUDED_ASSERT_H
#include <assert.h>
#endif

#ifdef _DEBUG
   #define new DEBUG_NEW
   #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

namespace
{
   const I_CHAR * const CLASSNAME = I_("SettlementInstrDlg");
}

class LVFundMgmtSettlementInstrData : public IFDSListCtrlRowDataBase
{
public:
   virtual ~LVFundMgmtSettlementInstrData() {}
   DString SettleLocationCode_;
   DString SettleLocationDesc_;
   DString SettleAccountNum_;
   DString Default_;   
   DString InternalSettlementAccount_;
   virtual void update(BaseDlg* pDlg, IFDSListCtrl* pCtrl, const DString* pKey)
   {
      pDlg->getParent()->getField( pDlg, BF::NullContainerId, ifds::SettleLocationCode, SettleLocationCode_ );
      SettleLocationCode_.strip();
      pDlg->getParent()->getField( pDlg, BF::NullContainerId, ifds::SettleLocationDesc, SettleLocationDesc_ );
      SettleLocationDesc_.strip();
      pDlg->getParent()->getField( pDlg, BF::NullContainerId, ifds::SettleAccountNum, SettleAccountNum_ );
      SettleAccountNum_.strip();
      pDlg->getParent()->getField( pDlg, BF::NullContainerId, ifds::Default, Default_ );
      Default_.strip();   
      pDlg->getParent()->getField( pDlg, BF::NullContainerId, ifds::Default, InternalSettlementAccount_ );
      InternalSettlementAccount_.strip();         
   }
};

class LVFundMgmtSettlementInstrAdapter : public IFDSListCtrlAdapter< LVFundMgmtSettlementInstrData >
{
public:
   // required overrides
   virtual int compare(IFDSListBase* pCtrl, int iSortColumn, bool bAscending, 
      RowData* pData1, RowData* pData2, LPARAM lParam1, LPARAM lParam2)
   {
      int result = 0;

      const BFFieldId* pFieldId = pCtrl->getColumnField(iSortColumn - 1);
      if (1 == iSortColumn) 
      {
         // Condition indicator column.  Sort on image index
         result = (IFDSListBase::getColumnLVItem(lParam1, iSortColumn - 1)->iImage - 
                    IFDSListBase::getColumnLVItem(lParam2, iSortColumn - 1)->iImage);
      } 
      else if (NULL == pFieldId) 
      {
         return (0);
      } 
      else if (*pFieldId == ifds::SettleLocationCode) 
      {
         result = i_strcmp(pData1->SettleLocationCode_.c_str(), pData2->SettleLocationCode_.c_str());
      } 
		else if (*pFieldId == ifds::SettleLocationDesc) 
      {
         result = i_strcmp(pData1->SettleLocationDesc_.c_str(), pData2->SettleLocationDesc_.c_str());
      } 
      else if (*pFieldId == ifds::SettleAccountNum) 
      {
         result = i_strcmp(pData1->SettleAccountNum_.c_str(), pData2->SettleAccountNum_.c_str());
      } 
      else if (*pFieldId == ifds::Default) 
      {
         result = i_strcmp(pData1->Default_.c_str(), pData2->Default_.c_str());
      }     
       else if (*pFieldId == ifds::InternalSettlementAccount) 
      {
         result = i_strcmp(pData1->InternalSettlementAccount_.c_str(), pData2->Default_.c_str());
      }         
      return (bAscending ? result : -result);
   }

   virtual LRESULT onGetDispInfo(IFDSListCtrl* pCtrl, RowData* pData, LV_DISPINFO* pDispInfo)
   {
      if (pDispInfo->item.mask & LVIF_TEXT)
      {
         const BFFieldId* pFieldId = pCtrl->getColumnField(pDispInfo->item.iSubItem);

         if (NULL == pFieldId) 
         {
            pDispInfo->item.pszText = I_("");
         } 
         else if (*pFieldId == ifds::SettleLocationCode) 
         {
            pDispInfo->item.pszText = (I_CHAR*)pData->SettleLocationCode_.c_str();
         } 
         else if (*pFieldId == ifds::SettleLocationDesc) 
         {
            pDispInfo->item.pszText = (I_CHAR*)pData->SettleLocationDesc_.c_str();
         } 
         else if (*pFieldId == ifds::SettleAccountNum) 
         {
            pDispInfo->item.pszText = (I_CHAR*)pData->SettleAccountNum_.c_str();
         } 
         else if (*pFieldId == ifds::Default)
         {
            pDispInfo->item.pszText = (I_CHAR*)pData->Default_.c_str();
         } 
         else if (*pFieldId == ifds::InternalSettlementAccount)
         {
            pDispInfo->item.pszText = (I_CHAR*)pData->InternalSettlementAccount_.c_str();
         }            
         return (1);
      }
      return (0);
   }
};

class LVSettlementInstrData : public IFDSListCtrlRowDataBase
{
public:
   virtual ~LVSettlementInstrData() {}
   DString SettlementInstrCode_;
   DString DeliveryTo_;
   DString ForAccount_;
   DString InFavourOf_;   
   DString DefaultSettlementInstr_;
   DString AcctClearingMethod_;
   DString EffectiveDate_;
   DString StopDate_;
   DString CSDLocation_;
   DString CSDAccount_;

	
   virtual void update(BaseDlg* pDlg, IFDSListCtrl* pCtrl, const DString* pKey)
   {
      pDlg->getParent()->getField( pDlg, BF::NullContainerId, ifds::SettlementInstrCode, SettlementInstrCode_ );
      SettlementInstrCode_.strip();
      pDlg->getParent()->getField( pDlg, BF::NullContainerId, ifds::DeliveryTo, DeliveryTo_ );
      DeliveryTo_.strip();
      pDlg->getParent()->getField( pDlg, BF::NullContainerId, ifds::ForAccount, ForAccount_ );
      ForAccount_.strip();
      pDlg->getParent()->getField( pDlg, BF::NullContainerId, ifds::InFavourOf, InFavourOf_ );
      InFavourOf_.strip(); 
	  pDlg->getParent()->getField( pDlg, BF::NullContainerId, ifds::CSDLocation, CSDLocation_ );
      CSDLocation_.strip();    
	  pDlg->getParent()->getField( pDlg, BF::NullContainerId, ifds::CSDAcctNum, CSDAccount_ );
      CSDAccount_.strip(); 
      pDlg->getParent()->getField( pDlg, BF::NullContainerId, ifds::DefaultSettlementInstr, DefaultSettlementInstr_ );
      DefaultSettlementInstr_.strip();            
      pDlg->getParent()->getField( pDlg, BF::NullContainerId, ifds::AcctClearingMethod, AcctClearingMethod_ );
      AcctClearingMethod_.strip();            
      pDlg->getParent()->getField( pDlg, BF::NullContainerId, ifds::EffectiveDate, EffectiveDate_ );
      EffectiveDate_.strip();            
      pDlg->getParent()->getField( pDlg, BF::NullContainerId, ifds::StopDate, StopDate_ );
      StopDate_.strip();            

   }
};

class LVSettlementInstrAdapter : public IFDSListCtrlAdapter< LVSettlementInstrData >
{
public:
   // required overrides
   virtual int compare(IFDSListBase* pCtrl, int iSortColumn, bool bAscending, 
      RowData* pData1, RowData* pData2, LPARAM lParam1, LPARAM lParam2)
   {
      int result = 0;

      const BFFieldId* pFieldId = pCtrl->getColumnField(iSortColumn - 1);
      if (1 == iSortColumn) 
      {
         // Condition indicator column.  Sort on image index
         result = (IFDSListBase::getColumnLVItem(lParam1, iSortColumn - 1)->iImage - 
                    IFDSListBase::getColumnLVItem(lParam2, iSortColumn - 1)->iImage);
      }
      else if (NULL == pFieldId)
      {
         return (0);
      }
      else if (*pFieldId == ifds::SettlementInstrCode) 
      {
         result = i_strcmp(pData1->SettlementInstrCode_.c_str(), pData2->SettlementInstrCode_.c_str());
      }
	  else if (*pFieldId == ifds::DeliveryTo)
      {
         result = i_strcmp(pData1->DeliveryTo_.c_str(), pData2->DeliveryTo_.c_str());
      }
      else if (*pFieldId == ifds::ForAccount) 
      {
         result = i_strcmp(pData1->ForAccount_.c_str(), pData2->ForAccount_.c_str());
      }
      else if (*pFieldId == ifds::InFavourOf) 
      {
         result = i_strcmp(pData1->InFavourOf_.c_str(), pData2->InFavourOf_.c_str());
      }
      else if (*pFieldId == ifds::DefaultSettlementInstr) 
      {
         result = i_strcmp(pData1->DefaultSettlementInstr_.c_str(), pData2->DefaultSettlementInstr_.c_str());
      }
      else if (*pFieldId == ifds::AcctClearingMethod) 
      {
         result = i_strcmp(pData1->AcctClearingMethod_.c_str(), pData2->AcctClearingMethod_.c_str());
      }
      else if (*pFieldId == ifds::EffectiveDate) 
      {
         result = i_strcmp(pData1->EffectiveDate_.c_str(), pData2->EffectiveDate_.c_str());
      }
      else if (*pFieldId == ifds::StopDate) 
      {
         result = i_strcmp(pData1->StopDate_.c_str(), pData2->StopDate_.c_str());
      }

	   else if (*pFieldId == ifds::CSDLocation) 
      {
         result = i_strcmp(pData1->CSDLocation_.c_str(), pData2->CSDLocation_.c_str());
      }
	   else if (*pFieldId == ifds::CSDAcctNum) 
      {
         result = i_strcmp(pData1->CSDAccount_.c_str(), pData2->CSDAccount_.c_str());
      }


      return (bAscending ? result : -result);
   }

   virtual LRESULT onGetDispInfo(IFDSListCtrl* pCtrl, RowData* pData, LV_DISPINFO* pDispInfo)
   {
      if (pDispInfo->item.mask & LVIF_TEXT)
      {
         const BFFieldId* pFieldId = pCtrl->getColumnField(pDispInfo->item.iSubItem);

         if (NULL == pFieldId) 
         {
            pDispInfo->item.pszText = I_("");
         } 
         else if (*pFieldId == ifds::SettlementInstrCode) 
         {
            pDispInfo->item.pszText = (I_CHAR*)pData->SettlementInstrCode_.c_str();
         } 
         else if (*pFieldId == ifds::DeliveryTo) 
         {
            pDispInfo->item.pszText = (I_CHAR*)pData->DeliveryTo_.c_str();
         } 
         else if (*pFieldId == ifds::ForAccount) 
         {
            pDispInfo->item.pszText = (I_CHAR*)pData->ForAccount_.c_str();
         } 
         else if (*pFieldId == ifds::InFavourOf)
         {
            pDispInfo->item.pszText = (I_CHAR*)pData->InFavourOf_.c_str();
         }   
         else if (*pFieldId == ifds::DefaultSettlementInstr)
         {
            pDispInfo->item.pszText = (I_CHAR*)pData->DefaultSettlementInstr_.c_str();
         }
         else if (*pFieldId == ifds::AcctClearingMethod)
         {
            pDispInfo->item.pszText = (I_CHAR*)pData->AcctClearingMethod_.c_str();
         }
         else if (*pFieldId == ifds::EffectiveDate)
         {
            pDispInfo->item.pszText = (I_CHAR*)pData->EffectiveDate_.c_str();
         }   
         else if (*pFieldId == ifds::StopDate)
         {
            pDispInfo->item.pszText = (I_CHAR*)pData->StopDate_.c_str();
         }   
		 else if (*pFieldId == ifds::CSDLocation)
         {
            pDispInfo->item.pszText = (I_CHAR*)pData->CSDLocation_.c_str();
         } 
		  else if (*pFieldId == ifds::CSDAcctNum)
         {
            pDispInfo->item.pszText = (I_CHAR*)pData->CSDAccount_.c_str();
         } 
		 
         return (1);
      }
      return (0);
   }
};

//*****************************************************************************
// Public methods
//*****************************************************************************
SettlementInstrDlg::SettlementInstrDlg( CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: BaseMainDlg( SettlementInstrDlg::IDD, pParent, pGIC, pGIParent, rCommand, CLASSNAME )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   //{{AFX_DATA_INIT(SettlementInstrDlg)
   //}}AFX_DATA_INIT
}

//*****************************************************************************
void SettlementInstrDlg::DoDataExchange( CDataExchange* pDX )
{
   BaseMainDlg::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(SettlementInstrDlg)
   //}}AFX_DATA_MAP
}

//*****************************************************************************
BEGIN_MESSAGE_MAP(SettlementInstrDlg, BaseMainDlg)
//{{AFX_MSG_MAP(SettlementInstrDlg)
ON_BN_CLICKED( IDC_BTN_ADD, OnBtnAdd )
ON_BN_CLICKED( IDC_BTN_DEL, OnBtnDel )
ON_BN_CLICKED( IDC_BTN_RESET, OnBtnReset )
ON_BN_CLICKED( IDC_BTN_HISTORICAL, OnBtnHistorical )
ON_BN_CLICKED( IDC_BTN_ADM_DATES, OnBtnAdmDates )
ON_BN_CLICKED( IDC_BTN_ADD_SETTLEMENT_INSTRUCTION, OnBtnAddSettlInstr )
ON_BN_CLICKED( IDC_BTN_DELETE_SETTLEMENT_INSTRUCTION, OnBtnDelSettlInstr )
ON_BN_CLICKED( IDC_BTN_RESET_SETTLEMENT_INSTRUCTION, OnBtnResetSettlInstr )
ON_BN_CLICKED( IDC_BTN_HISTORICAL_SETTLEMENT_INSTRUCTION, OnBtnHistoricalSettlInstr )
ON_BN_CLICKED( IDC_BTN_ADM_DATES_SETTLEMENT_INSTRUCTION, OnBtnAdmDatesSettlInstr )

//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//*****************************************************************************
// Message handlers
//*****************************************************************************
BOOL SettlementInstrDlg::OnInitDialog() 
{
   TRACE_METHOD( CLASSNAME, ONINITDIALOG );
   BaseMainDlg::OnInitDialog(); 

   return(TRUE);
}

//******************************************************************************
void SettlementInstrDlg::OnPostInitDialog()
{
   TRACE_METHOD( CLASSNAME, ONPOSTINITDIALOG );

	addBtnAddForPermissionCheck( IDC_BTN_ADD, IDC_LST_SETTLEMENT_INSTRUCTIONS );
	addBtnDeleteForPermissionCheck( IDC_BTN_DEL, IDC_LST_SETTLEMENT_INSTRUCTIONS );
   
	setSettlementInstructionsControls();

   IFDSListCtrl* ifdsListFundMgmtSettlementInstr = 
      new IFDSAdaptedListCtrl< LVFundMgmtSettlementInstrAdapter >( this, 
		                                                             CLASSNAME, 
                                                                   IDC_LST_SETTLEMENT_INSTRUCTIONS, 
																				       0, 
																				       0, 
																				       true, 
																				       true );

   AddIFDSListControl( ifdsListFundMgmtSettlementInstr, 
							  I_("FUND_MGMT_SETTLEMENT_INSTRUCTIONS"), 
							  IFASTBP_PROC::FUND_MGMT_SETTLEMENT_INSTR_LIST, 
                       ifds::FundMgmtSettleInstrHeadingSet );   

   // Default the sorting column to Settlement Location Description
	if ( NULL != ifdsListFundMgmtSettlementInstr )		
		ifdsListFundMgmtSettlementInstr->SortOnColumn( 3 );
	AddControl( CTRL_COMBO, IDC_CMB_SETTLEMENT_LOCATION, IFASTBP_PROC::FUND_MGMT_SETTLEMENT_INSTR_LIST, ifds::SettleLocationCode, CTRLFLAG_INITCOMBO_BY_SUB_LIST, IDC_LST_SETTLEMENT_INSTRUCTIONS ); 
	AddControl( CTRL_EDIT,  IDC_EDT_ACCOUNT,    IFASTBP_PROC::FUND_MGMT_SETTLEMENT_INSTR_LIST, ifds::SettleAccountNum, CTRLFLAG_DEFAULT | CTRLFLAG_NOT_UPDATABLE, IDC_LST_SETTLEMENT_INSTRUCTIONS );   
	AddControl( CTRL_COMBO, IDC_DEFAULT,                 IFASTBP_PROC::FUND_MGMT_SETTLEMENT_INSTR_LIST, ifds::Default, CTRLFLAG_INITCOMBO_BY_SUB_LIST, IDC_LST_SETTLEMENT_INSTRUCTIONS );
    AddControl( CTRL_EDIT,	IDC_EDT_INT_SETL_ACC, IFASTBP_PROC::FUND_MGMT_SETTLEMENT_INSTR_LIST, ifds::InternalSettlementAccount, CTRLFLAG_DEFAULT | CTRLFLAG_NOT_UPDATABLE, IDC_LST_SETTLEMENT_INSTRUCTIONS);

   IFDSListCtrl* ifdsListSettlementInstr = 
      new IFDSAdaptedListCtrl< LVSettlementInstrAdapter >( this, 
                                                           CLASSNAME, 
                                                           IDC_LST_SETTL_INSTR, 
                                                           0, 
                                                           0, 
                                                           true, 
                                                           true );

   AddIFDSListControl( ifdsListSettlementInstr, 
					   I_("SETTL_INSTR"), 
					   IFASTBP_PROC::SETTLEMENT_INSTRUCTIONS_LIST, 
                       ifds::SettlementInstrHeadingSet );   

   // Default the sorting column to Settlement Instruction Code
	if ( NULL != ifdsListSettlementInstr )		
		ifdsListSettlementInstr->SortOnColumn( 2 );
	
	AddControl( CTRL_EDIT, IDC_EDT_SETTL_INSTR_CODE,            IFASTBP_PROC::SETTLEMENT_INSTRUCTIONS_LIST, ifds::SettlementInstrCode,   CTRLFLAG_DEFAULT, (UINT)IDC_LST_SETTL_INSTR );   
	
   AddControl( CTRL_EDIT, IDC_EDT_SETTL_INSTR_DELIVERY_TO,     IFASTBP_PROC::SETTLEMENT_INSTRUCTIONS_LIST, ifds::DeliveryTo,      CTRLFLAG_DEFAULT, (UINT)IDC_LST_SETTL_INSTR );   
   dynamic_cast<DSTEdit *>(GetControl(IDC_EDT_SETTL_INSTR_DELIVERY_TO))->SetMaxCharNum( 50);

	AddControl( CTRL_EDIT, IDC_EDT_SETTL_INSTR_FOR_ACCOUNT,     IFASTBP_PROC::SETTLEMENT_INSTRUCTIONS_LIST, ifds::ForAccount,      CTRLFLAG_DEFAULT, (UINT)IDC_LST_SETTL_INSTR );   		
   dynamic_cast<DSTEdit *>(GetControl(IDC_EDT_SETTL_INSTR_FOR_ACCOUNT))->SetMaxCharNum( 50);

	AddControl( CTRL_EDIT, IDC_EDT_SETTL_INSTR_IN_FAVOUR_OF,    IFASTBP_PROC::SETTLEMENT_INSTRUCTIONS_LIST, ifds::InFavourOf,      CTRLFLAG_DEFAULT, (UINT)IDC_LST_SETTL_INSTR );   
   dynamic_cast<DSTEdit *>(GetControl(IDC_EDT_SETTL_INSTR_IN_FAVOUR_OF))->SetMaxCharNum( 50);

   	AddControl( CTRL_EDIT, IDC_EDT_SETTL_INSTR_CSD_LOCATION,    IFASTBP_PROC::SETTLEMENT_INSTRUCTIONS_LIST, ifds::CSDLocation,      CTRLFLAG_DEFAULT, (UINT)IDC_LST_SETTL_INSTR );   
   dynamic_cast<DSTEdit *>(GetControl(IDC_EDT_SETTL_INSTR_CSD_LOCATION))->SetMaxCharNum( 40);

   	AddControl( CTRL_EDIT, IDC_EDT_SETTL_INSTR_CSD_ACCOUNT,    IFASTBP_PROC::SETTLEMENT_INSTRUCTIONS_LIST, ifds::CSDAcctNum,      CTRLFLAG_DEFAULT, (UINT)IDC_LST_SETTL_INSTR );   
   dynamic_cast<DSTEdit *>(GetControl(IDC_EDT_SETTL_INSTR_CSD_ACCOUNT))->SetMaxCharNum( 40);

	AddControl( CTRL_COMBO, IDC_CMB_SETTL_INSTR_DEFAULT_SETTING, IFASTBP_PROC::SETTLEMENT_INSTRUCTIONS_LIST, ifds::DefaultSettlementInstr, CTRLFLAG_INITCOMBO_BY_SUB_LIST, (UINT)IDC_LST_SETTL_INSTR );   	
	
   AddControl( CTRL_DATE,	IDC_DTC_START_DATE,	     IFASTBP_PROC::SETTLEMENT_INSTRUCTIONS_LIST, ifds::EffectiveDate, CTRLFLAG_INITCOMBO_BY_SUB_LIST, (UINT)IDC_LST_SETTL_INSTR );
   AddControl( CTRL_DATE,	IDC_DTC_STOP_DATE,	     IFASTBP_PROC::SETTLEMENT_INSTRUCTIONS_LIST, ifds::StopDate,      CTRLFLAG_INITCOMBO_BY_SUB_LIST, (INT)IDC_LST_SETTL_INSTR );

   AddControl( CTRL_COMBO,  IDC_CMB_CLEARING_METHOD, IFASTBP_PROC::SETTLEMENT_INSTRUCTIONS_LIST, ifds::AcctClearingMethod, CTRLFLAG_INITCOMBO_BY_SUB_LIST, (UINT)IDC_LST_SETTL_INSTR );
   
   AddControl( CTRL_EDIT,	IDC_EDT_PREF_CASH_MSG_TYPE,	 IFASTBP_PROC::SETTLEMENT_INSTRUCTIONS_LIST, ifds::CashMsgType, CTRLFLAG_INITCOMBO_BY_SUB_LIST, (UINT)IDC_LST_SETTL_INSTR );
   AddControl( CTRL_EDIT,	IDC_EDT_INTERMEDIARY_BANK,	 IFASTBP_PROC::SETTLEMENT_INSTRUCTIONS_LIST, ifds::IntermediaryBank, CTRLFLAG_INITCOMBO_BY_SUB_LIST, (UINT)IDC_LST_SETTL_INSTR );
   AddControl( CTRL_EDIT,	IDC_EDT_RECEIVING_BANK,	     IFASTBP_PROC::SETTLEMENT_INSTRUCTIONS_LIST, ifds::ReceivingBank, CTRLFLAG_INITCOMBO_BY_SUB_LIST, (UINT)IDC_LST_SETTL_INSTR );
   AddControl( CTRL_EDIT,	IDC_EDT_BENFICIARY,	         IFASTBP_PROC::SETTLEMENT_INSTRUCTIONS_LIST, ifds::Beneficiary, CTRLFLAG_INITCOMBO_BY_SUB_LIST, (UINT)IDC_LST_SETTL_INSTR );
   AddControl( CTRL_EDIT,	IDC_EDT_SPECIAL_INST,	     IFASTBP_PROC::SETTLEMENT_INSTRUCTIONS_LIST, ifds::SpecialInstructions, CTRLFLAG_INITCOMBO_BY_SUB_LIST, (UINT)IDC_LST_SETTL_INSTR );
   
   dynamic_cast<DSTEdit *>( GetControl( IDC_EDT_PREF_CASH_MSG_TYPE ) )->SetMaxCharNum( 25 );
   dynamic_cast<DSTEdit *>( GetControl( IDC_EDT_INTERMEDIARY_BANK ) )->SetMaxCharNum( 50 );
   dynamic_cast<DSTEdit *>( GetControl( IDC_EDT_BENFICIARY ) )->SetMaxCharNum( 50 );
   dynamic_cast<DSTEdit *>( GetControl( IDC_EDT_SPECIAL_INST ) )->SetMaxCharNum( 50 );
   //GetControl( IDC_STC_SETTLE_ACCOUNT )->Enable (false);

	LoadListControl( IDC_LST_SETTLEMENT_INSTRUCTIONS );
	LoadListControl( IDC_LST_SETTL_INSTR );

   CWnd* pSettlInstrDeliveryToWnd = GetDlgItem(IDC_EDT_SETTL_INSTR_DELIVERY_TO);
   if (NULL != pSettlInstrDeliveryToWnd)
   {
       if (DSTEdit* pDSTEditSettlInstrDeliveryTo = dynamic_cast<DSTEdit*>(pSettlInstrDeliveryToWnd))
       {
           pDSTEditSettlInstrDeliveryTo->SetRemoveUnwantedCharsAfterPaste(true);
       }
   }

   CWnd* pSettlInstrForAccountWnd = GetDlgItem(IDC_EDT_SETTL_INSTR_FOR_ACCOUNT);
   if (NULL != pSettlInstrForAccountWnd)
   {
       if (DSTEdit* pDSTEditSettlInstrForAccount = dynamic_cast<DSTEdit*>(pSettlInstrForAccountWnd))
       {
           pDSTEditSettlInstrForAccount->SetRemoveUnwantedCharsAfterPaste(true);
       }
   }

   CWnd* pSettlInstrInFavorOfWnd = GetDlgItem(IDC_EDT_SETTL_INSTR_IN_FAVOUR_OF);
   if (NULL != pSettlInstrInFavorOfWnd)
   {
       if (DSTEdit* pDSTEditSettlInstrInFavorOf = dynamic_cast<DSTEdit*>(pSettlInstrInFavorOfWnd))
       {
           pDSTEditSettlInstrInFavorOf->SetRemoveUnwantedCharsAfterPaste(true);
       }
   }

   CWnd* pSettlInstrCsdLocationWnd = GetDlgItem(IDC_EDT_SETTL_INSTR_CSD_LOCATION);
   if (NULL != pSettlInstrCsdLocationWnd)
   {
       if (DSTEdit* pDSTEditSettlInstrCsdLocation = dynamic_cast<DSTEdit*>(pSettlInstrCsdLocationWnd))
       {
           pDSTEditSettlInstrCsdLocation->SetRemoveUnwantedCharsAfterPaste(true);
       }
   }

   CWnd* pSettlInstrCsdAccountNumWnd = GetDlgItem(IDC_EDT_SETTL_INSTR_CSD_ACCOUNT);
   if (NULL != pSettlInstrCsdAccountNumWnd)
   {
       if (DSTEdit* pDSTEditSettlInstrCsdAccountNum = dynamic_cast<DSTEdit*>(pSettlInstrCsdAccountNumWnd))
       {
           pDSTEditSettlInstrCsdAccountNum->SetRemoveUnwantedCharsAfterPaste(true);
       }
   }

   CWnd* pCashMsgTypeWnd = GetDlgItem(IDC_EDT_PREF_CASH_MSG_TYPE);
   if (NULL != pCashMsgTypeWnd)
   {
       if (DSTEdit* pDSTEditCashMsgType = dynamic_cast<DSTEdit*>(pCashMsgTypeWnd))
       {
           pDSTEditCashMsgType->SetRemoveUnwantedCharsAfterPaste(true);
       }
   }

   CWnd* pIntermediaryBankWnd = GetDlgItem(IDC_EDT_INTERMEDIARY_BANK);
   if (NULL != pIntermediaryBankWnd)
   {
       if (DSTEdit* pDSTEditIntermediaryBank = dynamic_cast<DSTEdit*>(pIntermediaryBankWnd))
       {
           pDSTEditIntermediaryBank->SetRemoveUnwantedCharsAfterPaste(true);
       }
   }

   CWnd* pReceivingBankWnd = GetDlgItem(IDC_EDT_RECEIVING_BANK);
   if (NULL != pReceivingBankWnd)
   {
       if (DSTEdit* pDSTEditReceivingBank = dynamic_cast<DSTEdit*>(pReceivingBankWnd))
       {
           pDSTEditReceivingBank->SetRemoveUnwantedCharsAfterPaste(true);
       }
   }

   CWnd* pBeneficiaryWnd = GetDlgItem(IDC_EDT_BENFICIARY);
   if (NULL != pBeneficiaryWnd)
   {
       if (DSTEdit* pDSTEditBeneficiary = dynamic_cast<DSTEdit*>(pBeneficiaryWnd))
       {
           pDSTEditBeneficiary->SetRemoveUnwantedCharsAfterPaste(true);
       }
   }

   CWnd* pSpecialInstWnd = GetDlgItem(IDC_EDT_SPECIAL_INST);
   if (NULL != pSpecialInstWnd)
   {
       if (DSTEdit* pDSTEditSpecialInst = dynamic_cast<DSTEdit*>(pSpecialInstWnd))
       {
           pDSTEditSpecialInst->SetRemoveUnwantedCharsAfterPaste(true);
       }
   }

}

//*****************************************************************************
void SettlementInstrDlg::setSettlementInstructionsControls()
{
}

//*********************************************************************
void SettlementInstrDlg::OnBtnAdd()
{
   TRACE_METHOD( CLASSNAME, I_("OnBtnAdd") );
   AddToListControl( IDC_LST_SETTLEMENT_INSTRUCTIONS );
}

//**********************************************************************
void SettlementInstrDlg::OnBtnDel()
{
   TRACE_METHOD( CLASSNAME, I_("OnBtnDel") );
   DeleteFromListControl( IDC_LST_SETTLEMENT_INSTRUCTIONS );
}

//*****************************************************************************
void SettlementInstrDlg::OnBtnReset()
{
   TRACE_METHOD( CLASSNAME, I_("OnBtnReset"));
   ResetListItem( IDC_LST_SETTLEMENT_INSTRUCTIONS );	
}

//*****************************************************************************
void SettlementInstrDlg::OnBtnHistorical() 
{
   TRACE_METHOD( CLASSNAME, I_("OnBtnHistorical") );   
   CWaitCursor wait;   
   IFastHistoricalInfo f;
   f( this, IFASTBP_PROC::FUND_MGMT_SETTLEMENT_INSTR_LIST );
}

//************************************************************************
void SettlementInstrDlg::OnBtnAdmDates() 
{
   ShowAdminDates( IFASTBP_PROC::FUND_MGMT_SETTLEMENT_INSTR_LIST );
}

//*********************************************************************
void SettlementInstrDlg::OnBtnAddSettlInstr()
{
   TRACE_METHOD( CLASSNAME, I_("OnBtnAddSettlInstr") );
   AddToListControl( IDC_LST_SETTL_INSTR );
}

//**********************************************************************
void SettlementInstrDlg::OnBtnDelSettlInstr()
{
   TRACE_METHOD( CLASSNAME, I_("OnBtnDelSettlInstr") );
   DeleteFromListControl( IDC_LST_SETTL_INSTR );
}

//*****************************************************************************
void SettlementInstrDlg::OnBtnResetSettlInstr()
{
   TRACE_METHOD( CLASSNAME, I_("OnBtnResetSettlInstr"));
	ResetListItem( IDC_LST_SETTL_INSTR );
}

//*****************************************************************************
void SettlementInstrDlg::OnBtnHistoricalSettlInstr() 
{
   TRACE_METHOD( CLASSNAME, I_("OnBtnHistoricalSettlInstr") );   
   CWaitCursor wait;   
   IFastHistoricalInfo f;
   f( this, IFASTBP_PROC::SETTLEMENT_INSTRUCTIONS_LIST );
}

//************************************************************************
void SettlementInstrDlg::OnBtnAdmDatesSettlInstr() 
{
   ShowAdminDates( IFASTBP_PROC::SETTLEMENT_INSTRUCTIONS_LIST );
}

//*****************************************************************************
bool SettlementInstrDlg::doRefresh(GenericInterface * rpGICaller, const I_CHAR* szOriginalCommand )
{ 
   TRACE_METHOD( CLASSNAME, DOREFRESH );
   return( true );
}

//**********************************************************************************
bool SettlementInstrDlg::GetOverrideItemString( long lSubstituteId, 
												const DString& dstrColumnKey, 
												DString& dstrOut )
{
	dstrOut = I_( "" );

   if( lSubstituteId == ifds::FundMgmtSettleInstrHeadingSet.getId() )
   {
		
      if( dstrColumnKey == I_("SettleLocationCode" ) )
      {
         getParent()->getField( this, IFASTBP_PROC::FUND_MGMT_SETTLEMENT_INSTR_LIST, ifds::SettleLocationCode, dstrOut, false );
         return( true );
      }
      else if( dstrColumnKey == I_("SettleLocationDesc" ) )
      {
         getParent()->getField( this, IFASTBP_PROC::FUND_MGMT_SETTLEMENT_INSTR_LIST, ifds::SettleLocationCode, dstrOut, true );
         return( true );
      }
		
   }
   return( false );
}

//**********************************************************************************
void SettlementInstrDlg::ControlUpdated( UINT controlID, const DString &strValue )
{  
	if( controlID == IDC_CMB_SETTLEMENT_LOCATION )
   {
		ConnectControlToData( IDC_EDT_ACCOUNT, true );
        ConnectControlToData( IDC_EDT_INT_SETL_ACC, true);
      LoadControl( IDC_EDT_ACCOUNT);
      //GetControl( IDC_STC_SETTLE_ACCOUNT )->Enable( false );
   }
}

//******************************************************************************
void SettlementInstrDlg::DoListItemChanged( UINT listControlID,
											const DString &strKey, 
											bool bIsNewItem, 
											bool bIsDummyItem )
{
	
   if( listControlID == IDC_LST_SETTLEMENT_INSTRUCTIONS )
   {
      // Keep historical button grayed for new and dummy items
      GetDlgItem( IDC_BTN_HISTORICAL )->EnableWindow( !bIsNewItem && !bIsDummyItem );
   }
	if( listControlID == IDC_LST_SETTL_INSTR )
   {
      // Keep historical button grayed for new and dummy items
      GetDlgItem( IDC_BTN_HISTORICAL_SETTLEMENT_INSTRUCTION )->EnableWindow( !bIsNewItem && !bIsDummyItem );
   }
	
}



//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastgui/SettlementInstrDlg.cpp-arc  $
// 
//    Rev 1.8   Nov 07 2007 12:14:50   daechach
// PET 5614 FN 01 - Acct Level Override for Clearing Settle Method
// 
//    Rev 1.7   May 04 2007 13:32:56   jankovii
// PET 2321 FN01 - MT54X Default Pay Type.
// 
//    Rev 1.6   Sep 15 2005 15:15:08   popescu
// Incident#403519 - added CLASSNAME as the fifth parameter to  BaseMainDlg constructor
// 
//    Rev 1.5   Dec 03 2004 17:32:42   vadeanum
// PET1117_FN21:  settlement instructions.
// 
//    Rev 1.4   Nov 30 2004 18:44:46   aguilaam
// PET1117_FN21:  settlement instructions.
// 
//    Rev 1.3   Nov 23 2004 13:58:10   aguilaam
// PET1117_FN21: Settlement Instructions
// 
//    Rev 1.2   Nov 19 2004 17:33:32   aguilaam
// PET117_FN21: settlement instructions enhancement (temporary check-in for build)
// 
//    Rev 1.0.1.1   Nov 14 2004 15:00:48   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.0.1.0   Nov 07 2004 14:56:44   popescu
// PET 1117/06, synch changes
// 
//    Rev 1.0   Oct 13 2004 15:40:20   VADEANUM
// Initial revision.
//
