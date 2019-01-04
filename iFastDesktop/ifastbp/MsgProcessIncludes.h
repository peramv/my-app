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
//
//******************************************************************************

#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif

#include <ifastdataimpl\dse_dstc0333_vw.hpp>
#include <ifastdataimpl\dse_dstc0336_vw.hpp>
#include <ifastdataimpl\dse_dstc0335_vw.hpp>

namespace IFASTBP_PROC
{
   extern IFASTBP_LINKAGE const BFContainerId SEARCH_CRITERIA_FILLER;
   extern IFASTBP_LINKAGE const BFContainerId MSG_PROCESS_LIST;
   extern IFASTBP_LINKAGE const BFContainerId MSG_ACTIVITY_LIST;
   extern IFASTBP_LINKAGE const BFContainerId MSG_EVENT_LIST;
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId MsgProcessHeading;
   extern CLASS_IMPORT const BFTextFieldId MsgActivityHeading;
   extern CLASS_IMPORT const BFTextFieldId MsgEventHeading;
}

extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_MSG_DETAIL;

const BFFieldId OVERRIDE1( 100 );
const BFFieldId OVERRIDE2( 101 );

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastbp/MsgProcessIncludes.h-arc  $
//
//   Rev 1.1   Apr 21 2005 11:15:58   hernando
//Incident #278666 - Added OVERRIDE2.
//
//   Rev 1.0   Feb 21 2005 11:09:14   hernando
//Initial revision.
