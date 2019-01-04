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

#include <ifastdataimpl\dse_dstc0090_vw.hpp>  //broker

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
	extern IFASTBP_LINKAGE const BFContainerId BROKER_LIST;
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId KYCRegulation;
   extern CLASS_IMPORT const BFTextFieldId AMLAgreement;
   extern CLASS_IMPORT const BFTextFieldId KYCSignture;
   extern CLASS_IMPORT const BFTextFieldId KYCStatus;
}


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//


