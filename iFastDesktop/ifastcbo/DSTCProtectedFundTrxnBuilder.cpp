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
//    Copyright 1999 by DST Systems, Inc.
//
//
//******************************************************************************
//
// ^FILE   : DSTCProtectedFundTrxnBuilder.cpp
// ^AUTHOR : Serban Popescu
// ^DATE   : Jan 2003
//
// ----------------------------------------------------------
//
// ^CLASS : DSTCProtectedFundTrxnBuilder
//
// ^MEMBER VARIABLES :  
//
// ^CODING COMMENTS  :
//
//******************************************************************************
#include "stdafx.h"
#include "ifasthosttransactioncontainer.hpp"

#include "dstcprotectedfundtrxnbuilder.hpp"
#include "dstclisttrxnbuilder.hpp"
#include "protectedfundlist.hpp"
#include "protectedfund.hpp"

#include <ifastdataimpl\dse_dstc0238_req.hpp>
#include <ifastdataimpl\dse_dstc0238_reqrepeat_record.hpp>
#include <ifastdataimpl\dse_dstc0238_vw.hpp>

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest PROTECTED_FUND_LIST_UPDATE;
}

namespace
{
   const I_CHAR* CLASSNAME = I_( "DSTCProtectedFundTrxnBuilder" );
   const I_CHAR* BUILDTRANSACTIONS = I_( "buildTransactions" );
}



//******************************************************************************
void DSTCProtectedFundTrxnBuilder::buildTrxnKey( DString& dstrKey ) 
{
}

//******************************************************************************
SEVERITY DSTCProtectedFundTrxnBuilder::buildTransactions( DSTCWorkSession &workSession,
   BFAbstractCBO* pObj, HostTransactionContainer* pTrCont, 
   BF_OBJ_ACTIVITY objActivity /*= OBJ_ACTIVITY_NONE*/ )
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, BUILDTRANSACTIONS);

   ProtectedFundList *pProtectedFundList = dynamic_cast<ProtectedFundList*>(pObj);
   DSTCListTrxnBuilder<ProtectedFund*> protectedFundTrxnBuilder;
   TRXNINFO protectedFundTrxnInfo(I_("ProtectedFundList"), 
      DSTC_REQUEST::PROTECTED_FUND_LIST_UPDATE,
      ifds::DSTC0238_REQ,
      ifds::DSTC0238_REQRepeat_Record,
      ifds::DSTC0238_VW);

   protectedFundTrxnBuilder.buildTransactions(workSession, pTrCont, 
      pProtectedFundList, protectedFundTrxnInfo);
   return GETCURRENTHIGHESTSEVERITY();
}


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/DSTCProtectedFundTrxnBuilder.cpp-arc  $
// 
//    Rev 1.6   Nov 14 2004 14:33:12   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.5   Jul 08 2003 13:34:52   popescu
// Used the DSTCListTrxnBuilder.hpp for building the transactions
// 
//    Rev 1.4   Mar 21 2003 18:06:28   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.3   Jan 20 2003 15:43:30   popescu
// Checked in for unit testing the ProtectedFundSetup feature
// 
//    Rev 1.2   Jan 10 2003 10:23:22   popescu
// Changed the promotion groups
 *
 */