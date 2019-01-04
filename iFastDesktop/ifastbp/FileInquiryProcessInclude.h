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
//    Copyright 2002 by Internantional Financial.
//
//******************************************************************************


#include <ifastdataimpl\dse_listviewheading.hpp>
#include <ifastdataimpl\dse_dstc0332_vw.hpp>
#include <ifastdataimpl\dse_dstc0332_req.hpp>
#include <ifastdataimpl\dse_dstc0335_vw.hpp>

// Import/Export resolution
#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif

namespace IFASTBP_PROC
{
   extern IFASTBP_LINKAGE const BFContainerId MSG_ENVELOPE_LIST;
	extern IFASTBP_LINKAGE const BFContainerId MSG_EVENT_LIST;
   
}
namespace FILESEARCH
{
   
	const I_CHAR * const NETWORKID				= I_( "NetWorkId" );
	const I_CHAR * const FILENAME					= I_( "FileName" ); 
	const I_CHAR * const STARTDATE				= I_( "StartDate" ); 
	const I_CHAR * const ENDDATE					= I_( "EndDate" ); 
}
namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId  NetworkID;
	extern CLASS_IMPORT const BFTextFieldId  FileName;
	extern CLASS_IMPORT const BFDateFieldId  StartDate;
	extern CLASS_IMPORT const BFDateFieldId  EndDate;
	extern CLASS_IMPORT const BFTextFieldId  EnvelopeStatus;
	extern CLASS_IMPORT const BFDateFieldId  ProcessDate;
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/FileInquiryProcessInclude.h-arc  $
//
//   Rev 1.0   Feb 24 2005 17:18:18   ZHANGCEL
//Initial revision.
 * 
 */