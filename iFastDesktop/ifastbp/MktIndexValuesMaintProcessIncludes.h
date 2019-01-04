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
//    Copyright 2003 by International Financial Data Services
//    AUTHOR : 
//    DATE   : 
//
//******************************************************************************

#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif

namespace IFASTBP_PROC
{
   extern IFASTBP_LINKAGE const BFContainerId FUNDS_LIST;
   extern IFASTBP_LINKAGE const BFContainerId INDICES_LIST;
}
namespace INDEX_VALUES
{
//CP20030319   const int INDICES_LIST = 1;
//CP20030319   const int FUNDS_LIST = 2;
   const BFFieldId FUNDDESC( 1000 );
}
const BFContainerId MKT_INDEX_SEARCH (1002);
const BFFieldId InputDataType (20019, I_("InputDataType"));
const BFFieldId HAS_OBJECT_UPDATE(1003);

namespace MKTINDEXPROC	
{
	//Fields names
	const I_CHAR * const SEARCH_TYPE		= I_( "SearchType" );
	const I_CHAR * const INDEX_CODE			= I_( "IndexCode" );
	const I_CHAR * const DATE			    = I_( "Date" );	
}
namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId IndexValuesHeading;
   extern CLASS_IMPORT const BFTextFieldId IndexFundsHeading;
   extern CLASS_IMPORT const BFTextFieldId FundNumber;
   extern CLASS_IMPORT const BFTextFieldId ElongName1;
}

const BFFieldId PERCENTAGE_CHANGED(100);

extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_FUNDCLASS;

#include <ifastdataimpl\dse_dstc0241_vw.hpp>
#include <ifastdataimpl\dse_dstc0241_req.hpp>
#include <ifastdataimpl\dse_dstc0247_vw.hpp>
#include <ifastdataimpl\dse_dstc0247_req.hpp>
#include <ifastdataimpl\dse_dstc0248_vw.hpp>
#include <ifastdataimpl\dse_dstc0248_req.hpp>

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/MktIndexValuesMaintProcessIncludes.h-arc  $
//
//   Rev 1.3   Jan 16 2012 14:43:22   wp040027
//P0188394_Performance Fees - Benchmark Upload
//
//   Rev 1.2   Mar 21 2003 17:45:36   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.1   Feb 07 2003 14:15:40   HERNANDO
//Added Fund Description.
//
//   Rev 1.0   Jan 29 2003 12:51:46   HERNANDO
//Initial Revision
//
//   Rev 1.0   Jan 23 2003 10:29:06   HERNANDO
//Initial Revision
 */

