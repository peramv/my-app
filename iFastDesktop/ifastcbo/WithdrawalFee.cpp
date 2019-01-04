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
//    Copyright 1999 by DST Canada Inc.
//
//
//******************************************************************************
//
// ^FILE   : WithdrawalFee.cpp
// ^AUTHOR : Serban Popescu
// ^DATE   : November 2004
//
// ^CLASS    : WithdrawalFee
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "withdrawalfee.hpp"

#include "errmsgruleslist.hpp"
#include "mgmtco.hpp"
#include "mfaccount.hpp"
#include "pendingtradedetails.hpp"
#include "trade.hpp"
#include "tradeacctalloc.hpp"
#include "tradeacctalloclist.hpp"
#include "tradefundalloc.hpp"
#include "tradefundalloclist.hpp"
#include "redcodebytaxtype.hpp"
#include "redcodebytaxtypelist.hpp"
#include "taxtyperule.hpp"
#include "taxtyperulelist.hpp"

namespace
{
   // Trace literals
   const I_CHAR *  CLASSNAME  = I_("WithdrawalFee");
}

namespace ifds
{
//mgmtco options
   extern CLASS_IMPORT const BFTextFieldId EarlyPWFeeElig;
//fee fields
   extern CLASS_IMPORT const BFTextFieldId TransType;
   extern CLASS_IMPORT const BFTextFieldId FeeCharge;
//account num fields
   extern CLASS_IMPORT const BFTextFieldId ChargeERFee;
   extern CLASS_IMPORT const BFTextFieldId TaxType;
   extern CLASS_IMPORT const BFIntegerFieldId WDFeeDefn;
}

namespace CND
{  // Conditions used
   extern const long ERR_REDEMPTION_FEE_SETUP_MISSING;
}

namespace FEES
{
   extern const I_CHAR * WITHDRAWAL;
}

namespace TRADETYPE
{
   extern CLASS_IMPORT I_CHAR * const REDEMPTION;
   extern CLASS_IMPORT I_CHAR * const ADMIN_FEE;
}

namespace IFASTERR
{
   // maximum payout amount is exceeded
   extern CLASS_IMPORT I_CHAR * const MISSING_REDEMPTION_FEE_SETUP;
}

namespace UAF
{
   extern CLASS_IMPORT I_CHAR * const CHARGE_WD_FEE;
}

//******************************************************************************
WithdrawalFee::WithdrawalFee (BFAbstractCBO &parent) : TransFeeCharge (parent, FEES::WITHDRAWAL)
{
   TRACE_CONSTRUCTOR (CLASSNAME, NULL_STRING);
}

//******************************************************************************
WithdrawalFee::~WithdrawalFee()
{
   TRACE_DESTRUCTOR (CLASSNAME);
}

//******************************************************************************
bool WithdrawalFee::hasContextChanged (const BFDataGroupId &idDataGroup)
{
//fee needs to be refreshed if red code changed and fund change
   return hasFieldContextChanged (ifds::RedCode, idDataGroup) ||
          hasFeeParamsContextChanged (idDataGroup);
}

//******************************************************************************
bool WithdrawalFee::isSystemApplicable (const BFDataGroupId &idDataGroup)
{
   return getWorkSession().hasUpdatePermission (UAF::CHARGE_WD_FEE);
}

//******************************************************************************
bool WithdrawalFee::isContextApplicable (const BFDataGroupId &idDataGroup)
{
   if (TransFee::isContextApplicable(idDataGroup))
   {
	   DString transType;

	   getContext().getField (ifds::TransType, transType, idDataGroup, false);
	   return transType == TRADETYPE::REDEMPTION &&
			  isApplicableForRedCode (idDataGroup) &&
			  withdrawalFeeExists (idDataGroup) ||
			  !shouldIgnoreSetup (idDataGroup);
   }
   return false;
}

//******************************************************************************
SEVERITY WithdrawalFee::setFeeDefault (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("setFeeDefaults")
                         );
//always the default is yes   
   setFieldNoValidate ( ifds::FeeCharge, Y, idDataGroup, false, 
                        false, true, false
                      );
   setFieldNoValidate ( ifds::FeeRate, charge2Rate (DString (Y)), idDataGroup, false, 
                        false, true, false
                     );
   setFieldNoValidate ( ifds::OrigFeeRate, charge2Rate (DString (Y)), idDataGroup, false, 
                        false, true, false
                        );
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY WithdrawalFee::doValidateField ( const BFFieldId &idField, 
                                          const DString &strValue, 
                                          const BFDataGroupId &idDataGroup
                                        )
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("doValidateField")
                         );
   if (TransFeeCharge::doValidateField (idField, strValue, idDataGroup) <= WARNING)
   {
      if (idField == ifds::FeeCharge)
      {
         if (strValue == Y)
         {
            if (!withdrawalFeeExists (idDataGroup))
            {
               getErrMsg ( IFASTERR::MISSING_REDEMPTION_FEE_SETUP, 
                           CND::ERR_REDEMPTION_FEE_SETUP_MISSING,
                           0, 
                           idDataGroup
                         );
            }
         }
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
bool WithdrawalFee::isApplicableForRedCode ( const BFDataGroupId &idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("isApplicableForRedCode") 
                         );
	bool bIsApplicable = false;
   DString accountNum,
      redCode;
	
   getContext().getField (ifds::AccountNum, accountNum, idDataGroup);
   getContext().getField (ifds::RedCode, redCode, idDataGroup);
   MFAccount *pMFAccount = NULL;

   if ( getWorkSession().getMFAccount (idDataGroup, accountNum, pMFAccount) <= WARNING && 
        pMFAccount
      )
   {
      TaxTypeRule *pTaxTypeRule = NULL;
	  if ( pMFAccount->getTaxTypeRule( pTaxTypeRule, idDataGroup ) <= WARNING && pTaxTypeRule )
	  {
         RedCodeByTaxTypeList *pRedCodeByTaxTypeList = NULL;

		 pTaxTypeRule->getRedCodeList (pRedCodeByTaxTypeList, idDataGroup);
         if (pRedCodeByTaxTypeList)
		 {
			 RedCodeByTaxType *pRedByTaxType = NULL;
            
             if ( pRedCodeByTaxTypeList->getRedCodeByTaxType (redCode, pRedByTaxType, idDataGroup) &&
			      pRedByTaxType
                )
             {                  
			    DString wdFeeDefn;

                pRedByTaxType->getField (ifds::WDFeeDefn, wdFeeDefn, idDataGroup);
                wdFeeDefn.strip();
			    bIsApplicable = I_("0") != wdFeeDefn;
            }
         }
      }
   }
   return bIsApplicable;
}

//******************************************************************************
bool WithdrawalFee::withdrawalFeeExists (const BFDataGroupId &idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("withdrawalFeeExists") 
                         );

	bool bFeeExists = false;
   DString fundCode,
      classCode;

   getContext().getField (ifds::FromFund, fundCode, idDataGroup, false);
   getContext().getField (ifds::FromClass, classCode, idDataGroup, false);
	if (!fundCode.stripAll().empty() && !classCode.stripAll().empty())
	{
      bFeeExists = hasFeeParams (idDataGroup);
	}
	else  // is it an allocated Trade?
	{
		assert (getParent() && getParent()->getParent());

      TradeFundAllocList *pFundAllocationList = NULL;
      Trade *pTrade = dynamic_cast <Trade*> (getParent()->getParent());
      bool bSearchForTradeFundAlloc = false;

      if (pTrade) 
      {
         bSearchForTradeFundAlloc = pTrade->getFundAllocationList (pFundAllocationList, idDataGroup) <= WARNING &&
                                    pFundAllocationList;
      }
      else //maybe parent is a pending trade
      {
         PendingTradeDetails *pPendingTradeDetails = dynamic_cast <PendingTradeDetails*> (getParent()->getParent());
         if (pPendingTradeDetails)
         {
            DString accountNum;

            getContext().getField (ifds::AccountNum, accountNum, idDataGroup, false);
            TradeAcctAllocList *pAccountAllocationList = NULL;
            if ( pPendingTradeDetails->getAccountAllocationList (pAccountAllocationList, idDataGroup, accountNum) <= WARNING && 
                 pAccountAllocationList)
            {
               TradeAcctAlloc *pAccountAllocation = NULL;

               if ( pAccountAllocationList->getAccountAllocation (accountNum, pAccountAllocation, idDataGroup) <= WARNING && 
                    pAccountAllocation)
               {
                  bSearchForTradeFundAlloc = 
                        pAccountAllocation->getFundAllocationList (pFundAllocationList, idDataGroup) <= WARNING && 
                        pFundAllocationList;
               }
            }
         }
      }
		if (bSearchForTradeFundAlloc)
		{
			BFObjIter iter ( *pFundAllocationList, 
								  idDataGroup, 
								  false, 
                          BFObjIter::ITERTYPE::NON_DELETED);
			iter.begin();
			int iAllocNum = iter.getNumberOfItemsInList();
			if (iAllocNum > 1)
			{																					
				while (!iter.end())
				{
					TradeFundAlloc *pTradeFundAlloc = dynamic_cast< TradeFundAlloc *>(iter.getObject());
					if ( NULL != pTradeFundAlloc )
					{
                  pTradeFundAlloc->getField (ifds::FundCode,  fundCode,  idDataGroup);
						pTradeFundAlloc->getField (ifds::ClassCode, classCode, idDataGroup);

						bFeeExists = hasFeeParams (fundCode, classCode, idDataGroup);
                  if (!bFeeExists)
                  {
                     break; //one fund does not have fee params, break, fee not applicable
                  }
					}
					++iter;
				}
			}
		}
   }
	return bFeeExists;
}

//******************************************************************************
bool WithdrawalFee::shouldIgnoreSetup (const BFDataGroupId &idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("shouldIgnoreSetup") 
                         );
	
   bool bShouldIgnore = false;
   ErrMsgRulesList* pErrMsgRulesList = NULL;
	
   if ( getMgmtCo().getErrMsgRulesList( pErrMsgRulesList ) <= WARNING &&
		  NULL != pErrMsgRulesList 
      )
	{
		DString dstrErrValue;
		
      pErrMsgRulesList->getEWIValue ( IFASTERR::MISSING_REDEMPTION_FEE_SETUP, 
                                      idDataGroup, 
                                      dstrErrValue
                                    );
		bShouldIgnore = dstrErrValue.upperCase() == I_("I");
   }
   return bShouldIgnore;
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/WithdrawalFee.cpp-arc  $
// 
//    Rev 1.6   15 Apr 2008 12:13:36   kovacsro
// PET2255 FN47 - New Ontario LIF
// 
//    Rev 1.5   Sep 02 2005 13:52:36   popescu
// PET 1117/56 - fixed crash in pending trade mode,if user clicks on the 'Fees' button of allocated redemption
// 
//    Rev 1.4   Dec 08 2004 22:08:34   popescu
// PET 1117/06, more fees
// 
//    Rev 1.3   Nov 17 2004 16:16:04   popescu
// PET 1117/06, Trade processing fees
// 
//    Rev 1.2   Nov 15 2004 16:24:28   popescu
// PET 1117/06, more synch to .NET changes
// 
//    Rev 1.1   Nov 15 2004 14:50:10   popescu
// PET 1117/06, .NET synch changes
// 
//    Rev 1.0   Nov 15 2004 13:40:12   popescu
// Initial revision.
// 
//    Rev 1.2   Nov 09 2004 16:49:06   popescu
// PET 1117/06, Trade processing
// 
//    Rev 1.1   Nov 06 2004 00:40:28   popescu
// PET 1117/06, synch changes
// 
//    Rev 1.0   Nov 05 2004 17:06:00   popescu
// Initial Revision
// 
//    Rev 1.1   Nov 04 2004 17:37:00   popescu
// PET 1117/06, Trade processing
// 
//    Rev 1.0   Nov 04 2004 11:03:26   popescu
// Initial revision.
// 
 */