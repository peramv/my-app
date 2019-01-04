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
// ^FILE   : ExchangeInFee.cpp
// ^AUTHOR : Serban Popescu
// ^DATE   : November 2004
//
// ^CLASS    : ExchangeInFee
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "exchangeinfee.hpp"

#include "trade.hpp"
#include "splitcommission.hpp"
#include "TransFeeList.hpp"

namespace
{
   // Trace literals
   const I_CHAR *  CLASSNAME  = I_("ExchangeInFee");
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
   extern const I_CHAR * EXCHANGE_IN;
}

namespace TRADETYPE
{
   extern CLASS_IMPORT I_CHAR * const EXCHANGE;
   extern CLASS_IMPORT I_CHAR * const INTER_CLASS_SWITCH;
}

//******************************************************************************
ExchangeInFee::ExchangeInFee (BFAbstractCBO &parent) : TransFeeRate (parent, FEES::EXCHANGE_IN)
{
   TRACE_CONSTRUCTOR (CLASSNAME, NULL_STRING);
}

//******************************************************************************
ExchangeInFee::~ExchangeInFee()
{
   TRACE_DESTRUCTOR (CLASSNAME);
}

//******************************************************************************
inline bool ExchangeInFee::useToSide ()
{
   return true;
}

//******************************************************************************
inline bool ExchangeInFee::ignoreTypeForFeeRate ()
{
   return true;
}

//******************************************************************************
bool ExchangeInFee::isSystemApplicable (const BFDataGroupId &idDataGroup)
{
   return SplitCommission::isTypeZERO (getWorkSession ());
}

//******************************************************************************
bool ExchangeInFee::isContextApplicable (const BFDataGroupId &idDataGroup)
{
   if (TransFee::isContextApplicable(idDataGroup))
   {
	   DString transType;

	   getContext().getField (ifds::TransType, transType, idDataGroup, false);
       return (transType == TRADETYPE::EXCHANGE || transType == TRADETYPE::INTER_CLASS_SWITCH) && 
		      hasFeeParams (idDataGroup);
   }
   return false;
}

//******************************************************************************
bool ExchangeInFee::hasContextChanged (const BFDataGroupId &idDataGroup)
{
//fee needs to be refreshed if any of the fee params request parameters changed
   bool retVal = false;
   retVal =  hasFeeParamsContextChanged (idDataGroup);

   if(!retVal)
   {
      TransFeeList *pTransFeeList = dynamic_cast <TransFeeList*> (getParent());
      if(pTransFeeList && pTransFeeList->getForcingRefresh())
      {
         retVal = true;
      }
   }
   return retVal;
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/ExchangeInFee.cpp-arc  $
// 
//    Rev 1.5   Mar 02 2005 08:40:52   popescu
// PET 1117/56 show and validate exch in/out fee base on set-up
// 
//    Rev 1.4   Mar 01 2005 18:19:18   winnie
// PET 1117 FN56 : Use ToFund and ToClass for getting the Exchange In Fee
// 
//    Rev 1.3   Nov 17 2004 16:14:56   popescu
// PET 1117/06, Trade processing fees
// 
//    Rev 1.2   Nov 15 2004 16:22:30   popescu
// PET 1117/06, more synch to .NET changes
// 
//    Rev 1.0   Nov 10 2004 09:31:14   popescu
// Initial revision.
// 
//    Rev 1.0   Nov 06 2004 00:35:04   popescu
// Initial revision.
// 
//    Rev 1.0   Nov 04 2004 11:03:16   popescu
// Initial revision.
// 
 */