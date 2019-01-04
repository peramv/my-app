
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
//    Copyright 2005 by International Financial Data Services
//
//
//******************************************************************************
//
// ^FILE   : ATWithdraw.cpp
// ^AUTHOR :   
// ^DATE   : 
//
// ^CLASS    : ATWithdraw 
// ^SUBCLASS : Redemption
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include "stdafx.h"
#include "atwithdraw.hpp"


namespace
{
   //Trace literals
   const I_CHAR * const CLASSNAME = I_ ("ATWithdraw");
}

namespace ifds
{

}

namespace CND
{ 
	extern const long ERR_EXCLUDE_IS_NOT_ALLOWED;
}

namespace TRADETYPE
{
   extern CLASS_IMPORT I_CHAR * const AUTO_WITHDRAW;
}


//******************************************************************************

ATWithdraw::ATWithdraw (BFAbstractCBO &parent) : Redemption (parent), Trade (parent)
{
   
   TRACE_CONSTRUCTOR ( CLASSNAME, 
                       NULL_STRING);
  
}
//******************************************************************************
ATWithdraw::~ATWithdraw ()
{
   TRACE_DESTRUCTOR (CLASSNAME);
}     

//******************************************************************************
SEVERITY ATWithdraw::doInit (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("doInit"));

   setFieldNoValidate ( ifds::TradesTransType, 
                        TRADETYPE::AUTO_WITHDRAW, 
                        idDataGroup, 
                        false);
   return GETCURRENTHIGHESTSEVERITY ();
}

//****************************************************************************** 
SEVERITY ATWithdraw::validateESGSettle (const DString &strValue, const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("validateESGSettle")); 


	if (strValue == I_("Ex"))
	{
		DString dstrPayType, 
         dstrFromFund, 
         dstrAddressCode;

      getField (ifds::TradesPayType, dstrPayType, idDataGroup, false);
		getField (ifds::AddrCode, dstrAddressCode, idDataGroup, false);
		getField (ifds::FromFund, dstrFromFund, idDataGroup, false);
		if ( !( ( allowESGSettleForNominee (idDataGroup) || 
			       allowESGSettleForIntermediary (idDataGroup)) &&
				    dstrPayType == I_("S") &&
				    dstrAddressCode == I_("01") &&
				   !dstrFromFund.empty()))

		{
			ADDCONDITIONFROMFILE (CND::ERR_EXCLUDE_IS_NOT_ALLOWED);
		}
	}		
   return GETCURRENTHIGHESTSEVERITY ();
}


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/ATWithdraw.cpp-arc  $
// 
//    Rev 1.3   Mar 06 2006 14:28:10   popescu
// PET1334 - FN01 -- Added logic for ESGSettle enhancement - beautify during code review
// 
//    Rev 1.2   Mar 01 2006 13:57:50   ZHANGCEL
// PET1334 - FN01 -- Added logic for ESGSettle enhancement
// 
//    Rev 1.1   Aug 11 2005 10:26:14   popescu
// PET 1235 - Reeebok, few changes
// 
//    Rev 1.0   Jul 09 2005 13:01:48   Yingbaol
// Initial revision.
// 
// 
// 
*/
