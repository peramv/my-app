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
// ^FILE   : ClawbackFee.cpp
// ^AUTHOR : Serban Popescu
// ^DATE   : November 2004
//
// ^CLASS    : ClawbackFee
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "clawbackfee.hpp"

#include "funddetail.hpp"
#include "fundmasterlist.hpp"
#include "mgmtco.hpp"
#include "trade.hpp"

namespace
{
   // Trace literals
   const I_CHAR *  CLASSNAME  = I_("ClawbackFee");
}

namespace ifds
{
//mgmtco fields
   extern CLASS_IMPORT const BFTextFieldId DSCOverride;
//fees fields
   extern CLASS_IMPORT const BFTextFieldId TransType;
//fund fields
   extern CLASS_IMPORT const BFTextFieldId OverrideDSCAllow;
   extern CLASS_IMPORT const BFTextFieldId LoadType;
}

namespace CND
{  // Conditions used
}

namespace FEES
{
   extern const I_CHAR * CLAWBACK;
}

namespace TRADETYPE
{
   extern CLASS_IMPORT I_CHAR * const REDEMPTION;
}

//******************************************************************************
ClawbackFee::ClawbackFee (BFAbstractCBO &parent) : DSCFee (parent, FEES::CLAWBACK)
{
   TRACE_CONSTRUCTOR (CLASSNAME, NULL_STRING);
}

//******************************************************************************
ClawbackFee::~ClawbackFee()
{
   TRACE_DESTRUCTOR (CLASSNAME);
}

//******************************************************************************
bool ClawbackFee::isContextApplicable (const BFDataGroupId &idDataGroup)
{
   if (TransFee::isContextApplicable(idDataGroup))
   {
	   DString transType;

	   getContext().getField (ifds::TransType, transType, idDataGroup, false);
	   return  transType == TRADETYPE::REDEMPTION && 
			   hasFeeParams (idDataGroup) && 
			   isApplicableForFund (idDataGroup);
   }
   return false;
}

//******************************************************************************
bool ClawbackFee::hasContextChanged (const BFDataGroupId &idDataGroup)
{
//fee needs to be refreshed if any of these parameters change
   return hasFieldContextChanged (ifds::FromFund, idDataGroup) ||
          hasFieldContextChanged (ifds::FromClass, idDataGroup) ||
          hasFieldContextChanged (ifds::Amount, idDataGroup);
}

//******************************************************************************
bool ClawbackFee::isApplicableForFund (const BFDataGroupId &idDataGroup)
{
   bool bIsApplicable = false;

   DString fundCode,
      classCode;
   FundDetail *pFundDetail = NULL;
   
   getContext().getField (ifds::FromFund, fundCode, idDataGroup);
   getContext().getField (ifds::FromClass, classCode, idDataGroup);
   
   if ( !fundCode.empty() &&
        !classCode.empty() &&
         getWorkSession().
            getFundDetail (fundCode, classCode, idDataGroup, pFundDetail) && 
         pFundDetail)
   {
      DString overrideDSCAllow,
         loadType;
      
      pFundDetail->getField (ifds::OverrideDSCAllow, overrideDSCAllow, idDataGroup, false);
      pFundDetail->getField (ifds::LoadType, loadType, idDataGroup, false);
      bIsApplicable = overrideDSCAllow == I_("Y") && loadType == I_("CB"); //charge back
   }
   return bIsApplicable;
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/ClawbackFee.cpp-arc  $
// 
//    Rev 1.0   Nov 27 2011 19:14:18   popescu
// Initial revision.
// 
// 
 */