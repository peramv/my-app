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
//    AUTHOR : Shaobo Huang
//    DATE   : July, 2002
//
//******************************************************************************

// Here we would include the header files for all the data sets we use, later
// these will be automatically created from the dictionary manager - also, maybe
// this would be includes set up to include data sets used for a CBO we use.

// Should include data set includes used by search here

#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif
#include <ifastdataimpl\dse_dstc0058_vwrepeat_record.hpp>

// Need to define list and search Id's to be used by a GUI object talking to the
// process.
namespace IFASTBP_PROC
{
}
namespace ESTATEMENT
{
   const BFFieldId ACCOUNT_NUM(100);
   const BFFieldId RTS_SESSION_ID(101);
   const BFFieldId USER_ID(102);
   const BFFieldId LANGUAGE_ID(103);
   const BFFieldId LOCALE_ID(104);
   const BFFieldId MANAGEMENT_CO_ID(105);
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/EStatementProcessIncludes.h-arc  $
//
//   Rev 1.3   Mar 21 2003 17:39:30   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.2   Oct 09 2002 23:53:12   PURDYECH
//PVCS Database Conversion
//
//   Rev 1.1   Aug 29 2002 12:52:22   SMITHDAV
//ClientLocale and typed field changes.
//
//   Rev 1.0   31 Jul 2002 09:36:36   HUANGSHA
//Initial revision.
 * 
 */

