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
//    AUTHOR : Serban Popescu
//    DATE   : 01/08/2003
//
//******************************************************************************


#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif

#include <ifastdataimpl\dse_dstc0249_vw.hpp>
#include <ifastdataimpl\dse_dstc0249_req.hpp>
#include <ifastdataimpl\dse_dstc0249_vwrepeat_record.hpp>

namespace IFASTBP_PROC
{
   extern IFASTBP_LINKAGE const BFContainerId HISTORICAL_INFO_LIST;
}
namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId HistoricalListHeadingSet;
   extern CLASS_IMPORT const BFTextFieldId WorkType;
   extern CLASS_IMPORT const BFTextFieldId AWDObjectId;
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/HistoricalInfoProcessIncludes.hpp-arc  $
//
//   Rev 1.6   Sep 15 2008 03:38:36   phiwponp
//IN 1394896    Inconsistence of Historical screen title under pending trade - clean code
//
//   Rev 1.5   Sep 10 2008 05:44:06   phiwponp
//IN 1394896  Inconsistence of Historical screen title under pending trade
//
//   Rev 1.4   07 Nov 2007 00:18:28   popescu
//InternlAudit Project - 5563/01 added code for handling the AWD lookup button on the Historical Screen
//
//   Rev 1.3   Jun 30 2003 16:56:12   popescu
//added historical info search to the Broker Features search;
//moved some param names to the mfcaniterprocparam namespace
//
//   Rev 1.2   Mar 21 2003 17:41:02   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.1   Feb 03 2003 11:53:32   popescu
//Changed to support the KeyString field of the 249 view
//
//   Rev 1.0   Jan 28 2003 13:14:00   popescu
//Initial revision.
*/

