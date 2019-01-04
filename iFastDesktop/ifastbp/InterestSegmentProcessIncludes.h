#pragma once
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
//    Copyright 1999 by DST Systems, Inc.
//
//******************************************************************************

//******************************************************************************
//
// ^FILE   : InterestSegmentProcessIncludes.h
// ^AUTHOR :  
// ^DATE   : 
//
// -----------------------------------------------------------------------------


// Import/Export resolution
#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif

#include <ifastdataimpl\dse_dstc0422_req.hpp>
#include <ifastdataimpl\dse_dstc0422_vwrepeat_record.hpp> //reqrepeat_record
#include <ifastdataimpl\dse_dstc0422_vw.hpp>

namespace IFASTBP_PROC
{
   extern IFASTBP_LINKAGE const BFContainerId INTEREST_SEGMENT_LIST;
}

namespace INTSEGMENT
{
	//Fields names
	const I_CHAR * const ACCOUNT_NUM_VALUE	= I_( "AccountNum" );
	const I_CHAR * const INVEST_ID			= I_( "InvHisInvestId" );
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/InterestSegmentProcessIncludes.h-arc  $
//
//   Rev 1.0   Dec 13 2011 10:11:22   wp040100
//Initial revision.
//
//
//
 * 
 * 
// 
*/