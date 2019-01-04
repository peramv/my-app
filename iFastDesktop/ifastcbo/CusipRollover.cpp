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
//    Copyright 2000 by International Financial Data Services
//
//
//******************************************************************************
//
// ^FILE   : CusipRollover.cpp
// ^AUTHOR :   
// ^DATE   : Jan, 2010
//
// ^CLASS    : CusipRollover - 
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include "stdafx.h"
#include "cusiprollover.hpp"

namespace TRADETYPE
{
	extern CLASS_IMPORT I_CHAR * const CUSIP_ROLLOVER;
}

namespace
{
	//Trace literals
	const I_CHAR * const CLASSNAME = I_ ("CusipRollover");
}


//******************************************************************************
CusipRollover::CusipRollover (BFAbstractCBO &parent) : Purchase (parent), Trade (parent)
{
	TRACE_CONSTRUCTOR (CLASSNAME, NULL_STRING);
}


//******************************************************************************
CusipRollover::~CusipRollover ()
{
	TRACE_DESTRUCTOR (CLASSNAME);
}     

//******************************************************************************
SEVERITY CusipRollover::doInit (const BFDataGroupId &idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("doInit"));

   setFieldNoValidate (ifds::TradesTransType, TRADETYPE::CUSIP_ROLLOVER, idDataGroup, false);

	return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/CusipRollover.cpp-arc  $
// 
//    Rev 1.0   Jan 29 2010 14:16:00   popescu
// Initial revision.
* 
*/