//******************************************************************************SpreadFee
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
// ^FILE   : SpreadFee.cpp
// ^AUTHOR : Robbins Kuriakose
// ^DATE   : November 2015
//
// ^CLASS    : SpreadFee
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "SpreadFee.hpp"
#include "fundmasterlist.hpp"
#include "mgmtco.hpp"
#include "trade.hpp"

namespace
{
   // Trace literals
   const I_CHAR *  CLASSNAME  = I_("SpreadFee");
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
   extern const I_CHAR * PURCHASE_SPREAD_FEE;
   extern const I_CHAR * REDEMPTION_SPREAD_FEE;
   extern const I_CHAR * REDEMPTION_LIQUIDITY_FEE;
}

namespace TRADETYPE
{
   extern CLASS_IMPORT I_CHAR * const PURCHASE_LIKE;
   extern CLASS_IMPORT I_CHAR * const REDEMPTION;
   extern CLASS_IMPORT I_CHAR * const HYBRID_REDEMPTION;
   extern CLASS_IMPORT I_CHAR * const INSPECIES_REDEMPTION;
   extern CLASS_IMPORT I_CHAR * const INSP_NON_PRO_RATA_REDEMPTION; 
   extern CLASS_IMPORT I_CHAR * const EXCHANGE;
   extern CLASS_IMPORT I_CHAR * const ROLLOVER_EXCHANGE;

}

//******************************************************************************
SpreadFee::SpreadFee (BFAbstractCBO &parent, const DString &feeCode) : TrxnFee (parent, feeCode)
{
   TRACE_CONSTRUCTOR (CLASSNAME, NULL_STRING);
}

//******************************************************************************
SpreadFee::~SpreadFee()
{
   TRACE_DESTRUCTOR (CLASSNAME);
}

//******************************************************************************
void SpreadFee::doInitWithDefaultValues (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("doInitWithDefaultValues"));
   if (canBeInitialized (idDataGroup))
   {
      TrxnFee::doInitWithDefaultValues (idDataGroup);
   }
}

//******************************************************************************
inline bool SpreadFee::useFeeModelCode ()
{
   return true;
}

//******************************************************************************
bool SpreadFee::isSystemApplicable (const BFDataGroupId &idDataGroup)
{
   return true;
}

//******************************************************************************
bool SpreadFee::isContextApplicable (const BFDataGroupId &idDataGroup)
{
   if (TransFee::isContextApplicable(idDataGroup))
   {
	   DString transType,
		   feeCode;

	   getContext().getField (ifds::TransType, transType, idDataGroup, false);
	   getField (ifds::TransFeeCode, feeCode, idDataGroup, false);
	   if(feeCode == FEES::REDEMPTION_SPREAD_FEE)
	   {
	   return (( DSTCommonFunctions::codeInList (transType, TRADETYPE::PURCHASE_LIKE) &&
			                                       feeCode == FEES::PURCHASE_SPREAD_FEE ) ||
			     ( ( transType == TRADETYPE::REDEMPTION ||
			         transType == TRADETYPE::INSPECIES_REDEMPTION ||
			         transType == TRADETYPE::INSP_NON_PRO_RATA_REDEMPTION ))) &&
			       isApplicableForFund (idDataGroup) &&
			        hasFeeParams (idDataGroup); //use the fee model code
	   }
	   else if(feeCode == FEES::REDEMPTION_LIQUIDITY_FEE)
	   {
		   return ( ( transType == TRADETYPE::REDEMPTION ||
			         transType == TRADETYPE::INSPECIES_REDEMPTION ||
			         transType == TRADETYPE::INSP_NON_PRO_RATA_REDEMPTION ||   
			         transType == TRADETYPE::HYBRID_REDEMPTION ||
					 transType == TRADETYPE::EXCHANGE ||
					 transType == TRADETYPE::ROLLOVER_EXCHANGE)) &&
			       isApplicableForFund (idDataGroup) &&
			        hasFeeParams (idDataGroup); //use the fee model code
	   }
   }
   return false;
}

//******************************************************************************
bool SpreadFee::hasContextChanged (const BFDataGroupId &idDataGroup)
{
   return hasFeeParamsContextChanged (idDataGroup);
}

//******************************************************************************
bool SpreadFee::isApplicableForFund (const BFDataGroupId &idDataGroup)
{
   bool bIsApplicable = false;
   DString fundCode,
      classCode,
	  transType,
	  feeCode,
	  toFund,
	  toClass;
   
   getContext().getField (ifds::FromFund, fundCode, idDataGroup, false);
   getContext().getField (ifds::FromClass, classCode, idDataGroup, false);
   getContext().getField (ifds::TransType, transType, idDataGroup, false);
   getField (ifds::TransFeeCode, feeCode, idDataGroup, false);
   getContext().getField (ifds::ToFund, toFund, idDataGroup, false);   
   getContext().getField (ifds::ToClass, toClass, idDataGroup, false);
   bIsApplicable = !fundCode.empty() && !classCode.empty();

   if((transType == TRADETYPE::EXCHANGE || transType == TRADETYPE::ROLLOVER_EXCHANGE) && feeCode == FEES::REDEMPTION_LIQUIDITY_FEE )
	   bIsApplicable = !fundCode.empty() && !classCode.empty() && !toFund.empty() && !toClass.empty() && (fundCode != toFund);
	   
   return bIsApplicable;
}
//******************************************************************************
SEVERITY SpreadFee::doApplyRelatedChanges ( const BFFieldId &idField, 
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
/* $Log:   Y:/VCS/BF iFAST/ifastcbo\SpreadFee.cpp-arc  $

   1.0 Inital version 20/Nov/2015

*/