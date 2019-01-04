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
// ^FILE   : TrxnFee.cpp
// ^AUTHOR : Serban Popescu
// ^DATE   : November 2004
//
// ^CLASS    : TrxnFee
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "trxnfee.hpp"

#include "fundmasterlist.hpp"
#include "mgmtco.hpp"
#include "trade.hpp"

namespace
{
   // Trace literals
   const I_CHAR *  CLASSNAME  = I_("TrxnFee");
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId TransType;
}

namespace CND
{  // Conditions used
}

namespace FEES
{
   extern const I_CHAR * PURCHASE_TRXN;
   extern const I_CHAR * REDEMPTION_TRXN;
}

namespace TRADETYPE
{
   extern CLASS_IMPORT I_CHAR * const PURCHASE_LIKE;
   extern CLASS_IMPORT I_CHAR * const REDEMPTION;
   extern CLASS_IMPORT I_CHAR * const HYBRID_REDEMPTION;
   extern CLASS_IMPORT I_CHAR * const INSPECIES_REDEMPTION;
   extern CLASS_IMPORT I_CHAR * const INSP_NON_PRO_RATA_REDEMPTION; 
}

//******************************************************************************
TrxnFee::TrxnFee (BFAbstractCBO &parent, const DString &feeCode) : TransFeeRate (parent, feeCode)
{
   TRACE_CONSTRUCTOR (CLASSNAME, NULL_STRING);
}

//******************************************************************************
TrxnFee::~TrxnFee()
{
   TRACE_DESTRUCTOR (CLASSNAME);
}

//******************************************************************************
void TrxnFee::doInitWithDefaultValues (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("doInitWithDefaultValues"));
   if (canBeInitialized (idDataGroup))
   {
      TransFeeRate::doInitWithDefaultValues (idDataGroup);
   }
}

//******************************************************************************
inline bool TrxnFee::useFeeModelCode ()
{
   return true;
}

//******************************************************************************
bool TrxnFee::isSystemApplicable (const BFDataGroupId &idDataGroup)
{
   return true;
}

//******************************************************************************
bool TrxnFee::isContextApplicable (const BFDataGroupId &idDataGroup)
{
   if (TransFee::isContextApplicable(idDataGroup))
   {
	   DString transType,
		   feeCode;

	   getContext().getField (ifds::TransType, transType, idDataGroup, false);
	   getField (ifds::TransFeeCode, feeCode, idDataGroup, false);
	   return (( DSTCommonFunctions::codeInList (transType, TRADETYPE::PURCHASE_LIKE) &&
			  feeCode == FEES::PURCHASE_TRXN) ||
			  ( (transType == TRADETYPE::REDEMPTION ||
			  transType == TRADETYPE::INSPECIES_REDEMPTION ||
			  transType == TRADETYPE::INSP_NON_PRO_RATA_REDEMPTION ||   
			  transType == TRADETYPE::HYBRID_REDEMPTION) && feeCode == FEES::REDEMPTION_TRXN)) &&
			  isApplicableForFund (idDataGroup) &&
			  hasFeeParams (idDataGroup); //use the fee model code
   }
   return false;
}

//******************************************************************************
bool TrxnFee::hasContextChanged (const BFDataGroupId &idDataGroup)
{
   return hasFeeParamsContextChanged (idDataGroup);
}

//******************************************************************************
bool TrxnFee::isApplicableForFund (const BFDataGroupId &idDataGroup)
{
   bool bIsApplicable = false;
   DString fundCode,
      classCode;
   
   getContext().getField (ifds::FromFund, fundCode, idDataGroup, false);
   getContext().getField (ifds::FromClass, classCode, idDataGroup, false);
   bIsApplicable = !fundCode.empty() && !classCode.empty();
#if 0
   if (!fundCode.empty())
   {
      /*FundMasterList *pFundMasterList;
      if ( getMgmtCo().getFundMasterList (pFundMasterList) <= WARNING && 
           pFundMasterList
         )
      {
         bIsApplicable = pFundMasterList->is3rdPartyFund (fundCode) ||
                         pFundMasterList->isDepotFund (fundCode);
      }*/
	  bIsApplicable = true; //Applicable if there set up at fee parm level
   }
#endif
   return bIsApplicable;
}

//******************************************************************************
SEVERITY TrxnFee::setFeeType (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("setFeeType"));
   TransFeeRate::setFeeType (idDataGroup);
   setFieldReadOnly (ifds::FeeType, idDataGroup, true);
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY TrxnFee::setFeeProperties (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("setFeeProperties"));
   
   TransFeeRate::setFeeProperties (idDataGroup);   
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY TrxnFee::doApplyRelatedChanges ( const BFFieldId &idField, 
                                          const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("doApplyRelatedChanges"));
   if (TransFeeRate::doApplyRelatedChanges (idField, idDataGroup) <= WARNING)
   {
      if (idField == ifds::TradeFeeOption)
      {
//always read only
         setFieldReadOnly (ifds::FeeType, idDataGroup, true);
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/TrxnFee.cpp-arc  $
// 
//    Rev 1.11   Jul 27 2012 08:27:30   wp040132
// P0199891 _FN01_Arrow_FAST_File
// 
//    Rev 1.10   Sep 29 2009 14:51:18   popescu
// Incident 1847231 - Default value of Option and Rate of Fee Type 112, 212, 113 and 213
// 
//    Rev 1.9   Sep 23 2009 14:24:28   jankovii
// IN 1848134 - Dealing Fee does not show up when entering InSpecies/Hybrid Purchase/Redemption
// 
//    Rev 1.8   Jan 31 2005 16:49:10   winnie
// PET 1117 FN08 : Transaction Fee is applicable as long as there is FeeParm set up for it. Not restricted to 3rdparty and Depot Fund only.
// 
//    Rev 1.7   Jan 23 2005 15:22:24   popescu
// PTS 10037685, read the charge option defaults and fee type defaults from view 253
// 
//    Rev 1.6   Jan 14 2005 10:31:08   popescu
// PTS 10037865, charge option field should be 'Charge' and locked for Conditionrate and all other fees, but TrxnFee where user should be allowed to change its value.
// 
//    Rev 1.5   Dec 10 2004 18:12:06   popescu
// PET 1117/06, more fixes
// 
//    Rev 1.4   Dec 10 2004 12:19:32   popescu
// PET 1117/56, make the fee less restrictive
// 
//    Rev 1.3   Dec 08 2004 22:08:34   popescu
// PET 1117/06, more fees
// 
//    Rev 1.2   Dec 02 2004 20:59:44   popescu
// PET 1117/06, more fee fixes
// 
//    Rev 1.1   Nov 24 2004 21:36:44   popescu
// PET 1117/06/56. trade processing, settle location
// 
//    Rev 1.0   Nov 18 2004 11:55:42   popescu
// Initial revision.
// 
//    Rev 1.3   Nov 17 2004 16:15:22   popescu
// PET 1117/06, Trade processing fees
// 
//    Rev 1.2   Nov 15 2004 16:23:20   popescu
// PET 1117/06, more synch to .NET changes
// 
//    Rev 1.0   Nov 05 2004 21:50:38   popescu
// Initial revision.
// 
 */