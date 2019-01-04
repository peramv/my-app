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
// ^FILE   : ExchangeOutFee.cpp
// ^AUTHOR : Serban Popescu
// ^DATE   : November 2004
//
// ^CLASS    : ExchangeOutFee
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "exchangeoutfee.hpp"

#include "trade.hpp"
#include "splitcommission.hpp"

namespace
{
   // Trace literals
   const I_CHAR *  CLASSNAME  = I_("ExchangeOutFee");
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
   extern const I_CHAR * EXCHANGE_OUT;
}

namespace TRADETYPE
{
   extern CLASS_IMPORT I_CHAR * const EXCHANGE;
   extern CLASS_IMPORT I_CHAR * const INTER_CLASS_SWITCH;
}

//******************************************************************************
ExchangeOutFee::ExchangeOutFee (BFAbstractCBO &parent) : TransFeeRate (parent, FEES::EXCHANGE_OUT)
{
   TRACE_CONSTRUCTOR (CLASSNAME, NULL_STRING);
}

//******************************************************************************
ExchangeOutFee::~ExchangeOutFee()
{
   TRACE_DESTRUCTOR (CLASSNAME);
}

//******************************************************************************
inline bool ExchangeOutFee::ignoreTypeForFeeRate ()
{
   return true;
}

//******************************************************************************
bool ExchangeOutFee::isSystemApplicable (const BFDataGroupId &idDataGroup)
{
   return SplitCommission::isTypeZERO (getWorkSession ());
}

//******************************************************************************
bool ExchangeOutFee::isContextApplicable (const BFDataGroupId &idDataGroup)
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
bool ExchangeOutFee::hasContextChanged (const BFDataGroupId &idDataGroup)
{
//fee needs to be refreshed if any of the fee params request parameters changed
   return hasFeeParamsContextChanged (idDataGroup);
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/ExchangeOutFee.cpp-arc  $
// 
//    Rev 1.4   Mar 02 2005 08:41:02   popescu
// PET 1117/56 show and validate exch in/out fee base on set-up
// 
//    Rev 1.3   Nov 17 2004 16:15:00   popescu
// PET 1117/06, Trade processing fees
// 
//    Rev 1.2   Nov 15 2004 16:22:32   popescu
// PET 1117/06, more synch to .NET changes
// 
//    Rev 1.0   Nov 10 2004 09:31:18   popescu
// Initial revision.
// 
//    Rev 1.0   Nov 06 2004 00:35:04   popescu
// Initial revision.
// 
//    Rev 1.0   Nov 04 2004 11:03:16   popescu
// Initial revision.
// 
 */