//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by International Financial Data Services,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2004 by International Financial
//
//******************************************************************************
//
// ^FILE   : TransactionHistoryDeductDetailDlg.cpp
// ^AUTHOR : Monica Vadeanu
// ^DATE   : Jan 2004
//
// ----------------------------------------------------------
//
// ^CLASS    : TransactionHistoryDeductDetailDlg
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :  This is the code for a list selection dialog

//******************************************************************************
#include "stdafx.h"


#ifndef IFASTGUI_H
   #include "MFDSTC.h"
#endif

#include <bfproc\AbstractProcess.hpp>
#include "TransactionHistoryDeductDetailDlg.h"
#include "ifastbp\TransHistoryProcessIncludes.h"

#include <ifastcbo\DSTCommonFunction.hpp>

extern CLASS_IMPORT const I_CHAR* CMD_GUI_TRANSACTION_HISTORY_DEDUCT_DETAIL;

#include <bfproc\concretedialogcreator.hpp>
static ConcreteDialogCreator< TransactionHistoryDeductDetailDlg > dlgCreator( CMD_GUI_TRANSACTION_HISTORY_DEDUCT_DETAIL );

#ifdef _DEBUG
   #define new DEBUG_NEW
   #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

namespace
{
   const I_CHAR * const CLASSNAME = I_( "TransactionHistoryDeductDetailDlg" );
}

namespace ifds
{ 
	extern CLASS_IMPORT const BFTextFieldId TransHistDeductDetailHeadingSet;
   extern CLASS_IMPORT const BFTextFieldId TransFeesListHeadingSet;
   extern CLASS_IMPORT const BFTextFieldId FeeCharge;
}

namespace CND
{  // Conditions used
   extern const long GUI_ERR_UNKNOWN_EXCEPTION;
}

namespace MFCAN_IP_PARAM
{
   extern CLASS_IMPORT const I_CHAR * const CALLER;
}

namespace FEES
{
   extern CLASS_IMPORT const I_CHAR * SHORT_TERM_TRANSFER;
   extern CLASS_IMPORT const I_CHAR * EARLY_REDEMPTION;
}

class LVFeesData : public IFDSListCtrlRowDataBase
{
public:
   virtual ~LVFeesData() {}
   DString TransFeeCode_;
   DString FeeType_;
   DString FeeRate_;
   DString FeeCharge_;
   DString Currency_;
   DString ChargeOption_;
   DString TradeFeeOption_;
   DString OrigFeeType_;
   DString OrigFeeRate_;
   DString IsChargeFee_;

   virtual void update(BaseDlg* pDlg, IFDSListCtrl* pCtrl, const DString* pKey)
   {
      pDlg->getParent()->getField( pDlg, IFASTBP_PROC::TRANS_FEE_LIST, ifds::TransFeeCode, TransFeeCode_ );
      TransFeeCode_.strip();
      pDlg->getParent()->getField( pDlg, IFASTBP_PROC::TRANS_FEE_LIST, ifds::FeeType, FeeType_ );
      FeeType_.strip();
      pDlg->getParent()->getField( pDlg, IFASTBP_PROC::TRANS_FEE_LIST, ifds::FeeRate, FeeRate_ );
      FeeRate_.strip();            
      pDlg->getParent()->getField( pDlg, IFASTBP_PROC::TRANS_FEE_LIST, ifds::FeeCharge, FeeCharge_ );
      FeeCharge_.strip();            
      pDlg->getParent()->getField( pDlg, IFASTBP_PROC::TRANS_FEE_LIST, ifds::Currency, Currency_ );
      Currency_.strip();            
      pDlg->getParent()->getField( pDlg, IFASTBP_PROC::TRANS_FEE_LIST, ifds::ChargeOption, ChargeOption_ );
      ChargeOption_.strip();            
      pDlg->getParent()->getField( pDlg, IFASTBP_PROC::TRANS_FEE_LIST, ifds::TradeFeeOption, TradeFeeOption_ );
      TradeFeeOption_.strip();            
      pDlg->getParent()->getField( pDlg, IFASTBP_PROC::TRANS_FEE_LIST, ifds::OrigFeeType, OrigFeeType_ );
      OrigFeeType_.strip();            
      pDlg->getParent()->getField( pDlg, IFASTBP_PROC::TRANS_FEE_LIST, ifds::OrigFeeRate, OrigFeeRate_ );
      OrigFeeRate_.strip();
      pDlg->getParent()->getField( pDlg, IFASTBP_PROC::TRANS_FEE_LIST, IsChargeTransFee, IsChargeFee_ );
      IsChargeFee_.strip();
   }
};

class LVFeesAdapter : public IFDSListCtrlAdapter< LVFeesData >
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
         result = ( IFDSListBase::getColumnLVItem(lParam1, iSortColumn - 1)->iImage - 
                    IFDSListBase::getColumnLVItem(lParam2, iSortColumn - 1)->iImage);
      } 
      else if (NULL == pFieldId) 
      {
         return (0);
      } 
		else if (*pFieldId == ifds::TransFeeCode) 
      {
			int iTransFeeCode1 = pData1->TransFeeCode_.asInteger();
			int iTransFeeCode2 = pData2->TransFeeCode_.asInteger();
			if ( iTransFeeCode1 > iTransFeeCode2 )
				result = 1;
			else if ( iTransFeeCode1 < iTransFeeCode2 )
				result = -1;
      } 
      else if (*pFieldId == ifds::FeeRate) 
      {         
         if (pData1->IsChargeFee_ == I_("Y") && pData2->IsChargeFee_ == I_("Y"))
         {
            result = i_strcmp(pData1->FeeCharge_.c_str(), pData2->FeeCharge_.c_str());
         }
         else if (pData1->IsChargeFee_ == I_("N") && pData2->IsChargeFee_ == I_("N"))
         {
			   double dblFeeRate1 = DSTCommonFunctions::convertToDouble ( pData1->FeeRate_.c_str() );
			   double dblFeeRate2 = DSTCommonFunctions::convertToDouble ( pData2->FeeRate_.c_str() );         			
			   if ( dblFeeRate1 > dblFeeRate2 )
				   result = 1;
			   else if ( dblFeeRate1 < dblFeeRate2 )
				   result = -1;
         }
         else if (pData1->IsChargeFee_ == I_("Y") && pData2->IsChargeFee_ == I_("N"))
         {
            result = i_strcmp (pData1->FeeCharge_.c_str(), pData2->FeeRate_.c_str()); //use string comp
         }
         else if (pData1->IsChargeFee_ == I_("N") && pData2->IsChargeFee_ == I_("Y"))
         {
            result = i_strcmp(pData1->FeeRate_.c_str(), pData2->FeeCharge_.c_str());//use string comp
         }
      }       
		else if (*pFieldId == ifds::FeeType) 
      {
         result = i_strcmp(pData1->FeeType_.c_str(), pData2->FeeType_.c_str());
      } 
		else if (*pFieldId == ifds::Currency) 
      {
         result = i_strcmp(pData1->Currency_.c_str(), pData2->Currency_.c_str());
      } 
		else if (*pFieldId == ifds::ChargeOption) 
      {
         result = i_strcmp(pData1->ChargeOption_.c_str(), pData2->ChargeOption_.c_str());
      } 
		else if (*pFieldId == ifds::TradeFeeOption) 
      {
         result = i_strcmp(pData1->TradeFeeOption_.c_str(), pData2->TradeFeeOption_.c_str());
      } 
		else if (*pFieldId == ifds::OrigFeeType) 
      {
         result = i_strcmp(pData1->OrigFeeType_.c_str(), pData2->OrigFeeType_.c_str());
      } 
      else if (*pFieldId == ifds::OrigFeeRate) 
      {         
			double dblFeeRate1 = DSTCommonFunctions::convertToDouble ( pData1->OrigFeeRate_.c_str() );
			double dblFeeRate2 = DSTCommonFunctions::convertToDouble ( pData2->OrigFeeRate_.c_str() );         			
			if ( dblFeeRate1 > dblFeeRate2 )
				result = 1;
			else if ( dblFeeRate1 < dblFeeRate2 )
				result = -1;
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
         else if (*pFieldId == ifds::TransFeeCode) 
         {
            pDispInfo->item.pszText = (I_CHAR*)pData->TransFeeCode_.c_str();
         } 
         else if (*pFieldId == ifds::FeeRate)
         {
            if (pData->IsChargeFee_ == I_("Y"))
            {
               pDispInfo->item.pszText = (I_CHAR*)pData->FeeCharge_.c_str();
            }
            else if (pData->IsChargeFee_ == I_("N"))
            {
               pDispInfo->item.pszText = (I_CHAR*)pData->FeeRate_.c_str();
            }
         } 
         else if (*pFieldId == ifds::FeeType)
         {
            pDispInfo->item.pszText = (I_CHAR*)pData->FeeType_.c_str();
         }          
         else if (*pFieldId == ifds::OrigFeeRate)
         {
            pDispInfo->item.pszText = (I_CHAR*)pData->OrigFeeRate_.c_str();
         } 
         else if (*pFieldId == ifds::OrigFeeType)
         {
            pDispInfo->item.pszText = (I_CHAR*)pData->OrigFeeType_.c_str();
         }          
         else if (*pFieldId == ifds::TradeFeeOption)
         {
            pDispInfo->item.pszText = (I_CHAR*)pData->TradeFeeOption_.c_str();
         } 
         else if (*pFieldId == ifds::ChargeOption)
         {
            pDispInfo->item.pszText = (I_CHAR*)pData->ChargeOption_.c_str();
         }          
         else if (*pFieldId == ifds::Currency)
         {
            pDispInfo->item.pszText = (I_CHAR*)pData->Currency_.c_str();
         }          
         return (1);
      }
      return (0);
   }
};

class LVDeductionsDetailData : public IFDSListCtrlRowDataBase
{
public:
   virtual ~LVDeductionsDetailData() {}
   DString DeductCode_;
   DString DeductDesc_;
   DString DeductAmt_;
   DString DeductCategory_;
   DString FeeRate_;   

   virtual void update(BaseDlg* pDlg, IFDSListCtrl* pCtrl, const DString* pKey)
   {
      pDlg->getParent()->getField( pDlg, IFASTBP_PROC::DEDUCTION_LIST, ifds::DeductCode, DeductCode_ );
      DeductCode_.strip();
      pDlg->getParent()->getField( pDlg, IFASTBP_PROC::DEDUCTION_LIST, ifds::DeductDesc, DeductDesc_ );
      DeductDesc_.strip();
      pDlg->getParent()->getField( pDlg, IFASTBP_PROC::DEDUCTION_LIST, ifds::DeductAmt, DeductAmt_ );
      DeductAmt_.strip();
      pDlg->getParent()->getField( pDlg, IFASTBP_PROC::DEDUCTION_LIST, ifds::DeductCategory, DeductCategory_ );
      DeductCategory_.strip();
      pDlg->getParent()->getField( pDlg, IFASTBP_PROC::DEDUCTION_LIST, ifds::FeeRate, FeeRate_ );
      FeeRate_.strip();            
   }
};

class LVDeductionsDetailAdapter : public IFDSListCtrlAdapter< LVDeductionsDetailData >
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
      else if (*pFieldId == ifds::DeductCode) 
      {         
			int iDeductCode1 = pData1->DeductCode_.asInteger();
			int iDeductCode2 = pData2->DeductCode_.asInteger();
			if ( iDeductCode1 > iDeductCode2 )
				result = 1;
			else if ( iDeductCode1 < iDeductCode2 )
				result = -1;
			// for equal result should be 0
      } 
		else if (*pFieldId == ifds::DeductDesc) 
      {
         result = i_strcmp(pData1->DeductDesc_.c_str(), pData2->DeductDesc_.c_str());
      } 
      else if (*pFieldId == ifds::DeductAmt) 
      {         
			double dblDeductAmt1 = DSTCommonFunctions::convertToDouble ( pData1->DeductAmt_.c_str() );
			double dblDeductAmt2 = DSTCommonFunctions::convertToDouble ( pData2->DeductAmt_.c_str() );         			
			if ( dblDeductAmt1 > dblDeductAmt2 )
				result = 1;
			else if ( dblDeductAmt1 < dblDeductAmt2 )
				result = -1;
			// for equal result will be 0;
      } 
      else if (*pFieldId == ifds::DeductCategory) 
      {
         result = i_strcmp(pData1->DeductCategory_.c_str(), pData2->DeductCategory_.c_str());
      } 
      else if (*pFieldId == ifds::FeeRate) 
      {         
//Incident 288176; change comparison method
         bool pData1IsERSSTR = pData1->DeductCode_ == FEES::SHORT_TERM_TRANSFER ||
                               pData1->DeductCode_ == FEES::EARLY_REDEMPTION,
              pData2IsERSSTR = pData2->DeductCode_ == FEES::SHORT_TERM_TRANSFER ||
                               pData2->DeductCode_ == FEES::EARLY_REDEMPTION;
         if ( (pData1IsERSSTR && pData2IsERSSTR) ||
              (pData1IsERSSTR && !pData2IsERSSTR) ||
              (!pData1IsERSSTR && pData2IsERSSTR))
         {
            result = i_strcmp(pData1->FeeRate_.c_str(), pData2->FeeRate_.c_str());
         }
         else if (!pData1IsERSSTR && !pData2IsERSSTR)
         {
			   //keep what was before
            double dblFeeRate1 = DSTCommonFunctions::convertToDouble ( pData1->FeeRate_.c_str() );
			   double dblFeeRate2 = DSTCommonFunctions::convertToDouble ( pData2->FeeRate_.c_str() );         			
			   if ( dblFeeRate1 > dblFeeRate2 )
				   result = 1;
			   else if ( dblFeeRate1 < dblFeeRate2 )
				   result = -1;
			   // for equal result will be 0;
         }
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
         else if (*pFieldId == ifds::DeductCode) 
         {
            pDispInfo->item.pszText = (I_CHAR*)pData->DeductCode_.c_str();
         } 
         else if (*pFieldId == ifds::DeductDesc) 
         {
            pDispInfo->item.pszText = (I_CHAR*)pData->DeductDesc_.c_str();
         } 
         else if (*pFieldId == ifds::DeductAmt) 
         {
            pDispInfo->item.pszText = (I_CHAR*)pData->DeductAmt_.c_str();
         } 
         else if (*pFieldId == ifds::DeductCategory)
         {
            pDispInfo->item.pszText = (I_CHAR*)pData->DeductCategory_.c_str();
         } 
         else if (*pFieldId == ifds::FeeRate)
         {
//Incident 288176; TPS cannot provide STTR/ER %, so Desktop will just display unavailable
            if ( pData->DeductCode_ == FEES::SHORT_TERM_TRANSFER ||
                 pData->DeductCode_ == FEES::EARLY_REDEMPTION)
            {               
               pDispInfo->item.pszText = I_("N/A");
            }
            else
            {
               pDispInfo->item.pszText = (I_CHAR*)pData->FeeRate_.c_str();
            }
         }          
         return (1);
      }
      return (0);
   }
};

//*****************************************************************************
// Public methods
//*****************************************************************************
TransactionHistoryDeductDetailDlg::TransactionHistoryDeductDetailDlg( 
      CWnd* pParent, GenericInterfaceContainer* pGIC, 
      GenericInterface* pGIParent, 
      const Command& rCommand )
: BaseMainDlg( TransactionHistoryDeductDetailDlg::IDD, pParent, pGIC, pGIParent, rCommand, CLASSNAME ),
m_caller (NULL_STRING)
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   //{{AFX_DATA_INIT(TransactionHistoryDeductDetailDlg)
   //}}AFX_DATA_INIT
}

//*****************************************************************************
void TransactionHistoryDeductDetailDlg::DoDataExchange( CDataExchange* pDX )
{
   BaseMainDlg::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(TransactionHistoryDeductDetailDlg)
   //}}AFX_DATA_MAP

}

//*****************************************************************************
SEVERITY TransactionHistoryDeductDetailDlg::doInit()
{
   TRACE_METHOD( CLASSNAME, DOINIT );
   getParameter (MFCAN_IP_PARAM::CALLER, m_caller);  		
   return NO_CONDITION;
}

//*****************************************************************************
BEGIN_MESSAGE_MAP( TransactionHistoryDeductDetailDlg, BaseMainDlg )
//{{AFX_MSG_MAP(TransactionHistoryDeductDetailDlg)

//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//*****************************************************************************
// Message handlers
//*****************************************************************************
BOOL TransactionHistoryDeductDetailDlg::OnInitDialog() 
{
   TRACE_METHOD( CLASSNAME, ONINITDIALOG );

   BaseMainDlg::OnInitDialog();

   return(TRUE);
}

//*****************************************************************************
void TransactionHistoryDeductDetailDlg::OnPostInitDialog()
{
   TRACE_METHOD( CLASSNAME, ONPOSTINITDIALOG ); 
	
	if (m_caller == I_("DeductDetail"))
   {
      IFDSListCtrl* pDeductionDetailsListCtrl = 
         new IFDSAdaptedListCtrl< LVDeductionsDetailAdapter >( this, 
		                                                         CLASSNAME, 
                                                               IDC_LV_DEDUCTION_DETAILS, 
																				   0, 
																				   0, 
																				   true, 
																				   true );

      AddIFDSListControl( pDeductionDetailsListCtrl, 
							   I_( "Transaction History Deduct Details" ), 
							   IFASTBP_PROC::DEDUCTION_LIST, 
                        ifds::TransHistDeductDetailHeadingSet );
   }
   else if (m_caller == I_("Fees"))
   {
      IFDSListCtrl* pDeductionDetailsListCtrl = 
         new IFDSAdaptedListCtrl< LVFeesAdapter >( this, 
                                                   CLASSNAME, 
                                                   IDC_LV_DEDUCTION_DETAILS, 
																	0, 
																	0, 
																	true, 
																	true );

	  AddIFDSListControl( pDeductionDetailsListCtrl, 
							     I_( "Pending Trade Fees" ), 
							     IFASTBP_PROC::TRANS_FEE_LIST, 
                          ifds::TransFeesListHeadingSet);
   }

   doRefresh( this, NULL_STRING );
}

//******************************************************************************
bool TransactionHistoryDeductDetailDlg::doRefresh( GenericInterface *rpGICaller, 
   const I_CHAR *szOriginalCommand )
{ 
   TRACE_METHOD( CLASSNAME, DOREFRESH );

	bool bLoadList = false;
   ConnectListToData( IDC_LV_DEDUCTION_DETAILS, true );
   
	// Deduction List
   if (m_caller == I_("DeductDetail"))
   {
      bLoadList = getParent()->getFirstListItemKey( this, IFASTBP_PROC::DEDUCTION_LIST ) != NULL_STRING;
   }
   else if (m_caller == I_("Fees"))
   {
      bLoadList = getParent()->getFirstListItemKey( this, IFASTBP_PROC::TRANS_FEE_LIST ) != NULL_STRING;
   }
   if (bLoadList)
   {
      LoadListControl( IDC_LV_DEDUCTION_DETAILS );
   }
   SetDlgCaption();
   return true;
}

//*************************************************************************
void TransactionHistoryDeductDetailDlg::SetDlgCaption()
{ 	
   DString dstrTransNum;
	DString dstrDlgCaption;
	if (m_caller == I_("DeductDetail"))
   {
      getParent()->getField( this, IFASTBP_PROC::TRANS_LIST, ifds::TransNum, dstrTransNum, false);
	  CString cstrDedDet;
	  cstrDedDet.LoadString(TXT_DED_DET_FOR_TRANS);
	  dstrDlgCaption = DString(cstrDedDet) + dstrTransNum;
   }
   else if (m_caller == I_("Fees"))
   {
      getParent()->getField( this, IFASTBP_PROC::PENDING_LIST, ifds::TransNum, dstrTransNum, false);
	  CString cstrTranFees;
	  cstrTranFees.LoadString(TXT_FEES_FOR_TRANS); 
	   dstrDlgCaption = DString(cstrTranFees) + dstrTransNum;
   }
   SetWindowText( dstrDlgCaption.c_str() );
}

//*************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/TransactionHistoryDeductDetailDlg.cpp-arc  $
// 
//    Rev 1.13   Nov 23 2011 15:19:40   wp040168
// P0186484/FN06 - DESKTOP - iFast Desktop (French Customizations)
// 
//    Rev 1.12   Nov 19 2011 01:39:26   wp040143
// P0186484/FN06 - DESKTOP - iFast Desktop (French Customizations)
// 
//    Rev 1.11   Sep 15 2005 15:15:54   popescu
// Incident#403519 - added CLASSNAME as the fifth parameter to  BaseMainDlg constructor
// 
//    Rev 1.10   May 11 2005 15:45:32   popescu
// Incident#288176 - sorted the sort issue out
// 
//    Rev 1.9   May 11 2005 13:47:02   popescu
// Incident#288176 - display N/A for STTR/ER fee rates, since the rate is not available, due to the fact that TPS does not stamp it.
// 
//    Rev 1.8   Dec 11 2004 13:25:36   popescu
// PET 1117/06, more fixes for banking instr in pending mode.
// 
//    Rev 1.7   Dec 11 2004 11:48:20   popescu
// PET 1117/56 more fixes, pending trade mods
// 
//    Rev 1.6   Dec 09 2004 12:37:58   popescu
// PET 1117/56, more fees work /pending trade
// 
//    Rev 1.5   Dec 07 2004 21:20:50   popescu
// PET 1117/06, pending trades/fees fixes, add-ons
// 
//    Rev 1.4   Feb 12 2004 13:22:14   VADEANUM
// PET859 FN23 - ADL - Check if any item exists before loading the list.
// 
//    Rev 1.3   Feb 11 2004 16:04:32   VADEANUM
// PET859 FN23 - ADL - IFDSListControl implementation for doubles and integers.
// 
//    Rev 1.2   Feb 11 2004 14:30:10   VADEANUM
// PET859 FN23 - ADL - IFDSListControl implementation.
// 
//    Rev 1.1   Feb 04 2004 16:56:14   VADEANUM
// PET 859 FN23 - ADL - Deductions Details.
// 
//    Rev 1.0   Feb 03 2004 16:58:52   VADEANUM
// Initial revision.
// 
*/

