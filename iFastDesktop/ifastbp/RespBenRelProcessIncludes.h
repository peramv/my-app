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
//    Copyright 1997 by DST Systems, Inc.
//
//******************************************************************************

#include <ifastdataimpl\dse_listviewheading.hpp>

// Import/Export resolution
#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif

namespace IFASTBP_PROC
{
   extern IFASTBP_LINKAGE const BFContainerId RESP_ACCOUNT_BEN;
   extern IFASTBP_LINKAGE const BFContainerId RESP_BEN_JOINED_LIST;
   extern IFASTBP_LINKAGE const BFContainerId RESP_BEN_TO_JOIN_LIST;
}
namespace NASULIT //nasu literals
{
   extern IFASTBP_LINKAGE const I_CHAR * const CREATING_ACCOUNT;
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId LV_RESPBenRelJoinHeading;
   extern CLASS_IMPORT const BFTextFieldId LV_RESPBenRelJoinHeadingSet;
   extern CLASS_IMPORT const BFTextFieldId LastName;
   extern CLASS_IMPORT const BFTextFieldId FirstName;
   extern CLASS_IMPORT const BFTextFieldId EntityType;
   extern CLASS_IMPORT const BFNumericFieldId AccountNum;
   extern CLASS_IMPORT const BFIntegerFieldId RESPParentSeq;
   extern CLASS_IMPORT const BFIntegerFieldId RESPDesInstSeq;
   extern CLASS_IMPORT const BFNumericFieldId SeqNumber;

}



namespace RESPBEN
{
//container IDs
//CP20030319   const int RESP_BEN_TO_JOIN_LIST    =  1;
//CP20030319   const int RESP_BEN_JOINED_LIST   =  2; 
//CP20030319   const int RESP_ACCOUNT_BEN          =  3;

   extern IFASTBP_LINKAGE const I_CHAR * const BTN_JOIN;
   extern IFASTBP_LINKAGE const I_CHAR * const BTN_REMOVE;

   extern IFASTBP_LINKAGE const I_CHAR * const ACCOUNT_NUMBER;
   extern IFASTBP_LINKAGE const I_CHAR * const CURRENT_RESP_BEN;
}
