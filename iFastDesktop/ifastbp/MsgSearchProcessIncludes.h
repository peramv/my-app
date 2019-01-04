#pragma once
//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by DST Systems, Inc.,
//    are proprietary in nature and as such are confIdential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2005
//    AUTHOR : 
//    DATE   : 
//
//******************************************************************************

#include <ifastdataimpl\dse_dstc0333_req.hpp>

#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId SearchUsing;
}

namespace IFASTBP_PROC
{
   extern IFASTBP_LINKAGE const BFContainerId SEARCH_CRITERIA_FILLER;
}

namespace MSG_SEARCH_TYPE
{
	const I_CHAR * const TRANSNUMBER = I_( "TransNum" );
   const I_CHAR * const AGGRORDNUM = I_( "AggrOrdRefNum" );
   const I_CHAR * const ACTIVITYID = I_( "ActivityID" );
   const I_CHAR * const SENDERREFNUM = I_( "SendersRefNum" );
   const I_CHAR * const NETWORKID = I_( "NetworkID" );
   const I_CHAR * const PROCESSTYPE = I_( "ProcessType" );
   const I_CHAR * const PROCESSCATEGORY = I_( "ProcessCategory" );
}


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastbp/MsgSearchProcessIncludes.h-arc  $
//
//   Rev 1.0   Feb 21 2005 11:09:26   hernando
//Initial revision.
