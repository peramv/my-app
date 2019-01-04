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
//    Copyright 1997 by DST Systems, Inc.
//
//******************************************************************************
//
// ^FILE   : DilutionProcessinclude.h
// ^AUTHOR : 
// ^DATE   : 03/15/2005
//
// ----------------------------------------------------------
//
// ^CLASS    : 
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :  This is the code for the Transaction Details dialog
//
//******************************************************************************


#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif

#include <ifastdataimpl\dse_dstc0339_vw.hpp>
#include <ifastdataimpl\dse_dstc0339_req.hpp>
#include <ifastdataimpl\dse_dstc0339_vwrepeat_record.hpp>

#include <bfproc/bfcontainerid.hpp>

namespace IFASTBP_PROC
{   
   extern IFASTBP_LINKAGE const BFContainerId DILUTION_LIST;
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/DilutionProcessIncludes.h-arc  $
//
//   Rev 1.0   Mar 03 2005 18:59:02   Fengyong
//Initial revision.
 */

