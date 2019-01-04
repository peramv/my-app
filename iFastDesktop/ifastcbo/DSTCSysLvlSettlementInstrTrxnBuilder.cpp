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
// ^FILE   : DSTCSysLvlSettlementInstrTrxnBuilder.cpp
// ^AUTHOR : 
// ^DATE   : 
//
// ----------------------------------------------------------
//
// ^CLASS : DSTCSysLvlSettlementInstrTrxnBuilder
//
// ^MEMBER VARIABLES :  
//
// ^CODING COMMENTS  :
//
//******************************************************************************
#include "stdafx.h"
#include "ifasthosttransactioncontainer.hpp"

#include "DSTCSysLvlSettlementInstrTrxnBuilder.hpp"
#include "dstclisttrxnbuilder.hpp"
#include "SysLvlSettlementInstrList.hpp"
#include "SysLvlSettlementInstr.hpp"

#include <ifastdataimpl\dse_dstc0268_req.hpp>
#include <ifastdataimpl\dse_dstc0268_reqrepeat_record.hpp>
#include <ifastdataimpl\dse_dstc0268_vw.hpp>

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest SETTLE_LOCATION_SYS_UPDATE;
}

namespace
{
   const I_CHAR* CLASSNAME = I_( "DSTCSysLvlSettlementInstrTrxnBuilder" );
   const I_CHAR* BUILDTRANSACTIONS = I_( "buildTransactions" );
}



//******************************************************************************
void DSTCSysLvlSettlementInstrTrxnBuilder::buildTrxnKey( DString& dstrKey ) 
{
}

//******************************************************************************
SEVERITY DSTCSysLvlSettlementInstrTrxnBuilder::buildTransactions( DSTCWorkSession &workSession,
   BFAbstractCBO* pObj, HostTransactionContainer* pTrCont, 
   BF_OBJ_ACTIVITY objActivity /*= OBJ_ACTIVITY_NONE*/ )
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, BUILDTRANSACTIONS);

   SysLvlSettlementInstrList *pSysLvlSettlementInstrList = dynamic_cast<SysLvlSettlementInstrList*>(pObj);
   DSTCListTrxnBuilder<SysLvlSettlementInstr*> sysLvlSettlementInstrTrxnBuilder;
   TRXNINFO sysLvlSettlementInstrTrxnInfo(I_("SysLvlSettlementInstrList"), 
      DSTC_REQUEST::SETTLE_LOCATION_SYS_UPDATE,
      ifds::DSTC0268_REQ,
      ifds::DSTC0268_REQRepeat_Record,
      ifds::DSTC0268_VW);

   sysLvlSettlementInstrTrxnBuilder.buildTransactions(workSession, pTrCont, 
      pSysLvlSettlementInstrList, sysLvlSettlementInstrTrxnInfo);
   return GETCURRENTHIGHESTSEVERITY();
}


//***********************************************
//R E V I S I O N   C O N T R O L   E N T R I E S
//***********************************************
// $Log:   Y:/VCS/BF iFAST/ifastcbo/DSTCSysLvlSettlementInstrTrxnBuilder.cpp-arc  $
// 
//    Rev 1.1   Nov 14 2004 14:33:48   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.0   Oct 13 2004 13:23:28   VADEANUM
// Initial revision.
// 
//    Rev 1.0   Nov 20 2003 11:08:38   HERNANDO
// Initial revision.
//
