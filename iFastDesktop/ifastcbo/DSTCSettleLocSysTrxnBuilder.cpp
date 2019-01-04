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
// ^FILE   : DSTCSettleLocSysTrxnBuilder.cpp
// ^AUTHOR : 
// ^DATE   : 
//
// ----------------------------------------------------------
//
// ^CLASS : DSTCSettleLocSysTrxnBuilder
//
// ^MEMBER VARIABLES :  
//
// ^CODING COMMENTS  :
//
//******************************************************************************
#include "stdafx.h"
#include "ifasthosttransactioncontainer.hpp"

#include "DSTCSettleLocSysTrxnBuilder.hpp"
#include "dstclisttrxnbuilder.hpp"
#include "SettleLocationSysLvlList.hpp"
#include "SettleLocationSysLvl.hpp"

#include <dataimpl\dse_dstc0268_req.hpp>
#include <dataimpl\dse_dstc0268_reqrepeat_record.hpp>
#include <dataimpl\dse_dstc0268_vw.hpp>

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest SETTLE_LOCATION_SYS_UPDATE;
}

namespace
{
   const I_CHAR* CLASSNAME = I_( "DSTCSettleLocSysTrxnBuilder" );
   const I_CHAR* BUILDTRANSACTIONS = I_( "buildTransactions" );
}



//******************************************************************************
void DSTCSettleLocSysTrxnBuilder::buildTrxnKey( DString& dstrKey ) 
{
}

//******************************************************************************
SEVERITY DSTCSettleLocSysTrxnBuilder::buildTransactions( DSTCWorkSession &workSession,
   BFAbstractCBO* pObj, HostTransactionContainer* pTrCont, 
   BF_OBJ_ACTIVITY objActivity /*= OBJ_ACTIVITY_NONE*/ )
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, BUILDTRANSACTIONS);

   SettleLocationSysLvlList *pSettleLocationSysLvlList = dynamic_cast<SettleLocationSysLvlList*>(pObj);
   DSTCListTrxnBuilder<SettleLocationSysLvl*> settleLocSysTrxnBuilder;
   TRXNINFO settleLocSysTrxnInfo(I_("SettleLocationSysLvlList"), 
      DSTC_REQUEST::SETTLE_LOCATION_SYS_UPDATE,
      ifds::DSTC0268_REQ,
      ifds::DSTC0268_REQRepeat_Record,
      ifds::DSTC0268_VW);

   settleLocSysTrxnBuilder.buildTransactions(workSession, pTrCont, 
      pSettleLocationSysLvlList, settleLocSysTrxnInfo);
   return GETCURRENTHIGHESTSEVERITY();
}


//***********************************************
//R E V I S I O N   C O N T R O L   E N T R I E S
//***********************************************
// $Log:   Y:/VCS/BF iFAST/ifastcbo/DSTCSettleLocSysTrxnBuilder.cpp-arc  $
// 
//    Rev 1.1   Nov 14 2004 14:33:30   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.0   Nov 20 2003 11:08:38   HERNANDO
// Initial revision.
//
