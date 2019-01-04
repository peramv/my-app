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
//    DATE   : June 2003
//
//******************************************************************************


#undef IFASTBP_LINKAGE
#ifdef IFASTBP_DLL
   #define IFASTBP_LINKAGE CLASS_EXPORT
#else
   #define IFASTBP_LINKAGE CLASS_IMPORT
#endif

#include <ifastdataimpl\dse_dstc0258_vw.hpp>

const BFFieldId HasItemsByBrokerCode(1);
const BFFieldId BrokerActive(2);

namespace IFASTBP_PROC
{
   extern IFASTBP_LINKAGE const BFContainerId PAY_TO_ENTITY_LIST;
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId BrokerName;
   extern CLASS_IMPORT const BFTextFieldId PayToEntityListHeading;
   extern CLASS_IMPORT const BFTextFieldId PayToEntityListHeadingSet;
	extern CLASS_IMPORT const BFTextFieldId PayToEntityListMgmtCoHeading;
   extern CLASS_IMPORT const BFDateFieldId CurrBusDate;
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/PayToEntityProcessIncludes.h-arc  $
//
//   Rev 1.4   Jul 27 2006 17:58:28   ZHANGCEL
//PET2192 FN11 - Commission Payments to MgmtCo related changes
//
//   Rev 1.3   Mar 04 2004 17:48:54   popescu
//PTS 10027865, fixed crash in Pay to entity search for inactive brokers. Disabled 'Instructions' button in pay to entity dialog if broker is inactive/not effective
//
//   Rev 1.2   Jul 09 2003 21:56:48   popescu
//Payment Instructiuons work, business rules implementation SSB_PET_821_FN17
//
//   Rev 1.1   Jul 01 2003 18:08:10   popescu
//Clean-up the code, new business rules, set the broker name to the dialog caption, etc...
//
//   Rev 1.0   Jun 27 2003 18:15:22   popescu
//Initial revision.
//
 * 
 */

