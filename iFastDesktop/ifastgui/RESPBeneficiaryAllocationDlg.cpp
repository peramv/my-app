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
// ^FILE   :RESPBeneficiaryAllocationDlg.cpp
// ^AUTHOR : 
// ^DATE   : 
//
// ----------------------------------------------------------
//
// ^CLASS    : RESPBeneficiaryAllocationDlg
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :  
//
//******************************************************************************

#include "stdafx.h"
#include "mfdstc.h"

#include "respbeneficiaryallocationdlg.h"
#include <configmanager.hpp>
#include <uibase\DSTEdit.h>
#include <uibase\ifdslistctrl.h>

#include <ifastbp\mfcaninterprocparam.hpp>
#include <ifastbp\respbeneficiaryallocationlistprocessincludes.h>
#include <ifastbp\respbeneficiaryallocationlistprocess.hpp>
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

extern CLASS_IMPORT const I_CHAR* CMD_GUI_RESP_BENEF_ALLOCATION_LIST;
#include <bfproc\concretedialogcreator.hpp>
static ConcreteDialogCreator< RESPBeneficiaryAllocationDlg > dlgCreator( CMD_GUI_RESP_BENEF_ALLOCATION_LIST ); 

extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_RESP_ALLOC_HISTROY;

#ifdef _DEBUG
   #define new DEBUG_NEW
   #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

namespace
{
   const I_CHAR * const CLASSNAME				= I_("RESPBeneficiaryAllocationDlg");
   const I_CHAR *LV_BENEFICIARIES				= I_( "BeneficiaryAllocations" );
}

namespace UAF
{
   extern CLASS_IMPORT I_CHAR * const RESP_BENEFICIARY_ALLOCATION;
}

namespace ifds
{
	extern CLASS_IMPORT const BFTextFieldId DepositType;
	extern CLASS_IMPORT const BFTextFieldId AmtType;
	extern CLASS_IMPORT const BFDecimalFieldId Amount;
	extern CLASS_IMPORT const BFTextFieldId TradesTransType;

}

//*****************************************************************************
// Public methods
//*****************************************************************************
RESPBeneficiaryAllocationDlg::RESPBeneficiaryAllocationDlg( CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: BaseMainDlg( RESPBeneficiaryAllocationDlg::IDD, pParent, pGIC, pGIParent, rCommand, CLASSNAME ),
m_bDialogInit (false),
m_DecimalDigits (0),
m_disableScreen (NULL_STRING)

{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   //{{AFX_DATA_INIT(RESPBeneficiaryAllocationDlg)
   //}}AFX_DATA_INIT
}

//*****************************************************************************
void RESPBeneficiaryAllocationDlg::DoDataExchange( CDataExchange* pDX )
{
   BaseMainDlg::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(RESPBeneficiaryAllocationDlg)
   //}}AFX_DATA_MAP
}

//*****************************************************************************
BEGIN_MESSAGE_MAP(RESPBeneficiaryAllocationDlg, BaseMainDlg)
//{{AFX_MSG_MAP(RESPBeneficiaryAllocationDlg)
ON_BN_CLICKED(IDC_BTN_ADD, OnBtnAdd)
ON_BN_CLICKED(IDC_BTN_DELETE, OnBtnDelete)
ON_BN_CLICKED(IDC_BTN_ALLOC_HISTORY, OnBtnAllocHistory)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//*****************************************************************************
// Message handlers
class LVBenefAllocData : public IFDSListCtrlRowDataBase
{
public:
   virtual ~LVBenefAllocData() {}
   DString BenefId_;
   DString AllocAmount_;
   DString AllocPercent_;
   DString HRDCRelationship_;
   DString EffectiveDate_;
   DString TaxJuris_;
   DString DateOfBirth_;

   virtual void update(BaseDlg* pDlg, IFDSListCtrl* pCtrl, const DString* pKey)
   {
      pDlg->getParent()->getField(pDlg, BF::NullContainerId, 
         ifds::RESPBenefId, BenefId_);
      BenefId_.strip();
      pDlg->getParent()->getField(pDlg, BF::NullContainerId, 
         ifds::RESPAllocAmt, AllocAmount_);
      AllocAmount_.strip();
      pDlg->getParent()->getField(pDlg, BF::NullContainerId, 
         ifds::RESPAllocPrcnt, AllocPercent_);
      AllocPercent_.strip();
      pDlg->getParent()->getField(pDlg, BF::NullContainerId, 
         ifds::HRDCRelateCode, HRDCRelationship_);
      HRDCRelationship_.strip();
      pDlg->getParent()->getField(pDlg, BF::NullContainerId, 
         ifds::EffectiveDate, EffectiveDate_);
      EffectiveDate_.strip();
      pDlg->getParent()->getField(pDlg, BF::NullContainerId, 
         ifds::TaxJuris, TaxJuris_);
      TaxJuris_.strip();
      pDlg->getParent()->getField(pDlg, BF::NullContainerId, 
         ifds::BenefDofB, DateOfBirth_);
      DateOfBirth_.strip();
   }
};

class LVBenefAllocAdapter : public IFDSListCtrlAdapter< LVBenefAllocData >
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
      else if (*pFieldId == ifds::RESPBenefId) 
      {
         result = i_strcmp(pData1->BenefId_.c_str(), pData2->BenefId_.c_str());
      } 
      else if (*pFieldId == ifds::RESPAllocAmt) 
      {
         result = i_strcmp(pData1->AllocAmount_.c_str(), pData2->AllocAmount_.c_str());
      } 
      else if (*pFieldId == ifds::RESPAllocPrcnt) 
      {
         result = i_strcmp(pData1->AllocPercent_.c_str(), pData2->AllocPercent_.c_str());
      } 
      else if (*pFieldId == ifds::HRDCRelateCode) 
      {
         result = i_strcmp(pData1->HRDCRelationship_.c_str(), pData2->HRDCRelationship_.c_str());
      } 
      else if (*pFieldId == ifds::TaxJuris) 
      {
         result = i_strcmp(pData1->TaxJuris_.c_str(), pData2->TaxJuris_.c_str());
      } 
      else if( *pFieldId == ifds::EffectiveDate ) 
	  {
			if ( DSTCommonFunctions::CompareDates( pData1->EffectiveDate_.c_str(), pData2->EffectiveDate_.c_str() ) == DSTCommonFunctions::FIRST_EARLIER )
				result = -1;
			else if ( DSTCommonFunctions::CompareDates( pData2->EffectiveDate_.c_str(), pData1->EffectiveDate_.c_str() ) == DSTCommonFunctions::FIRST_EARLIER ) 
				result = 1;
	  }
	  else if( *pFieldId == ifds::BenefDofB ) 
	  {
			if ( DSTCommonFunctions::CompareDates( pData1->DateOfBirth_.c_str(), pData2->DateOfBirth_.c_str() ) == DSTCommonFunctions::FIRST_EARLIER )
				result = -1;
			else if ( DSTCommonFunctions::CompareDates( pData2->DateOfBirth_.c_str(), pData1->DateOfBirth_.c_str() ) == DSTCommonFunctions::FIRST_EARLIER ) 
				result = 1;
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
         else if (*pFieldId == ifds::RESPBenefId) 
         {
            pDispInfo->item.pszText = (I_CHAR*)pData->BenefId_.c_str();
         } 
         else if (*pFieldId == ifds::RESPAllocAmt) 
         {
            pDispInfo->item.pszText = (I_CHAR*)pData->AllocAmount_.c_str();
         } 
         else if (*pFieldId == ifds::RESPAllocPrcnt) 
         {
            pDispInfo->item.pszText = (I_CHAR*)pData->AllocPercent_.c_str();
         } 
         else if (*pFieldId == ifds::HRDCRelateCode)
         {
            pDispInfo->item.pszText = (I_CHAR*)pData->HRDCRelationship_.c_str();
         } 
         else if (*pFieldId == ifds::TaxJuris)
         {
            pDispInfo->item.pszText = (I_CHAR*)pData->TaxJuris_.c_str();
         } 
         else if( *pFieldId == ifds::EffectiveDate ) 
		 {
            pDispInfo->item.pszText = (I_CHAR*)pData->EffectiveDate_.c_str();
         }
		 else if( *pFieldId == ifds::BenefDofB )
		{
            pDispInfo->item.pszText = (I_CHAR*)pData->DateOfBirth_.c_str();
		}

         return (1);
      }
      return (0);
   }
};

//*****************************************************************************
BOOL RESPBeneficiaryAllocationDlg::OnInitDialog() 
{
	TRACE_METHOD( CLASSNAME, ONINITDIALOG );
	BaseMainDlg::OnInitDialog(); 

	IFDSListCtrl* pBenefAllocListCtrl =  new IFDSAdaptedListCtrl< LVBenefAllocAdapter >(this, CLASSNAME, IDC_LV_BENEFICIARIES, 0, 0, true, true);
   
   AddIFDSListControl (pBenefAllocListCtrl, LV_BENEFICIARIES, IFASTBP_PROC::RESP_BENEF_ALLOC_LIST, ifds::RESPBenefAllocHeading);

	BFContainerId topControlsContainer = BF::NullContainerId;

   if (m_dstrCaller == I_("TradeEntry"))
   {
      AddControl (CTRL_COMBO, IDC_CMB_TRANS_TYPE, IFASTBP_PROC::TRADE, ifds::TradesTransType, CTRLFLAG_INITCOMBO_BY_SUB_LIST);
	   AddControl (CTRL_COMBO, IDC_CMB_GROSSNET, IFASTBP_PROC::TRADE, ifds::GrossOrNet, CTRLFLAG_INITCOMBO_BY_SUB_LIST);
	   AddControl (CTRL_EDIT,  IDC_EDT_ALLOC_AMOUNT, IFASTBP_PROC::TRADE, ifds::Amount, CTRLFLAG_DEFAULT);
	   AddControl (CTRL_COMBO, IDC_CMB_DEPOSIT_CODE, IFASTBP_PROC::TRADE, ifds::DepositType, CTRLFLAG_INITCOMBO_BY_SUB_LIST);
	   AddControl (CTRL_COMBO, IDC_CMB_AMOUNT_TYPE, IFASTBP_PROC::TRADE, ifds::AmtType, CTRLFLAG_INITCOMBO_BY_SUB_LIST);
   }
   else if (m_dstrCaller == I_("RESPTransactionsDlg") && m_HistoryPending == RESPINFONAMES::HISTORY)
   {
      AddControl (CTRL_COMBO, IDC_CMB_TRANS_TYPE, IFASTBP_PROC::TRANSACTION, ifds::TransType, CTRLFLAG_INITCOMBO_BY_SUB_LIST);
	   AddControl (CTRL_COMBO, IDC_CMB_GROSSNET, IFASTBP_PROC::TRANSACTION, ifds::GrossOrNet, CTRLFLAG_INITCOMBO_BY_SUB_LIST);
	   AddControl (CTRL_EDIT,  IDC_EDT_ALLOC_AMOUNT, IFASTBP_PROC::TRANSACTION, ifds::GrossAmt, CTRLFLAG_DEFAULT);
	   AddControl (CTRL_COMBO, IDC_CMB_DEPOSIT_CODE, IFASTBP_PROC::TRANSACTION, ifds::DepositType, CTRLFLAG_INITCOMBO_BY_SUB_LIST);
	   AddControl (CTRL_COMBO, IDC_CMB_AMOUNT_TYPE, IFASTBP_PROC::TRANSACTION, ifds::AmtType, CTRLFLAG_INITCOMBO_BY_SUB_LIST);
   }
   else if (m_dstrCaller == I_("RESPTransactionsDlg") && m_HistoryPending == RESPINFONAMES::PENDING)
   {
      AddControl (CTRL_COMBO, IDC_CMB_TRANS_TYPE, IFASTBP_PROC::PENDING_TRANSACTION, ifds::TransType, CTRLFLAG_INITCOMBO_BY_SUB_LIST);
	   AddControl (CTRL_COMBO, IDC_CMB_GROSSNET, IFASTBP_PROC::PENDING_TRANSACTION, ifds::GrossNetMethod, CTRLFLAG_INITCOMBO_BY_SUB_LIST);
	   AddControl (CTRL_EDIT,  IDC_EDT_ALLOC_AMOUNT, IFASTBP_PROC::PENDING_TRANSACTION, ifds::Amount, CTRLFLAG_DEFAULT);
	   AddControl (CTRL_COMBO, IDC_CMB_DEPOSIT_CODE, IFASTBP_PROC::PENDING_TRANSACTION, ifds::DepositType, CTRLFLAG_INITCOMBO_BY_SUB_LIST);
	   AddControl (CTRL_COMBO, IDC_CMB_AMOUNT_TYPE, IFASTBP_PROC::PENDING_TRANSACTION, ifds::AmountType, CTRLFLAG_INITCOMBO_BY_SUB_LIST);
   }

	AddControl (CTRL_COMBO, IDC_CMB_BENEFICIARY, IFASTBP_PROC::RESP_BENEF_ALLOC_LIST, ifds::RESPBenefId, CTRLFLAG_INITCOMBO_BY_SUB_LIST, IDC_LV_BENEFICIARIES);
	AddControl (CTRL_EDIT,IDC_EDT_BEN_AMOUNT, IFASTBP_PROC::RESP_BENEF_ALLOC_LIST, ifds::RESPAllocAmt, CTRLFLAG_DEFAULT, IDC_LV_BENEFICIARIES);
	AddControl (CTRL_EDIT,IDC_EDT_RESP_PERCENT, IFASTBP_PROC::RESP_BENEF_ALLOC_LIST, ifds::RESPAllocPrcnt, CTRLFLAG_DEFAULT, IDC_LV_BENEFICIARIES);
	AddControl (CTRL_COMBO, IDC_CMB_REALLOCATED, IFASTBP_PROC::RESP_BENEF_ALLOC_LIST, ifds::ReAllocated, CTRLFLAG_INITCOMBO_BY_SUB_LIST, IDC_LV_BENEFICIARIES);

	return TRUE;
}

//******************************************************************************
void RESPBeneficiaryAllocationDlg::OnPostInitDialog()
{
	TRACE_METHOD( CLASSNAME, ONPOSTINITDIALOG );

	if (m_dstrCaller != I_("TradeEntry"))
   {
		SetUserAccesFunctionCode (UAF::RESP_BENEFICIARY_ALLOCATION); 
		addControlGroupIDForPermissionCheck (IDC_LV_BENEFICIARIES);
      addBtnAddForPermissionCheck (IDC_BTN_ADD, IDC_LV_BENEFICIARIES);
		addBtnDeleteForPermissionCheck (IDC_BTN_DELETE, IDC_LV_BENEFICIARIES);
   }

	DSTEdit *edit = NULL;

   edit = dynamic_cast<DSTEdit *>( GetControl (IDC_EDT_BEN_AMOUNT));
   edit->SetAllowedChars(I_("0123456789."));
   edit->setInputAllowedUnsignedDecimal();
   //setting the decimal point to 2 digits as user was not able to enter digits after decimal point - PRB0042365
   if(m_DecimalDigits == 0)
	   m_DecimalDigits = 2; 
   edit->setMaxNumDigitsAfterDecimalPoint(m_DecimalDigits);

  	edit = dynamic_cast<DSTEdit *>( GetControl (IDC_EDT_RESP_PERCENT));
	edit->SetAllowedChars(I_("0123456789."));
	edit->setInputAllowedUnsignedDecimal();

	ConnectControlsToData ();
	LoadControls ();
	doRefresh (this, NULL_STRING);

	if (m_dstrCaller == TRANS_HIST)
	{
      bool bEnable = m_HistoryPending == RESPINFONAMES::HISTORY ? true : false;

		GetDlgItem (IDC_BTN_ADD)->EnableWindow (bEnable);
		GetDlgItem (IDC_BTN_DELETE)->EnableWindow (bEnable);
		GetDlgItem (IDC_EDT_BEN_AMOUNT)->EnableWindow (bEnable);
		GetDlgItem (IDC_EDT_RESP_PERCENT)->EnableWindow (bEnable);
	}
	else if (m_dstrCaller == TRADE_ENTRY)
	{
		GetDlgItem (IDC_BTN_ADD)->EnableWindow (true);
		GetDlgItem (IDC_BTN_DELETE)->EnableWindow (true);
	}
   
   GetDlgItem (IDC_CMB_TRANS_TYPE)->EnableWindow (false);
	GetDlgItem (IDC_CMB_GROSSNET)->EnableWindow (false);
	GetDlgItem (IDC_EDT_ALLOC_AMOUNT)->EnableWindow (false);
	GetDlgItem (IDC_CMB_DEPOSIT_CODE)->EnableWindow (false);
	GetDlgItem (IDC_CMB_AMOUNT_TYPE)->EnableWindow (false);

   m_bDialogInit = false;
}

//*****************************************************************************
void RESPBeneficiaryAllocationDlg::OnBtnAdd () 
{
	TRACE_METHOD( CLASSNAME, I_("OnBtnAdd") );   

	AddToListControl (IDC_LV_BENEFICIARIES);
}

//*****************************************************************************
void RESPBeneficiaryAllocationDlg::OnBtnDelete () 
{
	TRACE_METHOD( CLASSNAME, I_("OnBtnDelete") ); 

	DeleteFromListControl (IDC_LV_BENEFICIARIES);
}

//*****************************************************************************
void RESPBeneficiaryAllocationDlg::OnBtnAllocHistory () 
{
	TRACE_METHOD( CLASSNAME, I_("OnBtnAllocHistory") ); 

	DString urlParamsIDI;
	//DString strTransId;
        
	E_COMMANDRETURN eRtn = CMD_OK;

    setParameter( I_( "AccountNum" ), m_dstrAccountNum );
    setParameter( I_( "TransID" ), m_TransId ); 
    setParameter( I_( "from_screen" ), I_( "RESPBeneficiaryAllocationDlg" ) );

    addIDITagValue (urlParamsIDI, I_("AccountNum"), m_dstrAccountNum);
    addIDITagValue (urlParamsIDI, I_("TransId"), m_TransId);
    addIDITagValue (urlParamsIDI, I_("screen"), I_("BeneAllocHist")); //DesktopWeb conversion

    setParameter (I_("UrlParams"), urlParamsIDI);
	CString cstrRESPAllocHistory;
	cstrRESPAllocHistory.LoadString(TXT_RESP_ALLOCATION_HISTORY_TRANSID);
	setParameter (I_("BrowserTitle"), DString(cstrRESPAllocHistory) + m_TransId);
    setParameter (I_("from_screen"), I_("RESPBeneficiaryAllocationDlg"));

    eRtn = invokeCommand (getParent(), CMD_BPROC_RESP_ALLOC_HISTROY, PROC_NO_TYPE, true, NULL);

}
//*****************************************************************************
bool RESPBeneficiaryAllocationDlg::doRefresh (GenericInterface * rpGICaller, 
                                              const I_CHAR* szOriginalCommand)
{ 
   TRACE_METHOD( CLASSNAME, DOREFRESH );

   SetDlgCaption();

   LoadListControl( IDC_LV_BENEFICIARIES );

   return( true );
}


//**********************************************************************************
void RESPBeneficiaryAllocationDlg::ControlUpdated( UINT controlID, const DString &strValue )
{  
   if(controlID == IDC_EDT_RESP_PERCENT)
   {
      DString allowManualDelete;
      getParent()->getField(this, IFASTBP_PROC::RESP_BENEF_ALLOC_LIST, ifds::AllowManualDelete,allowManualDelete,false);
      if(allowManualDelete.strip().upperCase() == I_("N"))
      {
         GetDlgItem (IDC_BTN_DELETE)->EnableWindow (false);
      }
      else
      {
         GetDlgItem (IDC_BTN_DELETE)->EnableWindow (true);
      }
   }
}

//**********************************************************************************
void RESPBeneficiaryAllocationDlg::SetDlgCaption ()
{
	TRACE_METHOD( CLASSNAME, I_( "SetDlgCaption" ) );

   DString dstrShrNum, 
      dstrEntityName;

	// Get Entity Name
	if ( !m_dstrAccountNum.empty() ) 
		dynamic_cast<DSTCWorkSession *>(getBFWorkSession())->getFirstSequenced01AccountholderEntityName( 
         getDataGroupId(), m_dstrAccountNum, dstrEntityName);

	SetShrAcctCaption(dstrShrNum, m_dstrAccountNum, dstrEntityName);
}

//*****************************************************************************
SEVERITY RESPBeneficiaryAllocationDlg::doInit()
{
	TRACE_METHOD( CLASSNAME, I_("doInit"));

	DString dstrDecimalDigits;

	getParameter (I_("AccountNum"), m_dstrAccountNum);
	getParameter (CALLER, m_dstrCaller);
	getParameter (DECIMAL_DIGITS, dstrDecimalDigits);
   getParameter (HISTORY_PENDING_FIELD, m_HistoryPending);
   getParameter (I_("DisableScreen"), m_disableScreen);
   getParameter (TRANSID, m_TransId );

   if (!dstrDecimalDigits.empty ())
	{
		m_DecimalDigits = dstrDecimalDigits.asInteger();
	}

	m_bDialogInit = true;
	return NO_CONDITION;
}

//******************************************************************************
bool RESPBeneficiaryAllocationDlg::doDisableControl (UINT nID, bool bIsNew)
{
   return m_disableScreen == I_("Y");
}

//******************************************************************************
bool RESPBeneficiaryAllocationDlg::doDisablePermCheckButton (UINT nID)
{
   if(nID == IDC_BTN_DELETE)
   {
      DString allowManualDelete;
      getParent()->getField(this, IFASTBP_PROC::RESP_BENEF_ALLOC_LIST, ifds::AllowManualDelete,allowManualDelete,false);
      if(allowManualDelete.strip().upperCase() == I_("N"))
      {
         return true;
      }
      else
      {
         return m_disableScreen == I_("Y");
      }
   }
   else
   {
      return m_disableScreen == I_("Y");
   }
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/RESPBeneficiaryAllocationDlg.cpp-arc  $
// 
//    Rev 1.16   Feb 08 2012 04:55:22   panatcha
// DesktopWeb conversion
// 
//    Rev 1.15   Nov 25 2011 16:01:34   wp040168
// P0186484/FN06 - DESKTOP - iFast Desktop (French Customizations)
// 
//    Rev 1.14   Nov 21 2011 18:46:54   wp040168
// P0186484/FN06 - DESKTOP - iFast Desktop (French Customizations)
// 
//    Rev 1.13   Nov 19 2011 01:43:44   wp040168
// P0186484/FN06 - DESKTOP - iFast Desktop (French Customizations)
// 
//    Rev 1.12   Oct 27 2010 10:24:34   jankovii
// IN 2305655 - FN03 QESI - RESP Beneficiary Allocation History Button
// 
//    Rev 1.11   Aug 06 2010 13:54:58   jankovii
// PET165541 FN03 SOC14 & SOC6
// 
//    Rev 1.10   Jun 21 2010 17:20:06   popescu
// Incident 2162449 - REL Pre99 Bene Alloc button grayed out on RESP Transaction History Screen
 * 
 * 
 *
 */

