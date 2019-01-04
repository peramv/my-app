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
// ^FILE   : ContractMaturityInstructionProcessIncludes.h
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

#include <ifastdataimpl\dse_dstc0430_req.hpp>
#include <ifastdataimpl\dse_dstc0430_vwrepeat_record.hpp> //reqrepeat_record
#include <ifastdataimpl\dse_dstc0430_vw.hpp>

#include <ifastdataimpl\dse_dstc0431_req.hpp>
#include <ifastdataimpl\dse_dstc0431_reqrepeat_record.hpp> //reqrepeat_record
#include <ifastdataimpl\dse_dstc0431_vw.hpp>

#include <ifastdataimpl\dse_dstc0105_vw.hpp>
#include <ifastdataimpl\dse_dstc0105_vwrepeat_record.hpp>

#include <ifastdataimpl\dse_dstc0004_vw.hpp>
#include <ifastdataimpl\dse_dstc0004_vwrepeat_record.hpp>

#include <ifastdataimpl\dse_dstc0006_vw.hpp>
#include <ifastdataimpl\dse_dstc0006_vwrepeat_record.hpp>

#include <ifastdataimpl\dse_dstc0043_vwrepeat_record.hpp>
#include <ifastdataimpl\dse_dstc0043_vw.hpp>

namespace IFASTBP_PROC
{
	extern IFASTBP_LINKAGE const BFContainerId CONTRACT_MATURITY_INSTRUCTIONS;
	extern IFASTBP_LINKAGE const BFContainerId CONTRACTINFO_LIST;
	extern IFASTBP_LINKAGE const BFContainerId MFACCOUNT_CBO;
	extern IFASTBP_LINKAGE const BFContainerId ADDRESS_LIST;
	extern IFASTBP_LINKAGE const BFContainerId SHAREHOLDER_CBO;
	extern IFASTBP_LINKAGE const BFContainerId ACCOUNT_DETAILS_LIST;

	//extern IFASTBP_LINKAGE const BFContainerId MASTER_CONTRACT_LIST;
}

namespace CONMATINS_PROC
{
	const I_CHAR * const TRANS_ID_VALUE		= I_( "TransId" );
	const I_CHAR * const ACCOUNT_NUM_VALUE	= I_( "AccountNum" );
	const I_CHAR * const COT_REC_ID			= I_( "CotRecID" );
	const I_CHAR * const CONTRACT_TYPE		= I_( "ContractType" );
	const I_CHAR * const CONTRACT_TYPE_ID	= I_( "ContractTypeId" );
	const I_CHAR * const POLICY_YEAR		= I_( "PolicyYear" );
	const I_CHAR * const POLICY_TERM		= I_( "PolicyTerm" );
	const I_CHAR * const MATURITY_DATE		= I_( "MaturityDate" );
}