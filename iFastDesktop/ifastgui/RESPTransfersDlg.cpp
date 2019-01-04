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
// ^FILE   :RESPTransfersDlg.cpp
// ^AUTHOR : 
// ^DATE   : 
//
// ----------------------------------------------------------
//
// ^CLASS    : RESPTransfersDlg
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :  
//
//******************************************************************************

#include "stdafx.h"
#include "mfdstc.h"

#include "RESPTransfersDlg.h"
#include <configmanager.hpp>
#include <uibase\DSTEdit.h>
#include <uibase\ifdslistctrl.h>
#include <uibase\dsttabctrl.h>

#include <ifastbp\mfcaninterprocparam.hpp>
#include <ifastbp\RESPTransfersProcessincludes.h>
#include <ifastbp\RESPTransfersProcess.hpp>
#include <ifastbp\respinfoprocessincludes.h>
#include <configmanager.hpp>
#include <ifastcsi\csisession.h>
#include <ifastcsi\ifastcsi.h>
#include <uibase\dstgridwnd.h>
#include <uibase\dstlistctrl.h>
#include <ifastcbo\dstcommonfunction.hpp>
#include <ifastbp\mfcaninterprocparam.hpp>
#include <ifastcbo\MFAccount.hpp>
#include <ifastcbo\Entity.hpp>
#include <uibase\dstedit.h>
#include <ifastcbo\dstcworksession.hpp>
#include <assert.h>
#include <ifastgui\ifasthistoricalinfo.hpp>

#ifndef INCLUDED_ASSERT_H
#define INCLUDED_ASSERT_H
#include <assert.h>
#endif

extern CLASS_IMPORT const I_CHAR* CMD_GUI_RESP_TRANSFER;
#include <bfproc\concretedialogcreator.hpp>
static ConcreteDialogCreator< RESPTransfersDlg > dlgCreator( CMD_GUI_RESP_TRANSFER ); 

#ifdef _DEBUG
   #define new DEBUG_NEW
   #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

namespace
{
   const I_CHAR * const CLASSNAME      = I_("RESPTransfersDlg");
   const I_CHAR *LV_BENEFICIARIES      = I_( "TransferBeneficiaryAllocations" );
   const I_CHAR * PROC_TRADE           = I_( "Proc" ); 
   const I_CHAR * const TRANSFER_LIKE  = I_( "TR,AFTR" );
   const I_CHAR * const YES            = I_( "Y" );
   const I_CHAR * const NO             = I_( "N" );
}

namespace TRANSFER_TAB_CONTROLS
{
   const int FEDERAL    = 1;
   const int QESI		= 2;
}
  
namespace UAF
{
   extern CLASS_IMPORT I_CHAR * const RESP_TRANSFER;
   extern CLASS_IMPORT I_CHAR * const RESP_BENEFICIARY_ALLOCATION;
}

namespace ifds
{   
   extern CLASS_IMPORT const BFNumericFieldId HistNonTrustYear;
   extern CLASS_IMPORT const BFTextFieldId TotTransfINDC;
   extern CLASS_IMPORT const BFDateFieldId TradeDate;
   extern CLASS_IMPORT const BFTextFieldId IsNotionalTaxYearApplicable;
   extern CLASS_IMPORT const BFTextFieldId IsTotTransfINDCApplicable;
   extern CLASS_IMPORT const BFTextFieldId IsInNonTrusteeTxfrPeriod;
   extern CLASS_IMPORT const BFTextFieldId AnyBenefCurrTradeYear;
   extern CLASS_IMPORT const BFDecimalFieldId QESIPaid;
}

//*****************************************************************************
// Public methods
//*****************************************************************************
RESPTransfersDlg::RESPTransfersDlg( CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: BaseMainDlg( RESPTransfersDlg::IDD, pParent, pGIC, pGIParent, rCommand, CLASSNAME ),
m_bDialogInit (false),
m_DecimalDigits (0),
m_TransType (NULL_STRING),
m_bRespTransferListSelectionInProgress (false)
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   //{{AFX_DATA_INIT(RESPTransfersDlg)
   //}}AFX_DATA_INIT
}

//*****************************************************************************
void RESPTransfersDlg::DoDataExchange( CDataExchange* pDX )
{
   BaseMainDlg::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(RESPTransfersDlg)
   //}}AFX_DATA_MAP
}

//*****************************************************************************
BEGIN_MESSAGE_MAP(RESPTransfersDlg, BaseMainDlg)
//{{AFX_MSG_MAP(RESPTransfersDlg)
ON_BN_CLICKED(IDC_BTN_BEN_ADD, OnBtnAdd)
ON_BN_CLICKED(IDC_BTN_BEN_DELETE, OnBtnDelete)
ON_BN_CLICKED(IDC_CHK_LINK, OnAcctLevelOverride)
ON_BN_CLICKED(IDC_BTN_MORE, OnBtnMore)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//*****************************************************************************
// Message handlers
class LVRESPTransferData : public IFDSListCtrlRowDataBase
{
public:
   virtual ~LVRESPTransferData() {}
   DString BenefIdFrom_;
   DString RecordLevel_;
   DString BenefEffectiveDate_;
   DString Relationship_;
   DString TaxJuris_;
   DString RESPAllocPrcnt_;
   DString BenefDofB_;
   DString GrantRequest_;
   DString Tainted_;
   DString TaintEndDate_;
   DString HistNonTrustYear_;
   DString EffectiveDate_;

   virtual void update(BaseDlg* pDlg, IFDSListCtrl* pCtrl, const DString* pKey)
   {
      pDlg->getParent()->getField(pDlg, BF::NullContainerId, 
         ifds::RESPBenefIDFrom, BenefIdFrom_);
      BenefIdFrom_.strip();

      pDlg->getParent()->getField(pDlg, BF::NullContainerId, 
         ifds::RecordLevel, RecordLevel_);
      RecordLevel_.strip();

      pDlg->getParent()->getField(pDlg, BF::NullContainerId, 
         ifds::BenefEffectiveDate, BenefEffectiveDate_);
      BenefEffectiveDate_.strip();

      pDlg->getParent()->getField(pDlg, BF::NullContainerId, 
         ifds::Relation, Relationship_);
      Relationship_.strip();

      pDlg->getParent()->getField(pDlg, BF::NullContainerId, 
         ifds::TaxJuris, TaxJuris_);
      TaxJuris_.strip();

      pDlg->getParent()->getField(pDlg, BF::NullContainerId, 
         ifds::RESPAllocPrcnt, RESPAllocPrcnt_);
      RESPAllocPrcnt_.strip();

      pDlg->getParent()->getField(pDlg, BF::NullContainerId, 
         ifds::BenefDofB, BenefDofB_);
      BenefDofB_.strip();

      pDlg->getParent()->getField(pDlg, BF::NullContainerId, 
         ifds::GrantRequest, GrantRequest_);
      GrantRequest_.strip();

      pDlg->getParent()->getField(pDlg, BF::NullContainerId, 
         ifds::Tainted, Tainted_);
      Tainted_.strip();

      pDlg->getParent()->getField(pDlg, BF::NullContainerId, 
         ifds::TaintEndDate, TaintEndDate_);
      TaintEndDate_.strip();

      pDlg->getParent()->getField(pDlg, BF::NullContainerId, 
         ifds::HistNonTrustYear, HistNonTrustYear_);
      HistNonTrustYear_.strip();
   }
};

class LVESPTransferAdapter : public IFDSListCtrlAdapter< LVRESPTransferData >
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
      else if (*pFieldId == ifds::RESPBenefIDFrom) 
      {
         result = i_strcmp(pData1->BenefIdFrom_.c_str(), pData2->BenefIdFrom_.c_str());
      } 
      else if (*pFieldId == ifds::RecordLevel) 
      {
         result = i_strcmp(pData1->RecordLevel_.c_str(), pData2->RecordLevel_.c_str());
      } 
      else if (*pFieldId == ifds::BenefEffectiveDate) 
      {
         result = i_strcmp(pData1->BenefEffectiveDate_.c_str(), pData2->BenefEffectiveDate_.c_str());
      } 
      else if (*pFieldId == ifds::Relation) 
      {
         result = i_strcmp(pData1->Relationship_.c_str(), pData2->Relationship_.c_str());
      } 
      else if (*pFieldId == ifds::TaxJuris) 
      {
         result = i_strcmp(pData1->TaxJuris_.c_str(), pData2->TaxJuris_.c_str());
      } 
      else if (*pFieldId == ifds::RESPAllocPrcnt) 
      {
         result = i_strcmp(pData1->RESPAllocPrcnt_.c_str(), pData2->RESPAllocPrcnt_.c_str());
      } 
      else if (*pFieldId == ifds::BenefDofB) 
      {
         result = i_strcmp(pData1->BenefDofB_.c_str(), pData2->BenefDofB_.c_str());
      }
      else if (*pFieldId == ifds::GrantRequest) 
      {
         result = i_strcmp(pData1->GrantRequest_.c_str(), pData2->GrantRequest_.c_str());
      }
      else if (*pFieldId == ifds::Tainted) 
      {
         result = i_strcmp(pData1->Tainted_.c_str(), pData2->Tainted_.c_str());
      }
      else if (*pFieldId == ifds::TaintEndDate) 
      {
         result = i_strcmp(pData1->TaintEndDate_.c_str(), pData2->TaintEndDate_.c_str());
      }
      else if (*pFieldId == ifds::HistNonTrustYear) 
      {
         result = i_strcmp(pData1->HistNonTrustYear_.c_str(), pData2->HistNonTrustYear_.c_str());
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
         else if (*pFieldId == ifds::RESPBenefIDFrom) 
         {
            pDispInfo->item.pszText = (I_CHAR*)pData->BenefIdFrom_.c_str();
         } 
         else if (*pFieldId == ifds::RecordLevel) 
         {
            pDispInfo->item.pszText = (I_CHAR*)pData->RecordLevel_.c_str();
         } 
         else if (*pFieldId == ifds::BenefEffectiveDate) 
         {
            pDispInfo->item.pszText = (I_CHAR*)pData->BenefEffectiveDate_.c_str();
         } 
         else if (*pFieldId == ifds::Relation)
         {
            pDispInfo->item.pszText = (I_CHAR*)pData->Relationship_.c_str();
         } 
         else if (*pFieldId == ifds::TaxJuris)
         {
            pDispInfo->item.pszText = (I_CHAR*)pData->TaxJuris_.c_str();
         } 
         else if (*pFieldId == ifds::RESPAllocPrcnt)
         {
            pDispInfo->item.pszText = (I_CHAR*)pData->RESPAllocPrcnt_.c_str();
         } 
         else if (*pFieldId == ifds::BenefDofB)
         {
            pDispInfo->item.pszText = (I_CHAR*)pData->BenefDofB_.c_str();
         } 
         else if (*pFieldId == ifds::GrantRequest)
         {
            pDispInfo->item.pszText = (I_CHAR*)pData->GrantRequest_.c_str();
         } 
         else if (*pFieldId == ifds::Tainted)
         {
            pDispInfo->item.pszText = (I_CHAR*)pData->Tainted_.c_str();
         } 
         else if (*pFieldId == ifds::TaintEndDate)
         {
            pDispInfo->item.pszText = (I_CHAR*)pData->TaintEndDate_.c_str();
         } 
         else if (*pFieldId == ifds::HistNonTrustYear)
         {
            pDispInfo->item.pszText = (I_CHAR*)pData->HistNonTrustYear_.c_str();
         } 

         return (1);
      }
      return (0);
   }
};

//*****************************************************************************
BOOL RESPTransfersDlg::OnInitDialog() 
{
   TRACE_METHOD( CLASSNAME, ONINITDIALOG );
   BaseMainDlg::OnInitDialog(); 

   IFDSListCtrl* pBenefAllocListCtrl =  new IFDSAdaptedListCtrl< LVESPTransferAdapter >(this, CLASSNAME, IDC_LV_ACCT_BENEF, 0, 0, true, true);

   AddIFDSListControl (pBenefAllocListCtrl, LV_BENEFICIARIES, IFASTBP_PROC::RESP_TRANSFER_LIST, ifds::RESPTransferHeading);

   return TRUE;
}

//******************************************************************************
void RESPTransfersDlg::OnPostInitDialog()
{
   TRACE_METHOD( CLASSNAME, ONPOSTINITDIALOG );

   if (m_dstrCaller != I_("TradeEntry"))
   {
      SetUserAccesFunctionCode (UAF::RESP_TRANSFER);
      addControlGroupIDForPermissionCheck (IDC_LV_ACCT_BENEF);   
   }

   addControls ();
   registerControlsToTab ();
   displayQESITotTxfr();

   displayDynamicLabels ();

   setAllowedChars ();

   ShowTabCtrl (IDC_TAB_TR, true);
   LoadTabControl (IDC_TAB_TR);

   initAccLevelOverride ();

   if (m_dstrCaller == I_("RESPTransactionsDlg") && m_HistoryPending == RESPINFONAMES::PENDING)
   {
      GetDlgItem (IDC_CHK_LINK)->EnableWindow (false);
      GetDlgItem (IDOK)->EnableWindow (false);
   }

   enableNEQs ();

   doRefresh (this, NULL_STRING);

   m_bDialogInit = false;
}

//*****************************************************************************
void RESPTransfersDlg::OnBtnAdd () 
{
   TRACE_METHOD( CLASSNAME, I_("OnBtnAdd") );   

   AddToListControl (IDC_LV_ACCT_BENEF);
}

//*****************************************************************************
void RESPTransfersDlg::OnBtnDelete () 
{
   TRACE_METHOD( CLASSNAME, I_("OnBtnDelete") ); 

   DeleteFromListControl (IDC_LV_ACCT_BENEF);
}

//******************************************************************************
void RESPTransfersDlg::OnAcctLevelOverride()
{
   CWaitCursor wait;

   if (((CButton *) GetDlgItem (IDC_CHK_LINK))->GetCheck() != 1)
   {
      getParent()->setField (this, IFASTBP_PROC::RESP_TRANSFER_LIST, ifds::AcctLvlOverride, I_("N"), false);
   }
   else
   {
      getParent()->setField (this, IFASTBP_PROC::RESP_TRANSFER_LIST, ifds::AcctLvlOverride, I_("Y"), false);  
   }
}

//*****************************************************************************
void RESPTransfersDlg::setAllowedChars ()
{
   DSTEdit *edit = NULL;

   edit = dynamic_cast<DSTEdit *>( GetControl (IDC_EDT_TR_PERCENT));
   edit->SetAllowedChars(I_("0123456789."));
   edit->setInputAllowedUnsignedDecimal();

   edit = dynamic_cast<DSTEdit *>( GetControl (IDC_EDT_ANNUAL_CONTRIB));
   edit->SetAllowedChars(I_("0123456789."));
   edit->setInputAllowedUnsignedDecimal();

   edit = dynamic_cast<DSTEdit *>( GetControl (IDC_EDT_PRE98_CONTRIB));
   edit->SetAllowedChars(I_("0123456789."));
   edit->setInputAllowedUnsignedDecimal();

   edit = dynamic_cast<DSTEdit *>( GetControl (IDC_EDT_CESG));
   edit->SetAllowedChars(I_("0123456789."));
   edit->setInputAllowedUnsignedDecimal();

   edit = dynamic_cast<DSTEdit *>( GetControl (IDC_EDT_ADDITIONAL_CESG));
   edit->SetAllowedChars(I_("0123456789."));
   edit->setInputAllowedUnsignedDecimal();

   edit = dynamic_cast<DSTEdit *>( GetControl (IDC_EDT_CLB));
   edit->SetAllowedChars(I_("0123456789."));
   edit->setInputAllowedUnsignedDecimal();

   edit = dynamic_cast<DSTEdit *>( GetControl (IDC_EDT_ACES));
   edit->SetAllowedChars(I_("0123456789."));
   edit->setInputAllowedUnsignedDecimal();

   edit = dynamic_cast<DSTEdit *>( GetControl (IDC_EDT_FEDERAL_UNASSISTED_AMT));
   edit->setInputAllowedDecimal();

   edit = dynamic_cast<DSTEdit *>( GetControl (IDC_EDT_CONTRIB_REDEM));
   edit->SetAllowedChars(I_("0123456789."));
   edit->setInputAllowedUnsignedDecimal();

   edit = dynamic_cast<DSTEdit *>( GetControl (IDC_EDT_EARN_REDEM));
   edit->SetAllowedChars(I_("0123456789."));
   edit->setInputAllowedUnsignedDecimal();

   edit = dynamic_cast<DSTEdit *>( GetControl (IDC_EDT_PRE98_REDEM));
   edit->SetAllowedChars(I_("0123456789."));
   edit->setInputAllowedUnsignedDecimal();

   edit = dynamic_cast<DSTEdit *>( GetControl (IDC_EDT_CESG_REDEM));
   edit->SetAllowedChars(I_("0123456789."));
   edit->setInputAllowedUnsignedDecimal();

   edit = dynamic_cast<DSTEdit *>( GetControl (IDC_EDT_CLB_REDEM));
   edit->SetAllowedChars(I_("0123456789."));
   edit->setInputAllowedUnsignedDecimal();

   edit = dynamic_cast<DSTEdit *>( GetControl (IDC_EDT_ACES_REDEM));
   edit->SetAllowedChars(I_("0123456789."));
   edit->setInputAllowedUnsignedDecimal();

   edit = dynamic_cast<DSTEdit *>( GetControl (IDC_EDT_LIFE_CONTRIB));
   edit->SetAllowedChars(I_("0123456789."));
   edit->setInputAllowedUnsignedDecimal();

   edit = dynamic_cast<DSTEdit *>( GetControl (IDC_EDT_FEDERAL_ASSISTED_AMT));
   edit->setInputAllowedDecimal();
   
   //P0185010.FN02.R01.02 - new field CESG Grant paid
   edit = dynamic_cast<DSTEdit *>( GetControl (IDC_EDT_CESG_PAID));
   edit->SetAllowedChars(I_("0123456789."));
   edit->setInputAllowedUnsignedDecimal();

   bool bIsQESIClient = dynamic_cast<DSTCWorkSession *>(getBFWorkSession())->isQESIClient();

   if (bIsQESIClient)
   {
      edit = dynamic_cast<DSTEdit *>( GetControl (IDC_EDT_QESI_BASIC));
      edit->SetAllowedChars(I_("0123456789."));
      edit->setInputAllowedUnsignedDecimal();

      edit = dynamic_cast<DSTEdit *>( GetControl (IDC_EDT_QESI_INCREASE));
      edit->SetAllowedChars(I_("0123456789."));
      edit->setInputAllowedUnsignedDecimal();

      edit = dynamic_cast<DSTEdit *>( GetControl (IDC_EDT_PRE_2007_QESI));
      edit->SetAllowedChars(I_("0123456789."));
      edit->setInputAllowedUnsignedDecimal();

      edit = dynamic_cast<DSTEdit *>( GetControl (IDC_EDT_QESI_UNASSSITED_AMT));
      edit->setInputAllowedDecimal();

      edit = dynamic_cast<DSTEdit *>( GetControl (IDC_EDT_QESI_YTD));
      edit->SetAllowedChars(I_("0123456789."));
      edit->setInputAllowedUnsignedDecimal();

      edit = dynamic_cast<DSTEdit *>( GetControl (IDC_EDT_QESI_ASSISTED));
      edit->setInputAllowedDecimal();

      edit = dynamic_cast<DSTEdit *>( GetControl (IDC_EDT_QESI_PRE98));
      edit->SetAllowedChars(I_("0123456789."));
      edit->setInputAllowedUnsignedDecimal();
   }

   bool bIsSAGESClient = dynamic_cast<DSTCWorkSession *>(getBFWorkSession())->isSAGESClient();

   if (bIsSAGESClient)
   {
	   DString dstrSAGESMask;
	   int iDecimalPointPos;

	   edit = dynamic_cast<DSTEdit *>( GetControl (IDC_EDT_SAGES_GRANT));
	   edit->SetAllowedChars(I_("-0123456789."));
	   edit->setInputAllowedUnsignedDecimal();

	   dstrSAGESMask = DSTCommonFunctions::getMask( ifds::SAGESGrant );
	   iDecimalPointPos = dstrSAGESMask.find (I_("."));	
	   edit->setMaxNumDigitsBeforeDecimalPoint( iDecimalPointPos - 1 );
	   edit->setMaxNumDigitsAfterDecimalPoint( dstrSAGESMask.length() - iDecimalPointPos - 2 );	

	   edit = dynamic_cast<DSTEdit *>( GetControl (IDC_EDT_SAGES_UC_AMOUNT));
	   edit->SetAllowedChars(I_("-0123456789."));
	   edit->setInputAllowedUnsignedDecimal();

	   dstrSAGESMask = DSTCommonFunctions::getMask( ifds::SAGESUCAmount );
	   iDecimalPointPos = dstrSAGESMask.find (I_("."));	
	   edit->setMaxNumDigitsBeforeDecimalPoint( iDecimalPointPos -1 );
	   edit->setMaxNumDigitsAfterDecimalPoint( dstrSAGESMask.length() - iDecimalPointPos - 2 );

	   edit = dynamic_cast<DSTEdit *>( GetControl (IDC_EDT_SAGES_AC_AMOUNT));
	   edit->SetAllowedChars(I_("-0123456789."));
	   edit->setInputAllowedUnsignedDecimal();

	   dstrSAGESMask = DSTCommonFunctions::getMask( ifds::SAGESACAmount );
	   iDecimalPointPos = dstrSAGESMask.find (I_("."));	
	   edit->setMaxNumDigitsBeforeDecimalPoint( iDecimalPointPos - 1 );
	   edit->setMaxNumDigitsAfterDecimalPoint( dstrSAGESMask.length() - iDecimalPointPos - 2 );	   
   }

}
//*****************************************************************************
void RESPTransfersDlg::addControls ()
{
   // plan info
   AddControl (CTRL_EDIT, IDC_EDT_FROM_PLAN,				   IFASTBP_PROC::RESP_TRANSFER_LIST, ifds::FromPlanNum, 0, IDC_LV_ACCT_BENEF);
   AddControl (CTRL_EDIT, IDC_EDT_TO_PLAN,					IFASTBP_PROC::RESP_TRANSFER_LIST, ifds::ToPlanNum, 0, IDC_LV_ACCT_BENEF);
   AddControl (CTRL_DATE, IDC_DTP_INCEPTION_DATE,			IFASTBP_PROC::RESP_TRANSFER_LIST, ifds::InceptionDate, 0, IDC_LV_ACCT_BENEF);
   AddControl (CTRL_COMBO, IDC_CMB_FROM_NEQ,				   IFASTBP_PROC::RESP_TRANSFER_LIST, ifds::NEQ1, CTRLFLAG_INITCOMBO_BY_SUB_LIST, IDC_LV_ACCT_BENEF);
   AddControl (CTRL_COMBO, IDC_CMB_TO_NEQ,					IFASTBP_PROC::RESP_TRANSFER_LIST, ifds::NEQ2, CTRLFLAG_INITCOMBO_BY_SUB_LIST, IDC_LV_ACCT_BENEF);
   AddControl (CTRL_EDIT, IDC_EDT_FROM_CONTRACT_ID,		IFASTBP_PROC::RESP_TRANSFER_LIST, ifds::FromContractId, 0, IDC_LV_ACCT_BENEF);
   AddControl (CTRL_EDIT, IDC_EDT_TO_CONTRACT_ID,			IFASTBP_PROC::RESP_TRANSFER_LIST, ifds::ToContractId, 0, IDC_LV_ACCT_BENEF);
   AddControl (CTRL_DATE, IDC_DTP_PLAN_TERMINATION_DATE,	IFASTBP_PROC::RESP_TRANSFER_LIST, ifds::TerminationDate, 0, IDC_LV_ACCT_BENEF);

   // benef info
   AddControl (CTRL_COMBO, IDC_CMB_BEN_NAME,				   IFASTBP_PROC::RESP_TRANSFER_LIST, ifds::RESPBenefIDFrom, CTRLFLAG_INITCOMBO_BY_SUB_LIST, IDC_LV_ACCT_BENEF);
   AddControl (CTRL_COMBO, IDC_CMB_TO_BENEF,				   IFASTBP_PROC::RESP_TRANSFER_LIST, ifds::RESPBenefIDTo, CTRLFLAG_INITCOMBO_BY_SUB_LIST, IDC_LV_ACCT_BENEF);

   // percent & account level override
   AddControl (CTRL_EDIT, IDC_EDT_TR_PERCENT,				IFASTBP_PROC::RESP_TRANSFER_LIST, ifds::TransferPercent, 0, IDC_LV_ACCT_BENEF);
   AddControl( CTRL_CHECKBOX, IDC_CHK_LINK,					IFASTBP_PROC::RESP_TRANSFER_LIST, ifds::AcctLvlOverride, CTRLFLAG_DEFAULT);

   AddControl (CTRL_COMBO, IDC_CMB_ELIGIBLE_TRANSFER,    IFASTBP_PROC::RESP_TRANSFER_LIST, ifds::EligibleTransfer, CTRLFLAG_INITCOMBO_BY_SUB_LIST, IDC_LV_ACCT_BENEF);

   // letter & status
   AddControl (CTRL_COMBO, IDC_CMB_RESP_LETTER,			   IFASTBP_PROC::RESP_TRANSFER_LIST, ifds::RESPLetter, CTRLFLAG_INITCOMBO_BY_SUB_LIST, IDC_LV_ACCT_BENEF);
   AddControl (CTRL_COMBO, IDC_CMB_INFO_COMPLETED,			IFASTBP_PROC::RESP_TRANSFER_LIST, ifds::RESPTransStat, CTRLFLAG_INITCOMBO_BY_SUB_LIST, IDC_LV_ACCT_BENEF);
   AddControl (CTRL_COMBO, IDC_CMB_RES_CESG,			    IFASTBP_PROC::RESP_TRANSFER_LIST, ifds::IsResidualCESG, CTRLFLAG_INITCOMBO_BY_SUB_LIST, IDC_LV_ACCT_BENEF);

   // static controls
   AddControl (CTRL_STATIC, IDC_STC_ANNUAL_CONTRIB,	CTRLFLAG_GUI_FIELD,	TRANSFER_TAB_CONTROLS::FEDERAL);
   AddControl (CTRL_STATIC, IDC_STC_LIFE_CONTRIB,		CTRLFLAG_GUI_FIELD, TRANSFER_TAB_CONTROLS::FEDERAL);
   AddControl (CTRL_STATIC, IDC_STC_PRE98_CONTRIB,		CTRLFLAG_GUI_FIELD, TRANSFER_TAB_CONTROLS::FEDERAL);
   AddControl (CTRL_STATIC, IDC_STC_CESG_GRANT,		   CTRLFLAG_GUI_FIELD, TRANSFER_TAB_CONTROLS::FEDERAL);
   AddControl (CTRL_STATIC, IDC_STC_ADD_CESG_GRANT,	CTRLFLAG_GUI_FIELD, TRANSFER_TAB_CONTROLS::FEDERAL);
   AddControl (CTRL_STATIC, IDC_STC_CLB_AMT,			   CTRLFLAG_GUI_FIELD, TRANSFER_TAB_CONTROLS::FEDERAL);
   AddControl (CTRL_STATIC, IDC_STC_ACES,				   CTRLFLAG_GUI_FIELD, TRANSFER_TAB_CONTROLS::FEDERAL);
   AddControl (CTRL_STATIC, IDC_STC_FEDERAL_UNASSISTED,CTRLFLAG_GUI_FIELD, TRANSFER_TAB_CONTROLS::FEDERAL);
   AddControl (CTRL_STATIC, IDC_STC_REDEM_CONTRIB,		CTRLFLAG_GUI_FIELD, TRANSFER_TAB_CONTROLS::FEDERAL);
   AddControl (CTRL_STATIC, IDC_STC_REDEM_EARN,		   CTRLFLAG_GUI_FIELD, TRANSFER_TAB_CONTROLS::FEDERAL);
   AddControl (CTRL_STATIC, IDC_STC_PRE98_REDEM,		CTRLFLAG_GUI_FIELD, TRANSFER_TAB_CONTROLS::FEDERAL);
   AddControl (CTRL_STATIC, IDC_STC_CESG_REDEM,		   CTRLFLAG_GUI_FIELD, TRANSFER_TAB_CONTROLS::FEDERAL);
   AddControl (CTRL_STATIC, IDC_STC_CLB_REDEM,			CTRLFLAG_GUI_FIELD, TRANSFER_TAB_CONTROLS::FEDERAL);
   AddControl (CTRL_STATIC, IDC_STC_ACES_REDEM,		   CTRLFLAG_GUI_FIELD, TRANSFER_TAB_CONTROLS::FEDERAL);
   AddControl (CTRL_STATIC, IDC_STC_FEDERAL_ASSISTED,  CTRLFLAG_GUI_FIELD, TRANSFER_TAB_CONTROLS::FEDERAL);
   //P0185010.FN02.R01.02 - new field CESG Grant paid
   AddControl (CTRL_STATIC, IDC_STC_CESG_PAID,	CTRLFLAG_GUI_FIELD, TRANSFER_TAB_CONTROLS::FEDERAL);

   AddControl (CTRL_STATIC, IDC_STC_QESI_BASIC,                CTRLFLAG_GUI_FIELD, TRANSFER_TAB_CONTROLS::QESI);
   AddControl (CTRL_STATIC, IDC_STC_QESI_INCREASE,             CTRLFLAG_GUI_FIELD, TRANSFER_TAB_CONTROLS::QESI);
   AddControl (CTRL_STATIC, IDC_STC_PRE_FEB2007,               CTRLFLAG_GUI_FIELD, TRANSFER_TAB_CONTROLS::QESI);
   AddControl (CTRL_STATIC, IDC_STC_QESI_UNASSISTED,           CTRLFLAG_GUI_FIELD, TRANSFER_TAB_CONTROLS::QESI);
   AddControl (CTRL_STATIC, IDC_STC_QESI_YTD,                  CTRLFLAG_GUI_FIELD, TRANSFER_TAB_CONTROLS::QESI);
   AddControl (CTRL_STATIC, IDC_STC_QESI_ASSISTED,             CTRLFLAG_GUI_FIELD, TRANSFER_TAB_CONTROLS::QESI);
   AddControl (CTRL_STATIC, IDC_STC_QESI_PRE98,                CTRLFLAG_GUI_FIELD, TRANSFER_TAB_CONTROLS::QESI);
   AddControl (CTRL_STATIC, IDC_STC_QESI_PAID_BY_OTHER_INST ,  CTRLFLAG_GUI_FIELD, TRANSFER_TAB_CONTROLS::QESI);

   // federal controls
   AddControl(CTRL_EDIT, IDC_EDT_ANNUAL_CONTRIB,		IFASTBP_PROC::RESP_TRANSFER_LIST, ifds::YTDContr, 0, IDC_LV_ACCT_BENEF);
   AddControl(CTRL_EDIT, IDC_EDT_PRE98_CONTRIB,			IFASTBP_PROC::RESP_TRANSFER_LIST, ifds::Pre98ContribAmt, 0, IDC_LV_ACCT_BENEF);
   AddControl(CTRL_EDIT, IDC_EDT_CESG,						IFASTBP_PROC::RESP_TRANSFER_LIST, ifds::GrantAmount, 0, IDC_LV_ACCT_BENEF);
   AddControl(CTRL_EDIT, IDC_EDT_ADDITIONAL_CESG,		IFASTBP_PROC::RESP_TRANSFER_LIST, ifds::AdditionalGrant, 0, IDC_LV_ACCT_BENEF);
   AddControl(CTRL_EDIT, IDC_EDT_CLB,						IFASTBP_PROC::RESP_TRANSFER_LIST, ifds::CLBAmount, 0, IDC_LV_ACCT_BENEF);
   AddControl(CTRL_EDIT, IDC_EDT_ACES,						IFASTBP_PROC::RESP_TRANSFER_LIST, ifds::PGrantAmount, 0, IDC_LV_ACCT_BENEF);
   AddControl(CTRL_EDIT, IDC_EDT_FEDERAL_UNASSISTED_AMT,	IFASTBP_PROC::RESP_TRANSFER_LIST, ifds::UCAmt, 0, IDC_LV_ACCT_BENEF);
   AddControl(CTRL_EDIT, IDC_EDT_CONTRIB_REDEM,			IFASTBP_PROC::RESP_TRANSFER_LIST, ifds::TDRedContrib, 0, IDC_LV_ACCT_BENEF);
   AddControl(CTRL_EDIT, IDC_EDT_EARN_REDEM,				IFASTBP_PROC::RESP_TRANSFER_LIST, ifds::TDRedEarning, 0, IDC_LV_ACCT_BENEF);
   AddControl(CTRL_EDIT, IDC_EDT_PRE98_REDEM,			IFASTBP_PROC::RESP_TRANSFER_LIST, ifds::Pre98RedContribAmt, 0, IDC_LV_ACCT_BENEF);
   AddControl(CTRL_EDIT, IDC_EDT_CESG_REDEM,				IFASTBP_PROC::RESP_TRANSFER_LIST, ifds::RedCESG, 0, IDC_LV_ACCT_BENEF);
   AddControl(CTRL_EDIT, IDC_EDT_CLB_REDEM,				IFASTBP_PROC::RESP_TRANSFER_LIST, ifds::RedCLB, 0, IDC_LV_ACCT_BENEF);
   AddControl(CTRL_EDIT, IDC_EDT_ACES_REDEM,				IFASTBP_PROC::RESP_TRANSFER_LIST, ifds::RedPGrant, 0, IDC_LV_ACCT_BENEF);
   AddControl(CTRL_EDIT, IDC_EDT_LIFE_CONTRIB,			IFASTBP_PROC::RESP_TRANSFER_LIST, ifds::TDContr, 0, IDC_LV_ACCT_BENEF);
   AddControl(CTRL_EDIT, IDC_EDT_FEDERAL_ASSISTED_AMT,IFASTBP_PROC::RESP_TRANSFER_LIST, ifds::ACAmt, 0, IDC_LV_ACCT_BENEF);
   //P0185010.FN02.R01.02 - new field CESG Grant paid
   AddControl(CTRL_EDIT, IDC_EDT_CESG_PAID ,		IFASTBP_PROC::RESP_TRANSFER_LIST, ifds::CESGPaid, 0, IDC_LV_ACCT_BENEF);

   bool bIsQESIClient = dynamic_cast<DSTCWorkSession *>(getBFWorkSession())->isQESIClient();

   if (bIsQESIClient)
   {
      // qesi controls
      AddControl (CTRL_EDIT, IDC_EDT_QESI_BASIC,			      IFASTBP_PROC::RESP_TRANSFER_LIST, ifds::QESIBasicGrant, 0, IDC_LV_ACCT_BENEF);
      AddControl (CTRL_EDIT, IDC_EDT_QESI_INCREASE,		      IFASTBP_PROC::RESP_TRANSFER_LIST, ifds::QESIIncreaseAmt, 0, IDC_LV_ACCT_BENEF);
      AddControl (CTRL_EDIT, IDC_EDT_PRE_2007_QESI,		      IFASTBP_PROC::RESP_TRANSFER_LIST, ifds::Pre2007QESIContrib, 0, IDC_LV_ACCT_BENEF);
      AddControl (CTRL_EDIT, IDC_EDT_QESI_UNASSSITED_AMT,	   IFASTBP_PROC::RESP_TRANSFER_LIST, ifds::QESIUCAmount, 0, IDC_LV_ACCT_BENEF);
      AddControl (CTRL_EDIT, IDC_EDT_QESI_YTD,				      IFASTBP_PROC::RESP_TRANSFER_LIST, ifds::QESIYTDContribution, 0, IDC_LV_ACCT_BENEF);
      AddControl (CTRL_EDIT, IDC_EDT_QESI_ASSISTED,		      IFASTBP_PROC::RESP_TRANSFER_LIST, ifds::QESIACAmount, 0, IDC_LV_ACCT_BENEF);
      AddControl (CTRL_EDIT, IDC_EDT_QESI_PRE98,			      IFASTBP_PROC::RESP_TRANSFER_LIST, ifds::Pre98QESIContrib, 0, IDC_LV_ACCT_BENEF);
      AddControl (CTRL_STATIC, IDC_STC_RESP_NOTIONAL_YEAR,	CTRLFLAG_GUI_FIELD, TRANSFER_TAB_CONTROLS::QESI);
      AddControl (CTRL_COMBO, IDC_CMB_RESP_NOTIONAL_YEAR,	   IFASTBP_PROC::RESP_TRANSFER_LIST, ifds::HistNonTrustYear, CTRLFLAG_INITCOMBO_BY_SUB_LIST, IDC_LV_ACCT_BENEF);
      AddControl (CTRL_STATIC, IDC_STC_QESI_TOTAL_TRFX,	CTRLFLAG_GUI_FIELD, TRANSFER_TAB_CONTROLS::QESI);
      AddControl (CTRL_COMBO, IDC_CMB_QESI_TOTAL_TRFX ,	      IFASTBP_PROC::RESP_TRANSFER_LIST, ifds::TotTransfINDC, CTRLFLAG_INITCOMBO_BY_SUB_LIST, IDC_LV_ACCT_BENEF);
      AddControl (CTRL_EDIT, IDC_EDT_QESI_PAID_BY_OTHER_INST,  IFASTBP_PROC::RESP_TRANSFER_LIST, ifds::QESIPaid, 0, IDC_LV_ACCT_BENEF);
   }

   // SAGES
   AddControl (CTRL_STATIC, IDC_STC_SAGES_GRANT,	  CTRLFLAG_GUI_FIELD, TRANSFER_TAB_CONTROLS::FEDERAL);
   AddControl (CTRL_STATIC, IDC_STC_SAGES_AC_AMOUNT,  CTRLFLAG_GUI_FIELD, TRANSFER_TAB_CONTROLS::FEDERAL);
   AddControl (CTRL_STATIC, IDC_STC_SAGES_UC_AMOUNT,  CTRLFLAG_GUI_FIELD, TRANSFER_TAB_CONTROLS::FEDERAL);
   AddControl (CTRL_EDIT,	IDC_EDT_SAGES_GRANT,	  IFASTBP_PROC::RESP_TRANSFER_LIST, ifds::SAGESGrant, 0, IDC_LV_ACCT_BENEF);
   AddControl (CTRL_EDIT,	IDC_EDT_SAGES_UC_AMOUNT,  IFASTBP_PROC::RESP_TRANSFER_LIST, ifds::SAGESUCAmount, 0, IDC_LV_ACCT_BENEF);
   AddControl (CTRL_EDIT,	IDC_EDT_SAGES_AC_AMOUNT,  IFASTBP_PROC::RESP_TRANSFER_LIST, ifds::SAGESACAmount, 0, IDC_LV_ACCT_BENEF);

}

//*****************************************************************************
void RESPTransfersDlg::registerControlsToTab ()
{
   TRACE_METHOD( CLASSNAME, I_("addControlsToTab") ); 

   bool bQESITab = false;

   m_pTabCtrl = AddTabControl(CLASSNAME, IDC_TAB_TR, I_("ContribTab"));

   bool bIsQESIClient = dynamic_cast<DSTCWorkSession *>(getBFWorkSession())->isQESIClient();
   bool bIsSAGESClient = dynamic_cast<DSTCWorkSession *>(getBFWorkSession())->isSAGESClient();

   if (m_pTabCtrl)
   {
      m_pTabCtrl->AddTab (TXT_FEDERAL_TAB); 

      // Federal tab
      m_pTabCtrl->registerControl (IDC_EDT_ANNUAL_CONTRIB,			TXT_FEDERAL_TAB);
      m_pTabCtrl->registerControl (IDC_EDT_PRE98_CONTRIB,				TXT_FEDERAL_TAB);
      m_pTabCtrl->registerControl (IDC_EDT_CESG,						TXT_FEDERAL_TAB);
      m_pTabCtrl->registerControl (IDC_EDT_ADDITIONAL_CESG,			TXT_FEDERAL_TAB);
      m_pTabCtrl->registerControl (IDC_EDT_CLB,						TXT_FEDERAL_TAB);
      m_pTabCtrl->registerControl (IDC_EDT_ACES,						TXT_FEDERAL_TAB);
      m_pTabCtrl->registerControl (IDC_EDT_LIFE_CONTRIB,				TXT_FEDERAL_TAB);
      m_pTabCtrl->registerControl (IDC_EDT_FEDERAL_UNASSISTED_AMT,	TXT_FEDERAL_TAB);
      m_pTabCtrl->registerControl (IDC_STC_ANNUAL_CONTRIB,			TXT_FEDERAL_TAB);
      m_pTabCtrl->registerControl (IDC_STC_LIFE_CONTRIB,				TXT_FEDERAL_TAB);
      m_pTabCtrl->registerControl (IDC_STC_PRE98_CONTRIB,				TXT_FEDERAL_TAB);
      m_pTabCtrl->registerControl (IDC_STC_CESG_GRANT,				TXT_FEDERAL_TAB);
      m_pTabCtrl->registerControl (IDC_STC_ADD_CESG_GRANT,			TXT_FEDERAL_TAB);
      m_pTabCtrl->registerControl (IDC_STC_CLB_AMT,					TXT_FEDERAL_TAB);
      m_pTabCtrl->registerControl (IDC_STC_ACES,						TXT_FEDERAL_TAB);
      m_pTabCtrl->registerControl (IDC_STC_FEDERAL_UNASSISTED,		TXT_FEDERAL_TAB);
      m_pTabCtrl->registerControl (IDC_STC_REDEM_CONTRIB,				TXT_FEDERAL_TAB);
      m_pTabCtrl->registerControl (IDC_STC_REDEM_EARN,				TXT_FEDERAL_TAB);
      m_pTabCtrl->registerControl (IDC_STC_PRE98_REDEM,				TXT_FEDERAL_TAB);
      m_pTabCtrl->registerControl (IDC_EDT_CONTRIB_REDEM,				TXT_FEDERAL_TAB);
      m_pTabCtrl->registerControl (IDC_EDT_EARN_REDEM,				TXT_FEDERAL_TAB);
      m_pTabCtrl->registerControl (IDC_EDT_PRE98_REDEM,				TXT_FEDERAL_TAB);
      m_pTabCtrl->registerControl (IDC_STC_CESG_REDEM,				TXT_FEDERAL_TAB);
      m_pTabCtrl->registerControl (IDC_STC_CLB_REDEM,					TXT_FEDERAL_TAB);
      m_pTabCtrl->registerControl (IDC_STC_ACES_REDEM,				TXT_FEDERAL_TAB);
      m_pTabCtrl->registerControl (IDC_EDT_CESG_REDEM,				TXT_FEDERAL_TAB);
      m_pTabCtrl->registerControl (IDC_EDT_CLB_REDEM,					TXT_FEDERAL_TAB);
      m_pTabCtrl->registerControl (IDC_EDT_ACES_REDEM,				TXT_FEDERAL_TAB);
      m_pTabCtrl->registerControl (IDC_STC_FEDERAL_ASSISTED,			TXT_FEDERAL_TAB);
      m_pTabCtrl->registerControl (IDC_EDT_FEDERAL_ASSISTED_AMT,		TXT_FEDERAL_TAB);
      //P0185010.FN02.R01.02 - new field CESG Grant paid
      m_pTabCtrl->registerControl (IDC_STC_CESG_PAID ,		TXT_FEDERAL_TAB);
      m_pTabCtrl->registerControl (IDC_EDT_CESG_PAID ,		TXT_FEDERAL_TAB);
	  //SAGES
	  m_pTabCtrl->registerControl (IDC_STC_SAGES_GRANT ,	 TXT_FEDERAL_TAB);
	  m_pTabCtrl->registerControl (IDC_EDT_SAGES_GRANT ,	 TXT_FEDERAL_TAB);
	  m_pTabCtrl->registerControl (IDC_STC_SAGES_AC_AMOUNT , TXT_FEDERAL_TAB);
	  m_pTabCtrl->registerControl (IDC_EDT_SAGES_AC_AMOUNT , TXT_FEDERAL_TAB);
	  m_pTabCtrl->registerControl (IDC_STC_SAGES_UC_AMOUNT , TXT_FEDERAL_TAB);
	  m_pTabCtrl->registerControl (IDC_EDT_SAGES_UC_AMOUNT , TXT_FEDERAL_TAB);
      
      if (bIsQESIClient)
      {
         DString isAnyRESPBenefQCResident;

         getParent()->getField (this, IFASTBP_PROC::RESP_TRANSFER_LIST, IsAnyRESPBenefQCResident,  isAnyRESPBenefQCResident, false); 

         if (isAnyRESPBenefQCResident == YES)
         {
            addQESITab ();
            bQESITab = true;
         }
      }

	  showHideQESIControls (bQESITab == true ? SW_SHOW : SW_HIDE);

	  enableDisableSAGESControls (bIsSAGESClient);

   }

}

//*****************************************************************************
bool RESPTransfersDlg::doRefresh (GenericInterface * rpGICaller, 
                                  const I_CHAR* szOriginalCommand)
{ 
   TRACE_METHOD( CLASSNAME, DOREFRESH );

   SetDlgCaption();

   LoadListControl (IDC_LV_ACCT_BENEF);

   GetDlgItem (IDC_BTN_MORE)->
         EnableWindow (getParent()->doMoreRecordsExist (this, IFASTBP_PROC::RESP_TRANSFER_LIST));

   bool bIsQESIClient = dynamic_cast<DSTCWorkSession *>(getBFWorkSession())->isQESIClient();

   if(bIsQESIClient)
   {
      LoadControl(IDC_CMB_RESP_NOTIONAL_YEAR);
      LoadControl(IDC_CMB_QESI_TOTAL_TRFX);
   }
   else
   {
      showHideQESITextYear(false);
   }

   return true;
}

//******************************************************************************
bool RESPTransfersDlg::doSend ( GenericInterface *rpGICaller,
                                const I_CHAR *szMessage)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTGUI_CONDITION, 
                           CLASSNAME, 
                           I_("doSend"));
   bool bRet = true;

   if (DString (szMessage) == I_("RefreshBeneList"))
   {
      DString selectionKey;

      getParameter (I_("ListKey"), selectionKey); 
      LoadListControl (IDC_LV_ACCT_BENEF, &selectionKey);
      if (GETHIGHESTSEVERITY () > WARNING)
      {
         // Display error
         ConditionMessageBox (FRAMEBELOW (), GETHIGHESTSEVERITY ());
         bRet = false;
      }
   }
   else
   {
      bRet = BaseMainDlg::doSend (rpGICaller, szMessage);
   }
   return bRet;
}

//*****************************************************************************
void RESPTransfersDlg::showHideQESIControls (int bShowHide)
{
   GetDlgItem (IDC_STC_QESI_BASIC)->ShowWindow (bShowHide);
   GetDlgItem(IDC_EDT_QESI_BASIC)->ShowWindow (bShowHide);
   GetDlgItem(IDC_STC_QESI_INCREASE)->ShowWindow (bShowHide);
   GetDlgItem(IDC_EDT_QESI_INCREASE)->ShowWindow (bShowHide);
   GetDlgItem(IDC_STC_PRE_FEB2007)->ShowWindow (bShowHide);
   GetDlgItem(IDC_EDT_PRE_2007_QESI)->ShowWindow (bShowHide);
   GetDlgItem(IDC_STC_QESI_UNASSISTED)->ShowWindow (bShowHide);
   GetDlgItem(IDC_EDT_QESI_UNASSSITED_AMT)->ShowWindow (bShowHide);
   GetDlgItem(IDC_STC_QESI_YTD)->ShowWindow (bShowHide);
   GetDlgItem(IDC_EDT_QESI_YTD)->ShowWindow (bShowHide);
   GetDlgItem(IDC_STC_QESI_ASSISTED)->ShowWindow (bShowHide);
   GetDlgItem(IDC_EDT_QESI_ASSISTED)->ShowWindow (bShowHide);
   GetDlgItem(IDC_STC_QESI_PRE98)->ShowWindow (bShowHide);
   GetDlgItem(IDC_EDT_QESI_PRE98)->ShowWindow (bShowHide);
   GetDlgItem(IDC_STC_QESI_PAID_BY_OTHER_INST)->ShowWindow (bShowHide);
   GetDlgItem(IDC_EDT_QESI_PAID_BY_OTHER_INST)->ShowWindow (bShowHide);
}

//*****************************************************************************
void RESPTransfersDlg::displayDynamicLabels ()
{
   TRACE_METHOD( CLASSNAME, I_("displayDynamicLabels") ); 
   CString otherPlan;
   CString otherContractId;

   otherPlan.LoadString (IDS_OTHER_PLAN);
   otherContractId.LoadString (IDS_OTHER_CONTRACT_ID);

   if (m_TransType == I_("ED"))
   {
      GetDlgItem (IDC_STC_FROM_PLAN)->SetWindowText(otherPlan);
      GetDlgItem (IDC_STC_FROM_CONTRACT_ID)->SetWindowText(otherContractId);
   }
   else if (m_TransType == I_("PW"))
   {
      GetDlgItem (IDC_STC_TO_PLAN)->SetWindowText(otherPlan);
      GetDlgItem (IDC_STC_TO_CONTRACT_ID)->SetWindowText(otherContractId);
   }
   else if (DSTCommonFunctions::codeInList(m_TransType, TRANSFER_LIKE) && m_DepositType == I_("17") && !(m_RedemptonCode == I_("64") && m_RedemptonCode == I_("65")))
   {
      GetDlgItem (IDC_STC_TO_PLAN)->SetWindowText(otherPlan);
      GetDlgItem (IDC_STC_TO_CONTRACT_ID)->SetWindowText(otherContractId);
   }
}

//**********************************************************************************
void RESPTransfersDlg::ControlUpdated( UINT controlID, const DString &strValue )
{  
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTGUI_CONDITION, 
                           CLASSNAME, 
                           I_("ControlUpdated"));

   bool bIsQESIClient = dynamic_cast<DSTCWorkSession *>(getBFWorkSession())->isQESIClient();
   DString NEQ1(NULL_STRING);
   DString isInNonTrusteeTxfrPeriod(NULL_STRING);
   bool bHistTxfr(false);
   bool bNonTrusteeContrib(false);

   getParent ()->getField( this, IFASTBP_PROC::RESP_TRANSFER_LIST,  ifds::NEQ1, NEQ1, false );
   NEQ1.stripAll();
   bHistTxfr  = dynamic_cast<DSTCWorkSession *>(getBFWorkSession())->isHistTxfr();

   getParent ()->getField( this, IFASTBP_PROC::RESP_TRANSFER_LIST,  ifds::IsInNonTrusteeTxfrPeriod, isInNonTrusteeTxfrPeriod, false );

   if(NEQ1 == I_("0") && 
	   isInNonTrusteeTxfrPeriod == YES &&
	   bHistTxfr)
   {
	   bNonTrusteeContrib = true;
   }

   switch (controlID)
   {
      //for both transfer percentage and bene name the defaults should be read from the back-end
   case IDC_CMB_BEN_NAME:
      {
         //do not read default ifnon-trustee contrib
         //-----
         if(!bNonTrusteeContrib)
         {
            if (!m_bRespTransferListSelectionInProgress)
            {
               getParent ()->setField  (this, IFASTBP_PROC::RESP_TRANSFER_LIST, ReadBeneDefaults, I_("BEN"));
            }
         }
         
              
         break;
      }
      case IDC_EDT_TR_PERCENT:
      {
         if (GetControl (IDC_EDT_TR_PERCENT)->IsValid ())
         {
            if (!m_bRespTransferListSelectionInProgress)
            {
               getParent ()->setField  (this, IFASTBP_PROC::RESP_TRANSFER_LIST, ReadBeneDefaults, I_("TP"));
            }
         }
         break;
      }
      case IDC_CMB_FROM_NEQ:
		  {
           if(bIsQESIClient)
           {
              displayQESITotTxfr();

              ConnectControlToData(IDC_CMB_ELIGIBLE_TRANSFER, true);
              ConnectControlToData(IDC_CMB_QESI_TOTAL_TRFX ,true);
              LoadControl(IDC_CMB_QESI_TOTAL_TRFX);
              LoadControl(IDC_CMB_ELIGIBLE_TRANSFER);

              reloadControlsForNonTrusteeTxfr();
           }
           else
           {
              showHideQESITextYear(false);
           }

			  break;
		  }

      case IDC_CMB_ELIGIBLE_TRANSFER:
      case IDC_CMB_QESI_TOTAL_TRFX:
         {
            if (bIsQESIClient)
            {
               displayNotionalTaxYear();
               enableDisableNotionalControls();
               
               if (isNonTrusteeHistRecord ())
               {
                  GetDlgItem (IDC_BTN_BEN_ADD)->EnableWindow (true);
               }
               
               LoadControl (IDC_CMB_RESP_NOTIONAL_YEAR);
            }
            else
            {
               showHideQESITextYear(false);
            }
			if(controlID == IDC_CMB_ELIGIBLE_TRANSFER)
				GetDlgItem (IDC_CMB_ELIGIBLE_TRANSFER)->EnableWindow (bIsQESIClient);
            break;
         }
      case IDC_CMB_RESP_NOTIONAL_YEAR:
      {
         enableDisableNotionalControls();
         break;
      }
	  case IDC_CMB_RES_CESG:
	  {
	     DString dstrIsResidualCESG;
	     getParent ()->getField( this, IFASTBP_PROC::RESP_TRANSFER_LIST,  ifds::IsResidualCESG, dstrIsResidualCESG, false );
         if( (dstrIsResidualCESG == NO) && (!bNonTrusteeContrib) )
         {
            if (!m_bRespTransferListSelectionInProgress)
            {
			   /* IsResidualCESG is the Beneficiary level field, when we have to restore 
			      the value from it changed, just read notional for Beneficiary.  
			   */
               getParent ()->setField  (this, IFASTBP_PROC::RESP_TRANSFER_LIST, ReadBeneDefaults, I_("BEN"));
            }
         }
		 break;
	  }
      default:
         break;
   }
}
//**********************************************************************************
bool RESPTransfersDlg::isNonTrusteeCurrContribYear()
{
   bool ret(false);

   DString tradeDate;
   DString histNonTrustYear;
   int effectiveYear(0);
   DString tradeYear;

   getParent()->getField (this, IFASTBP_PROC::RESP_TRANSFER_LIST, ifds::TradeDate,  tradeDate, false);
   getParent()->getField (this, IFASTBP_PROC::RESP_TRANSFER_LIST, ifds::HistNonTrustYear,  histNonTrustYear, false);

   effectiveYear = DSTCommonFunctions::getYearFromUnFormattedDate (tradeDate);

   convertIntToString(effectiveYear, tradeYear);

   if(tradeYear == histNonTrustYear)
   {      
      ret = true;
   }
   return ret;
}
//**********************************************************************************
void RESPTransfersDlg::enableDisableNotionalControls()
{
   bool bNotionalControlInTabs = isNonTrusteeCurrContribYear();

   enableDisableControlsForNonTrusteeTxfr(bNotionalControlInTabs);
   reloadControlsForNonTrusteeTxfr();

}

//**********************************************************************************
void RESPTransfersDlg::SetDlgCaption()
{
   TRACE_METHOD( CLASSNAME, I_( "SetDlgCaption" ) );

   DString dstrShrNum, dstrEntityName;
   CString strName;

   // Get Entity Name
   if ( !m_dstrAccountNum.empty() ) 
      dynamic_cast<DSTCWorkSession *>(getBFWorkSession())->getFirstSequenced01AccountholderEntityName( 
      getDataGroupId(), m_dstrAccountNum, dstrEntityName);

   SetShrAcctCaption(dstrShrNum, m_dstrAccountNum, dstrEntityName);
}

//*****************************************************************************
SEVERITY RESPTransfersDlg::doInit()
{
   TRACE_METHOD( CLASSNAME, I_("doInit"));

   DString dstrDecimalDigits;

   getParameter (ACCOUNT_NUM, m_dstrAccountNum);
   getParameter (CALLER, m_dstrCaller);
   getParameter (DECIMAL_DIGITS, dstrDecimalDigits);
   getParameter (HISTORY_PENDING_FIELD, m_HistoryPending);
   getParameter (TRANS_TYPE, m_TransType);
   getParameter (DEPOSIT_TYPE, m_DepositType);
   getParameter (RED_CODE, m_RedemptonCode);
   getParameter (I_( "EffectiveDate" ), m_EffectiveDate);

   if (!dstrDecimalDigits.empty ())
   {
      m_DecimalDigits = dstrDecimalDigits.asInteger();
   }

   m_bDialogInit = true;

   return NO_CONDITION;
}

//******************************************************************************
void RESPTransfersDlg::initAccLevelOverride()
{

   DString acctLvlOverride,
      isAcctLevelOverrideApplicable;

   getParent ()->getField( this, IFASTBP_PROC::RESP_TRANSFER_LIST,  ifds::AcctLvlOverride, acctLvlOverride, false );
   getParent ()->getField (this, IFASTBP_PROC::RESP_TRANSFER_LIST, IsAcctLevelOverrideApplicable, isAcctLevelOverrideApplicable, false);

   if (isAcctLevelOverrideApplicable == I_("Y"))
   {
      if (acctLvlOverride == I_("Y"))
      {
         ((CButton *) GetDlgItem (IDC_CHK_LINK))->SetCheck(1);
      }
      else
      {
         ((CButton *) GetDlgItem (IDC_CHK_LINK))->SetCheck(0);
      }
   }
   else
   {
      GetDlgItem (IDC_CHK_LINK)->EnableWindow (false);
      ((CButton *) GetDlgItem (IDC_CHK_LINK))->SetCheck (0);
   }
}

//******************************************************************************
void RESPTransfersDlg::DoListItemChanged ( UINT listControlID, 
                                           const DString &strKey, 
                                           bool bIsNewItem, 
                                           bool bIsDummyItem)
{
   bool bIsQESIClient = dynamic_cast<DSTCWorkSession *>(getBFWorkSession())->isQESIClient();

   switch (listControlID)
   {
      case IDC_LV_ACCT_BENEF:
      {
         enableAddDelete ( bIsNewItem, bIsDummyItem );
         enableBeneficiaryData ();
         if (bIsQESIClient)
         {
            displayQESITotTxfr(); 
            LoadControl(IDC_CMB_QESI_TOTAL_TRFX);
            displayNotionalTaxYear();
            LoadControl(IDC_CMB_RESP_NOTIONAL_YEAR);
         }
         else
         {
            showHideQESITextYear(false);
         }

         m_bRespTransferListSelectionInProgress = false;
         break;
      }
      default:
         break;
   }
}

//******************************************************************************
void RESPTransfersDlg::enableNEQs ()
{
   bool bEnable = dynamic_cast<DSTCWorkSession *>(getBFWorkSession())->isQESIClient();

   GetDlgItem (IDC_CMB_FROM_NEQ)->EnableWindow (bEnable);
   GetDlgItem (IDC_CMB_TO_NEQ)->EnableWindow (bEnable);
}

//******************************************************************************
void RESPTransfersDlg::enableAddDelete (bool bIsNewItem /*false*/ , 
                                        bool bIsDummyItem /*false*/)
{
   bool  bEnableAdd = true;
   bool  bEnableDelete = true;

   if (m_dstrCaller == I_("RESPTransactionsDlg"))
   {
      //nonTrustee
      if (isNonTrusteeHistRecord ())
      {
         bEnableAdd = true;
         bEnableDelete = (bIsNewItem || bIsDummyItem);
      }
      else
      {
         bEnableAdd = false;
         bEnableDelete = false;
      }
   }
   else
   {
      DString dstrRecordLevel;

      getParent ()->getField( this, IFASTBP_PROC::RESP_TRANSFER_LIST,  ifds::RecordLevel, dstrRecordLevel, false );

      bEnableAdd = true;
      bEnableDelete = dstrRecordLevel == RECORD_LEVEL::BENEFICIARY ? true : false;
   }

   GetDlgItem (IDC_BTN_BEN_ADD)->EnableWindow (bEnableAdd);
   GetDlgItem (IDC_BTN_BEN_DELETE)->EnableWindow (bEnableDelete);
}

//******************************************************************************
void RESPTransfersDlg::enableBeneficiaryData ()
{
   bool bEnableFromBenf = false;
   bool bEnableToBenf = false;

   DString dstrRecordLevel;
   DString dstrRedCode;


   getParent()->getField (this, IFASTBP_PROC::RESP_TRANSFER_LIST, ifds::RecordLevel,  dstrRecordLevel, false);      	
   dstrRecordLevel.strip();

   if (dstrRecordLevel == RECORD_LEVEL::BENEFICIARY)
   {
      DString dstrIsInternalTransfer;

      getParent()->getField (this, IFASTBP_PROC::RESP_TRANSFER_LIST, IsInternalTransfer,  dstrIsInternalTransfer, false);      	

      if (dstrIsInternalTransfer == I_("Y") && DSTCommonFunctions::codeInList(m_TransType, TRANSFER_LIKE))
      {
         bEnableFromBenf = true;
         bEnableToBenf = true;
      }
      else
      {
         bEnableFromBenf = true;
         bEnableToBenf = false;
      }
   }

   GetDlgItem (IDC_CMB_BEN_NAME)->EnableWindow (bEnableFromBenf);		
   GetDlgItem (IDC_CMB_TO_BENEF)->EnableWindow (bEnableToBenf);		
}

//******************************************************************************
void RESPTransfersDlg::DoPreListItemChanged ( UINT listControlID,
                                              const DString &strKey,
                                              bool bIsNewItem,
                                              bool bIsDummyItem)
{
   switch (listControlID)
   {
      case IDC_LV_ACCT_BENEF:
         {
            m_bRespTransferListSelectionInProgress = true;
            break;
         }
      default:
         break;
   }
}

//******************************************************************************
void RESPTransfersDlg::addQESITab ()
{
   m_pTabCtrl->AddTab (TXT_QESI_TAB); 

   // QESI tab
   m_pTabCtrl->registerControl (IDC_STC_QESI_BASIC,               TXT_QESI_TAB);
   m_pTabCtrl->registerControl (IDC_EDT_QESI_BASIC,               TXT_QESI_TAB);
   m_pTabCtrl->registerControl (IDC_STC_QESI_INCREASE,            TXT_QESI_TAB);
   m_pTabCtrl->registerControl (IDC_EDT_QESI_INCREASE,            TXT_QESI_TAB);
   m_pTabCtrl->registerControl (IDC_STC_PRE_FEB2007,              TXT_QESI_TAB);
   m_pTabCtrl->registerControl (IDC_EDT_PRE_2007_QESI,            TXT_QESI_TAB);
   m_pTabCtrl->registerControl (IDC_STC_QESI_UNASSISTED,          TXT_QESI_TAB);
   m_pTabCtrl->registerControl (IDC_EDT_QESI_UNASSSITED_AMT,      TXT_QESI_TAB);
   m_pTabCtrl->registerControl (IDC_STC_QESI_YTD,                 TXT_QESI_TAB);
   m_pTabCtrl->registerControl (IDC_EDT_QESI_YTD,                 TXT_QESI_TAB);
   m_pTabCtrl->registerControl (IDC_STC_QESI_ASSISTED,            TXT_QESI_TAB);
   m_pTabCtrl->registerControl (IDC_EDT_QESI_ASSISTED,            TXT_QESI_TAB);
   m_pTabCtrl->registerControl (IDC_STC_QESI_PRE98,               TXT_QESI_TAB);
   m_pTabCtrl->registerControl (IDC_EDT_QESI_PRE98,               TXT_QESI_TAB);
   m_pTabCtrl->registerControl (IDC_STC_RESP_NOTIONAL_YEAR,       TXT_QESI_TAB);
   m_pTabCtrl->registerControl (IDC_CMB_RESP_NOTIONAL_YEAR,       TXT_QESI_TAB);
   m_pTabCtrl->registerControl (IDC_STC_QESI_PAID_BY_OTHER_INST,  TXT_QESI_TAB);
   m_pTabCtrl->registerControl (IDC_EDT_QESI_PAID_BY_OTHER_INST,  TXT_QESI_TAB);   
}

//******************************************************************************
void RESPTransfersDlg::OnBtnMore()
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OnBtnMore" ) );
   CWaitCursor wait;

   SetMessageStatusBar(TXT_LOAD_RESP_TRANSFER);

   static int cursel = GetList (IDC_LV_ACCT_BENEF)->GetNextItem (-1, LVIS_SELECTED | LVNI_FOCUSED);
   const DString *crtKey = &getParent()->getCurrentListItemKey (this, IFASTBP_PROC::RESP_TRANSFER_LIST);
   if (getParent()->performSearch (this, IFASTBP_PROC::RESP_TRANSFER_LIST, SEARCH_NEXT_BLOCK) <= WARNING)
   {
      LoadListControl (IDC_LV_ACCT_BENEF);
      if (*crtKey != NULL_STRING)
      {
         GetList (IDC_LV_ACCT_BENEF)->SetSelection (crtKey);
      }
   }
   else
   {
      ConditionMessageBox( FRAMEBELOW(), GETHIGHESTSEVERITY() );
   }

   GetDlgItem (IDC_BTN_MORE)->
         EnableWindow (getParent()->doMoreRecordsExist (this, IFASTBP_PROC::RESP_TRANSFER_LIST));

   SetMessageStatusBar(NULL_STRING);
}

//*****************************************************************************
void RESPTransfersDlg::showHideQESITotTxfr (int bShowHide)
{
   bool bIsQESIClient = dynamic_cast<DSTCWorkSession *>(getBFWorkSession())->isQESIClient();

   if(bIsQESIClient)
   {
      GetDlgItem(IDC_STC_QESI_TOTAL_TRFX)->ShowWindow (bShowHide);
      GetDlgItem(IDC_CMB_QESI_TOTAL_TRFX)->ShowWindow (bShowHide);
   }
   else
   {
      GetDlgItem(IDC_STC_QESI_TOTAL_TRFX)->ShowWindow (false);
      GetDlgItem(IDC_CMB_QESI_TOTAL_TRFX)->ShowWindow (false);
   }
}

//*****************************************************************************
void RESPTransfersDlg::showHideQESITextYear (int bShowHide)
{
   DSTTabCtrl* pTabCtrl = GetTabCtrl (IDC_TAB_TR);

   bool bShowControl = false;

   if (pTabCtrl != NULL)
   {
      CString cstrQESIPageName, cstrPageName;
      TCITEM tcItem;
      wchar_t buffer[256] = {0};
      tcItem.pszText = buffer;
      tcItem.cchTextMax = 256;
      tcItem.mask = TCIF_TEXT;

      int iPagePos = pTabCtrl->GetCurSel();
      pTabCtrl->GetItem(iPagePos, &tcItem);

      cstrPageName = tcItem.pszText;
      cstrQESIPageName.LoadString( TXT_QESI_TAB );

      if( cstrQESIPageName == cstrPageName )
      {
         bShowControl = true;
      }

      if (pTabCtrl->HasTab (TXT_QESI_TAB))
      {
         GetDlgItem(IDC_STC_RESP_NOTIONAL_YEAR)->ShowWindow (bShowControl && bShowHide);
         GetDlgItem(IDC_CMB_RESP_NOTIONAL_YEAR)->ShowWindow (bShowControl && bShowHide);
      }
      else
      {
         GetDlgItem(IDC_STC_RESP_NOTIONAL_YEAR)->ShowWindow (false);
         GetDlgItem(IDC_CMB_RESP_NOTIONAL_YEAR)->ShowWindow (false);
      }
   }
}

//*****************************************************************************
void RESPTransfersDlg::displayQESITotTxfr()
{
   DString strIsTotTransfINDCApplicable;
   getParent()->getField (this, 
                          IFASTBP_PROC::RESP_TRANSFER_LIST, 
                          ifds::IsTotTransfINDCApplicable, 
                          strIsTotTransfINDCApplicable, 
                          false);

   strIsTotTransfINDCApplicable.strip().upperCase();

   bool bIsQESIClient = dynamic_cast<DSTCWorkSession *>(getBFWorkSession())->isQESIClient();
   bool bDisplay = strIsTotTransfINDCApplicable == I_("Y");

   if(bIsQESIClient)
   {
      ConnectControlToData( IDC_CMB_QESI_TOTAL_TRFX, bDisplay );
      LoadControl(IDC_CMB_RESP_NOTIONAL_YEAR);
      showHideQESITotTxfr(bDisplay);
   }
   else
   {
      showHideQESITextYear(false);
	  showHideQESITotTxfr(false); //IN2750669 - BIP QESI FIELD DEPLOYED TO BRANDES IN ERRO
   }

}
//*****************************************************************************
void RESPTransfersDlg::enableDisableControlsForNonTrusteeTxfr (bool bShowHide)
{
   //QESI
	/*
   GetDlgItem (IDC_STC_QESI_BASIC)->EnableWindow (bShowHide);	
   GetDlgItem(IDC_STC_QESI_INCREASE)->EnableWindow (bShowHide);	
   GetDlgItem(IDC_STC_PRE_FEB2007)->EnableWindow (bShowHide);	
   GetDlgItem(IDC_STC_QESI_UNASSISTED)->EnableWindow (bShowHide);	
   GetDlgItem(IDC_STC_QESI_ASSISTED)->EnableWindow (bShowHide);	
   GetDlgItem(IDC_STC_QESI_PRE98)->EnableWindow (bShowHide);	
*/
  
   GetDlgItem(IDC_EDT_QESI_BASIC)->EnableWindow (bShowHide);
   GetDlgItem(IDC_EDT_QESI_INCREASE)->EnableWindow (bShowHide);
   GetDlgItem(IDC_EDT_PRE_2007_QESI)->EnableWindow (bShowHide);
   GetDlgItem(IDC_EDT_QESI_UNASSSITED_AMT)->EnableWindow (bShowHide);
   GetDlgItem(IDC_EDT_QESI_ASSISTED)->EnableWindow (bShowHide);
   GetDlgItem(IDC_EDT_QESI_PRE98)->EnableWindow (bShowHide);

   //Federal
   /*
   GetDlgItem (IDC_STC_ANNUAL_CONTRIB)->EnableWindow (bShowHide);
   GetDlgItem (IDC_STC_LIFE_CONTRIB)->EnableWindow (bShowHide);
   GetDlgItem (IDC_STC_PRE98_CONTRIB)->EnableWindow (bShowHide);
   GetDlgItem (IDC_STC_CESG_GRANT)->EnableWindow (bShowHide);
   GetDlgItem (IDC_STC_ADD_CESG_GRANT)->EnableWindow (bShowHide);
   GetDlgItem (IDC_STC_CLB_AMT)->EnableWindow (bShowHide);
   GetDlgItem (IDC_STC_ACES)->EnableWindow (bShowHide);
   GetDlgItem (IDC_STC_FEDERAL_UNASSISTED)->EnableWindow (bShowHide);
   GetDlgItem (IDC_STC_REDEM_CONTRIB)->EnableWindow (bShowHide);
   GetDlgItem (IDC_STC_REDEM_EARN)->EnableWindow (bShowHide);
   GetDlgItem (IDC_STC_PRE98_REDEM)->EnableWindow (bShowHide);
   GetDlgItem (IDC_STC_CESG_REDEM)->EnableWindow (bShowHide);
   GetDlgItem (IDC_STC_CLB_REDEM)->EnableWindow (bShowHide);
   GetDlgItem (IDC_STC_ACES_REDEM)->EnableWindow (bShowHide);
   GetDlgItem (IDC_STC_FEDERAL_ASSISTED)->EnableWindow (bShowHide);
   */
   GetDlgItem (IDC_EDT_ANNUAL_CONTRIB)->EnableWindow (bShowHide);
   GetDlgItem (IDC_EDT_PRE98_CONTRIB)->EnableWindow (bShowHide);
   GetDlgItem (IDC_EDT_CESG)->EnableWindow (bShowHide);
   GetDlgItem (IDC_EDT_ADDITIONAL_CESG)->EnableWindow (bShowHide);
   GetDlgItem (IDC_EDT_CLB)->EnableWindow (bShowHide);
   GetDlgItem (IDC_EDT_ACES)->EnableWindow (bShowHide);
   GetDlgItem (IDC_EDT_FEDERAL_UNASSISTED_AMT)->EnableWindow (bShowHide);
   GetDlgItem (IDC_EDT_CONTRIB_REDEM)->EnableWindow (bShowHide);
   GetDlgItem (IDC_EDT_EARN_REDEM)->EnableWindow (bShowHide);
   GetDlgItem (IDC_EDT_PRE98_REDEM)->EnableWindow (bShowHide);
   GetDlgItem (IDC_EDT_CESG_REDEM)->EnableWindow (bShowHide);
   GetDlgItem (IDC_EDT_CLB_REDEM)->EnableWindow (bShowHide);
   GetDlgItem (IDC_EDT_ACES_REDEM)->EnableWindow (bShowHide);
   GetDlgItem (IDC_EDT_LIFE_CONTRIB)->EnableWindow (bShowHide);
   GetDlgItem (IDC_EDT_FEDERAL_ASSISTED_AMT)->EnableWindow (bShowHide);
   GetDlgItem (IDC_EDT_CESG_PAID)->EnableWindow (bShowHide);//P0185010.FN02.R01.02 - new field CESG Grant paid
}

//*****************************************************************************
void RESPTransfersDlg::reloadControlsForNonTrusteeTxfr ()
{
   //QESI
	LoadControl(IDC_EDT_QESI_YTD);


   LoadControl(IDC_EDT_QESI_BASIC);
   LoadControl(IDC_EDT_QESI_INCREASE);
   LoadControl(IDC_EDT_PRE_2007_QESI);
   LoadControl(IDC_EDT_QESI_UNASSSITED_AMT);
   LoadControl(IDC_EDT_QESI_ASSISTED);
   LoadControl(IDC_EDT_QESI_PRE98);

   //Federal
   LoadControl (IDC_EDT_ANNUAL_CONTRIB);
   LoadControl (IDC_EDT_PRE98_CONTRIB);
   LoadControl (IDC_EDT_CESG);
   LoadControl (IDC_EDT_ADDITIONAL_CESG);
   LoadControl (IDC_EDT_CLB);
   LoadControl (IDC_EDT_ACES);
   LoadControl (IDC_EDT_FEDERAL_UNASSISTED_AMT);
   LoadControl (IDC_EDT_CONTRIB_REDEM);
   LoadControl (IDC_EDT_EARN_REDEM);
   LoadControl (IDC_EDT_PRE98_REDEM);
   LoadControl (IDC_EDT_CESG_REDEM);
   LoadControl (IDC_EDT_CLB_REDEM);
   LoadControl (IDC_EDT_ACES_REDEM);
   LoadControl (IDC_EDT_LIFE_CONTRIB);
   LoadControl (IDC_EDT_FEDERAL_ASSISTED_AMT);
   LoadControl (IDC_EDT_CESG_PAID ); //P0185010.FN02.R01.02 - new field CESG Grant paid
}

//******************************************************************************
void RESPTransfersDlg::displayNotionalTaxYear()
{
   DString strIsNotionalTaxYearApplicable;
   getParent()->getField (this, 
                          IFASTBP_PROC::RESP_TRANSFER_LIST, 
                          ifds::IsNotionalTaxYearApplicable, 
                          strIsNotionalTaxYearApplicable, 
                          false);

   strIsNotionalTaxYearApplicable.strip().upperCase();

   DSTTabCtrl* pTabCtrl = GetTabCtrl (IDC_TAB_TR);

   bool bDisplay = false;
   if (pTabCtrl != NULL && pTabCtrl->HasTab (TXT_QESI_TAB) )
   {
      bDisplay = strIsNotionalTaxYearApplicable == I_("Y");
   }

   bool bIsQESIClient = dynamic_cast<DSTCWorkSession *>(getBFWorkSession())->isQESIClient();

   if(bIsQESIClient)
   {
      ConnectControlToData( IDC_CMB_RESP_NOTIONAL_YEAR, bDisplay );
      showHideQESITextYear(bDisplay);
   }
   else
   {
      showHideQESITextYear(false);
   }

}

//******************************************************************************
void RESPTransfersDlg::tabSelectionChanged( UINT tabControlID, const DString& strPageName )
{ 
   CString cstrQESIPageName;
   cstrQESIPageName.LoadString( TXT_QESI_TAB );

   bool bIsQESIClient = dynamic_cast<DSTCWorkSession *>(getBFWorkSession())->isQESIClient();

   if( bIsQESIClient )
   {
      if( strPageName.c_str() == cstrQESIPageName )
      {
         displayNotionalTaxYear();
         enableDisableNotionalControls();
      }
      else
      {
         showHideQESITextYear(false);
      }
   }
   else
   {
      showHideQESITextYear(false);
   }
}

//******************************************************************************
bool RESPTransfersDlg::isNonTrusteeHistRecord ()
{
   DString NEQ1, 
      isInNonTrusteeTxfrPeriod,
      anyBenefCurrTradeYear;
   bool bHistTxfr (false);

   getParent ()->getField( this, IFASTBP_PROC::RESP_TRANSFER_LIST,  ifds::NEQ1, NEQ1, false );
   NEQ1.stripAll();
   bHistTxfr  = dynamic_cast<DSTCWorkSession *>(getBFWorkSession())->isHistTxfr();

   getParent ()->getField ( this, IFASTBP_PROC::RESP_TRANSFER_LIST,  ifds::IsInNonTrusteeTxfrPeriod, 
                            isInNonTrusteeTxfrPeriod, false );
   getParent ()->getField ( this, IFASTBP_PROC::RESP_TRANSFER_LIST,  ifds::AnyBenefCurrTradeYear, 
                            anyBenefCurrTradeYear, false );
   return NEQ1 == I_("0") && 
          isInNonTrusteeTxfrPeriod == YES &&
          anyBenefCurrTradeYear == YES &&
          bHistTxfr;
}

//*****************************************************************************
void RESPTransfersDlg::enableDisableSAGESControls (bool bEnableDisable)
{
   CString cstrSAGESAC, cstrSAGESUC, cstrSAGES;

   GetDlgItem(IDC_EDT_SAGES_GRANT)->EnableWindow(bEnableDisable);
   GetDlgItem(IDC_EDT_SAGES_AC_AMOUNT)->EnableWindow(bEnableDisable);
   GetDlgItem(IDC_EDT_SAGES_UC_AMOUNT)->EnableWindow(bEnableDisable);  

   if ( (m_TransType == I_("ED") && m_DepositType == I_("17")) || 
	    (m_TransType == I_("TI") && m_DepositType == I_("17") && (m_RedemptonCode == I_("01") || m_RedemptonCode == I_("64"))) ) // external/internal Transfer-In
   {
	   cstrSAGESAC.LoadString (TXT_SAGES_AC);
	   cstrSAGESUC.LoadString (TXT_SAGES_UC);
	   cstrSAGES.LoadString (TXT_SAGES);
	   GetDlgItem (IDC_STC_SAGES_GRANT)->SetWindowText(cstrSAGES);
	   GetDlgItem (IDC_STC_SAGES_AC_AMOUNT)->SetWindowText(cstrSAGESAC);
	   GetDlgItem (IDC_STC_SAGES_UC_AMOUNT)->SetWindowText(cstrSAGESUC);
   } 
   else
   {
	   cstrSAGESAC.LoadString (TXT_SAGES_AC_BALANCE);
	   cstrSAGESUC.LoadString (TXT_SAGES_UC_BALANCE);
	   cstrSAGES.LoadString (TXT_SAGES_BALANCE);
	   GetDlgItem (IDC_STC_SAGES_GRANT)->SetWindowText(cstrSAGES);
	   GetDlgItem (IDC_STC_SAGES_AC_AMOUNT)->SetWindowText(cstrSAGESAC);
	   GetDlgItem (IDC_STC_SAGES_UC_AMOUNT)->SetWindowText(cstrSAGESUC);
   }
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/RESPTransfersDlg.cpp-arc  $
// 
//    Rev 1.30   Nov 29 2011 06:01:46   panatcha
// P0184541FN01_IN2750669 - BIP QESI FIELD DEPLOYED TO BRANDES IN ERROR
// 
//    Rev 1.29   Oct 25 2011 05:00:22   wutipong
// IN#2625408 - Disable eligible transfer on non-QESI client
// 
//    Rev 1.28   Oct 07 2011 07:05:16   panatcha
// P0185010.FN02.R01.02 - new field CESG Grant paid
// 
//    Rev 1.27   Oct 06 2011 10:56:04   panatcha
// P0185010FN01 - Beneficiary Allocations, EAP, LLP Withdrawals
// 
//    Rev 1.26   Sep 23 2011 18:15:58   popescu
// Incident 2646349 - P0184541Fn01- Non QESI Desktop Issues
// 
//    Rev 1.25   Jul 29 2011 07:34:08   panatcha
// fix IN5285248 and IN2591262
// 
//    Rev 1.24   Jul 25 2011 07:05:32   panatcha
// P0184541_FN01_InvescoQESItrans incidents
// 
//    Rev 1.23   Jul 18 2011 05:52:46   panatcha
// IN2584478 - All reject error and re-label 
// 
//    Rev 1.22   Jul 11 2011 05:27:02   dchatcha
// IN# 2587585 - P0184541FN01- Error when accessing RESP TRFR notl in trading screen
// 
//    Rev 1.21   Jun 29 2011 08:58:54   panatcha
// P0184541_FN01_InvescoQESItrans
// 
//    Rev 1.20   Jun 28 2011 10:22:02   panatcha
// P0184541_FN01_InvescoQESItrans
// 
//    Rev 1.19   Jun 17 2011 16:33:00   wutipong
// IN2504087 - QESI Transfer Tab - Allow Negative Values
//  
//    Rev 1.18   Sep 09 2010 14:02:36   jankovii
// IN 2222676 - QESI notional tab on Transfer screen.
// 
//    Rev 1.17   Jun 24 2010 07:25:14   dchatcha
// PET0165541 FN09 QESI RESP phase2B - SOC04 - Eligible Transfer on RESP Transfer screen.
// 
//    Rev 1.16   Jun 09 2010 14:40:58   popescu
// IN 2124688 - Fixed showing the error message for the percentage value
//
 *
 */
