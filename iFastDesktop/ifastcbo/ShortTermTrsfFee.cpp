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
// ^FILE   : ShortTermTrsfFee.cpp
// ^AUTHOR : Serban Popescu
// ^DATE   : November 2004
//
// ^CLASS    : ShortTermTrsfFee
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "shorttermtrsffee.hpp"

#include "funddetail.hpp"
#include "fundtolist.hpp"
#include "mfaccount.hpp"
#include "trade.hpp"
#include "tradefundalloc.hpp"
#include "tradefundalloclist.hpp"

namespace
{
   // Trace literals
   const I_CHAR *  CLASSNAME  = I_("ShortTermTrsfFee");
}

namespace ifds
{
//mgmtco options
   extern CLASS_IMPORT const BFTextFieldId ShortTermTRFeeElig;
//fee fields
   extern CLASS_IMPORT const BFTextFieldId TransType;
   extern CLASS_IMPORT const BFTextFieldId FeeCharge;
//account num fields
   extern CLASS_IMPORT const BFTextFieldId ChargeSTTRFee;
//fund fields
   extern CLASS_IMPORT const BFTextFieldId ShortTermFee;
}

namespace CND
{  // Conditions used
   extern long const WARN_CHARGE_SHORT_TERM_TRANSFER_FEE_ALLOWED;
}

namespace FEES
{
   extern const I_CHAR * SHORT_TERM_TRANSFER;
}

namespace TRADETYPE
{
   extern CLASS_IMPORT I_CHAR * const EXCHANGE_LIKE;
}

//******************************************************************************
ShortTermTrsfFee::ShortTermTrsfFee (BFAbstractCBO &parent) : TransFeeCharge (parent, FEES::SHORT_TERM_TRANSFER)
{
   TRACE_CONSTRUCTOR (CLASSNAME, NULL_STRING);
}

//******************************************************************************
ShortTermTrsfFee::~ShortTermTrsfFee()
{
   TRACE_DESTRUCTOR (CLASSNAME);
}

//******************************************************************************
bool ShortTermTrsfFee::isSystemApplicable (const BFDataGroupId &idDataGroup)
{
   DString shortTermTRFeeElig;

   getWorkSession ().getOption ( ifds::ShortTermTRFeeElig, 
                                 shortTermTRFeeElig, 
                                 BF::HOST, 
                                 false
                               );
   return shortTermTRFeeElig == Y;
}

//******************************************************************************
bool ShortTermTrsfFee::isContextApplicable (const BFDataGroupId &idDataGroup)
{
   if (TransFee::isContextApplicable(idDataGroup))
   {
	   DString transType,
		   toFund,
		   toClass;

	   getContext().getField (ifds::TransType, transType, idDataGroup, false);
	   getContext().getField (ifds::ToFund, toFund, idDataGroup, false);
	   getContext().getField (ifds::ToClass, toClass, idDataGroup, false);
	   return DSTCommonFunctions::codeInList (transType, TRADETYPE::EXCHANGE_LIKE) &&
			  ((hasFeeParams (idDataGroup) && !toFund.empty () && !toClass.empty()) ||
			  (toFund.empty () && toClass.empty())) && //allocated exchanges/transfers
			  isFeeApplicableForFunds (idDataGroup);
   }
   return false;
}

//******************************************************************************
bool ShortTermTrsfFee::hasContextChanged (const BFDataGroupId &idDataGroup)
{
//if any of the fee params request parameters changed
   return hasFeeParamsContextChanged (idDataGroup) ||
          hasFieldContextChanged (ifds::ToFund, idDataGroup) ||
          hasFieldContextChanged (ifds::ToClass, idDataGroup);
}

//******************************************************************************
SEVERITY ShortTermTrsfFee::doValidateField ( const BFFieldId &idField, 
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
         if (strValue == N)
         {
//should raise the warning so user knows, that the sttr can be charged
            ADDCONDITIONFROMFILE (CND::WARN_CHARGE_SHORT_TERM_TRANSFER_FEE_ALLOWED) ;
         }
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY ShortTermTrsfFee::setFeeDefault (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("setFeeDefault")
                         );
   DString accountNum;
   MFAccount *pMFAccount = NULL;

   getContext().getField (ifds::AccountNum, accountNum, idDataGroup, false);
   if ( getWorkSession ().getMFAccount ( idDataGroup, 
                                         accountNum, 
                                         pMFAccount
                                       ) <= WARNING && 
        pMFAccount
      )
   {
      DString chargeSTTRFee;

      pMFAccount->getField (ifds::ChargeSTTRFee, chargeSTTRFee, idDataGroup, false);
      if (chargeSTTRFee.empty())
      {
         chargeSTTRFee = N;
      }
      setFieldNoValidate ( ifds::FeeCharge, chargeSTTRFee, idDataGroup, false, 
                           false, true, false
                         );
      setFieldNoValidate ( ifds::FeeRate, charge2Rate (chargeSTTRFee), idDataGroup, false, 
                           false, true, false
                        );
      setFieldNoValidate ( ifds::OrigFeeRate, charge2Rate (chargeSTTRFee), idDataGroup, false, 
                           false, true, false
                         );
}
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
bool ShortTermTrsfFee::isFeeApplicableForFunds (const BFDataGroupId &idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION,
                           CLASSNAME,
                           I_("isFeeApplicableForFunds")
                         );
	
	bool bApplicable = true;
	
	DString dstrSTTRFee,
      dstrFromFund, 
      dstrFromClass, 
      dstrFundTo, 
      dstrClassTo;               

   getContext().getField (ifds::FromFund,  dstrFromFund,  idDataGroup);
	getContext().getField (ifds::FromClass, dstrFromClass, idDataGroup);
	getContext().getField (ifds::ToFund,    dstrFundTo, idDataGroup);
	getContext().getField (ifds::ToClass,   dstrClassTo, idDataGroup);
	dstrFromFund.strip().upperCase();
	dstrFromClass.strip().upperCase();
	dstrFundTo.strip().upperCase();
	dstrClassTo.strip().upperCase();

	if ( !dstrFromFund.empty() && 
		  !dstrFromClass.empty()
      )
	{
		FundToList fundToList( *this );
		if ( !dstrFundTo.empty() &&
           !dstrClassTo.empty() 
         )
      {
         dstrSTTRFee = fundToList.getShortTermFee ( dstrFromFund, 
                                                    dstrFromClass,
                                                    dstrFundTo,
                                                    dstrClassTo 
                                                  );
	      // If 0, Not Applicable
	      if (I_( "N" ) == dstrSTTRFee)
         {
		      bApplicable = false;
         }         
		}
      else if ( dstrFundTo.empty() &&
		          dstrClassTo.empty()
               ) //allocated trade
      {
	      assert (getParent() && getParent()->getParent());

         Trade *pTrade = dynamic_cast <Trade*> (getParent()->getParent());
         TradeFundAllocList *pFundAllocationList = NULL;
	      if ( pTrade->getFundAllocationList (pFundAllocationList, idDataGroup) <= WARNING &&
		         pFundAllocationList
            )
	      {
		      BFObjIter iter ( *pFundAllocationList, 
							         idDataGroup, 
							         false, 
                              BFObjIter::ITERTYPE::NON_DELETED 
                           );
		      iter.begin();
		      int iAllocNum = iter.getNumberOfItemsInList();
		      if (iAllocNum > 1)
		      {																					
			      while (!iter.end())
			      {
				      TradeFundAlloc *pTradeFundAlloc = dynamic_cast< TradeFundAlloc *>(iter.getObject());
				      if ( NULL != pTradeFundAlloc )
				      {
					         DString dstrFundTo, dstrClassTo;
                        pTradeFundAlloc->getField (ifds::FundCode,  dstrFundTo,  idDataGroup);
					         pTradeFundAlloc->getField (ifds::ClassCode, dstrClassTo, idDataGroup);
                        dstrSTTRFee = fundToList.getShortTermFee ( dstrFromFund, 
                                                                   dstrFromClass,
                                                                   dstrFundTo,
                                                                   dstrClassTo 
                                                                 );
                        if ( I_( "N" ) == dstrSTTRFee ) //if one doesn't apply break
                        {
	                        bApplicable = false;
                           break;
                        }					               
                     }
                     ++iter;
               }
            }
         }
      }      			
   }
	return bApplicable;
}

//******************************************************************************
SEVERITY ShortTermTrsfFee::restore ( BFCBO &rpParent, 
													const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("restore"));
   DString chargeSTTRFee;

   rpParent.getField (ifds::ChargeERSTTRFee, chargeSTTRFee, idDataGroup);

   setFieldNoValidate ( ifds::FeeCharge, chargeSTTRFee, idDataGroup, false, 
                        false, true, false
                        );
   setFieldNoValidate ( ifds::FeeRate, charge2Rate (chargeSTTRFee), idDataGroup, false, 
                        false, true, false
                     );
   setFieldNoValidate ( ifds::OrigFeeRate, charge2Rate (chargeSTTRFee), idDataGroup, false, 
                        false, true, false
                         );

   return GETCURRENTHIGHESTSEVERITY();
}


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/ShortTermTrsfFee.cpp-arc  $
// 
//    Rev 1.10   Jan 13 2006 17:06:32   AGUILAAM
// IN 518397 - for rebook of trade that's not entered thru Desktop, get ChargeERSTTRFee from original trade instead of TransFee (it does not exist in this case) 
// 
//    Rev 1.9   Mar 13 2005 17:39:32   popescu
// PET 1117/56, fixed availability of ER and STTR fees
// 
//    Rev 1.8   Dec 08 2004 22:08:16   popescu
// PET 1117/06, more fees
// 
//    Rev 1.7   Nov 26 2004 18:01:48   popescu
// PET 1117/06, fixed typo
// 
//    Rev 1.6   Nov 24 2004 14:14:22   popescu
// PET 1117/06, fixed typo
// 
//    Rev 1.5   Nov 18 2004 14:57:12   YINGBAOL
// PET1117: performance tunning
// 
//    Rev 1.4   Nov 17 2004 16:15:28   popescu
// PET 1117/06, Trade processing fees
// 
//    Rev 1.3   Nov 15 2004 16:23:32   popescu
// PET 1117/06, more synch to .NET changes
// 
//    Rev 1.1   Nov 09 2004 16:50:40   popescu
// PET 1117/06, Trade processing
// 
//    Rev 1.0   Nov 05 2004 21:31:02   popescu
// Initial revision.
// 
//    Rev 1.1   Nov 04 2004 17:37:00   popescu
// PET 1117/06, Trade processing
// 
//    Rev 1.0   Nov 04 2004 11:03:26   popescu
// Initial revision.
// 
 */