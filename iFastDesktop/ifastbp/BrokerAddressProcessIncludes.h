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
//    Copyright 2003 by DST Systems, Inc.
//
//******************************************************************************

// Here we would include the header files for all the data sets we use, later
// these will be automatically created from the dictionary manager - also, maybe
// this would be includes set up to include data sets used for a CBO we use.

#include <ifastdataimpl\dse_dstc0086_vw.hpp>  //intermediary
#include <ifastdataimpl\dse_dstc0090_vw.hpp>  //broker
#include <ifastdataimpl\dse_dstc0004_vw.hpp>
#include <ifastdataimpl\dse_dstc0116_vw.hpp> //broke/nominee address

#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif

// Need to define list and search ID's to be used by a GUI object talking to the
// process.

namespace IFASTBP_PROC
{
	extern IFASTBP_LINKAGE const BFContainerId BROKER_ADDRESS_LIST;
}
namespace ADDRLIT
{
   extern IFASTBP_LINKAGE const I_CHAR * const  ACCOUNT_NUM;
	extern IFASTBP_LINKAGE const I_CHAR * const	ADDRESS_CODE;
	extern IFASTBP_LINKAGE const I_CHAR * const	AddrLine1;
	extern IFASTBP_LINKAGE const I_CHAR * const	AddrLine2;
	extern IFASTBP_LINKAGE const I_CHAR * const	AddrLine3;
	extern IFASTBP_LINKAGE const I_CHAR * const	AddrLine4;
	extern IFASTBP_LINKAGE const I_CHAR * const	AddrLine5;
	extern IFASTBP_LINKAGE const I_CHAR * const	CountryCode;
	extern IFASTBP_LINKAGE const I_CHAR * const	PostCode;
}
namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId BrokerAddressHeadingSet;

}
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//


